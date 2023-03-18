#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ForwardBackward_ffi_structs.rb                                    #
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

module ForwardBackward

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ForwardBackward_solver_params < FFI::Struct
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

  class ForwardBackward_model_params < FFI::Struct
    layout(

      :E_epsi0,  :data_t,

      :E_epsi1,  :data_t,

      :E_max,    :data_t,

      :E_tol0,   :data_t,

      :E_tol1,   :data_t,

      :WA,       :data_t,

      :a_max,    :data_t,

      :a_min,    :data_t,

      :c0,       :data_t,

      :c0_0,     :data_t,

      :c0_1,     :data_t,

      :c1,       :data_t,

      :c1_0,     :data_t,

      :c1_1,     :data_t,

      :epsilon,  :data_t,

      :v0,       :data_t,

      :v1,       :data_t,

      :v_max,    :data_t,

      :v_min,    :data_t,

      :wT,       :data_t,

      :epsilon0, :data_t,

      :epsilon1, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ForwardBackward_BC_params < FFI::Struct
    layout(

      :initial_v, :bool,

      :final_v,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ForwardBackward_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :LimitV_minSubType, :index_t,
      :LimitV_minEpsilon, :data_t,
      :LimitV_minTolerance, :data_t,
      :LimitV_maxSubType, :index_t,
      :LimitV_maxEpsilon, :data_t,
      :LimitV_maxTolerance, :data_t,
      :LimitA_minSubType, :index_t,
      :LimitA_minEpsilon, :data_t,
      :LimitA_minTolerance, :data_t,
      :LimitA_maxSubType, :index_t,
      :LimitA_maxEpsilon, :data_t,
      :LimitA_maxTolerance, :data_t,
      :LimitESubType, :index_t,
      :LimitEEpsilon, :data_t,
      :LimitETolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
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
                  :ForwardBackward_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ForwardBackward_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ForwardBackward_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ForwardBackward_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ForwardBackward_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ForwardBackward_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ForwardBackward_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ForwardBackward_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ForwardBackward_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ForwardBackward_ffi_stucts.rb
