#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Farmer_ffi_structs.rb                                             #
#                                                                          #
#  version: 1.0   date 26/2/2021                                           #
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

module Farmer

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Farmer_solver_params < FFI::Struct
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

  class Farmer_model_params < FFI::Struct
    layout(

      :P1,     :data_t,

      :P2,     :data_t,

      :res0,   :data_t,

      :t1,     :data_t,

      :t2,     :data_t,

      :tau__1, :data_t,

      :tau__2, :data_t,

      :tau__3, :data_t,

      :tau__4, :data_t,

      :tau__5, :data_t,

      :w1,     :data_t,

      :w2,     :data_t,

      :w3,     :data_t,

      :w4,     :data_t,

      :wJ1,    :data_t,

      :wJ2,    :data_t,

      :wJ3,    :data_t,

      :wJ4,    :data_t,

      :wP,     :data_t,

      :x10,    :data_t,

      :x20,    :data_t,

      :x30,    :data_t,

      :x40,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Farmer_BC_params < FFI::Struct
    layout(

      :initial_x1,  :bool,

      :initial_x2,  :bool,

      :initial_x3,  :bool,

      :initial_res, :bool,

      :initial_x4,  :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Farmer_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :LimitX2X4SubType,   :index_t,
      :LimitX2X4Epsilon,   :data_t,
      :LimitX2X4Tolerance, :data_t,

      # 2D constraints

      # Controls
      :x1__oControlType,      :index_t,
      :x1__oControlEpsilon,   :data_t,
      :x1__oControlTolerance, :data_t,
      :x2__oControlType,      :index_t,
      :x2__oControlEpsilon,   :data_t,
      :x2__oControlTolerance, :data_t,
      :x3__oControlType,      :index_t,
      :x3__oControlEpsilon,   :data_t,
      :x3__oControlTolerance, :data_t,
      :x4__oControlType,      :index_t,
      :x4__oControlEpsilon,   :data_t,
      :x4__oControlTolerance, :data_t,
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
                  :Farmer_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Farmer_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Farmer_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Farmer_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Farmer_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Farmer_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Farmer_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Farmer_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Farmer_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Farmer_ffi_stucts.rb
