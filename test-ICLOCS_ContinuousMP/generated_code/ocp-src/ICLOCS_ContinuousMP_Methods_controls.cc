/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
    real_type t1   = P__[iP_u20];
    real_type t3   = u20Limitation_min(-10 - t1);
    real_type t5   = u20Limitation_max(t1 - 10);
    real_type t6   = P__[iP_u18];
    real_type t8   = u18Limitation_min(-10 - t6);
    real_type t10  = u18Limitation_max(t6 - 10);
    real_type t11  = P__[iP_u19];
    real_type t13  = u19Limitation_min(-10 - t11);
    real_type t15  = u19Limitation_max(t11 - 10);
    real_type t16  = P__[iP_u16];
    real_type t18  = u16Limitation_min(-10 - t16);
    real_type t20  = u16Limitation_max(t16 - 10);
    real_type t21  = P__[iP_u17];
    real_type t23  = u17Limitation_min(-10 - t21);
    real_type t25  = u17Limitation_max(t21 - 10);
    real_type t26  = P__[iP_u14];
    real_type t28  = u14Limitation_max(t26 - 10);
    real_type t29  = P__[iP_u15];
    real_type t31  = u15Limitation_min(-10 - t29);
    real_type t33  = u15Limitation_max(t29 - 10);
    real_type t34  = t3 + t5 + t8 + t10 + t13 + t15 + t18 + t20 + t23 + t25 + t28 + t31 + t33;
    real_type t36  = P__[iP_u12];
    real_type t38  = u12Limitation_max(t36 - 10);
    real_type t39  = P__[iP_u13];
    real_type t41  = u13Limitation_min(-10 - t39);
    real_type t43  = u13Limitation_max(t39 - 10);
    real_type t45  = u14Limitation_min(-10 - t26);
    real_type t46  = P__[iP_u11];
    real_type t48  = u11Limitation_min(-10 - t46);
    real_type t50  = u11Limitation_max(t46 - 10);
    real_type t52  = u12Limitation_min(-10 - t36);
    real_type t53  = P__[iP_u9];
    real_type t55  = u9Limitation_min(-10 - t53);
    real_type t57  = u9Limitation_max(t53 - 10);
    real_type t58  = P__[iP_u10];
    real_type t60  = u10Limitation_min(-10 - t58);
    real_type t62  = u10Limitation_max(t58 - 10);
    real_type t63  = P__[iP_u7];
    real_type t65  = u7Limitation_min(-10 - t63);
    real_type t67  = u7Limitation_max(t63 - 10);
    real_type t68  = P__[iP_u8];
    real_type t70  = u8Limitation_min(-10 - t68);
    real_type t71  = t38 + t41 + t43 + t45 + t48 + t50 + t52 + t55 + t57 + t60 + t62 + t65 + t67 + t70;
    real_type t75  = u8Limitation_max(t68 - 10);
    real_type t77  = ModelPars[iM_xy_bound];
    real_type t78  = XL__[iX_yy9];
    real_type t80  = yy9Limitation_min(-t77 - t78);
    real_type t82  = yy9Limitation_max(t78 - t77);
    real_type t83  = XL__[iX_yy10];
    real_type t85  = yy10Limitation_min(-t77 - t83);
    real_type t87  = yy10Limitation_max(t83 - t77);
    real_type t88  = XL__[iX_yy11];
    real_type t90  = yy11Limitation_min(-t77 - t88);
    real_type t91  = XL__[iX_yy7];
    real_type t93  = yy7Limitation_min(-t77 - t91);
    real_type t95  = yy7Limitation_max(t91 - t77);
    real_type t96  = XL__[iX_yy8];
    real_type t98  = yy8Limitation_min(-t77 - t96);
    real_type t100 = yy8Limitation_max(t96 - t77);
    real_type t101 = XL__[iX_yy5];
    real_type t103 = yy5Limitation_min(-t77 - t101);
    real_type t105 = yy5Limitation_max(t101 - t77);
    real_type t106 = XL__[iX_yy6];
    real_type t108 = yy6Limitation_min(-t77 - t106);
    real_type t110 = yy6Limitation_max(t106 - t77);
    real_type t111 = 2 * t75 + t80 + t82 + t85 + t87 + t90 + t93 + t95 + t98 + t100 + t103 + t105 + t108 + t110;
    real_type t112 = XL__[iX_yy3];
    real_type t114 = yy3Limitation_min(-t77 - t112);
    real_type t116 = yy3Limitation_max(t112 - t77);
    real_type t117 = XL__[iX_yy4];
    real_type t119 = yy4Limitation_min(-t77 - t117);
    real_type t121 = yy4Limitation_max(t117 - t77);
    real_type t122 = XL__[iX_yy2];
    real_type t124 = yy2Limitation_min(-t77 - t122);
    real_type t126 = yy2Limitation_max(t122 - t77);
    real_type t127 = XL__[iX_x15];
    real_type t128 = t127 * t127;
    real_type t130 = XL__[iX_x16];
    real_type t131 = t130 * t130;
    real_type t133 = XL__[iX_x17];
    real_type t134 = t133 * t133;
    real_type t136 = XL__[iX_x9];
    real_type t137 = t136 * t136;
    real_type t139 = XL__[iX_x10];
    real_type t140 = t139 * t139;
    real_type t142 = XL__[iX_x11];
    real_type t143 = t142 * t142;
    real_type t145 = XL__[iX_x12];
    real_type t146 = t145 * t145;
    real_type t148 = XL__[iX_x13];
    real_type t149 = t148 * t148;
    real_type t151 = t114 + t116 + t119 + t121 + t124 + t126 + 6 * t128 + 5 * t131 + 4 * t134 + 12 * t137 + 11 * t140 + 10 * t143 + 9 * t146 + 8 * t149;
    real_type t154 = XL__[iX_x1];
    real_type t155 = t154 * t154;
    real_type t157 = XL__[iX_x2];
    real_type t158 = t157 * t157;
    real_type t160 = XL__[iX_x3];
    real_type t161 = t160 * t160;
    real_type t163 = XL__[iX_x4];
    real_type t164 = t163 * t163;
    real_type t166 = XL__[iX_x5];
    real_type t167 = t166 * t166;
    real_type t169 = XL__[iX_x6];
    real_type t170 = t169 * t169;
    real_type t172 = XL__[iX_x7];
    real_type t173 = t172 * t172;
    real_type t175 = XL__[iX_x8];
    real_type t176 = t175 * t175;
    real_type t178 = XL__[iX_x14];
    real_type t179 = t178 * t178;
    real_type t181 = XL__[iX_x20];
    real_type t182 = t181 * t181;
    real_type t183 = XL__[iX_y1];
    real_type t184 = t183 * t183;
    real_type t186 = XL__[iX_y2];
    real_type t187 = t186 * t186;
    real_type t189 = XL__[iX_y3];
    real_type t190 = t189 * t189;
    real_type t192 = 20 * t155 + 19 * t158 + 18 * t161 + 17 * t164 + 16 * t167 + 15 * t170 + 14 * t173 + 13 * t176 + 7 * t179 + t182 + 20 * t184 + 19 * t187 + 18 * t190;
    real_type t193 = XL__[iX_y4];
    real_type t194 = t193 * t193;
    real_type t196 = XL__[iX_y8];
    real_type t197 = t196 * t196;
    real_type t199 = XL__[iX_y9];
    real_type t200 = t199 * t199;
    real_type t202 = XL__[iX_y10];
    real_type t203 = t202 * t202;
    real_type t205 = XL__[iX_y11];
    real_type t206 = t205 * t205;
    real_type t208 = XL__[iX_y12];
    real_type t209 = t208 * t208;
    real_type t211 = XL__[iX_y13];
    real_type t212 = t211 * t211;
    real_type t214 = XL__[iX_y14];
    real_type t215 = t214 * t214;
    real_type t217 = XL__[iX_y15];
    real_type t218 = t217 * t217;
    real_type t220 = XL__[iX_y16];
    real_type t221 = t220 * t220;
    real_type t223 = XL__[iX_y17];
    real_type t224 = t223 * t223;
    real_type t226 = XL__[iX_y18];
    real_type t227 = t226 * t226;
    real_type t229 = XL__[iX_y19];
    real_type t230 = t229 * t229;
    real_type t232 = XL__[iX_y20];
    real_type t233 = t232 * t232;
    real_type t234 = 17 * t194 + 13 * t197 + 12 * t200 + 11 * t203 + 10 * t206 + 9 * t209 + 8 * t212 + 7 * t215 + 6 * t218 + 5 * t221 + 4 * t224 + 3 * t227 + 2 * t230 + t233;
    real_type t236 = XL__[iX_x18];
    real_type t237 = t236 * t236;
    real_type t239 = XL__[iX_x19];
    real_type t240 = t239 * t239;
    real_type t242 = XL__[iX_y5];
    real_type t243 = t242 * t242;
    real_type t245 = XL__[iX_y6];
    real_type t246 = t245 * t245;
    real_type t248 = XL__[iX_y7];
    real_type t249 = t248 * t248;
    real_type t251 = XR__[iX_x1];
    real_type t252 = t251 * t251;
    real_type t254 = XR__[iX_x2];
    real_type t255 = t254 * t254;
    real_type t257 = XR__[iX_x3];
    real_type t258 = t257 * t257;
    real_type t260 = XR__[iX_x4];
    real_type t261 = t260 * t260;
    real_type t263 = XR__[iX_x5];
    real_type t264 = t263 * t263;
    real_type t266 = XR__[iX_x6];
    real_type t267 = t266 * t266;
    real_type t269 = XR__[iX_x7];
    real_type t270 = t269 * t269;
    real_type t272 = XR__[iX_x8];
    real_type t273 = t272 * t272;
    real_type t275 = XR__[iX_x9];
    real_type t276 = t275 * t275;
    real_type t278 = 3 * t237 + 2 * t240 + 16 * t243 + 15 * t246 + 14 * t249 + 20 * t252 + 19 * t255 + 18 * t258 + 17 * t261 + 16 * t264 + 15 * t267 + 14 * t270 + 13 * t273 + 12 * t276;
    real_type t279 = XR__[iX_x10];
    real_type t280 = t279 * t279;
    real_type t282 = XR__[iX_x11];
    real_type t283 = t282 * t282;
    real_type t285 = XR__[iX_x12];
    real_type t286 = t285 * t285;
    real_type t288 = XR__[iX_x13];
    real_type t289 = t288 * t288;
    real_type t291 = XR__[iX_x14];
    real_type t292 = t291 * t291;
    real_type t294 = XR__[iX_x15];
    real_type t295 = t294 * t294;
    real_type t297 = XR__[iX_x16];
    real_type t298 = t297 * t297;
    real_type t300 = XR__[iX_y13];
    real_type t301 = t300 * t300;
    real_type t303 = XR__[iX_y14];
    real_type t304 = t303 * t303;
    real_type t306 = XR__[iX_y15];
    real_type t307 = t306 * t306;
    real_type t309 = XR__[iX_y16];
    real_type t310 = t309 * t309;
    real_type t312 = XR__[iX_y17];
    real_type t313 = t312 * t312;
    real_type t315 = XR__[iX_y18];
    real_type t316 = t315 * t315;
    real_type t318 = XR__[iX_y19];
    real_type t319 = t318 * t318;
    real_type t321 = 11 * t280 + 10 * t283 + 9 * t286 + 8 * t289 + 7 * t292 + 6 * t295 + 5 * t298 + 8 * t301 + 7 * t304 + 6 * t307 + 5 * t310 + 4 * t313 + 3 * t316 + 2 * t319;
    real_type t325 = XR__[iX_x18];
    real_type t326 = t325 * t325;
    real_type t328 = XR__[iX_x19];
    real_type t329 = t328 * t328;
    real_type t331 = XR__[iX_x20];
    real_type t332 = t331 * t331;
    real_type t333 = XR__[iX_y1];
    real_type t334 = t333 * t333;
    real_type t336 = XR__[iX_y5];
    real_type t337 = t336 * t336;
    real_type t339 = XR__[iX_y6];
    real_type t340 = t339 * t339;
    real_type t342 = XR__[iX_y7];
    real_type t343 = t342 * t342;
    real_type t345 = XR__[iX_y8];
    real_type t346 = t345 * t345;
    real_type t348 = XR__[iX_y9];
    real_type t349 = t348 * t348;
    real_type t351 = XR__[iX_y10];
    real_type t352 = t351 * t351;
    real_type t354 = XR__[iX_y11];
    real_type t355 = t354 * t354;
    real_type t357 = XR__[iX_y12];
    real_type t358 = t357 * t357;
    real_type t360 = XR__[iX_y20];
    real_type t361 = t360 * t360;
    real_type t362 = 3 * t326 + 2 * t329 + t332 + 20 * t334 + 16 * t337 + 15 * t340 + 14 * t343 + 13 * t346 + 12 * t349 + 11 * t352 + 10 * t355 + 9 * t358 + t361;
    real_type t363 = XR__[iX_y2];
    real_type t364 = t363 * t363;
    real_type t366 = XR__[iX_y3];
    real_type t367 = t366 * t366;
    real_type t369 = XR__[iX_y4];
    real_type t370 = t369 * t369;
    real_type t372 = XL__[iX_xx19];
    real_type t374 = xx19Limitation_max(t372 - t77);
    real_type t375 = XL__[iX_xx20];
    real_type t377 = xx20Limitation_min(-t77 - t375);
    real_type t379 = xx20Limitation_max(t375 - t77);
    real_type t380 = XL__[iX_yy1];
    real_type t382 = yy1Limitation_min(-t77 - t380);
    real_type t384 = yy1Limitation_max(t380 - t77);
    real_type t385 = XR__[iX_x17];
    real_type t386 = t385 * t385;
    real_type t388 = XL__[iX_xx17];
    real_type t390 = xx17Limitation_min(-t77 - t388);
    real_type t392 = xx17Limitation_max(t388 - t77);
    real_type t393 = XL__[iX_xx18];
    real_type t395 = xx18Limitation_min(-t77 - t393);
    real_type t397 = xx18Limitation_max(t393 - t77);
    real_type t399 = xx19Limitation_min(-t77 - t372);
    real_type t400 = 19 * t364 + 18 * t367 + 17 * t370 + t374 + t377 + t379 + t382 + t384 + 4 * t386 + t390 + t392 + t395 + t397 + t399;
    real_type t402 = XL__[iX_xx15];
    real_type t404 = xx15Limitation_max(t402 - t77);
    real_type t405 = XL__[iX_xx16];
    real_type t407 = xx16Limitation_min(-t77 - t405);
    real_type t409 = xx16Limitation_max(t405 - t77);
    real_type t410 = XL__[iX_xx14];
    real_type t412 = xx14Limitation_min(-t77 - t410);
    real_type t414 = xx14Limitation_max(t410 - t77);
    real_type t416 = xx15Limitation_min(-t77 - t402);
    real_type t417 = XL__[iX_xx11];
    real_type t419 = xx11Limitation_min(-t77 - t417);
    real_type t421 = xx11Limitation_max(t417 - t77);
    real_type t422 = XL__[iX_xx12];
    real_type t424 = xx12Limitation_min(-t77 - t422);
    real_type t426 = xx12Limitation_max(t422 - t77);
    real_type t427 = XL__[iX_xx13];
    real_type t429 = xx13Limitation_min(-t77 - t427);
    real_type t431 = xx13Limitation_max(t427 - t77);
    real_type t432 = XL__[iX_xx9];
    real_type t434 = xx9Limitation_min(-t77 - t432);
    real_type t436 = xx9Limitation_max(t432 - t77);
    real_type t437 = t404 + t407 + t409 + t412 + t414 + t416 + t419 + t421 + t424 + t426 + t429 + t431 + t434 + t436;
    real_type t438 = XL__[iX_xx10];
    real_type t440 = xx10Limitation_min(-t77 - t438);
    real_type t442 = xx10Limitation_max(t438 - t77);
    real_type t443 = XL__[iX_xx6];
    real_type t445 = xx6Limitation_min(-t77 - t443);
    real_type t446 = XL__[iX_xx7];
    real_type t448 = xx7Limitation_min(-t77 - t446);
    real_type t450 = xx7Limitation_max(t446 - t77);
    real_type t451 = XL__[iX_xx8];
    real_type t453 = xx8Limitation_min(-t77 - t451);
    real_type t455 = xx8Limitation_max(t451 - t77);
    real_type t456 = XL__[iX_xx4];
    real_type t458 = xx4Limitation_min(-t77 - t456);
    real_type t460 = xx4Limitation_max(t456 - t77);
    real_type t461 = XL__[iX_xx5];
    real_type t463 = xx5Limitation_min(-t77 - t461);
    real_type t465 = xx5Limitation_max(t461 - t77);
    real_type t467 = xx6Limitation_max(t443 - t77);
    real_type t468 = XL__[iX_xx1];
    real_type t470 = xx1Limitation_min(-t77 - t468);
    real_type t472 = xx1Limitation_max(t468 - t77);
    real_type t473 = t440 + t442 + t445 + t448 + t450 + t453 + t455 + t458 + t460 + t463 + t465 + t467 + t470 + t472;
    real_type t476 = XL__[iX_xx2];
    real_type t478 = xx2Limitation_min(-t77 - t476);
    real_type t480 = xx2Limitation_max(t476 - t77);
    real_type t481 = XL__[iX_xx3];
    real_type t483 = xx3Limitation_min(-t77 - t481);
    real_type t485 = xx3Limitation_max(t481 - t77);
    real_type t486 = XL__[iX_yy18];
    real_type t488 = yy18Limitation_max(t486 - t77);
    real_type t489 = XL__[iX_yy19];
    real_type t491 = yy19Limitation_min(-t77 - t489);
    real_type t493 = yy19Limitation_max(t489 - t77);
    real_type t494 = XL__[iX_yy20];
    real_type t496 = yy20Limitation_min(-t77 - t494);
    real_type t498 = yy20Limitation_max(t494 - t77);
    real_type t499 = XL__[iX_yy15];
    real_type t501 = yy15Limitation_max(t499 - t77);
    real_type t502 = XL__[iX_yy16];
    real_type t504 = yy16Limitation_max(t502 - t77);
    real_type t506 = yy16Limitation_min(-t77 - t502);
    real_type t507 = XL__[iX_yy17];
    real_type t509 = yy17Limitation_min(-t77 - t507);
    real_type t510 = t478 + t480 + t483 + t485 + t488 + t491 + t493 + t496 + t498 + t501 + t504 + t506 + t509;
    real_type t512 = yy17Limitation_max(t507 - t77);
    real_type t514 = yy18Limitation_min(-t77 - t486);
    real_type t515 = XR__[iX_yy11];
    real_type t517 = yy11Limitation_min(-t77 - t515);
    real_type t519 = yy11Limitation_max(t515 - t77);
    real_type t520 = XR__[iX_yy12];
    real_type t522 = yy12Limitation_min(-t77 - t520);
    real_type t524 = yy12Limitation_max(t520 - t77);
    real_type t525 = XL__[iX_yy14];
    real_type t527 = yy14Limitation_max(t525 - t77);
    real_type t529 = yy15Limitation_min(-t77 - t499);
    real_type t530 = XR__[iX_yy8];
    real_type t532 = yy8Limitation_min(-t77 - t530);
    real_type t534 = yy8Limitation_max(t530 - t77);
    real_type t535 = XR__[iX_yy9];
    real_type t537 = yy9Limitation_min(-t77 - t535);
    real_type t539 = yy9Limitation_max(t535 - t77);
    real_type t540 = XR__[iX_yy10];
    real_type t542 = yy10Limitation_min(-t77 - t540);
    real_type t544 = yy10Limitation_max(t540 - t77);
    real_type t545 = t512 + t514 + t517 + t519 + t522 + t524 + t527 + t529 + t532 + t534 + t537 + t539 + t542 + t544;
    real_type t547 = XR__[iX_yy5];
    real_type t549 = yy5Limitation_min(-t77 - t547);
    real_type t551 = yy5Limitation_max(t547 - t77);
    real_type t552 = XR__[iX_yy6];
    real_type t554 = yy6Limitation_min(-t77 - t552);
    real_type t556 = yy6Limitation_max(t552 - t77);
    real_type t557 = XR__[iX_yy7];
    real_type t559 = yy7Limitation_min(-t77 - t557);
    real_type t561 = yy7Limitation_max(t557 - t77);
    real_type t562 = XR__[iX_yy2];
    real_type t564 = yy2Limitation_min(-t77 - t562);
    real_type t566 = yy2Limitation_max(t562 - t77);
    real_type t567 = XR__[iX_yy3];
    real_type t569 = yy3Limitation_min(-t77 - t567);
    real_type t571 = yy3Limitation_max(t567 - t77);
    real_type t572 = XR__[iX_yy4];
    real_type t574 = yy4Limitation_min(-t77 - t572);
    real_type t576 = yy4Limitation_max(t572 - t77);
    real_type t577 = XR__[iX_xx20];
    real_type t579 = xx20Limitation_min(-t77 - t577);
    real_type t581 = xx20Limitation_max(t577 - t77);
    real_type t582 = t549 + t551 + t554 + t556 + t559 + t561 + t564 + t566 + t569 + t571 + t574 + t576 + t579 + t581;
    real_type t583 = XR__[iX_yy1];
    real_type t585 = yy1Limitation_min(-t77 - t583);
    real_type t587 = yy1Limitation_max(t583 - t77);
    real_type t588 = XR__[iX_xx18];
    real_type t590 = xx18Limitation_min(-t77 - t588);
    real_type t592 = xx18Limitation_max(t588 - t77);
    real_type t593 = XR__[iX_xx19];
    real_type t595 = xx19Limitation_min(-t77 - t593);
    real_type t597 = xx19Limitation_max(t593 - t77);
    real_type t598 = XR__[iX_xx16];
    real_type t600 = xx16Limitation_min(-t77 - t598);
    real_type t602 = xx16Limitation_max(t598 - t77);
    real_type t603 = XR__[iX_xx17];
    real_type t605 = xx17Limitation_min(-t77 - t603);
    real_type t607 = xx17Limitation_max(t603 - t77);
    real_type t608 = XR__[iX_xx14];
    real_type t610 = xx14Limitation_min(-t77 - t608);
    real_type t612 = xx14Limitation_max(t608 - t77);
    real_type t613 = XR__[iX_xx15];
    real_type t615 = xx15Limitation_min(-t77 - t613);
    real_type t617 = xx15Limitation_max(t613 - t77);
    real_type t618 = t585 + t587 + t590 + t592 + t595 + t597 + t600 + t602 + t605 + t607 + t610 + t612 + t615 + t617;
    real_type t623 = XR__[iX_xx12];
    real_type t625 = xx12Limitation_max(t623 - t77);
    real_type t626 = XR__[iX_xx13];
    real_type t628 = xx13Limitation_min(-t77 - t626);
    real_type t630 = xx13Limitation_max(t626 - t77);
    real_type t631 = XR__[iX_xx10];
    real_type t633 = xx10Limitation_max(t631 - t77);
    real_type t634 = XR__[iX_xx11];
    real_type t636 = xx11Limitation_min(-t77 - t634);
    real_type t638 = xx11Limitation_max(t634 - t77);
    real_type t640 = xx12Limitation_min(-t77 - t623);
    real_type t641 = XR__[iX_xx8];
    real_type t643 = xx8Limitation_max(t641 - t77);
    real_type t644 = XR__[iX_xx9];
    real_type t646 = xx9Limitation_min(-t77 - t644);
    real_type t648 = xx9Limitation_max(t644 - t77);
    real_type t650 = xx10Limitation_min(-t77 - t631);
    real_type t651 = XR__[iX_xx6];
    real_type t653 = xx6Limitation_max(t651 - t77);
    real_type t654 = XR__[iX_xx7];
    real_type t656 = xx7Limitation_min(-t77 - t654);
    real_type t657 = t625 + t628 + t630 + t633 + t636 + t638 + t640 + t643 + t646 + t648 + t650 + t653 + t656;
    real_type t659 = xx7Limitation_max(t654 - t77);
    real_type t661 = xx8Limitation_min(-t77 - t641);
    real_type t662 = XR__[iX_xx4];
    real_type t664 = xx4Limitation_max(t662 - t77);
    real_type t665 = XR__[iX_xx5];
    real_type t667 = xx5Limitation_min(-t77 - t665);
    real_type t669 = xx5Limitation_max(t665 - t77);
    real_type t671 = xx6Limitation_min(-t77 - t651);
    real_type t672 = XR__[iX_xx2];
    real_type t674 = xx2Limitation_max(t672 - t77);
    real_type t675 = XR__[iX_xx3];
    real_type t677 = xx3Limitation_min(-t77 - t675);
    real_type t679 = xx3Limitation_max(t675 - t77);
    real_type t681 = xx4Limitation_min(-t77 - t662);
    real_type t682 = XR__[iX_xx1];
    real_type t684 = xx1Limitation_min(-t77 - t682);
    real_type t686 = xx1Limitation_max(t682 - t77);
    real_type t688 = xx2Limitation_min(-t77 - t672);
    real_type t689 = XR__[iX_yy18];
    real_type t691 = yy18Limitation_max(t689 - t77);
    real_type t692 = t659 + t661 + t664 + t667 + t669 + t671 + t674 + t677 + t679 + t681 + t684 + t686 + t688 + t691;
    real_type t694 = XR__[iX_yy19];
    real_type t696 = yy19Limitation_min(-t77 - t694);
    real_type t698 = yy19Limitation_max(t694 - t77);
    real_type t699 = XR__[iX_yy20];
    real_type t701 = yy20Limitation_min(-t77 - t699);
    real_type t703 = yy20Limitation_max(t699 - t77);
    real_type t704 = XR__[iX_yy16];
    real_type t706 = yy16Limitation_min(-t77 - t704);
    real_type t707 = XR__[iX_yy17];
    real_type t709 = yy17Limitation_min(-t77 - t707);
    real_type t711 = yy17Limitation_max(t707 - t77);
    real_type t713 = yy18Limitation_min(-t77 - t689);
    real_type t714 = XR__[iX_yy14];
    real_type t716 = yy14Limitation_max(t714 - t77);
    real_type t717 = XR__[iX_yy15];
    real_type t719 = yy15Limitation_min(-t77 - t717);
    real_type t721 = yy15Limitation_max(t717 - t77);
    real_type t723 = yy16Limitation_max(t704 - t77);
    real_type t724 = XL__[iX_yy13];
    real_type t726 = yy13Limitation_max(t724 - t77);
    real_type t728 = yy14Limitation_min(-t77 - t525);
    real_type t729 = t696 + t698 + t701 + t703 + t706 + t709 + t711 + t713 + t716 + t719 + t721 + t723 + t726 + t728;
    real_type t730 = XR__[iX_yy13];
    real_type t732 = yy13Limitation_min(-t77 - t730);
    real_type t734 = yy13Limitation_max(t730 - t77);
    real_type t736 = yy14Limitation_min(-t77 - t714);
    real_type t738 = yy11Limitation_max(t88 - t77);
    real_type t739 = XL__[iX_yy12];
    real_type t741 = yy12Limitation_min(-t77 - t739);
    real_type t743 = yy12Limitation_max(t739 - t77);
    real_type t745 = yy13Limitation_min(-t77 - t724);
    real_type t746 = LM__[56];
    real_type t748 = QL__[iQ_zeta];
    real_type t750 = sin(t748 + 16);
    real_type t755 = QR__[iQ_zeta];
    real_type t757 = sin(t755 + 16);
    real_type t761 = LM__[57];
    real_type t764 = sin(t748 + 17);
    real_type t770 = sin(t755 + 17);
    real_type t774 = LM__[58];
    real_type t777 = sin(t748 + 18);
    real_type t783 = sin(t755 + 18);
    real_type t787 = LM__[59];
    real_type t790 = sin(t748 + 19);
    real_type t794 = t732 + t734 + t736 + t738 + t741 + t743 + t745 + (0.12e1 * t507 + 0.1e0 * t750) * t746 + (0.12e1 * t707 + 0.1e0 * t757) * t746 + (0.12e1 * t486 + 0.1e0 * t764) * t761 + (0.12e1 * t689 + 0.1e0 * t770) * t761 + (0.12e1 * t489 + 0.1e0 * t777) * t774 + (0.12e1 * t694 + 0.1e0 * t783) * t774 + (0.12e1 * t494 + 0.1e0 * t790) * t787;
    real_type t799 = sin(t755 + 19);
    real_type t803 = LM__[0];
    real_type t806 = LM__[1];
    real_type t809 = LM__[2];
    real_type t812 = LM__[3];
    real_type t815 = LM__[4];
    real_type t818 = LM__[5];
    real_type t821 = (0.12e1 * t699 + 0.1e0 * t799) * t787 + t333 * t803 + t183 * t803 + t363 * t806 + t186 * t806 + t366 * t809 + t189 * t809 + t369 * t812 + t193 * t812 + t336 * t815 + t242 * t815 + t339 * t818 + t245 * t818;
    real_type t822 = LM__[6];
    real_type t825 = LM__[7];
    real_type t828 = LM__[8];
    real_type t831 = LM__[9];
    real_type t834 = LM__[10];
    real_type t837 = LM__[11];
    real_type t840 = LM__[12];
    real_type t843 = t196 * t825 + t199 * t828 + t202 * t831 + t205 * t834 + t208 * t837 + t211 * t840 + t248 * t822 + t300 * t840 + t342 * t822 + t345 * t825 + t348 * t828 + t351 * t831 + t354 * t834 + t357 * t837;
    real_type t845 = LM__[13];
    real_type t848 = LM__[14];
    real_type t851 = LM__[15];
    real_type t854 = LM__[16];
    real_type t857 = LM__[17];
    real_type t860 = LM__[18];
    real_type t863 = LM__[19];
    real_type t866 = t214 * t845 + t217 * t848 + t220 * t851 + t223 * t854 + t226 * t857 + t229 * t860 + t232 * t863 + t303 * t845 + t306 * t848 + t309 * t851 + t312 * t854 + t315 * t857 + t318 * t860 + t360 * t863;
    real_type t867 = LM__[46];
    real_type t870 = sin(t748 + 6);
    real_type t876 = sin(t755 + 6);
    real_type t880 = LM__[47];
    real_type t883 = sin(t748 + 7);
    real_type t889 = sin(t755 + 7);
    real_type t893 = LM__[48];
    real_type t896 = sin(t748 + 8);
    real_type t902 = sin(t755 + 8);
    real_type t906 = LM__[49];
    real_type t909 = sin(t748 + 9);
    real_type t915 = sin(t755 + 9);
    real_type t919 = LM__[50];
    real_type t922 = sin(t748 + 10);
    real_type t928 = sin(t755 + 10);
    real_type t932 = LM__[51];
    real_type t935 = sin(t748 + 11);
    real_type t941 = sin(t755 + 11);
    real_type t945 = LM__[52];
    real_type t948 = sin(t748 + 12);
    real_type t954 = sin(t755 + 12);
    real_type t958 = (0.12e1 * t91 + 0.1e0 * t870) * t867 + (0.12e1 * t557 + 0.1e0 * t876) * t867 + (0.12e1 * t96 + 0.1e0 * t883) * t880 + (0.12e1 * t530 + 0.1e0 * t889) * t880 + (0.12e1 * t78 + 0.1e0 * t896) * t893 + (0.12e1 * t535 + 0.1e0 * t902) * t893 + (0.12e1 * t83 + 0.1e0 * t909) * t906 + (0.12e1 * t540 + 0.1e0 * t915) * t906 + (0.12e1 * t88 + 0.1e0 * t922) * t919 + (0.12e1 * t515 + 0.1e0 * t928) * t919 + (0.12e1 * t739 + 0.1e0 * t935) * t932 + (0.12e1 * t520 + 0.1e0 * t941) * t932 + (0.12e1 * t724 + 0.1e0 * t948) * t945 + (0.12e1 * t730 + 0.1e0 * t954) * t945;
    real_type t962 = LM__[53];
    real_type t965 = sin(t748 + 13);
    real_type t971 = sin(t755 + 13);
    real_type t975 = LM__[54];
    real_type t978 = sin(t748 + 14);
    real_type t984 = sin(t755 + 14);
    real_type t988 = LM__[55];
    real_type t991 = sin(t748 + 15);
    real_type t997 = sin(t755 + 15);
    real_type t1001 = LM__[40];
    real_type t1003 = sin(t748);
    real_type t1008 = sin(t755);
    real_type t1012 = LM__[41];
    real_type t1015 = sin(t748 + 1);
    real_type t1021 = sin(t755 + 1);
    real_type t1025 = LM__[42];
    real_type t1028 = sin(t748 + 2);
    real_type t1034 = sin(t755 + 2);
    real_type t1038 = LM__[43];
    real_type t1041 = sin(t748 + 3);
    real_type t1045 = (0.12e1 * t525 + 0.1e0 * t965) * t962 + (0.12e1 * t714 + 0.1e0 * t971) * t962 + (0.12e1 * t499 + 0.1e0 * t978) * t975 + (0.12e1 * t717 + 0.1e0 * t984) * t975 + (0.12e1 * t502 + 0.1e0 * t991) * t988 + (0.12e1 * t704 + 0.1e0 * t997) * t988 + (0.12e1 * t380 + 0.1e0 * t1003) * t1001 + (0.12e1 * t583 + 0.1e0 * t1008) * t1001 + (0.12e1 * t122 + 0.1e0 * t1015) * t1012 + (0.12e1 * t562 + 0.1e0 * t1021) * t1012 + (0.12e1 * t112 + 0.1e0 * t1028) * t1025 + (0.12e1 * t567 + 0.1e0 * t1034) * t1025 + (0.12e1 * t117 + 0.1e0 * t1041) * t1038;
    real_type t1048 = sin(t755 + 3);
    real_type t1052 = LM__[44];
    real_type t1055 = sin(t748 + 4);
    real_type t1061 = sin(t755 + 4);
    real_type t1065 = LM__[45];
    real_type t1068 = sin(t748 + 5);
    real_type t1074 = sin(t755 + 5);
    real_type t1078 = LM__[75];
    real_type t1079 = sin(t405);
    real_type t1083 = LM__[35];
    real_type t1084 = sin(t297);
    real_type t1087 = LM__[60];
    real_type t1088 = sin(t682);
    real_type t1090 = P__[iP_u1];
    real_type t1093 = sin(t468);
    real_type t1097 = LM__[20];
    real_type t1098 = sin(t251);
    real_type t1101 = sin(t154);
    real_type t1104 = LM__[61];
    real_type t1105 = sin(t672);
    real_type t1107 = P__[iP_u2];
    real_type t1110 = sin(t476);
    real_type t1114 = LM__[21];
    real_type t1115 = sin(t254);
    real_type t1118 = (0.12e1 * t572 + 0.1e0 * t1048) * t1038 + (0.12e1 * t101 + 0.1e0 * t1055) * t1052 + (0.12e1 * t547 + 0.1e0 * t1061) * t1052 + (0.12e1 * t106 + 0.1e0 * t1068) * t1065 + (0.12e1 * t552 + 0.1e0 * t1074) * t1065 + (0.2e0 * t1079 + t16) * t1078 + (t1084 + t16) * t1083 + (0.2e0 * t1088 + t1090) * t1087 + (0.2e0 * t1093 + t1090) * t1087 + (t1098 + t1090) * t1097 + (t1101 + t1090) * t1097 + (0.2e0 * t1105 + t1107) * t1104 + (0.2e0 * t1110 + t1107) * t1104 + (t1115 + t1107) * t1114;
    real_type t1120 = sin(t157);
    real_type t1123 = LM__[62];
    real_type t1124 = sin(t675);
    real_type t1126 = P__[iP_u3];
    real_type t1129 = sin(t481);
    real_type t1133 = LM__[22];
    real_type t1134 = sin(t257);
    real_type t1137 = sin(t160);
    real_type t1140 = LM__[63];
    real_type t1141 = sin(t662);
    real_type t1143 = P__[iP_u4];
    real_type t1146 = sin(t456);
    real_type t1150 = LM__[23];
    real_type t1151 = sin(t260);
    real_type t1154 = sin(t163);
    real_type t1157 = LM__[64];
    real_type t1158 = sin(t665);
    real_type t1160 = P__[iP_u5];
    real_type t1163 = sin(t461);
    real_type t1167 = LM__[24];
    real_type t1168 = sin(t263);
    real_type t1171 = sin(t166);
    real_type t1174 = LM__[65];
    real_type t1175 = sin(t651);
    real_type t1177 = P__[iP_u6];
    real_type t1180 = (t1120 + t1107) * t1114 + (0.2e0 * t1124 + t1126) * t1123 + (0.2e0 * t1129 + t1126) * t1123 + (t1134 + t1126) * t1133 + (t1137 + t1126) * t1133 + (0.2e0 * t1141 + t1143) * t1140 + (0.2e0 * t1146 + t1143) * t1140 + (t1151 + t1143) * t1150 + (t1154 + t1143) * t1150 + (0.2e0 * t1158 + t1160) * t1157 + (0.2e0 * t1163 + t1160) * t1157 + (t1168 + t1160) * t1167 + (t1171 + t1160) * t1167 + (0.2e0 * t1175 + t1177) * t1174;
    real_type t1181 = sin(t443);
    real_type t1185 = LM__[25];
    real_type t1186 = sin(t266);
    real_type t1189 = LM__[39];
    real_type t1190 = sin(t331);
    real_type t1193 = sin(t181);
    real_type t1196 = sin(t169);
    real_type t1199 = LM__[66];
    real_type t1200 = sin(t654);
    real_type t1204 = sin(t446);
    real_type t1208 = LM__[26];
    real_type t1209 = sin(t269);
    real_type t1212 = sin(t172);
    real_type t1215 = LM__[67];
    real_type t1216 = sin(t641);
    real_type t1220 = sin(t451);
    real_type t1224 = LM__[27];
    real_type t1225 = sin(t272);
    real_type t1228 = sin(t175);
    real_type t1231 = LM__[68];
    real_type t1232 = sin(t644);
    real_type t1236 = (0.2e0 * t1181 + t1177) * t1174 + (t1186 + t1177) * t1185 + (t1190 + t1) * t1189 + (t1193 + t1) * t1189 + (t1196 + t1177) * t1185 + (0.2e0 * t1200 + t63) * t1199 + (0.2e0 * t1204 + t63) * t1199 + (t1209 + t63) * t1208 + (t1212 + t63) * t1208 + (0.2e0 * t1216 + t68) * t1215 + (0.2e0 * t1220 + t68) * t1215 + (t1225 + t68) * t1224 + (t1228 + t68) * t1224 + (0.2e0 * t1232 + t53) * t1231;
    real_type t1239 = sin(t432);
    real_type t1243 = LM__[28];
    real_type t1244 = sin(t275);
    real_type t1247 = sin(t136);
    real_type t1250 = LM__[69];
    real_type t1251 = sin(t631);
    real_type t1255 = sin(t438);
    real_type t1259 = LM__[29];
    real_type t1260 = sin(t279);
    real_type t1263 = sin(t139);
    real_type t1266 = LM__[70];
    real_type t1267 = sin(t634);
    real_type t1271 = sin(t417);
    real_type t1275 = LM__[30];
    real_type t1276 = sin(t282);
    real_type t1279 = sin(t142);
    real_type t1282 = LM__[71];
    real_type t1283 = sin(t623);
    real_type t1287 = sin(t422);
    real_type t1291 = (0.2e0 * t1239 + t53) * t1231 + (t1244 + t53) * t1243 + (t1247 + t53) * t1243 + (0.2e0 * t1251 + t58) * t1250 + (0.2e0 * t1255 + t58) * t1250 + (t1260 + t58) * t1259 + (t1263 + t58) * t1259 + (0.2e0 * t1267 + t46) * t1266 + (0.2e0 * t1271 + t46) * t1266 + (t1276 + t46) * t1275 + (t1279 + t46) * t1275 + (0.2e0 * t1283 + t36) * t1282 + (0.2e0 * t1287 + t36) * t1282;
    real_type t1292 = LM__[31];
    real_type t1293 = sin(t285);
    real_type t1296 = sin(t145);
    real_type t1299 = LM__[72];
    real_type t1300 = sin(t626);
    real_type t1304 = sin(t427);
    real_type t1308 = LM__[32];
    real_type t1309 = sin(t288);
    real_type t1312 = sin(t148);
    real_type t1315 = LM__[73];
    real_type t1316 = sin(t608);
    real_type t1320 = sin(t410);
    real_type t1324 = LM__[33];
    real_type t1325 = sin(t291);
    real_type t1328 = sin(t178);
    real_type t1331 = LM__[74];
    real_type t1332 = sin(t613);
    real_type t1336 = sin(t402);
    real_type t1340 = LM__[34];
    real_type t1341 = sin(t294);
    real_type t1344 = sin(t127);
    real_type t1347 = (t1293 + t36) * t1292 + (t1296 + t36) * t1292 + (0.2e0 * t1300 + t39) * t1299 + (0.2e0 * t1304 + t39) * t1299 + (t1309 + t39) * t1308 + (t1312 + t39) * t1308 + (0.2e0 * t1316 + t26) * t1315 + (0.2e0 * t1320 + t26) * t1315 + (t1325 + t26) * t1324 + (t1328 + t26) * t1324 + (0.2e0 * t1332 + t29) * t1331 + (0.2e0 * t1336 + t29) * t1331 + (t1341 + t29) * t1340 + (t1344 + t29) * t1340;
    real_type t1349 = sin(t598);
    real_type t1353 = sin(t130);
    real_type t1356 = LM__[76];
    real_type t1357 = sin(t603);
    real_type t1361 = sin(t388);
    real_type t1365 = LM__[36];
    real_type t1366 = sin(t385);
    real_type t1369 = sin(t133);
    real_type t1372 = LM__[77];
    real_type t1373 = sin(t588);
    real_type t1377 = sin(t393);
    real_type t1381 = LM__[37];
    real_type t1382 = sin(t325);
    real_type t1385 = sin(t236);
    real_type t1388 = LM__[78];
    real_type t1389 = sin(t593);
    real_type t1393 = sin(t372);
    real_type t1397 = LM__[38];
    real_type t1398 = sin(t328);
    real_type t1401 = sin(t239);
    real_type t1404 = (0.2e0 * t1349 + t16) * t1078 + (t1353 + t16) * t1083 + (0.2e0 * t1357 + t21) * t1356 + (0.2e0 * t1361 + t21) * t1356 + (t1366 + t21) * t1365 + (t1369 + t21) * t1365 + (0.2e0 * t1373 + t6) * t1372 + (0.2e0 * t1377 + t6) * t1372 + (t1382 + t6) * t1381 + (t1385 + t6) * t1381 + (0.2e0 * t1389 + t11) * t1388 + (0.2e0 * t1393 + t11) * t1388 + (t1398 + t11) * t1397 + (t1401 + t11) * t1397;
    real_type t1405 = LM__[79];
    real_type t1406 = sin(t577);
    real_type t1410 = sin(t375);
    real_type t1415 = u5Limitation_max(t1160 - 10);
    real_type t1418 = u6Limitation_min(-10 - t1177);
    real_type t1421 = u6Limitation_max(t1177 - 10);
    real_type t1424 = u3Limitation_max(t1126 - 10);
    real_type t1427 = u4Limitation_min(-10 - t1143);
    real_type t1430 = u4Limitation_max(t1143 - 10);
    real_type t1433 = u5Limitation_min(-10 - t1160);
    real_type t1436 = u1Limitation_max(t1090 - 10);
    real_type t1439 = u2Limitation_min(-10 - t1107);
    real_type t1442 = u2Limitation_max(t1107 - 10);
    real_type t1445 = u3Limitation_min(-10 - t1126);
    real_type t1448 = u1Limitation_min(-10 - t1090);
    real_type t1450 = (0.2e0 * t1406 + t1) * t1405 + (0.2e0 * t1410 + t1) * t1405 + 2 * t1415 + 2 * t1418 + 2 * t1421 + 2 * t1424 + 2 * t1427 + 2 * t1430 + 2 * t1433 + 2 * t1436 + 2 * t1439 + 2 * t1442 + 2 * t1445 + 2 * t1448;
    real_type result__ = 2 * t34 + t1118 + t1450 + 2 * t71 + t1404 + t545 + t510 + t473 + t437 + t400 + t362 + t321 + t278 + t234 + t192 + t151 + t111 + t1180 + t1347 + t1236 + t866 + t729 + t692 + t657 + t1291 + t843 + t821 + t794 + t958 + t1045 + t618 + t582;
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
    real_type t1   = X__[iX_xx12];
    real_type t2   = ModelPars[iM_xy_bound];
    real_type t4   = xx12Limitation_max(t1 - t2);
    real_type t5   = X__[iX_xx13];
    real_type t7   = xx13Limitation_min(-t2 - t5);
    real_type t9   = xx13Limitation_max(t5 - t2);
    real_type t10  = X__[iX_xx14];
    real_type t12  = xx14Limitation_min(-t2 - t10);
    real_type t14  = X__[iX_yy1];
    real_type t16  = Q__[iQ_zeta];
    real_type t17  = sin(t16);
    real_type t20  = pow(V__[40] - 0.12e1 * t14 - 0.1e0 * t17, 2);
    real_type t23  = sin(X__[iX_x16]);
    real_type t24  = P__[iP_u16];
    real_type t26  = pow(V__[35] - t23 - t24, 2);
    real_type t27  = P__[iP_u17];
    real_type t29  = u17Limitation_min(-10 - t27);
    real_type t31  = u17Limitation_max(t27 - 10);
    real_type t33  = X__[iX_xx17];
    real_type t34  = sin(t33);
    real_type t37  = pow(V__[76] - 0.2e0 * t34 - t27, 2);
    real_type t39  = X__[iX_yy4];
    real_type t42  = sin(t16 + 3);
    real_type t45  = pow(V__[43] - 0.12e1 * t39 - 0.1e0 * t42, 2);
    real_type t47  = X__[iX_yy5];
    real_type t50  = sin(t16 + 4);
    real_type t53  = pow(V__[44] - 0.12e1 * t47 - 0.1e0 * t50, 2);
    real_type t55  = X__[iX_yy6];
    real_type t58  = sin(t16 + 5);
    real_type t61  = pow(V__[45] - 0.12e1 * t55 - 0.1e0 * t58, 2);
    real_type t62  = t4 + t7 + t9 + t12 + t20 + t26 + t29 + t31 + t37 + t45 + t53 + t61;
    real_type t63  = P__[iP_u19];
    real_type t65  = u19Limitation_max(t63 - 10);
    real_type t67  = X__[iX_xx19];
    real_type t68  = sin(t67);
    real_type t71  = pow(V__[78] - 0.2e0 * t68 - t63, 2);
    real_type t74  = sin(X__[iX_x19]);
    real_type t76  = pow(V__[38] - t74 - t63, 2);
    real_type t77  = P__[iP_u20];
    real_type t79  = u20Limitation_min(-10 - t77);
    real_type t81  = X__[iX_xx18];
    real_type t82  = sin(t81);
    real_type t84  = P__[iP_u18];
    real_type t86  = pow(V__[77] - 0.2e0 * t82 - t84, 2);
    real_type t89  = sin(X__[iX_x18]);
    real_type t91  = pow(V__[37] - t89 - t84, 2);
    real_type t93  = u19Limitation_min(-10 - t63);
    real_type t96  = sin(X__[iX_x17]);
    real_type t98  = pow(V__[36] - t96 - t27, 2);
    real_type t100 = u18Limitation_min(-10 - t84);
    real_type t102 = u18Limitation_max(t84 - 10);
    real_type t104 = xx19Limitation_min(-t2 - t67);
    real_type t106 = xx19Limitation_max(t67 - t2);
    real_type t107 = X__[iX_xx20];
    real_type t109 = xx20Limitation_min(-t2 - t107);
    real_type t110 = t65 + t71 + t76 + t79 + t86 + t91 + t93 + t98 + t100 + t102 + t104 + t106 + t109;
    real_type t113 = xx20Limitation_max(t107 - t2);
    real_type t115 = X__[iX_xx3];
    real_type t116 = sin(t115);
    real_type t118 = P__[iP_u3];
    real_type t120 = pow(V__[62] - 0.2e0 * t116 - t118, 2);
    real_type t121 = P__[iP_u4];
    real_type t123 = u4Limitation_min(-10 - t121);
    real_type t125 = u4Limitation_max(t121 - 10);
    real_type t128 = sin(X__[iX_x4]);
    real_type t130 = pow(V__[23] - t128 - t121, 2);
    real_type t132 = X__[iX_xx2];
    real_type t133 = sin(t132);
    real_type t135 = P__[iP_u2];
    real_type t137 = pow(V__[61] - 0.2e0 * t133 - t135, 2);
    real_type t139 = u3Limitation_min(-10 - t118);
    real_type t141 = u3Limitation_max(t118 - 10);
    real_type t144 = sin(X__[iX_x3]);
    real_type t146 = pow(V__[22] - t144 - t118, 2);
    real_type t148 = X__[iX_xx1];
    real_type t149 = sin(t148);
    real_type t151 = P__[iP_u1];
    real_type t153 = pow(V__[60] - 0.2e0 * t149 - t151, 2);
    real_type t155 = u2Limitation_min(-10 - t135);
    real_type t157 = u2Limitation_max(t135 - 10);
    real_type t158 = t113 + t120 + t123 + t125 + t130 + t137 + t139 + t141 + t146 + t153 + t155 + t157;
    real_type t161 = sin(X__[iX_x2]);
    real_type t163 = pow(V__[21] - t161 - t135, 2);
    real_type t166 = sin(X__[iX_x15]);
    real_type t167 = P__[iP_u15];
    real_type t169 = pow(V__[34] - t166 - t167, 2);
    real_type t171 = u16Limitation_min(-10 - t24);
    real_type t173 = u16Limitation_max(t24 - 10);
    real_type t175 = X__[iX_xx16];
    real_type t176 = sin(t175);
    real_type t179 = pow(V__[75] - 0.2e0 * t176 - t24, 2);
    real_type t182 = sin(X__[iX_x14]);
    real_type t183 = P__[iP_u14];
    real_type t185 = pow(V__[33] - t182 - t183, 2);
    real_type t187 = u15Limitation_min(-10 - t167);
    real_type t189 = u15Limitation_max(t167 - 10);
    real_type t191 = X__[iX_xx15];
    real_type t192 = sin(t191);
    real_type t195 = pow(V__[74] - 0.2e0 * t192 - t167, 2);
    real_type t198 = sin(X__[iX_x6]);
    real_type t199 = P__[iP_u6];
    real_type t201 = pow(V__[25] - t198 - t199, 2);
    real_type t203 = X__[iX_xx6];
    real_type t204 = sin(t203);
    real_type t207 = pow(V__[65] - 0.2e0 * t204 - t199, 2);
    real_type t208 = P__[iP_u7];
    real_type t210 = u7Limitation_min(-10 - t208);
    real_type t212 = X__[iX_xx5];
    real_type t213 = sin(t212);
    real_type t215 = P__[iP_u5];
    real_type t217 = pow(V__[64] - 0.2e0 * t213 - t215, 2);
    real_type t218 = t163 + t169 + t171 + t173 + t179 + t185 + t187 + t189 + t195 + t201 + t207 + t210 + t217;
    real_type t222 = u6Limitation_min(-10 - t199);
    real_type t224 = u6Limitation_max(t199 - 10);
    real_type t226 = X__[iX_xx4];
    real_type t227 = sin(t226);
    real_type t230 = pow(V__[63] - 0.2e0 * t227 - t121, 2);
    real_type t232 = u5Limitation_min(-10 - t215);
    real_type t234 = u5Limitation_max(t215 - 10);
    real_type t237 = sin(X__[iX_x5]);
    real_type t239 = pow(V__[24] - t237 - t215, 2);
    real_type t241 = xx17Limitation_min(-t2 - t33);
    real_type t243 = xx17Limitation_max(t33 - t2);
    real_type t245 = xx18Limitation_min(-t2 - t81);
    real_type t247 = xx18Limitation_max(t81 - t2);
    real_type t248 = P__[iP_u10];
    real_type t250 = u10Limitation_min(-10 - t248);
    real_type t252 = u10Limitation_max(t248 - 10);
    real_type t253 = t222 + t224 + t230 + t232 + t234 + t239 + t241 + t243 + t245 + t247 + t250 + t252;
    real_type t256 = sin(X__[iX_x10]);
    real_type t258 = pow(V__[29] - t256 - t248, 2);
    real_type t260 = X__[iX_xx10];
    real_type t261 = sin(t260);
    real_type t264 = pow(V__[69] - 0.2e0 * t261 - t248, 2);
    real_type t266 = xx15Limitation_min(-t2 - t191);
    real_type t268 = xx15Limitation_max(t191 - t2);
    real_type t270 = xx16Limitation_min(-t2 - t175);
    real_type t272 = xx16Limitation_max(t175 - t2);
    real_type t274 = xx14Limitation_max(t10 - t2);
    real_type t276 = u14Limitation_min(-10 - t183);
    real_type t278 = u14Limitation_max(t183 - 10);
    real_type t280 = sin(t10);
    real_type t283 = pow(V__[73] - 0.2e0 * t280 - t183, 2);
    real_type t284 = P__[iP_u9];
    real_type t286 = u9Limitation_min(-10 - t284);
    real_type t288 = u9Limitation_max(t284 - 10);
    real_type t291 = sin(X__[iX_x9]);
    real_type t293 = pow(V__[28] - t291 - t284, 2);
    real_type t294 = t258 + t264 + t266 + t268 + t270 + t272 + t274 + t276 + t278 + t283 + t286 + t288 + t293;
    real_type t297 = X__[iX_xx9];
    real_type t298 = sin(t297);
    real_type t301 = pow(V__[68] - 0.2e0 * t298 - t284, 2);
    real_type t302 = X__[iX_yy11];
    real_type t304 = yy11Limitation_min(-t2 - t302);
    real_type t306 = yy11Limitation_max(t302 - t2);
    real_type t307 = X__[iX_yy12];
    real_type t309 = yy12Limitation_min(-t2 - t307);
    real_type t311 = yy12Limitation_max(t307 - t2);
    real_type t312 = X__[iX_yy9];
    real_type t314 = yy9Limitation_min(-t2 - t312);
    real_type t316 = yy9Limitation_max(t312 - t2);
    real_type t317 = X__[iX_yy10];
    real_type t319 = yy10Limitation_min(-t2 - t317);
    real_type t321 = yy10Limitation_max(t317 - t2);
    real_type t322 = X__[iX_yy15];
    real_type t324 = yy15Limitation_min(-t2 - t322);
    real_type t326 = yy15Limitation_max(t322 - t2);
    real_type t327 = X__[iX_yy16];
    real_type t329 = yy16Limitation_max(t327 - t2);
    real_type t330 = t301 + t304 + t306 + t309 + t311 + t314 + t316 + t319 + t321 + t324 + t326 + t329;
    real_type t332 = yy16Limitation_min(-t2 - t327);
    real_type t334 = yy1Limitation_min(-t2 - t14);
    real_type t336 = yy1Limitation_max(t14 - t2);
    real_type t337 = X__[iX_yy2];
    real_type t339 = yy2Limitation_min(-t2 - t337);
    real_type t341 = yy2Limitation_max(t337 - t2);
    real_type t345 = pow(V__[9] - X__[iX_y10], 2);
    real_type t349 = pow(V__[10] - X__[iX_y11], 2);
    real_type t353 = pow(V__[11] - X__[iX_y12], 2);
    real_type t357 = pow(V__[12] - X__[iX_y13], 2);
    real_type t361 = pow(V__[5] - X__[iX_y6], 2);
    real_type t365 = pow(V__[6] - X__[iX_y7], 2);
    real_type t369 = pow(V__[7] - X__[iX_y8], 2);
    real_type t373 = pow(V__[8] - X__[iX_y9], 2);
    real_type t374 = t332 + t334 + t336 + t339 + t341 + t345 + t349 + t353 + t357 + t361 + t365 + t369 + t373;
    real_type t379 = X__[iX_yy7];
    real_type t382 = sin(t16 + 6);
    real_type t385 = pow(V__[46] - 0.12e1 * t379 - 0.1e0 * t382, 2);
    real_type t387 = X__[iX_yy8];
    real_type t390 = sin(t16 + 7);
    real_type t393 = pow(V__[47] - 0.12e1 * t387 - 0.1e0 * t390, 2);
    real_type t397 = sin(t16 + 8);
    real_type t400 = pow(V__[48] - 0.12e1 * t312 - 0.1e0 * t397, 2);
    real_type t401 = P__[iP_u11];
    real_type t403 = u11Limitation_min(-10 - t401);
    real_type t405 = u11Limitation_max(t401 - 10);
    real_type t407 = X__[iX_xx11];
    real_type t408 = sin(t407);
    real_type t411 = pow(V__[70] - 0.2e0 * t408 - t401, 2);
    real_type t414 = sin(X__[iX_x11]);
    real_type t416 = pow(V__[30] - t414 - t401, 2);
    real_type t417 = X__[iX_yy13];
    real_type t419 = yy13Limitation_min(-t2 - t417);
    real_type t421 = yy13Limitation_max(t417 - t2);
    real_type t422 = X__[iX_yy14];
    real_type t424 = yy14Limitation_min(-t2 - t422);
    real_type t426 = yy14Limitation_max(t422 - t2);
    real_type t430 = pow(V__[17] - X__[iX_y18], 2);
    real_type t431 = t385 + t393 + t400 + t403 + t405 + t411 + t416 + t419 + t421 + t424 + t426 + t430;
    real_type t435 = pow(V__[18] - X__[iX_y19], 2);
    real_type t439 = pow(V__[19] - X__[iX_y20], 2);
    real_type t440 = P__[iP_u13];
    real_type t442 = u13Limitation_min(-10 - t440);
    real_type t444 = u13Limitation_max(t440 - 10);
    real_type t446 = sin(t5);
    real_type t449 = pow(V__[72] - 0.2e0 * t446 - t440, 2);
    real_type t452 = sin(X__[iX_x13]);
    real_type t454 = pow(V__[32] - t452 - t440, 2);
    real_type t455 = P__[iP_u12];
    real_type t457 = u12Limitation_min(-10 - t455);
    real_type t459 = u12Limitation_max(t455 - 10);
    real_type t461 = sin(t1);
    real_type t464 = pow(V__[71] - 0.2e0 * t461 - t455, 2);
    real_type t467 = sin(X__[iX_x12]);
    real_type t469 = pow(V__[31] - t467 - t455, 2);
    real_type t470 = P__[iP_u8];
    real_type t472 = u8Limitation_min(-10 - t470);
    real_type t474 = u8Limitation_max(t470 - 10);
    real_type t477 = sin(X__[iX_x8]);
    real_type t479 = pow(V__[27] - t477 - t470, 2);
    real_type t480 = t435 + t439 + t442 + t444 + t449 + t454 + t457 + t459 + t464 + t469 + t472 + t474 + t479;
    real_type t483 = X__[iX_xx8];
    real_type t484 = sin(t483);
    real_type t487 = pow(V__[67] - 0.2e0 * t484 - t470, 2);
    real_type t491 = sin(t16 + 9);
    real_type t494 = pow(V__[49] - 0.12e1 * t317 - 0.1e0 * t491, 2);
    real_type t498 = sin(t16 + 10);
    real_type t501 = pow(V__[50] - 0.12e1 * t302 - 0.1e0 * t498, 2);
    real_type t505 = sin(t16 + 11);
    real_type t508 = pow(V__[51] - 0.12e1 * t307 - 0.1e0 * t505, 2);
    real_type t512 = pow(V__[13] - X__[iX_y14], 2);
    real_type t516 = pow(V__[14] - X__[iX_y15], 2);
    real_type t520 = pow(V__[15] - X__[iX_y16], 2);
    real_type t524 = pow(V__[16] - X__[iX_y17], 2);
    real_type t528 = sin(t16 + 1);
    real_type t531 = pow(V__[41] - 0.12e1 * t337 - 0.1e0 * t528, 2);
    real_type t533 = X__[iX_yy3];
    real_type t536 = sin(t16 + 2);
    real_type t539 = pow(V__[42] - 0.12e1 * t533 - 0.1e0 * t536, 2);
    real_type t543 = pow(V__[1] - X__[iX_y2], 2);
    real_type t547 = pow(V__[2] - X__[iX_y3], 2);
    real_type t548 = t487 + t494 + t501 + t508 + t512 + t516 + t520 + t524 + t531 + t539 + t543 + t547;
    real_type t552 = pow(V__[3] - X__[iX_y4], 2);
    real_type t556 = pow(V__[4] - X__[iX_y5], 2);
    real_type t558 = u20Limitation_max(t77 - 10);
    real_type t560 = sin(t107);
    real_type t563 = pow(V__[79] - 0.2e0 * t560 - t77, 2);
    real_type t566 = sin(X__[iX_x20]);
    real_type t568 = pow(V__[39] - t566 - t77, 2);
    real_type t572 = pow(V__[0] - X__[iX_y1], 2);
    real_type t574 = xx10Limitation_max(t260 - t2);
    real_type t576 = xx11Limitation_min(-t2 - t407);
    real_type t578 = xx11Limitation_max(t407 - t2);
    real_type t580 = xx12Limitation_min(-t2 - t1);
    real_type t582 = xx8Limitation_max(t483 - t2);
    real_type t584 = xx9Limitation_min(-t2 - t297);
    real_type t586 = xx9Limitation_max(t297 - t2);
    real_type t587 = t552 + t556 + t558 + t563 + t568 + t572 + t574 + t576 + t578 + t580 + t582 + t584 + t586;
    real_type t591 = xx10Limitation_min(-t2 - t260);
    real_type t593 = yy7Limitation_min(-t2 - t379);
    real_type t595 = yy7Limitation_max(t379 - t2);
    real_type t597 = yy8Limitation_min(-t2 - t387);
    real_type t599 = yy8Limitation_max(t387 - t2);
    real_type t601 = yy5Limitation_min(-t2 - t47);
    real_type t603 = yy5Limitation_max(t47 - t2);
    real_type t605 = yy6Limitation_min(-t2 - t55);
    real_type t607 = yy6Limitation_max(t55 - t2);
    real_type t609 = yy3Limitation_min(-t2 - t533);
    real_type t611 = yy3Limitation_max(t533 - t2);
    real_type t613 = yy4Limitation_min(-t2 - t39);
    real_type t614 = t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613;
    real_type t616 = yy4Limitation_max(t39 - t2);
    real_type t617 = X__[iX_xx7];
    real_type t619 = xx7Limitation_min(-t2 - t617);
    real_type t621 = xx7Limitation_max(t617 - t2);
    real_type t623 = xx8Limitation_min(-t2 - t483);
    real_type t625 = xx5Limitation_min(-t2 - t212);
    real_type t627 = xx5Limitation_max(t212 - t2);
    real_type t629 = xx6Limitation_max(t203 - t2);
    real_type t631 = xx6Limitation_min(-t2 - t203);
    real_type t633 = u7Limitation_max(t208 - 10);
    real_type t636 = sin(X__[iX_x7]);
    real_type t638 = pow(V__[26] - t636 - t208, 2);
    real_type t640 = sin(t617);
    real_type t643 = pow(V__[66] - 0.2e0 * t640 - t208, 2);
    real_type t645 = xx3Limitation_min(-t2 - t115);
    real_type t647 = xx3Limitation_max(t115 - t2);
    real_type t648 = t616 + t619 + t621 + t623 + t625 + t627 + t629 + t631 + t633 + t638 + t643 + t645 + t647;
    real_type t651 = xx4Limitation_min(-t2 - t226);
    real_type t653 = xx4Limitation_max(t226 - t2);
    real_type t655 = xx1Limitation_min(-t2 - t148);
    real_type t657 = xx1Limitation_max(t148 - t2);
    real_type t659 = xx2Limitation_min(-t2 - t132);
    real_type t661 = xx2Limitation_max(t132 - t2);
    real_type t662 = X__[iX_yy19];
    real_type t664 = yy19Limitation_min(-t2 - t662);
    real_type t666 = yy19Limitation_max(t662 - t2);
    real_type t667 = X__[iX_yy20];
    real_type t669 = yy20Limitation_min(-t2 - t667);
    real_type t671 = yy20Limitation_max(t667 - t2);
    real_type t672 = X__[iX_yy17];
    real_type t674 = yy17Limitation_min(-t2 - t672);
    real_type t676 = yy17Limitation_max(t672 - t2);
    real_type t677 = t651 + t653 + t655 + t657 + t659 + t661 + t664 + t666 + t669 + t671 + t674 + t676;
    real_type t678 = X__[iX_yy18];
    real_type t680 = yy18Limitation_min(-t2 - t678);
    real_type t682 = yy18Limitation_max(t678 - t2);
    real_type t684 = u1Limitation_min(-10 - t151);
    real_type t686 = u1Limitation_max(t151 - 10);
    real_type t689 = sin(X__[iX_x1]);
    real_type t691 = pow(V__[20] - t689 - t151, 2);
    real_type t695 = sin(t16 + 17);
    real_type t698 = pow(V__[57] - 0.12e1 * t678 - 0.1e0 * t695, 2);
    real_type t702 = sin(t16 + 18);
    real_type t705 = pow(V__[58] - 0.12e1 * t662 - 0.1e0 * t702, 2);
    real_type t709 = sin(t16 + 19);
    real_type t712 = pow(V__[59] - 0.12e1 * t667 - 0.1e0 * t709, 2);
    real_type t716 = sin(t16 + 14);
    real_type t719 = pow(V__[54] - 0.12e1 * t322 - 0.1e0 * t716, 2);
    real_type t723 = sin(t16 + 15);
    real_type t726 = pow(V__[55] - 0.12e1 * t327 - 0.1e0 * t723, 2);
    real_type t730 = sin(t16 + 16);
    real_type t733 = pow(V__[56] - 0.12e1 * t672 - 0.1e0 * t730, 2);
    real_type t737 = sin(t16 + 12);
    real_type t740 = pow(V__[52] - 0.12e1 * t417 - 0.1e0 * t737, 2);
    real_type t744 = sin(t16 + 13);
    real_type t747 = pow(V__[53] - 0.12e1 * t422 - 0.1e0 * t744, 2);
    real_type t748 = t680 + t682 + t684 + t686 + t691 + t698 + t705 + t712 + t719 + t726 + t733 + t740 + t747;
    real_type result__ = t62 + t110 + t158 + t218 + t253 + t294 + t330 + t374 + t431 + t480 + t548 + t587 + t614 + t648 + t677 + t748;
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
