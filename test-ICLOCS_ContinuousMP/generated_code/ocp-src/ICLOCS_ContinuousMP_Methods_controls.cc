/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


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


namespace ICLOCS_ContinuousMPDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS_ContinuousMP::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[80], LM__[80];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    LM__[8] = (LL__[8]+LR__[8])/2;
    LM__[9] = (LL__[9]+LR__[9])/2;
    LM__[10] = (LL__[10]+LR__[10])/2;
    LM__[11] = (LL__[11]+LR__[11])/2;
    LM__[12] = (LL__[12]+LR__[12])/2;
    LM__[13] = (LL__[13]+LR__[13])/2;
    LM__[14] = (LL__[14]+LR__[14])/2;
    LM__[15] = (LL__[15]+LR__[15])/2;
    LM__[16] = (LL__[16]+LR__[16])/2;
    LM__[17] = (LL__[17]+LR__[17])/2;
    LM__[18] = (LL__[18]+LR__[18])/2;
    LM__[19] = (LL__[19]+LR__[19])/2;
    LM__[20] = (LL__[20]+LR__[20])/2;
    LM__[21] = (LL__[21]+LR__[21])/2;
    LM__[22] = (LL__[22]+LR__[22])/2;
    LM__[23] = (LL__[23]+LR__[23])/2;
    LM__[24] = (LL__[24]+LR__[24])/2;
    LM__[25] = (LL__[25]+LR__[25])/2;
    LM__[26] = (LL__[26]+LR__[26])/2;
    LM__[27] = (LL__[27]+LR__[27])/2;
    LM__[28] = (LL__[28]+LR__[28])/2;
    LM__[29] = (LL__[29]+LR__[29])/2;
    LM__[30] = (LL__[30]+LR__[30])/2;
    LM__[31] = (LL__[31]+LR__[31])/2;
    LM__[32] = (LL__[32]+LR__[32])/2;
    LM__[33] = (LL__[33]+LR__[33])/2;
    LM__[34] = (LL__[34]+LR__[34])/2;
    LM__[35] = (LL__[35]+LR__[35])/2;
    LM__[36] = (LL__[36]+LR__[36])/2;
    LM__[37] = (LL__[37]+LR__[37])/2;
    LM__[38] = (LL__[38]+LR__[38])/2;
    LM__[39] = (LL__[39]+LR__[39])/2;
    LM__[40] = (LL__[40]+LR__[40])/2;
    LM__[41] = (LL__[41]+LR__[41])/2;
    LM__[42] = (LL__[42]+LR__[42])/2;
    LM__[43] = (LL__[43]+LR__[43])/2;
    LM__[44] = (LL__[44]+LR__[44])/2;
    LM__[45] = (LL__[45]+LR__[45])/2;
    LM__[46] = (LL__[46]+LR__[46])/2;
    LM__[47] = (LL__[47]+LR__[47])/2;
    LM__[48] = (LL__[48]+LR__[48])/2;
    LM__[49] = (LL__[49]+LR__[49])/2;
    LM__[50] = (LL__[50]+LR__[50])/2;
    LM__[51] = (LL__[51]+LR__[51])/2;
    LM__[52] = (LL__[52]+LR__[52])/2;
    LM__[53] = (LL__[53]+LR__[53])/2;
    LM__[54] = (LL__[54]+LR__[54])/2;
    LM__[55] = (LL__[55]+LR__[55])/2;
    LM__[56] = (LL__[56]+LR__[56])/2;
    LM__[57] = (LL__[57]+LR__[57])/2;
    LM__[58] = (LL__[58]+LR__[58])/2;
    LM__[59] = (LL__[59]+LR__[59])/2;
    LM__[60] = (LL__[60]+LR__[60])/2;
    LM__[61] = (LL__[61]+LR__[61])/2;
    LM__[62] = (LL__[62]+LR__[62])/2;
    LM__[63] = (LL__[63]+LR__[63])/2;
    LM__[64] = (LL__[64]+LR__[64])/2;
    LM__[65] = (LL__[65]+LR__[65])/2;
    LM__[66] = (LL__[66]+LR__[66])/2;
    LM__[67] = (LL__[67]+LR__[67])/2;
    LM__[68] = (LL__[68]+LR__[68])/2;
    LM__[69] = (LL__[69]+LR__[69])/2;
    LM__[70] = (LL__[70]+LR__[70])/2;
    LM__[71] = (LL__[71]+LR__[71])/2;
    LM__[72] = (LL__[72]+LR__[72])/2;
    LM__[73] = (LL__[73]+LR__[73])/2;
    LM__[74] = (LL__[74]+LR__[74])/2;
    LM__[75] = (LL__[75]+LR__[75])/2;
    LM__[76] = (LL__[76]+LR__[76])/2;
    LM__[77] = (LL__[77]+LR__[77])/2;
    LM__[78] = (LL__[78]+LR__[78])/2;
    LM__[79] = (LL__[79]+LR__[79])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = XM__[69];
    real_type t4   = QM__[0];
    real_type t6   = sin(t4 + 9);
    real_type t11  = XM__[70];
    real_type t14  = sin(t4 + 10);
    real_type t19  = XM__[71];
    real_type t22  = sin(t4 + 11);
    real_type t27  = XM__[72];
    real_type t30  = sin(t4 + 12);
    real_type t35  = XM__[79];
    real_type t38  = sin(t4 + 19);
    real_type t43  = XM__[51];
    real_type t44  = sin(t43);
    real_type t46  = P__[iP_u12];
    real_type t50  = XM__[11];
    real_type t51  = sin(t50);
    real_type t55  = XM__[52];
    real_type t56  = sin(t55);
    real_type t58  = P__[iP_u13];
    real_type t62  = XM__[12];
    real_type t63  = sin(t62);
    real_type t67  = XM__[53];
    real_type t68  = sin(t67);
    real_type t70  = P__[iP_u14];
    real_type t74  = XM__[13];
    real_type t75  = sin(t74);
    real_type t79  = XM__[54];
    real_type t80  = sin(t79);
    real_type t82  = P__[iP_u15];
    real_type t86  = XM__[14];
    real_type t87  = sin(t86);
    real_type t91  = XM__[55];
    real_type t92  = sin(t91);
    real_type t94  = P__[iP_u16];
    real_type t98  = XM__[15];
    real_type t99  = sin(t98);
    real_type t102 = (0.12e1 * t2 + 0.1e0 * t6) * LM__[49] + (0.12e1 * t11 + 0.1e0 * t14) * LM__[50] + (0.12e1 * t19 + 0.1e0 * t22) * LM__[51] + (0.12e1 * t27 + 0.1e0 * t30) * LM__[52] + (0.12e1 * t35 + 0.1e0 * t38) * LM__[59] + (0.2e0 * t44 + t46) * LM__[71] + (t51 + t46) * LM__[31] + (0.2e0 * t56 + t58) * LM__[72] + (t63 + t58) * LM__[32] + (0.2e0 * t68 + t70) * LM__[73] + (t75 + t70) * LM__[33] + (0.2e0 * t80 + t82) * LM__[74] + (t87 + t82) * LM__[34] + (0.2e0 * t92 + t94) * LM__[75] + (t99 + t94) * LM__[35];
    real_type t104 = XM__[56];
    real_type t105 = sin(t104);
    real_type t107 = P__[iP_u17];
    real_type t111 = XM__[16];
    real_type t112 = sin(t111);
    real_type t116 = XM__[57];
    real_type t117 = sin(t116);
    real_type t119 = P__[iP_u18];
    real_type t123 = XM__[17];
    real_type t124 = sin(t123);
    real_type t128 = XM__[18];
    real_type t129 = sin(t128);
    real_type t130 = P__[iP_u19];
    real_type t134 = XM__[58];
    real_type t135 = sin(t134);
    real_type t140 = XM__[19];
    real_type t141 = sin(t140);
    real_type t142 = P__[iP_u20];
    real_type t146 = XM__[59];
    real_type t147 = sin(t146);
    real_type t152 = XM__[60];
    real_type t154 = sin(t4);
    real_type t159 = XM__[61];
    real_type t162 = sin(t4 + 1);
    real_type t167 = XM__[62];
    real_type t170 = sin(t4 + 2);
    real_type t175 = XM__[63];
    real_type t178 = sin(t4 + 3);
    real_type t183 = XM__[64];
    real_type t186 = sin(t4 + 4);
    real_type t191 = XM__[65];
    real_type t194 = sin(t4 + 5);
    real_type t199 = XM__[66];
    real_type t202 = sin(t4 + 6);
    real_type t206 = (0.2e0 * t105 + t107) * LM__[76] + (t112 + t107) * LM__[36] + (0.2e0 * t117 + t119) * LM__[77] + (t124 + t119) * LM__[37] + (t129 + t130) * LM__[38] + (0.2e0 * t135 + t130) * LM__[78] + (t141 + t142) * LM__[39] + (0.2e0 * t147 + t142) * LM__[79] + (0.12e1 * t152 + 0.1e0 * t154) * LM__[40] + (0.12e1 * t159 + 0.1e0 * t162) * LM__[41] + (0.12e1 * t167 + 0.1e0 * t170) * LM__[42] + (0.12e1 * t175 + 0.1e0 * t178) * LM__[43] + (0.12e1 * t183 + 0.1e0 * t186) * LM__[44] + (0.12e1 * t191 + 0.1e0 * t194) * LM__[45] + (0.12e1 * t199 + 0.1e0 * t202) * LM__[46];
    real_type t209 = XM__[67];
    real_type t212 = sin(t4 + 7);
    real_type t217 = XM__[68];
    real_type t220 = sin(t4 + 8);
    real_type t225 = XM__[1];
    real_type t226 = sin(t225);
    real_type t227 = P__[iP_u2];
    real_type t231 = XM__[42];
    real_type t232 = sin(t231);
    real_type t234 = P__[iP_u3];
    real_type t238 = XM__[2];
    real_type t239 = sin(t238);
    real_type t243 = XM__[43];
    real_type t244 = sin(t243);
    real_type t246 = P__[iP_u4];
    real_type t250 = XM__[3];
    real_type t251 = sin(t250);
    real_type t255 = XM__[44];
    real_type t256 = sin(t255);
    real_type t258 = P__[iP_u5];
    real_type t262 = XM__[4];
    real_type t263 = sin(t262);
    real_type t267 = XM__[45];
    real_type t268 = sin(t267);
    real_type t270 = P__[iP_u6];
    real_type t274 = XM__[5];
    real_type t275 = sin(t274);
    real_type t279 = XM__[46];
    real_type t280 = sin(t279);
    real_type t282 = P__[iP_u7];
    real_type t286 = XM__[6];
    real_type t287 = sin(t286);
    real_type t291 = XM__[47];
    real_type t292 = sin(t291);
    real_type t294 = P__[iP_u8];
    real_type t298 = XM__[7];
    real_type t299 = sin(t298);
    real_type t302 = (0.12e1 * t209 + 0.1e0 * t212) * LM__[47] + (0.12e1 * t217 + 0.1e0 * t220) * LM__[48] + (t226 + t227) * LM__[21] + (0.2e0 * t232 + t234) * LM__[62] + (t239 + t234) * LM__[22] + (0.2e0 * t244 + t246) * LM__[63] + (t251 + t246) * LM__[23] + (0.2e0 * t256 + t258) * LM__[64] + (t263 + t258) * LM__[24] + (0.2e0 * t268 + t270) * LM__[65] + (t275 + t270) * LM__[25] + (0.2e0 * t280 + t282) * LM__[66] + (t287 + t282) * LM__[26] + (0.2e0 * t292 + t294) * LM__[67] + (t299 + t294) * LM__[27];
    real_type t304 = XM__[48];
    real_type t305 = sin(t304);
    real_type t307 = P__[iP_u9];
    real_type t311 = XM__[8];
    real_type t312 = sin(t311);
    real_type t316 = XM__[49];
    real_type t317 = sin(t316);
    real_type t319 = P__[iP_u10];
    real_type t323 = XM__[9];
    real_type t324 = sin(t323);
    real_type t328 = XM__[50];
    real_type t329 = sin(t328);
    real_type t331 = P__[iP_u11];
    real_type t335 = XM__[10];
    real_type t336 = sin(t335);
    real_type t340 = XM__[20];
    real_type t343 = XM__[21];
    real_type t346 = XM__[22];
    real_type t349 = XM__[23];
    real_type t352 = XM__[24];
    real_type t355 = XM__[25];
    real_type t358 = XM__[26];
    real_type t361 = XM__[27];
    real_type t364 = XM__[28];
    real_type t366 = (0.2e0 * t305 + t307) * LM__[68] + (t312 + t307) * LM__[28] + (0.2e0 * t317 + t319) * LM__[69] + (t324 + t319) * LM__[29] + (0.2e0 * t329 + t331) * LM__[70] + (t336 + t331) * LM__[30] + t340 * LM__[0] + t343 * LM__[1] + t346 * LM__[2] + t349 * LM__[3] + t352 * LM__[4] + t355 * LM__[5] + t358 * LM__[6] + t361 * LM__[7] + t364 * LM__[8];
    real_type t370 = XM__[29];
    real_type t373 = XM__[30];
    real_type t376 = XM__[31];
    real_type t379 = XM__[32];
    real_type t382 = XM__[33];
    real_type t385 = XM__[34];
    real_type t388 = XM__[35];
    real_type t391 = XM__[36];
    real_type t394 = XM__[37];
    real_type t397 = XM__[38];
    real_type t400 = XM__[39];
    real_type t403 = XM__[73];
    real_type t406 = sin(t4 + 13);
    real_type t411 = XM__[74];
    real_type t414 = sin(t4 + 14);
    real_type t419 = XM__[75];
    real_type t422 = sin(t4 + 15);
    real_type t427 = XM__[76];
    real_type t430 = sin(t4 + 16);
    real_type t434 = t370 * LM__[9] + t373 * LM__[10] + t376 * LM__[11] + t379 * LM__[12] + t382 * LM__[13] + t385 * LM__[14] + t388 * LM__[15] + t391 * LM__[16] + t394 * LM__[17] + t397 * LM__[18] + t400 * LM__[19] + (0.12e1 * t403 + 0.1e0 * t406) * LM__[53] + (0.12e1 * t411 + 0.1e0 * t414) * LM__[54] + (0.12e1 * t419 + 0.1e0 * t422) * LM__[55] + (0.12e1 * t427 + 0.1e0 * t430) * LM__[56];
    real_type t436 = XM__[77];
    real_type t439 = sin(t4 + 17);
    real_type t444 = XM__[78];
    real_type t447 = sin(t4 + 18);
    real_type t452 = XM__[40];
    real_type t453 = sin(t452);
    real_type t455 = P__[iP_u1];
    real_type t459 = XM__[0];
    real_type t460 = sin(t459);
    real_type t464 = XM__[41];
    real_type t465 = sin(t464);
    real_type t470 = u1Limitation_min(-10 - t455);
    real_type t472 = u1Limitation_max(t455 - 10);
    real_type t474 = u2Limitation_min(-10 - t227);
    real_type t476 = u2Limitation_max(t227 - 10);
    real_type t478 = u3Limitation_min(-10 - t234);
    real_type t480 = u3Limitation_max(t234 - 10);
    real_type t482 = u4Limitation_min(-10 - t246);
    real_type t484 = u4Limitation_max(t246 - 10);
    real_type t486 = u5Limitation_min(-10 - t258);
    real_type t488 = u5Limitation_max(t258 - 10);
    real_type t489 = (0.12e1 * t436 + 0.1e0 * t439) * LM__[57] + (0.12e1 * t444 + 0.1e0 * t447) * LM__[58] + (0.2e0 * t453 + t455) * LM__[60] + (t460 + t455) * LM__[20] + (0.2e0 * t465 + t227) * LM__[61] + t470 + t472 + t474 + t476 + t478 + t480 + t482 + t484 + t486 + t488;
    real_type t492 = u6Limitation_min(-10 - t270);
    real_type t494 = u6Limitation_max(t270 - 10);
    real_type t496 = u7Limitation_min(-10 - t282);
    real_type t498 = u7Limitation_max(t282 - 10);
    real_type t500 = u8Limitation_min(-10 - t294);
    real_type t502 = u8Limitation_max(t294 - 10);
    real_type t504 = u9Limitation_min(-10 - t307);
    real_type t506 = u9Limitation_max(t307 - 10);
    real_type t508 = u10Limitation_min(-10 - t319);
    real_type t510 = u10Limitation_max(t319 - 10);
    real_type t512 = u11Limitation_min(-10 - t331);
    real_type t514 = u11Limitation_max(t331 - 10);
    real_type t516 = u12Limitation_min(-10 - t46);
    real_type t518 = u12Limitation_max(t46 - 10);
    real_type t520 = u13Limitation_min(-10 - t58);
    real_type t521 = t492 + t494 + t496 + t498 + t500 + t502 + t504 + t506 + t508 + t510 + t512 + t514 + t516 + t518 + t520;
    real_type t523 = u13Limitation_max(t58 - 10);
    real_type t525 = u14Limitation_min(-10 - t70);
    real_type t527 = u14Limitation_max(t70 - 10);
    real_type t529 = u15Limitation_min(-10 - t82);
    real_type t531 = u15Limitation_max(t82 - 10);
    real_type t533 = u16Limitation_min(-10 - t94);
    real_type t535 = u16Limitation_max(t94 - 10);
    real_type t537 = u17Limitation_min(-10 - t107);
    real_type t539 = u17Limitation_max(t107 - 10);
    real_type t541 = u18Limitation_min(-10 - t119);
    real_type t543 = u18Limitation_max(t119 - 10);
    real_type t545 = u19Limitation_min(-10 - t130);
    real_type t547 = u19Limitation_max(t130 - 10);
    real_type t549 = u20Limitation_min(-10 - t142);
    real_type t551 = u20Limitation_max(t142 - 10);
    real_type t552 = t523 + t525 + t527 + t529 + t531 + t533 + t535 + t537 + t539 + t541 + t543 + t545 + t547 + t549 + t551;
    real_type t556 = t459 * t459;
    real_type t558 = t225 * t225;
    real_type t560 = t238 * t238;
    real_type t562 = t250 * t250;
    real_type t564 = t262 * t262;
    real_type t566 = t274 * t274;
    real_type t568 = t286 * t286;
    real_type t570 = t298 * t298;
    real_type t572 = t311 * t311;
    real_type t574 = t323 * t323;
    real_type t576 = t335 * t335;
    real_type t578 = t50 * t50;
    real_type t580 = t62 * t62;
    real_type t582 = t74 * t74;
    real_type t584 = t86 * t86;
    real_type t586 = 20 * t556 + 19 * t558 + 18 * t560 + 17 * t562 + 16 * t564 + 15 * t566 + 14 * t568 + 13 * t570 + 12 * t572 + 11 * t574 + 10 * t576 + 9 * t578 + 8 * t580 + 7 * t582 + 6 * t584;
    real_type t587 = t98 * t98;
    real_type t589 = t111 * t111;
    real_type t591 = t123 * t123;
    real_type t593 = t128 * t128;
    real_type t595 = t140 * t140;
    real_type t596 = t340 * t340;
    real_type t598 = t343 * t343;
    real_type t600 = t346 * t346;
    real_type t602 = t349 * t349;
    real_type t604 = t352 * t352;
    real_type t606 = t355 * t355;
    real_type t608 = t358 * t358;
    real_type t610 = t361 * t361;
    real_type t612 = t364 * t364;
    real_type t614 = t370 * t370;
    real_type t616 = 5 * t587 + 4 * t589 + 3 * t591 + 2 * t593 + t595 + 20 * t596 + 19 * t598 + 18 * t600 + 17 * t602 + 16 * t604 + 15 * t606 + 14 * t608 + 13 * t610 + 12 * t612 + 11 * t614;
    real_type t618 = t373 * t373;
    real_type t620 = t376 * t376;
    real_type t622 = t379 * t379;
    real_type t624 = t382 * t382;
    real_type t626 = t385 * t385;
    real_type t628 = t388 * t388;
    real_type t630 = t391 * t391;
    real_type t632 = t394 * t394;
    real_type t634 = t397 * t397;
    real_type t636 = t400 * t400;
    real_type t637 = ModelPars[iM_xy_bound];
    real_type t639 = xx1Limitation_min(-t637 - t452);
    real_type t641 = xx1Limitation_max(t452 - t637);
    real_type t643 = xx2Limitation_min(-t637 - t464);
    real_type t645 = xx2Limitation_max(t464 - t637);
    real_type t647 = xx3Limitation_min(-t637 - t231);
    real_type t648 = 10 * t618 + 9 * t620 + 8 * t622 + 7 * t624 + 6 * t626 + 5 * t628 + 4 * t630 + 3 * t632 + 2 * t634 + t636 + t639 + t641 + t643 + t645 + t647;
    real_type t650 = xx3Limitation_max(t231 - t637);
    real_type t652 = xx4Limitation_min(-t637 - t243);
    real_type t654 = xx4Limitation_max(t243 - t637);
    real_type t656 = xx5Limitation_min(-t637 - t255);
    real_type t658 = xx5Limitation_max(t255 - t637);
    real_type t660 = xx6Limitation_min(-t637 - t267);
    real_type t662 = xx6Limitation_max(t267 - t637);
    real_type t664 = xx7Limitation_min(-t637 - t279);
    real_type t666 = xx7Limitation_max(t279 - t637);
    real_type t668 = xx8Limitation_min(-t637 - t291);
    real_type t670 = xx8Limitation_max(t291 - t637);
    real_type t672 = xx9Limitation_min(-t637 - t304);
    real_type t674 = xx9Limitation_max(t304 - t637);
    real_type t676 = xx10Limitation_min(-t637 - t316);
    real_type t678 = xx10Limitation_max(t316 - t637);
    real_type t679 = t650 + t652 + t654 + t656 + t658 + t660 + t662 + t664 + t666 + t668 + t670 + t672 + t674 + t676 + t678;
    real_type t683 = xx11Limitation_min(-t637 - t328);
    real_type t685 = xx11Limitation_max(t328 - t637);
    real_type t687 = xx12Limitation_min(-t637 - t43);
    real_type t689 = xx12Limitation_max(t43 - t637);
    real_type t691 = xx13Limitation_min(-t637 - t55);
    real_type t693 = xx13Limitation_max(t55 - t637);
    real_type t695 = xx14Limitation_min(-t637 - t67);
    real_type t697 = xx14Limitation_max(t67 - t637);
    real_type t699 = xx15Limitation_min(-t637 - t79);
    real_type t701 = xx15Limitation_max(t79 - t637);
    real_type t703 = xx16Limitation_min(-t637 - t91);
    real_type t705 = xx16Limitation_max(t91 - t637);
    real_type t707 = xx17Limitation_min(-t637 - t104);
    real_type t709 = xx17Limitation_max(t104 - t637);
    real_type t711 = xx18Limitation_min(-t637 - t116);
    real_type t712 = t683 + t685 + t687 + t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = xx18Limitation_max(t116 - t637);
    real_type t716 = xx19Limitation_min(-t637 - t134);
    real_type t718 = xx19Limitation_max(t134 - t637);
    real_type t720 = xx20Limitation_min(-t637 - t146);
    real_type t722 = xx20Limitation_max(t146 - t637);
    real_type t724 = yy1Limitation_min(-t637 - t152);
    real_type t726 = yy1Limitation_max(t152 - t637);
    real_type t728 = yy2Limitation_min(-t637 - t159);
    real_type t730 = yy2Limitation_max(t159 - t637);
    real_type t732 = yy3Limitation_min(-t637 - t167);
    real_type t734 = yy3Limitation_max(t167 - t637);
    real_type t736 = yy4Limitation_min(-t637 - t175);
    real_type t738 = yy4Limitation_max(t175 - t637);
    real_type t740 = yy5Limitation_min(-t637 - t183);
    real_type t742 = yy5Limitation_max(t183 - t637);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = yy6Limitation_min(-t637 - t191);
    real_type t748 = yy6Limitation_max(t191 - t637);
    real_type t750 = yy7Limitation_min(-t637 - t199);
    real_type t752 = yy7Limitation_max(t199 - t637);
    real_type t754 = yy8Limitation_min(-t637 - t209);
    real_type t756 = yy8Limitation_max(t209 - t637);
    real_type t758 = yy9Limitation_min(-t637 - t217);
    real_type t760 = yy9Limitation_max(t217 - t637);
    real_type t762 = yy10Limitation_min(-t637 - t2);
    real_type t764 = yy10Limitation_max(t2 - t637);
    real_type t766 = yy11Limitation_min(-t637 - t11);
    real_type t768 = yy11Limitation_max(t11 - t637);
    real_type t770 = yy12Limitation_min(-t637 - t19);
    real_type t772 = yy12Limitation_max(t19 - t637);
    real_type t774 = yy13Limitation_min(-t637 - t27);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = yy13Limitation_max(t27 - t637);
    real_type t779 = yy14Limitation_min(-t637 - t403);
    real_type t781 = yy14Limitation_max(t403 - t637);
    real_type t783 = yy15Limitation_min(-t637 - t411);
    real_type t785 = yy15Limitation_max(t411 - t637);
    real_type t787 = yy16Limitation_min(-t637 - t419);
    real_type t789 = yy16Limitation_max(t419 - t637);
    real_type t791 = yy17Limitation_min(-t637 - t427);
    real_type t793 = yy17Limitation_max(t427 - t637);
    real_type t795 = yy18Limitation_min(-t637 - t436);
    real_type t797 = yy18Limitation_max(t436 - t637);
    real_type t799 = yy19Limitation_min(-t637 - t444);
    real_type t801 = yy19Limitation_max(t444 - t637);
    real_type t803 = yy20Limitation_min(-t637 - t35);
    real_type t805 = yy20Limitation_max(t35 - t637);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t102 + t206 + t302 + t366 + t434 + t489 + t521 + t552 + t586 + t616 + t648 + t679 + t712 + t743 + t775 + t806;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::g_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[80], LM__[80];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    LM__[8] = (LL__[8]+LR__[8])/2;
    LM__[9] = (LL__[9]+LR__[9])/2;
    LM__[10] = (LL__[10]+LR__[10])/2;
    LM__[11] = (LL__[11]+LR__[11])/2;
    LM__[12] = (LL__[12]+LR__[12])/2;
    LM__[13] = (LL__[13]+LR__[13])/2;
    LM__[14] = (LL__[14]+LR__[14])/2;
    LM__[15] = (LL__[15]+LR__[15])/2;
    LM__[16] = (LL__[16]+LR__[16])/2;
    LM__[17] = (LL__[17]+LR__[17])/2;
    LM__[18] = (LL__[18]+LR__[18])/2;
    LM__[19] = (LL__[19]+LR__[19])/2;
    LM__[20] = (LL__[20]+LR__[20])/2;
    LM__[21] = (LL__[21]+LR__[21])/2;
    LM__[22] = (LL__[22]+LR__[22])/2;
    LM__[23] = (LL__[23]+LR__[23])/2;
    LM__[24] = (LL__[24]+LR__[24])/2;
    LM__[25] = (LL__[25]+LR__[25])/2;
    LM__[26] = (LL__[26]+LR__[26])/2;
    LM__[27] = (LL__[27]+LR__[27])/2;
    LM__[28] = (LL__[28]+LR__[28])/2;
    LM__[29] = (LL__[29]+LR__[29])/2;
    LM__[30] = (LL__[30]+LR__[30])/2;
    LM__[31] = (LL__[31]+LR__[31])/2;
    LM__[32] = (LL__[32]+LR__[32])/2;
    LM__[33] = (LL__[33]+LR__[33])/2;
    LM__[34] = (LL__[34]+LR__[34])/2;
    LM__[35] = (LL__[35]+LR__[35])/2;
    LM__[36] = (LL__[36]+LR__[36])/2;
    LM__[37] = (LL__[37]+LR__[37])/2;
    LM__[38] = (LL__[38]+LR__[38])/2;
    LM__[39] = (LL__[39]+LR__[39])/2;
    LM__[40] = (LL__[40]+LR__[40])/2;
    LM__[41] = (LL__[41]+LR__[41])/2;
    LM__[42] = (LL__[42]+LR__[42])/2;
    LM__[43] = (LL__[43]+LR__[43])/2;
    LM__[44] = (LL__[44]+LR__[44])/2;
    LM__[45] = (LL__[45]+LR__[45])/2;
    LM__[46] = (LL__[46]+LR__[46])/2;
    LM__[47] = (LL__[47]+LR__[47])/2;
    LM__[48] = (LL__[48]+LR__[48])/2;
    LM__[49] = (LL__[49]+LR__[49])/2;
    LM__[50] = (LL__[50]+LR__[50])/2;
    LM__[51] = (LL__[51]+LR__[51])/2;
    LM__[52] = (LL__[52]+LR__[52])/2;
    LM__[53] = (LL__[53]+LR__[53])/2;
    LM__[54] = (LL__[54]+LR__[54])/2;
    LM__[55] = (LL__[55]+LR__[55])/2;
    LM__[56] = (LL__[56]+LR__[56])/2;
    LM__[57] = (LL__[57]+LR__[57])/2;
    LM__[58] = (LL__[58]+LR__[58])/2;
    LM__[59] = (LL__[59]+LR__[59])/2;
    LM__[60] = (LL__[60]+LR__[60])/2;
    LM__[61] = (LL__[61]+LR__[61])/2;
    LM__[62] = (LL__[62]+LR__[62])/2;
    LM__[63] = (LL__[63]+LR__[63])/2;
    LM__[64] = (LL__[64]+LR__[64])/2;
    LM__[65] = (LL__[65]+LR__[65])/2;
    LM__[66] = (LL__[66]+LR__[66])/2;
    LM__[67] = (LL__[67]+LR__[67])/2;
    LM__[68] = (LL__[68]+LR__[68])/2;
    LM__[69] = (LL__[69]+LR__[69])/2;
    LM__[70] = (LL__[70]+LR__[70])/2;
    LM__[71] = (LL__[71]+LR__[71])/2;
    LM__[72] = (LL__[72]+LR__[72])/2;
    LM__[73] = (LL__[73]+LR__[73])/2;
    LM__[74] = (LL__[74]+LR__[74])/2;
    LM__[75] = (LL__[75]+LR__[75])/2;
    LM__[76] = (LL__[76]+LR__[76])/2;
    LM__[77] = (LL__[77]+LR__[77])/2;
    LM__[78] = (LL__[78]+LR__[78])/2;
    LM__[79] = (LL__[79]+LR__[79])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DgDxlxlp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DgDxlxlp_numCols() const { return 340; }
  integer ICLOCS_ContinuousMP::DgDxlxlp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DgDu_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DgDu_numCols() const { return 0; }
  integer ICLOCS_ContinuousMP::DgDu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  ICLOCS_ContinuousMP::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    // no controls to compute
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  ICLOCS_ContinuousMP::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_xx7];
    real_type t4   = xx7Limitation_min(-t1 - t2);
    real_type t6   = xx7Limitation_max(t2 - t1);
    real_type t7   = X__[iX_xx8];
    real_type t9   = xx8Limitation_min(-t1 - t7);
    real_type t11  = xx8Limitation_max(t7 - t1);
    real_type t12  = X__[iX_xx5];
    real_type t14  = xx5Limitation_min(-t1 - t12);
    real_type t16  = xx5Limitation_max(t12 - t1);
    real_type t17  = X__[iX_xx6];
    real_type t19  = xx6Limitation_min(-t1 - t17);
    real_type t21  = xx6Limitation_max(t17 - t1);
    real_type t22  = X__[iX_xx3];
    real_type t24  = xx3Limitation_max(t22 - t1);
    real_type t25  = X__[iX_xx4];
    real_type t27  = xx4Limitation_min(-t1 - t25);
    real_type t29  = xx4Limitation_max(t25 - t1);
    real_type t31  = X__[iX_xx14];
    real_type t32  = sin(t31);
    real_type t34  = P__[iP_u14];
    real_type t36  = pow(V__[73] - 0.2e0 * t32 - t34, 2);
    real_type t37  = t4 + t6 + t9 + t11 + t14 + t16 + t19 + t21 + t24 + t27 + t29 + t36;
    real_type t38  = P__[iP_u15];
    real_type t40  = u15Limitation_min(-10 - t38);
    real_type t42  = u15Limitation_max(t38 - 10);
    real_type t45  = sin(X__[iX_x15]);
    real_type t47  = pow(V__[34] - t45 - t38, 2);
    real_type t49  = X__[iX_xx13];
    real_type t50  = sin(t49);
    real_type t52  = P__[iP_u13];
    real_type t54  = pow(V__[72] - 0.2e0 * t50 - t52, 2);
    real_type t56  = u14Limitation_min(-10 - t34);
    real_type t58  = u14Limitation_max(t34 - 10);
    real_type t61  = sin(X__[iX_x14]);
    real_type t63  = pow(V__[33] - t61 - t34, 2);
    real_type t64  = X__[iX_xx1];
    real_type t66  = xx1Limitation_max(t64 - t1);
    real_type t67  = X__[iX_xx2];
    real_type t69  = xx2Limitation_min(-t1 - t67);
    real_type t71  = xx2Limitation_max(t67 - t1);
    real_type t73  = xx3Limitation_min(-t1 - t22);
    real_type t76  = sin(X__[iX_x16]);
    real_type t77  = P__[iP_u16];
    real_type t79  = pow(V__[35] - t76 - t77, 2);
    real_type t81  = X__[iX_xx16];
    real_type t82  = sin(t81);
    real_type t85  = pow(V__[75] - 0.2e0 * t82 - t77, 2);
    real_type t86  = t40 + t42 + t47 + t54 + t56 + t58 + t63 + t66 + t69 + t71 + t73 + t79 + t85;
    real_type t88  = P__[iP_u17];
    real_type t90  = u17Limitation_min(-10 - t88);
    real_type t92  = X__[iX_xx15];
    real_type t93  = sin(t92);
    real_type t96  = pow(V__[74] - 0.2e0 * t93 - t38, 2);
    real_type t98  = u16Limitation_min(-10 - t77);
    real_type t100 = u16Limitation_max(t77 - 10);
    real_type t104 = pow(V__[13] - X__[iX_y14], 2);
    real_type t108 = pow(V__[14] - X__[iX_y15], 2);
    real_type t112 = pow(V__[15] - X__[iX_y16], 2);
    real_type t116 = pow(V__[9] - X__[iX_y10], 2);
    real_type t120 = pow(V__[10] - X__[iX_y11], 2);
    real_type t124 = pow(V__[11] - X__[iX_y12], 2);
    real_type t128 = pow(V__[12] - X__[iX_y13], 2);
    real_type t130 = X__[iX_yy8];
    real_type t132 = Q__[iQ_zeta];
    real_type t134 = sin(t132 + 7);
    real_type t137 = pow(V__[47] - 0.12e1 * t130 - 0.1e0 * t134, 2);
    real_type t138 = t90 + t96 + t98 + t100 + t104 + t108 + t112 + t116 + t120 + t124 + t128 + t137;
    real_type t140 = X__[iX_yy9];
    real_type t143 = sin(t132 + 8);
    real_type t146 = pow(V__[48] - 0.12e1 * t140 - 0.1e0 * t143, 2);
    real_type t148 = sin(t22);
    real_type t150 = P__[iP_u3];
    real_type t152 = pow(V__[62] - 0.2e0 * t148 - t150, 2);
    real_type t153 = P__[iP_u4];
    real_type t155 = u4Limitation_min(-10 - t153);
    real_type t157 = u4Limitation_max(t153 - 10);
    real_type t160 = sin(X__[iX_x4]);
    real_type t162 = pow(V__[23] - t160 - t153, 2);
    real_type t164 = u3Limitation_min(-10 - t150);
    real_type t166 = u3Limitation_max(t150 - 10);
    real_type t169 = sin(X__[iX_x3]);
    real_type t171 = pow(V__[22] - t169 - t150, 2);
    real_type t173 = X__[iX_yy6];
    real_type t176 = sin(t132 + 5);
    real_type t179 = pow(V__[45] - 0.12e1 * t173 - 0.1e0 * t176, 2);
    real_type t181 = X__[iX_yy7];
    real_type t184 = sin(t132 + 6);
    real_type t187 = pow(V__[46] - 0.12e1 * t181 - 0.1e0 * t184, 2);
    real_type t188 = P__[iP_u2];
    real_type t190 = u2Limitation_min(-10 - t188);
    real_type t192 = u2Limitation_max(t188 - 10);
    real_type t195 = sin(X__[iX_x2]);
    real_type t197 = pow(V__[21] - t195 - t188, 2);
    real_type t198 = t146 + t152 + t155 + t157 + t162 + t164 + t166 + t171 + t179 + t187 + t190 + t192 + t197;
    real_type t202 = sin(t67);
    real_type t205 = pow(V__[61] - 0.2e0 * t202 - t188, 2);
    real_type t207 = X__[iX_yy3];
    real_type t210 = sin(t132 + 2);
    real_type t213 = pow(V__[42] - 0.12e1 * t207 - 0.1e0 * t210, 2);
    real_type t215 = X__[iX_yy4];
    real_type t218 = sin(t132 + 3);
    real_type t221 = pow(V__[43] - 0.12e1 * t215 - 0.1e0 * t218, 2);
    real_type t223 = X__[iX_yy5];
    real_type t226 = sin(t132 + 4);
    real_type t229 = pow(V__[44] - 0.12e1 * t223 - 0.1e0 * t226, 2);
    real_type t230 = P__[iP_u1];
    real_type t232 = u1Limitation_min(-10 - t230);
    real_type t234 = u1Limitation_max(t230 - 10);
    real_type t237 = sin(X__[iX_x1]);
    real_type t239 = pow(V__[20] - t237 - t230, 2);
    real_type t241 = sin(t64);
    real_type t244 = pow(V__[60] - 0.2e0 * t241 - t230, 2);
    real_type t248 = pow(V__[5] - X__[iX_y6], 2);
    real_type t252 = pow(V__[6] - X__[iX_y7], 2);
    real_type t256 = pow(V__[7] - X__[iX_y8], 2);
    real_type t260 = pow(V__[8] - X__[iX_y9], 2);
    real_type t261 = t205 + t213 + t221 + t229 + t232 + t234 + t239 + t244 + t248 + t252 + t256 + t260;
    real_type t263 = xx1Limitation_min(-t1 - t64);
    real_type t265 = X__[iX_yy1];
    real_type t267 = sin(t132);
    real_type t270 = pow(V__[40] - 0.12e1 * t265 - 0.1e0 * t267, 2);
    real_type t272 = X__[iX_yy2];
    real_type t275 = sin(t132 + 1);
    real_type t278 = pow(V__[41] - 0.12e1 * t272 - 0.1e0 * t275, 2);
    real_type t280 = sin(t2);
    real_type t282 = P__[iP_u7];
    real_type t284 = pow(V__[66] - 0.2e0 * t280 - t282, 2);
    real_type t285 = P__[iP_u8];
    real_type t287 = u8Limitation_min(-10 - t285);
    real_type t288 = X__[iX_xx9];
    real_type t290 = xx9Limitation_min(-t1 - t288);
    real_type t292 = xx9Limitation_max(t288 - t1);
    real_type t293 = X__[iX_xx10];
    real_type t295 = xx10Limitation_min(-t1 - t293);
    real_type t299 = pow(V__[16] - X__[iX_y17], 2);
    real_type t303 = pow(V__[17] - X__[iX_y18], 2);
    real_type t307 = pow(V__[18] - X__[iX_y19], 2);
    real_type t311 = pow(V__[19] - X__[iX_y20], 2);
    real_type t313 = u13Limitation_min(-10 - t52);
    real_type t314 = t263 + t270 + t278 + t284 + t287 + t290 + t292 + t295 + t299 + t303 + t307 + t311 + t313;
    real_type t317 = u13Limitation_max(t52 - 10);
    real_type t320 = sin(X__[iX_x13]);
    real_type t322 = pow(V__[32] - t320 - t52, 2);
    real_type t323 = P__[iP_u12];
    real_type t325 = u12Limitation_min(-10 - t323);
    real_type t327 = u12Limitation_max(t323 - 10);
    real_type t330 = sin(X__[iX_x12]);
    real_type t332 = pow(V__[31] - t330 - t323, 2);
    real_type t334 = X__[iX_xx12];
    real_type t335 = sin(t334);
    real_type t338 = pow(V__[71] - 0.2e0 * t335 - t323, 2);
    real_type t340 = u17Limitation_max(t88 - 10);
    real_type t343 = sin(X__[iX_x17]);
    real_type t345 = pow(V__[36] - t343 - t88, 2);
    real_type t347 = X__[iX_xx17];
    real_type t348 = sin(t347);
    real_type t351 = pow(V__[76] - 0.2e0 * t348 - t88, 2);
    real_type t352 = P__[iP_u11];
    real_type t354 = u11Limitation_min(-10 - t352);
    real_type t356 = u11Limitation_max(t352 - 10);
    real_type t359 = sin(X__[iX_x11]);
    real_type t361 = pow(V__[30] - t359 - t352, 2);
    real_type t362 = t317 + t322 + t325 + t327 + t332 + t338 + t340 + t345 + t351 + t354 + t356 + t361;
    real_type t364 = X__[iX_xx11];
    real_type t365 = sin(t364);
    real_type t368 = pow(V__[70] - 0.2e0 * t365 - t352, 2);
    real_type t370 = sin(t17);
    real_type t372 = P__[iP_u6];
    real_type t374 = pow(V__[65] - 0.2e0 * t370 - t372, 2);
    real_type t376 = u7Limitation_min(-10 - t282);
    real_type t378 = u7Limitation_max(t282 - 10);
    real_type t381 = sin(X__[iX_x7]);
    real_type t383 = pow(V__[26] - t381 - t282, 2);
    real_type t384 = P__[iP_u19];
    real_type t386 = u19Limitation_min(-10 - t384);
    real_type t388 = u19Limitation_max(t384 - 10);
    real_type t391 = sin(X__[iX_x19]);
    real_type t393 = pow(V__[38] - t391 - t384, 2);
    real_type t395 = X__[iX_xx19];
    real_type t396 = sin(t395);
    real_type t399 = pow(V__[78] - 0.2e0 * t396 - t384, 2);
    real_type t400 = P__[iP_u18];
    real_type t402 = u18Limitation_min(-10 - t400);
    real_type t404 = u18Limitation_max(t400 - 10);
    real_type t407 = sin(X__[iX_x18]);
    real_type t409 = pow(V__[37] - t407 - t400, 2);
    real_type t411 = X__[iX_xx18];
    real_type t412 = sin(t411);
    real_type t415 = pow(V__[77] - 0.2e0 * t412 - t400, 2);
    real_type t416 = t368 + t374 + t376 + t378 + t383 + t386 + t388 + t393 + t399 + t402 + t404 + t409 + t415;
    real_type t423 = pow(V__[1] - X__[iX_y2], 2);
    real_type t427 = pow(V__[2] - X__[iX_y3], 2);
    real_type t431 = pow(V__[3] - X__[iX_y4], 2);
    real_type t435 = pow(V__[4] - X__[iX_y5], 2);
    real_type t436 = X__[iX_yy14];
    real_type t438 = yy14Limitation_max(t436 - t1);
    real_type t439 = X__[iX_yy15];
    real_type t441 = yy15Limitation_min(-t1 - t439);
    real_type t443 = yy15Limitation_max(t439 - t1);
    real_type t444 = X__[iX_yy16];
    real_type t446 = yy16Limitation_min(-t1 - t444);
    real_type t448 = xx16Limitation_min(-t1 - t81);
    real_type t450 = xx16Limitation_max(t81 - t1);
    real_type t452 = xx17Limitation_min(-t1 - t347);
    real_type t454 = xx14Limitation_max(t31 - t1);
    real_type t455 = t423 + t427 + t431 + t435 + t438 + t441 + t443 + t446 + t448 + t450 + t452 + t454;
    real_type t457 = xx15Limitation_min(-t1 - t92);
    real_type t459 = xx15Limitation_max(t92 - t1);
    real_type t463 = pow(V__[0] - X__[iX_y1], 2);
    real_type t465 = xx12Limitation_max(t334 - t1);
    real_type t467 = xx13Limitation_min(-t1 - t49);
    real_type t469 = xx13Limitation_max(t49 - t1);
    real_type t471 = xx14Limitation_min(-t1 - t31);
    real_type t473 = xx10Limitation_max(t293 - t1);
    real_type t475 = xx11Limitation_min(-t1 - t364);
    real_type t477 = xx11Limitation_max(t364 - t1);
    real_type t479 = xx12Limitation_min(-t1 - t334);
    real_type t480 = P__[iP_u20];
    real_type t482 = u20Limitation_min(-10 - t480);
    real_type t484 = u20Limitation_max(t480 - 10);
    real_type t485 = t457 + t459 + t463 + t465 + t467 + t469 + t471 + t473 + t475 + t477 + t479 + t482 + t484;
    real_type t489 = sin(X__[iX_x20]);
    real_type t491 = pow(V__[39] - t489 - t480, 2);
    real_type t493 = X__[iX_xx20];
    real_type t494 = sin(t493);
    real_type t497 = pow(V__[79] - 0.2e0 * t494 - t480, 2);
    real_type t498 = P__[iP_u9];
    real_type t500 = u9Limitation_max(t498 - 10);
    real_type t503 = sin(X__[iX_x9]);
    real_type t505 = pow(V__[28] - t503 - t498, 2);
    real_type t507 = sin(t288);
    real_type t510 = pow(V__[68] - 0.2e0 * t507 - t498, 2);
    real_type t512 = u8Limitation_max(t285 - 10);
    real_type t515 = sin(X__[iX_x8]);
    real_type t517 = pow(V__[27] - t515 - t285, 2);
    real_type t519 = sin(t7);
    real_type t522 = pow(V__[67] - 0.2e0 * t519 - t285, 2);
    real_type t524 = u9Limitation_min(-10 - t498);
    real_type t526 = yy6Limitation_min(-t1 - t173);
    real_type t528 = yy6Limitation_max(t173 - t1);
    real_type t530 = yy7Limitation_min(-t1 - t181);
    real_type t531 = t491 + t497 + t500 + t505 + t510 + t512 + t517 + t522 + t524 + t526 + t528 + t530;
    real_type t533 = yy7Limitation_max(t181 - t1);
    real_type t534 = X__[iX_yy19];
    real_type t536 = yy19Limitation_min(-t1 - t534);
    real_type t538 = yy19Limitation_max(t534 - t1);
    real_type t539 = X__[iX_yy20];
    real_type t541 = yy20Limitation_min(-t1 - t539);
    real_type t543 = yy20Limitation_max(t539 - t1);
    real_type t545 = yy16Limitation_max(t444 - t1);
    real_type t546 = X__[iX_yy17];
    real_type t548 = yy17Limitation_min(-t1 - t546);
    real_type t550 = yy17Limitation_max(t546 - t1);
    real_type t551 = X__[iX_yy18];
    real_type t553 = yy18Limitation_min(-t1 - t551);
    real_type t555 = yy18Limitation_max(t551 - t1);
    real_type t557 = X__[iX_yy10];
    real_type t560 = sin(t132 + 9);
    real_type t563 = pow(V__[49] - 0.12e1 * t557 - 0.1e0 * t560, 2);
    real_type t565 = X__[iX_yy11];
    real_type t568 = sin(t132 + 10);
    real_type t571 = pow(V__[50] - 0.12e1 * t565 - 0.1e0 * t568, 2);
    real_type t573 = X__[iX_yy12];
    real_type t576 = sin(t132 + 11);
    real_type t579 = pow(V__[51] - 0.12e1 * t573 - 0.1e0 * t576, 2);
    real_type t580 = t533 + t536 + t538 + t541 + t543 + t545 + t548 + t550 + t553 + t555 + t563 + t571 + t579;
    real_type t584 = yy4Limitation_min(-t1 - t215);
    real_type t586 = yy4Limitation_max(t215 - t1);
    real_type t588 = yy5Limitation_min(-t1 - t223);
    real_type t590 = yy5Limitation_max(t223 - t1);
    real_type t592 = yy2Limitation_min(-t1 - t272);
    real_type t594 = yy2Limitation_max(t272 - t1);
    real_type t596 = yy3Limitation_min(-t1 - t207);
    real_type t598 = yy3Limitation_max(t207 - t1);
    real_type t600 = xx19Limitation_max(t395 - t1);
    real_type t602 = xx20Limitation_min(-t1 - t493);
    real_type t604 = xx20Limitation_max(t493 - t1);
    real_type t606 = yy1Limitation_min(-t1 - t265);
    real_type t607 = t584 + t586 + t588 + t590 + t592 + t594 + t596 + t598 + t600 + t602 + t604 + t606;
    real_type t609 = yy1Limitation_max(t265 - t1);
    real_type t611 = yy12Limitation_max(t573 - t1);
    real_type t612 = X__[iX_yy13];
    real_type t614 = yy13Limitation_min(-t1 - t612);
    real_type t616 = yy13Limitation_max(t612 - t1);
    real_type t618 = yy14Limitation_min(-t1 - t436);
    real_type t620 = yy10Limitation_max(t557 - t1);
    real_type t622 = yy11Limitation_min(-t1 - t565);
    real_type t624 = yy11Limitation_max(t565 - t1);
    real_type t626 = yy12Limitation_min(-t1 - t573);
    real_type t628 = yy8Limitation_min(-t1 - t130);
    real_type t630 = yy8Limitation_max(t130 - t1);
    real_type t632 = yy9Limitation_min(-t1 - t140);
    real_type t634 = yy9Limitation_max(t140 - t1);
    real_type t635 = t609 + t611 + t614 + t616 + t618 + t620 + t622 + t624 + t626 + t628 + t630 + t632 + t634;
    real_type t638 = yy10Limitation_min(-t1 - t557);
    real_type t642 = sin(t132 + 17);
    real_type t645 = pow(V__[57] - 0.12e1 * t551 - 0.1e0 * t642, 2);
    real_type t649 = sin(t132 + 18);
    real_type t652 = pow(V__[58] - 0.12e1 * t534 - 0.1e0 * t649, 2);
    real_type t656 = sin(t132 + 19);
    real_type t659 = pow(V__[59] - 0.12e1 * t539 - 0.1e0 * t656, 2);
    real_type t660 = P__[iP_u10];
    real_type t662 = u10Limitation_min(-10 - t660);
    real_type t664 = u10Limitation_max(t660 - 10);
    real_type t667 = sin(X__[iX_x10]);
    real_type t669 = pow(V__[29] - t667 - t660, 2);
    real_type t671 = sin(t293);
    real_type t674 = pow(V__[69] - 0.2e0 * t671 - t660, 2);
    real_type t676 = sin(t12);
    real_type t678 = P__[iP_u5];
    real_type t680 = pow(V__[64] - 0.2e0 * t676 - t678, 2);
    real_type t682 = u6Limitation_min(-10 - t372);
    real_type t684 = u6Limitation_max(t372 - 10);
    real_type t687 = sin(X__[iX_x6]);
    real_type t689 = pow(V__[25] - t687 - t372, 2);
    real_type t690 = t638 + t645 + t652 + t659 + t662 + t664 + t669 + t674 + t680 + t682 + t684 + t689;
    real_type t692 = sin(t25);
    real_type t695 = pow(V__[63] - 0.2e0 * t692 - t153, 2);
    real_type t697 = u5Limitation_min(-10 - t678);
    real_type t699 = u5Limitation_max(t678 - 10);
    real_type t702 = sin(X__[iX_x5]);
    real_type t704 = pow(V__[24] - t702 - t678, 2);
    real_type t706 = xx17Limitation_max(t347 - t1);
    real_type t708 = xx18Limitation_min(-t1 - t411);
    real_type t710 = xx18Limitation_max(t411 - t1);
    real_type t712 = xx19Limitation_min(-t1 - t395);
    real_type t716 = sin(t132 + 14);
    real_type t719 = pow(V__[54] - 0.12e1 * t439 - 0.1e0 * t716, 2);
    real_type t723 = sin(t132 + 15);
    real_type t726 = pow(V__[55] - 0.12e1 * t444 - 0.1e0 * t723, 2);
    real_type t730 = sin(t132 + 16);
    real_type t733 = pow(V__[56] - 0.12e1 * t546 - 0.1e0 * t730, 2);
    real_type t737 = sin(t132 + 12);
    real_type t740 = pow(V__[52] - 0.12e1 * t612 - 0.1e0 * t737, 2);
    real_type t744 = sin(t132 + 13);
    real_type t747 = pow(V__[53] - 0.12e1 * t436 - 0.1e0 * t744, 2);
    real_type t748 = t695 + t697 + t699 + t704 + t706 + t708 + t710 + t712 + t719 + t726 + t733 + t740 + t747;
    real_type result__ = t37 + t86 + t138 + t198 + t261 + t314 + t362 + t416 + t455 + t485 + t531 + t580 + t607 + t635 + t690 + t748;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::DmDu_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DmDuu_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DmDuu_numCols() const { return 0; }
  integer ICLOCS_ContinuousMP::DmDuu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_controls.cc
