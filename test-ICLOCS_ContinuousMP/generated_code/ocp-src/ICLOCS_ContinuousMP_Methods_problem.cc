/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_problem.cc                         |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_ContinuousMP::continuation_step_0( real_type s ) {
    real_type t1   = ModelPars[iM_xy_eps0];
    real_type t5   = t1 + (ModelPars[iM_xy_eps1] - t1) * s;
    xx1Limitation_min.update_epsilon(t5);
    xx1Limitation_max.update_epsilon(t5);
    yy1Limitation_min.update_epsilon(t5);
    yy1Limitation_max.update_epsilon(t5);
    real_type t6   = ModelPars[iM_xy_tol0];
    real_type t10  = t6 + (ModelPars[iM_xy_tol1] - t6) * s;
    xx1Limitation_min.update_tolerance(t10);
    xx1Limitation_max.update_tolerance(t10);
    yy1Limitation_min.update_tolerance(t10);
    yy1Limitation_max.update_tolerance(t10);
    xx2Limitation_min.update_epsilon(t5);
    xx2Limitation_max.update_epsilon(t5);
    yy2Limitation_min.update_epsilon(t5);
    yy2Limitation_max.update_epsilon(t5);
    xx2Limitation_min.update_tolerance(t10);
    xx2Limitation_max.update_tolerance(t10);
    yy2Limitation_min.update_tolerance(t10);
    yy2Limitation_max.update_tolerance(t10);
    xx3Limitation_min.update_epsilon(t5);
    xx3Limitation_max.update_epsilon(t5);
    yy3Limitation_min.update_epsilon(t5);
    yy3Limitation_max.update_epsilon(t5);
    xx3Limitation_min.update_tolerance(t10);
    xx3Limitation_max.update_tolerance(t10);
    yy3Limitation_min.update_tolerance(t10);
    yy3Limitation_max.update_tolerance(t10);
    xx4Limitation_min.update_epsilon(t5);
    xx4Limitation_max.update_epsilon(t5);
    yy4Limitation_min.update_epsilon(t5);
    yy4Limitation_max.update_epsilon(t5);
    xx4Limitation_min.update_tolerance(t10);
    xx4Limitation_max.update_tolerance(t10);
    yy4Limitation_min.update_tolerance(t10);
    yy4Limitation_max.update_tolerance(t10);
    xx5Limitation_min.update_epsilon(t5);
    xx5Limitation_max.update_epsilon(t5);
    yy5Limitation_min.update_epsilon(t5);
    yy5Limitation_max.update_epsilon(t5);
    xx5Limitation_min.update_tolerance(t10);
    xx5Limitation_max.update_tolerance(t10);
    yy5Limitation_min.update_tolerance(t10);
    yy5Limitation_max.update_tolerance(t10);
    xx6Limitation_min.update_epsilon(t5);
    xx6Limitation_max.update_epsilon(t5);
    yy6Limitation_min.update_epsilon(t5);
    yy6Limitation_max.update_epsilon(t5);
    xx6Limitation_min.update_tolerance(t10);
    xx6Limitation_max.update_tolerance(t10);
    yy6Limitation_min.update_tolerance(t10);
    yy6Limitation_max.update_tolerance(t10);
    xx7Limitation_min.update_epsilon(t5);
    xx7Limitation_max.update_epsilon(t5);
    yy7Limitation_min.update_epsilon(t5);
    yy7Limitation_max.update_epsilon(t5);
    xx7Limitation_min.update_tolerance(t10);
    xx7Limitation_max.update_tolerance(t10);
    yy7Limitation_min.update_tolerance(t10);
    yy7Limitation_max.update_tolerance(t10);
    xx8Limitation_min.update_epsilon(t5);
    xx8Limitation_max.update_epsilon(t5);
    yy8Limitation_min.update_epsilon(t5);
    yy8Limitation_max.update_epsilon(t5);
    xx8Limitation_min.update_tolerance(t10);
    xx8Limitation_max.update_tolerance(t10);
    yy8Limitation_min.update_tolerance(t10);
    yy8Limitation_max.update_tolerance(t10);
    xx9Limitation_min.update_epsilon(t5);
    xx9Limitation_max.update_epsilon(t5);
    yy9Limitation_min.update_epsilon(t5);
    yy9Limitation_max.update_epsilon(t5);
    xx9Limitation_min.update_tolerance(t10);
    xx9Limitation_max.update_tolerance(t10);
    yy9Limitation_min.update_tolerance(t10);
    yy9Limitation_max.update_tolerance(t10);
    xx10Limitation_min.update_epsilon(t5);
    xx10Limitation_max.update_epsilon(t5);
    yy10Limitation_min.update_epsilon(t5);
    yy10Limitation_max.update_epsilon(t5);
    xx10Limitation_min.update_tolerance(t10);
    xx10Limitation_max.update_tolerance(t10);
    yy10Limitation_min.update_tolerance(t10);
    yy10Limitation_max.update_tolerance(t10);
    xx11Limitation_min.update_epsilon(t5);
    xx11Limitation_max.update_epsilon(t5);
    yy11Limitation_min.update_epsilon(t5);
    yy11Limitation_max.update_epsilon(t5);
    xx11Limitation_min.update_tolerance(t10);
    xx11Limitation_max.update_tolerance(t10);
    yy11Limitation_min.update_tolerance(t10);
    yy11Limitation_max.update_tolerance(t10);
    xx12Limitation_min.update_epsilon(t5);
    xx12Limitation_max.update_epsilon(t5);
    yy12Limitation_min.update_epsilon(t5);
    yy12Limitation_max.update_epsilon(t5);
    xx12Limitation_min.update_tolerance(t10);
    xx12Limitation_max.update_tolerance(t10);
    yy12Limitation_min.update_tolerance(t10);
    yy12Limitation_max.update_tolerance(t10);
    xx13Limitation_min.update_epsilon(t5);
    xx13Limitation_max.update_epsilon(t5);
    yy13Limitation_min.update_epsilon(t5);
    yy13Limitation_max.update_epsilon(t5);
    xx13Limitation_min.update_tolerance(t10);
    xx13Limitation_max.update_tolerance(t10);
    yy13Limitation_min.update_tolerance(t10);
    yy13Limitation_max.update_tolerance(t10);
    xx14Limitation_min.update_epsilon(t5);
    xx14Limitation_max.update_epsilon(t5);
    yy14Limitation_min.update_epsilon(t5);
    yy14Limitation_max.update_epsilon(t5);
    xx14Limitation_min.update_tolerance(t10);
    xx14Limitation_max.update_tolerance(t10);
    yy14Limitation_min.update_tolerance(t10);
    yy14Limitation_max.update_tolerance(t10);
    xx15Limitation_min.update_epsilon(t5);
    xx15Limitation_max.update_epsilon(t5);
    yy15Limitation_min.update_epsilon(t5);
    yy15Limitation_max.update_epsilon(t5);
    xx15Limitation_min.update_tolerance(t10);
    xx15Limitation_max.update_tolerance(t10);
    yy15Limitation_min.update_tolerance(t10);
    yy15Limitation_max.update_tolerance(t10);
    xx16Limitation_min.update_epsilon(t5);
    xx16Limitation_max.update_epsilon(t5);
    yy16Limitation_min.update_epsilon(t5);
    yy16Limitation_max.update_epsilon(t5);
    xx16Limitation_min.update_tolerance(t10);
    xx16Limitation_max.update_tolerance(t10);
    yy16Limitation_min.update_tolerance(t10);
    yy16Limitation_max.update_tolerance(t10);
    xx17Limitation_min.update_epsilon(t5);
    xx17Limitation_max.update_epsilon(t5);
    yy17Limitation_min.update_epsilon(t5);
    yy17Limitation_max.update_epsilon(t5);
    xx17Limitation_min.update_tolerance(t10);
    xx17Limitation_max.update_tolerance(t10);
    yy17Limitation_min.update_tolerance(t10);
    yy17Limitation_max.update_tolerance(t10);
    xx18Limitation_min.update_epsilon(t5);
    xx18Limitation_max.update_epsilon(t5);
    yy18Limitation_min.update_epsilon(t5);
    yy18Limitation_max.update_epsilon(t5);
    xx18Limitation_min.update_tolerance(t10);
    xx18Limitation_max.update_tolerance(t10);
    yy18Limitation_min.update_tolerance(t10);
    yy18Limitation_max.update_tolerance(t10);
    xx19Limitation_min.update_epsilon(t5);
    xx19Limitation_max.update_epsilon(t5);
    yy19Limitation_min.update_epsilon(t5);
    yy19Limitation_max.update_epsilon(t5);
    xx19Limitation_min.update_tolerance(t10);
    xx19Limitation_max.update_tolerance(t10);
    yy19Limitation_min.update_tolerance(t10);
    yy19Limitation_max.update_tolerance(t10);
    xx20Limitation_min.update_epsilon(t5);
    xx20Limitation_max.update_epsilon(t5);
    yy20Limitation_min.update_epsilon(t5);
    yy20Limitation_max.update_epsilon(t5);
    xx20Limitation_min.update_tolerance(t10);
    xx20Limitation_max.update_tolerance(t10);
    yy20Limitation_min.update_tolerance(t10);
    yy20Limitation_max.update_tolerance(t10);
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  ICLOCS_ContinuousMP::penalties_check_cell(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // midpoint
    real_type Q__[1], X__[80];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    X__[5] = (XL__[5]+XR__[5])/2;
    X__[6] = (XL__[6]+XR__[6])/2;
    X__[7] = (XL__[7]+XR__[7])/2;
    X__[8] = (XL__[8]+XR__[8])/2;
    X__[9] = (XL__[9]+XR__[9])/2;
    X__[10] = (XL__[10]+XR__[10])/2;
    X__[11] = (XL__[11]+XR__[11])/2;
    X__[12] = (XL__[12]+XR__[12])/2;
    X__[13] = (XL__[13]+XR__[13])/2;
    X__[14] = (XL__[14]+XR__[14])/2;
    X__[15] = (XL__[15]+XR__[15])/2;
    X__[16] = (XL__[16]+XR__[16])/2;
    X__[17] = (XL__[17]+XR__[17])/2;
    X__[18] = (XL__[18]+XR__[18])/2;
    X__[19] = (XL__[19]+XR__[19])/2;
    X__[20] = (XL__[20]+XR__[20])/2;
    X__[21] = (XL__[21]+XR__[21])/2;
    X__[22] = (XL__[22]+XR__[22])/2;
    X__[23] = (XL__[23]+XR__[23])/2;
    X__[24] = (XL__[24]+XR__[24])/2;
    X__[25] = (XL__[25]+XR__[25])/2;
    X__[26] = (XL__[26]+XR__[26])/2;
    X__[27] = (XL__[27]+XR__[27])/2;
    X__[28] = (XL__[28]+XR__[28])/2;
    X__[29] = (XL__[29]+XR__[29])/2;
    X__[30] = (XL__[30]+XR__[30])/2;
    X__[31] = (XL__[31]+XR__[31])/2;
    X__[32] = (XL__[32]+XR__[32])/2;
    X__[33] = (XL__[33]+XR__[33])/2;
    X__[34] = (XL__[34]+XR__[34])/2;
    X__[35] = (XL__[35]+XR__[35])/2;
    X__[36] = (XL__[36]+XR__[36])/2;
    X__[37] = (XL__[37]+XR__[37])/2;
    X__[38] = (XL__[38]+XR__[38])/2;
    X__[39] = (XL__[39]+XR__[39])/2;
    X__[40] = (XL__[40]+XR__[40])/2;
    X__[41] = (XL__[41]+XR__[41])/2;
    X__[42] = (XL__[42]+XR__[42])/2;
    X__[43] = (XL__[43]+XR__[43])/2;
    X__[44] = (XL__[44]+XR__[44])/2;
    X__[45] = (XL__[45]+XR__[45])/2;
    X__[46] = (XL__[46]+XR__[46])/2;
    X__[47] = (XL__[47]+XR__[47])/2;
    X__[48] = (XL__[48]+XR__[48])/2;
    X__[49] = (XL__[49]+XR__[49])/2;
    X__[50] = (XL__[50]+XR__[50])/2;
    X__[51] = (XL__[51]+XR__[51])/2;
    X__[52] = (XL__[52]+XR__[52])/2;
    X__[53] = (XL__[53]+XR__[53])/2;
    X__[54] = (XL__[54]+XR__[54])/2;
    X__[55] = (XL__[55]+XR__[55])/2;
    X__[56] = (XL__[56]+XR__[56])/2;
    X__[57] = (XL__[57]+XR__[57])/2;
    X__[58] = (XL__[58]+XR__[58])/2;
    X__[59] = (XL__[59]+XR__[59])/2;
    X__[60] = (XL__[60]+XR__[60])/2;
    X__[61] = (XL__[61]+XR__[61])/2;
    X__[62] = (XL__[62]+XR__[62])/2;
    X__[63] = (XL__[63]+XR__[63])/2;
    X__[64] = (XL__[64]+XR__[64])/2;
    X__[65] = (XL__[65]+XR__[65])/2;
    X__[66] = (XL__[66]+XR__[66])/2;
    X__[67] = (XL__[67]+XR__[67])/2;
    X__[68] = (XL__[68]+XR__[68])/2;
    X__[69] = (XL__[69]+XR__[69])/2;
    X__[70] = (XL__[70]+XR__[70])/2;
    X__[71] = (XL__[71]+XR__[71])/2;
    X__[72] = (XL__[72]+XR__[72])/2;
    X__[73] = (XL__[73]+XR__[73])/2;
    X__[74] = (XL__[74]+XR__[74])/2;
    X__[75] = (XL__[75]+XR__[75])/2;
    X__[76] = (XL__[76]+XR__[76])/2;
    X__[77] = (XL__[77]+XR__[77])/2;
    X__[78] = (XL__[78]+XR__[78])/2;
    X__[79] = (XL__[79]+XR__[79])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool res = true;
    real_type t1   = P__[iP_u1];
    res = res && u1Limitation_min.check_range(-10 - t1, m_max_penalty_value);
    res = res && u1Limitation_max.check_range(t1 - 10, m_max_penalty_value);
    real_type t4   = P__[iP_u2];
    res = res && u2Limitation_min.check_range(-10 - t4, m_max_penalty_value);
    res = res && u2Limitation_max.check_range(t4 - 10, m_max_penalty_value);
    real_type t7   = P__[iP_u3];
    res = res && u3Limitation_min.check_range(-10 - t7, m_max_penalty_value);
    res = res && u3Limitation_max.check_range(t7 - 10, m_max_penalty_value);
    real_type t10  = P__[iP_u4];
    res = res && u4Limitation_min.check_range(-10 - t10, m_max_penalty_value);
    res = res && u4Limitation_max.check_range(t10 - 10, m_max_penalty_value);
    real_type t13  = P__[iP_u5];
    res = res && u5Limitation_min.check_range(-10 - t13, m_max_penalty_value);
    res = res && u5Limitation_max.check_range(t13 - 10, m_max_penalty_value);
    real_type t16  = P__[iP_u6];
    res = res && u6Limitation_min.check_range(-10 - t16, m_max_penalty_value);
    res = res && u6Limitation_max.check_range(t16 - 10, m_max_penalty_value);
    real_type t19  = P__[iP_u7];
    res = res && u7Limitation_min.check_range(-10 - t19, m_max_penalty_value);
    res = res && u7Limitation_max.check_range(t19 - 10, m_max_penalty_value);
    real_type t22  = P__[iP_u8];
    res = res && u8Limitation_min.check_range(-10 - t22, m_max_penalty_value);
    res = res && u8Limitation_max.check_range(t22 - 10, m_max_penalty_value);
    real_type t25  = P__[iP_u9];
    res = res && u9Limitation_min.check_range(-10 - t25, m_max_penalty_value);
    res = res && u9Limitation_max.check_range(t25 - 10, m_max_penalty_value);
    real_type t28  = P__[iP_u10];
    res = res && u10Limitation_min.check_range(-10 - t28, m_max_penalty_value);
    res = res && u10Limitation_max.check_range(t28 - 10, m_max_penalty_value);
    real_type t31  = P__[iP_u11];
    res = res && u11Limitation_min.check_range(-10 - t31, m_max_penalty_value);
    res = res && u11Limitation_max.check_range(t31 - 10, m_max_penalty_value);
    real_type t34  = P__[iP_u12];
    res = res && u12Limitation_min.check_range(-10 - t34, m_max_penalty_value);
    res = res && u12Limitation_max.check_range(t34 - 10, m_max_penalty_value);
    real_type t37  = P__[iP_u13];
    res = res && u13Limitation_min.check_range(-10 - t37, m_max_penalty_value);
    res = res && u13Limitation_max.check_range(t37 - 10, m_max_penalty_value);
    real_type t40  = P__[iP_u14];
    res = res && u14Limitation_min.check_range(-10 - t40, m_max_penalty_value);
    res = res && u14Limitation_max.check_range(t40 - 10, m_max_penalty_value);
    real_type t43  = P__[iP_u15];
    res = res && u15Limitation_min.check_range(-10 - t43, m_max_penalty_value);
    res = res && u15Limitation_max.check_range(t43 - 10, m_max_penalty_value);
    real_type t46  = P__[iP_u16];
    res = res && u16Limitation_min.check_range(-10 - t46, m_max_penalty_value);
    res = res && u16Limitation_max.check_range(t46 - 10, m_max_penalty_value);
    real_type t49  = P__[iP_u17];
    res = res && u17Limitation_min.check_range(-10 - t49, m_max_penalty_value);
    res = res && u17Limitation_max.check_range(t49 - 10, m_max_penalty_value);
    real_type t52  = P__[iP_u18];
    res = res && u18Limitation_min.check_range(-10 - t52, m_max_penalty_value);
    res = res && u18Limitation_max.check_range(t52 - 10, m_max_penalty_value);
    real_type t55  = P__[iP_u19];
    res = res && u19Limitation_min.check_range(-10 - t55, m_max_penalty_value);
    res = res && u19Limitation_max.check_range(t55 - 10, m_max_penalty_value);
    real_type t58  = P__[iP_u20];
    res = res && u20Limitation_min.check_range(-10 - t58, m_max_penalty_value);
    res = res && u20Limitation_max.check_range(t58 - 10, m_max_penalty_value);
    real_type t61  = ModelPars[iM_xy_bound];
    real_type t62  = X__[iX_xx1];
    res = res && xx1Limitation_min.check_range(-t61 - t62, m_max_penalty_value);
    res = res && xx1Limitation_max.check_range(t62 - t61, m_max_penalty_value);
    real_type t65  = X__[iX_yy1];
    res = res && yy1Limitation_min.check_range(-t61 - t65, m_max_penalty_value);
    res = res && yy1Limitation_max.check_range(t65 - t61, m_max_penalty_value);
    real_type t68  = X__[iX_xx2];
    res = res && xx2Limitation_min.check_range(-t61 - t68, m_max_penalty_value);
    res = res && xx2Limitation_max.check_range(t68 - t61, m_max_penalty_value);
    real_type t71  = X__[iX_yy2];
    res = res && yy2Limitation_min.check_range(-t61 - t71, m_max_penalty_value);
    res = res && yy2Limitation_max.check_range(t71 - t61, m_max_penalty_value);
    real_type t74  = X__[iX_xx3];
    res = res && xx3Limitation_min.check_range(-t61 - t74, m_max_penalty_value);
    res = res && xx3Limitation_max.check_range(t74 - t61, m_max_penalty_value);
    real_type t77  = X__[iX_yy3];
    res = res && yy3Limitation_min.check_range(-t61 - t77, m_max_penalty_value);
    res = res && yy3Limitation_max.check_range(t77 - t61, m_max_penalty_value);
    real_type t80  = X__[iX_xx4];
    res = res && xx4Limitation_min.check_range(-t61 - t80, m_max_penalty_value);
    res = res && xx4Limitation_max.check_range(t80 - t61, m_max_penalty_value);
    real_type t83  = X__[iX_yy4];
    res = res && yy4Limitation_min.check_range(-t61 - t83, m_max_penalty_value);
    res = res && yy4Limitation_max.check_range(t83 - t61, m_max_penalty_value);
    real_type t86  = X__[iX_xx5];
    res = res && xx5Limitation_min.check_range(-t61 - t86, m_max_penalty_value);
    res = res && xx5Limitation_max.check_range(t86 - t61, m_max_penalty_value);
    real_type t89  = X__[iX_yy5];
    res = res && yy5Limitation_min.check_range(-t61 - t89, m_max_penalty_value);
    res = res && yy5Limitation_max.check_range(t89 - t61, m_max_penalty_value);
    real_type t92  = X__[iX_xx6];
    res = res && xx6Limitation_min.check_range(-t61 - t92, m_max_penalty_value);
    res = res && xx6Limitation_max.check_range(t92 - t61, m_max_penalty_value);
    real_type t95  = X__[iX_yy6];
    res = res && yy6Limitation_min.check_range(-t61 - t95, m_max_penalty_value);
    res = res && yy6Limitation_max.check_range(t95 - t61, m_max_penalty_value);
    real_type t98  = X__[iX_xx7];
    res = res && xx7Limitation_min.check_range(-t61 - t98, m_max_penalty_value);
    res = res && xx7Limitation_max.check_range(t98 - t61, m_max_penalty_value);
    real_type t101 = X__[iX_yy7];
    res = res && yy7Limitation_min.check_range(-t61 - t101, m_max_penalty_value);
    res = res && yy7Limitation_max.check_range(t101 - t61, m_max_penalty_value);
    real_type t104 = X__[iX_xx8];
    res = res && xx8Limitation_min.check_range(-t61 - t104, m_max_penalty_value);
    res = res && xx8Limitation_max.check_range(t104 - t61, m_max_penalty_value);
    real_type t107 = X__[iX_yy8];
    res = res && yy8Limitation_min.check_range(-t61 - t107, m_max_penalty_value);
    res = res && yy8Limitation_max.check_range(t107 - t61, m_max_penalty_value);
    real_type t110 = X__[iX_xx9];
    res = res && xx9Limitation_min.check_range(-t61 - t110, m_max_penalty_value);
    res = res && xx9Limitation_max.check_range(t110 - t61, m_max_penalty_value);
    real_type t113 = X__[iX_yy9];
    res = res && yy9Limitation_min.check_range(-t61 - t113, m_max_penalty_value);
    res = res && yy9Limitation_max.check_range(t113 - t61, m_max_penalty_value);
    real_type t116 = X__[iX_xx10];
    res = res && xx10Limitation_min.check_range(-t61 - t116, m_max_penalty_value);
    res = res && xx10Limitation_max.check_range(t116 - t61, m_max_penalty_value);
    real_type t119 = X__[iX_yy10];
    res = res && yy10Limitation_min.check_range(-t61 - t119, m_max_penalty_value);
    res = res && yy10Limitation_max.check_range(t119 - t61, m_max_penalty_value);
    real_type t122 = X__[iX_xx11];
    res = res && xx11Limitation_min.check_range(-t61 - t122, m_max_penalty_value);
    res = res && xx11Limitation_max.check_range(t122 - t61, m_max_penalty_value);
    real_type t125 = X__[iX_yy11];
    res = res && yy11Limitation_min.check_range(-t61 - t125, m_max_penalty_value);
    res = res && yy11Limitation_max.check_range(t125 - t61, m_max_penalty_value);
    real_type t128 = X__[iX_xx12];
    res = res && xx12Limitation_min.check_range(-t61 - t128, m_max_penalty_value);
    res = res && xx12Limitation_max.check_range(t128 - t61, m_max_penalty_value);
    real_type t131 = X__[iX_yy12];
    res = res && yy12Limitation_min.check_range(-t61 - t131, m_max_penalty_value);
    res = res && yy12Limitation_max.check_range(t131 - t61, m_max_penalty_value);
    real_type t134 = X__[iX_xx13];
    res = res && xx13Limitation_min.check_range(-t61 - t134, m_max_penalty_value);
    res = res && xx13Limitation_max.check_range(t134 - t61, m_max_penalty_value);
    real_type t137 = X__[iX_yy13];
    res = res && yy13Limitation_min.check_range(-t61 - t137, m_max_penalty_value);
    res = res && yy13Limitation_max.check_range(t137 - t61, m_max_penalty_value);
    real_type t140 = X__[iX_xx14];
    res = res && xx14Limitation_min.check_range(-t61 - t140, m_max_penalty_value);
    res = res && xx14Limitation_max.check_range(t140 - t61, m_max_penalty_value);
    real_type t143 = X__[iX_yy14];
    res = res && yy14Limitation_min.check_range(-t61 - t143, m_max_penalty_value);
    res = res && yy14Limitation_max.check_range(t143 - t61, m_max_penalty_value);
    real_type t146 = X__[iX_xx15];
    res = res && xx15Limitation_min.check_range(-t61 - t146, m_max_penalty_value);
    res = res && xx15Limitation_max.check_range(t146 - t61, m_max_penalty_value);
    real_type t149 = X__[iX_yy15];
    res = res && yy15Limitation_min.check_range(-t61 - t149, m_max_penalty_value);
    res = res && yy15Limitation_max.check_range(t149 - t61, m_max_penalty_value);
    real_type t152 = X__[iX_xx16];
    res = res && xx16Limitation_min.check_range(-t61 - t152, m_max_penalty_value);
    res = res && xx16Limitation_max.check_range(t152 - t61, m_max_penalty_value);
    real_type t155 = X__[iX_yy16];
    res = res && yy16Limitation_min.check_range(-t61 - t155, m_max_penalty_value);
    res = res && yy16Limitation_max.check_range(t155 - t61, m_max_penalty_value);
    real_type t158 = X__[iX_xx17];
    res = res && xx17Limitation_min.check_range(-t61 - t158, m_max_penalty_value);
    res = res && xx17Limitation_max.check_range(t158 - t61, m_max_penalty_value);
    real_type t161 = X__[iX_yy17];
    res = res && yy17Limitation_min.check_range(-t61 - t161, m_max_penalty_value);
    res = res && yy17Limitation_max.check_range(t161 - t61, m_max_penalty_value);
    real_type t164 = X__[iX_xx18];
    res = res && xx18Limitation_min.check_range(-t61 - t164, m_max_penalty_value);
    res = res && xx18Limitation_max.check_range(t164 - t61, m_max_penalty_value);
    real_type t167 = X__[iX_yy18];
    res = res && yy18Limitation_min.check_range(-t61 - t167, m_max_penalty_value);
    res = res && yy18Limitation_max.check_range(t167 - t61, m_max_penalty_value);
    real_type t170 = X__[iX_xx19];
    res = res && xx19Limitation_min.check_range(-t61 - t170, m_max_penalty_value);
    res = res && xx19Limitation_max.check_range(t170 - t61, m_max_penalty_value);
    real_type t173 = X__[iX_yy19];
    res = res && yy19Limitation_min.check_range(-t61 - t173, m_max_penalty_value);
    res = res && yy19Limitation_max.check_range(t173 - t61, m_max_penalty_value);
    real_type t176 = X__[iX_xx20];
    res = res && xx20Limitation_min.check_range(-t61 - t176, m_max_penalty_value);
    res = res && xx20Limitation_max.check_range(t176 - t61, m_max_penalty_value);
    real_type t179 = X__[iX_yy20];
    res = res && yy20Limitation_min.check_range(-t61 - t179, m_max_penalty_value);
    res = res && yy20Limitation_max.check_range(t179 - t61, m_max_penalty_value);
    return res;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS_ContinuousMP::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x4];
    real_type t2   = t1 * t1;
    real_type t4   = X__[iX_x5];
    real_type t5   = t4 * t4;
    real_type t7   = X__[iX_x6];
    real_type t8   = t7 * t7;
    real_type t10  = X__[iX_x7];
    real_type t11  = t10 * t10;
    real_type t13  = X__[iX_x8];
    real_type t14  = t13 * t13;
    real_type t16  = X__[iX_x9];
    real_type t17  = t16 * t16;
    real_type t19  = X__[iX_x10];
    real_type t20  = t19 * t19;
    real_type t22  = X__[iX_x11];
    real_type t23  = t22 * t22;
    real_type t25  = X__[iX_x12];
    real_type t26  = t25 * t25;
    real_type t28  = X__[iX_x13];
    real_type t29  = t28 * t28;
    real_type t31  = X__[iX_x14];
    real_type t32  = t31 * t31;
    real_type t34  = X__[iX_x15];
    real_type t35  = t34 * t34;
    real_type t37  = X__[iX_x16];
    real_type t38  = t37 * t37;
    real_type t40  = X__[iX_x17];
    real_type t41  = t40 * t40;
    real_type t43  = X__[iX_x18];
    real_type t44  = t43 * t43;
    real_type t46  = 17 * t2 + 16 * t5 + 15 * t8 + 14 * t11 + 13 * t14 + 12 * t17 + 11 * t20 + 10 * t23 + 9 * t26 + 8 * t29 + 7 * t32 + 6 * t35 + 5 * t38 + 4 * t41 + 3 * t44;
    real_type t47  = X__[iX_x19];
    real_type t48  = t47 * t47;
    real_type t50  = X__[iX_x20];
    real_type t51  = t50 * t50;
    real_type t52  = X__[iX_y1];
    real_type t53  = t52 * t52;
    real_type t55  = X__[iX_y2];
    real_type t56  = t55 * t55;
    real_type t58  = X__[iX_y3];
    real_type t59  = t58 * t58;
    real_type t61  = X__[iX_y4];
    real_type t62  = t61 * t61;
    real_type t64  = X__[iX_y12];
    real_type t65  = t64 * t64;
    real_type t67  = X__[iX_y13];
    real_type t68  = t67 * t67;
    real_type t70  = X__[iX_y14];
    real_type t71  = t70 * t70;
    real_type t73  = X__[iX_y15];
    real_type t74  = t73 * t73;
    real_type t76  = X__[iX_y16];
    real_type t77  = t76 * t76;
    real_type t79  = X__[iX_y17];
    real_type t80  = t79 * t79;
    real_type t82  = X__[iX_y18];
    real_type t83  = t82 * t82;
    real_type t85  = X__[iX_y19];
    real_type t86  = t85 * t85;
    real_type t88  = X__[iX_y20];
    real_type t89  = t88 * t88;
    real_type t90  = 2 * t48 + t51 + 20 * t53 + 19 * t56 + 18 * t59 + 17 * t62 + 9 * t65 + 8 * t68 + 7 * t71 + 6 * t74 + 5 * t77 + 4 * t80 + 3 * t83 + 2 * t86 + t89;
    real_type t93  = X__[iX_y8];
    real_type t96  = X__[iX_y9];
    real_type t99  = X__[iX_y10];
    real_type t102 = X__[iX_y11];
    real_type t106 = X__[iX_x1];
    real_type t107 = t106 * t106;
    real_type t109 = X__[iX_x2];
    real_type t110 = t109 * t109;
    real_type t112 = X__[iX_x3];
    real_type t113 = t112 * t112;
    real_type t115 = X__[iX_y5];
    real_type t116 = t115 * t115;
    real_type t118 = X__[iX_y6];
    real_type t119 = t118 * t118;
    real_type t121 = X__[iX_y7];
    real_type t122 = t121 * t121;
    real_type t124 = t93 * t93;
    real_type t126 = t96 * t96;
    real_type t128 = t99 * t99;
    real_type t130 = t102 * t102;
    real_type t132 = t102 * L__[iL_lambda11__xo] + t64 * L__[iL_lambda12__xo] + t93 * L__[iL_lambda8__xo] + t96 * L__[iL_lambda9__xo] + t99 * L__[iL_lambda10__xo] + 20 * t107 + 19 * t110 + 18 * t113 + 16 * t116 + 15 * t119 + 14 * t122 + 13 * t124 + 12 * t126 + 11 * t128 + 10 * t130;
    real_type t151 = sin(X__[iX_xx14]);
    real_type t153 = P__[iP_u14];
    real_type t157 = sin(t31);
    real_type t162 = sin(X__[iX_xx15]);
    real_type t164 = P__[iP_u15];
    real_type t168 = sin(t34);
    real_type t173 = sin(X__[iX_xx16]);
    real_type t175 = P__[iP_u16];
    real_type t179 = sin(t37);
    real_type t183 = sin(t106);
    real_type t184 = P__[iP_u1];
    real_type t187 = t67 * L__[iL_lambda13__xo] + t70 * L__[iL_lambda14__xo] + t73 * L__[iL_lambda15__xo] + t76 * L__[iL_lambda16__xo] + t79 * L__[iL_lambda17__xo] + t82 * L__[iL_lambda18__xo] + t85 * L__[iL_lambda19__xo] + t88 * L__[iL_lambda20__xo] + (0.2e0 * t151 + t153) * L__[iL_lambda74__xo] + (t157 + t153) * L__[iL_lambda34__xo] + (0.2e0 * t162 + t164) * L__[iL_lambda75__xo] + (t168 + t164) * L__[iL_lambda35__xo] + (0.2e0 * t173 + t175) * L__[iL_lambda76__xo] + (t179 + t175) * L__[iL_lambda36__xo] + (t183 + t184) * L__[iL_lambda21__xo];
    real_type t192 = sin(X__[iX_xx1]);
    real_type t197 = sin(t109);
    real_type t198 = P__[iP_u2];
    real_type t203 = sin(X__[iX_xx2]);
    real_type t208 = sin(t112);
    real_type t209 = P__[iP_u3];
    real_type t214 = sin(X__[iX_xx3]);
    real_type t219 = sin(t1);
    real_type t220 = P__[iP_u4];
    real_type t225 = sin(X__[iX_xx4]);
    real_type t230 = sin(t4);
    real_type t231 = P__[iP_u5];
    real_type t236 = sin(X__[iX_xx5]);
    real_type t241 = sin(t7);
    real_type t242 = P__[iP_u6];
    real_type t247 = sin(X__[iX_xx6]);
    real_type t254 = Q__[iQ_zeta];
    real_type t256 = sin(t254 + 6);
    real_type t264 = sin(t254 + 7);
    real_type t272 = sin(t254 + 8);
    real_type t280 = sin(t254 + 9);
    real_type t284 = (0.2e0 * t192 + t184) * L__[iL_lambda61__xo] + (t197 + t198) * L__[iL_lambda22__xo] + (0.2e0 * t203 + t198) * L__[iL_lambda62__xo] + (t208 + t209) * L__[iL_lambda23__xo] + (0.2e0 * t214 + t209) * L__[iL_lambda63__xo] + (t219 + t220) * L__[iL_lambda24__xo] + (0.2e0 * t225 + t220) * L__[iL_lambda64__xo] + (t230 + t231) * L__[iL_lambda25__xo] + (0.2e0 * t236 + t231) * L__[iL_lambda65__xo] + (t241 + t242) * L__[iL_lambda26__xo] + (0.2e0 * t247 + t242) * L__[iL_lambda66__xo] + (0.12e1 * X__[iX_yy7] + 0.1e0 * t256) * L__[iL_lambda47__xo] + (0.12e1 * X__[iX_yy8] + 0.1e0 * t264) * L__[iL_lambda48__xo] + (0.12e1 * X__[iX_yy9] + 0.1e0 * t272) * L__[iL_lambda49__xo] + (0.12e1 * X__[iX_yy10] + 0.1e0 * t280) * L__[iL_lambda50__xo];
    real_type t289 = sin(t254 + 10);
    real_type t297 = sin(t254 + 11);
    real_type t305 = sin(t254 + 12);
    real_type t327 = sin(t254 + 3);
    real_type t335 = sin(t254 + 4);
    real_type t343 = sin(t254 + 5);
    real_type t348 = sin(t28);
    real_type t349 = P__[iP_u13];
    real_type t354 = sin(X__[iX_xx17]);
    real_type t356 = P__[iP_u17];
    real_type t359 = (0.12e1 * X__[iX_yy11] + 0.1e0 * t289) * L__[iL_lambda51__xo] + (0.12e1 * X__[iX_yy12] + 0.1e0 * t297) * L__[iL_lambda52__xo] + (0.12e1 * X__[iX_yy13] + 0.1e0 * t305) * L__[iL_lambda53__xo] + t52 * L__[iL_lambda1__xo] + t55 * L__[iL_lambda2__xo] + t58 * L__[iL_lambda3__xo] + t61 * L__[iL_lambda4__xo] + t115 * L__[iL_lambda5__xo] + t118 * L__[iL_lambda6__xo] + t121 * L__[iL_lambda7__xo] + (0.12e1 * X__[iX_yy4] + 0.1e0 * t327) * L__[iL_lambda44__xo] + (0.12e1 * X__[iX_yy5] + 0.1e0 * t335) * L__[iL_lambda45__xo] + (0.12e1 * X__[iX_yy6] + 0.1e0 * t343) * L__[iL_lambda46__xo] + (t348 + t349) * L__[iL_lambda33__xo] + (0.2e0 * t354 + t356) * L__[iL_lambda77__xo];
    real_type t362 = sin(t40);
    real_type t367 = sin(X__[iX_xx18]);
    real_type t369 = P__[iP_u18];
    real_type t373 = sin(t43);
    real_type t378 = sin(X__[iX_xx19]);
    real_type t380 = P__[iP_u19];
    real_type t384 = sin(t47);
    real_type t389 = sin(X__[iX_xx20]);
    real_type t391 = P__[iP_u20];
    real_type t395 = sin(t50);
    real_type t402 = sin(t254 + 13);
    real_type t410 = sin(t254 + 14);
    real_type t418 = sin(t254 + 15);
    real_type t426 = sin(t254 + 16);
    real_type t434 = sin(t254 + 17);
    real_type t442 = sin(t254 + 18);
    real_type t450 = sin(t254 + 19);
    real_type t457 = sin(t254);
    real_type t461 = (t362 + t356) * L__[iL_lambda37__xo] + (0.2e0 * t367 + t369) * L__[iL_lambda78__xo] + (t373 + t369) * L__[iL_lambda38__xo] + (0.2e0 * t378 + t380) * L__[iL_lambda79__xo] + (t384 + t380) * L__[iL_lambda39__xo] + (0.2e0 * t389 + t391) * L__[iL_lambda80__xo] + (t395 + t391) * L__[iL_lambda40__xo] + (0.12e1 * X__[iX_yy14] + 0.1e0 * t402) * L__[iL_lambda54__xo] + (0.12e1 * X__[iX_yy15] + 0.1e0 * t410) * L__[iL_lambda55__xo] + (0.12e1 * X__[iX_yy16] + 0.1e0 * t418) * L__[iL_lambda56__xo] + (0.12e1 * X__[iX_yy17] + 0.1e0 * t426) * L__[iL_lambda57__xo] + (0.12e1 * X__[iX_yy18] + 0.1e0 * t434) * L__[iL_lambda58__xo] + (0.12e1 * X__[iX_yy19] + 0.1e0 * t442) * L__[iL_lambda59__xo] + (0.12e1 * X__[iX_yy20] + 0.1e0 * t450) * L__[iL_lambda60__xo] + (0.12e1 * X__[iX_yy1] + 0.1e0 * t457) * L__[iL_lambda41__xo];
    real_type t466 = sin(t254 + 1);
    real_type t474 = sin(t254 + 2);
    real_type t480 = sin(X__[iX_xx12]);
    real_type t482 = P__[iP_u12];
    real_type t486 = sin(t25);
    real_type t491 = sin(X__[iX_xx13]);
    real_type t497 = sin(X__[iX_xx7]);
    real_type t499 = P__[iP_u7];
    real_type t503 = sin(t10);
    real_type t508 = sin(X__[iX_xx8]);
    real_type t510 = P__[iP_u8];
    real_type t514 = sin(t13);
    real_type t519 = sin(X__[iX_xx9]);
    real_type t521 = P__[iP_u9];
    real_type t525 = sin(t16);
    real_type t530 = sin(X__[iX_xx10]);
    real_type t532 = P__[iP_u10];
    real_type t536 = sin(t19);
    real_type t541 = sin(X__[iX_xx11]);
    real_type t543 = P__[iP_u11];
    real_type t547 = sin(t22);
    real_type t550 = (0.12e1 * X__[iX_yy2] + 0.1e0 * t466) * L__[iL_lambda42__xo] + (0.12e1 * X__[iX_yy3] + 0.1e0 * t474) * L__[iL_lambda43__xo] + (0.2e0 * t480 + t482) * L__[iL_lambda72__xo] + (t486 + t482) * L__[iL_lambda32__xo] + (0.2e0 * t491 + t349) * L__[iL_lambda73__xo] + (0.2e0 * t497 + t499) * L__[iL_lambda67__xo] + (t503 + t499) * L__[iL_lambda27__xo] + (0.2e0 * t508 + t510) * L__[iL_lambda68__xo] + (t514 + t510) * L__[iL_lambda28__xo] + (0.2e0 * t519 + t521) * L__[iL_lambda69__xo] + (t525 + t521) * L__[iL_lambda29__xo] + (0.2e0 * t530 + t532) * L__[iL_lambda70__xo] + (t536 + t532) * L__[iL_lambda30__xo] + (0.2e0 * t541 + t543) * L__[iL_lambda71__xo] + (t547 + t543) * L__[iL_lambda31__xo];
    real_type result__ = t46 + t90 + t132 + t187 + t284 + t359 + t461 + t550;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  ICLOCS_ContinuousMP::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t2   = X__[iX_yy19];
    real_type t4   = yy19Limitation_min(-t1 - t2);
    real_type t6   = yy19Limitation_max(t2 - t1);
    real_type t7   = X__[iX_yy20];
    real_type t9   = yy20Limitation_min(-t1 - t7);
    real_type t11  = yy20Limitation_max(t7 - t1);
    real_type t12  = X__[iX_yy17];
    real_type t14  = yy17Limitation_min(-t1 - t12);
    real_type t16  = yy17Limitation_max(t12 - t1);
    real_type t17  = X__[iX_yy18];
    real_type t19  = yy18Limitation_min(-t1 - t17);
    real_type t21  = yy18Limitation_max(t17 - t1);
    real_type t22  = X__[iX_yy15];
    real_type t24  = yy15Limitation_min(-t1 - t22);
    real_type t26  = yy15Limitation_max(t22 - t1);
    real_type t27  = X__[iX_yy16];
    real_type t29  = yy16Limitation_min(-t1 - t27);
    real_type t31  = yy16Limitation_max(t27 - t1);
    real_type t32  = X__[iX_yy13];
    real_type t34  = yy13Limitation_min(-t1 - t32);
    real_type t36  = yy13Limitation_max(t32 - t1);
    real_type t37  = X__[iX_yy14];
    real_type t39  = yy14Limitation_min(-t1 - t37);
    real_type t40  = t4 + t6 + t9 + t11 + t14 + t16 + t19 + t21 + t24 + t26 + t29 + t31 + t34 + t36 + t39;
    real_type t42  = yy14Limitation_max(t37 - t1);
    real_type t43  = P__[iP_u12];
    real_type t45  = u12Limitation_min(-10 - t43);
    real_type t47  = u12Limitation_max(t43 - 10);
    real_type t48  = P__[iP_u13];
    real_type t50  = u13Limitation_min(-10 - t48);
    real_type t52  = u13Limitation_max(t48 - 10);
    real_type t53  = P__[iP_u14];
    real_type t55  = u14Limitation_min(-10 - t53);
    real_type t56  = P__[iP_u10];
    real_type t58  = u10Limitation_max(t56 - 10);
    real_type t60  = u10Limitation_min(-10 - t56);
    real_type t61  = P__[iP_u11];
    real_type t63  = u11Limitation_min(-10 - t61);
    real_type t65  = u11Limitation_max(t61 - 10);
    real_type t66  = P__[iP_u7];
    real_type t68  = u7Limitation_max(t66 - 10);
    real_type t69  = P__[iP_u8];
    real_type t71  = u8Limitation_min(-10 - t69);
    real_type t73  = u8Limitation_max(t69 - 10);
    real_type t74  = P__[iP_u9];
    real_type t76  = u9Limitation_min(-10 - t74);
    real_type t78  = u9Limitation_max(t74 - 10);
    real_type t79  = t42 + t45 + t47 + t50 + t52 + t55 + t58 + t60 + t63 + t65 + t68 + t71 + t73 + t76 + t78;
    real_type t81  = P__[iP_u5];
    real_type t83  = u5Limitation_min(-10 - t81);
    real_type t85  = u5Limitation_max(t81 - 10);
    real_type t86  = P__[iP_u6];
    real_type t88  = u6Limitation_min(-10 - t86);
    real_type t90  = u6Limitation_max(t86 - 10);
    real_type t92  = u7Limitation_min(-10 - t66);
    real_type t93  = P__[iP_u2];
    real_type t95  = u2Limitation_max(t93 - 10);
    real_type t96  = P__[iP_u3];
    real_type t98  = u3Limitation_min(-10 - t96);
    real_type t100 = u3Limitation_max(t96 - 10);
    real_type t101 = P__[iP_u4];
    real_type t103 = u4Limitation_min(-10 - t101);
    real_type t105 = u4Limitation_max(t101 - 10);
    real_type t106 = P__[iP_u1];
    real_type t108 = u1Limitation_min(-10 - t106);
    real_type t110 = u1Limitation_max(t106 - 10);
    real_type t112 = u2Limitation_min(-10 - t93);
    real_type t113 = X__[iX_yy11];
    real_type t115 = yy11Limitation_min(-t1 - t113);
    real_type t117 = yy11Limitation_max(t113 - t1);
    real_type t118 = t83 + t85 + t88 + t90 + t92 + t95 + t98 + t100 + t103 + t105 + t108 + t110 + t112 + t115 + t117;
    real_type t119 = X__[iX_yy12];
    real_type t121 = yy12Limitation_min(-t1 - t119);
    real_type t123 = yy12Limitation_max(t119 - t1);
    real_type t124 = X__[iX_yy9];
    real_type t126 = yy9Limitation_min(-t1 - t124);
    real_type t128 = yy9Limitation_max(t124 - t1);
    real_type t129 = X__[iX_yy10];
    real_type t131 = yy10Limitation_min(-t1 - t129);
    real_type t133 = yy10Limitation_max(t129 - t1);
    real_type t134 = X__[iX_yy7];
    real_type t136 = yy7Limitation_min(-t1 - t134);
    real_type t138 = yy7Limitation_max(t134 - t1);
    real_type t139 = X__[iX_yy8];
    real_type t141 = yy8Limitation_min(-t1 - t139);
    real_type t143 = yy8Limitation_max(t139 - t1);
    real_type t144 = X__[iX_yy5];
    real_type t146 = yy5Limitation_min(-t1 - t144);
    real_type t148 = yy5Limitation_max(t144 - t1);
    real_type t149 = X__[iX_yy6];
    real_type t151 = yy6Limitation_min(-t1 - t149);
    real_type t153 = yy6Limitation_max(t149 - t1);
    real_type t154 = X__[iX_yy3];
    real_type t156 = yy3Limitation_min(-t1 - t154);
    real_type t157 = t121 + t123 + t126 + t128 + t131 + t133 + t136 + t138 + t141 + t143 + t146 + t148 + t151 + t153 + t156;
    real_type t161 = yy3Limitation_max(t154 - t1);
    real_type t162 = X__[iX_yy4];
    real_type t164 = yy4Limitation_min(-t1 - t162);
    real_type t166 = yy4Limitation_max(t162 - t1);
    real_type t167 = X__[iX_xx7];
    real_type t169 = xx7Limitation_max(t167 - t1);
    real_type t170 = X__[iX_xx8];
    real_type t172 = xx8Limitation_min(-t1 - t170);
    real_type t174 = xx8Limitation_max(t170 - t1);
    real_type t175 = X__[iX_xx9];
    real_type t177 = xx9Limitation_min(-t1 - t175);
    real_type t178 = P__[iP_u19];
    real_type t180 = u19Limitation_max(t178 - 10);
    real_type t181 = P__[iP_u20];
    real_type t183 = u20Limitation_min(-10 - t181);
    real_type t185 = u20Limitation_max(t181 - 10);
    real_type t187 = xx7Limitation_min(-t1 - t167);
    real_type t188 = P__[iP_u17];
    real_type t190 = u17Limitation_min(-10 - t188);
    real_type t192 = u17Limitation_max(t188 - 10);
    real_type t193 = P__[iP_u18];
    real_type t195 = u18Limitation_min(-10 - t193);
    real_type t197 = u18Limitation_max(t193 - 10);
    real_type t198 = t161 + t164 + t166 + t169 + t172 + t174 + t177 + t180 + t183 + t185 + t187 + t190 + t192 + t195 + t197;
    real_type t200 = u19Limitation_min(-10 - t178);
    real_type t202 = u14Limitation_max(t53 - 10);
    real_type t203 = P__[iP_u15];
    real_type t205 = u15Limitation_min(-10 - t203);
    real_type t207 = u15Limitation_max(t203 - 10);
    real_type t208 = P__[iP_u16];
    real_type t210 = u16Limitation_min(-10 - t208);
    real_type t212 = u16Limitation_max(t208 - 10);
    real_type t213 = X__[iX_yy1];
    real_type t215 = yy1Limitation_min(-t1 - t213);
    real_type t217 = yy1Limitation_max(t213 - t1);
    real_type t218 = X__[iX_yy2];
    real_type t220 = yy2Limitation_min(-t1 - t218);
    real_type t222 = yy2Limitation_max(t218 - t1);
    real_type t223 = X__[iX_xx19];
    real_type t225 = xx19Limitation_min(-t1 - t223);
    real_type t227 = xx19Limitation_max(t223 - t1);
    real_type t228 = X__[iX_xx20];
    real_type t230 = xx20Limitation_min(-t1 - t228);
    real_type t232 = xx20Limitation_max(t228 - t1);
    real_type t233 = X__[iX_xx17];
    real_type t235 = xx17Limitation_min(-t1 - t233);
    real_type t236 = t200 + t202 + t205 + t207 + t210 + t212 + t215 + t217 + t220 + t222 + t225 + t227 + t230 + t232 + t235;
    real_type t239 = xx17Limitation_max(t233 - t1);
    real_type t240 = X__[iX_xx18];
    real_type t242 = xx18Limitation_min(-t1 - t240);
    real_type t244 = xx18Limitation_max(t240 - t1);
    real_type t245 = X__[iX_xx15];
    real_type t247 = xx15Limitation_min(-t1 - t245);
    real_type t249 = xx15Limitation_max(t245 - t1);
    real_type t250 = X__[iX_xx16];
    real_type t252 = xx16Limitation_min(-t1 - t250);
    real_type t254 = xx16Limitation_max(t250 - t1);
    real_type t255 = X__[iX_xx13];
    real_type t257 = xx13Limitation_min(-t1 - t255);
    real_type t259 = xx13Limitation_max(t255 - t1);
    real_type t260 = X__[iX_xx14];
    real_type t262 = xx14Limitation_min(-t1 - t260);
    real_type t264 = xx14Limitation_max(t260 - t1);
    real_type t265 = X__[iX_xx11];
    real_type t267 = xx11Limitation_min(-t1 - t265);
    real_type t269 = xx11Limitation_max(t265 - t1);
    real_type t270 = X__[iX_xx12];
    real_type t272 = xx12Limitation_min(-t1 - t270);
    real_type t274 = xx12Limitation_max(t270 - t1);
    real_type t275 = t239 + t242 + t244 + t247 + t249 + t252 + t254 + t257 + t259 + t262 + t264 + t267 + t269 + t272 + t274;
    real_type t277 = xx9Limitation_max(t175 - t1);
    real_type t278 = X__[iX_xx10];
    real_type t280 = xx10Limitation_min(-t1 - t278);
    real_type t282 = xx10Limitation_max(t278 - t1);
    real_type t283 = X__[iX_xx5];
    real_type t285 = xx5Limitation_min(-t1 - t283);
    real_type t287 = xx5Limitation_max(t283 - t1);
    real_type t288 = X__[iX_xx6];
    real_type t290 = xx6Limitation_min(-t1 - t288);
    real_type t292 = xx6Limitation_max(t288 - t1);
    real_type t293 = X__[iX_xx1];
    real_type t295 = xx1Limitation_min(-t1 - t293);
    real_type t297 = xx1Limitation_max(t293 - t1);
    real_type t298 = X__[iX_xx2];
    real_type t300 = xx2Limitation_min(-t1 - t298);
    real_type t302 = xx2Limitation_max(t298 - t1);
    real_type t303 = X__[iX_xx3];
    real_type t305 = xx3Limitation_min(-t1 - t303);
    real_type t307 = xx3Limitation_max(t303 - t1);
    real_type t308 = X__[iX_xx4];
    real_type t310 = xx4Limitation_min(-t1 - t308);
    real_type t312 = xx4Limitation_max(t308 - t1);
    real_type t313 = t277 + t280 + t282 + t285 + t287 + t290 + t292 + t295 + t297 + t300 + t302 + t305 + t307 + t310 + t312;
    real_type result__ = t40 + t79 + t118 + t157 + t198 + t236 + t275 + t313;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  ICLOCS_ContinuousMP::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x17] * X__[iX_x17];
    real_type t5   = X__[iX_x18] * X__[iX_x18];
    real_type t8   = X__[iX_y3] * X__[iX_y3];
    real_type t11  = X__[iX_y4] * X__[iX_y4];
    real_type t14  = X__[iX_y5] * X__[iX_y5];
    real_type t17  = X__[iX_y6] * X__[iX_y6];
    real_type t20  = X__[iX_y7] * X__[iX_y7];
    real_type t23  = X__[iX_y8] * X__[iX_y8];
    real_type t26  = X__[iX_y9] * X__[iX_y9];
    real_type t29  = X__[iX_y10] * X__[iX_y10];
    real_type t32  = X__[iX_y11] * X__[iX_y11];
    real_type t35  = X__[iX_y12] * X__[iX_y12];
    real_type t38  = X__[iX_y13] * X__[iX_y13];
    real_type t41  = X__[iX_y14] * X__[iX_y14];
    real_type t44  = X__[iX_y15] * X__[iX_y15];
    real_type t47  = X__[iX_y16] * X__[iX_y16];
    real_type t50  = X__[iX_y17] * X__[iX_y17];
    real_type t53  = X__[iX_y18] * X__[iX_y18];
    real_type t56  = X__[iX_y19] * X__[iX_y19];
    real_type t59  = X__[iX_y20] * X__[iX_y20];
    real_type t60  = 4 * t2 + 3 * t5 + 18 * t8 + 17 * t11 + 16 * t14 + 15 * t17 + 14 * t20 + 13 * t23 + 12 * t26 + 11 * t29 + 10 * t32 + 9 * t35 + 8 * t38 + 7 * t41 + 6 * t44 + 5 * t47 + 4 * t50 + 3 * t53 + 2 * t56 + t59;
    real_type t62  = X__[iX_x1] * X__[iX_x1];
    real_type t65  = X__[iX_x2] * X__[iX_x2];
    real_type t68  = X__[iX_x3] * X__[iX_x3];
    real_type t71  = X__[iX_x4] * X__[iX_x4];
    real_type t74  = X__[iX_x5] * X__[iX_x5];
    real_type t77  = X__[iX_x6] * X__[iX_x6];
    real_type t80  = X__[iX_x7] * X__[iX_x7];
    real_type t83  = X__[iX_x8] * X__[iX_x8];
    real_type t86  = X__[iX_x9] * X__[iX_x9];
    real_type t89  = X__[iX_x10] * X__[iX_x10];
    real_type t92  = X__[iX_x11] * X__[iX_x11];
    real_type t95  = X__[iX_x12] * X__[iX_x12];
    real_type t98  = X__[iX_x13] * X__[iX_x13];
    real_type t101 = X__[iX_x14] * X__[iX_x14];
    real_type t104 = X__[iX_x15] * X__[iX_x15];
    real_type t107 = X__[iX_x16] * X__[iX_x16];
    real_type t110 = X__[iX_x19] * X__[iX_x19];
    real_type t113 = X__[iX_x20] * X__[iX_x20];
    real_type t115 = X__[iX_y1] * X__[iX_y1];
    real_type t118 = X__[iX_y2] * X__[iX_y2];
    real_type t120 = 20 * t62 + 19 * t65 + 18 * t68 + 17 * t71 + 16 * t74 + 15 * t77 + 14 * t80 + 13 * t83 + 12 * t86 + 11 * t89 + 10 * t92 + 9 * t95 + 8 * t98 + 7 * t101 + 6 * t104 + 5 * t107 + 2 * t110 + t113 + 20 * t115 + 19 * t118;
    real_type result__ = t60 + t120;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  ICLOCS_ContinuousMP::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::DmayerDxxp_numEqns() const { return 180; }

  void
  ICLOCS_ContinuousMP::DmayerDxxp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
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
    result__[ 100 ] = 0;
    result__[ 101 ] = 0;
    result__[ 102 ] = 0;
    result__[ 103 ] = 0;
    result__[ 104 ] = 0;
    result__[ 105 ] = 0;
    result__[ 106 ] = 0;
    result__[ 107 ] = 0;
    result__[ 108 ] = 0;
    result__[ 109 ] = 0;
    result__[ 110 ] = 0;
    result__[ 111 ] = 0;
    result__[ 112 ] = 0;
    result__[ 113 ] = 0;
    result__[ 114 ] = 0;
    result__[ 115 ] = 0;
    result__[ 116 ] = 0;
    result__[ 117 ] = 0;
    result__[ 118 ] = 0;
    result__[ 119 ] = 0;
    result__[ 120 ] = 0;
    result__[ 121 ] = 0;
    result__[ 122 ] = 0;
    result__[ 123 ] = 0;
    result__[ 124 ] = 0;
    result__[ 125 ] = 0;
    result__[ 126 ] = 0;
    result__[ 127 ] = 0;
    result__[ 128 ] = 0;
    result__[ 129 ] = 0;
    result__[ 130 ] = 0;
    result__[ 131 ] = 0;
    result__[ 132 ] = 0;
    result__[ 133 ] = 0;
    result__[ 134 ] = 0;
    result__[ 135 ] = 0;
    result__[ 136 ] = 0;
    result__[ 137 ] = 0;
    result__[ 138 ] = 0;
    result__[ 139 ] = 0;
    result__[ 140 ] = 0;
    result__[ 141 ] = 0;
    result__[ 142 ] = 0;
    result__[ 143 ] = 0;
    result__[ 144 ] = 0;
    result__[ 145 ] = 0;
    result__[ 146 ] = 0;
    result__[ 147 ] = 0;
    result__[ 148 ] = 0;
    result__[ 149 ] = 0;
    result__[ 150 ] = 0;
    result__[ 151 ] = 0;
    result__[ 152 ] = 0;
    result__[ 153 ] = 0;
    result__[ 154 ] = 0;
    result__[ 155 ] = 0;
    result__[ 156 ] = 0;
    result__[ 157 ] = 0;
    result__[ 158 ] = 0;
    result__[ 159 ] = 0;
    result__[ 160 ] = 0;
    result__[ 161 ] = 0;
    result__[ 162 ] = 0;
    result__[ 163 ] = 0;
    result__[ 164 ] = 0;
    result__[ 165 ] = 0;
    result__[ 166 ] = 0;
    result__[ 167 ] = 0;
    result__[ 168 ] = 0;
    result__[ 169 ] = 0;
    result__[ 170 ] = 0;
    result__[ 171 ] = 0;
    result__[ 172 ] = 0;
    result__[ 173 ] = 0;
    result__[ 174 ] = 0;
    result__[ 175 ] = 0;
    result__[ 176 ] = 0;
    result__[ 177 ] = 0;
    result__[ 178 ] = 0;
    result__[ 179 ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 180, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2mayerD2xxp_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::D2mayerD2xxp_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::D2mayerD2xxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2mayerD2xxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer ICLOCS_ContinuousMP::DlagrangeDxup_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 40 * X__[iX_x1];
    result__[ 1   ] = 38 * X__[iX_x2];
    result__[ 2   ] = 36 * X__[iX_x3];
    result__[ 3   ] = 34 * X__[iX_x4];
    result__[ 4   ] = 32 * X__[iX_x5];
    result__[ 5   ] = 30 * X__[iX_x6];
    result__[ 6   ] = 28 * X__[iX_x7];
    result__[ 7   ] = 26 * X__[iX_x8];
    result__[ 8   ] = 24 * X__[iX_x9];
    result__[ 9   ] = 22 * X__[iX_x10];
    result__[ 10  ] = 20 * X__[iX_x11];
    result__[ 11  ] = 18 * X__[iX_x12];
    result__[ 12  ] = 16 * X__[iX_x13];
    result__[ 13  ] = 14 * X__[iX_x14];
    result__[ 14  ] = 12 * X__[iX_x15];
    result__[ 15  ] = 10 * X__[iX_x16];
    result__[ 16  ] = 8 * X__[iX_x17];
    result__[ 17  ] = 6 * X__[iX_x18];
    result__[ 18  ] = 4 * X__[iX_x19];
    result__[ 19  ] = 2 * X__[iX_x20];
    result__[ 20  ] = 40 * X__[iX_y1];
    result__[ 21  ] = 38 * X__[iX_y2];
    result__[ 22  ] = 36 * X__[iX_y3];
    result__[ 23  ] = 34 * X__[iX_y4];
    result__[ 24  ] = 32 * X__[iX_y5];
    result__[ 25  ] = 30 * X__[iX_y6];
    result__[ 26  ] = 28 * X__[iX_y7];
    result__[ 27  ] = 26 * X__[iX_y8];
    result__[ 28  ] = 24 * X__[iX_y9];
    result__[ 29  ] = 22 * X__[iX_y10];
    result__[ 30  ] = 20 * X__[iX_y11];
    result__[ 31  ] = 18 * X__[iX_y12];
    result__[ 32  ] = 16 * X__[iX_y13];
    result__[ 33  ] = 14 * X__[iX_y14];
    result__[ 34  ] = 12 * X__[iX_y15];
    result__[ 35  ] = 10 * X__[iX_y16];
    result__[ 36  ] = 8 * X__[iX_y17];
    result__[ 37  ] = 6 * X__[iX_y18];
    result__[ 38  ] = 4 * X__[iX_y19];
    result__[ 39  ] = 2 * X__[iX_y20];
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
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 100, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2lagrangeD2xup_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::D2lagrangeD2xup_numCols() const { return 100; }
  integer ICLOCS_ContinuousMP::D2lagrangeD2xup_nnz()     const { return 40; }

  void
  ICLOCS_ContinuousMP::D2lagrangeD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  ICLOCS_ContinuousMP::D2lagrangeD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 40;
    result__[ 1   ] = 38;
    result__[ 2   ] = 36;
    result__[ 3   ] = 34;
    result__[ 4   ] = 32;
    result__[ 5   ] = 30;
    result__[ 6   ] = 28;
    result__[ 7   ] = 26;
    result__[ 8   ] = 24;
    result__[ 9   ] = 22;
    result__[ 10  ] = 20;
    result__[ 11  ] = 18;
    result__[ 12  ] = 16;
    result__[ 13  ] = 14;
    result__[ 14  ] = 12;
    result__[ 15  ] = 10;
    result__[ 16  ] = 8;
    result__[ 17  ] = 6;
    result__[ 18  ] = 4;
    result__[ 19  ] = 2;
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xup_eval", 40, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS_ContinuousMP::q_numEqns() const
  { return 1; }

  void
  ICLOCS_ContinuousMP::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer ICLOCS_ContinuousMP::segmentLink_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::DsegmentLinkDxp_numRows() const { return 0; }
  integer ICLOCS_ContinuousMP::DsegmentLinkDxp_numCols() const { return 0; }
  integer ICLOCS_ContinuousMP::DsegmentLinkDxp_nnz() const { return 0; }

  void
  ICLOCS_ContinuousMP::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer ICLOCS_ContinuousMP::jump_numEqns() const { return 160; }

  void
  ICLOCS_ContinuousMP::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_x1] - XL__[iX_x1];
    result__[ 1   ] = XR__[iX_x2] - XL__[iX_x2];
    result__[ 2   ] = XR__[iX_x3] - XL__[iX_x3];
    result__[ 3   ] = XR__[iX_x4] - XL__[iX_x4];
    result__[ 4   ] = XR__[iX_x5] - XL__[iX_x5];
    result__[ 5   ] = XR__[iX_x6] - XL__[iX_x6];
    result__[ 6   ] = XR__[iX_x7] - XL__[iX_x7];
    result__[ 7   ] = XR__[iX_x8] - XL__[iX_x8];
    result__[ 8   ] = XR__[iX_x9] - XL__[iX_x9];
    result__[ 9   ] = XR__[iX_x10] - XL__[iX_x10];
    result__[ 10  ] = XR__[iX_x11] - XL__[iX_x11];
    result__[ 11  ] = XR__[iX_x12] - XL__[iX_x12];
    result__[ 12  ] = XR__[iX_x13] - XL__[iX_x13];
    result__[ 13  ] = XR__[iX_x14] - XL__[iX_x14];
    result__[ 14  ] = XR__[iX_x15] - XL__[iX_x15];
    result__[ 15  ] = XR__[iX_x16] - XL__[iX_x16];
    result__[ 16  ] = XR__[iX_x17] - XL__[iX_x17];
    result__[ 17  ] = XR__[iX_x18] - XL__[iX_x18];
    result__[ 18  ] = XR__[iX_x19] - XL__[iX_x19];
    result__[ 19  ] = XR__[iX_x20] - XL__[iX_x20];
    result__[ 20  ] = XR__[iX_y1] - XL__[iX_y1];
    result__[ 21  ] = XR__[iX_y2] - XL__[iX_y2];
    result__[ 22  ] = XR__[iX_y3] - XL__[iX_y3];
    result__[ 23  ] = XR__[iX_y4] - XL__[iX_y4];
    result__[ 24  ] = XR__[iX_y5] - XL__[iX_y5];
    result__[ 25  ] = XR__[iX_y6] - XL__[iX_y6];
    result__[ 26  ] = XR__[iX_y7] - XL__[iX_y7];
    result__[ 27  ] = XR__[iX_y8] - XL__[iX_y8];
    result__[ 28  ] = XR__[iX_y9] - XL__[iX_y9];
    result__[ 29  ] = XR__[iX_y10] - XL__[iX_y10];
    result__[ 30  ] = XR__[iX_y11] - XL__[iX_y11];
    result__[ 31  ] = XR__[iX_y12] - XL__[iX_y12];
    result__[ 32  ] = XR__[iX_y13] - XL__[iX_y13];
    result__[ 33  ] = XR__[iX_y14] - XL__[iX_y14];
    result__[ 34  ] = XR__[iX_y15] - XL__[iX_y15];
    result__[ 35  ] = XR__[iX_y16] - XL__[iX_y16];
    result__[ 36  ] = XR__[iX_y17] - XL__[iX_y17];
    result__[ 37  ] = XR__[iX_y18] - XL__[iX_y18];
    result__[ 38  ] = XR__[iX_y19] - XL__[iX_y19];
    result__[ 39  ] = XR__[iX_y20] - XL__[iX_y20];
    result__[ 40  ] = XR__[iX_xx1] - XL__[iX_xx1];
    result__[ 41  ] = XR__[iX_xx2] - XL__[iX_xx2];
    result__[ 42  ] = XR__[iX_xx3] - XL__[iX_xx3];
    result__[ 43  ] = XR__[iX_xx4] - XL__[iX_xx4];
    result__[ 44  ] = XR__[iX_xx5] - XL__[iX_xx5];
    result__[ 45  ] = XR__[iX_xx6] - XL__[iX_xx6];
    result__[ 46  ] = XR__[iX_xx7] - XL__[iX_xx7];
    result__[ 47  ] = XR__[iX_xx8] - XL__[iX_xx8];
    result__[ 48  ] = XR__[iX_xx9] - XL__[iX_xx9];
    result__[ 49  ] = XR__[iX_xx10] - XL__[iX_xx10];
    result__[ 50  ] = XR__[iX_xx11] - XL__[iX_xx11];
    result__[ 51  ] = XR__[iX_xx12] - XL__[iX_xx12];
    result__[ 52  ] = XR__[iX_xx13] - XL__[iX_xx13];
    result__[ 53  ] = XR__[iX_xx14] - XL__[iX_xx14];
    result__[ 54  ] = XR__[iX_xx15] - XL__[iX_xx15];
    result__[ 55  ] = XR__[iX_xx16] - XL__[iX_xx16];
    result__[ 56  ] = XR__[iX_xx17] - XL__[iX_xx17];
    result__[ 57  ] = XR__[iX_xx18] - XL__[iX_xx18];
    result__[ 58  ] = XR__[iX_xx19] - XL__[iX_xx19];
    result__[ 59  ] = XR__[iX_xx20] - XL__[iX_xx20];
    result__[ 60  ] = XR__[iX_yy1] - XL__[iX_yy1];
    result__[ 61  ] = XR__[iX_yy2] - XL__[iX_yy2];
    result__[ 62  ] = XR__[iX_yy3] - XL__[iX_yy3];
    result__[ 63  ] = XR__[iX_yy4] - XL__[iX_yy4];
    result__[ 64  ] = XR__[iX_yy5] - XL__[iX_yy5];
    result__[ 65  ] = XR__[iX_yy6] - XL__[iX_yy6];
    result__[ 66  ] = XR__[iX_yy7] - XL__[iX_yy7];
    result__[ 67  ] = XR__[iX_yy8] - XL__[iX_yy8];
    result__[ 68  ] = XR__[iX_yy9] - XL__[iX_yy9];
    result__[ 69  ] = XR__[iX_yy10] - XL__[iX_yy10];
    result__[ 70  ] = XR__[iX_yy11] - XL__[iX_yy11];
    result__[ 71  ] = XR__[iX_yy12] - XL__[iX_yy12];
    result__[ 72  ] = XR__[iX_yy13] - XL__[iX_yy13];
    result__[ 73  ] = XR__[iX_yy14] - XL__[iX_yy14];
    result__[ 74  ] = XR__[iX_yy15] - XL__[iX_yy15];
    result__[ 75  ] = XR__[iX_yy16] - XL__[iX_yy16];
    result__[ 76  ] = XR__[iX_yy17] - XL__[iX_yy17];
    result__[ 77  ] = XR__[iX_yy18] - XL__[iX_yy18];
    result__[ 78  ] = XR__[iX_yy19] - XL__[iX_yy19];
    result__[ 79  ] = XR__[iX_yy20] - XL__[iX_yy20];
    result__[ 80  ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 81  ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 82  ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 83  ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 84  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 85  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    result__[ 86  ] = LR__[iL_lambda7__xo] - LL__[iL_lambda7__xo];
    result__[ 87  ] = LR__[iL_lambda8__xo] - LL__[iL_lambda8__xo];
    result__[ 88  ] = LR__[iL_lambda9__xo] - LL__[iL_lambda9__xo];
    result__[ 89  ] = LR__[iL_lambda10__xo] - LL__[iL_lambda10__xo];
    result__[ 90  ] = LR__[iL_lambda11__xo] - LL__[iL_lambda11__xo];
    result__[ 91  ] = LR__[iL_lambda12__xo] - LL__[iL_lambda12__xo];
    result__[ 92  ] = LR__[iL_lambda13__xo] - LL__[iL_lambda13__xo];
    result__[ 93  ] = LR__[iL_lambda14__xo] - LL__[iL_lambda14__xo];
    result__[ 94  ] = LR__[iL_lambda15__xo] - LL__[iL_lambda15__xo];
    result__[ 95  ] = LR__[iL_lambda16__xo] - LL__[iL_lambda16__xo];
    result__[ 96  ] = LR__[iL_lambda17__xo] - LL__[iL_lambda17__xo];
    result__[ 97  ] = LR__[iL_lambda18__xo] - LL__[iL_lambda18__xo];
    result__[ 98  ] = LR__[iL_lambda19__xo] - LL__[iL_lambda19__xo];
    result__[ 99  ] = LR__[iL_lambda20__xo] - LL__[iL_lambda20__xo];
    result__[ 100 ] = LR__[iL_lambda21__xo] - LL__[iL_lambda21__xo];
    result__[ 101 ] = LR__[iL_lambda22__xo] - LL__[iL_lambda22__xo];
    result__[ 102 ] = LR__[iL_lambda23__xo] - LL__[iL_lambda23__xo];
    result__[ 103 ] = LR__[iL_lambda24__xo] - LL__[iL_lambda24__xo];
    result__[ 104 ] = LR__[iL_lambda25__xo] - LL__[iL_lambda25__xo];
    result__[ 105 ] = LR__[iL_lambda26__xo] - LL__[iL_lambda26__xo];
    result__[ 106 ] = LR__[iL_lambda27__xo] - LL__[iL_lambda27__xo];
    result__[ 107 ] = LR__[iL_lambda28__xo] - LL__[iL_lambda28__xo];
    result__[ 108 ] = LR__[iL_lambda29__xo] - LL__[iL_lambda29__xo];
    result__[ 109 ] = LR__[iL_lambda30__xo] - LL__[iL_lambda30__xo];
    result__[ 110 ] = LR__[iL_lambda31__xo] - LL__[iL_lambda31__xo];
    result__[ 111 ] = LR__[iL_lambda32__xo] - LL__[iL_lambda32__xo];
    result__[ 112 ] = LR__[iL_lambda33__xo] - LL__[iL_lambda33__xo];
    result__[ 113 ] = LR__[iL_lambda34__xo] - LL__[iL_lambda34__xo];
    result__[ 114 ] = LR__[iL_lambda35__xo] - LL__[iL_lambda35__xo];
    result__[ 115 ] = LR__[iL_lambda36__xo] - LL__[iL_lambda36__xo];
    result__[ 116 ] = LR__[iL_lambda37__xo] - LL__[iL_lambda37__xo];
    result__[ 117 ] = LR__[iL_lambda38__xo] - LL__[iL_lambda38__xo];
    result__[ 118 ] = LR__[iL_lambda39__xo] - LL__[iL_lambda39__xo];
    result__[ 119 ] = LR__[iL_lambda40__xo] - LL__[iL_lambda40__xo];
    result__[ 120 ] = LR__[iL_lambda41__xo] - LL__[iL_lambda41__xo];
    result__[ 121 ] = LR__[iL_lambda42__xo] - LL__[iL_lambda42__xo];
    result__[ 122 ] = LR__[iL_lambda43__xo] - LL__[iL_lambda43__xo];
    result__[ 123 ] = LR__[iL_lambda44__xo] - LL__[iL_lambda44__xo];
    result__[ 124 ] = LR__[iL_lambda45__xo] - LL__[iL_lambda45__xo];
    result__[ 125 ] = LR__[iL_lambda46__xo] - LL__[iL_lambda46__xo];
    result__[ 126 ] = LR__[iL_lambda47__xo] - LL__[iL_lambda47__xo];
    result__[ 127 ] = LR__[iL_lambda48__xo] - LL__[iL_lambda48__xo];
    result__[ 128 ] = LR__[iL_lambda49__xo] - LL__[iL_lambda49__xo];
    result__[ 129 ] = LR__[iL_lambda50__xo] - LL__[iL_lambda50__xo];
    result__[ 130 ] = LR__[iL_lambda51__xo] - LL__[iL_lambda51__xo];
    result__[ 131 ] = LR__[iL_lambda52__xo] - LL__[iL_lambda52__xo];
    result__[ 132 ] = LR__[iL_lambda53__xo] - LL__[iL_lambda53__xo];
    result__[ 133 ] = LR__[iL_lambda54__xo] - LL__[iL_lambda54__xo];
    result__[ 134 ] = LR__[iL_lambda55__xo] - LL__[iL_lambda55__xo];
    result__[ 135 ] = LR__[iL_lambda56__xo] - LL__[iL_lambda56__xo];
    result__[ 136 ] = LR__[iL_lambda57__xo] - LL__[iL_lambda57__xo];
    result__[ 137 ] = LR__[iL_lambda58__xo] - LL__[iL_lambda58__xo];
    result__[ 138 ] = LR__[iL_lambda59__xo] - LL__[iL_lambda59__xo];
    result__[ 139 ] = LR__[iL_lambda60__xo] - LL__[iL_lambda60__xo];
    result__[ 140 ] = LR__[iL_lambda61__xo] - LL__[iL_lambda61__xo];
    result__[ 141 ] = LR__[iL_lambda62__xo] - LL__[iL_lambda62__xo];
    result__[ 142 ] = LR__[iL_lambda63__xo] - LL__[iL_lambda63__xo];
    result__[ 143 ] = LR__[iL_lambda64__xo] - LL__[iL_lambda64__xo];
    result__[ 144 ] = LR__[iL_lambda65__xo] - LL__[iL_lambda65__xo];
    result__[ 145 ] = LR__[iL_lambda66__xo] - LL__[iL_lambda66__xo];
    result__[ 146 ] = LR__[iL_lambda67__xo] - LL__[iL_lambda67__xo];
    result__[ 147 ] = LR__[iL_lambda68__xo] - LL__[iL_lambda68__xo];
    result__[ 148 ] = LR__[iL_lambda69__xo] - LL__[iL_lambda69__xo];
    result__[ 149 ] = LR__[iL_lambda70__xo] - LL__[iL_lambda70__xo];
    result__[ 150 ] = LR__[iL_lambda71__xo] - LL__[iL_lambda71__xo];
    result__[ 151 ] = LR__[iL_lambda72__xo] - LL__[iL_lambda72__xo];
    result__[ 152 ] = LR__[iL_lambda73__xo] - LL__[iL_lambda73__xo];
    result__[ 153 ] = LR__[iL_lambda74__xo] - LL__[iL_lambda74__xo];
    result__[ 154 ] = LR__[iL_lambda75__xo] - LL__[iL_lambda75__xo];
    result__[ 155 ] = LR__[iL_lambda76__xo] - LL__[iL_lambda76__xo];
    result__[ 156 ] = LR__[iL_lambda77__xo] - LL__[iL_lambda77__xo];
    result__[ 157 ] = LR__[iL_lambda78__xo] - LL__[iL_lambda78__xo];
    result__[ 158 ] = LR__[iL_lambda79__xo] - LL__[iL_lambda79__xo];
    result__[ 159 ] = LR__[iL_lambda80__xo] - LL__[iL_lambda80__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 160, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DjumpDxlxlp_numRows() const { return 160; }
  integer ICLOCS_ContinuousMP::DjumpDxlxlp_numCols() const { return 340; }
  integer ICLOCS_ContinuousMP::DjumpDxlxlp_nnz()     const { return 320; }

  void
  ICLOCS_ContinuousMP::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 160 ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 161 ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 162 ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 163 ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 164 ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 165 ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 166 ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 167 ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 168 ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 169 ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 170 ;
    iIndex[22] = 11  ; jIndex[22] = 11  ;
    iIndex[23] = 11  ; jIndex[23] = 171 ;
    iIndex[24] = 12  ; jIndex[24] = 12  ;
    iIndex[25] = 12  ; jIndex[25] = 172 ;
    iIndex[26] = 13  ; jIndex[26] = 13  ;
    iIndex[27] = 13  ; jIndex[27] = 173 ;
    iIndex[28] = 14  ; jIndex[28] = 14  ;
    iIndex[29] = 14  ; jIndex[29] = 174 ;
    iIndex[30] = 15  ; jIndex[30] = 15  ;
    iIndex[31] = 15  ; jIndex[31] = 175 ;
    iIndex[32] = 16  ; jIndex[32] = 16  ;
    iIndex[33] = 16  ; jIndex[33] = 176 ;
    iIndex[34] = 17  ; jIndex[34] = 17  ;
    iIndex[35] = 17  ; jIndex[35] = 177 ;
    iIndex[36] = 18  ; jIndex[36] = 18  ;
    iIndex[37] = 18  ; jIndex[37] = 178 ;
    iIndex[38] = 19  ; jIndex[38] = 19  ;
    iIndex[39] = 19  ; jIndex[39] = 179 ;
    iIndex[40] = 20  ; jIndex[40] = 20  ;
    iIndex[41] = 20  ; jIndex[41] = 180 ;
    iIndex[42] = 21  ; jIndex[42] = 21  ;
    iIndex[43] = 21  ; jIndex[43] = 181 ;
    iIndex[44] = 22  ; jIndex[44] = 22  ;
    iIndex[45] = 22  ; jIndex[45] = 182 ;
    iIndex[46] = 23  ; jIndex[46] = 23  ;
    iIndex[47] = 23  ; jIndex[47] = 183 ;
    iIndex[48] = 24  ; jIndex[48] = 24  ;
    iIndex[49] = 24  ; jIndex[49] = 184 ;
    iIndex[50] = 25  ; jIndex[50] = 25  ;
    iIndex[51] = 25  ; jIndex[51] = 185 ;
    iIndex[52] = 26  ; jIndex[52] = 26  ;
    iIndex[53] = 26  ; jIndex[53] = 186 ;
    iIndex[54] = 27  ; jIndex[54] = 27  ;
    iIndex[55] = 27  ; jIndex[55] = 187 ;
    iIndex[56] = 28  ; jIndex[56] = 28  ;
    iIndex[57] = 28  ; jIndex[57] = 188 ;
    iIndex[58] = 29  ; jIndex[58] = 29  ;
    iIndex[59] = 29  ; jIndex[59] = 189 ;
    iIndex[60] = 30  ; jIndex[60] = 30  ;
    iIndex[61] = 30  ; jIndex[61] = 190 ;
    iIndex[62] = 31  ; jIndex[62] = 31  ;
    iIndex[63] = 31  ; jIndex[63] = 191 ;
    iIndex[64] = 32  ; jIndex[64] = 32  ;
    iIndex[65] = 32  ; jIndex[65] = 192 ;
    iIndex[66] = 33  ; jIndex[66] = 33  ;
    iIndex[67] = 33  ; jIndex[67] = 193 ;
    iIndex[68] = 34  ; jIndex[68] = 34  ;
    iIndex[69] = 34  ; jIndex[69] = 194 ;
    iIndex[70] = 35  ; jIndex[70] = 35  ;
    iIndex[71] = 35  ; jIndex[71] = 195 ;
    iIndex[72] = 36  ; jIndex[72] = 36  ;
    iIndex[73] = 36  ; jIndex[73] = 196 ;
    iIndex[74] = 37  ; jIndex[74] = 37  ;
    iIndex[75] = 37  ; jIndex[75] = 197 ;
    iIndex[76] = 38  ; jIndex[76] = 38  ;
    iIndex[77] = 38  ; jIndex[77] = 198 ;
    iIndex[78] = 39  ; jIndex[78] = 39  ;
    iIndex[79] = 39  ; jIndex[79] = 199 ;
    iIndex[80] = 40  ; jIndex[80] = 40  ;
    iIndex[81] = 40  ; jIndex[81] = 200 ;
    iIndex[82] = 41  ; jIndex[82] = 41  ;
    iIndex[83] = 41  ; jIndex[83] = 201 ;
    iIndex[84] = 42  ; jIndex[84] = 42  ;
    iIndex[85] = 42  ; jIndex[85] = 202 ;
    iIndex[86] = 43  ; jIndex[86] = 43  ;
    iIndex[87] = 43  ; jIndex[87] = 203 ;
    iIndex[88] = 44  ; jIndex[88] = 44  ;
    iIndex[89] = 44  ; jIndex[89] = 204 ;
    iIndex[90] = 45  ; jIndex[90] = 45  ;
    iIndex[91] = 45  ; jIndex[91] = 205 ;
    iIndex[92] = 46  ; jIndex[92] = 46  ;
    iIndex[93] = 46  ; jIndex[93] = 206 ;
    iIndex[94] = 47  ; jIndex[94] = 47  ;
    iIndex[95] = 47  ; jIndex[95] = 207 ;
    iIndex[96] = 48  ; jIndex[96] = 48  ;
    iIndex[97] = 48  ; jIndex[97] = 208 ;
    iIndex[98] = 49  ; jIndex[98] = 49  ;
    iIndex[99] = 49  ; jIndex[99] = 209 ;
    iIndex[100] = 50  ; jIndex[100] = 50  ;
    iIndex[101] = 50  ; jIndex[101] = 210 ;
    iIndex[102] = 51  ; jIndex[102] = 51  ;
    iIndex[103] = 51  ; jIndex[103] = 211 ;
    iIndex[104] = 52  ; jIndex[104] = 52  ;
    iIndex[105] = 52  ; jIndex[105] = 212 ;
    iIndex[106] = 53  ; jIndex[106] = 53  ;
    iIndex[107] = 53  ; jIndex[107] = 213 ;
    iIndex[108] = 54  ; jIndex[108] = 54  ;
    iIndex[109] = 54  ; jIndex[109] = 214 ;
    iIndex[110] = 55  ; jIndex[110] = 55  ;
    iIndex[111] = 55  ; jIndex[111] = 215 ;
    iIndex[112] = 56  ; jIndex[112] = 56  ;
    iIndex[113] = 56  ; jIndex[113] = 216 ;
    iIndex[114] = 57  ; jIndex[114] = 57  ;
    iIndex[115] = 57  ; jIndex[115] = 217 ;
    iIndex[116] = 58  ; jIndex[116] = 58  ;
    iIndex[117] = 58  ; jIndex[117] = 218 ;
    iIndex[118] = 59  ; jIndex[118] = 59  ;
    iIndex[119] = 59  ; jIndex[119] = 219 ;
    iIndex[120] = 60  ; jIndex[120] = 60  ;
    iIndex[121] = 60  ; jIndex[121] = 220 ;
    iIndex[122] = 61  ; jIndex[122] = 61  ;
    iIndex[123] = 61  ; jIndex[123] = 221 ;
    iIndex[124] = 62  ; jIndex[124] = 62  ;
    iIndex[125] = 62  ; jIndex[125] = 222 ;
    iIndex[126] = 63  ; jIndex[126] = 63  ;
    iIndex[127] = 63  ; jIndex[127] = 223 ;
    iIndex[128] = 64  ; jIndex[128] = 64  ;
    iIndex[129] = 64  ; jIndex[129] = 224 ;
    iIndex[130] = 65  ; jIndex[130] = 65  ;
    iIndex[131] = 65  ; jIndex[131] = 225 ;
    iIndex[132] = 66  ; jIndex[132] = 66  ;
    iIndex[133] = 66  ; jIndex[133] = 226 ;
    iIndex[134] = 67  ; jIndex[134] = 67  ;
    iIndex[135] = 67  ; jIndex[135] = 227 ;
    iIndex[136] = 68  ; jIndex[136] = 68  ;
    iIndex[137] = 68  ; jIndex[137] = 228 ;
    iIndex[138] = 69  ; jIndex[138] = 69  ;
    iIndex[139] = 69  ; jIndex[139] = 229 ;
    iIndex[140] = 70  ; jIndex[140] = 70  ;
    iIndex[141] = 70  ; jIndex[141] = 230 ;
    iIndex[142] = 71  ; jIndex[142] = 71  ;
    iIndex[143] = 71  ; jIndex[143] = 231 ;
    iIndex[144] = 72  ; jIndex[144] = 72  ;
    iIndex[145] = 72  ; jIndex[145] = 232 ;
    iIndex[146] = 73  ; jIndex[146] = 73  ;
    iIndex[147] = 73  ; jIndex[147] = 233 ;
    iIndex[148] = 74  ; jIndex[148] = 74  ;
    iIndex[149] = 74  ; jIndex[149] = 234 ;
    iIndex[150] = 75  ; jIndex[150] = 75  ;
    iIndex[151] = 75  ; jIndex[151] = 235 ;
    iIndex[152] = 76  ; jIndex[152] = 76  ;
    iIndex[153] = 76  ; jIndex[153] = 236 ;
    iIndex[154] = 77  ; jIndex[154] = 77  ;
    iIndex[155] = 77  ; jIndex[155] = 237 ;
    iIndex[156] = 78  ; jIndex[156] = 78  ;
    iIndex[157] = 78  ; jIndex[157] = 238 ;
    iIndex[158] = 79  ; jIndex[158] = 79  ;
    iIndex[159] = 79  ; jIndex[159] = 239 ;
    iIndex[160] = 80  ; jIndex[160] = 80  ;
    iIndex[161] = 80  ; jIndex[161] = 240 ;
    iIndex[162] = 81  ; jIndex[162] = 81  ;
    iIndex[163] = 81  ; jIndex[163] = 241 ;
    iIndex[164] = 82  ; jIndex[164] = 82  ;
    iIndex[165] = 82  ; jIndex[165] = 242 ;
    iIndex[166] = 83  ; jIndex[166] = 83  ;
    iIndex[167] = 83  ; jIndex[167] = 243 ;
    iIndex[168] = 84  ; jIndex[168] = 84  ;
    iIndex[169] = 84  ; jIndex[169] = 244 ;
    iIndex[170] = 85  ; jIndex[170] = 85  ;
    iIndex[171] = 85  ; jIndex[171] = 245 ;
    iIndex[172] = 86  ; jIndex[172] = 86  ;
    iIndex[173] = 86  ; jIndex[173] = 246 ;
    iIndex[174] = 87  ; jIndex[174] = 87  ;
    iIndex[175] = 87  ; jIndex[175] = 247 ;
    iIndex[176] = 88  ; jIndex[176] = 88  ;
    iIndex[177] = 88  ; jIndex[177] = 248 ;
    iIndex[178] = 89  ; jIndex[178] = 89  ;
    iIndex[179] = 89  ; jIndex[179] = 249 ;
    iIndex[180] = 90  ; jIndex[180] = 90  ;
    iIndex[181] = 90  ; jIndex[181] = 250 ;
    iIndex[182] = 91  ; jIndex[182] = 91  ;
    iIndex[183] = 91  ; jIndex[183] = 251 ;
    iIndex[184] = 92  ; jIndex[184] = 92  ;
    iIndex[185] = 92  ; jIndex[185] = 252 ;
    iIndex[186] = 93  ; jIndex[186] = 93  ;
    iIndex[187] = 93  ; jIndex[187] = 253 ;
    iIndex[188] = 94  ; jIndex[188] = 94  ;
    iIndex[189] = 94  ; jIndex[189] = 254 ;
    iIndex[190] = 95  ; jIndex[190] = 95  ;
    iIndex[191] = 95  ; jIndex[191] = 255 ;
    iIndex[192] = 96  ; jIndex[192] = 96  ;
    iIndex[193] = 96  ; jIndex[193] = 256 ;
    iIndex[194] = 97  ; jIndex[194] = 97  ;
    iIndex[195] = 97  ; jIndex[195] = 257 ;
    iIndex[196] = 98  ; jIndex[196] = 98  ;
    iIndex[197] = 98  ; jIndex[197] = 258 ;
    iIndex[198] = 99  ; jIndex[198] = 99  ;
    iIndex[199] = 99  ; jIndex[199] = 259 ;
    iIndex[200] = 100 ; jIndex[200] = 100 ;
    iIndex[201] = 100 ; jIndex[201] = 260 ;
    iIndex[202] = 101 ; jIndex[202] = 101 ;
    iIndex[203] = 101 ; jIndex[203] = 261 ;
    iIndex[204] = 102 ; jIndex[204] = 102 ;
    iIndex[205] = 102 ; jIndex[205] = 262 ;
    iIndex[206] = 103 ; jIndex[206] = 103 ;
    iIndex[207] = 103 ; jIndex[207] = 263 ;
    iIndex[208] = 104 ; jIndex[208] = 104 ;
    iIndex[209] = 104 ; jIndex[209] = 264 ;
    iIndex[210] = 105 ; jIndex[210] = 105 ;
    iIndex[211] = 105 ; jIndex[211] = 265 ;
    iIndex[212] = 106 ; jIndex[212] = 106 ;
    iIndex[213] = 106 ; jIndex[213] = 266 ;
    iIndex[214] = 107 ; jIndex[214] = 107 ;
    iIndex[215] = 107 ; jIndex[215] = 267 ;
    iIndex[216] = 108 ; jIndex[216] = 108 ;
    iIndex[217] = 108 ; jIndex[217] = 268 ;
    iIndex[218] = 109 ; jIndex[218] = 109 ;
    iIndex[219] = 109 ; jIndex[219] = 269 ;
    iIndex[220] = 110 ; jIndex[220] = 110 ;
    iIndex[221] = 110 ; jIndex[221] = 270 ;
    iIndex[222] = 111 ; jIndex[222] = 111 ;
    iIndex[223] = 111 ; jIndex[223] = 271 ;
    iIndex[224] = 112 ; jIndex[224] = 112 ;
    iIndex[225] = 112 ; jIndex[225] = 272 ;
    iIndex[226] = 113 ; jIndex[226] = 113 ;
    iIndex[227] = 113 ; jIndex[227] = 273 ;
    iIndex[228] = 114 ; jIndex[228] = 114 ;
    iIndex[229] = 114 ; jIndex[229] = 274 ;
    iIndex[230] = 115 ; jIndex[230] = 115 ;
    iIndex[231] = 115 ; jIndex[231] = 275 ;
    iIndex[232] = 116 ; jIndex[232] = 116 ;
    iIndex[233] = 116 ; jIndex[233] = 276 ;
    iIndex[234] = 117 ; jIndex[234] = 117 ;
    iIndex[235] = 117 ; jIndex[235] = 277 ;
    iIndex[236] = 118 ; jIndex[236] = 118 ;
    iIndex[237] = 118 ; jIndex[237] = 278 ;
    iIndex[238] = 119 ; jIndex[238] = 119 ;
    iIndex[239] = 119 ; jIndex[239] = 279 ;
    iIndex[240] = 120 ; jIndex[240] = 120 ;
    iIndex[241] = 120 ; jIndex[241] = 280 ;
    iIndex[242] = 121 ; jIndex[242] = 121 ;
    iIndex[243] = 121 ; jIndex[243] = 281 ;
    iIndex[244] = 122 ; jIndex[244] = 122 ;
    iIndex[245] = 122 ; jIndex[245] = 282 ;
    iIndex[246] = 123 ; jIndex[246] = 123 ;
    iIndex[247] = 123 ; jIndex[247] = 283 ;
    iIndex[248] = 124 ; jIndex[248] = 124 ;
    iIndex[249] = 124 ; jIndex[249] = 284 ;
    iIndex[250] = 125 ; jIndex[250] = 125 ;
    iIndex[251] = 125 ; jIndex[251] = 285 ;
    iIndex[252] = 126 ; jIndex[252] = 126 ;
    iIndex[253] = 126 ; jIndex[253] = 286 ;
    iIndex[254] = 127 ; jIndex[254] = 127 ;
    iIndex[255] = 127 ; jIndex[255] = 287 ;
    iIndex[256] = 128 ; jIndex[256] = 128 ;
    iIndex[257] = 128 ; jIndex[257] = 288 ;
    iIndex[258] = 129 ; jIndex[258] = 129 ;
    iIndex[259] = 129 ; jIndex[259] = 289 ;
    iIndex[260] = 130 ; jIndex[260] = 130 ;
    iIndex[261] = 130 ; jIndex[261] = 290 ;
    iIndex[262] = 131 ; jIndex[262] = 131 ;
    iIndex[263] = 131 ; jIndex[263] = 291 ;
    iIndex[264] = 132 ; jIndex[264] = 132 ;
    iIndex[265] = 132 ; jIndex[265] = 292 ;
    iIndex[266] = 133 ; jIndex[266] = 133 ;
    iIndex[267] = 133 ; jIndex[267] = 293 ;
    iIndex[268] = 134 ; jIndex[268] = 134 ;
    iIndex[269] = 134 ; jIndex[269] = 294 ;
    iIndex[270] = 135 ; jIndex[270] = 135 ;
    iIndex[271] = 135 ; jIndex[271] = 295 ;
    iIndex[272] = 136 ; jIndex[272] = 136 ;
    iIndex[273] = 136 ; jIndex[273] = 296 ;
    iIndex[274] = 137 ; jIndex[274] = 137 ;
    iIndex[275] = 137 ; jIndex[275] = 297 ;
    iIndex[276] = 138 ; jIndex[276] = 138 ;
    iIndex[277] = 138 ; jIndex[277] = 298 ;
    iIndex[278] = 139 ; jIndex[278] = 139 ;
    iIndex[279] = 139 ; jIndex[279] = 299 ;
    iIndex[280] = 140 ; jIndex[280] = 140 ;
    iIndex[281] = 140 ; jIndex[281] = 300 ;
    iIndex[282] = 141 ; jIndex[282] = 141 ;
    iIndex[283] = 141 ; jIndex[283] = 301 ;
    iIndex[284] = 142 ; jIndex[284] = 142 ;
    iIndex[285] = 142 ; jIndex[285] = 302 ;
    iIndex[286] = 143 ; jIndex[286] = 143 ;
    iIndex[287] = 143 ; jIndex[287] = 303 ;
    iIndex[288] = 144 ; jIndex[288] = 144 ;
    iIndex[289] = 144 ; jIndex[289] = 304 ;
    iIndex[290] = 145 ; jIndex[290] = 145 ;
    iIndex[291] = 145 ; jIndex[291] = 305 ;
    iIndex[292] = 146 ; jIndex[292] = 146 ;
    iIndex[293] = 146 ; jIndex[293] = 306 ;
    iIndex[294] = 147 ; jIndex[294] = 147 ;
    iIndex[295] = 147 ; jIndex[295] = 307 ;
    iIndex[296] = 148 ; jIndex[296] = 148 ;
    iIndex[297] = 148 ; jIndex[297] = 308 ;
    iIndex[298] = 149 ; jIndex[298] = 149 ;
    iIndex[299] = 149 ; jIndex[299] = 309 ;
    iIndex[300] = 150 ; jIndex[300] = 150 ;
    iIndex[301] = 150 ; jIndex[301] = 310 ;
    iIndex[302] = 151 ; jIndex[302] = 151 ;
    iIndex[303] = 151 ; jIndex[303] = 311 ;
    iIndex[304] = 152 ; jIndex[304] = 152 ;
    iIndex[305] = 152 ; jIndex[305] = 312 ;
    iIndex[306] = 153 ; jIndex[306] = 153 ;
    iIndex[307] = 153 ; jIndex[307] = 313 ;
    iIndex[308] = 154 ; jIndex[308] = 154 ;
    iIndex[309] = 154 ; jIndex[309] = 314 ;
    iIndex[310] = 155 ; jIndex[310] = 155 ;
    iIndex[311] = 155 ; jIndex[311] = 315 ;
    iIndex[312] = 156 ; jIndex[312] = 156 ;
    iIndex[313] = 156 ; jIndex[313] = 316 ;
    iIndex[314] = 157 ; jIndex[314] = 157 ;
    iIndex[315] = 157 ; jIndex[315] = 317 ;
    iIndex[316] = 158 ; jIndex[316] = 158 ;
    iIndex[317] = 158 ; jIndex[317] = 318 ;
    iIndex[318] = 159 ; jIndex[318] = 159 ;
    iIndex[319] = 159 ; jIndex[319] = 319 ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
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
    result__[ 120 ] = -1;
    result__[ 121 ] = 1;
    result__[ 122 ] = -1;
    result__[ 123 ] = 1;
    result__[ 124 ] = -1;
    result__[ 125 ] = 1;
    result__[ 126 ] = -1;
    result__[ 127 ] = 1;
    result__[ 128 ] = -1;
    result__[ 129 ] = 1;
    result__[ 130 ] = -1;
    result__[ 131 ] = 1;
    result__[ 132 ] = -1;
    result__[ 133 ] = 1;
    result__[ 134 ] = -1;
    result__[ 135 ] = 1;
    result__[ 136 ] = -1;
    result__[ 137 ] = 1;
    result__[ 138 ] = -1;
    result__[ 139 ] = 1;
    result__[ 140 ] = -1;
    result__[ 141 ] = 1;
    result__[ 142 ] = -1;
    result__[ 143 ] = 1;
    result__[ 144 ] = -1;
    result__[ 145 ] = 1;
    result__[ 146 ] = -1;
    result__[ 147 ] = 1;
    result__[ 148 ] = -1;
    result__[ 149 ] = 1;
    result__[ 150 ] = -1;
    result__[ 151 ] = 1;
    result__[ 152 ] = -1;
    result__[ 153 ] = 1;
    result__[ 154 ] = -1;
    result__[ 155 ] = 1;
    result__[ 156 ] = -1;
    result__[ 157 ] = 1;
    result__[ 158 ] = -1;
    result__[ 159 ] = 1;
    result__[ 160 ] = -1;
    result__[ 161 ] = 1;
    result__[ 162 ] = -1;
    result__[ 163 ] = 1;
    result__[ 164 ] = -1;
    result__[ 165 ] = 1;
    result__[ 166 ] = -1;
    result__[ 167 ] = 1;
    result__[ 168 ] = -1;
    result__[ 169 ] = 1;
    result__[ 170 ] = -1;
    result__[ 171 ] = 1;
    result__[ 172 ] = -1;
    result__[ 173 ] = 1;
    result__[ 174 ] = -1;
    result__[ 175 ] = 1;
    result__[ 176 ] = -1;
    result__[ 177 ] = 1;
    result__[ 178 ] = -1;
    result__[ 179 ] = 1;
    result__[ 180 ] = -1;
    result__[ 181 ] = 1;
    result__[ 182 ] = -1;
    result__[ 183 ] = 1;
    result__[ 184 ] = -1;
    result__[ 185 ] = 1;
    result__[ 186 ] = -1;
    result__[ 187 ] = 1;
    result__[ 188 ] = -1;
    result__[ 189 ] = 1;
    result__[ 190 ] = -1;
    result__[ 191 ] = 1;
    result__[ 192 ] = -1;
    result__[ 193 ] = 1;
    result__[ 194 ] = -1;
    result__[ 195 ] = 1;
    result__[ 196 ] = -1;
    result__[ 197 ] = 1;
    result__[ 198 ] = -1;
    result__[ 199 ] = 1;
    result__[ 200 ] = -1;
    result__[ 201 ] = 1;
    result__[ 202 ] = -1;
    result__[ 203 ] = 1;
    result__[ 204 ] = -1;
    result__[ 205 ] = 1;
    result__[ 206 ] = -1;
    result__[ 207 ] = 1;
    result__[ 208 ] = -1;
    result__[ 209 ] = 1;
    result__[ 210 ] = -1;
    result__[ 211 ] = 1;
    result__[ 212 ] = -1;
    result__[ 213 ] = 1;
    result__[ 214 ] = -1;
    result__[ 215 ] = 1;
    result__[ 216 ] = -1;
    result__[ 217 ] = 1;
    result__[ 218 ] = -1;
    result__[ 219 ] = 1;
    result__[ 220 ] = -1;
    result__[ 221 ] = 1;
    result__[ 222 ] = -1;
    result__[ 223 ] = 1;
    result__[ 224 ] = -1;
    result__[ 225 ] = 1;
    result__[ 226 ] = -1;
    result__[ 227 ] = 1;
    result__[ 228 ] = -1;
    result__[ 229 ] = 1;
    result__[ 230 ] = -1;
    result__[ 231 ] = 1;
    result__[ 232 ] = -1;
    result__[ 233 ] = 1;
    result__[ 234 ] = -1;
    result__[ 235 ] = 1;
    result__[ 236 ] = -1;
    result__[ 237 ] = 1;
    result__[ 238 ] = -1;
    result__[ 239 ] = 1;
    result__[ 240 ] = -1;
    result__[ 241 ] = 1;
    result__[ 242 ] = -1;
    result__[ 243 ] = 1;
    result__[ 244 ] = -1;
    result__[ 245 ] = 1;
    result__[ 246 ] = -1;
    result__[ 247 ] = 1;
    result__[ 248 ] = -1;
    result__[ 249 ] = 1;
    result__[ 250 ] = -1;
    result__[ 251 ] = 1;
    result__[ 252 ] = -1;
    result__[ 253 ] = 1;
    result__[ 254 ] = -1;
    result__[ 255 ] = 1;
    result__[ 256 ] = -1;
    result__[ 257 ] = 1;
    result__[ 258 ] = -1;
    result__[ 259 ] = 1;
    result__[ 260 ] = -1;
    result__[ 261 ] = 1;
    result__[ 262 ] = -1;
    result__[ 263 ] = 1;
    result__[ 264 ] = -1;
    result__[ 265 ] = 1;
    result__[ 266 ] = -1;
    result__[ 267 ] = 1;
    result__[ 268 ] = -1;
    result__[ 269 ] = 1;
    result__[ 270 ] = -1;
    result__[ 271 ] = 1;
    result__[ 272 ] = -1;
    result__[ 273 ] = 1;
    result__[ 274 ] = -1;
    result__[ 275 ] = 1;
    result__[ 276 ] = -1;
    result__[ 277 ] = 1;
    result__[ 278 ] = -1;
    result__[ 279 ] = 1;
    result__[ 280 ] = -1;
    result__[ 281 ] = 1;
    result__[ 282 ] = -1;
    result__[ 283 ] = 1;
    result__[ 284 ] = -1;
    result__[ 285 ] = 1;
    result__[ 286 ] = -1;
    result__[ 287 ] = 1;
    result__[ 288 ] = -1;
    result__[ 289 ] = 1;
    result__[ 290 ] = -1;
    result__[ 291 ] = 1;
    result__[ 292 ] = -1;
    result__[ 293 ] = 1;
    result__[ 294 ] = -1;
    result__[ 295 ] = 1;
    result__[ 296 ] = -1;
    result__[ 297 ] = 1;
    result__[ 298 ] = -1;
    result__[ 299 ] = 1;
    result__[ 300 ] = -1;
    result__[ 301 ] = 1;
    result__[ 302 ] = -1;
    result__[ 303 ] = 1;
    result__[ 304 ] = -1;
    result__[ 305 ] = 1;
    result__[ 306 ] = -1;
    result__[ 307 ] = 1;
    result__[ 308 ] = -1;
    result__[ 309 ] = 1;
    result__[ 310 ] = -1;
    result__[ 311 ] = 1;
    result__[ 312 ] = -1;
    result__[ 313 ] = 1;
    result__[ 314 ] = -1;
    result__[ 315 ] = 1;
    result__[ 316 ] = -1;
    result__[ 317 ] = 1;
    result__[ 318 ] = -1;
    result__[ 319 ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 320, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer ICLOCS_ContinuousMP::post_numEqns() const { return 120; }

  void
  ICLOCS_ContinuousMP::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
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
    Mechatronix::check_in_segment( result__, "post_eval", 120, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::integrated_post_numEqns() const { return 0; }

  void
  ICLOCS_ContinuousMP::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_problem.cc
