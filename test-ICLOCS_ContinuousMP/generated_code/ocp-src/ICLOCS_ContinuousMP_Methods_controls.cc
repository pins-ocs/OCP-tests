/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_yy2];
    real_type t4   = yy2Limitation_min(-t1 - t2);
    real_type t5   = X__[iX_x11];
    real_type t6   = t5 * t5;
    real_type t8   = X__[iX_x12];
    real_type t9   = t8 * t8;
    real_type t11  = X__[iX_x13];
    real_type t12  = t11 * t11;
    real_type t14  = X__[iX_x14];
    real_type t15  = t14 * t14;
    real_type t17  = X__[iX_x15];
    real_type t18  = t17 * t17;
    real_type t20  = X__[iX_x16];
    real_type t21  = t20 * t20;
    real_type t23  = X__[iX_x17];
    real_type t24  = t23 * t23;
    real_type t26  = X__[iX_x18];
    real_type t27  = t26 * t26;
    real_type t29  = X__[iX_x19];
    real_type t30  = t29 * t29;
    real_type t32  = X__[iX_xx17];
    real_type t34  = xx17Limitation_min(-t1 - t32);
    real_type t35  = X__[iX_yy9];
    real_type t37  = yy9Limitation_min(-t1 - t35);
    real_type t39  = yy9Limitation_max(t35 - t1);
    real_type t40  = X__[iX_yy10];
    real_type t42  = yy10Limitation_min(-t1 - t40);
    real_type t43  = X__[iX_yy3];
    real_type t45  = yy3Limitation_min(-t1 - t43);
    real_type t46  = t4 + 10 * t6 + 9 * t9 + 8 * t12 + 7 * t15 + 6 * t18 + 5 * t21 + 4 * t24 + 3 * t27 + 2 * t30 + t34 + t37 + t39 + t42 + t45;
    real_type t47  = X__[iX_xx13];
    real_type t49  = xx13Limitation_max(t47 - t1);
    real_type t51  = yy2Limitation_max(t2 - t1);
    real_type t52  = X__[iX_xx6];
    real_type t54  = xx6Limitation_min(-t1 - t52);
    real_type t56  = xx6Limitation_max(t52 - t1);
    real_type t58  = yy3Limitation_max(t43 - t1);
    real_type t59  = X__[iX_yy1];
    real_type t61  = yy1Limitation_min(-t1 - t59);
    real_type t63  = yy1Limitation_max(t59 - t1);
    real_type t64  = X__[iX_y6];
    real_type t65  = t64 * t64;
    real_type t67  = X__[iX_y7];
    real_type t68  = t67 * t67;
    real_type t70  = X__[iX_y8];
    real_type t71  = t70 * t70;
    real_type t73  = X__[iX_y9];
    real_type t74  = t73 * t73;
    real_type t76  = X__[iX_y10];
    real_type t77  = t76 * t76;
    real_type t79  = X__[iX_y11];
    real_type t80  = t79 * t79;
    real_type t82  = X__[iX_y12];
    real_type t83  = t82 * t82;
    real_type t86  = X__[iX_xx2];
    real_type t87  = sin(t86);
    real_type t89  = P__[iP_u2];
    real_type t92  = t49 + t51 + t54 + t56 + t58 + t61 + t63 + 15 * t65 + 14 * t68 + 13 * t71 + 12 * t74 + 11 * t77 + 10 * t80 + 9 * t83 + (0.2e0 * t87 + t89) * MU__[61];
    real_type t95  = X__[iX_x2];
    real_type t96  = sin(t95);
    real_type t100 = X__[iX_xx3];
    real_type t101 = sin(t100);
    real_type t103 = P__[iP_u3];
    real_type t107 = X__[iX_x3];
    real_type t108 = sin(t107);
    real_type t112 = X__[iX_xx4];
    real_type t113 = sin(t112);
    real_type t115 = P__[iP_u4];
    real_type t119 = X__[iX_x4];
    real_type t120 = sin(t119);
    real_type t124 = X__[iX_xx5];
    real_type t125 = sin(t124);
    real_type t127 = P__[iP_u5];
    real_type t131 = X__[iX_x5];
    real_type t132 = sin(t131);
    real_type t136 = sin(t52);
    real_type t138 = P__[iP_u6];
    real_type t142 = X__[iX_x6];
    real_type t143 = sin(t142);
    real_type t147 = X__[iX_xx7];
    real_type t148 = sin(t147);
    real_type t150 = P__[iP_u7];
    real_type t154 = X__[iX_x7];
    real_type t155 = sin(t154);
    real_type t159 = X__[iX_xx8];
    real_type t160 = sin(t159);
    real_type t162 = P__[iP_u8];
    real_type t166 = X__[iX_x8];
    real_type t167 = sin(t166);
    real_type t171 = X__[iX_xx9];
    real_type t172 = sin(t171);
    real_type t174 = P__[iP_u9];
    real_type t178 = X__[iX_x9];
    real_type t179 = sin(t178);
    real_type t182 = (t96 + t89) * MU__[21] + (0.2e0 * t101 + t103) * MU__[62] + (t108 + t103) * MU__[22] + (0.2e0 * t113 + t115) * MU__[63] + (t120 + t115) * MU__[23] + (0.2e0 * t125 + t127) * MU__[64] + (t132 + t127) * MU__[24] + (0.2e0 * t136 + t138) * MU__[65] + (t143 + t138) * MU__[25] + (0.2e0 * t148 + t150) * MU__[66] + (t155 + t150) * MU__[26] + (0.2e0 * t160 + t162) * MU__[67] + (t167 + t162) * MU__[27] + (0.2e0 * t172 + t174) * MU__[68] + (t179 + t174) * MU__[28];
    real_type t184 = X__[iX_xx10];
    real_type t185 = sin(t184);
    real_type t187 = P__[iP_u10];
    real_type t191 = X__[iX_x10];
    real_type t192 = sin(t191);
    real_type t196 = X__[iX_xx11];
    real_type t197 = sin(t196);
    real_type t199 = P__[iP_u11];
    real_type t203 = sin(t5);
    real_type t207 = X__[iX_xx12];
    real_type t208 = sin(t207);
    real_type t210 = P__[iP_u12];
    real_type t214 = sin(t8);
    real_type t218 = X__[iX_y1];
    real_type t221 = X__[iX_y2];
    real_type t224 = X__[iX_y3];
    real_type t227 = X__[iX_y4];
    real_type t230 = X__[iX_y5];
    real_type t240 = (0.2e0 * t185 + t187) * MU__[69] + (t192 + t187) * MU__[29] + (0.2e0 * t197 + t199) * MU__[70] + (t203 + t199) * MU__[30] + (0.2e0 * t208 + t210) * MU__[71] + (t214 + t210) * MU__[31] + t218 * MU__[0] + t221 * MU__[1] + t224 * MU__[2] + t227 * MU__[3] + t230 * MU__[4] + t64 * MU__[5] + t67 * MU__[6] + t70 * MU__[7] + t73 * MU__[8];
    real_type t250 = X__[iX_y13];
    real_type t253 = X__[iX_y14];
    real_type t256 = X__[iX_y15];
    real_type t259 = X__[iX_y16];
    real_type t262 = X__[iX_y17];
    real_type t265 = X__[iX_y18];
    real_type t268 = X__[iX_y19];
    real_type t271 = X__[iX_y20];
    real_type t274 = X__[iX_yy12];
    real_type t276 = Q__[iQ_zeta];
    real_type t278 = sin(t276 + 11);
    real_type t283 = X__[iX_yy13];
    real_type t286 = sin(t276 + 12);
    real_type t291 = X__[iX_yy14];
    real_type t294 = sin(t276 + 13);
    real_type t299 = X__[iX_yy15];
    real_type t302 = sin(t276 + 14);
    real_type t306 = t76 * MU__[9] + t79 * MU__[10] + t82 * MU__[11] + t250 * MU__[12] + t253 * MU__[13] + t256 * MU__[14] + t259 * MU__[15] + t262 * MU__[16] + t265 * MU__[17] + t268 * MU__[18] + t271 * MU__[19] + (0.12e1 * t274 + 0.1e0 * t278) * MU__[51] + (0.12e1 * t283 + 0.1e0 * t286) * MU__[52] + (0.12e1 * t291 + 0.1e0 * t294) * MU__[53] + (0.12e1 * t299 + 0.1e0 * t302) * MU__[54];
    real_type t308 = X__[iX_yy16];
    real_type t311 = sin(t276 + 15);
    real_type t316 = X__[iX_yy17];
    real_type t319 = sin(t276 + 16);
    real_type t324 = X__[iX_yy18];
    real_type t327 = sin(t276 + 17);
    real_type t332 = X__[iX_yy19];
    real_type t335 = sin(t276 + 18);
    real_type t340 = sin(t47);
    real_type t342 = P__[iP_u13];
    real_type t346 = sin(t11);
    real_type t350 = X__[iX_xx14];
    real_type t351 = sin(t350);
    real_type t353 = P__[iP_u14];
    real_type t357 = sin(t14);
    real_type t361 = sin(t17);
    real_type t362 = P__[iP_u15];
    real_type t366 = X__[iX_xx15];
    real_type t367 = sin(t366);
    real_type t372 = sin(t20);
    real_type t373 = P__[iP_u16];
    real_type t377 = X__[iX_xx16];
    real_type t378 = sin(t377);
    real_type t383 = sin(t23);
    real_type t384 = P__[iP_u17];
    real_type t388 = sin(t32);
    real_type t393 = sin(t26);
    real_type t394 = P__[iP_u18];
    real_type t397 = (0.12e1 * t308 + 0.1e0 * t311) * MU__[55] + (0.12e1 * t316 + 0.1e0 * t319) * MU__[56] + (0.12e1 * t324 + 0.1e0 * t327) * MU__[57] + (0.12e1 * t332 + 0.1e0 * t335) * MU__[58] + (0.2e0 * t340 + t342) * MU__[72] + (t346 + t342) * MU__[32] + (0.2e0 * t351 + t353) * MU__[73] + (t357 + t353) * MU__[33] + (t361 + t362) * MU__[34] + (0.2e0 * t367 + t362) * MU__[74] + (t372 + t373) * MU__[35] + (0.2e0 * t378 + t373) * MU__[75] + (t383 + t384) * MU__[36] + (0.2e0 * t388 + t384) * MU__[76] + (t393 + t394) * MU__[37];
    real_type t400 = X__[iX_xx18];
    real_type t401 = sin(t400);
    real_type t406 = sin(t29);
    real_type t407 = P__[iP_u19];
    real_type t411 = X__[iX_xx19];
    real_type t412 = sin(t411);
    real_type t417 = X__[iX_x20];
    real_type t418 = sin(t417);
    real_type t419 = P__[iP_u20];
    real_type t423 = X__[iX_xx20];
    real_type t424 = sin(t423);
    real_type t430 = sin(t276);
    real_type t437 = sin(t276 + 1);
    real_type t444 = sin(t276 + 2);
    real_type t449 = X__[iX_xx1];
    real_type t450 = sin(t449);
    real_type t452 = P__[iP_u1];
    real_type t456 = X__[iX_x1];
    real_type t457 = sin(t456);
    real_type t461 = X__[iX_yy20];
    real_type t464 = sin(t276 + 19);
    real_type t469 = X__[iX_yy4];
    real_type t472 = sin(t276 + 3);
    real_type t477 = X__[iX_yy5];
    real_type t480 = sin(t276 + 4);
    real_type t485 = X__[iX_yy6];
    real_type t488 = sin(t276 + 5);
    real_type t493 = X__[iX_yy7];
    real_type t496 = sin(t276 + 6);
    real_type t500 = (0.2e0 * t401 + t394) * MU__[77] + (t406 + t407) * MU__[38] + (0.2e0 * t412 + t407) * MU__[78] + (t418 + t419) * MU__[39] + (0.2e0 * t424 + t419) * MU__[79] + (0.12e1 * t59 + 0.1e0 * t430) * MU__[40] + (0.12e1 * t2 + 0.1e0 * t437) * MU__[41] + (0.12e1 * t43 + 0.1e0 * t444) * MU__[42] + (0.2e0 * t450 + t452) * MU__[60] + (t457 + t452) * MU__[20] + (0.12e1 * t461 + 0.1e0 * t464) * MU__[59] + (0.12e1 * t469 + 0.1e0 * t472) * MU__[43] + (0.12e1 * t477 + 0.1e0 * t480) * MU__[44] + (0.12e1 * t485 + 0.1e0 * t488) * MU__[45] + (0.12e1 * t493 + 0.1e0 * t496) * MU__[46];
    real_type t502 = X__[iX_yy8];
    real_type t505 = sin(t276 + 7);
    real_type t512 = sin(t276 + 8);
    real_type t519 = sin(t276 + 9);
    real_type t524 = X__[iX_yy11];
    real_type t527 = sin(t276 + 10);
    real_type t532 = xx15Limitation_min(-t1 - t366);
    real_type t534 = xx14Limitation_min(-t1 - t350);
    real_type t536 = xx14Limitation_max(t350 - t1);
    real_type t538 = xx15Limitation_max(t366 - t1);
    real_type t540 = yy12Limitation_min(-t1 - t274);
    real_type t542 = yy12Limitation_max(t274 - t1);
    real_type t544 = yy13Limitation_min(-t1 - t283);
    real_type t546 = yy13Limitation_max(t283 - t1);
    real_type t548 = yy10Limitation_max(t40 - t1);
    real_type t550 = yy11Limitation_min(-t1 - t524);
    real_type t552 = yy11Limitation_max(t524 - t1);
    real_type t553 = (0.12e1 * t502 + 0.1e0 * t505) * MU__[47] + (0.12e1 * t35 + 0.1e0 * t512) * MU__[48] + (0.12e1 * t40 + 0.1e0 * t519) * MU__[49] + (0.12e1 * t524 + 0.1e0 * t527) * MU__[50] + t532 + t534 + t536 + t538 + t540 + t542 + t544 + t546 + t548 + t550 + t552;
    real_type t558 = xx17Limitation_max(t32 - t1);
    real_type t560 = xx3Limitation_min(-t1 - t100);
    real_type t562 = xx3Limitation_max(t100 - t1);
    real_type t564 = xx4Limitation_min(-t1 - t112);
    real_type t566 = u4Limitation_max(t115 - 10);
    real_type t568 = u5Limitation_min(-10 - t127);
    real_type t570 = u5Limitation_max(t127 - 10);
    real_type t572 = u6Limitation_min(-10 - t138);
    real_type t574 = yy6Limitation_max(t485 - t1);
    real_type t576 = yy7Limitation_min(-t1 - t493);
    real_type t578 = yy7Limitation_max(t493 - t1);
    real_type t580 = xx18Limitation_min(-t1 - t400);
    real_type t582 = u18Limitation_max(t394 - 10);
    real_type t584 = u19Limitation_min(-10 - t407);
    real_type t586 = u19Limitation_max(t407 - 10);
    real_type t587 = t558 + t560 + t562 + t564 + t566 + t568 + t570 + t572 + t574 + t576 + t578 + t580 + t582 + t584 + t586;
    real_type t589 = u15Limitation_max(t362 - 10);
    real_type t591 = u16Limitation_min(-10 - t373);
    real_type t593 = u16Limitation_max(t373 - 10);
    real_type t595 = u17Limitation_min(-10 - t384);
    real_type t597 = u17Limitation_max(t384 - 10);
    real_type t599 = u18Limitation_min(-10 - t394);
    real_type t601 = u15Limitation_min(-10 - t362);
    real_type t603 = u14Limitation_min(-10 - t353);
    real_type t605 = u14Limitation_max(t353 - 10);
    real_type t607 = u13Limitation_max(t342 - 10);
    real_type t609 = u12Limitation_min(-10 - t210);
    real_type t611 = u12Limitation_max(t210 - 10);
    real_type t613 = u13Limitation_min(-10 - t342);
    real_type t615 = u11Limitation_max(t199 - 10);
    real_type t617 = yy4Limitation_min(-t1 - t469);
    real_type t618 = t589 + t591 + t593 + t595 + t597 + t599 + t601 + t603 + t605 + t607 + t609 + t611 + t613 + t615 + t617;
    real_type t620 = t417 * t417;
    real_type t621 = t218 * t218;
    real_type t623 = t221 * t221;
    real_type t625 = t224 * t224;
    real_type t627 = t227 * t227;
    real_type t629 = t230 * t230;
    real_type t632 = u1Limitation_min(-10 - t452);
    real_type t634 = u1Limitation_max(t452 - 10);
    real_type t635 = t95 * t95;
    real_type t637 = t107 * t107;
    real_type t639 = t119 * t119;
    real_type t641 = t131 * t131;
    real_type t643 = t142 * t142;
    real_type t645 = t154 * t154;
    real_type t647 = t166 * t166;
    real_type t649 = t620 + 20 * t621 + 19 * t623 + 18 * t625 + 17 * t627 + 16 * t629 + t632 + t634 + 19 * t635 + 18 * t637 + 17 * t639 + 16 * t641 + 15 * t643 + 14 * t645 + 13 * t647;
    real_type t650 = t178 * t178;
    real_type t652 = t191 * t191;
    real_type t654 = t250 * t250;
    real_type t656 = t253 * t253;
    real_type t658 = t256 * t256;
    real_type t660 = t259 * t259;
    real_type t662 = t262 * t262;
    real_type t664 = t265 * t265;
    real_type t666 = t268 * t268;
    real_type t668 = t271 * t271;
    real_type t669 = t456 * t456;
    real_type t672 = xx11Limitation_min(-t1 - t196);
    real_type t674 = xx11Limitation_max(t196 - t1);
    real_type t676 = xx12Limitation_min(-t1 - t207);
    real_type t678 = xx10Limitation_max(t184 - t1);
    real_type t679 = 12 * t650 + 11 * t652 + 8 * t654 + 7 * t656 + 6 * t658 + 5 * t660 + 4 * t662 + 3 * t664 + 2 * t666 + t668 + 20 * t669 + t672 + t674 + t676 + t678;
    real_type t683 = yy4Limitation_max(t469 - t1);
    real_type t685 = u20Limitation_min(-10 - t419);
    real_type t687 = u20Limitation_max(t419 - 10);
    real_type t689 = xx4Limitation_max(t112 - t1);
    real_type t691 = u9Limitation_min(-10 - t174);
    real_type t693 = u9Limitation_max(t174 - 10);
    real_type t695 = u10Limitation_min(-10 - t187);
    real_type t697 = u10Limitation_max(t187 - 10);
    real_type t699 = u11Limitation_min(-10 - t199);
    real_type t701 = xx5Limitation_min(-t1 - t124);
    real_type t703 = xx5Limitation_max(t124 - t1);
    real_type t705 = yy18Limitation_max(t324 - t1);
    real_type t707 = yy19Limitation_min(-t1 - t332);
    real_type t709 = yy19Limitation_max(t332 - t1);
    real_type t711 = yy20Limitation_min(-t1 - t461);
    real_type t712 = t683 + t685 + t687 + t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = yy20Limitation_max(t461 - t1);
    real_type t716 = yy16Limitation_max(t308 - t1);
    real_type t718 = yy17Limitation_min(-t1 - t316);
    real_type t720 = yy17Limitation_max(t316 - t1);
    real_type t722 = yy18Limitation_min(-t1 - t324);
    real_type t724 = xx12Limitation_max(t207 - t1);
    real_type t726 = xx13Limitation_min(-t1 - t47);
    real_type t728 = xx1Limitation_min(-t1 - t449);
    real_type t730 = xx1Limitation_max(t449 - t1);
    real_type t732 = xx2Limitation_min(-t1 - t86);
    real_type t734 = xx2Limitation_max(t86 - t1);
    real_type t736 = yy8Limitation_min(-t1 - t502);
    real_type t738 = yy8Limitation_max(t502 - t1);
    real_type t740 = xx16Limitation_min(-t1 - t377);
    real_type t742 = xx16Limitation_max(t377 - t1);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = yy5Limitation_max(t477 - t1);
    real_type t748 = yy6Limitation_min(-t1 - t485);
    real_type t750 = xx20Limitation_max(t423 - t1);
    real_type t752 = xx18Limitation_max(t400 - t1);
    real_type t754 = xx19Limitation_min(-t1 - t411);
    real_type t756 = xx19Limitation_max(t411 - t1);
    real_type t758 = xx20Limitation_min(-t1 - t423);
    real_type t760 = u6Limitation_max(t138 - 10);
    real_type t762 = u7Limitation_min(-10 - t150);
    real_type t764 = u7Limitation_max(t150 - 10);
    real_type t766 = u8Limitation_min(-10 - t162);
    real_type t768 = u8Limitation_max(t162 - 10);
    real_type t770 = yy5Limitation_min(-t1 - t477);
    real_type t772 = xx7Limitation_min(-t1 - t147);
    real_type t774 = xx7Limitation_max(t147 - t1);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = xx8Limitation_min(-t1 - t159);
    real_type t779 = xx8Limitation_max(t159 - t1);
    real_type t781 = yy14Limitation_min(-t1 - t291);
    real_type t783 = u2Limitation_min(-10 - t89);
    real_type t785 = u2Limitation_max(t89 - 10);
    real_type t787 = u3Limitation_min(-10 - t103);
    real_type t789 = u3Limitation_max(t103 - 10);
    real_type t791 = u4Limitation_min(-10 - t115);
    real_type t793 = xx9Limitation_min(-t1 - t171);
    real_type t795 = xx9Limitation_max(t171 - t1);
    real_type t797 = xx10Limitation_min(-t1 - t184);
    real_type t799 = yy14Limitation_max(t291 - t1);
    real_type t801 = yy15Limitation_min(-t1 - t299);
    real_type t803 = yy15Limitation_max(t299 - t1);
    real_type t805 = yy16Limitation_min(-t1 - t308);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t46 + t92 + t182 + t240 + t306 + t397 + t500 + t553 + t587 + t618 + t649 + t679 + t712 + t743 + t775 + t806;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::g_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DgDxpm_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DgDxpm_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DgDxpm_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
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
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
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
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    // no controls to compute
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_controls.cc
