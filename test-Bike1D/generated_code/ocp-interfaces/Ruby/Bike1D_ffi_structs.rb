#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Bike1D_ffi_structs.rb                                             #
#                                                                          #
#  version: 1.0   date 3/4/2022                                            #
#                                                                          #
#  Copyright (C) 2022                                                      #
#                                                                          #
#      Enrico Bertolazzi and Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      Via Mesiano 77, I-38050 Trento, Italy                               #
#      email: enrico.bertolazzi@ing.unitn.it                               #
#             francesco.biral@ing.unitn.it                                 #
#             paolo.bosetti@ing.unitn.it                                   #
#                                                                          #
############################################################################

module Bike1D

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Bike1D_solver_params < FFI::Struct
    layout(
      :max_iter,             :index_t,
      :max_step_iter,        :index_t,
      :max_accumulated_iter, :index_t,
      :tolerance,            :data_t,
    )
    def initialize
      self[:max_iter]      = 500
      self[:max_step_iter] = 20
      self[:tolerance]     = 1e-10
    end
  end

  class Bike1D_model_params < FFI::Struct
    layout(

      :Pmax,    :data_t,

      :g,       :data_t,

      :m,       :data_t,

      :muf_min, :data_t,

      :mur_max, :data_t,

      :mur_min, :data_t,

      :v_f,     :data_t,

      :v_i,     :data_t,

      :v_min,   :data_t,

      :vmax,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Bike1D_BC_params < FFI::Struct
    layout(

      :initial_v, :bool,

      :final_v,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Bike1D_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :vMinLimitSubType, :index_t,
      :vMinLimitEpsilon, :data_t,
      :vMinLimitTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :murControlType,      :index_t,
      :murControlEpsilon,   :data_t,
      :murControlTolerance, :data_t,
      :mufControlType,      :index_t,
      :mufControlEpsilon,   :data_t,
      :mufControlTolerance, :data_t,
    )

    def initialize
      members.each do |m|
        case self[m]
        when Float
          self[m] = Float::NAN
        when Fixnum
          self[m] = 0
        when FFI::Pointer
          self[m] = nil
        else
          warn "Unmanaged initialization type in struct (for field #{m} of type #{self[m].class})"
        end
      end
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  attach_function :setup_model, # ruby name
                  :Bike1D_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Bike1D_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Bike1D_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Bike1D_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Bike1D_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Bike1D_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Bike1D_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Bike1D_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Bike1D_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Bike1D_ffi_stucts.rb
