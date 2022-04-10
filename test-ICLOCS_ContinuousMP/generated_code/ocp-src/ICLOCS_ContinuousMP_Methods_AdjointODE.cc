/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JPx_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    result__[ 14  ] = 0;
    result__[ 15  ] = 0;
    result__[ 16  ] = 0;
    result__[ 17  ] = 0;
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    result__[ 20  ] = 0;
    result__[ 21  ] = 0;
    result__[ 22  ] = 0;
    result__[ 23  ] = 0;
    result__[ 24  ] = 0;
    result__[ 25  ] = 0;
    result__[ 26  ] = 0;
    result__[ 27  ] = 0;
    result__[ 28  ] = 0;
    result__[ 29  ] = 0;
    result__[ 30  ] = 0;
    result__[ 31  ] = 0;
    result__[ 32  ] = 0;
    result__[ 33  ] = 0;
    result__[ 34  ] = 0;
    result__[ 35  ] = 0;
    result__[ 36  ] = 0;
    result__[ 37  ] = 0;
    result__[ 38  ] = 0;
    result__[ 39  ] = 0;
    result__[ 40  ] = 0;
    result__[ 41  ] = 0;
    result__[ 42  ] = 0;
    result__[ 43  ] = 0;
    result__[ 44  ] = 0;
    result__[ 45  ] = 0;
    result__[ 46  ] = 0;
    result__[ 47  ] = 0;
    result__[ 48  ] = 0;
    result__[ 49  ] = 0;
    result__[ 50  ] = 0;
    result__[ 51  ] = 0;
    result__[ 52  ] = 0;
    result__[ 53  ] = 0;
    result__[ 54  ] = 0;
    result__[ 55  ] = 0;
    result__[ 56  ] = 0;
    result__[ 57  ] = 0;
    result__[ 58  ] = 0;
    result__[ 59  ] = 0;
    result__[ 60  ] = 0;
    result__[ 61  ] = 0;
    result__[ 62  ] = 0;
    result__[ 63  ] = 0;
    result__[ 64  ] = 0;
    result__[ 65  ] = 0;
    result__[ 66  ] = 0;
    result__[ 67  ] = 0;
    result__[ 68  ] = 0;
    result__[ 69  ] = 0;
    result__[ 70  ] = 0;
    result__[ 71  ] = 0;
    result__[ 72  ] = 0;
    result__[ 73  ] = 0;
    result__[ 74  ] = 0;
    result__[ 75  ] = 0;
    result__[ 76  ] = 0;
    result__[ 77  ] = 0;
    result__[ 78  ] = 0;
    result__[ 79  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTx_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    result__[ 14  ] = 0;
    result__[ 15  ] = 0;
    result__[ 16  ] = 0;
    result__[ 17  ] = 0;
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    result__[ 20  ] = 0;
    result__[ 21  ] = 0;
    result__[ 22  ] = 0;
    result__[ 23  ] = 0;
    result__[ 24  ] = 0;
    result__[ 25  ] = 0;
    result__[ 26  ] = 0;
    result__[ 27  ] = 0;
    result__[ 28  ] = 0;
    result__[ 29  ] = 0;
    result__[ 30  ] = 0;
    result__[ 31  ] = 0;
    result__[ 32  ] = 0;
    result__[ 33  ] = 0;
    result__[ 34  ] = 0;
    result__[ 35  ] = 0;
    result__[ 36  ] = 0;
    result__[ 37  ] = 0;
    result__[ 38  ] = 0;
    result__[ 39  ] = 0;
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_xx1];
    real_type t4   = ALIAS_xx1Limitation_min_D(-t1 - t2);
    real_type t6   = ALIAS_xx1Limitation_max_D(t2 - t1);
    result__[ 40  ] = -t4 + t6;
    real_type t7   = X__[iX_xx2];
    real_type t9   = ALIAS_xx2Limitation_min_D(-t1 - t7);
    real_type t11  = ALIAS_xx2Limitation_max_D(t7 - t1);
    result__[ 41  ] = -t9 + t11;
    real_type t12  = X__[iX_xx3];
    real_type t14  = ALIAS_xx3Limitation_min_D(-t1 - t12);
    real_type t16  = ALIAS_xx3Limitation_max_D(t12 - t1);
    result__[ 42  ] = -t14 + t16;
    real_type t17  = X__[iX_xx4];
    real_type t19  = ALIAS_xx4Limitation_min_D(-t1 - t17);
    real_type t21  = ALIAS_xx4Limitation_max_D(t17 - t1);
    result__[ 43  ] = -t19 + t21;
    real_type t22  = X__[iX_xx5];
    real_type t24  = ALIAS_xx5Limitation_min_D(-t1 - t22);
    real_type t26  = ALIAS_xx5Limitation_max_D(t22 - t1);
    result__[ 44  ] = -t24 + t26;
    real_type t27  = X__[iX_xx6];
    real_type t29  = ALIAS_xx6Limitation_min_D(-t1 - t27);
    real_type t31  = ALIAS_xx6Limitation_max_D(t27 - t1);
    result__[ 45  ] = -t29 + t31;
    real_type t32  = X__[iX_xx7];
    real_type t34  = ALIAS_xx7Limitation_min_D(-t1 - t32);
    real_type t36  = ALIAS_xx7Limitation_max_D(t32 - t1);
    result__[ 46  ] = -t34 + t36;
    real_type t37  = X__[iX_xx8];
    real_type t39  = ALIAS_xx8Limitation_min_D(-t1 - t37);
    real_type t41  = ALIAS_xx8Limitation_max_D(t37 - t1);
    result__[ 47  ] = -t39 + t41;
    real_type t42  = X__[iX_xx9];
    real_type t44  = ALIAS_xx9Limitation_max_D(t42 - t1);
    real_type t46  = ALIAS_xx9Limitation_min_D(-t1 - t42);
    result__[ 48  ] = t44 - t46;
    real_type t47  = X__[iX_xx10];
    real_type t49  = ALIAS_xx10Limitation_min_D(-t1 - t47);
    real_type t51  = ALIAS_xx10Limitation_max_D(t47 - t1);
    result__[ 49  ] = -t49 + t51;
    real_type t52  = X__[iX_xx11];
    real_type t54  = ALIAS_xx11Limitation_min_D(-t1 - t52);
    real_type t56  = ALIAS_xx11Limitation_max_D(t52 - t1);
    result__[ 50  ] = -t54 + t56;
    real_type t57  = X__[iX_xx12];
    real_type t59  = ALIAS_xx12Limitation_min_D(-t1 - t57);
    real_type t61  = ALIAS_xx12Limitation_max_D(t57 - t1);
    result__[ 51  ] = -t59 + t61;
    real_type t62  = X__[iX_xx13];
    real_type t64  = ALIAS_xx13Limitation_min_D(-t1 - t62);
    real_type t66  = ALIAS_xx13Limitation_max_D(t62 - t1);
    result__[ 52  ] = -t64 + t66;
    real_type t67  = X__[iX_xx14];
    real_type t69  = ALIAS_xx14Limitation_min_D(-t1 - t67);
    real_type t71  = ALIAS_xx14Limitation_max_D(t67 - t1);
    result__[ 53  ] = -t69 + t71;
    real_type t72  = X__[iX_xx15];
    real_type t74  = ALIAS_xx15Limitation_min_D(-t1 - t72);
    real_type t76  = ALIAS_xx15Limitation_max_D(t72 - t1);
    result__[ 54  ] = -t74 + t76;
    real_type t77  = X__[iX_xx16];
    real_type t79  = ALIAS_xx16Limitation_min_D(-t1 - t77);
    real_type t81  = ALIAS_xx16Limitation_max_D(t77 - t1);
    result__[ 55  ] = -t79 + t81;
    real_type t82  = X__[iX_xx17];
    real_type t84  = ALIAS_xx17Limitation_min_D(-t1 - t82);
    real_type t86  = ALIAS_xx17Limitation_max_D(t82 - t1);
    result__[ 56  ] = -t84 + t86;
    real_type t87  = X__[iX_xx18];
    real_type t89  = ALIAS_xx18Limitation_min_D(-t1 - t87);
    real_type t91  = ALIAS_xx18Limitation_max_D(t87 - t1);
    result__[ 57  ] = -t89 + t91;
    real_type t92  = X__[iX_xx19];
    real_type t94  = ALIAS_xx19Limitation_min_D(-t1 - t92);
    real_type t96  = ALIAS_xx19Limitation_max_D(t92 - t1);
    result__[ 58  ] = -t94 + t96;
    real_type t97  = X__[iX_xx20];
    real_type t99  = ALIAS_xx20Limitation_min_D(-t1 - t97);
    real_type t101 = ALIAS_xx20Limitation_max_D(t97 - t1);
    result__[ 59  ] = -t99 + t101;
    real_type t102 = X__[iX_yy1];
    real_type t104 = ALIAS_yy1Limitation_min_D(-t1 - t102);
    real_type t106 = ALIAS_yy1Limitation_max_D(t102 - t1);
    result__[ 60  ] = -t104 + t106;
    real_type t107 = X__[iX_yy2];
    real_type t109 = ALIAS_yy2Limitation_min_D(-t1 - t107);
    real_type t111 = ALIAS_yy2Limitation_max_D(t107 - t1);
    result__[ 61  ] = -t109 + t111;
    real_type t112 = X__[iX_yy3];
    real_type t114 = ALIAS_yy3Limitation_min_D(-t1 - t112);
    real_type t116 = ALIAS_yy3Limitation_max_D(t112 - t1);
    result__[ 62  ] = -t114 + t116;
    real_type t117 = X__[iX_yy4];
    real_type t119 = ALIAS_yy4Limitation_min_D(-t1 - t117);
    real_type t121 = ALIAS_yy4Limitation_max_D(t117 - t1);
    result__[ 63  ] = -t119 + t121;
    real_type t122 = X__[iX_yy5];
    real_type t124 = ALIAS_yy5Limitation_min_D(-t1 - t122);
    real_type t126 = ALIAS_yy5Limitation_max_D(t122 - t1);
    result__[ 64  ] = -t124 + t126;
    real_type t127 = X__[iX_yy6];
    real_type t129 = ALIAS_yy6Limitation_min_D(-t1 - t127);
    real_type t131 = ALIAS_yy6Limitation_max_D(t127 - t1);
    result__[ 65  ] = -t129 + t131;
    real_type t132 = X__[iX_yy7];
    real_type t134 = ALIAS_yy7Limitation_min_D(-t1 - t132);
    real_type t136 = ALIAS_yy7Limitation_max_D(t132 - t1);
    result__[ 66  ] = -t134 + t136;
    real_type t137 = X__[iX_yy8];
    real_type t139 = ALIAS_yy8Limitation_min_D(-t1 - t137);
    real_type t141 = ALIAS_yy8Limitation_max_D(t137 - t1);
    result__[ 67  ] = -t139 + t141;
    real_type t142 = X__[iX_yy9];
    real_type t144 = ALIAS_yy9Limitation_min_D(-t1 - t142);
    real_type t146 = ALIAS_yy9Limitation_max_D(t142 - t1);
    result__[ 68  ] = -t144 + t146;
    real_type t147 = X__[iX_yy10];
    real_type t149 = ALIAS_yy10Limitation_min_D(-t1 - t147);
    real_type t151 = ALIAS_yy10Limitation_max_D(t147 - t1);
    result__[ 69  ] = -t149 + t151;
    real_type t152 = X__[iX_yy11];
    real_type t154 = ALIAS_yy11Limitation_min_D(-t1 - t152);
    real_type t156 = ALIAS_yy11Limitation_max_D(t152 - t1);
    result__[ 70  ] = -t154 + t156;
    real_type t157 = X__[iX_yy12];
    real_type t159 = ALIAS_yy12Limitation_min_D(-t1 - t157);
    real_type t161 = ALIAS_yy12Limitation_max_D(t157 - t1);
    result__[ 71  ] = -t159 + t161;
    real_type t162 = X__[iX_yy13];
    real_type t164 = ALIAS_yy13Limitation_min_D(-t1 - t162);
    real_type t166 = ALIAS_yy13Limitation_max_D(t162 - t1);
    result__[ 72  ] = -t164 + t166;
    real_type t167 = X__[iX_yy14];
    real_type t169 = ALIAS_yy14Limitation_min_D(-t1 - t167);
    real_type t171 = ALIAS_yy14Limitation_max_D(t167 - t1);
    result__[ 73  ] = -t169 + t171;
    real_type t172 = X__[iX_yy15];
    real_type t174 = ALIAS_yy15Limitation_min_D(-t1 - t172);
    real_type t176 = ALIAS_yy15Limitation_max_D(t172 - t1);
    result__[ 74  ] = -t174 + t176;
    real_type t177 = X__[iX_yy16];
    real_type t179 = ALIAS_yy16Limitation_min_D(-t1 - t177);
    real_type t181 = ALIAS_yy16Limitation_max_D(t177 - t1);
    result__[ 75  ] = -t179 + t181;
    real_type t182 = X__[iX_yy17];
    real_type t184 = ALIAS_yy17Limitation_min_D(-t1 - t182);
    real_type t186 = ALIAS_yy17Limitation_max_D(t182 - t1);
    result__[ 76  ] = -t184 + t186;
    real_type t187 = X__[iX_yy18];
    real_type t189 = ALIAS_yy18Limitation_max_D(t187 - t1);
    real_type t191 = ALIAS_yy18Limitation_min_D(-t1 - t187);
    result__[ 77  ] = t189 - t191;
    real_type t192 = X__[iX_yy19];
    real_type t194 = ALIAS_yy19Limitation_min_D(-t1 - t192);
    real_type t196 = ALIAS_yy19Limitation_max_D(t192 - t1);
    result__[ 78  ] = -t194 + t196;
    real_type t197 = X__[iX_yy20];
    real_type t199 = ALIAS_yy20Limitation_min_D(-t1 - t197);
    real_type t201 = ALIAS_yy20Limitation_max_D(t197 - t1);
    result__[ 79  ] = -t199 + t201;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JUx_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    result__[ 14  ] = 0;
    result__[ 15  ] = 0;
    result__[ 16  ] = 0;
    result__[ 17  ] = 0;
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    result__[ 20  ] = 0;
    result__[ 21  ] = 0;
    result__[ 22  ] = 0;
    result__[ 23  ] = 0;
    result__[ 24  ] = 0;
    result__[ 25  ] = 0;
    result__[ 26  ] = 0;
    result__[ 27  ] = 0;
    result__[ 28  ] = 0;
    result__[ 29  ] = 0;
    result__[ 30  ] = 0;
    result__[ 31  ] = 0;
    result__[ 32  ] = 0;
    result__[ 33  ] = 0;
    result__[ 34  ] = 0;
    result__[ 35  ] = 0;
    result__[ 36  ] = 0;
    result__[ 37  ] = 0;
    result__[ 38  ] = 0;
    result__[ 39  ] = 0;
    result__[ 40  ] = 0;
    result__[ 41  ] = 0;
    result__[ 42  ] = 0;
    result__[ 43  ] = 0;
    result__[ 44  ] = 0;
    result__[ 45  ] = 0;
    result__[ 46  ] = 0;
    result__[ 47  ] = 0;
    result__[ 48  ] = 0;
    result__[ 49  ] = 0;
    result__[ 50  ] = 0;
    result__[ 51  ] = 0;
    result__[ 52  ] = 0;
    result__[ 53  ] = 0;
    result__[ 54  ] = 0;
    result__[ 55  ] = 0;
    result__[ 56  ] = 0;
    result__[ 57  ] = 0;
    result__[ 58  ] = 0;
    result__[ 59  ] = 0;
    result__[ 60  ] = 0;
    result__[ 61  ] = 0;
    result__[ 62  ] = 0;
    result__[ 63  ] = 0;
    result__[ 64  ] = 0;
    result__[ 65  ] = 0;
    result__[ 66  ] = 0;
    result__[ 67  ] = 0;
    result__[ 68  ] = 0;
    result__[ 69  ] = 0;
    result__[ 70  ] = 0;
    result__[ 71  ] = 0;
    result__[ 72  ] = 0;
    result__[ 73  ] = 0;
    result__[ 74  ] = 0;
    result__[ 75  ] = 0;
    result__[ 76  ] = 0;
    result__[ 77  ] = 0;
    result__[ 78  ] = 0;
    result__[ 79  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JPp_numEqns() const { return 20; }

  void
  ICLOCS_ContinuousMP::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    result__[ 14  ] = 0;
    result__[ 15  ] = 0;
    result__[ 16  ] = 0;
    result__[ 17  ] = 0;
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPp_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTp_numEqns() const { return 20; }

  void
  ICLOCS_ContinuousMP::LTp_eval(
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
    real_type t5   = ALIAS_u1Limitation_max_D(t1 - 10);
    result__[ 0   ] = -t3 + t5;
    real_type t6   = P__[iP_u2];
    real_type t8   = ALIAS_u2Limitation_min_D(-10 - t6);
    real_type t10  = ALIAS_u2Limitation_max_D(t6 - 10);
    result__[ 1   ] = -t8 + t10;
    real_type t11  = P__[iP_u3];
    real_type t13  = ALIAS_u3Limitation_min_D(-10 - t11);
    real_type t15  = ALIAS_u3Limitation_max_D(t11 - 10);
    result__[ 2   ] = -t13 + t15;
    real_type t16  = P__[iP_u4];
    real_type t18  = ALIAS_u4Limitation_min_D(-10 - t16);
    real_type t20  = ALIAS_u4Limitation_max_D(t16 - 10);
    result__[ 3   ] = -t18 + t20;
    real_type t21  = P__[iP_u5];
    real_type t23  = ALIAS_u5Limitation_min_D(-10 - t21);
    real_type t25  = ALIAS_u5Limitation_max_D(t21 - 10);
    result__[ 4   ] = -t23 + t25;
    real_type t26  = P__[iP_u6];
    real_type t28  = ALIAS_u6Limitation_min_D(-10 - t26);
    real_type t30  = ALIAS_u6Limitation_max_D(t26 - 10);
    result__[ 5   ] = -t28 + t30;
    real_type t31  = P__[iP_u7];
    real_type t33  = ALIAS_u7Limitation_min_D(-10 - t31);
    real_type t35  = ALIAS_u7Limitation_max_D(t31 - 10);
    result__[ 6   ] = -t33 + t35;
    real_type t36  = P__[iP_u8];
    real_type t38  = ALIAS_u8Limitation_min_D(-10 - t36);
    real_type t40  = ALIAS_u8Limitation_max_D(t36 - 10);
    result__[ 7   ] = -t38 + t40;
    real_type t41  = P__[iP_u9];
    real_type t43  = ALIAS_u9Limitation_min_D(-10 - t41);
    real_type t45  = ALIAS_u9Limitation_max_D(t41 - 10);
    result__[ 8   ] = -t43 + t45;
    real_type t46  = P__[iP_u10];
    real_type t48  = ALIAS_u10Limitation_min_D(-10 - t46);
    real_type t50  = ALIAS_u10Limitation_max_D(t46 - 10);
    result__[ 9   ] = -t48 + t50;
    real_type t51  = P__[iP_u11];
    real_type t53  = ALIAS_u11Limitation_min_D(-10 - t51);
    real_type t55  = ALIAS_u11Limitation_max_D(t51 - 10);
    result__[ 10  ] = -t53 + t55;
    real_type t56  = P__[iP_u12];
    real_type t58  = ALIAS_u12Limitation_min_D(-10 - t56);
    real_type t60  = ALIAS_u12Limitation_max_D(t56 - 10);
    result__[ 11  ] = -t58 + t60;
    real_type t61  = P__[iP_u13];
    real_type t63  = ALIAS_u13Limitation_min_D(-10 - t61);
    real_type t65  = ALIAS_u13Limitation_max_D(t61 - 10);
    result__[ 12  ] = -t63 + t65;
    real_type t66  = P__[iP_u14];
    real_type t68  = ALIAS_u14Limitation_min_D(-10 - t66);
    real_type t70  = ALIAS_u14Limitation_max_D(t66 - 10);
    result__[ 13  ] = -t68 + t70;
    real_type t71  = P__[iP_u15];
    real_type t73  = ALIAS_u15Limitation_min_D(-10 - t71);
    real_type t75  = ALIAS_u15Limitation_max_D(t71 - 10);
    result__[ 14  ] = -t73 + t75;
    real_type t76  = P__[iP_u16];
    real_type t78  = ALIAS_u16Limitation_min_D(-10 - t76);
    real_type t80  = ALIAS_u16Limitation_max_D(t76 - 10);
    result__[ 15  ] = -t78 + t80;
    real_type t81  = P__[iP_u17];
    real_type t83  = ALIAS_u17Limitation_min_D(-10 - t81);
    real_type t85  = ALIAS_u17Limitation_max_D(t81 - 10);
    result__[ 16  ] = -t83 + t85;
    real_type t86  = P__[iP_u18];
    real_type t88  = ALIAS_u18Limitation_min_D(-10 - t86);
    real_type t90  = ALIAS_u18Limitation_max_D(t86 - 10);
    result__[ 17  ] = -t88 + t90;
    real_type t91  = P__[iP_u19];
    real_type t93  = ALIAS_u19Limitation_min_D(-10 - t91);
    real_type t95  = ALIAS_u19Limitation_max_D(t91 - 10);
    result__[ 18  ] = -t93 + t95;
    real_type t96  = P__[iP_u20];
    real_type t98  = ALIAS_u20Limitation_min_D(-10 - t96);
    real_type t100 = ALIAS_u20Limitation_max_D(t96 - 10);
    result__[ 19  ] = -t98 + t100;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JUp_numEqns() const { return 20; }

  void
  ICLOCS_ContinuousMP::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    result__[ 14  ] = 0;
    result__[ 15  ] = 0;
    result__[ 16  ] = 0;
    result__[ 17  ] = 0;
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JPu_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTu_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JUu_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::JUu_eval(
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
  integer ICLOCS_ContinuousMP::DJPxDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DJPxDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJPxDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTxDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DLTxDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DLTxDxp_nnz()     const { return 40; }

  void
  ICLOCS_ContinuousMP::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  ICLOCS_ContinuousMP::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_xx1];
    real_type t4   = ALIAS_xx1Limitation_min_DD(-t1 - t2);
    real_type t6   = ALIAS_xx1Limitation_max_DD(t2 - t1);
    result__[ 0   ] = t4 + t6;
    real_type t7   = X__[iX_xx2];
    real_type t9   = ALIAS_xx2Limitation_min_DD(-t1 - t7);
    real_type t11  = ALIAS_xx2Limitation_max_DD(t7 - t1);
    result__[ 1   ] = t9 + t11;
    real_type t12  = X__[iX_xx3];
    real_type t14  = ALIAS_xx3Limitation_min_DD(-t1 - t12);
    real_type t16  = ALIAS_xx3Limitation_max_DD(t12 - t1);
    result__[ 2   ] = t14 + t16;
    real_type t17  = X__[iX_xx4];
    real_type t19  = ALIAS_xx4Limitation_min_DD(-t1 - t17);
    real_type t21  = ALIAS_xx4Limitation_max_DD(t17 - t1);
    result__[ 3   ] = t19 + t21;
    real_type t22  = X__[iX_xx5];
    real_type t24  = ALIAS_xx5Limitation_min_DD(-t1 - t22);
    real_type t26  = ALIAS_xx5Limitation_max_DD(t22 - t1);
    result__[ 4   ] = t24 + t26;
    real_type t27  = X__[iX_xx6];
    real_type t29  = ALIAS_xx6Limitation_min_DD(-t1 - t27);
    real_type t31  = ALIAS_xx6Limitation_max_DD(t27 - t1);
    result__[ 5   ] = t29 + t31;
    real_type t32  = X__[iX_xx7];
    real_type t34  = ALIAS_xx7Limitation_min_DD(-t1 - t32);
    real_type t36  = ALIAS_xx7Limitation_max_DD(t32 - t1);
    result__[ 6   ] = t34 + t36;
    real_type t37  = X__[iX_xx8];
    real_type t39  = ALIAS_xx8Limitation_min_DD(-t1 - t37);
    real_type t41  = ALIAS_xx8Limitation_max_DD(t37 - t1);
    result__[ 7   ] = t39 + t41;
    real_type t42  = X__[iX_xx9];
    real_type t44  = ALIAS_xx9Limitation_max_DD(t42 - t1);
    real_type t46  = ALIAS_xx9Limitation_min_DD(-t1 - t42);
    result__[ 8   ] = t44 + t46;
    real_type t47  = X__[iX_xx10];
    real_type t49  = ALIAS_xx10Limitation_min_DD(-t1 - t47);
    real_type t51  = ALIAS_xx10Limitation_max_DD(t47 - t1);
    result__[ 9   ] = t49 + t51;
    real_type t52  = X__[iX_xx11];
    real_type t54  = ALIAS_xx11Limitation_min_DD(-t1 - t52);
    real_type t56  = ALIAS_xx11Limitation_max_DD(t52 - t1);
    result__[ 10  ] = t54 + t56;
    real_type t57  = X__[iX_xx12];
    real_type t59  = ALIAS_xx12Limitation_min_DD(-t1 - t57);
    real_type t61  = ALIAS_xx12Limitation_max_DD(t57 - t1);
    result__[ 11  ] = t59 + t61;
    real_type t62  = X__[iX_xx13];
    real_type t64  = ALIAS_xx13Limitation_min_DD(-t1 - t62);
    real_type t66  = ALIAS_xx13Limitation_max_DD(t62 - t1);
    result__[ 12  ] = t64 + t66;
    real_type t67  = X__[iX_xx14];
    real_type t69  = ALIAS_xx14Limitation_min_DD(-t1 - t67);
    real_type t71  = ALIAS_xx14Limitation_max_DD(t67 - t1);
    result__[ 13  ] = t69 + t71;
    real_type t72  = X__[iX_xx15];
    real_type t74  = ALIAS_xx15Limitation_min_DD(-t1 - t72);
    real_type t76  = ALIAS_xx15Limitation_max_DD(t72 - t1);
    result__[ 14  ] = t74 + t76;
    real_type t77  = X__[iX_xx16];
    real_type t79  = ALIAS_xx16Limitation_min_DD(-t1 - t77);
    real_type t81  = ALIAS_xx16Limitation_max_DD(t77 - t1);
    result__[ 15  ] = t79 + t81;
    real_type t82  = X__[iX_xx17];
    real_type t84  = ALIAS_xx17Limitation_min_DD(-t1 - t82);
    real_type t86  = ALIAS_xx17Limitation_max_DD(t82 - t1);
    result__[ 16  ] = t84 + t86;
    real_type t87  = X__[iX_xx18];
    real_type t89  = ALIAS_xx18Limitation_min_DD(-t1 - t87);
    real_type t91  = ALIAS_xx18Limitation_max_DD(t87 - t1);
    result__[ 17  ] = t89 + t91;
    real_type t92  = X__[iX_xx19];
    real_type t94  = ALIAS_xx19Limitation_min_DD(-t1 - t92);
    real_type t96  = ALIAS_xx19Limitation_max_DD(t92 - t1);
    result__[ 18  ] = t94 + t96;
    real_type t97  = X__[iX_xx20];
    real_type t99  = ALIAS_xx20Limitation_min_DD(-t1 - t97);
    real_type t101 = ALIAS_xx20Limitation_max_DD(t97 - t1);
    result__[ 19  ] = t99 + t101;
    real_type t102 = X__[iX_yy1];
    real_type t104 = ALIAS_yy1Limitation_min_DD(-t1 - t102);
    real_type t106 = ALIAS_yy1Limitation_max_DD(t102 - t1);
    result__[ 20  ] = t104 + t106;
    real_type t107 = X__[iX_yy2];
    real_type t109 = ALIAS_yy2Limitation_min_DD(-t1 - t107);
    real_type t111 = ALIAS_yy2Limitation_max_DD(t107 - t1);
    result__[ 21  ] = t109 + t111;
    real_type t112 = X__[iX_yy3];
    real_type t114 = ALIAS_yy3Limitation_min_DD(-t1 - t112);
    real_type t116 = ALIAS_yy3Limitation_max_DD(t112 - t1);
    result__[ 22  ] = t114 + t116;
    real_type t117 = X__[iX_yy4];
    real_type t119 = ALIAS_yy4Limitation_min_DD(-t1 - t117);
    real_type t121 = ALIAS_yy4Limitation_max_DD(t117 - t1);
    result__[ 23  ] = t119 + t121;
    real_type t122 = X__[iX_yy5];
    real_type t124 = ALIAS_yy5Limitation_min_DD(-t1 - t122);
    real_type t126 = ALIAS_yy5Limitation_max_DD(t122 - t1);
    result__[ 24  ] = t124 + t126;
    real_type t127 = X__[iX_yy6];
    real_type t129 = ALIAS_yy6Limitation_min_DD(-t1 - t127);
    real_type t131 = ALIAS_yy6Limitation_max_DD(t127 - t1);
    result__[ 25  ] = t129 + t131;
    real_type t132 = X__[iX_yy7];
    real_type t134 = ALIAS_yy7Limitation_min_DD(-t1 - t132);
    real_type t136 = ALIAS_yy7Limitation_max_DD(t132 - t1);
    result__[ 26  ] = t134 + t136;
    real_type t137 = X__[iX_yy8];
    real_type t139 = ALIAS_yy8Limitation_min_DD(-t1 - t137);
    real_type t141 = ALIAS_yy8Limitation_max_DD(t137 - t1);
    result__[ 27  ] = t139 + t141;
    real_type t142 = X__[iX_yy9];
    real_type t144 = ALIAS_yy9Limitation_min_DD(-t1 - t142);
    real_type t146 = ALIAS_yy9Limitation_max_DD(t142 - t1);
    result__[ 28  ] = t144 + t146;
    real_type t147 = X__[iX_yy10];
    real_type t149 = ALIAS_yy10Limitation_min_DD(-t1 - t147);
    real_type t151 = ALIAS_yy10Limitation_max_DD(t147 - t1);
    result__[ 29  ] = t149 + t151;
    real_type t152 = X__[iX_yy11];
    real_type t154 = ALIAS_yy11Limitation_min_DD(-t1 - t152);
    real_type t156 = ALIAS_yy11Limitation_max_DD(t152 - t1);
    result__[ 30  ] = t154 + t156;
    real_type t157 = X__[iX_yy12];
    real_type t159 = ALIAS_yy12Limitation_min_DD(-t1 - t157);
    real_type t161 = ALIAS_yy12Limitation_max_DD(t157 - t1);
    result__[ 31  ] = t159 + t161;
    real_type t162 = X__[iX_yy13];
    real_type t164 = ALIAS_yy13Limitation_min_DD(-t1 - t162);
    real_type t166 = ALIAS_yy13Limitation_max_DD(t162 - t1);
    result__[ 32  ] = t164 + t166;
    real_type t167 = X__[iX_yy14];
    real_type t169 = ALIAS_yy14Limitation_min_DD(-t1 - t167);
    real_type t171 = ALIAS_yy14Limitation_max_DD(t167 - t1);
    result__[ 33  ] = t169 + t171;
    real_type t172 = X__[iX_yy15];
    real_type t174 = ALIAS_yy15Limitation_min_DD(-t1 - t172);
    real_type t176 = ALIAS_yy15Limitation_max_DD(t172 - t1);
    result__[ 34  ] = t174 + t176;
    real_type t177 = X__[iX_yy16];
    real_type t179 = ALIAS_yy16Limitation_min_DD(-t1 - t177);
    real_type t181 = ALIAS_yy16Limitation_max_DD(t177 - t1);
    result__[ 35  ] = t179 + t181;
    real_type t182 = X__[iX_yy17];
    real_type t184 = ALIAS_yy17Limitation_min_DD(-t1 - t182);
    real_type t186 = ALIAS_yy17Limitation_max_DD(t182 - t1);
    result__[ 36  ] = t184 + t186;
    real_type t187 = X__[iX_yy18];
    real_type t189 = ALIAS_yy18Limitation_max_DD(t187 - t1);
    real_type t191 = ALIAS_yy18Limitation_min_DD(-t1 - t187);
    result__[ 37  ] = t189 + t191;
    real_type t192 = X__[iX_yy19];
    real_type t194 = ALIAS_yy19Limitation_min_DD(-t1 - t192);
    real_type t196 = ALIAS_yy19Limitation_max_DD(t192 - t1);
    result__[ 38  ] = t194 + t196;
    real_type t197 = X__[iX_yy20];
    real_type t199 = ALIAS_yy20Limitation_min_DD(-t1 - t197);
    real_type t201 = ALIAS_yy20Limitation_max_DD(t197 - t1);
    result__[ 39  ] = t199 + t201;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJUxDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DJUxDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJUxDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJPuDxp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DJPuDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJPuDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTuDxp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DLTuDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DLTuDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJUuDxp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DJUuDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DJUuDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJPpDp_numRows() const { return 20; }
  integer ICLOCS_ContinuousMP::DJPpDp_numCols() const { return 20; }
  integer ICLOCS_ContinuousMP::DJPpDp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTpDp_numRows() const { return 20; }
  integer ICLOCS_ContinuousMP::DLTpDp_numCols() const { return 20; }
  integer ICLOCS_ContinuousMP::DLTpDp_nnz()     const { return 20; }

  void
  ICLOCS_ContinuousMP::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  ICLOCS_ContinuousMP::DLTpDp_sparse(
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
    real_type t3   = ALIAS_u1Limitation_min_DD(-10 - t1);
    real_type t5   = ALIAS_u1Limitation_max_DD(t1 - 10);
    result__[ 0   ] = t3 + t5;
    real_type t6   = P__[iP_u2];
    real_type t8   = ALIAS_u2Limitation_min_DD(-10 - t6);
    real_type t10  = ALIAS_u2Limitation_max_DD(t6 - 10);
    result__[ 1   ] = t8 + t10;
    real_type t11  = P__[iP_u3];
    real_type t13  = ALIAS_u3Limitation_min_DD(-10 - t11);
    real_type t15  = ALIAS_u3Limitation_max_DD(t11 - 10);
    result__[ 2   ] = t13 + t15;
    real_type t16  = P__[iP_u4];
    real_type t18  = ALIAS_u4Limitation_min_DD(-10 - t16);
    real_type t20  = ALIAS_u4Limitation_max_DD(t16 - 10);
    result__[ 3   ] = t18 + t20;
    real_type t21  = P__[iP_u5];
    real_type t23  = ALIAS_u5Limitation_min_DD(-10 - t21);
    real_type t25  = ALIAS_u5Limitation_max_DD(t21 - 10);
    result__[ 4   ] = t23 + t25;
    real_type t26  = P__[iP_u6];
    real_type t28  = ALIAS_u6Limitation_min_DD(-10 - t26);
    real_type t30  = ALIAS_u6Limitation_max_DD(t26 - 10);
    result__[ 5   ] = t28 + t30;
    real_type t31  = P__[iP_u7];
    real_type t33  = ALIAS_u7Limitation_min_DD(-10 - t31);
    real_type t35  = ALIAS_u7Limitation_max_DD(t31 - 10);
    result__[ 6   ] = t33 + t35;
    real_type t36  = P__[iP_u8];
    real_type t38  = ALIAS_u8Limitation_min_DD(-10 - t36);
    real_type t40  = ALIAS_u8Limitation_max_DD(t36 - 10);
    result__[ 7   ] = t38 + t40;
    real_type t41  = P__[iP_u9];
    real_type t43  = ALIAS_u9Limitation_min_DD(-10 - t41);
    real_type t45  = ALIAS_u9Limitation_max_DD(t41 - 10);
    result__[ 8   ] = t43 + t45;
    real_type t46  = P__[iP_u10];
    real_type t48  = ALIAS_u10Limitation_min_DD(-10 - t46);
    real_type t50  = ALIAS_u10Limitation_max_DD(t46 - 10);
    result__[ 9   ] = t48 + t50;
    real_type t51  = P__[iP_u11];
    real_type t53  = ALIAS_u11Limitation_min_DD(-10 - t51);
    real_type t55  = ALIAS_u11Limitation_max_DD(t51 - 10);
    result__[ 10  ] = t53 + t55;
    real_type t56  = P__[iP_u12];
    real_type t58  = ALIAS_u12Limitation_min_DD(-10 - t56);
    real_type t60  = ALIAS_u12Limitation_max_DD(t56 - 10);
    result__[ 11  ] = t58 + t60;
    real_type t61  = P__[iP_u13];
    real_type t63  = ALIAS_u13Limitation_min_DD(-10 - t61);
    real_type t65  = ALIAS_u13Limitation_max_DD(t61 - 10);
    result__[ 12  ] = t63 + t65;
    real_type t66  = P__[iP_u14];
    real_type t68  = ALIAS_u14Limitation_min_DD(-10 - t66);
    real_type t70  = ALIAS_u14Limitation_max_DD(t66 - 10);
    result__[ 13  ] = t68 + t70;
    real_type t71  = P__[iP_u15];
    real_type t73  = ALIAS_u15Limitation_min_DD(-10 - t71);
    real_type t75  = ALIAS_u15Limitation_max_DD(t71 - 10);
    result__[ 14  ] = t73 + t75;
    real_type t76  = P__[iP_u16];
    real_type t78  = ALIAS_u16Limitation_min_DD(-10 - t76);
    real_type t80  = ALIAS_u16Limitation_max_DD(t76 - 10);
    result__[ 15  ] = t78 + t80;
    real_type t81  = P__[iP_u17];
    real_type t83  = ALIAS_u17Limitation_min_DD(-10 - t81);
    real_type t85  = ALIAS_u17Limitation_max_DD(t81 - 10);
    result__[ 16  ] = t83 + t85;
    real_type t86  = P__[iP_u18];
    real_type t88  = ALIAS_u18Limitation_min_DD(-10 - t86);
    real_type t90  = ALIAS_u18Limitation_max_DD(t86 - 10);
    result__[ 17  ] = t88 + t90;
    real_type t91  = P__[iP_u19];
    real_type t93  = ALIAS_u19Limitation_min_DD(-10 - t91);
    real_type t95  = ALIAS_u19Limitation_max_DD(t91 - 10);
    result__[ 18  ] = t93 + t95;
    real_type t96  = P__[iP_u20];
    real_type t98  = ALIAS_u20Limitation_min_DD(-10 - t96);
    real_type t100 = ALIAS_u20Limitation_max_DD(t96 - 10);
    result__[ 19  ] = t98 + t100;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTpDp_sparse", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DJUpDp_numRows() const { return 20; }
  integer ICLOCS_ContinuousMP::DJUpDp_numCols() const { return 20; }
  integer ICLOCS_ContinuousMP::DJUpDp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DLTargsDxup_numRows() const { return 120; }
  integer ICLOCS_ContinuousMP::DLTargsDxup_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DLTargsDxup_nnz()     const { return 120; }

  void
  ICLOCS_ContinuousMP::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_ContinuousMP::DLTargsDxup_sparse(
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
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 120, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2LTargsD2xup_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xup_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xup_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::Hx_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::Hx_eval(
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
    real_type t4   = cos(t1);
    result__[ 0   ] = t4 * L__[iL_lambda21__xo] + 40 * t1;
    real_type t6   = X__[iX_x2];
    real_type t9   = cos(t6);
    result__[ 1   ] = t9 * L__[iL_lambda22__xo] + 38 * t6;
    real_type t11  = X__[iX_x3];
    real_type t14  = cos(t11);
    result__[ 2   ] = t14 * L__[iL_lambda23__xo] + 36 * t11;
    real_type t16  = X__[iX_x4];
    real_type t19  = cos(t16);
    result__[ 3   ] = t19 * L__[iL_lambda24__xo] + 34 * t16;
    real_type t21  = X__[iX_x5];
    real_type t24  = cos(t21);
    result__[ 4   ] = t24 * L__[iL_lambda25__xo] + 32 * t21;
    real_type t26  = X__[iX_x6];
    real_type t29  = cos(t26);
    result__[ 5   ] = t29 * L__[iL_lambda26__xo] + 30 * t26;
    real_type t31  = X__[iX_x7];
    real_type t34  = cos(t31);
    result__[ 6   ] = t34 * L__[iL_lambda27__xo] + 28 * t31;
    real_type t36  = X__[iX_x8];
    real_type t39  = cos(t36);
    result__[ 7   ] = t39 * L__[iL_lambda28__xo] + 26 * t36;
    real_type t41  = X__[iX_x9];
    real_type t44  = cos(t41);
    result__[ 8   ] = t44 * L__[iL_lambda29__xo] + 24 * t41;
    real_type t46  = X__[iX_x10];
    real_type t49  = cos(t46);
    result__[ 9   ] = t49 * L__[iL_lambda30__xo] + 22 * t46;
    real_type t51  = X__[iX_x11];
    real_type t54  = cos(t51);
    result__[ 10  ] = t54 * L__[iL_lambda31__xo] + 20 * t51;
    real_type t56  = X__[iX_x12];
    real_type t59  = cos(t56);
    result__[ 11  ] = t59 * L__[iL_lambda32__xo] + 18 * t56;
    real_type t61  = X__[iX_x13];
    real_type t64  = cos(t61);
    result__[ 12  ] = t64 * L__[iL_lambda33__xo] + 16 * t61;
    real_type t66  = X__[iX_x14];
    real_type t69  = cos(t66);
    result__[ 13  ] = t69 * L__[iL_lambda34__xo] + 14 * t66;
    real_type t71  = X__[iX_x15];
    real_type t74  = cos(t71);
    result__[ 14  ] = t74 * L__[iL_lambda35__xo] + 12 * t71;
    real_type t76  = X__[iX_x16];
    real_type t79  = cos(t76);
    result__[ 15  ] = t79 * L__[iL_lambda36__xo] + 10 * t76;
    real_type t81  = X__[iX_x17];
    real_type t84  = cos(t81);
    result__[ 16  ] = t84 * L__[iL_lambda37__xo] + 8 * t81;
    real_type t86  = X__[iX_x18];
    real_type t89  = cos(t86);
    result__[ 17  ] = t89 * L__[iL_lambda38__xo] + 6 * t86;
    real_type t91  = X__[iX_x19];
    real_type t94  = cos(t91);
    result__[ 18  ] = t94 * L__[iL_lambda39__xo] + 4 * t91;
    real_type t96  = X__[iX_x20];
    real_type t99  = cos(t96);
    result__[ 19  ] = t99 * L__[iL_lambda40__xo] + 2 * t96;
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
    real_type t163 = cos(X__[iX_xx1]);
    result__[ 40  ] = 0.2e0 * t163 * L__[iL_lambda61__xo];
    real_type t167 = cos(X__[iX_xx2]);
    result__[ 41  ] = 0.2e0 * t167 * L__[iL_lambda62__xo];
    real_type t171 = cos(X__[iX_xx3]);
    result__[ 42  ] = 0.2e0 * t171 * L__[iL_lambda63__xo];
    real_type t175 = cos(X__[iX_xx4]);
    result__[ 43  ] = 0.2e0 * t175 * L__[iL_lambda64__xo];
    real_type t179 = cos(X__[iX_xx5]);
    result__[ 44  ] = 0.2e0 * t179 * L__[iL_lambda65__xo];
    real_type t183 = cos(X__[iX_xx6]);
    result__[ 45  ] = 0.2e0 * t183 * L__[iL_lambda66__xo];
    real_type t187 = cos(X__[iX_xx7]);
    result__[ 46  ] = 0.2e0 * t187 * L__[iL_lambda67__xo];
    real_type t191 = cos(X__[iX_xx8]);
    result__[ 47  ] = 0.2e0 * t191 * L__[iL_lambda68__xo];
    real_type t195 = cos(X__[iX_xx9]);
    result__[ 48  ] = 0.2e0 * t195 * L__[iL_lambda69__xo];
    real_type t199 = cos(X__[iX_xx10]);
    result__[ 49  ] = 0.2e0 * t199 * L__[iL_lambda70__xo];
    real_type t203 = cos(X__[iX_xx11]);
    result__[ 50  ] = 0.2e0 * t203 * L__[iL_lambda71__xo];
    real_type t207 = cos(X__[iX_xx12]);
    result__[ 51  ] = 0.2e0 * t207 * L__[iL_lambda72__xo];
    real_type t211 = cos(X__[iX_xx13]);
    result__[ 52  ] = 0.2e0 * t211 * L__[iL_lambda73__xo];
    real_type t215 = cos(X__[iX_xx14]);
    result__[ 53  ] = 0.2e0 * t215 * L__[iL_lambda74__xo];
    real_type t219 = cos(X__[iX_xx15]);
    result__[ 54  ] = 0.2e0 * t219 * L__[iL_lambda75__xo];
    real_type t223 = cos(X__[iX_xx16]);
    result__[ 55  ] = 0.2e0 * t223 * L__[iL_lambda76__xo];
    real_type t227 = cos(X__[iX_xx17]);
    result__[ 56  ] = 0.2e0 * t227 * L__[iL_lambda77__xo];
    real_type t231 = cos(X__[iX_xx18]);
    result__[ 57  ] = 0.2e0 * t231 * L__[iL_lambda78__xo];
    real_type t235 = cos(X__[iX_xx19]);
    result__[ 58  ] = 0.2e0 * t235 * L__[iL_lambda79__xo];
    real_type t239 = cos(X__[iX_xx20]);
    result__[ 59  ] = 0.2e0 * t239 * L__[iL_lambda80__xo];
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::Hp_numEqns() const { return 20; }

  void
  ICLOCS_ContinuousMP::Hp_eval(
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
    result__[ 0   ] = L__[iL_lambda21__xo] + L__[iL_lambda61__xo];
    result__[ 1   ] = L__[iL_lambda22__xo] + L__[iL_lambda62__xo];
    result__[ 2   ] = L__[iL_lambda23__xo] + L__[iL_lambda63__xo];
    result__[ 3   ] = L__[iL_lambda24__xo] + L__[iL_lambda64__xo];
    result__[ 4   ] = L__[iL_lambda25__xo] + L__[iL_lambda65__xo];
    result__[ 5   ] = L__[iL_lambda26__xo] + L__[iL_lambda66__xo];
    result__[ 6   ] = L__[iL_lambda27__xo] + L__[iL_lambda67__xo];
    result__[ 7   ] = L__[iL_lambda28__xo] + L__[iL_lambda68__xo];
    result__[ 8   ] = L__[iL_lambda29__xo] + L__[iL_lambda69__xo];
    result__[ 9   ] = L__[iL_lambda30__xo] + L__[iL_lambda70__xo];
    result__[ 10  ] = L__[iL_lambda31__xo] + L__[iL_lambda71__xo];
    result__[ 11  ] = L__[iL_lambda32__xo] + L__[iL_lambda72__xo];
    result__[ 12  ] = L__[iL_lambda33__xo] + L__[iL_lambda73__xo];
    result__[ 13  ] = L__[iL_lambda34__xo] + L__[iL_lambda74__xo];
    result__[ 14  ] = L__[iL_lambda35__xo] + L__[iL_lambda75__xo];
    result__[ 15  ] = L__[iL_lambda36__xo] + L__[iL_lambda76__xo];
    result__[ 16  ] = L__[iL_lambda37__xo] + L__[iL_lambda77__xo];
    result__[ 17  ] = L__[iL_lambda38__xo] + L__[iL_lambda78__xo];
    result__[ 18  ] = L__[iL_lambda39__xo] + L__[iL_lambda79__xo];
    result__[ 19  ] = L__[iL_lambda40__xo] + L__[iL_lambda80__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 20, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DHxDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DHxDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DHxDxp_nnz()     const { return 60; }

  void
  ICLOCS_ContinuousMP::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_ContinuousMP::DHxDxp_sparse(
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
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 60, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DHpDp_numRows() const { return 20; }
  integer ICLOCS_ContinuousMP::DHpDp_numCols() const { return 20; }
  integer ICLOCS_ContinuousMP::DHpDp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DHuDxp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DHuDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DHuDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::eta_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    result__[ 7   ] = L__[iL_lambda8__xo];
    result__[ 8   ] = L__[iL_lambda9__xo];
    result__[ 9   ] = L__[iL_lambda10__xo];
    result__[ 10  ] = L__[iL_lambda11__xo];
    result__[ 11  ] = L__[iL_lambda12__xo];
    result__[ 12  ] = L__[iL_lambda13__xo];
    result__[ 13  ] = L__[iL_lambda14__xo];
    result__[ 14  ] = L__[iL_lambda15__xo];
    result__[ 15  ] = L__[iL_lambda16__xo];
    result__[ 16  ] = L__[iL_lambda17__xo];
    result__[ 17  ] = L__[iL_lambda18__xo];
    result__[ 18  ] = L__[iL_lambda19__xo];
    result__[ 19  ] = L__[iL_lambda20__xo];
    result__[ 20  ] = L__[iL_lambda21__xo];
    result__[ 21  ] = L__[iL_lambda22__xo];
    result__[ 22  ] = L__[iL_lambda23__xo];
    result__[ 23  ] = L__[iL_lambda24__xo];
    result__[ 24  ] = L__[iL_lambda25__xo];
    result__[ 25  ] = L__[iL_lambda26__xo];
    result__[ 26  ] = L__[iL_lambda27__xo];
    result__[ 27  ] = L__[iL_lambda28__xo];
    result__[ 28  ] = L__[iL_lambda29__xo];
    result__[ 29  ] = L__[iL_lambda30__xo];
    result__[ 30  ] = L__[iL_lambda31__xo];
    result__[ 31  ] = L__[iL_lambda32__xo];
    result__[ 32  ] = L__[iL_lambda33__xo];
    result__[ 33  ] = L__[iL_lambda34__xo];
    result__[ 34  ] = L__[iL_lambda35__xo];
    result__[ 35  ] = L__[iL_lambda36__xo];
    result__[ 36  ] = L__[iL_lambda37__xo];
    result__[ 37  ] = L__[iL_lambda38__xo];
    result__[ 38  ] = L__[iL_lambda39__xo];
    result__[ 39  ] = L__[iL_lambda40__xo];
    result__[ 40  ] = L__[iL_lambda41__xo];
    result__[ 41  ] = L__[iL_lambda42__xo];
    result__[ 42  ] = L__[iL_lambda43__xo];
    result__[ 43  ] = L__[iL_lambda44__xo];
    result__[ 44  ] = L__[iL_lambda45__xo];
    result__[ 45  ] = L__[iL_lambda46__xo];
    result__[ 46  ] = L__[iL_lambda47__xo];
    result__[ 47  ] = L__[iL_lambda48__xo];
    result__[ 48  ] = L__[iL_lambda49__xo];
    result__[ 49  ] = L__[iL_lambda50__xo];
    result__[ 50  ] = L__[iL_lambda51__xo];
    result__[ 51  ] = L__[iL_lambda52__xo];
    result__[ 52  ] = L__[iL_lambda53__xo];
    result__[ 53  ] = L__[iL_lambda54__xo];
    result__[ 54  ] = L__[iL_lambda55__xo];
    result__[ 55  ] = L__[iL_lambda56__xo];
    result__[ 56  ] = L__[iL_lambda57__xo];
    result__[ 57  ] = L__[iL_lambda58__xo];
    result__[ 58  ] = L__[iL_lambda59__xo];
    result__[ 59  ] = L__[iL_lambda60__xo];
    result__[ 60  ] = L__[iL_lambda61__xo];
    result__[ 61  ] = L__[iL_lambda62__xo];
    result__[ 62  ] = L__[iL_lambda63__xo];
    result__[ 63  ] = L__[iL_lambda64__xo];
    result__[ 64  ] = L__[iL_lambda65__xo];
    result__[ 65  ] = L__[iL_lambda66__xo];
    result__[ 66  ] = L__[iL_lambda67__xo];
    result__[ 67  ] = L__[iL_lambda68__xo];
    result__[ 68  ] = L__[iL_lambda69__xo];
    result__[ 69  ] = L__[iL_lambda70__xo];
    result__[ 70  ] = L__[iL_lambda71__xo];
    result__[ 71  ] = L__[iL_lambda72__xo];
    result__[ 72  ] = L__[iL_lambda73__xo];
    result__[ 73  ] = L__[iL_lambda74__xo];
    result__[ 74  ] = L__[iL_lambda75__xo];
    result__[ 75  ] = L__[iL_lambda76__xo];
    result__[ 76  ] = L__[iL_lambda77__xo];
    result__[ 77  ] = L__[iL_lambda78__xo];
    result__[ 78  ] = L__[iL_lambda79__xo];
    result__[ 79  ] = L__[iL_lambda80__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DetaDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DetaDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::nu_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    result__[ 7   ] = V__[7];
    result__[ 8   ] = V__[8];
    result__[ 9   ] = V__[9];
    result__[ 10  ] = V__[10];
    result__[ 11  ] = V__[11];
    result__[ 12  ] = V__[12];
    result__[ 13  ] = V__[13];
    result__[ 14  ] = V__[14];
    result__[ 15  ] = V__[15];
    result__[ 16  ] = V__[16];
    result__[ 17  ] = V__[17];
    result__[ 18  ] = V__[18];
    result__[ 19  ] = V__[19];
    result__[ 20  ] = V__[20];
    result__[ 21  ] = V__[21];
    result__[ 22  ] = V__[22];
    result__[ 23  ] = V__[23];
    result__[ 24  ] = V__[24];
    result__[ 25  ] = V__[25];
    result__[ 26  ] = V__[26];
    result__[ 27  ] = V__[27];
    result__[ 28  ] = V__[28];
    result__[ 29  ] = V__[29];
    result__[ 30  ] = V__[30];
    result__[ 31  ] = V__[31];
    result__[ 32  ] = V__[32];
    result__[ 33  ] = V__[33];
    result__[ 34  ] = V__[34];
    result__[ 35  ] = V__[35];
    result__[ 36  ] = V__[36];
    result__[ 37  ] = V__[37];
    result__[ 38  ] = V__[38];
    result__[ 39  ] = V__[39];
    result__[ 40  ] = V__[40];
    result__[ 41  ] = V__[41];
    result__[ 42  ] = V__[42];
    result__[ 43  ] = V__[43];
    result__[ 44  ] = V__[44];
    result__[ 45  ] = V__[45];
    result__[ 46  ] = V__[46];
    result__[ 47  ] = V__[47];
    result__[ 48  ] = V__[48];
    result__[ 49  ] = V__[49];
    result__[ 50  ] = V__[50];
    result__[ 51  ] = V__[51];
    result__[ 52  ] = V__[52];
    result__[ 53  ] = V__[53];
    result__[ 54  ] = V__[54];
    result__[ 55  ] = V__[55];
    result__[ 56  ] = V__[56];
    result__[ 57  ] = V__[57];
    result__[ 58  ] = V__[58];
    result__[ 59  ] = V__[59];
    result__[ 60  ] = V__[60];
    result__[ 61  ] = V__[61];
    result__[ 62  ] = V__[62];
    result__[ 63  ] = V__[63];
    result__[ 64  ] = V__[64];
    result__[ 65  ] = V__[65];
    result__[ 66  ] = V__[66];
    result__[ 67  ] = V__[67];
    result__[ 68  ] = V__[68];
    result__[ 69  ] = V__[69];
    result__[ 70  ] = V__[70];
    result__[ 71  ] = V__[71];
    result__[ 72  ] = V__[72];
    result__[ 73  ] = V__[73];
    result__[ 74  ] = V__[74];
    result__[ 75  ] = V__[75];
    result__[ 76  ] = V__[76];
    result__[ 77  ] = V__[77];
    result__[ 78  ] = V__[78];
    result__[ 79  ] = V__[79];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DnuDxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DnuDxp_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
