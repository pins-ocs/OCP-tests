#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: PointMassCarModel_4_ffi_structs.rb                                #
#                                                                          #
#  version: 1.0   date 19/3/2022                                           #
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

module PointMassCarModel_4

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class PointMassCarModel_4_solver_params < FFI::Struct
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

  class PointMassCarModel_4_model_params < FFI::Struct
    layout(

      :Pmax,          :data_t,

      :V0,            :data_t,

      :Vguess,        :data_t,

      :g,             :data_t,

      :kD,            :data_t,

      :m,             :data_t,

      :p_epsi0,       :data_t,

      :p_epsi1,       :data_t,

      :wT,            :data_t,

      :wT0,           :data_t,

      :wT1,           :data_t,

      :mu__x__max,    :data_t,

      :mu__y__max,    :data_t,

      :up_epsi0,      :data_t,

      :up_epsi1,      :data_t,

      :v__Omega__max, :data_t,

      :v__fx__max,    :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class PointMassCarModel_4_BC_params < FFI::Struct
    layout(

      :initial_V,    :bool,

      :initial_s,    :bool,

      :final_s,      :bool,

      :cyclic_n,     :bool,

      :cyclic_alpha, :bool,

      :cyclic_V,     :bool,

      :cyclic_fx,    :bool,

      :cyclic_Omega, :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class PointMassCarModel_4_constraints_params < FFI::Struct
    layout(
      # LT constraints
      :AdherenceEllipseSubType, :index_t,
      :AdherenceEllipseEpsilon, :data_t,
      :AdherenceEllipseTolerance, :data_t,
      :RoadLeftBorderSubType, :index_t,
      :RoadLeftBorderEpsilon, :data_t,
      :RoadLeftBorderTolerance, :data_t,
      :RoadRightBorderSubType, :index_t,
      :RoadRightBorderEpsilon, :data_t,
      :RoadRightBorderTolerance, :data_t,
      :PowerLimitSubType, :index_t,
      :PowerLimitEpsilon, :data_t,
      :PowerLimitTolerance, :data_t,

      # 1D constraints

      # 2D constraints

      # Controls
      :v__fxControlType,         :index_t,
      :v__fxControlEpsilon,      :data_t,
      :v__fxControlTolerance,    :data_t,
      :v__OmegaControlType,      :index_t,
      :v__OmegaControlEpsilon,   :data_t,
      :v__OmegaControlTolerance, :data_t,
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
                  :PointMassCarModel_4_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :PointMassCarModel_4_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :PointMassCarModel_4_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :PointMassCarModel_4_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :PointMassCarModel_4_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :PointMassCarModel_4_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :PointMassCarModel_4_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :PointMassCarModel_4_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :PointMassCarModel_4_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: PointMassCarModel_4_ffi_stucts.rb
