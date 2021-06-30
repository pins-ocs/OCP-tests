#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Crossroad_ffi_structs.rb                                          #
#                                                                          #
#  version: 1.0   date 5/7/2021                                            #
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

module Crossroad

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Crossroad_solver_params < FFI::Struct
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

  class Crossroad_model_params < FFI::Struct
    layout(

      :L,         :data_t,

      :Vmean,     :data_t,

      :a_f,       :data_t,

      :a_i,       :data_t,

      :kappa0,    :data_t,

      :kappa1,    :data_t,

      :kappa2,    :data_t,

      :s_f,       :data_t,

      :s_i,       :data_t,

      :v_f,       :data_t,

      :v_i,       :data_t,

      :wJ,        :data_t,

      :wT,        :data_t,

      :alat_max,  :data_t,

      :along_max, :data_t,

      :jerk_max,  :data_t,

      :jerk_min,  :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Crossroad_BC_params < FFI::Struct
    layout(

      :initial_s, :bool,

      :initial_v, :bool,

      :initial_a, :bool,

      :final_s,   :bool,

      :final_v,   :bool,

      :final_a,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Crossroad_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :TpositiveSubType,   :index_t,
      :TpositiveEpsilon,   :data_t,
      :TpositiveTolerance, :data_t,
      :AccBoundSubType,    :index_t,
      :AccBoundEpsilon,    :data_t,
      :AccBoundTolerance,  :data_t,
      :VelBoundSubType,    :index_t,
      :VelBoundEpsilon,    :data_t,
      :VelBoundTolerance,  :data_t,
      :VelBoundMinValue,   :data_t,
      :VelBoundMaxValue,   :data_t,

      # 2D constraints

      # Controls
      :jerkControlType,      :index_t,
      :jerkControlEpsilon,   :data_t,
      :jerkControlTolerance, :data_t,
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
                  :Crossroad_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Crossroad_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Crossroad_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Crossroad_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Crossroad_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Crossroad_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Crossroad_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Crossroad_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Crossroad_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Crossroad_ffi_stucts.rb
