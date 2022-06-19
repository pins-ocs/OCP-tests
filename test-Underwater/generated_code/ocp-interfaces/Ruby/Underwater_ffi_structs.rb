#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Underwater_ffi_structs.rb                                         #
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

module Underwater

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Underwater_solver_params < FFI::Struct
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

  class Underwater_model_params < FFI::Struct
    layout(

      :Tguess,   :data_t,

      :inertia,  :data_t,

      :m1,       :data_t,

      :m3,       :data_t,

      :theta_f,  :data_t,

      :theta_i,  :data_t,

      :vx_f,     :data_t,

      :vx_i,     :data_t,

      :vz_f,     :data_t,

      :vz_i,     :data_t,

      :x_f,      :data_t,

      :x_i,      :data_t,

      :z_f,      :data_t,

      :z_i,      :data_t,

      :epsi_max, :data_t,

      :epsi_min, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Underwater_BC_params < FFI::Struct
    layout(

      :initial_x,     :bool,

      :initial_z,     :bool,

      :initial_vx,    :bool,

      :initial_vz,    :bool,

      :initial_theta, :bool,

      :final_x,       :bool,

      :final_z,       :bool,

      :final_vx,      :bool,

      :final_vz,      :bool,

      :final_theta,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Underwater_constraints_params < FFI::Struct
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
      :u3ControlType,      :index_t,
      :u3ControlEpsilon,   :data_t,
      :u3ControlTolerance, :data_t,
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
                  :Underwater_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Underwater_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Underwater_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Underwater_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Underwater_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Underwater_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Underwater_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Underwater_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Underwater_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Underwater_ffi_stucts.rb
