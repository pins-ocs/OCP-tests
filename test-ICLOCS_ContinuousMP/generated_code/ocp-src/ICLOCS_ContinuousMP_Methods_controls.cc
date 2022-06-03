/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
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
    real_type t2   = XM__[10];
    real_type t3   = sin(t2);
    real_type t4   = P__[iP_u11];
    real_type t8   = XM__[51];
    real_type t9   = sin(t8);
    real_type t11  = P__[iP_u12];
    real_type t15  = XM__[11];
    real_type t16  = sin(t15);
    real_type t20  = XM__[52];
    real_type t21  = sin(t20);
    real_type t23  = P__[iP_u13];
    real_type t27  = XM__[12];
    real_type t28  = sin(t27);
    real_type t32  = XM__[53];
    real_type t33  = sin(t32);
    real_type t35  = P__[iP_u14];
    real_type t39  = XM__[13];
    real_type t40  = sin(t39);
    real_type t44  = XM__[54];
    real_type t45  = sin(t44);
    real_type t47  = P__[iP_u15];
    real_type t51  = XM__[20];
    real_type t54  = XM__[21];
    real_type t57  = XM__[22];
    real_type t60  = XM__[23];
    real_type t63  = XM__[24];
    real_type t66  = XM__[25];
    real_type t69  = XM__[26];
    real_type t71  = (t3 + t4) * LM__[30] + (0.2e0 * t9 + t11) * LM__[71] + (t16 + t11) * LM__[31] + (0.2e0 * t21 + t23) * LM__[72] + (t28 + t23) * LM__[32] + (0.2e0 * t33 + t35) * LM__[73] + (t40 + t35) * LM__[33] + (0.2e0 * t45 + t47) * LM__[74] + t51 * LM__[0] + t54 * LM__[1] + t57 * LM__[2] + t60 * LM__[3] + t63 * LM__[4] + t66 * LM__[5] + t69 * LM__[6];
    real_type t73  = XM__[27];
    real_type t76  = XM__[28];
    real_type t79  = XM__[29];
    real_type t82  = XM__[30];
    real_type t85  = XM__[31];
    real_type t88  = XM__[32];
    real_type t91  = XM__[33];
    real_type t94  = XM__[34];
    real_type t97  = XM__[35];
    real_type t100 = XM__[36];
    real_type t103 = XM__[37];
    real_type t106 = XM__[38];
    real_type t109 = XM__[39];
    real_type t112 = XM__[72];
    real_type t114 = QM__[0];
    real_type t116 = sin(t114 + 12);
    real_type t121 = XM__[73];
    real_type t124 = sin(t114 + 13);
    real_type t128 = t73 * LM__[7] + t76 * LM__[8] + t79 * LM__[9] + t82 * LM__[10] + t85 * LM__[11] + t88 * LM__[12] + t91 * LM__[13] + t94 * LM__[14] + t97 * LM__[15] + t100 * LM__[16] + t103 * LM__[17] + t106 * LM__[18] + t109 * LM__[19] + (0.12e1 * t112 + 0.1e0 * t116) * LM__[52] + (0.12e1 * t121 + 0.1e0 * t124) * LM__[53];
    real_type t131 = XM__[74];
    real_type t134 = sin(t114 + 14);
    real_type t139 = XM__[75];
    real_type t142 = sin(t114 + 15);
    real_type t147 = XM__[76];
    real_type t150 = sin(t114 + 16);
    real_type t155 = XM__[77];
    real_type t158 = sin(t114 + 17);
    real_type t163 = XM__[78];
    real_type t166 = sin(t114 + 18);
    real_type t171 = XM__[0];
    real_type t172 = sin(t171);
    real_type t173 = P__[iP_u1];
    real_type t177 = XM__[40];
    real_type t178 = sin(t177);
    real_type t183 = XM__[41];
    real_type t184 = sin(t183);
    real_type t186 = P__[iP_u2];
    real_type t190 = XM__[1];
    real_type t191 = sin(t190);
    real_type t195 = XM__[42];
    real_type t196 = sin(t195);
    real_type t198 = P__[iP_u3];
    real_type t202 = XM__[2];
    real_type t203 = sin(t202);
    real_type t207 = XM__[43];
    real_type t208 = sin(t207);
    real_type t210 = P__[iP_u4];
    real_type t214 = XM__[3];
    real_type t215 = sin(t214);
    real_type t219 = XM__[44];
    real_type t220 = sin(t219);
    real_type t222 = P__[iP_u5];
    real_type t226 = XM__[4];
    real_type t227 = sin(t226);
    real_type t230 = (0.12e1 * t131 + 0.1e0 * t134) * LM__[54] + (0.12e1 * t139 + 0.1e0 * t142) * LM__[55] + (0.12e1 * t147 + 0.1e0 * t150) * LM__[56] + (0.12e1 * t155 + 0.1e0 * t158) * LM__[57] + (0.12e1 * t163 + 0.1e0 * t166) * LM__[58] + (t172 + t173) * LM__[20] + (0.2e0 * t178 + t173) * LM__[60] + (0.2e0 * t184 + t186) * LM__[61] + (t191 + t186) * LM__[21] + (0.2e0 * t196 + t198) * LM__[62] + (t203 + t198) * LM__[22] + (0.2e0 * t208 + t210) * LM__[63] + (t215 + t210) * LM__[23] + (0.2e0 * t220 + t222) * LM__[64] + (t227 + t222) * LM__[24];
    real_type t232 = XM__[45];
    real_type t233 = sin(t232);
    real_type t235 = P__[iP_u6];
    real_type t239 = XM__[5];
    real_type t240 = sin(t239);
    real_type t244 = XM__[46];
    real_type t245 = sin(t244);
    real_type t247 = P__[iP_u7];
    real_type t251 = XM__[6];
    real_type t252 = sin(t251);
    real_type t256 = XM__[47];
    real_type t257 = sin(t256);
    real_type t259 = P__[iP_u8];
    real_type t263 = XM__[7];
    real_type t264 = sin(t263);
    real_type t268 = XM__[48];
    real_type t269 = sin(t268);
    real_type t271 = P__[iP_u9];
    real_type t275 = XM__[8];
    real_type t276 = sin(t275);
    real_type t280 = XM__[49];
    real_type t281 = sin(t280);
    real_type t283 = P__[iP_u10];
    real_type t287 = XM__[9];
    real_type t288 = sin(t287);
    real_type t292 = XM__[50];
    real_type t293 = sin(t292);
    real_type t298 = XM__[79];
    real_type t301 = sin(t114 + 19);
    real_type t306 = XM__[14];
    real_type t307 = sin(t306);
    real_type t311 = XM__[55];
    real_type t312 = sin(t311);
    real_type t314 = P__[iP_u16];
    real_type t318 = XM__[15];
    real_type t319 = sin(t318);
    real_type t322 = (0.2e0 * t233 + t235) * LM__[65] + (t240 + t235) * LM__[25] + (0.2e0 * t245 + t247) * LM__[66] + (t252 + t247) * LM__[26] + (0.2e0 * t257 + t259) * LM__[67] + (t264 + t259) * LM__[27] + (0.2e0 * t269 + t271) * LM__[68] + (t276 + t271) * LM__[28] + (0.2e0 * t281 + t283) * LM__[69] + (t288 + t283) * LM__[29] + (0.2e0 * t293 + t4) * LM__[70] + (0.12e1 * t298 + 0.1e0 * t301) * LM__[59] + (t307 + t47) * LM__[34] + (0.2e0 * t312 + t314) * LM__[75] + (t319 + t314) * LM__[35];
    real_type t326 = XM__[56];
    real_type t327 = sin(t326);
    real_type t329 = P__[iP_u17];
    real_type t333 = XM__[16];
    real_type t334 = sin(t333);
    real_type t338 = XM__[57];
    real_type t339 = sin(t338);
    real_type t341 = P__[iP_u18];
    real_type t345 = XM__[17];
    real_type t346 = sin(t345);
    real_type t350 = XM__[58];
    real_type t351 = sin(t350);
    real_type t353 = P__[iP_u19];
    real_type t357 = XM__[18];
    real_type t358 = sin(t357);
    real_type t362 = XM__[59];
    real_type t363 = sin(t362);
    real_type t365 = P__[iP_u20];
    real_type t369 = XM__[19];
    real_type t370 = sin(t369);
    real_type t374 = XM__[60];
    real_type t376 = sin(t114);
    real_type t381 = XM__[61];
    real_type t384 = sin(t114 + 1);
    real_type t389 = XM__[62];
    real_type t392 = sin(t114 + 2);
    real_type t397 = XM__[63];
    real_type t400 = sin(t114 + 3);
    real_type t405 = XM__[64];
    real_type t408 = sin(t114 + 4);
    real_type t413 = XM__[65];
    real_type t416 = sin(t114 + 5);
    real_type t421 = XM__[66];
    real_type t424 = sin(t114 + 6);
    real_type t428 = (0.2e0 * t327 + t329) * LM__[76] + (t334 + t329) * LM__[36] + (0.2e0 * t339 + t341) * LM__[77] + (t346 + t341) * LM__[37] + (0.2e0 * t351 + t353) * LM__[78] + (t358 + t353) * LM__[38] + (0.2e0 * t363 + t365) * LM__[79] + (t370 + t365) * LM__[39] + (0.12e1 * t374 + 0.1e0 * t376) * LM__[40] + (0.12e1 * t381 + 0.1e0 * t384) * LM__[41] + (0.12e1 * t389 + 0.1e0 * t392) * LM__[42] + (0.12e1 * t397 + 0.1e0 * t400) * LM__[43] + (0.12e1 * t405 + 0.1e0 * t408) * LM__[44] + (0.12e1 * t413 + 0.1e0 * t416) * LM__[45] + (0.12e1 * t421 + 0.1e0 * t424) * LM__[46];
    real_type t430 = XM__[67];
    real_type t433 = sin(t114 + 7);
    real_type t438 = XM__[68];
    real_type t441 = sin(t114 + 8);
    real_type t446 = XM__[69];
    real_type t449 = sin(t114 + 9);
    real_type t454 = XM__[70];
    real_type t457 = sin(t114 + 10);
    real_type t462 = XM__[71];
    real_type t465 = sin(t114 + 11);
    real_type t470 = u1Limitation_min(-10 - t173);
    real_type t472 = u1Limitation_max(t173 - 10);
    real_type t474 = u2Limitation_min(-10 - t186);
    real_type t476 = u2Limitation_max(t186 - 10);
    real_type t478 = u3Limitation_min(-10 - t198);
    real_type t480 = u3Limitation_max(t198 - 10);
    real_type t482 = u4Limitation_min(-10 - t210);
    real_type t484 = u4Limitation_max(t210 - 10);
    real_type t486 = u5Limitation_min(-10 - t222);
    real_type t488 = u5Limitation_max(t222 - 10);
    real_type t489 = (0.12e1 * t430 + 0.1e0 * t433) * LM__[47] + (0.12e1 * t438 + 0.1e0 * t441) * LM__[48] + (0.12e1 * t446 + 0.1e0 * t449) * LM__[49] + (0.12e1 * t454 + 0.1e0 * t457) * LM__[50] + (0.12e1 * t462 + 0.1e0 * t465) * LM__[51] + t470 + t472 + t474 + t476 + t478 + t480 + t482 + t484 + t486 + t488;
    real_type t492 = u6Limitation_min(-10 - t235);
    real_type t494 = u6Limitation_max(t235 - 10);
    real_type t496 = u7Limitation_min(-10 - t247);
    real_type t498 = u7Limitation_max(t247 - 10);
    real_type t500 = u8Limitation_min(-10 - t259);
    real_type t502 = u8Limitation_max(t259 - 10);
    real_type t504 = u9Limitation_min(-10 - t271);
    real_type t506 = u9Limitation_max(t271 - 10);
    real_type t508 = u10Limitation_min(-10 - t283);
    real_type t510 = u10Limitation_max(t283 - 10);
    real_type t512 = u11Limitation_min(-10 - t4);
    real_type t514 = u11Limitation_max(t4 - 10);
    real_type t516 = u12Limitation_min(-10 - t11);
    real_type t518 = u12Limitation_max(t11 - 10);
    real_type t520 = u13Limitation_min(-10 - t23);
    real_type t521 = t492 + t494 + t496 + t498 + t500 + t502 + t504 + t506 + t508 + t510 + t512 + t514 + t516 + t518 + t520;
    real_type t523 = u13Limitation_max(t23 - 10);
    real_type t525 = u14Limitation_min(-10 - t35);
    real_type t527 = u14Limitation_max(t35 - 10);
    real_type t529 = u15Limitation_min(-10 - t47);
    real_type t531 = u15Limitation_max(t47 - 10);
    real_type t533 = u16Limitation_min(-10 - t314);
    real_type t535 = u16Limitation_max(t314 - 10);
    real_type t537 = u17Limitation_min(-10 - t329);
    real_type t539 = u17Limitation_max(t329 - 10);
    real_type t541 = u18Limitation_min(-10 - t341);
    real_type t543 = u18Limitation_max(t341 - 10);
    real_type t545 = u19Limitation_min(-10 - t353);
    real_type t547 = u19Limitation_max(t353 - 10);
    real_type t549 = u20Limitation_min(-10 - t365);
    real_type t551 = u20Limitation_max(t365 - 10);
    real_type t552 = t523 + t525 + t527 + t529 + t531 + t533 + t535 + t537 + t539 + t541 + t543 + t545 + t547 + t549 + t551;
    real_type t556 = t171 * t171;
    real_type t558 = t190 * t190;
    real_type t560 = t202 * t202;
    real_type t562 = t214 * t214;
    real_type t564 = t226 * t226;
    real_type t566 = t239 * t239;
    real_type t568 = t251 * t251;
    real_type t570 = t263 * t263;
    real_type t572 = t275 * t275;
    real_type t574 = t287 * t287;
    real_type t576 = t2 * t2;
    real_type t578 = t15 * t15;
    real_type t580 = t27 * t27;
    real_type t582 = t39 * t39;
    real_type t584 = t306 * t306;
    real_type t586 = 20 * t556 + 19 * t558 + 18 * t560 + 17 * t562 + 16 * t564 + 15 * t566 + 14 * t568 + 13 * t570 + 12 * t572 + 11 * t574 + 10 * t576 + 9 * t578 + 8 * t580 + 7 * t582 + 6 * t584;
    real_type t587 = t318 * t318;
    real_type t589 = t333 * t333;
    real_type t591 = t345 * t345;
    real_type t593 = t357 * t357;
    real_type t595 = t369 * t369;
    real_type t596 = t51 * t51;
    real_type t598 = t54 * t54;
    real_type t600 = t57 * t57;
    real_type t602 = t60 * t60;
    real_type t604 = t63 * t63;
    real_type t606 = t66 * t66;
    real_type t608 = t69 * t69;
    real_type t610 = t73 * t73;
    real_type t612 = t76 * t76;
    real_type t614 = t79 * t79;
    real_type t616 = 5 * t587 + 4 * t589 + 3 * t591 + 2 * t593 + t595 + 20 * t596 + 19 * t598 + 18 * t600 + 17 * t602 + 16 * t604 + 15 * t606 + 14 * t608 + 13 * t610 + 12 * t612 + 11 * t614;
    real_type t618 = t82 * t82;
    real_type t620 = t85 * t85;
    real_type t622 = t88 * t88;
    real_type t624 = t91 * t91;
    real_type t626 = t94 * t94;
    real_type t628 = t97 * t97;
    real_type t630 = t100 * t100;
    real_type t632 = t103 * t103;
    real_type t634 = t106 * t106;
    real_type t636 = t109 * t109;
    real_type t637 = ModelPars[iM_xy_bound];
    real_type t639 = xx1Limitation_min(-t637 - t177);
    real_type t641 = xx1Limitation_max(t177 - t637);
    real_type t643 = xx2Limitation_min(-t637 - t183);
    real_type t645 = xx2Limitation_max(t183 - t637);
    real_type t647 = xx3Limitation_min(-t637 - t195);
    real_type t648 = 10 * t618 + 9 * t620 + 8 * t622 + 7 * t624 + 6 * t626 + 5 * t628 + 4 * t630 + 3 * t632 + 2 * t634 + t636 + t639 + t641 + t643 + t645 + t647;
    real_type t650 = xx3Limitation_max(t195 - t637);
    real_type t652 = xx4Limitation_min(-t637 - t207);
    real_type t654 = xx4Limitation_max(t207 - t637);
    real_type t656 = xx5Limitation_min(-t637 - t219);
    real_type t658 = xx5Limitation_max(t219 - t637);
    real_type t660 = xx6Limitation_min(-t637 - t232);
    real_type t662 = xx6Limitation_max(t232 - t637);
    real_type t664 = xx7Limitation_min(-t637 - t244);
    real_type t666 = xx7Limitation_max(t244 - t637);
    real_type t668 = xx8Limitation_min(-t637 - t256);
    real_type t670 = xx8Limitation_max(t256 - t637);
    real_type t672 = xx9Limitation_min(-t637 - t268);
    real_type t674 = xx9Limitation_max(t268 - t637);
    real_type t676 = xx10Limitation_min(-t637 - t280);
    real_type t678 = xx10Limitation_max(t280 - t637);
    real_type t679 = t650 + t652 + t654 + t656 + t658 + t660 + t662 + t664 + t666 + t668 + t670 + t672 + t674 + t676 + t678;
    real_type t683 = xx11Limitation_min(-t637 - t292);
    real_type t685 = xx11Limitation_max(t292 - t637);
    real_type t687 = xx12Limitation_min(-t637 - t8);
    real_type t689 = xx12Limitation_max(t8 - t637);
    real_type t691 = xx13Limitation_min(-t637 - t20);
    real_type t693 = xx13Limitation_max(t20 - t637);
    real_type t695 = xx14Limitation_min(-t637 - t32);
    real_type t697 = xx14Limitation_max(t32 - t637);
    real_type t699 = xx15Limitation_min(-t637 - t44);
    real_type t701 = xx15Limitation_max(t44 - t637);
    real_type t703 = xx16Limitation_min(-t637 - t311);
    real_type t705 = xx16Limitation_max(t311 - t637);
    real_type t707 = xx17Limitation_min(-t637 - t326);
    real_type t709 = xx17Limitation_max(t326 - t637);
    real_type t711 = xx18Limitation_min(-t637 - t338);
    real_type t712 = t683 + t685 + t687 + t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = xx18Limitation_max(t338 - t637);
    real_type t716 = xx19Limitation_min(-t637 - t350);
    real_type t718 = xx19Limitation_max(t350 - t637);
    real_type t720 = xx20Limitation_min(-t637 - t362);
    real_type t722 = xx20Limitation_max(t362 - t637);
    real_type t724 = yy1Limitation_min(-t637 - t374);
    real_type t726 = yy1Limitation_max(t374 - t637);
    real_type t728 = yy2Limitation_min(-t637 - t381);
    real_type t730 = yy2Limitation_max(t381 - t637);
    real_type t732 = yy3Limitation_min(-t637 - t389);
    real_type t734 = yy3Limitation_max(t389 - t637);
    real_type t736 = yy4Limitation_min(-t637 - t397);
    real_type t738 = yy4Limitation_max(t397 - t637);
    real_type t740 = yy5Limitation_min(-t637 - t405);
    real_type t742 = yy5Limitation_max(t405 - t637);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = yy6Limitation_min(-t637 - t413);
    real_type t748 = yy6Limitation_max(t413 - t637);
    real_type t750 = yy7Limitation_min(-t637 - t421);
    real_type t752 = yy7Limitation_max(t421 - t637);
    real_type t754 = yy8Limitation_min(-t637 - t430);
    real_type t756 = yy8Limitation_max(t430 - t637);
    real_type t758 = yy9Limitation_min(-t637 - t438);
    real_type t760 = yy9Limitation_max(t438 - t637);
    real_type t762 = yy10Limitation_min(-t637 - t446);
    real_type t764 = yy10Limitation_max(t446 - t637);
    real_type t766 = yy11Limitation_min(-t637 - t454);
    real_type t768 = yy11Limitation_max(t454 - t637);
    real_type t770 = yy12Limitation_min(-t637 - t462);
    real_type t772 = yy12Limitation_max(t462 - t637);
    real_type t774 = yy13Limitation_min(-t637 - t112);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = yy13Limitation_max(t112 - t637);
    real_type t779 = yy14Limitation_min(-t637 - t121);
    real_type t781 = yy14Limitation_max(t121 - t637);
    real_type t783 = yy15Limitation_min(-t637 - t131);
    real_type t785 = yy15Limitation_max(t131 - t637);
    real_type t787 = yy16Limitation_min(-t637 - t139);
    real_type t789 = yy16Limitation_max(t139 - t637);
    real_type t791 = yy17Limitation_min(-t637 - t147);
    real_type t793 = yy17Limitation_max(t147 - t637);
    real_type t795 = yy18Limitation_min(-t637 - t155);
    real_type t797 = yy18Limitation_max(t155 - t637);
    real_type t799 = yy19Limitation_min(-t637 - t163);
    real_type t801 = yy19Limitation_max(t163 - t637);
    real_type t803 = yy20Limitation_min(-t637 - t298);
    real_type t805 = yy20Limitation_max(t298 - t637);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t71 + t128 + t230 + t322 + t428 + t489 + t521 + t552 + t586 + t616 + t648 + t679 + t712 + t743 + t775 + t806;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
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
    real_type t2   = X__[iX_xx9];
    real_type t4   = xx9Limitation_min(-t1 - t2);
    real_type t6   = xx9Limitation_max(t2 - t1);
    real_type t7   = X__[iX_xx10];
    real_type t9   = xx10Limitation_min(-t1 - t7);
    real_type t10  = X__[iX_xx7];
    real_type t12  = xx7Limitation_min(-t1 - t10);
    real_type t14  = xx7Limitation_max(t10 - t1);
    real_type t15  = X__[iX_xx8];
    real_type t17  = xx8Limitation_min(-t1 - t15);
    real_type t19  = xx8Limitation_max(t15 - t1);
    real_type t20  = X__[iX_xx5];
    real_type t22  = xx5Limitation_min(-t1 - t20);
    real_type t24  = xx5Limitation_max(t20 - t1);
    real_type t25  = X__[iX_xx6];
    real_type t27  = xx6Limitation_min(-t1 - t25);
    real_type t29  = xx6Limitation_max(t25 - t1);
    real_type t30  = X__[iX_xx2];
    real_type t32  = xx2Limitation_max(t30 - t1);
    real_type t33  = t4 + t6 + t9 + t12 + t14 + t17 + t19 + t22 + t24 + t27 + t29 + t32;
    real_type t34  = X__[iX_xx3];
    real_type t36  = xx3Limitation_min(-t1 - t34);
    real_type t38  = xx3Limitation_max(t34 - t1);
    real_type t39  = X__[iX_xx4];
    real_type t41  = xx4Limitation_min(-t1 - t39);
    real_type t43  = xx4Limitation_max(t39 - t1);
    real_type t44  = X__[iX_yy20];
    real_type t46  = yy20Limitation_max(t44 - t1);
    real_type t47  = X__[iX_xx1];
    real_type t49  = xx1Limitation_min(-t1 - t47);
    real_type t51  = xx1Limitation_max(t47 - t1);
    real_type t53  = xx2Limitation_min(-t1 - t30);
    real_type t54  = X__[iX_yy18];
    real_type t56  = yy18Limitation_max(t54 - t1);
    real_type t57  = X__[iX_yy19];
    real_type t59  = yy19Limitation_min(-t1 - t57);
    real_type t61  = yy19Limitation_max(t57 - t1);
    real_type t63  = yy20Limitation_min(-t1 - t44);
    real_type t64  = X__[iX_yy16];
    real_type t66  = yy16Limitation_min(-t1 - t64);
    real_type t67  = t36 + t38 + t41 + t43 + t46 + t49 + t51 + t53 + t56 + t59 + t61 + t63 + t66;
    real_type t70  = yy16Limitation_max(t64 - t1);
    real_type t71  = X__[iX_yy17];
    real_type t73  = yy17Limitation_min(-t1 - t71);
    real_type t75  = yy17Limitation_max(t71 - t1);
    real_type t77  = yy18Limitation_min(-t1 - t54);
    real_type t78  = X__[iX_yy14];
    real_type t80  = yy14Limitation_min(-t1 - t78);
    real_type t82  = yy14Limitation_max(t78 - t1);
    real_type t83  = X__[iX_yy15];
    real_type t85  = yy15Limitation_min(-t1 - t83);
    real_type t87  = yy15Limitation_max(t83 - t1);
    real_type t88  = X__[iX_yy12];
    real_type t90  = yy12Limitation_min(-t1 - t88);
    real_type t92  = yy12Limitation_max(t88 - t1);
    real_type t93  = X__[iX_yy13];
    real_type t95  = yy13Limitation_min(-t1 - t93);
    real_type t97  = yy13Limitation_max(t93 - t1);
    real_type t98  = t70 + t73 + t75 + t77 + t80 + t82 + t85 + t87 + t90 + t92 + t95 + t97;
    real_type t99  = X__[iX_yy9];
    real_type t101 = yy9Limitation_max(t99 - t1);
    real_type t102 = X__[iX_yy10];
    real_type t104 = yy10Limitation_min(-t1 - t102);
    real_type t106 = yy10Limitation_max(t102 - t1);
    real_type t107 = X__[iX_yy11];
    real_type t109 = yy11Limitation_min(-t1 - t107);
    real_type t111 = yy11Limitation_max(t107 - t1);
    real_type t112 = X__[iX_yy7];
    real_type t114 = yy7Limitation_max(t112 - t1);
    real_type t115 = X__[iX_yy8];
    real_type t117 = yy8Limitation_min(-t1 - t115);
    real_type t119 = yy8Limitation_max(t115 - t1);
    real_type t121 = yy9Limitation_min(-t1 - t99);
    real_type t122 = X__[iX_yy5];
    real_type t124 = yy5Limitation_max(t122 - t1);
    real_type t125 = X__[iX_yy6];
    real_type t127 = yy6Limitation_min(-t1 - t125);
    real_type t129 = yy6Limitation_max(t125 - t1);
    real_type t131 = yy7Limitation_min(-t1 - t112);
    real_type t132 = t101 + t104 + t106 + t109 + t111 + t114 + t117 + t119 + t121 + t124 + t127 + t129 + t131;
    real_type t135 = X__[iX_yy3];
    real_type t137 = yy3Limitation_min(-t1 - t135);
    real_type t139 = yy3Limitation_max(t135 - t1);
    real_type t140 = X__[iX_yy4];
    real_type t142 = yy4Limitation_min(-t1 - t140);
    real_type t144 = yy4Limitation_max(t140 - t1);
    real_type t146 = yy5Limitation_min(-t1 - t122);
    real_type t147 = X__[iX_yy1];
    real_type t149 = yy1Limitation_min(-t1 - t147);
    real_type t151 = yy1Limitation_max(t147 - t1);
    real_type t152 = X__[iX_yy2];
    real_type t154 = yy2Limitation_min(-t1 - t152);
    real_type t156 = yy2Limitation_max(t152 - t1);
    real_type t157 = X__[iX_xx19];
    real_type t159 = xx19Limitation_min(-t1 - t157);
    real_type t161 = xx19Limitation_max(t157 - t1);
    real_type t162 = X__[iX_xx20];
    real_type t164 = xx20Limitation_min(-t1 - t162);
    real_type t165 = t137 + t139 + t142 + t144 + t146 + t149 + t151 + t154 + t156 + t159 + t161 + t164;
    real_type t167 = xx20Limitation_max(t162 - t1);
    real_type t168 = X__[iX_xx16];
    real_type t170 = xx16Limitation_max(t168 - t1);
    real_type t171 = X__[iX_xx17];
    real_type t173 = xx17Limitation_min(-t1 - t171);
    real_type t175 = xx17Limitation_max(t171 - t1);
    real_type t176 = X__[iX_xx18];
    real_type t178 = xx18Limitation_min(-t1 - t176);
    real_type t180 = xx18Limitation_max(t176 - t1);
    real_type t181 = X__[iX_xx14];
    real_type t183 = xx14Limitation_max(t181 - t1);
    real_type t184 = X__[iX_xx15];
    real_type t186 = xx15Limitation_min(-t1 - t184);
    real_type t188 = xx15Limitation_max(t184 - t1);
    real_type t190 = xx16Limitation_min(-t1 - t168);
    real_type t191 = X__[iX_xx12];
    real_type t193 = xx12Limitation_max(t191 - t1);
    real_type t194 = X__[iX_xx13];
    real_type t196 = xx13Limitation_min(-t1 - t194);
    real_type t198 = xx13Limitation_max(t194 - t1);
    real_type t199 = t167 + t170 + t173 + t175 + t178 + t180 + t183 + t186 + t188 + t190 + t193 + t196 + t198;
    real_type t202 = xx14Limitation_min(-t1 - t181);
    real_type t204 = xx10Limitation_max(t7 - t1);
    real_type t205 = X__[iX_xx11];
    real_type t207 = xx11Limitation_min(-t1 - t205);
    real_type t209 = xx11Limitation_max(t205 - t1);
    real_type t211 = xx12Limitation_min(-t1 - t191);
    real_type t215 = pow(V__[17] - X__[iX_y18], 2);
    real_type t219 = pow(V__[18] - X__[iX_y19], 2);
    real_type t223 = pow(V__[19] - X__[iX_y20], 2);
    real_type t227 = pow(V__[13] - X__[iX_y14], 2);
    real_type t231 = pow(V__[14] - X__[iX_y15], 2);
    real_type t235 = pow(V__[15] - X__[iX_y16], 2);
    real_type t239 = pow(V__[16] - X__[iX_y17], 2);
    real_type t240 = t202 + t204 + t207 + t209 + t211 + t215 + t219 + t223 + t227 + t231 + t235 + t239;
    real_type t244 = pow(V__[9] - X__[iX_y10], 2);
    real_type t248 = pow(V__[10] - X__[iX_y11], 2);
    real_type t252 = pow(V__[11] - X__[iX_y12], 2);
    real_type t256 = pow(V__[12] - X__[iX_y13], 2);
    real_type t260 = pow(V__[5] - X__[iX_y6], 2);
    real_type t264 = pow(V__[6] - X__[iX_y7], 2);
    real_type t268 = pow(V__[7] - X__[iX_y8], 2);
    real_type t272 = pow(V__[8] - X__[iX_y9], 2);
    real_type t276 = pow(V__[1] - X__[iX_y2], 2);
    real_type t280 = pow(V__[2] - X__[iX_y3], 2);
    real_type t284 = pow(V__[3] - X__[iX_y4], 2);
    real_type t288 = pow(V__[4] - X__[iX_y5], 2);
    real_type t289 = P__[iP_u20];
    real_type t291 = u20Limitation_max(t289 - 10);
    real_type t292 = t244 + t248 + t252 + t256 + t260 + t264 + t268 + t272 + t276 + t280 + t284 + t288 + t291;
    real_type t297 = sin(t162);
    real_type t300 = pow(V__[79] - 0.2e0 * t297 - t289, 2);
    real_type t303 = sin(X__[iX_x20]);
    real_type t305 = pow(V__[39] - t303 - t289, 2);
    real_type t309 = pow(V__[0] - X__[iX_y1], 2);
    real_type t312 = sin(X__[iX_x19]);
    real_type t313 = P__[iP_u19];
    real_type t315 = pow(V__[38] - t312 - t313, 2);
    real_type t317 = u20Limitation_min(-10 - t289);
    real_type t320 = sin(X__[iX_x18]);
    real_type t321 = P__[iP_u18];
    real_type t323 = pow(V__[37] - t320 - t321, 2);
    real_type t325 = u19Limitation_min(-10 - t313);
    real_type t327 = u19Limitation_max(t313 - 10);
    real_type t329 = sin(t157);
    real_type t332 = pow(V__[78] - 0.2e0 * t329 - t313, 2);
    real_type t335 = sin(X__[iX_x17]);
    real_type t336 = P__[iP_u17];
    real_type t338 = pow(V__[36] - t335 - t336, 2);
    real_type t340 = u18Limitation_min(-10 - t321);
    real_type t342 = u18Limitation_max(t321 - 10);
    real_type t343 = t300 + t305 + t309 + t315 + t317 + t323 + t325 + t327 + t332 + t338 + t340 + t342;
    real_type t345 = sin(t176);
    real_type t348 = pow(V__[77] - 0.2e0 * t345 - t321, 2);
    real_type t350 = u17Limitation_min(-10 - t336);
    real_type t352 = u17Limitation_max(t336 - 10);
    real_type t354 = sin(t171);
    real_type t357 = pow(V__[76] - 0.2e0 * t354 - t336, 2);
    real_type t358 = P__[iP_u16];
    real_type t360 = u16Limitation_min(-10 - t358);
    real_type t362 = u16Limitation_max(t358 - 10);
    real_type t364 = sin(t168);
    real_type t367 = pow(V__[75] - 0.2e0 * t364 - t358, 2);
    real_type t370 = sin(X__[iX_x16]);
    real_type t372 = pow(V__[35] - t370 - t358, 2);
    real_type t373 = P__[iP_u15];
    real_type t375 = u15Limitation_min(-10 - t373);
    real_type t377 = u15Limitation_max(t373 - 10);
    real_type t379 = sin(t184);
    real_type t382 = pow(V__[74] - 0.2e0 * t379 - t373, 2);
    real_type t385 = sin(X__[iX_x15]);
    real_type t387 = pow(V__[34] - t385 - t373, 2);
    real_type t388 = P__[iP_u14];
    real_type t390 = u14Limitation_min(-10 - t388);
    real_type t391 = t348 + t350 + t352 + t357 + t360 + t362 + t367 + t372 + t375 + t377 + t382 + t387 + t390;
    real_type t394 = u14Limitation_max(t388 - 10);
    real_type t396 = sin(t181);
    real_type t399 = pow(V__[73] - 0.2e0 * t396 - t388, 2);
    real_type t402 = sin(X__[iX_x14]);
    real_type t404 = pow(V__[33] - t402 - t388, 2);
    real_type t405 = P__[iP_u13];
    real_type t407 = u13Limitation_max(t405 - 10);
    real_type t409 = sin(t194);
    real_type t412 = pow(V__[72] - 0.2e0 * t409 - t405, 2);
    real_type t415 = sin(X__[iX_x13]);
    real_type t417 = pow(V__[32] - t415 - t405, 2);
    real_type t418 = P__[iP_u12];
    real_type t420 = u12Limitation_max(t418 - 10);
    real_type t422 = sin(t191);
    real_type t425 = pow(V__[71] - 0.2e0 * t422 - t418, 2);
    real_type t428 = sin(X__[iX_x12]);
    real_type t430 = pow(V__[31] - t428 - t418, 2);
    real_type t432 = u13Limitation_min(-10 - t405);
    real_type t435 = sin(X__[iX_x11]);
    real_type t436 = P__[iP_u11];
    real_type t438 = pow(V__[30] - t435 - t436, 2);
    real_type t440 = u12Limitation_min(-10 - t418);
    real_type t441 = t394 + t399 + t404 + t407 + t412 + t417 + t420 + t425 + t430 + t432 + t438 + t440;
    real_type t444 = sin(X__[iX_x10]);
    real_type t445 = P__[iP_u10];
    real_type t447 = pow(V__[29] - t444 - t445, 2);
    real_type t449 = u11Limitation_min(-10 - t436);
    real_type t451 = u11Limitation_max(t436 - 10);
    real_type t453 = sin(t205);
    real_type t456 = pow(V__[70] - 0.2e0 * t453 - t436, 2);
    real_type t458 = u10Limitation_min(-10 - t445);
    real_type t460 = u10Limitation_max(t445 - 10);
    real_type t462 = sin(t7);
    real_type t465 = pow(V__[69] - 0.2e0 * t462 - t445, 2);
    real_type t466 = P__[iP_u9];
    real_type t468 = u9Limitation_min(-10 - t466);
    real_type t470 = u9Limitation_max(t466 - 10);
    real_type t472 = sin(t2);
    real_type t475 = pow(V__[68] - 0.2e0 * t472 - t466, 2);
    real_type t478 = sin(X__[iX_x9]);
    real_type t480 = pow(V__[28] - t478 - t466, 2);
    real_type t481 = P__[iP_u8];
    real_type t483 = u8Limitation_min(-10 - t481);
    real_type t485 = u8Limitation_max(t481 - 10);
    real_type t486 = t447 + t449 + t451 + t456 + t458 + t460 + t465 + t468 + t470 + t475 + t480 + t483 + t485;
    real_type t490 = sin(t15);
    real_type t493 = pow(V__[67] - 0.2e0 * t490 - t481, 2);
    real_type t496 = sin(X__[iX_x8]);
    real_type t498 = pow(V__[27] - t496 - t481, 2);
    real_type t499 = P__[iP_u7];
    real_type t501 = u7Limitation_min(-10 - t499);
    real_type t503 = u7Limitation_max(t499 - 10);
    real_type t505 = sin(t10);
    real_type t508 = pow(V__[66] - 0.2e0 * t505 - t499, 2);
    real_type t511 = sin(X__[iX_x7]);
    real_type t513 = pow(V__[26] - t511 - t499, 2);
    real_type t514 = P__[iP_u6];
    real_type t516 = u6Limitation_min(-10 - t514);
    real_type t518 = u6Limitation_max(t514 - 10);
    real_type t520 = sin(t25);
    real_type t523 = pow(V__[65] - 0.2e0 * t520 - t514, 2);
    real_type t526 = sin(X__[iX_x6]);
    real_type t528 = pow(V__[25] - t526 - t514, 2);
    real_type t529 = P__[iP_u5];
    real_type t531 = u5Limitation_max(t529 - 10);
    real_type t533 = sin(t20);
    real_type t536 = pow(V__[64] - 0.2e0 * t533 - t529, 2);
    real_type t537 = t493 + t498 + t501 + t503 + t508 + t513 + t516 + t518 + t523 + t528 + t531 + t536;
    real_type t540 = sin(X__[iX_x5]);
    real_type t542 = pow(V__[24] - t540 - t529, 2);
    real_type t545 = sin(X__[iX_x4]);
    real_type t546 = P__[iP_u4];
    real_type t548 = pow(V__[23] - t545 - t546, 2);
    real_type t550 = u5Limitation_min(-10 - t529);
    real_type t553 = sin(X__[iX_x3]);
    real_type t554 = P__[iP_u3];
    real_type t556 = pow(V__[22] - t553 - t554, 2);
    real_type t558 = u4Limitation_min(-10 - t546);
    real_type t560 = u4Limitation_max(t546 - 10);
    real_type t562 = sin(t39);
    real_type t565 = pow(V__[63] - 0.2e0 * t562 - t546, 2);
    real_type t567 = u3Limitation_min(-10 - t554);
    real_type t569 = u3Limitation_max(t554 - 10);
    real_type t571 = sin(t34);
    real_type t574 = pow(V__[62] - 0.2e0 * t571 - t554, 2);
    real_type t575 = P__[iP_u2];
    real_type t577 = u2Limitation_min(-10 - t575);
    real_type t579 = u2Limitation_max(t575 - 10);
    real_type t581 = sin(t30);
    real_type t584 = pow(V__[61] - 0.2e0 * t581 - t575, 2);
    real_type t585 = t542 + t548 + t550 + t556 + t558 + t560 + t565 + t567 + t569 + t574 + t577 + t579 + t584;
    real_type t589 = sin(X__[iX_x2]);
    real_type t591 = pow(V__[21] - t589 - t575, 2);
    real_type t592 = P__[iP_u1];
    real_type t594 = u1Limitation_min(-10 - t592);
    real_type t596 = u1Limitation_max(t592 - 10);
    real_type t598 = sin(t47);
    real_type t601 = pow(V__[60] - 0.2e0 * t598 - t592, 2);
    real_type t604 = sin(X__[iX_x1]);
    real_type t606 = pow(V__[20] - t604 - t592, 2);
    real_type t609 = Q__[iQ_zeta];
    real_type t611 = sin(t609 + 16);
    real_type t614 = pow(V__[56] - 0.12e1 * t71 - 0.1e0 * t611, 2);
    real_type t618 = sin(t609 + 17);
    real_type t621 = pow(V__[57] - 0.12e1 * t54 - 0.1e0 * t618, 2);
    real_type t625 = sin(t609 + 14);
    real_type t628 = pow(V__[54] - 0.12e1 * t83 - 0.1e0 * t625, 2);
    real_type t632 = sin(t609 + 15);
    real_type t635 = pow(V__[55] - 0.12e1 * t64 - 0.1e0 * t632, 2);
    real_type t639 = sin(t609 + 11);
    real_type t642 = pow(V__[51] - 0.12e1 * t88 - 0.1e0 * t639, 2);
    real_type t646 = sin(t609 + 12);
    real_type t649 = pow(V__[52] - 0.12e1 * t93 - 0.1e0 * t646, 2);
    real_type t653 = sin(t609 + 13);
    real_type t656 = pow(V__[53] - 0.12e1 * t78 - 0.1e0 * t653, 2);
    real_type t657 = t591 + t594 + t596 + t601 + t606 + t614 + t621 + t628 + t635 + t642 + t649 + t656;
    real_type t661 = sin(t609 + 9);
    real_type t664 = pow(V__[49] - 0.12e1 * t102 - 0.1e0 * t661, 2);
    real_type t668 = sin(t609 + 10);
    real_type t671 = pow(V__[50] - 0.12e1 * t107 - 0.1e0 * t668, 2);
    real_type t675 = sin(t609 + 6);
    real_type t678 = pow(V__[46] - 0.12e1 * t112 - 0.1e0 * t675, 2);
    real_type t682 = sin(t609 + 7);
    real_type t685 = pow(V__[47] - 0.12e1 * t115 - 0.1e0 * t682, 2);
    real_type t689 = sin(t609 + 8);
    real_type t692 = pow(V__[48] - 0.12e1 * t99 - 0.1e0 * t689, 2);
    real_type t696 = sin(t609 + 4);
    real_type t699 = pow(V__[44] - 0.12e1 * t122 - 0.1e0 * t696, 2);
    real_type t703 = sin(t609 + 5);
    real_type t706 = pow(V__[45] - 0.12e1 * t125 - 0.1e0 * t703, 2);
    real_type t710 = sin(t609 + 2);
    real_type t713 = pow(V__[42] - 0.12e1 * t135 - 0.1e0 * t710, 2);
    real_type t717 = sin(t609 + 3);
    real_type t720 = pow(V__[43] - 0.12e1 * t140 - 0.1e0 * t717, 2);
    real_type t724 = sin(t609 + 19);
    real_type t727 = pow(V__[59] - 0.12e1 * t44 - 0.1e0 * t724, 2);
    real_type t730 = sin(t609);
    real_type t733 = pow(V__[40] - 0.12e1 * t147 - 0.1e0 * t730, 2);
    real_type t737 = sin(t609 + 1);
    real_type t740 = pow(V__[41] - 0.12e1 * t152 - 0.1e0 * t737, 2);
    real_type t744 = sin(t609 + 18);
    real_type t747 = pow(V__[58] - 0.12e1 * t57 - 0.1e0 * t744, 2);
    real_type t748 = t664 + t671 + t678 + t685 + t692 + t699 + t706 + t713 + t720 + t727 + t733 + t740 + t747;
    real_type result__ = t33 + t67 + t98 + t132 + t165 + t199 + t240 + t292 + t343 + t391 + t441 + t486 + t537 + t585 + t657 + t748;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
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
