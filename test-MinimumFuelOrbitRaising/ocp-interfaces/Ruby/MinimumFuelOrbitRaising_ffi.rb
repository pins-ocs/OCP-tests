#-----------------------------------------------------------------------#
#  file: MinimumFuelOrbitRaising_run.rb                                 #
#                                                                       #
#  version: 1.0   date 28/3/2020                                        #
#                                                                       #
#  Copyright (C) 2020                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#


HOST_OS = RbConfig::CONFIG['host_os']
@ext    = ".noextension"
case HOST_OS
when /mac|darwin/
  DYLIB_EXT = 'dylib';
when /linux|cygwin|bsd/
  DYLIB_EXT = 'so';
when /mswin|win|mingw/
  DYLIB_EXT = 'dll';
end

MECHATRONIX_LIB_PATH = File.expand_path('../../../lib', __FILE__)

module GenericContainer
  @libGenericContainer = MECHATRONIX_LIB_PATH+"/libMinimumFuelOrbitRaising.#{DYLIB_EXT}"
end

module Splines
  @libSplines = MECHATRONIX_LIB_PATH+"/libMinimumFuelOrbitRaising.#{DYLIB_EXT}"
end

require_relative 'GenericContainer_ffi.rb';
require_relative 'Splines_ffi.rb';
require 'pp'

module Mechatronix
  SET  = true
  FREE = false
end

module MinimumFuelOrbitRaising

  extend FFI::Library

  LIB_PATH = MECHATRONIX_LIB_PATH+"/libMinimumFuelOrbitRaising.#{DYLIB_EXT}"

  raise RuntimeError, "Missing library #{LIB_PATH}" unless File.exist? LIB_PATH
  begin
    ffi_lib LIB_PATH
  rescue
    warn "remember to run export DYLD_LIBRARY_PATH=#{LIB_PATH}"
    exit
  end

  attach_function :OCP_setup,
                  :MinimumFuelOrbitRaising_ocp_setup,
                  [ :string, :buffer_in ], :bool

  attach_function :OCP_guess,
                  :MinimumFuelOrbitRaising_ocp_guess,
                  [ :string, :buffer_in ], :bool

  attach_function :OCP_solve,
                  :MinimumFuelOrbitRaising_ocp_solve,
                  [ :string, :buffer_in, :buffer_out ], :bool

  attach_function :OCP_write_ocp_solution,
                  :MinimumFuelOrbitRaising_write_ocp_solution,
                  [ :string, :string ], :void

  class OCPSolver
    attr_accessor :data
    attr_reader   :id, :id_solution

    def initialize(data=nil)
      @id          = self.__id__.to_s
      @id_solution = @id+"_solution"
      self.data    = (data || Mechatronix.content)
      ok = GenericContainer.GC_select @id_solution
      ok = GenericContainer.GC_new @id_solution unless ok == 0
      raise RuntimeError, "Failed to create/select generic object: #{@id_solution}\n" unless ok == 0
      ok = GenericContainer.GC_select @id
      ok = GenericContainer.GC_new @id unless ok == 0
      raise RuntimeError, "Failed to create/select generic object: #{@id}\n" unless ok == 0
      ObjectSpace.define_finalizer(self, proc { GenericContainer.GC_delete @id; GenericContainer.GC_delete @id_solution })
      return @id
    end

    def get_result( id )
      ok = GenericContainer.GC_select id
      raise RuntimeError, "Failed to select generic object: #{id}\n" unless ok == 0
      out = GenericContainer.GC_to_hash
      raise RuntimeError, "Failed to convert generic object: #{id} to hash\n" unless out
      return out;
    end

    def set_data( id, data )
      ok = GenericContainer.GC_select id
      ok = GenericContainer.GC_new id unless ok == 0
      raise RuntimeError, "Failed to select or create generic object: #{id}\n" unless ok == 0
      GenericContainer.GC_from_hash data
    end

    def solve( convert = true )
      set_data( @id, @data );

      ok = MinimumFuelOrbitRaising.OCP_setup( @id, GenericContainer.GC_mem_ptr(@id) )
      raise RuntimeError, "Failed to do setup: #{out[:Error]}\n" unless ok

      ok = MinimumFuelOrbitRaising.OCP_guess( @id, GenericContainer.GC_mem_ptr(@id) )
      raise RuntimeError, "Failed to do guess: #{out[:Error]}\n" unless ok

      ok  = MinimumFuelOrbitRaising.OCP_solve( @id,
                                      GenericContainer.GC_mem_ptr(@id),
                                      GenericContainer.GC_mem_ptr(@id_solution) )
      out = self.get_result( @id_solution )
      raise RuntimeError, "Failed to do solve: #{out[:Error]}\n" unless ok

      if convert then
        if out[:Error] then
          raise RuntimeError, "Failed to compute: #{out[:Error]}\n"
        else
          idx  = out[:idx]
          data = out[:data]
          tmp  = {}
          out[:headers].each { |h| tmp[h.to_sym] = data[idx[h.to_sym]].dup }
          out.delete(:idx);
          out.delete(:data);
          out[:data] = tmp;
        end
      end
      return out
    end

    def write_ocp_solution( fname )
      MinimumFuelOrbitRaising.OCP_write_ocp_solution( @id, fname )
    end

  end

end

module Mechatronix
  @@content = nil
  def self.content=(v); @@content = v; end
  def self.content;     @@content;     end

  class Container
    attr_accessor :name, :match, :content
    attr_reader   :key_converter

    def self.[](hsh)
      raise ArgumentError, "Need a Hash" unless hsh.respond_to? :to_hash
      m = self.new
      hsh.to_hash.each do |k,v|
        m.send("#{k}=".to_sym, v)
      end
      return m
    end

    def initialize(name="My model")
      @name = name
      @match = /^[A-Z]/
      @content= Hash.new
      @key_converter = :to_sym
      return self
    end

    def keys; @content.keys; end

    def key_converter=(sym)
      raise RuntimeError, "Either :to_s or :to_sym" unless [:to_s, :to_sym].include? sym
      @key_converter = sym
    end

    def [](key)
      return @content[key.send(@key_converter)]
    end

    def []=(key, value)
      @content[key.send(@key_converter)] = value
    end

    def method_missing name, *args, &block
      unless name.to_s.match(@match)
        raise RuntimeError, "Undefined method #{name}"
      end

      case name.to_s
      when /=$/
        key = name.to_s.chop.to_sym
        @content[key.send(@key_converter)] = args.first
      else
        return @content[name.send(@key_converter)]
      end
    end

    def inspect
      return @content.inspect
    end

    alias :to_hash :content
  end

  class Mesh
    class ParsingError < Exception; end

    attr_reader :segments, :s0, :default_mesh, :wrong_indexes

    def initialize(s0=0, ms=0.01)
      @segments               = []
      @s0                     = s0
      @default_mesh_grid_size = ms
      @wrong_indexes          = []
    end

    def << arg
      s = {}
      case arg
      when Numeric
        s = { :length => arg.to_f, :n => len_to_n(arg)}
      when Hash
        # la lunghezza deve esserci sempre!
        if arg[:n] then
          s = {
            :length => arg[:length].to_f,
            :n      => arg[:n].to_i
          }
        elsif arg[:grid_size] then
          s = {
            :length => arg[:length].to_f,
            :n      => len_to_n(arg[:length], arg[:grid_size])
          }
        elsif arg[:length]
          s = {
            :length => arg[:length].to_f,
            :n      => len_to_n(arg[:length])
          }
        else
          raise ParsingError
        end
      else
        raise ParsingError
      end
      raise ParsingError unless s[:length].kind_of?(Float) && s[:n].kind_of?(Fixnum)
    rescue ParsingError
      s = arg
      @wrong_indexes << @segments.length
    ensure
      @segments << s
    end

    def consistent?
      return @wrong_indexes.empty?
    end

    def to_hash
      hash = {}
      self.instance_variables.map { |var| hash[var.to_s[1..-1].to_sym] = self.instance_variable_get(var) }
      return hash
    end

  private # da qui in poi i metodi sono privati, occhio!
    def len_to_n(arg, gs=@default_mesh_grid_size)
      ((arg + gs) / gs).to_i
    rescue
      nil
    end
  end

  class Road < Container
    def initialize()
      super("road")
      self.MeshGridSize = 1
      self.RoadWidth    = 6
      self.Segments     = []
      self.Theta0       = 0  # initial orientation in x-y plane\n"
      self.S0           = 0  # initial curvilinear abscissa\n"
      self.X0           = 0  # initial x position of road middle line\n"
      self.Y0           = 0  # initial y position of road middle line\n"
      self.Z0           = 0  # initial z position of road middle line\n"
      self.Banking0     = 0  # initial y position of road middle line\n"
      self.IsSAE        = false
    end

    def << hsh
      raise ArgumentError, "Need a kind of Hash" unless hsh.respond_to? :to_hash
      hsh = hsh.to_hash
      if hsh[:Radius] then
        curvature = 1.0/hsh[:radius]
        if hsh[:Angle] then
          length = (hsh[:Angle] / hsh[:Curvature] ).abs
        elsif hsh[:AngleDeg] then
          length = ((Math::PI*hsh[:AngleDeg]/180.0) / hsh[:Curvature] ).abs
        else
          raise RuntimeError, "Missing Angle field in Road segment #{self.Segments.length}"
        end
        initialCurvature = finalCurvature = curvature
      else
        initialCurvature = hsh[:InitialCurvature] || hsh[:Curvature] || 0;
        finalCurvature   = hsh[:FinalCurvature]   || hsh[:Curvature] || 0;
        raise RuntimeError, "Missing Length field in Road segment #{self.Segments.length}" unless hsh[:Length]
        length           = hsh[:Length]
      end
      self.Segments << {
        Length:            length,
        GridSize:          hsh[:GridSize]                || self.MeshGridSize,
        Width:             hsh[:Width]                   || self.RoadWidth,
        InitialCurvature:  initialCurvature,
        FinalCurvature:    finalCurvature,
        InitialLeftWidth:  hsh[:InitialLeftWidth]        || hsh[:LeftWidth]  || self.RoadWidth / 2.0,
        FinalLeftWidth:    hsh[:FinalLeftWidth]          || hsh[:LeftWidth]  || self.RoadWidth / 2.0,
        InitialRightWidth: hsh[:InitialRightWidth]       || hsh[:RightWidth] || self.RoadWidth / 2.0,
        FinalRightWidth:   hsh[:FinalRightWidth]         || hsh[:RightWidth] || self.RoadWidth / 2.0,
        SpeedLimit:        hsh[:SpeedLimit]              || 300,
        Adherence:         hsh[:FrictionReductionFactor] || hsh[:adherence]  || 1,
        FinalZ:            hsh[:End_z]                   || hsh[:z]          || 0,
        FinalBanking:      hsh[:End_banking]             || hsh[:banking]    || 0
      }
  end
  def consistent?
      return true
    end
  end

  class ToolPath2D
    attr_reader :toolPath2D

    def initialize(pars = {})
      self.init pars
    end

    def init(pars = {})
      @toolPath2D = {:segments => [] }
      @defaultFeedRate     = pars[:defaultFeedRate]     || 0.1
      @defaultSpindleRate  = pars[:defaultSpindleRate]  || 500
      @defaultCrossSection = pars[:defaultCrossSection] || 0.01
      @defaultN            = pars[:defaultN]            || 10
    end

    def <<(pars)
      x0           = pars[:x0]
      y0           = pars[:y0]
      x1           = pars[:x1]
      y1           = pars[:y1]
      n            = pars[:n]            || @defaultN
      feedRate     = pars[:feedRate]     || @defaultFeedRate
      spindleRate  = pars[:spindleRate]  || @defaultSpindleRate
      crossSection = pars[:crossSection] || @defaultCrossSection

      tmp = {
        :x0           => x0,
        :y0           => y0,
        :x1           => x1,
        :y1           => y1,
        :feedRate     => feedRate,
        :spindleRate  => spindleRate,
        :crossSection => crossSection,
        :n            => n
      }

      tmp[:angle0] = pars[:angle0] if pars.key? :angle0
      tmp[:angle1] = pars[:angle1] if pars.key? :angle1
      @toolPath2D[:segments] << tmp
    end
    alias add <<

    def to_h; @toolPath2D; end
    alias :to_hash :to_h

  end #class ToolPath2D

end

def self.mechatronix(name=nil, &block)
  unless (Mechatronix.content && Mechatronix.content.kind_of?(Mechatronix::Container)) then
    Mechatronix.content = Mechatronix::Container.new(name)
  end
  yield Mechatronix.content
end

alias require_relative_old require_relative
def require_relative(f, base)
  require_relative_old(f)
end

# EOF: MinimumFuelOrbitRaising_ffi.rb
