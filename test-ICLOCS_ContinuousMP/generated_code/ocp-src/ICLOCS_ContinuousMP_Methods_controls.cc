/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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
    real_type t1   = XM__[13];
    real_type t2   = t1 * t1;
    real_type t4   = XM__[14];
    real_type t5   = t4 * t4;
    real_type t7   = XM__[15];
    real_type t8   = t7 * t7;
    real_type t10  = XM__[16];
    real_type t11  = t10 * t10;
    real_type t13  = XM__[17];
    real_type t14  = t13 * t13;
    real_type t16  = XM__[18];
    real_type t17  = t16 * t16;
    real_type t19  = XM__[19];
    real_type t20  = t19 * t19;
    real_type t21  = XM__[20];
    real_type t22  = t21 * t21;
    real_type t24  = XM__[21];
    real_type t25  = t24 * t24;
    real_type t27  = XM__[22];
    real_type t28  = t27 * t27;
    real_type t30  = XM__[23];
    real_type t31  = t30 * t30;
    real_type t33  = XM__[24];
    real_type t34  = t33 * t33;
    real_type t36  = XM__[25];
    real_type t37  = t36 * t36;
    real_type t39  = XM__[26];
    real_type t40  = t39 * t39;
    real_type t42  = XM__[27];
    real_type t43  = t42 * t42;
    real_type t45  = 7 * t2 + 6 * t5 + 5 * t8 + 4 * t11 + 3 * t14 + 2 * t17 + t20 + 20 * t22 + 19 * t25 + 18 * t28 + 17 * t31 + 16 * t34 + 15 * t37 + 14 * t40 + 13 * t43;
    real_type t46  = XM__[12];
    real_type t47  = t46 * t46;
    real_type t49  = XM__[11];
    real_type t50  = t49 * t49;
    real_type t52  = XM__[10];
    real_type t53  = t52 * t52;
    real_type t55  = XM__[9];
    real_type t56  = t55 * t55;
    real_type t58  = XM__[8];
    real_type t59  = t58 * t58;
    real_type t61  = XM__[7];
    real_type t62  = t61 * t61;
    real_type t64  = XM__[5];
    real_type t65  = t64 * t64;
    real_type t67  = XM__[6];
    real_type t68  = t67 * t67;
    real_type t70  = XM__[4];
    real_type t71  = t70 * t70;
    real_type t73  = XM__[3];
    real_type t74  = t73 * t73;
    real_type t76  = XM__[2];
    real_type t77  = t76 * t76;
    real_type t79  = XM__[1];
    real_type t80  = t79 * t79;
    real_type t82  = XM__[0];
    real_type t83  = t82 * t82;
    real_type t85  = XM__[68];
    real_type t86  = ModelPars[iM_xy_bound];
    real_type t88  = yy9Limitation_max(t85 - t86);
    real_type t90  = yy9Limitation_min(-t86 - t85);
    real_type t91  = 8 * t47 + 9 * t50 + 10 * t53 + 11 * t56 + 12 * t59 + 13 * t62 + 15 * t65 + 14 * t68 + 16 * t71 + 17 * t74 + 18 * t77 + 19 * t80 + 20 * t83 + t88 + t90;
    real_type t93  = XM__[67];
    real_type t95  = yy8Limitation_max(t93 - t86);
    real_type t97  = yy8Limitation_min(-t86 - t93);
    real_type t98  = XM__[66];
    real_type t100 = yy7Limitation_max(t98 - t86);
    real_type t102 = yy7Limitation_min(-t86 - t98);
    real_type t103 = XM__[65];
    real_type t105 = yy6Limitation_max(t103 - t86);
    real_type t107 = yy6Limitation_min(-t86 - t103);
    real_type t108 = XM__[64];
    real_type t110 = yy5Limitation_min(-t86 - t108);
    real_type t112 = yy5Limitation_max(t108 - t86);
    real_type t113 = XM__[63];
    real_type t115 = yy4Limitation_min(-t86 - t113);
    real_type t117 = yy4Limitation_max(t113 - t86);
    real_type t118 = XM__[62];
    real_type t120 = yy3Limitation_max(t118 - t86);
    real_type t122 = yy3Limitation_min(-t86 - t118);
    real_type t123 = XM__[61];
    real_type t125 = yy2Limitation_max(t123 - t86);
    real_type t127 = yy2Limitation_min(-t86 - t123);
    real_type t128 = XM__[60];
    real_type t130 = yy1Limitation_max(t128 - t86);
    real_type t131 = t95 + t97 + t100 + t102 + t105 + t107 + t110 + t112 + t115 + t117 + t120 + t122 + t125 + t127 + t130;
    real_type t133 = yy1Limitation_min(-t86 - t128);
    real_type t134 = XM__[59];
    real_type t136 = xx20Limitation_max(t134 - t86);
    real_type t138 = xx20Limitation_min(-t86 - t134);
    real_type t139 = XM__[58];
    real_type t141 = xx19Limitation_max(t139 - t86);
    real_type t143 = xx19Limitation_min(-t86 - t139);
    real_type t144 = XM__[57];
    real_type t146 = xx18Limitation_max(t144 - t86);
    real_type t148 = xx18Limitation_min(-t86 - t144);
    real_type t149 = XM__[56];
    real_type t151 = xx17Limitation_max(t149 - t86);
    real_type t153 = xx17Limitation_min(-t86 - t149);
    real_type t154 = XM__[55];
    real_type t156 = xx16Limitation_max(t154 - t86);
    real_type t158 = xx16Limitation_min(-t86 - t154);
    real_type t159 = XM__[54];
    real_type t161 = xx15Limitation_max(t159 - t86);
    real_type t163 = xx15Limitation_min(-t86 - t159);
    real_type t164 = XM__[53];
    real_type t166 = xx14Limitation_max(t164 - t86);
    real_type t168 = xx14Limitation_min(-t86 - t164);
    real_type t169 = t133 + t136 + t138 + t141 + t143 + t146 + t148 + t151 + t153 + t156 + t158 + t161 + t163 + t166 + t168;
    real_type t172 = XM__[52];
    real_type t174 = xx13Limitation_max(t172 - t86);
    real_type t176 = xx13Limitation_min(-t86 - t172);
    real_type t177 = XM__[51];
    real_type t179 = xx12Limitation_min(-t86 - t177);
    real_type t181 = xx12Limitation_max(t177 - t86);
    real_type t182 = XM__[50];
    real_type t184 = xx11Limitation_max(t182 - t86);
    real_type t186 = xx11Limitation_min(-t86 - t182);
    real_type t187 = XM__[49];
    real_type t189 = xx10Limitation_max(t187 - t86);
    real_type t191 = xx10Limitation_min(-t86 - t187);
    real_type t192 = XM__[48];
    real_type t194 = xx9Limitation_max(t192 - t86);
    real_type t196 = xx9Limitation_min(-t86 - t192);
    real_type t197 = XM__[47];
    real_type t199 = xx8Limitation_max(t197 - t86);
    real_type t201 = xx8Limitation_min(-t86 - t197);
    real_type t202 = XM__[46];
    real_type t204 = xx7Limitation_max(t202 - t86);
    real_type t206 = xx7Limitation_min(-t86 - t202);
    real_type t207 = XM__[45];
    real_type t209 = xx6Limitation_max(t207 - t86);
    real_type t210 = t174 + t176 + t179 + t181 + t184 + t186 + t189 + t191 + t194 + t196 + t199 + t201 + t204 + t206 + t209;
    real_type t212 = xx6Limitation_min(-t86 - t207);
    real_type t213 = XM__[44];
    real_type t215 = xx5Limitation_max(t213 - t86);
    real_type t217 = xx5Limitation_min(-t86 - t213);
    real_type t218 = XM__[43];
    real_type t220 = xx4Limitation_max(t218 - t86);
    real_type t222 = xx4Limitation_min(-t86 - t218);
    real_type t223 = XM__[42];
    real_type t225 = xx3Limitation_max(t223 - t86);
    real_type t227 = xx3Limitation_min(-t86 - t223);
    real_type t228 = XM__[41];
    real_type t230 = xx2Limitation_min(-t86 - t228);
    real_type t232 = xx2Limitation_max(t228 - t86);
    real_type t233 = XM__[40];
    real_type t235 = xx1Limitation_max(t233 - t86);
    real_type t237 = xx1Limitation_min(-t86 - t233);
    real_type t238 = XM__[79];
    real_type t240 = yy20Limitation_max(t238 - t86);
    real_type t242 = yy20Limitation_min(-t86 - t238);
    real_type t243 = XM__[71];
    real_type t245 = yy12Limitation_min(-t86 - t243);
    real_type t247 = yy12Limitation_max(t243 - t86);
    real_type t248 = t212 + t215 + t217 + t220 + t222 + t225 + t227 + t230 + t232 + t235 + t237 + t240 + t242 + t245 + t247;
    real_type t250 = XM__[72];
    real_type t252 = yy13Limitation_min(-t86 - t250);
    real_type t254 = yy13Limitation_max(t250 - t86);
    real_type t255 = XM__[73];
    real_type t257 = yy14Limitation_min(-t86 - t255);
    real_type t259 = yy14Limitation_max(t255 - t86);
    real_type t260 = XM__[74];
    real_type t262 = yy15Limitation_min(-t86 - t260);
    real_type t264 = yy15Limitation_max(t260 - t86);
    real_type t265 = P__[iP_u20];
    real_type t267 = u20Limitation_max(t265 - 10);
    real_type t269 = u20Limitation_min(-10 - t265);
    real_type t270 = P__[iP_u19];
    real_type t272 = u19Limitation_min(-10 - t270);
    real_type t274 = u19Limitation_max(t270 - 10);
    real_type t275 = P__[iP_u18];
    real_type t277 = u18Limitation_min(-10 - t275);
    real_type t279 = u18Limitation_max(t275 - 10);
    real_type t280 = P__[iP_u17];
    real_type t282 = u17Limitation_max(t280 - 10);
    real_type t283 = P__[iP_u16];
    real_type t285 = u16Limitation_min(-10 - t283);
    real_type t287 = u16Limitation_max(t283 - 10);
    real_type t288 = t252 + t254 + t257 + t259 + t262 + t264 + t267 + t269 + t272 + t274 + t277 + t279 + t282 + t285 + t287;
    real_type t290 = u17Limitation_min(-10 - t280);
    real_type t291 = P__[iP_u14];
    real_type t293 = u14Limitation_min(-10 - t291);
    real_type t295 = u14Limitation_max(t291 - 10);
    real_type t296 = P__[iP_u15];
    real_type t298 = u15Limitation_min(-10 - t296);
    real_type t300 = u15Limitation_max(t296 - 10);
    real_type t301 = P__[iP_u13];
    real_type t303 = u13Limitation_max(t301 - 10);
    real_type t305 = u13Limitation_min(-10 - t301);
    real_type t306 = P__[iP_u12];
    real_type t308 = u12Limitation_min(-10 - t306);
    real_type t310 = u12Limitation_max(t306 - 10);
    real_type t311 = P__[iP_u11];
    real_type t313 = u11Limitation_min(-10 - t311);
    real_type t315 = u11Limitation_max(t311 - 10);
    real_type t316 = P__[iP_u10];
    real_type t318 = u10Limitation_min(-10 - t316);
    real_type t320 = u10Limitation_max(t316 - 10);
    real_type t321 = P__[iP_u9];
    real_type t323 = u9Limitation_max(t321 - 10);
    real_type t325 = u9Limitation_min(-10 - t321);
    real_type t326 = t290 + t293 + t295 + t298 + t300 + t303 + t305 + t308 + t310 + t313 + t315 + t318 + t320 + t323 + t325;
    real_type t330 = P__[iP_u8];
    real_type t332 = u8Limitation_max(t330 - 10);
    real_type t333 = P__[iP_u7];
    real_type t335 = u7Limitation_max(t333 - 10);
    real_type t337 = u8Limitation_min(-10 - t330);
    real_type t339 = u7Limitation_min(-10 - t333);
    real_type t340 = P__[iP_u6];
    real_type t342 = u6Limitation_min(-10 - t340);
    real_type t344 = u6Limitation_max(t340 - 10);
    real_type t345 = P__[iP_u5];
    real_type t347 = u5Limitation_max(t345 - 10);
    real_type t349 = u5Limitation_min(-10 - t345);
    real_type t350 = P__[iP_u4];
    real_type t352 = u4Limitation_min(-10 - t350);
    real_type t354 = u4Limitation_max(t350 - 10);
    real_type t355 = P__[iP_u3];
    real_type t357 = u3Limitation_max(t355 - 10);
    real_type t359 = u3Limitation_min(-10 - t355);
    real_type t360 = P__[iP_u2];
    real_type t362 = u2Limitation_min(-10 - t360);
    real_type t364 = u2Limitation_max(t360 - 10);
    real_type t365 = P__[iP_u1];
    real_type t367 = u1Limitation_max(t365 - 10);
    real_type t368 = t332 + t335 + t337 + t339 + t342 + t344 + t347 + t349 + t352 + t354 + t357 + t359 + t362 + t364 + t367;
    real_type t370 = u1Limitation_min(-10 - t365);
    real_type t371 = XM__[38];
    real_type t372 = t371 * t371;
    real_type t374 = XM__[39];
    real_type t375 = t374 * t374;
    real_type t376 = XM__[37];
    real_type t377 = t376 * t376;
    real_type t379 = XM__[35];
    real_type t380 = t379 * t379;
    real_type t382 = XM__[36];
    real_type t383 = t382 * t382;
    real_type t385 = XM__[34];
    real_type t386 = t385 * t385;
    real_type t388 = XM__[32];
    real_type t389 = t388 * t388;
    real_type t391 = XM__[33];
    real_type t392 = t391 * t391;
    real_type t394 = XM__[31];
    real_type t395 = t394 * t394;
    real_type t397 = XM__[30];
    real_type t398 = t397 * t397;
    real_type t400 = XM__[28];
    real_type t401 = t400 * t400;
    real_type t403 = XM__[29];
    real_type t404 = t403 * t403;
    real_type t406 = XM__[75];
    real_type t408 = yy16Limitation_min(-t86 - t406);
    real_type t410 = yy16Limitation_max(t406 - t86);
    real_type t411 = t370 + 2 * t372 + t375 + 3 * t377 + 5 * t380 + 4 * t383 + 6 * t386 + 8 * t389 + 7 * t392 + 9 * t395 + 10 * t398 + 12 * t401 + 11 * t404 + t408 + t410;
    real_type t413 = XM__[76];
    real_type t415 = yy17Limitation_min(-t86 - t413);
    real_type t417 = yy17Limitation_max(t413 - t86);
    real_type t418 = XM__[77];
    real_type t420 = yy18Limitation_min(-t86 - t418);
    real_type t422 = yy18Limitation_max(t418 - t86);
    real_type t423 = XM__[78];
    real_type t425 = yy19Limitation_min(-t86 - t423);
    real_type t427 = yy19Limitation_max(t423 - t86);
    real_type t428 = XM__[69];
    real_type t430 = yy10Limitation_min(-t86 - t428);
    real_type t432 = yy10Limitation_max(t428 - t86);
    real_type t433 = XM__[70];
    real_type t435 = yy11Limitation_min(-t86 - t433);
    real_type t437 = yy11Limitation_max(t433 - t86);
    real_type t439 = sin(t73);
    real_type t443 = sin(t218);
    real_type t448 = sin(t70);
    real_type t452 = sin(t213);
    real_type t457 = sin(t64);
    real_type t460 = t415 + t417 + t420 + t422 + t425 + t427 + t430 + t432 + t435 + t437 + (t439 + t350) * LM__[23] + (0.2e0 * t443 + t350) * LM__[63] + (t448 + t345) * LM__[24] + (0.2e0 * t452 + t345) * LM__[64] + (t457 + t340) * LM__[25];
    real_type t462 = sin(t207);
    real_type t467 = sin(t67);
    real_type t471 = sin(t202);
    real_type t476 = sin(t61);
    real_type t480 = sin(t197);
    real_type t504 = (0.2e0 * t462 + t340) * LM__[65] + (t467 + t333) * LM__[26] + (0.2e0 * t471 + t333) * LM__[66] + (t476 + t330) * LM__[27] + (0.2e0 * t480 + t330) * LM__[67] + t21 * LM__[0] + t24 * LM__[1] + t27 * LM__[2] + t30 * LM__[3] + t33 * LM__[4] + t36 * LM__[5] + t39 * LM__[6] + t42 * LM__[7] + t400 * LM__[8] + t403 * LM__[9];
    real_type t528 = sin(t52);
    real_type t532 = sin(t182);
    real_type t537 = sin(t49);
    real_type t541 = sin(t177);
    real_type t546 = sin(t46);
    real_type t549 = t397 * LM__[10] + t394 * LM__[11] + t388 * LM__[12] + t391 * LM__[13] + t385 * LM__[14] + t379 * LM__[15] + t382 * LM__[16] + t376 * LM__[17] + t371 * LM__[18] + t374 * LM__[19] + (t528 + t311) * LM__[30] + (0.2e0 * t532 + t311) * LM__[70] + (t537 + t306) * LM__[31] + (0.2e0 * t541 + t306) * LM__[71] + (t546 + t301) * LM__[32];
    real_type t551 = sin(t172);
    real_type t556 = sin(t1);
    real_type t560 = sin(t164);
    real_type t565 = sin(t4);
    real_type t569 = sin(t159);
    real_type t574 = sin(t7);
    real_type t578 = sin(t154);
    real_type t583 = sin(t10);
    real_type t587 = sin(t149);
    real_type t592 = sin(t13);
    real_type t596 = sin(t144);
    real_type t601 = sin(t16);
    real_type t605 = sin(t139);
    real_type t610 = sin(t19);
    real_type t614 = sin(t134);
    real_type t618 = (0.2e0 * t551 + t301) * LM__[72] + (t556 + t291) * LM__[33] + (0.2e0 * t560 + t291) * LM__[73] + (t565 + t296) * LM__[34] + (0.2e0 * t569 + t296) * LM__[74] + (t574 + t283) * LM__[35] + (0.2e0 * t578 + t283) * LM__[75] + (t583 + t280) * LM__[36] + (0.2e0 * t587 + t280) * LM__[76] + (t592 + t275) * LM__[37] + (0.2e0 * t596 + t275) * LM__[77] + (t601 + t270) * LM__[38] + (0.2e0 * t605 + t270) * LM__[78] + (t610 + t265) * LM__[39] + (0.2e0 * t614 + t265) * LM__[79];
    real_type t622 = QM__[0];
    real_type t623 = sin(t622);
    real_type t630 = sin(t622 + 1);
    real_type t637 = sin(t622 + 2);
    real_type t644 = sin(t622 + 3);
    real_type t651 = sin(t622 + 4);
    real_type t656 = sin(t233);
    real_type t661 = sin(t82);
    real_type t665 = sin(t228);
    real_type t670 = sin(t79);
    real_type t674 = sin(t76);
    real_type t678 = sin(t223);
    real_type t685 = sin(t622 + 5);
    real_type t692 = sin(t622 + 6);
    real_type t699 = sin(t622 + 7);
    real_type t706 = sin(t622 + 8);
    real_type t710 = (0.12e1 * t128 + 0.1e0 * t623) * LM__[40] + (0.12e1 * t123 + 0.1e0 * t630) * LM__[41] + (0.12e1 * t118 + 0.1e0 * t637) * LM__[42] + (0.12e1 * t113 + 0.1e0 * t644) * LM__[43] + (0.12e1 * t108 + 0.1e0 * t651) * LM__[44] + (0.2e0 * t656 + t365) * LM__[60] + (t661 + t365) * LM__[20] + (0.2e0 * t665 + t360) * LM__[61] + (t670 + t360) * LM__[21] + (t674 + t355) * LM__[22] + (0.2e0 * t678 + t355) * LM__[62] + (0.12e1 * t103 + 0.1e0 * t685) * LM__[45] + (0.12e1 * t98 + 0.1e0 * t692) * LM__[46] + (0.12e1 * t93 + 0.1e0 * t699) * LM__[47] + (0.12e1 * t85 + 0.1e0 * t706) * LM__[48];
    real_type t714 = sin(t622 + 9);
    real_type t721 = sin(t622 + 10);
    real_type t728 = sin(t622 + 11);
    real_type t735 = sin(t622 + 12);
    real_type t742 = sin(t622 + 13);
    real_type t749 = sin(t622 + 14);
    real_type t756 = sin(t622 + 15);
    real_type t763 = sin(t622 + 16);
    real_type t770 = sin(t622 + 17);
    real_type t777 = sin(t622 + 18);
    real_type t784 = sin(t622 + 19);
    real_type t789 = sin(t58);
    real_type t793 = sin(t192);
    real_type t798 = sin(t55);
    real_type t802 = sin(t187);
    real_type t806 = (0.12e1 * t428 + 0.1e0 * t714) * LM__[49] + (0.12e1 * t433 + 0.1e0 * t721) * LM__[50] + (0.12e1 * t243 + 0.1e0 * t728) * LM__[51] + (0.12e1 * t250 + 0.1e0 * t735) * LM__[52] + (0.12e1 * t255 + 0.1e0 * t742) * LM__[53] + (0.12e1 * t260 + 0.1e0 * t749) * LM__[54] + (0.12e1 * t406 + 0.1e0 * t756) * LM__[55] + (0.12e1 * t413 + 0.1e0 * t763) * LM__[56] + (0.12e1 * t418 + 0.1e0 * t770) * LM__[57] + (0.12e1 * t423 + 0.1e0 * t777) * LM__[58] + (0.12e1 * t238 + 0.1e0 * t784) * LM__[59] + (t789 + t321) * LM__[28] + (0.2e0 * t793 + t321) * LM__[68] + (t798 + t316) * LM__[29] + (0.2e0 * t802 + t316) * LM__[69];
    real_type result__ = t45 + t91 + t131 + t169 + t210 + t248 + t288 + t326 + t368 + t411 + t460 + t504 + t549 + t618 + t710 + t806;
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
    real_type t2   = X__[iX_yy16];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = sin(t4 + 15);
    real_type t9   = pow(V__[55] - 0.12e1 * t2 - 0.1e0 * t6, 2);
    real_type t11  = X__[iX_yy17];
    real_type t14  = sin(t4 + 16);
    real_type t17  = pow(V__[56] - 0.12e1 * t11 - 0.1e0 * t14, 2);
    real_type t19  = X__[iX_yy18];
    real_type t22  = sin(t4 + 17);
    real_type t25  = pow(V__[57] - 0.12e1 * t19 - 0.1e0 * t22, 2);
    real_type t27  = X__[iX_yy19];
    real_type t30  = sin(t4 + 18);
    real_type t33  = pow(V__[58] - 0.12e1 * t27 - 0.1e0 * t30, 2);
    real_type t35  = X__[iX_yy20];
    real_type t38  = sin(t4 + 19);
    real_type t41  = pow(V__[59] - 0.12e1 * t35 - 0.1e0 * t38, 2);
    real_type t43  = X__[iX_yy11];
    real_type t46  = sin(t4 + 10);
    real_type t49  = pow(V__[50] - 0.12e1 * t43 - 0.1e0 * t46, 2);
    real_type t51  = X__[iX_yy12];
    real_type t54  = sin(t4 + 11);
    real_type t57  = pow(V__[51] - 0.12e1 * t51 - 0.1e0 * t54, 2);
    real_type t59  = X__[iX_yy13];
    real_type t62  = sin(t4 + 12);
    real_type t65  = pow(V__[52] - 0.12e1 * t59 - 0.1e0 * t62, 2);
    real_type t67  = X__[iX_yy9];
    real_type t70  = sin(t4 + 8);
    real_type t73  = pow(V__[48] - 0.12e1 * t67 - 0.1e0 * t70, 2);
    real_type t75  = X__[iX_yy10];
    real_type t78  = sin(t4 + 9);
    real_type t81  = pow(V__[49] - 0.12e1 * t75 - 0.1e0 * t78, 2);
    real_type t83  = X__[iX_yy8];
    real_type t86  = sin(t4 + 7);
    real_type t89  = pow(V__[47] - 0.12e1 * t83 - 0.1e0 * t86, 2);
    real_type t90  = ModelPars[iM_xy_bound];
    real_type t91  = X__[iX_xx19];
    real_type t93  = xx19Limitation_min(-t90 - t91);
    real_type t94  = t9 + t17 + t25 + t33 + t41 + t49 + t57 + t65 + t73 + t81 + t89 + t93;
    real_type t96  = xx19Limitation_max(t91 - t90);
    real_type t97  = X__[iX_xx20];
    real_type t99  = xx20Limitation_min(-t90 - t97);
    real_type t101 = xx20Limitation_max(t97 - t90);
    real_type t102 = X__[iX_xx12];
    real_type t104 = xx12Limitation_min(-t90 - t102);
    real_type t105 = X__[iX_xx13];
    real_type t107 = xx13Limitation_min(-t90 - t105);
    real_type t109 = xx13Limitation_max(t105 - t90);
    real_type t110 = X__[iX_xx14];
    real_type t112 = xx14Limitation_min(-t90 - t110);
    real_type t113 = X__[iX_xx10];
    real_type t115 = xx10Limitation_max(t113 - t90);
    real_type t116 = X__[iX_xx11];
    real_type t118 = xx11Limitation_min(-t90 - t116);
    real_type t120 = xx11Limitation_max(t116 - t90);
    real_type t122 = xx12Limitation_max(t102 - t90);
    real_type t123 = X__[iX_xx8];
    real_type t125 = xx8Limitation_min(-t90 - t123);
    real_type t127 = xx8Limitation_max(t123 - t90);
    real_type t128 = t96 + t99 + t101 + t104 + t107 + t109 + t112 + t115 + t118 + t120 + t122 + t125 + t127;
    real_type t130 = X__[iX_xx9];
    real_type t132 = xx9Limitation_min(-t90 - t130);
    real_type t134 = xx9Limitation_max(t130 - t90);
    real_type t136 = xx10Limitation_min(-t90 - t113);
    real_type t137 = X__[iX_yy5];
    real_type t139 = yy5Limitation_max(t137 - t90);
    real_type t140 = X__[iX_yy6];
    real_type t142 = yy6Limitation_min(-t90 - t140);
    real_type t144 = yy6Limitation_max(t140 - t90);
    real_type t145 = X__[iX_yy7];
    real_type t147 = yy7Limitation_min(-t90 - t145);
    real_type t149 = yy7Limitation_max(t145 - t90);
    real_type t150 = X__[iX_xx6];
    real_type t152 = xx6Limitation_min(-t90 - t150);
    real_type t154 = xx6Limitation_max(t150 - t90);
    real_type t155 = X__[iX_xx7];
    real_type t157 = xx7Limitation_min(-t90 - t155);
    real_type t159 = xx7Limitation_max(t155 - t90);
    real_type t160 = t132 + t134 + t136 + t139 + t142 + t144 + t147 + t149 + t152 + t154 + t157 + t159;
    real_type t161 = X__[iX_yy3];
    real_type t163 = yy3Limitation_max(t161 - t90);
    real_type t164 = X__[iX_yy4];
    real_type t166 = yy4Limitation_min(-t90 - t164);
    real_type t168 = yy4Limitation_max(t164 - t90);
    real_type t170 = yy5Limitation_min(-t90 - t137);
    real_type t171 = X__[iX_yy1];
    real_type t173 = yy1Limitation_min(-t90 - t171);
    real_type t175 = yy1Limitation_max(t171 - t90);
    real_type t176 = X__[iX_yy2];
    real_type t178 = yy2Limitation_min(-t90 - t176);
    real_type t180 = yy2Limitation_max(t176 - t90);
    real_type t182 = yy3Limitation_min(-t90 - t161);
    real_type t183 = X__[iX_xx17];
    real_type t185 = xx17Limitation_min(-t90 - t183);
    real_type t187 = xx17Limitation_max(t183 - t90);
    real_type t188 = X__[iX_xx18];
    real_type t190 = xx18Limitation_min(-t90 - t188);
    real_type t192 = xx18Limitation_max(t188 - t90);
    real_type t193 = t163 + t166 + t168 + t170 + t173 + t175 + t178 + t180 + t182 + t185 + t187 + t190 + t192;
    real_type t197 = xx14Limitation_max(t110 - t90);
    real_type t198 = X__[iX_xx15];
    real_type t200 = xx15Limitation_min(-t90 - t198);
    real_type t202 = xx15Limitation_max(t198 - t90);
    real_type t203 = X__[iX_xx16];
    real_type t205 = xx16Limitation_min(-t90 - t203);
    real_type t207 = xx16Limitation_max(t203 - t90);
    real_type t209 = X__[iX_xx4];
    real_type t210 = sin(t209);
    real_type t212 = P__[iP_u4];
    real_type t214 = pow(V__[63] - 0.2e0 * t210 - t212, 2);
    real_type t217 = sin(X__[iX_x4]);
    real_type t219 = pow(V__[23] - t217 - t212, 2);
    real_type t222 = sin(X__[iX_x2]);
    real_type t223 = P__[iP_u2];
    real_type t225 = pow(V__[21] - t222 - t223, 2);
    real_type t227 = X__[iX_xx3];
    real_type t228 = sin(t227);
    real_type t230 = P__[iP_u3];
    real_type t232 = pow(V__[62] - 0.2e0 * t228 - t230, 2);
    real_type t235 = sin(X__[iX_x3]);
    real_type t237 = pow(V__[22] - t235 - t230, 2);
    real_type t240 = sin(X__[iX_x1]);
    real_type t241 = P__[iP_u1];
    real_type t243 = pow(V__[20] - t240 - t241, 2);
    real_type t245 = X__[iX_xx2];
    real_type t246 = sin(t245);
    real_type t249 = pow(V__[61] - 0.2e0 * t246 - t223, 2);
    real_type t250 = t197 + t200 + t202 + t205 + t207 + t214 + t219 + t225 + t232 + t237 + t243 + t249;
    real_type t252 = xx4Limitation_min(-t90 - t209);
    real_type t254 = xx4Limitation_max(t209 - t90);
    real_type t255 = X__[iX_xx5];
    real_type t257 = xx5Limitation_min(-t90 - t255);
    real_type t259 = xx5Limitation_max(t255 - t90);
    real_type t260 = X__[iX_xx1];
    real_type t262 = xx1Limitation_max(t260 - t90);
    real_type t264 = xx2Limitation_min(-t90 - t245);
    real_type t266 = xx2Limitation_max(t245 - t90);
    real_type t268 = xx3Limitation_min(-t90 - t227);
    real_type t270 = xx3Limitation_max(t227 - t90);
    real_type t272 = u2Limitation_max(t223 - 10);
    real_type t274 = u3Limitation_min(-10 - t230);
    real_type t276 = u3Limitation_max(t230 - 10);
    real_type t278 = xx1Limitation_min(-t90 - t260);
    real_type t279 = t252 + t254 + t257 + t259 + t262 + t264 + t266 + t268 + t270 + t272 + t274 + t276 + t278;
    real_type t283 = sin(X__[iX_x7]);
    real_type t284 = P__[iP_u7];
    real_type t286 = pow(V__[26] - t283 - t284, 2);
    real_type t288 = sin(t123);
    real_type t290 = P__[iP_u8];
    real_type t292 = pow(V__[67] - 0.2e0 * t288 - t290, 2);
    real_type t295 = sin(X__[iX_x8]);
    real_type t297 = pow(V__[27] - t295 - t290, 2);
    real_type t300 = sin(X__[iX_x6]);
    real_type t301 = P__[iP_u6];
    real_type t303 = pow(V__[25] - t300 - t301, 2);
    real_type t305 = sin(t155);
    real_type t308 = pow(V__[66] - 0.2e0 * t305 - t284, 2);
    real_type t310 = sin(t255);
    real_type t312 = P__[iP_u5];
    real_type t314 = pow(V__[64] - 0.2e0 * t310 - t312, 2);
    real_type t317 = sin(X__[iX_x5]);
    real_type t319 = pow(V__[24] - t317 - t312, 2);
    real_type t321 = sin(t150);
    real_type t324 = pow(V__[65] - 0.2e0 * t321 - t301, 2);
    real_type t327 = sin(X__[iX_x11]);
    real_type t328 = P__[iP_u11];
    real_type t330 = pow(V__[30] - t327 - t328, 2);
    real_type t332 = sin(t102);
    real_type t334 = P__[iP_u12];
    real_type t336 = pow(V__[71] - 0.2e0 * t332 - t334, 2);
    real_type t339 = sin(X__[iX_x12]);
    real_type t341 = pow(V__[31] - t339 - t334, 2);
    real_type t344 = sin(X__[iX_x10]);
    real_type t345 = P__[iP_u10];
    real_type t347 = pow(V__[29] - t344 - t345, 2);
    real_type t348 = t286 + t292 + t297 + t303 + t308 + t314 + t319 + t324 + t330 + t336 + t341 + t347;
    real_type t350 = sin(t116);
    real_type t353 = pow(V__[70] - 0.2e0 * t350 - t328, 2);
    real_type t355 = sin(t130);
    real_type t357 = P__[iP_u9];
    real_type t359 = pow(V__[68] - 0.2e0 * t355 - t357, 2);
    real_type t362 = sin(X__[iX_x9]);
    real_type t364 = pow(V__[28] - t362 - t357, 2);
    real_type t366 = sin(t113);
    real_type t369 = pow(V__[69] - 0.2e0 * t366 - t345, 2);
    real_type t371 = u9Limitation_max(t357 - 10);
    real_type t373 = u10Limitation_min(-10 - t345);
    real_type t375 = u10Limitation_max(t345 - 10);
    real_type t377 = u11Limitation_min(-10 - t328);
    real_type t379 = u11Limitation_max(t328 - 10);
    real_type t381 = u12Limitation_min(-10 - t334);
    real_type t383 = u7Limitation_min(-10 - t284);
    real_type t385 = u7Limitation_max(t284 - 10);
    real_type t387 = u8Limitation_min(-10 - t290);
    real_type t388 = t353 + t359 + t364 + t369 + t371 + t373 + t375 + t377 + t379 + t381 + t383 + t385 + t387;
    real_type t393 = u8Limitation_max(t290 - 10);
    real_type t395 = u9Limitation_min(-10 - t357);
    real_type t397 = u4Limitation_min(-10 - t212);
    real_type t399 = u4Limitation_max(t212 - 10);
    real_type t401 = u5Limitation_min(-10 - t312);
    real_type t403 = u5Limitation_max(t312 - 10);
    real_type t405 = u6Limitation_min(-10 - t301);
    real_type t407 = u6Limitation_max(t301 - 10);
    real_type t408 = X__[iX_yy14];
    real_type t410 = yy14Limitation_max(t408 - t90);
    real_type t411 = X__[iX_yy15];
    real_type t413 = yy15Limitation_min(-t90 - t411);
    real_type t415 = yy15Limitation_max(t411 - t90);
    real_type t417 = yy16Limitation_min(-t90 - t2);
    real_type t418 = t393 + t395 + t397 + t399 + t401 + t403 + t405 + t407 + t410 + t413 + t415 + t417;
    real_type t422 = pow(V__[19] - X__[iX_y20], 2);
    real_type t424 = u1Limitation_min(-10 - t241);
    real_type t426 = u1Limitation_max(t241 - 10);
    real_type t428 = u2Limitation_min(-10 - t223);
    real_type t432 = pow(V__[15] - X__[iX_y16], 2);
    real_type t436 = pow(V__[16] - X__[iX_y17], 2);
    real_type t440 = pow(V__[17] - X__[iX_y18], 2);
    real_type t444 = pow(V__[18] - X__[iX_y19], 2);
    real_type t448 = pow(V__[11] - X__[iX_y12], 2);
    real_type t452 = pow(V__[12] - X__[iX_y13], 2);
    real_type t456 = pow(V__[13] - X__[iX_y14], 2);
    real_type t460 = pow(V__[14] - X__[iX_y15], 2);
    real_type t463 = sin(X__[iX_x19]);
    real_type t464 = P__[iP_u19];
    real_type t466 = pow(V__[38] - t463 - t464, 2);
    real_type t467 = t422 + t424 + t426 + t428 + t432 + t436 + t440 + t444 + t448 + t452 + t456 + t460 + t466;
    real_type t470 = sin(t97);
    real_type t472 = P__[iP_u20];
    real_type t474 = pow(V__[79] - 0.2e0 * t470 - t472, 2);
    real_type t476 = sin(t188);
    real_type t478 = P__[iP_u18];
    real_type t480 = pow(V__[77] - 0.2e0 * t476 - t478, 2);
    real_type t483 = sin(X__[iX_x18]);
    real_type t485 = pow(V__[37] - t483 - t478, 2);
    real_type t487 = sin(t91);
    real_type t490 = pow(V__[78] - 0.2e0 * t487 - t464, 2);
    real_type t492 = sin(t183);
    real_type t494 = P__[iP_u17];
    real_type t496 = pow(V__[76] - 0.2e0 * t492 - t494, 2);
    real_type t499 = sin(X__[iX_x17]);
    real_type t501 = pow(V__[36] - t499 - t494, 2);
    real_type t503 = u17Limitation_max(t494 - 10);
    real_type t505 = u18Limitation_min(-10 - t478);
    real_type t507 = u18Limitation_max(t478 - 10);
    real_type t509 = u19Limitation_min(-10 - t464);
    real_type t511 = u19Limitation_max(t464 - 10);
    real_type t512 = P__[iP_u15];
    real_type t514 = u15Limitation_min(-10 - t512);
    real_type t515 = t474 + t480 + t485 + t490 + t496 + t501 + t503 + t505 + t507 + t509 + t511 + t514;
    real_type t517 = u15Limitation_max(t512 - 10);
    real_type t518 = P__[iP_u16];
    real_type t520 = u16Limitation_min(-10 - t518);
    real_type t522 = u16Limitation_max(t518 - 10);
    real_type t524 = u17Limitation_min(-10 - t494);
    real_type t526 = yy10Limitation_min(-t90 - t75);
    real_type t528 = yy10Limitation_max(t75 - t90);
    real_type t530 = yy11Limitation_min(-t90 - t43);
    real_type t532 = yy11Limitation_max(t43 - t90);
    real_type t534 = yy8Limitation_min(-t90 - t83);
    real_type t536 = yy8Limitation_max(t83 - t90);
    real_type t538 = yy9Limitation_min(-t90 - t67);
    real_type t540 = yy9Limitation_max(t67 - t90);
    real_type t544 = sin(t4 + 5);
    real_type t547 = pow(V__[45] - 0.12e1 * t140 - 0.1e0 * t544, 2);
    real_type t548 = t517 + t520 + t522 + t524 + t526 + t528 + t530 + t532 + t534 + t536 + t538 + t540 + t547;
    real_type t554 = sin(t4 + 6);
    real_type t557 = pow(V__[46] - 0.12e1 * t145 - 0.1e0 * t554, 2);
    real_type t559 = sin(t260);
    real_type t562 = pow(V__[60] - 0.2e0 * t559 - t241, 2);
    real_type t566 = sin(t4 + 3);
    real_type t569 = pow(V__[43] - 0.12e1 * t164 - 0.1e0 * t566, 2);
    real_type t573 = sin(t4 + 4);
    real_type t576 = pow(V__[44] - 0.12e1 * t137 - 0.1e0 * t573, 2);
    real_type t579 = sin(X__[iX_x15]);
    real_type t581 = pow(V__[34] - t579 - t512, 2);
    real_type t583 = sin(t203);
    real_type t586 = pow(V__[75] - 0.2e0 * t583 - t518, 2);
    real_type t589 = sin(X__[iX_x16]);
    real_type t591 = pow(V__[35] - t589 - t518, 2);
    real_type t594 = sin(X__[iX_x14]);
    real_type t595 = P__[iP_u14];
    real_type t597 = pow(V__[33] - t594 - t595, 2);
    real_type t599 = sin(t198);
    real_type t602 = pow(V__[74] - 0.2e0 * t599 - t512, 2);
    real_type t605 = sin(t4);
    real_type t608 = pow(V__[40] - 0.12e1 * t171 - 0.1e0 * t605, 2);
    real_type t612 = sin(t4 + 1);
    real_type t615 = pow(V__[41] - 0.12e1 * t176 - 0.1e0 * t612, 2);
    real_type t619 = sin(t4 + 2);
    real_type t622 = pow(V__[42] - 0.12e1 * t161 - 0.1e0 * t619, 2);
    real_type t623 = t557 + t562 + t569 + t576 + t581 + t586 + t591 + t597 + t602 + t608 + t615 + t622;
    real_type t625 = u20Limitation_min(-10 - t472);
    real_type t627 = u20Limitation_max(t472 - 10);
    real_type t629 = sin(t105);
    real_type t631 = P__[iP_u13];
    real_type t633 = pow(V__[72] - 0.2e0 * t629 - t631, 2);
    real_type t636 = sin(X__[iX_x13]);
    real_type t638 = pow(V__[32] - t636 - t631, 2);
    real_type t640 = sin(t110);
    real_type t643 = pow(V__[73] - 0.2e0 * t640 - t595, 2);
    real_type t647 = pow(V__[7] - X__[iX_y8], 2);
    real_type t651 = pow(V__[8] - X__[iX_y9], 2);
    real_type t655 = pow(V__[9] - X__[iX_y10], 2);
    real_type t659 = pow(V__[10] - X__[iX_y11], 2);
    real_type t663 = pow(V__[3] - X__[iX_y4], 2);
    real_type t667 = pow(V__[4] - X__[iX_y5], 2);
    real_type t671 = pow(V__[5] - X__[iX_y6], 2);
    real_type t675 = pow(V__[6] - X__[iX_y7], 2);
    real_type t676 = t625 + t627 + t633 + t638 + t643 + t647 + t651 + t655 + t659 + t663 + t667 + t671 + t675;
    real_type t680 = sin(X__[iX_x20]);
    real_type t682 = pow(V__[39] - t680 - t472, 2);
    real_type t686 = pow(V__[0] - X__[iX_y1], 2);
    real_type t690 = pow(V__[1] - X__[iX_y2], 2);
    real_type t694 = pow(V__[2] - X__[iX_y3], 2);
    real_type t696 = u12Limitation_max(t334 - 10);
    real_type t698 = u13Limitation_min(-10 - t631);
    real_type t700 = u13Limitation_max(t631 - 10);
    real_type t702 = u14Limitation_min(-10 - t595);
    real_type t704 = u14Limitation_max(t595 - 10);
    real_type t706 = yy18Limitation_max(t19 - t90);
    real_type t708 = yy19Limitation_min(-t90 - t27);
    real_type t710 = yy19Limitation_max(t27 - t90);
    real_type t711 = t682 + t686 + t690 + t694 + t696 + t698 + t700 + t702 + t704 + t706 + t708 + t710;
    real_type t713 = yy20Limitation_min(-t90 - t35);
    real_type t715 = yy20Limitation_max(t35 - t90);
    real_type t717 = yy12Limitation_min(-t90 - t51);
    real_type t719 = yy12Limitation_max(t51 - t90);
    real_type t721 = yy13Limitation_min(-t90 - t59);
    real_type t723 = yy13Limitation_max(t59 - t90);
    real_type t725 = yy14Limitation_min(-t90 - t408);
    real_type t729 = sin(t4 + 13);
    real_type t732 = pow(V__[53] - 0.12e1 * t408 - 0.1e0 * t729, 2);
    real_type t736 = sin(t4 + 14);
    real_type t739 = pow(V__[54] - 0.12e1 * t411 - 0.1e0 * t736, 2);
    real_type t741 = yy16Limitation_max(t2 - t90);
    real_type t743 = yy17Limitation_min(-t90 - t11);
    real_type t745 = yy17Limitation_max(t11 - t90);
    real_type t747 = yy18Limitation_min(-t90 - t19);
    real_type t748 = t713 + t715 + t717 + t719 + t721 + t723 + t725 + t732 + t739 + t741 + t743 + t745 + t747;
    real_type result__ = t94 + t128 + t160 + t193 + t250 + t279 + t348 + t388 + t418 + t467 + t515 + t548 + t623 + t676 + t711 + t748;
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
