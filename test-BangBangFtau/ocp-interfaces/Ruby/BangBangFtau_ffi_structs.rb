#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: BangBangFtau_ffi_structs.rb                                       #
#                                                                          #
#  version: 1.0   date 5/3/2021                                            #
#                                                                          #
#  Copyright (C) 2021                                                      #
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

module BangBangFtau

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class BangBangFtau_solver_params < FFI::Struct
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

  class BangBangFtau_model_params < FFI::Struct
    layout(

      :epsiTB,  :data_t,

      :maxClip, :data_t,

      :maxT,    :data_t,

      :minClip, :data_t,

      :tauB,    :data_t,

      :tauT,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class BangBangFtau_BC_params < FFI::Struct
    layout(

      :initial_x,  :bool,

      :initial_v,  :bool,

      :initial_sT, :bool,

      :initial_sB, :bool,

      :final_v,    :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class BangBangFtau_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :vsTpositiveSubType,    :index_t,
      :vsTpositiveEpsilon,    :data_t,
      :vsTpositiveTolerance,  :data_t,
      :vsBpositiveSubType,    :index_t,
      :vsBpositiveEpsilon,    :data_t,
      :vsBpositiveTolerance,  :data_t,
      :vsTmaxSubType,         :index_t,
      :vsTmaxEpsilon,         :data_t,
      :vsTmaxTolerance,       :data_t,
      :vsTBIntervalSubType,   :index_t,
      :vsTBIntervalEpsilon,   :data_t,
      :vsTBIntervalTolerance, :data_t,
      :vsTBIntervalMinValue,  :data_t,
      :vsTBIntervalMaxValue,  :data_t,

      # 2D constraints

      # Controls
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
                  :BangBangFtau_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :BangBangFtau_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :BangBangFtau_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :BangBangFtau_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :BangBangFtau_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :BangBangFtau_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :BangBangFtau_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :BangBangFtau_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :BangBangFtau_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: BangBangFtau_ffi_stucts.rb
