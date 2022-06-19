#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: GoddardRocket_ffi_structs.rb                                      #
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

module GoddardRocket

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class GoddardRocket_solver_params < FFI::Struct
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

  class GoddardRocket_model_params < FFI::Struct
    layout(

      :Dc,            :data_t,

      :Tmax,          :data_t,

      :c,             :data_t,

      :g0,            :data_t,

      :h_i,           :data_t,

      :hc,            :data_t,

      :m_f,           :data_t,

      :m_i,           :data_t,

      :v_i,           :data_t,

      :epsi_TS_max,   :data_t,

      :epsi_TS_min,   :data_t,

      :epsi_T_max,    :data_t,

      :epsi_T_min,    :data_t,

      :epsi_mass_max, :data_t,

      :epsi_mass_min, :data_t,

      :epsi_v_max,    :data_t,

      :epsi_v_min,    :data_t,

      :tol_TS_max,    :data_t,

      :tol_TS_min,    :data_t,

      :tol_T_max,     :data_t,

      :tol_T_min,     :data_t,

      :tol_mass_max,  :data_t,

      :tol_mass_min,  :data_t,

      :tol_v_max,     :data_t,

      :tol_v_min,     :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class GoddardRocket_BC_params < FFI::Struct
    layout(

      :initial_h, :bool,

      :initial_v, :bool,

      :initial_m, :bool,

      :final_m,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class GoddardRocket_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :massPositiveSubType, :index_t,
      :massPositiveEpsilon, :data_t,
      :massPositiveTolerance, :data_t,
      :vPositiveSubType, :index_t,
      :vPositiveEpsilon, :data_t,
      :vPositiveTolerance, :data_t,
      :TSPositiveSubType, :index_t,
      :TSPositiveEpsilon, :data_t,
      :TSPositiveTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :TControlType,      :index_t,
      :TControlEpsilon,   :data_t,
      :TControlTolerance, :data_t,
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
                  :GoddardRocket_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :GoddardRocket_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :GoddardRocket_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :GoddardRocket_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :GoddardRocket_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :GoddardRocket_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :GoddardRocket_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :GoddardRocket_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :GoddardRocket_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: GoddardRocket_ffi_stucts.rb
