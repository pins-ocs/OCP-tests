/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_Guess.cc                           |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunused-macros"
#elif defined(__llvm__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-macros"
#elif defined(_MSC_VER)
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_yy20Limitation_max_DD(__t1) yy20Limitation_max.DD( __t1)
#define ALIAS_yy20Limitation_max_D(__t1) yy20Limitation_max.D( __t1)
#define ALIAS_yy20Limitation_min_DD(__t1) yy20Limitation_min.DD( __t1)
#define ALIAS_yy20Limitation_min_D(__t1) yy20Limitation_min.D( __t1)
#define ALIAS_xx20Limitation_max_DD(__t1) xx20Limitation_max.DD( __t1)
#define ALIAS_xx20Limitation_max_D(__t1) xx20Limitation_max.D( __t1)
#define ALIAS_xx20Limitation_min_DD(__t1) xx20Limitation_min.DD( __t1)
#define ALIAS_xx20Limitation_min_D(__t1) xx20Limitation_min.D( __t1)
#define ALIAS_yy19Limitation_max_DD(__t1) yy19Limitation_max.DD( __t1)
#define ALIAS_yy19Limitation_max_D(__t1) yy19Limitation_max.D( __t1)
#define ALIAS_yy19Limitation_min_DD(__t1) yy19Limitation_min.DD( __t1)
#define ALIAS_yy19Limitation_min_D(__t1) yy19Limitation_min.D( __t1)
#define ALIAS_xx19Limitation_max_DD(__t1) xx19Limitation_max.DD( __t1)
#define ALIAS_xx19Limitation_max_D(__t1) xx19Limitation_max.D( __t1)
#define ALIAS_xx19Limitation_min_DD(__t1) xx19Limitation_min.DD( __t1)
#define ALIAS_xx19Limitation_min_D(__t1) xx19Limitation_min.D( __t1)
#define ALIAS_yy18Limitation_max_DD(__t1) yy18Limitation_max.DD( __t1)
#define ALIAS_yy18Limitation_max_D(__t1) yy18Limitation_max.D( __t1)
#define ALIAS_yy18Limitation_min_DD(__t1) yy18Limitation_min.DD( __t1)
#define ALIAS_yy18Limitation_min_D(__t1) yy18Limitation_min.D( __t1)
#define ALIAS_xx18Limitation_max_DD(__t1) xx18Limitation_max.DD( __t1)
#define ALIAS_xx18Limitation_max_D(__t1) xx18Limitation_max.D( __t1)
#define ALIAS_xx18Limitation_min_DD(__t1) xx18Limitation_min.DD( __t1)
#define ALIAS_xx18Limitation_min_D(__t1) xx18Limitation_min.D( __t1)
#define ALIAS_yy17Limitation_max_DD(__t1) yy17Limitation_max.DD( __t1)
#define ALIAS_yy17Limitation_max_D(__t1) yy17Limitation_max.D( __t1)
#define ALIAS_yy17Limitation_min_DD(__t1) yy17Limitation_min.DD( __t1)
#define ALIAS_yy17Limitation_min_D(__t1) yy17Limitation_min.D( __t1)
#define ALIAS_xx17Limitation_max_DD(__t1) xx17Limitation_max.DD( __t1)
#define ALIAS_xx17Limitation_max_D(__t1) xx17Limitation_max.D( __t1)
#define ALIAS_xx17Limitation_min_DD(__t1) xx17Limitation_min.DD( __t1)
#define ALIAS_xx17Limitation_min_D(__t1) xx17Limitation_min.D( __t1)
#define ALIAS_yy16Limitation_max_DD(__t1) yy16Limitation_max.DD( __t1)
#define ALIAS_yy16Limitation_max_D(__t1) yy16Limitation_max.D( __t1)
#define ALIAS_yy16Limitation_min_DD(__t1) yy16Limitation_min.DD( __t1)
#define ALIAS_yy16Limitation_min_D(__t1) yy16Limitation_min.D( __t1)
#define ALIAS_xx16Limitation_max_DD(__t1) xx16Limitation_max.DD( __t1)
#define ALIAS_xx16Limitation_max_D(__t1) xx16Limitation_max.D( __t1)
#define ALIAS_xx16Limitation_min_DD(__t1) xx16Limitation_min.DD( __t1)
#define ALIAS_xx16Limitation_min_D(__t1) xx16Limitation_min.D( __t1)
#define ALIAS_yy15Limitation_max_DD(__t1) yy15Limitation_max.DD( __t1)
#define ALIAS_yy15Limitation_max_D(__t1) yy15Limitation_max.D( __t1)
#define ALIAS_yy15Limitation_min_DD(__t1) yy15Limitation_min.DD( __t1)
#define ALIAS_yy15Limitation_min_D(__t1) yy15Limitation_min.D( __t1)
#define ALIAS_xx15Limitation_max_DD(__t1) xx15Limitation_max.DD( __t1)
#define ALIAS_xx15Limitation_max_D(__t1) xx15Limitation_max.D( __t1)
#define ALIAS_xx15Limitation_min_DD(__t1) xx15Limitation_min.DD( __t1)
#define ALIAS_xx15Limitation_min_D(__t1) xx15Limitation_min.D( __t1)
#define ALIAS_yy14Limitation_max_DD(__t1) yy14Limitation_max.DD( __t1)
#define ALIAS_yy14Limitation_max_D(__t1) yy14Limitation_max.D( __t1)
#define ALIAS_yy14Limitation_min_DD(__t1) yy14Limitation_min.DD( __t1)
#define ALIAS_yy14Limitation_min_D(__t1) yy14Limitation_min.D( __t1)
#define ALIAS_xx14Limitation_max_DD(__t1) xx14Limitation_max.DD( __t1)
#define ALIAS_xx14Limitation_max_D(__t1) xx14Limitation_max.D( __t1)
#define ALIAS_xx14Limitation_min_DD(__t1) xx14Limitation_min.DD( __t1)
#define ALIAS_xx14Limitation_min_D(__t1) xx14Limitation_min.D( __t1)
#define ALIAS_yy13Limitation_max_DD(__t1) yy13Limitation_max.DD( __t1)
#define ALIAS_yy13Limitation_max_D(__t1) yy13Limitation_max.D( __t1)
#define ALIAS_yy13Limitation_min_DD(__t1) yy13Limitation_min.DD( __t1)
#define ALIAS_yy13Limitation_min_D(__t1) yy13Limitation_min.D( __t1)
#define ALIAS_xx13Limitation_max_DD(__t1) xx13Limitation_max.DD( __t1)
#define ALIAS_xx13Limitation_max_D(__t1) xx13Limitation_max.D( __t1)
#define ALIAS_xx13Limitation_min_DD(__t1) xx13Limitation_min.DD( __t1)
#define ALIAS_xx13Limitation_min_D(__t1) xx13Limitation_min.D( __t1)
#define ALIAS_yy12Limitation_max_DD(__t1) yy12Limitation_max.DD( __t1)
#define ALIAS_yy12Limitation_max_D(__t1) yy12Limitation_max.D( __t1)
#define ALIAS_yy12Limitation_min_DD(__t1) yy12Limitation_min.DD( __t1)
#define ALIAS_yy12Limitation_min_D(__t1) yy12Limitation_min.D( __t1)
#define ALIAS_xx12Limitation_max_DD(__t1) xx12Limitation_max.DD( __t1)
#define ALIAS_xx12Limitation_max_D(__t1) xx12Limitation_max.D( __t1)
#define ALIAS_xx12Limitation_min_DD(__t1) xx12Limitation_min.DD( __t1)
#define ALIAS_xx12Limitation_min_D(__t1) xx12Limitation_min.D( __t1)
#define ALIAS_yy11Limitation_max_DD(__t1) yy11Limitation_max.DD( __t1)
#define ALIAS_yy11Limitation_max_D(__t1) yy11Limitation_max.D( __t1)
#define ALIAS_yy11Limitation_min_DD(__t1) yy11Limitation_min.DD( __t1)
#define ALIAS_yy11Limitation_min_D(__t1) yy11Limitation_min.D( __t1)
#define ALIAS_xx11Limitation_max_DD(__t1) xx11Limitation_max.DD( __t1)
#define ALIAS_xx11Limitation_max_D(__t1) xx11Limitation_max.D( __t1)
#define ALIAS_xx11Limitation_min_DD(__t1) xx11Limitation_min.DD( __t1)
#define ALIAS_xx11Limitation_min_D(__t1) xx11Limitation_min.D( __t1)
#define ALIAS_yy10Limitation_max_DD(__t1) yy10Limitation_max.DD( __t1)
#define ALIAS_yy10Limitation_max_D(__t1) yy10Limitation_max.D( __t1)
#define ALIAS_yy10Limitation_min_DD(__t1) yy10Limitation_min.DD( __t1)
#define ALIAS_yy10Limitation_min_D(__t1) yy10Limitation_min.D( __t1)
#define ALIAS_xx10Limitation_max_DD(__t1) xx10Limitation_max.DD( __t1)
#define ALIAS_xx10Limitation_max_D(__t1) xx10Limitation_max.D( __t1)
#define ALIAS_xx10Limitation_min_DD(__t1) xx10Limitation_min.DD( __t1)
#define ALIAS_xx10Limitation_min_D(__t1) xx10Limitation_min.D( __t1)
#define ALIAS_yy9Limitation_max_DD(__t1) yy9Limitation_max.DD( __t1)
#define ALIAS_yy9Limitation_max_D(__t1) yy9Limitation_max.D( __t1)
#define ALIAS_yy9Limitation_min_DD(__t1) yy9Limitation_min.DD( __t1)
#define ALIAS_yy9Limitation_min_D(__t1) yy9Limitation_min.D( __t1)
#define ALIAS_xx9Limitation_max_DD(__t1) xx9Limitation_max.DD( __t1)
#define ALIAS_xx9Limitation_max_D(__t1) xx9Limitation_max.D( __t1)
#define ALIAS_xx9Limitation_min_DD(__t1) xx9Limitation_min.DD( __t1)
#define ALIAS_xx9Limitation_min_D(__t1) xx9Limitation_min.D( __t1)
#define ALIAS_yy8Limitation_max_DD(__t1) yy8Limitation_max.DD( __t1)
#define ALIAS_yy8Limitation_max_D(__t1) yy8Limitation_max.D( __t1)
#define ALIAS_yy8Limitation_min_DD(__t1) yy8Limitation_min.DD( __t1)
#define ALIAS_yy8Limitation_min_D(__t1) yy8Limitation_min.D( __t1)
#define ALIAS_xx8Limitation_max_DD(__t1) xx8Limitation_max.DD( __t1)
#define ALIAS_xx8Limitation_max_D(__t1) xx8Limitation_max.D( __t1)
#define ALIAS_xx8Limitation_min_DD(__t1) xx8Limitation_min.DD( __t1)
#define ALIAS_xx8Limitation_min_D(__t1) xx8Limitation_min.D( __t1)
#define ALIAS_yy7Limitation_max_DD(__t1) yy7Limitation_max.DD( __t1)
#define ALIAS_yy7Limitation_max_D(__t1) yy7Limitation_max.D( __t1)
#define ALIAS_yy7Limitation_min_DD(__t1) yy7Limitation_min.DD( __t1)
#define ALIAS_yy7Limitation_min_D(__t1) yy7Limitation_min.D( __t1)
#define ALIAS_xx7Limitation_max_DD(__t1) xx7Limitation_max.DD( __t1)
#define ALIAS_xx7Limitation_max_D(__t1) xx7Limitation_max.D( __t1)
#define ALIAS_xx7Limitation_min_DD(__t1) xx7Limitation_min.DD( __t1)
#define ALIAS_xx7Limitation_min_D(__t1) xx7Limitation_min.D( __t1)
#define ALIAS_yy6Limitation_max_DD(__t1) yy6Limitation_max.DD( __t1)
#define ALIAS_yy6Limitation_max_D(__t1) yy6Limitation_max.D( __t1)
#define ALIAS_yy6Limitation_min_DD(__t1) yy6Limitation_min.DD( __t1)
#define ALIAS_yy6Limitation_min_D(__t1) yy6Limitation_min.D( __t1)
#define ALIAS_xx6Limitation_max_DD(__t1) xx6Limitation_max.DD( __t1)
#define ALIAS_xx6Limitation_max_D(__t1) xx6Limitation_max.D( __t1)
#define ALIAS_xx6Limitation_min_DD(__t1) xx6Limitation_min.DD( __t1)
#define ALIAS_xx6Limitation_min_D(__t1) xx6Limitation_min.D( __t1)
#define ALIAS_yy5Limitation_max_DD(__t1) yy5Limitation_max.DD( __t1)
#define ALIAS_yy5Limitation_max_D(__t1) yy5Limitation_max.D( __t1)
#define ALIAS_yy5Limitation_min_DD(__t1) yy5Limitation_min.DD( __t1)
#define ALIAS_yy5Limitation_min_D(__t1) yy5Limitation_min.D( __t1)
#define ALIAS_xx5Limitation_max_DD(__t1) xx5Limitation_max.DD( __t1)
#define ALIAS_xx5Limitation_max_D(__t1) xx5Limitation_max.D( __t1)
#define ALIAS_xx5Limitation_min_DD(__t1) xx5Limitation_min.DD( __t1)
#define ALIAS_xx5Limitation_min_D(__t1) xx5Limitation_min.D( __t1)
#define ALIAS_yy4Limitation_max_DD(__t1) yy4Limitation_max.DD( __t1)
#define ALIAS_yy4Limitation_max_D(__t1) yy4Limitation_max.D( __t1)
#define ALIAS_yy4Limitation_min_DD(__t1) yy4Limitation_min.DD( __t1)
#define ALIAS_yy4Limitation_min_D(__t1) yy4Limitation_min.D( __t1)
#define ALIAS_xx4Limitation_max_DD(__t1) xx4Limitation_max.DD( __t1)
#define ALIAS_xx4Limitation_max_D(__t1) xx4Limitation_max.D( __t1)
#define ALIAS_xx4Limitation_min_DD(__t1) xx4Limitation_min.DD( __t1)
#define ALIAS_xx4Limitation_min_D(__t1) xx4Limitation_min.D( __t1)
#define ALIAS_yy3Limitation_max_DD(__t1) yy3Limitation_max.DD( __t1)
#define ALIAS_yy3Limitation_max_D(__t1) yy3Limitation_max.D( __t1)
#define ALIAS_yy3Limitation_min_DD(__t1) yy3Limitation_min.DD( __t1)
#define ALIAS_yy3Limitation_min_D(__t1) yy3Limitation_min.D( __t1)
#define ALIAS_xx3Limitation_max_DD(__t1) xx3Limitation_max.DD( __t1)
#define ALIAS_xx3Limitation_max_D(__t1) xx3Limitation_max.D( __t1)
#define ALIAS_xx3Limitation_min_DD(__t1) xx3Limitation_min.DD( __t1)
#define ALIAS_xx3Limitation_min_D(__t1) xx3Limitation_min.D( __t1)
#define ALIAS_yy2Limitation_max_DD(__t1) yy2Limitation_max.DD( __t1)
#define ALIAS_yy2Limitation_max_D(__t1) yy2Limitation_max.D( __t1)
#define ALIAS_yy2Limitation_min_DD(__t1) yy2Limitation_min.DD( __t1)
#define ALIAS_yy2Limitation_min_D(__t1) yy2Limitation_min.D( __t1)
#define ALIAS_xx2Limitation_max_DD(__t1) xx2Limitation_max.DD( __t1)
#define ALIAS_xx2Limitation_max_D(__t1) xx2Limitation_max.D( __t1)
#define ALIAS_xx2Limitation_min_DD(__t1) xx2Limitation_min.DD( __t1)
#define ALIAS_xx2Limitation_min_D(__t1) xx2Limitation_min.D( __t1)
#define ALIAS_yy1Limitation_max_DD(__t1) yy1Limitation_max.DD( __t1)
#define ALIAS_yy1Limitation_max_D(__t1) yy1Limitation_max.D( __t1)
#define ALIAS_yy1Limitation_min_DD(__t1) yy1Limitation_min.DD( __t1)
#define ALIAS_yy1Limitation_min_D(__t1) yy1Limitation_min.D( __t1)
#define ALIAS_xx1Limitation_max_DD(__t1) xx1Limitation_max.DD( __t1)
#define ALIAS_xx1Limitation_max_D(__t1) xx1Limitation_max.D( __t1)
#define ALIAS_xx1Limitation_min_DD(__t1) xx1Limitation_min.DD( __t1)
#define ALIAS_xx1Limitation_min_D(__t1) xx1Limitation_min.D( __t1)
#define ALIAS_u20Limitation_max_DD(__t1) u20Limitation_max.DD( __t1)
#define ALIAS_u20Limitation_max_D(__t1) u20Limitation_max.D( __t1)
#define ALIAS_u20Limitation_min_DD(__t1) u20Limitation_min.DD( __t1)
#define ALIAS_u20Limitation_min_D(__t1) u20Limitation_min.D( __t1)
#define ALIAS_u19Limitation_max_DD(__t1) u19Limitation_max.DD( __t1)
#define ALIAS_u19Limitation_max_D(__t1) u19Limitation_max.D( __t1)
#define ALIAS_u19Limitation_min_DD(__t1) u19Limitation_min.DD( __t1)
#define ALIAS_u19Limitation_min_D(__t1) u19Limitation_min.D( __t1)
#define ALIAS_u18Limitation_max_DD(__t1) u18Limitation_max.DD( __t1)
#define ALIAS_u18Limitation_max_D(__t1) u18Limitation_max.D( __t1)
#define ALIAS_u18Limitation_min_DD(__t1) u18Limitation_min.DD( __t1)
#define ALIAS_u18Limitation_min_D(__t1) u18Limitation_min.D( __t1)
#define ALIAS_u17Limitation_max_DD(__t1) u17Limitation_max.DD( __t1)
#define ALIAS_u17Limitation_max_D(__t1) u17Limitation_max.D( __t1)
#define ALIAS_u17Limitation_min_DD(__t1) u17Limitation_min.DD( __t1)
#define ALIAS_u17Limitation_min_D(__t1) u17Limitation_min.D( __t1)
#define ALIAS_u16Limitation_max_DD(__t1) u16Limitation_max.DD( __t1)
#define ALIAS_u16Limitation_max_D(__t1) u16Limitation_max.D( __t1)
#define ALIAS_u16Limitation_min_DD(__t1) u16Limitation_min.DD( __t1)
#define ALIAS_u16Limitation_min_D(__t1) u16Limitation_min.D( __t1)
#define ALIAS_u15Limitation_max_DD(__t1) u15Limitation_max.DD( __t1)
#define ALIAS_u15Limitation_max_D(__t1) u15Limitation_max.D( __t1)
#define ALIAS_u15Limitation_min_DD(__t1) u15Limitation_min.DD( __t1)
#define ALIAS_u15Limitation_min_D(__t1) u15Limitation_min.D( __t1)
#define ALIAS_u14Limitation_max_DD(__t1) u14Limitation_max.DD( __t1)
#define ALIAS_u14Limitation_max_D(__t1) u14Limitation_max.D( __t1)
#define ALIAS_u14Limitation_min_DD(__t1) u14Limitation_min.DD( __t1)
#define ALIAS_u14Limitation_min_D(__t1) u14Limitation_min.D( __t1)
#define ALIAS_u13Limitation_max_DD(__t1) u13Limitation_max.DD( __t1)
#define ALIAS_u13Limitation_max_D(__t1) u13Limitation_max.D( __t1)
#define ALIAS_u13Limitation_min_DD(__t1) u13Limitation_min.DD( __t1)
#define ALIAS_u13Limitation_min_D(__t1) u13Limitation_min.D( __t1)
#define ALIAS_u12Limitation_max_DD(__t1) u12Limitation_max.DD( __t1)
#define ALIAS_u12Limitation_max_D(__t1) u12Limitation_max.D( __t1)
#define ALIAS_u12Limitation_min_DD(__t1) u12Limitation_min.DD( __t1)
#define ALIAS_u12Limitation_min_D(__t1) u12Limitation_min.D( __t1)
#define ALIAS_u11Limitation_max_DD(__t1) u11Limitation_max.DD( __t1)
#define ALIAS_u11Limitation_max_D(__t1) u11Limitation_max.D( __t1)
#define ALIAS_u11Limitation_min_DD(__t1) u11Limitation_min.DD( __t1)
#define ALIAS_u11Limitation_min_D(__t1) u11Limitation_min.D( __t1)
#define ALIAS_u10Limitation_max_DD(__t1) u10Limitation_max.DD( __t1)
#define ALIAS_u10Limitation_max_D(__t1) u10Limitation_max.D( __t1)
#define ALIAS_u10Limitation_min_DD(__t1) u10Limitation_min.DD( __t1)
#define ALIAS_u10Limitation_min_D(__t1) u10Limitation_min.D( __t1)
#define ALIAS_u9Limitation_max_DD(__t1) u9Limitation_max.DD( __t1)
#define ALIAS_u9Limitation_max_D(__t1) u9Limitation_max.D( __t1)
#define ALIAS_u9Limitation_min_DD(__t1) u9Limitation_min.DD( __t1)
#define ALIAS_u9Limitation_min_D(__t1) u9Limitation_min.D( __t1)
#define ALIAS_u8Limitation_max_DD(__t1) u8Limitation_max.DD( __t1)
#define ALIAS_u8Limitation_max_D(__t1) u8Limitation_max.D( __t1)
#define ALIAS_u8Limitation_min_DD(__t1) u8Limitation_min.DD( __t1)
#define ALIAS_u8Limitation_min_D(__t1) u8Limitation_min.D( __t1)
#define ALIAS_u7Limitation_max_DD(__t1) u7Limitation_max.DD( __t1)
#define ALIAS_u7Limitation_max_D(__t1) u7Limitation_max.D( __t1)
#define ALIAS_u7Limitation_min_DD(__t1) u7Limitation_min.DD( __t1)
#define ALIAS_u7Limitation_min_D(__t1) u7Limitation_min.D( __t1)
#define ALIAS_u6Limitation_max_DD(__t1) u6Limitation_max.DD( __t1)
#define ALIAS_u6Limitation_max_D(__t1) u6Limitation_max.D( __t1)
#define ALIAS_u6Limitation_min_DD(__t1) u6Limitation_min.DD( __t1)
#define ALIAS_u6Limitation_min_D(__t1) u6Limitation_min.D( __t1)
#define ALIAS_u5Limitation_max_DD(__t1) u5Limitation_max.DD( __t1)
#define ALIAS_u5Limitation_max_D(__t1) u5Limitation_max.D( __t1)
#define ALIAS_u5Limitation_min_DD(__t1) u5Limitation_min.DD( __t1)
#define ALIAS_u5Limitation_min_D(__t1) u5Limitation_min.D( __t1)
#define ALIAS_u4Limitation_max_DD(__t1) u4Limitation_max.DD( __t1)
#define ALIAS_u4Limitation_max_D(__t1) u4Limitation_max.D( __t1)
#define ALIAS_u4Limitation_min_DD(__t1) u4Limitation_min.DD( __t1)
#define ALIAS_u4Limitation_min_D(__t1) u4Limitation_min.D( __t1)
#define ALIAS_u3Limitation_max_DD(__t1) u3Limitation_max.DD( __t1)
#define ALIAS_u3Limitation_max_D(__t1) u3Limitation_max.D( __t1)
#define ALIAS_u3Limitation_min_DD(__t1) u3Limitation_min.DD( __t1)
#define ALIAS_u3Limitation_min_D(__t1) u3Limitation_min.D( __t1)
#define ALIAS_u2Limitation_max_DD(__t1) u2Limitation_max.DD( __t1)
#define ALIAS_u2Limitation_max_D(__t1) u2Limitation_max.D( __t1)
#define ALIAS_u2Limitation_min_DD(__t1) u2Limitation_min.DD( __t1)
#define ALIAS_u2Limitation_min_D(__t1) u2Limitation_min.D( __t1)
#define ALIAS_u1Limitation_max_DD(__t1) u1Limitation_max.DD( __t1)
#define ALIAS_u1Limitation_max_D(__t1) u1Limitation_max.D( __t1)
#define ALIAS_u1Limitation_min_DD(__t1) u1Limitation_min.DD( __t1)
#define ALIAS_u1Limitation_min_D(__t1) u1Limitation_min.D( __t1)


using namespace std;

namespace ICLOCS_ContinuousMPDefine {

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer ICLOCS_ContinuousMP::eta_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::eta_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = MU__[0];
    result__[ 1   ] = MU__[1];
    result__[ 2   ] = MU__[2];
    result__[ 3   ] = MU__[3];
    result__[ 4   ] = MU__[4];
    result__[ 5   ] = MU__[5];
    result__[ 6   ] = MU__[6];
    result__[ 7   ] = MU__[7];
    result__[ 8   ] = MU__[8];
    result__[ 9   ] = MU__[9];
    result__[ 10  ] = MU__[10];
    result__[ 11  ] = MU__[11];
    result__[ 12  ] = MU__[12];
    result__[ 13  ] = MU__[13];
    result__[ 14  ] = MU__[14];
    result__[ 15  ] = MU__[15];
    result__[ 16  ] = MU__[16];
    result__[ 17  ] = MU__[17];
    result__[ 18  ] = MU__[18];
    result__[ 19  ] = MU__[19];
    result__[ 20  ] = MU__[20];
    result__[ 21  ] = MU__[21];
    result__[ 22  ] = MU__[22];
    result__[ 23  ] = MU__[23];
    result__[ 24  ] = MU__[24];
    result__[ 25  ] = MU__[25];
    result__[ 26  ] = MU__[26];
    result__[ 27  ] = MU__[27];
    result__[ 28  ] = MU__[28];
    result__[ 29  ] = MU__[29];
    result__[ 30  ] = MU__[30];
    result__[ 31  ] = MU__[31];
    result__[ 32  ] = MU__[32];
    result__[ 33  ] = MU__[33];
    result__[ 34  ] = MU__[34];
    result__[ 35  ] = MU__[35];
    result__[ 36  ] = MU__[36];
    result__[ 37  ] = MU__[37];
    result__[ 38  ] = MU__[38];
    result__[ 39  ] = MU__[39];
    result__[ 40  ] = MU__[40];
    result__[ 41  ] = MU__[41];
    result__[ 42  ] = MU__[42];
    result__[ 43  ] = MU__[43];
    result__[ 44  ] = MU__[44];
    result__[ 45  ] = MU__[45];
    result__[ 46  ] = MU__[46];
    result__[ 47  ] = MU__[47];
    result__[ 48  ] = MU__[48];
    result__[ 49  ] = MU__[49];
    result__[ 50  ] = MU__[50];
    result__[ 51  ] = MU__[51];
    result__[ 52  ] = MU__[52];
    result__[ 53  ] = MU__[53];
    result__[ 54  ] = MU__[54];
    result__[ 55  ] = MU__[55];
    result__[ 56  ] = MU__[56];
    result__[ 57  ] = MU__[57];
    result__[ 58  ] = MU__[58];
    result__[ 59  ] = MU__[59];
    result__[ 60  ] = MU__[60];
    result__[ 61  ] = MU__[61];
    result__[ 62  ] = MU__[62];
    result__[ 63  ] = MU__[63];
    result__[ 64  ] = MU__[64];
    result__[ 65  ] = MU__[65];
    result__[ 66  ] = MU__[66];
    result__[ 67  ] = MU__[67];
    result__[ 68  ] = MU__[68];
    result__[ 69  ] = MU__[69];
    result__[ 70  ] = MU__[70];
    result__[ 71  ] = MU__[71];
    result__[ 72  ] = MU__[72];
    result__[ 73  ] = MU__[73];
    result__[ 74  ] = MU__[74];
    result__[ 75  ] = MU__[75];
    result__[ 76  ] = MU__[76];
    result__[ 77  ] = MU__[77];
    result__[ 78  ] = MU__[78];
    result__[ 79  ] = MU__[79];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "eta", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DetaDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DetaDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DetaDxp_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

  /*\
  :|:   ___           _ _               _
  :|:  |_ _|_ __   __| (_)_ __ ___  ___| |_
  :|:   | || '_ \ / _` | | '__/ _ \/ __| __|
  :|:   | || | | | (_| | | | |  __/ (__| |_
  :|:  |___|_| |_|\__,_|_|_|  \___|\___|\__|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::node_LR_to_cell(
    NodeQX const & LEFT,
    NodeQX const & RIGHT,
    NodeQX       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    X[6] = (LEFT.x[6]+RIGHT.x[6])/2;
    X[7] = (LEFT.x[7]+RIGHT.x[7])/2;
    X[8] = (LEFT.x[8]+RIGHT.x[8])/2;
    X[9] = (LEFT.x[9]+RIGHT.x[9])/2;
    X[10] = (LEFT.x[10]+RIGHT.x[10])/2;
    X[11] = (LEFT.x[11]+RIGHT.x[11])/2;
    X[12] = (LEFT.x[12]+RIGHT.x[12])/2;
    X[13] = (LEFT.x[13]+RIGHT.x[13])/2;
    X[14] = (LEFT.x[14]+RIGHT.x[14])/2;
    X[15] = (LEFT.x[15]+RIGHT.x[15])/2;
    X[16] = (LEFT.x[16]+RIGHT.x[16])/2;
    X[17] = (LEFT.x[17]+RIGHT.x[17])/2;
    X[18] = (LEFT.x[18]+RIGHT.x[18])/2;
    X[19] = (LEFT.x[19]+RIGHT.x[19])/2;
    X[20] = (LEFT.x[20]+RIGHT.x[20])/2;
    X[21] = (LEFT.x[21]+RIGHT.x[21])/2;
    X[22] = (LEFT.x[22]+RIGHT.x[22])/2;
    X[23] = (LEFT.x[23]+RIGHT.x[23])/2;
    X[24] = (LEFT.x[24]+RIGHT.x[24])/2;
    X[25] = (LEFT.x[25]+RIGHT.x[25])/2;
    X[26] = (LEFT.x[26]+RIGHT.x[26])/2;
    X[27] = (LEFT.x[27]+RIGHT.x[27])/2;
    X[28] = (LEFT.x[28]+RIGHT.x[28])/2;
    X[29] = (LEFT.x[29]+RIGHT.x[29])/2;
    X[30] = (LEFT.x[30]+RIGHT.x[30])/2;
    X[31] = (LEFT.x[31]+RIGHT.x[31])/2;
    X[32] = (LEFT.x[32]+RIGHT.x[32])/2;
    X[33] = (LEFT.x[33]+RIGHT.x[33])/2;
    X[34] = (LEFT.x[34]+RIGHT.x[34])/2;
    X[35] = (LEFT.x[35]+RIGHT.x[35])/2;
    X[36] = (LEFT.x[36]+RIGHT.x[36])/2;
    X[37] = (LEFT.x[37]+RIGHT.x[37])/2;
    X[38] = (LEFT.x[38]+RIGHT.x[38])/2;
    X[39] = (LEFT.x[39]+RIGHT.x[39])/2;
    X[40] = (LEFT.x[40]+RIGHT.x[40])/2;
    X[41] = (LEFT.x[41]+RIGHT.x[41])/2;
    X[42] = (LEFT.x[42]+RIGHT.x[42])/2;
    X[43] = (LEFT.x[43]+RIGHT.x[43])/2;
    X[44] = (LEFT.x[44]+RIGHT.x[44])/2;
    X[45] = (LEFT.x[45]+RIGHT.x[45])/2;
    X[46] = (LEFT.x[46]+RIGHT.x[46])/2;
    X[47] = (LEFT.x[47]+RIGHT.x[47])/2;
    X[48] = (LEFT.x[48]+RIGHT.x[48])/2;
    X[49] = (LEFT.x[49]+RIGHT.x[49])/2;
    X[50] = (LEFT.x[50]+RIGHT.x[50])/2;
    X[51] = (LEFT.x[51]+RIGHT.x[51])/2;
    X[52] = (LEFT.x[52]+RIGHT.x[52])/2;
    X[53] = (LEFT.x[53]+RIGHT.x[53])/2;
    X[54] = (LEFT.x[54]+RIGHT.x[54])/2;
    X[55] = (LEFT.x[55]+RIGHT.x[55])/2;
    X[56] = (LEFT.x[56]+RIGHT.x[56])/2;
    X[57] = (LEFT.x[57]+RIGHT.x[57])/2;
    X[58] = (LEFT.x[58]+RIGHT.x[58])/2;
    X[59] = (LEFT.x[59]+RIGHT.x[59])/2;
    X[60] = (LEFT.x[60]+RIGHT.x[60])/2;
    X[61] = (LEFT.x[61]+RIGHT.x[61])/2;
    X[62] = (LEFT.x[62]+RIGHT.x[62])/2;
    X[63] = (LEFT.x[63]+RIGHT.x[63])/2;
    X[64] = (LEFT.x[64]+RIGHT.x[64])/2;
    X[65] = (LEFT.x[65]+RIGHT.x[65])/2;
    X[66] = (LEFT.x[66]+RIGHT.x[66])/2;
    X[67] = (LEFT.x[67]+RIGHT.x[67])/2;
    X[68] = (LEFT.x[68]+RIGHT.x[68])/2;
    X[69] = (LEFT.x[69]+RIGHT.x[69])/2;
    X[70] = (LEFT.x[70]+RIGHT.x[70])/2;
    X[71] = (LEFT.x[71]+RIGHT.x[71])/2;
    X[72] = (LEFT.x[72]+RIGHT.x[72])/2;
    X[73] = (LEFT.x[73]+RIGHT.x[73])/2;
    X[74] = (LEFT.x[74]+RIGHT.x[74])/2;
    X[75] = (LEFT.x[75]+RIGHT.x[75])/2;
    X[76] = (LEFT.x[76]+RIGHT.x[76])/2;
    X[77] = (LEFT.x[77]+RIGHT.x[77])/2;
    X[78] = (LEFT.x[78]+RIGHT.x[78])/2;
    X[79] = (LEFT.x[79]+RIGHT.x[79])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::node_LR_to_cell(
    NodeQXL const & LEFT,
    NodeQXL const & RIGHT,
    NodeQXL       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    real_ptr L = const_cast<real_ptr>(NODE.lambda);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    X[6] = (LEFT.x[6]+RIGHT.x[6])/2;
    X[7] = (LEFT.x[7]+RIGHT.x[7])/2;
    X[8] = (LEFT.x[8]+RIGHT.x[8])/2;
    X[9] = (LEFT.x[9]+RIGHT.x[9])/2;
    X[10] = (LEFT.x[10]+RIGHT.x[10])/2;
    X[11] = (LEFT.x[11]+RIGHT.x[11])/2;
    X[12] = (LEFT.x[12]+RIGHT.x[12])/2;
    X[13] = (LEFT.x[13]+RIGHT.x[13])/2;
    X[14] = (LEFT.x[14]+RIGHT.x[14])/2;
    X[15] = (LEFT.x[15]+RIGHT.x[15])/2;
    X[16] = (LEFT.x[16]+RIGHT.x[16])/2;
    X[17] = (LEFT.x[17]+RIGHT.x[17])/2;
    X[18] = (LEFT.x[18]+RIGHT.x[18])/2;
    X[19] = (LEFT.x[19]+RIGHT.x[19])/2;
    X[20] = (LEFT.x[20]+RIGHT.x[20])/2;
    X[21] = (LEFT.x[21]+RIGHT.x[21])/2;
    X[22] = (LEFT.x[22]+RIGHT.x[22])/2;
    X[23] = (LEFT.x[23]+RIGHT.x[23])/2;
    X[24] = (LEFT.x[24]+RIGHT.x[24])/2;
    X[25] = (LEFT.x[25]+RIGHT.x[25])/2;
    X[26] = (LEFT.x[26]+RIGHT.x[26])/2;
    X[27] = (LEFT.x[27]+RIGHT.x[27])/2;
    X[28] = (LEFT.x[28]+RIGHT.x[28])/2;
    X[29] = (LEFT.x[29]+RIGHT.x[29])/2;
    X[30] = (LEFT.x[30]+RIGHT.x[30])/2;
    X[31] = (LEFT.x[31]+RIGHT.x[31])/2;
    X[32] = (LEFT.x[32]+RIGHT.x[32])/2;
    X[33] = (LEFT.x[33]+RIGHT.x[33])/2;
    X[34] = (LEFT.x[34]+RIGHT.x[34])/2;
    X[35] = (LEFT.x[35]+RIGHT.x[35])/2;
    X[36] = (LEFT.x[36]+RIGHT.x[36])/2;
    X[37] = (LEFT.x[37]+RIGHT.x[37])/2;
    X[38] = (LEFT.x[38]+RIGHT.x[38])/2;
    X[39] = (LEFT.x[39]+RIGHT.x[39])/2;
    X[40] = (LEFT.x[40]+RIGHT.x[40])/2;
    X[41] = (LEFT.x[41]+RIGHT.x[41])/2;
    X[42] = (LEFT.x[42]+RIGHT.x[42])/2;
    X[43] = (LEFT.x[43]+RIGHT.x[43])/2;
    X[44] = (LEFT.x[44]+RIGHT.x[44])/2;
    X[45] = (LEFT.x[45]+RIGHT.x[45])/2;
    X[46] = (LEFT.x[46]+RIGHT.x[46])/2;
    X[47] = (LEFT.x[47]+RIGHT.x[47])/2;
    X[48] = (LEFT.x[48]+RIGHT.x[48])/2;
    X[49] = (LEFT.x[49]+RIGHT.x[49])/2;
    X[50] = (LEFT.x[50]+RIGHT.x[50])/2;
    X[51] = (LEFT.x[51]+RIGHT.x[51])/2;
    X[52] = (LEFT.x[52]+RIGHT.x[52])/2;
    X[53] = (LEFT.x[53]+RIGHT.x[53])/2;
    X[54] = (LEFT.x[54]+RIGHT.x[54])/2;
    X[55] = (LEFT.x[55]+RIGHT.x[55])/2;
    X[56] = (LEFT.x[56]+RIGHT.x[56])/2;
    X[57] = (LEFT.x[57]+RIGHT.x[57])/2;
    X[58] = (LEFT.x[58]+RIGHT.x[58])/2;
    X[59] = (LEFT.x[59]+RIGHT.x[59])/2;
    X[60] = (LEFT.x[60]+RIGHT.x[60])/2;
    X[61] = (LEFT.x[61]+RIGHT.x[61])/2;
    X[62] = (LEFT.x[62]+RIGHT.x[62])/2;
    X[63] = (LEFT.x[63]+RIGHT.x[63])/2;
    X[64] = (LEFT.x[64]+RIGHT.x[64])/2;
    X[65] = (LEFT.x[65]+RIGHT.x[65])/2;
    X[66] = (LEFT.x[66]+RIGHT.x[66])/2;
    X[67] = (LEFT.x[67]+RIGHT.x[67])/2;
    X[68] = (LEFT.x[68]+RIGHT.x[68])/2;
    X[69] = (LEFT.x[69]+RIGHT.x[69])/2;
    X[70] = (LEFT.x[70]+RIGHT.x[70])/2;
    X[71] = (LEFT.x[71]+RIGHT.x[71])/2;
    X[72] = (LEFT.x[72]+RIGHT.x[72])/2;
    X[73] = (LEFT.x[73]+RIGHT.x[73])/2;
    X[74] = (LEFT.x[74]+RIGHT.x[74])/2;
    X[75] = (LEFT.x[75]+RIGHT.x[75])/2;
    X[76] = (LEFT.x[76]+RIGHT.x[76])/2;
    X[77] = (LEFT.x[77]+RIGHT.x[77])/2;
    X[78] = (LEFT.x[78]+RIGHT.x[78])/2;
    X[79] = (LEFT.x[79]+RIGHT.x[79])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
    L[2] = (LEFT.lambda[2]+RIGHT.lambda[2])/2;
    L[3] = (LEFT.lambda[3]+RIGHT.lambda[3])/2;
    L[4] = (LEFT.lambda[4]+RIGHT.lambda[4])/2;
    L[5] = (LEFT.lambda[5]+RIGHT.lambda[5])/2;
    L[6] = (LEFT.lambda[6]+RIGHT.lambda[6])/2;
    L[7] = (LEFT.lambda[7]+RIGHT.lambda[7])/2;
    L[8] = (LEFT.lambda[8]+RIGHT.lambda[8])/2;
    L[9] = (LEFT.lambda[9]+RIGHT.lambda[9])/2;
    L[10] = (LEFT.lambda[10]+RIGHT.lambda[10])/2;
    L[11] = (LEFT.lambda[11]+RIGHT.lambda[11])/2;
    L[12] = (LEFT.lambda[12]+RIGHT.lambda[12])/2;
    L[13] = (LEFT.lambda[13]+RIGHT.lambda[13])/2;
    L[14] = (LEFT.lambda[14]+RIGHT.lambda[14])/2;
    L[15] = (LEFT.lambda[15]+RIGHT.lambda[15])/2;
    L[16] = (LEFT.lambda[16]+RIGHT.lambda[16])/2;
    L[17] = (LEFT.lambda[17]+RIGHT.lambda[17])/2;
    L[18] = (LEFT.lambda[18]+RIGHT.lambda[18])/2;
    L[19] = (LEFT.lambda[19]+RIGHT.lambda[19])/2;
    L[20] = (LEFT.lambda[20]+RIGHT.lambda[20])/2;
    L[21] = (LEFT.lambda[21]+RIGHT.lambda[21])/2;
    L[22] = (LEFT.lambda[22]+RIGHT.lambda[22])/2;
    L[23] = (LEFT.lambda[23]+RIGHT.lambda[23])/2;
    L[24] = (LEFT.lambda[24]+RIGHT.lambda[24])/2;
    L[25] = (LEFT.lambda[25]+RIGHT.lambda[25])/2;
    L[26] = (LEFT.lambda[26]+RIGHT.lambda[26])/2;
    L[27] = (LEFT.lambda[27]+RIGHT.lambda[27])/2;
    L[28] = (LEFT.lambda[28]+RIGHT.lambda[28])/2;
    L[29] = (LEFT.lambda[29]+RIGHT.lambda[29])/2;
    L[30] = (LEFT.lambda[30]+RIGHT.lambda[30])/2;
    L[31] = (LEFT.lambda[31]+RIGHT.lambda[31])/2;
    L[32] = (LEFT.lambda[32]+RIGHT.lambda[32])/2;
    L[33] = (LEFT.lambda[33]+RIGHT.lambda[33])/2;
    L[34] = (LEFT.lambda[34]+RIGHT.lambda[34])/2;
    L[35] = (LEFT.lambda[35]+RIGHT.lambda[35])/2;
    L[36] = (LEFT.lambda[36]+RIGHT.lambda[36])/2;
    L[37] = (LEFT.lambda[37]+RIGHT.lambda[37])/2;
    L[38] = (LEFT.lambda[38]+RIGHT.lambda[38])/2;
    L[39] = (LEFT.lambda[39]+RIGHT.lambda[39])/2;
    L[40] = (LEFT.lambda[40]+RIGHT.lambda[40])/2;
    L[41] = (LEFT.lambda[41]+RIGHT.lambda[41])/2;
    L[42] = (LEFT.lambda[42]+RIGHT.lambda[42])/2;
    L[43] = (LEFT.lambda[43]+RIGHT.lambda[43])/2;
    L[44] = (LEFT.lambda[44]+RIGHT.lambda[44])/2;
    L[45] = (LEFT.lambda[45]+RIGHT.lambda[45])/2;
    L[46] = (LEFT.lambda[46]+RIGHT.lambda[46])/2;
    L[47] = (LEFT.lambda[47]+RIGHT.lambda[47])/2;
    L[48] = (LEFT.lambda[48]+RIGHT.lambda[48])/2;
    L[49] = (LEFT.lambda[49]+RIGHT.lambda[49])/2;
    L[50] = (LEFT.lambda[50]+RIGHT.lambda[50])/2;
    L[51] = (LEFT.lambda[51]+RIGHT.lambda[51])/2;
    L[52] = (LEFT.lambda[52]+RIGHT.lambda[52])/2;
    L[53] = (LEFT.lambda[53]+RIGHT.lambda[53])/2;
    L[54] = (LEFT.lambda[54]+RIGHT.lambda[54])/2;
    L[55] = (LEFT.lambda[55]+RIGHT.lambda[55])/2;
    L[56] = (LEFT.lambda[56]+RIGHT.lambda[56])/2;
    L[57] = (LEFT.lambda[57]+RIGHT.lambda[57])/2;
    L[58] = (LEFT.lambda[58]+RIGHT.lambda[58])/2;
    L[59] = (LEFT.lambda[59]+RIGHT.lambda[59])/2;
    L[60] = (LEFT.lambda[60]+RIGHT.lambda[60])/2;
    L[61] = (LEFT.lambda[61]+RIGHT.lambda[61])/2;
    L[62] = (LEFT.lambda[62]+RIGHT.lambda[62])/2;
    L[63] = (LEFT.lambda[63]+RIGHT.lambda[63])/2;
    L[64] = (LEFT.lambda[64]+RIGHT.lambda[64])/2;
    L[65] = (LEFT.lambda[65]+RIGHT.lambda[65])/2;
    L[66] = (LEFT.lambda[66]+RIGHT.lambda[66])/2;
    L[67] = (LEFT.lambda[67]+RIGHT.lambda[67])/2;
    L[68] = (LEFT.lambda[68]+RIGHT.lambda[68])/2;
    L[69] = (LEFT.lambda[69]+RIGHT.lambda[69])/2;
    L[70] = (LEFT.lambda[70]+RIGHT.lambda[70])/2;
    L[71] = (LEFT.lambda[71]+RIGHT.lambda[71])/2;
    L[72] = (LEFT.lambda[72]+RIGHT.lambda[72])/2;
    L[73] = (LEFT.lambda[73]+RIGHT.lambda[73])/2;
    L[74] = (LEFT.lambda[74]+RIGHT.lambda[74])/2;
    L[75] = (LEFT.lambda[75]+RIGHT.lambda[75])/2;
    L[76] = (LEFT.lambda[76]+RIGHT.lambda[76])/2;
    L[77] = (LEFT.lambda[77]+RIGHT.lambda[77])/2;
    L[78] = (LEFT.lambda[78]+RIGHT.lambda[78])/2;
    L[79] = (LEFT.lambda[79]+RIGHT.lambda[79])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::node_LR_to_cell(
    NodeQXL const & LEFT,
    NodeQXL const & RIGHT,
    NodeQXL       & NODE,
    V_p_type      & V,
    VL_p_type     & VL
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    real_ptr L = const_cast<real_ptr>(NODE.lambda);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    X[6] = (LEFT.x[6]+RIGHT.x[6])/2;
    X[7] = (LEFT.x[7]+RIGHT.x[7])/2;
    X[8] = (LEFT.x[8]+RIGHT.x[8])/2;
    X[9] = (LEFT.x[9]+RIGHT.x[9])/2;
    X[10] = (LEFT.x[10]+RIGHT.x[10])/2;
    X[11] = (LEFT.x[11]+RIGHT.x[11])/2;
    X[12] = (LEFT.x[12]+RIGHT.x[12])/2;
    X[13] = (LEFT.x[13]+RIGHT.x[13])/2;
    X[14] = (LEFT.x[14]+RIGHT.x[14])/2;
    X[15] = (LEFT.x[15]+RIGHT.x[15])/2;
    X[16] = (LEFT.x[16]+RIGHT.x[16])/2;
    X[17] = (LEFT.x[17]+RIGHT.x[17])/2;
    X[18] = (LEFT.x[18]+RIGHT.x[18])/2;
    X[19] = (LEFT.x[19]+RIGHT.x[19])/2;
    X[20] = (LEFT.x[20]+RIGHT.x[20])/2;
    X[21] = (LEFT.x[21]+RIGHT.x[21])/2;
    X[22] = (LEFT.x[22]+RIGHT.x[22])/2;
    X[23] = (LEFT.x[23]+RIGHT.x[23])/2;
    X[24] = (LEFT.x[24]+RIGHT.x[24])/2;
    X[25] = (LEFT.x[25]+RIGHT.x[25])/2;
    X[26] = (LEFT.x[26]+RIGHT.x[26])/2;
    X[27] = (LEFT.x[27]+RIGHT.x[27])/2;
    X[28] = (LEFT.x[28]+RIGHT.x[28])/2;
    X[29] = (LEFT.x[29]+RIGHT.x[29])/2;
    X[30] = (LEFT.x[30]+RIGHT.x[30])/2;
    X[31] = (LEFT.x[31]+RIGHT.x[31])/2;
    X[32] = (LEFT.x[32]+RIGHT.x[32])/2;
    X[33] = (LEFT.x[33]+RIGHT.x[33])/2;
    X[34] = (LEFT.x[34]+RIGHT.x[34])/2;
    X[35] = (LEFT.x[35]+RIGHT.x[35])/2;
    X[36] = (LEFT.x[36]+RIGHT.x[36])/2;
    X[37] = (LEFT.x[37]+RIGHT.x[37])/2;
    X[38] = (LEFT.x[38]+RIGHT.x[38])/2;
    X[39] = (LEFT.x[39]+RIGHT.x[39])/2;
    X[40] = (LEFT.x[40]+RIGHT.x[40])/2;
    X[41] = (LEFT.x[41]+RIGHT.x[41])/2;
    X[42] = (LEFT.x[42]+RIGHT.x[42])/2;
    X[43] = (LEFT.x[43]+RIGHT.x[43])/2;
    X[44] = (LEFT.x[44]+RIGHT.x[44])/2;
    X[45] = (LEFT.x[45]+RIGHT.x[45])/2;
    X[46] = (LEFT.x[46]+RIGHT.x[46])/2;
    X[47] = (LEFT.x[47]+RIGHT.x[47])/2;
    X[48] = (LEFT.x[48]+RIGHT.x[48])/2;
    X[49] = (LEFT.x[49]+RIGHT.x[49])/2;
    X[50] = (LEFT.x[50]+RIGHT.x[50])/2;
    X[51] = (LEFT.x[51]+RIGHT.x[51])/2;
    X[52] = (LEFT.x[52]+RIGHT.x[52])/2;
    X[53] = (LEFT.x[53]+RIGHT.x[53])/2;
    X[54] = (LEFT.x[54]+RIGHT.x[54])/2;
    X[55] = (LEFT.x[55]+RIGHT.x[55])/2;
    X[56] = (LEFT.x[56]+RIGHT.x[56])/2;
    X[57] = (LEFT.x[57]+RIGHT.x[57])/2;
    X[58] = (LEFT.x[58]+RIGHT.x[58])/2;
    X[59] = (LEFT.x[59]+RIGHT.x[59])/2;
    X[60] = (LEFT.x[60]+RIGHT.x[60])/2;
    X[61] = (LEFT.x[61]+RIGHT.x[61])/2;
    X[62] = (LEFT.x[62]+RIGHT.x[62])/2;
    X[63] = (LEFT.x[63]+RIGHT.x[63])/2;
    X[64] = (LEFT.x[64]+RIGHT.x[64])/2;
    X[65] = (LEFT.x[65]+RIGHT.x[65])/2;
    X[66] = (LEFT.x[66]+RIGHT.x[66])/2;
    X[67] = (LEFT.x[67]+RIGHT.x[67])/2;
    X[68] = (LEFT.x[68]+RIGHT.x[68])/2;
    X[69] = (LEFT.x[69]+RIGHT.x[69])/2;
    X[70] = (LEFT.x[70]+RIGHT.x[70])/2;
    X[71] = (LEFT.x[71]+RIGHT.x[71])/2;
    X[72] = (LEFT.x[72]+RIGHT.x[72])/2;
    X[73] = (LEFT.x[73]+RIGHT.x[73])/2;
    X[74] = (LEFT.x[74]+RIGHT.x[74])/2;
    X[75] = (LEFT.x[75]+RIGHT.x[75])/2;
    X[76] = (LEFT.x[76]+RIGHT.x[76])/2;
    X[77] = (LEFT.x[77]+RIGHT.x[77])/2;
    X[78] = (LEFT.x[78]+RIGHT.x[78])/2;
    X[79] = (LEFT.x[79]+RIGHT.x[79])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
    L[2] = (LEFT.lambda[2]+RIGHT.lambda[2])/2;
    L[3] = (LEFT.lambda[3]+RIGHT.lambda[3])/2;
    L[4] = (LEFT.lambda[4]+RIGHT.lambda[4])/2;
    L[5] = (LEFT.lambda[5]+RIGHT.lambda[5])/2;
    L[6] = (LEFT.lambda[6]+RIGHT.lambda[6])/2;
    L[7] = (LEFT.lambda[7]+RIGHT.lambda[7])/2;
    L[8] = (LEFT.lambda[8]+RIGHT.lambda[8])/2;
    L[9] = (LEFT.lambda[9]+RIGHT.lambda[9])/2;
    L[10] = (LEFT.lambda[10]+RIGHT.lambda[10])/2;
    L[11] = (LEFT.lambda[11]+RIGHT.lambda[11])/2;
    L[12] = (LEFT.lambda[12]+RIGHT.lambda[12])/2;
    L[13] = (LEFT.lambda[13]+RIGHT.lambda[13])/2;
    L[14] = (LEFT.lambda[14]+RIGHT.lambda[14])/2;
    L[15] = (LEFT.lambda[15]+RIGHT.lambda[15])/2;
    L[16] = (LEFT.lambda[16]+RIGHT.lambda[16])/2;
    L[17] = (LEFT.lambda[17]+RIGHT.lambda[17])/2;
    L[18] = (LEFT.lambda[18]+RIGHT.lambda[18])/2;
    L[19] = (LEFT.lambda[19]+RIGHT.lambda[19])/2;
    L[20] = (LEFT.lambda[20]+RIGHT.lambda[20])/2;
    L[21] = (LEFT.lambda[21]+RIGHT.lambda[21])/2;
    L[22] = (LEFT.lambda[22]+RIGHT.lambda[22])/2;
    L[23] = (LEFT.lambda[23]+RIGHT.lambda[23])/2;
    L[24] = (LEFT.lambda[24]+RIGHT.lambda[24])/2;
    L[25] = (LEFT.lambda[25]+RIGHT.lambda[25])/2;
    L[26] = (LEFT.lambda[26]+RIGHT.lambda[26])/2;
    L[27] = (LEFT.lambda[27]+RIGHT.lambda[27])/2;
    L[28] = (LEFT.lambda[28]+RIGHT.lambda[28])/2;
    L[29] = (LEFT.lambda[29]+RIGHT.lambda[29])/2;
    L[30] = (LEFT.lambda[30]+RIGHT.lambda[30])/2;
    L[31] = (LEFT.lambda[31]+RIGHT.lambda[31])/2;
    L[32] = (LEFT.lambda[32]+RIGHT.lambda[32])/2;
    L[33] = (LEFT.lambda[33]+RIGHT.lambda[33])/2;
    L[34] = (LEFT.lambda[34]+RIGHT.lambda[34])/2;
    L[35] = (LEFT.lambda[35]+RIGHT.lambda[35])/2;
    L[36] = (LEFT.lambda[36]+RIGHT.lambda[36])/2;
    L[37] = (LEFT.lambda[37]+RIGHT.lambda[37])/2;
    L[38] = (LEFT.lambda[38]+RIGHT.lambda[38])/2;
    L[39] = (LEFT.lambda[39]+RIGHT.lambda[39])/2;
    L[40] = (LEFT.lambda[40]+RIGHT.lambda[40])/2;
    L[41] = (LEFT.lambda[41]+RIGHT.lambda[41])/2;
    L[42] = (LEFT.lambda[42]+RIGHT.lambda[42])/2;
    L[43] = (LEFT.lambda[43]+RIGHT.lambda[43])/2;
    L[44] = (LEFT.lambda[44]+RIGHT.lambda[44])/2;
    L[45] = (LEFT.lambda[45]+RIGHT.lambda[45])/2;
    L[46] = (LEFT.lambda[46]+RIGHT.lambda[46])/2;
    L[47] = (LEFT.lambda[47]+RIGHT.lambda[47])/2;
    L[48] = (LEFT.lambda[48]+RIGHT.lambda[48])/2;
    L[49] = (LEFT.lambda[49]+RIGHT.lambda[49])/2;
    L[50] = (LEFT.lambda[50]+RIGHT.lambda[50])/2;
    L[51] = (LEFT.lambda[51]+RIGHT.lambda[51])/2;
    L[52] = (LEFT.lambda[52]+RIGHT.lambda[52])/2;
    L[53] = (LEFT.lambda[53]+RIGHT.lambda[53])/2;
    L[54] = (LEFT.lambda[54]+RIGHT.lambda[54])/2;
    L[55] = (LEFT.lambda[55]+RIGHT.lambda[55])/2;
    L[56] = (LEFT.lambda[56]+RIGHT.lambda[56])/2;
    L[57] = (LEFT.lambda[57]+RIGHT.lambda[57])/2;
    L[58] = (LEFT.lambda[58]+RIGHT.lambda[58])/2;
    L[59] = (LEFT.lambda[59]+RIGHT.lambda[59])/2;
    L[60] = (LEFT.lambda[60]+RIGHT.lambda[60])/2;
    L[61] = (LEFT.lambda[61]+RIGHT.lambda[61])/2;
    L[62] = (LEFT.lambda[62]+RIGHT.lambda[62])/2;
    L[63] = (LEFT.lambda[63]+RIGHT.lambda[63])/2;
    L[64] = (LEFT.lambda[64]+RIGHT.lambda[64])/2;
    L[65] = (LEFT.lambda[65]+RIGHT.lambda[65])/2;
    L[66] = (LEFT.lambda[66]+RIGHT.lambda[66])/2;
    L[67] = (LEFT.lambda[67]+RIGHT.lambda[67])/2;
    L[68] = (LEFT.lambda[68]+RIGHT.lambda[68])/2;
    L[69] = (LEFT.lambda[69]+RIGHT.lambda[69])/2;
    L[70] = (LEFT.lambda[70]+RIGHT.lambda[70])/2;
    L[71] = (LEFT.lambda[71]+RIGHT.lambda[71])/2;
    L[72] = (LEFT.lambda[72]+RIGHT.lambda[72])/2;
    L[73] = (LEFT.lambda[73]+RIGHT.lambda[73])/2;
    L[74] = (LEFT.lambda[74]+RIGHT.lambda[74])/2;
    L[75] = (LEFT.lambda[75]+RIGHT.lambda[75])/2;
    L[76] = (LEFT.lambda[76]+RIGHT.lambda[76])/2;
    L[77] = (LEFT.lambda[77]+RIGHT.lambda[77])/2;
    L[78] = (LEFT.lambda[78]+RIGHT.lambda[78])/2;
    L[79] = (LEFT.lambda[79]+RIGHT.lambda[79])/2;
    real_type DZETA__xo = RIGHT.q[0] - LEFT.q[0];
    V[0]  = (RIGHT.x[0]-LEFT.x[0])/DZETA__xo;
    V[1]  = (RIGHT.x[1]-LEFT.x[1])/DZETA__xo;
    V[2]  = (RIGHT.x[2]-LEFT.x[2])/DZETA__xo;
    V[3]  = (RIGHT.x[3]-LEFT.x[3])/DZETA__xo;
    V[4]  = (RIGHT.x[4]-LEFT.x[4])/DZETA__xo;
    V[5]  = (RIGHT.x[5]-LEFT.x[5])/DZETA__xo;
    V[6]  = (RIGHT.x[6]-LEFT.x[6])/DZETA__xo;
    V[7]  = (RIGHT.x[7]-LEFT.x[7])/DZETA__xo;
    V[8]  = (RIGHT.x[8]-LEFT.x[8])/DZETA__xo;
    V[9]  = (RIGHT.x[9]-LEFT.x[9])/DZETA__xo;
    V[10]  = (RIGHT.x[10]-LEFT.x[10])/DZETA__xo;
    V[11]  = (RIGHT.x[11]-LEFT.x[11])/DZETA__xo;
    V[12]  = (RIGHT.x[12]-LEFT.x[12])/DZETA__xo;
    V[13]  = (RIGHT.x[13]-LEFT.x[13])/DZETA__xo;
    V[14]  = (RIGHT.x[14]-LEFT.x[14])/DZETA__xo;
    V[15]  = (RIGHT.x[15]-LEFT.x[15])/DZETA__xo;
    V[16]  = (RIGHT.x[16]-LEFT.x[16])/DZETA__xo;
    V[17]  = (RIGHT.x[17]-LEFT.x[17])/DZETA__xo;
    V[18]  = (RIGHT.x[18]-LEFT.x[18])/DZETA__xo;
    V[19]  = (RIGHT.x[19]-LEFT.x[19])/DZETA__xo;
    V[20]  = (RIGHT.x[20]-LEFT.x[20])/DZETA__xo;
    V[21]  = (RIGHT.x[21]-LEFT.x[21])/DZETA__xo;
    V[22]  = (RIGHT.x[22]-LEFT.x[22])/DZETA__xo;
    V[23]  = (RIGHT.x[23]-LEFT.x[23])/DZETA__xo;
    V[24]  = (RIGHT.x[24]-LEFT.x[24])/DZETA__xo;
    V[25]  = (RIGHT.x[25]-LEFT.x[25])/DZETA__xo;
    V[26]  = (RIGHT.x[26]-LEFT.x[26])/DZETA__xo;
    V[27]  = (RIGHT.x[27]-LEFT.x[27])/DZETA__xo;
    V[28]  = (RIGHT.x[28]-LEFT.x[28])/DZETA__xo;
    V[29]  = (RIGHT.x[29]-LEFT.x[29])/DZETA__xo;
    V[30]  = (RIGHT.x[30]-LEFT.x[30])/DZETA__xo;
    V[31]  = (RIGHT.x[31]-LEFT.x[31])/DZETA__xo;
    V[32]  = (RIGHT.x[32]-LEFT.x[32])/DZETA__xo;
    V[33]  = (RIGHT.x[33]-LEFT.x[33])/DZETA__xo;
    V[34]  = (RIGHT.x[34]-LEFT.x[34])/DZETA__xo;
    V[35]  = (RIGHT.x[35]-LEFT.x[35])/DZETA__xo;
    V[36]  = (RIGHT.x[36]-LEFT.x[36])/DZETA__xo;
    V[37]  = (RIGHT.x[37]-LEFT.x[37])/DZETA__xo;
    V[38]  = (RIGHT.x[38]-LEFT.x[38])/DZETA__xo;
    V[39]  = (RIGHT.x[39]-LEFT.x[39])/DZETA__xo;
    V[40]  = (RIGHT.x[40]-LEFT.x[40])/DZETA__xo;
    V[41]  = (RIGHT.x[41]-LEFT.x[41])/DZETA__xo;
    V[42]  = (RIGHT.x[42]-LEFT.x[42])/DZETA__xo;
    V[43]  = (RIGHT.x[43]-LEFT.x[43])/DZETA__xo;
    V[44]  = (RIGHT.x[44]-LEFT.x[44])/DZETA__xo;
    V[45]  = (RIGHT.x[45]-LEFT.x[45])/DZETA__xo;
    V[46]  = (RIGHT.x[46]-LEFT.x[46])/DZETA__xo;
    V[47]  = (RIGHT.x[47]-LEFT.x[47])/DZETA__xo;
    V[48]  = (RIGHT.x[48]-LEFT.x[48])/DZETA__xo;
    V[49]  = (RIGHT.x[49]-LEFT.x[49])/DZETA__xo;
    V[50]  = (RIGHT.x[50]-LEFT.x[50])/DZETA__xo;
    V[51]  = (RIGHT.x[51]-LEFT.x[51])/DZETA__xo;
    V[52]  = (RIGHT.x[52]-LEFT.x[52])/DZETA__xo;
    V[53]  = (RIGHT.x[53]-LEFT.x[53])/DZETA__xo;
    V[54]  = (RIGHT.x[54]-LEFT.x[54])/DZETA__xo;
    V[55]  = (RIGHT.x[55]-LEFT.x[55])/DZETA__xo;
    V[56]  = (RIGHT.x[56]-LEFT.x[56])/DZETA__xo;
    V[57]  = (RIGHT.x[57]-LEFT.x[57])/DZETA__xo;
    V[58]  = (RIGHT.x[58]-LEFT.x[58])/DZETA__xo;
    V[59]  = (RIGHT.x[59]-LEFT.x[59])/DZETA__xo;
    V[60]  = (RIGHT.x[60]-LEFT.x[60])/DZETA__xo;
    V[61]  = (RIGHT.x[61]-LEFT.x[61])/DZETA__xo;
    V[62]  = (RIGHT.x[62]-LEFT.x[62])/DZETA__xo;
    V[63]  = (RIGHT.x[63]-LEFT.x[63])/DZETA__xo;
    V[64]  = (RIGHT.x[64]-LEFT.x[64])/DZETA__xo;
    V[65]  = (RIGHT.x[65]-LEFT.x[65])/DZETA__xo;
    V[66]  = (RIGHT.x[66]-LEFT.x[66])/DZETA__xo;
    V[67]  = (RIGHT.x[67]-LEFT.x[67])/DZETA__xo;
    V[68]  = (RIGHT.x[68]-LEFT.x[68])/DZETA__xo;
    V[69]  = (RIGHT.x[69]-LEFT.x[69])/DZETA__xo;
    V[70]  = (RIGHT.x[70]-LEFT.x[70])/DZETA__xo;
    V[71]  = (RIGHT.x[71]-LEFT.x[71])/DZETA__xo;
    V[72]  = (RIGHT.x[72]-LEFT.x[72])/DZETA__xo;
    V[73]  = (RIGHT.x[73]-LEFT.x[73])/DZETA__xo;
    V[74]  = (RIGHT.x[74]-LEFT.x[74])/DZETA__xo;
    V[75]  = (RIGHT.x[75]-LEFT.x[75])/DZETA__xo;
    V[76]  = (RIGHT.x[76]-LEFT.x[76])/DZETA__xo;
    V[77]  = (RIGHT.x[77]-LEFT.x[77])/DZETA__xo;
    V[78]  = (RIGHT.x[78]-LEFT.x[78])/DZETA__xo;
    V[79]  = (RIGHT.x[79]-LEFT.x[79])/DZETA__xo;
    VL[0] = (RIGHT.lambda[0]-LEFT.lambda[0])/DZETA__xo;
    VL[1] = (RIGHT.lambda[1]-LEFT.lambda[1])/DZETA__xo;
    VL[2] = (RIGHT.lambda[2]-LEFT.lambda[2])/DZETA__xo;
    VL[3] = (RIGHT.lambda[3]-LEFT.lambda[3])/DZETA__xo;
    VL[4] = (RIGHT.lambda[4]-LEFT.lambda[4])/DZETA__xo;
    VL[5] = (RIGHT.lambda[5]-LEFT.lambda[5])/DZETA__xo;
    VL[6] = (RIGHT.lambda[6]-LEFT.lambda[6])/DZETA__xo;
    VL[7] = (RIGHT.lambda[7]-LEFT.lambda[7])/DZETA__xo;
    VL[8] = (RIGHT.lambda[8]-LEFT.lambda[8])/DZETA__xo;
    VL[9] = (RIGHT.lambda[9]-LEFT.lambda[9])/DZETA__xo;
    VL[10] = (RIGHT.lambda[10]-LEFT.lambda[10])/DZETA__xo;
    VL[11] = (RIGHT.lambda[11]-LEFT.lambda[11])/DZETA__xo;
    VL[12] = (RIGHT.lambda[12]-LEFT.lambda[12])/DZETA__xo;
    VL[13] = (RIGHT.lambda[13]-LEFT.lambda[13])/DZETA__xo;
    VL[14] = (RIGHT.lambda[14]-LEFT.lambda[14])/DZETA__xo;
    VL[15] = (RIGHT.lambda[15]-LEFT.lambda[15])/DZETA__xo;
    VL[16] = (RIGHT.lambda[16]-LEFT.lambda[16])/DZETA__xo;
    VL[17] = (RIGHT.lambda[17]-LEFT.lambda[17])/DZETA__xo;
    VL[18] = (RIGHT.lambda[18]-LEFT.lambda[18])/DZETA__xo;
    VL[19] = (RIGHT.lambda[19]-LEFT.lambda[19])/DZETA__xo;
    VL[20] = (RIGHT.lambda[20]-LEFT.lambda[20])/DZETA__xo;
    VL[21] = (RIGHT.lambda[21]-LEFT.lambda[21])/DZETA__xo;
    VL[22] = (RIGHT.lambda[22]-LEFT.lambda[22])/DZETA__xo;
    VL[23] = (RIGHT.lambda[23]-LEFT.lambda[23])/DZETA__xo;
    VL[24] = (RIGHT.lambda[24]-LEFT.lambda[24])/DZETA__xo;
    VL[25] = (RIGHT.lambda[25]-LEFT.lambda[25])/DZETA__xo;
    VL[26] = (RIGHT.lambda[26]-LEFT.lambda[26])/DZETA__xo;
    VL[27] = (RIGHT.lambda[27]-LEFT.lambda[27])/DZETA__xo;
    VL[28] = (RIGHT.lambda[28]-LEFT.lambda[28])/DZETA__xo;
    VL[29] = (RIGHT.lambda[29]-LEFT.lambda[29])/DZETA__xo;
    VL[30] = (RIGHT.lambda[30]-LEFT.lambda[30])/DZETA__xo;
    VL[31] = (RIGHT.lambda[31]-LEFT.lambda[31])/DZETA__xo;
    VL[32] = (RIGHT.lambda[32]-LEFT.lambda[32])/DZETA__xo;
    VL[33] = (RIGHT.lambda[33]-LEFT.lambda[33])/DZETA__xo;
    VL[34] = (RIGHT.lambda[34]-LEFT.lambda[34])/DZETA__xo;
    VL[35] = (RIGHT.lambda[35]-LEFT.lambda[35])/DZETA__xo;
    VL[36] = (RIGHT.lambda[36]-LEFT.lambda[36])/DZETA__xo;
    VL[37] = (RIGHT.lambda[37]-LEFT.lambda[37])/DZETA__xo;
    VL[38] = (RIGHT.lambda[38]-LEFT.lambda[38])/DZETA__xo;
    VL[39] = (RIGHT.lambda[39]-LEFT.lambda[39])/DZETA__xo;
    VL[40] = (RIGHT.lambda[40]-LEFT.lambda[40])/DZETA__xo;
    VL[41] = (RIGHT.lambda[41]-LEFT.lambda[41])/DZETA__xo;
    VL[42] = (RIGHT.lambda[42]-LEFT.lambda[42])/DZETA__xo;
    VL[43] = (RIGHT.lambda[43]-LEFT.lambda[43])/DZETA__xo;
    VL[44] = (RIGHT.lambda[44]-LEFT.lambda[44])/DZETA__xo;
    VL[45] = (RIGHT.lambda[45]-LEFT.lambda[45])/DZETA__xo;
    VL[46] = (RIGHT.lambda[46]-LEFT.lambda[46])/DZETA__xo;
    VL[47] = (RIGHT.lambda[47]-LEFT.lambda[47])/DZETA__xo;
    VL[48] = (RIGHT.lambda[48]-LEFT.lambda[48])/DZETA__xo;
    VL[49] = (RIGHT.lambda[49]-LEFT.lambda[49])/DZETA__xo;
    VL[50] = (RIGHT.lambda[50]-LEFT.lambda[50])/DZETA__xo;
    VL[51] = (RIGHT.lambda[51]-LEFT.lambda[51])/DZETA__xo;
    VL[52] = (RIGHT.lambda[52]-LEFT.lambda[52])/DZETA__xo;
    VL[53] = (RIGHT.lambda[53]-LEFT.lambda[53])/DZETA__xo;
    VL[54] = (RIGHT.lambda[54]-LEFT.lambda[54])/DZETA__xo;
    VL[55] = (RIGHT.lambda[55]-LEFT.lambda[55])/DZETA__xo;
    VL[56] = (RIGHT.lambda[56]-LEFT.lambda[56])/DZETA__xo;
    VL[57] = (RIGHT.lambda[57]-LEFT.lambda[57])/DZETA__xo;
    VL[58] = (RIGHT.lambda[58]-LEFT.lambda[58])/DZETA__xo;
    VL[59] = (RIGHT.lambda[59]-LEFT.lambda[59])/DZETA__xo;
    VL[60] = (RIGHT.lambda[60]-LEFT.lambda[60])/DZETA__xo;
    VL[61] = (RIGHT.lambda[61]-LEFT.lambda[61])/DZETA__xo;
    VL[62] = (RIGHT.lambda[62]-LEFT.lambda[62])/DZETA__xo;
    VL[63] = (RIGHT.lambda[63]-LEFT.lambda[63])/DZETA__xo;
    VL[64] = (RIGHT.lambda[64]-LEFT.lambda[64])/DZETA__xo;
    VL[65] = (RIGHT.lambda[65]-LEFT.lambda[65])/DZETA__xo;
    VL[66] = (RIGHT.lambda[66]-LEFT.lambda[66])/DZETA__xo;
    VL[67] = (RIGHT.lambda[67]-LEFT.lambda[67])/DZETA__xo;
    VL[68] = (RIGHT.lambda[68]-LEFT.lambda[68])/DZETA__xo;
    VL[69] = (RIGHT.lambda[69]-LEFT.lambda[69])/DZETA__xo;
    VL[70] = (RIGHT.lambda[70]-LEFT.lambda[70])/DZETA__xo;
    VL[71] = (RIGHT.lambda[71]-LEFT.lambda[71])/DZETA__xo;
    VL[72] = (RIGHT.lambda[72]-LEFT.lambda[72])/DZETA__xo;
    VL[73] = (RIGHT.lambda[73]-LEFT.lambda[73])/DZETA__xo;
    VL[74] = (RIGHT.lambda[74]-LEFT.lambda[74])/DZETA__xo;
    VL[75] = (RIGHT.lambda[75]-LEFT.lambda[75])/DZETA__xo;
    VL[76] = (RIGHT.lambda[76]-LEFT.lambda[76])/DZETA__xo;
    VL[77] = (RIGHT.lambda[77]-LEFT.lambda[77])/DZETA__xo;
    VL[78] = (RIGHT.lambda[78]-LEFT.lambda[78])/DZETA__xo;
    VL[79] = (RIGHT.lambda[79]-LEFT.lambda[79])/DZETA__xo;
    return DZETA__xo;
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_Guess.cc
