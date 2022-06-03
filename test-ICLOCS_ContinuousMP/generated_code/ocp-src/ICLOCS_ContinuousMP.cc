/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP.cc                                         |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace ICLOCS_ContinuousMPDefine {

  using GenericContainerNamespace::vec_string_type;

  /*
  //   _ __   __ _ _ __ ___   ___  ___
  //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | | | | (_| | | | | | |  __/\__ \
  //  |_| |_|\__,_|_| |_| |_|\___||___/
  //
  */

  char const *namesXvars[numXvars+1] = {
    "x1",
    "x2",
    "x3",
    "x4",
    "x5",
    "x6",
    "x7",
    "x8",
    "x9",
    "x10",
    "x11",
    "x12",
    "x13",
    "x14",
    "x15",
    "x16",
    "x17",
    "x18",
    "x19",
    "x20",
    "y1",
    "y2",
    "y3",
    "y4",
    "y5",
    "y6",
    "y7",
    "y8",
    "y9",
    "y10",
    "y11",
    "y12",
    "y13",
    "y14",
    "y15",
    "y16",
    "y17",
    "y18",
    "y19",
    "y20",
    "xx1",
    "xx2",
    "xx3",
    "xx4",
    "xx5",
    "xx6",
    "xx7",
    "xx8",
    "xx9",
    "xx10",
    "xx11",
    "xx12",
    "xx13",
    "xx14",
    "xx15",
    "xx16",
    "xx17",
    "xx18",
    "xx19",
    "xx20",
    "yy1",
    "yy2",
    "yy3",
    "yy4",
    "yy5",
    "yy6",
    "yy7",
    "yy8",
    "yy9",
    "yy10",
    "yy11",
    "yy12",
    "yy13",
    "yy14",
    "yy15",
    "yy16",
    "yy17",
    "yy18",
    "yy19",
    "yy20",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    "lambda2__xo",
    "lambda3__xo",
    "lambda4__xo",
    "lambda5__xo",
    "lambda6__xo",
    "lambda7__xo",
    "lambda8__xo",
    "lambda9__xo",
    "lambda10__xo",
    "lambda11__xo",
    "lambda12__xo",
    "lambda13__xo",
    "lambda14__xo",
    "lambda15__xo",
    "lambda16__xo",
    "lambda17__xo",
    "lambda18__xo",
    "lambda19__xo",
    "lambda20__xo",
    "lambda21__xo",
    "lambda22__xo",
    "lambda23__xo",
    "lambda24__xo",
    "lambda25__xo",
    "lambda26__xo",
    "lambda27__xo",
    "lambda28__xo",
    "lambda29__xo",
    "lambda30__xo",
    "lambda31__xo",
    "lambda32__xo",
    "lambda33__xo",
    "lambda34__xo",
    "lambda35__xo",
    "lambda36__xo",
    "lambda37__xo",
    "lambda38__xo",
    "lambda39__xo",
    "lambda40__xo",
    "lambda41__xo",
    "lambda42__xo",
    "lambda43__xo",
    "lambda44__xo",
    "lambda45__xo",
    "lambda46__xo",
    "lambda47__xo",
    "lambda48__xo",
    "lambda49__xo",
    "lambda50__xo",
    "lambda51__xo",
    "lambda52__xo",
    "lambda53__xo",
    "lambda54__xo",
    "lambda55__xo",
    "lambda56__xo",
    "lambda57__xo",
    "lambda58__xo",
    "lambda59__xo",
    "lambda60__xo",
    "lambda61__xo",
    "lambda62__xo",
    "lambda63__xo",
    "lambda64__xo",
    "lambda65__xo",
    "lambda66__xo",
    "lambda67__xo",
    "lambda68__xo",
    "lambda69__xo",
    "lambda70__xo",
    "lambda71__xo",
    "lambda72__xo",
    "lambda73__xo",
    "lambda74__xo",
    "lambda75__xo",
    "lambda76__xo",
    "lambda77__xo",
    "lambda78__xo",
    "lambda79__xo",
    "lambda80__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    nullptr
  };

  char const *namesQvars[numQvars+1] = {
    "zeta",
    nullptr
  };

  char const *namesPvars[numPvars+1] = {
    "u1",
    "u2",
    "u3",
    "u4",
    "u5",
    "u6",
    "u7",
    "u8",
    "u9",
    "u10",
    "u11",
    "u12",
    "u13",
    "u14",
    "u15",
    "u16",
    "u17",
    "u18",
    "u19",
    "u20",
    nullptr
  };

  char const *namesOMEGAvars[numOMEGAvars+1] = {
    "omega1__xo",
    "omega2__xo",
    "omega3__xo",
    "omega4__xo",
    "omega5__xo",
    "omega6__xo",
    "omega7__xo",
    "omega8__xo",
    "omega9__xo",
    "omega10__xo",
    "omega11__xo",
    "omega12__xo",
    "omega13__xo",
    "omega14__xo",
    "omega15__xo",
    "omega16__xo",
    "omega17__xo",
    "omega18__xo",
    "omega19__xo",
    "omega20__xo",
    "omega21__xo",
    "omega22__xo",
    "omega23__xo",
    "omega24__xo",
    "omega25__xo",
    "omega26__xo",
    "omega27__xo",
    "omega28__xo",
    "omega29__xo",
    "omega30__xo",
    "omega31__xo",
    "omega32__xo",
    "omega33__xo",
    "omega34__xo",
    "omega35__xo",
    "omega36__xo",
    "omega37__xo",
    "omega38__xo",
    "omega39__xo",
    "omega40__xo",
    "omega41__xo",
    "omega42__xo",
    "omega43__xo",
    "omega44__xo",
    "omega45__xo",
    "omega46__xo",
    "omega47__xo",
    "omega48__xo",
    "omega49__xo",
    "omega50__xo",
    "omega51__xo",
    "omega52__xo",
    "omega53__xo",
    "omega54__xo",
    "omega55__xo",
    "omega56__xo",
    "omega57__xo",
    "omega58__xo",
    "omega59__xo",
    "omega60__xo",
    "omega61__xo",
    "omega62__xo",
    "omega63__xo",
    "omega64__xo",
    "omega65__xo",
    "omega66__xo",
    "omega67__xo",
    "omega68__xo",
    "omega69__xo",
    "omega70__xo",
    "omega71__xo",
    "omega72__xo",
    "omega73__xo",
    "omega74__xo",
    "omega75__xo",
    "omega76__xo",
    "omega77__xo",
    "omega78__xo",
    "omega79__xo",
    "omega80__xo",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "u1Limitation_min",
    "u1Limitation_max",
    "u2Limitation_min",
    "u2Limitation_max",
    "u3Limitation_min",
    "u3Limitation_max",
    "u4Limitation_min",
    "u4Limitation_max",
    "u5Limitation_min",
    "u5Limitation_max",
    "u6Limitation_min",
    "u6Limitation_max",
    "u7Limitation_min",
    "u7Limitation_max",
    "u8Limitation_min",
    "u8Limitation_max",
    "u9Limitation_min",
    "u9Limitation_max",
    "u10Limitation_min",
    "u10Limitation_max",
    "u11Limitation_min",
    "u11Limitation_max",
    "u12Limitation_min",
    "u12Limitation_max",
    "u13Limitation_min",
    "u13Limitation_max",
    "u14Limitation_min",
    "u14Limitation_max",
    "u15Limitation_min",
    "u15Limitation_max",
    "u16Limitation_min",
    "u16Limitation_max",
    "u17Limitation_min",
    "u17Limitation_max",
    "u18Limitation_min",
    "u18Limitation_max",
    "u19Limitation_min",
    "u19Limitation_max",
    "u20Limitation_min",
    "u20Limitation_max",
    "xx1Limitation_min",
    "xx1Limitation_max",
    "yy1Limitation_min",
    "yy1Limitation_max",
    "xx2Limitation_min",
    "xx2Limitation_max",
    "yy2Limitation_min",
    "yy2Limitation_max",
    "xx3Limitation_min",
    "xx3Limitation_max",
    "yy3Limitation_min",
    "yy3Limitation_max",
    "xx4Limitation_min",
    "xx4Limitation_max",
    "yy4Limitation_min",
    "yy4Limitation_max",
    "xx5Limitation_min",
    "xx5Limitation_max",
    "yy5Limitation_min",
    "yy5Limitation_max",
    "xx6Limitation_min",
    "xx6Limitation_max",
    "yy6Limitation_min",
    "yy6Limitation_max",
    "xx7Limitation_min",
    "xx7Limitation_max",
    "yy7Limitation_min",
    "yy7Limitation_max",
    "xx8Limitation_min",
    "xx8Limitation_max",
    "yy8Limitation_min",
    "yy8Limitation_max",
    "xx9Limitation_min",
    "xx9Limitation_max",
    "yy9Limitation_min",
    "yy9Limitation_max",
    "xx10Limitation_min",
    "xx10Limitation_max",
    "yy10Limitation_min",
    "yy10Limitation_max",
    "xx11Limitation_min",
    "xx11Limitation_max",
    "yy11Limitation_min",
    "yy11Limitation_max",
    "xx12Limitation_min",
    "xx12Limitation_max",
    "yy12Limitation_min",
    "yy12Limitation_max",
    "xx13Limitation_min",
    "xx13Limitation_max",
    "yy13Limitation_min",
    "yy13Limitation_max",
    "xx14Limitation_min",
    "xx14Limitation_max",
    "yy14Limitation_min",
    "yy14Limitation_max",
    "xx15Limitation_min",
    "xx15Limitation_max",
    "yy15Limitation_min",
    "yy15Limitation_max",
    "xx16Limitation_min",
    "xx16Limitation_max",
    "yy16Limitation_min",
    "yy16Limitation_max",
    "xx17Limitation_min",
    "xx17Limitation_max",
    "yy17Limitation_min",
    "yy17Limitation_max",
    "xx18Limitation_min",
    "xx18Limitation_max",
    "yy18Limitation_min",
    "yy18Limitation_max",
    "xx19Limitation_min",
    "xx19Limitation_max",
    "yy19Limitation_min",
    "yy19Limitation_max",
    "xx20Limitation_min",
    "xx20Limitation_max",
    "yy20Limitation_min",
    "yy20Limitation_max",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "xy_eps0",
    "xy_eps1",
    "xy_tol0",
    "xy_tol1",
    "xy_bound",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "u1Limitation_min",
    "u1Limitation_max",
    "u2Limitation_min",
    "u2Limitation_max",
    "u3Limitation_min",
    "u3Limitation_max",
    "u4Limitation_min",
    "u4Limitation_max",
    "u5Limitation_min",
    "u5Limitation_max",
    "u6Limitation_min",
    "u6Limitation_max",
    "u7Limitation_min",
    "u7Limitation_max",
    "u8Limitation_min",
    "u8Limitation_max",
    "u9Limitation_min",
    "u9Limitation_max",
    "u10Limitation_min",
    "u10Limitation_max",
    "u11Limitation_min",
    "u11Limitation_max",
    "u12Limitation_min",
    "u12Limitation_max",
    "u13Limitation_min",
    "u13Limitation_max",
    "u14Limitation_min",
    "u14Limitation_max",
    "u15Limitation_min",
    "u15Limitation_max",
    "u16Limitation_min",
    "u16Limitation_max",
    "u17Limitation_min",
    "u17Limitation_max",
    "u18Limitation_min",
    "u18Limitation_max",
    "u19Limitation_min",
    "u19Limitation_max",
    "u20Limitation_min",
    "u20Limitation_max",
    "xx1Limitation_min",
    "xx1Limitation_max",
    "yy1Limitation_min",
    "yy1Limitation_max",
    "xx2Limitation_min",
    "xx2Limitation_max",
    "yy2Limitation_min",
    "yy2Limitation_max",
    "xx3Limitation_min",
    "xx3Limitation_max",
    "yy3Limitation_min",
    "yy3Limitation_max",
    "xx4Limitation_min",
    "xx4Limitation_max",
    "yy4Limitation_min",
    "yy4Limitation_max",
    "xx5Limitation_min",
    "xx5Limitation_max",
    "yy5Limitation_min",
    "yy5Limitation_max",
    "xx6Limitation_min",
    "xx6Limitation_max",
    "yy6Limitation_min",
    "yy6Limitation_max",
    "xx7Limitation_min",
    "xx7Limitation_max",
    "yy7Limitation_min",
    "yy7Limitation_max",
    "xx8Limitation_min",
    "xx8Limitation_max",
    "yy8Limitation_min",
    "yy8Limitation_max",
    "xx9Limitation_min",
    "xx9Limitation_max",
    "yy9Limitation_min",
    "yy9Limitation_max",
    "xx10Limitation_min",
    "xx10Limitation_max",
    "yy10Limitation_min",
    "yy10Limitation_max",
    "xx11Limitation_min",
    "xx11Limitation_max",
    "yy11Limitation_min",
    "yy11Limitation_max",
    "xx12Limitation_min",
    "xx12Limitation_max",
    "yy12Limitation_min",
    "yy12Limitation_max",
    "xx13Limitation_min",
    "xx13Limitation_max",
    "yy13Limitation_min",
    "yy13Limitation_max",
    "xx14Limitation_min",
    "xx14Limitation_max",
    "yy14Limitation_min",
    "yy14Limitation_max",
    "xx15Limitation_min",
    "xx15Limitation_max",
    "yy15Limitation_min",
    "yy15Limitation_max",
    "xx16Limitation_min",
    "xx16Limitation_max",
    "yy16Limitation_min",
    "yy16Limitation_max",
    "xx17Limitation_min",
    "xx17Limitation_max",
    "yy17Limitation_min",
    "yy17Limitation_max",
    "xx18Limitation_min",
    "xx18Limitation_max",
    "yy18Limitation_min",
    "yy18Limitation_max",
    "xx19Limitation_min",
    "xx19Limitation_max",
    "yy19Limitation_min",
    "yy19Limitation_max",
    "xx20Limitation_min",
    "xx20Limitation_max",
    "yy20Limitation_min",
    "yy20Limitation_max",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_xx1",
    "initial_yy1",
    "X1_continuity",
    "X2_continuity",
    "X3_continuity",
    "X4_continuity",
    "X5_continuity",
    "X6_continuity",
    "X7_continuity",
    "X8_continuity",
    "X9_continuity",
    "X10_continuity",
    "X11_continuity",
    "X12_continuity",
    "X13_continuity",
    "X14_continuity",
    "X15_continuity",
    "X16_continuity",
    "X17_continuity",
    "X18_continuity",
    "X19_continuity",
    "Y1_continuity",
    "Y2_continuity",
    "Y3_continuity",
    "Y4_continuity",
    "Y5_continuity",
    "Y6_continuity",
    "Y7_continuity",
    "Y8_continuity",
    "Y9_continuity",
    "Y10_continuity",
    "Y11_continuity",
    "Y12_continuity",
    "Y13_continuity",
    "Y14_continuity",
    "Y15_continuity",
    "Y16_continuity",
    "Y17_continuity",
    "Y18_continuity",
    "Y19_continuity",
    "X1_initial",
    "X2_initial",
    "X3_initial",
    "X4_initial",
    "X5_initial",
    "X6_initial",
    "X7_initial",
    "X8_initial",
    "X9_initial",
    "X10_initial",
    "X11_initial",
    "X12_initial",
    "X13_initial",
    "X14_initial",
    "X15_initial",
    "X16_initial",
    "X17_initial",
    "X18_initial",
    "X19_initial",
    "X20_initial",
    "Y1_initial",
    "Y2_initial",
    "Y3_initial",
    "Y4_initial",
    "Y5_initial",
    "Y6_initial",
    "Y7_initial",
    "Y8_initial",
    "Y9_initial",
    "Y10_initial",
    "Y11_initial",
    "Y12_initial",
    "Y13_initial",
    "Y14_initial",
    "Y15_initial",
    "Y16_initial",
    "Y17_initial",
    "Y18_initial",
    "Y19_initial",
    "Y20_initial",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  ICLOCS_ContinuousMP::ICLOCS_ContinuousMP(
    string const   & name,
    integer          n_threads,
    Console const  * console
  )
  : Discretized_Indirect_OCP( name, n_threads, console )
  // Controls
  // Constraints LT
  , u1Limitation_min("u1Limitation_min")
  , u1Limitation_max("u1Limitation_max")
  , u2Limitation_min("u2Limitation_min")
  , u2Limitation_max("u2Limitation_max")
  , u3Limitation_min("u3Limitation_min")
  , u3Limitation_max("u3Limitation_max")
  , u4Limitation_min("u4Limitation_min")
  , u4Limitation_max("u4Limitation_max")
  , u5Limitation_min("u5Limitation_min")
  , u5Limitation_max("u5Limitation_max")
  , u6Limitation_min("u6Limitation_min")
  , u6Limitation_max("u6Limitation_max")
  , u7Limitation_min("u7Limitation_min")
  , u7Limitation_max("u7Limitation_max")
  , u8Limitation_min("u8Limitation_min")
  , u8Limitation_max("u8Limitation_max")
  , u9Limitation_min("u9Limitation_min")
  , u9Limitation_max("u9Limitation_max")
  , u10Limitation_min("u10Limitation_min")
  , u10Limitation_max("u10Limitation_max")
  , u11Limitation_min("u11Limitation_min")
  , u11Limitation_max("u11Limitation_max")
  , u12Limitation_min("u12Limitation_min")
  , u12Limitation_max("u12Limitation_max")
  , u13Limitation_min("u13Limitation_min")
  , u13Limitation_max("u13Limitation_max")
  , u14Limitation_min("u14Limitation_min")
  , u14Limitation_max("u14Limitation_max")
  , u15Limitation_min("u15Limitation_min")
  , u15Limitation_max("u15Limitation_max")
  , u16Limitation_min("u16Limitation_min")
  , u16Limitation_max("u16Limitation_max")
  , u17Limitation_min("u17Limitation_min")
  , u17Limitation_max("u17Limitation_max")
  , u18Limitation_min("u18Limitation_min")
  , u18Limitation_max("u18Limitation_max")
  , u19Limitation_min("u19Limitation_min")
  , u19Limitation_max("u19Limitation_max")
  , u20Limitation_min("u20Limitation_min")
  , u20Limitation_max("u20Limitation_max")
  , xx1Limitation_min("xx1Limitation_min")
  , xx1Limitation_max("xx1Limitation_max")
  , yy1Limitation_min("yy1Limitation_min")
  , yy1Limitation_max("yy1Limitation_max")
  , xx2Limitation_min("xx2Limitation_min")
  , xx2Limitation_max("xx2Limitation_max")
  , yy2Limitation_min("yy2Limitation_min")
  , yy2Limitation_max("yy2Limitation_max")
  , xx3Limitation_min("xx3Limitation_min")
  , xx3Limitation_max("xx3Limitation_max")
  , yy3Limitation_min("yy3Limitation_min")
  , yy3Limitation_max("yy3Limitation_max")
  , xx4Limitation_min("xx4Limitation_min")
  , xx4Limitation_max("xx4Limitation_max")
  , yy4Limitation_min("yy4Limitation_min")
  , yy4Limitation_max("yy4Limitation_max")
  , xx5Limitation_min("xx5Limitation_min")
  , xx5Limitation_max("xx5Limitation_max")
  , yy5Limitation_min("yy5Limitation_min")
  , yy5Limitation_max("yy5Limitation_max")
  , xx6Limitation_min("xx6Limitation_min")
  , xx6Limitation_max("xx6Limitation_max")
  , yy6Limitation_min("yy6Limitation_min")
  , yy6Limitation_max("yy6Limitation_max")
  , xx7Limitation_min("xx7Limitation_min")
  , xx7Limitation_max("xx7Limitation_max")
  , yy7Limitation_min("yy7Limitation_min")
  , yy7Limitation_max("yy7Limitation_max")
  , xx8Limitation_min("xx8Limitation_min")
  , xx8Limitation_max("xx8Limitation_max")
  , yy8Limitation_min("yy8Limitation_min")
  , yy8Limitation_max("yy8Limitation_max")
  , xx9Limitation_min("xx9Limitation_min")
  , xx9Limitation_max("xx9Limitation_max")
  , yy9Limitation_min("yy9Limitation_min")
  , yy9Limitation_max("yy9Limitation_max")
  , xx10Limitation_min("xx10Limitation_min")
  , xx10Limitation_max("xx10Limitation_max")
  , yy10Limitation_min("yy10Limitation_min")
  , yy10Limitation_max("yy10Limitation_max")
  , xx11Limitation_min("xx11Limitation_min")
  , xx11Limitation_max("xx11Limitation_max")
  , yy11Limitation_min("yy11Limitation_min")
  , yy11Limitation_max("yy11Limitation_max")
  , xx12Limitation_min("xx12Limitation_min")
  , xx12Limitation_max("xx12Limitation_max")
  , yy12Limitation_min("yy12Limitation_min")
  , yy12Limitation_max("yy12Limitation_max")
  , xx13Limitation_min("xx13Limitation_min")
  , xx13Limitation_max("xx13Limitation_max")
  , yy13Limitation_min("yy13Limitation_min")
  , yy13Limitation_max("yy13Limitation_max")
  , xx14Limitation_min("xx14Limitation_min")
  , xx14Limitation_max("xx14Limitation_max")
  , yy14Limitation_min("yy14Limitation_min")
  , yy14Limitation_max("yy14Limitation_max")
  , xx15Limitation_min("xx15Limitation_min")
  , xx15Limitation_max("xx15Limitation_max")
  , yy15Limitation_min("yy15Limitation_min")
  , yy15Limitation_max("yy15Limitation_max")
  , xx16Limitation_min("xx16Limitation_min")
  , xx16Limitation_max("xx16Limitation_max")
  , yy16Limitation_min("yy16Limitation_min")
  , yy16Limitation_max("yy16Limitation_max")
  , xx17Limitation_min("xx17Limitation_min")
  , xx17Limitation_max("xx17Limitation_max")
  , yy17Limitation_min("yy17Limitation_min")
  , yy17Limitation_max("yy17Limitation_max")
  , xx18Limitation_min("xx18Limitation_min")
  , xx18Limitation_max("xx18Limitation_max")
  , yy18Limitation_min("yy18Limitation_min")
  , yy18Limitation_max("yy18Limitation_max")
  , xx19Limitation_min("xx19Limitation_min")
  , xx19Limitation_max("xx19Limitation_max")
  , yy19Limitation_min("yy19Limitation_min")
  , yy19Limitation_max("yy19Limitation_max")
  , xx20Limitation_min("xx20Limitation_min")
  , xx20Limitation_max("xx20Limitation_max")
  , yy20Limitation_min("yy20Limitation_min")
  , yy20Limitation_max("yy20Limitation_max")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // continuation
    this->ns_continuation_begin = 0;
    this->ns_continuation_end   = 1;
    // Initialize to NaN all the ModelPars
    std::fill_n( ModelPars, numModelPars, Utils::NaN<real_type>() );

    // Initialize string of names
    setup_names(
      numPvars,                 namesPvars,
      numXvars,                 namesXvars,
      numLvars,                 namesLvars,
      numUvars,                 namesUvars,
      numQvars,                 namesQvars,
      numPostProcess,           namesPostProcess,
      numIntegratedPostProcess, namesIntegratedPostProcess,
      numBc,                    namesBc
    );
    //m_solver = &m_solver_NewtonDumped;
    m_solver = &m_solver_Hyness;
  }

  ICLOCS_ContinuousMP::~ICLOCS_ContinuousMP() {
    // Begin: User Exit Code
    // End: User Exit Code
  }

  /* --------------------------------------------------------------------------
  //                  _       _       ____  _
  //  _   _ _ __   __| | __ _| |_ ___|  _ \| |__   __ _ ___  ___
  // | | | | '_ \ / _` |/ _` | __/ _ \ |_) | '_ \ / _` / __|/ _ \
  // | |_| | |_) | (_| | (_| | ||  __/  __/| | | | (_| \__ \  __/
  //  \__,_| .__/ \__,_|\__,_|\__\___|_|   |_| |_|\__,_|___/\___|
  //       |_|
  */
  void
  ICLOCS_ContinuousMP::update_continuation(
    integer   phase,
    real_type old_s,
    real_type s
  ) {
    int msg_level = 3;
    m_console->message(
      fmt::format(
        "\nContinuation step N.{} s={:.5}, ds={:.5}, old_s={:5}\n",
        phase+1, s, s-old_s, old_s
      ),
      msg_level
    );
    UTILS_ASSERT(
      0 <= old_s && old_s < s && s <= 1,
      "ICLOCS_ContinuousMP::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 0: continuation_step_0( s ); break;
      default:
        UTILS_ERROR(
          "ICLOCS_ContinuousMP::update_continuation( phase number={}, old_s={}, s={} )"
          " phase N.{} is not defined\n",
          phase, old_s, s, phase
        );
    }
  }

  /* --------------------------------------------------------------------------
  //           _               ____                                _
  //  ___  ___| |_ _   _ _ __ |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  // / __|/ _ \ __| | | | '_ \| |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  // \__ \  __/ |_| |_| | |_) |  __/ (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  // |___/\___|\__|\__,_| .__/|_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  //                    |_|
  // initialize parameters using associative array
  */
  void
  ICLOCS_ContinuousMP::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "ICLOCS_ContinuousMP::setup_parameters: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Parameters");

    bool allfound = true;
    for ( integer i = 0; i < numModelPars; ++i ) {
      char const * namei = namesModelPars[i];
      if ( gc.exists( namei ) ) {
        ModelPars[i] = gc(namei).get_number();
      } else {
        m_console->error( fmt::format( "Missing parameter: '{}'\n", namei ) );
        allfound = false;
      }
    }
    UTILS_ASSERT0(
      allfound, "in ICLOCS_ContinuousMP::setup not all parameters are set!\n"
    );
  }

  void
  ICLOCS_ContinuousMP::setup_parameters( real_type const Pars[] ) {
    std::copy( Pars, Pars + numModelPars, ModelPars );
  }

  /* --------------------------------------------------------------------------
  //            _                ____ _
  //   ___  ___| |_ _   _ _ __  / ___| | __ _ ___ ___  ___  ___
  //  / __|/ _ \ __| | | | '_ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  \__ \  __/ |_| |_| | |_) | |___| | (_| \__ \__ \  __/\__ \
  //  |___/\___|\__|\__,_| .__/ \____|_|\__,_|___/___/\___||___/
  //                     |_|
  */
  void
  ICLOCS_ContinuousMP::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "ICLOCS_ContinuousMP::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("u1Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u1Limitation_min''\n"
    );
    u1Limitation_min.setup( gc("u1Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u1Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u1Limitation_max''\n"
    );
    u1Limitation_max.setup( gc("u1Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u2Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u2Limitation_min''\n"
    );
    u2Limitation_min.setup( gc("u2Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u2Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u2Limitation_max''\n"
    );
    u2Limitation_max.setup( gc("u2Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u3Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u3Limitation_min''\n"
    );
    u3Limitation_min.setup( gc("u3Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u3Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u3Limitation_max''\n"
    );
    u3Limitation_max.setup( gc("u3Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u4Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u4Limitation_min''\n"
    );
    u4Limitation_min.setup( gc("u4Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u4Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u4Limitation_max''\n"
    );
    u4Limitation_max.setup( gc("u4Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u5Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u5Limitation_min''\n"
    );
    u5Limitation_min.setup( gc("u5Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u5Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u5Limitation_max''\n"
    );
    u5Limitation_max.setup( gc("u5Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u6Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u6Limitation_min''\n"
    );
    u6Limitation_min.setup( gc("u6Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u6Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u6Limitation_max''\n"
    );
    u6Limitation_max.setup( gc("u6Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u7Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u7Limitation_min''\n"
    );
    u7Limitation_min.setup( gc("u7Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u7Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u7Limitation_max''\n"
    );
    u7Limitation_max.setup( gc("u7Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u8Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u8Limitation_min''\n"
    );
    u8Limitation_min.setup( gc("u8Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u8Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u8Limitation_max''\n"
    );
    u8Limitation_max.setup( gc("u8Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u9Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u9Limitation_min''\n"
    );
    u9Limitation_min.setup( gc("u9Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u9Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u9Limitation_max''\n"
    );
    u9Limitation_max.setup( gc("u9Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u10Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u10Limitation_min''\n"
    );
    u10Limitation_min.setup( gc("u10Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u10Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u10Limitation_max''\n"
    );
    u10Limitation_max.setup( gc("u10Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u11Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u11Limitation_min''\n"
    );
    u11Limitation_min.setup( gc("u11Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u11Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u11Limitation_max''\n"
    );
    u11Limitation_max.setup( gc("u11Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u12Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u12Limitation_min''\n"
    );
    u12Limitation_min.setup( gc("u12Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u12Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u12Limitation_max''\n"
    );
    u12Limitation_max.setup( gc("u12Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u13Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u13Limitation_min''\n"
    );
    u13Limitation_min.setup( gc("u13Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u13Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u13Limitation_max''\n"
    );
    u13Limitation_max.setup( gc("u13Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u14Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u14Limitation_min''\n"
    );
    u14Limitation_min.setup( gc("u14Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u14Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u14Limitation_max''\n"
    );
    u14Limitation_max.setup( gc("u14Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u15Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u15Limitation_min''\n"
    );
    u15Limitation_min.setup( gc("u15Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u15Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u15Limitation_max''\n"
    );
    u15Limitation_max.setup( gc("u15Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u16Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u16Limitation_min''\n"
    );
    u16Limitation_min.setup( gc("u16Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u16Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u16Limitation_max''\n"
    );
    u16Limitation_max.setup( gc("u16Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u17Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u17Limitation_min''\n"
    );
    u17Limitation_min.setup( gc("u17Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u17Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u17Limitation_max''\n"
    );
    u17Limitation_max.setup( gc("u17Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u18Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u18Limitation_min''\n"
    );
    u18Limitation_min.setup( gc("u18Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u18Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u18Limitation_max''\n"
    );
    u18Limitation_max.setup( gc("u18Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u19Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u19Limitation_min''\n"
    );
    u19Limitation_min.setup( gc("u19Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u19Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u19Limitation_max''\n"
    );
    u19Limitation_max.setup( gc("u19Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("u20Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u20Limitation_min''\n"
    );
    u20Limitation_min.setup( gc("u20Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("u20Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u20Limitation_max''\n"
    );
    u20Limitation_max.setup( gc("u20Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx1Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx1Limitation_min''\n"
    );
    xx1Limitation_min.setup( gc("xx1Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx1Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx1Limitation_max''\n"
    );
    xx1Limitation_max.setup( gc("xx1Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy1Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy1Limitation_min''\n"
    );
    yy1Limitation_min.setup( gc("yy1Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy1Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy1Limitation_max''\n"
    );
    yy1Limitation_max.setup( gc("yy1Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx2Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx2Limitation_min''\n"
    );
    xx2Limitation_min.setup( gc("xx2Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx2Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx2Limitation_max''\n"
    );
    xx2Limitation_max.setup( gc("xx2Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy2Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy2Limitation_min''\n"
    );
    yy2Limitation_min.setup( gc("yy2Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy2Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy2Limitation_max''\n"
    );
    yy2Limitation_max.setup( gc("yy2Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx3Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx3Limitation_min''\n"
    );
    xx3Limitation_min.setup( gc("xx3Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx3Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx3Limitation_max''\n"
    );
    xx3Limitation_max.setup( gc("xx3Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy3Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy3Limitation_min''\n"
    );
    yy3Limitation_min.setup( gc("yy3Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy3Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy3Limitation_max''\n"
    );
    yy3Limitation_max.setup( gc("yy3Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx4Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx4Limitation_min''\n"
    );
    xx4Limitation_min.setup( gc("xx4Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx4Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx4Limitation_max''\n"
    );
    xx4Limitation_max.setup( gc("xx4Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy4Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy4Limitation_min''\n"
    );
    yy4Limitation_min.setup( gc("yy4Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy4Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy4Limitation_max''\n"
    );
    yy4Limitation_max.setup( gc("yy4Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx5Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx5Limitation_min''\n"
    );
    xx5Limitation_min.setup( gc("xx5Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx5Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx5Limitation_max''\n"
    );
    xx5Limitation_max.setup( gc("xx5Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy5Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy5Limitation_min''\n"
    );
    yy5Limitation_min.setup( gc("yy5Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy5Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy5Limitation_max''\n"
    );
    yy5Limitation_max.setup( gc("yy5Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx6Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx6Limitation_min''\n"
    );
    xx6Limitation_min.setup( gc("xx6Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx6Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx6Limitation_max''\n"
    );
    xx6Limitation_max.setup( gc("xx6Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy6Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy6Limitation_min''\n"
    );
    yy6Limitation_min.setup( gc("yy6Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy6Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy6Limitation_max''\n"
    );
    yy6Limitation_max.setup( gc("yy6Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx7Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx7Limitation_min''\n"
    );
    xx7Limitation_min.setup( gc("xx7Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx7Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx7Limitation_max''\n"
    );
    xx7Limitation_max.setup( gc("xx7Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy7Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy7Limitation_min''\n"
    );
    yy7Limitation_min.setup( gc("yy7Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy7Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy7Limitation_max''\n"
    );
    yy7Limitation_max.setup( gc("yy7Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx8Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx8Limitation_min''\n"
    );
    xx8Limitation_min.setup( gc("xx8Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx8Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx8Limitation_max''\n"
    );
    xx8Limitation_max.setup( gc("xx8Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy8Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy8Limitation_min''\n"
    );
    yy8Limitation_min.setup( gc("yy8Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy8Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy8Limitation_max''\n"
    );
    yy8Limitation_max.setup( gc("yy8Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx9Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx9Limitation_min''\n"
    );
    xx9Limitation_min.setup( gc("xx9Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx9Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx9Limitation_max''\n"
    );
    xx9Limitation_max.setup( gc("xx9Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy9Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy9Limitation_min''\n"
    );
    yy9Limitation_min.setup( gc("yy9Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy9Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy9Limitation_max''\n"
    );
    yy9Limitation_max.setup( gc("yy9Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx10Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx10Limitation_min''\n"
    );
    xx10Limitation_min.setup( gc("xx10Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx10Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx10Limitation_max''\n"
    );
    xx10Limitation_max.setup( gc("xx10Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy10Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy10Limitation_min''\n"
    );
    yy10Limitation_min.setup( gc("yy10Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy10Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy10Limitation_max''\n"
    );
    yy10Limitation_max.setup( gc("yy10Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx11Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx11Limitation_min''\n"
    );
    xx11Limitation_min.setup( gc("xx11Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx11Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx11Limitation_max''\n"
    );
    xx11Limitation_max.setup( gc("xx11Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy11Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy11Limitation_min''\n"
    );
    yy11Limitation_min.setup( gc("yy11Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy11Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy11Limitation_max''\n"
    );
    yy11Limitation_max.setup( gc("yy11Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx12Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx12Limitation_min''\n"
    );
    xx12Limitation_min.setup( gc("xx12Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx12Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx12Limitation_max''\n"
    );
    xx12Limitation_max.setup( gc("xx12Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy12Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy12Limitation_min''\n"
    );
    yy12Limitation_min.setup( gc("yy12Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy12Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy12Limitation_max''\n"
    );
    yy12Limitation_max.setup( gc("yy12Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx13Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx13Limitation_min''\n"
    );
    xx13Limitation_min.setup( gc("xx13Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx13Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx13Limitation_max''\n"
    );
    xx13Limitation_max.setup( gc("xx13Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy13Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy13Limitation_min''\n"
    );
    yy13Limitation_min.setup( gc("yy13Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy13Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy13Limitation_max''\n"
    );
    yy13Limitation_max.setup( gc("yy13Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx14Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx14Limitation_min''\n"
    );
    xx14Limitation_min.setup( gc("xx14Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx14Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx14Limitation_max''\n"
    );
    xx14Limitation_max.setup( gc("xx14Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy14Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy14Limitation_min''\n"
    );
    yy14Limitation_min.setup( gc("yy14Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy14Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy14Limitation_max''\n"
    );
    yy14Limitation_max.setup( gc("yy14Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx15Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx15Limitation_min''\n"
    );
    xx15Limitation_min.setup( gc("xx15Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx15Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx15Limitation_max''\n"
    );
    xx15Limitation_max.setup( gc("xx15Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy15Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy15Limitation_min''\n"
    );
    yy15Limitation_min.setup( gc("yy15Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy15Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy15Limitation_max''\n"
    );
    yy15Limitation_max.setup( gc("yy15Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx16Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx16Limitation_min''\n"
    );
    xx16Limitation_min.setup( gc("xx16Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx16Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx16Limitation_max''\n"
    );
    xx16Limitation_max.setup( gc("xx16Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy16Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy16Limitation_min''\n"
    );
    yy16Limitation_min.setup( gc("yy16Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy16Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy16Limitation_max''\n"
    );
    yy16Limitation_max.setup( gc("yy16Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx17Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx17Limitation_min''\n"
    );
    xx17Limitation_min.setup( gc("xx17Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx17Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx17Limitation_max''\n"
    );
    xx17Limitation_max.setup( gc("xx17Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy17Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy17Limitation_min''\n"
    );
    yy17Limitation_min.setup( gc("yy17Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy17Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy17Limitation_max''\n"
    );
    yy17Limitation_max.setup( gc("yy17Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx18Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx18Limitation_min''\n"
    );
    xx18Limitation_min.setup( gc("xx18Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx18Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx18Limitation_max''\n"
    );
    xx18Limitation_max.setup( gc("xx18Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy18Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy18Limitation_min''\n"
    );
    yy18Limitation_min.setup( gc("yy18Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy18Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy18Limitation_max''\n"
    );
    yy18Limitation_max.setup( gc("yy18Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx19Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx19Limitation_min''\n"
    );
    xx19Limitation_min.setup( gc("xx19Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx19Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx19Limitation_max''\n"
    );
    xx19Limitation_max.setup( gc("xx19Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy19Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy19Limitation_min''\n"
    );
    yy19Limitation_min.setup( gc("yy19Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy19Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy19Limitation_max''\n"
    );
    yy19Limitation_max.setup( gc("yy19Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("xx20Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx20Limitation_min''\n"
    );
    xx20Limitation_min.setup( gc("xx20Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("xx20Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx20Limitation_max''\n"
    );
    xx20Limitation_max.setup( gc("xx20Limitation_max") );

    UTILS_ASSERT0(
      gc.exists("yy20Limitation_min"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy20Limitation_min''\n"
    );
    yy20Limitation_min.setup( gc("yy20Limitation_min") );

    UTILS_ASSERT0(
      gc.exists("yy20Limitation_max"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy20Limitation_max''\n"
    );
    yy20Limitation_max.setup( gc("yy20Limitation_max") );

  }

  /* --------------------------------------------------------------------------
  //           _               _   _                ____ _
  //  ___  ___| |_ _   _ _ __ | | | |___  ___ _ __ / ___| | __ _ ___ ___  ___  ___
  // / __|/ _ \ __| | | | '_ \| | | / __|/ _ \ '__| |   | |/ _` / __/ __|/ _ \/ __|
  // \__ \  __/ |_| |_| | |_) | |_| \__ \  __/ |  | |___| | (_| \__ \__ \  __/\__ \
  // |___/\___|\__|\__,_| .__/ \___/|___/\___|_|   \____|_|\__,_|___/___/\___||___/
  //                    |_|
  */
  void
  ICLOCS_ContinuousMP::setup_user_classes( GenericContainer const & gc ) {
  }

  /* --------------------------------------------------------------------------
  //           _             _   _
  //   ___ ___| |_ _  _ _ __| | | |___ ___ _ _
  //  (_-</ -_)  _| || | '_ \ |_| (_-</ -_) '_|
  //  /__/\___|\__|\_,_| .__/\___//__/\___|_|
  //                   |_|
  //   __  __                        _ ___             _   _
  //  |  \/  |__ _ _ __ _ __  ___ __| | __|  _ _ _  __| |_(_)___ _ _  ___
  //  | |\/| / _` | '_ \ '_ \/ -_) _` | _| || | ' \/ _|  _| / _ \ ' \(_-<
  //  |_|  |_\__,_| .__/ .__/\___\__,_|_| \_,_|_||_\__|\__|_\___/_||_/__/
  //              |_|  |_|
  */
  void
  ICLOCS_ContinuousMP::setup_user_mapped_functions( GenericContainer const & gc_data ) {
  }
  /* --------------------------------------------------------------------------
  //            _                ____            _             _
  //   ___  ___| |_ _   _ _ __  / ___|___  _ __ | |_ _ __ ___ | |___
  //  / __|/ _ \ __| | | | '_ \| |   / _ \| '_ \| __| '__/ _ \| / __|
  //  \__ \  __/ |_| |_| | |_) | |__| (_) | | | | |_| | | (_) | \__ \
  //  |___/\___|\__|\__,_| .__/ \____\___/|_| |_|\__|_|  \___/|_|___/
  //                     |_|
  */
  void
  ICLOCS_ContinuousMP::setup_controls( GenericContainer const & gc_data ) {
    // no Control penalties, setup only iterative solver
    this->setup_control_solver( gc_data );
  }

  /* --------------------------------------------------------------------------
  //            _               ____       _       _
  //   ___  ___| |_ _   _ _ __ |  _ \ ___ (_)_ __ | |_ ___ _ __ ___
  //  / __|/ _ \ __| | | | '_ \| |_) / _ \| | '_ \| __/ _ \ '__/ __|
  //  \__ \  __/ |_| |_| | |_) |  __/ (_) | | | | | ||  __/ |  \__ \
  //  |___/\___|\__|\__,_| .__/|_|   \___/|_|_| |_|\__\___|_|  |___/
  //                     |_|
  */
  void
  ICLOCS_ContinuousMP::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "ICLOCS_ContinuousMP::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pMesh"),
      "in ICLOCS_ContinuousMP::setup_pointers(gc) cant find key `pMesh' in gc\n"
    );
    pMesh = gc("pMesh").get_pointer<MeshStd*>();
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  ICLOCS_ContinuousMP::info_classes() const {
    int msg_level = 3;
    ostringstream mstr;

    m_console->message("\nConstraints LT\n",msg_level);
    mstr.str("");
    u1Limitation_min.info(mstr);
    u1Limitation_max.info(mstr);
    u2Limitation_min.info(mstr);
    u2Limitation_max.info(mstr);
    u3Limitation_min.info(mstr);
    u3Limitation_max.info(mstr);
    u4Limitation_min.info(mstr);
    u4Limitation_max.info(mstr);
    u5Limitation_min.info(mstr);
    u5Limitation_max.info(mstr);
    u6Limitation_min.info(mstr);
    u6Limitation_max.info(mstr);
    u7Limitation_min.info(mstr);
    u7Limitation_max.info(mstr);
    u8Limitation_min.info(mstr);
    u8Limitation_max.info(mstr);
    u9Limitation_min.info(mstr);
    u9Limitation_max.info(mstr);
    u10Limitation_min.info(mstr);
    u10Limitation_max.info(mstr);
    u11Limitation_min.info(mstr);
    u11Limitation_max.info(mstr);
    u12Limitation_min.info(mstr);
    u12Limitation_max.info(mstr);
    u13Limitation_min.info(mstr);
    u13Limitation_max.info(mstr);
    u14Limitation_min.info(mstr);
    u14Limitation_max.info(mstr);
    u15Limitation_min.info(mstr);
    u15Limitation_max.info(mstr);
    u16Limitation_min.info(mstr);
    u16Limitation_max.info(mstr);
    u17Limitation_min.info(mstr);
    u17Limitation_max.info(mstr);
    u18Limitation_min.info(mstr);
    u18Limitation_max.info(mstr);
    u19Limitation_min.info(mstr);
    u19Limitation_max.info(mstr);
    u20Limitation_min.info(mstr);
    u20Limitation_max.info(mstr);
    xx1Limitation_min.info(mstr);
    xx1Limitation_max.info(mstr);
    yy1Limitation_min.info(mstr);
    yy1Limitation_max.info(mstr);
    xx2Limitation_min.info(mstr);
    xx2Limitation_max.info(mstr);
    yy2Limitation_min.info(mstr);
    yy2Limitation_max.info(mstr);
    xx3Limitation_min.info(mstr);
    xx3Limitation_max.info(mstr);
    yy3Limitation_min.info(mstr);
    yy3Limitation_max.info(mstr);
    xx4Limitation_min.info(mstr);
    xx4Limitation_max.info(mstr);
    yy4Limitation_min.info(mstr);
    yy4Limitation_max.info(mstr);
    xx5Limitation_min.info(mstr);
    xx5Limitation_max.info(mstr);
    yy5Limitation_min.info(mstr);
    yy5Limitation_max.info(mstr);
    xx6Limitation_min.info(mstr);
    xx6Limitation_max.info(mstr);
    yy6Limitation_min.info(mstr);
    yy6Limitation_max.info(mstr);
    xx7Limitation_min.info(mstr);
    xx7Limitation_max.info(mstr);
    yy7Limitation_min.info(mstr);
    yy7Limitation_max.info(mstr);
    xx8Limitation_min.info(mstr);
    xx8Limitation_max.info(mstr);
    yy8Limitation_min.info(mstr);
    yy8Limitation_max.info(mstr);
    xx9Limitation_min.info(mstr);
    xx9Limitation_max.info(mstr);
    yy9Limitation_min.info(mstr);
    yy9Limitation_max.info(mstr);
    xx10Limitation_min.info(mstr);
    xx10Limitation_max.info(mstr);
    yy10Limitation_min.info(mstr);
    yy10Limitation_max.info(mstr);
    xx11Limitation_min.info(mstr);
    xx11Limitation_max.info(mstr);
    yy11Limitation_min.info(mstr);
    yy11Limitation_max.info(mstr);
    xx12Limitation_min.info(mstr);
    xx12Limitation_max.info(mstr);
    yy12Limitation_min.info(mstr);
    yy12Limitation_max.info(mstr);
    xx13Limitation_min.info(mstr);
    xx13Limitation_max.info(mstr);
    yy13Limitation_min.info(mstr);
    yy13Limitation_max.info(mstr);
    xx14Limitation_min.info(mstr);
    xx14Limitation_max.info(mstr);
    yy14Limitation_min.info(mstr);
    yy14Limitation_max.info(mstr);
    xx15Limitation_min.info(mstr);
    xx15Limitation_max.info(mstr);
    yy15Limitation_min.info(mstr);
    yy15Limitation_max.info(mstr);
    xx16Limitation_min.info(mstr);
    xx16Limitation_max.info(mstr);
    yy16Limitation_min.info(mstr);
    yy16Limitation_max.info(mstr);
    xx17Limitation_min.info(mstr);
    xx17Limitation_max.info(mstr);
    yy17Limitation_min.info(mstr);
    yy17Limitation_max.info(mstr);
    xx18Limitation_min.info(mstr);
    xx18Limitation_max.info(mstr);
    yy18Limitation_min.info(mstr);
    yy18Limitation_max.info(mstr);
    xx19Limitation_min.info(mstr);
    xx19Limitation_max.info(mstr);
    yy19Limitation_min.info(mstr);
    yy19Limitation_max.info(mstr);
    xx20Limitation_min.info(mstr);
    xx20Limitation_max.info(mstr);
    yy20Limitation_min.info(mstr);
    yy20Limitation_max.info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    mstr.str("");
    mstr << "\nUser function `pMesh`\n";
    pMesh->info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nModel Parameters\n",msg_level);
    for ( integer i = 0; i < numModelPars; ++i ) {
      m_console->message(
        fmt::format("{:.>40} = {}\n",namesModelPars[i], ModelPars[i]),
        msg_level
      );
    }

  }

  /* --------------------------------------------------------------------------
  //            _
  //   ___  ___| |_ _   _ _ __
  //  / __|/ _ \ __| | | | '_ \
  //  \__ \  __/ |_| |_| | |_) |
  //  |___/\___|\__|\__,_| .__/
  //                     |_|
  */
  void
  ICLOCS_ContinuousMP::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("ICLOCS_ContinuousMP::setup, Debug");

    this->setup_parameters( gc );
    this->setup_classes( gc );
    this->setup_user_mapped_functions( gc );
    this->setup_user_classes( gc );
    this->setup_pointers( gc );
    this->setup_BC( gc );
    this->setup_controls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pMesh, gc );

    // Begin: User Setup Code
    // End: User Setup Code

    this->info_BC();
    this->info_classes();
    // this->info(); stampato dopo GUESS
  }

  /* --------------------------------------------------------------------------
  //              _
  //    __ _  ___| |_     _ __   __ _ _ __ ___   ___  ___
  //   / _` |/ _ \ __|   | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | (_| |  __/ |_    | | | | (_| | | | | | |  __/\__ \
  //   \__, |\___|\__|___|_| |_|\__,_|_| |_| |_|\___||___/
  //   |___/        |_____|
  */
  void
  ICLOCS_ContinuousMP::get_names( GenericContainer & out ) const {
    vec_string_type & X_names = out["state_names"].set_vec_string();
    for ( integer i = 0; i < numXvars; ++i ) X_names.push_back(namesXvars[i]);

    vec_string_type & LM_names = out["lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numLvars; ++i ) LM_names.push_back(namesLvars[i]);

    vec_string_type & U_names = out["control_names"].set_vec_string();
    for ( integer i = 0; i < numUvars; ++i ) U_names.push_back(namesUvars[i]);

    vec_string_type & Q_names = out["mesh_variable_names"].set_vec_string();
    for ( integer i = 0; i < numQvars; ++i ) Q_names.push_back(namesQvars[i]);

    vec_string_type & P_names = out["parameter_names"].set_vec_string();
    for ( integer i = 0; i < numPvars; ++i ) P_names.push_back(namesPvars[i]);

    vec_string_type & OMEGA_names = out["bc_lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numOMEGAvars; ++i ) OMEGA_names.push_back(namesOMEGAvars[i]);

    vec_string_type & PP_names = out["post_processing_names"].set_vec_string();
    for ( integer i = 0; i < numPostProcess; ++i ) PP_names.push_back(namesPostProcess[i]);

    for ( integer i = 0; i < numIntegratedPostProcess; ++i )
      PP_names.push_back(namesIntegratedPostProcess[i]);

    vec_string_type & model_names = out["model_names"].set_vec_string();
    for ( integer i = 0; i < numModelPars; ++i )
      model_names.push_back(namesModelPars[i]);
  }

  // save model parameters
  void
  ICLOCS_ContinuousMP::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: ICLOCS_ContinuousMP.cc
