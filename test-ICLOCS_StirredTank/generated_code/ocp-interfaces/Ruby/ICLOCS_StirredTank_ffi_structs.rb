#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS_StirredTank_ffi_structs.rb                                 #
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

module ICLOCS_StirredTank

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ICLOCS_StirredTank_solver_params < FFI::Struct
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

  class ICLOCS_StirredTank_model_params < FFI::Struct
    layout(

      :En,         :data_t,

      :T_guess,    :data_t,

      :T_min,      :data_t,

      :Tc,         :data_t,

      :Tf,         :data_t,

      :a,          :data_t,

      :k,          :data_t,

      :theta,      :data_t,

      :u_f,        :data_t,

      :w_time,     :data_t,

      :x1_f,       :data_t,

      :x1_i,       :data_t,

      :x2_f,       :data_t,

      :x2_i,       :data_t,

      :epsi_ctrl0, :data_t,

      :epsi_ctrl1, :data_t,

      :tol_ctrl0,  :data_t,

      :tol_ctrl1,  :data_t,

      :w_time_max, :data_t,

      :w_time_min, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_StirredTank_BC_params < FFI::Struct
    layout(

      :initial_x1, :bool,

      :initial_x2, :bool,

      :final_x1,   :bool,

      :final_x2,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_StirredTank_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :tfboundSubType, :index_t,
      :tfboundEpsilon, :data_t,
      :tfboundTolerance, :data_t,
      :x1bound_minSubType, :index_t,
      :x1bound_minEpsilon, :data_t,
      :x1bound_minTolerance, :data_t,
      :x1bound_maxSubType, :index_t,
      :x1bound_maxEpsilon, :data_t,
      :x1bound_maxTolerance, :data_t,
      :x2bound_minSubType, :index_t,
      :x2bound_minEpsilon, :data_t,
      :x2bound_minTolerance, :data_t,
      :x2bound_maxSubType, :index_t,
      :x2bound_maxEpsilon, :data_t,
      :x2bound_maxTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :uControlType,      :index_t,
      :uControlEpsilon,   :data_t,
      :uControlTolerance, :data_t,
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
                  :ICLOCS_StirredTank_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ICLOCS_StirredTank_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ICLOCS_StirredTank_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ICLOCS_StirredTank_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ICLOCS_StirredTank_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ICLOCS_StirredTank_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ICLOCS_StirredTank_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ICLOCS_StirredTank_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ICLOCS_StirredTank_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ICLOCS_StirredTank_ffi_stucts.rb
