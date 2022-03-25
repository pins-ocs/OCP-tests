/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
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
    real_type t1   = XM__[58];
    real_type t2   = ModelPars[iM_xy_bound];
    real_type t4   = xx19Limitation_max(t1 - t2);
    real_type t5   = XM__[59];
    real_type t7   = xx20Limitation_min(-t2 - t5);
    real_type t9   = xx20Limitation_max(t5 - t2);
    real_type t10  = XM__[60];
    real_type t12  = yy1Limitation_min(-t2 - t10);
    real_type t14  = yy1Limitation_max(t10 - t2);
    real_type t15  = XM__[61];
    real_type t17  = yy2Limitation_min(-t2 - t15);
    real_type t19  = yy2Limitation_max(t15 - t2);
    real_type t20  = XM__[62];
    real_type t22  = yy3Limitation_min(-t2 - t20);
    real_type t24  = yy3Limitation_max(t20 - t2);
    real_type t25  = XM__[63];
    real_type t27  = yy4Limitation_min(-t2 - t25);
    real_type t29  = yy4Limitation_max(t25 - t2);
    real_type t30  = XM__[64];
    real_type t32  = yy5Limitation_min(-t2 - t30);
    real_type t34  = yy5Limitation_max(t30 - t2);
    real_type t35  = XM__[65];
    real_type t37  = yy6Limitation_min(-t2 - t35);
    real_type t39  = yy6Limitation_max(t35 - t2);
    real_type t40  = t4 + t7 + t9 + t12 + t14 + t17 + t19 + t22 + t24 + t27 + t29 + t32 + t34 + t37 + t39;
    real_type t41  = XM__[66];
    real_type t43  = yy7Limitation_min(-t2 - t41);
    real_type t45  = yy7Limitation_max(t41 - t2);
    real_type t46  = XM__[67];
    real_type t48  = yy8Limitation_min(-t2 - t46);
    real_type t50  = yy8Limitation_max(t46 - t2);
    real_type t51  = XM__[68];
    real_type t53  = yy9Limitation_min(-t2 - t51);
    real_type t55  = yy9Limitation_max(t51 - t2);
    real_type t56  = XM__[69];
    real_type t58  = yy10Limitation_min(-t2 - t56);
    real_type t60  = yy10Limitation_max(t56 - t2);
    real_type t61  = XM__[70];
    real_type t63  = yy11Limitation_min(-t2 - t61);
    real_type t65  = yy11Limitation_max(t61 - t2);
    real_type t66  = XM__[71];
    real_type t68  = yy12Limitation_min(-t2 - t66);
    real_type t70  = yy12Limitation_max(t66 - t2);
    real_type t71  = XM__[72];
    real_type t73  = yy13Limitation_min(-t2 - t71);
    real_type t74  = XM__[3];
    real_type t75  = t74 * t74;
    real_type t77  = XM__[4];
    real_type t78  = t77 * t77;
    real_type t80  = t43 + t45 + t48 + t50 + t53 + t55 + t58 + t60 + t63 + t65 + t68 + t70 + t73 + 17 * t75 + 16 * t78;
    real_type t82  = XM__[5];
    real_type t83  = t82 * t82;
    real_type t85  = XM__[6];
    real_type t86  = t85 * t85;
    real_type t88  = XM__[7];
    real_type t89  = t88 * t88;
    real_type t91  = XM__[8];
    real_type t92  = t91 * t91;
    real_type t94  = XM__[9];
    real_type t95  = t94 * t94;
    real_type t98  = XM__[46];
    real_type t99  = sin(t98);
    real_type t101 = P__[iP_u7];
    real_type t105 = sin(t88);
    real_type t106 = P__[iP_u8];
    real_type t110 = XM__[47];
    real_type t111 = sin(t110);
    real_type t116 = sin(t91);
    real_type t117 = P__[iP_u9];
    real_type t121 = XM__[48];
    real_type t122 = sin(t121);
    real_type t127 = sin(t94);
    real_type t128 = P__[iP_u10];
    real_type t132 = XM__[49];
    real_type t133 = sin(t132);
    real_type t138 = XM__[10];
    real_type t139 = sin(t138);
    real_type t140 = P__[iP_u11];
    real_type t144 = XM__[50];
    real_type t145 = sin(t144);
    real_type t150 = XM__[11];
    real_type t151 = sin(t150);
    real_type t152 = P__[iP_u12];
    real_type t155 = 15 * t83 + 14 * t86 + 13 * t89 + 12 * t92 + 11 * t95 + (0.2e0 * t99 + t101) * LM__[66] + (t105 + t106) * LM__[27] + (0.2e0 * t111 + t106) * LM__[67] + (t116 + t117) * LM__[28] + (0.2e0 * t122 + t117) * LM__[68] + (t127 + t128) * LM__[29] + (0.2e0 * t133 + t128) * LM__[69] + (t139 + t140) * LM__[30] + (0.2e0 * t145 + t140) * LM__[70] + (t151 + t152) * LM__[31];
    real_type t157 = XM__[51];
    real_type t158 = sin(t157);
    real_type t163 = XM__[12];
    real_type t164 = sin(t163);
    real_type t165 = P__[iP_u13];
    real_type t169 = XM__[52];
    real_type t170 = sin(t169);
    real_type t175 = XM__[13];
    real_type t176 = sin(t175);
    real_type t177 = P__[iP_u14];
    real_type t181 = XM__[53];
    real_type t182 = sin(t181);
    real_type t187 = XM__[14];
    real_type t188 = sin(t187);
    real_type t189 = P__[iP_u15];
    real_type t193 = XM__[54];
    real_type t194 = sin(t193);
    real_type t199 = XM__[15];
    real_type t200 = sin(t199);
    real_type t201 = P__[iP_u16];
    real_type t205 = XM__[55];
    real_type t206 = sin(t205);
    real_type t211 = XM__[16];
    real_type t212 = sin(t211);
    real_type t213 = P__[iP_u17];
    real_type t217 = XM__[56];
    real_type t218 = sin(t217);
    real_type t223 = XM__[17];
    real_type t224 = sin(t223);
    real_type t225 = P__[iP_u18];
    real_type t229 = XM__[57];
    real_type t230 = sin(t229);
    real_type t235 = XM__[18];
    real_type t236 = sin(t235);
    real_type t237 = P__[iP_u19];
    real_type t241 = sin(t1);
    real_type t245 = (0.2e0 * t158 + t152) * LM__[71] + (t164 + t165) * LM__[32] + (0.2e0 * t170 + t165) * LM__[72] + (t176 + t177) * LM__[33] + (0.2e0 * t182 + t177) * LM__[73] + (t188 + t189) * LM__[34] + (0.2e0 * t194 + t189) * LM__[74] + (t200 + t201) * LM__[35] + (0.2e0 * t206 + t201) * LM__[75] + (t212 + t213) * LM__[36] + (0.2e0 * t218 + t213) * LM__[76] + (t224 + t225) * LM__[37] + (0.2e0 * t230 + t225) * LM__[77] + (t236 + t237) * LM__[38] + (0.2e0 * t241 + t237) * LM__[78];
    real_type t249 = XM__[19];
    real_type t250 = sin(t249);
    real_type t251 = P__[iP_u20];
    real_type t255 = sin(t5);
    real_type t261 = QM__[0];
    real_type t262 = sin(t261);
    real_type t269 = sin(t261 + 1);
    real_type t276 = sin(t261 + 2);
    real_type t283 = sin(t261 + 3);
    real_type t290 = sin(t261 + 4);
    real_type t297 = sin(t261 + 5);
    real_type t304 = sin(t261 + 6);
    real_type t311 = sin(t261 + 7);
    real_type t318 = sin(t261 + 8);
    real_type t325 = sin(t261 + 9);
    real_type t332 = sin(t261 + 10);
    real_type t339 = sin(t261 + 11);
    real_type t346 = sin(t261 + 12);
    real_type t350 = (t250 + t251) * LM__[39] + (0.2e0 * t255 + t251) * LM__[79] + (0.12e1 * t10 + 0.1e0 * t262) * LM__[40] + (0.12e1 * t15 + 0.1e0 * t269) * LM__[41] + (0.12e1 * t20 + 0.1e0 * t276) * LM__[42] + (0.12e1 * t25 + 0.1e0 * t283) * LM__[43] + (0.12e1 * t30 + 0.1e0 * t290) * LM__[44] + (0.12e1 * t35 + 0.1e0 * t297) * LM__[45] + (0.12e1 * t41 + 0.1e0 * t304) * LM__[46] + (0.12e1 * t46 + 0.1e0 * t311) * LM__[47] + (0.12e1 * t51 + 0.1e0 * t318) * LM__[48] + (0.12e1 * t56 + 0.1e0 * t325) * LM__[49] + (0.12e1 * t61 + 0.1e0 * t332) * LM__[50] + (0.12e1 * t66 + 0.1e0 * t339) * LM__[51] + (0.12e1 * t71 + 0.1e0 * t346) * LM__[52];
    real_type t352 = XM__[73];
    real_type t355 = sin(t261 + 13);
    real_type t360 = XM__[74];
    real_type t363 = sin(t261 + 14);
    real_type t368 = XM__[75];
    real_type t371 = sin(t261 + 15);
    real_type t376 = XM__[76];
    real_type t379 = sin(t261 + 16);
    real_type t384 = XM__[77];
    real_type t387 = sin(t261 + 17);
    real_type t392 = XM__[78];
    real_type t395 = sin(t261 + 18);
    real_type t400 = XM__[79];
    real_type t403 = sin(t261 + 19);
    real_type t408 = XM__[20];
    real_type t411 = XM__[21];
    real_type t414 = XM__[22];
    real_type t417 = XM__[23];
    real_type t420 = XM__[24];
    real_type t423 = XM__[25];
    real_type t426 = XM__[26];
    real_type t429 = XM__[27];
    real_type t431 = (0.12e1 * t352 + 0.1e0 * t355) * LM__[53] + (0.12e1 * t360 + 0.1e0 * t363) * LM__[54] + (0.12e1 * t368 + 0.1e0 * t371) * LM__[55] + (0.12e1 * t376 + 0.1e0 * t379) * LM__[56] + (0.12e1 * t384 + 0.1e0 * t387) * LM__[57] + (0.12e1 * t392 + 0.1e0 * t395) * LM__[58] + (0.12e1 * t400 + 0.1e0 * t403) * LM__[59] + t408 * LM__[0] + t411 * LM__[1] + t414 * LM__[2] + t417 * LM__[3] + t420 * LM__[4] + t423 * LM__[5] + t426 * LM__[6] + t429 * LM__[7];
    real_type t434 = XM__[28];
    real_type t437 = XM__[29];
    real_type t440 = XM__[30];
    real_type t443 = XM__[31];
    real_type t446 = XM__[32];
    real_type t449 = XM__[33];
    real_type t452 = XM__[34];
    real_type t455 = XM__[35];
    real_type t458 = XM__[36];
    real_type t461 = XM__[37];
    real_type t464 = XM__[38];
    real_type t467 = XM__[39];
    real_type t470 = XM__[0];
    real_type t471 = sin(t470);
    real_type t472 = P__[iP_u1];
    real_type t476 = XM__[40];
    real_type t477 = sin(t476);
    real_type t482 = XM__[1];
    real_type t483 = sin(t482);
    real_type t484 = P__[iP_u2];
    real_type t487 = t434 * LM__[8] + t437 * LM__[9] + t440 * LM__[10] + t443 * LM__[11] + t446 * LM__[12] + t449 * LM__[13] + t452 * LM__[14] + t455 * LM__[15] + t458 * LM__[16] + t461 * LM__[17] + t464 * LM__[18] + t467 * LM__[19] + (t471 + t472) * LM__[20] + (0.2e0 * t477 + t472) * LM__[60] + (t483 + t484) * LM__[21];
    real_type t489 = XM__[41];
    real_type t490 = sin(t489);
    real_type t495 = XM__[2];
    real_type t496 = sin(t495);
    real_type t497 = P__[iP_u3];
    real_type t501 = XM__[42];
    real_type t502 = sin(t501);
    real_type t507 = sin(t74);
    real_type t508 = P__[iP_u4];
    real_type t512 = XM__[43];
    real_type t513 = sin(t512);
    real_type t518 = sin(t77);
    real_type t519 = P__[iP_u5];
    real_type t523 = XM__[44];
    real_type t524 = sin(t523);
    real_type t529 = sin(t82);
    real_type t530 = P__[iP_u6];
    real_type t534 = XM__[45];
    real_type t535 = sin(t534);
    real_type t540 = sin(t85);
    real_type t543 = t138 * t138;
    real_type t545 = t150 * t150;
    real_type t547 = t163 * t163;
    real_type t549 = t175 * t175;
    real_type t551 = t187 * t187;
    real_type t553 = (0.2e0 * t490 + t484) * LM__[61] + (t496 + t497) * LM__[22] + (0.2e0 * t502 + t497) * LM__[62] + (t507 + t508) * LM__[23] + (0.2e0 * t513 + t508) * LM__[63] + (t518 + t519) * LM__[24] + (0.2e0 * t524 + t519) * LM__[64] + (t529 + t530) * LM__[25] + (0.2e0 * t535 + t530) * LM__[65] + (t540 + t101) * LM__[26] + 10 * t543 + 9 * t545 + 8 * t547 + 7 * t549 + 6 * t551;
    real_type t557 = t199 * t199;
    real_type t559 = t211 * t211;
    real_type t561 = t223 * t223;
    real_type t563 = t235 * t235;
    real_type t565 = t249 * t249;
    real_type t566 = t408 * t408;
    real_type t568 = t411 * t411;
    real_type t570 = t414 * t414;
    real_type t572 = t417 * t417;
    real_type t574 = t420 * t420;
    real_type t577 = u6Limitation_max(t530 - 10);
    real_type t579 = u7Limitation_min(-10 - t101);
    real_type t581 = u7Limitation_max(t101 - 10);
    real_type t583 = u8Limitation_min(-10 - t106);
    real_type t585 = u8Limitation_max(t106 - 10);
    real_type t586 = 5 * t557 + 4 * t559 + 3 * t561 + 2 * t563 + t565 + 20 * t566 + 19 * t568 + 18 * t570 + 17 * t572 + 16 * t574 + t577 + t579 + t581 + t583 + t585;
    real_type t588 = u9Limitation_min(-10 - t117);
    real_type t590 = u9Limitation_max(t117 - 10);
    real_type t592 = xx5Limitation_min(-t2 - t523);
    real_type t594 = xx6Limitation_min(-t2 - t534);
    real_type t596 = xx6Limitation_max(t534 - t2);
    real_type t598 = xx7Limitation_min(-t2 - t98);
    real_type t600 = xx7Limitation_max(t98 - t2);
    real_type t602 = xx10Limitation_min(-t2 - t132);
    real_type t604 = xx10Limitation_max(t132 - t2);
    real_type t606 = xx11Limitation_min(-t2 - t144);
    real_type t608 = xx11Limitation_max(t144 - t2);
    real_type t610 = xx12Limitation_min(-t2 - t157);
    real_type t612 = xx8Limitation_min(-t2 - t110);
    real_type t614 = xx8Limitation_max(t110 - t2);
    real_type t616 = xx9Limitation_min(-t2 - t121);
    real_type t617 = t588 + t590 + t592 + t594 + t596 + t598 + t600 + t602 + t604 + t606 + t608 + t610 + t612 + t614 + t616;
    real_type t620 = xx9Limitation_max(t121 - t2);
    real_type t622 = u1Limitation_min(-10 - t472);
    real_type t624 = u1Limitation_max(t472 - 10);
    real_type t626 = u2Limitation_min(-10 - t484);
    real_type t628 = u2Limitation_max(t484 - 10);
    real_type t630 = u3Limitation_min(-10 - t497);
    real_type t632 = u3Limitation_max(t497 - 10);
    real_type t634 = xx12Limitation_max(t157 - t2);
    real_type t636 = xx13Limitation_min(-t2 - t169);
    real_type t638 = xx13Limitation_max(t169 - t2);
    real_type t640 = xx14Limitation_min(-t2 - t181);
    real_type t642 = xx14Limitation_max(t181 - t2);
    real_type t644 = xx1Limitation_max(t476 - t2);
    real_type t646 = xx2Limitation_min(-t2 - t489);
    real_type t648 = xx2Limitation_max(t489 - t2);
    real_type t649 = t620 + t622 + t624 + t626 + t628 + t630 + t632 + t634 + t636 + t638 + t640 + t642 + t644 + t646 + t648;
    real_type t651 = xx3Limitation_min(-t2 - t501);
    real_type t652 = t423 * t423;
    real_type t654 = t426 * t426;
    real_type t656 = t429 * t429;
    real_type t658 = t434 * t434;
    real_type t660 = t437 * t437;
    real_type t662 = t440 * t440;
    real_type t665 = u19Limitation_min(-10 - t237);
    real_type t667 = u19Limitation_max(t237 - 10);
    real_type t669 = u20Limitation_min(-10 - t251);
    real_type t671 = u20Limitation_max(t251 - 10);
    real_type t672 = t470 * t470;
    real_type t674 = t482 * t482;
    real_type t676 = t495 * t495;
    real_type t679 = u10Limitation_max(t128 - 10);
    real_type t680 = t651 + 15 * t652 + 14 * t654 + 13 * t656 + 12 * t658 + 11 * t660 + 10 * t662 + t665 + t667 + t669 + t671 + 20 * t672 + 19 * t674 + 18 * t676 + t679;
    real_type t684 = u10Limitation_min(-10 - t128);
    real_type t686 = u11Limitation_min(-10 - t140);
    real_type t688 = u11Limitation_max(t140 - 10);
    real_type t690 = u12Limitation_min(-10 - t152);
    real_type t692 = u12Limitation_max(t152 - 10);
    real_type t693 = t458 * t458;
    real_type t695 = t461 * t461;
    real_type t697 = t464 * t464;
    real_type t699 = t467 * t467;
    real_type t701 = xx1Limitation_min(-t2 - t476);
    real_type t703 = xx15Limitation_min(-t2 - t193);
    real_type t705 = xx15Limitation_max(t193 - t2);
    real_type t707 = xx16Limitation_min(-t2 - t205);
    real_type t709 = xx16Limitation_max(t205 - t2);
    real_type t711 = u13Limitation_min(-10 - t165);
    real_type t712 = t684 + t686 + t688 + t690 + t692 + 4 * t693 + 3 * t695 + 2 * t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = u13Limitation_max(t165 - 10);
    real_type t716 = u14Limitation_min(-10 - t177);
    real_type t718 = u14Limitation_max(t177 - 10);
    real_type t720 = u15Limitation_min(-10 - t189);
    real_type t722 = u15Limitation_max(t189 - 10);
    real_type t724 = xx17Limitation_min(-t2 - t217);
    real_type t726 = xx17Limitation_max(t217 - t2);
    real_type t728 = xx18Limitation_min(-t2 - t229);
    real_type t730 = xx18Limitation_max(t229 - t2);
    real_type t732 = xx19Limitation_min(-t2 - t1);
    real_type t733 = t443 * t443;
    real_type t735 = t446 * t446;
    real_type t737 = t449 * t449;
    real_type t739 = t452 * t452;
    real_type t741 = t455 * t455;
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + 9 * t733 + 8 * t735 + 7 * t737 + 6 * t739 + 5 * t741;
    real_type t746 = u16Limitation_min(-10 - t201);
    real_type t748 = u16Limitation_max(t201 - 10);
    real_type t750 = u17Limitation_min(-10 - t213);
    real_type t752 = u17Limitation_max(t213 - 10);
    real_type t754 = u18Limitation_min(-10 - t225);
    real_type t756 = u18Limitation_max(t225 - 10);
    real_type t758 = u4Limitation_min(-10 - t508);
    real_type t760 = u4Limitation_max(t508 - 10);
    real_type t762 = u5Limitation_min(-10 - t519);
    real_type t764 = u5Limitation_max(t519 - 10);
    real_type t766 = u6Limitation_min(-10 - t530);
    real_type t768 = xx3Limitation_max(t501 - t2);
    real_type t770 = xx4Limitation_min(-t2 - t512);
    real_type t772 = xx4Limitation_max(t512 - t2);
    real_type t774 = xx5Limitation_max(t523 - t2);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = yy13Limitation_max(t71 - t2);
    real_type t779 = yy14Limitation_min(-t2 - t352);
    real_type t781 = yy14Limitation_max(t352 - t2);
    real_type t783 = yy15Limitation_min(-t2 - t360);
    real_type t785 = yy15Limitation_max(t360 - t2);
    real_type t787 = yy16Limitation_min(-t2 - t368);
    real_type t789 = yy16Limitation_max(t368 - t2);
    real_type t791 = yy17Limitation_min(-t2 - t376);
    real_type t793 = yy17Limitation_max(t376 - t2);
    real_type t795 = yy18Limitation_min(-t2 - t384);
    real_type t797 = yy18Limitation_max(t384 - t2);
    real_type t799 = yy19Limitation_min(-t2 - t392);
    real_type t801 = yy19Limitation_max(t392 - t2);
    real_type t803 = yy20Limitation_min(-t2 - t400);
    real_type t805 = yy20Limitation_max(t400 - t2);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t40 + t80 + t155 + t245 + t350 + t431 + t487 + t553 + t586 + t617 + t649 + t680 + t712 + t743 + t775 + t806;
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
    real_type t4   = pow(V__[0] - X__[iX_y1], 2);
    real_type t8   = pow(V__[1] - X__[iX_y2], 2);
    real_type t10  = X__[iX_xx1];
    real_type t11  = sin(t10);
    real_type t13  = P__[iP_u1];
    real_type t15  = pow(V__[60] - 0.2e0 * t11 - t13, 2);
    real_type t18  = sin(X__[iX_x2]);
    real_type t19  = P__[iP_u2];
    real_type t21  = pow(V__[21] - t18 - t19, 2);
    real_type t23  = X__[iX_xx2];
    real_type t24  = sin(t23);
    real_type t27  = pow(V__[61] - 0.2e0 * t24 - t19, 2);
    real_type t31  = pow(V__[17] - X__[iX_y18], 2);
    real_type t35  = pow(V__[18] - X__[iX_y19], 2);
    real_type t39  = pow(V__[19] - X__[iX_y20], 2);
    real_type t42  = sin(X__[iX_x1]);
    real_type t44  = pow(V__[20] - t42 - t13, 2);
    real_type t48  = pow(V__[14] - X__[iX_y15], 2);
    real_type t52  = pow(V__[15] - X__[iX_y16], 2);
    real_type t56  = pow(V__[16] - X__[iX_y17], 2);
    real_type t57  = t4 + t8 + t15 + t21 + t27 + t31 + t35 + t39 + t44 + t48 + t52 + t56;
    real_type t61  = pow(V__[10] - X__[iX_y11], 2);
    real_type t65  = pow(V__[11] - X__[iX_y12], 2);
    real_type t69  = pow(V__[12] - X__[iX_y13], 2);
    real_type t73  = pow(V__[13] - X__[iX_y14], 2);
    real_type t77  = pow(V__[6] - X__[iX_y7], 2);
    real_type t81  = pow(V__[7] - X__[iX_y8], 2);
    real_type t85  = pow(V__[8] - X__[iX_y9], 2);
    real_type t89  = pow(V__[9] - X__[iX_y10], 2);
    real_type t93  = pow(V__[2] - X__[iX_y3], 2);
    real_type t97  = pow(V__[3] - X__[iX_y4], 2);
    real_type t101 = pow(V__[4] - X__[iX_y5], 2);
    real_type t105 = pow(V__[5] - X__[iX_y6], 2);
    real_type t107 = X__[iX_xx19];
    real_type t108 = sin(t107);
    real_type t110 = P__[iP_u19];
    real_type t112 = pow(V__[78] - 0.2e0 * t108 - t110, 2);
    real_type t113 = t61 + t65 + t69 + t73 + t77 + t81 + t85 + t89 + t93 + t97 + t101 + t105 + t112;
    real_type t117 = sin(X__[iX_x20]);
    real_type t118 = P__[iP_u20];
    real_type t120 = pow(V__[39] - t117 - t118, 2);
    real_type t122 = X__[iX_xx20];
    real_type t123 = sin(t122);
    real_type t126 = pow(V__[79] - 0.2e0 * t123 - t118, 2);
    real_type t129 = sin(X__[iX_x18]);
    real_type t130 = P__[iP_u18];
    real_type t132 = pow(V__[37] - t129 - t130, 2);
    real_type t134 = X__[iX_xx18];
    real_type t135 = sin(t134);
    real_type t138 = pow(V__[77] - 0.2e0 * t135 - t130, 2);
    real_type t141 = sin(X__[iX_x19]);
    real_type t143 = pow(V__[38] - t141 - t110, 2);
    real_type t145 = X__[iX_xx16];
    real_type t146 = sin(t145);
    real_type t148 = P__[iP_u16];
    real_type t150 = pow(V__[75] - 0.2e0 * t146 - t148, 2);
    real_type t153 = sin(X__[iX_x17]);
    real_type t154 = P__[iP_u17];
    real_type t156 = pow(V__[36] - t153 - t154, 2);
    real_type t158 = X__[iX_xx17];
    real_type t159 = sin(t158);
    real_type t162 = pow(V__[76] - 0.2e0 * t159 - t154, 2);
    real_type t165 = sin(X__[iX_x15]);
    real_type t166 = P__[iP_u15];
    real_type t168 = pow(V__[34] - t165 - t166, 2);
    real_type t170 = X__[iX_xx15];
    real_type t171 = sin(t170);
    real_type t174 = pow(V__[74] - 0.2e0 * t171 - t166, 2);
    real_type t177 = sin(X__[iX_x16]);
    real_type t179 = pow(V__[35] - t177 - t148, 2);
    real_type t181 = X__[iX_xx13];
    real_type t182 = sin(t181);
    real_type t184 = P__[iP_u13];
    real_type t186 = pow(V__[72] - 0.2e0 * t182 - t184, 2);
    real_type t187 = t120 + t126 + t132 + t138 + t143 + t150 + t156 + t162 + t168 + t174 + t179 + t186;
    real_type t190 = sin(X__[iX_x14]);
    real_type t191 = P__[iP_u14];
    real_type t193 = pow(V__[33] - t190 - t191, 2);
    real_type t195 = X__[iX_xx14];
    real_type t196 = sin(t195);
    real_type t199 = pow(V__[73] - 0.2e0 * t196 - t191, 2);
    real_type t202 = sin(X__[iX_x12]);
    real_type t203 = P__[iP_u12];
    real_type t205 = pow(V__[31] - t202 - t203, 2);
    real_type t207 = X__[iX_xx12];
    real_type t208 = sin(t207);
    real_type t211 = pow(V__[71] - 0.2e0 * t208 - t203, 2);
    real_type t214 = sin(X__[iX_x13]);
    real_type t216 = pow(V__[32] - t214 - t184, 2);
    real_type t218 = X__[iX_xx10];
    real_type t219 = sin(t218);
    real_type t221 = P__[iP_u10];
    real_type t223 = pow(V__[69] - 0.2e0 * t219 - t221, 2);
    real_type t226 = sin(X__[iX_x11]);
    real_type t227 = P__[iP_u11];
    real_type t229 = pow(V__[30] - t226 - t227, 2);
    real_type t231 = X__[iX_xx11];
    real_type t232 = sin(t231);
    real_type t235 = pow(V__[70] - 0.2e0 * t232 - t227, 2);
    real_type t238 = sin(X__[iX_x9]);
    real_type t239 = P__[iP_u9];
    real_type t241 = pow(V__[28] - t238 - t239, 2);
    real_type t243 = X__[iX_xx9];
    real_type t244 = sin(t243);
    real_type t247 = pow(V__[68] - 0.2e0 * t244 - t239, 2);
    real_type t250 = sin(X__[iX_x10]);
    real_type t252 = pow(V__[29] - t250 - t221, 2);
    real_type t254 = X__[iX_xx7];
    real_type t255 = sin(t254);
    real_type t257 = P__[iP_u7];
    real_type t259 = pow(V__[66] - 0.2e0 * t255 - t257, 2);
    real_type t262 = sin(X__[iX_x8]);
    real_type t263 = P__[iP_u8];
    real_type t265 = pow(V__[27] - t262 - t263, 2);
    real_type t266 = t193 + t199 + t205 + t211 + t216 + t223 + t229 + t235 + t241 + t247 + t252 + t259 + t265;
    real_type t270 = X__[iX_xx8];
    real_type t271 = sin(t270);
    real_type t274 = pow(V__[67] - 0.2e0 * t271 - t263, 2);
    real_type t277 = sin(X__[iX_x6]);
    real_type t278 = P__[iP_u6];
    real_type t280 = pow(V__[25] - t277 - t278, 2);
    real_type t282 = X__[iX_xx6];
    real_type t283 = sin(t282);
    real_type t286 = pow(V__[65] - 0.2e0 * t283 - t278, 2);
    real_type t289 = sin(X__[iX_x7]);
    real_type t291 = pow(V__[26] - t289 - t257, 2);
    real_type t293 = X__[iX_xx4];
    real_type t294 = sin(t293);
    real_type t296 = P__[iP_u4];
    real_type t298 = pow(V__[63] - 0.2e0 * t294 - t296, 2);
    real_type t301 = sin(X__[iX_x5]);
    real_type t302 = P__[iP_u5];
    real_type t304 = pow(V__[24] - t301 - t302, 2);
    real_type t306 = X__[iX_xx5];
    real_type t307 = sin(t306);
    real_type t310 = pow(V__[64] - 0.2e0 * t307 - t302, 2);
    real_type t313 = sin(X__[iX_x3]);
    real_type t314 = P__[iP_u3];
    real_type t316 = pow(V__[22] - t313 - t314, 2);
    real_type t318 = X__[iX_xx3];
    real_type t319 = sin(t318);
    real_type t322 = pow(V__[62] - 0.2e0 * t319 - t314, 2);
    real_type t325 = sin(X__[iX_x4]);
    real_type t327 = pow(V__[23] - t325 - t296, 2);
    real_type t329 = X__[iX_yy19];
    real_type t331 = Q__[iQ_zeta];
    real_type t333 = sin(t331 + 18);
    real_type t336 = pow(V__[58] - 0.12e1 * t329 - 0.1e0 * t333, 2);
    real_type t338 = X__[iX_yy20];
    real_type t341 = sin(t331 + 19);
    real_type t344 = pow(V__[59] - 0.12e1 * t338 - 0.1e0 * t341, 2);
    real_type t345 = t274 + t280 + t286 + t291 + t298 + t304 + t310 + t316 + t322 + t327 + t336 + t344;
    real_type t347 = X__[iX_yy16];
    real_type t350 = sin(t331 + 15);
    real_type t353 = pow(V__[55] - 0.12e1 * t347 - 0.1e0 * t350, 2);
    real_type t355 = X__[iX_yy17];
    real_type t358 = sin(t331 + 16);
    real_type t361 = pow(V__[56] - 0.12e1 * t355 - 0.1e0 * t358, 2);
    real_type t363 = X__[iX_yy18];
    real_type t366 = sin(t331 + 17);
    real_type t369 = pow(V__[57] - 0.12e1 * t363 - 0.1e0 * t366, 2);
    real_type t371 = X__[iX_yy13];
    real_type t374 = sin(t331 + 12);
    real_type t377 = pow(V__[52] - 0.12e1 * t371 - 0.1e0 * t374, 2);
    real_type t379 = X__[iX_yy14];
    real_type t382 = sin(t331 + 13);
    real_type t385 = pow(V__[53] - 0.12e1 * t379 - 0.1e0 * t382, 2);
    real_type t387 = X__[iX_yy15];
    real_type t390 = sin(t331 + 14);
    real_type t393 = pow(V__[54] - 0.12e1 * t387 - 0.1e0 * t390, 2);
    real_type t395 = X__[iX_yy10];
    real_type t398 = sin(t331 + 9);
    real_type t401 = pow(V__[49] - 0.12e1 * t395 - 0.1e0 * t398, 2);
    real_type t403 = X__[iX_yy11];
    real_type t406 = sin(t331 + 10);
    real_type t409 = pow(V__[50] - 0.12e1 * t403 - 0.1e0 * t406, 2);
    real_type t411 = X__[iX_yy12];
    real_type t414 = sin(t331 + 11);
    real_type t417 = pow(V__[51] - 0.12e1 * t411 - 0.1e0 * t414, 2);
    real_type t419 = X__[iX_yy8];
    real_type t422 = sin(t331 + 7);
    real_type t425 = pow(V__[47] - 0.12e1 * t419 - 0.1e0 * t422, 2);
    real_type t427 = X__[iX_yy9];
    real_type t430 = sin(t331 + 8);
    real_type t433 = pow(V__[48] - 0.12e1 * t427 - 0.1e0 * t430, 2);
    real_type t435 = X__[iX_yy5];
    real_type t438 = sin(t331 + 4);
    real_type t441 = pow(V__[44] - 0.12e1 * t435 - 0.1e0 * t438, 2);
    real_type t443 = X__[iX_yy6];
    real_type t446 = sin(t331 + 5);
    real_type t449 = pow(V__[45] - 0.12e1 * t443 - 0.1e0 * t446, 2);
    real_type t450 = t353 + t361 + t369 + t377 + t385 + t393 + t401 + t409 + t417 + t425 + t433 + t441 + t449;
    real_type t453 = X__[iX_yy7];
    real_type t456 = sin(t331 + 6);
    real_type t459 = pow(V__[46] - 0.12e1 * t453 - 0.1e0 * t456, 2);
    real_type t461 = X__[iX_yy2];
    real_type t464 = sin(t331 + 1);
    real_type t467 = pow(V__[41] - 0.12e1 * t461 - 0.1e0 * t464, 2);
    real_type t469 = X__[iX_yy3];
    real_type t472 = sin(t331 + 2);
    real_type t475 = pow(V__[42] - 0.12e1 * t469 - 0.1e0 * t472, 2);
    real_type t477 = X__[iX_yy4];
    real_type t480 = sin(t331 + 3);
    real_type t483 = pow(V__[43] - 0.12e1 * t477 - 0.1e0 * t480, 2);
    real_type t484 = ModelPars[iM_xy_bound];
    real_type t486 = xx5Limitation_max(t306 - t484);
    real_type t488 = xx6Limitation_min(-t484 - t282);
    real_type t490 = xx6Limitation_max(t282 - t484);
    real_type t492 = X__[iX_yy1];
    real_type t494 = sin(t331);
    real_type t497 = pow(V__[40] - 0.12e1 * t492 - 0.1e0 * t494, 2);
    real_type t499 = xx3Limitation_max(t318 - t484);
    real_type t501 = xx4Limitation_min(-t484 - t293);
    real_type t503 = xx4Limitation_max(t293 - t484);
    real_type t505 = xx5Limitation_min(-t484 - t306);
    real_type t506 = t459 + t467 + t475 + t483 + t486 + t488 + t490 + t497 + t499 + t501 + t503 + t505;
    real_type t508 = xx1Limitation_max(t10 - t484);
    real_type t510 = xx2Limitation_min(-t484 - t23);
    real_type t512 = xx2Limitation_max(t23 - t484);
    real_type t514 = xx3Limitation_min(-t484 - t318);
    real_type t516 = yy20Limitation_min(-t484 - t338);
    real_type t518 = yy20Limitation_max(t338 - t484);
    real_type t520 = xx1Limitation_min(-t484 - t10);
    real_type t522 = yy18Limitation_min(-t484 - t363);
    real_type t524 = yy18Limitation_max(t363 - t484);
    real_type t526 = yy19Limitation_min(-t484 - t329);
    real_type t528 = yy19Limitation_max(t329 - t484);
    real_type t530 = yy16Limitation_min(-t484 - t347);
    real_type t532 = yy16Limitation_max(t347 - t484);
    real_type t533 = t508 + t510 + t512 + t514 + t516 + t518 + t520 + t522 + t524 + t526 + t528 + t530 + t532;
    real_type t538 = yy17Limitation_min(-t484 - t355);
    real_type t540 = yy17Limitation_max(t355 - t484);
    real_type t542 = yy14Limitation_min(-t484 - t379);
    real_type t544 = yy14Limitation_max(t379 - t484);
    real_type t546 = yy15Limitation_min(-t484 - t387);
    real_type t548 = yy15Limitation_max(t387 - t484);
    real_type t550 = yy12Limitation_max(t411 - t484);
    real_type t552 = yy13Limitation_min(-t484 - t371);
    real_type t554 = yy13Limitation_max(t371 - t484);
    real_type t556 = yy10Limitation_max(t395 - t484);
    real_type t558 = yy11Limitation_min(-t484 - t403);
    real_type t560 = yy11Limitation_max(t403 - t484);
    real_type t561 = t538 + t540 + t542 + t544 + t546 + t548 + t550 + t552 + t554 + t556 + t558 + t560;
    real_type t563 = yy12Limitation_min(-t484 - t411);
    real_type t565 = yy8Limitation_max(t419 - t484);
    real_type t567 = yy9Limitation_min(-t484 - t427);
    real_type t569 = yy9Limitation_max(t427 - t484);
    real_type t571 = yy10Limitation_min(-t484 - t395);
    real_type t573 = yy7Limitation_min(-t484 - t453);
    real_type t575 = yy7Limitation_max(t453 - t484);
    real_type t577 = yy8Limitation_min(-t484 - t419);
    real_type t579 = yy5Limitation_min(-t484 - t435);
    real_type t581 = yy5Limitation_max(t435 - t484);
    real_type t583 = yy6Limitation_min(-t484 - t443);
    real_type t585 = yy6Limitation_max(t443 - t484);
    real_type t587 = yy3Limitation_min(-t484 - t469);
    real_type t588 = t563 + t565 + t567 + t569 + t571 + t573 + t575 + t577 + t579 + t581 + t583 + t585 + t587;
    real_type t591 = yy3Limitation_max(t469 - t484);
    real_type t593 = yy4Limitation_min(-t484 - t477);
    real_type t595 = yy4Limitation_max(t477 - t484);
    real_type t597 = yy1Limitation_max(t492 - t484);
    real_type t599 = yy2Limitation_min(-t484 - t461);
    real_type t601 = yy2Limitation_max(t461 - t484);
    real_type t603 = xx19Limitation_max(t107 - t484);
    real_type t605 = xx20Limitation_min(-t484 - t122);
    real_type t607 = xx20Limitation_max(t122 - t484);
    real_type t609 = yy1Limitation_min(-t484 - t492);
    real_type t611 = xx17Limitation_max(t158 - t484);
    real_type t613 = xx18Limitation_min(-t484 - t134);
    real_type t614 = t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613;
    real_type t616 = xx18Limitation_max(t134 - t484);
    real_type t618 = xx19Limitation_min(-t484 - t107);
    real_type t620 = xx15Limitation_max(t170 - t484);
    real_type t622 = xx16Limitation_min(-t484 - t145);
    real_type t624 = xx16Limitation_max(t145 - t484);
    real_type t626 = xx17Limitation_min(-t484 - t158);
    real_type t628 = xx13Limitation_max(t181 - t484);
    real_type t630 = xx14Limitation_min(-t484 - t195);
    real_type t632 = xx14Limitation_max(t195 - t484);
    real_type t634 = xx15Limitation_min(-t484 - t170);
    real_type t636 = xx11Limitation_max(t231 - t484);
    real_type t638 = xx12Limitation_min(-t484 - t207);
    real_type t640 = xx12Limitation_max(t207 - t484);
    real_type t641 = t616 + t618 + t620 + t622 + t624 + t626 + t628 + t630 + t632 + t634 + t636 + t638 + t640;
    real_type t645 = xx13Limitation_min(-t484 - t181);
    real_type t647 = xx9Limitation_max(t243 - t484);
    real_type t649 = xx10Limitation_min(-t484 - t218);
    real_type t651 = xx10Limitation_max(t218 - t484);
    real_type t653 = xx11Limitation_min(-t484 - t231);
    real_type t655 = xx7Limitation_max(t254 - t484);
    real_type t657 = xx8Limitation_min(-t484 - t270);
    real_type t659 = xx8Limitation_max(t270 - t484);
    real_type t661 = xx9Limitation_min(-t484 - t243);
    real_type t663 = u20Limitation_min(-10 - t118);
    real_type t665 = u20Limitation_max(t118 - 10);
    real_type t667 = xx7Limitation_min(-t484 - t254);
    real_type t668 = t645 + t647 + t649 + t651 + t653 + t655 + t657 + t659 + t661 + t663 + t665 + t667;
    real_type t670 = u17Limitation_max(t154 - 10);
    real_type t672 = u18Limitation_min(-10 - t130);
    real_type t674 = u18Limitation_max(t130 - 10);
    real_type t676 = u19Limitation_min(-10 - t110);
    real_type t678 = u19Limitation_max(t110 - 10);
    real_type t680 = u15Limitation_min(-10 - t166);
    real_type t682 = u15Limitation_max(t166 - 10);
    real_type t684 = u16Limitation_min(-10 - t148);
    real_type t686 = u16Limitation_max(t148 - 10);
    real_type t688 = u17Limitation_min(-10 - t154);
    real_type t690 = u12Limitation_max(t203 - 10);
    real_type t692 = u13Limitation_min(-10 - t184);
    real_type t694 = u13Limitation_max(t184 - 10);
    real_type t695 = t670 + t672 + t674 + t676 + t678 + t680 + t682 + t684 + t686 + t688 + t690 + t692 + t694;
    real_type t698 = u14Limitation_min(-10 - t191);
    real_type t700 = u14Limitation_max(t191 - 10);
    real_type t702 = u10Limitation_min(-10 - t221);
    real_type t704 = u11Limitation_min(-10 - t227);
    real_type t706 = u11Limitation_max(t227 - 10);
    real_type t708 = u12Limitation_min(-10 - t203);
    real_type t710 = u8Limitation_min(-10 - t263);
    real_type t712 = u8Limitation_max(t263 - 10);
    real_type t714 = u9Limitation_min(-10 - t239);
    real_type t716 = u9Limitation_max(t239 - 10);
    real_type t718 = u10Limitation_max(t221 - 10);
    real_type t720 = u6Limitation_max(t278 - 10);
    real_type t721 = t698 + t700 + t702 + t704 + t706 + t708 + t710 + t712 + t714 + t716 + t718 + t720;
    real_type t723 = u7Limitation_min(-10 - t257);
    real_type t725 = u7Limitation_max(t257 - 10);
    real_type t727 = u5Limitation_min(-10 - t302);
    real_type t729 = u5Limitation_max(t302 - 10);
    real_type t731 = u6Limitation_min(-10 - t278);
    real_type t733 = u2Limitation_max(t19 - 10);
    real_type t735 = u3Limitation_min(-10 - t314);
    real_type t737 = u3Limitation_max(t314 - 10);
    real_type t739 = u4Limitation_min(-10 - t296);
    real_type t741 = u4Limitation_max(t296 - 10);
    real_type t743 = u1Limitation_min(-10 - t13);
    real_type t745 = u1Limitation_max(t13 - 10);
    real_type t747 = u2Limitation_min(-10 - t19);
    real_type t748 = t723 + t725 + t727 + t729 + t731 + t733 + t735 + t737 + t739 + t741 + t743 + t745 + t747;
    real_type result__ = t57 + t113 + t187 + t266 + t345 + t450 + t506 + t533 + t561 + t588 + t614 + t641 + t668 + t695 + t721 + t748;
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
