#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: HangGlider_ffi_structs.rb                                         #
#                                                                          #
#  version: 1.0   date 13/12/2021                                          #
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

module HangGlider

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class HangGlider_solver_params < FFI::Struct
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

  class HangGlider_model_params < FFI::Struct
    layout(

      :S,        :data_t,

      :Tguess,   :data_t,

      :W,        :data_t,

      :W0,       :data_t,

      :W1,       :data_t,

      :c0,       :data_t,

      :c1,       :data_t,

      :cL_max,   :data_t,

      :cL_min,   :data_t,

      :g,        :data_t,

      :m,        :data_t,

      :rc,       :data_t,

      :rho,      :data_t,

      :tol_max,  :data_t,

      :tol_min,  :data_t,

      :uc,       :data_t,

      :vx_f,     :data_t,

      :vx_i,     :data_t,

      :vy_f,     :data_t,

      :vy_i,     :data_t,

      :x_i,      :data_t,

      :y_f,      :data_t,

      :y_i,      :data_t,

      :epsi_max, :data_t,

      :epsi_min, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class HangGlider_BC_params < FFI::Struct
    layout(

      :initial_x,  :bool,

      :initial_y,  :bool,

      :initial_vx, :bool,

      :initial_vy, :bool,

      :final_y,    :bool,

      :final_vx,   :bool,

      :final_vy,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class HangGlider_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :TboundSubType,   :index_t,
      :TboundEpsilon,   :data_t,
      :TboundTolerance, :data_t,

      # 2D constraints

      # Controls
      :cLControlType,      :index_t,
      :cLControlEpsilon,   :data_t,
      :cLControlTolerance, :data_t,
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
                  :HangGlider_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :HangGlider_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :HangGlider_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :HangGlider_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :HangGlider_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :HangGlider_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :HangGlider_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :HangGlider_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :HangGlider_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: HangGlider_ffi_stucts.rb
