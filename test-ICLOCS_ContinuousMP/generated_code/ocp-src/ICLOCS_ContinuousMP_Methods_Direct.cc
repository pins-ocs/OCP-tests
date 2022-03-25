/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_Guess.cc                           |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    result__[ 7   ] = V__[7];
    result__[ 8   ] = V__[8];
    result__[ 9   ] = V__[9];
    result__[ 10  ] = V__[10];
    result__[ 11  ] = V__[11];
    result__[ 12  ] = V__[12];
    result__[ 13  ] = V__[13];
    result__[ 14  ] = V__[14];
    result__[ 15  ] = V__[15];
    result__[ 16  ] = V__[16];
    result__[ 17  ] = V__[17];
    result__[ 18  ] = V__[18];
    result__[ 19  ] = V__[19];
    result__[ 20  ] = V__[20];
    result__[ 21  ] = V__[21];
    result__[ 22  ] = V__[22];
    result__[ 23  ] = V__[23];
    result__[ 24  ] = V__[24];
    result__[ 25  ] = V__[25];
    result__[ 26  ] = V__[26];
    result__[ 27  ] = V__[27];
    result__[ 28  ] = V__[28];
    result__[ 29  ] = V__[29];
    result__[ 30  ] = V__[30];
    result__[ 31  ] = V__[31];
    result__[ 32  ] = V__[32];
    result__[ 33  ] = V__[33];
    result__[ 34  ] = V__[34];
    result__[ 35  ] = V__[35];
    result__[ 36  ] = V__[36];
    result__[ 37  ] = V__[37];
    result__[ 38  ] = V__[38];
    result__[ 39  ] = V__[39];
    result__[ 40  ] = V__[40];
    result__[ 41  ] = V__[41];
    result__[ 42  ] = V__[42];
    result__[ 43  ] = V__[43];
    result__[ 44  ] = V__[44];
    result__[ 45  ] = V__[45];
    result__[ 46  ] = V__[46];
    result__[ 47  ] = V__[47];
    result__[ 48  ] = V__[48];
    result__[ 49  ] = V__[49];
    result__[ 50  ] = V__[50];
    result__[ 51  ] = V__[51];
    result__[ 52  ] = V__[52];
    result__[ 53  ] = V__[53];
    result__[ 54  ] = V__[54];
    result__[ 55  ] = V__[55];
    result__[ 56  ] = V__[56];
    result__[ 57  ] = V__[57];
    result__[ 58  ] = V__[58];
    result__[ 59  ] = V__[59];
    result__[ 60  ] = V__[60];
    result__[ 61  ] = V__[61];
    result__[ 62  ] = V__[62];
    result__[ 63  ] = V__[63];
    result__[ 64  ] = V__[64];
    result__[ 65  ] = V__[65];
    result__[ 66  ] = V__[66];
    result__[ 67  ] = V__[67];
    result__[ 68  ] = V__[68];
    result__[ 69  ] = V__[69];
    result__[ 70  ] = V__[70];
    result__[ 71  ] = V__[71];
    result__[ 72  ] = V__[72];
    result__[ 73  ] = V__[73];
    result__[ 74  ] = V__[74];
    result__[ 75  ] = V__[75];
    result__[ 76  ] = V__[76];
    result__[ 77  ] = V__[77];
    result__[ 78  ] = V__[78];
    result__[ 79  ] = V__[79];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::Dfd_odeDxxup_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::Dfd_odeDxxup_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::Dfd_odeDxxup_nnz()     const { return 160; }

  void
  ICLOCS_ContinuousMP::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[40] = 20  ; jIndex[40] = 20  ;
    iIndex[41] = 20  ; jIndex[41] = 100 ;
    iIndex[42] = 21  ; jIndex[42] = 21  ;
    iIndex[43] = 21  ; jIndex[43] = 101 ;
    iIndex[44] = 22  ; jIndex[44] = 22  ;
    iIndex[45] = 22  ; jIndex[45] = 102 ;
    iIndex[46] = 23  ; jIndex[46] = 23  ;
    iIndex[47] = 23  ; jIndex[47] = 103 ;
    iIndex[48] = 24  ; jIndex[48] = 24  ;
    iIndex[49] = 24  ; jIndex[49] = 104 ;
    iIndex[50] = 25  ; jIndex[50] = 25  ;
    iIndex[51] = 25  ; jIndex[51] = 105 ;
    iIndex[52] = 26  ; jIndex[52] = 26  ;
    iIndex[53] = 26  ; jIndex[53] = 106 ;
    iIndex[54] = 27  ; jIndex[54] = 27  ;
    iIndex[55] = 27  ; jIndex[55] = 107 ;
    iIndex[56] = 28  ; jIndex[56] = 28  ;
    iIndex[57] = 28  ; jIndex[57] = 108 ;
    iIndex[58] = 29  ; jIndex[58] = 29  ;
    iIndex[59] = 29  ; jIndex[59] = 109 ;
    iIndex[60] = 30  ; jIndex[60] = 30  ;
    iIndex[61] = 30  ; jIndex[61] = 110 ;
    iIndex[62] = 31  ; jIndex[62] = 31  ;
    iIndex[63] = 31  ; jIndex[63] = 111 ;
    iIndex[64] = 32  ; jIndex[64] = 32  ;
    iIndex[65] = 32  ; jIndex[65] = 112 ;
    iIndex[66] = 33  ; jIndex[66] = 33  ;
    iIndex[67] = 33  ; jIndex[67] = 113 ;
    iIndex[68] = 34  ; jIndex[68] = 34  ;
    iIndex[69] = 34  ; jIndex[69] = 114 ;
    iIndex[70] = 35  ; jIndex[70] = 35  ;
    iIndex[71] = 35  ; jIndex[71] = 115 ;
    iIndex[72] = 36  ; jIndex[72] = 36  ;
    iIndex[73] = 36  ; jIndex[73] = 116 ;
    iIndex[74] = 37  ; jIndex[74] = 37  ;
    iIndex[75] = 37  ; jIndex[75] = 117 ;
    iIndex[76] = 38  ; jIndex[76] = 38  ;
    iIndex[77] = 38  ; jIndex[77] = 118 ;
    iIndex[78] = 39  ; jIndex[78] = 39  ;
    iIndex[79] = 39  ; jIndex[79] = 119 ;
    iIndex[80] = 40  ; jIndex[80] = 40  ;
    iIndex[81] = 40  ; jIndex[81] = 120 ;
    iIndex[82] = 41  ; jIndex[82] = 41  ;
    iIndex[83] = 41  ; jIndex[83] = 121 ;
    iIndex[84] = 42  ; jIndex[84] = 42  ;
    iIndex[85] = 42  ; jIndex[85] = 122 ;
    iIndex[86] = 43  ; jIndex[86] = 43  ;
    iIndex[87] = 43  ; jIndex[87] = 123 ;
    iIndex[88] = 44  ; jIndex[88] = 44  ;
    iIndex[89] = 44  ; jIndex[89] = 124 ;
    iIndex[90] = 45  ; jIndex[90] = 45  ;
    iIndex[91] = 45  ; jIndex[91] = 125 ;
    iIndex[92] = 46  ; jIndex[92] = 46  ;
    iIndex[93] = 46  ; jIndex[93] = 126 ;
    iIndex[94] = 47  ; jIndex[94] = 47  ;
    iIndex[95] = 47  ; jIndex[95] = 127 ;
    iIndex[96] = 48  ; jIndex[96] = 48  ;
    iIndex[97] = 48  ; jIndex[97] = 128 ;
    iIndex[98] = 49  ; jIndex[98] = 49  ;
    iIndex[99] = 49  ; jIndex[99] = 129 ;
    iIndex[100] = 50  ; jIndex[100] = 50  ;
    iIndex[101] = 50  ; jIndex[101] = 130 ;
    iIndex[102] = 51  ; jIndex[102] = 51  ;
    iIndex[103] = 51  ; jIndex[103] = 131 ;
    iIndex[104] = 52  ; jIndex[104] = 52  ;
    iIndex[105] = 52  ; jIndex[105] = 132 ;
    iIndex[106] = 53  ; jIndex[106] = 53  ;
    iIndex[107] = 53  ; jIndex[107] = 133 ;
    iIndex[108] = 54  ; jIndex[108] = 54  ;
    iIndex[109] = 54  ; jIndex[109] = 134 ;
    iIndex[110] = 55  ; jIndex[110] = 55  ;
    iIndex[111] = 55  ; jIndex[111] = 135 ;
    iIndex[112] = 56  ; jIndex[112] = 56  ;
    iIndex[113] = 56  ; jIndex[113] = 136 ;
    iIndex[114] = 57  ; jIndex[114] = 57  ;
    iIndex[115] = 57  ; jIndex[115] = 137 ;
    iIndex[116] = 58  ; jIndex[116] = 58  ;
    iIndex[117] = 58  ; jIndex[117] = 138 ;
    iIndex[118] = 59  ; jIndex[118] = 59  ;
    iIndex[119] = 59  ; jIndex[119] = 139 ;
    iIndex[120] = 60  ; jIndex[120] = 60  ;
    iIndex[121] = 60  ; jIndex[121] = 140 ;
    iIndex[122] = 61  ; jIndex[122] = 61  ;
    iIndex[123] = 61  ; jIndex[123] = 141 ;
    iIndex[124] = 62  ; jIndex[124] = 62  ;
    iIndex[125] = 62  ; jIndex[125] = 142 ;
    iIndex[126] = 63  ; jIndex[126] = 63  ;
    iIndex[127] = 63  ; jIndex[127] = 143 ;
    iIndex[128] = 64  ; jIndex[128] = 64  ;
    iIndex[129] = 64  ; jIndex[129] = 144 ;
    iIndex[130] = 65  ; jIndex[130] = 65  ;
    iIndex[131] = 65  ; jIndex[131] = 145 ;
    iIndex[132] = 66  ; jIndex[132] = 66  ;
    iIndex[133] = 66  ; jIndex[133] = 146 ;
    iIndex[134] = 67  ; jIndex[134] = 67  ;
    iIndex[135] = 67  ; jIndex[135] = 147 ;
    iIndex[136] = 68  ; jIndex[136] = 68  ;
    iIndex[137] = 68  ; jIndex[137] = 148 ;
    iIndex[138] = 69  ; jIndex[138] = 69  ;
    iIndex[139] = 69  ; jIndex[139] = 149 ;
    iIndex[140] = 70  ; jIndex[140] = 70  ;
    iIndex[141] = 70  ; jIndex[141] = 150 ;
    iIndex[142] = 71  ; jIndex[142] = 71  ;
    iIndex[143] = 71  ; jIndex[143] = 151 ;
    iIndex[144] = 72  ; jIndex[144] = 72  ;
    iIndex[145] = 72  ; jIndex[145] = 152 ;
    iIndex[146] = 73  ; jIndex[146] = 73  ;
    iIndex[147] = 73  ; jIndex[147] = 153 ;
    iIndex[148] = 74  ; jIndex[148] = 74  ;
    iIndex[149] = 74  ; jIndex[149] = 154 ;
    iIndex[150] = 75  ; jIndex[150] = 75  ;
    iIndex[151] = 75  ; jIndex[151] = 155 ;
    iIndex[152] = 76  ; jIndex[152] = 76  ;
    iIndex[153] = 76  ; jIndex[153] = 156 ;
    iIndex[154] = 77  ; jIndex[154] = 77  ;
    iIndex[155] = 77  ; jIndex[155] = 157 ;
    iIndex[156] = 78  ; jIndex[156] = 78  ;
    iIndex[157] = 78  ; jIndex[157] = 158 ;
    iIndex[158] = 79  ; jIndex[158] = 79  ;
    iIndex[159] = 79  ; jIndex[159] = 159 ;
  }


  void
  ICLOCS_ContinuousMP::Dfd_odeDxxup_sparse(
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
    result__[ 1   ] = __INV_DZETA;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = __INV_DZETA;
    result__[ 4   ] = result__[2];
    result__[ 5   ] = __INV_DZETA;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = __INV_DZETA;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = __INV_DZETA;
    result__[ 10  ] = result__[8];
    result__[ 11  ] = __INV_DZETA;
    result__[ 12  ] = result__[10];
    result__[ 13  ] = __INV_DZETA;
    result__[ 14  ] = result__[12];
    result__[ 15  ] = __INV_DZETA;
    result__[ 16  ] = result__[14];
    result__[ 17  ] = __INV_DZETA;
    result__[ 18  ] = result__[16];
    result__[ 19  ] = __INV_DZETA;
    result__[ 20  ] = result__[18];
    result__[ 21  ] = __INV_DZETA;
    result__[ 22  ] = result__[20];
    result__[ 23  ] = __INV_DZETA;
    result__[ 24  ] = result__[22];
    result__[ 25  ] = __INV_DZETA;
    result__[ 26  ] = result__[24];
    result__[ 27  ] = __INV_DZETA;
    result__[ 28  ] = result__[26];
    result__[ 29  ] = __INV_DZETA;
    result__[ 30  ] = result__[28];
    result__[ 31  ] = __INV_DZETA;
    result__[ 32  ] = result__[30];
    result__[ 33  ] = __INV_DZETA;
    result__[ 34  ] = result__[32];
    result__[ 35  ] = __INV_DZETA;
    result__[ 36  ] = result__[34];
    result__[ 37  ] = __INV_DZETA;
    result__[ 38  ] = result__[36];
    result__[ 39  ] = __INV_DZETA;
    result__[ 40  ] = result__[38];
    result__[ 41  ] = __INV_DZETA;
    result__[ 42  ] = result__[40];
    result__[ 43  ] = __INV_DZETA;
    result__[ 44  ] = result__[42];
    result__[ 45  ] = __INV_DZETA;
    result__[ 46  ] = result__[44];
    result__[ 47  ] = __INV_DZETA;
    result__[ 48  ] = result__[46];
    result__[ 49  ] = __INV_DZETA;
    result__[ 50  ] = result__[48];
    result__[ 51  ] = __INV_DZETA;
    result__[ 52  ] = result__[50];
    result__[ 53  ] = __INV_DZETA;
    result__[ 54  ] = result__[52];
    result__[ 55  ] = __INV_DZETA;
    result__[ 56  ] = result__[54];
    result__[ 57  ] = __INV_DZETA;
    result__[ 58  ] = result__[56];
    result__[ 59  ] = __INV_DZETA;
    result__[ 60  ] = result__[58];
    result__[ 61  ] = __INV_DZETA;
    result__[ 62  ] = result__[60];
    result__[ 63  ] = __INV_DZETA;
    result__[ 64  ] = result__[62];
    result__[ 65  ] = __INV_DZETA;
    result__[ 66  ] = result__[64];
    result__[ 67  ] = __INV_DZETA;
    result__[ 68  ] = result__[66];
    result__[ 69  ] = __INV_DZETA;
    result__[ 70  ] = result__[68];
    result__[ 71  ] = __INV_DZETA;
    result__[ 72  ] = result__[70];
    result__[ 73  ] = __INV_DZETA;
    result__[ 74  ] = result__[72];
    result__[ 75  ] = __INV_DZETA;
    result__[ 76  ] = result__[74];
    result__[ 77  ] = __INV_DZETA;
    result__[ 78  ] = result__[76];
    result__[ 79  ] = __INV_DZETA;
    result__[ 80  ] = result__[78];
    result__[ 81  ] = __INV_DZETA;
    result__[ 82  ] = result__[80];
    result__[ 83  ] = __INV_DZETA;
    result__[ 84  ] = result__[82];
    result__[ 85  ] = __INV_DZETA;
    result__[ 86  ] = result__[84];
    result__[ 87  ] = __INV_DZETA;
    result__[ 88  ] = result__[86];
    result__[ 89  ] = __INV_DZETA;
    result__[ 90  ] = result__[88];
    result__[ 91  ] = __INV_DZETA;
    result__[ 92  ] = result__[90];
    result__[ 93  ] = __INV_DZETA;
    result__[ 94  ] = result__[92];
    result__[ 95  ] = __INV_DZETA;
    result__[ 96  ] = result__[94];
    result__[ 97  ] = __INV_DZETA;
    result__[ 98  ] = result__[96];
    result__[ 99  ] = __INV_DZETA;
    result__[ 100 ] = result__[98];
    result__[ 101 ] = __INV_DZETA;
    result__[ 102 ] = result__[100];
    result__[ 103 ] = __INV_DZETA;
    result__[ 104 ] = result__[102];
    result__[ 105 ] = __INV_DZETA;
    result__[ 106 ] = result__[104];
    result__[ 107 ] = __INV_DZETA;
    result__[ 108 ] = result__[106];
    result__[ 109 ] = __INV_DZETA;
    result__[ 110 ] = result__[108];
    result__[ 111 ] = __INV_DZETA;
    result__[ 112 ] = result__[110];
    result__[ 113 ] = __INV_DZETA;
    result__[ 114 ] = result__[112];
    result__[ 115 ] = __INV_DZETA;
    result__[ 116 ] = result__[114];
    result__[ 117 ] = __INV_DZETA;
    result__[ 118 ] = result__[116];
    result__[ 119 ] = __INV_DZETA;
    result__[ 120 ] = result__[118];
    result__[ 121 ] = __INV_DZETA;
    result__[ 122 ] = result__[120];
    result__[ 123 ] = __INV_DZETA;
    result__[ 124 ] = result__[122];
    result__[ 125 ] = __INV_DZETA;
    result__[ 126 ] = result__[124];
    result__[ 127 ] = __INV_DZETA;
    result__[ 128 ] = result__[126];
    result__[ 129 ] = __INV_DZETA;
    result__[ 130 ] = result__[128];
    result__[ 131 ] = __INV_DZETA;
    result__[ 132 ] = result__[130];
    result__[ 133 ] = __INV_DZETA;
    result__[ 134 ] = result__[132];
    result__[ 135 ] = __INV_DZETA;
    result__[ 136 ] = result__[134];
    result__[ 137 ] = __INV_DZETA;
    result__[ 138 ] = result__[136];
    result__[ 139 ] = __INV_DZETA;
    result__[ 140 ] = result__[138];
    result__[ 141 ] = __INV_DZETA;
    result__[ 142 ] = result__[140];
    result__[ 143 ] = __INV_DZETA;
    result__[ 144 ] = result__[142];
    result__[ 145 ] = __INV_DZETA;
    result__[ 146 ] = result__[144];
    result__[ 147 ] = __INV_DZETA;
    result__[ 148 ] = result__[146];
    result__[ 149 ] = __INV_DZETA;
    result__[ 150 ] = result__[148];
    result__[ 151 ] = __INV_DZETA;
    result__[ 152 ] = result__[150];
    result__[ 153 ] = __INV_DZETA;
    result__[ 154 ] = result__[152];
    result__[ 155 ] = __INV_DZETA;
    result__[ 156 ] = result__[154];
    result__[ 157 ] = __INV_DZETA;
    result__[ 158 ] = result__[156];
    result__[ 159 ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 160, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxup_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxup_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::D2fd_odeD2xxup_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2fd_odeD2xxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS_ContinuousMP_Methods_Guess.cc
