#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: BikeSteering_ffi_structs.rb                                       #
#                                                                          #
#  version: 1.0   date 20/3/2023                                           #
#                                                                          #
#  Copyright (C) 2023                                                      #
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

module BikeSteering

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class BikeSteering_solver_params < FFI::Struct
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

  class BikeSteering_model_params < FFI::Struct
    layout(

      :Fmax,    :data_t,

      :Ix,      :data_t,

      :g,       :data_t,

      :h,       :data_t,

      :m,       :data_t,

      :omega_f, :data_t,

      :omega_i, :data_t,

      :phi_f,   :data_t,

      :phi_i,   :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class BikeSteering_BC_params < FFI::Struct
    layout(

      :initial_omega, :bool,

      :initial_phi,   :bool,

      :final_omega,   :bool,

      :final_phi,     :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class BikeSteering_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :minimumTimeSizeSubType, :index_t,
      :minimumTimeSizeEpsilon, :data_t,
      :minimumTimeSizeTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :FyControlType,      :index_t,
      :FyControlEpsilon,   :data_t,
      :FyControlTolerance, :data_t,
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
                  :BikeSteering_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :BikeSteering_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :BikeSteering_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :BikeSteering_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :BikeSteering_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :BikeSteering_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :BikeSteering_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :BikeSteering_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :BikeSteering_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: BikeSteering_ffi_stucts.rb
