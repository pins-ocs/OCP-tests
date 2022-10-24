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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JP_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LT_numEqns() const { return 120; }

  void
  ICLOCS_ContinuousMP::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_u1];
    result__[ 0   ] = u1Limitation_min(-10 - t1);
    result__[ 1   ] = u1Limitation_max(t1 - 10);
    real_type t4   = P__[iP_u2];
    result__[ 2   ] = u2Limitation_min(-10 - t4);
    result__[ 3   ] = u2Limitation_max(t4 - 10);
    real_type t7   = P__[iP_u3];
    result__[ 4   ] = u3Limitation_min(-10 - t7);
    result__[ 5   ] = u3Limitation_max(t7 - 10);
    real_type t10  = P__[iP_u4];
    result__[ 6   ] = u4Limitation_min(-10 - t10);
    result__[ 7   ] = u4Limitation_max(t10 - 10);
    real_type t13  = P__[iP_u5];
    result__[ 8   ] = u5Limitation_min(-10 - t13);
    result__[ 9   ] = u5Limitation_max(t13 - 10);
    real_type t16  = P__[iP_u6];
    result__[ 10  ] = u6Limitation_min(-10 - t16);
    result__[ 11  ] = u6Limitation_max(t16 - 10);
    real_type t19  = P__[iP_u7];
    result__[ 12  ] = u7Limitation_min(-10 - t19);
    result__[ 13  ] = u7Limitation_max(t19 - 10);
    real_type t22  = P__[iP_u8];
    result__[ 14  ] = u8Limitation_min(-10 - t22);
    result__[ 15  ] = u8Limitation_max(t22 - 10);
    real_type t25  = P__[iP_u9];
    result__[ 16  ] = u9Limitation_min(-10 - t25);
    result__[ 17  ] = u9Limitation_max(t25 - 10);
    real_type t28  = P__[iP_u10];
    result__[ 18  ] = u10Limitation_min(-10 - t28);
    result__[ 19  ] = u10Limitation_max(t28 - 10);
    real_type t31  = P__[iP_u11];
    result__[ 20  ] = u11Limitation_min(-10 - t31);
    result__[ 21  ] = u11Limitation_max(t31 - 10);
    real_type t34  = P__[iP_u12];
    result__[ 22  ] = u12Limitation_min(-10 - t34);
    result__[ 23  ] = u12Limitation_max(t34 - 10);
    real_type t37  = P__[iP_u13];
    result__[ 24  ] = u13Limitation_min(-10 - t37);
    result__[ 25  ] = u13Limitation_max(t37 - 10);
    real_type t40  = P__[iP_u14];
    result__[ 26  ] = u14Limitation_min(-10 - t40);
    result__[ 27  ] = u14Limitation_max(t40 - 10);
    real_type t43  = P__[iP_u15];
    result__[ 28  ] = u15Limitation_min(-10 - t43);
    result__[ 29  ] = u15Limitation_max(t43 - 10);
    real_type t46  = P__[iP_u16];
    result__[ 30  ] = u16Limitation_min(-10 - t46);
    result__[ 31  ] = u16Limitation_max(t46 - 10);
    real_type t49  = P__[iP_u17];
    result__[ 32  ] = u17Limitation_min(-10 - t49);
    result__[ 33  ] = u17Limitation_max(t49 - 10);
    real_type t52  = P__[iP_u18];
    result__[ 34  ] = u18Limitation_min(-10 - t52);
    result__[ 35  ] = u18Limitation_max(t52 - 10);
    real_type t55  = P__[iP_u19];
    result__[ 36  ] = u19Limitation_min(-10 - t55);
    result__[ 37  ] = u19Limitation_max(t55 - 10);
    real_type t58  = P__[iP_u20];
    result__[ 38  ] = u20Limitation_min(-10 - t58);
    result__[ 39  ] = u20Limitation_max(t58 - 10);
    real_type t61  = ModelPars[iM_xy_bound];
    real_type t62  = X__[iX_xx1];
    result__[ 40  ] = xx1Limitation_min(-t61 - t62);
    result__[ 41  ] = xx1Limitation_max(t62 - t61);
    real_type t65  = X__[iX_yy1];
    result__[ 42  ] = yy1Limitation_min(-t61 - t65);
    result__[ 43  ] = yy1Limitation_max(t65 - t61);
    real_type t68  = X__[iX_xx2];
    result__[ 44  ] = xx2Limitation_min(-t61 - t68);
    result__[ 45  ] = xx2Limitation_max(t68 - t61);
    real_type t71  = X__[iX_yy2];
    result__[ 46  ] = yy2Limitation_min(-t61 - t71);
    result__[ 47  ] = yy2Limitation_max(t71 - t61);
    real_type t74  = X__[iX_xx3];
    result__[ 48  ] = xx3Limitation_min(-t61 - t74);
    result__[ 49  ] = xx3Limitation_max(t74 - t61);
    real_type t77  = X__[iX_yy3];
    result__[ 50  ] = yy3Limitation_min(-t61 - t77);
    result__[ 51  ] = yy3Limitation_max(t77 - t61);
    real_type t80  = X__[iX_xx4];
    result__[ 52  ] = xx4Limitation_min(-t61 - t80);
    result__[ 53  ] = xx4Limitation_max(t80 - t61);
    real_type t83  = X__[iX_yy4];
    result__[ 54  ] = yy4Limitation_min(-t61 - t83);
    result__[ 55  ] = yy4Limitation_max(t83 - t61);
    real_type t86  = X__[iX_xx5];
    result__[ 56  ] = xx5Limitation_min(-t61 - t86);
    result__[ 57  ] = xx5Limitation_max(t86 - t61);
    real_type t89  = X__[iX_yy5];
    result__[ 58  ] = yy5Limitation_min(-t61 - t89);
    result__[ 59  ] = yy5Limitation_max(t89 - t61);
    real_type t92  = X__[iX_xx6];
    result__[ 60  ] = xx6Limitation_min(-t61 - t92);
    result__[ 61  ] = xx6Limitation_max(t92 - t61);
    real_type t95  = X__[iX_yy6];
    result__[ 62  ] = yy6Limitation_min(-t61 - t95);
    result__[ 63  ] = yy6Limitation_max(t95 - t61);
    real_type t98  = X__[iX_xx7];
    result__[ 64  ] = xx7Limitation_min(-t61 - t98);
    result__[ 65  ] = xx7Limitation_max(t98 - t61);
    real_type t101 = X__[iX_yy7];
    result__[ 66  ] = yy7Limitation_min(-t61 - t101);
    result__[ 67  ] = yy7Limitation_max(t101 - t61);
    real_type t104 = X__[iX_xx8];
    result__[ 68  ] = xx8Limitation_min(-t61 - t104);
    result__[ 69  ] = xx8Limitation_max(t104 - t61);
    real_type t107 = X__[iX_yy8];
    result__[ 70  ] = yy8Limitation_min(-t61 - t107);
    result__[ 71  ] = yy8Limitation_max(t107 - t61);
    real_type t110 = X__[iX_xx9];
    result__[ 72  ] = xx9Limitation_min(-t61 - t110);
    result__[ 73  ] = xx9Limitation_max(t110 - t61);
    real_type t113 = X__[iX_yy9];
    result__[ 74  ] = yy9Limitation_min(-t61 - t113);
    result__[ 75  ] = yy9Limitation_max(t113 - t61);
    real_type t116 = X__[iX_xx10];
    result__[ 76  ] = xx10Limitation_min(-t61 - t116);
    result__[ 77  ] = xx10Limitation_max(t116 - t61);
    real_type t119 = X__[iX_yy10];
    result__[ 78  ] = yy10Limitation_min(-t61 - t119);
    result__[ 79  ] = yy10Limitation_max(t119 - t61);
    real_type t122 = X__[iX_xx11];
    result__[ 80  ] = xx11Limitation_min(-t61 - t122);
    result__[ 81  ] = xx11Limitation_max(t122 - t61);
    real_type t125 = X__[iX_yy11];
    result__[ 82  ] = yy11Limitation_min(-t61 - t125);
    result__[ 83  ] = yy11Limitation_max(t125 - t61);
    real_type t128 = X__[iX_xx12];
    result__[ 84  ] = xx12Limitation_min(-t61 - t128);
    result__[ 85  ] = xx12Limitation_max(t128 - t61);
    real_type t131 = X__[iX_yy12];
    result__[ 86  ] = yy12Limitation_min(-t61 - t131);
    result__[ 87  ] = yy12Limitation_max(t131 - t61);
    real_type t134 = X__[iX_xx13];
    result__[ 88  ] = xx13Limitation_min(-t61 - t134);
    result__[ 89  ] = xx13Limitation_max(t134 - t61);
    real_type t137 = X__[iX_yy13];
    result__[ 90  ] = yy13Limitation_min(-t61 - t137);
    result__[ 91  ] = yy13Limitation_max(t137 - t61);
    real_type t140 = X__[iX_xx14];
    result__[ 92  ] = xx14Limitation_min(-t61 - t140);
    result__[ 93  ] = xx14Limitation_max(t140 - t61);
    real_type t143 = X__[iX_yy14];
    result__[ 94  ] = yy14Limitation_min(-t61 - t143);
    result__[ 95  ] = yy14Limitation_max(t143 - t61);
    real_type t146 = X__[iX_xx15];
    result__[ 96  ] = xx15Limitation_min(-t61 - t146);
    result__[ 97  ] = xx15Limitation_max(t146 - t61);
    real_type t149 = X__[iX_yy15];
    result__[ 98  ] = yy15Limitation_min(-t61 - t149);
    result__[ 99  ] = yy15Limitation_max(t149 - t61);
    real_type t152 = X__[iX_xx16];
    result__[ 100 ] = xx16Limitation_min(-t61 - t152);
    result__[ 101 ] = xx16Limitation_max(t152 - t61);
    real_type t155 = X__[iX_yy16];
    result__[ 102 ] = yy16Limitation_min(-t61 - t155);
    result__[ 103 ] = yy16Limitation_max(t155 - t61);
    real_type t158 = X__[iX_xx17];
    result__[ 104 ] = xx17Limitation_min(-t61 - t158);
    result__[ 105 ] = xx17Limitation_max(t158 - t61);
    real_type t161 = X__[iX_yy17];
    result__[ 106 ] = yy17Limitation_min(-t61 - t161);
    result__[ 107 ] = yy17Limitation_max(t161 - t61);
    real_type t164 = X__[iX_xx18];
    result__[ 108 ] = xx18Limitation_min(-t61 - t164);
    result__[ 109 ] = xx18Limitation_max(t164 - t61);
    real_type t167 = X__[iX_yy18];
    result__[ 110 ] = yy18Limitation_min(-t61 - t167);
    result__[ 111 ] = yy18Limitation_max(t167 - t61);
    real_type t170 = X__[iX_xx19];
    result__[ 112 ] = xx19Limitation_min(-t61 - t170);
    result__[ 113 ] = xx19Limitation_max(t170 - t61);
    real_type t173 = X__[iX_yy19];
    result__[ 114 ] = yy19Limitation_min(-t61 - t173);
    result__[ 115 ] = yy19Limitation_max(t173 - t61);
    real_type t176 = X__[iX_xx20];
    result__[ 116 ] = xx20Limitation_min(-t61 - t176);
    result__[ 117 ] = xx20Limitation_max(t176 - t61);
    real_type t179 = X__[iX_yy20];
    result__[ 118 ] = yy20Limitation_min(-t61 - t179);
    result__[ 119 ] = yy20Limitation_max(t179 - t61);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 120, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JU_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTargs_numEqns() const { return 120; }

  void
  ICLOCS_ContinuousMP::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_u1];
    result__[ 0   ] = -10 - t1;
    result__[ 1   ] = t1 - 10;
    real_type t2   = P__[iP_u2];
    result__[ 2   ] = -10 - t2;
    result__[ 3   ] = t2 - 10;
    real_type t3   = P__[iP_u3];
    result__[ 4   ] = -10 - t3;
    result__[ 5   ] = t3 - 10;
    real_type t4   = P__[iP_u4];
    result__[ 6   ] = -10 - t4;
    result__[ 7   ] = t4 - 10;
    real_type t5   = P__[iP_u5];
    result__[ 8   ] = -10 - t5;
    result__[ 9   ] = t5 - 10;
    real_type t6   = P__[iP_u6];
    result__[ 10  ] = -10 - t6;
    result__[ 11  ] = t6 - 10;
    real_type t7   = P__[iP_u7];
    result__[ 12  ] = -10 - t7;
    result__[ 13  ] = t7 - 10;
    real_type t8   = P__[iP_u8];
    result__[ 14  ] = -10 - t8;
    result__[ 15  ] = t8 - 10;
    real_type t9   = P__[iP_u9];
    result__[ 16  ] = -10 - t9;
    result__[ 17  ] = t9 - 10;
    real_type t10  = P__[iP_u10];
    result__[ 18  ] = -10 - t10;
    result__[ 19  ] = t10 - 10;
    real_type t11  = P__[iP_u11];
    result__[ 20  ] = -10 - t11;
    result__[ 21  ] = t11 - 10;
    real_type t12  = P__[iP_u12];
    result__[ 22  ] = -10 - t12;
    result__[ 23  ] = t12 - 10;
    real_type t13  = P__[iP_u13];
    result__[ 24  ] = -10 - t13;
    result__[ 25  ] = t13 - 10;
    real_type t14  = P__[iP_u14];
    result__[ 26  ] = -10 - t14;
    result__[ 27  ] = t14 - 10;
    real_type t15  = P__[iP_u15];
    result__[ 28  ] = -10 - t15;
    result__[ 29  ] = t15 - 10;
    real_type t16  = P__[iP_u16];
    result__[ 30  ] = -10 - t16;
    result__[ 31  ] = t16 - 10;
    real_type t17  = P__[iP_u17];
    result__[ 32  ] = -10 - t17;
    result__[ 33  ] = t17 - 10;
    real_type t18  = P__[iP_u18];
    result__[ 34  ] = -10 - t18;
    result__[ 35  ] = t18 - 10;
    real_type t19  = P__[iP_u19];
    result__[ 36  ] = -10 - t19;
    result__[ 37  ] = t19 - 10;
    real_type t20  = P__[iP_u20];
    result__[ 38  ] = -10 - t20;
    result__[ 39  ] = t20 - 10;
    real_type t21  = ModelPars[iM_xy_bound];
    real_type t22  = X__[iX_xx1];
    result__[ 40  ] = -t21 - t22;
    result__[ 41  ] = t22 - t21;
    real_type t23  = X__[iX_yy1];
    result__[ 42  ] = -t21 - t23;
    result__[ 43  ] = t23 - t21;
    real_type t24  = X__[iX_xx2];
    result__[ 44  ] = -t21 - t24;
    result__[ 45  ] = t24 - t21;
    real_type t25  = X__[iX_yy2];
    result__[ 46  ] = -t21 - t25;
    result__[ 47  ] = t25 - t21;
    real_type t26  = X__[iX_xx3];
    result__[ 48  ] = -t21 - t26;
    result__[ 49  ] = t26 - t21;
    real_type t27  = X__[iX_yy3];
    result__[ 50  ] = -t21 - t27;
    result__[ 51  ] = t27 - t21;
    real_type t28  = X__[iX_xx4];
    result__[ 52  ] = -t21 - t28;
    result__[ 53  ] = t28 - t21;
    real_type t29  = X__[iX_yy4];
    result__[ 54  ] = -t21 - t29;
    result__[ 55  ] = t29 - t21;
    real_type t30  = X__[iX_xx5];
    result__[ 56  ] = -t21 - t30;
    result__[ 57  ] = t30 - t21;
    real_type t31  = X__[iX_yy5];
    result__[ 58  ] = -t21 - t31;
    result__[ 59  ] = t31 - t21;
    real_type t32  = X__[iX_xx6];
    result__[ 60  ] = -t21 - t32;
    result__[ 61  ] = t32 - t21;
    real_type t33  = X__[iX_yy6];
    result__[ 62  ] = -t21 - t33;
    result__[ 63  ] = t33 - t21;
    real_type t34  = X__[iX_xx7];
    result__[ 64  ] = -t21 - t34;
    result__[ 65  ] = t34 - t21;
    real_type t35  = X__[iX_yy7];
    result__[ 66  ] = -t21 - t35;
    result__[ 67  ] = t35 - t21;
    real_type t36  = X__[iX_xx8];
    result__[ 68  ] = -t21 - t36;
    result__[ 69  ] = t36 - t21;
    real_type t37  = X__[iX_yy8];
    result__[ 70  ] = -t21 - t37;
    result__[ 71  ] = t37 - t21;
    real_type t38  = X__[iX_xx9];
    result__[ 72  ] = -t21 - t38;
    result__[ 73  ] = t38 - t21;
    real_type t39  = X__[iX_yy9];
    result__[ 74  ] = -t21 - t39;
    result__[ 75  ] = t39 - t21;
    real_type t40  = X__[iX_xx10];
    result__[ 76  ] = -t21 - t40;
    result__[ 77  ] = t40 - t21;
    real_type t41  = X__[iX_yy10];
    result__[ 78  ] = -t21 - t41;
    result__[ 79  ] = t41 - t21;
    real_type t42  = X__[iX_xx11];
    result__[ 80  ] = -t21 - t42;
    result__[ 81  ] = t42 - t21;
    real_type t43  = X__[iX_yy11];
    result__[ 82  ] = -t21 - t43;
    result__[ 83  ] = t43 - t21;
    real_type t44  = X__[iX_xx12];
    result__[ 84  ] = -t21 - t44;
    result__[ 85  ] = t44 - t21;
    real_type t45  = X__[iX_yy12];
    result__[ 86  ] = -t21 - t45;
    result__[ 87  ] = t45 - t21;
    real_type t46  = X__[iX_xx13];
    result__[ 88  ] = -t21 - t46;
    result__[ 89  ] = t46 - t21;
    real_type t47  = X__[iX_yy13];
    result__[ 90  ] = -t21 - t47;
    result__[ 91  ] = t47 - t21;
    real_type t48  = X__[iX_xx14];
    result__[ 92  ] = -t21 - t48;
    result__[ 93  ] = t48 - t21;
    real_type t49  = X__[iX_yy14];
    result__[ 94  ] = -t21 - t49;
    result__[ 95  ] = t49 - t21;
    real_type t50  = X__[iX_xx15];
    result__[ 96  ] = -t21 - t50;
    result__[ 97  ] = t50 - t21;
    real_type t51  = X__[iX_yy15];
    result__[ 98  ] = -t21 - t51;
    result__[ 99  ] = t51 - t21;
    real_type t52  = X__[iX_xx16];
    result__[ 100 ] = -t21 - t52;
    result__[ 101 ] = t52 - t21;
    real_type t53  = X__[iX_yy16];
    result__[ 102 ] = -t21 - t53;
    result__[ 103 ] = t53 - t21;
    real_type t54  = X__[iX_xx17];
    result__[ 104 ] = -t21 - t54;
    result__[ 105 ] = t54 - t21;
    real_type t55  = X__[iX_yy17];
    result__[ 106 ] = -t21 - t55;
    result__[ 107 ] = t55 - t21;
    real_type t56  = X__[iX_xx18];
    result__[ 108 ] = -t21 - t56;
    result__[ 109 ] = t56 - t21;
    real_type t57  = X__[iX_yy18];
    result__[ 110 ] = -t21 - t57;
    result__[ 111 ] = t57 - t21;
    real_type t58  = X__[iX_xx19];
    result__[ 112 ] = -t21 - t58;
    result__[ 113 ] = t58 - t21;
    real_type t59  = X__[iX_yy19];
    result__[ 114 ] = -t21 - t59;
    result__[ 115 ] = t59 - t21;
    real_type t60  = X__[iX_xx20];
    result__[ 116 ] = -t21 - t60;
    result__[ 117 ] = t60 - t21;
    real_type t61  = X__[iX_yy20];
    result__[ 118 ] = -t21 - t61;
    result__[ 119 ] = t61 - t21;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 120, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJPDxpu_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DJPDxpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJPDxpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTDxpu_numRows() const { return 120; }
  integer ICLOCS_ContinuousMP::DLTDxpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DLTDxpu_nnz()     const { return 120; }

  void
  ICLOCS_ContinuousMP::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 80  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 80  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 81  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 81  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 82  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 82  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 83  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 83  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 84  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 84  ;
    iIndex[10] = 10  ; jIndex[10] = 85  ;
    iIndex[11] = 11  ; jIndex[11] = 85  ;
    iIndex[12] = 12  ; jIndex[12] = 86  ;
    iIndex[13] = 13  ; jIndex[13] = 86  ;
    iIndex[14] = 14  ; jIndex[14] = 87  ;
    iIndex[15] = 15  ; jIndex[15] = 87  ;
    iIndex[16] = 16  ; jIndex[16] = 88  ;
    iIndex[17] = 17  ; jIndex[17] = 88  ;
    iIndex[18] = 18  ; jIndex[18] = 89  ;
    iIndex[19] = 19  ; jIndex[19] = 89  ;
    iIndex[20] = 20  ; jIndex[20] = 90  ;
    iIndex[21] = 21  ; jIndex[21] = 90  ;
    iIndex[22] = 22  ; jIndex[22] = 91  ;
    iIndex[23] = 23  ; jIndex[23] = 91  ;
    iIndex[24] = 24  ; jIndex[24] = 92  ;
    iIndex[25] = 25  ; jIndex[25] = 92  ;
    iIndex[26] = 26  ; jIndex[26] = 93  ;
    iIndex[27] = 27  ; jIndex[27] = 93  ;
    iIndex[28] = 28  ; jIndex[28] = 94  ;
    iIndex[29] = 29  ; jIndex[29] = 94  ;
    iIndex[30] = 30  ; jIndex[30] = 95  ;
    iIndex[31] = 31  ; jIndex[31] = 95  ;
    iIndex[32] = 32  ; jIndex[32] = 96  ;
    iIndex[33] = 33  ; jIndex[33] = 96  ;
    iIndex[34] = 34  ; jIndex[34] = 97  ;
    iIndex[35] = 35  ; jIndex[35] = 97  ;
    iIndex[36] = 36  ; jIndex[36] = 98  ;
    iIndex[37] = 37  ; jIndex[37] = 98  ;
    iIndex[38] = 38  ; jIndex[38] = 99  ;
    iIndex[39] = 39  ; jIndex[39] = 99  ;
    iIndex[40] = 40  ; jIndex[40] = 40  ;
    iIndex[41] = 41  ; jIndex[41] = 40  ;
    iIndex[42] = 42  ; jIndex[42] = 60  ;
    iIndex[43] = 43  ; jIndex[43] = 60  ;
    iIndex[44] = 44  ; jIndex[44] = 41  ;
    iIndex[45] = 45  ; jIndex[45] = 41  ;
    iIndex[46] = 46  ; jIndex[46] = 61  ;
    iIndex[47] = 47  ; jIndex[47] = 61  ;
    iIndex[48] = 48  ; jIndex[48] = 42  ;
    iIndex[49] = 49  ; jIndex[49] = 42  ;
    iIndex[50] = 50  ; jIndex[50] = 62  ;
    iIndex[51] = 51  ; jIndex[51] = 62  ;
    iIndex[52] = 52  ; jIndex[52] = 43  ;
    iIndex[53] = 53  ; jIndex[53] = 43  ;
    iIndex[54] = 54  ; jIndex[54] = 63  ;
    iIndex[55] = 55  ; jIndex[55] = 63  ;
    iIndex[56] = 56  ; jIndex[56] = 44  ;
    iIndex[57] = 57  ; jIndex[57] = 44  ;
    iIndex[58] = 58  ; jIndex[58] = 64  ;
    iIndex[59] = 59  ; jIndex[59] = 64  ;
    iIndex[60] = 60  ; jIndex[60] = 45  ;
    iIndex[61] = 61  ; jIndex[61] = 45  ;
    iIndex[62] = 62  ; jIndex[62] = 65  ;
    iIndex[63] = 63  ; jIndex[63] = 65  ;
    iIndex[64] = 64  ; jIndex[64] = 46  ;
    iIndex[65] = 65  ; jIndex[65] = 46  ;
    iIndex[66] = 66  ; jIndex[66] = 66  ;
    iIndex[67] = 67  ; jIndex[67] = 66  ;
    iIndex[68] = 68  ; jIndex[68] = 47  ;
    iIndex[69] = 69  ; jIndex[69] = 47  ;
    iIndex[70] = 70  ; jIndex[70] = 67  ;
    iIndex[71] = 71  ; jIndex[71] = 67  ;
    iIndex[72] = 72  ; jIndex[72] = 48  ;
    iIndex[73] = 73  ; jIndex[73] = 48  ;
    iIndex[74] = 74  ; jIndex[74] = 68  ;
    iIndex[75] = 75  ; jIndex[75] = 68  ;
    iIndex[76] = 76  ; jIndex[76] = 49  ;
    iIndex[77] = 77  ; jIndex[77] = 49  ;
    iIndex[78] = 78  ; jIndex[78] = 69  ;
    iIndex[79] = 79  ; jIndex[79] = 69  ;
    iIndex[80] = 80  ; jIndex[80] = 50  ;
    iIndex[81] = 81  ; jIndex[81] = 50  ;
    iIndex[82] = 82  ; jIndex[82] = 70  ;
    iIndex[83] = 83  ; jIndex[83] = 70  ;
    iIndex[84] = 84  ; jIndex[84] = 51  ;
    iIndex[85] = 85  ; jIndex[85] = 51  ;
    iIndex[86] = 86  ; jIndex[86] = 71  ;
    iIndex[87] = 87  ; jIndex[87] = 71  ;
    iIndex[88] = 88  ; jIndex[88] = 52  ;
    iIndex[89] = 89  ; jIndex[89] = 52  ;
    iIndex[90] = 90  ; jIndex[90] = 72  ;
    iIndex[91] = 91  ; jIndex[91] = 72  ;
    iIndex[92] = 92  ; jIndex[92] = 53  ;
    iIndex[93] = 93  ; jIndex[93] = 53  ;
    iIndex[94] = 94  ; jIndex[94] = 73  ;
    iIndex[95] = 95  ; jIndex[95] = 73  ;
    iIndex[96] = 96  ; jIndex[96] = 54  ;
    iIndex[97] = 97  ; jIndex[97] = 54  ;
    iIndex[98] = 98  ; jIndex[98] = 74  ;
    iIndex[99] = 99  ; jIndex[99] = 74  ;
    iIndex[100] = 100 ; jIndex[100] = 55  ;
    iIndex[101] = 101 ; jIndex[101] = 55  ;
    iIndex[102] = 102 ; jIndex[102] = 75  ;
    iIndex[103] = 103 ; jIndex[103] = 75  ;
    iIndex[104] = 104 ; jIndex[104] = 56  ;
    iIndex[105] = 105 ; jIndex[105] = 56  ;
    iIndex[106] = 106 ; jIndex[106] = 76  ;
    iIndex[107] = 107 ; jIndex[107] = 76  ;
    iIndex[108] = 108 ; jIndex[108] = 57  ;
    iIndex[109] = 109 ; jIndex[109] = 57  ;
    iIndex[110] = 110 ; jIndex[110] = 77  ;
    iIndex[111] = 111 ; jIndex[111] = 77  ;
    iIndex[112] = 112 ; jIndex[112] = 58  ;
    iIndex[113] = 113 ; jIndex[113] = 58  ;
    iIndex[114] = 114 ; jIndex[114] = 78  ;
    iIndex[115] = 115 ; jIndex[115] = 78  ;
    iIndex[116] = 116 ; jIndex[116] = 59  ;
    iIndex[117] = 117 ; jIndex[117] = 59  ;
    iIndex[118] = 118 ; jIndex[118] = 79  ;
    iIndex[119] = 119 ; jIndex[119] = 79  ;
  }


  void
  ICLOCS_ContinuousMP::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_u1];
    real_type t3   = ALIAS_u1Limitation_min_D(-10 - t1);
    result__[ 0   ] = -t3;
    result__[ 1   ] = ALIAS_u1Limitation_max_D(t1 - 10);
    real_type t5   = P__[iP_u2];
    real_type t7   = ALIAS_u2Limitation_min_D(-10 - t5);
    result__[ 2   ] = -t7;
    result__[ 3   ] = ALIAS_u2Limitation_max_D(t5 - 10);
    real_type t9   = P__[iP_u3];
    real_type t11  = ALIAS_u3Limitation_min_D(-10 - t9);
    result__[ 4   ] = -t11;
    result__[ 5   ] = ALIAS_u3Limitation_max_D(t9 - 10);
    real_type t13  = P__[iP_u4];
    real_type t15  = ALIAS_u4Limitation_min_D(-10 - t13);
    result__[ 6   ] = -t15;
    result__[ 7   ] = ALIAS_u4Limitation_max_D(t13 - 10);
    real_type t17  = P__[iP_u5];
    real_type t19  = ALIAS_u5Limitation_min_D(-10 - t17);
    result__[ 8   ] = -t19;
    result__[ 9   ] = ALIAS_u5Limitation_max_D(t17 - 10);
    real_type t21  = P__[iP_u6];
    real_type t23  = ALIAS_u6Limitation_min_D(-10 - t21);
    result__[ 10  ] = -t23;
    result__[ 11  ] = ALIAS_u6Limitation_max_D(t21 - 10);
    real_type t25  = P__[iP_u7];
    real_type t27  = ALIAS_u7Limitation_min_D(-10 - t25);
    result__[ 12  ] = -t27;
    result__[ 13  ] = ALIAS_u7Limitation_max_D(t25 - 10);
    real_type t29  = P__[iP_u8];
    real_type t31  = ALIAS_u8Limitation_min_D(-10 - t29);
    result__[ 14  ] = -t31;
    result__[ 15  ] = ALIAS_u8Limitation_max_D(t29 - 10);
    real_type t33  = P__[iP_u9];
    real_type t35  = ALIAS_u9Limitation_min_D(-10 - t33);
    result__[ 16  ] = -t35;
    result__[ 17  ] = ALIAS_u9Limitation_max_D(t33 - 10);
    real_type t37  = P__[iP_u10];
    real_type t39  = ALIAS_u10Limitation_min_D(-10 - t37);
    result__[ 18  ] = -t39;
    result__[ 19  ] = ALIAS_u10Limitation_max_D(t37 - 10);
    real_type t41  = P__[iP_u11];
    real_type t43  = ALIAS_u11Limitation_min_D(-10 - t41);
    result__[ 20  ] = -t43;
    result__[ 21  ] = ALIAS_u11Limitation_max_D(t41 - 10);
    real_type t45  = P__[iP_u12];
    real_type t47  = ALIAS_u12Limitation_min_D(-10 - t45);
    result__[ 22  ] = -t47;
    result__[ 23  ] = ALIAS_u12Limitation_max_D(t45 - 10);
    real_type t49  = P__[iP_u13];
    real_type t51  = ALIAS_u13Limitation_min_D(-10 - t49);
    result__[ 24  ] = -t51;
    result__[ 25  ] = ALIAS_u13Limitation_max_D(t49 - 10);
    real_type t53  = P__[iP_u14];
    real_type t55  = ALIAS_u14Limitation_min_D(-10 - t53);
    result__[ 26  ] = -t55;
    result__[ 27  ] = ALIAS_u14Limitation_max_D(t53 - 10);
    real_type t57  = P__[iP_u15];
    real_type t59  = ALIAS_u15Limitation_min_D(-10 - t57);
    result__[ 28  ] = -t59;
    result__[ 29  ] = ALIAS_u15Limitation_max_D(t57 - 10);
    real_type t61  = P__[iP_u16];
    real_type t63  = ALIAS_u16Limitation_min_D(-10 - t61);
    result__[ 30  ] = -t63;
    result__[ 31  ] = ALIAS_u16Limitation_max_D(t61 - 10);
    real_type t65  = P__[iP_u17];
    real_type t67  = ALIAS_u17Limitation_min_D(-10 - t65);
    result__[ 32  ] = -t67;
    result__[ 33  ] = ALIAS_u17Limitation_max_D(t65 - 10);
    real_type t69  = P__[iP_u18];
    real_type t71  = ALIAS_u18Limitation_min_D(-10 - t69);
    result__[ 34  ] = -t71;
    result__[ 35  ] = ALIAS_u18Limitation_max_D(t69 - 10);
    real_type t73  = P__[iP_u19];
    real_type t75  = ALIAS_u19Limitation_min_D(-10 - t73);
    result__[ 36  ] = -t75;
    result__[ 37  ] = ALIAS_u19Limitation_max_D(t73 - 10);
    real_type t77  = P__[iP_u20];
    real_type t79  = ALIAS_u20Limitation_min_D(-10 - t77);
    result__[ 38  ] = -t79;
    result__[ 39  ] = ALIAS_u20Limitation_max_D(t77 - 10);
    real_type t81  = ModelPars[iM_xy_bound];
    real_type t82  = X__[iX_xx1];
    real_type t84  = ALIAS_xx1Limitation_min_D(-t81 - t82);
    result__[ 40  ] = -t84;
    result__[ 41  ] = ALIAS_xx1Limitation_max_D(t82 - t81);
    real_type t86  = X__[iX_yy1];
    real_type t88  = ALIAS_yy1Limitation_min_D(-t81 - t86);
    result__[ 42  ] = -t88;
    result__[ 43  ] = ALIAS_yy1Limitation_max_D(t86 - t81);
    real_type t90  = X__[iX_xx2];
    real_type t92  = ALIAS_xx2Limitation_min_D(-t81 - t90);
    result__[ 44  ] = -t92;
    result__[ 45  ] = ALIAS_xx2Limitation_max_D(t90 - t81);
    real_type t94  = X__[iX_yy2];
    real_type t96  = ALIAS_yy2Limitation_min_D(-t81 - t94);
    result__[ 46  ] = -t96;
    result__[ 47  ] = ALIAS_yy2Limitation_max_D(t94 - t81);
    real_type t98  = X__[iX_xx3];
    real_type t100 = ALIAS_xx3Limitation_min_D(-t81 - t98);
    result__[ 48  ] = -t100;
    result__[ 49  ] = ALIAS_xx3Limitation_max_D(t98 - t81);
    real_type t102 = X__[iX_yy3];
    real_type t104 = ALIAS_yy3Limitation_min_D(-t81 - t102);
    result__[ 50  ] = -t104;
    result__[ 51  ] = ALIAS_yy3Limitation_max_D(t102 - t81);
    real_type t106 = X__[iX_xx4];
    real_type t108 = ALIAS_xx4Limitation_min_D(-t81 - t106);
    result__[ 52  ] = -t108;
    result__[ 53  ] = ALIAS_xx4Limitation_max_D(t106 - t81);
    real_type t110 = X__[iX_yy4];
    real_type t112 = ALIAS_yy4Limitation_min_D(-t81 - t110);
    result__[ 54  ] = -t112;
    result__[ 55  ] = ALIAS_yy4Limitation_max_D(t110 - t81);
    real_type t114 = X__[iX_xx5];
    real_type t116 = ALIAS_xx5Limitation_min_D(-t81 - t114);
    result__[ 56  ] = -t116;
    result__[ 57  ] = ALIAS_xx5Limitation_max_D(t114 - t81);
    real_type t118 = X__[iX_yy5];
    real_type t120 = ALIAS_yy5Limitation_min_D(-t81 - t118);
    result__[ 58  ] = -t120;
    result__[ 59  ] = ALIAS_yy5Limitation_max_D(t118 - t81);
    real_type t122 = X__[iX_xx6];
    real_type t124 = ALIAS_xx6Limitation_min_D(-t81 - t122);
    result__[ 60  ] = -t124;
    result__[ 61  ] = ALIAS_xx6Limitation_max_D(t122 - t81);
    real_type t126 = X__[iX_yy6];
    real_type t128 = ALIAS_yy6Limitation_min_D(-t81 - t126);
    result__[ 62  ] = -t128;
    result__[ 63  ] = ALIAS_yy6Limitation_max_D(t126 - t81);
    real_type t130 = X__[iX_xx7];
    real_type t132 = ALIAS_xx7Limitation_min_D(-t81 - t130);
    result__[ 64  ] = -t132;
    result__[ 65  ] = ALIAS_xx7Limitation_max_D(t130 - t81);
    real_type t134 = X__[iX_yy7];
    real_type t136 = ALIAS_yy7Limitation_min_D(-t81 - t134);
    result__[ 66  ] = -t136;
    result__[ 67  ] = ALIAS_yy7Limitation_max_D(t134 - t81);
    real_type t138 = X__[iX_xx8];
    real_type t140 = ALIAS_xx8Limitation_min_D(-t81 - t138);
    result__[ 68  ] = -t140;
    result__[ 69  ] = ALIAS_xx8Limitation_max_D(t138 - t81);
    real_type t142 = X__[iX_yy8];
    real_type t144 = ALIAS_yy8Limitation_min_D(-t81 - t142);
    result__[ 70  ] = -t144;
    result__[ 71  ] = ALIAS_yy8Limitation_max_D(t142 - t81);
    real_type t146 = X__[iX_xx9];
    real_type t148 = ALIAS_xx9Limitation_min_D(-t81 - t146);
    result__[ 72  ] = -t148;
    result__[ 73  ] = ALIAS_xx9Limitation_max_D(t146 - t81);
    real_type t150 = X__[iX_yy9];
    real_type t152 = ALIAS_yy9Limitation_min_D(-t81 - t150);
    result__[ 74  ] = -t152;
    result__[ 75  ] = ALIAS_yy9Limitation_max_D(t150 - t81);
    real_type t154 = X__[iX_xx10];
    real_type t156 = ALIAS_xx10Limitation_min_D(-t81 - t154);
    result__[ 76  ] = -t156;
    result__[ 77  ] = ALIAS_xx10Limitation_max_D(t154 - t81);
    real_type t158 = X__[iX_yy10];
    real_type t160 = ALIAS_yy10Limitation_min_D(-t81 - t158);
    result__[ 78  ] = -t160;
    result__[ 79  ] = ALIAS_yy10Limitation_max_D(t158 - t81);
    real_type t162 = X__[iX_xx11];
    real_type t164 = ALIAS_xx11Limitation_min_D(-t81 - t162);
    result__[ 80  ] = -t164;
    result__[ 81  ] = ALIAS_xx11Limitation_max_D(t162 - t81);
    real_type t166 = X__[iX_yy11];
    real_type t168 = ALIAS_yy11Limitation_min_D(-t81 - t166);
    result__[ 82  ] = -t168;
    result__[ 83  ] = ALIAS_yy11Limitation_max_D(t166 - t81);
    real_type t170 = X__[iX_xx12];
    real_type t172 = ALIAS_xx12Limitation_min_D(-t81 - t170);
    result__[ 84  ] = -t172;
    result__[ 85  ] = ALIAS_xx12Limitation_max_D(t170 - t81);
    real_type t174 = X__[iX_yy12];
    real_type t176 = ALIAS_yy12Limitation_min_D(-t81 - t174);
    result__[ 86  ] = -t176;
    result__[ 87  ] = ALIAS_yy12Limitation_max_D(t174 - t81);
    real_type t178 = X__[iX_xx13];
    real_type t180 = ALIAS_xx13Limitation_min_D(-t81 - t178);
    result__[ 88  ] = -t180;
    result__[ 89  ] = ALIAS_xx13Limitation_max_D(t178 - t81);
    real_type t182 = X__[iX_yy13];
    real_type t184 = ALIAS_yy13Limitation_min_D(-t81 - t182);
    result__[ 90  ] = -t184;
    result__[ 91  ] = ALIAS_yy13Limitation_max_D(t182 - t81);
    real_type t186 = X__[iX_xx14];
    real_type t188 = ALIAS_xx14Limitation_min_D(-t81 - t186);
    result__[ 92  ] = -t188;
    result__[ 93  ] = ALIAS_xx14Limitation_max_D(t186 - t81);
    real_type t190 = X__[iX_yy14];
    real_type t192 = ALIAS_yy14Limitation_min_D(-t81 - t190);
    result__[ 94  ] = -t192;
    result__[ 95  ] = ALIAS_yy14Limitation_max_D(t190 - t81);
    real_type t194 = X__[iX_xx15];
    real_type t196 = ALIAS_xx15Limitation_min_D(-t81 - t194);
    result__[ 96  ] = -t196;
    result__[ 97  ] = ALIAS_xx15Limitation_max_D(t194 - t81);
    real_type t198 = X__[iX_yy15];
    real_type t200 = ALIAS_yy15Limitation_min_D(-t81 - t198);
    result__[ 98  ] = -t200;
    result__[ 99  ] = ALIAS_yy15Limitation_max_D(t198 - t81);
    real_type t202 = X__[iX_xx16];
    real_type t204 = ALIAS_xx16Limitation_min_D(-t81 - t202);
    result__[ 100 ] = -t204;
    result__[ 101 ] = ALIAS_xx16Limitation_max_D(t202 - t81);
    real_type t206 = X__[iX_yy16];
    real_type t208 = ALIAS_yy16Limitation_min_D(-t81 - t206);
    result__[ 102 ] = -t208;
    result__[ 103 ] = ALIAS_yy16Limitation_max_D(t206 - t81);
    real_type t210 = X__[iX_xx17];
    real_type t212 = ALIAS_xx17Limitation_min_D(-t81 - t210);
    result__[ 104 ] = -t212;
    result__[ 105 ] = ALIAS_xx17Limitation_max_D(t210 - t81);
    real_type t214 = X__[iX_yy17];
    real_type t216 = ALIAS_yy17Limitation_min_D(-t81 - t214);
    result__[ 106 ] = -t216;
    result__[ 107 ] = ALIAS_yy17Limitation_max_D(t214 - t81);
    real_type t218 = X__[iX_xx18];
    real_type t220 = ALIAS_xx18Limitation_min_D(-t81 - t218);
    result__[ 108 ] = -t220;
    result__[ 109 ] = ALIAS_xx18Limitation_max_D(t218 - t81);
    real_type t222 = X__[iX_yy18];
    real_type t224 = ALIAS_yy18Limitation_min_D(-t81 - t222);
    result__[ 110 ] = -t224;
    result__[ 111 ] = ALIAS_yy18Limitation_max_D(t222 - t81);
    real_type t226 = X__[iX_xx19];
    real_type t228 = ALIAS_xx19Limitation_min_D(-t81 - t226);
    result__[ 112 ] = -t228;
    result__[ 113 ] = ALIAS_xx19Limitation_max_D(t226 - t81);
    real_type t230 = X__[iX_yy19];
    real_type t232 = ALIAS_yy19Limitation_min_D(-t81 - t230);
    result__[ 114 ] = -t232;
    result__[ 115 ] = ALIAS_yy19Limitation_max_D(t230 - t81);
    real_type t234 = X__[iX_xx20];
    real_type t236 = ALIAS_xx20Limitation_min_D(-t81 - t234);
    result__[ 116 ] = -t236;
    result__[ 117 ] = ALIAS_xx20Limitation_max_D(t234 - t81);
    real_type t238 = X__[iX_yy20];
    real_type t240 = ALIAS_yy20Limitation_min_D(-t81 - t238);
    result__[ 118 ] = -t240;
    result__[ 119 ] = ALIAS_yy20Limitation_max_D(t238 - t81);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 120, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJUDxpu_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DJUDxpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJUDxpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTargsDxpu_numRows() const { return 120; }
  integer ICLOCS_ContinuousMP::DLTargsDxpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DLTargsDxpu_nnz()     const { return 120; }

  void
  ICLOCS_ContinuousMP::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 80  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 80  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 81  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 81  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 82  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 82  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 83  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 83  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 84  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 84  ;
    iIndex[10] = 10  ; jIndex[10] = 85  ;
    iIndex[11] = 11  ; jIndex[11] = 85  ;
    iIndex[12] = 12  ; jIndex[12] = 86  ;
    iIndex[13] = 13  ; jIndex[13] = 86  ;
    iIndex[14] = 14  ; jIndex[14] = 87  ;
    iIndex[15] = 15  ; jIndex[15] = 87  ;
    iIndex[16] = 16  ; jIndex[16] = 88  ;
    iIndex[17] = 17  ; jIndex[17] = 88  ;
    iIndex[18] = 18  ; jIndex[18] = 89  ;
    iIndex[19] = 19  ; jIndex[19] = 89  ;
    iIndex[20] = 20  ; jIndex[20] = 90  ;
    iIndex[21] = 21  ; jIndex[21] = 90  ;
    iIndex[22] = 22  ; jIndex[22] = 91  ;
    iIndex[23] = 23  ; jIndex[23] = 91  ;
    iIndex[24] = 24  ; jIndex[24] = 92  ;
    iIndex[25] = 25  ; jIndex[25] = 92  ;
    iIndex[26] = 26  ; jIndex[26] = 93  ;
    iIndex[27] = 27  ; jIndex[27] = 93  ;
    iIndex[28] = 28  ; jIndex[28] = 94  ;
    iIndex[29] = 29  ; jIndex[29] = 94  ;
    iIndex[30] = 30  ; jIndex[30] = 95  ;
    iIndex[31] = 31  ; jIndex[31] = 95  ;
    iIndex[32] = 32  ; jIndex[32] = 96  ;
    iIndex[33] = 33  ; jIndex[33] = 96  ;
    iIndex[34] = 34  ; jIndex[34] = 97  ;
    iIndex[35] = 35  ; jIndex[35] = 97  ;
    iIndex[36] = 36  ; jIndex[36] = 98  ;
    iIndex[37] = 37  ; jIndex[37] = 98  ;
    iIndex[38] = 38  ; jIndex[38] = 99  ;
    iIndex[39] = 39  ; jIndex[39] = 99  ;
    iIndex[40] = 40  ; jIndex[40] = 40  ;
    iIndex[41] = 41  ; jIndex[41] = 40  ;
    iIndex[42] = 42  ; jIndex[42] = 60  ;
    iIndex[43] = 43  ; jIndex[43] = 60  ;
    iIndex[44] = 44  ; jIndex[44] = 41  ;
    iIndex[45] = 45  ; jIndex[45] = 41  ;
    iIndex[46] = 46  ; jIndex[46] = 61  ;
    iIndex[47] = 47  ; jIndex[47] = 61  ;
    iIndex[48] = 48  ; jIndex[48] = 42  ;
    iIndex[49] = 49  ; jIndex[49] = 42  ;
    iIndex[50] = 50  ; jIndex[50] = 62  ;
    iIndex[51] = 51  ; jIndex[51] = 62  ;
    iIndex[52] = 52  ; jIndex[52] = 43  ;
    iIndex[53] = 53  ; jIndex[53] = 43  ;
    iIndex[54] = 54  ; jIndex[54] = 63  ;
    iIndex[55] = 55  ; jIndex[55] = 63  ;
    iIndex[56] = 56  ; jIndex[56] = 44  ;
    iIndex[57] = 57  ; jIndex[57] = 44  ;
    iIndex[58] = 58  ; jIndex[58] = 64  ;
    iIndex[59] = 59  ; jIndex[59] = 64  ;
    iIndex[60] = 60  ; jIndex[60] = 45  ;
    iIndex[61] = 61  ; jIndex[61] = 45  ;
    iIndex[62] = 62  ; jIndex[62] = 65  ;
    iIndex[63] = 63  ; jIndex[63] = 65  ;
    iIndex[64] = 64  ; jIndex[64] = 46  ;
    iIndex[65] = 65  ; jIndex[65] = 46  ;
    iIndex[66] = 66  ; jIndex[66] = 66  ;
    iIndex[67] = 67  ; jIndex[67] = 66  ;
    iIndex[68] = 68  ; jIndex[68] = 47  ;
    iIndex[69] = 69  ; jIndex[69] = 47  ;
    iIndex[70] = 70  ; jIndex[70] = 67  ;
    iIndex[71] = 71  ; jIndex[71] = 67  ;
    iIndex[72] = 72  ; jIndex[72] = 48  ;
    iIndex[73] = 73  ; jIndex[73] = 48  ;
    iIndex[74] = 74  ; jIndex[74] = 68  ;
    iIndex[75] = 75  ; jIndex[75] = 68  ;
    iIndex[76] = 76  ; jIndex[76] = 49  ;
    iIndex[77] = 77  ; jIndex[77] = 49  ;
    iIndex[78] = 78  ; jIndex[78] = 69  ;
    iIndex[79] = 79  ; jIndex[79] = 69  ;
    iIndex[80] = 80  ; jIndex[80] = 50  ;
    iIndex[81] = 81  ; jIndex[81] = 50  ;
    iIndex[82] = 82  ; jIndex[82] = 70  ;
    iIndex[83] = 83  ; jIndex[83] = 70  ;
    iIndex[84] = 84  ; jIndex[84] = 51  ;
    iIndex[85] = 85  ; jIndex[85] = 51  ;
    iIndex[86] = 86  ; jIndex[86] = 71  ;
    iIndex[87] = 87  ; jIndex[87] = 71  ;
    iIndex[88] = 88  ; jIndex[88] = 52  ;
    iIndex[89] = 89  ; jIndex[89] = 52  ;
    iIndex[90] = 90  ; jIndex[90] = 72  ;
    iIndex[91] = 91  ; jIndex[91] = 72  ;
    iIndex[92] = 92  ; jIndex[92] = 53  ;
    iIndex[93] = 93  ; jIndex[93] = 53  ;
    iIndex[94] = 94  ; jIndex[94] = 73  ;
    iIndex[95] = 95  ; jIndex[95] = 73  ;
    iIndex[96] = 96  ; jIndex[96] = 54  ;
    iIndex[97] = 97  ; jIndex[97] = 54  ;
    iIndex[98] = 98  ; jIndex[98] = 74  ;
    iIndex[99] = 99  ; jIndex[99] = 74  ;
    iIndex[100] = 100 ; jIndex[100] = 55  ;
    iIndex[101] = 101 ; jIndex[101] = 55  ;
    iIndex[102] = 102 ; jIndex[102] = 75  ;
    iIndex[103] = 103 ; jIndex[103] = 75  ;
    iIndex[104] = 104 ; jIndex[104] = 56  ;
    iIndex[105] = 105 ; jIndex[105] = 56  ;
    iIndex[106] = 106 ; jIndex[106] = 76  ;
    iIndex[107] = 107 ; jIndex[107] = 76  ;
    iIndex[108] = 108 ; jIndex[108] = 57  ;
    iIndex[109] = 109 ; jIndex[109] = 57  ;
    iIndex[110] = 110 ; jIndex[110] = 77  ;
    iIndex[111] = 111 ; jIndex[111] = 77  ;
    iIndex[112] = 112 ; jIndex[112] = 58  ;
    iIndex[113] = 113 ; jIndex[113] = 58  ;
    iIndex[114] = 114 ; jIndex[114] = 78  ;
    iIndex[115] = 115 ; jIndex[115] = 78  ;
    iIndex[116] = 116 ; jIndex[116] = 59  ;
    iIndex[117] = 117 ; jIndex[117] = 59  ;
    iIndex[118] = 118 ; jIndex[118] = 79  ;
    iIndex[119] = 119 ; jIndex[119] = 79  ;
  }


  void
  ICLOCS_ContinuousMP::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    result__[ 20  ] = -1;
    result__[ 21  ] = 1;
    result__[ 22  ] = -1;
    result__[ 23  ] = 1;
    result__[ 24  ] = -1;
    result__[ 25  ] = 1;
    result__[ 26  ] = -1;
    result__[ 27  ] = 1;
    result__[ 28  ] = -1;
    result__[ 29  ] = 1;
    result__[ 30  ] = -1;
    result__[ 31  ] = 1;
    result__[ 32  ] = -1;
    result__[ 33  ] = 1;
    result__[ 34  ] = -1;
    result__[ 35  ] = 1;
    result__[ 36  ] = -1;
    result__[ 37  ] = 1;
    result__[ 38  ] = -1;
    result__[ 39  ] = 1;
    result__[ 40  ] = -1;
    result__[ 41  ] = 1;
    result__[ 42  ] = -1;
    result__[ 43  ] = 1;
    result__[ 44  ] = -1;
    result__[ 45  ] = 1;
    result__[ 46  ] = -1;
    result__[ 47  ] = 1;
    result__[ 48  ] = -1;
    result__[ 49  ] = 1;
    result__[ 50  ] = -1;
    result__[ 51  ] = 1;
    result__[ 52  ] = -1;
    result__[ 53  ] = 1;
    result__[ 54  ] = -1;
    result__[ 55  ] = 1;
    result__[ 56  ] = -1;
    result__[ 57  ] = 1;
    result__[ 58  ] = -1;
    result__[ 59  ] = 1;
    result__[ 60  ] = -1;
    result__[ 61  ] = 1;
    result__[ 62  ] = -1;
    result__[ 63  ] = 1;
    result__[ 64  ] = -1;
    result__[ 65  ] = 1;
    result__[ 66  ] = -1;
    result__[ 67  ] = 1;
    result__[ 68  ] = -1;
    result__[ 69  ] = 1;
    result__[ 70  ] = -1;
    result__[ 71  ] = 1;
    result__[ 72  ] = -1;
    result__[ 73  ] = 1;
    result__[ 74  ] = -1;
    result__[ 75  ] = 1;
    result__[ 76  ] = -1;
    result__[ 77  ] = 1;
    result__[ 78  ] = -1;
    result__[ 79  ] = 1;
    result__[ 80  ] = -1;
    result__[ 81  ] = 1;
    result__[ 82  ] = -1;
    result__[ 83  ] = 1;
    result__[ 84  ] = -1;
    result__[ 85  ] = 1;
    result__[ 86  ] = -1;
    result__[ 87  ] = 1;
    result__[ 88  ] = -1;
    result__[ 89  ] = 1;
    result__[ 90  ] = -1;
    result__[ 91  ] = 1;
    result__[ 92  ] = -1;
    result__[ 93  ] = 1;
    result__[ 94  ] = -1;
    result__[ 95  ] = 1;
    result__[ 96  ] = -1;
    result__[ 97  ] = 1;
    result__[ 98  ] = -1;
    result__[ 99  ] = 1;
    result__[ 100 ] = -1;
    result__[ 101 ] = 1;
    result__[ 102 ] = -1;
    result__[ 103 ] = 1;
    result__[ 104 ] = -1;
    result__[ 105 ] = 1;
    result__[ 106 ] = -1;
    result__[ 107 ] = 1;
    result__[ 108 ] = -1;
    result__[ 109 ] = 1;
    result__[ 110 ] = -1;
    result__[ 111 ] = 1;
    result__[ 112 ] = -1;
    result__[ 113 ] = 1;
    result__[ 114 ] = -1;
    result__[ 115 ] = 1;
    result__[ 116 ] = -1;
    result__[ 117 ] = 1;
    result__[ 118 ] = -1;
    result__[ 119 ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 120, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2JPD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JPD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2LTD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTD2xpu_nnz()     const { return 60; }

  void
  ICLOCS_ContinuousMP::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 40  ; jIndex[0 ] = 40  ;
    iIndex[1 ] = 41  ; jIndex[1 ] = 41  ;
    iIndex[2 ] = 42  ; jIndex[2 ] = 42  ;
    iIndex[3 ] = 43  ; jIndex[3 ] = 43  ;
    iIndex[4 ] = 44  ; jIndex[4 ] = 44  ;
    iIndex[5 ] = 45  ; jIndex[5 ] = 45  ;
    iIndex[6 ] = 46  ; jIndex[6 ] = 46  ;
    iIndex[7 ] = 47  ; jIndex[7 ] = 47  ;
    iIndex[8 ] = 48  ; jIndex[8 ] = 48  ;
    iIndex[9 ] = 49  ; jIndex[9 ] = 49  ;
    iIndex[10] = 50  ; jIndex[10] = 50  ;
    iIndex[11] = 51  ; jIndex[11] = 51  ;
    iIndex[12] = 52  ; jIndex[12] = 52  ;
    iIndex[13] = 53  ; jIndex[13] = 53  ;
    iIndex[14] = 54  ; jIndex[14] = 54  ;
    iIndex[15] = 55  ; jIndex[15] = 55  ;
    iIndex[16] = 56  ; jIndex[16] = 56  ;
    iIndex[17] = 57  ; jIndex[17] = 57  ;
    iIndex[18] = 58  ; jIndex[18] = 58  ;
    iIndex[19] = 59  ; jIndex[19] = 59  ;
    iIndex[20] = 60  ; jIndex[20] = 60  ;
    iIndex[21] = 61  ; jIndex[21] = 61  ;
    iIndex[22] = 62  ; jIndex[22] = 62  ;
    iIndex[23] = 63  ; jIndex[23] = 63  ;
    iIndex[24] = 64  ; jIndex[24] = 64  ;
    iIndex[25] = 65  ; jIndex[25] = 65  ;
    iIndex[26] = 66  ; jIndex[26] = 66  ;
    iIndex[27] = 67  ; jIndex[27] = 67  ;
    iIndex[28] = 68  ; jIndex[28] = 68  ;
    iIndex[29] = 69  ; jIndex[29] = 69  ;
    iIndex[30] = 70  ; jIndex[30] = 70  ;
    iIndex[31] = 71  ; jIndex[31] = 71  ;
    iIndex[32] = 72  ; jIndex[32] = 72  ;
    iIndex[33] = 73  ; jIndex[33] = 73  ;
    iIndex[34] = 74  ; jIndex[34] = 74  ;
    iIndex[35] = 75  ; jIndex[35] = 75  ;
    iIndex[36] = 76  ; jIndex[36] = 76  ;
    iIndex[37] = 77  ; jIndex[37] = 77  ;
    iIndex[38] = 78  ; jIndex[38] = 78  ;
    iIndex[39] = 79  ; jIndex[39] = 79  ;
    iIndex[40] = 80  ; jIndex[40] = 80  ;
    iIndex[41] = 81  ; jIndex[41] = 81  ;
    iIndex[42] = 82  ; jIndex[42] = 82  ;
    iIndex[43] = 83  ; jIndex[43] = 83  ;
    iIndex[44] = 84  ; jIndex[44] = 84  ;
    iIndex[45] = 85  ; jIndex[45] = 85  ;
    iIndex[46] = 86  ; jIndex[46] = 86  ;
    iIndex[47] = 87  ; jIndex[47] = 87  ;
    iIndex[48] = 88  ; jIndex[48] = 88  ;
    iIndex[49] = 89  ; jIndex[49] = 89  ;
    iIndex[50] = 90  ; jIndex[50] = 90  ;
    iIndex[51] = 91  ; jIndex[51] = 91  ;
    iIndex[52] = 92  ; jIndex[52] = 92  ;
    iIndex[53] = 93  ; jIndex[53] = 93  ;
    iIndex[54] = 94  ; jIndex[54] = 94  ;
    iIndex[55] = 95  ; jIndex[55] = 95  ;
    iIndex[56] = 96  ; jIndex[56] = 96  ;
    iIndex[57] = 97  ; jIndex[57] = 97  ;
    iIndex[58] = 98  ; jIndex[58] = 98  ;
    iIndex[59] = 99  ; jIndex[59] = 99  ;
  }


  void
  ICLOCS_ContinuousMP::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_xx1];
    real_type t4   = ALIAS_xx1Limitation_min_DD(-t1 - t2);
    real_type t8   = ALIAS_xx1Limitation_max_DD(t2 - t1);
    result__[ 0   ] = OMEGA__[40] * t4 + OMEGA__[41] * t8;
    real_type t11  = X__[iX_xx2];
    real_type t13  = ALIAS_xx2Limitation_min_DD(-t1 - t11);
    real_type t17  = ALIAS_xx2Limitation_max_DD(t11 - t1);
    result__[ 1   ] = OMEGA__[44] * t13 + OMEGA__[45] * t17;
    real_type t20  = X__[iX_xx3];
    real_type t22  = ALIAS_xx3Limitation_min_DD(-t1 - t20);
    real_type t26  = ALIAS_xx3Limitation_max_DD(t20 - t1);
    result__[ 2   ] = OMEGA__[48] * t22 + OMEGA__[49] * t26;
    real_type t29  = X__[iX_xx4];
    real_type t31  = ALIAS_xx4Limitation_min_DD(-t1 - t29);
    real_type t35  = ALIAS_xx4Limitation_max_DD(t29 - t1);
    result__[ 3   ] = OMEGA__[52] * t31 + OMEGA__[53] * t35;
    real_type t38  = X__[iX_xx5];
    real_type t40  = ALIAS_xx5Limitation_min_DD(-t1 - t38);
    real_type t44  = ALIAS_xx5Limitation_max_DD(t38 - t1);
    result__[ 4   ] = OMEGA__[56] * t40 + OMEGA__[57] * t44;
    real_type t47  = X__[iX_xx6];
    real_type t49  = ALIAS_xx6Limitation_min_DD(-t1 - t47);
    real_type t53  = ALIAS_xx6Limitation_max_DD(t47 - t1);
    result__[ 5   ] = OMEGA__[60] * t49 + OMEGA__[61] * t53;
    real_type t56  = X__[iX_xx7];
    real_type t58  = ALIAS_xx7Limitation_min_DD(-t1 - t56);
    real_type t62  = ALIAS_xx7Limitation_max_DD(t56 - t1);
    result__[ 6   ] = OMEGA__[64] * t58 + OMEGA__[65] * t62;
    real_type t65  = X__[iX_xx8];
    real_type t67  = ALIAS_xx8Limitation_min_DD(-t1 - t65);
    real_type t71  = ALIAS_xx8Limitation_max_DD(t65 - t1);
    result__[ 7   ] = OMEGA__[68] * t67 + OMEGA__[69] * t71;
    real_type t74  = X__[iX_xx9];
    real_type t76  = ALIAS_xx9Limitation_min_DD(-t1 - t74);
    real_type t80  = ALIAS_xx9Limitation_max_DD(t74 - t1);
    result__[ 8   ] = OMEGA__[72] * t76 + OMEGA__[73] * t80;
    real_type t83  = X__[iX_xx10];
    real_type t85  = ALIAS_xx10Limitation_min_DD(-t1 - t83);
    real_type t89  = ALIAS_xx10Limitation_max_DD(t83 - t1);
    result__[ 9   ] = OMEGA__[76] * t85 + OMEGA__[77] * t89;
    real_type t92  = X__[iX_xx11];
    real_type t94  = ALIAS_xx11Limitation_min_DD(-t1 - t92);
    real_type t98  = ALIAS_xx11Limitation_max_DD(t92 - t1);
    result__[ 10  ] = OMEGA__[80] * t94 + OMEGA__[81] * t98;
    real_type t101 = X__[iX_xx12];
    real_type t103 = ALIAS_xx12Limitation_min_DD(-t1 - t101);
    real_type t107 = ALIAS_xx12Limitation_max_DD(t101 - t1);
    result__[ 11  ] = OMEGA__[84] * t103 + OMEGA__[85] * t107;
    real_type t110 = X__[iX_xx13];
    real_type t112 = ALIAS_xx13Limitation_min_DD(-t1 - t110);
    real_type t116 = ALIAS_xx13Limitation_max_DD(t110 - t1);
    result__[ 12  ] = OMEGA__[88] * t112 + OMEGA__[89] * t116;
    real_type t119 = X__[iX_xx14];
    real_type t121 = ALIAS_xx14Limitation_min_DD(-t1 - t119);
    real_type t125 = ALIAS_xx14Limitation_max_DD(t119 - t1);
    result__[ 13  ] = OMEGA__[92] * t121 + OMEGA__[93] * t125;
    real_type t128 = X__[iX_xx15];
    real_type t130 = ALIAS_xx15Limitation_min_DD(-t1 - t128);
    real_type t134 = ALIAS_xx15Limitation_max_DD(t128 - t1);
    result__[ 14  ] = OMEGA__[96] * t130 + OMEGA__[97] * t134;
    real_type t137 = X__[iX_xx16];
    real_type t139 = ALIAS_xx16Limitation_min_DD(-t1 - t137);
    real_type t143 = ALIAS_xx16Limitation_max_DD(t137 - t1);
    result__[ 15  ] = OMEGA__[100] * t139 + OMEGA__[101] * t143;
    real_type t146 = X__[iX_xx17];
    real_type t148 = ALIAS_xx17Limitation_min_DD(-t1 - t146);
    real_type t152 = ALIAS_xx17Limitation_max_DD(t146 - t1);
    result__[ 16  ] = OMEGA__[104] * t148 + OMEGA__[105] * t152;
    real_type t155 = X__[iX_xx18];
    real_type t157 = ALIAS_xx18Limitation_min_DD(-t1 - t155);
    real_type t161 = ALIAS_xx18Limitation_max_DD(t155 - t1);
    result__[ 17  ] = OMEGA__[108] * t157 + OMEGA__[109] * t161;
    real_type t164 = X__[iX_xx19];
    real_type t166 = ALIAS_xx19Limitation_min_DD(-t1 - t164);
    real_type t170 = ALIAS_xx19Limitation_max_DD(t164 - t1);
    result__[ 18  ] = OMEGA__[112] * t166 + OMEGA__[113] * t170;
    real_type t173 = X__[iX_xx20];
    real_type t175 = ALIAS_xx20Limitation_min_DD(-t1 - t173);
    real_type t179 = ALIAS_xx20Limitation_max_DD(t173 - t1);
    result__[ 19  ] = OMEGA__[116] * t175 + OMEGA__[117] * t179;
    real_type t182 = X__[iX_yy1];
    real_type t184 = ALIAS_yy1Limitation_min_DD(-t1 - t182);
    real_type t188 = ALIAS_yy1Limitation_max_DD(t182 - t1);
    result__[ 20  ] = OMEGA__[42] * t184 + OMEGA__[43] * t188;
    real_type t191 = X__[iX_yy2];
    real_type t193 = ALIAS_yy2Limitation_min_DD(-t1 - t191);
    real_type t197 = ALIAS_yy2Limitation_max_DD(t191 - t1);
    result__[ 21  ] = OMEGA__[46] * t193 + OMEGA__[47] * t197;
    real_type t200 = X__[iX_yy3];
    real_type t202 = ALIAS_yy3Limitation_min_DD(-t1 - t200);
    real_type t206 = ALIAS_yy3Limitation_max_DD(t200 - t1);
    result__[ 22  ] = OMEGA__[50] * t202 + OMEGA__[51] * t206;
    real_type t209 = X__[iX_yy4];
    real_type t211 = ALIAS_yy4Limitation_min_DD(-t1 - t209);
    real_type t215 = ALIAS_yy4Limitation_max_DD(t209 - t1);
    result__[ 23  ] = OMEGA__[54] * t211 + OMEGA__[55] * t215;
    real_type t218 = X__[iX_yy5];
    real_type t220 = ALIAS_yy5Limitation_min_DD(-t1 - t218);
    real_type t224 = ALIAS_yy5Limitation_max_DD(t218 - t1);
    result__[ 24  ] = OMEGA__[58] * t220 + OMEGA__[59] * t224;
    real_type t227 = X__[iX_yy6];
    real_type t229 = ALIAS_yy6Limitation_min_DD(-t1 - t227);
    real_type t233 = ALIAS_yy6Limitation_max_DD(t227 - t1);
    result__[ 25  ] = OMEGA__[62] * t229 + OMEGA__[63] * t233;
    real_type t236 = X__[iX_yy7];
    real_type t238 = ALIAS_yy7Limitation_min_DD(-t1 - t236);
    real_type t242 = ALIAS_yy7Limitation_max_DD(t236 - t1);
    result__[ 26  ] = OMEGA__[66] * t238 + OMEGA__[67] * t242;
    real_type t245 = X__[iX_yy8];
    real_type t247 = ALIAS_yy8Limitation_min_DD(-t1 - t245);
    real_type t251 = ALIAS_yy8Limitation_max_DD(t245 - t1);
    result__[ 27  ] = OMEGA__[70] * t247 + OMEGA__[71] * t251;
    real_type t254 = X__[iX_yy9];
    real_type t256 = ALIAS_yy9Limitation_min_DD(-t1 - t254);
    real_type t260 = ALIAS_yy9Limitation_max_DD(t254 - t1);
    result__[ 28  ] = OMEGA__[74] * t256 + OMEGA__[75] * t260;
    real_type t263 = X__[iX_yy10];
    real_type t265 = ALIAS_yy10Limitation_min_DD(-t1 - t263);
    real_type t269 = ALIAS_yy10Limitation_max_DD(t263 - t1);
    result__[ 29  ] = OMEGA__[78] * t265 + OMEGA__[79] * t269;
    real_type t272 = X__[iX_yy11];
    real_type t274 = ALIAS_yy11Limitation_min_DD(-t1 - t272);
    real_type t278 = ALIAS_yy11Limitation_max_DD(t272 - t1);
    result__[ 30  ] = OMEGA__[82] * t274 + OMEGA__[83] * t278;
    real_type t281 = X__[iX_yy12];
    real_type t283 = ALIAS_yy12Limitation_min_DD(-t1 - t281);
    real_type t287 = ALIAS_yy12Limitation_max_DD(t281 - t1);
    result__[ 31  ] = OMEGA__[86] * t283 + OMEGA__[87] * t287;
    real_type t290 = X__[iX_yy13];
    real_type t292 = ALIAS_yy13Limitation_min_DD(-t1 - t290);
    real_type t296 = ALIAS_yy13Limitation_max_DD(t290 - t1);
    result__[ 32  ] = OMEGA__[90] * t292 + OMEGA__[91] * t296;
    real_type t299 = X__[iX_yy14];
    real_type t301 = ALIAS_yy14Limitation_max_DD(t299 - t1);
    real_type t305 = ALIAS_yy14Limitation_min_DD(-t1 - t299);
    result__[ 33  ] = OMEGA__[95] * t301 + OMEGA__[94] * t305;
    real_type t308 = X__[iX_yy15];
    real_type t310 = ALIAS_yy15Limitation_min_DD(-t1 - t308);
    real_type t314 = ALIAS_yy15Limitation_max_DD(t308 - t1);
    result__[ 34  ] = OMEGA__[98] * t310 + OMEGA__[99] * t314;
    real_type t317 = X__[iX_yy16];
    real_type t319 = ALIAS_yy16Limitation_max_DD(t317 - t1);
    real_type t323 = ALIAS_yy16Limitation_min_DD(-t1 - t317);
    result__[ 35  ] = OMEGA__[103] * t319 + OMEGA__[102] * t323;
    real_type t326 = X__[iX_yy17];
    real_type t328 = ALIAS_yy17Limitation_min_DD(-t1 - t326);
    real_type t332 = ALIAS_yy17Limitation_max_DD(t326 - t1);
    result__[ 36  ] = OMEGA__[106] * t328 + OMEGA__[107] * t332;
    real_type t335 = X__[iX_yy18];
    real_type t337 = ALIAS_yy18Limitation_min_DD(-t1 - t335);
    real_type t341 = ALIAS_yy18Limitation_max_DD(t335 - t1);
    result__[ 37  ] = OMEGA__[110] * t337 + OMEGA__[111] * t341;
    real_type t344 = X__[iX_yy19];
    real_type t346 = ALIAS_yy19Limitation_min_DD(-t1 - t344);
    real_type t350 = ALIAS_yy19Limitation_max_DD(t344 - t1);
    result__[ 38  ] = OMEGA__[114] * t346 + OMEGA__[115] * t350;
    real_type t353 = X__[iX_yy20];
    real_type t355 = ALIAS_yy20Limitation_min_DD(-t1 - t353);
    real_type t359 = ALIAS_yy20Limitation_max_DD(t353 - t1);
    result__[ 39  ] = OMEGA__[118] * t355 + OMEGA__[119] * t359;
    real_type t362 = P__[iP_u1];
    real_type t364 = ALIAS_u1Limitation_min_DD(-10 - t362);
    real_type t368 = ALIAS_u1Limitation_max_DD(t362 - 10);
    result__[ 40  ] = OMEGA__[0] * t364 + OMEGA__[1] * t368;
    real_type t371 = P__[iP_u2];
    real_type t373 = ALIAS_u2Limitation_min_DD(-10 - t371);
    real_type t377 = ALIAS_u2Limitation_max_DD(t371 - 10);
    result__[ 41  ] = OMEGA__[2] * t373 + OMEGA__[3] * t377;
    real_type t380 = P__[iP_u3];
    real_type t382 = ALIAS_u3Limitation_min_DD(-10 - t380);
    real_type t386 = ALIAS_u3Limitation_max_DD(t380 - 10);
    result__[ 42  ] = OMEGA__[4] * t382 + OMEGA__[5] * t386;
    real_type t389 = P__[iP_u4];
    real_type t391 = ALIAS_u4Limitation_min_DD(-10 - t389);
    real_type t395 = ALIAS_u4Limitation_max_DD(t389 - 10);
    result__[ 43  ] = OMEGA__[6] * t391 + OMEGA__[7] * t395;
    real_type t398 = P__[iP_u5];
    real_type t400 = ALIAS_u5Limitation_min_DD(-10 - t398);
    real_type t404 = ALIAS_u5Limitation_max_DD(t398 - 10);
    result__[ 44  ] = OMEGA__[8] * t400 + OMEGA__[9] * t404;
    real_type t407 = P__[iP_u6];
    real_type t409 = ALIAS_u6Limitation_min_DD(-10 - t407);
    real_type t413 = ALIAS_u6Limitation_max_DD(t407 - 10);
    result__[ 45  ] = OMEGA__[10] * t409 + OMEGA__[11] * t413;
    real_type t416 = P__[iP_u7];
    real_type t418 = ALIAS_u7Limitation_min_DD(-10 - t416);
    real_type t422 = ALIAS_u7Limitation_max_DD(t416 - 10);
    result__[ 46  ] = OMEGA__[12] * t418 + OMEGA__[13] * t422;
    real_type t425 = P__[iP_u8];
    real_type t427 = ALIAS_u8Limitation_min_DD(-10 - t425);
    real_type t431 = ALIAS_u8Limitation_max_DD(t425 - 10);
    result__[ 47  ] = OMEGA__[14] * t427 + OMEGA__[15] * t431;
    real_type t434 = P__[iP_u9];
    real_type t436 = ALIAS_u9Limitation_min_DD(-10 - t434);
    real_type t440 = ALIAS_u9Limitation_max_DD(t434 - 10);
    result__[ 48  ] = OMEGA__[16] * t436 + OMEGA__[17] * t440;
    real_type t443 = P__[iP_u10];
    real_type t445 = ALIAS_u10Limitation_min_DD(-10 - t443);
    real_type t449 = ALIAS_u10Limitation_max_DD(t443 - 10);
    result__[ 49  ] = OMEGA__[18] * t445 + OMEGA__[19] * t449;
    real_type t452 = P__[iP_u11];
    real_type t454 = ALIAS_u11Limitation_min_DD(-10 - t452);
    real_type t458 = ALIAS_u11Limitation_max_DD(t452 - 10);
    result__[ 50  ] = OMEGA__[20] * t454 + OMEGA__[21] * t458;
    real_type t461 = P__[iP_u12];
    real_type t463 = ALIAS_u12Limitation_min_DD(-10 - t461);
    real_type t467 = ALIAS_u12Limitation_max_DD(t461 - 10);
    result__[ 51  ] = OMEGA__[22] * t463 + OMEGA__[23] * t467;
    real_type t470 = P__[iP_u13];
    real_type t472 = ALIAS_u13Limitation_min_DD(-10 - t470);
    real_type t476 = ALIAS_u13Limitation_max_DD(t470 - 10);
    result__[ 52  ] = OMEGA__[24] * t472 + OMEGA__[25] * t476;
    real_type t479 = P__[iP_u14];
    real_type t481 = ALIAS_u14Limitation_min_DD(-10 - t479);
    real_type t485 = ALIAS_u14Limitation_max_DD(t479 - 10);
    result__[ 53  ] = OMEGA__[26] * t481 + OMEGA__[27] * t485;
    real_type t488 = P__[iP_u15];
    real_type t490 = ALIAS_u15Limitation_min_DD(-10 - t488);
    real_type t494 = ALIAS_u15Limitation_max_DD(t488 - 10);
    result__[ 54  ] = OMEGA__[28] * t490 + OMEGA__[29] * t494;
    real_type t497 = P__[iP_u16];
    real_type t499 = ALIAS_u16Limitation_min_DD(-10 - t497);
    real_type t503 = ALIAS_u16Limitation_max_DD(t497 - 10);
    result__[ 55  ] = OMEGA__[30] * t499 + OMEGA__[31] * t503;
    real_type t506 = P__[iP_u17];
    real_type t508 = ALIAS_u17Limitation_min_DD(-10 - t506);
    real_type t512 = ALIAS_u17Limitation_max_DD(t506 - 10);
    result__[ 56  ] = OMEGA__[32] * t508 + OMEGA__[33] * t512;
    real_type t515 = P__[iP_u18];
    real_type t517 = ALIAS_u18Limitation_min_DD(-10 - t515);
    real_type t521 = ALIAS_u18Limitation_max_DD(t515 - 10);
    result__[ 57  ] = OMEGA__[34] * t517 + OMEGA__[35] * t521;
    real_type t524 = P__[iP_u19];
    real_type t526 = ALIAS_u19Limitation_min_DD(-10 - t524);
    real_type t530 = ALIAS_u19Limitation_max_DD(t524 - 10);
    result__[ 58  ] = OMEGA__[36] * t526 + OMEGA__[37] * t530;
    real_type t533 = P__[iP_u20];
    real_type t535 = ALIAS_u20Limitation_min_DD(-10 - t533);
    real_type t539 = ALIAS_u20Limitation_max_DD(t533 - 10);
    result__[ 59  ] = OMEGA__[38] * t535 + OMEGA__[39] * t539;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 60, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2JUD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JUD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JUD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
