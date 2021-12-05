#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS_ContinuousMP_ffi_structs.rb                                #
#                                                                          #
#  version: 1.0   date 10/12/2021                                          #
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

module ICLOCS_ContinuousMP

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class ICLOCS_ContinuousMP_solver_params < FFI::Struct
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

  class ICLOCS_ContinuousMP_model_params < FFI::Struct
    layout(

      :xy_eps0, :data_t,

      :xy_eps1, :data_t,

      :xy_tol0, :data_t,

      :xy_tol1, :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_ContinuousMP_BC_params < FFI::Struct
    layout(

      :initial_xx1,    :bool,

      :initial_yy1,    :bool,

      :X1_continuity,  :bool,

      :X2_continuity,  :bool,

      :X3_continuity,  :bool,

      :X4_continuity,  :bool,

      :X5_continuity,  :bool,

      :X6_continuity,  :bool,

      :X7_continuity,  :bool,

      :X8_continuity,  :bool,

      :X9_continuity,  :bool,

      :X10_continuity, :bool,

      :X11_continuity, :bool,

      :X12_continuity, :bool,

      :X13_continuity, :bool,

      :X14_continuity, :bool,

      :X15_continuity, :bool,

      :X16_continuity, :bool,

      :X17_continuity, :bool,

      :X18_continuity, :bool,

      :X19_continuity, :bool,

      :Y1_continuity,  :bool,

      :Y2_continuity,  :bool,

      :Y3_continuity,  :bool,

      :Y4_continuity,  :bool,

      :Y5_continuity,  :bool,

      :Y6_continuity,  :bool,

      :Y7_continuity,  :bool,

      :Y8_continuity,  :bool,

      :Y9_continuity,  :bool,

      :Y10_continuity, :bool,

      :Y11_continuity, :bool,

      :Y12_continuity, :bool,

      :Y13_continuity, :bool,

      :Y14_continuity, :bool,

      :Y15_continuity, :bool,

      :Y16_continuity, :bool,

      :Y17_continuity, :bool,

      :Y18_continuity, :bool,

      :Y19_continuity, :bool,

      :X1_initial,     :bool,

      :X2_initial,     :bool,

      :X3_initial,     :bool,

      :X4_initial,     :bool,

      :X5_initial,     :bool,

      :X6_initial,     :bool,

      :X7_initial,     :bool,

      :X8_initial,     :bool,

      :X9_initial,     :bool,

      :X10_initial,    :bool,

      :X11_initial,    :bool,

      :X12_initial,    :bool,

      :X13_initial,    :bool,

      :X14_initial,    :bool,

      :X15_initial,    :bool,

      :X16_initial,    :bool,

      :X17_initial,    :bool,

      :X18_initial,    :bool,

      :X19_initial,    :bool,

      :X20_initial,    :bool,

      :Y1_initial,     :bool,

      :Y2_initial,     :bool,

      :Y3_initial,     :bool,

      :Y4_initial,     :bool,

      :Y5_initial,     :bool,

      :Y6_initial,     :bool,

      :Y7_initial,     :bool,

      :Y8_initial,     :bool,

      :Y9_initial,     :bool,

      :Y10_initial,    :bool,

      :Y11_initial,    :bool,

      :Y12_initial,    :bool,

      :Y13_initial,    :bool,

      :Y14_initial,    :bool,

      :Y15_initial,    :bool,

      :Y16_initial,    :bool,

      :Y17_initial,    :bool,

      :Y18_initial,    :bool,

      :Y19_initial,    :bool,

      :Y20_initial,    :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class ICLOCS_ContinuousMP_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :u1LimitationSubType,     :index_t,
      :u1LimitationEpsilon,     :data_t,
      :u1LimitationTolerance,   :data_t,
      :u1LimitationMinValue,    :data_t,
      :u1LimitationMaxValue,    :data_t,
      :u2LimitationSubType,     :index_t,
      :u2LimitationEpsilon,     :data_t,
      :u2LimitationTolerance,   :data_t,
      :u2LimitationMinValue,    :data_t,
      :u2LimitationMaxValue,    :data_t,
      :u3LimitationSubType,     :index_t,
      :u3LimitationEpsilon,     :data_t,
      :u3LimitationTolerance,   :data_t,
      :u3LimitationMinValue,    :data_t,
      :u3LimitationMaxValue,    :data_t,
      :u4LimitationSubType,     :index_t,
      :u4LimitationEpsilon,     :data_t,
      :u4LimitationTolerance,   :data_t,
      :u4LimitationMinValue,    :data_t,
      :u4LimitationMaxValue,    :data_t,
      :u5LimitationSubType,     :index_t,
      :u5LimitationEpsilon,     :data_t,
      :u5LimitationTolerance,   :data_t,
      :u5LimitationMinValue,    :data_t,
      :u5LimitationMaxValue,    :data_t,
      :u6LimitationSubType,     :index_t,
      :u6LimitationEpsilon,     :data_t,
      :u6LimitationTolerance,   :data_t,
      :u6LimitationMinValue,    :data_t,
      :u6LimitationMaxValue,    :data_t,
      :u7LimitationSubType,     :index_t,
      :u7LimitationEpsilon,     :data_t,
      :u7LimitationTolerance,   :data_t,
      :u7LimitationMinValue,    :data_t,
      :u7LimitationMaxValue,    :data_t,
      :u8LimitationSubType,     :index_t,
      :u8LimitationEpsilon,     :data_t,
      :u8LimitationTolerance,   :data_t,
      :u8LimitationMinValue,    :data_t,
      :u8LimitationMaxValue,    :data_t,
      :u9LimitationSubType,     :index_t,
      :u9LimitationEpsilon,     :data_t,
      :u9LimitationTolerance,   :data_t,
      :u9LimitationMinValue,    :data_t,
      :u9LimitationMaxValue,    :data_t,
      :u10LimitationSubType,    :index_t,
      :u10LimitationEpsilon,    :data_t,
      :u10LimitationTolerance,  :data_t,
      :u10LimitationMinValue,   :data_t,
      :u10LimitationMaxValue,   :data_t,
      :u11LimitationSubType,    :index_t,
      :u11LimitationEpsilon,    :data_t,
      :u11LimitationTolerance,  :data_t,
      :u11LimitationMinValue,   :data_t,
      :u11LimitationMaxValue,   :data_t,
      :u12LimitationSubType,    :index_t,
      :u12LimitationEpsilon,    :data_t,
      :u12LimitationTolerance,  :data_t,
      :u12LimitationMinValue,   :data_t,
      :u12LimitationMaxValue,   :data_t,
      :u13LimitationSubType,    :index_t,
      :u13LimitationEpsilon,    :data_t,
      :u13LimitationTolerance,  :data_t,
      :u13LimitationMinValue,   :data_t,
      :u13LimitationMaxValue,   :data_t,
      :u14LimitationSubType,    :index_t,
      :u14LimitationEpsilon,    :data_t,
      :u14LimitationTolerance,  :data_t,
      :u14LimitationMinValue,   :data_t,
      :u14LimitationMaxValue,   :data_t,
      :u15LimitationSubType,    :index_t,
      :u15LimitationEpsilon,    :data_t,
      :u15LimitationTolerance,  :data_t,
      :u15LimitationMinValue,   :data_t,
      :u15LimitationMaxValue,   :data_t,
      :u16LimitationSubType,    :index_t,
      :u16LimitationEpsilon,    :data_t,
      :u16LimitationTolerance,  :data_t,
      :u16LimitationMinValue,   :data_t,
      :u16LimitationMaxValue,   :data_t,
      :u17LimitationSubType,    :index_t,
      :u17LimitationEpsilon,    :data_t,
      :u17LimitationTolerance,  :data_t,
      :u17LimitationMinValue,   :data_t,
      :u17LimitationMaxValue,   :data_t,
      :u18LimitationSubType,    :index_t,
      :u18LimitationEpsilon,    :data_t,
      :u18LimitationTolerance,  :data_t,
      :u18LimitationMinValue,   :data_t,
      :u18LimitationMaxValue,   :data_t,
      :u19LimitationSubType,    :index_t,
      :u19LimitationEpsilon,    :data_t,
      :u19LimitationTolerance,  :data_t,
      :u19LimitationMinValue,   :data_t,
      :u19LimitationMaxValue,   :data_t,
      :u20LimitationSubType,    :index_t,
      :u20LimitationEpsilon,    :data_t,
      :u20LimitationTolerance,  :data_t,
      :u20LimitationMinValue,   :data_t,
      :u20LimitationMaxValue,   :data_t,
      :xx1LimitationSubType,    :index_t,
      :xx1LimitationEpsilon,    :data_t,
      :xx1LimitationTolerance,  :data_t,
      :xx1LimitationMinValue,   :data_t,
      :xx1LimitationMaxValue,   :data_t,
      :yy1LimitationSubType,    :index_t,
      :yy1LimitationEpsilon,    :data_t,
      :yy1LimitationTolerance,  :data_t,
      :yy1LimitationMinValue,   :data_t,
      :yy1LimitationMaxValue,   :data_t,
      :xx2LimitationSubType,    :index_t,
      :xx2LimitationEpsilon,    :data_t,
      :xx2LimitationTolerance,  :data_t,
      :xx2LimitationMinValue,   :data_t,
      :xx2LimitationMaxValue,   :data_t,
      :yy2LimitationSubType,    :index_t,
      :yy2LimitationEpsilon,    :data_t,
      :yy2LimitationTolerance,  :data_t,
      :yy2LimitationMinValue,   :data_t,
      :yy2LimitationMaxValue,   :data_t,
      :xx3LimitationSubType,    :index_t,
      :xx3LimitationEpsilon,    :data_t,
      :xx3LimitationTolerance,  :data_t,
      :xx3LimitationMinValue,   :data_t,
      :xx3LimitationMaxValue,   :data_t,
      :yy3LimitationSubType,    :index_t,
      :yy3LimitationEpsilon,    :data_t,
      :yy3LimitationTolerance,  :data_t,
      :yy3LimitationMinValue,   :data_t,
      :yy3LimitationMaxValue,   :data_t,
      :xx4LimitationSubType,    :index_t,
      :xx4LimitationEpsilon,    :data_t,
      :xx4LimitationTolerance,  :data_t,
      :xx4LimitationMinValue,   :data_t,
      :xx4LimitationMaxValue,   :data_t,
      :yy4LimitationSubType,    :index_t,
      :yy4LimitationEpsilon,    :data_t,
      :yy4LimitationTolerance,  :data_t,
      :yy4LimitationMinValue,   :data_t,
      :yy4LimitationMaxValue,   :data_t,
      :xx5LimitationSubType,    :index_t,
      :xx5LimitationEpsilon,    :data_t,
      :xx5LimitationTolerance,  :data_t,
      :xx5LimitationMinValue,   :data_t,
      :xx5LimitationMaxValue,   :data_t,
      :yy5LimitationSubType,    :index_t,
      :yy5LimitationEpsilon,    :data_t,
      :yy5LimitationTolerance,  :data_t,
      :yy5LimitationMinValue,   :data_t,
      :yy5LimitationMaxValue,   :data_t,
      :xx6LimitationSubType,    :index_t,
      :xx6LimitationEpsilon,    :data_t,
      :xx6LimitationTolerance,  :data_t,
      :xx6LimitationMinValue,   :data_t,
      :xx6LimitationMaxValue,   :data_t,
      :yy6LimitationSubType,    :index_t,
      :yy6LimitationEpsilon,    :data_t,
      :yy6LimitationTolerance,  :data_t,
      :yy6LimitationMinValue,   :data_t,
      :yy6LimitationMaxValue,   :data_t,
      :xx7LimitationSubType,    :index_t,
      :xx7LimitationEpsilon,    :data_t,
      :xx7LimitationTolerance,  :data_t,
      :xx7LimitationMinValue,   :data_t,
      :xx7LimitationMaxValue,   :data_t,
      :yy7LimitationSubType,    :index_t,
      :yy7LimitationEpsilon,    :data_t,
      :yy7LimitationTolerance,  :data_t,
      :yy7LimitationMinValue,   :data_t,
      :yy7LimitationMaxValue,   :data_t,
      :xx8LimitationSubType,    :index_t,
      :xx8LimitationEpsilon,    :data_t,
      :xx8LimitationTolerance,  :data_t,
      :xx8LimitationMinValue,   :data_t,
      :xx8LimitationMaxValue,   :data_t,
      :yy8LimitationSubType,    :index_t,
      :yy8LimitationEpsilon,    :data_t,
      :yy8LimitationTolerance,  :data_t,
      :yy8LimitationMinValue,   :data_t,
      :yy8LimitationMaxValue,   :data_t,
      :xx9LimitationSubType,    :index_t,
      :xx9LimitationEpsilon,    :data_t,
      :xx9LimitationTolerance,  :data_t,
      :xx9LimitationMinValue,   :data_t,
      :xx9LimitationMaxValue,   :data_t,
      :yy9LimitationSubType,    :index_t,
      :yy9LimitationEpsilon,    :data_t,
      :yy9LimitationTolerance,  :data_t,
      :yy9LimitationMinValue,   :data_t,
      :yy9LimitationMaxValue,   :data_t,
      :xx10LimitationSubType,   :index_t,
      :xx10LimitationEpsilon,   :data_t,
      :xx10LimitationTolerance, :data_t,
      :xx10LimitationMinValue,  :data_t,
      :xx10LimitationMaxValue,  :data_t,
      :yy10LimitationSubType,   :index_t,
      :yy10LimitationEpsilon,   :data_t,
      :yy10LimitationTolerance, :data_t,
      :yy10LimitationMinValue,  :data_t,
      :yy10LimitationMaxValue,  :data_t,
      :xx11LimitationSubType,   :index_t,
      :xx11LimitationEpsilon,   :data_t,
      :xx11LimitationTolerance, :data_t,
      :xx11LimitationMinValue,  :data_t,
      :xx11LimitationMaxValue,  :data_t,
      :yy11LimitationSubType,   :index_t,
      :yy11LimitationEpsilon,   :data_t,
      :yy11LimitationTolerance, :data_t,
      :yy11LimitationMinValue,  :data_t,
      :yy11LimitationMaxValue,  :data_t,
      :xx12LimitationSubType,   :index_t,
      :xx12LimitationEpsilon,   :data_t,
      :xx12LimitationTolerance, :data_t,
      :xx12LimitationMinValue,  :data_t,
      :xx12LimitationMaxValue,  :data_t,
      :yy12LimitationSubType,   :index_t,
      :yy12LimitationEpsilon,   :data_t,
      :yy12LimitationTolerance, :data_t,
      :yy12LimitationMinValue,  :data_t,
      :yy12LimitationMaxValue,  :data_t,
      :xx13LimitationSubType,   :index_t,
      :xx13LimitationEpsilon,   :data_t,
      :xx13LimitationTolerance, :data_t,
      :xx13LimitationMinValue,  :data_t,
      :xx13LimitationMaxValue,  :data_t,
      :yy13LimitationSubType,   :index_t,
      :yy13LimitationEpsilon,   :data_t,
      :yy13LimitationTolerance, :data_t,
      :yy13LimitationMinValue,  :data_t,
      :yy13LimitationMaxValue,  :data_t,
      :xx14LimitationSubType,   :index_t,
      :xx14LimitationEpsilon,   :data_t,
      :xx14LimitationTolerance, :data_t,
      :xx14LimitationMinValue,  :data_t,
      :xx14LimitationMaxValue,  :data_t,
      :yy14LimitationSubType,   :index_t,
      :yy14LimitationEpsilon,   :data_t,
      :yy14LimitationTolerance, :data_t,
      :yy14LimitationMinValue,  :data_t,
      :yy14LimitationMaxValue,  :data_t,
      :xx15LimitationSubType,   :index_t,
      :xx15LimitationEpsilon,   :data_t,
      :xx15LimitationTolerance, :data_t,
      :xx15LimitationMinValue,  :data_t,
      :xx15LimitationMaxValue,  :data_t,
      :yy15LimitationSubType,   :index_t,
      :yy15LimitationEpsilon,   :data_t,
      :yy15LimitationTolerance, :data_t,
      :yy15LimitationMinValue,  :data_t,
      :yy15LimitationMaxValue,  :data_t,
      :xx16LimitationSubType,   :index_t,
      :xx16LimitationEpsilon,   :data_t,
      :xx16LimitationTolerance, :data_t,
      :xx16LimitationMinValue,  :data_t,
      :xx16LimitationMaxValue,  :data_t,
      :yy16LimitationSubType,   :index_t,
      :yy16LimitationEpsilon,   :data_t,
      :yy16LimitationTolerance, :data_t,
      :yy16LimitationMinValue,  :data_t,
      :yy16LimitationMaxValue,  :data_t,
      :xx17LimitationSubType,   :index_t,
      :xx17LimitationEpsilon,   :data_t,
      :xx17LimitationTolerance, :data_t,
      :xx17LimitationMinValue,  :data_t,
      :xx17LimitationMaxValue,  :data_t,
      :yy17LimitationSubType,   :index_t,
      :yy17LimitationEpsilon,   :data_t,
      :yy17LimitationTolerance, :data_t,
      :yy17LimitationMinValue,  :data_t,
      :yy17LimitationMaxValue,  :data_t,
      :xx18LimitationSubType,   :index_t,
      :xx18LimitationEpsilon,   :data_t,
      :xx18LimitationTolerance, :data_t,
      :xx18LimitationMinValue,  :data_t,
      :xx18LimitationMaxValue,  :data_t,
      :yy18LimitationSubType,   :index_t,
      :yy18LimitationEpsilon,   :data_t,
      :yy18LimitationTolerance, :data_t,
      :yy18LimitationMinValue,  :data_t,
      :yy18LimitationMaxValue,  :data_t,
      :xx19LimitationSubType,   :index_t,
      :xx19LimitationEpsilon,   :data_t,
      :xx19LimitationTolerance, :data_t,
      :xx19LimitationMinValue,  :data_t,
      :xx19LimitationMaxValue,  :data_t,
      :yy19LimitationSubType,   :index_t,
      :yy19LimitationEpsilon,   :data_t,
      :yy19LimitationTolerance, :data_t,
      :yy19LimitationMinValue,  :data_t,
      :yy19LimitationMaxValue,  :data_t,
      :xx20LimitationSubType,   :index_t,
      :xx20LimitationEpsilon,   :data_t,
      :xx20LimitationTolerance, :data_t,
      :xx20LimitationMinValue,  :data_t,
      :xx20LimitationMaxValue,  :data_t,
      :yy20LimitationSubType,   :index_t,
      :yy20LimitationEpsilon,   :data_t,
      :yy20LimitationTolerance, :data_t,
      :yy20LimitationMinValue,  :data_t,
      :yy20LimitationMaxValue,  :data_t,

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
                  :ICLOCS_ContinuousMP_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :ICLOCS_ContinuousMP_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :ICLOCS_ContinuousMP_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :ICLOCS_ContinuousMP_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :ICLOCS_ContinuousMP_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :ICLOCS_ContinuousMP_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :ICLOCS_ContinuousMP_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :ICLOCS_ContinuousMP_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :ICLOCS_ContinuousMP_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: ICLOCS_ContinuousMP_ffi_stucts.rb
