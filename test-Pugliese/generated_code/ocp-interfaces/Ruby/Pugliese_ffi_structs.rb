#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: Pugliese_ffi_structs.rb                                           #
#                                                                          #
#  version: 1.0   date 25/3/2022                                           #
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

module Pugliese

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class Pugliese_solver_params < FFI::Struct
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

  class Pugliese_model_params < FFI::Struct
    layout(

      :C0,        :data_t,

      :D0,        :data_t,

      :Ip0,       :data_t,

      :K,         :data_t,

      :R0,        :data_t,

      :T0,        :data_t,

      :a,         :data_t,

      :a__IL,     :data_t,

      :a__R,      :data_t,

      :b,         :data_t,

      :e,         :data_t,

      :e__C,      :data_t,

      :e__D,      :data_t,

      :e__IL,     :data_t,

      :i0,        :data_t,

      :lambda,    :data_t,

      :mu__C,     :data_t,

      :mu__D,     :data_t,

      :mu__R,     :data_t,

      :r,         :data_t,

      :rho__D,    :data_t,

      :s,         :data_t,

      :s__C,      :data_t,

      :s__D,      :data_t,

      :s__IL,     :data_t,

      :w2,        :data_t,

      :kappa__AC, :data_t,

      :kappa__R,  :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Pugliese_BC_params < FFI::Struct
    layout(

      :initial_T,    :bool,

      :initial_C,    :bool,

      :initial_R,    :bool,

      :initial_DD,   :bool,

      :initial_I__p, :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class Pugliese_constraints_params < FFI::Struct
    layout(
      # LT constraints

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
                  :Pugliese_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :Pugliese_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :Pugliese_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :Pugliese_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :Pugliese_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :Pugliese_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :Pugliese_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :Pugliese_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :Pugliese_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: Pugliese_ffi_stucts.rb