#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS2_BatchFermentor_ffi_structs.rb                             #
#                                                                          #
#  version: 1.0   date 17/6/2022                                           #
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

module ICLOCS2_BatchFermentor

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ICLOCS2_BatchFermentor_solver_params < FFI::Struct
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

  class ICLOCS2_BatchFermentor_model_params < FFI::Struct
    layout(

      :K_degr,   :data_t,

      :S_f,      :data_t,

      :Tf,       :data_t,

      :W,        :data_t,

      :W0,       :data_t,

      :W1,       :data_t,

      :WP,       :data_t,

      :WP0,      :data_t,

      :WP1,      :data_t,

      :Yes,      :data_t,

      :Yxs,      :data_t,

      :epsilon,  :data_t,

      :kappa_m,  :data_t,

      :kappa_p,  :data_t,

      :kappa_x,  :data_t,

      :mu_max,   :data_t,

      :mu_s,     :data_t,

      :p_f,      :data_t,

      :p_i,      :data_t,

      :p_max,    :data_t,

      :rho_max,  :data_t,

      :s_f,      :data_t,

      :s_i,      :data_t,

      :s_max,    :data_t,

      :v_f,      :data_t,

      :v_i,      :data_t,

      :v_max,    :data_t,

      :x_f,      :data_t,

      :x_i,      :data_t,

      :x_max,    :data_t,

      :epsilon0, :data_t,

      :epsilon1, :data_t,

      :kappa_in, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS2_BatchFermentor_BC_params < FFI::Struct
    layout(

      :initial_x, :bool,

      :initial_p, :bool,

      :initial_s, :bool,

      :initial_v, :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS2_BatchFermentor_constraints_params < FFI::Struct
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
                  :ICLOCS2_BatchFermentor_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ICLOCS2_BatchFermentor_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ICLOCS2_BatchFermentor_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ICLOCS2_BatchFermentor_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ICLOCS2_BatchFermentor_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ICLOCS2_BatchFermentor_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ICLOCS2_BatchFermentor_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ICLOCS2_BatchFermentor_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ICLOCS2_BatchFermentor_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ICLOCS2_BatchFermentor_ffi_stucts.rb
