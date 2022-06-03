/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_Guess.cc                           |
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

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer ICLOCS_ContinuousMP::fd_ode_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::fd_ode_eval(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[80], V__[80];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    XM__[8] = (XL__[8]+XR__[8])/2;
    XM__[9] = (XL__[9]+XR__[9])/2;
    XM__[10] = (XL__[10]+XR__[10])/2;
    XM__[11] = (XL__[11]+XR__[11])/2;
    XM__[12] = (XL__[12]+XR__[12])/2;
    XM__[13] = (XL__[13]+XR__[13])/2;
    XM__[14] = (XL__[14]+XR__[14])/2;
    XM__[15] = (XL__[15]+XR__[15])/2;
    XM__[16] = (XL__[16]+XR__[16])/2;
    XM__[17] = (XL__[17]+XR__[17])/2;
    XM__[18] = (XL__[18]+XR__[18])/2;
    XM__[19] = (XL__[19]+XR__[19])/2;
    XM__[20] = (XL__[20]+XR__[20])/2;
    XM__[21] = (XL__[21]+XR__[21])/2;
    XM__[22] = (XL__[22]+XR__[22])/2;
    XM__[23] = (XL__[23]+XR__[23])/2;
    XM__[24] = (XL__[24]+XR__[24])/2;
    XM__[25] = (XL__[25]+XR__[25])/2;
    XM__[26] = (XL__[26]+XR__[26])/2;
    XM__[27] = (XL__[27]+XR__[27])/2;
    XM__[28] = (XL__[28]+XR__[28])/2;
    XM__[29] = (XL__[29]+XR__[29])/2;
    XM__[30] = (XL__[30]+XR__[30])/2;
    XM__[31] = (XL__[31]+XR__[31])/2;
    XM__[32] = (XL__[32]+XR__[32])/2;
    XM__[33] = (XL__[33]+XR__[33])/2;
    XM__[34] = (XL__[34]+XR__[34])/2;
    XM__[35] = (XL__[35]+XR__[35])/2;
    XM__[36] = (XL__[36]+XR__[36])/2;
    XM__[37] = (XL__[37]+XR__[37])/2;
    XM__[38] = (XL__[38]+XR__[38])/2;
    XM__[39] = (XL__[39]+XR__[39])/2;
    XM__[40] = (XL__[40]+XR__[40])/2;
    XM__[41] = (XL__[41]+XR__[41])/2;
    XM__[42] = (XL__[42]+XR__[42])/2;
    XM__[43] = (XL__[43]+XR__[43])/2;
    XM__[44] = (XL__[44]+XR__[44])/2;
    XM__[45] = (XL__[45]+XR__[45])/2;
    XM__[46] = (XL__[46]+XR__[46])/2;
    XM__[47] = (XL__[47]+XR__[47])/2;
    XM__[48] = (XL__[48]+XR__[48])/2;
    XM__[49] = (XL__[49]+XR__[49])/2;
    XM__[50] = (XL__[50]+XR__[50])/2;
    XM__[51] = (XL__[51]+XR__[51])/2;
    XM__[52] = (XL__[52]+XR__[52])/2;
    XM__[53] = (XL__[53]+XR__[53])/2;
    XM__[54] = (XL__[54]+XR__[54])/2;
    XM__[55] = (XL__[55]+XR__[55])/2;
    XM__[56] = (XL__[56]+XR__[56])/2;
    XM__[57] = (XL__[57]+XR__[57])/2;
    XM__[58] = (XL__[58]+XR__[58])/2;
    XM__[59] = (XL__[59]+XR__[59])/2;
    XM__[60] = (XL__[60]+XR__[60])/2;
    XM__[61] = (XL__[61]+XR__[61])/2;
    XM__[62] = (XL__[62]+XR__[62])/2;
    XM__[63] = (XL__[63]+XR__[63])/2;
    XM__[64] = (XL__[64]+XR__[64])/2;
    XM__[65] = (XL__[65]+XR__[65])/2;
    XM__[66] = (XL__[66]+XR__[66])/2;
    XM__[67] = (XL__[67]+XR__[67])/2;
    XM__[68] = (XL__[68]+XR__[68])/2;
    XM__[69] = (XL__[69]+XR__[69])/2;
    XM__[70] = (XL__[70]+XR__[70])/2;
    XM__[71] = (XL__[71]+XR__[71])/2;
    XM__[72] = (XL__[72]+XR__[72])/2;
    XM__[73] = (XL__[73]+XR__[73])/2;
    XM__[74] = (XL__[74]+XR__[74])/2;
    XM__[75] = (XL__[75]+XR__[75])/2;
    XM__[76] = (XL__[76]+XR__[76])/2;
    XM__[77] = (XL__[77]+XR__[77])/2;
    XM__[78] = (XL__[78]+XR__[78])/2;
    XM__[79] = (XL__[79]+XR__[79])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    V__[7] = __INV_DZETA*(XR__[7]-XL__[7]);
    V__[8] = __INV_DZETA*(XR__[8]-XL__[8]);
    V__[9] = __INV_DZETA*(XR__[9]-XL__[9]);
    V__[10] = __INV_DZETA*(XR__[10]-XL__[10]);
    V__[11] = __INV_DZETA*(XR__[11]-XL__[11]);
    V__[12] = __INV_DZETA*(XR__[12]-XL__[12]);
    V__[13] = __INV_DZETA*(XR__[13]-XL__[13]);
    V__[14] = __INV_DZETA*(XR__[14]-XL__[14]);
    V__[15] = __INV_DZETA*(XR__[15]-XL__[15]);
    V__[16] = __INV_DZETA*(XR__[16]-XL__[16]);
    V__[17] = __INV_DZETA*(XR__[17]-XL__[17]);
    V__[18] = __INV_DZETA*(XR__[18]-XL__[18]);
    V__[19] = __INV_DZETA*(XR__[19]-XL__[19]);
    V__[20] = __INV_DZETA*(XR__[20]-XL__[20]);
    V__[21] = __INV_DZETA*(XR__[21]-XL__[21]);
    V__[22] = __INV_DZETA*(XR__[22]-XL__[22]);
    V__[23] = __INV_DZETA*(XR__[23]-XL__[23]);
    V__[24] = __INV_DZETA*(XR__[24]-XL__[24]);
    V__[25] = __INV_DZETA*(XR__[25]-XL__[25]);
    V__[26] = __INV_DZETA*(XR__[26]-XL__[26]);
    V__[27] = __INV_DZETA*(XR__[27]-XL__[27]);
    V__[28] = __INV_DZETA*(XR__[28]-XL__[28]);
    V__[29] = __INV_DZETA*(XR__[29]-XL__[29]);
    V__[30] = __INV_DZETA*(XR__[30]-XL__[30]);
    V__[31] = __INV_DZETA*(XR__[31]-XL__[31]);
    V__[32] = __INV_DZETA*(XR__[32]-XL__[32]);
    V__[33] = __INV_DZETA*(XR__[33]-XL__[33]);
    V__[34] = __INV_DZETA*(XR__[34]-XL__[34]);
    V__[35] = __INV_DZETA*(XR__[35]-XL__[35]);
    V__[36] = __INV_DZETA*(XR__[36]-XL__[36]);
    V__[37] = __INV_DZETA*(XR__[37]-XL__[37]);
    V__[38] = __INV_DZETA*(XR__[38]-XL__[38]);
    V__[39] = __INV_DZETA*(XR__[39]-XL__[39]);
    V__[40] = __INV_DZETA*(XR__[40]-XL__[40]);
    V__[41] = __INV_DZETA*(XR__[41]-XL__[41]);
    V__[42] = __INV_DZETA*(XR__[42]-XL__[42]);
    V__[43] = __INV_DZETA*(XR__[43]-XL__[43]);
    V__[44] = __INV_DZETA*(XR__[44]-XL__[44]);
    V__[45] = __INV_DZETA*(XR__[45]-XL__[45]);
    V__[46] = __INV_DZETA*(XR__[46]-XL__[46]);
    V__[47] = __INV_DZETA*(XR__[47]-XL__[47]);
    V__[48] = __INV_DZETA*(XR__[48]-XL__[48]);
    V__[49] = __INV_DZETA*(XR__[49]-XL__[49]);
    V__[50] = __INV_DZETA*(XR__[50]-XL__[50]);
    V__[51] = __INV_DZETA*(XR__[51]-XL__[51]);
    V__[52] = __INV_DZETA*(XR__[52]-XL__[52]);
    V__[53] = __INV_DZETA*(XR__[53]-XL__[53]);
    V__[54] = __INV_DZETA*(XR__[54]-XL__[54]);
    V__[55] = __INV_DZETA*(XR__[55]-XL__[55]);
    V__[56] = __INV_DZETA*(XR__[56]-XL__[56]);
    V__[57] = __INV_DZETA*(XR__[57]-XL__[57]);
    V__[58] = __INV_DZETA*(XR__[58]-XL__[58]);
    V__[59] = __INV_DZETA*(XR__[59]-XL__[59]);
    V__[60] = __INV_DZETA*(XR__[60]-XL__[60]);
    V__[61] = __INV_DZETA*(XR__[61]-XL__[61]);
    V__[62] = __INV_DZETA*(XR__[62]-XL__[62]);
    V__[63] = __INV_DZETA*(XR__[63]-XL__[63]);
    V__[64] = __INV_DZETA*(XR__[64]-XL__[64]);
    V__[65] = __INV_DZETA*(XR__[65]-XL__[65]);
    V__[66] = __INV_DZETA*(XR__[66]-XL__[66]);
    V__[67] = __INV_DZETA*(XR__[67]-XL__[67]);
    V__[68] = __INV_DZETA*(XR__[68]-XL__[68]);
    V__[69] = __INV_DZETA*(XR__[69]-XL__[69]);
    V__[70] = __INV_DZETA*(XR__[70]-XL__[70]);
    V__[71] = __INV_DZETA*(XR__[71]-XL__[71]);
    V__[72] = __INV_DZETA*(XR__[72]-XL__[72]);
    V__[73] = __INV_DZETA*(XR__[73]-XL__[73]);
    V__[74] = __INV_DZETA*(XR__[74]-XL__[74]);
    V__[75] = __INV_DZETA*(XR__[75]-XL__[75]);
    V__[76] = __INV_DZETA*(XR__[76]-XL__[76]);
    V__[77] = __INV_DZETA*(XR__[77]-XL__[77]);
    V__[78] = __INV_DZETA*(XR__[78]-XL__[78]);
    V__[79] = __INV_DZETA*(XR__[79]-XL__[79]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0] - XM__[20];
    result__[ 1   ] = V__[1] - XM__[21];
    result__[ 2   ] = V__[2] - XM__[22];
    result__[ 3   ] = V__[3] - XM__[23];
    result__[ 4   ] = V__[4] - XM__[24];
    result__[ 5   ] = V__[5] - XM__[25];
    result__[ 6   ] = V__[6] - XM__[26];
    result__[ 7   ] = V__[7] - XM__[27];
    result__[ 8   ] = V__[8] - XM__[28];
    result__[ 9   ] = V__[9] - XM__[29];
    result__[ 10  ] = V__[10] - XM__[30];
    result__[ 11  ] = V__[11] - XM__[31];
    result__[ 12  ] = V__[12] - XM__[32];
    result__[ 13  ] = V__[13] - XM__[33];
    result__[ 14  ] = V__[14] - XM__[34];
    result__[ 15  ] = V__[15] - XM__[35];
    result__[ 16  ] = V__[16] - XM__[36];
    result__[ 17  ] = V__[17] - XM__[37];
    result__[ 18  ] = V__[18] - XM__[38];
    result__[ 19  ] = V__[19] - XM__[39];
    real_type t43  = sin(XM__[0]);
    real_type t44  = P__[iP_u1];
    result__[ 20  ] = V__[20] - t43 - t44;
    real_type t47  = sin(XM__[1]);
    real_type t48  = P__[iP_u2];
    result__[ 21  ] = V__[21] - t47 - t48;
    real_type t51  = sin(XM__[2]);
    real_type t52  = P__[iP_u3];
    result__[ 22  ] = V__[22] - t51 - t52;
    real_type t55  = sin(XM__[3]);
    real_type t56  = P__[iP_u4];
    result__[ 23  ] = V__[23] - t55 - t56;
    real_type t59  = sin(XM__[4]);
    real_type t60  = P__[iP_u5];
    result__[ 24  ] = V__[24] - t59 - t60;
    real_type t63  = sin(XM__[5]);
    real_type t64  = P__[iP_u6];
    result__[ 25  ] = V__[25] - t63 - t64;
    real_type t67  = sin(XM__[6]);
    real_type t68  = P__[iP_u7];
    result__[ 26  ] = V__[26] - t67 - t68;
    real_type t71  = sin(XM__[7]);
    real_type t72  = P__[iP_u8];
    result__[ 27  ] = V__[27] - t71 - t72;
    real_type t75  = sin(XM__[8]);
    real_type t76  = P__[iP_u9];
    result__[ 28  ] = V__[28] - t75 - t76;
    real_type t79  = sin(XM__[9]);
    real_type t80  = P__[iP_u10];
    result__[ 29  ] = V__[29] - t79 - t80;
    real_type t83  = sin(XM__[10]);
    real_type t84  = P__[iP_u11];
    result__[ 30  ] = V__[30] - t83 - t84;
    real_type t87  = sin(XM__[11]);
    real_type t88  = P__[iP_u12];
    result__[ 31  ] = V__[31] - t87 - t88;
    real_type t91  = sin(XM__[12]);
    real_type t92  = P__[iP_u13];
    result__[ 32  ] = V__[32] - t91 - t92;
    real_type t95  = sin(XM__[13]);
    real_type t96  = P__[iP_u14];
    result__[ 33  ] = V__[33] - t95 - t96;
    real_type t99  = sin(XM__[14]);
    real_type t100 = P__[iP_u15];
    result__[ 34  ] = V__[34] - t99 - t100;
    real_type t103 = sin(XM__[15]);
    real_type t104 = P__[iP_u16];
    result__[ 35  ] = V__[35] - t103 - t104;
    real_type t107 = sin(XM__[16]);
    real_type t108 = P__[iP_u17];
    result__[ 36  ] = V__[36] - t107 - t108;
    real_type t111 = sin(XM__[17]);
    real_type t112 = P__[iP_u18];
    result__[ 37  ] = V__[37] - t111 - t112;
    real_type t115 = sin(XM__[18]);
    real_type t116 = P__[iP_u19];
    result__[ 38  ] = V__[38] - t115 - t116;
    real_type t119 = sin(XM__[19]);
    real_type t120 = P__[iP_u20];
    result__[ 39  ] = V__[39] - t119 - t120;
    real_type t124 = QM__[0];
    real_type t125 = sin(t124);
    result__[ 40  ] = V__[40] - 0.12e1 * XM__[60] - 0.1e0 * t125;
    real_type t131 = sin(t124 + 1);
    result__[ 41  ] = V__[41] - 0.12e1 * XM__[61] - 0.1e0 * t131;
    real_type t137 = sin(t124 + 2);
    result__[ 42  ] = V__[42] - 0.12e1 * XM__[62] - 0.1e0 * t137;
    real_type t143 = sin(t124 + 3);
    result__[ 43  ] = V__[43] - 0.12e1 * XM__[63] - 0.1e0 * t143;
    real_type t149 = sin(t124 + 4);
    result__[ 44  ] = V__[44] - 0.12e1 * XM__[64] - 0.1e0 * t149;
    real_type t155 = sin(t124 + 5);
    result__[ 45  ] = V__[45] - 0.12e1 * XM__[65] - 0.1e0 * t155;
    real_type t161 = sin(t124 + 6);
    result__[ 46  ] = V__[46] - 0.12e1 * XM__[66] - 0.1e0 * t161;
    real_type t167 = sin(t124 + 7);
    result__[ 47  ] = V__[47] - 0.12e1 * XM__[67] - 0.1e0 * t167;
    real_type t173 = sin(t124 + 8);
    result__[ 48  ] = V__[48] - 0.12e1 * XM__[68] - 0.1e0 * t173;
    real_type t179 = sin(t124 + 9);
    result__[ 49  ] = V__[49] - 0.12e1 * XM__[69] - 0.1e0 * t179;
    real_type t185 = sin(t124 + 10);
    result__[ 50  ] = V__[50] - 0.12e1 * XM__[70] - 0.1e0 * t185;
    real_type t191 = sin(t124 + 11);
    result__[ 51  ] = V__[51] - 0.12e1 * XM__[71] - 0.1e0 * t191;
    real_type t197 = sin(t124 + 12);
    result__[ 52  ] = V__[52] - 0.12e1 * XM__[72] - 0.1e0 * t197;
    real_type t203 = sin(t124 + 13);
    result__[ 53  ] = V__[53] - 0.12e1 * XM__[73] - 0.1e0 * t203;
    real_type t209 = sin(t124 + 14);
    result__[ 54  ] = V__[54] - 0.12e1 * XM__[74] - 0.1e0 * t209;
    real_type t215 = sin(t124 + 15);
    result__[ 55  ] = V__[55] - 0.12e1 * XM__[75] - 0.1e0 * t215;
    real_type t221 = sin(t124 + 16);
    result__[ 56  ] = V__[56] - 0.12e1 * XM__[76] - 0.1e0 * t221;
    real_type t227 = sin(t124 + 17);
    result__[ 57  ] = V__[57] - 0.12e1 * XM__[77] - 0.1e0 * t227;
    real_type t233 = sin(t124 + 18);
    result__[ 58  ] = V__[58] - 0.12e1 * XM__[78] - 0.1e0 * t233;
    real_type t239 = sin(t124 + 19);
    result__[ 59  ] = V__[59] - 0.12e1 * XM__[79] - 0.1e0 * t239;
    real_type t243 = sin(XM__[40]);
    result__[ 60  ] = V__[60] - 0.2e0 * t243 - t44;
    real_type t247 = sin(XM__[41]);
    result__[ 61  ] = V__[61] - 0.2e0 * t247 - t48;
    real_type t251 = sin(XM__[42]);
    result__[ 62  ] = V__[62] - 0.2e0 * t251 - t52;
    real_type t255 = sin(XM__[43]);
    result__[ 63  ] = V__[63] - 0.2e0 * t255 - t56;
    real_type t259 = sin(XM__[44]);
    result__[ 64  ] = V__[64] - 0.2e0 * t259 - t60;
    real_type t263 = sin(XM__[45]);
    result__[ 65  ] = V__[65] - 0.2e0 * t263 - t64;
    real_type t267 = sin(XM__[46]);
    result__[ 66  ] = V__[66] - 0.2e0 * t267 - t68;
    real_type t271 = sin(XM__[47]);
    result__[ 67  ] = V__[67] - 0.2e0 * t271 - t72;
    real_type t275 = sin(XM__[48]);
    result__[ 68  ] = V__[68] - 0.2e0 * t275 - t76;
    real_type t279 = sin(XM__[49]);
    result__[ 69  ] = V__[69] - 0.2e0 * t279 - t80;
    real_type t283 = sin(XM__[50]);
    result__[ 70  ] = V__[70] - 0.2e0 * t283 - t84;
    real_type t287 = sin(XM__[51]);
    result__[ 71  ] = V__[71] - 0.2e0 * t287 - t88;
    real_type t291 = sin(XM__[52]);
    result__[ 72  ] = V__[72] - 0.2e0 * t291 - t92;
    real_type t295 = sin(XM__[53]);
    result__[ 73  ] = V__[73] - 0.2e0 * t295 - t96;
    real_type t299 = sin(XM__[54]);
    result__[ 74  ] = V__[74] - 0.2e0 * t299 - t100;
    real_type t303 = sin(XM__[55]);
    result__[ 75  ] = V__[75] - 0.2e0 * t303 - t104;
    real_type t307 = sin(XM__[56]);
    result__[ 76  ] = V__[76] - 0.2e0 * t307 - t108;
    real_type t311 = sin(XM__[57]);
    result__[ 77  ] = V__[77] - 0.2e0 * t311 - t112;
    real_type t315 = sin(XM__[58]);
    result__[ 78  ] = V__[78] - 0.2e0 * t315 - t116;
    real_type t319 = sin(XM__[59]);
    result__[ 79  ] = V__[79] - 0.2e0 * t319 - t120;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::Dfd_odeDxxpu_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::Dfd_odeDxxpu_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::Dfd_odeDxxpu_nnz()     const { return 360; }

  void
  ICLOCS_ContinuousMP::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 20  ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 80  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 100 ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 21  ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 81  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 101 ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 22  ;
    iIndex[10] = 2   ; jIndex[10] = 82  ;
    iIndex[11] = 2   ; jIndex[11] = 102 ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 3   ; jIndex[13] = 23  ;
    iIndex[14] = 3   ; jIndex[14] = 83  ;
    iIndex[15] = 3   ; jIndex[15] = 103 ;
    iIndex[16] = 4   ; jIndex[16] = 4   ;
    iIndex[17] = 4   ; jIndex[17] = 24  ;
    iIndex[18] = 4   ; jIndex[18] = 84  ;
    iIndex[19] = 4   ; jIndex[19] = 104 ;
    iIndex[20] = 5   ; jIndex[20] = 5   ;
    iIndex[21] = 5   ; jIndex[21] = 25  ;
    iIndex[22] = 5   ; jIndex[22] = 85  ;
    iIndex[23] = 5   ; jIndex[23] = 105 ;
    iIndex[24] = 6   ; jIndex[24] = 6   ;
    iIndex[25] = 6   ; jIndex[25] = 26  ;
    iIndex[26] = 6   ; jIndex[26] = 86  ;
    iIndex[27] = 6   ; jIndex[27] = 106 ;
    iIndex[28] = 7   ; jIndex[28] = 7   ;
    iIndex[29] = 7   ; jIndex[29] = 27  ;
    iIndex[30] = 7   ; jIndex[30] = 87  ;
    iIndex[31] = 7   ; jIndex[31] = 107 ;
    iIndex[32] = 8   ; jIndex[32] = 8   ;
    iIndex[33] = 8   ; jIndex[33] = 28  ;
    iIndex[34] = 8   ; jIndex[34] = 88  ;
    iIndex[35] = 8   ; jIndex[35] = 108 ;
    iIndex[36] = 9   ; jIndex[36] = 9   ;
    iIndex[37] = 9   ; jIndex[37] = 29  ;
    iIndex[38] = 9   ; jIndex[38] = 89  ;
    iIndex[39] = 9   ; jIndex[39] = 109 ;
    iIndex[40] = 10  ; jIndex[40] = 10  ;
    iIndex[41] = 10  ; jIndex[41] = 30  ;
    iIndex[42] = 10  ; jIndex[42] = 90  ;
    iIndex[43] = 10  ; jIndex[43] = 110 ;
    iIndex[44] = 11  ; jIndex[44] = 11  ;
    iIndex[45] = 11  ; jIndex[45] = 31  ;
    iIndex[46] = 11  ; jIndex[46] = 91  ;
    iIndex[47] = 11  ; jIndex[47] = 111 ;
    iIndex[48] = 12  ; jIndex[48] = 12  ;
    iIndex[49] = 12  ; jIndex[49] = 32  ;
    iIndex[50] = 12  ; jIndex[50] = 92  ;
    iIndex[51] = 12  ; jIndex[51] = 112 ;
    iIndex[52] = 13  ; jIndex[52] = 13  ;
    iIndex[53] = 13  ; jIndex[53] = 33  ;
    iIndex[54] = 13  ; jIndex[54] = 93  ;
    iIndex[55] = 13  ; jIndex[55] = 113 ;
    iIndex[56] = 14  ; jIndex[56] = 14  ;
    iIndex[57] = 14  ; jIndex[57] = 34  ;
    iIndex[58] = 14  ; jIndex[58] = 94  ;
    iIndex[59] = 14  ; jIndex[59] = 114 ;
    iIndex[60] = 15  ; jIndex[60] = 15  ;
    iIndex[61] = 15  ; jIndex[61] = 35  ;
    iIndex[62] = 15  ; jIndex[62] = 95  ;
    iIndex[63] = 15  ; jIndex[63] = 115 ;
    iIndex[64] = 16  ; jIndex[64] = 16  ;
    iIndex[65] = 16  ; jIndex[65] = 36  ;
    iIndex[66] = 16  ; jIndex[66] = 96  ;
    iIndex[67] = 16  ; jIndex[67] = 116 ;
    iIndex[68] = 17  ; jIndex[68] = 17  ;
    iIndex[69] = 17  ; jIndex[69] = 37  ;
    iIndex[70] = 17  ; jIndex[70] = 97  ;
    iIndex[71] = 17  ; jIndex[71] = 117 ;
    iIndex[72] = 18  ; jIndex[72] = 18  ;
    iIndex[73] = 18  ; jIndex[73] = 38  ;
    iIndex[74] = 18  ; jIndex[74] = 98  ;
    iIndex[75] = 18  ; jIndex[75] = 118 ;
    iIndex[76] = 19  ; jIndex[76] = 19  ;
    iIndex[77] = 19  ; jIndex[77] = 39  ;
    iIndex[78] = 19  ; jIndex[78] = 99  ;
    iIndex[79] = 19  ; jIndex[79] = 119 ;
    iIndex[80] = 20  ; jIndex[80] = 0   ;
    iIndex[81] = 20  ; jIndex[81] = 20  ;
    iIndex[82] = 20  ; jIndex[82] = 80  ;
    iIndex[83] = 20  ; jIndex[83] = 100 ;
    iIndex[84] = 20  ; jIndex[84] = 160 ;
    iIndex[85] = 21  ; jIndex[85] = 1   ;
    iIndex[86] = 21  ; jIndex[86] = 21  ;
    iIndex[87] = 21  ; jIndex[87] = 81  ;
    iIndex[88] = 21  ; jIndex[88] = 101 ;
    iIndex[89] = 21  ; jIndex[89] = 161 ;
    iIndex[90] = 22  ; jIndex[90] = 2   ;
    iIndex[91] = 22  ; jIndex[91] = 22  ;
    iIndex[92] = 22  ; jIndex[92] = 82  ;
    iIndex[93] = 22  ; jIndex[93] = 102 ;
    iIndex[94] = 22  ; jIndex[94] = 162 ;
    iIndex[95] = 23  ; jIndex[95] = 3   ;
    iIndex[96] = 23  ; jIndex[96] = 23  ;
    iIndex[97] = 23  ; jIndex[97] = 83  ;
    iIndex[98] = 23  ; jIndex[98] = 103 ;
    iIndex[99] = 23  ; jIndex[99] = 163 ;
    iIndex[100] = 24  ; jIndex[100] = 4   ;
    iIndex[101] = 24  ; jIndex[101] = 24  ;
    iIndex[102] = 24  ; jIndex[102] = 84  ;
    iIndex[103] = 24  ; jIndex[103] = 104 ;
    iIndex[104] = 24  ; jIndex[104] = 164 ;
    iIndex[105] = 25  ; jIndex[105] = 5   ;
    iIndex[106] = 25  ; jIndex[106] = 25  ;
    iIndex[107] = 25  ; jIndex[107] = 85  ;
    iIndex[108] = 25  ; jIndex[108] = 105 ;
    iIndex[109] = 25  ; jIndex[109] = 165 ;
    iIndex[110] = 26  ; jIndex[110] = 6   ;
    iIndex[111] = 26  ; jIndex[111] = 26  ;
    iIndex[112] = 26  ; jIndex[112] = 86  ;
    iIndex[113] = 26  ; jIndex[113] = 106 ;
    iIndex[114] = 26  ; jIndex[114] = 166 ;
    iIndex[115] = 27  ; jIndex[115] = 7   ;
    iIndex[116] = 27  ; jIndex[116] = 27  ;
    iIndex[117] = 27  ; jIndex[117] = 87  ;
    iIndex[118] = 27  ; jIndex[118] = 107 ;
    iIndex[119] = 27  ; jIndex[119] = 167 ;
    iIndex[120] = 28  ; jIndex[120] = 8   ;
    iIndex[121] = 28  ; jIndex[121] = 28  ;
    iIndex[122] = 28  ; jIndex[122] = 88  ;
    iIndex[123] = 28  ; jIndex[123] = 108 ;
    iIndex[124] = 28  ; jIndex[124] = 168 ;
    iIndex[125] = 29  ; jIndex[125] = 9   ;
    iIndex[126] = 29  ; jIndex[126] = 29  ;
    iIndex[127] = 29  ; jIndex[127] = 89  ;
    iIndex[128] = 29  ; jIndex[128] = 109 ;
    iIndex[129] = 29  ; jIndex[129] = 169 ;
    iIndex[130] = 30  ; jIndex[130] = 10  ;
    iIndex[131] = 30  ; jIndex[131] = 30  ;
    iIndex[132] = 30  ; jIndex[132] = 90  ;
    iIndex[133] = 30  ; jIndex[133] = 110 ;
    iIndex[134] = 30  ; jIndex[134] = 170 ;
    iIndex[135] = 31  ; jIndex[135] = 11  ;
    iIndex[136] = 31  ; jIndex[136] = 31  ;
    iIndex[137] = 31  ; jIndex[137] = 91  ;
    iIndex[138] = 31  ; jIndex[138] = 111 ;
    iIndex[139] = 31  ; jIndex[139] = 171 ;
    iIndex[140] = 32  ; jIndex[140] = 12  ;
    iIndex[141] = 32  ; jIndex[141] = 32  ;
    iIndex[142] = 32  ; jIndex[142] = 92  ;
    iIndex[143] = 32  ; jIndex[143] = 112 ;
    iIndex[144] = 32  ; jIndex[144] = 172 ;
    iIndex[145] = 33  ; jIndex[145] = 13  ;
    iIndex[146] = 33  ; jIndex[146] = 33  ;
    iIndex[147] = 33  ; jIndex[147] = 93  ;
    iIndex[148] = 33  ; jIndex[148] = 113 ;
    iIndex[149] = 33  ; jIndex[149] = 173 ;
    iIndex[150] = 34  ; jIndex[150] = 14  ;
    iIndex[151] = 34  ; jIndex[151] = 34  ;
    iIndex[152] = 34  ; jIndex[152] = 94  ;
    iIndex[153] = 34  ; jIndex[153] = 114 ;
    iIndex[154] = 34  ; jIndex[154] = 174 ;
    iIndex[155] = 35  ; jIndex[155] = 15  ;
    iIndex[156] = 35  ; jIndex[156] = 35  ;
    iIndex[157] = 35  ; jIndex[157] = 95  ;
    iIndex[158] = 35  ; jIndex[158] = 115 ;
    iIndex[159] = 35  ; jIndex[159] = 175 ;
    iIndex[160] = 36  ; jIndex[160] = 16  ;
    iIndex[161] = 36  ; jIndex[161] = 36  ;
    iIndex[162] = 36  ; jIndex[162] = 96  ;
    iIndex[163] = 36  ; jIndex[163] = 116 ;
    iIndex[164] = 36  ; jIndex[164] = 176 ;
    iIndex[165] = 37  ; jIndex[165] = 17  ;
    iIndex[166] = 37  ; jIndex[166] = 37  ;
    iIndex[167] = 37  ; jIndex[167] = 97  ;
    iIndex[168] = 37  ; jIndex[168] = 117 ;
    iIndex[169] = 37  ; jIndex[169] = 177 ;
    iIndex[170] = 38  ; jIndex[170] = 18  ;
    iIndex[171] = 38  ; jIndex[171] = 38  ;
    iIndex[172] = 38  ; jIndex[172] = 98  ;
    iIndex[173] = 38  ; jIndex[173] = 118 ;
    iIndex[174] = 38  ; jIndex[174] = 178 ;
    iIndex[175] = 39  ; jIndex[175] = 19  ;
    iIndex[176] = 39  ; jIndex[176] = 39  ;
    iIndex[177] = 39  ; jIndex[177] = 99  ;
    iIndex[178] = 39  ; jIndex[178] = 119 ;
    iIndex[179] = 39  ; jIndex[179] = 179 ;
    iIndex[180] = 40  ; jIndex[180] = 40  ;
    iIndex[181] = 40  ; jIndex[181] = 60  ;
    iIndex[182] = 40  ; jIndex[182] = 120 ;
    iIndex[183] = 40  ; jIndex[183] = 140 ;
    iIndex[184] = 41  ; jIndex[184] = 41  ;
    iIndex[185] = 41  ; jIndex[185] = 61  ;
    iIndex[186] = 41  ; jIndex[186] = 121 ;
    iIndex[187] = 41  ; jIndex[187] = 141 ;
    iIndex[188] = 42  ; jIndex[188] = 42  ;
    iIndex[189] = 42  ; jIndex[189] = 62  ;
    iIndex[190] = 42  ; jIndex[190] = 122 ;
    iIndex[191] = 42  ; jIndex[191] = 142 ;
    iIndex[192] = 43  ; jIndex[192] = 43  ;
    iIndex[193] = 43  ; jIndex[193] = 63  ;
    iIndex[194] = 43  ; jIndex[194] = 123 ;
    iIndex[195] = 43  ; jIndex[195] = 143 ;
    iIndex[196] = 44  ; jIndex[196] = 44  ;
    iIndex[197] = 44  ; jIndex[197] = 64  ;
    iIndex[198] = 44  ; jIndex[198] = 124 ;
    iIndex[199] = 44  ; jIndex[199] = 144 ;
    iIndex[200] = 45  ; jIndex[200] = 45  ;
    iIndex[201] = 45  ; jIndex[201] = 65  ;
    iIndex[202] = 45  ; jIndex[202] = 125 ;
    iIndex[203] = 45  ; jIndex[203] = 145 ;
    iIndex[204] = 46  ; jIndex[204] = 46  ;
    iIndex[205] = 46  ; jIndex[205] = 66  ;
    iIndex[206] = 46  ; jIndex[206] = 126 ;
    iIndex[207] = 46  ; jIndex[207] = 146 ;
    iIndex[208] = 47  ; jIndex[208] = 47  ;
    iIndex[209] = 47  ; jIndex[209] = 67  ;
    iIndex[210] = 47  ; jIndex[210] = 127 ;
    iIndex[211] = 47  ; jIndex[211] = 147 ;
    iIndex[212] = 48  ; jIndex[212] = 48  ;
    iIndex[213] = 48  ; jIndex[213] = 68  ;
    iIndex[214] = 48  ; jIndex[214] = 128 ;
    iIndex[215] = 48  ; jIndex[215] = 148 ;
    iIndex[216] = 49  ; jIndex[216] = 49  ;
    iIndex[217] = 49  ; jIndex[217] = 69  ;
    iIndex[218] = 49  ; jIndex[218] = 129 ;
    iIndex[219] = 49  ; jIndex[219] = 149 ;
    iIndex[220] = 50  ; jIndex[220] = 50  ;
    iIndex[221] = 50  ; jIndex[221] = 70  ;
    iIndex[222] = 50  ; jIndex[222] = 130 ;
    iIndex[223] = 50  ; jIndex[223] = 150 ;
    iIndex[224] = 51  ; jIndex[224] = 51  ;
    iIndex[225] = 51  ; jIndex[225] = 71  ;
    iIndex[226] = 51  ; jIndex[226] = 131 ;
    iIndex[227] = 51  ; jIndex[227] = 151 ;
    iIndex[228] = 52  ; jIndex[228] = 52  ;
    iIndex[229] = 52  ; jIndex[229] = 72  ;
    iIndex[230] = 52  ; jIndex[230] = 132 ;
    iIndex[231] = 52  ; jIndex[231] = 152 ;
    iIndex[232] = 53  ; jIndex[232] = 53  ;
    iIndex[233] = 53  ; jIndex[233] = 73  ;
    iIndex[234] = 53  ; jIndex[234] = 133 ;
    iIndex[235] = 53  ; jIndex[235] = 153 ;
    iIndex[236] = 54  ; jIndex[236] = 54  ;
    iIndex[237] = 54  ; jIndex[237] = 74  ;
    iIndex[238] = 54  ; jIndex[238] = 134 ;
    iIndex[239] = 54  ; jIndex[239] = 154 ;
    iIndex[240] = 55  ; jIndex[240] = 55  ;
    iIndex[241] = 55  ; jIndex[241] = 75  ;
    iIndex[242] = 55  ; jIndex[242] = 135 ;
    iIndex[243] = 55  ; jIndex[243] = 155 ;
    iIndex[244] = 56  ; jIndex[244] = 56  ;
    iIndex[245] = 56  ; jIndex[245] = 76  ;
    iIndex[246] = 56  ; jIndex[246] = 136 ;
    iIndex[247] = 56  ; jIndex[247] = 156 ;
    iIndex[248] = 57  ; jIndex[248] = 57  ;
    iIndex[249] = 57  ; jIndex[249] = 77  ;
    iIndex[250] = 57  ; jIndex[250] = 137 ;
    iIndex[251] = 57  ; jIndex[251] = 157 ;
    iIndex[252] = 58  ; jIndex[252] = 58  ;
    iIndex[253] = 58  ; jIndex[253] = 78  ;
    iIndex[254] = 58  ; jIndex[254] = 138 ;
    iIndex[255] = 58  ; jIndex[255] = 158 ;
    iIndex[256] = 59  ; jIndex[256] = 59  ;
    iIndex[257] = 59  ; jIndex[257] = 79  ;
    iIndex[258] = 59  ; jIndex[258] = 139 ;
    iIndex[259] = 59  ; jIndex[259] = 159 ;
    iIndex[260] = 60  ; jIndex[260] = 40  ;
    iIndex[261] = 60  ; jIndex[261] = 60  ;
    iIndex[262] = 60  ; jIndex[262] = 120 ;
    iIndex[263] = 60  ; jIndex[263] = 140 ;
    iIndex[264] = 60  ; jIndex[264] = 160 ;
    iIndex[265] = 61  ; jIndex[265] = 41  ;
    iIndex[266] = 61  ; jIndex[266] = 61  ;
    iIndex[267] = 61  ; jIndex[267] = 121 ;
    iIndex[268] = 61  ; jIndex[268] = 141 ;
    iIndex[269] = 61  ; jIndex[269] = 161 ;
    iIndex[270] = 62  ; jIndex[270] = 42  ;
    iIndex[271] = 62  ; jIndex[271] = 62  ;
    iIndex[272] = 62  ; jIndex[272] = 122 ;
    iIndex[273] = 62  ; jIndex[273] = 142 ;
    iIndex[274] = 62  ; jIndex[274] = 162 ;
    iIndex[275] = 63  ; jIndex[275] = 43  ;
    iIndex[276] = 63  ; jIndex[276] = 63  ;
    iIndex[277] = 63  ; jIndex[277] = 123 ;
    iIndex[278] = 63  ; jIndex[278] = 143 ;
    iIndex[279] = 63  ; jIndex[279] = 163 ;
    iIndex[280] = 64  ; jIndex[280] = 44  ;
    iIndex[281] = 64  ; jIndex[281] = 64  ;
    iIndex[282] = 64  ; jIndex[282] = 124 ;
    iIndex[283] = 64  ; jIndex[283] = 144 ;
    iIndex[284] = 64  ; jIndex[284] = 164 ;
    iIndex[285] = 65  ; jIndex[285] = 45  ;
    iIndex[286] = 65  ; jIndex[286] = 65  ;
    iIndex[287] = 65  ; jIndex[287] = 125 ;
    iIndex[288] = 65  ; jIndex[288] = 145 ;
    iIndex[289] = 65  ; jIndex[289] = 165 ;
    iIndex[290] = 66  ; jIndex[290] = 46  ;
    iIndex[291] = 66  ; jIndex[291] = 66  ;
    iIndex[292] = 66  ; jIndex[292] = 126 ;
    iIndex[293] = 66  ; jIndex[293] = 146 ;
    iIndex[294] = 66  ; jIndex[294] = 166 ;
    iIndex[295] = 67  ; jIndex[295] = 47  ;
    iIndex[296] = 67  ; jIndex[296] = 67  ;
    iIndex[297] = 67  ; jIndex[297] = 127 ;
    iIndex[298] = 67  ; jIndex[298] = 147 ;
    iIndex[299] = 67  ; jIndex[299] = 167 ;
    iIndex[300] = 68  ; jIndex[300] = 48  ;
    iIndex[301] = 68  ; jIndex[301] = 68  ;
    iIndex[302] = 68  ; jIndex[302] = 128 ;
    iIndex[303] = 68  ; jIndex[303] = 148 ;
    iIndex[304] = 68  ; jIndex[304] = 168 ;
    iIndex[305] = 69  ; jIndex[305] = 49  ;
    iIndex[306] = 69  ; jIndex[306] = 69  ;
    iIndex[307] = 69  ; jIndex[307] = 129 ;
    iIndex[308] = 69  ; jIndex[308] = 149 ;
    iIndex[309] = 69  ; jIndex[309] = 169 ;
    iIndex[310] = 70  ; jIndex[310] = 50  ;
    iIndex[311] = 70  ; jIndex[311] = 70  ;
    iIndex[312] = 70  ; jIndex[312] = 130 ;
    iIndex[313] = 70  ; jIndex[313] = 150 ;
    iIndex[314] = 70  ; jIndex[314] = 170 ;
    iIndex[315] = 71  ; jIndex[315] = 51  ;
    iIndex[316] = 71  ; jIndex[316] = 71  ;
    iIndex[317] = 71  ; jIndex[317] = 131 ;
    iIndex[318] = 71  ; jIndex[318] = 151 ;
    iIndex[319] = 71  ; jIndex[319] = 171 ;
    iIndex[320] = 72  ; jIndex[320] = 52  ;
    iIndex[321] = 72  ; jIndex[321] = 72  ;
    iIndex[322] = 72  ; jIndex[322] = 132 ;
    iIndex[323] = 72  ; jIndex[323] = 152 ;
    iIndex[324] = 72  ; jIndex[324] = 172 ;
    iIndex[325] = 73  ; jIndex[325] = 53  ;
    iIndex[326] = 73  ; jIndex[326] = 73  ;
    iIndex[327] = 73  ; jIndex[327] = 133 ;
    iIndex[328] = 73  ; jIndex[328] = 153 ;
    iIndex[329] = 73  ; jIndex[329] = 173 ;
    iIndex[330] = 74  ; jIndex[330] = 54  ;
    iIndex[331] = 74  ; jIndex[331] = 74  ;
    iIndex[332] = 74  ; jIndex[332] = 134 ;
    iIndex[333] = 74  ; jIndex[333] = 154 ;
    iIndex[334] = 74  ; jIndex[334] = 174 ;
    iIndex[335] = 75  ; jIndex[335] = 55  ;
    iIndex[336] = 75  ; jIndex[336] = 75  ;
    iIndex[337] = 75  ; jIndex[337] = 135 ;
    iIndex[338] = 75  ; jIndex[338] = 155 ;
    iIndex[339] = 75  ; jIndex[339] = 175 ;
    iIndex[340] = 76  ; jIndex[340] = 56  ;
    iIndex[341] = 76  ; jIndex[341] = 76  ;
    iIndex[342] = 76  ; jIndex[342] = 136 ;
    iIndex[343] = 76  ; jIndex[343] = 156 ;
    iIndex[344] = 76  ; jIndex[344] = 176 ;
    iIndex[345] = 77  ; jIndex[345] = 57  ;
    iIndex[346] = 77  ; jIndex[346] = 77  ;
    iIndex[347] = 77  ; jIndex[347] = 137 ;
    iIndex[348] = 77  ; jIndex[348] = 157 ;
    iIndex[349] = 77  ; jIndex[349] = 177 ;
    iIndex[350] = 78  ; jIndex[350] = 58  ;
    iIndex[351] = 78  ; jIndex[351] = 78  ;
    iIndex[352] = 78  ; jIndex[352] = 138 ;
    iIndex[353] = 78  ; jIndex[353] = 158 ;
    iIndex[354] = 78  ; jIndex[354] = 178 ;
    iIndex[355] = 79  ; jIndex[355] = 59  ;
    iIndex[356] = 79  ; jIndex[356] = 79  ;
    iIndex[357] = 79  ; jIndex[357] = 139 ;
    iIndex[358] = 79  ; jIndex[358] = 159 ;
    iIndex[359] = 79  ; jIndex[359] = 179 ;
  }


  void
  ICLOCS_ContinuousMP::Dfd_odeDxxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[80], V__[80];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    XM__[8] = (XL__[8]+XR__[8])/2;
    XM__[9] = (XL__[9]+XR__[9])/2;
    XM__[10] = (XL__[10]+XR__[10])/2;
    XM__[11] = (XL__[11]+XR__[11])/2;
    XM__[12] = (XL__[12]+XR__[12])/2;
    XM__[13] = (XL__[13]+XR__[13])/2;
    XM__[14] = (XL__[14]+XR__[14])/2;
    XM__[15] = (XL__[15]+XR__[15])/2;
    XM__[16] = (XL__[16]+XR__[16])/2;
    XM__[17] = (XL__[17]+XR__[17])/2;
    XM__[18] = (XL__[18]+XR__[18])/2;
    XM__[19] = (XL__[19]+XR__[19])/2;
    XM__[20] = (XL__[20]+XR__[20])/2;
    XM__[21] = (XL__[21]+XR__[21])/2;
    XM__[22] = (XL__[22]+XR__[22])/2;
    XM__[23] = (XL__[23]+XR__[23])/2;
    XM__[24] = (XL__[24]+XR__[24])/2;
    XM__[25] = (XL__[25]+XR__[25])/2;
    XM__[26] = (XL__[26]+XR__[26])/2;
    XM__[27] = (XL__[27]+XR__[27])/2;
    XM__[28] = (XL__[28]+XR__[28])/2;
    XM__[29] = (XL__[29]+XR__[29])/2;
    XM__[30] = (XL__[30]+XR__[30])/2;
    XM__[31] = (XL__[31]+XR__[31])/2;
    XM__[32] = (XL__[32]+XR__[32])/2;
    XM__[33] = (XL__[33]+XR__[33])/2;
    XM__[34] = (XL__[34]+XR__[34])/2;
    XM__[35] = (XL__[35]+XR__[35])/2;
    XM__[36] = (XL__[36]+XR__[36])/2;
    XM__[37] = (XL__[37]+XR__[37])/2;
    XM__[38] = (XL__[38]+XR__[38])/2;
    XM__[39] = (XL__[39]+XR__[39])/2;
    XM__[40] = (XL__[40]+XR__[40])/2;
    XM__[41] = (XL__[41]+XR__[41])/2;
    XM__[42] = (XL__[42]+XR__[42])/2;
    XM__[43] = (XL__[43]+XR__[43])/2;
    XM__[44] = (XL__[44]+XR__[44])/2;
    XM__[45] = (XL__[45]+XR__[45])/2;
    XM__[46] = (XL__[46]+XR__[46])/2;
    XM__[47] = (XL__[47]+XR__[47])/2;
    XM__[48] = (XL__[48]+XR__[48])/2;
    XM__[49] = (XL__[49]+XR__[49])/2;
    XM__[50] = (XL__[50]+XR__[50])/2;
    XM__[51] = (XL__[51]+XR__[51])/2;
    XM__[52] = (XL__[52]+XR__[52])/2;
    XM__[53] = (XL__[53]+XR__[53])/2;
    XM__[54] = (XL__[54]+XR__[54])/2;
    XM__[55] = (XL__[55]+XR__[55])/2;
    XM__[56] = (XL__[56]+XR__[56])/2;
    XM__[57] = (XL__[57]+XR__[57])/2;
    XM__[58] = (XL__[58]+XR__[58])/2;
    XM__[59] = (XL__[59]+XR__[59])/2;
    XM__[60] = (XL__[60]+XR__[60])/2;
    XM__[61] = (XL__[61]+XR__[61])/2;
    XM__[62] = (XL__[62]+XR__[62])/2;
    XM__[63] = (XL__[63]+XR__[63])/2;
    XM__[64] = (XL__[64]+XR__[64])/2;
    XM__[65] = (XL__[65]+XR__[65])/2;
    XM__[66] = (XL__[66]+XR__[66])/2;
    XM__[67] = (XL__[67]+XR__[67])/2;
    XM__[68] = (XL__[68]+XR__[68])/2;
    XM__[69] = (XL__[69]+XR__[69])/2;
    XM__[70] = (XL__[70]+XR__[70])/2;
    XM__[71] = (XL__[71]+XR__[71])/2;
    XM__[72] = (XL__[72]+XR__[72])/2;
    XM__[73] = (XL__[73]+XR__[73])/2;
    XM__[74] = (XL__[74]+XR__[74])/2;
    XM__[75] = (XL__[75]+XR__[75])/2;
    XM__[76] = (XL__[76]+XR__[76])/2;
    XM__[77] = (XL__[77]+XR__[77])/2;
    XM__[78] = (XL__[78]+XR__[78])/2;
    XM__[79] = (XL__[79]+XR__[79])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    V__[7] = __INV_DZETA*(XR__[7]-XL__[7]);
    V__[8] = __INV_DZETA*(XR__[8]-XL__[8]);
    V__[9] = __INV_DZETA*(XR__[9]-XL__[9]);
    V__[10] = __INV_DZETA*(XR__[10]-XL__[10]);
    V__[11] = __INV_DZETA*(XR__[11]-XL__[11]);
    V__[12] = __INV_DZETA*(XR__[12]-XL__[12]);
    V__[13] = __INV_DZETA*(XR__[13]-XL__[13]);
    V__[14] = __INV_DZETA*(XR__[14]-XL__[14]);
    V__[15] = __INV_DZETA*(XR__[15]-XL__[15]);
    V__[16] = __INV_DZETA*(XR__[16]-XL__[16]);
    V__[17] = __INV_DZETA*(XR__[17]-XL__[17]);
    V__[18] = __INV_DZETA*(XR__[18]-XL__[18]);
    V__[19] = __INV_DZETA*(XR__[19]-XL__[19]);
    V__[20] = __INV_DZETA*(XR__[20]-XL__[20]);
    V__[21] = __INV_DZETA*(XR__[21]-XL__[21]);
    V__[22] = __INV_DZETA*(XR__[22]-XL__[22]);
    V__[23] = __INV_DZETA*(XR__[23]-XL__[23]);
    V__[24] = __INV_DZETA*(XR__[24]-XL__[24]);
    V__[25] = __INV_DZETA*(XR__[25]-XL__[25]);
    V__[26] = __INV_DZETA*(XR__[26]-XL__[26]);
    V__[27] = __INV_DZETA*(XR__[27]-XL__[27]);
    V__[28] = __INV_DZETA*(XR__[28]-XL__[28]);
    V__[29] = __INV_DZETA*(XR__[29]-XL__[29]);
    V__[30] = __INV_DZETA*(XR__[30]-XL__[30]);
    V__[31] = __INV_DZETA*(XR__[31]-XL__[31]);
    V__[32] = __INV_DZETA*(XR__[32]-XL__[32]);
    V__[33] = __INV_DZETA*(XR__[33]-XL__[33]);
    V__[34] = __INV_DZETA*(XR__[34]-XL__[34]);
    V__[35] = __INV_DZETA*(XR__[35]-XL__[35]);
    V__[36] = __INV_DZETA*(XR__[36]-XL__[36]);
    V__[37] = __INV_DZETA*(XR__[37]-XL__[37]);
    V__[38] = __INV_DZETA*(XR__[38]-XL__[38]);
    V__[39] = __INV_DZETA*(XR__[39]-XL__[39]);
    V__[40] = __INV_DZETA*(XR__[40]-XL__[40]);
    V__[41] = __INV_DZETA*(XR__[41]-XL__[41]);
    V__[42] = __INV_DZETA*(XR__[42]-XL__[42]);
    V__[43] = __INV_DZETA*(XR__[43]-XL__[43]);
    V__[44] = __INV_DZETA*(XR__[44]-XL__[44]);
    V__[45] = __INV_DZETA*(XR__[45]-XL__[45]);
    V__[46] = __INV_DZETA*(XR__[46]-XL__[46]);
    V__[47] = __INV_DZETA*(XR__[47]-XL__[47]);
    V__[48] = __INV_DZETA*(XR__[48]-XL__[48]);
    V__[49] = __INV_DZETA*(XR__[49]-XL__[49]);
    V__[50] = __INV_DZETA*(XR__[50]-XL__[50]);
    V__[51] = __INV_DZETA*(XR__[51]-XL__[51]);
    V__[52] = __INV_DZETA*(XR__[52]-XL__[52]);
    V__[53] = __INV_DZETA*(XR__[53]-XL__[53]);
    V__[54] = __INV_DZETA*(XR__[54]-XL__[54]);
    V__[55] = __INV_DZETA*(XR__[55]-XL__[55]);
    V__[56] = __INV_DZETA*(XR__[56]-XL__[56]);
    V__[57] = __INV_DZETA*(XR__[57]-XL__[57]);
    V__[58] = __INV_DZETA*(XR__[58]-XL__[58]);
    V__[59] = __INV_DZETA*(XR__[59]-XL__[59]);
    V__[60] = __INV_DZETA*(XR__[60]-XL__[60]);
    V__[61] = __INV_DZETA*(XR__[61]-XL__[61]);
    V__[62] = __INV_DZETA*(XR__[62]-XL__[62]);
    V__[63] = __INV_DZETA*(XR__[63]-XL__[63]);
    V__[64] = __INV_DZETA*(XR__[64]-XL__[64]);
    V__[65] = __INV_DZETA*(XR__[65]-XL__[65]);
    V__[66] = __INV_DZETA*(XR__[66]-XL__[66]);
    V__[67] = __INV_DZETA*(XR__[67]-XL__[67]);
    V__[68] = __INV_DZETA*(XR__[68]-XL__[68]);
    V__[69] = __INV_DZETA*(XR__[69]-XL__[69]);
    V__[70] = __INV_DZETA*(XR__[70]-XL__[70]);
    V__[71] = __INV_DZETA*(XR__[71]-XL__[71]);
    V__[72] = __INV_DZETA*(XR__[72]-XL__[72]);
    V__[73] = __INV_DZETA*(XR__[73]-XL__[73]);
    V__[74] = __INV_DZETA*(XR__[74]-XL__[74]);
    V__[75] = __INV_DZETA*(XR__[75]-XL__[75]);
    V__[76] = __INV_DZETA*(XR__[76]-XL__[76]);
    V__[77] = __INV_DZETA*(XR__[77]-XL__[77]);
    V__[78] = __INV_DZETA*(XR__[78]-XL__[78]);
    V__[79] = __INV_DZETA*(XR__[79]-XL__[79]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    result__[ 1   ] = -0.5e0;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = -0.5e0;
    result__[ 4   ] = result__[0];
    result__[ 5   ] = -0.5e0;
    result__[ 6   ] = __INV_DZETA;
    result__[ 7   ] = -0.5e0;
    result__[ 8   ] = result__[4];
    result__[ 9   ] = -0.5e0;
    result__[ 10  ] = __INV_DZETA;
    result__[ 11  ] = -0.5e0;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = -0.5e0;
    result__[ 14  ] = __INV_DZETA;
    result__[ 15  ] = -0.5e0;
    result__[ 16  ] = result__[12];
    result__[ 17  ] = -0.5e0;
    result__[ 18  ] = __INV_DZETA;
    result__[ 19  ] = -0.5e0;
    result__[ 20  ] = result__[16];
    result__[ 21  ] = -0.5e0;
    result__[ 22  ] = __INV_DZETA;
    result__[ 23  ] = -0.5e0;
    result__[ 24  ] = result__[20];
    result__[ 25  ] = -0.5e0;
    result__[ 26  ] = __INV_DZETA;
    result__[ 27  ] = -0.5e0;
    result__[ 28  ] = result__[24];
    result__[ 29  ] = -0.5e0;
    result__[ 30  ] = __INV_DZETA;
    result__[ 31  ] = -0.5e0;
    result__[ 32  ] = result__[28];
    result__[ 33  ] = -0.5e0;
    result__[ 34  ] = __INV_DZETA;
    result__[ 35  ] = -0.5e0;
    result__[ 36  ] = result__[32];
    result__[ 37  ] = -0.5e0;
    result__[ 38  ] = __INV_DZETA;
    result__[ 39  ] = -0.5e0;
    result__[ 40  ] = result__[36];
    result__[ 41  ] = -0.5e0;
    result__[ 42  ] = __INV_DZETA;
    result__[ 43  ] = -0.5e0;
    result__[ 44  ] = result__[40];
    result__[ 45  ] = -0.5e0;
    result__[ 46  ] = __INV_DZETA;
    result__[ 47  ] = -0.5e0;
    result__[ 48  ] = result__[44];
    result__[ 49  ] = -0.5e0;
    result__[ 50  ] = __INV_DZETA;
    result__[ 51  ] = -0.5e0;
    result__[ 52  ] = result__[48];
    result__[ 53  ] = -0.5e0;
    result__[ 54  ] = __INV_DZETA;
    result__[ 55  ] = -0.5e0;
    result__[ 56  ] = result__[52];
    result__[ 57  ] = -0.5e0;
    result__[ 58  ] = __INV_DZETA;
    result__[ 59  ] = -0.5e0;
    result__[ 60  ] = result__[56];
    result__[ 61  ] = -0.5e0;
    result__[ 62  ] = __INV_DZETA;
    result__[ 63  ] = -0.5e0;
    result__[ 64  ] = result__[60];
    result__[ 65  ] = -0.5e0;
    result__[ 66  ] = __INV_DZETA;
    result__[ 67  ] = -0.5e0;
    result__[ 68  ] = result__[64];
    result__[ 69  ] = -0.5e0;
    result__[ 70  ] = __INV_DZETA;
    result__[ 71  ] = -0.5e0;
    result__[ 72  ] = result__[68];
    result__[ 73  ] = -0.5e0;
    result__[ 74  ] = __INV_DZETA;
    result__[ 75  ] = -0.5e0;
    result__[ 76  ] = result__[72];
    result__[ 77  ] = -0.5e0;
    result__[ 78  ] = __INV_DZETA;
    result__[ 79  ] = -0.5e0;
    real_type t2   = cos(XM__[0]);
    result__[ 80  ] = -0.5e0 * t2;
    result__[ 81  ] = result__[76];
    result__[ 82  ] = result__[80];
    result__[ 83  ] = __INV_DZETA;
    result__[ 84  ] = -1.0;
    real_type t5   = cos(XM__[1]);
    result__[ 85  ] = -0.5e0 * t5;
    result__[ 86  ] = result__[81];
    result__[ 87  ] = result__[85];
    result__[ 88  ] = __INV_DZETA;
    result__[ 89  ] = -1.0;
    real_type t8   = cos(XM__[2]);
    result__[ 90  ] = -0.5e0 * t8;
    result__[ 91  ] = result__[86];
    result__[ 92  ] = result__[90];
    result__[ 93  ] = __INV_DZETA;
    result__[ 94  ] = -1.0;
    real_type t11  = cos(XM__[3]);
    result__[ 95  ] = -0.5e0 * t11;
    result__[ 96  ] = result__[91];
    result__[ 97  ] = result__[95];
    result__[ 98  ] = __INV_DZETA;
    result__[ 99  ] = -1.0;
    real_type t14  = cos(XM__[4]);
    result__[ 100 ] = -0.5e0 * t14;
    result__[ 101 ] = result__[96];
    result__[ 102 ] = result__[100];
    result__[ 103 ] = __INV_DZETA;
    result__[ 104 ] = -1.0;
    real_type t17  = cos(XM__[5]);
    result__[ 105 ] = -0.5e0 * t17;
    result__[ 106 ] = result__[101];
    result__[ 107 ] = result__[105];
    result__[ 108 ] = __INV_DZETA;
    result__[ 109 ] = -1.0;
    real_type t20  = cos(XM__[6]);
    result__[ 110 ] = -0.5e0 * t20;
    result__[ 111 ] = result__[106];
    result__[ 112 ] = result__[110];
    result__[ 113 ] = __INV_DZETA;
    result__[ 114 ] = -1.0;
    real_type t23  = cos(XM__[7]);
    result__[ 115 ] = -0.5e0 * t23;
    result__[ 116 ] = result__[111];
    result__[ 117 ] = result__[115];
    result__[ 118 ] = __INV_DZETA;
    result__[ 119 ] = -1.0;
    real_type t26  = cos(XM__[8]);
    result__[ 120 ] = -0.5e0 * t26;
    result__[ 121 ] = result__[116];
    result__[ 122 ] = result__[120];
    result__[ 123 ] = __INV_DZETA;
    result__[ 124 ] = -1.0;
    real_type t29  = cos(XM__[9]);
    result__[ 125 ] = -0.5e0 * t29;
    result__[ 126 ] = result__[121];
    result__[ 127 ] = result__[125];
    result__[ 128 ] = __INV_DZETA;
    result__[ 129 ] = -1.0;
    real_type t32  = cos(XM__[10]);
    result__[ 130 ] = -0.5e0 * t32;
    result__[ 131 ] = result__[126];
    result__[ 132 ] = result__[130];
    result__[ 133 ] = __INV_DZETA;
    result__[ 134 ] = -1.0;
    real_type t35  = cos(XM__[11]);
    result__[ 135 ] = -0.5e0 * t35;
    result__[ 136 ] = result__[131];
    result__[ 137 ] = result__[135];
    result__[ 138 ] = __INV_DZETA;
    result__[ 139 ] = -1.0;
    real_type t38  = cos(XM__[12]);
    result__[ 140 ] = -0.5e0 * t38;
    result__[ 141 ] = result__[136];
    result__[ 142 ] = result__[140];
    result__[ 143 ] = __INV_DZETA;
    result__[ 144 ] = -1.0;
    real_type t41  = cos(XM__[13]);
    result__[ 145 ] = -0.5e0 * t41;
    result__[ 146 ] = result__[141];
    result__[ 147 ] = result__[145];
    result__[ 148 ] = __INV_DZETA;
    result__[ 149 ] = -1.0;
    real_type t44  = cos(XM__[14]);
    result__[ 150 ] = -0.5e0 * t44;
    result__[ 151 ] = result__[146];
    result__[ 152 ] = result__[150];
    result__[ 153 ] = __INV_DZETA;
    result__[ 154 ] = -1.0;
    real_type t47  = cos(XM__[15]);
    result__[ 155 ] = -0.5e0 * t47;
    result__[ 156 ] = result__[151];
    result__[ 157 ] = result__[155];
    result__[ 158 ] = __INV_DZETA;
    result__[ 159 ] = -1.0;
    real_type t50  = cos(XM__[16]);
    result__[ 160 ] = -0.5e0 * t50;
    result__[ 161 ] = result__[156];
    result__[ 162 ] = result__[160];
    result__[ 163 ] = __INV_DZETA;
    result__[ 164 ] = -1.0;
    real_type t53  = cos(XM__[17]);
    result__[ 165 ] = -0.5e0 * t53;
    result__[ 166 ] = result__[161];
    result__[ 167 ] = result__[165];
    result__[ 168 ] = __INV_DZETA;
    result__[ 169 ] = -1.0;
    real_type t56  = cos(XM__[18]);
    result__[ 170 ] = -0.5e0 * t56;
    result__[ 171 ] = result__[166];
    result__[ 172 ] = result__[170];
    result__[ 173 ] = __INV_DZETA;
    result__[ 174 ] = -1.0;
    real_type t59  = cos(XM__[19]);
    result__[ 175 ] = -0.5e0 * t59;
    result__[ 176 ] = result__[171];
    result__[ 177 ] = result__[175];
    result__[ 178 ] = __INV_DZETA;
    result__[ 179 ] = -1.0;
    result__[ 180 ] = result__[176];
    result__[ 181 ] = -0.60e0;
    result__[ 182 ] = __INV_DZETA;
    result__[ 183 ] = -0.60e0;
    result__[ 184 ] = result__[180];
    result__[ 185 ] = -0.60e0;
    result__[ 186 ] = __INV_DZETA;
    result__[ 187 ] = -0.60e0;
    result__[ 188 ] = result__[184];
    result__[ 189 ] = -0.60e0;
    result__[ 190 ] = __INV_DZETA;
    result__[ 191 ] = -0.60e0;
    result__[ 192 ] = result__[188];
    result__[ 193 ] = -0.60e0;
    result__[ 194 ] = __INV_DZETA;
    result__[ 195 ] = -0.60e0;
    result__[ 196 ] = result__[192];
    result__[ 197 ] = -0.60e0;
    result__[ 198 ] = __INV_DZETA;
    result__[ 199 ] = -0.60e0;
    result__[ 200 ] = result__[196];
    result__[ 201 ] = -0.60e0;
    result__[ 202 ] = __INV_DZETA;
    result__[ 203 ] = -0.60e0;
    result__[ 204 ] = result__[200];
    result__[ 205 ] = -0.60e0;
    result__[ 206 ] = __INV_DZETA;
    result__[ 207 ] = -0.60e0;
    result__[ 208 ] = result__[204];
    result__[ 209 ] = -0.60e0;
    result__[ 210 ] = __INV_DZETA;
    result__[ 211 ] = -0.60e0;
    result__[ 212 ] = result__[208];
    result__[ 213 ] = -0.60e0;
    result__[ 214 ] = __INV_DZETA;
    result__[ 215 ] = -0.60e0;
    result__[ 216 ] = result__[212];
    result__[ 217 ] = -0.60e0;
    result__[ 218 ] = __INV_DZETA;
    result__[ 219 ] = -0.60e0;
    result__[ 220 ] = result__[216];
    result__[ 221 ] = -0.60e0;
    result__[ 222 ] = __INV_DZETA;
    result__[ 223 ] = -0.60e0;
    result__[ 224 ] = result__[220];
    result__[ 225 ] = -0.60e0;
    result__[ 226 ] = __INV_DZETA;
    result__[ 227 ] = -0.60e0;
    result__[ 228 ] = result__[224];
    result__[ 229 ] = -0.60e0;
    result__[ 230 ] = __INV_DZETA;
    result__[ 231 ] = -0.60e0;
    result__[ 232 ] = result__[228];
    result__[ 233 ] = -0.60e0;
    result__[ 234 ] = __INV_DZETA;
    result__[ 235 ] = -0.60e0;
    result__[ 236 ] = result__[232];
    result__[ 237 ] = -0.60e0;
    result__[ 238 ] = __INV_DZETA;
    result__[ 239 ] = -0.60e0;
    result__[ 240 ] = result__[236];
    result__[ 241 ] = -0.60e0;
    result__[ 242 ] = __INV_DZETA;
    result__[ 243 ] = -0.60e0;
    result__[ 244 ] = result__[240];
    result__[ 245 ] = -0.60e0;
    result__[ 246 ] = __INV_DZETA;
    result__[ 247 ] = -0.60e0;
    result__[ 248 ] = result__[244];
    result__[ 249 ] = -0.60e0;
    result__[ 250 ] = __INV_DZETA;
    result__[ 251 ] = -0.60e0;
    result__[ 252 ] = result__[248];
    result__[ 253 ] = -0.60e0;
    result__[ 254 ] = __INV_DZETA;
    result__[ 255 ] = -0.60e0;
    result__[ 256 ] = result__[252];
    result__[ 257 ] = -0.60e0;
    result__[ 258 ] = __INV_DZETA;
    result__[ 259 ] = -0.60e0;
    real_type t62  = cos(XM__[40]);
    result__[ 260 ] = -0.10e0 * t62;
    result__[ 261 ] = result__[256];
    result__[ 262 ] = result__[260];
    result__[ 263 ] = __INV_DZETA;
    result__[ 264 ] = -1.0;
    real_type t65  = cos(XM__[41]);
    result__[ 265 ] = -0.10e0 * t65;
    result__[ 266 ] = result__[261];
    result__[ 267 ] = result__[265];
    result__[ 268 ] = __INV_DZETA;
    result__[ 269 ] = -1.0;
    real_type t68  = cos(XM__[42]);
    result__[ 270 ] = -0.10e0 * t68;
    result__[ 271 ] = result__[266];
    result__[ 272 ] = result__[270];
    result__[ 273 ] = __INV_DZETA;
    result__[ 274 ] = -1.0;
    real_type t71  = cos(XM__[43]);
    result__[ 275 ] = -0.10e0 * t71;
    result__[ 276 ] = result__[271];
    result__[ 277 ] = result__[275];
    result__[ 278 ] = __INV_DZETA;
    result__[ 279 ] = -1.0;
    real_type t74  = cos(XM__[44]);
    result__[ 280 ] = -0.10e0 * t74;
    result__[ 281 ] = result__[276];
    result__[ 282 ] = result__[280];
    result__[ 283 ] = __INV_DZETA;
    result__[ 284 ] = -1.0;
    real_type t77  = cos(XM__[45]);
    result__[ 285 ] = -0.10e0 * t77;
    result__[ 286 ] = result__[281];
    result__[ 287 ] = result__[285];
    result__[ 288 ] = __INV_DZETA;
    result__[ 289 ] = -1.0;
    real_type t80  = cos(XM__[46]);
    result__[ 290 ] = -0.10e0 * t80;
    result__[ 291 ] = result__[286];
    result__[ 292 ] = result__[290];
    result__[ 293 ] = __INV_DZETA;
    result__[ 294 ] = -1.0;
    real_type t83  = cos(XM__[47]);
    result__[ 295 ] = -0.10e0 * t83;
    result__[ 296 ] = result__[291];
    result__[ 297 ] = result__[295];
    result__[ 298 ] = __INV_DZETA;
    result__[ 299 ] = -1.0;
    real_type t86  = cos(XM__[48]);
    result__[ 300 ] = -0.10e0 * t86;
    result__[ 301 ] = result__[296];
    result__[ 302 ] = result__[300];
    result__[ 303 ] = __INV_DZETA;
    result__[ 304 ] = -1.0;
    real_type t89  = cos(XM__[49]);
    result__[ 305 ] = -0.10e0 * t89;
    result__[ 306 ] = result__[301];
    result__[ 307 ] = result__[305];
    result__[ 308 ] = __INV_DZETA;
    result__[ 309 ] = -1.0;
    real_type t92  = cos(XM__[50]);
    result__[ 310 ] = -0.10e0 * t92;
    result__[ 311 ] = result__[306];
    result__[ 312 ] = result__[310];
    result__[ 313 ] = __INV_DZETA;
    result__[ 314 ] = -1.0;
    real_type t95  = cos(XM__[51]);
    result__[ 315 ] = -0.10e0 * t95;
    result__[ 316 ] = result__[311];
    result__[ 317 ] = result__[315];
    result__[ 318 ] = __INV_DZETA;
    result__[ 319 ] = -1.0;
    real_type t98  = cos(XM__[52]);
    result__[ 320 ] = -0.10e0 * t98;
    result__[ 321 ] = result__[316];
    result__[ 322 ] = result__[320];
    result__[ 323 ] = __INV_DZETA;
    result__[ 324 ] = -1.0;
    real_type t101 = cos(XM__[53]);
    result__[ 325 ] = -0.10e0 * t101;
    result__[ 326 ] = result__[321];
    result__[ 327 ] = result__[325];
    result__[ 328 ] = __INV_DZETA;
    result__[ 329 ] = -1.0;
    real_type t104 = cos(XM__[54]);
    result__[ 330 ] = -0.10e0 * t104;
    result__[ 331 ] = result__[326];
    result__[ 332 ] = result__[330];
    result__[ 333 ] = __INV_DZETA;
    result__[ 334 ] = -1.0;
    real_type t107 = cos(XM__[55]);
    result__[ 335 ] = -0.10e0 * t107;
    result__[ 336 ] = result__[331];
    result__[ 337 ] = result__[335];
    result__[ 338 ] = __INV_DZETA;
    result__[ 339 ] = -1.0;
    real_type t110 = cos(XM__[56]);
    result__[ 340 ] = -0.10e0 * t110;
    result__[ 341 ] = result__[336];
    result__[ 342 ] = result__[340];
    result__[ 343 ] = __INV_DZETA;
    result__[ 344 ] = -1.0;
    real_type t113 = cos(XM__[57]);
    result__[ 345 ] = -0.10e0 * t113;
    result__[ 346 ] = result__[341];
    result__[ 347 ] = result__[345];
    result__[ 348 ] = __INV_DZETA;
    result__[ 349 ] = -1.0;
    real_type t116 = cos(XM__[58]);
    result__[ 350 ] = -0.10e0 * t116;
    result__[ 351 ] = result__[346];
    result__[ 352 ] = result__[350];
    result__[ 353 ] = __INV_DZETA;
    result__[ 354 ] = -1.0;
    real_type t119 = cos(XM__[59]);
    result__[ 355 ] = -0.10e0 * t119;
    result__[ 356 ] = result__[351];
    result__[ 357 ] = result__[355];
    result__[ 358 ] = __INV_DZETA;
    result__[ 359 ] = -1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 360, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxpu_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxpu_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxpu_nnz()     const { return 160; }

  void
  ICLOCS_ContinuousMP::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 80  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 81  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 82  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 83  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 84  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 85  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 86  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 87  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 88  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 89  ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 90  ;
    iIndex[22] = 11  ; jIndex[22] = 11  ;
    iIndex[23] = 11  ; jIndex[23] = 91  ;
    iIndex[24] = 12  ; jIndex[24] = 12  ;
    iIndex[25] = 12  ; jIndex[25] = 92  ;
    iIndex[26] = 13  ; jIndex[26] = 13  ;
    iIndex[27] = 13  ; jIndex[27] = 93  ;
    iIndex[28] = 14  ; jIndex[28] = 14  ;
    iIndex[29] = 14  ; jIndex[29] = 94  ;
    iIndex[30] = 15  ; jIndex[30] = 15  ;
    iIndex[31] = 15  ; jIndex[31] = 95  ;
    iIndex[32] = 16  ; jIndex[32] = 16  ;
    iIndex[33] = 16  ; jIndex[33] = 96  ;
    iIndex[34] = 17  ; jIndex[34] = 17  ;
    iIndex[35] = 17  ; jIndex[35] = 97  ;
    iIndex[36] = 18  ; jIndex[36] = 18  ;
    iIndex[37] = 18  ; jIndex[37] = 98  ;
    iIndex[38] = 19  ; jIndex[38] = 19  ;
    iIndex[39] = 19  ; jIndex[39] = 99  ;
    iIndex[40] = 40  ; jIndex[40] = 40  ;
    iIndex[41] = 40  ; jIndex[41] = 120 ;
    iIndex[42] = 41  ; jIndex[42] = 41  ;
    iIndex[43] = 41  ; jIndex[43] = 121 ;
    iIndex[44] = 42  ; jIndex[44] = 42  ;
    iIndex[45] = 42  ; jIndex[45] = 122 ;
    iIndex[46] = 43  ; jIndex[46] = 43  ;
    iIndex[47] = 43  ; jIndex[47] = 123 ;
    iIndex[48] = 44  ; jIndex[48] = 44  ;
    iIndex[49] = 44  ; jIndex[49] = 124 ;
    iIndex[50] = 45  ; jIndex[50] = 45  ;
    iIndex[51] = 45  ; jIndex[51] = 125 ;
    iIndex[52] = 46  ; jIndex[52] = 46  ;
    iIndex[53] = 46  ; jIndex[53] = 126 ;
    iIndex[54] = 47  ; jIndex[54] = 47  ;
    iIndex[55] = 47  ; jIndex[55] = 127 ;
    iIndex[56] = 48  ; jIndex[56] = 48  ;
    iIndex[57] = 48  ; jIndex[57] = 128 ;
    iIndex[58] = 49  ; jIndex[58] = 49  ;
    iIndex[59] = 49  ; jIndex[59] = 129 ;
    iIndex[60] = 50  ; jIndex[60] = 50  ;
    iIndex[61] = 50  ; jIndex[61] = 130 ;
    iIndex[62] = 51  ; jIndex[62] = 51  ;
    iIndex[63] = 51  ; jIndex[63] = 131 ;
    iIndex[64] = 52  ; jIndex[64] = 52  ;
    iIndex[65] = 52  ; jIndex[65] = 132 ;
    iIndex[66] = 53  ; jIndex[66] = 53  ;
    iIndex[67] = 53  ; jIndex[67] = 133 ;
    iIndex[68] = 54  ; jIndex[68] = 54  ;
    iIndex[69] = 54  ; jIndex[69] = 134 ;
    iIndex[70] = 55  ; jIndex[70] = 55  ;
    iIndex[71] = 55  ; jIndex[71] = 135 ;
    iIndex[72] = 56  ; jIndex[72] = 56  ;
    iIndex[73] = 56  ; jIndex[73] = 136 ;
    iIndex[74] = 57  ; jIndex[74] = 57  ;
    iIndex[75] = 57  ; jIndex[75] = 137 ;
    iIndex[76] = 58  ; jIndex[76] = 58  ;
    iIndex[77] = 58  ; jIndex[77] = 138 ;
    iIndex[78] = 59  ; jIndex[78] = 59  ;
    iIndex[79] = 59  ; jIndex[79] = 139 ;
    iIndex[80] = 80  ; jIndex[80] = 0   ;
    iIndex[81] = 80  ; jIndex[81] = 80  ;
    iIndex[82] = 81  ; jIndex[82] = 1   ;
    iIndex[83] = 81  ; jIndex[83] = 81  ;
    iIndex[84] = 82  ; jIndex[84] = 2   ;
    iIndex[85] = 82  ; jIndex[85] = 82  ;
    iIndex[86] = 83  ; jIndex[86] = 3   ;
    iIndex[87] = 83  ; jIndex[87] = 83  ;
    iIndex[88] = 84  ; jIndex[88] = 4   ;
    iIndex[89] = 84  ; jIndex[89] = 84  ;
    iIndex[90] = 85  ; jIndex[90] = 5   ;
    iIndex[91] = 85  ; jIndex[91] = 85  ;
    iIndex[92] = 86  ; jIndex[92] = 6   ;
    iIndex[93] = 86  ; jIndex[93] = 86  ;
    iIndex[94] = 87  ; jIndex[94] = 7   ;
    iIndex[95] = 87  ; jIndex[95] = 87  ;
    iIndex[96] = 88  ; jIndex[96] = 8   ;
    iIndex[97] = 88  ; jIndex[97] = 88  ;
    iIndex[98] = 89  ; jIndex[98] = 9   ;
    iIndex[99] = 89  ; jIndex[99] = 89  ;
    iIndex[100] = 90  ; jIndex[100] = 10  ;
    iIndex[101] = 90  ; jIndex[101] = 90  ;
    iIndex[102] = 91  ; jIndex[102] = 11  ;
    iIndex[103] = 91  ; jIndex[103] = 91  ;
    iIndex[104] = 92  ; jIndex[104] = 12  ;
    iIndex[105] = 92  ; jIndex[105] = 92  ;
    iIndex[106] = 93  ; jIndex[106] = 13  ;
    iIndex[107] = 93  ; jIndex[107] = 93  ;
    iIndex[108] = 94  ; jIndex[108] = 14  ;
    iIndex[109] = 94  ; jIndex[109] = 94  ;
    iIndex[110] = 95  ; jIndex[110] = 15  ;
    iIndex[111] = 95  ; jIndex[111] = 95  ;
    iIndex[112] = 96  ; jIndex[112] = 16  ;
    iIndex[113] = 96  ; jIndex[113] = 96  ;
    iIndex[114] = 97  ; jIndex[114] = 17  ;
    iIndex[115] = 97  ; jIndex[115] = 97  ;
    iIndex[116] = 98  ; jIndex[116] = 18  ;
    iIndex[117] = 98  ; jIndex[117] = 98  ;
    iIndex[118] = 99  ; jIndex[118] = 19  ;
    iIndex[119] = 99  ; jIndex[119] = 99  ;
    iIndex[120] = 120 ; jIndex[120] = 40  ;
    iIndex[121] = 120 ; jIndex[121] = 120 ;
    iIndex[122] = 121 ; jIndex[122] = 41  ;
    iIndex[123] = 121 ; jIndex[123] = 121 ;
    iIndex[124] = 122 ; jIndex[124] = 42  ;
    iIndex[125] = 122 ; jIndex[125] = 122 ;
    iIndex[126] = 123 ; jIndex[126] = 43  ;
    iIndex[127] = 123 ; jIndex[127] = 123 ;
    iIndex[128] = 124 ; jIndex[128] = 44  ;
    iIndex[129] = 124 ; jIndex[129] = 124 ;
    iIndex[130] = 125 ; jIndex[130] = 45  ;
    iIndex[131] = 125 ; jIndex[131] = 125 ;
    iIndex[132] = 126 ; jIndex[132] = 46  ;
    iIndex[133] = 126 ; jIndex[133] = 126 ;
    iIndex[134] = 127 ; jIndex[134] = 47  ;
    iIndex[135] = 127 ; jIndex[135] = 127 ;
    iIndex[136] = 128 ; jIndex[136] = 48  ;
    iIndex[137] = 128 ; jIndex[137] = 128 ;
    iIndex[138] = 129 ; jIndex[138] = 49  ;
    iIndex[139] = 129 ; jIndex[139] = 129 ;
    iIndex[140] = 130 ; jIndex[140] = 50  ;
    iIndex[141] = 130 ; jIndex[141] = 130 ;
    iIndex[142] = 131 ; jIndex[142] = 51  ;
    iIndex[143] = 131 ; jIndex[143] = 131 ;
    iIndex[144] = 132 ; jIndex[144] = 52  ;
    iIndex[145] = 132 ; jIndex[145] = 132 ;
    iIndex[146] = 133 ; jIndex[146] = 53  ;
    iIndex[147] = 133 ; jIndex[147] = 133 ;
    iIndex[148] = 134 ; jIndex[148] = 54  ;
    iIndex[149] = 134 ; jIndex[149] = 134 ;
    iIndex[150] = 135 ; jIndex[150] = 55  ;
    iIndex[151] = 135 ; jIndex[151] = 135 ;
    iIndex[152] = 136 ; jIndex[152] = 56  ;
    iIndex[153] = 136 ; jIndex[153] = 136 ;
    iIndex[154] = 137 ; jIndex[154] = 57  ;
    iIndex[155] = 137 ; jIndex[155] = 137 ;
    iIndex[156] = 138 ; jIndex[156] = 58  ;
    iIndex[157] = 138 ; jIndex[157] = 138 ;
    iIndex[158] = 139 ; jIndex[158] = 59  ;
    iIndex[159] = 139 ; jIndex[159] = 139 ;
  }


  void
  ICLOCS_ContinuousMP::D2fd_odeD2xxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[80], V__[80];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    XM__[8] = (XL__[8]+XR__[8])/2;
    XM__[9] = (XL__[9]+XR__[9])/2;
    XM__[10] = (XL__[10]+XR__[10])/2;
    XM__[11] = (XL__[11]+XR__[11])/2;
    XM__[12] = (XL__[12]+XR__[12])/2;
    XM__[13] = (XL__[13]+XR__[13])/2;
    XM__[14] = (XL__[14]+XR__[14])/2;
    XM__[15] = (XL__[15]+XR__[15])/2;
    XM__[16] = (XL__[16]+XR__[16])/2;
    XM__[17] = (XL__[17]+XR__[17])/2;
    XM__[18] = (XL__[18]+XR__[18])/2;
    XM__[19] = (XL__[19]+XR__[19])/2;
    XM__[20] = (XL__[20]+XR__[20])/2;
    XM__[21] = (XL__[21]+XR__[21])/2;
    XM__[22] = (XL__[22]+XR__[22])/2;
    XM__[23] = (XL__[23]+XR__[23])/2;
    XM__[24] = (XL__[24]+XR__[24])/2;
    XM__[25] = (XL__[25]+XR__[25])/2;
    XM__[26] = (XL__[26]+XR__[26])/2;
    XM__[27] = (XL__[27]+XR__[27])/2;
    XM__[28] = (XL__[28]+XR__[28])/2;
    XM__[29] = (XL__[29]+XR__[29])/2;
    XM__[30] = (XL__[30]+XR__[30])/2;
    XM__[31] = (XL__[31]+XR__[31])/2;
    XM__[32] = (XL__[32]+XR__[32])/2;
    XM__[33] = (XL__[33]+XR__[33])/2;
    XM__[34] = (XL__[34]+XR__[34])/2;
    XM__[35] = (XL__[35]+XR__[35])/2;
    XM__[36] = (XL__[36]+XR__[36])/2;
    XM__[37] = (XL__[37]+XR__[37])/2;
    XM__[38] = (XL__[38]+XR__[38])/2;
    XM__[39] = (XL__[39]+XR__[39])/2;
    XM__[40] = (XL__[40]+XR__[40])/2;
    XM__[41] = (XL__[41]+XR__[41])/2;
    XM__[42] = (XL__[42]+XR__[42])/2;
    XM__[43] = (XL__[43]+XR__[43])/2;
    XM__[44] = (XL__[44]+XR__[44])/2;
    XM__[45] = (XL__[45]+XR__[45])/2;
    XM__[46] = (XL__[46]+XR__[46])/2;
    XM__[47] = (XL__[47]+XR__[47])/2;
    XM__[48] = (XL__[48]+XR__[48])/2;
    XM__[49] = (XL__[49]+XR__[49])/2;
    XM__[50] = (XL__[50]+XR__[50])/2;
    XM__[51] = (XL__[51]+XR__[51])/2;
    XM__[52] = (XL__[52]+XR__[52])/2;
    XM__[53] = (XL__[53]+XR__[53])/2;
    XM__[54] = (XL__[54]+XR__[54])/2;
    XM__[55] = (XL__[55]+XR__[55])/2;
    XM__[56] = (XL__[56]+XR__[56])/2;
    XM__[57] = (XL__[57]+XR__[57])/2;
    XM__[58] = (XL__[58]+XR__[58])/2;
    XM__[59] = (XL__[59]+XR__[59])/2;
    XM__[60] = (XL__[60]+XR__[60])/2;
    XM__[61] = (XL__[61]+XR__[61])/2;
    XM__[62] = (XL__[62]+XR__[62])/2;
    XM__[63] = (XL__[63]+XR__[63])/2;
    XM__[64] = (XL__[64]+XR__[64])/2;
    XM__[65] = (XL__[65]+XR__[65])/2;
    XM__[66] = (XL__[66]+XR__[66])/2;
    XM__[67] = (XL__[67]+XR__[67])/2;
    XM__[68] = (XL__[68]+XR__[68])/2;
    XM__[69] = (XL__[69]+XR__[69])/2;
    XM__[70] = (XL__[70]+XR__[70])/2;
    XM__[71] = (XL__[71]+XR__[71])/2;
    XM__[72] = (XL__[72]+XR__[72])/2;
    XM__[73] = (XL__[73]+XR__[73])/2;
    XM__[74] = (XL__[74]+XR__[74])/2;
    XM__[75] = (XL__[75]+XR__[75])/2;
    XM__[76] = (XL__[76]+XR__[76])/2;
    XM__[77] = (XL__[77]+XR__[77])/2;
    XM__[78] = (XL__[78]+XR__[78])/2;
    XM__[79] = (XL__[79]+XR__[79])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    V__[7] = __INV_DZETA*(XR__[7]-XL__[7]);
    V__[8] = __INV_DZETA*(XR__[8]-XL__[8]);
    V__[9] = __INV_DZETA*(XR__[9]-XL__[9]);
    V__[10] = __INV_DZETA*(XR__[10]-XL__[10]);
    V__[11] = __INV_DZETA*(XR__[11]-XL__[11]);
    V__[12] = __INV_DZETA*(XR__[12]-XL__[12]);
    V__[13] = __INV_DZETA*(XR__[13]-XL__[13]);
    V__[14] = __INV_DZETA*(XR__[14]-XL__[14]);
    V__[15] = __INV_DZETA*(XR__[15]-XL__[15]);
    V__[16] = __INV_DZETA*(XR__[16]-XL__[16]);
    V__[17] = __INV_DZETA*(XR__[17]-XL__[17]);
    V__[18] = __INV_DZETA*(XR__[18]-XL__[18]);
    V__[19] = __INV_DZETA*(XR__[19]-XL__[19]);
    V__[20] = __INV_DZETA*(XR__[20]-XL__[20]);
    V__[21] = __INV_DZETA*(XR__[21]-XL__[21]);
    V__[22] = __INV_DZETA*(XR__[22]-XL__[22]);
    V__[23] = __INV_DZETA*(XR__[23]-XL__[23]);
    V__[24] = __INV_DZETA*(XR__[24]-XL__[24]);
    V__[25] = __INV_DZETA*(XR__[25]-XL__[25]);
    V__[26] = __INV_DZETA*(XR__[26]-XL__[26]);
    V__[27] = __INV_DZETA*(XR__[27]-XL__[27]);
    V__[28] = __INV_DZETA*(XR__[28]-XL__[28]);
    V__[29] = __INV_DZETA*(XR__[29]-XL__[29]);
    V__[30] = __INV_DZETA*(XR__[30]-XL__[30]);
    V__[31] = __INV_DZETA*(XR__[31]-XL__[31]);
    V__[32] = __INV_DZETA*(XR__[32]-XL__[32]);
    V__[33] = __INV_DZETA*(XR__[33]-XL__[33]);
    V__[34] = __INV_DZETA*(XR__[34]-XL__[34]);
    V__[35] = __INV_DZETA*(XR__[35]-XL__[35]);
    V__[36] = __INV_DZETA*(XR__[36]-XL__[36]);
    V__[37] = __INV_DZETA*(XR__[37]-XL__[37]);
    V__[38] = __INV_DZETA*(XR__[38]-XL__[38]);
    V__[39] = __INV_DZETA*(XR__[39]-XL__[39]);
    V__[40] = __INV_DZETA*(XR__[40]-XL__[40]);
    V__[41] = __INV_DZETA*(XR__[41]-XL__[41]);
    V__[42] = __INV_DZETA*(XR__[42]-XL__[42]);
    V__[43] = __INV_DZETA*(XR__[43]-XL__[43]);
    V__[44] = __INV_DZETA*(XR__[44]-XL__[44]);
    V__[45] = __INV_DZETA*(XR__[45]-XL__[45]);
    V__[46] = __INV_DZETA*(XR__[46]-XL__[46]);
    V__[47] = __INV_DZETA*(XR__[47]-XL__[47]);
    V__[48] = __INV_DZETA*(XR__[48]-XL__[48]);
    V__[49] = __INV_DZETA*(XR__[49]-XL__[49]);
    V__[50] = __INV_DZETA*(XR__[50]-XL__[50]);
    V__[51] = __INV_DZETA*(XR__[51]-XL__[51]);
    V__[52] = __INV_DZETA*(XR__[52]-XL__[52]);
    V__[53] = __INV_DZETA*(XR__[53]-XL__[53]);
    V__[54] = __INV_DZETA*(XR__[54]-XL__[54]);
    V__[55] = __INV_DZETA*(XR__[55]-XL__[55]);
    V__[56] = __INV_DZETA*(XR__[56]-XL__[56]);
    V__[57] = __INV_DZETA*(XR__[57]-XL__[57]);
    V__[58] = __INV_DZETA*(XR__[58]-XL__[58]);
    V__[59] = __INV_DZETA*(XR__[59]-XL__[59]);
    V__[60] = __INV_DZETA*(XR__[60]-XL__[60]);
    V__[61] = __INV_DZETA*(XR__[61]-XL__[61]);
    V__[62] = __INV_DZETA*(XR__[62]-XL__[62]);
    V__[63] = __INV_DZETA*(XR__[63]-XL__[63]);
    V__[64] = __INV_DZETA*(XR__[64]-XL__[64]);
    V__[65] = __INV_DZETA*(XR__[65]-XL__[65]);
    V__[66] = __INV_DZETA*(XR__[66]-XL__[66]);
    V__[67] = __INV_DZETA*(XR__[67]-XL__[67]);
    V__[68] = __INV_DZETA*(XR__[68]-XL__[68]);
    V__[69] = __INV_DZETA*(XR__[69]-XL__[69]);
    V__[70] = __INV_DZETA*(XR__[70]-XL__[70]);
    V__[71] = __INV_DZETA*(XR__[71]-XL__[71]);
    V__[72] = __INV_DZETA*(XR__[72]-XL__[72]);
    V__[73] = __INV_DZETA*(XR__[73]-XL__[73]);
    V__[74] = __INV_DZETA*(XR__[74]-XL__[74]);
    V__[75] = __INV_DZETA*(XR__[75]-XL__[75]);
    V__[76] = __INV_DZETA*(XR__[76]-XL__[76]);
    V__[77] = __INV_DZETA*(XR__[77]-XL__[77]);
    V__[78] = __INV_DZETA*(XR__[78]-XL__[78]);
    V__[79] = __INV_DZETA*(XR__[79]-XL__[79]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t6   = sin(XR__[iX_x1] / 2 + XL__[iX_x1] / 2);
    result__[ 0   ] = t6 * LM__[20] / 4;
    result__[ 1   ] = result__[0];
    real_type t13  = sin(XR__[iX_x2] / 2 + XL__[iX_x2] / 2);
    result__[ 2   ] = t13 * LM__[21] / 4;
    result__[ 3   ] = result__[2];
    real_type t20  = sin(XR__[iX_x3] / 2 + XL__[iX_x3] / 2);
    result__[ 4   ] = t20 * LM__[22] / 4;
    result__[ 5   ] = result__[4];
    real_type t27  = sin(XR__[iX_x4] / 2 + XL__[iX_x4] / 2);
    result__[ 6   ] = t27 * LM__[23] / 4;
    result__[ 7   ] = result__[6];
    real_type t34  = sin(XR__[iX_x5] / 2 + XL__[iX_x5] / 2);
    result__[ 8   ] = t34 * LM__[24] / 4;
    result__[ 9   ] = result__[8];
    real_type t41  = sin(XR__[iX_x6] / 2 + XL__[iX_x6] / 2);
    result__[ 10  ] = t41 * LM__[25] / 4;
    result__[ 11  ] = result__[10];
    real_type t48  = sin(XR__[iX_x7] / 2 + XL__[iX_x7] / 2);
    result__[ 12  ] = t48 * LM__[26] / 4;
    result__[ 13  ] = result__[12];
    real_type t55  = sin(XR__[iX_x8] / 2 + XL__[iX_x8] / 2);
    result__[ 14  ] = t55 * LM__[27] / 4;
    result__[ 15  ] = result__[14];
    real_type t62  = sin(XR__[iX_x9] / 2 + XL__[iX_x9] / 2);
    result__[ 16  ] = t62 * LM__[28] / 4;
    result__[ 17  ] = result__[16];
    real_type t69  = sin(XR__[iX_x10] / 2 + XL__[iX_x10] / 2);
    result__[ 18  ] = t69 * LM__[29] / 4;
    result__[ 19  ] = result__[18];
    real_type t76  = sin(XR__[iX_x11] / 2 + XL__[iX_x11] / 2);
    result__[ 20  ] = t76 * LM__[30] / 4;
    result__[ 21  ] = result__[20];
    real_type t83  = sin(XR__[iX_x12] / 2 + XL__[iX_x12] / 2);
    result__[ 22  ] = t83 * LM__[31] / 4;
    result__[ 23  ] = result__[22];
    real_type t90  = sin(XR__[iX_x13] / 2 + XL__[iX_x13] / 2);
    result__[ 24  ] = t90 * LM__[32] / 4;
    result__[ 25  ] = result__[24];
    real_type t97  = sin(XR__[iX_x14] / 2 + XL__[iX_x14] / 2);
    result__[ 26  ] = t97 * LM__[33] / 4;
    result__[ 27  ] = result__[26];
    real_type t104 = sin(XR__[iX_x15] / 2 + XL__[iX_x15] / 2);
    result__[ 28  ] = t104 * LM__[34] / 4;
    result__[ 29  ] = result__[28];
    real_type t111 = sin(XR__[iX_x16] / 2 + XL__[iX_x16] / 2);
    result__[ 30  ] = t111 * LM__[35] / 4;
    result__[ 31  ] = result__[30];
    real_type t118 = sin(XR__[iX_x17] / 2 + XL__[iX_x17] / 2);
    result__[ 32  ] = t118 * LM__[36] / 4;
    result__[ 33  ] = result__[32];
    real_type t125 = sin(XR__[iX_x18] / 2 + XL__[iX_x18] / 2);
    result__[ 34  ] = t125 * LM__[37] / 4;
    result__[ 35  ] = result__[34];
    real_type t132 = sin(XR__[iX_x19] / 2 + XL__[iX_x19] / 2);
    result__[ 36  ] = t132 * LM__[38] / 4;
    result__[ 37  ] = result__[36];
    real_type t139 = sin(XR__[iX_x20] / 2 + XL__[iX_x20] / 2);
    result__[ 38  ] = t139 * LM__[39] / 4;
    result__[ 39  ] = result__[38];
    real_type t146 = sin(XR__[iX_xx1] / 2 + XL__[iX_xx1] / 2);
    result__[ 40  ] = 0.5000000000e-1 * t146 * LM__[60];
    result__[ 41  ] = result__[40];
    real_type t153 = sin(XR__[iX_xx2] / 2 + XL__[iX_xx2] / 2);
    result__[ 42  ] = 0.5000000000e-1 * t153 * LM__[61];
    result__[ 43  ] = result__[42];
    real_type t160 = sin(XR__[iX_xx3] / 2 + XL__[iX_xx3] / 2);
    result__[ 44  ] = 0.5000000000e-1 * t160 * LM__[62];
    result__[ 45  ] = result__[44];
    real_type t167 = sin(XR__[iX_xx4] / 2 + XL__[iX_xx4] / 2);
    result__[ 46  ] = 0.5000000000e-1 * t167 * LM__[63];
    result__[ 47  ] = result__[46];
    real_type t174 = sin(XR__[iX_xx5] / 2 + XL__[iX_xx5] / 2);
    result__[ 48  ] = 0.5000000000e-1 * t174 * LM__[64];
    result__[ 49  ] = result__[48];
    real_type t181 = sin(XR__[iX_xx6] / 2 + XL__[iX_xx6] / 2);
    result__[ 50  ] = 0.5000000000e-1 * t181 * LM__[65];
    result__[ 51  ] = result__[50];
    real_type t188 = sin(XR__[iX_xx7] / 2 + XL__[iX_xx7] / 2);
    result__[ 52  ] = 0.5000000000e-1 * t188 * LM__[66];
    result__[ 53  ] = result__[52];
    real_type t195 = sin(XR__[iX_xx8] / 2 + XL__[iX_xx8] / 2);
    result__[ 54  ] = 0.5000000000e-1 * t195 * LM__[67];
    result__[ 55  ] = result__[54];
    real_type t202 = sin(XR__[iX_xx9] / 2 + XL__[iX_xx9] / 2);
    result__[ 56  ] = 0.5000000000e-1 * t202 * LM__[68];
    result__[ 57  ] = result__[56];
    real_type t209 = sin(XR__[iX_xx10] / 2 + XL__[iX_xx10] / 2);
    result__[ 58  ] = 0.5000000000e-1 * t209 * LM__[69];
    result__[ 59  ] = result__[58];
    real_type t216 = sin(XR__[iX_xx11] / 2 + XL__[iX_xx11] / 2);
    result__[ 60  ] = 0.5000000000e-1 * t216 * LM__[70];
    result__[ 61  ] = result__[60];
    real_type t223 = sin(XR__[iX_xx12] / 2 + XL__[iX_xx12] / 2);
    result__[ 62  ] = 0.5000000000e-1 * t223 * LM__[71];
    result__[ 63  ] = result__[62];
    real_type t230 = sin(XR__[iX_xx13] / 2 + XL__[iX_xx13] / 2);
    result__[ 64  ] = 0.5000000000e-1 * t230 * LM__[72];
    result__[ 65  ] = result__[64];
    real_type t237 = sin(XR__[iX_xx14] / 2 + XL__[iX_xx14] / 2);
    result__[ 66  ] = 0.5000000000e-1 * t237 * LM__[73];
    result__[ 67  ] = result__[66];
    real_type t244 = sin(XR__[iX_xx15] / 2 + XL__[iX_xx15] / 2);
    result__[ 68  ] = 0.5000000000e-1 * t244 * LM__[74];
    result__[ 69  ] = result__[68];
    real_type t251 = sin(XR__[iX_xx16] / 2 + XL__[iX_xx16] / 2);
    result__[ 70  ] = 0.5000000000e-1 * t251 * LM__[75];
    result__[ 71  ] = result__[70];
    real_type t258 = sin(XR__[iX_xx17] / 2 + XL__[iX_xx17] / 2);
    result__[ 72  ] = 0.5000000000e-1 * t258 * LM__[76];
    result__[ 73  ] = result__[72];
    real_type t265 = sin(XR__[iX_xx18] / 2 + XL__[iX_xx18] / 2);
    result__[ 74  ] = 0.5000000000e-1 * t265 * LM__[77];
    result__[ 75  ] = result__[74];
    real_type t272 = sin(XR__[iX_xx19] / 2 + XL__[iX_xx19] / 2);
    result__[ 76  ] = 0.5000000000e-1 * t272 * LM__[78];
    result__[ 77  ] = result__[76];
    real_type t279 = sin(XR__[iX_xx20] / 2 + XL__[iX_xx20] / 2);
    result__[ 78  ] = 0.5000000000e-1 * t279 * LM__[79];
    result__[ 79  ] = result__[78];
    result__[ 80  ] = result__[1];
    result__[ 81  ] = result__[80];
    result__[ 82  ] = result__[3];
    result__[ 83  ] = result__[82];
    result__[ 84  ] = result__[5];
    result__[ 85  ] = result__[84];
    result__[ 86  ] = result__[7];
    result__[ 87  ] = result__[86];
    result__[ 88  ] = result__[9];
    result__[ 89  ] = result__[88];
    result__[ 90  ] = result__[11];
    result__[ 91  ] = result__[90];
    result__[ 92  ] = result__[13];
    result__[ 93  ] = result__[92];
    result__[ 94  ] = result__[15];
    result__[ 95  ] = result__[94];
    result__[ 96  ] = result__[17];
    result__[ 97  ] = result__[96];
    result__[ 98  ] = result__[19];
    result__[ 99  ] = result__[98];
    result__[ 100 ] = result__[21];
    result__[ 101 ] = result__[100];
    result__[ 102 ] = result__[23];
    result__[ 103 ] = result__[102];
    result__[ 104 ] = result__[25];
    result__[ 105 ] = result__[104];
    result__[ 106 ] = result__[27];
    result__[ 107 ] = result__[106];
    result__[ 108 ] = result__[29];
    result__[ 109 ] = result__[108];
    result__[ 110 ] = result__[31];
    result__[ 111 ] = result__[110];
    result__[ 112 ] = result__[33];
    result__[ 113 ] = result__[112];
    result__[ 114 ] = result__[35];
    result__[ 115 ] = result__[114];
    result__[ 116 ] = result__[37];
    result__[ 117 ] = result__[116];
    result__[ 118 ] = result__[39];
    result__[ 119 ] = result__[118];
    result__[ 120 ] = result__[41];
    result__[ 121 ] = result__[120];
    result__[ 122 ] = result__[43];
    result__[ 123 ] = result__[122];
    result__[ 124 ] = result__[45];
    result__[ 125 ] = result__[124];
    result__[ 126 ] = result__[47];
    result__[ 127 ] = result__[126];
    result__[ 128 ] = result__[49];
    result__[ 129 ] = result__[128];
    result__[ 130 ] = result__[51];
    result__[ 131 ] = result__[130];
    result__[ 132 ] = result__[53];
    result__[ 133 ] = result__[132];
    result__[ 134 ] = result__[55];
    result__[ 135 ] = result__[134];
    result__[ 136 ] = result__[57];
    result__[ 137 ] = result__[136];
    result__[ 138 ] = result__[59];
    result__[ 139 ] = result__[138];
    result__[ 140 ] = result__[61];
    result__[ 141 ] = result__[140];
    result__[ 142 ] = result__[63];
    result__[ 143 ] = result__[142];
    result__[ 144 ] = result__[65];
    result__[ 145 ] = result__[144];
    result__[ 146 ] = result__[67];
    result__[ 147 ] = result__[146];
    result__[ 148 ] = result__[69];
    result__[ 149 ] = result__[148];
    result__[ 150 ] = result__[71];
    result__[ 151 ] = result__[150];
    result__[ 152 ] = result__[73];
    result__[ 153 ] = result__[152];
    result__[ 154 ] = result__[75];
    result__[ 155 ] = result__[154];
    result__[ 156 ] = result__[77];
    result__[ 157 ] = result__[156];
    result__[ 158 ] = result__[79];
    result__[ 159 ] = result__[158];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 160, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS_ContinuousMP_Methods_Guess.cc
