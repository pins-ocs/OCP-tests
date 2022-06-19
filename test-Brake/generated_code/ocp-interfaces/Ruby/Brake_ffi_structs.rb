#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Brake_ffi_structs.rb                                              #
#                                                                          #
#  version: 1.0   date 19/6/2022                                           #
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

module Brake

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Brake_solver_params < FFI::Struct
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

  class Brake_model_params < FFI::Struct
    layout(

      :v_f, :data_t,

      :v_i, :data_t,

      :x_i, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Brake_BC_params < FFI::Struct
    layout(

      :initial_x, :bool,

      :initial_v, :bool,

      :final_v,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Brake_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :TpositiveSubType, :index_t,
      :TpositiveEpsilon, :data_t,
      :TpositiveTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :aControlType,      :index_t,
      :aControlEpsilon,   :data_t,
      :aControlTolerance, :data_t,
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
                  :Brake_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Brake_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Brake_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Brake_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Brake_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Brake_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Brake_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Brake_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Brake_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Brake_ffi_stucts.rb
