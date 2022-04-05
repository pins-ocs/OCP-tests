/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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
    real_type t1   = XM__[2];
    real_type t2   = t1 * t1;
    real_type t4   = XM__[3];
    real_type t5   = t4 * t4;
    real_type t7   = XM__[4];
    real_type t8   = t7 * t7;
    real_type t10  = XM__[5];
    real_type t11  = t10 * t10;
    real_type t13  = XM__[6];
    real_type t14  = t13 * t13;
    real_type t16  = XM__[7];
    real_type t17  = t16 * t16;
    real_type t19  = XM__[8];
    real_type t20  = t19 * t19;
    real_type t22  = XM__[9];
    real_type t23  = t22 * t22;
    real_type t25  = ModelPars[iM_xy_bound];
    real_type t26  = XM__[78];
    real_type t28  = yy19Limitation_min(-t25 - t26);
    real_type t30  = yy19Limitation_max(t26 - t25);
    real_type t31  = XM__[79];
    real_type t33  = yy20Limitation_min(-t25 - t31);
    real_type t35  = yy20Limitation_max(t31 - t25);
    real_type t36  = XM__[0];
    real_type t37  = t36 * t36;
    real_type t39  = XM__[1];
    real_type t40  = t39 * t39;
    real_type t43  = XM__[17];
    real_type t44  = sin(t43);
    real_type t45  = P__[iP_u18];
    real_type t48  = 18 * t2 + 17 * t5 + 16 * t8 + 15 * t11 + 14 * t14 + 13 * t17 + 12 * t20 + 11 * t23 + t28 + t30 + t33 + t35 + 20 * t37 + 19 * t40 + (t44 + t45) * LM__[37];
    real_type t50  = XM__[57];
    real_type t51  = sin(t50);
    real_type t56  = XM__[18];
    real_type t57  = sin(t56);
    real_type t58  = P__[iP_u19];
    real_type t62  = XM__[58];
    real_type t63  = sin(t62);
    real_type t68  = XM__[19];
    real_type t69  = sin(t68);
    real_type t70  = P__[iP_u20];
    real_type t74  = XM__[59];
    real_type t75  = sin(t74);
    real_type t80  = XM__[60];
    real_type t82  = QM__[0];
    real_type t83  = sin(t82);
    real_type t88  = XM__[61];
    real_type t91  = sin(t82 + 1);
    real_type t96  = XM__[62];
    real_type t99  = sin(t82 + 2);
    real_type t104 = XM__[63];
    real_type t107 = sin(t82 + 3);
    real_type t112 = XM__[64];
    real_type t115 = sin(t82 + 4);
    real_type t120 = XM__[65];
    real_type t123 = sin(t82 + 5);
    real_type t128 = XM__[66];
    real_type t131 = sin(t82 + 6);
    real_type t136 = XM__[67];
    real_type t139 = sin(t82 + 7);
    real_type t144 = XM__[68];
    real_type t147 = sin(t82 + 8);
    real_type t152 = XM__[69];
    real_type t155 = sin(t82 + 9);
    real_type t159 = (0.2e0 * t51 + t45) * LM__[77] + (t57 + t58) * LM__[38] + (0.2e0 * t63 + t58) * LM__[78] + (t69 + t70) * LM__[39] + (0.2e0 * t75 + t70) * LM__[79] + (0.12e1 * t80 + 0.1e0 * t83) * LM__[40] + (0.12e1 * t88 + 0.1e0 * t91) * LM__[41] + (0.12e1 * t96 + 0.1e0 * t99) * LM__[42] + (0.12e1 * t104 + 0.1e0 * t107) * LM__[43] + (0.12e1 * t112 + 0.1e0 * t115) * LM__[44] + (0.12e1 * t120 + 0.1e0 * t123) * LM__[45] + (0.12e1 * t128 + 0.1e0 * t131) * LM__[46] + (0.12e1 * t136 + 0.1e0 * t139) * LM__[47] + (0.12e1 * t144 + 0.1e0 * t147) * LM__[48] + (0.12e1 * t152 + 0.1e0 * t155) * LM__[49];
    real_type t162 = XM__[70];
    real_type t165 = sin(t82 + 10);
    real_type t170 = XM__[71];
    real_type t173 = sin(t82 + 11);
    real_type t178 = XM__[72];
    real_type t181 = sin(t82 + 12);
    real_type t186 = XM__[73];
    real_type t189 = sin(t82 + 13);
    real_type t194 = XM__[74];
    real_type t197 = sin(t82 + 14);
    real_type t202 = XM__[75];
    real_type t205 = sin(t82 + 15);
    real_type t210 = XM__[76];
    real_type t213 = sin(t82 + 16);
    real_type t218 = XM__[77];
    real_type t221 = sin(t82 + 17);
    real_type t228 = sin(t82 + 18);
    real_type t235 = sin(t82 + 19);
    real_type t240 = XM__[47];
    real_type t241 = sin(t240);
    real_type t243 = P__[iP_u8];
    real_type t247 = sin(t19);
    real_type t248 = P__[iP_u9];
    real_type t252 = XM__[48];
    real_type t253 = sin(t252);
    real_type t258 = sin(t22);
    real_type t259 = P__[iP_u10];
    real_type t263 = XM__[49];
    real_type t264 = sin(t263);
    real_type t268 = (0.12e1 * t162 + 0.1e0 * t165) * LM__[50] + (0.12e1 * t170 + 0.1e0 * t173) * LM__[51] + (0.12e1 * t178 + 0.1e0 * t181) * LM__[52] + (0.12e1 * t186 + 0.1e0 * t189) * LM__[53] + (0.12e1 * t194 + 0.1e0 * t197) * LM__[54] + (0.12e1 * t202 + 0.1e0 * t205) * LM__[55] + (0.12e1 * t210 + 0.1e0 * t213) * LM__[56] + (0.12e1 * t218 + 0.1e0 * t221) * LM__[57] + (0.12e1 * t26 + 0.1e0 * t228) * LM__[58] + (0.12e1 * t31 + 0.1e0 * t235) * LM__[59] + (0.2e0 * t241 + t243) * LM__[67] + (t247 + t248) * LM__[28] + (0.2e0 * t253 + t248) * LM__[68] + (t258 + t259) * LM__[29] + (0.2e0 * t264 + t259) * LM__[69];
    real_type t270 = XM__[10];
    real_type t271 = sin(t270);
    real_type t272 = P__[iP_u11];
    real_type t276 = XM__[50];
    real_type t277 = sin(t276);
    real_type t282 = XM__[11];
    real_type t283 = sin(t282);
    real_type t284 = P__[iP_u12];
    real_type t288 = XM__[51];
    real_type t289 = sin(t288);
    real_type t294 = XM__[12];
    real_type t295 = sin(t294);
    real_type t296 = P__[iP_u13];
    real_type t300 = XM__[52];
    real_type t301 = sin(t300);
    real_type t306 = XM__[13];
    real_type t307 = sin(t306);
    real_type t308 = P__[iP_u14];
    real_type t312 = XM__[53];
    real_type t313 = sin(t312);
    real_type t318 = XM__[14];
    real_type t319 = sin(t318);
    real_type t320 = P__[iP_u15];
    real_type t324 = XM__[54];
    real_type t325 = sin(t324);
    real_type t330 = XM__[15];
    real_type t331 = sin(t330);
    real_type t332 = P__[iP_u16];
    real_type t336 = XM__[55];
    real_type t337 = sin(t336);
    real_type t342 = XM__[16];
    real_type t343 = sin(t342);
    real_type t344 = P__[iP_u17];
    real_type t348 = XM__[56];
    real_type t349 = sin(t348);
    real_type t354 = XM__[44];
    real_type t355 = sin(t354);
    real_type t357 = P__[iP_u5];
    real_type t360 = (t271 + t272) * LM__[30] + (0.2e0 * t277 + t272) * LM__[70] + (t283 + t284) * LM__[31] + (0.2e0 * t289 + t284) * LM__[71] + (t295 + t296) * LM__[32] + (0.2e0 * t301 + t296) * LM__[72] + (t307 + t308) * LM__[33] + (0.2e0 * t313 + t308) * LM__[73] + (t319 + t320) * LM__[34] + (0.2e0 * t325 + t320) * LM__[74] + (t331 + t332) * LM__[35] + (0.2e0 * t337 + t332) * LM__[75] + (t343 + t344) * LM__[36] + (0.2e0 * t349 + t344) * LM__[76] + (0.2e0 * t355 + t357) * LM__[64];
    real_type t364 = sin(t10);
    real_type t365 = P__[iP_u6];
    real_type t369 = XM__[45];
    real_type t370 = sin(t369);
    real_type t375 = sin(t13);
    real_type t376 = P__[iP_u7];
    real_type t380 = XM__[46];
    real_type t381 = sin(t380);
    real_type t386 = sin(t16);
    real_type t390 = sin(t36);
    real_type t391 = P__[iP_u1];
    real_type t395 = XM__[40];
    real_type t396 = sin(t395);
    real_type t401 = sin(t39);
    real_type t402 = P__[iP_u2];
    real_type t406 = XM__[41];
    real_type t407 = sin(t406);
    real_type t412 = sin(t1);
    real_type t413 = P__[iP_u3];
    real_type t417 = XM__[42];
    real_type t418 = sin(t417);
    real_type t423 = sin(t4);
    real_type t424 = P__[iP_u4];
    real_type t428 = XM__[43];
    real_type t429 = sin(t428);
    real_type t434 = sin(t7);
    real_type t438 = XM__[23];
    real_type t440 = (t364 + t365) * LM__[25] + (0.2e0 * t370 + t365) * LM__[65] + (t375 + t376) * LM__[26] + (0.2e0 * t381 + t376) * LM__[66] + (t386 + t243) * LM__[27] + (t390 + t391) * LM__[20] + (0.2e0 * t396 + t391) * LM__[60] + (t401 + t402) * LM__[21] + (0.2e0 * t407 + t402) * LM__[61] + (t412 + t413) * LM__[22] + (0.2e0 * t418 + t413) * LM__[62] + (t423 + t424) * LM__[23] + (0.2e0 * t429 + t424) * LM__[63] + (t434 + t357) * LM__[24] + t438 * LM__[3];
    real_type t442 = XM__[24];
    real_type t445 = XM__[25];
    real_type t448 = XM__[26];
    real_type t451 = XM__[27];
    real_type t454 = XM__[28];
    real_type t457 = XM__[29];
    real_type t460 = XM__[30];
    real_type t463 = XM__[31];
    real_type t466 = XM__[32];
    real_type t469 = XM__[33];
    real_type t472 = XM__[34];
    real_type t475 = XM__[35];
    real_type t478 = XM__[36];
    real_type t481 = XM__[37];
    real_type t484 = XM__[38];
    real_type t486 = t442 * LM__[4] + t445 * LM__[5] + t448 * LM__[6] + t451 * LM__[7] + t454 * LM__[8] + t457 * LM__[9] + t460 * LM__[10] + t463 * LM__[11] + t466 * LM__[12] + t469 * LM__[13] + t472 * LM__[14] + t475 * LM__[15] + t478 * LM__[16] + t481 * LM__[17] + t484 * LM__[18];
    real_type t489 = XM__[39];
    real_type t492 = XM__[20];
    real_type t495 = XM__[21];
    real_type t498 = XM__[22];
    real_type t501 = yy12Limitation_min(-t25 - t170);
    real_type t503 = yy12Limitation_max(t170 - t25);
    real_type t505 = yy13Limitation_min(-t25 - t178);
    real_type t507 = yy13Limitation_max(t178 - t25);
    real_type t509 = yy14Limitation_min(-t25 - t186);
    real_type t511 = yy14Limitation_max(t186 - t25);
    real_type t513 = yy15Limitation_min(-t25 - t194);
    real_type t515 = yy15Limitation_max(t194 - t25);
    real_type t517 = yy16Limitation_min(-t25 - t202);
    real_type t519 = xx6Limitation_max(t369 - t25);
    real_type t521 = xx7Limitation_min(-t25 - t380);
    real_type t522 = t489 * LM__[19] + t492 * LM__[0] + t495 * LM__[1] + t498 * LM__[2] + t501 + t503 + t505 + t507 + t509 + t511 + t513 + t515 + t517 + t519 + t521;
    real_type t524 = xx7Limitation_max(t380 - t25);
    real_type t526 = xx8Limitation_min(-t25 - t240);
    real_type t528 = xx8Limitation_max(t240 - t25);
    real_type t530 = xx9Limitation_min(-t25 - t252);
    real_type t532 = xx9Limitation_max(t252 - t25);
    real_type t534 = xx10Limitation_min(-t25 - t263);
    real_type t536 = xx10Limitation_max(t263 - t25);
    real_type t538 = xx11Limitation_min(-t25 - t276);
    real_type t540 = xx11Limitation_max(t276 - t25);
    real_type t542 = xx12Limitation_min(-t25 - t288);
    real_type t544 = xx12Limitation_max(t288 - t25);
    real_type t546 = xx13Limitation_min(-t25 - t300);
    real_type t548 = yy16Limitation_max(t202 - t25);
    real_type t550 = yy17Limitation_min(-t25 - t210);
    real_type t552 = yy17Limitation_max(t210 - t25);
    real_type t553 = t524 + t526 + t528 + t530 + t532 + t534 + t536 + t538 + t540 + t542 + t544 + t546 + t548 + t550 + t552;
    real_type t558 = yy18Limitation_min(-t25 - t218);
    real_type t560 = yy18Limitation_max(t218 - t25);
    real_type t562 = xx15Limitation_max(t324 - t25);
    real_type t564 = xx16Limitation_min(-t25 - t336);
    real_type t566 = xx16Limitation_max(t336 - t25);
    real_type t568 = xx17Limitation_min(-t25 - t348);
    real_type t570 = xx17Limitation_max(t348 - t25);
    real_type t572 = xx18Limitation_min(-t25 - t50);
    real_type t574 = xx18Limitation_max(t50 - t25);
    real_type t576 = xx19Limitation_min(-t25 - t62);
    real_type t578 = xx19Limitation_max(t62 - t25);
    real_type t580 = xx20Limitation_min(-t25 - t74);
    real_type t582 = xx20Limitation_max(t74 - t25);
    real_type t584 = yy1Limitation_min(-t25 - t80);
    real_type t586 = yy1Limitation_max(t80 - t25);
    real_type t587 = t558 + t560 + t562 + t564 + t566 + t568 + t570 + t572 + t574 + t576 + t578 + t580 + t582 + t584 + t586;
    real_type t589 = yy2Limitation_min(-t25 - t88);
    real_type t591 = yy2Limitation_max(t88 - t25);
    real_type t593 = yy3Limitation_min(-t25 - t96);
    real_type t595 = yy3Limitation_max(t96 - t25);
    real_type t597 = yy4Limitation_min(-t25 - t104);
    real_type t599 = yy4Limitation_max(t104 - t25);
    real_type t601 = yy5Limitation_min(-t25 - t112);
    real_type t603 = yy5Limitation_max(t112 - t25);
    real_type t605 = yy6Limitation_min(-t25 - t120);
    real_type t607 = yy6Limitation_max(t120 - t25);
    real_type t609 = yy7Limitation_min(-t25 - t128);
    real_type t611 = yy7Limitation_max(t128 - t25);
    real_type t613 = yy8Limitation_min(-t25 - t136);
    real_type t615 = yy8Limitation_max(t136 - t25);
    real_type t617 = yy9Limitation_min(-t25 - t144);
    real_type t618 = t589 + t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613 + t615 + t617;
    real_type t621 = yy9Limitation_max(t144 - t25);
    real_type t623 = yy10Limitation_min(-t25 - t152);
    real_type t625 = yy10Limitation_max(t152 - t25);
    real_type t627 = yy11Limitation_min(-t25 - t162);
    real_type t629 = yy11Limitation_max(t162 - t25);
    real_type t630 = t270 * t270;
    real_type t632 = t282 * t282;
    real_type t634 = t294 * t294;
    real_type t636 = t306 * t306;
    real_type t638 = t318 * t318;
    real_type t640 = t330 * t330;
    real_type t642 = t342 * t342;
    real_type t644 = t43 * t43;
    real_type t646 = t56 * t56;
    real_type t648 = t68 * t68;
    real_type t649 = t621 + t623 + t625 + t627 + t629 + 10 * t630 + 9 * t632 + 8 * t634 + 7 * t636 + 6 * t638 + 5 * t640 + 4 * t642 + 3 * t644 + 2 * t646 + t648;
    real_type t651 = xx13Limitation_max(t300 - t25);
    real_type t653 = xx14Limitation_min(-t25 - t312);
    real_type t655 = xx14Limitation_max(t312 - t25);
    real_type t657 = xx15Limitation_min(-t25 - t324);
    real_type t659 = u1Limitation_min(-10 - t391);
    real_type t661 = u1Limitation_max(t391 - 10);
    real_type t663 = u2Limitation_min(-10 - t402);
    real_type t665 = u2Limitation_max(t402 - 10);
    real_type t667 = u3Limitation_min(-10 - t413);
    real_type t669 = u3Limitation_max(t413 - 10);
    real_type t671 = u4Limitation_min(-10 - t424);
    real_type t673 = u4Limitation_max(t424 - 10);
    real_type t675 = u5Limitation_min(-10 - t357);
    real_type t677 = u5Limitation_max(t357 - 10);
    real_type t679 = u6Limitation_min(-10 - t365);
    real_type t680 = t651 + t653 + t655 + t657 + t659 + t661 + t663 + t665 + t667 + t669 + t671 + t673 + t675 + t677 + t679;
    real_type t684 = u6Limitation_max(t365 - 10);
    real_type t686 = u7Limitation_min(-10 - t376);
    real_type t688 = u7Limitation_max(t376 - 10);
    real_type t690 = u8Limitation_min(-10 - t243);
    real_type t692 = u8Limitation_max(t243 - 10);
    real_type t694 = u9Limitation_min(-10 - t248);
    real_type t696 = u9Limitation_max(t248 - 10);
    real_type t698 = u10Limitation_min(-10 - t259);
    real_type t700 = u10Limitation_max(t259 - 10);
    real_type t702 = u11Limitation_min(-10 - t272);
    real_type t704 = u11Limitation_max(t272 - 10);
    real_type t706 = u12Limitation_min(-10 - t284);
    real_type t708 = u12Limitation_max(t284 - 10);
    real_type t710 = u13Limitation_min(-10 - t296);
    real_type t712 = u13Limitation_max(t296 - 10);
    real_type t713 = t684 + t686 + t688 + t690 + t692 + t694 + t696 + t698 + t700 + t702 + t704 + t706 + t708 + t710 + t712;
    real_type t715 = u14Limitation_min(-10 - t308);
    real_type t717 = u14Limitation_max(t308 - 10);
    real_type t719 = u15Limitation_min(-10 - t320);
    real_type t721 = u15Limitation_max(t320 - 10);
    real_type t723 = u16Limitation_min(-10 - t332);
    real_type t725 = u16Limitation_max(t332 - 10);
    real_type t727 = u17Limitation_min(-10 - t344);
    real_type t729 = u17Limitation_max(t344 - 10);
    real_type t731 = u18Limitation_min(-10 - t45);
    real_type t733 = u18Limitation_max(t45 - 10);
    real_type t735 = u19Limitation_min(-10 - t58);
    real_type t737 = u19Limitation_max(t58 - 10);
    real_type t739 = u20Limitation_min(-10 - t70);
    real_type t741 = u20Limitation_max(t70 - 10);
    real_type t742 = t492 * t492;
    real_type t744 = t715 + t717 + t719 + t721 + t723 + t725 + t727 + t729 + t731 + t733 + t735 + t737 + t739 + t741 + 20 * t742;
    real_type t746 = t495 * t495;
    real_type t748 = t498 * t498;
    real_type t750 = t438 * t438;
    real_type t752 = t442 * t442;
    real_type t754 = t445 * t445;
    real_type t756 = t448 * t448;
    real_type t758 = t451 * t451;
    real_type t760 = t454 * t454;
    real_type t762 = t457 * t457;
    real_type t764 = t460 * t460;
    real_type t766 = t463 * t463;
    real_type t768 = t466 * t466;
    real_type t770 = t469 * t469;
    real_type t772 = t472 * t472;
    real_type t774 = t475 * t475;
    real_type t776 = 19 * t746 + 18 * t748 + 17 * t750 + 16 * t752 + 15 * t754 + 14 * t756 + 13 * t758 + 12 * t760 + 11 * t762 + 10 * t764 + 9 * t766 + 8 * t768 + 7 * t770 + 6 * t772 + 5 * t774;
    real_type t777 = t478 * t478;
    real_type t779 = t481 * t481;
    real_type t781 = t484 * t484;
    real_type t783 = t489 * t489;
    real_type t785 = xx1Limitation_min(-t25 - t395);
    real_type t787 = xx1Limitation_max(t395 - t25);
    real_type t789 = xx2Limitation_min(-t25 - t406);
    real_type t791 = xx2Limitation_max(t406 - t25);
    real_type t793 = xx3Limitation_min(-t25 - t417);
    real_type t795 = xx3Limitation_max(t417 - t25);
    real_type t797 = xx4Limitation_min(-t25 - t428);
    real_type t799 = xx4Limitation_max(t428 - t25);
    real_type t801 = xx5Limitation_min(-t25 - t354);
    real_type t803 = xx5Limitation_max(t354 - t25);
    real_type t805 = xx6Limitation_min(-t25 - t369);
    real_type t806 = 4 * t777 + 3 * t779 + 2 * t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t48 + t159 + t268 + t360 + t440 + t486 + t522 + t553 + t587 + t618 + t649 + t680 + t713 + t744 + t776 + t806;
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
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
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
    real_type t2   = X__[iX_xx12];
    real_type t3   = sin(t2);
    real_type t5   = P__[iP_u12];
    real_type t7   = pow(V__[71] - 0.2e0 * t3 - t5, 2);
    real_type t10  = sin(X__[iX_x12]);
    real_type t12  = pow(V__[31] - t10 - t5, 2);
    real_type t14  = X__[iX_yy3];
    real_type t16  = Q__[iQ_zeta];
    real_type t18  = sin(t16 + 2);
    real_type t21  = pow(V__[42] - 0.12e1 * t14 - 0.1e0 * t18, 2);
    real_type t23  = X__[iX_yy4];
    real_type t26  = sin(t16 + 3);
    real_type t29  = pow(V__[43] - 0.12e1 * t23 - 0.1e0 * t26, 2);
    real_type t31  = X__[iX_yy5];
    real_type t34  = sin(t16 + 4);
    real_type t37  = pow(V__[44] - 0.12e1 * t31 - 0.1e0 * t34, 2);
    real_type t39  = X__[iX_xx13];
    real_type t40  = sin(t39);
    real_type t42  = P__[iP_u13];
    real_type t44  = pow(V__[72] - 0.2e0 * t40 - t42, 2);
    real_type t47  = sin(X__[iX_x13]);
    real_type t49  = pow(V__[32] - t47 - t42, 2);
    real_type t51  = X__[iX_xx14];
    real_type t52  = sin(t51);
    real_type t54  = P__[iP_u14];
    real_type t56  = pow(V__[73] - 0.2e0 * t52 - t54, 2);
    real_type t57  = ModelPars[iM_xy_bound];
    real_type t58  = X__[iX_yy20];
    real_type t60  = yy20Limitation_min(-t57 - t58);
    real_type t62  = yy20Limitation_max(t58 - t57);
    real_type t64  = X__[iX_yy1];
    real_type t66  = sin(t16);
    real_type t69  = pow(V__[40] - 0.12e1 * t64 - 0.1e0 * t66, 2);
    real_type t71  = X__[iX_yy2];
    real_type t74  = sin(t16 + 1);
    real_type t77  = pow(V__[41] - 0.12e1 * t71 - 0.1e0 * t74, 2);
    real_type t78  = t7 + t12 + t21 + t29 + t37 + t44 + t49 + t56 + t60 + t62 + t69 + t77;
    real_type t81  = sin(X__[iX_x17]);
    real_type t82  = P__[iP_u17];
    real_type t84  = pow(V__[36] - t81 - t82, 2);
    real_type t86  = X__[iX_xx18];
    real_type t87  = sin(t86);
    real_type t89  = P__[iP_u18];
    real_type t91  = pow(V__[77] - 0.2e0 * t87 - t89, 2);
    real_type t94  = sin(X__[iX_x18]);
    real_type t96  = pow(V__[37] - t94 - t89, 2);
    real_type t98  = X__[iX_yy6];
    real_type t101 = sin(t16 + 5);
    real_type t104 = pow(V__[45] - 0.12e1 * t98 - 0.1e0 * t101, 2);
    real_type t106 = X__[iX_yy7];
    real_type t109 = sin(t16 + 6);
    real_type t112 = pow(V__[46] - 0.12e1 * t106 - 0.1e0 * t109, 2);
    real_type t114 = X__[iX_xx9];
    real_type t115 = sin(t114);
    real_type t117 = P__[iP_u9];
    real_type t119 = pow(V__[68] - 0.2e0 * t115 - t117, 2);
    real_type t122 = sin(X__[iX_x9]);
    real_type t124 = pow(V__[28] - t122 - t117, 2);
    real_type t126 = X__[iX_xx10];
    real_type t127 = sin(t126);
    real_type t129 = P__[iP_u10];
    real_type t131 = pow(V__[69] - 0.2e0 * t127 - t129, 2);
    real_type t133 = X__[iX_xx19];
    real_type t134 = sin(t133);
    real_type t136 = P__[iP_u19];
    real_type t138 = pow(V__[78] - 0.2e0 * t134 - t136, 2);
    real_type t141 = sin(X__[iX_x19]);
    real_type t143 = pow(V__[38] - t141 - t136, 2);
    real_type t145 = X__[iX_xx20];
    real_type t146 = sin(t145);
    real_type t148 = P__[iP_u20];
    real_type t150 = pow(V__[79] - 0.2e0 * t146 - t148, 2);
    real_type t153 = sin(X__[iX_x10]);
    real_type t155 = pow(V__[29] - t153 - t129, 2);
    real_type t157 = X__[iX_xx11];
    real_type t158 = sin(t157);
    real_type t160 = P__[iP_u11];
    real_type t162 = pow(V__[70] - 0.2e0 * t158 - t160, 2);
    real_type t163 = t84 + t91 + t96 + t104 + t112 + t119 + t124 + t131 + t138 + t143 + t150 + t155 + t162;
    real_type t167 = sin(X__[iX_x11]);
    real_type t169 = pow(V__[30] - t167 - t160, 2);
    real_type t172 = sin(X__[iX_x7]);
    real_type t173 = P__[iP_u7];
    real_type t175 = pow(V__[26] - t172 - t173, 2);
    real_type t177 = X__[iX_xx8];
    real_type t178 = sin(t177);
    real_type t180 = P__[iP_u8];
    real_type t182 = pow(V__[67] - 0.2e0 * t178 - t180, 2);
    real_type t185 = sin(X__[iX_x8]);
    real_type t187 = pow(V__[27] - t185 - t180, 2);
    real_type t189 = X__[iX_xx16];
    real_type t190 = sin(t189);
    real_type t192 = P__[iP_u16];
    real_type t194 = pow(V__[75] - 0.2e0 * t190 - t192, 2);
    real_type t197 = sin(X__[iX_x16]);
    real_type t199 = pow(V__[35] - t197 - t192, 2);
    real_type t201 = X__[iX_xx17];
    real_type t202 = sin(t201);
    real_type t205 = pow(V__[76] - 0.2e0 * t202 - t82, 2);
    real_type t207 = X__[iX_xx6];
    real_type t208 = sin(t207);
    real_type t210 = P__[iP_u6];
    real_type t212 = pow(V__[65] - 0.2e0 * t208 - t210, 2);
    real_type t215 = sin(X__[iX_x6]);
    real_type t217 = pow(V__[25] - t215 - t210, 2);
    real_type t219 = X__[iX_xx7];
    real_type t220 = sin(t219);
    real_type t223 = pow(V__[66] - 0.2e0 * t220 - t173, 2);
    real_type t225 = X__[iX_xx4];
    real_type t226 = sin(t225);
    real_type t228 = P__[iP_u4];
    real_type t230 = pow(V__[63] - 0.2e0 * t226 - t228, 2);
    real_type t232 = X__[iX_xx5];
    real_type t233 = sin(t232);
    real_type t235 = P__[iP_u5];
    real_type t237 = pow(V__[64] - 0.2e0 * t233 - t235, 2);
    real_type t238 = t169 + t175 + t182 + t187 + t194 + t199 + t205 + t212 + t217 + t223 + t230 + t237;
    real_type t241 = sin(X__[iX_x5]);
    real_type t243 = pow(V__[24] - t241 - t235, 2);
    real_type t247 = pow(V__[10] - X__[iX_y11], 2);
    real_type t251 = pow(V__[11] - X__[iX_y12], 2);
    real_type t255 = pow(V__[12] - X__[iX_y13], 2);
    real_type t259 = pow(V__[13] - X__[iX_y14], 2);
    real_type t262 = sin(X__[iX_x3]);
    real_type t263 = P__[iP_u3];
    real_type t265 = pow(V__[22] - t262 - t263, 2);
    real_type t267 = X__[iX_xx3];
    real_type t268 = sin(t267);
    real_type t271 = pow(V__[62] - 0.2e0 * t268 - t263, 2);
    real_type t274 = sin(X__[iX_x4]);
    real_type t276 = pow(V__[23] - t274 - t228, 2);
    real_type t278 = X__[iX_xx1];
    real_type t279 = sin(t278);
    real_type t281 = P__[iP_u1];
    real_type t283 = pow(V__[60] - 0.2e0 * t279 - t281, 2);
    real_type t286 = sin(X__[iX_x2]);
    real_type t287 = P__[iP_u2];
    real_type t289 = pow(V__[21] - t286 - t287, 2);
    real_type t291 = X__[iX_xx2];
    real_type t292 = sin(t291);
    real_type t295 = pow(V__[61] - 0.2e0 * t292 - t287, 2);
    real_type t298 = sin(X__[iX_x14]);
    real_type t300 = pow(V__[33] - t298 - t54, 2);
    real_type t302 = X__[iX_xx15];
    real_type t303 = sin(t302);
    real_type t305 = P__[iP_u15];
    real_type t307 = pow(V__[74] - 0.2e0 * t303 - t305, 2);
    real_type t308 = t243 + t247 + t251 + t255 + t259 + t265 + t271 + t276 + t283 + t289 + t295 + t300 + t307;
    real_type t313 = sin(X__[iX_x15]);
    real_type t315 = pow(V__[34] - t313 - t305, 2);
    real_type t317 = X__[iX_yy19];
    real_type t320 = sin(t16 + 18);
    real_type t323 = pow(V__[58] - 0.12e1 * t317 - 0.1e0 * t320, 2);
    real_type t327 = sin(t16 + 19);
    real_type t330 = pow(V__[59] - 0.12e1 * t58 - 0.1e0 * t327, 2);
    real_type t333 = sin(X__[iX_x1]);
    real_type t335 = pow(V__[20] - t333 - t281, 2);
    real_type t337 = X__[iX_yy17];
    real_type t340 = sin(t16 + 16);
    real_type t343 = pow(V__[56] - 0.12e1 * t337 - 0.1e0 * t340, 2);
    real_type t345 = X__[iX_yy18];
    real_type t348 = sin(t16 + 17);
    real_type t351 = pow(V__[57] - 0.12e1 * t345 - 0.1e0 * t348, 2);
    real_type t353 = X__[iX_yy14];
    real_type t356 = sin(t16 + 13);
    real_type t359 = pow(V__[53] - 0.12e1 * t353 - 0.1e0 * t356, 2);
    real_type t361 = X__[iX_yy15];
    real_type t364 = sin(t16 + 14);
    real_type t367 = pow(V__[54] - 0.12e1 * t361 - 0.1e0 * t364, 2);
    real_type t369 = X__[iX_yy16];
    real_type t372 = sin(t16 + 15);
    real_type t375 = pow(V__[55] - 0.12e1 * t369 - 0.1e0 * t372, 2);
    real_type t377 = X__[iX_yy11];
    real_type t380 = sin(t16 + 10);
    real_type t383 = pow(V__[50] - 0.12e1 * t377 - 0.1e0 * t380, 2);
    real_type t385 = X__[iX_yy12];
    real_type t388 = sin(t16 + 11);
    real_type t391 = pow(V__[51] - 0.12e1 * t385 - 0.1e0 * t388, 2);
    real_type t393 = X__[iX_yy13];
    real_type t396 = sin(t16 + 12);
    real_type t399 = pow(V__[52] - 0.12e1 * t393 - 0.1e0 * t396, 2);
    real_type t400 = t315 + t323 + t330 + t335 + t343 + t351 + t359 + t367 + t375 + t383 + t391 + t399;
    real_type t402 = X__[iX_yy8];
    real_type t405 = sin(t16 + 7);
    real_type t408 = pow(V__[47] - 0.12e1 * t402 - 0.1e0 * t405, 2);
    real_type t410 = X__[iX_yy9];
    real_type t413 = sin(t16 + 8);
    real_type t416 = pow(V__[48] - 0.12e1 * t410 - 0.1e0 * t413, 2);
    real_type t418 = X__[iX_yy10];
    real_type t421 = sin(t16 + 9);
    real_type t424 = pow(V__[49] - 0.12e1 * t418 - 0.1e0 * t421, 2);
    real_type t428 = pow(V__[2] - X__[iX_y3], 2);
    real_type t432 = pow(V__[3] - X__[iX_y4], 2);
    real_type t436 = pow(V__[4] - X__[iX_y5], 2);
    real_type t440 = pow(V__[5] - X__[iX_y6], 2);
    real_type t444 = pow(V__[17] - X__[iX_y18], 2);
    real_type t448 = pow(V__[18] - X__[iX_y19], 2);
    real_type t452 = pow(V__[19] - X__[iX_y20], 2);
    real_type t456 = pow(V__[14] - X__[iX_y15], 2);
    real_type t460 = pow(V__[15] - X__[iX_y16], 2);
    real_type t464 = pow(V__[16] - X__[iX_y17], 2);
    real_type t465 = t408 + t416 + t424 + t428 + t432 + t436 + t440 + t444 + t448 + t452 + t456 + t460 + t464;
    real_type t470 = pow(V__[6] - X__[iX_y7], 2);
    real_type t474 = pow(V__[7] - X__[iX_y8], 2);
    real_type t478 = pow(V__[8] - X__[iX_y9], 2);
    real_type t482 = pow(V__[9] - X__[iX_y10], 2);
    real_type t484 = yy18Limitation_max(t345 - t57);
    real_type t486 = yy19Limitation_min(-t57 - t317);
    real_type t488 = yy19Limitation_max(t317 - t57);
    real_type t490 = yy16Limitation_max(t369 - t57);
    real_type t492 = yy17Limitation_min(-t57 - t337);
    real_type t494 = yy17Limitation_max(t337 - t57);
    real_type t496 = yy18Limitation_min(-t57 - t345);
    real_type t498 = yy15Limitation_min(-t57 - t361);
    real_type t499 = t470 + t474 + t478 + t482 + t484 + t486 + t488 + t490 + t492 + t494 + t496 + t498;
    real_type t501 = yy15Limitation_max(t361 - t57);
    real_type t503 = yy16Limitation_min(-t57 - t369);
    real_type t505 = yy13Limitation_min(-t57 - t393);
    real_type t507 = yy13Limitation_max(t393 - t57);
    real_type t509 = yy14Limitation_min(-t57 - t353);
    real_type t511 = yy14Limitation_max(t353 - t57);
    real_type t513 = yy11Limitation_min(-t57 - t377);
    real_type t515 = yy11Limitation_max(t377 - t57);
    real_type t517 = yy12Limitation_min(-t57 - t385);
    real_type t519 = yy12Limitation_max(t385 - t57);
    real_type t521 = yy9Limitation_min(-t57 - t410);
    real_type t523 = yy9Limitation_max(t410 - t57);
    real_type t525 = yy10Limitation_min(-t57 - t418);
    real_type t526 = t501 + t503 + t505 + t507 + t509 + t511 + t513 + t515 + t517 + t519 + t521 + t523 + t525;
    real_type t531 = yy10Limitation_max(t418 - t57);
    real_type t533 = yy7Limitation_min(-t57 - t106);
    real_type t535 = yy7Limitation_max(t106 - t57);
    real_type t537 = yy8Limitation_min(-t57 - t402);
    real_type t539 = yy8Limitation_max(t402 - t57);
    real_type t541 = yy5Limitation_min(-t57 - t31);
    real_type t543 = yy5Limitation_max(t31 - t57);
    real_type t545 = yy6Limitation_min(-t57 - t98);
    real_type t547 = yy6Limitation_max(t98 - t57);
    real_type t549 = yy3Limitation_min(-t57 - t14);
    real_type t551 = yy3Limitation_max(t14 - t57);
    real_type t553 = yy4Limitation_min(-t57 - t23);
    real_type t554 = t531 + t533 + t535 + t537 + t539 + t541 + t543 + t545 + t547 + t549 + t551 + t553;
    real_type t556 = yy4Limitation_max(t23 - t57);
    real_type t558 = yy1Limitation_max(t64 - t57);
    real_type t560 = yy2Limitation_min(-t57 - t71);
    real_type t562 = yy2Limitation_max(t71 - t57);
    real_type t564 = xx19Limitation_max(t133 - t57);
    real_type t566 = xx20Limitation_min(-t57 - t145);
    real_type t568 = xx20Limitation_max(t145 - t57);
    real_type t570 = yy1Limitation_min(-t57 - t64);
    real_type t572 = xx17Limitation_max(t201 - t57);
    real_type t574 = xx18Limitation_min(-t57 - t86);
    real_type t576 = xx18Limitation_max(t86 - t57);
    real_type t578 = xx19Limitation_min(-t57 - t133);
    real_type t580 = xx15Limitation_max(t302 - t57);
    real_type t581 = t556 + t558 + t560 + t562 + t564 + t566 + t568 + t570 + t572 + t574 + t576 + t578 + t580;
    real_type t584 = xx16Limitation_min(-t57 - t189);
    real_type t586 = xx16Limitation_max(t189 - t57);
    real_type t588 = xx17Limitation_min(-t57 - t201);
    real_type t590 = xx13Limitation_max(t39 - t57);
    real_type t592 = xx14Limitation_min(-t57 - t51);
    real_type t594 = xx14Limitation_max(t51 - t57);
    real_type t596 = xx15Limitation_min(-t57 - t302);
    real_type t598 = xx12Limitation_min(-t57 - t2);
    real_type t600 = xx12Limitation_max(t2 - t57);
    real_type t602 = xx13Limitation_min(-t57 - t39);
    real_type t604 = xx10Limitation_min(-t57 - t126);
    real_type t606 = xx10Limitation_max(t126 - t57);
    real_type t607 = t584 + t586 + t588 + t590 + t592 + t594 + t596 + t598 + t600 + t602 + t604 + t606;
    real_type t609 = xx11Limitation_min(-t57 - t157);
    real_type t611 = xx11Limitation_max(t157 - t57);
    real_type t613 = xx8Limitation_min(-t57 - t177);
    real_type t615 = xx8Limitation_max(t177 - t57);
    real_type t617 = xx9Limitation_min(-t57 - t114);
    real_type t619 = xx9Limitation_max(t114 - t57);
    real_type t621 = xx6Limitation_min(-t57 - t207);
    real_type t623 = xx6Limitation_max(t207 - t57);
    real_type t625 = xx7Limitation_min(-t57 - t219);
    real_type t627 = xx7Limitation_max(t219 - t57);
    real_type t629 = xx4Limitation_min(-t57 - t225);
    real_type t631 = xx4Limitation_max(t225 - t57);
    real_type t633 = xx5Limitation_min(-t57 - t232);
    real_type t634 = t609 + t611 + t613 + t615 + t617 + t619 + t621 + t623 + t625 + t627 + t629 + t631 + t633;
    real_type t638 = xx5Limitation_max(t232 - t57);
    real_type t640 = u20Limitation_max(t148 - 10);
    real_type t642 = xx2Limitation_max(t291 - t57);
    real_type t644 = xx3Limitation_min(-t57 - t267);
    real_type t646 = xx3Limitation_max(t267 - t57);
    real_type t648 = u18Limitation_min(-10 - t89);
    real_type t650 = u18Limitation_max(t89 - 10);
    real_type t652 = u19Limitation_min(-10 - t136);
    real_type t654 = u19Limitation_max(t136 - 10);
    real_type t656 = u20Limitation_min(-10 - t148);
    real_type t658 = u16Limitation_min(-10 - t192);
    real_type t660 = u16Limitation_max(t192 - 10);
    real_type t661 = t638 + t640 + t642 + t644 + t646 + t648 + t650 + t652 + t654 + t656 + t658 + t660;
    real_type t663 = u17Limitation_min(-10 - t82);
    real_type t665 = u17Limitation_max(t82 - 10);
    real_type t667 = u13Limitation_max(t42 - 10);
    real_type t669 = u14Limitation_min(-10 - t54);
    real_type t671 = u14Limitation_max(t54 - 10);
    real_type t673 = u15Limitation_min(-10 - t305);
    real_type t675 = u15Limitation_max(t305 - 10);
    real_type t677 = u11Limitation_min(-10 - t160);
    real_type t679 = u11Limitation_max(t160 - 10);
    real_type t681 = u12Limitation_min(-10 - t5);
    real_type t683 = u12Limitation_max(t5 - 10);
    real_type t685 = u13Limitation_min(-10 - t42);
    real_type t687 = u9Limitation_min(-10 - t117);
    real_type t688 = t663 + t665 + t667 + t669 + t671 + t673 + t675 + t677 + t679 + t681 + t683 + t685 + t687;
    real_type t691 = u9Limitation_max(t117 - 10);
    real_type t693 = u10Limitation_min(-10 - t129);
    real_type t695 = u10Limitation_max(t129 - 10);
    real_type t697 = u6Limitation_max(t210 - 10);
    real_type t699 = u7Limitation_min(-10 - t173);
    real_type t701 = u7Limitation_max(t173 - 10);
    real_type t703 = u8Limitation_min(-10 - t180);
    real_type t705 = u8Limitation_max(t180 - 10);
    real_type t707 = u4Limitation_min(-10 - t228);
    real_type t709 = u4Limitation_max(t228 - 10);
    real_type t711 = u5Limitation_min(-10 - t235);
    real_type t713 = u5Limitation_max(t235 - 10);
    real_type t714 = t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711 + t713;
    real_type t716 = u6Limitation_min(-10 - t210);
    real_type t718 = u2Limitation_min(-10 - t287);
    real_type t720 = u2Limitation_max(t287 - 10);
    real_type t722 = u3Limitation_min(-10 - t263);
    real_type t724 = u3Limitation_max(t263 - 10);
    real_type t726 = xx1Limitation_max(t278 - t57);
    real_type t728 = xx2Limitation_min(-t57 - t291);
    real_type t730 = u1Limitation_min(-10 - t281);
    real_type t732 = u1Limitation_max(t281 - 10);
    real_type t734 = xx1Limitation_min(-t57 - t278);
    real_type t737 = sin(X__[iX_x20]);
    real_type t739 = pow(V__[39] - t737 - t148, 2);
    real_type t743 = pow(V__[0] - X__[iX_y1], 2);
    real_type t747 = pow(V__[1] - X__[iX_y2], 2);
    real_type t748 = t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t739 + t743 + t747;
    real_type result__ = t78 + t163 + t238 + t308 + t400 + t465 + t499 + t526 + t554 + t581 + t607 + t634 + t661 + t688 + t714 + t748;
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
