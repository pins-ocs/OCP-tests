#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: MinimumEnergyProblem_ffi_structs.rb                               #
#                                                                          #
#  version: 1.0   date 12/11/2020                                          #
#                                                                          #
#  Copyright (C) 2020                                                      #
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

module MinimumEnergyProblem

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class MinimumEnergyProblem_solver_params < FFI::Struct
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

  class MinimumEnergyProblem_model_params < FFI::Struct
    layout(

      :maxEpsi, :data_t,

      :maxTol,  :data_t,

      :minEpsi, :data_t,

      :minTol,  :data_t,

      :x1_f,    :data_t,

      :x1_i,    :data_t,

      :x2_f,    :data_t,

      :x2_i,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class MinimumEnergyProblem_BC_params < FFI::Struct
    layout(

      :initial_x1, :bool,

      :initial_x2, :bool,

      :final_x1,   :bool,

      :final_x2,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class MinimumEnergyProblem_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :x1LimitationSubType,   :index_t,
      :x1LimitationEpsilon,   :data_t,
      :x1LimitationTolerance, :data_t,

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

  attach_function :setup_model,                          # ruby name
                  :MinimumEnergyProblem_setup_model,        # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver,                         # ruby name
                  :MinimumEnergyProblem_setup_solver,       # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file,                   # ruby name
                  :MinimumEnergyProblem_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?,                       # ruby name
                  :MinimumEnergyProblem_printout_is_enabled,   # C name
                  [],
                  :int

  attach_function :enable_printout,                      # ruby name
                  :MinimumEnergyProblem_enable_printout,    # C name
                  [],
                  :void

  attach_function :disable_printout,                     # ruby name
                  :MinimumEnergyProblem_disable_printout,   # C name
                  [],
                  :void

  attach_function :reset_multiplier,                     # ruby name
                  :MinimumEnergyProblem_reset_multiplier,   # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier,                     # ruby name
                  :MinimumEnergyProblem_reset_BC_multiplier,   # C name
                  [],
                  :void

  attach_function :set_internal_guess,                     # ruby name
                  :MinimumEnergyProblem_set_internal_guess,   # C name
                  [],
                  :void

end

# EOF: MinimumEnergyProblem_ffi_stucts.rb
