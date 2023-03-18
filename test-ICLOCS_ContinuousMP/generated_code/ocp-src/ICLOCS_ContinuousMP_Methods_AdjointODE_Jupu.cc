/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_AdjointODE.cc                      |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_u4];
    real_type t3   = u4Limitation_min(-10 - t1);
    real_type t4   = ModelPars[iM_xy_bound];
    real_type t5   = X__[iX_xx15];
    real_type t7   = xx15Limitation_min(-t4 - t5);
    real_type t9   = xx15Limitation_max(t5 - t4);
    real_type t10  = X__[iX_xx16];
    real_type t12  = xx16Limitation_min(-t4 - t10);
    real_type t14  = xx16Limitation_max(t10 - t4);
    real_type t15  = X__[iX_xx17];
    real_type t17  = xx17Limitation_min(-t4 - t15);
    real_type t19  = xx17Limitation_max(t15 - t4);
    real_type t20  = X__[iX_xx18];
    real_type t22  = xx18Limitation_min(-t4 - t20);
    real_type t24  = xx18Limitation_max(t20 - t4);
    real_type t25  = X__[iX_xx19];
    real_type t27  = xx19Limitation_min(-t4 - t25);
    real_type t29  = xx19Limitation_max(t25 - t4);
    real_type t30  = X__[iX_xx20];
    real_type t32  = xx20Limitation_min(-t4 - t30);
    real_type t34  = xx20Limitation_max(t30 - t4);
    real_type t35  = X__[iX_yy1];
    real_type t37  = yy1Limitation_min(-t4 - t35);
    real_type t39  = yy1Limitation_max(t35 - t4);
    real_type t40  = t3 + t7 + t9 + t12 + t14 + t17 + t19 + t22 + t24 + t27 + t29 + t32 + t34 + t37 + t39;
    real_type t41  = X__[iX_yy2];
    real_type t43  = yy2Limitation_min(-t4 - t41);
    real_type t45  = yy2Limitation_max(t41 - t4);
    real_type t46  = X__[iX_yy3];
    real_type t48  = yy3Limitation_min(-t4 - t46);
    real_type t50  = yy3Limitation_max(t46 - t4);
    real_type t51  = X__[iX_yy4];
    real_type t53  = yy4Limitation_max(t51 - t4);
    real_type t55  = yy4Limitation_min(-t4 - t51);
    real_type t56  = X__[iX_yy5];
    real_type t58  = yy5Limitation_min(-t4 - t56);
    real_type t60  = yy5Limitation_max(t56 - t4);
    real_type t61  = X__[iX_yy18];
    real_type t63  = yy18Limitation_min(-t4 - t61);
    real_type t65  = yy18Limitation_max(t61 - t4);
    real_type t66  = X__[iX_yy19];
    real_type t68  = yy19Limitation_min(-t4 - t66);
    real_type t70  = yy19Limitation_max(t66 - t4);
    real_type t72  = u4Limitation_max(t1 - 10);
    real_type t73  = P__[iP_u5];
    real_type t75  = u5Limitation_min(-10 - t73);
    real_type t77  = u5Limitation_max(t73 - 10);
    real_type t78  = t43 + t45 + t48 + t50 + t53 + t55 + t58 + t60 + t63 + t65 + t68 + t70 + t72 + t75 + t77;
    real_type t80  = P__[iP_u6];
    real_type t82  = u6Limitation_min(-10 - t80);
    real_type t84  = u6Limitation_max(t80 - 10);
    real_type t85  = P__[iP_u7];
    real_type t87  = u7Limitation_min(-10 - t85);
    real_type t89  = u7Limitation_max(t85 - 10);
    real_type t90  = P__[iP_u8];
    real_type t92  = u8Limitation_min(-10 - t90);
    real_type t94  = u8Limitation_max(t90 - 10);
    real_type t95  = P__[iP_u9];
    real_type t97  = u9Limitation_min(-10 - t95);
    real_type t99  = u9Limitation_max(t95 - 10);
    real_type t100 = P__[iP_u10];
    real_type t102 = u10Limitation_min(-10 - t100);
    real_type t104 = u10Limitation_max(t100 - 10);
    real_type t105 = P__[iP_u11];
    real_type t107 = u11Limitation_min(-10 - t105);
    real_type t109 = u11Limitation_max(t105 - 10);
    real_type t110 = P__[iP_u12];
    real_type t112 = u12Limitation_max(t110 - 10);
    real_type t114 = u12Limitation_min(-10 - t110);
    real_type t115 = P__[iP_u13];
    real_type t117 = u13Limitation_min(-10 - t115);
    real_type t118 = t82 + t84 + t87 + t89 + t92 + t94 + t97 + t99 + t102 + t104 + t107 + t109 + t112 + t114 + t117;
    real_type t120 = u13Limitation_max(t115 - 10);
    real_type t121 = P__[iP_u14];
    real_type t123 = u14Limitation_min(-10 - t121);
    real_type t125 = u14Limitation_max(t121 - 10);
    real_type t126 = P__[iP_u15];
    real_type t128 = u15Limitation_min(-10 - t126);
    real_type t130 = u15Limitation_max(t126 - 10);
    real_type t131 = P__[iP_u16];
    real_type t133 = u16Limitation_min(-10 - t131);
    real_type t135 = u16Limitation_max(t131 - 10);
    real_type t136 = P__[iP_u17];
    real_type t138 = u17Limitation_min(-10 - t136);
    real_type t140 = u17Limitation_max(t136 - 10);
    real_type t141 = P__[iP_u18];
    real_type t143 = u18Limitation_min(-10 - t141);
    real_type t145 = u18Limitation_max(t141 - 10);
    real_type t146 = P__[iP_u19];
    real_type t148 = u19Limitation_min(-10 - t146);
    real_type t150 = u19Limitation_max(t146 - 10);
    real_type t151 = P__[iP_u20];
    real_type t153 = u20Limitation_min(-10 - t151);
    real_type t155 = u20Limitation_max(t151 - 10);
    real_type t156 = t120 + t123 + t125 + t128 + t130 + t133 + t135 + t138 + t140 + t143 + t145 + t148 + t150 + t153 + t155;
    real_type t159 = P__[iP_u1];
    real_type t161 = u1Limitation_min(-10 - t159);
    real_type t163 = u1Limitation_max(t159 - 10);
    real_type t164 = P__[iP_u2];
    real_type t166 = u2Limitation_min(-10 - t164);
    real_type t168 = u2Limitation_max(t164 - 10);
    real_type t169 = P__[iP_u3];
    real_type t171 = u3Limitation_min(-10 - t169);
    real_type t173 = u3Limitation_max(t169 - 10);
    real_type t174 = X__[iX_yy20];
    real_type t176 = yy20Limitation_min(-t4 - t174);
    real_type t178 = yy20Limitation_max(t174 - t4);
    real_type t179 = X__[iX_xx1];
    real_type t181 = xx1Limitation_min(-t4 - t179);
    real_type t183 = xx1Limitation_max(t179 - t4);
    real_type t184 = X__[iX_xx10];
    real_type t186 = xx10Limitation_min(-t4 - t184);
    real_type t188 = xx10Limitation_max(t184 - t4);
    real_type t189 = X__[iX_xx11];
    real_type t191 = xx11Limitation_min(-t4 - t189);
    real_type t193 = xx11Limitation_max(t189 - t4);
    real_type t194 = X__[iX_xx12];
    real_type t196 = xx12Limitation_min(-t4 - t194);
    real_type t197 = t161 + t163 + t166 + t168 + t171 + t173 + t176 + t178 + t181 + t183 + t186 + t188 + t191 + t193 + t196;
    real_type t199 = xx12Limitation_max(t194 - t4);
    real_type t200 = X__[iX_xx13];
    real_type t202 = xx13Limitation_min(-t4 - t200);
    real_type t204 = xx13Limitation_max(t200 - t4);
    real_type t205 = X__[iX_xx14];
    real_type t207 = xx14Limitation_min(-t4 - t205);
    real_type t209 = xx14Limitation_max(t205 - t4);
    real_type t210 = X__[iX_yy10];
    real_type t212 = yy10Limitation_min(-t4 - t210);
    real_type t214 = yy10Limitation_max(t210 - t4);
    real_type t215 = X__[iX_yy11];
    real_type t217 = yy11Limitation_min(-t4 - t215);
    real_type t219 = yy11Limitation_max(t215 - t4);
    real_type t220 = X__[iX_yy6];
    real_type t222 = yy6Limitation_min(-t4 - t220);
    real_type t224 = yy6Limitation_max(t220 - t4);
    real_type t225 = X__[iX_yy7];
    real_type t227 = yy7Limitation_min(-t4 - t225);
    real_type t229 = yy7Limitation_max(t225 - t4);
    real_type t230 = X__[iX_yy8];
    real_type t232 = yy8Limitation_min(-t4 - t230);
    real_type t234 = yy8Limitation_max(t230 - t4);
    real_type t235 = t199 + t202 + t204 + t207 + t209 + t212 + t214 + t217 + t219 + t222 + t224 + t227 + t229 + t232 + t234;
    real_type t237 = X__[iX_yy9];
    real_type t239 = yy9Limitation_min(-t4 - t237);
    real_type t241 = yy9Limitation_max(t237 - t4);
    real_type t242 = X__[iX_xx6];
    real_type t244 = xx6Limitation_min(-t4 - t242);
    real_type t246 = xx6Limitation_max(t242 - t4);
    real_type t247 = X__[iX_xx7];
    real_type t249 = xx7Limitation_min(-t4 - t247);
    real_type t251 = xx7Limitation_max(t247 - t4);
    real_type t252 = X__[iX_xx8];
    real_type t254 = xx8Limitation_min(-t4 - t252);
    real_type t256 = xx8Limitation_max(t252 - t4);
    real_type t257 = X__[iX_xx9];
    real_type t259 = xx9Limitation_min(-t4 - t257);
    real_type t261 = xx9Limitation_max(t257 - t4);
    real_type t262 = X__[iX_xx2];
    real_type t264 = xx2Limitation_min(-t4 - t262);
    real_type t266 = xx2Limitation_max(t262 - t4);
    real_type t267 = X__[iX_xx3];
    real_type t269 = xx3Limitation_min(-t4 - t267);
    real_type t271 = xx3Limitation_max(t267 - t4);
    real_type t272 = X__[iX_yy14];
    real_type t274 = yy14Limitation_min(-t4 - t272);
    real_type t275 = t239 + t241 + t244 + t246 + t249 + t251 + t254 + t256 + t259 + t261 + t264 + t266 + t269 + t271 + t274;
    real_type t277 = yy14Limitation_max(t272 - t4);
    real_type t278 = X__[iX_yy15];
    real_type t280 = yy15Limitation_min(-t4 - t278);
    real_type t282 = yy15Limitation_max(t278 - t4);
    real_type t283 = X__[iX_yy12];
    real_type t285 = yy12Limitation_min(-t4 - t283);
    real_type t287 = yy12Limitation_max(t283 - t4);
    real_type t288 = X__[iX_yy13];
    real_type t290 = yy13Limitation_min(-t4 - t288);
    real_type t292 = yy13Limitation_max(t288 - t4);
    real_type t293 = X__[iX_xx4];
    real_type t295 = xx4Limitation_min(-t4 - t293);
    real_type t297 = xx4Limitation_max(t293 - t4);
    real_type t298 = X__[iX_xx5];
    real_type t300 = xx5Limitation_min(-t4 - t298);
    real_type t302 = xx5Limitation_max(t298 - t4);
    real_type t303 = X__[iX_yy16];
    real_type t305 = yy16Limitation_min(-t4 - t303);
    real_type t307 = yy16Limitation_max(t303 - t4);
    real_type t308 = X__[iX_yy17];
    real_type t310 = yy17Limitation_min(-t4 - t308);
    real_type t312 = yy17Limitation_max(t308 - t4);
    real_type t313 = t277 + t280 + t282 + t285 + t287 + t290 + t292 + t295 + t297 + t300 + t302 + t305 + t307 + t310 + t312;
    real_type result__ = t40 + t78 + t118 + t156 + t197 + t235 + t275 + t313;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JPxpu_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    result__[ 80  ] = 0;
    result__[ 81  ] = 0;
    result__[ 82  ] = 0;
    result__[ 83  ] = 0;
    result__[ 84  ] = 0;
    result__[ 85  ] = 0;
    result__[ 86  ] = 0;
    result__[ 87  ] = 0;
    result__[ 88  ] = 0;
    result__[ 89  ] = 0;
    result__[ 90  ] = 0;
    result__[ 91  ] = 0;
    result__[ 92  ] = 0;
    result__[ 93  ] = 0;
    result__[ 94  ] = 0;
    result__[ 95  ] = 0;
    result__[ 96  ] = 0;
    result__[ 97  ] = 0;
    result__[ 98  ] = 0;
    result__[ 99  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 100, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::JUxpu_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    result__[ 80  ] = 0;
    result__[ 81  ] = 0;
    result__[ 82  ] = 0;
    result__[ 83  ] = 0;
    result__[ 84  ] = 0;
    result__[ 85  ] = 0;
    result__[ 86  ] = 0;
    result__[ 87  ] = 0;
    result__[ 88  ] = 0;
    result__[ 89  ] = 0;
    result__[ 90  ] = 0;
    result__[ 91  ] = 0;
    result__[ 92  ] = 0;
    result__[ 93  ] = 0;
    result__[ 94  ] = 0;
    result__[ 95  ] = 0;
    result__[ 96  ] = 0;
    result__[ 97  ] = 0;
    result__[ 98  ] = 0;
    result__[ 99  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 100, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTxpu_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    real_type t44  = ALIAS_xx9Limitation_min_D(-t1 - t42);
    real_type t46  = ALIAS_xx9Limitation_max_D(t42 - t1);
    result__[ 48  ] = -t44 + t46;
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
    real_type t189 = ALIAS_yy18Limitation_min_D(-t1 - t187);
    real_type t191 = ALIAS_yy18Limitation_max_D(t187 - t1);
    result__[ 77  ] = -t189 + t191;
    real_type t192 = X__[iX_yy19];
    real_type t194 = ALIAS_yy19Limitation_min_D(-t1 - t192);
    real_type t196 = ALIAS_yy19Limitation_max_D(t192 - t1);
    result__[ 78  ] = -t194 + t196;
    real_type t197 = X__[iX_yy20];
    real_type t199 = ALIAS_yy20Limitation_min_D(-t1 - t197);
    real_type t201 = ALIAS_yy20Limitation_max_D(t197 - t1);
    result__[ 79  ] = -t199 + t201;
    real_type t202 = P__[iP_u1];
    real_type t204 = ALIAS_u1Limitation_min_D(-10 - t202);
    real_type t206 = ALIAS_u1Limitation_max_D(t202 - 10);
    result__[ 80  ] = -t204 + t206;
    real_type t207 = P__[iP_u2];
    real_type t209 = ALIAS_u2Limitation_min_D(-10 - t207);
    real_type t211 = ALIAS_u2Limitation_max_D(t207 - 10);
    result__[ 81  ] = -t209 + t211;
    real_type t212 = P__[iP_u3];
    real_type t214 = ALIAS_u3Limitation_min_D(-10 - t212);
    real_type t216 = ALIAS_u3Limitation_max_D(t212 - 10);
    result__[ 82  ] = -t214 + t216;
    real_type t217 = P__[iP_u4];
    real_type t219 = ALIAS_u4Limitation_min_D(-10 - t217);
    real_type t221 = ALIAS_u4Limitation_max_D(t217 - 10);
    result__[ 83  ] = -t219 + t221;
    real_type t222 = P__[iP_u5];
    real_type t224 = ALIAS_u5Limitation_min_D(-10 - t222);
    real_type t226 = ALIAS_u5Limitation_max_D(t222 - 10);
    result__[ 84  ] = -t224 + t226;
    real_type t227 = P__[iP_u6];
    real_type t229 = ALIAS_u6Limitation_min_D(-10 - t227);
    real_type t231 = ALIAS_u6Limitation_max_D(t227 - 10);
    result__[ 85  ] = -t229 + t231;
    real_type t232 = P__[iP_u7];
    real_type t234 = ALIAS_u7Limitation_min_D(-10 - t232);
    real_type t236 = ALIAS_u7Limitation_max_D(t232 - 10);
    result__[ 86  ] = -t234 + t236;
    real_type t237 = P__[iP_u8];
    real_type t239 = ALIAS_u8Limitation_min_D(-10 - t237);
    real_type t241 = ALIAS_u8Limitation_max_D(t237 - 10);
    result__[ 87  ] = -t239 + t241;
    real_type t242 = P__[iP_u9];
    real_type t244 = ALIAS_u9Limitation_min_D(-10 - t242);
    real_type t246 = ALIAS_u9Limitation_max_D(t242 - 10);
    result__[ 88  ] = -t244 + t246;
    real_type t247 = P__[iP_u10];
    real_type t249 = ALIAS_u10Limitation_min_D(-10 - t247);
    real_type t251 = ALIAS_u10Limitation_max_D(t247 - 10);
    result__[ 89  ] = -t249 + t251;
    real_type t252 = P__[iP_u11];
    real_type t254 = ALIAS_u11Limitation_min_D(-10 - t252);
    real_type t256 = ALIAS_u11Limitation_max_D(t252 - 10);
    result__[ 90  ] = -t254 + t256;
    real_type t257 = P__[iP_u12];
    real_type t259 = ALIAS_u12Limitation_max_D(t257 - 10);
    real_type t261 = ALIAS_u12Limitation_min_D(-10 - t257);
    result__[ 91  ] = t259 - t261;
    real_type t262 = P__[iP_u13];
    real_type t264 = ALIAS_u13Limitation_min_D(-10 - t262);
    real_type t266 = ALIAS_u13Limitation_max_D(t262 - 10);
    result__[ 92  ] = -t264 + t266;
    real_type t267 = P__[iP_u14];
    real_type t269 = ALIAS_u14Limitation_min_D(-10 - t267);
    real_type t271 = ALIAS_u14Limitation_max_D(t267 - 10);
    result__[ 93  ] = -t269 + t271;
    real_type t272 = P__[iP_u15];
    real_type t274 = ALIAS_u15Limitation_min_D(-10 - t272);
    real_type t276 = ALIAS_u15Limitation_max_D(t272 - 10);
    result__[ 94  ] = -t274 + t276;
    real_type t277 = P__[iP_u16];
    real_type t279 = ALIAS_u16Limitation_min_D(-10 - t277);
    real_type t281 = ALIAS_u16Limitation_max_D(t277 - 10);
    result__[ 95  ] = -t279 + t281;
    real_type t282 = P__[iP_u17];
    real_type t284 = ALIAS_u17Limitation_min_D(-10 - t282);
    real_type t286 = ALIAS_u17Limitation_max_D(t282 - 10);
    result__[ 96  ] = -t284 + t286;
    real_type t287 = P__[iP_u18];
    real_type t289 = ALIAS_u18Limitation_min_D(-10 - t287);
    real_type t291 = ALIAS_u18Limitation_max_D(t287 - 10);
    result__[ 97  ] = -t289 + t291;
    real_type t292 = P__[iP_u19];
    real_type t294 = ALIAS_u19Limitation_min_D(-10 - t292);
    real_type t296 = ALIAS_u19Limitation_max_D(t292 - 10);
    result__[ 98  ] = -t294 + t296;
    real_type t297 = P__[iP_u20];
    real_type t299 = ALIAS_u20Limitation_min_D(-10 - t297);
    real_type t301 = ALIAS_u20Limitation_max_D(t297 - 10);
    result__[ 99  ] = -t299 + t301;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 100, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::LTargs_numEqns() const { return 120; }

  void
  ICLOCS_ContinuousMP::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer ICLOCS_ContinuousMP::D2JPD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JPD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    real_type t44  = ALIAS_xx9Limitation_min_DD(-t1 - t42);
    real_type t46  = ALIAS_xx9Limitation_max_DD(t42 - t1);
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
    real_type t189 = ALIAS_yy18Limitation_min_DD(-t1 - t187);
    real_type t191 = ALIAS_yy18Limitation_max_DD(t187 - t1);
    result__[ 37  ] = t189 + t191;
    real_type t192 = X__[iX_yy19];
    real_type t194 = ALIAS_yy19Limitation_min_DD(-t1 - t192);
    real_type t196 = ALIAS_yy19Limitation_max_DD(t192 - t1);
    result__[ 38  ] = t194 + t196;
    real_type t197 = X__[iX_yy20];
    real_type t199 = ALIAS_yy20Limitation_min_DD(-t1 - t197);
    real_type t201 = ALIAS_yy20Limitation_max_DD(t197 - t1);
    result__[ 39  ] = t199 + t201;
    real_type t202 = P__[iP_u1];
    real_type t204 = ALIAS_u1Limitation_min_DD(-10 - t202);
    real_type t206 = ALIAS_u1Limitation_max_DD(t202 - 10);
    result__[ 40  ] = t204 + t206;
    real_type t207 = P__[iP_u2];
    real_type t209 = ALIAS_u2Limitation_min_DD(-10 - t207);
    real_type t211 = ALIAS_u2Limitation_max_DD(t207 - 10);
    result__[ 41  ] = t209 + t211;
    real_type t212 = P__[iP_u3];
    real_type t214 = ALIAS_u3Limitation_min_DD(-10 - t212);
    real_type t216 = ALIAS_u3Limitation_max_DD(t212 - 10);
    result__[ 42  ] = t214 + t216;
    real_type t217 = P__[iP_u4];
    real_type t219 = ALIAS_u4Limitation_min_DD(-10 - t217);
    real_type t221 = ALIAS_u4Limitation_max_DD(t217 - 10);
    result__[ 43  ] = t219 + t221;
    real_type t222 = P__[iP_u5];
    real_type t224 = ALIAS_u5Limitation_min_DD(-10 - t222);
    real_type t226 = ALIAS_u5Limitation_max_DD(t222 - 10);
    result__[ 44  ] = t224 + t226;
    real_type t227 = P__[iP_u6];
    real_type t229 = ALIAS_u6Limitation_min_DD(-10 - t227);
    real_type t231 = ALIAS_u6Limitation_max_DD(t227 - 10);
    result__[ 45  ] = t229 + t231;
    real_type t232 = P__[iP_u7];
    real_type t234 = ALIAS_u7Limitation_min_DD(-10 - t232);
    real_type t236 = ALIAS_u7Limitation_max_DD(t232 - 10);
    result__[ 46  ] = t234 + t236;
    real_type t237 = P__[iP_u8];
    real_type t239 = ALIAS_u8Limitation_min_DD(-10 - t237);
    real_type t241 = ALIAS_u8Limitation_max_DD(t237 - 10);
    result__[ 47  ] = t239 + t241;
    real_type t242 = P__[iP_u9];
    real_type t244 = ALIAS_u9Limitation_min_DD(-10 - t242);
    real_type t246 = ALIAS_u9Limitation_max_DD(t242 - 10);
    result__[ 48  ] = t244 + t246;
    real_type t247 = P__[iP_u10];
    real_type t249 = ALIAS_u10Limitation_min_DD(-10 - t247);
    real_type t251 = ALIAS_u10Limitation_max_DD(t247 - 10);
    result__[ 49  ] = t249 + t251;
    real_type t252 = P__[iP_u11];
    real_type t254 = ALIAS_u11Limitation_min_DD(-10 - t252);
    real_type t256 = ALIAS_u11Limitation_max_DD(t252 - 10);
    result__[ 50  ] = t254 + t256;
    real_type t257 = P__[iP_u12];
    real_type t259 = ALIAS_u12Limitation_max_DD(t257 - 10);
    real_type t261 = ALIAS_u12Limitation_min_DD(-10 - t257);
    result__[ 51  ] = t259 + t261;
    real_type t262 = P__[iP_u13];
    real_type t264 = ALIAS_u13Limitation_min_DD(-10 - t262);
    real_type t266 = ALIAS_u13Limitation_max_DD(t262 - 10);
    result__[ 52  ] = t264 + t266;
    real_type t267 = P__[iP_u14];
    real_type t269 = ALIAS_u14Limitation_min_DD(-10 - t267);
    real_type t271 = ALIAS_u14Limitation_max_DD(t267 - 10);
    result__[ 53  ] = t269 + t271;
    real_type t272 = P__[iP_u15];
    real_type t274 = ALIAS_u15Limitation_min_DD(-10 - t272);
    real_type t276 = ALIAS_u15Limitation_max_DD(t272 - 10);
    result__[ 54  ] = t274 + t276;
    real_type t277 = P__[iP_u16];
    real_type t279 = ALIAS_u16Limitation_min_DD(-10 - t277);
    real_type t281 = ALIAS_u16Limitation_max_DD(t277 - 10);
    result__[ 55  ] = t279 + t281;
    real_type t282 = P__[iP_u17];
    real_type t284 = ALIAS_u17Limitation_min_DD(-10 - t282);
    real_type t286 = ALIAS_u17Limitation_max_DD(t282 - 10);
    result__[ 56  ] = t284 + t286;
    real_type t287 = P__[iP_u18];
    real_type t289 = ALIAS_u18Limitation_min_DD(-10 - t287);
    real_type t291 = ALIAS_u18Limitation_max_DD(t287 - 10);
    result__[ 57  ] = t289 + t291;
    real_type t292 = P__[iP_u19];
    real_type t294 = ALIAS_u19Limitation_min_DD(-10 - t292);
    real_type t296 = ALIAS_u19Limitation_max_DD(t292 - 10);
    result__[ 58  ] = t294 + t296;
    real_type t297 = P__[iP_u20];
    real_type t299 = ALIAS_u20Limitation_min_DD(-10 - t297);
    real_type t301 = ALIAS_u20Limitation_max_DD(t297 - 10);
    result__[ 59  ] = t299 + t301;
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
