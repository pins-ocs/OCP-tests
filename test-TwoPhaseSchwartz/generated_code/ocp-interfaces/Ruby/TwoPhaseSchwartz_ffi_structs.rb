#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: TwoPhaseSchwartz_ffi_structs.rb                                   #
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

module TwoPhaseSchwartz

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class TwoPhaseSchwartz_solver_params < FFI::Struct
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

  class TwoPhaseSchwartz_model_params < FFI::Struct
    layout(

      :T2,       :data_t,

      :epsi0,    :data_t,

      :epsi1,    :data_t,

      :epsilon,  :data_t,

      :tol0,     :data_t,

      :tol1,     :data_t,

      :epsilon0, :data_t,

      :epsilon1, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class TwoPhaseSchwartz_BC_params < FFI::Struct
    layout(

      :initial_x1, :bool,

      :initial_x2, :bool,

      :x13,        :bool,

      :x24,        :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class TwoPhaseSchwartz_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :bound1SubType, :index_t,
      :bound1Epsilon, :data_t,
      :bound1Tolerance, :data_t,
      :bound2SubType, :index_t,
      :bound2Epsilon, :data_t,
      :bound2Tolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :u1ControlType,      :index_t,
      :u1ControlEpsilon,   :data_t,
      :u1ControlTolerance, :data_t,
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
                  :TwoPhaseSchwartz_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :TwoPhaseSchwartz_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :TwoPhaseSchwartz_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :TwoPhaseSchwartz_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :TwoPhaseSchwartz_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :TwoPhaseSchwartz_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :TwoPhaseSchwartz_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :TwoPhaseSchwartz_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :TwoPhaseSchwartz_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: TwoPhaseSchwartz_ffi_stucts.rb
