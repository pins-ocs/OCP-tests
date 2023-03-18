/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_ODE.cc                             |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ICLOCS_ContinuousMP::ode_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_y1] - V__[0];
    result__[ 1   ] = X__[iX_y2] - V__[1];
    result__[ 2   ] = X__[iX_y3] - V__[2];
    result__[ 3   ] = X__[iX_y4] - V__[3];
    result__[ 4   ] = X__[iX_y5] - V__[4];
    result__[ 5   ] = X__[iX_y6] - V__[5];
    result__[ 6   ] = X__[iX_y7] - V__[6];
    result__[ 7   ] = X__[iX_y8] - V__[7];
    result__[ 8   ] = X__[iX_y9] - V__[8];
    result__[ 9   ] = X__[iX_y10] - V__[9];
    result__[ 10  ] = X__[iX_y11] - V__[10];
    result__[ 11  ] = X__[iX_y12] - V__[11];
    result__[ 12  ] = X__[iX_y13] - V__[12];
    result__[ 13  ] = X__[iX_y14] - V__[13];
    result__[ 14  ] = X__[iX_y15] - V__[14];
    result__[ 15  ] = X__[iX_y16] - V__[15];
    result__[ 16  ] = X__[iX_y17] - V__[16];
    result__[ 17  ] = X__[iX_y18] - V__[17];
    result__[ 18  ] = X__[iX_y19] - V__[18];
    result__[ 19  ] = X__[iX_y20] - V__[19];
    real_type t42  = sin(X__[iX_x1]);
    real_type t43  = P__[iP_u1];
    result__[ 20  ] = t42 + t43 - V__[20];
    real_type t46  = sin(X__[iX_x2]);
    real_type t47  = P__[iP_u2];
    result__[ 21  ] = t46 + t47 - V__[21];
    real_type t50  = sin(X__[iX_x3]);
    real_type t51  = P__[iP_u3];
    result__[ 22  ] = t50 + t51 - V__[22];
    real_type t54  = sin(X__[iX_x4]);
    real_type t55  = P__[iP_u4];
    result__[ 23  ] = t54 + t55 - V__[23];
    real_type t58  = sin(X__[iX_x5]);
    real_type t59  = P__[iP_u5];
    result__[ 24  ] = t58 + t59 - V__[24];
    real_type t62  = sin(X__[iX_x6]);
    real_type t63  = P__[iP_u6];
    result__[ 25  ] = t62 + t63 - V__[25];
    real_type t66  = sin(X__[iX_x7]);
    real_type t67  = P__[iP_u7];
    result__[ 26  ] = t66 + t67 - V__[26];
    real_type t70  = sin(X__[iX_x8]);
    real_type t71  = P__[iP_u8];
    result__[ 27  ] = t70 + t71 - V__[27];
    real_type t74  = sin(X__[iX_x9]);
    real_type t75  = P__[iP_u9];
    result__[ 28  ] = t74 + t75 - V__[28];
    real_type t78  = sin(X__[iX_x10]);
    real_type t79  = P__[iP_u10];
    result__[ 29  ] = t78 + t79 - V__[29];
    real_type t82  = sin(X__[iX_x11]);
    real_type t83  = P__[iP_u11];
    result__[ 30  ] = t82 + t83 - V__[30];
    real_type t86  = sin(X__[iX_x12]);
    real_type t87  = P__[iP_u12];
    result__[ 31  ] = t86 + t87 - V__[31];
    real_type t90  = sin(X__[iX_x13]);
    real_type t91  = P__[iP_u13];
    result__[ 32  ] = t90 + t91 - V__[32];
    real_type t94  = sin(X__[iX_x14]);
    real_type t95  = P__[iP_u14];
    result__[ 33  ] = t94 + t95 - V__[33];
    real_type t98  = sin(X__[iX_x15]);
    real_type t99  = P__[iP_u15];
    result__[ 34  ] = t98 + t99 - V__[34];
    real_type t102 = sin(X__[iX_x16]);
    real_type t103 = P__[iP_u16];
    result__[ 35  ] = t102 + t103 - V__[35];
    real_type t106 = sin(X__[iX_x17]);
    real_type t107 = P__[iP_u17];
    result__[ 36  ] = t106 + t107 - V__[36];
    real_type t110 = sin(X__[iX_x18]);
    real_type t111 = P__[iP_u18];
    result__[ 37  ] = t110 + t111 - V__[37];
    real_type t114 = sin(X__[iX_x19]);
    real_type t115 = P__[iP_u19];
    result__[ 38  ] = t114 + t115 - V__[38];
    real_type t118 = sin(X__[iX_x20]);
    real_type t119 = P__[iP_u20];
    result__[ 39  ] = t118 + t119 - V__[39];
    real_type t123 = Q__[iQ_zeta];
    real_type t124 = sin(t123);
    result__[ 40  ] = 0.12e1 * X__[iX_yy1] + 0.1e0 * t124 - V__[40];
    real_type t130 = sin(t123 + 1);
    result__[ 41  ] = 0.12e1 * X__[iX_yy2] + 0.1e0 * t130 - V__[41];
    real_type t136 = sin(t123 + 2);
    result__[ 42  ] = 0.12e1 * X__[iX_yy3] + 0.1e0 * t136 - V__[42];
    real_type t142 = sin(t123 + 3);
    result__[ 43  ] = 0.12e1 * X__[iX_yy4] + 0.1e0 * t142 - V__[43];
    real_type t148 = sin(t123 + 4);
    result__[ 44  ] = 0.12e1 * X__[iX_yy5] + 0.1e0 * t148 - V__[44];
    real_type t154 = sin(t123 + 5);
    result__[ 45  ] = 0.12e1 * X__[iX_yy6] + 0.1e0 * t154 - V__[45];
    real_type t160 = sin(t123 + 6);
    result__[ 46  ] = 0.12e1 * X__[iX_yy7] + 0.1e0 * t160 - V__[46];
    real_type t166 = sin(t123 + 7);
    result__[ 47  ] = 0.12e1 * X__[iX_yy8] + 0.1e0 * t166 - V__[47];
    real_type t172 = sin(t123 + 8);
    result__[ 48  ] = 0.12e1 * X__[iX_yy9] + 0.1e0 * t172 - V__[48];
    real_type t178 = sin(t123 + 9);
    result__[ 49  ] = 0.12e1 * X__[iX_yy10] + 0.1e0 * t178 - V__[49];
    real_type t184 = sin(t123 + 10);
    result__[ 50  ] = 0.12e1 * X__[iX_yy11] + 0.1e0 * t184 - V__[50];
    real_type t190 = sin(t123 + 11);
    result__[ 51  ] = 0.12e1 * X__[iX_yy12] + 0.1e0 * t190 - V__[51];
    real_type t196 = sin(t123 + 12);
    result__[ 52  ] = 0.12e1 * X__[iX_yy13] + 0.1e0 * t196 - V__[52];
    real_type t202 = sin(t123 + 13);
    result__[ 53  ] = 0.12e1 * X__[iX_yy14] + 0.1e0 * t202 - V__[53];
    real_type t208 = sin(t123 + 14);
    result__[ 54  ] = 0.12e1 * X__[iX_yy15] + 0.1e0 * t208 - V__[54];
    real_type t214 = sin(t123 + 15);
    result__[ 55  ] = 0.12e1 * X__[iX_yy16] + 0.1e0 * t214 - V__[55];
    real_type t220 = sin(t123 + 16);
    result__[ 56  ] = 0.12e1 * X__[iX_yy17] + 0.1e0 * t220 - V__[56];
    real_type t226 = sin(t123 + 17);
    result__[ 57  ] = 0.12e1 * X__[iX_yy18] + 0.1e0 * t226 - V__[57];
    real_type t232 = sin(t123 + 18);
    result__[ 58  ] = 0.12e1 * X__[iX_yy19] + 0.1e0 * t232 - V__[58];
    real_type t238 = sin(t123 + 19);
    result__[ 59  ] = 0.12e1 * X__[iX_yy20] + 0.1e0 * t238 - V__[59];
    real_type t242 = sin(X__[iX_xx1]);
    result__[ 60  ] = 0.2e0 * t242 + t43 - V__[60];
    real_type t246 = sin(X__[iX_xx2]);
    result__[ 61  ] = 0.2e0 * t246 + t47 - V__[61];
    real_type t250 = sin(X__[iX_xx3]);
    result__[ 62  ] = 0.2e0 * t250 + t51 - V__[62];
    real_type t254 = sin(X__[iX_xx4]);
    result__[ 63  ] = 0.2e0 * t254 + t55 - V__[63];
    real_type t258 = sin(X__[iX_xx5]);
    result__[ 64  ] = 0.2e0 * t258 + t59 - V__[64];
    real_type t262 = sin(X__[iX_xx6]);
    result__[ 65  ] = 0.2e0 * t262 + t63 - V__[65];
    real_type t266 = sin(X__[iX_xx7]);
    result__[ 66  ] = 0.2e0 * t266 + t67 - V__[66];
    real_type t270 = sin(X__[iX_xx8]);
    result__[ 67  ] = 0.2e0 * t270 + t71 - V__[67];
    real_type t274 = sin(X__[iX_xx9]);
    result__[ 68  ] = 0.2e0 * t274 + t75 - V__[68];
    real_type t278 = sin(X__[iX_xx10]);
    result__[ 69  ] = 0.2e0 * t278 + t79 - V__[69];
    real_type t282 = sin(X__[iX_xx11]);
    result__[ 70  ] = 0.2e0 * t282 + t83 - V__[70];
    real_type t286 = sin(X__[iX_xx12]);
    result__[ 71  ] = 0.2e0 * t286 + t87 - V__[71];
    real_type t290 = sin(X__[iX_xx13]);
    result__[ 72  ] = 0.2e0 * t290 + t91 - V__[72];
    real_type t294 = sin(X__[iX_xx14]);
    result__[ 73  ] = 0.2e0 * t294 + t95 - V__[73];
    real_type t298 = sin(X__[iX_xx15]);
    result__[ 74  ] = 0.2e0 * t298 + t99 - V__[74];
    real_type t302 = sin(X__[iX_xx16]);
    result__[ 75  ] = 0.2e0 * t302 + t103 - V__[75];
    real_type t306 = sin(X__[iX_xx17]);
    result__[ 76  ] = 0.2e0 * t306 + t107 - V__[76];
    real_type t310 = sin(X__[iX_xx18]);
    result__[ 77  ] = 0.2e0 * t310 + t111 - V__[77];
    real_type t314 = sin(X__[iX_xx19]);
    result__[ 78  ] = 0.2e0 * t314 + t115 - V__[78];
    real_type t318 = sin(X__[iX_xx20]);
    result__[ 79  ] = 0.2e0 * t318 + t119 - V__[79];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DodeDxpuv_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DodeDxpuv_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DodeDxpuv_nnz()     const { return 200; }

  void
  ICLOCS_ContinuousMP::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 20  ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 100 ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 21  ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 101 ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 22  ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 102 ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 23  ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 103 ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 24  ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 104 ;
    iIndex[10] = 5   ; jIndex[10] = 25  ;
    iIndex[11] = 5   ; jIndex[11] = 105 ;
    iIndex[12] = 6   ; jIndex[12] = 26  ;
    iIndex[13] = 6   ; jIndex[13] = 106 ;
    iIndex[14] = 7   ; jIndex[14] = 27  ;
    iIndex[15] = 7   ; jIndex[15] = 107 ;
    iIndex[16] = 8   ; jIndex[16] = 28  ;
    iIndex[17] = 8   ; jIndex[17] = 108 ;
    iIndex[18] = 9   ; jIndex[18] = 29  ;
    iIndex[19] = 9   ; jIndex[19] = 109 ;
    iIndex[20] = 10  ; jIndex[20] = 30  ;
    iIndex[21] = 10  ; jIndex[21] = 110 ;
    iIndex[22] = 11  ; jIndex[22] = 31  ;
    iIndex[23] = 11  ; jIndex[23] = 111 ;
    iIndex[24] = 12  ; jIndex[24] = 32  ;
    iIndex[25] = 12  ; jIndex[25] = 112 ;
    iIndex[26] = 13  ; jIndex[26] = 33  ;
    iIndex[27] = 13  ; jIndex[27] = 113 ;
    iIndex[28] = 14  ; jIndex[28] = 34  ;
    iIndex[29] = 14  ; jIndex[29] = 114 ;
    iIndex[30] = 15  ; jIndex[30] = 35  ;
    iIndex[31] = 15  ; jIndex[31] = 115 ;
    iIndex[32] = 16  ; jIndex[32] = 36  ;
    iIndex[33] = 16  ; jIndex[33] = 116 ;
    iIndex[34] = 17  ; jIndex[34] = 37  ;
    iIndex[35] = 17  ; jIndex[35] = 117 ;
    iIndex[36] = 18  ; jIndex[36] = 38  ;
    iIndex[37] = 18  ; jIndex[37] = 118 ;
    iIndex[38] = 19  ; jIndex[38] = 39  ;
    iIndex[39] = 19  ; jIndex[39] = 119 ;
    iIndex[40] = 20  ; jIndex[40] = 0   ;
    iIndex[41] = 20  ; jIndex[41] = 80  ;
    iIndex[42] = 20  ; jIndex[42] = 120 ;
    iIndex[43] = 21  ; jIndex[43] = 1   ;
    iIndex[44] = 21  ; jIndex[44] = 81  ;
    iIndex[45] = 21  ; jIndex[45] = 121 ;
    iIndex[46] = 22  ; jIndex[46] = 2   ;
    iIndex[47] = 22  ; jIndex[47] = 82  ;
    iIndex[48] = 22  ; jIndex[48] = 122 ;
    iIndex[49] = 23  ; jIndex[49] = 3   ;
    iIndex[50] = 23  ; jIndex[50] = 83  ;
    iIndex[51] = 23  ; jIndex[51] = 123 ;
    iIndex[52] = 24  ; jIndex[52] = 4   ;
    iIndex[53] = 24  ; jIndex[53] = 84  ;
    iIndex[54] = 24  ; jIndex[54] = 124 ;
    iIndex[55] = 25  ; jIndex[55] = 5   ;
    iIndex[56] = 25  ; jIndex[56] = 85  ;
    iIndex[57] = 25  ; jIndex[57] = 125 ;
    iIndex[58] = 26  ; jIndex[58] = 6   ;
    iIndex[59] = 26  ; jIndex[59] = 86  ;
    iIndex[60] = 26  ; jIndex[60] = 126 ;
    iIndex[61] = 27  ; jIndex[61] = 7   ;
    iIndex[62] = 27  ; jIndex[62] = 87  ;
    iIndex[63] = 27  ; jIndex[63] = 127 ;
    iIndex[64] = 28  ; jIndex[64] = 8   ;
    iIndex[65] = 28  ; jIndex[65] = 88  ;
    iIndex[66] = 28  ; jIndex[66] = 128 ;
    iIndex[67] = 29  ; jIndex[67] = 9   ;
    iIndex[68] = 29  ; jIndex[68] = 89  ;
    iIndex[69] = 29  ; jIndex[69] = 129 ;
    iIndex[70] = 30  ; jIndex[70] = 10  ;
    iIndex[71] = 30  ; jIndex[71] = 90  ;
    iIndex[72] = 30  ; jIndex[72] = 130 ;
    iIndex[73] = 31  ; jIndex[73] = 11  ;
    iIndex[74] = 31  ; jIndex[74] = 91  ;
    iIndex[75] = 31  ; jIndex[75] = 131 ;
    iIndex[76] = 32  ; jIndex[76] = 12  ;
    iIndex[77] = 32  ; jIndex[77] = 92  ;
    iIndex[78] = 32  ; jIndex[78] = 132 ;
    iIndex[79] = 33  ; jIndex[79] = 13  ;
    iIndex[80] = 33  ; jIndex[80] = 93  ;
    iIndex[81] = 33  ; jIndex[81] = 133 ;
    iIndex[82] = 34  ; jIndex[82] = 14  ;
    iIndex[83] = 34  ; jIndex[83] = 94  ;
    iIndex[84] = 34  ; jIndex[84] = 134 ;
    iIndex[85] = 35  ; jIndex[85] = 15  ;
    iIndex[86] = 35  ; jIndex[86] = 95  ;
    iIndex[87] = 35  ; jIndex[87] = 135 ;
    iIndex[88] = 36  ; jIndex[88] = 16  ;
    iIndex[89] = 36  ; jIndex[89] = 96  ;
    iIndex[90] = 36  ; jIndex[90] = 136 ;
    iIndex[91] = 37  ; jIndex[91] = 17  ;
    iIndex[92] = 37  ; jIndex[92] = 97  ;
    iIndex[93] = 37  ; jIndex[93] = 137 ;
    iIndex[94] = 38  ; jIndex[94] = 18  ;
    iIndex[95] = 38  ; jIndex[95] = 98  ;
    iIndex[96] = 38  ; jIndex[96] = 138 ;
    iIndex[97] = 39  ; jIndex[97] = 19  ;
    iIndex[98] = 39  ; jIndex[98] = 99  ;
    iIndex[99] = 39  ; jIndex[99] = 139 ;
    iIndex[100] = 40  ; jIndex[100] = 60  ;
    iIndex[101] = 40  ; jIndex[101] = 140 ;
    iIndex[102] = 41  ; jIndex[102] = 61  ;
    iIndex[103] = 41  ; jIndex[103] = 141 ;
    iIndex[104] = 42  ; jIndex[104] = 62  ;
    iIndex[105] = 42  ; jIndex[105] = 142 ;
    iIndex[106] = 43  ; jIndex[106] = 63  ;
    iIndex[107] = 43  ; jIndex[107] = 143 ;
    iIndex[108] = 44  ; jIndex[108] = 64  ;
    iIndex[109] = 44  ; jIndex[109] = 144 ;
    iIndex[110] = 45  ; jIndex[110] = 65  ;
    iIndex[111] = 45  ; jIndex[111] = 145 ;
    iIndex[112] = 46  ; jIndex[112] = 66  ;
    iIndex[113] = 46  ; jIndex[113] = 146 ;
    iIndex[114] = 47  ; jIndex[114] = 67  ;
    iIndex[115] = 47  ; jIndex[115] = 147 ;
    iIndex[116] = 48  ; jIndex[116] = 68  ;
    iIndex[117] = 48  ; jIndex[117] = 148 ;
    iIndex[118] = 49  ; jIndex[118] = 69  ;
    iIndex[119] = 49  ; jIndex[119] = 149 ;
    iIndex[120] = 50  ; jIndex[120] = 70  ;
    iIndex[121] = 50  ; jIndex[121] = 150 ;
    iIndex[122] = 51  ; jIndex[122] = 71  ;
    iIndex[123] = 51  ; jIndex[123] = 151 ;
    iIndex[124] = 52  ; jIndex[124] = 72  ;
    iIndex[125] = 52  ; jIndex[125] = 152 ;
    iIndex[126] = 53  ; jIndex[126] = 73  ;
    iIndex[127] = 53  ; jIndex[127] = 153 ;
    iIndex[128] = 54  ; jIndex[128] = 74  ;
    iIndex[129] = 54  ; jIndex[129] = 154 ;
    iIndex[130] = 55  ; jIndex[130] = 75  ;
    iIndex[131] = 55  ; jIndex[131] = 155 ;
    iIndex[132] = 56  ; jIndex[132] = 76  ;
    iIndex[133] = 56  ; jIndex[133] = 156 ;
    iIndex[134] = 57  ; jIndex[134] = 77  ;
    iIndex[135] = 57  ; jIndex[135] = 157 ;
    iIndex[136] = 58  ; jIndex[136] = 78  ;
    iIndex[137] = 58  ; jIndex[137] = 158 ;
    iIndex[138] = 59  ; jIndex[138] = 79  ;
    iIndex[139] = 59  ; jIndex[139] = 159 ;
    iIndex[140] = 60  ; jIndex[140] = 40  ;
    iIndex[141] = 60  ; jIndex[141] = 80  ;
    iIndex[142] = 60  ; jIndex[142] = 160 ;
    iIndex[143] = 61  ; jIndex[143] = 41  ;
    iIndex[144] = 61  ; jIndex[144] = 81  ;
    iIndex[145] = 61  ; jIndex[145] = 161 ;
    iIndex[146] = 62  ; jIndex[146] = 42  ;
    iIndex[147] = 62  ; jIndex[147] = 82  ;
    iIndex[148] = 62  ; jIndex[148] = 162 ;
    iIndex[149] = 63  ; jIndex[149] = 43  ;
    iIndex[150] = 63  ; jIndex[150] = 83  ;
    iIndex[151] = 63  ; jIndex[151] = 163 ;
    iIndex[152] = 64  ; jIndex[152] = 44  ;
    iIndex[153] = 64  ; jIndex[153] = 84  ;
    iIndex[154] = 64  ; jIndex[154] = 164 ;
    iIndex[155] = 65  ; jIndex[155] = 45  ;
    iIndex[156] = 65  ; jIndex[156] = 85  ;
    iIndex[157] = 65  ; jIndex[157] = 165 ;
    iIndex[158] = 66  ; jIndex[158] = 46  ;
    iIndex[159] = 66  ; jIndex[159] = 86  ;
    iIndex[160] = 66  ; jIndex[160] = 166 ;
    iIndex[161] = 67  ; jIndex[161] = 47  ;
    iIndex[162] = 67  ; jIndex[162] = 87  ;
    iIndex[163] = 67  ; jIndex[163] = 167 ;
    iIndex[164] = 68  ; jIndex[164] = 48  ;
    iIndex[165] = 68  ; jIndex[165] = 88  ;
    iIndex[166] = 68  ; jIndex[166] = 168 ;
    iIndex[167] = 69  ; jIndex[167] = 49  ;
    iIndex[168] = 69  ; jIndex[168] = 89  ;
    iIndex[169] = 69  ; jIndex[169] = 169 ;
    iIndex[170] = 70  ; jIndex[170] = 50  ;
    iIndex[171] = 70  ; jIndex[171] = 90  ;
    iIndex[172] = 70  ; jIndex[172] = 170 ;
    iIndex[173] = 71  ; jIndex[173] = 51  ;
    iIndex[174] = 71  ; jIndex[174] = 91  ;
    iIndex[175] = 71  ; jIndex[175] = 171 ;
    iIndex[176] = 72  ; jIndex[176] = 52  ;
    iIndex[177] = 72  ; jIndex[177] = 92  ;
    iIndex[178] = 72  ; jIndex[178] = 172 ;
    iIndex[179] = 73  ; jIndex[179] = 53  ;
    iIndex[180] = 73  ; jIndex[180] = 93  ;
    iIndex[181] = 73  ; jIndex[181] = 173 ;
    iIndex[182] = 74  ; jIndex[182] = 54  ;
    iIndex[183] = 74  ; jIndex[183] = 94  ;
    iIndex[184] = 74  ; jIndex[184] = 174 ;
    iIndex[185] = 75  ; jIndex[185] = 55  ;
    iIndex[186] = 75  ; jIndex[186] = 95  ;
    iIndex[187] = 75  ; jIndex[187] = 175 ;
    iIndex[188] = 76  ; jIndex[188] = 56  ;
    iIndex[189] = 76  ; jIndex[189] = 96  ;
    iIndex[190] = 76  ; jIndex[190] = 176 ;
    iIndex[191] = 77  ; jIndex[191] = 57  ;
    iIndex[192] = 77  ; jIndex[192] = 97  ;
    iIndex[193] = 77  ; jIndex[193] = 177 ;
    iIndex[194] = 78  ; jIndex[194] = 58  ;
    iIndex[195] = 78  ; jIndex[195] = 98  ;
    iIndex[196] = 78  ; jIndex[196] = 178 ;
    iIndex[197] = 79  ; jIndex[197] = 59  ;
    iIndex[198] = 79  ; jIndex[198] = 99  ;
    iIndex[199] = 79  ; jIndex[199] = 179 ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    result__[ 5   ] = -1;
    result__[ 6   ] = 1;
    result__[ 7   ] = -1;
    result__[ 8   ] = 1;
    result__[ 9   ] = -1;
    result__[ 10  ] = 1;
    result__[ 11  ] = -1;
    result__[ 12  ] = 1;
    result__[ 13  ] = -1;
    result__[ 14  ] = 1;
    result__[ 15  ] = -1;
    result__[ 16  ] = 1;
    result__[ 17  ] = -1;
    result__[ 18  ] = 1;
    result__[ 19  ] = -1;
    result__[ 20  ] = 1;
    result__[ 21  ] = -1;
    result__[ 22  ] = 1;
    result__[ 23  ] = -1;
    result__[ 24  ] = 1;
    result__[ 25  ] = -1;
    result__[ 26  ] = 1;
    result__[ 27  ] = -1;
    result__[ 28  ] = 1;
    result__[ 29  ] = -1;
    result__[ 30  ] = 1;
    result__[ 31  ] = -1;
    result__[ 32  ] = 1;
    result__[ 33  ] = -1;
    result__[ 34  ] = 1;
    result__[ 35  ] = -1;
    result__[ 36  ] = 1;
    result__[ 37  ] = -1;
    result__[ 38  ] = 1;
    result__[ 39  ] = -1;
    result__[ 40  ] = cos(X__[iX_x1]);
    result__[ 41  ] = 1;
    result__[ 42  ] = -1;
    result__[ 43  ] = cos(X__[iX_x2]);
    result__[ 44  ] = 1;
    result__[ 45  ] = -1;
    result__[ 46  ] = cos(X__[iX_x3]);
    result__[ 47  ] = 1;
    result__[ 48  ] = -1;
    result__[ 49  ] = cos(X__[iX_x4]);
    result__[ 50  ] = 1;
    result__[ 51  ] = -1;
    result__[ 52  ] = cos(X__[iX_x5]);
    result__[ 53  ] = 1;
    result__[ 54  ] = -1;
    result__[ 55  ] = cos(X__[iX_x6]);
    result__[ 56  ] = 1;
    result__[ 57  ] = -1;
    result__[ 58  ] = cos(X__[iX_x7]);
    result__[ 59  ] = 1;
    result__[ 60  ] = -1;
    result__[ 61  ] = cos(X__[iX_x8]);
    result__[ 62  ] = 1;
    result__[ 63  ] = -1;
    result__[ 64  ] = cos(X__[iX_x9]);
    result__[ 65  ] = 1;
    result__[ 66  ] = -1;
    result__[ 67  ] = cos(X__[iX_x10]);
    result__[ 68  ] = 1;
    result__[ 69  ] = -1;
    result__[ 70  ] = cos(X__[iX_x11]);
    result__[ 71  ] = 1;
    result__[ 72  ] = -1;
    result__[ 73  ] = cos(X__[iX_x12]);
    result__[ 74  ] = 1;
    result__[ 75  ] = -1;
    result__[ 76  ] = cos(X__[iX_x13]);
    result__[ 77  ] = 1;
    result__[ 78  ] = -1;
    result__[ 79  ] = cos(X__[iX_x14]);
    result__[ 80  ] = 1;
    result__[ 81  ] = -1;
    result__[ 82  ] = cos(X__[iX_x15]);
    result__[ 83  ] = 1;
    result__[ 84  ] = -1;
    result__[ 85  ] = cos(X__[iX_x16]);
    result__[ 86  ] = 1;
    result__[ 87  ] = -1;
    result__[ 88  ] = cos(X__[iX_x17]);
    result__[ 89  ] = 1;
    result__[ 90  ] = -1;
    result__[ 91  ] = cos(X__[iX_x18]);
    result__[ 92  ] = 1;
    result__[ 93  ] = -1;
    result__[ 94  ] = cos(X__[iX_x19]);
    result__[ 95  ] = 1;
    result__[ 96  ] = -1;
    result__[ 97  ] = cos(X__[iX_x20]);
    result__[ 98  ] = 1;
    result__[ 99  ] = -1;
    result__[ 100 ] = 0.12e1;
    result__[ 101 ] = -1;
    result__[ 102 ] = 0.12e1;
    result__[ 103 ] = -1;
    result__[ 104 ] = 0.12e1;
    result__[ 105 ] = -1;
    result__[ 106 ] = 0.12e1;
    result__[ 107 ] = -1;
    result__[ 108 ] = 0.12e1;
    result__[ 109 ] = -1;
    result__[ 110 ] = 0.12e1;
    result__[ 111 ] = -1;
    result__[ 112 ] = 0.12e1;
    result__[ 113 ] = -1;
    result__[ 114 ] = 0.12e1;
    result__[ 115 ] = -1;
    result__[ 116 ] = 0.12e1;
    result__[ 117 ] = -1;
    result__[ 118 ] = 0.12e1;
    result__[ 119 ] = -1;
    result__[ 120 ] = 0.12e1;
    result__[ 121 ] = -1;
    result__[ 122 ] = 0.12e1;
    result__[ 123 ] = -1;
    result__[ 124 ] = 0.12e1;
    result__[ 125 ] = -1;
    result__[ 126 ] = 0.12e1;
    result__[ 127 ] = -1;
    result__[ 128 ] = 0.12e1;
    result__[ 129 ] = -1;
    result__[ 130 ] = 0.12e1;
    result__[ 131 ] = -1;
    result__[ 132 ] = 0.12e1;
    result__[ 133 ] = -1;
    result__[ 134 ] = 0.12e1;
    result__[ 135 ] = -1;
    result__[ 136 ] = 0.12e1;
    result__[ 137 ] = -1;
    result__[ 138 ] = 0.12e1;
    result__[ 139 ] = -1;
    real_type t22  = cos(X__[iX_xx1]);
    result__[ 140 ] = 0.2e0 * t22;
    result__[ 141 ] = 1;
    result__[ 142 ] = -1;
    real_type t24  = cos(X__[iX_xx2]);
    result__[ 143 ] = 0.2e0 * t24;
    result__[ 144 ] = 1;
    result__[ 145 ] = -1;
    real_type t26  = cos(X__[iX_xx3]);
    result__[ 146 ] = 0.2e0 * t26;
    result__[ 147 ] = 1;
    result__[ 148 ] = -1;
    real_type t28  = cos(X__[iX_xx4]);
    result__[ 149 ] = 0.2e0 * t28;
    result__[ 150 ] = 1;
    result__[ 151 ] = -1;
    real_type t30  = cos(X__[iX_xx5]);
    result__[ 152 ] = 0.2e0 * t30;
    result__[ 153 ] = 1;
    result__[ 154 ] = -1;
    real_type t32  = cos(X__[iX_xx6]);
    result__[ 155 ] = 0.2e0 * t32;
    result__[ 156 ] = 1;
    result__[ 157 ] = -1;
    real_type t34  = cos(X__[iX_xx7]);
    result__[ 158 ] = 0.2e0 * t34;
    result__[ 159 ] = 1;
    result__[ 160 ] = -1;
    real_type t36  = cos(X__[iX_xx8]);
    result__[ 161 ] = 0.2e0 * t36;
    result__[ 162 ] = 1;
    result__[ 163 ] = -1;
    real_type t38  = cos(X__[iX_xx9]);
    result__[ 164 ] = 0.2e0 * t38;
    result__[ 165 ] = 1;
    result__[ 166 ] = -1;
    real_type t40  = cos(X__[iX_xx10]);
    result__[ 167 ] = 0.2e0 * t40;
    result__[ 168 ] = 1;
    result__[ 169 ] = -1;
    real_type t42  = cos(X__[iX_xx11]);
    result__[ 170 ] = 0.2e0 * t42;
    result__[ 171 ] = 1;
    result__[ 172 ] = -1;
    real_type t44  = cos(X__[iX_xx12]);
    result__[ 173 ] = 0.2e0 * t44;
    result__[ 174 ] = 1;
    result__[ 175 ] = -1;
    real_type t46  = cos(X__[iX_xx13]);
    result__[ 176 ] = 0.2e0 * t46;
    result__[ 177 ] = 1;
    result__[ 178 ] = -1;
    real_type t48  = cos(X__[iX_xx14]);
    result__[ 179 ] = 0.2e0 * t48;
    result__[ 180 ] = 1;
    result__[ 181 ] = -1;
    real_type t50  = cos(X__[iX_xx15]);
    result__[ 182 ] = 0.2e0 * t50;
    result__[ 183 ] = 1;
    result__[ 184 ] = -1;
    real_type t52  = cos(X__[iX_xx16]);
    result__[ 185 ] = 0.2e0 * t52;
    result__[ 186 ] = 1;
    result__[ 187 ] = -1;
    real_type t54  = cos(X__[iX_xx17]);
    result__[ 188 ] = 0.2e0 * t54;
    result__[ 189 ] = 1;
    result__[ 190 ] = -1;
    real_type t56  = cos(X__[iX_xx18]);
    result__[ 191 ] = 0.2e0 * t56;
    result__[ 192 ] = 1;
    result__[ 193 ] = -1;
    real_type t58  = cos(X__[iX_xx19]);
    result__[ 194 ] = 0.2e0 * t58;
    result__[ 195 ] = 1;
    result__[ 196 ] = -1;
    real_type t60  = cos(X__[iX_xx20]);
    result__[ 197 ] = 0.2e0 * t60;
    result__[ 198 ] = 1;
    result__[ 199 ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 200, i_segment );
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
