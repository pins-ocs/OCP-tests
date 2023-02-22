/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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
    real_type t2   = X__[iX_xx1];
    real_type t4   = xx1Limitation_min(-t1 - t2);
    real_type t6   = xx1Limitation_max(t2 - t1);
    real_type t7   = X__[iX_xx2];
    real_type t9   = xx2Limitation_min(-t1 - t7);
    real_type t11  = xx2Limitation_max(t7 - t1);
    real_type t12  = X__[iX_xx7];
    real_type t14  = xx7Limitation_min(-t1 - t12);
    real_type t16  = xx7Limitation_max(t12 - t1);
    real_type t17  = X__[iX_xx8];
    real_type t19  = xx8Limitation_min(-t1 - t17);
    real_type t21  = xx8Limitation_max(t17 - t1);
    real_type t22  = X__[iX_xx20];
    real_type t24  = xx20Limitation_max(t22 - t1);
    real_type t25  = X__[iX_yy1];
    real_type t27  = yy1Limitation_min(-t1 - t25);
    real_type t29  = yy1Limitation_max(t25 - t1);
    real_type t30  = X__[iX_yy2];
    real_type t32  = yy2Limitation_min(-t1 - t30);
    real_type t33  = X__[iX_yy19];
    real_type t35  = yy19Limitation_min(-t1 - t33);
    real_type t37  = yy19Limitation_max(t33 - t1);
    real_type t38  = X__[iX_yy20];
    real_type t40  = yy20Limitation_min(-t1 - t38);
    real_type t41  = t4 + t6 + t9 + t11 + t14 + t16 + t19 + t21 + t24 + t27 + t29 + t32 + t35 + t37 + t40;
    real_type t43  = yy20Limitation_max(t38 - t1);
    real_type t44  = X__[iX_xx9];
    real_type t46  = xx9Limitation_min(-t1 - t44);
    real_type t48  = xx9Limitation_max(t44 - t1);
    real_type t49  = X__[iX_xx10];
    real_type t51  = xx10Limitation_min(-t1 - t49);
    real_type t53  = xx10Limitation_max(t49 - t1);
    real_type t54  = X__[iX_yy6];
    real_type t56  = yy6Limitation_max(t54 - t1);
    real_type t57  = X__[iX_yy7];
    real_type t59  = yy7Limitation_min(-t1 - t57);
    real_type t61  = yy7Limitation_max(t57 - t1);
    real_type t62  = X__[iX_yy8];
    real_type t64  = yy8Limitation_min(-t1 - t62);
    real_type t65  = X__[iX_xx5];
    real_type t67  = xx5Limitation_min(-t1 - t65);
    real_type t69  = xx5Limitation_max(t65 - t1);
    real_type t70  = X__[iX_xx6];
    real_type t72  = xx6Limitation_min(-t1 - t70);
    real_type t74  = xx6Limitation_max(t70 - t1);
    real_type t75  = X__[iX_xx11];
    real_type t77  = xx11Limitation_min(-t1 - t75);
    real_type t79  = xx11Limitation_max(t75 - t1);
    real_type t80  = t43 + t46 + t48 + t51 + t53 + t56 + t59 + t61 + t64 + t67 + t69 + t72 + t74 + t77 + t79;
    real_type t82  = X__[iX_xx12];
    real_type t84  = xx12Limitation_min(-t1 - t82);
    real_type t85  = X__[iX_y2];
    real_type t86  = t85 * t85;
    real_type t88  = X__[iX_y3];
    real_type t89  = t88 * t88;
    real_type t91  = X__[iX_y4];
    real_type t92  = t91 * t91;
    real_type t94  = X__[iX_y5];
    real_type t95  = t94 * t94;
    real_type t97  = X__[iX_y6];
    real_type t98  = t97 * t97;
    real_type t100 = X__[iX_y7];
    real_type t101 = t100 * t100;
    real_type t103 = X__[iX_y8];
    real_type t104 = t103 * t103;
    real_type t106 = X__[iX_y9];
    real_type t107 = t106 * t106;
    real_type t110 = yy2Limitation_max(t30 - t1);
    real_type t111 = X__[iX_yy3];
    real_type t113 = yy3Limitation_max(t111 - t1);
    real_type t115 = yy3Limitation_min(-t1 - t111);
    real_type t116 = X__[iX_yy4];
    real_type t118 = yy4Limitation_min(-t1 - t116);
    real_type t119 = X__[iX_y18];
    real_type t120 = t119 * t119;
    real_type t122 = X__[iX_y19];
    real_type t123 = t122 * t122;
    real_type t125 = t84 + 19 * t86 + 18 * t89 + 17 * t92 + 16 * t95 + 15 * t98 + 14 * t101 + 13 * t104 + 12 * t107 + t110 + t113 + t115 + t118 + 3 * t120 + 2 * t123;
    real_type t126 = X__[iX_y20];
    real_type t127 = t126 * t126;
    real_type t128 = X__[iX_y10];
    real_type t129 = t128 * t128;
    real_type t131 = X__[iX_y11];
    real_type t132 = t131 * t131;
    real_type t134 = X__[iX_y12];
    real_type t135 = t134 * t134;
    real_type t137 = X__[iX_y13];
    real_type t138 = t137 * t137;
    real_type t140 = X__[iX_y14];
    real_type t141 = t140 * t140;
    real_type t143 = X__[iX_y15];
    real_type t144 = t143 * t143;
    real_type t146 = X__[iX_y16];
    real_type t147 = t146 * t146;
    real_type t149 = X__[iX_y17];
    real_type t150 = t149 * t149;
    real_type t152 = X__[iX_xx3];
    real_type t154 = xx3Limitation_min(-t1 - t152);
    real_type t156 = xx3Limitation_max(t152 - t1);
    real_type t157 = X__[iX_xx4];
    real_type t159 = xx4Limitation_min(-t1 - t157);
    real_type t161 = xx4Limitation_max(t157 - t1);
    real_type t166 = t131 * MU__[10] + t134 * MU__[11] + t127 + 11 * t129 + 10 * t132 + 9 * t135 + 8 * t138 + 7 * t141 + 6 * t144 + 5 * t147 + 4 * t150 + t154 + t156 + t159 + t161;
    real_type t186 = X__[iX_x1];
    real_type t187 = sin(t186);
    real_type t188 = P__[iP_u1];
    real_type t192 = sin(t2);
    real_type t197 = X__[iX_x2];
    real_type t198 = sin(t197);
    real_type t199 = P__[iP_u2];
    real_type t203 = sin(t7);
    real_type t208 = X__[iX_x3];
    real_type t209 = sin(t208);
    real_type t210 = P__[iP_u3];
    real_type t214 = sin(t152);
    real_type t219 = X__[iX_x4];
    real_type t220 = sin(t219);
    real_type t221 = P__[iP_u4];
    real_type t224 = t137 * MU__[12] + t140 * MU__[13] + t143 * MU__[14] + t146 * MU__[15] + t149 * MU__[16] + t119 * MU__[17] + t122 * MU__[18] + t126 * MU__[19] + (t187 + t188) * MU__[20] + (0.2e0 * t192 + t188) * MU__[60] + (t198 + t199) * MU__[21] + (0.2e0 * t203 + t199) * MU__[61] + (t209 + t210) * MU__[22] + (0.2e0 * t214 + t210) * MU__[62] + (t220 + t221) * MU__[23];
    real_type t226 = sin(t157);
    real_type t231 = X__[iX_x5];
    real_type t232 = sin(t231);
    real_type t233 = P__[iP_u5];
    real_type t237 = sin(t65);
    real_type t242 = X__[iX_x6];
    real_type t243 = sin(t242);
    real_type t244 = P__[iP_u6];
    real_type t248 = sin(t70);
    real_type t253 = X__[iX_xx15];
    real_type t254 = sin(t253);
    real_type t256 = P__[iP_u15];
    real_type t260 = X__[iX_x16];
    real_type t261 = sin(t260);
    real_type t262 = P__[iP_u16];
    real_type t266 = X__[iX_xx16];
    real_type t267 = sin(t266);
    real_type t272 = X__[iX_x17];
    real_type t273 = sin(t272);
    real_type t274 = P__[iP_u17];
    real_type t278 = X__[iX_xx17];
    real_type t279 = sin(t278);
    real_type t284 = X__[iX_x18];
    real_type t285 = sin(t284);
    real_type t286 = P__[iP_u18];
    real_type t290 = X__[iX_xx18];
    real_type t291 = sin(t290);
    real_type t296 = X__[iX_x19];
    real_type t297 = sin(t296);
    real_type t298 = P__[iP_u19];
    real_type t302 = X__[iX_xx19];
    real_type t303 = sin(t302);
    real_type t308 = X__[iX_x20];
    real_type t309 = sin(t308);
    real_type t310 = P__[iP_u20];
    real_type t313 = (0.2e0 * t226 + t221) * MU__[63] + (t232 + t233) * MU__[24] + (0.2e0 * t237 + t233) * MU__[64] + (t243 + t244) * MU__[25] + (0.2e0 * t248 + t244) * MU__[65] + (0.2e0 * t254 + t256) * MU__[74] + (t261 + t262) * MU__[35] + (0.2e0 * t267 + t262) * MU__[75] + (t273 + t274) * MU__[36] + (0.2e0 * t279 + t274) * MU__[76] + (t285 + t286) * MU__[37] + (0.2e0 * t291 + t286) * MU__[77] + (t297 + t298) * MU__[38] + (0.2e0 * t303 + t298) * MU__[78] + (t309 + t310) * MU__[39];
    real_type t316 = sin(t22);
    real_type t322 = Q__[iQ_zeta];
    real_type t323 = sin(t322);
    real_type t330 = sin(t322 + 1);
    real_type t337 = sin(t322 + 2);
    real_type t344 = sin(t322 + 3);
    real_type t349 = X__[iX_yy5];
    real_type t352 = sin(t322 + 4);
    real_type t359 = sin(t322 + 5);
    real_type t366 = sin(t322 + 6);
    real_type t373 = sin(t322 + 7);
    real_type t378 = X__[iX_yy9];
    real_type t381 = sin(t322 + 8);
    real_type t386 = X__[iX_yy10];
    real_type t389 = sin(t322 + 9);
    real_type t394 = X__[iX_yy11];
    real_type t397 = sin(t322 + 10);
    real_type t402 = X__[iX_yy12];
    real_type t405 = sin(t322 + 11);
    real_type t410 = X__[iX_yy13];
    real_type t413 = sin(t322 + 12);
    real_type t418 = X__[iX_yy14];
    real_type t421 = sin(t322 + 13);
    real_type t425 = (0.2e0 * t316 + t310) * MU__[79] + (0.12e1 * t25 + 0.1e0 * t323) * MU__[40] + (0.12e1 * t30 + 0.1e0 * t330) * MU__[41] + (0.12e1 * t111 + 0.1e0 * t337) * MU__[42] + (0.12e1 * t116 + 0.1e0 * t344) * MU__[43] + (0.12e1 * t349 + 0.1e0 * t352) * MU__[44] + (0.12e1 * t54 + 0.1e0 * t359) * MU__[45] + (0.12e1 * t57 + 0.1e0 * t366) * MU__[46] + (0.12e1 * t62 + 0.1e0 * t373) * MU__[47] + (0.12e1 * t378 + 0.1e0 * t381) * MU__[48] + (0.12e1 * t386 + 0.1e0 * t389) * MU__[49] + (0.12e1 * t394 + 0.1e0 * t397) * MU__[50] + (0.12e1 * t402 + 0.1e0 * t405) * MU__[51] + (0.12e1 * t410 + 0.1e0 * t413) * MU__[52] + (0.12e1 * t418 + 0.1e0 * t421) * MU__[53];
    real_type t427 = X__[iX_yy15];
    real_type t430 = sin(t322 + 14);
    real_type t435 = X__[iX_yy16];
    real_type t438 = sin(t322 + 15);
    real_type t443 = X__[iX_yy17];
    real_type t446 = sin(t322 + 16);
    real_type t451 = X__[iX_yy18];
    real_type t454 = sin(t322 + 17);
    real_type t461 = sin(t322 + 18);
    real_type t468 = sin(t322 + 19);
    real_type t473 = X__[iX_x7];
    real_type t474 = sin(t473);
    real_type t475 = P__[iP_u7];
    real_type t479 = sin(t12);
    real_type t484 = X__[iX_x8];
    real_type t485 = sin(t484);
    real_type t486 = P__[iP_u8];
    real_type t490 = sin(t17);
    real_type t495 = X__[iX_x9];
    real_type t496 = sin(t495);
    real_type t497 = P__[iP_u9];
    real_type t501 = sin(t44);
    real_type t506 = X__[iX_x10];
    real_type t507 = sin(t506);
    real_type t508 = P__[iP_u10];
    real_type t512 = sin(t49);
    real_type t517 = X__[iX_x11];
    real_type t518 = sin(t517);
    real_type t519 = P__[iP_u11];
    real_type t522 = (0.12e1 * t427 + 0.1e0 * t430) * MU__[54] + (0.12e1 * t435 + 0.1e0 * t438) * MU__[55] + (0.12e1 * t443 + 0.1e0 * t446) * MU__[56] + (0.12e1 * t451 + 0.1e0 * t454) * MU__[57] + (0.12e1 * t33 + 0.1e0 * t461) * MU__[58] + (0.12e1 * t38 + 0.1e0 * t468) * MU__[59] + (t474 + t475) * MU__[26] + (0.2e0 * t479 + t475) * MU__[66] + (t485 + t486) * MU__[27] + (0.2e0 * t490 + t486) * MU__[67] + (t496 + t497) * MU__[28] + (0.2e0 * t501 + t497) * MU__[68] + (t507 + t508) * MU__[29] + (0.2e0 * t512 + t508) * MU__[69] + (t518 + t519) * MU__[30];
    real_type t527 = sin(t75);
    real_type t532 = X__[iX_x12];
    real_type t533 = sin(t532);
    real_type t534 = P__[iP_u12];
    real_type t538 = sin(t82);
    real_type t543 = X__[iX_x13];
    real_type t544 = sin(t543);
    real_type t545 = P__[iP_u13];
    real_type t549 = X__[iX_xx13];
    real_type t550 = sin(t549);
    real_type t555 = X__[iX_x14];
    real_type t556 = sin(t555);
    real_type t557 = P__[iP_u14];
    real_type t561 = X__[iX_xx14];
    real_type t562 = sin(t561);
    real_type t567 = X__[iX_x15];
    real_type t568 = sin(t567);
    real_type t572 = X__[iX_y1];
    real_type t586 = (0.2e0 * t527 + t519) * MU__[70] + (t533 + t534) * MU__[31] + (0.2e0 * t538 + t534) * MU__[71] + (t544 + t545) * MU__[32] + (0.2e0 * t550 + t545) * MU__[72] + (t556 + t557) * MU__[33] + (0.2e0 * t562 + t557) * MU__[73] + (t568 + t256) * MU__[34] + t572 * MU__[0] + t85 * MU__[1] + t88 * MU__[2] + t91 * MU__[3] + t94 * MU__[4] + t97 * MU__[5] + t100 * MU__[6];
    real_type t594 = yy4Limitation_max(t116 - t1);
    real_type t596 = yy5Limitation_min(-t1 - t349);
    real_type t598 = yy5Limitation_max(t349 - t1);
    real_type t600 = yy6Limitation_min(-t1 - t54);
    real_type t601 = t543 * t543;
    real_type t603 = t555 * t555;
    real_type t605 = t567 * t567;
    real_type t607 = t260 * t260;
    real_type t609 = t272 * t272;
    real_type t611 = t284 * t284;
    real_type t613 = t296 * t296;
    real_type t615 = t308 * t308;
    real_type t616 = t103 * MU__[7] + t106 * MU__[8] + t128 * MU__[9] + t594 + t596 + t598 + t600 + 8 * t601 + 7 * t603 + 6 * t605 + 5 * t607 + 4 * t609 + 3 * t611 + 2 * t613 + t615;
    real_type t618 = t572 * t572;
    real_type t621 = yy17Limitation_min(-t1 - t443);
    real_type t623 = yy17Limitation_max(t443 - t1);
    real_type t625 = yy18Limitation_min(-t1 - t451);
    real_type t627 = yy18Limitation_max(t451 - t1);
    real_type t629 = yy10Limitation_max(t386 - t1);
    real_type t631 = yy11Limitation_min(-t1 - t394);
    real_type t633 = yy11Limitation_max(t394 - t1);
    real_type t635 = yy12Limitation_min(-t1 - t402);
    real_type t637 = xx12Limitation_max(t82 - t1);
    real_type t639 = xx13Limitation_min(-t1 - t549);
    real_type t641 = xx13Limitation_max(t549 - t1);
    real_type t643 = xx14Limitation_min(-t1 - t561);
    real_type t645 = xx18Limitation_max(t290 - t1);
    real_type t647 = xx19Limitation_min(-t1 - t302);
    real_type t648 = 20 * t618 + t621 + t623 + t625 + t627 + t629 + t631 + t633 + t635 + t637 + t639 + t641 + t643 + t645 + t647;
    real_type t650 = xx19Limitation_max(t302 - t1);
    real_type t652 = xx20Limitation_min(-t1 - t22);
    real_type t654 = xx14Limitation_max(t561 - t1);
    real_type t656 = xx15Limitation_min(-t1 - t253);
    real_type t658 = xx15Limitation_max(t253 - t1);
    real_type t660 = xx16Limitation_min(-t1 - t266);
    real_type t662 = yy8Limitation_max(t62 - t1);
    real_type t664 = yy9Limitation_min(-t1 - t378);
    real_type t666 = yy9Limitation_max(t378 - t1);
    real_type t668 = yy10Limitation_min(-t1 - t386);
    real_type t670 = xx16Limitation_max(t266 - t1);
    real_type t672 = xx17Limitation_min(-t1 - t278);
    real_type t674 = xx17Limitation_max(t278 - t1);
    real_type t676 = xx18Limitation_min(-t1 - t290);
    real_type t677 = t242 * t242;
    real_type t679 = t650 + t652 + t654 + t656 + t658 + t660 + t662 + t664 + t666 + t668 + t670 + t672 + t674 + t676 + 15 * t677;
    real_type t682 = t473 * t473;
    real_type t684 = t484 * t484;
    real_type t686 = t495 * t495;
    real_type t688 = t506 * t506;
    real_type t690 = t517 * t517;
    real_type t692 = t532 * t532;
    real_type t695 = u19Limitation_max(t298 - 10);
    real_type t697 = u20Limitation_min(-10 - t310);
    real_type t699 = u20Limitation_max(t310 - 10);
    real_type t701 = u17Limitation_min(-10 - t274);
    real_type t703 = u17Limitation_max(t274 - 10);
    real_type t705 = u18Limitation_min(-10 - t286);
    real_type t707 = u18Limitation_max(t286 - 10);
    real_type t709 = u19Limitation_min(-10 - t298);
    real_type t711 = u15Limitation_min(-10 - t256);
    real_type t712 = 14 * t682 + 13 * t684 + 12 * t686 + 11 * t688 + 10 * t690 + 9 * t692 + t695 + t697 + t699 + t701 + t703 + t705 + t707 + t709 + t711;
    real_type t714 = u15Limitation_max(t256 - 10);
    real_type t716 = u16Limitation_min(-10 - t262);
    real_type t718 = u16Limitation_max(t262 - 10);
    real_type t720 = u12Limitation_max(t534 - 10);
    real_type t722 = u13Limitation_min(-10 - t545);
    real_type t724 = u13Limitation_max(t545 - 10);
    real_type t726 = u14Limitation_min(-10 - t557);
    real_type t728 = u14Limitation_max(t557 - 10);
    real_type t730 = u10Limitation_min(-10 - t508);
    real_type t732 = u10Limitation_max(t508 - 10);
    real_type t734 = u11Limitation_min(-10 - t519);
    real_type t736 = u11Limitation_max(t519 - 10);
    real_type t738 = u12Limitation_min(-10 - t534);
    real_type t740 = u7Limitation_max(t475 - 10);
    real_type t742 = u8Limitation_min(-10 - t486);
    real_type t743 = t714 + t716 + t718 + t720 + t722 + t724 + t726 + t728 + t730 + t732 + t734 + t736 + t738 + t740 + t742;
    real_type t746 = u8Limitation_max(t486 - 10);
    real_type t748 = u9Limitation_min(-10 - t497);
    real_type t750 = u9Limitation_max(t497 - 10);
    real_type t752 = u5Limitation_max(t233 - 10);
    real_type t754 = u5Limitation_min(-10 - t233);
    real_type t756 = u6Limitation_min(-10 - t244);
    real_type t758 = u6Limitation_max(t244 - 10);
    real_type t760 = u7Limitation_min(-10 - t475);
    real_type t762 = u2Limitation_max(t199 - 10);
    real_type t764 = u3Limitation_min(-10 - t210);
    real_type t766 = u3Limitation_max(t210 - 10);
    real_type t768 = u4Limitation_min(-10 - t221);
    real_type t770 = u4Limitation_max(t221 - 10);
    real_type t771 = t186 * t186;
    real_type t773 = t197 * t197;
    real_type t775 = t746 + t748 + t750 + t752 + t754 + t756 + t758 + t760 + t762 + t764 + t766 + t768 + t770 + 20 * t771 + 19 * t773;
    real_type t776 = t208 * t208;
    real_type t778 = t219 * t219;
    real_type t780 = t231 * t231;
    real_type t783 = yy16Limitation_max(t435 - t1);
    real_type t785 = u1Limitation_min(-10 - t188);
    real_type t787 = u1Limitation_max(t188 - 10);
    real_type t789 = u2Limitation_min(-10 - t199);
    real_type t791 = yy14Limitation_max(t418 - t1);
    real_type t793 = yy15Limitation_min(-t1 - t427);
    real_type t795 = yy15Limitation_max(t427 - t1);
    real_type t797 = yy16Limitation_min(-t1 - t435);
    real_type t799 = yy12Limitation_max(t402 - t1);
    real_type t801 = yy13Limitation_min(-t1 - t410);
    real_type t803 = yy13Limitation_max(t410 - t1);
    real_type t805 = yy14Limitation_min(-t1 - t418);
    real_type t806 = 18 * t776 + 17 * t778 + 16 * t780 + t783 + t785 + t787 + t789 + t791 + t793 + t795 + t797 + t799 + t801 + t803 + t805;
    real_type result__ = t41 + t80 + t125 + t166 + t224 + t313 + t425 + t522 + t586 + t616 + t648 + t679 + t712 + t743 + t775 + t806;
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
