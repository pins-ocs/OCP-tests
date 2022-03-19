/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_ODE.cc                             |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ICLOCS_ContinuousMP::rhs_ode_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_y1];
    result__[ 1   ] = X__[iX_y2];
    result__[ 2   ] = X__[iX_y3];
    result__[ 3   ] = X__[iX_y4];
    result__[ 4   ] = X__[iX_y5];
    result__[ 5   ] = X__[iX_y6];
    result__[ 6   ] = X__[iX_y7];
    result__[ 7   ] = X__[iX_y8];
    result__[ 8   ] = X__[iX_y9];
    result__[ 9   ] = X__[iX_y10];
    result__[ 10  ] = X__[iX_y11];
    result__[ 11  ] = X__[iX_y12];
    result__[ 12  ] = X__[iX_y13];
    result__[ 13  ] = X__[iX_y14];
    result__[ 14  ] = X__[iX_y15];
    result__[ 15  ] = X__[iX_y16];
    result__[ 16  ] = X__[iX_y17];
    result__[ 17  ] = X__[iX_y18];
    result__[ 18  ] = X__[iX_y19];
    result__[ 19  ] = X__[iX_y20];
    real_type t2   = sin(X__[iX_x1]);
    real_type t3   = P__[iP_u1];
    result__[ 20  ] = t2 + t3;
    real_type t5   = sin(X__[iX_x2]);
    real_type t6   = P__[iP_u2];
    result__[ 21  ] = t5 + t6;
    real_type t8   = sin(X__[iX_x3]);
    real_type t9   = P__[iP_u3];
    result__[ 22  ] = t8 + t9;
    real_type t11  = sin(X__[iX_x4]);
    real_type t12  = P__[iP_u4];
    result__[ 23  ] = t11 + t12;
    real_type t14  = sin(X__[iX_x5]);
    real_type t15  = P__[iP_u5];
    result__[ 24  ] = t14 + t15;
    real_type t17  = sin(X__[iX_x6]);
    real_type t18  = P__[iP_u6];
    result__[ 25  ] = t17 + t18;
    real_type t20  = sin(X__[iX_x7]);
    real_type t21  = P__[iP_u7];
    result__[ 26  ] = t20 + t21;
    real_type t23  = sin(X__[iX_x8]);
    real_type t24  = P__[iP_u8];
    result__[ 27  ] = t23 + t24;
    real_type t26  = sin(X__[iX_x9]);
    real_type t27  = P__[iP_u9];
    result__[ 28  ] = t26 + t27;
    real_type t29  = sin(X__[iX_x10]);
    real_type t30  = P__[iP_u10];
    result__[ 29  ] = t29 + t30;
    real_type t32  = sin(X__[iX_x11]);
    real_type t33  = P__[iP_u11];
    result__[ 30  ] = t32 + t33;
    real_type t35  = sin(X__[iX_x12]);
    real_type t36  = P__[iP_u12];
    result__[ 31  ] = t35 + t36;
    real_type t38  = sin(X__[iX_x13]);
    real_type t39  = P__[iP_u13];
    result__[ 32  ] = t38 + t39;
    real_type t41  = sin(X__[iX_x14]);
    real_type t42  = P__[iP_u14];
    result__[ 33  ] = t41 + t42;
    real_type t44  = sin(X__[iX_x15]);
    real_type t45  = P__[iP_u15];
    result__[ 34  ] = t44 + t45;
    real_type t47  = sin(X__[iX_x16]);
    real_type t48  = P__[iP_u16];
    result__[ 35  ] = t47 + t48;
    real_type t50  = sin(X__[iX_x17]);
    real_type t51  = P__[iP_u17];
    result__[ 36  ] = t50 + t51;
    real_type t53  = sin(X__[iX_x18]);
    real_type t54  = P__[iP_u18];
    result__[ 37  ] = t53 + t54;
    real_type t56  = sin(X__[iX_x19]);
    real_type t57  = P__[iP_u19];
    result__[ 38  ] = t56 + t57;
    real_type t59  = sin(X__[iX_x20]);
    real_type t60  = P__[iP_u20];
    result__[ 39  ] = t59 + t60;
    real_type t63  = Q__[iQ_zeta];
    real_type t64  = sin(t63);
    result__[ 40  ] = 0.12e1 * X__[iX_yy1] + 0.1e0 * t64;
    real_type t69  = sin(t63 + 1);
    result__[ 41  ] = 0.12e1 * X__[iX_yy2] + 0.1e0 * t69;
    real_type t74  = sin(t63 + 2);
    result__[ 42  ] = 0.12e1 * X__[iX_yy3] + 0.1e0 * t74;
    real_type t79  = sin(t63 + 3);
    result__[ 43  ] = 0.12e1 * X__[iX_yy4] + 0.1e0 * t79;
    real_type t84  = sin(t63 + 4);
    result__[ 44  ] = 0.12e1 * X__[iX_yy5] + 0.1e0 * t84;
    real_type t89  = sin(t63 + 5);
    result__[ 45  ] = 0.12e1 * X__[iX_yy6] + 0.1e0 * t89;
    real_type t94  = sin(t63 + 6);
    result__[ 46  ] = 0.12e1 * X__[iX_yy7] + 0.1e0 * t94;
    real_type t99  = sin(t63 + 7);
    result__[ 47  ] = 0.12e1 * X__[iX_yy8] + 0.1e0 * t99;
    real_type t104 = sin(t63 + 8);
    result__[ 48  ] = 0.12e1 * X__[iX_yy9] + 0.1e0 * t104;
    real_type t109 = sin(t63 + 9);
    result__[ 49  ] = 0.12e1 * X__[iX_yy10] + 0.1e0 * t109;
    real_type t114 = sin(t63 + 10);
    result__[ 50  ] = 0.12e1 * X__[iX_yy11] + 0.1e0 * t114;
    real_type t119 = sin(t63 + 11);
    result__[ 51  ] = 0.12e1 * X__[iX_yy12] + 0.1e0 * t119;
    real_type t124 = sin(t63 + 12);
    result__[ 52  ] = 0.12e1 * X__[iX_yy13] + 0.1e0 * t124;
    real_type t129 = sin(t63 + 13);
    result__[ 53  ] = 0.12e1 * X__[iX_yy14] + 0.1e0 * t129;
    real_type t134 = sin(t63 + 14);
    result__[ 54  ] = 0.12e1 * X__[iX_yy15] + 0.1e0 * t134;
    real_type t139 = sin(t63 + 15);
    result__[ 55  ] = 0.12e1 * X__[iX_yy16] + 0.1e0 * t139;
    real_type t144 = sin(t63 + 16);
    result__[ 56  ] = 0.12e1 * X__[iX_yy17] + 0.1e0 * t144;
    real_type t149 = sin(t63 + 17);
    result__[ 57  ] = 0.12e1 * X__[iX_yy18] + 0.1e0 * t149;
    real_type t154 = sin(t63 + 18);
    result__[ 58  ] = 0.12e1 * X__[iX_yy19] + 0.1e0 * t154;
    real_type t159 = sin(t63 + 19);
    result__[ 59  ] = 0.12e1 * X__[iX_yy20] + 0.1e0 * t159;
    real_type t162 = sin(X__[iX_xx1]);
    result__[ 60  ] = 0.2e0 * t162 + t3;
    real_type t165 = sin(X__[iX_xx2]);
    result__[ 61  ] = 0.2e0 * t165 + t6;
    real_type t168 = sin(X__[iX_xx3]);
    result__[ 62  ] = 0.2e0 * t168 + t9;
    real_type t171 = sin(X__[iX_xx4]);
    result__[ 63  ] = 0.2e0 * t171 + t12;
    real_type t174 = sin(X__[iX_xx5]);
    result__[ 64  ] = 0.2e0 * t174 + t15;
    real_type t177 = sin(X__[iX_xx6]);
    result__[ 65  ] = 0.2e0 * t177 + t18;
    real_type t180 = sin(X__[iX_xx7]);
    result__[ 66  ] = 0.2e0 * t180 + t21;
    real_type t183 = sin(X__[iX_xx8]);
    result__[ 67  ] = 0.2e0 * t183 + t24;
    real_type t186 = sin(X__[iX_xx9]);
    result__[ 68  ] = 0.2e0 * t186 + t27;
    real_type t189 = sin(X__[iX_xx10]);
    result__[ 69  ] = 0.2e0 * t189 + t30;
    real_type t192 = sin(X__[iX_xx11]);
    result__[ 70  ] = 0.2e0 * t192 + t33;
    real_type t195 = sin(X__[iX_xx12]);
    result__[ 71  ] = 0.2e0 * t195 + t36;
    real_type t198 = sin(X__[iX_xx13]);
    result__[ 72  ] = 0.2e0 * t198 + t39;
    real_type t201 = sin(X__[iX_xx14]);
    result__[ 73  ] = 0.2e0 * t201 + t42;
    real_type t204 = sin(X__[iX_xx15]);
    result__[ 74  ] = 0.2e0 * t204 + t45;
    real_type t207 = sin(X__[iX_xx16]);
    result__[ 75  ] = 0.2e0 * t207 + t48;
    real_type t210 = sin(X__[iX_xx17]);
    result__[ 76  ] = 0.2e0 * t210 + t51;
    real_type t213 = sin(X__[iX_xx18]);
    result__[ 77  ] = 0.2e0 * t213 + t54;
    real_type t216 = sin(X__[iX_xx19]);
    result__[ 78  ] = 0.2e0 * t216 + t57;
    real_type t219 = sin(X__[iX_xx20]);
    result__[ 79  ] = 0.2e0 * t219 + t60;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::Drhs_odeDxup_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::Drhs_odeDxup_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::Drhs_odeDxup_nnz()     const { return 120; }

  void
  ICLOCS_ContinuousMP::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 20  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 21  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 22  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 23  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 24  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 25  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 26  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 27  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 28  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 29  ;
    iIndex[10] = 10  ; jIndex[10] = 30  ;
    iIndex[11] = 11  ; jIndex[11] = 31  ;
    iIndex[12] = 12  ; jIndex[12] = 32  ;
    iIndex[13] = 13  ; jIndex[13] = 33  ;
    iIndex[14] = 14  ; jIndex[14] = 34  ;
    iIndex[15] = 15  ; jIndex[15] = 35  ;
    iIndex[16] = 16  ; jIndex[16] = 36  ;
    iIndex[17] = 17  ; jIndex[17] = 37  ;
    iIndex[18] = 18  ; jIndex[18] = 38  ;
    iIndex[19] = 19  ; jIndex[19] = 39  ;
    iIndex[20] = 20  ; jIndex[20] = 0   ;
    iIndex[21] = 20  ; jIndex[21] = 80  ;
    iIndex[22] = 21  ; jIndex[22] = 1   ;
    iIndex[23] = 21  ; jIndex[23] = 81  ;
    iIndex[24] = 22  ; jIndex[24] = 2   ;
    iIndex[25] = 22  ; jIndex[25] = 82  ;
    iIndex[26] = 23  ; jIndex[26] = 3   ;
    iIndex[27] = 23  ; jIndex[27] = 83  ;
    iIndex[28] = 24  ; jIndex[28] = 4   ;
    iIndex[29] = 24  ; jIndex[29] = 84  ;
    iIndex[30] = 25  ; jIndex[30] = 5   ;
    iIndex[31] = 25  ; jIndex[31] = 85  ;
    iIndex[32] = 26  ; jIndex[32] = 6   ;
    iIndex[33] = 26  ; jIndex[33] = 86  ;
    iIndex[34] = 27  ; jIndex[34] = 7   ;
    iIndex[35] = 27  ; jIndex[35] = 87  ;
    iIndex[36] = 28  ; jIndex[36] = 8   ;
    iIndex[37] = 28  ; jIndex[37] = 88  ;
    iIndex[38] = 29  ; jIndex[38] = 9   ;
    iIndex[39] = 29  ; jIndex[39] = 89  ;
    iIndex[40] = 30  ; jIndex[40] = 10  ;
    iIndex[41] = 30  ; jIndex[41] = 90  ;
    iIndex[42] = 31  ; jIndex[42] = 11  ;
    iIndex[43] = 31  ; jIndex[43] = 91  ;
    iIndex[44] = 32  ; jIndex[44] = 12  ;
    iIndex[45] = 32  ; jIndex[45] = 92  ;
    iIndex[46] = 33  ; jIndex[46] = 13  ;
    iIndex[47] = 33  ; jIndex[47] = 93  ;
    iIndex[48] = 34  ; jIndex[48] = 14  ;
    iIndex[49] = 34  ; jIndex[49] = 94  ;
    iIndex[50] = 35  ; jIndex[50] = 15  ;
    iIndex[51] = 35  ; jIndex[51] = 95  ;
    iIndex[52] = 36  ; jIndex[52] = 16  ;
    iIndex[53] = 36  ; jIndex[53] = 96  ;
    iIndex[54] = 37  ; jIndex[54] = 17  ;
    iIndex[55] = 37  ; jIndex[55] = 97  ;
    iIndex[56] = 38  ; jIndex[56] = 18  ;
    iIndex[57] = 38  ; jIndex[57] = 98  ;
    iIndex[58] = 39  ; jIndex[58] = 19  ;
    iIndex[59] = 39  ; jIndex[59] = 99  ;
    iIndex[60] = 40  ; jIndex[60] = 60  ;
    iIndex[61] = 41  ; jIndex[61] = 61  ;
    iIndex[62] = 42  ; jIndex[62] = 62  ;
    iIndex[63] = 43  ; jIndex[63] = 63  ;
    iIndex[64] = 44  ; jIndex[64] = 64  ;
    iIndex[65] = 45  ; jIndex[65] = 65  ;
    iIndex[66] = 46  ; jIndex[66] = 66  ;
    iIndex[67] = 47  ; jIndex[67] = 67  ;
    iIndex[68] = 48  ; jIndex[68] = 68  ;
    iIndex[69] = 49  ; jIndex[69] = 69  ;
    iIndex[70] = 50  ; jIndex[70] = 70  ;
    iIndex[71] = 51  ; jIndex[71] = 71  ;
    iIndex[72] = 52  ; jIndex[72] = 72  ;
    iIndex[73] = 53  ; jIndex[73] = 73  ;
    iIndex[74] = 54  ; jIndex[74] = 74  ;
    iIndex[75] = 55  ; jIndex[75] = 75  ;
    iIndex[76] = 56  ; jIndex[76] = 76  ;
    iIndex[77] = 57  ; jIndex[77] = 77  ;
    iIndex[78] = 58  ; jIndex[78] = 78  ;
    iIndex[79] = 59  ; jIndex[79] = 79  ;
    iIndex[80] = 60  ; jIndex[80] = 40  ;
    iIndex[81] = 60  ; jIndex[81] = 80  ;
    iIndex[82] = 61  ; jIndex[82] = 41  ;
    iIndex[83] = 61  ; jIndex[83] = 81  ;
    iIndex[84] = 62  ; jIndex[84] = 42  ;
    iIndex[85] = 62  ; jIndex[85] = 82  ;
    iIndex[86] = 63  ; jIndex[86] = 43  ;
    iIndex[87] = 63  ; jIndex[87] = 83  ;
    iIndex[88] = 64  ; jIndex[88] = 44  ;
    iIndex[89] = 64  ; jIndex[89] = 84  ;
    iIndex[90] = 65  ; jIndex[90] = 45  ;
    iIndex[91] = 65  ; jIndex[91] = 85  ;
    iIndex[92] = 66  ; jIndex[92] = 46  ;
    iIndex[93] = 66  ; jIndex[93] = 86  ;
    iIndex[94] = 67  ; jIndex[94] = 47  ;
    iIndex[95] = 67  ; jIndex[95] = 87  ;
    iIndex[96] = 68  ; jIndex[96] = 48  ;
    iIndex[97] = 68  ; jIndex[97] = 88  ;
    iIndex[98] = 69  ; jIndex[98] = 49  ;
    iIndex[99] = 69  ; jIndex[99] = 89  ;
    iIndex[100] = 70  ; jIndex[100] = 50  ;
    iIndex[101] = 70  ; jIndex[101] = 90  ;
    iIndex[102] = 71  ; jIndex[102] = 51  ;
    iIndex[103] = 71  ; jIndex[103] = 91  ;
    iIndex[104] = 72  ; jIndex[104] = 52  ;
    iIndex[105] = 72  ; jIndex[105] = 92  ;
    iIndex[106] = 73  ; jIndex[106] = 53  ;
    iIndex[107] = 73  ; jIndex[107] = 93  ;
    iIndex[108] = 74  ; jIndex[108] = 54  ;
    iIndex[109] = 74  ; jIndex[109] = 94  ;
    iIndex[110] = 75  ; jIndex[110] = 55  ;
    iIndex[111] = 75  ; jIndex[111] = 95  ;
    iIndex[112] = 76  ; jIndex[112] = 56  ;
    iIndex[113] = 76  ; jIndex[113] = 96  ;
    iIndex[114] = 77  ; jIndex[114] = 57  ;
    iIndex[115] = 77  ; jIndex[115] = 97  ;
    iIndex[116] = 78  ; jIndex[116] = 58  ;
    iIndex[117] = 78  ; jIndex[117] = 98  ;
    iIndex[118] = 79  ; jIndex[118] = 59  ;
    iIndex[119] = 79  ; jIndex[119] = 99  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    result__[ 9   ] = 1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    result__[ 12  ] = 1;
    result__[ 13  ] = 1;
    result__[ 14  ] = 1;
    result__[ 15  ] = 1;
    result__[ 16  ] = 1;
    result__[ 17  ] = 1;
    result__[ 18  ] = 1;
    result__[ 19  ] = 1;
    result__[ 20  ] = cos(X__[iX_x1]);
    result__[ 21  ] = 1;
    result__[ 22  ] = cos(X__[iX_x2]);
    result__[ 23  ] = 1;
    result__[ 24  ] = cos(X__[iX_x3]);
    result__[ 25  ] = 1;
    result__[ 26  ] = cos(X__[iX_x4]);
    result__[ 27  ] = 1;
    result__[ 28  ] = cos(X__[iX_x5]);
    result__[ 29  ] = 1;
    result__[ 30  ] = cos(X__[iX_x6]);
    result__[ 31  ] = 1;
    result__[ 32  ] = cos(X__[iX_x7]);
    result__[ 33  ] = 1;
    result__[ 34  ] = cos(X__[iX_x8]);
    result__[ 35  ] = 1;
    result__[ 36  ] = cos(X__[iX_x9]);
    result__[ 37  ] = 1;
    result__[ 38  ] = cos(X__[iX_x10]);
    result__[ 39  ] = 1;
    result__[ 40  ] = cos(X__[iX_x11]);
    result__[ 41  ] = 1;
    result__[ 42  ] = cos(X__[iX_x12]);
    result__[ 43  ] = 1;
    result__[ 44  ] = cos(X__[iX_x13]);
    result__[ 45  ] = 1;
    result__[ 46  ] = cos(X__[iX_x14]);
    result__[ 47  ] = 1;
    result__[ 48  ] = cos(X__[iX_x15]);
    result__[ 49  ] = 1;
    result__[ 50  ] = cos(X__[iX_x16]);
    result__[ 51  ] = 1;
    result__[ 52  ] = cos(X__[iX_x17]);
    result__[ 53  ] = 1;
    result__[ 54  ] = cos(X__[iX_x18]);
    result__[ 55  ] = 1;
    result__[ 56  ] = cos(X__[iX_x19]);
    result__[ 57  ] = 1;
    result__[ 58  ] = cos(X__[iX_x20]);
    result__[ 59  ] = 1;
    result__[ 60  ] = 0.12e1;
    result__[ 61  ] = 0.12e1;
    result__[ 62  ] = 0.12e1;
    result__[ 63  ] = 0.12e1;
    result__[ 64  ] = 0.12e1;
    result__[ 65  ] = 0.12e1;
    result__[ 66  ] = 0.12e1;
    result__[ 67  ] = 0.12e1;
    result__[ 68  ] = 0.12e1;
    result__[ 69  ] = 0.12e1;
    result__[ 70  ] = 0.12e1;
    result__[ 71  ] = 0.12e1;
    result__[ 72  ] = 0.12e1;
    result__[ 73  ] = 0.12e1;
    result__[ 74  ] = 0.12e1;
    result__[ 75  ] = 0.12e1;
    result__[ 76  ] = 0.12e1;
    result__[ 77  ] = 0.12e1;
    result__[ 78  ] = 0.12e1;
    result__[ 79  ] = 0.12e1;
    real_type t22  = cos(X__[iX_xx1]);
    result__[ 80  ] = 0.2e0 * t22;
    result__[ 81  ] = 1;
    real_type t24  = cos(X__[iX_xx2]);
    result__[ 82  ] = 0.2e0 * t24;
    result__[ 83  ] = 1;
    real_type t26  = cos(X__[iX_xx3]);
    result__[ 84  ] = 0.2e0 * t26;
    result__[ 85  ] = 1;
    real_type t28  = cos(X__[iX_xx4]);
    result__[ 86  ] = 0.2e0 * t28;
    result__[ 87  ] = 1;
    real_type t30  = cos(X__[iX_xx5]);
    result__[ 88  ] = 0.2e0 * t30;
    result__[ 89  ] = 1;
    real_type t32  = cos(X__[iX_xx6]);
    result__[ 90  ] = 0.2e0 * t32;
    result__[ 91  ] = 1;
    real_type t34  = cos(X__[iX_xx7]);
    result__[ 92  ] = 0.2e0 * t34;
    result__[ 93  ] = 1;
    real_type t36  = cos(X__[iX_xx8]);
    result__[ 94  ] = 0.2e0 * t36;
    result__[ 95  ] = 1;
    real_type t38  = cos(X__[iX_xx9]);
    result__[ 96  ] = 0.2e0 * t38;
    result__[ 97  ] = 1;
    real_type t40  = cos(X__[iX_xx10]);
    result__[ 98  ] = 0.2e0 * t40;
    result__[ 99  ] = 1;
    real_type t42  = cos(X__[iX_xx11]);
    result__[ 100 ] = 0.2e0 * t42;
    result__[ 101 ] = 1;
    real_type t44  = cos(X__[iX_xx12]);
    result__[ 102 ] = 0.2e0 * t44;
    result__[ 103 ] = 1;
    real_type t46  = cos(X__[iX_xx13]);
    result__[ 104 ] = 0.2e0 * t46;
    result__[ 105 ] = 1;
    real_type t48  = cos(X__[iX_xx14]);
    result__[ 106 ] = 0.2e0 * t48;
    result__[ 107 ] = 1;
    real_type t50  = cos(X__[iX_xx15]);
    result__[ 108 ] = 0.2e0 * t50;
    result__[ 109 ] = 1;
    real_type t52  = cos(X__[iX_xx16]);
    result__[ 110 ] = 0.2e0 * t52;
    result__[ 111 ] = 1;
    real_type t54  = cos(X__[iX_xx17]);
    result__[ 112 ] = 0.2e0 * t54;
    result__[ 113 ] = 1;
    real_type t56  = cos(X__[iX_xx18]);
    result__[ 114 ] = 0.2e0 * t56;
    result__[ 115 ] = 1;
    real_type t58  = cos(X__[iX_xx19]);
    result__[ 116 ] = 0.2e0 * t58;
    result__[ 117 ] = 1;
    real_type t60  = cos(X__[iX_xx20]);
    result__[ 118 ] = 0.2e0 * t60;
    result__[ 119 ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 120, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::A_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::A_numCols() const { return 80; }
  integer ICLOCS_ContinuousMP::A_nnz()     const { return 80; }

  void
  ICLOCS_ContinuousMP::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 9   ;
    iIndex[10] = 10  ; jIndex[10] = 10  ;
    iIndex[11] = 11  ; jIndex[11] = 11  ;
    iIndex[12] = 12  ; jIndex[12] = 12  ;
    iIndex[13] = 13  ; jIndex[13] = 13  ;
    iIndex[14] = 14  ; jIndex[14] = 14  ;
    iIndex[15] = 15  ; jIndex[15] = 15  ;
    iIndex[16] = 16  ; jIndex[16] = 16  ;
    iIndex[17] = 17  ; jIndex[17] = 17  ;
    iIndex[18] = 18  ; jIndex[18] = 18  ;
    iIndex[19] = 19  ; jIndex[19] = 19  ;
    iIndex[20] = 20  ; jIndex[20] = 20  ;
    iIndex[21] = 21  ; jIndex[21] = 21  ;
    iIndex[22] = 22  ; jIndex[22] = 22  ;
    iIndex[23] = 23  ; jIndex[23] = 23  ;
    iIndex[24] = 24  ; jIndex[24] = 24  ;
    iIndex[25] = 25  ; jIndex[25] = 25  ;
    iIndex[26] = 26  ; jIndex[26] = 26  ;
    iIndex[27] = 27  ; jIndex[27] = 27  ;
    iIndex[28] = 28  ; jIndex[28] = 28  ;
    iIndex[29] = 29  ; jIndex[29] = 29  ;
    iIndex[30] = 30  ; jIndex[30] = 30  ;
    iIndex[31] = 31  ; jIndex[31] = 31  ;
    iIndex[32] = 32  ; jIndex[32] = 32  ;
    iIndex[33] = 33  ; jIndex[33] = 33  ;
    iIndex[34] = 34  ; jIndex[34] = 34  ;
    iIndex[35] = 35  ; jIndex[35] = 35  ;
    iIndex[36] = 36  ; jIndex[36] = 36  ;
    iIndex[37] = 37  ; jIndex[37] = 37  ;
    iIndex[38] = 38  ; jIndex[38] = 38  ;
    iIndex[39] = 39  ; jIndex[39] = 39  ;
    iIndex[40] = 40  ; jIndex[40] = 40  ;
    iIndex[41] = 41  ; jIndex[41] = 41  ;
    iIndex[42] = 42  ; jIndex[42] = 42  ;
    iIndex[43] = 43  ; jIndex[43] = 43  ;
    iIndex[44] = 44  ; jIndex[44] = 44  ;
    iIndex[45] = 45  ; jIndex[45] = 45  ;
    iIndex[46] = 46  ; jIndex[46] = 46  ;
    iIndex[47] = 47  ; jIndex[47] = 47  ;
    iIndex[48] = 48  ; jIndex[48] = 48  ;
    iIndex[49] = 49  ; jIndex[49] = 49  ;
    iIndex[50] = 50  ; jIndex[50] = 50  ;
    iIndex[51] = 51  ; jIndex[51] = 51  ;
    iIndex[52] = 52  ; jIndex[52] = 52  ;
    iIndex[53] = 53  ; jIndex[53] = 53  ;
    iIndex[54] = 54  ; jIndex[54] = 54  ;
    iIndex[55] = 55  ; jIndex[55] = 55  ;
    iIndex[56] = 56  ; jIndex[56] = 56  ;
    iIndex[57] = 57  ; jIndex[57] = 57  ;
    iIndex[58] = 58  ; jIndex[58] = 58  ;
    iIndex[59] = 59  ; jIndex[59] = 59  ;
    iIndex[60] = 60  ; jIndex[60] = 60  ;
    iIndex[61] = 61  ; jIndex[61] = 61  ;
    iIndex[62] = 62  ; jIndex[62] = 62  ;
    iIndex[63] = 63  ; jIndex[63] = 63  ;
    iIndex[64] = 64  ; jIndex[64] = 64  ;
    iIndex[65] = 65  ; jIndex[65] = 65  ;
    iIndex[66] = 66  ; jIndex[66] = 66  ;
    iIndex[67] = 67  ; jIndex[67] = 67  ;
    iIndex[68] = 68  ; jIndex[68] = 68  ;
    iIndex[69] = 69  ; jIndex[69] = 69  ;
    iIndex[70] = 70  ; jIndex[70] = 70  ;
    iIndex[71] = 71  ; jIndex[71] = 71  ;
    iIndex[72] = 72  ; jIndex[72] = 72  ;
    iIndex[73] = 73  ; jIndex[73] = 73  ;
    iIndex[74] = 74  ; jIndex[74] = 74  ;
    iIndex[75] = 75  ; jIndex[75] = 75  ;
    iIndex[76] = 76  ; jIndex[76] = 76  ;
    iIndex[77] = 77  ; jIndex[77] = 77  ;
    iIndex[78] = 78  ; jIndex[78] = 78  ;
    iIndex[79] = 79  ; jIndex[79] = 79  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    result__[ 9   ] = 1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    result__[ 12  ] = 1;
    result__[ 13  ] = 1;
    result__[ 14  ] = 1;
    result__[ 15  ] = 1;
    result__[ 16  ] = 1;
    result__[ 17  ] = 1;
    result__[ 18  ] = 1;
    result__[ 19  ] = 1;
    result__[ 20  ] = 1;
    result__[ 21  ] = 1;
    result__[ 22  ] = 1;
    result__[ 23  ] = 1;
    result__[ 24  ] = 1;
    result__[ 25  ] = 1;
    result__[ 26  ] = 1;
    result__[ 27  ] = 1;
    result__[ 28  ] = 1;
    result__[ 29  ] = 1;
    result__[ 30  ] = 1;
    result__[ 31  ] = 1;
    result__[ 32  ] = 1;
    result__[ 33  ] = 1;
    result__[ 34  ] = 1;
    result__[ 35  ] = 1;
    result__[ 36  ] = 1;
    result__[ 37  ] = 1;
    result__[ 38  ] = 1;
    result__[ 39  ] = 1;
    result__[ 40  ] = 1;
    result__[ 41  ] = 1;
    result__[ 42  ] = 1;
    result__[ 43  ] = 1;
    result__[ 44  ] = 1;
    result__[ 45  ] = 1;
    result__[ 46  ] = 1;
    result__[ 47  ] = 1;
    result__[ 48  ] = 1;
    result__[ 49  ] = 1;
    result__[ 50  ] = 1;
    result__[ 51  ] = 1;
    result__[ 52  ] = 1;
    result__[ 53  ] = 1;
    result__[ 54  ] = 1;
    result__[ 55  ] = 1;
    result__[ 56  ] = 1;
    result__[ 57  ] = 1;
    result__[ 58  ] = 1;
    result__[ 59  ] = 1;
    result__[ 60  ] = 1;
    result__[ 61  ] = 1;
    result__[ 62  ] = 1;
    result__[ 63  ] = 1;
    result__[ 64  ] = 1;
    result__[ 65  ] = 1;
    result__[ 66  ] = 1;
    result__[ 67  ] = 1;
    result__[ 68  ] = 1;
    result__[ 69  ] = 1;
    result__[ 70  ] = 1;
    result__[ 71  ] = 1;
    result__[ 72  ] = 1;
    result__[ 73  ] = 1;
    result__[ 74  ] = 1;
    result__[ 75  ] = 1;
    result__[ 76  ] = 1;
    result__[ 77  ] = 1;
    result__[ 78  ] = 1;
    result__[ 79  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 80, i_segment );
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_ODE.cc
