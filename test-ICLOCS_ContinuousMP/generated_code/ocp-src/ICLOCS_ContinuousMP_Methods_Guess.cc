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

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  ICLOCS_ContinuousMP::p_guess_eval( P_p_type P__ ) const {
    P__[ iP_u1  ] = 0;
    P__[ iP_u2  ] = 0;
    P__[ iP_u3  ] = 0;
    P__[ iP_u4  ] = 0;
    P__[ iP_u5  ] = 0;
    P__[ iP_u6  ] = 0;
    P__[ iP_u7  ] = 0;
    P__[ iP_u8  ] = 0;
    P__[ iP_u9  ] = 0;
    P__[ iP_u10 ] = 0;
    P__[ iP_u11 ] = 0;
    P__[ iP_u12 ] = 0;
    P__[ iP_u13 ] = 0;
    P__[ iP_u14 ] = 0;
    P__[ iP_u15 ] = 0;
    P__[ iP_u16 ] = 0;
    P__[ iP_u17 ] = 0;
    P__[ iP_u18 ] = 0;
    P__[ iP_u19 ] = 0;
    P__[ iP_u20 ] = 0;
    if ( m_debug )
      Mechatronix::check( P__.pointer(), "p_guess_eval", 20 );
  }

  void
  ICLOCS_ContinuousMP::xlambda_guess_eval(
    integer        i_segment,
    Q_const_p_type Q__,
    P_const_p_type P__,
    X_p_type       X__,
    L_p_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    { // open block to avoid temporary clash
      X__[ iX_x1   ] = 1;
      X__[ iX_x2   ] = 1;
      X__[ iX_x3   ] = 1;
      X__[ iX_x4   ] = 1;
      X__[ iX_x5   ] = 1;
      X__[ iX_x6   ] = 1;
      X__[ iX_x7   ] = 1;
      X__[ iX_x8   ] = 1;
      X__[ iX_x9   ] = 1;
      X__[ iX_x10  ] = 1;
      X__[ iX_x11  ] = 1;
      X__[ iX_x12  ] = 1;
      X__[ iX_x13  ] = 1;
      X__[ iX_x14  ] = 1;
      X__[ iX_x15  ] = 1;
      X__[ iX_x16  ] = 1;
      X__[ iX_x17  ] = 1;
      X__[ iX_x18  ] = 1;
      X__[ iX_x19  ] = 1;
      X__[ iX_x20  ] = 1;
      X__[ iX_y1   ] = 1;
      X__[ iX_y2   ] = 1;
      X__[ iX_y3   ] = 1;
      X__[ iX_y4   ] = 1;
      X__[ iX_y5   ] = 1;
      X__[ iX_y6   ] = 1;
      X__[ iX_y7   ] = 1;
      X__[ iX_y8   ] = 1;
      X__[ iX_y9   ] = 1;
      X__[ iX_y10  ] = 1;
    }
    { // open block to avoid temporary clash

    }
    if ( m_debug ) {
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 80 );
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 80 );
    }
  }

  /*\
   |    ____ _               _
   |   / ___| |__   ___  ___| | __
   |  | |   | '_ \ / _ \/ __| |/ /
   |  | |___| | | |  __/ (__|   <
   |   \____|_| |_|\___|\___|_|\_\
  \*/

  #define Xoptima__check__node__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on node={} segment={}: {}\nfail {} < {}\n",     \
        ipos, i_segment, MSG, a, b                                    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__node__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on node={} segment={}: {}\nfail {} <= {}\n",    \
        ipos, i_segment, MSG, a, b                                    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__cell__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on cell={}: {}\nfail {} < {}\n",                \
        icell, MSG, a, b                                              \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__cell__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on cell={}: {}\nfail {} <= {}\n",               \
        icell, MSG, a, b                                              \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__pars__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on parameter: {}\nfail {} < {}\n", MSG, a, b    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__pars__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on parameter: {}\nfail {} <= {}\n", MSG, a, b   \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__params__lt(A,B,MSG)                         \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on params: {}\nfail {} < {}\n", MSG, a, b       \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__params__le(A,B,MSG)                         \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on params: {}\nfail {} <= {}\n", MSG, a, b      \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__u__lt(A,B,MSG)                              \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_U_console.yellow(fmt::format(                                 \
        "Failed check on control: {}\nfail {} < {}\n", MSG, a, b      \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__u__le(A,B,MSG)                              \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_U_console.yellow(fmt::format(                                 \
        "Failed check on control: {}\nfail {} <= {}\n", MSG, a, b     \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_ContinuousMP::p_check( P_const_p_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_ContinuousMP::xlambda_check_node(
    integer         ipos,
    NodeQXL const & NODE__,
    P_const_p_type  P__
  ) const {
    return true;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  ICLOCS_ContinuousMP::penalties_check_node(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool ok = true;
    real_type t1   = P__[iP_u1];
    ok = ok && u1Limitation_min.check_range(-10 - t1, m_max_penalty_value);
    ok = ok && u1Limitation_max.check_range(t1 - 10, m_max_penalty_value);
    real_type t4   = P__[iP_u2];
    ok = ok && u2Limitation_min.check_range(-10 - t4, m_max_penalty_value);
    ok = ok && u2Limitation_max.check_range(t4 - 10, m_max_penalty_value);
    real_type t7   = P__[iP_u3];
    ok = ok && u3Limitation_min.check_range(-10 - t7, m_max_penalty_value);
    ok = ok && u3Limitation_max.check_range(t7 - 10, m_max_penalty_value);
    real_type t10  = P__[iP_u4];
    ok = ok && u4Limitation_min.check_range(-10 - t10, m_max_penalty_value);
    ok = ok && u4Limitation_max.check_range(t10 - 10, m_max_penalty_value);
    real_type t13  = P__[iP_u5];
    ok = ok && u5Limitation_min.check_range(-10 - t13, m_max_penalty_value);
    ok = ok && u5Limitation_max.check_range(t13 - 10, m_max_penalty_value);
    real_type t16  = P__[iP_u6];
    ok = ok && u6Limitation_min.check_range(-10 - t16, m_max_penalty_value);
    ok = ok && u6Limitation_max.check_range(t16 - 10, m_max_penalty_value);
    real_type t19  = P__[iP_u7];
    ok = ok && u7Limitation_min.check_range(-10 - t19, m_max_penalty_value);
    ok = ok && u7Limitation_max.check_range(t19 - 10, m_max_penalty_value);
    real_type t22  = P__[iP_u8];
    ok = ok && u8Limitation_min.check_range(-10 - t22, m_max_penalty_value);
    ok = ok && u8Limitation_max.check_range(t22 - 10, m_max_penalty_value);
    real_type t25  = P__[iP_u9];
    ok = ok && u9Limitation_min.check_range(-10 - t25, m_max_penalty_value);
    ok = ok && u9Limitation_max.check_range(t25 - 10, m_max_penalty_value);
    real_type t28  = P__[iP_u10];
    ok = ok && u10Limitation_min.check_range(-10 - t28, m_max_penalty_value);
    ok = ok && u10Limitation_max.check_range(t28 - 10, m_max_penalty_value);
    real_type t31  = P__[iP_u11];
    ok = ok && u11Limitation_min.check_range(-10 - t31, m_max_penalty_value);
    ok = ok && u11Limitation_max.check_range(t31 - 10, m_max_penalty_value);
    real_type t34  = P__[iP_u12];
    ok = ok && u12Limitation_min.check_range(-10 - t34, m_max_penalty_value);
    ok = ok && u12Limitation_max.check_range(t34 - 10, m_max_penalty_value);
    real_type t37  = P__[iP_u13];
    ok = ok && u13Limitation_min.check_range(-10 - t37, m_max_penalty_value);
    ok = ok && u13Limitation_max.check_range(t37 - 10, m_max_penalty_value);
    real_type t40  = P__[iP_u14];
    ok = ok && u14Limitation_min.check_range(-10 - t40, m_max_penalty_value);
    ok = ok && u14Limitation_max.check_range(t40 - 10, m_max_penalty_value);
    real_type t43  = P__[iP_u15];
    ok = ok && u15Limitation_min.check_range(-10 - t43, m_max_penalty_value);
    ok = ok && u15Limitation_max.check_range(t43 - 10, m_max_penalty_value);
    real_type t46  = P__[iP_u16];
    ok = ok && u16Limitation_min.check_range(-10 - t46, m_max_penalty_value);
    ok = ok && u16Limitation_max.check_range(t46 - 10, m_max_penalty_value);
    real_type t49  = P__[iP_u17];
    ok = ok && u17Limitation_min.check_range(-10 - t49, m_max_penalty_value);
    ok = ok && u17Limitation_max.check_range(t49 - 10, m_max_penalty_value);
    real_type t52  = P__[iP_u18];
    ok = ok && u18Limitation_min.check_range(-10 - t52, m_max_penalty_value);
    ok = ok && u18Limitation_max.check_range(t52 - 10, m_max_penalty_value);
    real_type t55  = P__[iP_u19];
    ok = ok && u19Limitation_min.check_range(-10 - t55, m_max_penalty_value);
    ok = ok && u19Limitation_max.check_range(t55 - 10, m_max_penalty_value);
    real_type t58  = P__[iP_u20];
    ok = ok && u20Limitation_min.check_range(-10 - t58, m_max_penalty_value);
    ok = ok && u20Limitation_max.check_range(t58 - 10, m_max_penalty_value);
    real_type t61  = ModelPars[iM_xy_bound];
    real_type t62  = X__[iX_xx1];
    ok = ok && xx1Limitation_min.check_range(-t61 - t62, m_max_penalty_value);
    ok = ok && xx1Limitation_max.check_range(t62 - t61, m_max_penalty_value);
    real_type t65  = X__[iX_yy1];
    ok = ok && yy1Limitation_min.check_range(-t61 - t65, m_max_penalty_value);
    ok = ok && yy1Limitation_max.check_range(t65 - t61, m_max_penalty_value);
    real_type t68  = X__[iX_xx2];
    ok = ok && xx2Limitation_min.check_range(-t61 - t68, m_max_penalty_value);
    ok = ok && xx2Limitation_max.check_range(t68 - t61, m_max_penalty_value);
    real_type t71  = X__[iX_yy2];
    ok = ok && yy2Limitation_min.check_range(-t61 - t71, m_max_penalty_value);
    ok = ok && yy2Limitation_max.check_range(t71 - t61, m_max_penalty_value);
    real_type t74  = X__[iX_xx3];
    ok = ok && xx3Limitation_min.check_range(-t61 - t74, m_max_penalty_value);
    ok = ok && xx3Limitation_max.check_range(t74 - t61, m_max_penalty_value);
    real_type t77  = X__[iX_yy3];
    ok = ok && yy3Limitation_min.check_range(-t61 - t77, m_max_penalty_value);
    ok = ok && yy3Limitation_max.check_range(t77 - t61, m_max_penalty_value);
    real_type t80  = X__[iX_xx4];
    ok = ok && xx4Limitation_min.check_range(-t61 - t80, m_max_penalty_value);
    ok = ok && xx4Limitation_max.check_range(t80 - t61, m_max_penalty_value);
    real_type t83  = X__[iX_yy4];
    ok = ok && yy4Limitation_min.check_range(-t61 - t83, m_max_penalty_value);
    ok = ok && yy4Limitation_max.check_range(t83 - t61, m_max_penalty_value);
    real_type t86  = X__[iX_xx5];
    ok = ok && xx5Limitation_min.check_range(-t61 - t86, m_max_penalty_value);
    ok = ok && xx5Limitation_max.check_range(t86 - t61, m_max_penalty_value);
    real_type t89  = X__[iX_yy5];
    ok = ok && yy5Limitation_min.check_range(-t61 - t89, m_max_penalty_value);
    ok = ok && yy5Limitation_max.check_range(t89 - t61, m_max_penalty_value);
    real_type t92  = X__[iX_xx6];
    ok = ok && xx6Limitation_min.check_range(-t61 - t92, m_max_penalty_value);
    ok = ok && xx6Limitation_max.check_range(t92 - t61, m_max_penalty_value);
    real_type t95  = X__[iX_yy6];
    ok = ok && yy6Limitation_min.check_range(-t61 - t95, m_max_penalty_value);
    ok = ok && yy6Limitation_max.check_range(t95 - t61, m_max_penalty_value);
    real_type t98  = X__[iX_xx7];
    ok = ok && xx7Limitation_min.check_range(-t61 - t98, m_max_penalty_value);
    ok = ok && xx7Limitation_max.check_range(t98 - t61, m_max_penalty_value);
    real_type t101 = X__[iX_yy7];
    ok = ok && yy7Limitation_min.check_range(-t61 - t101, m_max_penalty_value);
    ok = ok && yy7Limitation_max.check_range(t101 - t61, m_max_penalty_value);
    real_type t104 = X__[iX_xx8];
    ok = ok && xx8Limitation_min.check_range(-t61 - t104, m_max_penalty_value);
    ok = ok && xx8Limitation_max.check_range(t104 - t61, m_max_penalty_value);
    real_type t107 = X__[iX_yy8];
    ok = ok && yy8Limitation_min.check_range(-t61 - t107, m_max_penalty_value);
    ok = ok && yy8Limitation_max.check_range(t107 - t61, m_max_penalty_value);
    real_type t110 = X__[iX_xx9];
    ok = ok && xx9Limitation_min.check_range(-t61 - t110, m_max_penalty_value);
    ok = ok && xx9Limitation_max.check_range(t110 - t61, m_max_penalty_value);
    real_type t113 = X__[iX_yy9];
    ok = ok && yy9Limitation_min.check_range(-t61 - t113, m_max_penalty_value);
    ok = ok && yy9Limitation_max.check_range(t113 - t61, m_max_penalty_value);
    real_type t116 = X__[iX_xx10];
    ok = ok && xx10Limitation_min.check_range(-t61 - t116, m_max_penalty_value);
    ok = ok && xx10Limitation_max.check_range(t116 - t61, m_max_penalty_value);
    real_type t119 = X__[iX_yy10];
    ok = ok && yy10Limitation_min.check_range(-t61 - t119, m_max_penalty_value);
    ok = ok && yy10Limitation_max.check_range(t119 - t61, m_max_penalty_value);
    real_type t122 = X__[iX_xx11];
    ok = ok && xx11Limitation_min.check_range(-t61 - t122, m_max_penalty_value);
    ok = ok && xx11Limitation_max.check_range(t122 - t61, m_max_penalty_value);
    real_type t125 = X__[iX_yy11];
    ok = ok && yy11Limitation_min.check_range(-t61 - t125, m_max_penalty_value);
    ok = ok && yy11Limitation_max.check_range(t125 - t61, m_max_penalty_value);
    real_type t128 = X__[iX_xx12];
    ok = ok && xx12Limitation_min.check_range(-t61 - t128, m_max_penalty_value);
    ok = ok && xx12Limitation_max.check_range(t128 - t61, m_max_penalty_value);
    real_type t131 = X__[iX_yy12];
    ok = ok && yy12Limitation_min.check_range(-t61 - t131, m_max_penalty_value);
    ok = ok && yy12Limitation_max.check_range(t131 - t61, m_max_penalty_value);
    real_type t134 = X__[iX_xx13];
    ok = ok && xx13Limitation_min.check_range(-t61 - t134, m_max_penalty_value);
    ok = ok && xx13Limitation_max.check_range(t134 - t61, m_max_penalty_value);
    real_type t137 = X__[iX_yy13];
    ok = ok && yy13Limitation_min.check_range(-t61 - t137, m_max_penalty_value);
    ok = ok && yy13Limitation_max.check_range(t137 - t61, m_max_penalty_value);
    real_type t140 = X__[iX_xx14];
    ok = ok && xx14Limitation_min.check_range(-t61 - t140, m_max_penalty_value);
    ok = ok && xx14Limitation_max.check_range(t140 - t61, m_max_penalty_value);
    real_type t143 = X__[iX_yy14];
    ok = ok && yy14Limitation_min.check_range(-t61 - t143, m_max_penalty_value);
    ok = ok && yy14Limitation_max.check_range(t143 - t61, m_max_penalty_value);
    real_type t146 = X__[iX_xx15];
    ok = ok && xx15Limitation_min.check_range(-t61 - t146, m_max_penalty_value);
    ok = ok && xx15Limitation_max.check_range(t146 - t61, m_max_penalty_value);
    real_type t149 = X__[iX_yy15];
    ok = ok && yy15Limitation_min.check_range(-t61 - t149, m_max_penalty_value);
    ok = ok && yy15Limitation_max.check_range(t149 - t61, m_max_penalty_value);
    real_type t152 = X__[iX_xx16];
    ok = ok && xx16Limitation_min.check_range(-t61 - t152, m_max_penalty_value);
    ok = ok && xx16Limitation_max.check_range(t152 - t61, m_max_penalty_value);
    real_type t155 = X__[iX_yy16];
    ok = ok && yy16Limitation_min.check_range(-t61 - t155, m_max_penalty_value);
    ok = ok && yy16Limitation_max.check_range(t155 - t61, m_max_penalty_value);
    real_type t158 = X__[iX_xx17];
    ok = ok && xx17Limitation_min.check_range(-t61 - t158, m_max_penalty_value);
    ok = ok && xx17Limitation_max.check_range(t158 - t61, m_max_penalty_value);
    real_type t161 = X__[iX_yy17];
    ok = ok && yy17Limitation_min.check_range(-t61 - t161, m_max_penalty_value);
    ok = ok && yy17Limitation_max.check_range(t161 - t61, m_max_penalty_value);
    real_type t164 = X__[iX_xx18];
    ok = ok && xx18Limitation_min.check_range(-t61 - t164, m_max_penalty_value);
    ok = ok && xx18Limitation_max.check_range(t164 - t61, m_max_penalty_value);
    real_type t167 = X__[iX_yy18];
    ok = ok && yy18Limitation_min.check_range(-t61 - t167, m_max_penalty_value);
    ok = ok && yy18Limitation_max.check_range(t167 - t61, m_max_penalty_value);
    real_type t170 = X__[iX_xx19];
    ok = ok && xx19Limitation_min.check_range(-t61 - t170, m_max_penalty_value);
    ok = ok && xx19Limitation_max.check_range(t170 - t61, m_max_penalty_value);
    real_type t173 = X__[iX_yy19];
    ok = ok && yy19Limitation_min.check_range(-t61 - t173, m_max_penalty_value);
    ok = ok && yy19Limitation_max.check_range(t173 - t61, m_max_penalty_value);
    real_type t176 = X__[iX_xx20];
    ok = ok && xx20Limitation_min.check_range(-t61 - t176, m_max_penalty_value);
    ok = ok && xx20Limitation_max.check_range(t176 - t61, m_max_penalty_value);
    real_type t179 = X__[iX_yy20];
    ok = ok && yy20Limitation_min.check_range(-t61 - t179, m_max_penalty_value);
    ok = ok && yy20Limitation_max.check_range(t179 - t61, m_max_penalty_value);
    return ok;
  }

  /*\
   |   _   _        ____
   |  | | | |      / ___|_   _  ___  ___ ___
   |  | | | |_____| |  _| | | |/ _ \/ __/ __|
   |  | |_| |_____| |_| | |_| |  __/\__ \__ \
   |   \___/       \____|\__,_|\___||___/___/
  \*/

  integer ICLOCS_ContinuousMP::u_guess_numEqns() const { return 0; }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::u_guess_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        UGUESS__
  ) const {
    // no controls to compute
  }

  /*\
   |   _   _        ____ _               _
   |  | | | |      / ___| |__   ___  ___| | __
   |  | | | |_____| |   | '_ \ / _ \/ __| |/ /
   |  | |_| |_____| |___| | | |  __/ (__|   <
   |   \___/       \____|_| |_|\___|\___|_|\_\
  \*/

  bool
  ICLOCS_ContinuousMP::u_check_if_admissible(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    bool ok = true;
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    // no controls to check
    return ok;
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_Guess.cc
