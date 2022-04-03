#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: ICLOCS_ContinuousMP_ffi_structs.rb                                #
#                                                                          #
#  version: 1.0   date 3/4/2022                                            #
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

      :xy_eps0,  :data_t,

      :xy_eps1,  :data_t,

      :xy_tol0,  :data_t,

      :xy_tol1,  :data_t,

      :xy_bound, :data_t,

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
      # LT constraints
      :u1Limitation_minSubType, :index_t,
      :u1Limitation_minEpsilon, :data_t,
      :u1Limitation_minTolerance, :data_t,
      :u1Limitation_maxSubType, :index_t,
      :u1Limitation_maxEpsilon, :data_t,
      :u1Limitation_maxTolerance, :data_t,
      :u2Limitation_minSubType, :index_t,
      :u2Limitation_minEpsilon, :data_t,
      :u2Limitation_minTolerance, :data_t,
      :u2Limitation_maxSubType, :index_t,
      :u2Limitation_maxEpsilon, :data_t,
      :u2Limitation_maxTolerance, :data_t,
      :u3Limitation_minSubType, :index_t,
      :u3Limitation_minEpsilon, :data_t,
      :u3Limitation_minTolerance, :data_t,
      :u3Limitation_maxSubType, :index_t,
      :u3Limitation_maxEpsilon, :data_t,
      :u3Limitation_maxTolerance, :data_t,
      :u4Limitation_minSubType, :index_t,
      :u4Limitation_minEpsilon, :data_t,
      :u4Limitation_minTolerance, :data_t,
      :u4Limitation_maxSubType, :index_t,
      :u4Limitation_maxEpsilon, :data_t,
      :u4Limitation_maxTolerance, :data_t,
      :u5Limitation_minSubType, :index_t,
      :u5Limitation_minEpsilon, :data_t,
      :u5Limitation_minTolerance, :data_t,
      :u5Limitation_maxSubType, :index_t,
      :u5Limitation_maxEpsilon, :data_t,
      :u5Limitation_maxTolerance, :data_t,
      :u6Limitation_minSubType, :index_t,
      :u6Limitation_minEpsilon, :data_t,
      :u6Limitation_minTolerance, :data_t,
      :u6Limitation_maxSubType, :index_t,
      :u6Limitation_maxEpsilon, :data_t,
      :u6Limitation_maxTolerance, :data_t,
      :u7Limitation_minSubType, :index_t,
      :u7Limitation_minEpsilon, :data_t,
      :u7Limitation_minTolerance, :data_t,
      :u7Limitation_maxSubType, :index_t,
      :u7Limitation_maxEpsilon, :data_t,
      :u7Limitation_maxTolerance, :data_t,
      :u8Limitation_minSubType, :index_t,
      :u8Limitation_minEpsilon, :data_t,
      :u8Limitation_minTolerance, :data_t,
      :u8Limitation_maxSubType, :index_t,
      :u8Limitation_maxEpsilon, :data_t,
      :u8Limitation_maxTolerance, :data_t,
      :u9Limitation_minSubType, :index_t,
      :u9Limitation_minEpsilon, :data_t,
      :u9Limitation_minTolerance, :data_t,
      :u9Limitation_maxSubType, :index_t,
      :u9Limitation_maxEpsilon, :data_t,
      :u9Limitation_maxTolerance, :data_t,
      :u10Limitation_minSubType, :index_t,
      :u10Limitation_minEpsilon, :data_t,
      :u10Limitation_minTolerance, :data_t,
      :u10Limitation_maxSubType, :index_t,
      :u10Limitation_maxEpsilon, :data_t,
      :u10Limitation_maxTolerance, :data_t,
      :u11Limitation_minSubType, :index_t,
      :u11Limitation_minEpsilon, :data_t,
      :u11Limitation_minTolerance, :data_t,
      :u11Limitation_maxSubType, :index_t,
      :u11Limitation_maxEpsilon, :data_t,
      :u11Limitation_maxTolerance, :data_t,
      :u12Limitation_minSubType, :index_t,
      :u12Limitation_minEpsilon, :data_t,
      :u12Limitation_minTolerance, :data_t,
      :u12Limitation_maxSubType, :index_t,
      :u12Limitation_maxEpsilon, :data_t,
      :u12Limitation_maxTolerance, :data_t,
      :u13Limitation_minSubType, :index_t,
      :u13Limitation_minEpsilon, :data_t,
      :u13Limitation_minTolerance, :data_t,
      :u13Limitation_maxSubType, :index_t,
      :u13Limitation_maxEpsilon, :data_t,
      :u13Limitation_maxTolerance, :data_t,
      :u14Limitation_minSubType, :index_t,
      :u14Limitation_minEpsilon, :data_t,
      :u14Limitation_minTolerance, :data_t,
      :u14Limitation_maxSubType, :index_t,
      :u14Limitation_maxEpsilon, :data_t,
      :u14Limitation_maxTolerance, :data_t,
      :u15Limitation_minSubType, :index_t,
      :u15Limitation_minEpsilon, :data_t,
      :u15Limitation_minTolerance, :data_t,
      :u15Limitation_maxSubType, :index_t,
      :u15Limitation_maxEpsilon, :data_t,
      :u15Limitation_maxTolerance, :data_t,
      :u16Limitation_minSubType, :index_t,
      :u16Limitation_minEpsilon, :data_t,
      :u16Limitation_minTolerance, :data_t,
      :u16Limitation_maxSubType, :index_t,
      :u16Limitation_maxEpsilon, :data_t,
      :u16Limitation_maxTolerance, :data_t,
      :u17Limitation_minSubType, :index_t,
      :u17Limitation_minEpsilon, :data_t,
      :u17Limitation_minTolerance, :data_t,
      :u17Limitation_maxSubType, :index_t,
      :u17Limitation_maxEpsilon, :data_t,
      :u17Limitation_maxTolerance, :data_t,
      :u18Limitation_minSubType, :index_t,
      :u18Limitation_minEpsilon, :data_t,
      :u18Limitation_minTolerance, :data_t,
      :u18Limitation_maxSubType, :index_t,
      :u18Limitation_maxEpsilon, :data_t,
      :u18Limitation_maxTolerance, :data_t,
      :u19Limitation_minSubType, :index_t,
      :u19Limitation_minEpsilon, :data_t,
      :u19Limitation_minTolerance, :data_t,
      :u19Limitation_maxSubType, :index_t,
      :u19Limitation_maxEpsilon, :data_t,
      :u19Limitation_maxTolerance, :data_t,
      :u20Limitation_minSubType, :index_t,
      :u20Limitation_minEpsilon, :data_t,
      :u20Limitation_minTolerance, :data_t,
      :u20Limitation_maxSubType, :index_t,
      :u20Limitation_maxEpsilon, :data_t,
      :u20Limitation_maxTolerance, :data_t,
      :xx1Limitation_minSubType, :index_t,
      :xx1Limitation_minEpsilon, :data_t,
      :xx1Limitation_minTolerance, :data_t,
      :xx1Limitation_maxSubType, :index_t,
      :xx1Limitation_maxEpsilon, :data_t,
      :xx1Limitation_maxTolerance, :data_t,
      :yy1Limitation_minSubType, :index_t,
      :yy1Limitation_minEpsilon, :data_t,
      :yy1Limitation_minTolerance, :data_t,
      :yy1Limitation_maxSubType, :index_t,
      :yy1Limitation_maxEpsilon, :data_t,
      :yy1Limitation_maxTolerance, :data_t,
      :xx2Limitation_minSubType, :index_t,
      :xx2Limitation_minEpsilon, :data_t,
      :xx2Limitation_minTolerance, :data_t,
      :xx2Limitation_maxSubType, :index_t,
      :xx2Limitation_maxEpsilon, :data_t,
      :xx2Limitation_maxTolerance, :data_t,
      :yy2Limitation_minSubType, :index_t,
      :yy2Limitation_minEpsilon, :data_t,
      :yy2Limitation_minTolerance, :data_t,
      :yy2Limitation_maxSubType, :index_t,
      :yy2Limitation_maxEpsilon, :data_t,
      :yy2Limitation_maxTolerance, :data_t,
      :xx3Limitation_minSubType, :index_t,
      :xx3Limitation_minEpsilon, :data_t,
      :xx3Limitation_minTolerance, :data_t,
      :xx3Limitation_maxSubType, :index_t,
      :xx3Limitation_maxEpsilon, :data_t,
      :xx3Limitation_maxTolerance, :data_t,
      :yy3Limitation_minSubType, :index_t,
      :yy3Limitation_minEpsilon, :data_t,
      :yy3Limitation_minTolerance, :data_t,
      :yy3Limitation_maxSubType, :index_t,
      :yy3Limitation_maxEpsilon, :data_t,
      :yy3Limitation_maxTolerance, :data_t,
      :xx4Limitation_minSubType, :index_t,
      :xx4Limitation_minEpsilon, :data_t,
      :xx4Limitation_minTolerance, :data_t,
      :xx4Limitation_maxSubType, :index_t,
      :xx4Limitation_maxEpsilon, :data_t,
      :xx4Limitation_maxTolerance, :data_t,
      :yy4Limitation_minSubType, :index_t,
      :yy4Limitation_minEpsilon, :data_t,
      :yy4Limitation_minTolerance, :data_t,
      :yy4Limitation_maxSubType, :index_t,
      :yy4Limitation_maxEpsilon, :data_t,
      :yy4Limitation_maxTolerance, :data_t,
      :xx5Limitation_minSubType, :index_t,
      :xx5Limitation_minEpsilon, :data_t,
      :xx5Limitation_minTolerance, :data_t,
      :xx5Limitation_maxSubType, :index_t,
      :xx5Limitation_maxEpsilon, :data_t,
      :xx5Limitation_maxTolerance, :data_t,
      :yy5Limitation_minSubType, :index_t,
      :yy5Limitation_minEpsilon, :data_t,
      :yy5Limitation_minTolerance, :data_t,
      :yy5Limitation_maxSubType, :index_t,
      :yy5Limitation_maxEpsilon, :data_t,
      :yy5Limitation_maxTolerance, :data_t,
      :xx6Limitation_minSubType, :index_t,
      :xx6Limitation_minEpsilon, :data_t,
      :xx6Limitation_minTolerance, :data_t,
      :xx6Limitation_maxSubType, :index_t,
      :xx6Limitation_maxEpsilon, :data_t,
      :xx6Limitation_maxTolerance, :data_t,
      :yy6Limitation_minSubType, :index_t,
      :yy6Limitation_minEpsilon, :data_t,
      :yy6Limitation_minTolerance, :data_t,
      :yy6Limitation_maxSubType, :index_t,
      :yy6Limitation_maxEpsilon, :data_t,
      :yy6Limitation_maxTolerance, :data_t,
      :xx7Limitation_minSubType, :index_t,
      :xx7Limitation_minEpsilon, :data_t,
      :xx7Limitation_minTolerance, :data_t,
      :xx7Limitation_maxSubType, :index_t,
      :xx7Limitation_maxEpsilon, :data_t,
      :xx7Limitation_maxTolerance, :data_t,
      :yy7Limitation_minSubType, :index_t,
      :yy7Limitation_minEpsilon, :data_t,
      :yy7Limitation_minTolerance, :data_t,
      :yy7Limitation_maxSubType, :index_t,
      :yy7Limitation_maxEpsilon, :data_t,
      :yy7Limitation_maxTolerance, :data_t,
      :xx8Limitation_minSubType, :index_t,
      :xx8Limitation_minEpsilon, :data_t,
      :xx8Limitation_minTolerance, :data_t,
      :xx8Limitation_maxSubType, :index_t,
      :xx8Limitation_maxEpsilon, :data_t,
      :xx8Limitation_maxTolerance, :data_t,
      :yy8Limitation_minSubType, :index_t,
      :yy8Limitation_minEpsilon, :data_t,
      :yy8Limitation_minTolerance, :data_t,
      :yy8Limitation_maxSubType, :index_t,
      :yy8Limitation_maxEpsilon, :data_t,
      :yy8Limitation_maxTolerance, :data_t,
      :xx9Limitation_minSubType, :index_t,
      :xx9Limitation_minEpsilon, :data_t,
      :xx9Limitation_minTolerance, :data_t,
      :xx9Limitation_maxSubType, :index_t,
      :xx9Limitation_maxEpsilon, :data_t,
      :xx9Limitation_maxTolerance, :data_t,
      :yy9Limitation_minSubType, :index_t,
      :yy9Limitation_minEpsilon, :data_t,
      :yy9Limitation_minTolerance, :data_t,
      :yy9Limitation_maxSubType, :index_t,
      :yy9Limitation_maxEpsilon, :data_t,
      :yy9Limitation_maxTolerance, :data_t,
      :xx10Limitation_minSubType, :index_t,
      :xx10Limitation_minEpsilon, :data_t,
      :xx10Limitation_minTolerance, :data_t,
      :xx10Limitation_maxSubType, :index_t,
      :xx10Limitation_maxEpsilon, :data_t,
      :xx10Limitation_maxTolerance, :data_t,
      :yy10Limitation_minSubType, :index_t,
      :yy10Limitation_minEpsilon, :data_t,
      :yy10Limitation_minTolerance, :data_t,
      :yy10Limitation_maxSubType, :index_t,
      :yy10Limitation_maxEpsilon, :data_t,
      :yy10Limitation_maxTolerance, :data_t,
      :xx11Limitation_minSubType, :index_t,
      :xx11Limitation_minEpsilon, :data_t,
      :xx11Limitation_minTolerance, :data_t,
      :xx11Limitation_maxSubType, :index_t,
      :xx11Limitation_maxEpsilon, :data_t,
      :xx11Limitation_maxTolerance, :data_t,
      :yy11Limitation_minSubType, :index_t,
      :yy11Limitation_minEpsilon, :data_t,
      :yy11Limitation_minTolerance, :data_t,
      :yy11Limitation_maxSubType, :index_t,
      :yy11Limitation_maxEpsilon, :data_t,
      :yy11Limitation_maxTolerance, :data_t,
      :xx12Limitation_minSubType, :index_t,
      :xx12Limitation_minEpsilon, :data_t,
      :xx12Limitation_minTolerance, :data_t,
      :xx12Limitation_maxSubType, :index_t,
      :xx12Limitation_maxEpsilon, :data_t,
      :xx12Limitation_maxTolerance, :data_t,
      :yy12Limitation_minSubType, :index_t,
      :yy12Limitation_minEpsilon, :data_t,
      :yy12Limitation_minTolerance, :data_t,
      :yy12Limitation_maxSubType, :index_t,
      :yy12Limitation_maxEpsilon, :data_t,
      :yy12Limitation_maxTolerance, :data_t,
      :xx13Limitation_minSubType, :index_t,
      :xx13Limitation_minEpsilon, :data_t,
      :xx13Limitation_minTolerance, :data_t,
      :xx13Limitation_maxSubType, :index_t,
      :xx13Limitation_maxEpsilon, :data_t,
      :xx13Limitation_maxTolerance, :data_t,
      :yy13Limitation_minSubType, :index_t,
      :yy13Limitation_minEpsilon, :data_t,
      :yy13Limitation_minTolerance, :data_t,
      :yy13Limitation_maxSubType, :index_t,
      :yy13Limitation_maxEpsilon, :data_t,
      :yy13Limitation_maxTolerance, :data_t,
      :xx14Limitation_minSubType, :index_t,
      :xx14Limitation_minEpsilon, :data_t,
      :xx14Limitation_minTolerance, :data_t,
      :xx14Limitation_maxSubType, :index_t,
      :xx14Limitation_maxEpsilon, :data_t,
      :xx14Limitation_maxTolerance, :data_t,
      :yy14Limitation_minSubType, :index_t,
      :yy14Limitation_minEpsilon, :data_t,
      :yy14Limitation_minTolerance, :data_t,
      :yy14Limitation_maxSubType, :index_t,
      :yy14Limitation_maxEpsilon, :data_t,
      :yy14Limitation_maxTolerance, :data_t,
      :xx15Limitation_minSubType, :index_t,
      :xx15Limitation_minEpsilon, :data_t,
      :xx15Limitation_minTolerance, :data_t,
      :xx15Limitation_maxSubType, :index_t,
      :xx15Limitation_maxEpsilon, :data_t,
      :xx15Limitation_maxTolerance, :data_t,
      :yy15Limitation_minSubType, :index_t,
      :yy15Limitation_minEpsilon, :data_t,
      :yy15Limitation_minTolerance, :data_t,
      :yy15Limitation_maxSubType, :index_t,
      :yy15Limitation_maxEpsilon, :data_t,
      :yy15Limitation_maxTolerance, :data_t,
      :xx16Limitation_minSubType, :index_t,
      :xx16Limitation_minEpsilon, :data_t,
      :xx16Limitation_minTolerance, :data_t,
      :xx16Limitation_maxSubType, :index_t,
      :xx16Limitation_maxEpsilon, :data_t,
      :xx16Limitation_maxTolerance, :data_t,
      :yy16Limitation_minSubType, :index_t,
      :yy16Limitation_minEpsilon, :data_t,
      :yy16Limitation_minTolerance, :data_t,
      :yy16Limitation_maxSubType, :index_t,
      :yy16Limitation_maxEpsilon, :data_t,
      :yy16Limitation_maxTolerance, :data_t,
      :xx17Limitation_minSubType, :index_t,
      :xx17Limitation_minEpsilon, :data_t,
      :xx17Limitation_minTolerance, :data_t,
      :xx17Limitation_maxSubType, :index_t,
      :xx17Limitation_maxEpsilon, :data_t,
      :xx17Limitation_maxTolerance, :data_t,
      :yy17Limitation_minSubType, :index_t,
      :yy17Limitation_minEpsilon, :data_t,
      :yy17Limitation_minTolerance, :data_t,
      :yy17Limitation_maxSubType, :index_t,
      :yy17Limitation_maxEpsilon, :data_t,
      :yy17Limitation_maxTolerance, :data_t,
      :xx18Limitation_minSubType, :index_t,
      :xx18Limitation_minEpsilon, :data_t,
      :xx18Limitation_minTolerance, :data_t,
      :xx18Limitation_maxSubType, :index_t,
      :xx18Limitation_maxEpsilon, :data_t,
      :xx18Limitation_maxTolerance, :data_t,
      :yy18Limitation_minSubType, :index_t,
      :yy18Limitation_minEpsilon, :data_t,
      :yy18Limitation_minTolerance, :data_t,
      :yy18Limitation_maxSubType, :index_t,
      :yy18Limitation_maxEpsilon, :data_t,
      :yy18Limitation_maxTolerance, :data_t,
      :xx19Limitation_minSubType, :index_t,
      :xx19Limitation_minEpsilon, :data_t,
      :xx19Limitation_minTolerance, :data_t,
      :xx19Limitation_maxSubType, :index_t,
      :xx19Limitation_maxEpsilon, :data_t,
      :xx19Limitation_maxTolerance, :data_t,
      :yy19Limitation_minSubType, :index_t,
      :yy19Limitation_minEpsilon, :data_t,
      :yy19Limitation_minTolerance, :data_t,
      :yy19Limitation_maxSubType, :index_t,
      :yy19Limitation_maxEpsilon, :data_t,
      :yy19Limitation_maxTolerance, :data_t,
      :xx20Limitation_minSubType, :index_t,
      :xx20Limitation_minEpsilon, :data_t,
      :xx20Limitation_minTolerance, :data_t,
      :xx20Limitation_maxSubType, :index_t,
      :xx20Limitation_maxEpsilon, :data_t,
      :xx20Limitation_maxTolerance, :data_t,
      :yy20Limitation_minSubType, :index_t,
      :yy20Limitation_minEpsilon, :data_t,
      :yy20Limitation_minTolerance, :data_t,
      :yy20Limitation_maxSubType, :index_t,
      :yy20Limitation_maxEpsilon, :data_t,
      :yy20Limitation_maxTolerance, :data_t,

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
