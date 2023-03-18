/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_u12];
    real_type t3   = u12Limitation_max(t1 - 10);
    real_type t5   = u12Limitation_min(-10 - t1);
    real_type t6   = P__[iP_u13];
    real_type t8   = u13Limitation_min(-10 - t6);
    real_type t10  = u13Limitation_max(t6 - 10);
    real_type t11  = P__[iP_u14];
    real_type t13  = u14Limitation_min(-10 - t11);
    real_type t15  = u14Limitation_max(t11 - 10);
    real_type t16  = P__[iP_u15];
    real_type t18  = u15Limitation_min(-10 - t16);
    real_type t20  = u15Limitation_max(t16 - 10);
    real_type t21  = P__[iP_u16];
    real_type t23  = u16Limitation_min(-10 - t21);
    real_type t25  = u16Limitation_max(t21 - 10);
    real_type t26  = P__[iP_u7];
    real_type t28  = u7Limitation_min(-10 - t26);
    real_type t30  = u7Limitation_max(t26 - 10);
    real_type t31  = P__[iP_u8];
    real_type t33  = u8Limitation_min(-10 - t31);
    real_type t35  = u8Limitation_max(t31 - 10);
    real_type t36  = P__[iP_u9];
    real_type t38  = u9Limitation_min(-10 - t36);
    real_type t39  = t3 + t5 + t8 + t10 + t13 + t15 + t18 + t20 + t23 + t25 + t28 + t30 + t33 + t35 + t38;
    real_type t41  = u9Limitation_max(t36 - 10);
    real_type t42  = P__[iP_u10];
    real_type t44  = u10Limitation_min(-10 - t42);
    real_type t46  = u10Limitation_max(t42 - 10);
    real_type t47  = P__[iP_u11];
    real_type t49  = u11Limitation_min(-10 - t47);
    real_type t51  = u11Limitation_max(t47 - 10);
    real_type t52  = X__[iX_yy5];
    real_type t53  = ModelPars[iM_xy_bound];
    real_type t55  = yy5Limitation_max(t52 - t53);
    real_type t56  = X__[iX_yy6];
    real_type t58  = yy6Limitation_min(-t53 - t56);
    real_type t60  = yy6Limitation_max(t56 - t53);
    real_type t61  = X__[iX_yy7];
    real_type t63  = yy7Limitation_min(-t53 - t61);
    real_type t65  = X__[iX_yy20];
    real_type t67  = Q__[iQ_zeta];
    real_type t69  = sin(t67 + 19);
    real_type t74  = X__[iX_yy1];
    real_type t76  = sin(t67);
    real_type t81  = X__[iX_yy2];
    real_type t84  = sin(t67 + 1);
    real_type t89  = X__[iX_yy3];
    real_type t92  = sin(t67 + 2);
    real_type t97  = X__[iX_yy4];
    real_type t100 = sin(t67 + 3);
    real_type t105 = X__[iX_xx1];
    real_type t106 = sin(t105);
    real_type t108 = P__[iP_u1];
    real_type t111 = t41 + t44 + t46 + t49 + t51 + t55 + t58 + t60 + t63 + (0.12e1 * t65 + 0.1e0 * t69) * MU__[59] + (0.12e1 * t74 + 0.1e0 * t76) * MU__[40] + (0.12e1 * t81 + 0.1e0 * t84) * MU__[41] + (0.12e1 * t89 + 0.1e0 * t92) * MU__[42] + (0.12e1 * t97 + 0.1e0 * t100) * MU__[43] + (0.2e0 * t106 + t108) * MU__[60];
    real_type t114 = X__[iX_x1];
    real_type t115 = sin(t114);
    real_type t119 = X__[iX_xx2];
    real_type t120 = sin(t119);
    real_type t122 = P__[iP_u2];
    real_type t126 = X__[iX_x2];
    real_type t127 = sin(t126);
    real_type t131 = X__[iX_xx3];
    real_type t132 = sin(t131);
    real_type t134 = P__[iP_u3];
    real_type t138 = X__[iX_x19];
    real_type t139 = sin(t138);
    real_type t140 = P__[iP_u19];
    real_type t144 = X__[iX_xx20];
    real_type t145 = sin(t144);
    real_type t147 = P__[iP_u20];
    real_type t151 = X__[iX_x20];
    real_type t152 = sin(t151);
    real_type t156 = X__[iX_yy19];
    real_type t159 = sin(t67 + 18);
    real_type t164 = X__[iX_x18];
    real_type t165 = sin(t164);
    real_type t166 = P__[iP_u18];
    real_type t170 = X__[iX_xx19];
    real_type t171 = sin(t170);
    real_type t176 = X__[iX_x15];
    real_type t177 = sin(t176);
    real_type t181 = X__[iX_xx16];
    real_type t182 = sin(t181);
    real_type t187 = X__[iX_x16];
    real_type t188 = sin(t187);
    real_type t192 = X__[iX_xx17];
    real_type t193 = sin(t192);
    real_type t195 = P__[iP_u17];
    real_type t199 = X__[iX_x17];
    real_type t200 = sin(t199);
    real_type t203 = (t115 + t108) * MU__[20] + (0.2e0 * t120 + t122) * MU__[61] + (t127 + t122) * MU__[21] + (0.2e0 * t132 + t134) * MU__[62] + (t139 + t140) * MU__[38] + (0.2e0 * t145 + t147) * MU__[79] + (t152 + t147) * MU__[39] + (0.12e1 * t156 + 0.1e0 * t159) * MU__[58] + (t165 + t166) * MU__[37] + (0.2e0 * t171 + t140) * MU__[78] + (t177 + t16) * MU__[34] + (0.2e0 * t182 + t21) * MU__[75] + (t188 + t21) * MU__[35] + (0.2e0 * t193 + t195) * MU__[76] + (t200 + t195) * MU__[36];
    real_type t205 = X__[iX_xx18];
    real_type t206 = sin(t205);
    real_type t211 = X__[iX_x6];
    real_type t212 = sin(t211);
    real_type t213 = P__[iP_u6];
    real_type t217 = X__[iX_xx7];
    real_type t218 = sin(t217);
    real_type t223 = X__[iX_x7];
    real_type t224 = sin(t223);
    real_type t228 = X__[iX_xx8];
    real_type t229 = sin(t228);
    real_type t234 = X__[iX_x8];
    real_type t235 = sin(t234);
    real_type t239 = X__[iX_xx9];
    real_type t240 = sin(t239);
    real_type t245 = X__[iX_x9];
    real_type t246 = sin(t245);
    real_type t250 = X__[iX_xx10];
    real_type t251 = sin(t250);
    real_type t256 = X__[iX_x10];
    real_type t257 = sin(t256);
    real_type t261 = X__[iX_xx11];
    real_type t262 = sin(t261);
    real_type t267 = X__[iX_x11];
    real_type t268 = sin(t267);
    real_type t272 = X__[iX_xx12];
    real_type t273 = sin(t272);
    real_type t278 = X__[iX_x12];
    real_type t279 = sin(t278);
    real_type t283 = X__[iX_xx13];
    real_type t284 = sin(t283);
    real_type t288 = (0.2e0 * t206 + t166) * MU__[77] + (t212 + t213) * MU__[25] + (0.2e0 * t218 + t26) * MU__[66] + (t224 + t26) * MU__[26] + (0.2e0 * t229 + t31) * MU__[67] + (t235 + t31) * MU__[27] + (0.2e0 * t240 + t36) * MU__[68] + (t246 + t36) * MU__[28] + (0.2e0 * t251 + t42) * MU__[69] + (t257 + t42) * MU__[29] + (0.2e0 * t262 + t47) * MU__[70] + (t268 + t47) * MU__[30] + (0.2e0 * t273 + t1) * MU__[71] + (t279 + t1) * MU__[31] + (0.2e0 * t284 + t6) * MU__[72];
    real_type t292 = X__[iX_x13];
    real_type t293 = sin(t292);
    real_type t297 = X__[iX_xx14];
    real_type t298 = sin(t297);
    real_type t303 = X__[iX_x14];
    real_type t304 = sin(t303);
    real_type t308 = X__[iX_xx15];
    real_type t309 = sin(t308);
    real_type t314 = X__[iX_yy10];
    real_type t317 = sin(t67 + 9);
    real_type t322 = X__[iX_yy11];
    real_type t325 = sin(t67 + 10);
    real_type t330 = X__[iX_yy12];
    real_type t333 = sin(t67 + 11);
    real_type t338 = X__[iX_yy13];
    real_type t341 = sin(t67 + 12);
    real_type t346 = X__[iX_yy14];
    real_type t349 = sin(t67 + 13);
    real_type t354 = X__[iX_yy15];
    real_type t357 = sin(t67 + 14);
    real_type t362 = X__[iX_yy16];
    real_type t365 = sin(t67 + 15);
    real_type t370 = X__[iX_yy17];
    real_type t373 = sin(t67 + 16);
    real_type t378 = X__[iX_yy18];
    real_type t381 = sin(t67 + 17);
    real_type t388 = sin(t67 + 5);
    real_type t395 = sin(t67 + 6);
    real_type t399 = (t293 + t6) * MU__[32] + (0.2e0 * t298 + t11) * MU__[73] + (t304 + t11) * MU__[33] + (0.2e0 * t309 + t16) * MU__[74] + (0.12e1 * t314 + 0.1e0 * t317) * MU__[49] + (0.12e1 * t322 + 0.1e0 * t325) * MU__[50] + (0.12e1 * t330 + 0.1e0 * t333) * MU__[51] + (0.12e1 * t338 + 0.1e0 * t341) * MU__[52] + (0.12e1 * t346 + 0.1e0 * t349) * MU__[53] + (0.12e1 * t354 + 0.1e0 * t357) * MU__[54] + (0.12e1 * t362 + 0.1e0 * t365) * MU__[55] + (0.12e1 * t370 + 0.1e0 * t373) * MU__[56] + (0.12e1 * t378 + 0.1e0 * t381) * MU__[57] + (0.12e1 * t56 + 0.1e0 * t388) * MU__[45] + (0.12e1 * t61 + 0.1e0 * t395) * MU__[46];
    real_type t401 = X__[iX_yy8];
    real_type t404 = sin(t67 + 7);
    real_type t409 = X__[iX_yy9];
    real_type t412 = sin(t67 + 8);
    real_type t419 = sin(t67 + 4);
    real_type t423 = t245 * t245;
    real_type t425 = t256 * t256;
    real_type t427 = t267 * t267;
    real_type t429 = t278 * t278;
    real_type t431 = t292 * t292;
    real_type t433 = t303 * t303;
    real_type t435 = t176 * t176;
    real_type t437 = X__[iX_x3];
    real_type t438 = t437 * t437;
    real_type t440 = X__[iX_x4];
    real_type t441 = t440 * t440;
    real_type t443 = X__[iX_x5];
    real_type t444 = t443 * t443;
    real_type t446 = t211 * t211;
    real_type t448 = t223 * t223;
    real_type t450 = (0.12e1 * t401 + 0.1e0 * t404) * MU__[47] + (0.12e1 * t409 + 0.1e0 * t412) * MU__[48] + (0.12e1 * t52 + 0.1e0 * t419) * MU__[44] + 12 * t423 + 11 * t425 + 10 * t427 + 9 * t429 + 8 * t431 + 7 * t433 + 6 * t435 + 18 * t438 + 17 * t441 + 16 * t444 + 15 * t446 + 14 * t448;
    real_type t452 = t234 * t234;
    real_type t455 = u19Limitation_min(-10 - t140);
    real_type t457 = u19Limitation_max(t140 - 10);
    real_type t459 = u20Limitation_min(-10 - t147);
    real_type t461 = u20Limitation_max(t147 - 10);
    real_type t462 = t114 * t114;
    real_type t464 = t126 * t126;
    real_type t467 = u17Limitation_min(-10 - t195);
    real_type t469 = u17Limitation_max(t195 - 10);
    real_type t471 = u18Limitation_min(-10 - t166);
    real_type t473 = u18Limitation_max(t166 - 10);
    real_type t474 = X__[iX_y14];
    real_type t475 = t474 * t474;
    real_type t477 = X__[iX_y15];
    real_type t478 = t477 * t477;
    real_type t480 = X__[iX_y16];
    real_type t481 = t480 * t480;
    real_type t483 = X__[iX_y17];
    real_type t484 = t483 * t483;
    real_type t486 = 13 * t452 + t455 + t457 + t459 + t461 + 20 * t462 + 19 * t464 + t467 + t469 + t471 + t473 + 7 * t475 + 6 * t478 + 5 * t481 + 4 * t484;
    real_type t487 = X__[iX_y2];
    real_type t488 = t487 * t487;
    real_type t490 = X__[iX_y3];
    real_type t491 = t490 * t490;
    real_type t493 = X__[iX_y4];
    real_type t494 = t493 * t493;
    real_type t496 = X__[iX_y5];
    real_type t497 = t496 * t496;
    real_type t499 = X__[iX_y6];
    real_type t500 = t499 * t499;
    real_type t502 = X__[iX_y7];
    real_type t503 = t502 * t502;
    real_type t505 = X__[iX_y8];
    real_type t506 = t505 * t505;
    real_type t508 = X__[iX_y9];
    real_type t509 = t508 * t508;
    real_type t511 = X__[iX_y10];
    real_type t512 = t511 * t511;
    real_type t514 = X__[iX_y11];
    real_type t515 = t514 * t514;
    real_type t517 = X__[iX_y12];
    real_type t518 = t517 * t517;
    real_type t520 = X__[iX_y13];
    real_type t521 = t520 * t520;
    real_type t523 = X__[iX_y18];
    real_type t524 = t523 * t523;
    real_type t526 = X__[iX_y19];
    real_type t527 = t526 * t526;
    real_type t529 = X__[iX_y20];
    real_type t530 = t529 * t529;
    real_type t531 = 19 * t488 + 18 * t491 + 17 * t494 + 16 * t497 + 15 * t500 + 14 * t503 + 13 * t506 + 12 * t509 + 11 * t512 + 10 * t515 + 9 * t518 + 8 * t521 + 3 * t524 + 2 * t527 + t530;
    real_type t535 = t187 * t187;
    real_type t537 = t199 * t199;
    real_type t539 = t164 * t164;
    real_type t541 = t138 * t138;
    real_type t543 = t151 * t151;
    real_type t544 = X__[iX_y1];
    real_type t545 = t544 * t544;
    real_type t548 = xx7Limitation_min(-t53 - t217);
    real_type t550 = xx7Limitation_max(t217 - t53);
    real_type t552 = xx8Limitation_min(-t53 - t228);
    real_type t554 = xx8Limitation_max(t228 - t53);
    real_type t556 = yy1Limitation_max(t74 - t53);
    real_type t558 = yy2Limitation_min(-t53 - t81);
    real_type t560 = yy2Limitation_max(t81 - t53);
    real_type t562 = yy3Limitation_min(-t53 - t89);
    real_type t563 = P__[iP_u5];
    real_type t565 = u5Limitation_min(-10 - t563);
    real_type t566 = 5 * t535 + 4 * t537 + 3 * t539 + 2 * t541 + t543 + 20 * t545 + t548 + t550 + t552 + t554 + t556 + t558 + t560 + t562 + t565;
    real_type t568 = u5Limitation_max(t563 - 10);
    real_type t570 = u6Limitation_min(-10 - t213);
    real_type t572 = u6Limitation_max(t213 - 10);
    real_type t573 = P__[iP_u4];
    real_type t575 = u4Limitation_max(t573 - 10);
    real_type t577 = sin(t437);
    real_type t581 = X__[iX_xx4];
    real_type t582 = sin(t581);
    real_type t587 = sin(t440);
    real_type t591 = X__[iX_xx5];
    real_type t592 = sin(t591);
    real_type t597 = sin(t443);
    real_type t601 = X__[iX_xx6];
    real_type t602 = sin(t601);
    real_type t616 = t568 + t570 + t572 + t575 + (t577 + t134) * MU__[22] + (0.2e0 * t582 + t573) * MU__[63] + (t587 + t573) * MU__[23] + (0.2e0 * t592 + t563) * MU__[64] + (t597 + t563) * MU__[24] + (0.2e0 * t602 + t213) * MU__[65] + t520 * MU__[12] + t474 * MU__[13] + t477 * MU__[14] + t480 * MU__[15] + t483 * MU__[16];
    real_type t648 = t487 * MU__[1] + t490 * MU__[2] + t493 * MU__[3] + t496 * MU__[4] + t499 * MU__[5] + t502 * MU__[6] + t505 * MU__[7] + t508 * MU__[8] + t511 * MU__[9] + t514 * MU__[10] + t517 * MU__[11] + t523 * MU__[17] + t526 * MU__[18] + t529 * MU__[19] + t544 * MU__[0];
    real_type t650 = yy19Limitation_min(-t53 - t156);
    real_type t652 = yy19Limitation_max(t156 - t53);
    real_type t654 = yy20Limitation_min(-t53 - t65);
    real_type t656 = yy20Limitation_max(t65 - t53);
    real_type t658 = yy11Limitation_min(-t53 - t322);
    real_type t660 = yy11Limitation_max(t322 - t53);
    real_type t662 = yy12Limitation_min(-t53 - t330);
    real_type t664 = yy12Limitation_max(t330 - t53);
    real_type t666 = xx13Limitation_min(-t53 - t283);
    real_type t668 = xx13Limitation_max(t283 - t53);
    real_type t670 = xx14Limitation_min(-t53 - t297);
    real_type t672 = xx14Limitation_max(t297 - t53);
    real_type t674 = yy3Limitation_max(t89 - t53);
    real_type t676 = yy4Limitation_max(t97 - t53);
    real_type t678 = yy4Limitation_min(-t53 - t97);
    real_type t679 = t650 + t652 + t654 + t656 + t658 + t660 + t662 + t664 + t666 + t668 + t670 + t672 + t674 + t676 + t678;
    real_type t683 = yy5Limitation_min(-t53 - t52);
    real_type t685 = xx15Limitation_max(t308 - t53);
    real_type t687 = xx16Limitation_min(-t53 - t181);
    real_type t689 = xx16Limitation_max(t181 - t53);
    real_type t691 = xx17Limitation_min(-t53 - t192);
    real_type t693 = xx17Limitation_max(t192 - t53);
    real_type t695 = xx18Limitation_min(-t53 - t205);
    real_type t697 = xx18Limitation_max(t205 - t53);
    real_type t699 = xx19Limitation_min(-t53 - t170);
    real_type t701 = u3Limitation_min(-10 - t134);
    real_type t703 = u3Limitation_max(t134 - 10);
    real_type t705 = u4Limitation_min(-10 - t573);
    real_type t707 = xx15Limitation_min(-t53 - t308);
    real_type t709 = yy15Limitation_min(-t53 - t354);
    real_type t711 = yy15Limitation_max(t354 - t53);
    real_type t712 = t683 + t685 + t687 + t689 + t691 + t693 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = yy16Limitation_min(-t53 - t362);
    real_type t716 = yy16Limitation_max(t362 - t53);
    real_type t718 = yy17Limitation_min(-t53 - t370);
    real_type t720 = yy17Limitation_max(t370 - t53);
    real_type t722 = yy18Limitation_min(-t53 - t378);
    real_type t724 = yy18Limitation_max(t378 - t53);
    real_type t726 = xx11Limitation_min(-t53 - t261);
    real_type t728 = xx11Limitation_max(t261 - t53);
    real_type t730 = xx12Limitation_min(-t53 - t272);
    real_type t732 = xx12Limitation_max(t272 - t53);
    real_type t734 = xx19Limitation_max(t170 - t53);
    real_type t736 = xx20Limitation_min(-t53 - t144);
    real_type t738 = xx20Limitation_max(t144 - t53);
    real_type t740 = yy1Limitation_min(-t53 - t74);
    real_type t742 = yy7Limitation_max(t61 - t53);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = yy8Limitation_min(-t53 - t401);
    real_type t748 = yy8Limitation_max(t401 - t53);
    real_type t750 = yy9Limitation_min(-t53 - t409);
    real_type t752 = u1Limitation_min(-10 - t108);
    real_type t754 = u1Limitation_max(t108 - 10);
    real_type t756 = u2Limitation_min(-10 - t122);
    real_type t758 = u2Limitation_max(t122 - 10);
    real_type t760 = yy13Limitation_min(-t53 - t338);
    real_type t762 = yy13Limitation_max(t338 - t53);
    real_type t764 = yy14Limitation_min(-t53 - t346);
    real_type t766 = yy14Limitation_max(t346 - t53);
    real_type t768 = xx9Limitation_min(-t53 - t239);
    real_type t770 = xx9Limitation_max(t239 - t53);
    real_type t772 = xx10Limitation_min(-t53 - t250);
    real_type t774 = xx10Limitation_max(t250 - t53);
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + t772 + t774;
    real_type t777 = xx3Limitation_min(-t53 - t131);
    real_type t779 = xx3Limitation_max(t131 - t53);
    real_type t781 = xx4Limitation_min(-t53 - t581);
    real_type t783 = xx4Limitation_max(t581 - t53);
    real_type t785 = xx1Limitation_min(-t53 - t105);
    real_type t787 = xx1Limitation_max(t105 - t53);
    real_type t789 = xx2Limitation_min(-t53 - t119);
    real_type t791 = xx2Limitation_max(t119 - t53);
    real_type t793 = yy9Limitation_max(t409 - t53);
    real_type t795 = yy10Limitation_min(-t53 - t314);
    real_type t797 = yy10Limitation_max(t314 - t53);
    real_type t799 = xx5Limitation_min(-t53 - t591);
    real_type t801 = xx5Limitation_max(t591 - t53);
    real_type t803 = xx6Limitation_min(-t53 - t601);
    real_type t805 = xx6Limitation_max(t601 - t53);
    real_type t806 = t777 + t779 + t781 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t39 + t111 + t203 + t288 + t399 + t450 + t486 + t531 + t566 + t616 + t648 + t679 + t712 + t743 + t775 + t806;
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);

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
