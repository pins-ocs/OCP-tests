#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: HypersonicProblem3DOF_ffi_structs.rb                              #
#                                                                          #
#  version: 1.0   date 22/2/2023                                           #
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

module HypersonicProblem3DOF

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class HypersonicProblem3DOF_solver_params < FFI::Struct
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

  class HypersonicProblem3DOF_model_params < FFI::Struct
    layout(

      :Aref,          :data_t,

      :CD0,           :data_t,

      :CD1,           :data_t,

      :CD2,           :data_t,

      :CL0,           :data_t,

      :CL1,           :data_t,

      :CTRL,          :data_t,

      :CTRL0,         :data_t,

      :CTRL1,         :data_t,

      :G_f,           :data_t,

      :G_i,           :data_t,

      :ODE,           :data_t,

      :ODE0,          :data_t,

      :ODE1,          :data_t,

      :S,             :data_t,

      :V_f,           :data_t,

      :V_i,           :data_t,

      :WTF,           :data_t,

      :WTF0,          :data_t,

      :WTF1,          :data_t,

      :h_f,           :data_t,

      :h_i,           :data_t,

      :m,             :data_t,

      :mu,            :data_t,

      :phi_f,         :data_t,

      :phi_i,         :data_t,

      :psi_f,         :data_t,

      :psi_i,         :data_t,

      :re,            :data_t,

      :rho0,          :data_t,

      :sigma_i,       :data_t,

      :theta_f,       :data_t,

      :theta_i,       :data_t,

      :to_deg,        :data_t,

      :Tf_guess,      :data_t,

      :sigma_dot_max, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class HypersonicProblem3DOF_BC_params < FFI::Struct
    layout(

      :initial_h,     :bool,

      :initial_theta, :bool,

      :initial_phi,   :bool,

      :initial_V,     :bool,

      :initial_G,     :bool,

      :initial_psi,   :bool,

      :initial_sigma, :bool,

      :final_h,       :bool,

      :final_theta,   :bool,

      :final_phi,     :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class HypersonicProblem3DOF_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :G_bound_minSubType, :index_t,
      :G_bound_minEpsilon, :data_t,
      :G_bound_minTolerance, :data_t,
      :G_bound_maxSubType, :index_t,
      :G_bound_maxEpsilon, :data_t,
      :G_bound_maxTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
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
                  :HypersonicProblem3DOF_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :HypersonicProblem3DOF_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :HypersonicProblem3DOF_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :HypersonicProblem3DOF_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :HypersonicProblem3DOF_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :HypersonicProblem3DOF_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :HypersonicProblem3DOF_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :HypersonicProblem3DOF_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :HypersonicProblem3DOF_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: HypersonicProblem3DOF_ffi_stucts.rb
