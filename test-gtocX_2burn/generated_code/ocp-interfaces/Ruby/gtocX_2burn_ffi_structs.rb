#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: gtocX_2burn_ffi_structs.rb                                        #
#                                                                          #
#  version: 1.0   date 20/12/2021                                          #
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

module gtocX_2burn

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class gtocX_2burn_solver_params < FFI::Struct
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

  class gtocX_2burn_model_params < FFI::Struct
    layout(

      :muS,        :data_t,

      :time_f,     :data_t,

      :time_i,     :data_t,

      :w_guess,    :data_t,

      :epsi_norm,  :data_t,

      :retrograde, :data_t,

      :w_nonlin,   :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class gtocX_2burn_BC_params < FFI::Struct
    layout(

      :initial_x, :bool,

      :initial_y, :bool,

      :initial_z, :bool,

      :final_x,   :bool,

      :final_y,   :bool,

      :final_z,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class gtocX_2burn_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :ray_positiveSubType,   :index_t,
      :ray_positiveEpsilon,   :data_t,
      :ray_positiveTolerance, :data_t,

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
                  :gtocX_2burn_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :gtocX_2burn_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :gtocX_2burn_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :gtocX_2burn_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :gtocX_2burn_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :gtocX_2burn_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :gtocX_2burn_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :gtocX_2burn_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :gtocX_2burn_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: gtocX_2burn_ffi_stucts.rb
