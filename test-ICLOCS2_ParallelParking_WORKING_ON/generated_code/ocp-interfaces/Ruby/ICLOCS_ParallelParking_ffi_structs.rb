#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS_ParallelParking_ffi_structs.rb                             #
#                                                                          #
#  version: 1.0   date 5/12/2021                                           #
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

module ICLOCS_ParallelParking

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ICLOCS_ParallelParking_solver_params < FFI::Struct
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

  class ICLOCS_ParallelParking_model_params < FFI::Struct
    layout(

      :T_guess, :data_t,

      :a_f,     :data_t,

      :a_i,     :data_t,

      :b,       :data_t,

      :len_SL,  :data_t,

      :len_a,   :data_t,

      :len_f,   :data_t,

      :len_r,   :data_t,

      :phi_i,   :data_t,

      :theta_i, :data_t,

      :v_f,     :data_t,

      :v_i,     :data_t,

      :x_i,     :data_t,

      :y_i,     :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_ParallelParking_BC_params < FFI::Struct
    layout(

      :initial_x,     :bool,

      :initial_y,     :bool,

      :initial_theta, :bool,

      :initial_phi,   :bool,

      :initial_v,     :bool,

      :initial_a,     :bool,

      :final_v,       :bool,

      :final_a,       :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_ParallelParking_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :A_boundSubType,        :index_t,
      :A_boundEpsilon,        :data_t,
      :A_boundTolerance,      :data_t,
      :A_boundMinValue,       :data_t,
      :A_boundMaxValue,       :data_t,
      :B_boundSubType,        :index_t,
      :B_boundEpsilon,        :data_t,
      :B_boundTolerance,      :data_t,
      :B_boundMinValue,       :data_t,
      :B_boundMaxValue,       :data_t,
      :C_boundSubType,        :index_t,
      :C_boundEpsilon,        :data_t,
      :C_boundTolerance,      :data_t,
      :C_boundMinValue,       :data_t,
      :C_boundMaxValue,       :data_t,
      :D_boundSubType,        :index_t,
      :D_boundEpsilon,        :data_t,
      :D_boundTolerance,      :data_t,
      :D_boundMinValue,       :data_t,
      :D_boundMaxValue,       :data_t,
      :EXTRA1_boundSubType,   :index_t,
      :EXTRA1_boundEpsilon,   :data_t,
      :EXTRA1_boundTolerance, :data_t,
      :EXTRA2_boundSubType,   :index_t,
      :EXTRA2_boundEpsilon,   :data_t,
      :EXTRA2_boundTolerance, :data_t,
      :vel_boundSubType,      :index_t,
      :vel_boundEpsilon,      :data_t,
      :vel_boundTolerance,    :data_t,
      :vel_boundMinValue,     :data_t,
      :vel_boundMaxValue,     :data_t,
      :acc_boundSubType,      :index_t,
      :acc_boundEpsilon,      :data_t,
      :acc_boundTolerance,    :data_t,
      :acc_boundMinValue,     :data_t,
      :acc_boundMaxValue,     :data_t,
      :phi_boundSubType,      :index_t,
      :phi_boundEpsilon,      :data_t,
      :phi_boundTolerance,    :data_t,
      :phi_boundMinValue,     :data_t,
      :phi_boundMaxValue,     :data_t,

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
                  :ICLOCS_ParallelParking_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ICLOCS_ParallelParking_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ICLOCS_ParallelParking_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ICLOCS_ParallelParking_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ICLOCS_ParallelParking_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ICLOCS_ParallelParking_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ICLOCS_ParallelParking_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ICLOCS_ParallelParking_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ICLOCS_ParallelParking_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ICLOCS_ParallelParking_ffi_stucts.rb
