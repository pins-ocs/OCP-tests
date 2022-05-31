#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS_TwoLinkRobotArm_ffi_structs.rb                             #
#                                                                          #
#  version: 1.0   date 1/6/2022                                            #
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

module ICLOCS_TwoLinkRobotArm

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ICLOCS_TwoLinkRobotArm_solver_params < FFI::Struct
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

  class ICLOCS_TwoLinkRobotArm_model_params < FFI::Struct
    layout(

      :T_guess,        :data_t,

      :W,              :data_t,

      :alpha_f,        :data_t,

      :alpha_i,        :data_t,

      :rho,            :data_t,

      :theta_f,        :data_t,

      :theta_i,        :data_t,

      :omega__alpha_f, :data_t,

      :omega__alpha_i, :data_t,

      :omega__beta_f,  :data_t,

      :omega__beta_i,  :data_t,

      :u_epsilon0,     :data_t,

      :u_epsilon1,     :data_t,

      :u_tolerance0,   :data_t,

      :u_tolerance1,   :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_TwoLinkRobotArm_BC_params < FFI::Struct
    layout(

      :initial_omega__alpha, :bool,

      :initial_omega__beta,  :bool,

      :initial_theta,        :bool,

      :initial_alpha,        :bool,

      :final_omega__alpha,   :bool,

      :final_omega__beta,    :bool,

      :final_theta,          :bool,

      :final_alpha,          :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_TwoLinkRobotArm_constraints_params < FFI::Struct
    layout(
      # LT constraints

      # 1D constraints

      # 2D constraints

      # Controls
      :u1ControlType,      :index_t,
      :u1ControlEpsilon,   :data_t,
      :u1ControlTolerance, :data_t,
      :u2ControlType,      :index_t,
      :u2ControlEpsilon,   :data_t,
      :u2ControlTolerance, :data_t,
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
                  :ICLOCS_TwoLinkRobotArm_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ICLOCS_TwoLinkRobotArm_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ICLOCS_TwoLinkRobotArm_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ICLOCS_TwoLinkRobotArm_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ICLOCS_TwoLinkRobotArm_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ICLOCS_TwoLinkRobotArm_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ICLOCS_TwoLinkRobotArm_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ICLOCS_TwoLinkRobotArm_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ICLOCS_TwoLinkRobotArm_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ICLOCS_TwoLinkRobotArm_ffi_stucts.rb
