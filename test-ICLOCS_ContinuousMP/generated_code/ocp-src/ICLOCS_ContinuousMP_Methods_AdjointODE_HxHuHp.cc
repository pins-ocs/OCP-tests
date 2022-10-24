/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_AdjointODE.cc                      |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::Hxp_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t3   = L__[iL_lambda21__xo];
    real_type t4   = cos(t1);
    result__[ 0   ] = t4 * t3 + 40 * t1;
    real_type t6   = X__[iX_x2];
    real_type t8   = L__[iL_lambda22__xo];
    real_type t9   = cos(t6);
    result__[ 1   ] = t9 * t8 + 38 * t6;
    real_type t11  = X__[iX_x3];
    real_type t13  = L__[iL_lambda23__xo];
    real_type t14  = cos(t11);
    result__[ 2   ] = t14 * t13 + 36 * t11;
    real_type t16  = X__[iX_x4];
    real_type t18  = L__[iL_lambda24__xo];
    real_type t19  = cos(t16);
    result__[ 3   ] = t19 * t18 + 34 * t16;
    real_type t21  = X__[iX_x5];
    real_type t23  = L__[iL_lambda25__xo];
    real_type t24  = cos(t21);
    result__[ 4   ] = t24 * t23 + 32 * t21;
    real_type t26  = X__[iX_x6];
    real_type t28  = L__[iL_lambda26__xo];
    real_type t29  = cos(t26);
    result__[ 5   ] = t29 * t28 + 30 * t26;
    real_type t31  = X__[iX_x7];
    real_type t33  = L__[iL_lambda27__xo];
    real_type t34  = cos(t31);
    result__[ 6   ] = t34 * t33 + 28 * t31;
    real_type t36  = X__[iX_x8];
    real_type t38  = L__[iL_lambda28__xo];
    real_type t39  = cos(t36);
    result__[ 7   ] = t39 * t38 + 26 * t36;
    real_type t41  = X__[iX_x9];
    real_type t43  = L__[iL_lambda29__xo];
    real_type t44  = cos(t41);
    result__[ 8   ] = t44 * t43 + 24 * t41;
    real_type t46  = X__[iX_x10];
    real_type t48  = L__[iL_lambda30__xo];
    real_type t49  = cos(t46);
    result__[ 9   ] = t49 * t48 + 22 * t46;
    real_type t51  = X__[iX_x11];
    real_type t53  = L__[iL_lambda31__xo];
    real_type t54  = cos(t51);
    result__[ 10  ] = t54 * t53 + 20 * t51;
    real_type t56  = X__[iX_x12];
    real_type t58  = L__[iL_lambda32__xo];
    real_type t59  = cos(t56);
    result__[ 11  ] = t59 * t58 + 18 * t56;
    real_type t61  = X__[iX_x13];
    real_type t63  = L__[iL_lambda33__xo];
    real_type t64  = cos(t61);
    result__[ 12  ] = t64 * t63 + 16 * t61;
    real_type t66  = X__[iX_x14];
    real_type t68  = L__[iL_lambda34__xo];
    real_type t69  = cos(t66);
    result__[ 13  ] = t69 * t68 + 14 * t66;
    real_type t71  = X__[iX_x15];
    real_type t73  = L__[iL_lambda35__xo];
    real_type t74  = cos(t71);
    result__[ 14  ] = t74 * t73 + 12 * t71;
    real_type t76  = X__[iX_x16];
    real_type t78  = L__[iL_lambda36__xo];
    real_type t79  = cos(t76);
    result__[ 15  ] = t79 * t78 + 10 * t76;
    real_type t81  = X__[iX_x17];
    real_type t83  = L__[iL_lambda37__xo];
    real_type t84  = cos(t81);
    result__[ 16  ] = t84 * t83 + 8 * t81;
    real_type t86  = X__[iX_x18];
    real_type t88  = L__[iL_lambda38__xo];
    real_type t89  = cos(t86);
    result__[ 17  ] = t89 * t88 + 6 * t86;
    real_type t91  = X__[iX_x19];
    real_type t93  = L__[iL_lambda39__xo];
    real_type t94  = cos(t91);
    result__[ 18  ] = t94 * t93 + 4 * t91;
    real_type t96  = X__[iX_x20];
    real_type t98  = L__[iL_lambda40__xo];
    real_type t99  = cos(t96);
    result__[ 19  ] = t99 * t98 + 2 * t96;
    result__[ 20  ] = 40 * X__[iX_y1] + L__[iL_lambda1__xo];
    result__[ 21  ] = 38 * X__[iX_y2] + L__[iL_lambda2__xo];
    result__[ 22  ] = 36 * X__[iX_y3] + L__[iL_lambda3__xo];
    result__[ 23  ] = 34 * X__[iX_y4] + L__[iL_lambda4__xo];
    result__[ 24  ] = 32 * X__[iX_y5] + L__[iL_lambda5__xo];
    result__[ 25  ] = 30 * X__[iX_y6] + L__[iL_lambda6__xo];
    result__[ 26  ] = 28 * X__[iX_y7] + L__[iL_lambda7__xo];
    result__[ 27  ] = 26 * X__[iX_y8] + L__[iL_lambda8__xo];
    result__[ 28  ] = 24 * X__[iX_y9] + L__[iL_lambda9__xo];
    result__[ 29  ] = 22 * X__[iX_y10] + L__[iL_lambda10__xo];
    result__[ 30  ] = 20 * X__[iX_y11] + L__[iL_lambda11__xo];
    result__[ 31  ] = 18 * X__[iX_y12] + L__[iL_lambda12__xo];
    result__[ 32  ] = 16 * X__[iX_y13] + L__[iL_lambda13__xo];
    result__[ 33  ] = 14 * X__[iX_y14] + L__[iL_lambda14__xo];
    result__[ 34  ] = 12 * X__[iX_y15] + L__[iL_lambda15__xo];
    result__[ 35  ] = 10 * X__[iX_y16] + L__[iL_lambda16__xo];
    result__[ 36  ] = 8 * X__[iX_y17] + L__[iL_lambda17__xo];
    result__[ 37  ] = 6 * X__[iX_y18] + L__[iL_lambda18__xo];
    result__[ 38  ] = 4 * X__[iX_y19] + L__[iL_lambda19__xo];
    result__[ 39  ] = 2 * X__[iX_y20] + L__[iL_lambda20__xo];
    real_type t161 = L__[iL_lambda61__xo];
    real_type t163 = cos(X__[iX_xx1]);
    result__[ 40  ] = 0.2e0 * t163 * t161;
    real_type t165 = L__[iL_lambda62__xo];
    real_type t167 = cos(X__[iX_xx2]);
    result__[ 41  ] = 0.2e0 * t167 * t165;
    real_type t169 = L__[iL_lambda63__xo];
    real_type t171 = cos(X__[iX_xx3]);
    result__[ 42  ] = 0.2e0 * t171 * t169;
    real_type t173 = L__[iL_lambda64__xo];
    real_type t175 = cos(X__[iX_xx4]);
    result__[ 43  ] = 0.2e0 * t175 * t173;
    real_type t177 = L__[iL_lambda65__xo];
    real_type t179 = cos(X__[iX_xx5]);
    result__[ 44  ] = 0.2e0 * t179 * t177;
    real_type t181 = L__[iL_lambda66__xo];
    real_type t183 = cos(X__[iX_xx6]);
    result__[ 45  ] = 0.2e0 * t183 * t181;
    real_type t185 = L__[iL_lambda67__xo];
    real_type t187 = cos(X__[iX_xx7]);
    result__[ 46  ] = 0.2e0 * t187 * t185;
    real_type t189 = L__[iL_lambda68__xo];
    real_type t191 = cos(X__[iX_xx8]);
    result__[ 47  ] = 0.2e0 * t191 * t189;
    real_type t193 = L__[iL_lambda69__xo];
    real_type t195 = cos(X__[iX_xx9]);
    result__[ 48  ] = 0.2e0 * t195 * t193;
    real_type t197 = L__[iL_lambda70__xo];
    real_type t199 = cos(X__[iX_xx10]);
    result__[ 49  ] = 0.2e0 * t199 * t197;
    real_type t201 = L__[iL_lambda71__xo];
    real_type t203 = cos(X__[iX_xx11]);
    result__[ 50  ] = 0.2e0 * t203 * t201;
    real_type t205 = L__[iL_lambda72__xo];
    real_type t207 = cos(X__[iX_xx12]);
    result__[ 51  ] = 0.2e0 * t207 * t205;
    real_type t209 = L__[iL_lambda73__xo];
    real_type t211 = cos(X__[iX_xx13]);
    result__[ 52  ] = 0.2e0 * t211 * t209;
    real_type t213 = L__[iL_lambda74__xo];
    real_type t215 = cos(X__[iX_xx14]);
    result__[ 53  ] = 0.2e0 * t215 * t213;
    real_type t217 = L__[iL_lambda75__xo];
    real_type t219 = cos(X__[iX_xx15]);
    result__[ 54  ] = 0.2e0 * t219 * t217;
    real_type t221 = L__[iL_lambda76__xo];
    real_type t223 = cos(X__[iX_xx16]);
    result__[ 55  ] = 0.2e0 * t223 * t221;
    real_type t225 = L__[iL_lambda77__xo];
    real_type t227 = cos(X__[iX_xx17]);
    result__[ 56  ] = 0.2e0 * t227 * t225;
    real_type t229 = L__[iL_lambda78__xo];
    real_type t231 = cos(X__[iX_xx18]);
    result__[ 57  ] = 0.2e0 * t231 * t229;
    real_type t233 = L__[iL_lambda79__xo];
    real_type t235 = cos(X__[iX_xx19]);
    result__[ 58  ] = 0.2e0 * t235 * t233;
    real_type t237 = L__[iL_lambda80__xo];
    real_type t239 = cos(X__[iX_xx20]);
    result__[ 59  ] = 0.2e0 * t239 * t237;
    result__[ 60  ] = 0.12e1 * L__[iL_lambda41__xo];
    result__[ 61  ] = 0.12e1 * L__[iL_lambda42__xo];
    result__[ 62  ] = 0.12e1 * L__[iL_lambda43__xo];
    result__[ 63  ] = 0.12e1 * L__[iL_lambda44__xo];
    result__[ 64  ] = 0.12e1 * L__[iL_lambda45__xo];
    result__[ 65  ] = 0.12e1 * L__[iL_lambda46__xo];
    result__[ 66  ] = 0.12e1 * L__[iL_lambda47__xo];
    result__[ 67  ] = 0.12e1 * L__[iL_lambda48__xo];
    result__[ 68  ] = 0.12e1 * L__[iL_lambda49__xo];
    result__[ 69  ] = 0.12e1 * L__[iL_lambda50__xo];
    result__[ 70  ] = 0.12e1 * L__[iL_lambda51__xo];
    result__[ 71  ] = 0.12e1 * L__[iL_lambda52__xo];
    result__[ 72  ] = 0.12e1 * L__[iL_lambda53__xo];
    result__[ 73  ] = 0.12e1 * L__[iL_lambda54__xo];
    result__[ 74  ] = 0.12e1 * L__[iL_lambda55__xo];
    result__[ 75  ] = 0.12e1 * L__[iL_lambda56__xo];
    result__[ 76  ] = 0.12e1 * L__[iL_lambda57__xo];
    result__[ 77  ] = 0.12e1 * L__[iL_lambda58__xo];
    result__[ 78  ] = 0.12e1 * L__[iL_lambda59__xo];
    result__[ 79  ] = 0.12e1 * L__[iL_lambda60__xo];
    result__[ 80  ] = t161 + t3;
    result__[ 81  ] = t165 + t8;
    result__[ 82  ] = t169 + t13;
    result__[ 83  ] = t173 + t18;
    result__[ 84  ] = t177 + t23;
    result__[ 85  ] = t181 + t28;
    result__[ 86  ] = t33 + t185;
    result__[ 87  ] = t38 + t189;
    result__[ 88  ] = t43 + t193;
    result__[ 89  ] = t48 + t197;
    result__[ 90  ] = t53 + t201;
    result__[ 91  ] = t58 + t205;
    result__[ 92  ] = t63 + t209;
    result__[ 93  ] = t68 + t213;
    result__[ 94  ] = t73 + t217;
    result__[ 95  ] = t78 + t221;
    result__[ 96  ] = t83 + t225;
    result__[ 97  ] = t88 + t229;
    result__[ 98  ] = t93 + t233;
    result__[ 99  ] = t98 + t237;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 100, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DHxpDxpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::DHxpDxpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DHxpDxpu_nnz()     const { return 60; }

  void
  ICLOCS_ContinuousMP::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  ICLOCS_ContinuousMP::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = sin(X__[iX_x1]);
    result__[ 0   ] = -t3 * L__[iL_lambda21__xo] + 40;
    real_type t7   = sin(X__[iX_x2]);
    result__[ 1   ] = -t7 * L__[iL_lambda22__xo] + 38;
    real_type t11  = sin(X__[iX_x3]);
    result__[ 2   ] = -t11 * L__[iL_lambda23__xo] + 36;
    real_type t15  = sin(X__[iX_x4]);
    result__[ 3   ] = -t15 * L__[iL_lambda24__xo] + 34;
    real_type t19  = sin(X__[iX_x5]);
    result__[ 4   ] = -t19 * L__[iL_lambda25__xo] + 32;
    real_type t23  = sin(X__[iX_x6]);
    result__[ 5   ] = -t23 * L__[iL_lambda26__xo] + 30;
    real_type t27  = sin(X__[iX_x7]);
    result__[ 6   ] = -t27 * L__[iL_lambda27__xo] + 28;
    real_type t31  = sin(X__[iX_x8]);
    result__[ 7   ] = -t31 * L__[iL_lambda28__xo] + 26;
    real_type t35  = sin(X__[iX_x9]);
    result__[ 8   ] = -t35 * L__[iL_lambda29__xo] + 24;
    real_type t39  = sin(X__[iX_x10]);
    result__[ 9   ] = -t39 * L__[iL_lambda30__xo] + 22;
    real_type t43  = sin(X__[iX_x11]);
    result__[ 10  ] = -t43 * L__[iL_lambda31__xo] + 20;
    real_type t47  = sin(X__[iX_x12]);
    result__[ 11  ] = -t47 * L__[iL_lambda32__xo] + 18;
    real_type t51  = sin(X__[iX_x13]);
    result__[ 12  ] = -t51 * L__[iL_lambda33__xo] + 16;
    real_type t55  = sin(X__[iX_x14]);
    result__[ 13  ] = -t55 * L__[iL_lambda34__xo] + 14;
    real_type t59  = sin(X__[iX_x15]);
    result__[ 14  ] = -t59 * L__[iL_lambda35__xo] + 12;
    real_type t63  = sin(X__[iX_x16]);
    result__[ 15  ] = -t63 * L__[iL_lambda36__xo] + 10;
    real_type t67  = sin(X__[iX_x17]);
    result__[ 16  ] = -t67 * L__[iL_lambda37__xo] + 8;
    real_type t71  = sin(X__[iX_x18]);
    result__[ 17  ] = -t71 * L__[iL_lambda38__xo] + 6;
    real_type t75  = sin(X__[iX_x19]);
    result__[ 18  ] = -t75 * L__[iL_lambda39__xo] + 4;
    real_type t79  = sin(X__[iX_x20]);
    result__[ 19  ] = -t79 * L__[iL_lambda40__xo] + 2;
    result__[ 20  ] = 40;
    result__[ 21  ] = 38;
    result__[ 22  ] = 36;
    result__[ 23  ] = 34;
    result__[ 24  ] = 32;
    result__[ 25  ] = 30;
    result__[ 26  ] = 28;
    result__[ 27  ] = 26;
    result__[ 28  ] = 24;
    result__[ 29  ] = 22;
    result__[ 30  ] = 20;
    result__[ 31  ] = 18;
    result__[ 32  ] = 16;
    result__[ 33  ] = 14;
    result__[ 34  ] = 12;
    result__[ 35  ] = 10;
    result__[ 36  ] = 8;
    result__[ 37  ] = 6;
    result__[ 38  ] = 4;
    result__[ 39  ] = 2;
    real_type t83  = sin(X__[iX_xx1]);
    result__[ 40  ] = -0.2e0 * t83 * L__[iL_lambda61__xo];
    real_type t88  = sin(X__[iX_xx2]);
    result__[ 41  ] = -0.2e0 * t88 * L__[iL_lambda62__xo];
    real_type t93  = sin(X__[iX_xx3]);
    result__[ 42  ] = -0.2e0 * t93 * L__[iL_lambda63__xo];
    real_type t98  = sin(X__[iX_xx4]);
    result__[ 43  ] = -0.2e0 * t98 * L__[iL_lambda64__xo];
    real_type t103 = sin(X__[iX_xx5]);
    result__[ 44  ] = -0.2e0 * t103 * L__[iL_lambda65__xo];
    real_type t108 = sin(X__[iX_xx6]);
    result__[ 45  ] = -0.2e0 * t108 * L__[iL_lambda66__xo];
    real_type t113 = sin(X__[iX_xx7]);
    result__[ 46  ] = -0.2e0 * t113 * L__[iL_lambda67__xo];
    real_type t118 = sin(X__[iX_xx8]);
    result__[ 47  ] = -0.2e0 * t118 * L__[iL_lambda68__xo];
    real_type t123 = sin(X__[iX_xx9]);
    result__[ 48  ] = -0.2e0 * t123 * L__[iL_lambda69__xo];
    real_type t128 = sin(X__[iX_xx10]);
    result__[ 49  ] = -0.2e0 * t128 * L__[iL_lambda70__xo];
    real_type t133 = sin(X__[iX_xx11]);
    result__[ 50  ] = -0.2e0 * t133 * L__[iL_lambda71__xo];
    real_type t138 = sin(X__[iX_xx12]);
    result__[ 51  ] = -0.2e0 * t138 * L__[iL_lambda72__xo];
    real_type t143 = sin(X__[iX_xx13]);
    result__[ 52  ] = -0.2e0 * t143 * L__[iL_lambda73__xo];
    real_type t148 = sin(X__[iX_xx14]);
    result__[ 53  ] = -0.2e0 * t148 * L__[iL_lambda74__xo];
    real_type t153 = sin(X__[iX_xx15]);
    result__[ 54  ] = -0.2e0 * t153 * L__[iL_lambda75__xo];
    real_type t158 = sin(X__[iX_xx16]);
    result__[ 55  ] = -0.2e0 * t158 * L__[iL_lambda76__xo];
    real_type t163 = sin(X__[iX_xx17]);
    result__[ 56  ] = -0.2e0 * t163 * L__[iL_lambda77__xo];
    real_type t168 = sin(X__[iX_xx18]);
    result__[ 57  ] = -0.2e0 * t168 * L__[iL_lambda78__xo];
    real_type t173 = sin(X__[iX_xx19]);
    result__[ 58  ] = -0.2e0 * t173 * L__[iL_lambda79__xo];
    real_type t178 = sin(X__[iX_xx20]);
    result__[ 59  ] = -0.2e0 * t178 * L__[iL_lambda80__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 60, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::Hu_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
