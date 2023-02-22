#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: TyreDynamic_ffi_structs.rb                                        #
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

module TyreDynamic

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class TyreDynamic_solver_params < FFI::Struct
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

  class TyreDynamic_model_params < FFI::Struct
    layout(

      :BT__max,     :data_t,

      :Bx0,         :data_t,

      :Cx0,         :data_t,

      :E__pow,      :data_t,

      :Iw,          :data_t,

      :TB__max,     :data_t,

      :TT__max,     :data_t,

      :b__lb,       :data_t,

      :b__ss,       :data_t,

      :b__ub,       :data_t,

      :eps_c0,      :data_t,

      :eps_c1,      :data_t,

      :g,           :data_t,

      :h__b,        :data_t,

      :kD,          :data_t,

      :kDo,         :data_t,

      :l__x,        :data_t,

      :m,           :data_t,

      :mu__x0,      :data_t,

      :p__lb,       :data_t,

      :p__ss,       :data_t,

      :p__ub,       :data_t,

      :rho_a,       :data_t,

      :rw,          :data_t,

      :tau__b,      :data_t,

      :tau__p,      :data_t,

      :tol_c0,      :data_t,

      :tol_c1,      :data_t,

      :v__adm,      :data_t,

      :v__lb,       :data_t,

      :v__ss,       :data_t,

      :v__ub,       :data_t,

      :w__U,        :data_t,

      :w__t,        :data_t,

      :w__t0,       :data_t,

      :w__t1,       :data_t,

      :BTv__max,    :data_t,

      :b__o__lb,    :data_t,

      :b__o__ub,    :data_t,

      :lambda__lb,  :data_t,

      :lambda__max, :data_t,

      :lambda__ss,  :data_t,

      :lambda__ub,  :data_t,

      :omega__lb,   :data_t,

      :omega__ss,   :data_t,

      :omega__ub,   :data_t,

      :p__o__lb,    :data_t,

      :p__o__ub,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class TyreDynamic_BC_params < FFI::Struct
    layout(

      :initial_v, :bool,

      :initial_b, :bool,

      :final_v,   :bool,

      :lambda__i, :bool,

      :p__i,      :bool,

      :omega__i,  :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class TyreDynamic_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :OnlyBrakingRearSubType, :index_t,
      :OnlyBrakingRearEpsilon, :data_t,
      :OnlyBrakingRearTolerance, :data_t,
      :OnlyTractionRearSubType, :index_t,
      :OnlyTractionRearEpsilon, :data_t,
      :OnlyTractionRearTolerance, :data_t,
      :LongSlipRear_minSubType, :index_t,
      :LongSlipRear_minEpsilon, :data_t,
      :LongSlipRear_minTolerance, :data_t,
      :LongSlipRear_maxSubType, :index_t,
      :LongSlipRear_maxEpsilon, :data_t,
      :LongSlipRear_maxTolerance, :data_t,
      :v_minSubType, :index_t,
      :v_minEpsilon, :data_t,
      :v_minTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :b__oControlType,      :index_t,
      :b__oControlEpsilon,   :data_t,
      :b__oControlTolerance, :data_t,
      :p__oControlType,      :index_t,
      :p__oControlEpsilon,   :data_t,
      :p__oControlTolerance, :data_t,
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
                  :TyreDynamic_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :TyreDynamic_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :TyreDynamic_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :TyreDynamic_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :TyreDynamic_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :TyreDynamic_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :TyreDynamic_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :TyreDynamic_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :TyreDynamic_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: TyreDynamic_ffi_stucts.rb
