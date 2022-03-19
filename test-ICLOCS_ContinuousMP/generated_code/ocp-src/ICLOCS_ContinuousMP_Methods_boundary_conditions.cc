/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_boundary_conditions.cc             |
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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer ICLOCS_ContinuousMP::boundaryConditions_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XL__[iX_xx1];
    result__[ 0   ] = t1 - 1;
    real_type t2   = XL__[iX_yy1];
    result__[ 1   ] = t2 - 1;
    real_type t4   = XL__[iX_xx2];
    result__[ 2   ] = XR__[iX_xx1] - t4;
    real_type t6   = XL__[iX_xx3];
    result__[ 3   ] = XR__[iX_xx2] - t6;
    real_type t8   = XL__[iX_xx4];
    result__[ 4   ] = XR__[iX_xx3] - t8;
    real_type t10  = XL__[iX_xx5];
    result__[ 5   ] = XR__[iX_xx4] - t10;
    real_type t12  = XL__[iX_xx6];
    result__[ 6   ] = XR__[iX_xx5] - t12;
    real_type t14  = XL__[iX_xx7];
    result__[ 7   ] = XR__[iX_xx6] - t14;
    real_type t16  = XL__[iX_xx8];
    result__[ 8   ] = XR__[iX_xx7] - t16;
    real_type t18  = XL__[iX_xx9];
    result__[ 9   ] = XR__[iX_xx8] - t18;
    real_type t20  = XL__[iX_xx10];
    result__[ 10  ] = XR__[iX_xx9] - t20;
    real_type t22  = XL__[iX_xx11];
    result__[ 11  ] = XR__[iX_xx10] - t22;
    real_type t24  = XL__[iX_xx12];
    result__[ 12  ] = XR__[iX_xx11] - t24;
    real_type t26  = XL__[iX_xx13];
    result__[ 13  ] = XR__[iX_xx12] - t26;
    real_type t28  = XL__[iX_xx14];
    result__[ 14  ] = XR__[iX_xx13] - t28;
    real_type t30  = XL__[iX_xx15];
    result__[ 15  ] = XR__[iX_xx14] - t30;
    real_type t32  = XL__[iX_xx16];
    result__[ 16  ] = XR__[iX_xx15] - t32;
    real_type t34  = XL__[iX_xx17];
    result__[ 17  ] = XR__[iX_xx16] - t34;
    real_type t36  = XL__[iX_xx18];
    result__[ 18  ] = XR__[iX_xx17] - t36;
    real_type t38  = XL__[iX_xx19];
    result__[ 19  ] = XR__[iX_xx18] - t38;
    real_type t40  = XL__[iX_xx20];
    result__[ 20  ] = XR__[iX_xx19] - t40;
    real_type t42  = XL__[iX_yy2];
    result__[ 21  ] = XR__[iX_yy1] - t42;
    real_type t44  = XL__[iX_yy3];
    result__[ 22  ] = XR__[iX_yy2] - t44;
    real_type t46  = XL__[iX_yy4];
    result__[ 23  ] = XR__[iX_yy3] - t46;
    real_type t48  = XL__[iX_yy5];
    result__[ 24  ] = XR__[iX_yy4] - t48;
    real_type t50  = XL__[iX_yy6];
    result__[ 25  ] = XR__[iX_yy5] - t50;
    real_type t52  = XL__[iX_yy7];
    result__[ 26  ] = XR__[iX_yy6] - t52;
    real_type t54  = XL__[iX_yy8];
    result__[ 27  ] = XR__[iX_yy7] - t54;
    real_type t56  = XL__[iX_yy9];
    result__[ 28  ] = XR__[iX_yy8] - t56;
    real_type t58  = XL__[iX_yy10];
    result__[ 29  ] = XR__[iX_yy9] - t58;
    real_type t60  = XL__[iX_yy11];
    result__[ 30  ] = XR__[iX_yy10] - t60;
    real_type t62  = XL__[iX_yy12];
    result__[ 31  ] = XR__[iX_yy11] - t62;
    real_type t64  = XL__[iX_yy13];
    result__[ 32  ] = XR__[iX_yy12] - t64;
    real_type t66  = XL__[iX_yy14];
    result__[ 33  ] = XR__[iX_yy13] - t66;
    real_type t68  = XL__[iX_yy15];
    result__[ 34  ] = XR__[iX_yy14] - t68;
    real_type t70  = XL__[iX_yy16];
    result__[ 35  ] = XR__[iX_yy15] - t70;
    real_type t72  = XL__[iX_yy17];
    result__[ 36  ] = XR__[iX_yy16] - t72;
    real_type t74  = XL__[iX_yy18];
    result__[ 37  ] = XR__[iX_yy17] - t74;
    real_type t76  = XL__[iX_yy19];
    result__[ 38  ] = XR__[iX_yy18] - t76;
    real_type t78  = XL__[iX_yy20];
    result__[ 39  ] = XR__[iX_yy19] - t78;
    result__[ 40  ] = XL__[iX_x1] - t1;
    result__[ 41  ] = XL__[iX_x2] - t4;
    result__[ 42  ] = XL__[iX_x3] - t6;
    result__[ 43  ] = XL__[iX_x4] - t8;
    result__[ 44  ] = XL__[iX_x5] - t10;
    result__[ 45  ] = XL__[iX_x6] - t12;
    result__[ 46  ] = XL__[iX_x7] - t14;
    result__[ 47  ] = XL__[iX_x8] - t16;
    result__[ 48  ] = XL__[iX_x9] - t18;
    result__[ 49  ] = XL__[iX_x10] - t20;
    result__[ 50  ] = XL__[iX_x11] - t22;
    result__[ 51  ] = XL__[iX_x12] - t24;
    result__[ 52  ] = XL__[iX_x13] - t26;
    result__[ 53  ] = XL__[iX_x14] - t28;
    result__[ 54  ] = XL__[iX_x15] - t30;
    result__[ 55  ] = XL__[iX_x16] - t32;
    result__[ 56  ] = XL__[iX_x17] - t34;
    result__[ 57  ] = XL__[iX_x18] - t36;
    result__[ 58  ] = XL__[iX_x19] - t38;
    result__[ 59  ] = XL__[iX_x20] - t40;
    result__[ 60  ] = XL__[iX_y1] - t2;
    result__[ 61  ] = XL__[iX_y2] - t42;
    result__[ 62  ] = XL__[iX_y3] - t44;
    result__[ 63  ] = XL__[iX_y4] - t46;
    result__[ 64  ] = XL__[iX_y5] - t48;
    result__[ 65  ] = XL__[iX_y6] - t50;
    result__[ 66  ] = XL__[iX_y7] - t52;
    result__[ 67  ] = XL__[iX_y8] - t54;
    result__[ 68  ] = XL__[iX_y9] - t56;
    result__[ 69  ] = XL__[iX_y10] - t58;
    result__[ 70  ] = XL__[iX_y11] - t60;
    result__[ 71  ] = XL__[iX_y12] - t62;
    result__[ 72  ] = XL__[iX_y13] - t64;
    result__[ 73  ] = XL__[iX_y14] - t66;
    result__[ 74  ] = XL__[iX_y15] - t68;
    result__[ 75  ] = XL__[iX_y16] - t70;
    result__[ 76  ] = XL__[iX_y17] - t72;
    result__[ 77  ] = XL__[iX_y18] - t74;
    result__[ 78  ] = XL__[iX_y19] - t76;
    result__[ 79  ] = XL__[iX_y20] - t78;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 80, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DboundaryConditionsDxxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DboundaryConditionsDxxp_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DboundaryConditionsDxxp_nnz()     const { return 158; }

  void
  ICLOCS_ContinuousMP::DboundaryConditionsDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 40  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 60  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 41  ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 120 ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 42  ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 121 ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 43  ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 122 ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 44  ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 123 ;
    iIndex[10] = 6   ; jIndex[10] = 45  ;
    iIndex[11] = 6   ; jIndex[11] = 124 ;
    iIndex[12] = 7   ; jIndex[12] = 46  ;
    iIndex[13] = 7   ; jIndex[13] = 125 ;
    iIndex[14] = 8   ; jIndex[14] = 47  ;
    iIndex[15] = 8   ; jIndex[15] = 126 ;
    iIndex[16] = 9   ; jIndex[16] = 48  ;
    iIndex[17] = 9   ; jIndex[17] = 127 ;
    iIndex[18] = 10  ; jIndex[18] = 49  ;
    iIndex[19] = 10  ; jIndex[19] = 128 ;
    iIndex[20] = 11  ; jIndex[20] = 50  ;
    iIndex[21] = 11  ; jIndex[21] = 129 ;
    iIndex[22] = 12  ; jIndex[22] = 51  ;
    iIndex[23] = 12  ; jIndex[23] = 130 ;
    iIndex[24] = 13  ; jIndex[24] = 52  ;
    iIndex[25] = 13  ; jIndex[25] = 131 ;
    iIndex[26] = 14  ; jIndex[26] = 53  ;
    iIndex[27] = 14  ; jIndex[27] = 132 ;
    iIndex[28] = 15  ; jIndex[28] = 54  ;
    iIndex[29] = 15  ; jIndex[29] = 133 ;
    iIndex[30] = 16  ; jIndex[30] = 55  ;
    iIndex[31] = 16  ; jIndex[31] = 134 ;
    iIndex[32] = 17  ; jIndex[32] = 56  ;
    iIndex[33] = 17  ; jIndex[33] = 135 ;
    iIndex[34] = 18  ; jIndex[34] = 57  ;
    iIndex[35] = 18  ; jIndex[35] = 136 ;
    iIndex[36] = 19  ; jIndex[36] = 58  ;
    iIndex[37] = 19  ; jIndex[37] = 137 ;
    iIndex[38] = 20  ; jIndex[38] = 59  ;
    iIndex[39] = 20  ; jIndex[39] = 138 ;
    iIndex[40] = 21  ; jIndex[40] = 61  ;
    iIndex[41] = 21  ; jIndex[41] = 140 ;
    iIndex[42] = 22  ; jIndex[42] = 62  ;
    iIndex[43] = 22  ; jIndex[43] = 141 ;
    iIndex[44] = 23  ; jIndex[44] = 63  ;
    iIndex[45] = 23  ; jIndex[45] = 142 ;
    iIndex[46] = 24  ; jIndex[46] = 64  ;
    iIndex[47] = 24  ; jIndex[47] = 143 ;
    iIndex[48] = 25  ; jIndex[48] = 65  ;
    iIndex[49] = 25  ; jIndex[49] = 144 ;
    iIndex[50] = 26  ; jIndex[50] = 66  ;
    iIndex[51] = 26  ; jIndex[51] = 145 ;
    iIndex[52] = 27  ; jIndex[52] = 67  ;
    iIndex[53] = 27  ; jIndex[53] = 146 ;
    iIndex[54] = 28  ; jIndex[54] = 68  ;
    iIndex[55] = 28  ; jIndex[55] = 147 ;
    iIndex[56] = 29  ; jIndex[56] = 69  ;
    iIndex[57] = 29  ; jIndex[57] = 148 ;
    iIndex[58] = 30  ; jIndex[58] = 70  ;
    iIndex[59] = 30  ; jIndex[59] = 149 ;
    iIndex[60] = 31  ; jIndex[60] = 71  ;
    iIndex[61] = 31  ; jIndex[61] = 150 ;
    iIndex[62] = 32  ; jIndex[62] = 72  ;
    iIndex[63] = 32  ; jIndex[63] = 151 ;
    iIndex[64] = 33  ; jIndex[64] = 73  ;
    iIndex[65] = 33  ; jIndex[65] = 152 ;
    iIndex[66] = 34  ; jIndex[66] = 74  ;
    iIndex[67] = 34  ; jIndex[67] = 153 ;
    iIndex[68] = 35  ; jIndex[68] = 75  ;
    iIndex[69] = 35  ; jIndex[69] = 154 ;
    iIndex[70] = 36  ; jIndex[70] = 76  ;
    iIndex[71] = 36  ; jIndex[71] = 155 ;
    iIndex[72] = 37  ; jIndex[72] = 77  ;
    iIndex[73] = 37  ; jIndex[73] = 156 ;
    iIndex[74] = 38  ; jIndex[74] = 78  ;
    iIndex[75] = 38  ; jIndex[75] = 157 ;
    iIndex[76] = 39  ; jIndex[76] = 79  ;
    iIndex[77] = 39  ; jIndex[77] = 158 ;
    iIndex[78] = 40  ; jIndex[78] = 0   ;
    iIndex[79] = 40  ; jIndex[79] = 40  ;
    iIndex[80] = 41  ; jIndex[80] = 1   ;
    iIndex[81] = 41  ; jIndex[81] = 41  ;
    iIndex[82] = 42  ; jIndex[82] = 2   ;
    iIndex[83] = 42  ; jIndex[83] = 42  ;
    iIndex[84] = 43  ; jIndex[84] = 3   ;
    iIndex[85] = 43  ; jIndex[85] = 43  ;
    iIndex[86] = 44  ; jIndex[86] = 4   ;
    iIndex[87] = 44  ; jIndex[87] = 44  ;
    iIndex[88] = 45  ; jIndex[88] = 5   ;
    iIndex[89] = 45  ; jIndex[89] = 45  ;
    iIndex[90] = 46  ; jIndex[90] = 6   ;
    iIndex[91] = 46  ; jIndex[91] = 46  ;
    iIndex[92] = 47  ; jIndex[92] = 7   ;
    iIndex[93] = 47  ; jIndex[93] = 47  ;
    iIndex[94] = 48  ; jIndex[94] = 8   ;
    iIndex[95] = 48  ; jIndex[95] = 48  ;
    iIndex[96] = 49  ; jIndex[96] = 9   ;
    iIndex[97] = 49  ; jIndex[97] = 49  ;
    iIndex[98] = 50  ; jIndex[98] = 10  ;
    iIndex[99] = 50  ; jIndex[99] = 50  ;
    iIndex[100] = 51  ; jIndex[100] = 11  ;
    iIndex[101] = 51  ; jIndex[101] = 51  ;
    iIndex[102] = 52  ; jIndex[102] = 12  ;
    iIndex[103] = 52  ; jIndex[103] = 52  ;
    iIndex[104] = 53  ; jIndex[104] = 13  ;
    iIndex[105] = 53  ; jIndex[105] = 53  ;
    iIndex[106] = 54  ; jIndex[106] = 14  ;
    iIndex[107] = 54  ; jIndex[107] = 54  ;
    iIndex[108] = 55  ; jIndex[108] = 15  ;
    iIndex[109] = 55  ; jIndex[109] = 55  ;
    iIndex[110] = 56  ; jIndex[110] = 16  ;
    iIndex[111] = 56  ; jIndex[111] = 56  ;
    iIndex[112] = 57  ; jIndex[112] = 17  ;
    iIndex[113] = 57  ; jIndex[113] = 57  ;
    iIndex[114] = 58  ; jIndex[114] = 18  ;
    iIndex[115] = 58  ; jIndex[115] = 58  ;
    iIndex[116] = 59  ; jIndex[116] = 19  ;
    iIndex[117] = 59  ; jIndex[117] = 59  ;
    iIndex[118] = 60  ; jIndex[118] = 20  ;
    iIndex[119] = 60  ; jIndex[119] = 60  ;
    iIndex[120] = 61  ; jIndex[120] = 21  ;
    iIndex[121] = 61  ; jIndex[121] = 61  ;
    iIndex[122] = 62  ; jIndex[122] = 22  ;
    iIndex[123] = 62  ; jIndex[123] = 62  ;
    iIndex[124] = 63  ; jIndex[124] = 23  ;
    iIndex[125] = 63  ; jIndex[125] = 63  ;
    iIndex[126] = 64  ; jIndex[126] = 24  ;
    iIndex[127] = 64  ; jIndex[127] = 64  ;
    iIndex[128] = 65  ; jIndex[128] = 25  ;
    iIndex[129] = 65  ; jIndex[129] = 65  ;
    iIndex[130] = 66  ; jIndex[130] = 26  ;
    iIndex[131] = 66  ; jIndex[131] = 66  ;
    iIndex[132] = 67  ; jIndex[132] = 27  ;
    iIndex[133] = 67  ; jIndex[133] = 67  ;
    iIndex[134] = 68  ; jIndex[134] = 28  ;
    iIndex[135] = 68  ; jIndex[135] = 68  ;
    iIndex[136] = 69  ; jIndex[136] = 29  ;
    iIndex[137] = 69  ; jIndex[137] = 69  ;
    iIndex[138] = 70  ; jIndex[138] = 30  ;
    iIndex[139] = 70  ; jIndex[139] = 70  ;
    iIndex[140] = 71  ; jIndex[140] = 31  ;
    iIndex[141] = 71  ; jIndex[141] = 71  ;
    iIndex[142] = 72  ; jIndex[142] = 32  ;
    iIndex[143] = 72  ; jIndex[143] = 72  ;
    iIndex[144] = 73  ; jIndex[144] = 33  ;
    iIndex[145] = 73  ; jIndex[145] = 73  ;
    iIndex[146] = 74  ; jIndex[146] = 34  ;
    iIndex[147] = 74  ; jIndex[147] = 74  ;
    iIndex[148] = 75  ; jIndex[148] = 35  ;
    iIndex[149] = 75  ; jIndex[149] = 75  ;
    iIndex[150] = 76  ; jIndex[150] = 36  ;
    iIndex[151] = 76  ; jIndex[151] = 76  ;
    iIndex[152] = 77  ; jIndex[152] = 37  ;
    iIndex[153] = 77  ; jIndex[153] = 77  ;
    iIndex[154] = 78  ; jIndex[154] = 38  ;
    iIndex[155] = 78  ; jIndex[155] = 78  ;
    iIndex[156] = 79  ; jIndex[156] = 39  ;
    iIndex[157] = 79  ; jIndex[157] = 79  ;
  }


  void
  ICLOCS_ContinuousMP::DboundaryConditionsDxxp_sparse(
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
    result__[ 0   ] = 1;
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
    result__[ 78  ] = 1;
    result__[ 79  ] = -1;
    result__[ 80  ] = 1;
    result__[ 81  ] = -1;
    result__[ 82  ] = 1;
    result__[ 83  ] = -1;
    result__[ 84  ] = 1;
    result__[ 85  ] = -1;
    result__[ 86  ] = 1;
    result__[ 87  ] = -1;
    result__[ 88  ] = 1;
    result__[ 89  ] = -1;
    result__[ 90  ] = 1;
    result__[ 91  ] = -1;
    result__[ 92  ] = 1;
    result__[ 93  ] = -1;
    result__[ 94  ] = 1;
    result__[ 95  ] = -1;
    result__[ 96  ] = 1;
    result__[ 97  ] = -1;
    result__[ 98  ] = 1;
    result__[ 99  ] = -1;
    result__[ 100 ] = 1;
    result__[ 101 ] = -1;
    result__[ 102 ] = 1;
    result__[ 103 ] = -1;
    result__[ 104 ] = 1;
    result__[ 105 ] = -1;
    result__[ 106 ] = 1;
    result__[ 107 ] = -1;
    result__[ 108 ] = 1;
    result__[ 109 ] = -1;
    result__[ 110 ] = 1;
    result__[ 111 ] = -1;
    result__[ 112 ] = 1;
    result__[ 113 ] = -1;
    result__[ 114 ] = 1;
    result__[ 115 ] = -1;
    result__[ 116 ] = 1;
    result__[ 117 ] = -1;
    result__[ 118 ] = 1;
    result__[ 119 ] = -1;
    result__[ 120 ] = 1;
    result__[ 121 ] = -1;
    result__[ 122 ] = 1;
    result__[ 123 ] = -1;
    result__[ 124 ] = 1;
    result__[ 125 ] = -1;
    result__[ 126 ] = 1;
    result__[ 127 ] = -1;
    result__[ 128 ] = 1;
    result__[ 129 ] = -1;
    result__[ 130 ] = 1;
    result__[ 131 ] = -1;
    result__[ 132 ] = 1;
    result__[ 133 ] = -1;
    result__[ 134 ] = 1;
    result__[ 135 ] = -1;
    result__[ 136 ] = 1;
    result__[ 137 ] = -1;
    result__[ 138 ] = 1;
    result__[ 139 ] = -1;
    result__[ 140 ] = 1;
    result__[ 141 ] = -1;
    result__[ 142 ] = 1;
    result__[ 143 ] = -1;
    result__[ 144 ] = 1;
    result__[ 145 ] = -1;
    result__[ 146 ] = 1;
    result__[ 147 ] = -1;
    result__[ 148 ] = 1;
    result__[ 149 ] = -1;
    result__[ 150 ] = 1;
    result__[ 151 ] = -1;
    result__[ 152 ] = 1;
    result__[ 153 ] = -1;
    result__[ 154 ] = 1;
    result__[ 155 ] = -1;
    result__[ 156 ] = 1;
    result__[ 157 ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxxp_sparse", 158, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::adjointBC_numEqns() const { return 180; }

  void
  ICLOCS_ContinuousMP::adjointBC_eval(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[40];
    result__[ 1   ] = OMEGA__[41];
    result__[ 2   ] = OMEGA__[42];
    result__[ 3   ] = OMEGA__[43];
    result__[ 4   ] = OMEGA__[44];
    result__[ 5   ] = OMEGA__[45];
    result__[ 6   ] = OMEGA__[46];
    result__[ 7   ] = OMEGA__[47];
    result__[ 8   ] = OMEGA__[48];
    result__[ 9   ] = OMEGA__[49];
    result__[ 10  ] = OMEGA__[50];
    result__[ 11  ] = OMEGA__[51];
    result__[ 12  ] = OMEGA__[52];
    result__[ 13  ] = OMEGA__[53];
    result__[ 14  ] = OMEGA__[54];
    result__[ 15  ] = OMEGA__[55];
    result__[ 16  ] = OMEGA__[56];
    result__[ 17  ] = OMEGA__[57];
    result__[ 18  ] = OMEGA__[58];
    result__[ 19  ] = OMEGA__[59];
    result__[ 20  ] = OMEGA__[60];
    result__[ 21  ] = OMEGA__[61];
    result__[ 22  ] = OMEGA__[62];
    result__[ 23  ] = OMEGA__[63];
    result__[ 24  ] = OMEGA__[64];
    result__[ 25  ] = OMEGA__[65];
    result__[ 26  ] = OMEGA__[66];
    result__[ 27  ] = OMEGA__[67];
    result__[ 28  ] = OMEGA__[68];
    result__[ 29  ] = OMEGA__[69];
    result__[ 30  ] = OMEGA__[70];
    result__[ 31  ] = OMEGA__[71];
    result__[ 32  ] = OMEGA__[72];
    result__[ 33  ] = OMEGA__[73];
    result__[ 34  ] = OMEGA__[74];
    result__[ 35  ] = OMEGA__[75];
    result__[ 36  ] = OMEGA__[76];
    result__[ 37  ] = OMEGA__[77];
    result__[ 38  ] = OMEGA__[78];
    result__[ 39  ] = OMEGA__[79];
    result__[ 40  ] = OMEGA__[0] - result__[0];
    real_type t2   = OMEGA__[2];
    result__[ 41  ] = -t2 - result__[1];
    real_type t3   = OMEGA__[3];
    result__[ 42  ] = -t3 - result__[2];
    real_type t4   = OMEGA__[4];
    result__[ 43  ] = -t4 - result__[3];
    real_type t5   = OMEGA__[5];
    result__[ 44  ] = -t5 - result__[4];
    real_type t6   = OMEGA__[6];
    result__[ 45  ] = -result__[5] - t6;
    real_type t7   = OMEGA__[7];
    result__[ 46  ] = -result__[6] - t7;
    real_type t8   = OMEGA__[8];
    result__[ 47  ] = -result__[7] - t8;
    real_type t9   = OMEGA__[9];
    result__[ 48  ] = -result__[8] - t9;
    real_type t10  = OMEGA__[10];
    result__[ 49  ] = -result__[9] - t10;
    real_type t11  = OMEGA__[11];
    result__[ 50  ] = -result__[10] - t11;
    real_type t12  = OMEGA__[12];
    result__[ 51  ] = -result__[11] - t12;
    real_type t13  = OMEGA__[13];
    result__[ 52  ] = -result__[12] - t13;
    real_type t14  = OMEGA__[14];
    result__[ 53  ] = -result__[13] - t14;
    real_type t15  = OMEGA__[15];
    result__[ 54  ] = -result__[14] - t15;
    real_type t16  = OMEGA__[16];
    result__[ 55  ] = -result__[15] - t16;
    real_type t17  = OMEGA__[17];
    result__[ 56  ] = -result__[16] - t17;
    real_type t18  = OMEGA__[18];
    result__[ 57  ] = -result__[17] - t18;
    real_type t19  = OMEGA__[19];
    result__[ 58  ] = -result__[18] - t19;
    real_type t20  = OMEGA__[20];
    result__[ 59  ] = -result__[19] - t20;
    result__[ 60  ] = -result__[20] + OMEGA__[1];
    real_type t22  = OMEGA__[21];
    result__[ 61  ] = -result__[21] - t22;
    real_type t23  = OMEGA__[22];
    result__[ 62  ] = -result__[22] - t23;
    real_type t24  = OMEGA__[23];
    result__[ 63  ] = -result__[23] - t24;
    real_type t25  = OMEGA__[24];
    result__[ 64  ] = -result__[24] - t25;
    real_type t26  = OMEGA__[25];
    result__[ 65  ] = -result__[25] - t26;
    real_type t27  = OMEGA__[26];
    result__[ 66  ] = -result__[26] - t27;
    real_type t28  = OMEGA__[27];
    result__[ 67  ] = -result__[27] - t28;
    real_type t29  = OMEGA__[28];
    result__[ 68  ] = -result__[28] - t29;
    real_type t30  = OMEGA__[29];
    result__[ 69  ] = -result__[29] - t30;
    real_type t31  = OMEGA__[30];
    result__[ 70  ] = -result__[30] - t31;
    real_type t32  = OMEGA__[31];
    result__[ 71  ] = -result__[31] - t32;
    real_type t33  = OMEGA__[32];
    result__[ 72  ] = -result__[32] - t33;
    real_type t34  = OMEGA__[33];
    result__[ 73  ] = -result__[33] - t34;
    real_type t35  = OMEGA__[34];
    result__[ 74  ] = -result__[34] - t35;
    real_type t36  = OMEGA__[35];
    result__[ 75  ] = -result__[35] - t36;
    real_type t37  = OMEGA__[36];
    result__[ 76  ] = -result__[36] - t37;
    real_type t38  = OMEGA__[37];
    result__[ 77  ] = -result__[37] - t38;
    real_type t39  = OMEGA__[38];
    result__[ 78  ] = -result__[38] - t39;
    real_type t40  = OMEGA__[39];
    result__[ 79  ] = -t40 - result__[39];
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
    result__[ 120 ] = t2;
    result__[ 121 ] = t3;
    result__[ 122 ] = t4;
    result__[ 123 ] = t5;
    result__[ 124 ] = t6;
    result__[ 125 ] = t7;
    result__[ 126 ] = t8;
    result__[ 127 ] = t9;
    result__[ 128 ] = t10;
    result__[ 129 ] = t11;
    result__[ 130 ] = t12;
    result__[ 131 ] = t13;
    result__[ 132 ] = t14;
    result__[ 133 ] = t15;
    result__[ 134 ] = t16;
    result__[ 135 ] = t17;
    result__[ 136 ] = t18;
    result__[ 137 ] = t19;
    result__[ 138 ] = t20;
    result__[ 139 ] = 0;
    result__[ 140 ] = t22;
    result__[ 141 ] = t23;
    result__[ 142 ] = t24;
    result__[ 143 ] = t25;
    result__[ 144 ] = t26;
    result__[ 145 ] = t27;
    result__[ 146 ] = t28;
    result__[ 147 ] = t29;
    result__[ 148 ] = t30;
    result__[ 149 ] = t31;
    result__[ 150 ] = t32;
    result__[ 151 ] = t33;
    result__[ 152 ] = t34;
    result__[ 153 ] = t35;
    result__[ 154 ] = t36;
    result__[ 155 ] = t37;
    result__[ 156 ] = t38;
    result__[ 157 ] = t39;
    result__[ 158 ] = t40;
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
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 180, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DadjointBCDxxp_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::DadjointBCDxxp_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DadjointBCDxxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::DadjointBCDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::DadjointBCDxxp_sparse(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }
}

// EOF: ICLOCS_ContinuousMP_Methods_boundary_conditions.cc
