#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: stirred_tank_ffi_structs.rb                                       #
#                                                                          #
#  version: 1.0   date 9/5/2023                                            #
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

module stirred_tank

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class stirred_tank_solver_params < FFI::Struct
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

  class stirred_tank_model_params < FFI::Struct
    layout(

      :tol_max,  :data_t,

      :tol_min,  :data_t,

      :epsi_max, :data_t,

      :epsi_min, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class stirred_tank_BC_params < FFI::Struct
    layout(

      :initial_x1, :bool,

      :initial_x2, :bool,

      :initial_x3, :bool,

      :initial_x4, :bool,

      :initial_x5, :bool,

      :initial_x6, :bool,

      :initial_x7, :bool,

      :initial_x8, :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class stirred_tank_constraints_params < FFI::Struct
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
      :u4ControlType,      :index_t,
      :u4ControlEpsilon,   :data_t,
      :u4ControlTolerance, :data_t,
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
                  :stirred_tank_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :stirred_tank_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :stirred_tank_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :stirred_tank_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :stirred_tank_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :stirred_tank_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :stirred_tank_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :stirred_tank_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :stirred_tank_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: stirred_tank_ffi_stucts.rb
