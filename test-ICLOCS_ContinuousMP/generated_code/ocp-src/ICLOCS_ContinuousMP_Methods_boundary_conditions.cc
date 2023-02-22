/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_boundary_conditions.cc             |
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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer ICLOCS_ContinuousMP::bc_numEqns() const { return 80; }

  void
  ICLOCS_ContinuousMP::bc_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
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
      Mechatronix::check_in_segment2( result__, "bc_eval", 80, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DbcDxxp_numRows() const { return 80; }
  integer ICLOCS_ContinuousMP::DbcDxxp_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DbcDxxp_nnz()     const { return 158; }

  void
  ICLOCS_ContinuousMP::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_ContinuousMP::DbcDxxp_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
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
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 158, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::D2bcD2xxp_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::D2bcD2xxp_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::D2bcD2xxp_nnz()     const { return 0; }

  void
  ICLOCS_ContinuousMP::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_ContinuousMP::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::fd_BC_numEqns() const { return 160; }

  void
  ICLOCS_ContinuousMP::fd_BC_eval(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
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
    real_type t1   = OMEGA__[40];
    result__[ 0   ] = t1 + LL__[iL_lambda1__xo];
    real_type t3   = OMEGA__[41];
    result__[ 1   ] = t3 + LL__[iL_lambda2__xo];
    real_type t5   = OMEGA__[42];
    result__[ 2   ] = t5 + LL__[iL_lambda3__xo];
    real_type t7   = OMEGA__[43];
    result__[ 3   ] = t7 + LL__[iL_lambda4__xo];
    real_type t9   = OMEGA__[44];
    result__[ 4   ] = t9 + LL__[iL_lambda5__xo];
    real_type t11  = OMEGA__[45];
    result__[ 5   ] = t11 + LL__[iL_lambda6__xo];
    real_type t13  = OMEGA__[46];
    result__[ 6   ] = t13 + LL__[iL_lambda7__xo];
    real_type t15  = OMEGA__[47];
    result__[ 7   ] = t15 + LL__[iL_lambda8__xo];
    real_type t17  = OMEGA__[48];
    result__[ 8   ] = t17 + LL__[iL_lambda9__xo];
    real_type t19  = OMEGA__[49];
    result__[ 9   ] = t19 + LL__[iL_lambda10__xo];
    real_type t21  = OMEGA__[50];
    result__[ 10  ] = t21 + LL__[iL_lambda11__xo];
    real_type t23  = OMEGA__[51];
    result__[ 11  ] = t23 + LL__[iL_lambda12__xo];
    real_type t25  = OMEGA__[52];
    result__[ 12  ] = t25 + LL__[iL_lambda13__xo];
    real_type t27  = OMEGA__[53];
    result__[ 13  ] = t27 + LL__[iL_lambda14__xo];
    real_type t29  = OMEGA__[54];
    result__[ 14  ] = t29 + LL__[iL_lambda15__xo];
    real_type t31  = OMEGA__[55];
    result__[ 15  ] = t31 + LL__[iL_lambda16__xo];
    real_type t33  = OMEGA__[56];
    result__[ 16  ] = t33 + LL__[iL_lambda17__xo];
    real_type t35  = OMEGA__[57];
    result__[ 17  ] = t35 + LL__[iL_lambda18__xo];
    real_type t37  = OMEGA__[58];
    result__[ 18  ] = t37 + LL__[iL_lambda19__xo];
    real_type t39  = OMEGA__[59];
    result__[ 19  ] = t39 + LL__[iL_lambda20__xo];
    real_type t41  = OMEGA__[60];
    result__[ 20  ] = t41 + LL__[iL_lambda21__xo];
    real_type t43  = OMEGA__[61];
    result__[ 21  ] = t43 + LL__[iL_lambda22__xo];
    real_type t45  = OMEGA__[62];
    result__[ 22  ] = t45 + LL__[iL_lambda23__xo];
    real_type t47  = OMEGA__[63];
    result__[ 23  ] = t47 + LL__[iL_lambda24__xo];
    real_type t49  = OMEGA__[64];
    result__[ 24  ] = t49 + LL__[iL_lambda25__xo];
    real_type t51  = OMEGA__[65];
    result__[ 25  ] = t51 + LL__[iL_lambda26__xo];
    real_type t53  = OMEGA__[66];
    result__[ 26  ] = t53 + LL__[iL_lambda27__xo];
    real_type t55  = OMEGA__[67];
    result__[ 27  ] = t55 + LL__[iL_lambda28__xo];
    real_type t57  = OMEGA__[68];
    result__[ 28  ] = t57 + LL__[iL_lambda29__xo];
    real_type t59  = OMEGA__[69];
    result__[ 29  ] = t59 + LL__[iL_lambda30__xo];
    real_type t61  = OMEGA__[70];
    result__[ 30  ] = t61 + LL__[iL_lambda31__xo];
    real_type t63  = OMEGA__[71];
    result__[ 31  ] = t63 + LL__[iL_lambda32__xo];
    real_type t65  = OMEGA__[72];
    result__[ 32  ] = t65 + LL__[iL_lambda33__xo];
    real_type t67  = OMEGA__[73];
    result__[ 33  ] = t67 + LL__[iL_lambda34__xo];
    real_type t69  = OMEGA__[74];
    result__[ 34  ] = t69 + LL__[iL_lambda35__xo];
    real_type t71  = OMEGA__[75];
    result__[ 35  ] = t71 + LL__[iL_lambda36__xo];
    real_type t73  = OMEGA__[76];
    result__[ 36  ] = t73 + LL__[iL_lambda37__xo];
    real_type t75  = OMEGA__[77];
    result__[ 37  ] = t75 + LL__[iL_lambda38__xo];
    real_type t77  = OMEGA__[78];
    result__[ 38  ] = t77 + LL__[iL_lambda39__xo];
    real_type t79  = OMEGA__[79];
    result__[ 39  ] = t79 + LL__[iL_lambda40__xo];
    result__[ 40  ] = -t1 + OMEGA__[0] + LL__[iL_lambda41__xo];
    real_type t83  = OMEGA__[2];
    result__[ 41  ] = -t3 - t83 + LL__[iL_lambda42__xo];
    real_type t85  = OMEGA__[3];
    result__[ 42  ] = -t5 - t85 + LL__[iL_lambda43__xo];
    real_type t87  = OMEGA__[4];
    result__[ 43  ] = -t7 - t87 + LL__[iL_lambda44__xo];
    real_type t89  = OMEGA__[5];
    result__[ 44  ] = -t9 - t89 + LL__[iL_lambda45__xo];
    real_type t91  = OMEGA__[6];
    result__[ 45  ] = -t11 - t91 + LL__[iL_lambda46__xo];
    real_type t93  = OMEGA__[7];
    result__[ 46  ] = -t13 - t93 + LL__[iL_lambda47__xo];
    real_type t95  = OMEGA__[8];
    result__[ 47  ] = -t15 - t95 + LL__[iL_lambda48__xo];
    real_type t97  = OMEGA__[9];
    result__[ 48  ] = -t17 - t97 + LL__[iL_lambda49__xo];
    real_type t99  = OMEGA__[10];
    result__[ 49  ] = -t19 - t99 + LL__[iL_lambda50__xo];
    real_type t101 = OMEGA__[11];
    result__[ 50  ] = -t21 - t101 + LL__[iL_lambda51__xo];
    real_type t103 = OMEGA__[12];
    result__[ 51  ] = -t23 - t103 + LL__[iL_lambda52__xo];
    real_type t105 = OMEGA__[13];
    result__[ 52  ] = -t25 - t105 + LL__[iL_lambda53__xo];
    real_type t107 = OMEGA__[14];
    result__[ 53  ] = -t107 - t27 + LL__[iL_lambda54__xo];
    real_type t109 = OMEGA__[15];
    result__[ 54  ] = -t109 - t29 + LL__[iL_lambda55__xo];
    real_type t111 = OMEGA__[16];
    result__[ 55  ] = -t111 - t31 + LL__[iL_lambda56__xo];
    real_type t113 = OMEGA__[17];
    result__[ 56  ] = -t113 - t33 + LL__[iL_lambda57__xo];
    real_type t115 = OMEGA__[18];
    result__[ 57  ] = -t115 - t35 + LL__[iL_lambda58__xo];
    real_type t117 = OMEGA__[19];
    result__[ 58  ] = -t117 - t37 + LL__[iL_lambda59__xo];
    real_type t119 = OMEGA__[20];
    result__[ 59  ] = -t119 - t39 + LL__[iL_lambda60__xo];
    result__[ 60  ] = -t41 + OMEGA__[1] + LL__[iL_lambda61__xo];
    real_type t123 = OMEGA__[21];
    result__[ 61  ] = -t123 - t43 + LL__[iL_lambda62__xo];
    real_type t125 = OMEGA__[22];
    result__[ 62  ] = -t125 - t45 + LL__[iL_lambda63__xo];
    real_type t127 = OMEGA__[23];
    result__[ 63  ] = -t127 - t47 + LL__[iL_lambda64__xo];
    real_type t129 = OMEGA__[24];
    result__[ 64  ] = -t129 - t49 + LL__[iL_lambda65__xo];
    real_type t131 = OMEGA__[25];
    result__[ 65  ] = -t131 - t51 + LL__[iL_lambda66__xo];
    real_type t133 = OMEGA__[26];
    result__[ 66  ] = -t133 - t53 + LL__[iL_lambda67__xo];
    real_type t135 = OMEGA__[27];
    result__[ 67  ] = -t135 - t55 + LL__[iL_lambda68__xo];
    real_type t137 = OMEGA__[28];
    result__[ 68  ] = -t137 - t57 + LL__[iL_lambda69__xo];
    real_type t139 = OMEGA__[29];
    result__[ 69  ] = -t139 - t59 + LL__[iL_lambda70__xo];
    real_type t141 = OMEGA__[30];
    result__[ 70  ] = -t141 - t61 + LL__[iL_lambda71__xo];
    real_type t143 = OMEGA__[31];
    result__[ 71  ] = -t143 - t63 + LL__[iL_lambda72__xo];
    real_type t145 = OMEGA__[32];
    result__[ 72  ] = -t145 - t65 + LL__[iL_lambda73__xo];
    real_type t147 = OMEGA__[33];
    result__[ 73  ] = -t147 - t67 + LL__[iL_lambda74__xo];
    real_type t149 = OMEGA__[34];
    result__[ 74  ] = -t149 - t69 + LL__[iL_lambda75__xo];
    real_type t151 = OMEGA__[35];
    result__[ 75  ] = -t151 - t71 + LL__[iL_lambda76__xo];
    real_type t153 = OMEGA__[36];
    result__[ 76  ] = -t153 - t73 + LL__[iL_lambda77__xo];
    real_type t155 = OMEGA__[37];
    result__[ 77  ] = -t155 - t75 + LL__[iL_lambda78__xo];
    real_type t157 = OMEGA__[38];
    result__[ 78  ] = -t157 - t77 + LL__[iL_lambda79__xo];
    real_type t159 = OMEGA__[39];
    result__[ 79  ] = -t159 - t79 + LL__[iL_lambda80__xo];
    result__[ 80  ] = -LR__[iL_lambda1__xo];
    result__[ 81  ] = -LR__[iL_lambda2__xo];
    result__[ 82  ] = -LR__[iL_lambda3__xo];
    result__[ 83  ] = -LR__[iL_lambda4__xo];
    result__[ 84  ] = -LR__[iL_lambda5__xo];
    result__[ 85  ] = -LR__[iL_lambda6__xo];
    result__[ 86  ] = -LR__[iL_lambda7__xo];
    result__[ 87  ] = -LR__[iL_lambda8__xo];
    result__[ 88  ] = -LR__[iL_lambda9__xo];
    result__[ 89  ] = -LR__[iL_lambda10__xo];
    result__[ 90  ] = -LR__[iL_lambda11__xo];
    result__[ 91  ] = -LR__[iL_lambda12__xo];
    result__[ 92  ] = -LR__[iL_lambda13__xo];
    result__[ 93  ] = -LR__[iL_lambda14__xo];
    result__[ 94  ] = -LR__[iL_lambda15__xo];
    result__[ 95  ] = -LR__[iL_lambda16__xo];
    result__[ 96  ] = -LR__[iL_lambda17__xo];
    result__[ 97  ] = -LR__[iL_lambda18__xo];
    result__[ 98  ] = -LR__[iL_lambda19__xo];
    result__[ 99  ] = -LR__[iL_lambda20__xo];
    result__[ 100 ] = -LR__[iL_lambda21__xo];
    result__[ 101 ] = -LR__[iL_lambda22__xo];
    result__[ 102 ] = -LR__[iL_lambda23__xo];
    result__[ 103 ] = -LR__[iL_lambda24__xo];
    result__[ 104 ] = -LR__[iL_lambda25__xo];
    result__[ 105 ] = -LR__[iL_lambda26__xo];
    result__[ 106 ] = -LR__[iL_lambda27__xo];
    result__[ 107 ] = -LR__[iL_lambda28__xo];
    result__[ 108 ] = -LR__[iL_lambda29__xo];
    result__[ 109 ] = -LR__[iL_lambda30__xo];
    result__[ 110 ] = -LR__[iL_lambda31__xo];
    result__[ 111 ] = -LR__[iL_lambda32__xo];
    result__[ 112 ] = -LR__[iL_lambda33__xo];
    result__[ 113 ] = -LR__[iL_lambda34__xo];
    result__[ 114 ] = -LR__[iL_lambda35__xo];
    result__[ 115 ] = -LR__[iL_lambda36__xo];
    result__[ 116 ] = -LR__[iL_lambda37__xo];
    result__[ 117 ] = -LR__[iL_lambda38__xo];
    result__[ 118 ] = -LR__[iL_lambda39__xo];
    result__[ 119 ] = -LR__[iL_lambda40__xo];
    result__[ 120 ] = t83 - LR__[iL_lambda41__xo];
    result__[ 121 ] = t85 - LR__[iL_lambda42__xo];
    result__[ 122 ] = t87 - LR__[iL_lambda43__xo];
    result__[ 123 ] = t89 - LR__[iL_lambda44__xo];
    result__[ 124 ] = t91 - LR__[iL_lambda45__xo];
    result__[ 125 ] = t93 - LR__[iL_lambda46__xo];
    result__[ 126 ] = t95 - LR__[iL_lambda47__xo];
    result__[ 127 ] = t97 - LR__[iL_lambda48__xo];
    result__[ 128 ] = t99 - LR__[iL_lambda49__xo];
    result__[ 129 ] = t101 - LR__[iL_lambda50__xo];
    result__[ 130 ] = t103 - LR__[iL_lambda51__xo];
    result__[ 131 ] = t105 - LR__[iL_lambda52__xo];
    result__[ 132 ] = t107 - LR__[iL_lambda53__xo];
    result__[ 133 ] = t109 - LR__[iL_lambda54__xo];
    result__[ 134 ] = t111 - LR__[iL_lambda55__xo];
    result__[ 135 ] = t113 - LR__[iL_lambda56__xo];
    result__[ 136 ] = t115 - LR__[iL_lambda57__xo];
    result__[ 137 ] = t117 - LR__[iL_lambda58__xo];
    result__[ 138 ] = t119 - LR__[iL_lambda59__xo];
    result__[ 139 ] = -LR__[iL_lambda60__xo];
    result__[ 140 ] = t123 - LR__[iL_lambda61__xo];
    result__[ 141 ] = t125 - LR__[iL_lambda62__xo];
    result__[ 142 ] = t127 - LR__[iL_lambda63__xo];
    result__[ 143 ] = t129 - LR__[iL_lambda64__xo];
    result__[ 144 ] = t131 - LR__[iL_lambda65__xo];
    result__[ 145 ] = t133 - LR__[iL_lambda66__xo];
    result__[ 146 ] = t135 - LR__[iL_lambda67__xo];
    result__[ 147 ] = t137 - LR__[iL_lambda68__xo];
    result__[ 148 ] = t139 - LR__[iL_lambda69__xo];
    result__[ 149 ] = t141 - LR__[iL_lambda70__xo];
    result__[ 150 ] = t143 - LR__[iL_lambda71__xo];
    result__[ 151 ] = t145 - LR__[iL_lambda72__xo];
    result__[ 152 ] = t147 - LR__[iL_lambda73__xo];
    result__[ 153 ] = t149 - LR__[iL_lambda74__xo];
    result__[ 154 ] = t151 - LR__[iL_lambda75__xo];
    result__[ 155 ] = t153 - LR__[iL_lambda76__xo];
    result__[ 156 ] = t155 - LR__[iL_lambda77__xo];
    result__[ 157 ] = t157 - LR__[iL_lambda78__xo];
    result__[ 158 ] = t159 - LR__[iL_lambda79__xo];
    result__[ 159 ] = -LR__[iL_lambda80__xo];
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
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 80, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::Dfd_BCDxlxlp_numRows() const { return 180; }
  integer ICLOCS_ContinuousMP::Dfd_BCDxlxlp_numCols() const { return 340; }
  integer ICLOCS_ContinuousMP::Dfd_BCDxlxlp_nnz()     const { return 160; }

  void
  ICLOCS_ContinuousMP::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 80  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 81  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 82  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 83  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 84  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 85  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 86  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 87  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 88  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 89  ;
    iIndex[10] = 10  ; jIndex[10] = 90  ;
    iIndex[11] = 11  ; jIndex[11] = 91  ;
    iIndex[12] = 12  ; jIndex[12] = 92  ;
    iIndex[13] = 13  ; jIndex[13] = 93  ;
    iIndex[14] = 14  ; jIndex[14] = 94  ;
    iIndex[15] = 15  ; jIndex[15] = 95  ;
    iIndex[16] = 16  ; jIndex[16] = 96  ;
    iIndex[17] = 17  ; jIndex[17] = 97  ;
    iIndex[18] = 18  ; jIndex[18] = 98  ;
    iIndex[19] = 19  ; jIndex[19] = 99  ;
    iIndex[20] = 20  ; jIndex[20] = 100 ;
    iIndex[21] = 21  ; jIndex[21] = 101 ;
    iIndex[22] = 22  ; jIndex[22] = 102 ;
    iIndex[23] = 23  ; jIndex[23] = 103 ;
    iIndex[24] = 24  ; jIndex[24] = 104 ;
    iIndex[25] = 25  ; jIndex[25] = 105 ;
    iIndex[26] = 26  ; jIndex[26] = 106 ;
    iIndex[27] = 27  ; jIndex[27] = 107 ;
    iIndex[28] = 28  ; jIndex[28] = 108 ;
    iIndex[29] = 29  ; jIndex[29] = 109 ;
    iIndex[30] = 30  ; jIndex[30] = 110 ;
    iIndex[31] = 31  ; jIndex[31] = 111 ;
    iIndex[32] = 32  ; jIndex[32] = 112 ;
    iIndex[33] = 33  ; jIndex[33] = 113 ;
    iIndex[34] = 34  ; jIndex[34] = 114 ;
    iIndex[35] = 35  ; jIndex[35] = 115 ;
    iIndex[36] = 36  ; jIndex[36] = 116 ;
    iIndex[37] = 37  ; jIndex[37] = 117 ;
    iIndex[38] = 38  ; jIndex[38] = 118 ;
    iIndex[39] = 39  ; jIndex[39] = 119 ;
    iIndex[40] = 40  ; jIndex[40] = 120 ;
    iIndex[41] = 41  ; jIndex[41] = 121 ;
    iIndex[42] = 42  ; jIndex[42] = 122 ;
    iIndex[43] = 43  ; jIndex[43] = 123 ;
    iIndex[44] = 44  ; jIndex[44] = 124 ;
    iIndex[45] = 45  ; jIndex[45] = 125 ;
    iIndex[46] = 46  ; jIndex[46] = 126 ;
    iIndex[47] = 47  ; jIndex[47] = 127 ;
    iIndex[48] = 48  ; jIndex[48] = 128 ;
    iIndex[49] = 49  ; jIndex[49] = 129 ;
    iIndex[50] = 50  ; jIndex[50] = 130 ;
    iIndex[51] = 51  ; jIndex[51] = 131 ;
    iIndex[52] = 52  ; jIndex[52] = 132 ;
    iIndex[53] = 53  ; jIndex[53] = 133 ;
    iIndex[54] = 54  ; jIndex[54] = 134 ;
    iIndex[55] = 55  ; jIndex[55] = 135 ;
    iIndex[56] = 56  ; jIndex[56] = 136 ;
    iIndex[57] = 57  ; jIndex[57] = 137 ;
    iIndex[58] = 58  ; jIndex[58] = 138 ;
    iIndex[59] = 59  ; jIndex[59] = 139 ;
    iIndex[60] = 60  ; jIndex[60] = 140 ;
    iIndex[61] = 61  ; jIndex[61] = 141 ;
    iIndex[62] = 62  ; jIndex[62] = 142 ;
    iIndex[63] = 63  ; jIndex[63] = 143 ;
    iIndex[64] = 64  ; jIndex[64] = 144 ;
    iIndex[65] = 65  ; jIndex[65] = 145 ;
    iIndex[66] = 66  ; jIndex[66] = 146 ;
    iIndex[67] = 67  ; jIndex[67] = 147 ;
    iIndex[68] = 68  ; jIndex[68] = 148 ;
    iIndex[69] = 69  ; jIndex[69] = 149 ;
    iIndex[70] = 70  ; jIndex[70] = 150 ;
    iIndex[71] = 71  ; jIndex[71] = 151 ;
    iIndex[72] = 72  ; jIndex[72] = 152 ;
    iIndex[73] = 73  ; jIndex[73] = 153 ;
    iIndex[74] = 74  ; jIndex[74] = 154 ;
    iIndex[75] = 75  ; jIndex[75] = 155 ;
    iIndex[76] = 76  ; jIndex[76] = 156 ;
    iIndex[77] = 77  ; jIndex[77] = 157 ;
    iIndex[78] = 78  ; jIndex[78] = 158 ;
    iIndex[79] = 79  ; jIndex[79] = 159 ;
    iIndex[80] = 80  ; jIndex[80] = 240 ;
    iIndex[81] = 81  ; jIndex[81] = 241 ;
    iIndex[82] = 82  ; jIndex[82] = 242 ;
    iIndex[83] = 83  ; jIndex[83] = 243 ;
    iIndex[84] = 84  ; jIndex[84] = 244 ;
    iIndex[85] = 85  ; jIndex[85] = 245 ;
    iIndex[86] = 86  ; jIndex[86] = 246 ;
    iIndex[87] = 87  ; jIndex[87] = 247 ;
    iIndex[88] = 88  ; jIndex[88] = 248 ;
    iIndex[89] = 89  ; jIndex[89] = 249 ;
    iIndex[90] = 90  ; jIndex[90] = 250 ;
    iIndex[91] = 91  ; jIndex[91] = 251 ;
    iIndex[92] = 92  ; jIndex[92] = 252 ;
    iIndex[93] = 93  ; jIndex[93] = 253 ;
    iIndex[94] = 94  ; jIndex[94] = 254 ;
    iIndex[95] = 95  ; jIndex[95] = 255 ;
    iIndex[96] = 96  ; jIndex[96] = 256 ;
    iIndex[97] = 97  ; jIndex[97] = 257 ;
    iIndex[98] = 98  ; jIndex[98] = 258 ;
    iIndex[99] = 99  ; jIndex[99] = 259 ;
    iIndex[100] = 100 ; jIndex[100] = 260 ;
    iIndex[101] = 101 ; jIndex[101] = 261 ;
    iIndex[102] = 102 ; jIndex[102] = 262 ;
    iIndex[103] = 103 ; jIndex[103] = 263 ;
    iIndex[104] = 104 ; jIndex[104] = 264 ;
    iIndex[105] = 105 ; jIndex[105] = 265 ;
    iIndex[106] = 106 ; jIndex[106] = 266 ;
    iIndex[107] = 107 ; jIndex[107] = 267 ;
    iIndex[108] = 108 ; jIndex[108] = 268 ;
    iIndex[109] = 109 ; jIndex[109] = 269 ;
    iIndex[110] = 110 ; jIndex[110] = 270 ;
    iIndex[111] = 111 ; jIndex[111] = 271 ;
    iIndex[112] = 112 ; jIndex[112] = 272 ;
    iIndex[113] = 113 ; jIndex[113] = 273 ;
    iIndex[114] = 114 ; jIndex[114] = 274 ;
    iIndex[115] = 115 ; jIndex[115] = 275 ;
    iIndex[116] = 116 ; jIndex[116] = 276 ;
    iIndex[117] = 117 ; jIndex[117] = 277 ;
    iIndex[118] = 118 ; jIndex[118] = 278 ;
    iIndex[119] = 119 ; jIndex[119] = 279 ;
    iIndex[120] = 120 ; jIndex[120] = 280 ;
    iIndex[121] = 121 ; jIndex[121] = 281 ;
    iIndex[122] = 122 ; jIndex[122] = 282 ;
    iIndex[123] = 123 ; jIndex[123] = 283 ;
    iIndex[124] = 124 ; jIndex[124] = 284 ;
    iIndex[125] = 125 ; jIndex[125] = 285 ;
    iIndex[126] = 126 ; jIndex[126] = 286 ;
    iIndex[127] = 127 ; jIndex[127] = 287 ;
    iIndex[128] = 128 ; jIndex[128] = 288 ;
    iIndex[129] = 129 ; jIndex[129] = 289 ;
    iIndex[130] = 130 ; jIndex[130] = 290 ;
    iIndex[131] = 131 ; jIndex[131] = 291 ;
    iIndex[132] = 132 ; jIndex[132] = 292 ;
    iIndex[133] = 133 ; jIndex[133] = 293 ;
    iIndex[134] = 134 ; jIndex[134] = 294 ;
    iIndex[135] = 135 ; jIndex[135] = 295 ;
    iIndex[136] = 136 ; jIndex[136] = 296 ;
    iIndex[137] = 137 ; jIndex[137] = 297 ;
    iIndex[138] = 138 ; jIndex[138] = 298 ;
    iIndex[139] = 139 ; jIndex[139] = 299 ;
    iIndex[140] = 140 ; jIndex[140] = 300 ;
    iIndex[141] = 141 ; jIndex[141] = 301 ;
    iIndex[142] = 142 ; jIndex[142] = 302 ;
    iIndex[143] = 143 ; jIndex[143] = 303 ;
    iIndex[144] = 144 ; jIndex[144] = 304 ;
    iIndex[145] = 145 ; jIndex[145] = 305 ;
    iIndex[146] = 146 ; jIndex[146] = 306 ;
    iIndex[147] = 147 ; jIndex[147] = 307 ;
    iIndex[148] = 148 ; jIndex[148] = 308 ;
    iIndex[149] = 149 ; jIndex[149] = 309 ;
    iIndex[150] = 150 ; jIndex[150] = 310 ;
    iIndex[151] = 151 ; jIndex[151] = 311 ;
    iIndex[152] = 152 ; jIndex[152] = 312 ;
    iIndex[153] = 153 ; jIndex[153] = 313 ;
    iIndex[154] = 154 ; jIndex[154] = 314 ;
    iIndex[155] = 155 ; jIndex[155] = 315 ;
    iIndex[156] = 156 ; jIndex[156] = 316 ;
    iIndex[157] = 157 ; jIndex[157] = 317 ;
    iIndex[158] = 158 ; jIndex[158] = 318 ;
    iIndex[159] = 159 ; jIndex[159] = 319 ;
  }


  void
  ICLOCS_ContinuousMP::Dfd_BCDxlxlp_sparse(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
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
    result__[ 80  ] = -1;
    result__[ 81  ] = -1;
    result__[ 82  ] = -1;
    result__[ 83  ] = -1;
    result__[ 84  ] = -1;
    result__[ 85  ] = -1;
    result__[ 86  ] = -1;
    result__[ 87  ] = -1;
    result__[ 88  ] = -1;
    result__[ 89  ] = -1;
    result__[ 90  ] = -1;
    result__[ 91  ] = -1;
    result__[ 92  ] = -1;
    result__[ 93  ] = -1;
    result__[ 94  ] = -1;
    result__[ 95  ] = -1;
    result__[ 96  ] = -1;
    result__[ 97  ] = -1;
    result__[ 98  ] = -1;
    result__[ 99  ] = -1;
    result__[ 100 ] = -1;
    result__[ 101 ] = -1;
    result__[ 102 ] = -1;
    result__[ 103 ] = -1;
    result__[ 104 ] = -1;
    result__[ 105 ] = -1;
    result__[ 106 ] = -1;
    result__[ 107 ] = -1;
    result__[ 108 ] = -1;
    result__[ 109 ] = -1;
    result__[ 110 ] = -1;
    result__[ 111 ] = -1;
    result__[ 112 ] = -1;
    result__[ 113 ] = -1;
    result__[ 114 ] = -1;
    result__[ 115 ] = -1;
    result__[ 116 ] = -1;
    result__[ 117 ] = -1;
    result__[ 118 ] = -1;
    result__[ 119 ] = -1;
    result__[ 120 ] = -1;
    result__[ 121 ] = -1;
    result__[ 122 ] = -1;
    result__[ 123 ] = -1;
    result__[ 124 ] = -1;
    result__[ 125 ] = -1;
    result__[ 126 ] = -1;
    result__[ 127 ] = -1;
    result__[ 128 ] = -1;
    result__[ 129 ] = -1;
    result__[ 130 ] = -1;
    result__[ 131 ] = -1;
    result__[ 132 ] = -1;
    result__[ 133 ] = -1;
    result__[ 134 ] = -1;
    result__[ 135 ] = -1;
    result__[ 136 ] = -1;
    result__[ 137 ] = -1;
    result__[ 138 ] = -1;
    result__[ 139 ] = -1;
    result__[ 140 ] = -1;
    result__[ 141 ] = -1;
    result__[ 142 ] = -1;
    result__[ 143 ] = -1;
    result__[ 144 ] = -1;
    result__[ 145 ] = -1;
    result__[ 146 ] = -1;
    result__[ 147 ] = -1;
    result__[ 148 ] = -1;
    result__[ 149 ] = -1;
    result__[ 150 ] = -1;
    result__[ 151 ] = -1;
    result__[ 152 ] = -1;
    result__[ 153 ] = -1;
    result__[ 154 ] = -1;
    result__[ 155 ] = -1;
    result__[ 156 ] = -1;
    result__[ 157 ] = -1;
    result__[ 158 ] = -1;
    result__[ 159 ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 160, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: ICLOCS_ContinuousMP_Methods_boundary_conditions.cc
