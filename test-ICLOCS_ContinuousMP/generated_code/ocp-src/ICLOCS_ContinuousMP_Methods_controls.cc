/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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
    real_type t2   = XM__[0];
    real_type t3   = sin(t2);
    real_type t4   = P__[iP_u1];
    real_type t8   = XM__[40];
    real_type t9   = sin(t8);
    real_type t14  = XM__[1];
    real_type t15  = sin(t14);
    real_type t16  = P__[iP_u2];
    real_type t20  = XM__[41];
    real_type t21  = sin(t20);
    real_type t26  = XM__[2];
    real_type t27  = sin(t26);
    real_type t28  = P__[iP_u3];
    real_type t32  = XM__[42];
    real_type t33  = sin(t32);
    real_type t38  = XM__[3];
    real_type t39  = sin(t38);
    real_type t40  = P__[iP_u4];
    real_type t44  = XM__[32];
    real_type t47  = XM__[33];
    real_type t50  = XM__[34];
    real_type t53  = XM__[35];
    real_type t56  = XM__[36];
    real_type t59  = XM__[37];
    real_type t62  = XM__[38];
    real_type t65  = XM__[39];
    real_type t67  = (t3 + t4) * LM__[20] + (0.2e0 * t9 + t4) * LM__[60] + (t15 + t16) * LM__[21] + (0.2e0 * t21 + t16) * LM__[61] + (t27 + t28) * LM__[22] + (0.2e0 * t33 + t28) * LM__[62] + (t39 + t40) * LM__[23] + t44 * LM__[12] + t47 * LM__[13] + t50 * LM__[14] + t53 * LM__[15] + t56 * LM__[16] + t59 * LM__[17] + t62 * LM__[18] + t65 * LM__[19];
    real_type t69  = XM__[15];
    real_type t70  = sin(t69);
    real_type t71  = P__[iP_u16];
    real_type t75  = XM__[55];
    real_type t76  = sin(t75);
    real_type t81  = XM__[16];
    real_type t82  = sin(t81);
    real_type t83  = P__[iP_u17];
    real_type t87  = XM__[56];
    real_type t88  = sin(t87);
    real_type t93  = XM__[17];
    real_type t94  = sin(t93);
    real_type t95  = P__[iP_u18];
    real_type t99  = XM__[57];
    real_type t100 = sin(t99);
    real_type t105 = XM__[18];
    real_type t106 = sin(t105);
    real_type t107 = P__[iP_u19];
    real_type t111 = XM__[58];
    real_type t112 = sin(t111);
    real_type t117 = XM__[19];
    real_type t118 = sin(t117);
    real_type t119 = P__[iP_u20];
    real_type t123 = XM__[59];
    real_type t124 = sin(t123);
    real_type t129 = XM__[60];
    real_type t131 = QM__[0];
    real_type t132 = sin(t131);
    real_type t137 = XM__[61];
    real_type t140 = sin(t131 + 1);
    real_type t145 = XM__[62];
    real_type t148 = sin(t131 + 2);
    real_type t153 = XM__[63];
    real_type t156 = sin(t131 + 3);
    real_type t161 = XM__[64];
    real_type t164 = sin(t131 + 4);
    real_type t168 = (t70 + t71) * LM__[35] + (0.2e0 * t76 + t71) * LM__[75] + (t82 + t83) * LM__[36] + (0.2e0 * t88 + t83) * LM__[76] + (t94 + t95) * LM__[37] + (0.2e0 * t100 + t95) * LM__[77] + (t106 + t107) * LM__[38] + (0.2e0 * t112 + t107) * LM__[78] + (t118 + t119) * LM__[39] + (0.2e0 * t124 + t119) * LM__[79] + (0.12e1 * t129 + 0.1e0 * t132) * LM__[40] + (0.12e1 * t137 + 0.1e0 * t140) * LM__[41] + (0.12e1 * t145 + 0.1e0 * t148) * LM__[42] + (0.12e1 * t153 + 0.1e0 * t156) * LM__[43] + (0.12e1 * t161 + 0.1e0 * t164) * LM__[44];
    real_type t171 = XM__[65];
    real_type t174 = sin(t131 + 5);
    real_type t179 = XM__[66];
    real_type t182 = sin(t131 + 6);
    real_type t187 = XM__[67];
    real_type t190 = sin(t131 + 7);
    real_type t195 = XM__[68];
    real_type t198 = sin(t131 + 8);
    real_type t203 = XM__[69];
    real_type t206 = sin(t131 + 9);
    real_type t211 = XM__[70];
    real_type t214 = sin(t131 + 10);
    real_type t219 = XM__[71];
    real_type t222 = sin(t131 + 11);
    real_type t227 = XM__[72];
    real_type t230 = sin(t131 + 12);
    real_type t235 = XM__[20];
    real_type t238 = XM__[21];
    real_type t241 = XM__[22];
    real_type t244 = XM__[23];
    real_type t247 = XM__[24];
    real_type t250 = XM__[25];
    real_type t253 = XM__[26];
    real_type t255 = (0.12e1 * t171 + 0.1e0 * t174) * LM__[45] + (0.12e1 * t179 + 0.1e0 * t182) * LM__[46] + (0.12e1 * t187 + 0.1e0 * t190) * LM__[47] + (0.12e1 * t195 + 0.1e0 * t198) * LM__[48] + (0.12e1 * t203 + 0.1e0 * t206) * LM__[49] + (0.12e1 * t211 + 0.1e0 * t214) * LM__[50] + (0.12e1 * t219 + 0.1e0 * t222) * LM__[51] + (0.12e1 * t227 + 0.1e0 * t230) * LM__[52] + t235 * LM__[0] + t238 * LM__[1] + t241 * LM__[2] + t244 * LM__[3] + t247 * LM__[4] + t250 * LM__[5] + t253 * LM__[6];
    real_type t257 = XM__[27];
    real_type t260 = XM__[28];
    real_type t263 = XM__[29];
    real_type t266 = XM__[30];
    real_type t269 = XM__[31];
    real_type t272 = XM__[73];
    real_type t275 = sin(t131 + 13);
    real_type t280 = XM__[74];
    real_type t283 = sin(t131 + 14);
    real_type t288 = XM__[75];
    real_type t291 = sin(t131 + 15);
    real_type t296 = XM__[76];
    real_type t299 = sin(t131 + 16);
    real_type t304 = XM__[77];
    real_type t307 = sin(t131 + 17);
    real_type t312 = XM__[78];
    real_type t315 = sin(t131 + 18);
    real_type t320 = XM__[79];
    real_type t323 = sin(t131 + 19);
    real_type t328 = XM__[49];
    real_type t329 = sin(t328);
    real_type t331 = P__[iP_u10];
    real_type t335 = XM__[10];
    real_type t336 = sin(t335);
    real_type t337 = P__[iP_u11];
    real_type t341 = XM__[50];
    real_type t342 = sin(t341);
    real_type t346 = t257 * LM__[7] + t260 * LM__[8] + t263 * LM__[9] + t266 * LM__[10] + t269 * LM__[11] + (0.12e1 * t272 + 0.1e0 * t275) * LM__[53] + (0.12e1 * t280 + 0.1e0 * t283) * LM__[54] + (0.12e1 * t288 + 0.1e0 * t291) * LM__[55] + (0.12e1 * t296 + 0.1e0 * t299) * LM__[56] + (0.12e1 * t304 + 0.1e0 * t307) * LM__[57] + (0.12e1 * t312 + 0.1e0 * t315) * LM__[58] + (0.12e1 * t320 + 0.1e0 * t323) * LM__[59] + (0.2e0 * t329 + t331) * LM__[69] + (t336 + t337) * LM__[30] + (0.2e0 * t342 + t337) * LM__[70];
    real_type t350 = XM__[11];
    real_type t351 = sin(t350);
    real_type t352 = P__[iP_u12];
    real_type t356 = XM__[51];
    real_type t357 = sin(t356);
    real_type t362 = XM__[12];
    real_type t363 = sin(t362);
    real_type t364 = P__[iP_u13];
    real_type t368 = XM__[52];
    real_type t369 = sin(t368);
    real_type t374 = XM__[13];
    real_type t375 = sin(t374);
    real_type t376 = P__[iP_u14];
    real_type t380 = XM__[53];
    real_type t381 = sin(t380);
    real_type t386 = XM__[14];
    real_type t387 = sin(t386);
    real_type t388 = P__[iP_u15];
    real_type t392 = XM__[54];
    real_type t393 = sin(t392);
    real_type t397 = t253 * t253;
    real_type t399 = t257 * t257;
    real_type t401 = t260 * t260;
    real_type t403 = t263 * t263;
    real_type t405 = t266 * t266;
    real_type t407 = t269 * t269;
    real_type t409 = t44 * t44;
    real_type t411 = (t351 + t352) * LM__[31] + (0.2e0 * t357 + t352) * LM__[71] + (t363 + t364) * LM__[32] + (0.2e0 * t369 + t364) * LM__[72] + (t375 + t376) * LM__[33] + (0.2e0 * t381 + t376) * LM__[73] + (t387 + t388) * LM__[34] + (0.2e0 * t393 + t388) * LM__[74] + 14 * t397 + 13 * t399 + 12 * t401 + 11 * t403 + 10 * t405 + 9 * t407 + 8 * t409;
    real_type t412 = t47 * t47;
    real_type t414 = ModelPars[iM_xy_bound];
    real_type t416 = yy20Limitation_max(t320 - t414);
    real_type t417 = t105 * t105;
    real_type t419 = t117 * t117;
    real_type t420 = t235 * t235;
    real_type t422 = t238 * t238;
    real_type t424 = t241 * t241;
    real_type t426 = t244 * t244;
    real_type t428 = t247 * t247;
    real_type t430 = t250 * t250;
    real_type t433 = u16Limitation_max(t71 - 10);
    real_type t435 = u17Limitation_min(-10 - t83);
    real_type t437 = u17Limitation_max(t83 - 10);
    real_type t439 = u18Limitation_min(-10 - t95);
    real_type t441 = u18Limitation_max(t95 - 10);
    real_type t442 = 7 * t412 + t416 + 2 * t417 + t419 + 20 * t420 + 19 * t422 + 18 * t424 + 17 * t426 + 16 * t428 + 15 * t430 + t433 + t435 + t437 + t439 + t441;
    real_type t445 = u19Limitation_min(-10 - t107);
    real_type t447 = u19Limitation_max(t107 - 10);
    real_type t449 = u13Limitation_max(t364 - 10);
    real_type t451 = u14Limitation_min(-10 - t376);
    real_type t453 = u14Limitation_max(t376 - 10);
    real_type t455 = u15Limitation_min(-10 - t388);
    real_type t457 = u15Limitation_max(t388 - 10);
    real_type t459 = u16Limitation_min(-10 - t71);
    real_type t461 = u10Limitation_min(-10 - t331);
    real_type t463 = u10Limitation_max(t331 - 10);
    real_type t465 = u11Limitation_min(-10 - t337);
    real_type t467 = u11Limitation_max(t337 - 10);
    real_type t469 = u12Limitation_min(-10 - t352);
    real_type t471 = u12Limitation_max(t352 - 10);
    real_type t473 = u13Limitation_min(-10 - t364);
    real_type t474 = t445 + t447 + t449 + t451 + t453 + t455 + t457 + t459 + t461 + t463 + t465 + t467 + t469 + t471 + t473;
    real_type t476 = xx13Limitation_min(-t414 - t368);
    real_type t478 = xx13Limitation_max(t368 - t414);
    real_type t480 = xx14Limitation_min(-t414 - t380);
    real_type t482 = xx14Limitation_max(t380 - t414);
    real_type t484 = yy7Limitation_min(-t414 - t179);
    real_type t486 = yy7Limitation_max(t179 - t414);
    real_type t488 = yy8Limitation_min(-t414 - t187);
    real_type t490 = yy8Limitation_max(t187 - t414);
    real_type t492 = yy4Limitation_max(t153 - t414);
    real_type t494 = yy5Limitation_min(-t414 - t161);
    real_type t496 = yy5Limitation_max(t161 - t414);
    real_type t498 = yy6Limitation_min(-t414 - t171);
    real_type t500 = yy6Limitation_max(t171 - t414);
    real_type t501 = t2 * t2;
    real_type t503 = t14 * t14;
    real_type t505 = t476 + t478 + t480 + t482 + t484 + t486 + t488 + t490 + t492 + t494 + t496 + t498 + t500 + 20 * t501 + 19 * t503;
    real_type t509 = XM__[45];
    real_type t511 = xx6Limitation_min(-t414 - t509);
    real_type t513 = xx6Limitation_max(t509 - t414);
    real_type t514 = XM__[46];
    real_type t516 = xx7Limitation_min(-t414 - t514);
    real_type t518 = xx7Limitation_max(t514 - t414);
    real_type t519 = XM__[43];
    real_type t521 = xx4Limitation_min(-t414 - t519);
    real_type t523 = xx4Limitation_max(t519 - t414);
    real_type t524 = XM__[44];
    real_type t526 = xx5Limitation_min(-t414 - t524);
    real_type t528 = xx5Limitation_max(t524 - t414);
    real_type t530 = xx2Limitation_min(-t414 - t20);
    real_type t532 = xx2Limitation_max(t20 - t414);
    real_type t534 = xx3Limitation_min(-t414 - t32);
    real_type t536 = xx3Limitation_max(t32 - t414);
    real_type t538 = u20Limitation_min(-10 - t119);
    real_type t540 = u20Limitation_max(t119 - 10);
    real_type t542 = xx1Limitation_min(-t414 - t8);
    real_type t543 = t511 + t513 + t516 + t518 + t521 + t523 + t526 + t528 + t530 + t532 + t534 + t536 + t538 + t540 + t542;
    real_type t545 = xx1Limitation_max(t8 - t414);
    real_type t547 = xx10Limitation_max(t328 - t414);
    real_type t549 = xx11Limitation_min(-t414 - t341);
    real_type t551 = xx11Limitation_max(t341 - t414);
    real_type t553 = xx12Limitation_min(-t414 - t356);
    real_type t555 = xx12Limitation_max(t356 - t414);
    real_type t556 = P__[iP_u7];
    real_type t558 = u7Limitation_max(t556 - 10);
    real_type t559 = P__[iP_u8];
    real_type t561 = u8Limitation_min(-10 - t559);
    real_type t563 = u8Limitation_max(t559 - 10);
    real_type t564 = P__[iP_u9];
    real_type t566 = u9Limitation_min(-10 - t564);
    real_type t568 = u9Limitation_max(t564 - 10);
    real_type t569 = t50 * t50;
    real_type t571 = t53 * t53;
    real_type t573 = t56 * t56;
    real_type t575 = t59 * t59;
    real_type t577 = t545 + t547 + t549 + t551 + t553 + t555 + t558 + t561 + t563 + t566 + t568 + 6 * t569 + 5 * t571 + 4 * t573 + 3 * t575;
    real_type t579 = t62 * t62;
    real_type t581 = t65 * t65;
    real_type t582 = XM__[47];
    real_type t584 = xx8Limitation_min(-t414 - t582);
    real_type t586 = xx8Limitation_max(t582 - t414);
    real_type t587 = XM__[48];
    real_type t589 = xx9Limitation_max(t587 - t414);
    real_type t591 = xx9Limitation_min(-t414 - t587);
    real_type t593 = xx10Limitation_min(-t414 - t328);
    real_type t595 = yy9Limitation_min(-t414 - t195);
    real_type t597 = yy9Limitation_max(t195 - t414);
    real_type t599 = yy10Limitation_min(-t414 - t203);
    real_type t601 = yy10Limitation_max(t203 - t414);
    real_type t603 = yy11Limitation_min(-t414 - t211);
    real_type t605 = yy2Limitation_min(-t414 - t137);
    real_type t607 = yy2Limitation_max(t137 - t414);
    real_type t609 = yy3Limitation_min(-t414 - t145);
    real_type t610 = 2 * t579 + t581 + t584 + t586 + t589 + t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609;
    real_type t612 = yy3Limitation_max(t145 - t414);
    real_type t614 = yy4Limitation_min(-t414 - t153);
    real_type t616 = xx20Limitation_min(-t414 - t123);
    real_type t618 = xx20Limitation_max(t123 - t414);
    real_type t620 = yy1Limitation_min(-t414 - t129);
    real_type t622 = yy1Limitation_max(t129 - t414);
    real_type t624 = sin(t519);
    real_type t629 = XM__[4];
    real_type t630 = sin(t629);
    real_type t631 = P__[iP_u5];
    real_type t635 = sin(t524);
    real_type t640 = XM__[5];
    real_type t641 = sin(t640);
    real_type t642 = P__[iP_u6];
    real_type t646 = sin(t509);
    real_type t651 = XM__[6];
    real_type t652 = sin(t651);
    real_type t656 = sin(t514);
    real_type t661 = XM__[7];
    real_type t662 = sin(t661);
    real_type t666 = sin(t582);
    real_type t670 = t612 + t614 + t616 + t618 + t620 + t622 + (0.2e0 * t624 + t40) * LM__[63] + (t630 + t631) * LM__[24] + (0.2e0 * t635 + t631) * LM__[64] + (t641 + t642) * LM__[25] + (0.2e0 * t646 + t642) * LM__[65] + (t652 + t556) * LM__[26] + (0.2e0 * t656 + t556) * LM__[66] + (t662 + t559) * LM__[27] + (0.2e0 * t666 + t559) * LM__[67];
    real_type t674 = XM__[8];
    real_type t675 = sin(t674);
    real_type t679 = sin(t587);
    real_type t684 = XM__[9];
    real_type t685 = sin(t684);
    real_type t689 = u2Limitation_min(-10 - t16);
    real_type t691 = u2Limitation_max(t16 - 10);
    real_type t693 = u3Limitation_min(-10 - t28);
    real_type t695 = u3Limitation_max(t28 - 10);
    real_type t697 = u4Limitation_min(-10 - t40);
    real_type t699 = u4Limitation_max(t40 - 10);
    real_type t701 = yy11Limitation_max(t211 - t414);
    real_type t703 = yy12Limitation_min(-t414 - t219);
    real_type t705 = yy12Limitation_max(t219 - t414);
    real_type t707 = yy13Limitation_min(-t414 - t227);
    real_type t709 = yy13Limitation_max(t227 - t414);
    real_type t711 = u1Limitation_min(-10 - t4);
    real_type t712 = (t675 + t564) * LM__[28] + (0.2e0 * t679 + t564) * LM__[68] + (t685 + t331) * LM__[29] + t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = u1Limitation_max(t4 - 10);
    real_type t716 = yy18Limitation_min(-t414 - t304);
    real_type t718 = yy19Limitation_min(-t414 - t312);
    real_type t720 = yy19Limitation_max(t312 - t414);
    real_type t722 = yy20Limitation_min(-t414 - t320);
    real_type t724 = yy16Limitation_min(-t414 - t288);
    real_type t726 = yy16Limitation_max(t288 - t414);
    real_type t728 = yy17Limitation_min(-t414 - t296);
    real_type t730 = yy17Limitation_max(t296 - t414);
    real_type t732 = yy18Limitation_max(t304 - t414);
    real_type t734 = xx17Limitation_max(t87 - t414);
    real_type t736 = xx18Limitation_min(-t414 - t99);
    real_type t738 = xx18Limitation_max(t99 - t414);
    real_type t740 = xx19Limitation_min(-t414 - t111);
    real_type t742 = xx19Limitation_max(t111 - t414);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = xx15Limitation_min(-t414 - t392);
    real_type t748 = xx15Limitation_max(t392 - t414);
    real_type t750 = xx16Limitation_min(-t414 - t75);
    real_type t752 = xx16Limitation_max(t75 - t414);
    real_type t754 = xx17Limitation_min(-t414 - t87);
    real_type t756 = yy14Limitation_min(-t414 - t272);
    real_type t758 = yy14Limitation_max(t272 - t414);
    real_type t760 = yy15Limitation_min(-t414 - t280);
    real_type t762 = yy15Limitation_max(t280 - t414);
    real_type t763 = t386 * t386;
    real_type t765 = t69 * t69;
    real_type t767 = t81 * t81;
    real_type t769 = t93 * t93;
    real_type t771 = t674 * t674;
    real_type t773 = t684 * t684;
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + 6 * t763 + 5 * t765 + 4 * t767 + 3 * t769 + 12 * t771 + 11 * t773;
    real_type t776 = t335 * t335;
    real_type t778 = t350 * t350;
    real_type t780 = t362 * t362;
    real_type t782 = t374 * t374;
    real_type t784 = t26 * t26;
    real_type t786 = t38 * t38;
    real_type t788 = t629 * t629;
    real_type t790 = t640 * t640;
    real_type t792 = t651 * t651;
    real_type t794 = t661 * t661;
    real_type t797 = u5Limitation_min(-10 - t631);
    real_type t799 = u5Limitation_max(t631 - 10);
    real_type t801 = u6Limitation_min(-10 - t642);
    real_type t803 = u6Limitation_max(t642 - 10);
    real_type t805 = u7Limitation_min(-10 - t556);
    real_type t806 = 10 * t776 + 9 * t778 + 8 * t780 + 7 * t782 + 18 * t784 + 17 * t786 + 16 * t788 + 15 * t790 + 14 * t792 + 13 * t794 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t67 + t168 + t255 + t346 + t411 + t442 + t474 + t505 + t543 + t577 + t610 + t670 + t712 + t743 + t775 + t806;
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
    real_type t2   = X__[iX_xx2];
    real_type t3   = sin(t2);
    real_type t5   = P__[iP_u2];
    real_type t7   = pow(V__[61] - 0.2e0 * t3 - t5, 2);
    real_type t10  = sin(X__[iX_x3]);
    real_type t11  = P__[iP_u3];
    real_type t13  = pow(V__[22] - t10 - t11, 2);
    real_type t15  = X__[iX_xx3];
    real_type t16  = sin(t15);
    real_type t19  = pow(V__[62] - 0.2e0 * t16 - t11, 2);
    real_type t21  = X__[iX_yy19];
    real_type t23  = Q__[iQ_zeta];
    real_type t25  = sin(t23 + 18);
    real_type t28  = pow(V__[58] - 0.12e1 * t21 - 0.1e0 * t25, 2);
    real_type t30  = X__[iX_yy20];
    real_type t33  = sin(t23 + 19);
    real_type t36  = pow(V__[59] - 0.12e1 * t30 - 0.1e0 * t33, 2);
    real_type t39  = sin(X__[iX_x8]);
    real_type t40  = P__[iP_u8];
    real_type t42  = pow(V__[27] - t39 - t40, 2);
    real_type t44  = X__[iX_xx9];
    real_type t45  = sin(t44);
    real_type t47  = P__[iP_u9];
    real_type t49  = pow(V__[68] - 0.2e0 * t45 - t47, 2);
    real_type t52  = sin(X__[iX_x9]);
    real_type t54  = pow(V__[28] - t52 - t47, 2);
    real_type t58  = pow(V__[18] - X__[iX_y19], 2);
    real_type t62  = pow(V__[19] - X__[iX_y20], 2);
    real_type t64  = X__[iX_xx7];
    real_type t65  = sin(t64);
    real_type t67  = P__[iP_u7];
    real_type t69  = pow(V__[66] - 0.2e0 * t65 - t67, 2);
    real_type t72  = sin(X__[iX_x7]);
    real_type t74  = pow(V__[26] - t72 - t67, 2);
    real_type t75  = t7 + t13 + t19 + t28 + t36 + t42 + t49 + t54 + t58 + t62 + t69 + t74;
    real_type t77  = X__[iX_xx8];
    real_type t78  = sin(t77);
    real_type t81  = pow(V__[67] - 0.2e0 * t78 - t40, 2);
    real_type t84  = sin(X__[iX_x5]);
    real_type t85  = P__[iP_u5];
    real_type t87  = pow(V__[24] - t84 - t85, 2);
    real_type t89  = X__[iX_xx6];
    real_type t90  = sin(t89);
    real_type t92  = P__[iP_u6];
    real_type t94  = pow(V__[65] - 0.2e0 * t90 - t92, 2);
    real_type t97  = sin(X__[iX_x6]);
    real_type t99  = pow(V__[25] - t97 - t92, 2);
    real_type t101 = X__[iX_xx4];
    real_type t102 = sin(t101);
    real_type t104 = P__[iP_u4];
    real_type t106 = pow(V__[63] - 0.2e0 * t102 - t104, 2);
    real_type t109 = sin(X__[iX_x4]);
    real_type t111 = pow(V__[23] - t109 - t104, 2);
    real_type t113 = X__[iX_xx5];
    real_type t114 = sin(t113);
    real_type t117 = pow(V__[64] - 0.2e0 * t114 - t85, 2);
    real_type t120 = sin(X__[iX_x1]);
    real_type t121 = P__[iP_u1];
    real_type t123 = pow(V__[20] - t120 - t121, 2);
    real_type t125 = X__[iX_xx1];
    real_type t126 = sin(t125);
    real_type t129 = pow(V__[60] - 0.2e0 * t126 - t121, 2);
    real_type t132 = sin(X__[iX_x2]);
    real_type t134 = pow(V__[21] - t132 - t5, 2);
    real_type t136 = X__[iX_xx16];
    real_type t137 = sin(t136);
    real_type t139 = P__[iP_u16];
    real_type t141 = pow(V__[75] - 0.2e0 * t137 - t139, 2);
    real_type t144 = sin(X__[iX_x16]);
    real_type t146 = pow(V__[35] - t144 - t139, 2);
    real_type t148 = X__[iX_xx20];
    real_type t149 = sin(t148);
    real_type t151 = P__[iP_u20];
    real_type t153 = pow(V__[79] - 0.2e0 * t149 - t151, 2);
    real_type t154 = t81 + t87 + t94 + t99 + t106 + t111 + t117 + t123 + t129 + t134 + t141 + t146 + t153;
    real_type t158 = sin(X__[iX_x20]);
    real_type t160 = pow(V__[39] - t158 - t151, 2);
    real_type t164 = pow(V__[0] - X__[iX_y1], 2);
    real_type t166 = X__[iX_xx13];
    real_type t167 = sin(t166);
    real_type t169 = P__[iP_u13];
    real_type t171 = pow(V__[72] - 0.2e0 * t167 - t169, 2);
    real_type t174 = sin(X__[iX_x13]);
    real_type t176 = pow(V__[32] - t174 - t169, 2);
    real_type t178 = X__[iX_xx14];
    real_type t179 = sin(t178);
    real_type t181 = P__[iP_u14];
    real_type t183 = pow(V__[73] - 0.2e0 * t179 - t181, 2);
    real_type t187 = pow(V__[10] - X__[iX_y11], 2);
    real_type t191 = pow(V__[11] - X__[iX_y12], 2);
    real_type t195 = pow(V__[12] - X__[iX_y13], 2);
    real_type t199 = pow(V__[13] - X__[iX_y14], 2);
    real_type t203 = pow(V__[14] - X__[iX_y15], 2);
    real_type t207 = pow(V__[15] - X__[iX_y16], 2);
    real_type t211 = pow(V__[16] - X__[iX_y17], 2);
    real_type t212 = t160 + t164 + t171 + t176 + t183 + t187 + t191 + t195 + t199 + t203 + t207 + t211;
    real_type t216 = pow(V__[17] - X__[iX_y18], 2);
    real_type t220 = pow(V__[6] - X__[iX_y7], 2);
    real_type t224 = pow(V__[7] - X__[iX_y8], 2);
    real_type t228 = pow(V__[8] - X__[iX_y9], 2);
    real_type t232 = pow(V__[9] - X__[iX_y10], 2);
    real_type t235 = sin(X__[iX_x11]);
    real_type t236 = P__[iP_u11];
    real_type t238 = pow(V__[30] - t235 - t236, 2);
    real_type t240 = X__[iX_xx12];
    real_type t241 = sin(t240);
    real_type t243 = P__[iP_u12];
    real_type t245 = pow(V__[71] - 0.2e0 * t241 - t243, 2);
    real_type t248 = sin(X__[iX_x12]);
    real_type t250 = pow(V__[31] - t248 - t243, 2);
    real_type t254 = pow(V__[2] - X__[iX_y3], 2);
    real_type t258 = pow(V__[3] - X__[iX_y4], 2);
    real_type t262 = pow(V__[4] - X__[iX_y5], 2);
    real_type t266 = pow(V__[5] - X__[iX_y6], 2);
    real_type t268 = X__[iX_xx17];
    real_type t269 = sin(t268);
    real_type t271 = P__[iP_u17];
    real_type t273 = pow(V__[76] - 0.2e0 * t269 - t271, 2);
    real_type t274 = t216 + t220 + t224 + t228 + t232 + t238 + t245 + t250 + t254 + t258 + t262 + t266 + t273;
    real_type t279 = sin(X__[iX_x17]);
    real_type t281 = pow(V__[36] - t279 - t271, 2);
    real_type t283 = X__[iX_xx18];
    real_type t284 = sin(t283);
    real_type t286 = P__[iP_u18];
    real_type t288 = pow(V__[77] - 0.2e0 * t284 - t286, 2);
    real_type t292 = pow(V__[1] - X__[iX_y2], 2);
    real_type t294 = X__[iX_xx10];
    real_type t295 = sin(t294);
    real_type t297 = P__[iP_u10];
    real_type t299 = pow(V__[69] - 0.2e0 * t295 - t297, 2);
    real_type t302 = sin(X__[iX_x10]);
    real_type t304 = pow(V__[29] - t302 - t297, 2);
    real_type t306 = X__[iX_xx11];
    real_type t307 = sin(t306);
    real_type t310 = pow(V__[70] - 0.2e0 * t307 - t236, 2);
    real_type t313 = sin(X__[iX_x14]);
    real_type t315 = pow(V__[33] - t313 - t181, 2);
    real_type t317 = X__[iX_xx15];
    real_type t318 = sin(t317);
    real_type t320 = P__[iP_u15];
    real_type t322 = pow(V__[74] - 0.2e0 * t318 - t320, 2);
    real_type t325 = sin(X__[iX_x15]);
    real_type t327 = pow(V__[34] - t325 - t320, 2);
    real_type t329 = X__[iX_yy16];
    real_type t332 = sin(t23 + 15);
    real_type t335 = pow(V__[55] - 0.12e1 * t329 - 0.1e0 * t332, 2);
    real_type t337 = X__[iX_yy17];
    real_type t340 = sin(t23 + 16);
    real_type t343 = pow(V__[56] - 0.12e1 * t337 - 0.1e0 * t340, 2);
    real_type t345 = X__[iX_yy18];
    real_type t348 = sin(t23 + 17);
    real_type t351 = pow(V__[57] - 0.12e1 * t345 - 0.1e0 * t348, 2);
    real_type t352 = t281 + t288 + t292 + t299 + t304 + t310 + t315 + t322 + t327 + t335 + t343 + t351;
    real_type t354 = X__[iX_yy13];
    real_type t357 = sin(t23 + 12);
    real_type t360 = pow(V__[52] - 0.12e1 * t354 - 0.1e0 * t357, 2);
    real_type t362 = X__[iX_yy14];
    real_type t365 = sin(t23 + 13);
    real_type t368 = pow(V__[53] - 0.12e1 * t362 - 0.1e0 * t365, 2);
    real_type t370 = X__[iX_yy15];
    real_type t373 = sin(t23 + 14);
    real_type t376 = pow(V__[54] - 0.12e1 * t370 - 0.1e0 * t373, 2);
    real_type t378 = X__[iX_yy11];
    real_type t381 = sin(t23 + 10);
    real_type t384 = pow(V__[50] - 0.12e1 * t378 - 0.1e0 * t381, 2);
    real_type t386 = X__[iX_yy12];
    real_type t389 = sin(t23 + 11);
    real_type t392 = pow(V__[51] - 0.12e1 * t386 - 0.1e0 * t389, 2);
    real_type t394 = X__[iX_yy8];
    real_type t397 = sin(t23 + 7);
    real_type t400 = pow(V__[47] - 0.12e1 * t394 - 0.1e0 * t397, 2);
    real_type t402 = X__[iX_yy9];
    real_type t405 = sin(t23 + 8);
    real_type t408 = pow(V__[48] - 0.12e1 * t402 - 0.1e0 * t405, 2);
    real_type t410 = X__[iX_yy10];
    real_type t413 = sin(t23 + 9);
    real_type t416 = pow(V__[49] - 0.12e1 * t410 - 0.1e0 * t413, 2);
    real_type t418 = X__[iX_yy5];
    real_type t421 = sin(t23 + 4);
    real_type t424 = pow(V__[44] - 0.12e1 * t418 - 0.1e0 * t421, 2);
    real_type t426 = X__[iX_yy6];
    real_type t429 = sin(t23 + 5);
    real_type t432 = pow(V__[45] - 0.12e1 * t426 - 0.1e0 * t429, 2);
    real_type t434 = X__[iX_yy7];
    real_type t437 = sin(t23 + 6);
    real_type t440 = pow(V__[46] - 0.12e1 * t434 - 0.1e0 * t437, 2);
    real_type t442 = X__[iX_yy3];
    real_type t445 = sin(t23 + 2);
    real_type t448 = pow(V__[42] - 0.12e1 * t442 - 0.1e0 * t445, 2);
    real_type t450 = X__[iX_yy4];
    real_type t453 = sin(t23 + 3);
    real_type t456 = pow(V__[43] - 0.12e1 * t450 - 0.1e0 * t453, 2);
    real_type t457 = t360 + t368 + t376 + t384 + t392 + t400 + t408 + t416 + t424 + t432 + t440 + t448 + t456;
    real_type t459 = ModelPars[iM_xy_bound];
    real_type t461 = yy20Limitation_min(-t459 - t30);
    real_type t463 = yy20Limitation_max(t30 - t459);
    real_type t465 = X__[iX_yy1];
    real_type t467 = sin(t23);
    real_type t470 = pow(V__[40] - 0.12e1 * t465 - 0.1e0 * t467, 2);
    real_type t472 = X__[iX_yy2];
    real_type t475 = sin(t23 + 1);
    real_type t478 = pow(V__[41] - 0.12e1 * t472 - 0.1e0 * t475, 2);
    real_type t480 = yy18Limitation_min(-t459 - t345);
    real_type t482 = yy19Limitation_min(-t459 - t21);
    real_type t484 = yy19Limitation_max(t21 - t459);
    real_type t486 = yy16Limitation_min(-t459 - t329);
    real_type t488 = yy16Limitation_max(t329 - t459);
    real_type t490 = yy17Limitation_min(-t459 - t337);
    real_type t492 = yy17Limitation_max(t337 - t459);
    real_type t494 = yy18Limitation_max(t345 - t459);
    real_type t495 = t461 + t463 + t470 + t478 + t480 + t482 + t484 + t486 + t488 + t490 + t492 + t494;
    real_type t497 = yy14Limitation_max(t362 - t459);
    real_type t499 = yy15Limitation_min(-t459 - t370);
    real_type t501 = yy15Limitation_max(t370 - t459);
    real_type t503 = yy12Limitation_max(t386 - t459);
    real_type t505 = yy13Limitation_min(-t459 - t354);
    real_type t507 = yy13Limitation_max(t354 - t459);
    real_type t509 = yy14Limitation_min(-t459 - t362);
    real_type t511 = yy11Limitation_min(-t459 - t378);
    real_type t513 = yy11Limitation_max(t378 - t459);
    real_type t515 = yy12Limitation_min(-t459 - t386);
    real_type t517 = yy9Limitation_min(-t459 - t402);
    real_type t519 = yy9Limitation_max(t402 - t459);
    real_type t521 = yy10Limitation_min(-t459 - t410);
    real_type t522 = t497 + t499 + t501 + t503 + t505 + t507 + t509 + t511 + t513 + t515 + t517 + t519 + t521;
    real_type t527 = yy10Limitation_max(t410 - t459);
    real_type t529 = yy7Limitation_min(-t459 - t434);
    real_type t531 = yy7Limitation_max(t434 - t459);
    real_type t533 = yy8Limitation_min(-t459 - t394);
    real_type t535 = yy8Limitation_max(t394 - t459);
    real_type t537 = yy5Limitation_min(-t459 - t418);
    real_type t539 = yy5Limitation_max(t418 - t459);
    real_type t541 = yy6Limitation_min(-t459 - t426);
    real_type t543 = yy6Limitation_max(t426 - t459);
    real_type t545 = yy3Limitation_min(-t459 - t442);
    real_type t547 = yy3Limitation_max(t442 - t459);
    real_type t549 = yy4Limitation_min(-t459 - t450);
    real_type t550 = t527 + t529 + t531 + t533 + t535 + t537 + t539 + t541 + t543 + t545 + t547 + t549;
    real_type t552 = yy4Limitation_max(t450 - t459);
    real_type t554 = yy1Limitation_min(-t459 - t465);
    real_type t556 = yy1Limitation_max(t465 - t459);
    real_type t558 = yy2Limitation_min(-t459 - t472);
    real_type t560 = yy2Limitation_max(t472 - t459);
    real_type t561 = X__[iX_xx19];
    real_type t563 = xx19Limitation_min(-t459 - t561);
    real_type t565 = xx19Limitation_max(t561 - t459);
    real_type t567 = xx20Limitation_min(-t459 - t148);
    real_type t569 = xx20Limitation_max(t148 - t459);
    real_type t571 = xx17Limitation_min(-t459 - t268);
    real_type t573 = xx17Limitation_max(t268 - t459);
    real_type t575 = xx18Limitation_min(-t459 - t283);
    real_type t577 = xx18Limitation_max(t283 - t459);
    real_type t578 = t552 + t554 + t556 + t558 + t560 + t563 + t565 + t567 + t569 + t571 + t573 + t575 + t577;
    real_type t581 = xx15Limitation_max(t317 - t459);
    real_type t583 = xx16Limitation_min(-t459 - t136);
    real_type t585 = xx16Limitation_max(t136 - t459);
    real_type t587 = xx13Limitation_max(t166 - t459);
    real_type t589 = xx14Limitation_min(-t459 - t178);
    real_type t591 = xx14Limitation_max(t178 - t459);
    real_type t593 = xx15Limitation_min(-t459 - t317);
    real_type t595 = xx11Limitation_max(t306 - t459);
    real_type t597 = xx12Limitation_min(-t459 - t240);
    real_type t599 = xx12Limitation_max(t240 - t459);
    real_type t601 = xx13Limitation_min(-t459 - t166);
    real_type t603 = xx9Limitation_min(-t459 - t44);
    real_type t604 = t581 + t583 + t585 + t587 + t589 + t591 + t593 + t595 + t597 + t599 + t601 + t603;
    real_type t606 = xx10Limitation_min(-t459 - t294);
    real_type t608 = xx10Limitation_max(t294 - t459);
    real_type t610 = xx11Limitation_min(-t459 - t306);
    real_type t612 = xx7Limitation_max(t64 - t459);
    real_type t614 = xx8Limitation_min(-t459 - t77);
    real_type t616 = xx8Limitation_max(t77 - t459);
    real_type t618 = xx9Limitation_max(t44 - t459);
    real_type t620 = xx6Limitation_min(-t459 - t89);
    real_type t622 = xx6Limitation_max(t89 - t459);
    real_type t624 = xx7Limitation_min(-t459 - t64);
    real_type t626 = xx4Limitation_min(-t459 - t101);
    real_type t628 = xx4Limitation_max(t101 - t459);
    real_type t630 = xx5Limitation_min(-t459 - t113);
    real_type t631 = t606 + t608 + t610 + t612 + t614 + t616 + t618 + t620 + t622 + t624 + t626 + t628 + t630;
    real_type t635 = xx5Limitation_max(t113 - t459);
    real_type t637 = xx2Limitation_min(-t459 - t2);
    real_type t639 = xx2Limitation_max(t2 - t459);
    real_type t641 = xx3Limitation_min(-t459 - t15);
    real_type t643 = xx3Limitation_max(t15 - t459);
    real_type t645 = u20Limitation_min(-10 - t151);
    real_type t647 = u20Limitation_max(t151 - 10);
    real_type t649 = xx1Limitation_min(-t459 - t125);
    real_type t651 = xx1Limitation_max(t125 - t459);
    real_type t653 = u18Limitation_min(-10 - t286);
    real_type t655 = u18Limitation_max(t286 - 10);
    real_type t656 = P__[iP_u19];
    real_type t658 = u19Limitation_min(-10 - t656);
    real_type t659 = t635 + t637 + t639 + t641 + t643 + t645 + t647 + t649 + t651 + t653 + t655 + t658;
    real_type t661 = u19Limitation_max(t656 - 10);
    real_type t663 = u15Limitation_max(t320 - 10);
    real_type t665 = u16Limitation_min(-10 - t139);
    real_type t667 = u16Limitation_max(t139 - 10);
    real_type t669 = u17Limitation_min(-10 - t271);
    real_type t671 = u17Limitation_max(t271 - 10);
    real_type t673 = u13Limitation_min(-10 - t169);
    real_type t675 = u13Limitation_max(t169 - 10);
    real_type t677 = u14Limitation_min(-10 - t181);
    real_type t679 = u14Limitation_max(t181 - 10);
    real_type t681 = u15Limitation_min(-10 - t320);
    real_type t683 = u11Limitation_min(-10 - t236);
    real_type t685 = u11Limitation_max(t236 - 10);
    real_type t686 = t661 + t663 + t665 + t667 + t669 + t671 + t673 + t675 + t677 + t679 + t681 + t683 + t685;
    real_type t689 = u12Limitation_min(-10 - t243);
    real_type t691 = u12Limitation_max(t243 - 10);
    real_type t693 = u9Limitation_min(-10 - t47);
    real_type t695 = u9Limitation_max(t47 - 10);
    real_type t697 = u10Limitation_min(-10 - t297);
    real_type t699 = u10Limitation_max(t297 - 10);
    real_type t701 = u8Limitation_min(-10 - t40);
    real_type t703 = u8Limitation_max(t40 - 10);
    real_type t705 = u6Limitation_max(t92 - 10);
    real_type t707 = u7Limitation_min(-10 - t67);
    real_type t709 = u7Limitation_max(t67 - 10);
    real_type t711 = u4Limitation_max(t104 - 10);
    real_type t712 = t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = u5Limitation_min(-10 - t85);
    real_type t716 = u5Limitation_max(t85 - 10);
    real_type t718 = u6Limitation_min(-10 - t92);
    real_type t720 = u2Limitation_min(-10 - t5);
    real_type t722 = u2Limitation_max(t5 - 10);
    real_type t724 = u3Limitation_min(-10 - t11);
    real_type t726 = u3Limitation_max(t11 - 10);
    real_type t728 = u4Limitation_min(-10 - t104);
    real_type t730 = u1Limitation_min(-10 - t121);
    real_type t732 = u1Limitation_max(t121 - 10);
    real_type t735 = sin(X__[iX_x18]);
    real_type t737 = pow(V__[37] - t735 - t286, 2);
    real_type t739 = sin(t561);
    real_type t742 = pow(V__[78] - 0.2e0 * t739 - t656, 2);
    real_type t745 = sin(X__[iX_x19]);
    real_type t747 = pow(V__[38] - t745 - t656, 2);
    real_type t748 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t737 + t742 + t747;
    real_type result__ = t75 + t154 + t212 + t274 + t352 + t457 + t495 + t522 + t550 + t578 + t604 + t631 + t659 + t686 + t712 + t748;
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
