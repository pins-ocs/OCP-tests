#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: CNOC_ffi_structs.rb                                               #
#                                                                          #
#  version: 1.0   date 10/4/2022                                           #
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

module CNOC

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class CNOC_solver_params < FFI::Struct
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

  class CNOC_model_params < FFI::Struct
    layout(

      :an_f,                     :data_t,

      :an_i,                     :data_t,

      :an_max,                   :data_t,

      :as_f,                     :data_t,

      :as_i,                     :data_t,

      :as_max,                   :data_t,

      :ax_max,                   :data_t,

      :ay_max,                   :data_t,

      :jn_max,                   :data_t,

      :js_max,                   :data_t,

      :js_min,                   :data_t,

      :n_f,                      :data_t,

      :n_i,                      :data_t,

      :vn_f,                     :data_t,

      :vn_i,                     :data_t,

      :vs_f,                     :data_t,

      :vs_i,                     :data_t,

      :deltaFeed,                :data_t,

      :pf_error,                 :data_t,

      :path_following_tolerance, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class CNOC_BC_params < FFI::Struct
    layout(

      :initial_n,  :bool,

      :initial_vs, :bool,

      :initial_vn, :bool,

      :initial_as, :bool,

      :initial_an, :bool,

      :final_n,    :bool,

      :final_vs,   :bool,

      :final_vn,   :bool,

      :final_as,   :bool,

      :final_an,   :bool,

      :initial_s,  :bool,

      :final_s,    :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class CNOC_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :timePositiveSubType, :index_t,
      :timePositiveEpsilon, :data_t,
      :timePositiveTolerance, :data_t,
      :vLimitSubType, :index_t,
      :vLimitEpsilon, :data_t,
      :vLimitTolerance, :data_t,
      :PathFollowingTolerance_minSubType, :index_t,
      :PathFollowingTolerance_minEpsilon, :data_t,
      :PathFollowingTolerance_minTolerance, :data_t,
      :PathFollowingTolerance_maxSubType, :index_t,
      :PathFollowingTolerance_maxEpsilon, :data_t,
      :PathFollowingTolerance_maxTolerance, :data_t,
      :as_limit_minSubType, :index_t,
      :as_limit_minEpsilon, :data_t,
      :as_limit_minTolerance, :data_t,
      :as_limit_maxSubType, :index_t,
      :as_limit_maxEpsilon, :data_t,
      :as_limit_maxTolerance, :data_t,
      :an_limit_minSubType, :index_t,
      :an_limit_minEpsilon, :data_t,
      :an_limit_minTolerance, :data_t,
      :an_limit_maxSubType, :index_t,
      :an_limit_maxEpsilon, :data_t,
      :an_limit_maxTolerance, :data_t,
      :ax_limit_minSubType, :index_t,
      :ax_limit_minEpsilon, :data_t,
      :ax_limit_minTolerance, :data_t,
      :ax_limit_maxSubType, :index_t,
      :ax_limit_maxEpsilon, :data_t,
      :ax_limit_maxTolerance, :data_t,
      :ay_limit_minSubType, :index_t,
      :ay_limit_minEpsilon, :data_t,
      :ay_limit_minTolerance, :data_t,
      :ay_limit_maxSubType, :index_t,
      :ay_limit_maxEpsilon, :data_t,
      :ay_limit_maxTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :jsControlType,      :index_t,
      :jsControlEpsilon,   :data_t,
      :jsControlTolerance, :data_t,
      :jnControlType,      :index_t,
      :jnControlEpsilon,   :data_t,
      :jnControlTolerance, :data_t,
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
                  :CNOC_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :CNOC_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :CNOC_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :CNOC_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :CNOC_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :CNOC_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :CNOC_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :CNOC_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :CNOC_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: CNOC_ffi_stucts.rb
