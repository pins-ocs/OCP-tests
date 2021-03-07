#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: RobotArm_ffi_structs.rb                                           #
#                                                                          #
#  version: 1.0   date 9/3/2021                                            #
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

module RobotArm

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class RobotArm_solver_params < FFI::Struct
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

  class RobotArm_model_params < FFI::Struct
    layout(

      :L,            :data_t,

      :Tguess,       :data_t,

      :W,            :data_t,

      :u_epsilon0,   :data_t,

      :u_epsilon1,   :data_t,

      :u_tolerance0, :data_t,

      :u_tolerance1, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class RobotArm_BC_params < FFI::Struct
    layout(

      :initial_rho,    :bool,

      :initial_theta,  :bool,

      :initial_phi,    :bool,

      :initial_rho1,   :bool,

      :initial_theta1, :bool,

      :initial_phi1,   :bool,

      :final_rho,      :bool,

      :final_theta,    :bool,

      :final_phi,      :bool,

      :final_rho1,     :bool,

      :final_theta1,   :bool,

      :final_phi1,     :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class RobotArm_constraints_params < FFI::Struct
    layout(
      # 1D constraints

      # 2D constraints

      # Controls
      :u_rhoControlType,        :index_t,
      :u_rhoControlEpsilon,     :data_t,
      :u_rhoControlTolerance,   :data_t,
      :u_thetaControlType,      :index_t,
      :u_thetaControlEpsilon,   :data_t,
      :u_thetaControlTolerance, :data_t,
      :u_phiControlType,        :index_t,
      :u_phiControlEpsilon,     :data_t,
      :u_phiControlTolerance,   :data_t,
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
                  :RobotArm_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :RobotArm_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :RobotArm_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :RobotArm_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :RobotArm_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :RobotArm_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :RobotArm_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :RobotArm_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :RobotArm_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: RobotArm_ffi_stucts.rb
