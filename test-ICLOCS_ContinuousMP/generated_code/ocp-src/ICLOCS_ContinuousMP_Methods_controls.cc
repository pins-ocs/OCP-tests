/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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
    real_type t2   = XM__[62];
    real_type t4   = QM__[0];
    real_type t6   = sin(t4 + 2);
    real_type t11  = XM__[63];
    real_type t14  = sin(t4 + 3);
    real_type t19  = XM__[64];
    real_type t22  = sin(t4 + 4);
    real_type t27  = XM__[65];
    real_type t30  = sin(t4 + 5);
    real_type t35  = XM__[66];
    real_type t38  = sin(t4 + 6);
    real_type t43  = XM__[67];
    real_type t46  = sin(t4 + 7);
    real_type t51  = XM__[68];
    real_type t54  = sin(t4 + 8);
    real_type t59  = XM__[69];
    real_type t62  = sin(t4 + 9);
    real_type t67  = XM__[70];
    real_type t70  = sin(t4 + 10);
    real_type t75  = XM__[71];
    real_type t78  = sin(t4 + 11);
    real_type t83  = XM__[72];
    real_type t86  = sin(t4 + 12);
    real_type t91  = XM__[73];
    real_type t94  = sin(t4 + 13);
    real_type t99  = XM__[74];
    real_type t102 = sin(t4 + 14);
    real_type t107 = XM__[75];
    real_type t110 = sin(t4 + 15);
    real_type t115 = XM__[76];
    real_type t118 = sin(t4 + 16);
    real_type t122 = (0.12e1 * t2 + 0.1e0 * t6) * LM__[42] + (0.12e1 * t11 + 0.1e0 * t14) * LM__[43] + (0.12e1 * t19 + 0.1e0 * t22) * LM__[44] + (0.12e1 * t27 + 0.1e0 * t30) * LM__[45] + (0.12e1 * t35 + 0.1e0 * t38) * LM__[46] + (0.12e1 * t43 + 0.1e0 * t46) * LM__[47] + (0.12e1 * t51 + 0.1e0 * t54) * LM__[48] + (0.12e1 * t59 + 0.1e0 * t62) * LM__[49] + (0.12e1 * t67 + 0.1e0 * t70) * LM__[50] + (0.12e1 * t75 + 0.1e0 * t78) * LM__[51] + (0.12e1 * t83 + 0.1e0 * t86) * LM__[52] + (0.12e1 * t91 + 0.1e0 * t94) * LM__[53] + (0.12e1 * t99 + 0.1e0 * t102) * LM__[54] + (0.12e1 * t107 + 0.1e0 * t110) * LM__[55] + (0.12e1 * t115 + 0.1e0 * t118) * LM__[56];
    real_type t124 = XM__[77];
    real_type t127 = sin(t4 + 17);
    real_type t132 = XM__[78];
    real_type t135 = sin(t4 + 18);
    real_type t140 = XM__[79];
    real_type t143 = sin(t4 + 19);
    real_type t148 = XM__[40];
    real_type t149 = sin(t148);
    real_type t151 = P__[iP_u1];
    real_type t155 = XM__[0];
    real_type t156 = sin(t155);
    real_type t160 = XM__[41];
    real_type t161 = sin(t160);
    real_type t163 = P__[iP_u2];
    real_type t167 = XM__[1];
    real_type t168 = sin(t167);
    real_type t172 = XM__[42];
    real_type t173 = sin(t172);
    real_type t175 = P__[iP_u3];
    real_type t179 = XM__[2];
    real_type t180 = sin(t179);
    real_type t184 = XM__[43];
    real_type t185 = sin(t184);
    real_type t187 = P__[iP_u4];
    real_type t191 = XM__[3];
    real_type t192 = sin(t191);
    real_type t196 = XM__[44];
    real_type t197 = sin(t196);
    real_type t199 = P__[iP_u5];
    real_type t203 = XM__[4];
    real_type t204 = sin(t203);
    real_type t208 = XM__[45];
    real_type t209 = sin(t208);
    real_type t211 = P__[iP_u6];
    real_type t215 = XM__[5];
    real_type t216 = sin(t215);
    real_type t219 = (0.12e1 * t124 + 0.1e0 * t127) * LM__[57] + (0.12e1 * t132 + 0.1e0 * t135) * LM__[58] + (0.12e1 * t140 + 0.1e0 * t143) * LM__[59] + (0.2e0 * t149 + t151) * LM__[60] + (t156 + t151) * LM__[20] + (0.2e0 * t161 + t163) * LM__[61] + (t168 + t163) * LM__[21] + (0.2e0 * t173 + t175) * LM__[62] + (t180 + t175) * LM__[22] + (0.2e0 * t185 + t187) * LM__[63] + (t192 + t187) * LM__[23] + (0.2e0 * t197 + t199) * LM__[64] + (t204 + t199) * LM__[24] + (0.2e0 * t209 + t211) * LM__[65] + (t216 + t211) * LM__[25];
    real_type t222 = XM__[46];
    real_type t223 = sin(t222);
    real_type t225 = P__[iP_u7];
    real_type t229 = XM__[6];
    real_type t230 = sin(t229);
    real_type t234 = XM__[47];
    real_type t235 = sin(t234);
    real_type t237 = P__[iP_u8];
    real_type t241 = XM__[7];
    real_type t242 = sin(t241);
    real_type t246 = XM__[48];
    real_type t247 = sin(t246);
    real_type t249 = P__[iP_u9];
    real_type t253 = XM__[8];
    real_type t254 = sin(t253);
    real_type t258 = XM__[49];
    real_type t259 = sin(t258);
    real_type t261 = P__[iP_u10];
    real_type t265 = XM__[9];
    real_type t266 = sin(t265);
    real_type t270 = XM__[50];
    real_type t271 = sin(t270);
    real_type t273 = P__[iP_u11];
    real_type t277 = XM__[10];
    real_type t278 = sin(t277);
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
    real_type t311 = (0.2e0 * t223 + t225) * LM__[66] + (t230 + t225) * LM__[26] + (0.2e0 * t235 + t237) * LM__[67] + (t242 + t237) * LM__[27] + (0.2e0 * t247 + t249) * LM__[68] + (t254 + t249) * LM__[28] + (0.2e0 * t259 + t261) * LM__[69] + (t266 + t261) * LM__[29] + (0.2e0 * t271 + t273) * LM__[70] + (t278 + t273) * LM__[30] + (t283 + t284) * LM__[31] + (0.2e0 * t289 + t284) * LM__[71] + (t295 + t296) * LM__[32] + (0.2e0 * t301 + t296) * LM__[72] + (t307 + t308) * LM__[33];
    real_type t313 = XM__[53];
    real_type t314 = sin(t313);
    real_type t319 = XM__[14];
    real_type t320 = sin(t319);
    real_type t321 = P__[iP_u15];
    real_type t325 = XM__[54];
    real_type t326 = sin(t325);
    real_type t331 = XM__[15];
    real_type t332 = sin(t331);
    real_type t333 = P__[iP_u16];
    real_type t337 = XM__[55];
    real_type t338 = sin(t337);
    real_type t343 = XM__[16];
    real_type t344 = sin(t343);
    real_type t345 = P__[iP_u17];
    real_type t349 = XM__[56];
    real_type t350 = sin(t349);
    real_type t355 = XM__[17];
    real_type t356 = sin(t355);
    real_type t357 = P__[iP_u18];
    real_type t361 = XM__[57];
    real_type t362 = sin(t361);
    real_type t367 = XM__[18];
    real_type t368 = sin(t367);
    real_type t369 = P__[iP_u19];
    real_type t373 = XM__[58];
    real_type t374 = sin(t373);
    real_type t379 = XM__[19];
    real_type t380 = sin(t379);
    real_type t381 = P__[iP_u20];
    real_type t385 = XM__[59];
    real_type t386 = sin(t385);
    real_type t391 = XM__[60];
    real_type t393 = sin(t4);
    real_type t398 = XM__[61];
    real_type t401 = sin(t4 + 1);
    real_type t405 = (0.2e0 * t314 + t308) * LM__[73] + (t320 + t321) * LM__[34] + (0.2e0 * t326 + t321) * LM__[74] + (t332 + t333) * LM__[35] + (0.2e0 * t338 + t333) * LM__[75] + (t344 + t345) * LM__[36] + (0.2e0 * t350 + t345) * LM__[76] + (t356 + t357) * LM__[37] + (0.2e0 * t362 + t357) * LM__[77] + (t368 + t369) * LM__[38] + (0.2e0 * t374 + t369) * LM__[78] + (t380 + t381) * LM__[39] + (0.2e0 * t386 + t381) * LM__[79] + (0.12e1 * t391 + 0.1e0 * t393) * LM__[40] + (0.12e1 * t398 + 0.1e0 * t401) * LM__[41];
    real_type t409 = XM__[20];
    real_type t412 = XM__[21];
    real_type t415 = XM__[22];
    real_type t418 = XM__[23];
    real_type t421 = XM__[24];
    real_type t424 = XM__[25];
    real_type t427 = XM__[26];
    real_type t430 = XM__[27];
    real_type t433 = XM__[28];
    real_type t436 = XM__[29];
    real_type t439 = XM__[30];
    real_type t442 = XM__[31];
    real_type t445 = XM__[32];
    real_type t448 = XM__[33];
    real_type t451 = XM__[34];
    real_type t453 = t409 * LM__[0] + t412 * LM__[1] + t415 * LM__[2] + t418 * LM__[3] + t421 * LM__[4] + t424 * LM__[5] + t427 * LM__[6] + t430 * LM__[7] + t433 * LM__[8] + t436 * LM__[9] + t439 * LM__[10] + t442 * LM__[11] + t445 * LM__[12] + t448 * LM__[13] + t451 * LM__[14];
    real_type t455 = XM__[35];
    real_type t458 = XM__[36];
    real_type t461 = XM__[37];
    real_type t464 = XM__[38];
    real_type t467 = XM__[39];
    real_type t470 = u9Limitation_min(-10 - t249);
    real_type t472 = u9Limitation_max(t249 - 10);
    real_type t474 = u10Limitation_min(-10 - t261);
    real_type t476 = u10Limitation_max(t261 - 10);
    real_type t478 = u11Limitation_min(-10 - t273);
    real_type t479 = ModelPars[iM_xy_bound];
    real_type t481 = yy8Limitation_max(t43 - t479);
    real_type t483 = yy9Limitation_min(-t479 - t51);
    real_type t485 = yy9Limitation_max(t51 - t479);
    real_type t487 = yy10Limitation_min(-t479 - t59);
    real_type t489 = yy10Limitation_max(t59 - t479);
    real_type t490 = t455 * LM__[15] + t458 * LM__[16] + t461 * LM__[17] + t464 * LM__[18] + t467 * LM__[19] + t470 + t472 + t474 + t476 + t478 + t481 + t483 + t485 + t487 + t489;
    real_type t493 = yy11Limitation_min(-t479 - t67);
    real_type t495 = yy11Limitation_max(t67 - t479);
    real_type t497 = yy12Limitation_min(-t479 - t75);
    real_type t499 = yy12Limitation_max(t75 - t479);
    real_type t501 = yy13Limitation_min(-t479 - t83);
    real_type t503 = yy13Limitation_max(t83 - t479);
    real_type t505 = yy14Limitation_min(-t479 - t91);
    real_type t507 = yy14Limitation_max(t91 - t479);
    real_type t509 = xx11Limitation_max(t270 - t479);
    real_type t511 = xx12Limitation_min(-t479 - t288);
    real_type t513 = xx12Limitation_max(t288 - t479);
    real_type t515 = xx13Limitation_min(-t479 - t300);
    real_type t517 = xx13Limitation_max(t300 - t479);
    real_type t519 = yy15Limitation_min(-t479 - t99);
    real_type t521 = yy15Limitation_max(t99 - t479);
    real_type t522 = t493 + t495 + t497 + t499 + t501 + t503 + t505 + t507 + t509 + t511 + t513 + t515 + t517 + t519 + t521;
    real_type t524 = yy16Limitation_min(-t479 - t107);
    real_type t526 = yy16Limitation_max(t107 - t479);
    real_type t528 = yy17Limitation_min(-t479 - t115);
    real_type t530 = yy17Limitation_max(t115 - t479);
    real_type t532 = yy18Limitation_min(-t479 - t124);
    real_type t534 = yy18Limitation_max(t124 - t479);
    real_type t536 = yy19Limitation_min(-t479 - t132);
    real_type t538 = yy19Limitation_max(t132 - t479);
    real_type t540 = u11Limitation_max(t273 - 10);
    real_type t542 = u12Limitation_min(-10 - t284);
    real_type t544 = u12Limitation_max(t284 - 10);
    real_type t546 = u13Limitation_min(-10 - t296);
    real_type t548 = u13Limitation_max(t296 - 10);
    real_type t550 = u3Limitation_min(-10 - t175);
    real_type t552 = u3Limitation_max(t175 - 10);
    real_type t553 = t524 + t526 + t528 + t530 + t532 + t534 + t536 + t538 + t540 + t542 + t544 + t546 + t548 + t550 + t552;
    real_type t558 = u4Limitation_min(-10 - t187);
    real_type t560 = u4Limitation_max(t187 - 10);
    real_type t562 = u5Limitation_min(-10 - t199);
    real_type t564 = u5Limitation_max(t199 - 10);
    real_type t566 = u6Limitation_min(-10 - t211);
    real_type t568 = xx18Limitation_max(t361 - t479);
    real_type t570 = xx19Limitation_min(-t479 - t373);
    real_type t572 = xx19Limitation_max(t373 - t479);
    real_type t574 = xx20Limitation_min(-t479 - t385);
    real_type t576 = xx20Limitation_max(t385 - t479);
    real_type t578 = yy5Limitation_max(t19 - t479);
    real_type t580 = yy6Limitation_min(-t479 - t27);
    real_type t582 = yy6Limitation_max(t27 - t479);
    real_type t584 = yy7Limitation_min(-t479 - t35);
    real_type t586 = yy7Limitation_max(t35 - t479);
    real_type t587 = t558 + t560 + t562 + t564 + t566 + t568 + t570 + t572 + t574 + t576 + t578 + t580 + t582 + t584 + t586;
    real_type t589 = yy1Limitation_min(-t479 - t391);
    real_type t591 = yy1Limitation_max(t391 - t479);
    real_type t593 = yy2Limitation_min(-t479 - t398);
    real_type t595 = yy2Limitation_max(t398 - t479);
    real_type t597 = yy3Limitation_min(-t479 - t2);
    real_type t599 = yy3Limitation_max(t2 - t479);
    real_type t601 = yy4Limitation_min(-t479 - t11);
    real_type t603 = yy4Limitation_max(t11 - t479);
    real_type t605 = yy5Limitation_min(-t479 - t19);
    real_type t607 = yy20Limitation_min(-t479 - t140);
    real_type t609 = yy20Limitation_max(t140 - t479);
    real_type t611 = xx1Limitation_min(-t479 - t148);
    real_type t613 = xx1Limitation_max(t148 - t479);
    real_type t615 = xx9Limitation_min(-t479 - t246);
    real_type t617 = xx9Limitation_max(t246 - t479);
    real_type t618 = t589 + t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613 + t615 + t617;
    real_type t621 = xx10Limitation_min(-t479 - t258);
    real_type t623 = xx10Limitation_max(t258 - t479);
    real_type t625 = xx11Limitation_min(-t479 - t270);
    real_type t627 = u14Limitation_min(-10 - t308);
    real_type t629 = u14Limitation_max(t308 - 10);
    real_type t631 = u15Limitation_min(-10 - t321);
    real_type t633 = u15Limitation_max(t321 - 10);
    real_type t635 = u16Limitation_min(-10 - t333);
    real_type t637 = u16Limitation_max(t333 - 10);
    real_type t639 = yy8Limitation_min(-t479 - t43);
    real_type t640 = t167 * t167;
    real_type t642 = t179 * t179;
    real_type t644 = t191 * t191;
    real_type t646 = t203 * t203;
    real_type t648 = t215 * t215;
    real_type t650 = t621 + t623 + t625 + t627 + t629 + t631 + t633 + t635 + t637 + t639 + 19 * t640 + 18 * t642 + 17 * t644 + 16 * t646 + 15 * t648;
    real_type t651 = t229 * t229;
    real_type t653 = t241 * t241;
    real_type t655 = t253 * t253;
    real_type t657 = t265 * t265;
    real_type t659 = t277 * t277;
    real_type t661 = t282 * t282;
    real_type t663 = t294 * t294;
    real_type t665 = t306 * t306;
    real_type t667 = t319 * t319;
    real_type t669 = t331 * t331;
    real_type t671 = t343 * t343;
    real_type t673 = t355 * t355;
    real_type t675 = t367 * t367;
    real_type t677 = t379 * t379;
    real_type t678 = t409 * t409;
    real_type t680 = 14 * t651 + 13 * t653 + 12 * t655 + 11 * t657 + 10 * t659 + 9 * t661 + 8 * t663 + 7 * t665 + 6 * t667 + 5 * t669 + 4 * t671 + 3 * t673 + 2 * t675 + t677 + 20 * t678;
    real_type t683 = t412 * t412;
    real_type t685 = t415 * t415;
    real_type t687 = t418 * t418;
    real_type t689 = t421 * t421;
    real_type t691 = t424 * t424;
    real_type t693 = t427 * t427;
    real_type t695 = t430 * t430;
    real_type t697 = t433 * t433;
    real_type t699 = t436 * t436;
    real_type t701 = t439 * t439;
    real_type t703 = t442 * t442;
    real_type t706 = u6Limitation_max(t211 - 10);
    real_type t708 = u7Limitation_min(-10 - t225);
    real_type t710 = u7Limitation_max(t225 - 10);
    real_type t712 = u8Limitation_min(-10 - t237);
    real_type t713 = 19 * t683 + 18 * t685 + 17 * t687 + 16 * t689 + 15 * t691 + 14 * t693 + 13 * t695 + 12 * t697 + 11 * t699 + 10 * t701 + 9 * t703 + t706 + t708 + t710 + t712;
    real_type t715 = u8Limitation_max(t237 - 10);
    real_type t717 = xx2Limitation_min(-t479 - t160);
    real_type t719 = xx2Limitation_max(t160 - t479);
    real_type t721 = xx3Limitation_min(-t479 - t172);
    real_type t723 = xx3Limitation_max(t172 - t479);
    real_type t725 = xx4Limitation_min(-t479 - t184);
    real_type t726 = t445 * t445;
    real_type t728 = t448 * t448;
    real_type t730 = t451 * t451;
    real_type t732 = t455 * t455;
    real_type t734 = t458 * t458;
    real_type t736 = t461 * t461;
    real_type t738 = t464 * t464;
    real_type t740 = t467 * t467;
    real_type t741 = t155 * t155;
    real_type t743 = t715 + t717 + t719 + t721 + t723 + t725 + 8 * t726 + 7 * t728 + 6 * t730 + 5 * t732 + 4 * t734 + 3 * t736 + 2 * t738 + t740 + 20 * t741;
    real_type t746 = xx14Limitation_min(-t479 - t313);
    real_type t748 = xx14Limitation_max(t313 - t479);
    real_type t750 = xx15Limitation_min(-t479 - t325);
    real_type t752 = xx15Limitation_max(t325 - t479);
    real_type t754 = xx16Limitation_min(-t479 - t337);
    real_type t756 = xx16Limitation_max(t337 - t479);
    real_type t758 = xx17Limitation_min(-t479 - t349);
    real_type t760 = xx17Limitation_max(t349 - t479);
    real_type t762 = xx18Limitation_min(-t479 - t361);
    real_type t764 = xx4Limitation_max(t184 - t479);
    real_type t766 = xx5Limitation_min(-t479 - t196);
    real_type t768 = xx5Limitation_max(t196 - t479);
    real_type t770 = xx6Limitation_min(-t479 - t208);
    real_type t772 = xx6Limitation_max(t208 - t479);
    real_type t774 = xx7Limitation_min(-t479 - t222);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = xx7Limitation_max(t222 - t479);
    real_type t779 = xx8Limitation_min(-t479 - t234);
    real_type t781 = xx8Limitation_max(t234 - t479);
    real_type t783 = u17Limitation_min(-10 - t345);
    real_type t785 = u17Limitation_max(t345 - 10);
    real_type t787 = u18Limitation_min(-10 - t357);
    real_type t789 = u18Limitation_max(t357 - 10);
    real_type t791 = u19Limitation_max(t369 - 10);
    real_type t793 = u19Limitation_min(-10 - t369);
    real_type t795 = u20Limitation_min(-10 - t381);
    real_type t797 = u20Limitation_max(t381 - 10);
    real_type t799 = u1Limitation_min(-10 - t151);
    real_type t801 = u1Limitation_max(t151 - 10);
    real_type t803 = u2Limitation_min(-10 - t163);
    real_type t805 = u2Limitation_max(t163 - 10);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t122 + t219 + t311 + t405 + t453 + t490 + t522 + t553 + t587 + t618 + t650 + t680 + t713 + t743 + t775 + t806;
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
    real_type t2   = X__[iX_xx8];
    real_type t3   = sin(t2);
    real_type t5   = P__[iP_u8];
    real_type t7   = pow(V__[67] - 0.2e0 * t3 - t5, 2);
    real_type t10  = sin(X__[iX_x8]);
    real_type t12  = pow(V__[27] - t10 - t5, 2);
    real_type t14  = X__[iX_xx9];
    real_type t15  = sin(t14);
    real_type t17  = P__[iP_u9];
    real_type t19  = pow(V__[68] - 0.2e0 * t15 - t17, 2);
    real_type t22  = sin(X__[iX_x9]);
    real_type t24  = pow(V__[28] - t22 - t17, 2);
    real_type t26  = X__[iX_xx10];
    real_type t27  = sin(t26);
    real_type t29  = P__[iP_u10];
    real_type t31  = pow(V__[69] - 0.2e0 * t27 - t29, 2);
    real_type t34  = sin(X__[iX_x10]);
    real_type t36  = pow(V__[29] - t34 - t29, 2);
    real_type t38  = X__[iX_xx11];
    real_type t39  = sin(t38);
    real_type t41  = P__[iP_u11];
    real_type t43  = pow(V__[70] - 0.2e0 * t39 - t41, 2);
    real_type t46  = sin(X__[iX_x11]);
    real_type t48  = pow(V__[30] - t46 - t41, 2);
    real_type t50  = X__[iX_xx12];
    real_type t51  = sin(t50);
    real_type t53  = P__[iP_u12];
    real_type t55  = pow(V__[71] - 0.2e0 * t51 - t53, 2);
    real_type t58  = sin(X__[iX_x12]);
    real_type t60  = pow(V__[31] - t58 - t53, 2);
    real_type t62  = X__[iX_xx13];
    real_type t63  = sin(t62);
    real_type t65  = P__[iP_u13];
    real_type t67  = pow(V__[72] - 0.2e0 * t63 - t65, 2);
    real_type t70  = sin(X__[iX_x13]);
    real_type t72  = pow(V__[32] - t70 - t65, 2);
    real_type t73  = t7 + t12 + t19 + t24 + t31 + t36 + t43 + t48 + t55 + t60 + t67 + t72;
    real_type t75  = X__[iX_xx14];
    real_type t76  = sin(t75);
    real_type t78  = P__[iP_u14];
    real_type t80  = pow(V__[73] - 0.2e0 * t76 - t78, 2);
    real_type t82  = X__[iX_yy9];
    real_type t84  = Q__[iQ_zeta];
    real_type t86  = sin(t84 + 8);
    real_type t89  = pow(V__[48] - 0.12e1 * t82 - 0.1e0 * t86, 2);
    real_type t91  = X__[iX_yy10];
    real_type t94  = sin(t84 + 9);
    real_type t97  = pow(V__[49] - 0.12e1 * t91 - 0.1e0 * t94, 2);
    real_type t99  = X__[iX_yy11];
    real_type t102 = sin(t84 + 10);
    real_type t105 = pow(V__[50] - 0.12e1 * t99 - 0.1e0 * t102, 2);
    real_type t107 = X__[iX_yy12];
    real_type t110 = sin(t84 + 11);
    real_type t113 = pow(V__[51] - 0.12e1 * t107 - 0.1e0 * t110, 2);
    real_type t115 = X__[iX_yy13];
    real_type t118 = sin(t84 + 12);
    real_type t121 = pow(V__[52] - 0.12e1 * t115 - 0.1e0 * t118, 2);
    real_type t123 = X__[iX_yy14];
    real_type t126 = sin(t84 + 13);
    real_type t129 = pow(V__[53] - 0.12e1 * t123 - 0.1e0 * t126, 2);
    real_type t131 = X__[iX_yy15];
    real_type t134 = sin(t84 + 14);
    real_type t137 = pow(V__[54] - 0.12e1 * t131 - 0.1e0 * t134, 2);
    real_type t139 = X__[iX_yy16];
    real_type t142 = sin(t84 + 15);
    real_type t145 = pow(V__[55] - 0.12e1 * t139 - 0.1e0 * t142, 2);
    real_type t147 = X__[iX_yy17];
    real_type t150 = sin(t84 + 16);
    real_type t153 = pow(V__[56] - 0.12e1 * t147 - 0.1e0 * t150, 2);
    real_type t155 = X__[iX_yy18];
    real_type t158 = sin(t84 + 17);
    real_type t161 = pow(V__[57] - 0.12e1 * t155 - 0.1e0 * t158, 2);
    real_type t163 = X__[iX_yy19];
    real_type t166 = sin(t84 + 18);
    real_type t169 = pow(V__[58] - 0.12e1 * t163 - 0.1e0 * t166, 2);
    real_type t171 = X__[iX_yy20];
    real_type t174 = sin(t84 + 19);
    real_type t177 = pow(V__[59] - 0.12e1 * t171 - 0.1e0 * t174, 2);
    real_type t178 = t80 + t89 + t97 + t105 + t113 + t121 + t129 + t137 + t145 + t153 + t161 + t169 + t177;
    real_type t181 = X__[iX_yy1];
    real_type t183 = sin(t84);
    real_type t186 = pow(V__[40] - 0.12e1 * t181 - 0.1e0 * t183, 2);
    real_type t188 = X__[iX_yy2];
    real_type t191 = sin(t84 + 1);
    real_type t194 = pow(V__[41] - 0.12e1 * t188 - 0.1e0 * t191, 2);
    real_type t196 = X__[iX_yy3];
    real_type t199 = sin(t84 + 2);
    real_type t202 = pow(V__[42] - 0.12e1 * t196 - 0.1e0 * t199, 2);
    real_type t204 = X__[iX_yy4];
    real_type t207 = sin(t84 + 3);
    real_type t210 = pow(V__[43] - 0.12e1 * t204 - 0.1e0 * t207, 2);
    real_type t212 = X__[iX_yy5];
    real_type t215 = sin(t84 + 4);
    real_type t218 = pow(V__[44] - 0.12e1 * t212 - 0.1e0 * t215, 2);
    real_type t220 = X__[iX_xx1];
    real_type t221 = sin(t220);
    real_type t223 = P__[iP_u1];
    real_type t225 = pow(V__[60] - 0.2e0 * t221 - t223, 2);
    real_type t228 = sin(X__[iX_x1]);
    real_type t230 = pow(V__[20] - t228 - t223, 2);
    real_type t232 = X__[iX_xx2];
    real_type t233 = sin(t232);
    real_type t235 = P__[iP_u2];
    real_type t237 = pow(V__[61] - 0.2e0 * t233 - t235, 2);
    real_type t240 = sin(X__[iX_x2]);
    real_type t242 = pow(V__[21] - t240 - t235, 2);
    real_type t244 = X__[iX_xx3];
    real_type t245 = sin(t244);
    real_type t247 = P__[iP_u3];
    real_type t249 = pow(V__[62] - 0.2e0 * t245 - t247, 2);
    real_type t252 = sin(X__[iX_x3]);
    real_type t254 = pow(V__[22] - t252 - t247, 2);
    real_type t256 = X__[iX_xx4];
    real_type t257 = sin(t256);
    real_type t259 = P__[iP_u4];
    real_type t261 = pow(V__[63] - 0.2e0 * t257 - t259, 2);
    real_type t262 = t186 + t194 + t202 + t210 + t218 + t225 + t230 + t237 + t242 + t249 + t254 + t261;
    real_type t265 = sin(X__[iX_x4]);
    real_type t267 = pow(V__[23] - t265 - t259, 2);
    real_type t269 = X__[iX_xx5];
    real_type t270 = sin(t269);
    real_type t272 = P__[iP_u5];
    real_type t274 = pow(V__[64] - 0.2e0 * t270 - t272, 2);
    real_type t278 = pow(V__[13] - X__[iX_y14], 2);
    real_type t282 = pow(V__[14] - X__[iX_y15], 2);
    real_type t286 = pow(V__[15] - X__[iX_y16], 2);
    real_type t290 = pow(V__[16] - X__[iX_y17], 2);
    real_type t293 = sin(X__[iX_x19]);
    real_type t294 = P__[iP_u19];
    real_type t296 = pow(V__[38] - t293 - t294, 2);
    real_type t298 = X__[iX_xx20];
    real_type t299 = sin(t298);
    real_type t301 = P__[iP_u20];
    real_type t303 = pow(V__[79] - 0.2e0 * t299 - t301, 2);
    real_type t306 = sin(X__[iX_x5]);
    real_type t308 = pow(V__[24] - t306 - t272, 2);
    real_type t310 = X__[iX_xx6];
    real_type t311 = sin(t310);
    real_type t313 = P__[iP_u6];
    real_type t315 = pow(V__[65] - 0.2e0 * t311 - t313, 2);
    real_type t318 = sin(X__[iX_x6]);
    real_type t320 = pow(V__[25] - t318 - t313, 2);
    real_type t322 = X__[iX_yy7];
    real_type t325 = sin(t84 + 6);
    real_type t328 = pow(V__[46] - 0.12e1 * t322 - 0.1e0 * t325, 2);
    real_type t330 = X__[iX_yy8];
    real_type t333 = sin(t84 + 7);
    real_type t336 = pow(V__[47] - 0.12e1 * t330 - 0.1e0 * t333, 2);
    real_type t337 = t267 + t274 + t278 + t282 + t286 + t290 + t296 + t303 + t308 + t315 + t320 + t328 + t336;
    real_type t341 = X__[iX_yy6];
    real_type t344 = sin(t84 + 5);
    real_type t347 = pow(V__[45] - 0.12e1 * t341 - 0.1e0 * t344, 2);
    real_type t349 = X__[iX_xx18];
    real_type t350 = sin(t349);
    real_type t352 = P__[iP_u18];
    real_type t354 = pow(V__[77] - 0.2e0 * t350 - t352, 2);
    real_type t357 = sin(X__[iX_x18]);
    real_type t359 = pow(V__[37] - t357 - t352, 2);
    real_type t361 = X__[iX_xx19];
    real_type t362 = sin(t361);
    real_type t365 = pow(V__[78] - 0.2e0 * t362 - t294, 2);
    real_type t367 = X__[iX_xx17];
    real_type t368 = sin(t367);
    real_type t370 = P__[iP_u17];
    real_type t372 = pow(V__[76] - 0.2e0 * t368 - t370, 2);
    real_type t375 = sin(X__[iX_x17]);
    real_type t377 = pow(V__[36] - t375 - t370, 2);
    real_type t380 = sin(X__[iX_x15]);
    real_type t381 = P__[iP_u15];
    real_type t383 = pow(V__[34] - t380 - t381, 2);
    real_type t385 = X__[iX_xx16];
    real_type t386 = sin(t385);
    real_type t388 = P__[iP_u16];
    real_type t390 = pow(V__[75] - 0.2e0 * t386 - t388, 2);
    real_type t393 = sin(X__[iX_x16]);
    real_type t395 = pow(V__[35] - t393 - t388, 2);
    real_type t398 = sin(X__[iX_x14]);
    real_type t400 = pow(V__[33] - t398 - t78, 2);
    real_type t402 = X__[iX_xx15];
    real_type t403 = sin(t402);
    real_type t406 = pow(V__[74] - 0.2e0 * t403 - t381, 2);
    real_type t410 = pow(V__[10] - X__[iX_y11], 2);
    real_type t411 = t347 + t354 + t359 + t365 + t372 + t377 + t383 + t390 + t395 + t400 + t406 + t410;
    real_type t415 = pow(V__[11] - X__[iX_y12], 2);
    real_type t419 = pow(V__[12] - X__[iX_y13], 2);
    real_type t423 = pow(V__[6] - X__[iX_y7], 2);
    real_type t427 = pow(V__[7] - X__[iX_y8], 2);
    real_type t431 = pow(V__[8] - X__[iX_y9], 2);
    real_type t435 = pow(V__[9] - X__[iX_y10], 2);
    real_type t439 = pow(V__[2] - X__[iX_y3], 2);
    real_type t443 = pow(V__[3] - X__[iX_y4], 2);
    real_type t447 = pow(V__[4] - X__[iX_y5], 2);
    real_type t451 = pow(V__[5] - X__[iX_y6], 2);
    real_type t454 = sin(X__[iX_x20]);
    real_type t456 = pow(V__[39] - t454 - t301, 2);
    real_type t460 = pow(V__[0] - X__[iX_y1], 2);
    real_type t464 = pow(V__[1] - X__[iX_y2], 2);
    real_type t465 = t415 + t419 + t423 + t427 + t431 + t435 + t439 + t443 + t447 + t451 + t456 + t460 + t464;
    real_type t468 = X__[iX_xx7];
    real_type t469 = sin(t468);
    real_type t471 = P__[iP_u7];
    real_type t473 = pow(V__[66] - 0.2e0 * t469 - t471, 2);
    real_type t476 = sin(X__[iX_x7]);
    real_type t478 = pow(V__[26] - t476 - t471, 2);
    real_type t482 = pow(V__[17] - X__[iX_y18], 2);
    real_type t486 = pow(V__[18] - X__[iX_y19], 2);
    real_type t490 = pow(V__[19] - X__[iX_y20], 2);
    real_type t491 = ModelPars[iM_xy_bound];
    real_type t493 = yy20Limitation_min(-t491 - t171);
    real_type t495 = yy20Limitation_max(t171 - t491);
    real_type t497 = yy19Limitation_min(-t491 - t163);
    real_type t499 = yy19Limitation_max(t163 - t491);
    real_type t501 = yy17Limitation_min(-t491 - t147);
    real_type t503 = yy17Limitation_max(t147 - t491);
    real_type t505 = yy18Limitation_min(-t491 - t155);
    real_type t506 = t473 + t478 + t482 + t486 + t490 + t493 + t495 + t497 + t499 + t501 + t503 + t505;
    real_type t508 = yy18Limitation_max(t155 - t491);
    real_type t510 = yy16Limitation_min(-t491 - t139);
    real_type t512 = yy16Limitation_max(t139 - t491);
    real_type t514 = yy14Limitation_max(t123 - t491);
    real_type t516 = yy15Limitation_min(-t491 - t131);
    real_type t518 = yy15Limitation_max(t131 - t491);
    real_type t520 = yy12Limitation_max(t107 - t491);
    real_type t522 = yy13Limitation_min(-t491 - t115);
    real_type t524 = yy13Limitation_max(t115 - t491);
    real_type t526 = yy14Limitation_min(-t491 - t123);
    real_type t528 = yy12Limitation_min(-t491 - t107);
    real_type t530 = yy10Limitation_max(t91 - t491);
    real_type t532 = yy11Limitation_min(-t491 - t99);
    real_type t533 = t508 + t510 + t512 + t514 + t516 + t518 + t520 + t522 + t524 + t526 + t528 + t530 + t532;
    real_type t538 = yy11Limitation_max(t99 - t491);
    real_type t540 = yy9Limitation_max(t82 - t491);
    real_type t542 = yy10Limitation_min(-t491 - t91);
    real_type t544 = yy8Limitation_min(-t491 - t330);
    real_type t546 = yy8Limitation_max(t330 - t491);
    real_type t548 = yy9Limitation_min(-t491 - t82);
    real_type t550 = yy7Limitation_min(-t491 - t322);
    real_type t552 = yy7Limitation_max(t322 - t491);
    real_type t554 = yy6Limitation_min(-t491 - t341);
    real_type t556 = yy6Limitation_max(t341 - t491);
    real_type t558 = yy4Limitation_max(t204 - t491);
    real_type t560 = yy5Limitation_min(-t491 - t212);
    real_type t561 = t538 + t540 + t542 + t544 + t546 + t548 + t550 + t552 + t554 + t556 + t558 + t560;
    real_type t563 = yy5Limitation_max(t212 - t491);
    real_type t565 = yy3Limitation_max(t196 - t491);
    real_type t567 = yy4Limitation_min(-t491 - t204);
    real_type t569 = yy2Limitation_min(-t491 - t188);
    real_type t571 = yy2Limitation_max(t188 - t491);
    real_type t573 = yy3Limitation_min(-t491 - t196);
    real_type t575 = xx20Limitation_max(t298 - t491);
    real_type t577 = yy1Limitation_min(-t491 - t181);
    real_type t579 = yy1Limitation_max(t181 - t491);
    real_type t581 = xx20Limitation_min(-t491 - t298);
    real_type t583 = xx18Limitation_min(-t491 - t349);
    real_type t585 = xx18Limitation_max(t349 - t491);
    real_type t587 = xx19Limitation_min(-t491 - t361);
    real_type t588 = t563 + t565 + t567 + t569 + t571 + t573 + t575 + t577 + t579 + t581 + t583 + t585 + t587;
    real_type t591 = xx19Limitation_max(t361 - t491);
    real_type t593 = xx16Limitation_min(-t491 - t385);
    real_type t595 = xx16Limitation_max(t385 - t491);
    real_type t597 = xx17Limitation_min(-t491 - t367);
    real_type t599 = xx17Limitation_max(t367 - t491);
    real_type t601 = xx14Limitation_min(-t491 - t75);
    real_type t603 = xx14Limitation_max(t75 - t491);
    real_type t605 = xx15Limitation_min(-t491 - t402);
    real_type t607 = xx15Limitation_max(t402 - t491);
    real_type t609 = xx11Limitation_max(t38 - t491);
    real_type t611 = xx12Limitation_min(-t491 - t50);
    real_type t613 = xx12Limitation_max(t50 - t491);
    real_type t614 = t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613;
    real_type t616 = xx13Limitation_min(-t491 - t62);
    real_type t618 = xx13Limitation_max(t62 - t491);
    real_type t620 = xx9Limitation_max(t14 - t491);
    real_type t622 = xx10Limitation_min(-t491 - t26);
    real_type t624 = xx10Limitation_max(t26 - t491);
    real_type t626 = xx11Limitation_min(-t491 - t38);
    real_type t628 = xx7Limitation_max(t468 - t491);
    real_type t630 = xx8Limitation_min(-t491 - t2);
    real_type t632 = xx8Limitation_max(t2 - t491);
    real_type t634 = xx9Limitation_min(-t491 - t14);
    real_type t636 = xx5Limitation_max(t269 - t491);
    real_type t638 = xx6Limitation_min(-t491 - t310);
    real_type t640 = xx6Limitation_max(t310 - t491);
    real_type t641 = t616 + t618 + t620 + t622 + t624 + t626 + t628 + t630 + t632 + t634 + t636 + t638 + t640;
    real_type t645 = xx7Limitation_min(-t491 - t468);
    real_type t647 = xx3Limitation_max(t244 - t491);
    real_type t649 = xx4Limitation_min(-t491 - t256);
    real_type t651 = xx4Limitation_max(t256 - t491);
    real_type t653 = xx5Limitation_min(-t491 - t269);
    real_type t655 = xx1Limitation_min(-t491 - t220);
    real_type t657 = xx1Limitation_max(t220 - t491);
    real_type t659 = xx2Limitation_min(-t491 - t232);
    real_type t661 = xx2Limitation_max(t232 - t491);
    real_type t663 = xx3Limitation_min(-t491 - t244);
    real_type t665 = u4Limitation_max(t259 - 10);
    real_type t667 = u5Limitation_min(-10 - t272);
    real_type t668 = t645 + t647 + t649 + t651 + t653 + t655 + t657 + t659 + t661 + t663 + t665 + t667;
    real_type t670 = u5Limitation_max(t272 - 10);
    real_type t672 = u6Limitation_min(-10 - t313);
    real_type t674 = u2Limitation_min(-10 - t235);
    real_type t676 = u2Limitation_max(t235 - 10);
    real_type t678 = u3Limitation_min(-10 - t247);
    real_type t680 = u3Limitation_max(t247 - 10);
    real_type t682 = u4Limitation_min(-10 - t259);
    real_type t684 = u19Limitation_min(-10 - t294);
    real_type t686 = u20Limitation_min(-10 - t301);
    real_type t688 = u20Limitation_max(t301 - 10);
    real_type t690 = u1Limitation_min(-10 - t223);
    real_type t692 = u1Limitation_max(t223 - 10);
    real_type t694 = u16Limitation_max(t388 - 10);
    real_type t695 = t670 + t672 + t674 + t676 + t678 + t680 + t682 + t684 + t686 + t688 + t690 + t692 + t694;
    real_type t698 = u17Limitation_min(-10 - t370);
    real_type t700 = u17Limitation_max(t370 - 10);
    real_type t702 = u18Limitation_min(-10 - t352);
    real_type t704 = u18Limitation_max(t352 - 10);
    real_type t706 = u19Limitation_max(t294 - 10);
    real_type t708 = u14Limitation_min(-10 - t78);
    real_type t710 = u14Limitation_max(t78 - 10);
    real_type t712 = u15Limitation_min(-10 - t381);
    real_type t714 = u15Limitation_max(t381 - 10);
    real_type t716 = u16Limitation_min(-10 - t388);
    real_type t718 = u11Limitation_min(-10 - t41);
    real_type t720 = u11Limitation_max(t41 - 10);
    real_type t721 = t698 + t700 + t702 + t704 + t706 + t708 + t710 + t712 + t714 + t716 + t718 + t720;
    real_type t723 = u12Limitation_min(-10 - t53);
    real_type t725 = u12Limitation_max(t53 - 10);
    real_type t727 = u13Limitation_min(-10 - t65);
    real_type t729 = u13Limitation_max(t65 - 10);
    real_type t731 = u8Limitation_max(t5 - 10);
    real_type t733 = u9Limitation_min(-10 - t17);
    real_type t735 = u9Limitation_max(t17 - 10);
    real_type t737 = u10Limitation_min(-10 - t29);
    real_type t739 = u10Limitation_max(t29 - 10);
    real_type t741 = u6Limitation_max(t313 - 10);
    real_type t743 = u7Limitation_min(-10 - t471);
    real_type t745 = u7Limitation_max(t471 - 10);
    real_type t747 = u8Limitation_min(-10 - t5);
    real_type t748 = t723 + t725 + t727 + t729 + t731 + t733 + t735 + t737 + t739 + t741 + t743 + t745 + t747;
    real_type result__ = t73 + t178 + t262 + t337 + t411 + t465 + t506 + t533 + t561 + t588 + t614 + t641 + t668 + t695 + t721 + t748;
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
