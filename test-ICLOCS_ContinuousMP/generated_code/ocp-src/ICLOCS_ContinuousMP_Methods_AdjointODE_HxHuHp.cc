/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_AdjointODE.cc                      |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_ContinuousMP::Hxp_numEqns() const { return 100; }

  void
  ICLOCS_ContinuousMP::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t3   = MU__[20];
    real_type t4   = cos(t1);
    result__[ 0   ] = t4 * t3 + 40 * t1;
    real_type t6   = X__[iX_x2];
    real_type t8   = MU__[21];
    real_type t9   = cos(t6);
    result__[ 1   ] = t9 * t8 + 38 * t6;
    real_type t11  = X__[iX_x3];
    real_type t13  = MU__[22];
    real_type t14  = cos(t11);
    result__[ 2   ] = t14 * t13 + 36 * t11;
    real_type t16  = X__[iX_x4];
    real_type t18  = MU__[23];
    real_type t19  = cos(t16);
    result__[ 3   ] = t19 * t18 + 34 * t16;
    real_type t21  = X__[iX_x5];
    real_type t23  = MU__[24];
    real_type t24  = cos(t21);
    result__[ 4   ] = t24 * t23 + 32 * t21;
    real_type t26  = X__[iX_x6];
    real_type t28  = MU__[25];
    real_type t29  = cos(t26);
    result__[ 5   ] = t29 * t28 + 30 * t26;
    real_type t31  = X__[iX_x7];
    real_type t33  = MU__[26];
    real_type t34  = cos(t31);
    result__[ 6   ] = t34 * t33 + 28 * t31;
    real_type t36  = X__[iX_x8];
    real_type t38  = MU__[27];
    real_type t39  = cos(t36);
    result__[ 7   ] = t39 * t38 + 26 * t36;
    real_type t41  = X__[iX_x9];
    real_type t43  = MU__[28];
    real_type t44  = cos(t41);
    result__[ 8   ] = t44 * t43 + 24 * t41;
    real_type t46  = X__[iX_x10];
    real_type t48  = MU__[29];
    real_type t49  = cos(t46);
    result__[ 9   ] = t49 * t48 + 22 * t46;
    real_type t51  = X__[iX_x11];
    real_type t53  = MU__[30];
    real_type t54  = cos(t51);
    result__[ 10  ] = t54 * t53 + 20 * t51;
    real_type t56  = X__[iX_x12];
    real_type t58  = MU__[31];
    real_type t59  = cos(t56);
    result__[ 11  ] = t59 * t58 + 18 * t56;
    real_type t61  = X__[iX_x13];
    real_type t63  = MU__[32];
    real_type t64  = cos(t61);
    result__[ 12  ] = t64 * t63 + 16 * t61;
    real_type t66  = X__[iX_x14];
    real_type t68  = MU__[33];
    real_type t69  = cos(t66);
    result__[ 13  ] = t69 * t68 + 14 * t66;
    real_type t71  = X__[iX_x15];
    real_type t73  = MU__[34];
    real_type t74  = cos(t71);
    result__[ 14  ] = t74 * t73 + 12 * t71;
    real_type t76  = X__[iX_x16];
    real_type t78  = MU__[35];
    real_type t79  = cos(t76);
    result__[ 15  ] = t79 * t78 + 10 * t76;
    real_type t81  = X__[iX_x17];
    real_type t83  = MU__[36];
    real_type t84  = cos(t81);
    result__[ 16  ] = t84 * t83 + 8 * t81;
    real_type t86  = X__[iX_x18];
    real_type t88  = MU__[37];
    real_type t89  = cos(t86);
    result__[ 17  ] = t89 * t88 + 6 * t86;
    real_type t91  = X__[iX_x19];
    real_type t93  = MU__[38];
    real_type t94  = cos(t91);
    result__[ 18  ] = t94 * t93 + 4 * t91;
    real_type t96  = X__[iX_x20];
    real_type t98  = MU__[39];
    real_type t99  = cos(t96);
    result__[ 19  ] = t99 * t98 + 2 * t96;
    result__[ 20  ] = 40 * X__[iX_y1] + MU__[0];
    result__[ 21  ] = 38 * X__[iX_y2] + MU__[1];
    result__[ 22  ] = 36 * X__[iX_y3] + MU__[2];
    result__[ 23  ] = 34 * X__[iX_y4] + MU__[3];
    result__[ 24  ] = 32 * X__[iX_y5] + MU__[4];
    result__[ 25  ] = 30 * X__[iX_y6] + MU__[5];
    result__[ 26  ] = 28 * X__[iX_y7] + MU__[6];
    result__[ 27  ] = 26 * X__[iX_y8] + MU__[7];
    result__[ 28  ] = 24 * X__[iX_y9] + MU__[8];
    result__[ 29  ] = 22 * X__[iX_y10] + MU__[9];
    result__[ 30  ] = 20 * X__[iX_y11] + MU__[10];
    result__[ 31  ] = 18 * X__[iX_y12] + MU__[11];
    result__[ 32  ] = 16 * X__[iX_y13] + MU__[12];
    result__[ 33  ] = 14 * X__[iX_y14] + MU__[13];
    result__[ 34  ] = 12 * X__[iX_y15] + MU__[14];
    result__[ 35  ] = 10 * X__[iX_y16] + MU__[15];
    result__[ 36  ] = 8 * X__[iX_y17] + MU__[16];
    result__[ 37  ] = 6 * X__[iX_y18] + MU__[17];
    result__[ 38  ] = 4 * X__[iX_y19] + MU__[18];
    result__[ 39  ] = 2 * X__[iX_y20] + MU__[19];
    real_type t161 = ModelPars[iM_xy_bound];
    real_type t162 = X__[iX_xx1];
    real_type t164 = ALIAS_xx1Limitation_min_D(-t161 - t162);
    real_type t166 = ALIAS_xx1Limitation_max_D(t162 - t161);
    real_type t167 = MU__[60];
    real_type t168 = cos(t162);
    result__[ 40  ] = -t164 + t166 + 0.2e0 * t168 * t167;
    real_type t171 = X__[iX_xx2];
    real_type t173 = ALIAS_xx2Limitation_min_D(-t161 - t171);
    real_type t175 = ALIAS_xx2Limitation_max_D(t171 - t161);
    real_type t176 = MU__[61];
    real_type t177 = cos(t171);
    result__[ 41  ] = -t173 + t175 + 0.2e0 * t177 * t176;
    real_type t180 = X__[iX_xx3];
    real_type t182 = ALIAS_xx3Limitation_min_D(-t161 - t180);
    real_type t184 = ALIAS_xx3Limitation_max_D(t180 - t161);
    real_type t185 = MU__[62];
    real_type t186 = cos(t180);
    result__[ 42  ] = -t182 + t184 + 0.2e0 * t186 * t185;
    real_type t189 = X__[iX_xx4];
    real_type t191 = ALIAS_xx4Limitation_min_D(-t161 - t189);
    real_type t193 = ALIAS_xx4Limitation_max_D(t189 - t161);
    real_type t194 = MU__[63];
    real_type t195 = cos(t189);
    result__[ 43  ] = -t191 + t193 + 0.2e0 * t195 * t194;
    real_type t198 = X__[iX_xx5];
    real_type t200 = ALIAS_xx5Limitation_min_D(-t161 - t198);
    real_type t202 = ALIAS_xx5Limitation_max_D(t198 - t161);
    real_type t203 = MU__[64];
    real_type t204 = cos(t198);
    result__[ 44  ] = -t200 + t202 + 0.2e0 * t204 * t203;
    real_type t207 = X__[iX_xx6];
    real_type t209 = ALIAS_xx6Limitation_min_D(-t161 - t207);
    real_type t211 = ALIAS_xx6Limitation_max_D(t207 - t161);
    real_type t212 = MU__[65];
    real_type t213 = cos(t207);
    result__[ 45  ] = -t209 + t211 + 0.2e0 * t213 * t212;
    real_type t216 = MU__[66];
    real_type t217 = X__[iX_xx7];
    real_type t218 = cos(t217);
    real_type t222 = ALIAS_xx7Limitation_min_D(-t161 - t217);
    real_type t224 = ALIAS_xx7Limitation_max_D(t217 - t161);
    result__[ 46  ] = 0.2e0 * t218 * t216 - t222 + t224;
    real_type t225 = MU__[67];
    real_type t226 = X__[iX_xx8];
    real_type t227 = cos(t226);
    real_type t231 = ALIAS_xx8Limitation_min_D(-t161 - t226);
    real_type t233 = ALIAS_xx8Limitation_max_D(t226 - t161);
    result__[ 47  ] = 0.2e0 * t227 * t225 - t231 + t233;
    real_type t234 = MU__[68];
    real_type t235 = X__[iX_xx9];
    real_type t236 = cos(t235);
    real_type t240 = ALIAS_xx9Limitation_min_D(-t161 - t235);
    real_type t242 = ALIAS_xx9Limitation_max_D(t235 - t161);
    result__[ 48  ] = 0.2e0 * t236 * t234 - t240 + t242;
    real_type t243 = MU__[69];
    real_type t244 = X__[iX_xx10];
    real_type t245 = cos(t244);
    real_type t249 = ALIAS_xx10Limitation_min_D(-t161 - t244);
    real_type t251 = ALIAS_xx10Limitation_max_D(t244 - t161);
    result__[ 49  ] = 0.2e0 * t245 * t243 - t249 + t251;
    real_type t252 = MU__[70];
    real_type t253 = X__[iX_xx11];
    real_type t254 = cos(t253);
    real_type t258 = ALIAS_xx11Limitation_min_D(-t161 - t253);
    real_type t260 = ALIAS_xx11Limitation_max_D(t253 - t161);
    result__[ 50  ] = 0.2e0 * t254 * t252 - t258 + t260;
    real_type t261 = MU__[71];
    real_type t262 = X__[iX_xx12];
    real_type t263 = cos(t262);
    real_type t267 = ALIAS_xx12Limitation_min_D(-t161 - t262);
    real_type t269 = ALIAS_xx12Limitation_max_D(t262 - t161);
    result__[ 51  ] = 0.2e0 * t263 * t261 - t267 + t269;
    real_type t270 = MU__[72];
    real_type t271 = X__[iX_xx13];
    real_type t272 = cos(t271);
    real_type t276 = ALIAS_xx13Limitation_min_D(-t161 - t271);
    real_type t278 = ALIAS_xx13Limitation_max_D(t271 - t161);
    result__[ 52  ] = 0.2e0 * t272 * t270 - t276 + t278;
    real_type t279 = MU__[73];
    real_type t280 = X__[iX_xx14];
    real_type t281 = cos(t280);
    real_type t285 = ALIAS_xx14Limitation_min_D(-t161 - t280);
    real_type t287 = ALIAS_xx14Limitation_max_D(t280 - t161);
    result__[ 53  ] = 0.2e0 * t281 * t279 - t285 + t287;
    real_type t288 = MU__[74];
    real_type t289 = X__[iX_xx15];
    real_type t290 = cos(t289);
    real_type t294 = ALIAS_xx15Limitation_min_D(-t161 - t289);
    real_type t296 = ALIAS_xx15Limitation_max_D(t289 - t161);
    result__[ 54  ] = 0.2e0 * t290 * t288 - t294 + t296;
    real_type t297 = MU__[75];
    real_type t298 = X__[iX_xx16];
    real_type t299 = cos(t298);
    real_type t303 = ALIAS_xx16Limitation_min_D(-t161 - t298);
    real_type t305 = ALIAS_xx16Limitation_max_D(t298 - t161);
    result__[ 55  ] = 0.2e0 * t299 * t297 - t303 + t305;
    real_type t306 = MU__[76];
    real_type t307 = X__[iX_xx17];
    real_type t308 = cos(t307);
    real_type t312 = ALIAS_xx17Limitation_min_D(-t161 - t307);
    real_type t314 = ALIAS_xx17Limitation_max_D(t307 - t161);
    result__[ 56  ] = 0.2e0 * t308 * t306 - t312 + t314;
    real_type t315 = X__[iX_xx18];
    real_type t317 = ALIAS_xx18Limitation_min_D(-t161 - t315);
    real_type t319 = ALIAS_xx18Limitation_max_D(t315 - t161);
    real_type t320 = MU__[77];
    real_type t321 = cos(t315);
    result__[ 57  ] = -t317 + t319 + 0.2e0 * t321 * t320;
    real_type t324 = X__[iX_xx19];
    real_type t326 = ALIAS_xx19Limitation_min_D(-t161 - t324);
    real_type t328 = ALIAS_xx19Limitation_max_D(t324 - t161);
    real_type t329 = MU__[78];
    real_type t330 = cos(t324);
    result__[ 58  ] = -t326 + t328 + 0.2e0 * t330 * t329;
    real_type t333 = X__[iX_xx20];
    real_type t335 = ALIAS_xx20Limitation_min_D(-t161 - t333);
    real_type t337 = ALIAS_xx20Limitation_max_D(t333 - t161);
    real_type t338 = MU__[79];
    real_type t339 = cos(t333);
    result__[ 59  ] = -t335 + t337 + 0.2e0 * t339 * t338;
    real_type t342 = X__[iX_yy1];
    real_type t344 = ALIAS_yy1Limitation_min_D(-t161 - t342);
    real_type t346 = ALIAS_yy1Limitation_max_D(t342 - t161);
    result__[ 60  ] = -t344 + t346 + 0.12e1 * MU__[40];
    real_type t349 = X__[iX_yy2];
    real_type t351 = ALIAS_yy2Limitation_min_D(-t161 - t349);
    real_type t353 = ALIAS_yy2Limitation_max_D(t349 - t161);
    result__[ 61  ] = -t351 + t353 + 0.12e1 * MU__[41];
    real_type t356 = X__[iX_yy3];
    real_type t358 = ALIAS_yy3Limitation_max_D(t356 - t161);
    real_type t360 = ALIAS_yy3Limitation_min_D(-t161 - t356);
    result__[ 62  ] = t358 - t360 + 0.12e1 * MU__[42];
    real_type t363 = X__[iX_yy4];
    real_type t365 = ALIAS_yy4Limitation_min_D(-t161 - t363);
    real_type t367 = ALIAS_yy4Limitation_max_D(t363 - t161);
    result__[ 63  ] = -t365 + t367 + 0.12e1 * MU__[43];
    real_type t370 = X__[iX_yy5];
    real_type t372 = ALIAS_yy5Limitation_min_D(-t161 - t370);
    real_type t374 = ALIAS_yy5Limitation_max_D(t370 - t161);
    result__[ 64  ] = -t372 + t374 + 0.12e1 * MU__[44];
    real_type t377 = X__[iX_yy6];
    real_type t379 = ALIAS_yy6Limitation_min_D(-t161 - t377);
    real_type t381 = ALIAS_yy6Limitation_max_D(t377 - t161);
    result__[ 65  ] = -t379 + t381 + 0.12e1 * MU__[45];
    real_type t384 = X__[iX_yy7];
    real_type t386 = ALIAS_yy7Limitation_min_D(-t161 - t384);
    real_type t388 = ALIAS_yy7Limitation_max_D(t384 - t161);
    result__[ 66  ] = -t386 + t388 + 0.12e1 * MU__[46];
    real_type t391 = X__[iX_yy8];
    real_type t393 = ALIAS_yy8Limitation_min_D(-t161 - t391);
    real_type t395 = ALIAS_yy8Limitation_max_D(t391 - t161);
    result__[ 67  ] = -t393 + t395 + 0.12e1 * MU__[47];
    real_type t398 = X__[iX_yy9];
    real_type t400 = ALIAS_yy9Limitation_min_D(-t161 - t398);
    real_type t402 = ALIAS_yy9Limitation_max_D(t398 - t161);
    result__[ 68  ] = -t400 + t402 + 0.12e1 * MU__[48];
    real_type t405 = X__[iX_yy10];
    real_type t407 = ALIAS_yy10Limitation_min_D(-t161 - t405);
    real_type t409 = ALIAS_yy10Limitation_max_D(t405 - t161);
    result__[ 69  ] = -t407 + t409 + 0.12e1 * MU__[49];
    real_type t412 = X__[iX_yy11];
    real_type t414 = ALIAS_yy11Limitation_min_D(-t161 - t412);
    real_type t416 = ALIAS_yy11Limitation_max_D(t412 - t161);
    result__[ 70  ] = -t414 + t416 + 0.12e1 * MU__[50];
    real_type t419 = X__[iX_yy12];
    real_type t421 = ALIAS_yy12Limitation_min_D(-t161 - t419);
    real_type t423 = ALIAS_yy12Limitation_max_D(t419 - t161);
    result__[ 71  ] = -t421 + t423 + 0.12e1 * MU__[51];
    real_type t426 = X__[iX_yy13];
    real_type t428 = ALIAS_yy13Limitation_min_D(-t161 - t426);
    real_type t430 = ALIAS_yy13Limitation_max_D(t426 - t161);
    result__[ 72  ] = -t428 + t430 + 0.12e1 * MU__[52];
    real_type t433 = X__[iX_yy14];
    real_type t435 = ALIAS_yy14Limitation_min_D(-t161 - t433);
    real_type t437 = ALIAS_yy14Limitation_max_D(t433 - t161);
    result__[ 73  ] = -t435 + t437 + 0.12e1 * MU__[53];
    real_type t440 = X__[iX_yy15];
    real_type t442 = ALIAS_yy15Limitation_min_D(-t161 - t440);
    real_type t444 = ALIAS_yy15Limitation_max_D(t440 - t161);
    result__[ 74  ] = -t442 + t444 + 0.12e1 * MU__[54];
    real_type t447 = X__[iX_yy16];
    real_type t449 = ALIAS_yy16Limitation_min_D(-t161 - t447);
    real_type t451 = ALIAS_yy16Limitation_max_D(t447 - t161);
    result__[ 75  ] = -t449 + t451 + 0.12e1 * MU__[55];
    real_type t454 = X__[iX_yy17];
    real_type t456 = ALIAS_yy17Limitation_min_D(-t161 - t454);
    real_type t458 = ALIAS_yy17Limitation_max_D(t454 - t161);
    result__[ 76  ] = -t456 + t458 + 0.12e1 * MU__[56];
    real_type t461 = X__[iX_yy18];
    real_type t463 = ALIAS_yy18Limitation_min_D(-t161 - t461);
    real_type t465 = ALIAS_yy18Limitation_max_D(t461 - t161);
    result__[ 77  ] = -t463 + t465 + 0.12e1 * MU__[57];
    real_type t468 = X__[iX_yy19];
    real_type t470 = ALIAS_yy19Limitation_min_D(-t161 - t468);
    real_type t472 = ALIAS_yy19Limitation_max_D(t468 - t161);
    result__[ 78  ] = -t470 + t472 + 0.12e1 * MU__[58];
    real_type t475 = X__[iX_yy20];
    real_type t477 = ALIAS_yy20Limitation_min_D(-t161 - t475);
    real_type t479 = ALIAS_yy20Limitation_max_D(t475 - t161);
    result__[ 79  ] = -t477 + t479 + 0.12e1 * MU__[59];
    real_type t482 = P__[iP_u1];
    real_type t484 = ALIAS_u1Limitation_min_D(-10 - t482);
    real_type t486 = ALIAS_u1Limitation_max_D(t482 - 10);
    result__[ 80  ] = -t484 + t486 + t3 + t167;
    real_type t487 = P__[iP_u2];
    real_type t489 = ALIAS_u2Limitation_min_D(-10 - t487);
    real_type t491 = ALIAS_u2Limitation_max_D(t487 - 10);
    result__[ 81  ] = -t489 + t491 + t8 + t176;
    real_type t492 = P__[iP_u3];
    real_type t494 = ALIAS_u3Limitation_min_D(-10 - t492);
    real_type t496 = ALIAS_u3Limitation_max_D(t492 - 10);
    result__[ 82  ] = -t494 + t496 + t13 + t185;
    real_type t497 = P__[iP_u4];
    real_type t499 = ALIAS_u4Limitation_min_D(-10 - t497);
    real_type t501 = ALIAS_u4Limitation_max_D(t497 - 10);
    result__[ 83  ] = -t499 + t501 + t18 + t194;
    real_type t502 = P__[iP_u5];
    real_type t504 = ALIAS_u5Limitation_max_D(t502 - 10);
    real_type t506 = ALIAS_u5Limitation_min_D(-10 - t502);
    result__[ 84  ] = t504 - t506 + t23 + t203;
    real_type t507 = P__[iP_u6];
    real_type t509 = ALIAS_u6Limitation_min_D(-10 - t507);
    real_type t511 = ALIAS_u6Limitation_max_D(t507 - 10);
    result__[ 85  ] = -t509 + t511 + t28 + t212;
    real_type t512 = P__[iP_u7];
    real_type t514 = ALIAS_u7Limitation_min_D(-10 - t512);
    real_type t516 = ALIAS_u7Limitation_max_D(t512 - 10);
    result__[ 86  ] = -t514 + t516 + t33 + t216;
    real_type t517 = P__[iP_u8];
    real_type t519 = ALIAS_u8Limitation_min_D(-10 - t517);
    real_type t521 = ALIAS_u8Limitation_max_D(t517 - 10);
    result__[ 87  ] = -t519 + t521 + t38 + t225;
    real_type t522 = P__[iP_u9];
    real_type t524 = ALIAS_u9Limitation_min_D(-10 - t522);
    real_type t526 = ALIAS_u9Limitation_max_D(t522 - 10);
    result__[ 88  ] = -t524 + t526 + t43 + t234;
    real_type t527 = P__[iP_u10];
    real_type t529 = ALIAS_u10Limitation_min_D(-10 - t527);
    real_type t531 = ALIAS_u10Limitation_max_D(t527 - 10);
    result__[ 89  ] = -t529 + t531 + t48 + t243;
    real_type t532 = P__[iP_u11];
    real_type t534 = ALIAS_u11Limitation_min_D(-10 - t532);
    real_type t536 = ALIAS_u11Limitation_max_D(t532 - 10);
    result__[ 90  ] = -t534 + t536 + t53 + t252;
    real_type t537 = P__[iP_u12];
    real_type t539 = ALIAS_u12Limitation_min_D(-10 - t537);
    real_type t541 = ALIAS_u12Limitation_max_D(t537 - 10);
    result__[ 91  ] = -t539 + t541 + t58 + t261;
    real_type t542 = P__[iP_u13];
    real_type t544 = ALIAS_u13Limitation_max_D(t542 - 10);
    real_type t546 = ALIAS_u13Limitation_min_D(-10 - t542);
    result__[ 92  ] = t544 - t546 + t63 + t270;
    real_type t547 = P__[iP_u14];
    real_type t549 = ALIAS_u14Limitation_min_D(-10 - t547);
    real_type t551 = ALIAS_u14Limitation_max_D(t547 - 10);
    result__[ 93  ] = -t549 + t551 + t68 + t279;
    real_type t552 = P__[iP_u15];
    real_type t554 = ALIAS_u15Limitation_min_D(-10 - t552);
    real_type t556 = ALIAS_u15Limitation_max_D(t552 - 10);
    result__[ 94  ] = -t554 + t556 + t73 + t288;
    real_type t557 = P__[iP_u16];
    real_type t559 = ALIAS_u16Limitation_min_D(-10 - t557);
    real_type t561 = ALIAS_u16Limitation_max_D(t557 - 10);
    result__[ 95  ] = -t559 + t561 + t78 + t297;
    real_type t562 = P__[iP_u17];
    real_type t564 = ALIAS_u17Limitation_min_D(-10 - t562);
    real_type t566 = ALIAS_u17Limitation_max_D(t562 - 10);
    result__[ 96  ] = -t564 + t566 + t83 + t306;
    real_type t567 = P__[iP_u18];
    real_type t569 = ALIAS_u18Limitation_min_D(-10 - t567);
    real_type t571 = ALIAS_u18Limitation_max_D(t567 - 10);
    result__[ 97  ] = -t569 + t571 + t88 + t320;
    real_type t572 = P__[iP_u19];
    real_type t574 = ALIAS_u19Limitation_min_D(-10 - t572);
    real_type t576 = ALIAS_u19Limitation_max_D(t572 - 10);
    result__[ 98  ] = -t574 + t576 + t93 + t329;
    real_type t577 = P__[iP_u20];
    real_type t579 = ALIAS_u20Limitation_min_D(-10 - t577);
    real_type t581 = ALIAS_u20Limitation_max_D(t577 - 10);
    result__[ 99  ] = -t579 + t581 + t98 + t338;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 100, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_ContinuousMP::DHxpDxpuv_numRows() const { return 100; }
  integer ICLOCS_ContinuousMP::DHxpDxpuv_numCols() const { return 180; }
  integer ICLOCS_ContinuousMP::DHxpDxpuv_nnz()     const { return 100; }

  void
  ICLOCS_ContinuousMP::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[80] = 80  ; jIndex[80] = 80  ;
    iIndex[81] = 81  ; jIndex[81] = 81  ;
    iIndex[82] = 82  ; jIndex[82] = 82  ;
    iIndex[83] = 83  ; jIndex[83] = 83  ;
    iIndex[84] = 84  ; jIndex[84] = 84  ;
    iIndex[85] = 85  ; jIndex[85] = 85  ;
    iIndex[86] = 86  ; jIndex[86] = 86  ;
    iIndex[87] = 87  ; jIndex[87] = 87  ;
    iIndex[88] = 88  ; jIndex[88] = 88  ;
    iIndex[89] = 89  ; jIndex[89] = 89  ;
    iIndex[90] = 90  ; jIndex[90] = 90  ;
    iIndex[91] = 91  ; jIndex[91] = 91  ;
    iIndex[92] = 92  ; jIndex[92] = 92  ;
    iIndex[93] = 93  ; jIndex[93] = 93  ;
    iIndex[94] = 94  ; jIndex[94] = 94  ;
    iIndex[95] = 95  ; jIndex[95] = 95  ;
    iIndex[96] = 96  ; jIndex[96] = 96  ;
    iIndex[97] = 97  ; jIndex[97] = 97  ;
    iIndex[98] = 98  ; jIndex[98] = 98  ;
    iIndex[99] = 99  ; jIndex[99] = 99  ;
  }


  void
  ICLOCS_ContinuousMP::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = sin(X__[iX_x1]);
    result__[ 0   ] = -t3 * MU__[20] + 40;
    real_type t7   = sin(X__[iX_x2]);
    result__[ 1   ] = -t7 * MU__[21] + 38;
    real_type t11  = sin(X__[iX_x3]);
    result__[ 2   ] = -t11 * MU__[22] + 36;
    real_type t15  = sin(X__[iX_x4]);
    result__[ 3   ] = -t15 * MU__[23] + 34;
    real_type t19  = sin(X__[iX_x5]);
    result__[ 4   ] = -t19 * MU__[24] + 32;
    real_type t23  = sin(X__[iX_x6]);
    result__[ 5   ] = -t23 * MU__[25] + 30;
    real_type t27  = sin(X__[iX_x7]);
    result__[ 6   ] = -t27 * MU__[26] + 28;
    real_type t31  = sin(X__[iX_x8]);
    result__[ 7   ] = -t31 * MU__[27] + 26;
    real_type t35  = sin(X__[iX_x9]);
    result__[ 8   ] = -t35 * MU__[28] + 24;
    real_type t39  = sin(X__[iX_x10]);
    result__[ 9   ] = -t39 * MU__[29] + 22;
    real_type t43  = sin(X__[iX_x11]);
    result__[ 10  ] = -t43 * MU__[30] + 20;
    real_type t47  = sin(X__[iX_x12]);
    result__[ 11  ] = -t47 * MU__[31] + 18;
    real_type t51  = sin(X__[iX_x13]);
    result__[ 12  ] = -t51 * MU__[32] + 16;
    real_type t55  = sin(X__[iX_x14]);
    result__[ 13  ] = -t55 * MU__[33] + 14;
    real_type t59  = sin(X__[iX_x15]);
    result__[ 14  ] = -t59 * MU__[34] + 12;
    real_type t63  = sin(X__[iX_x16]);
    result__[ 15  ] = -t63 * MU__[35] + 10;
    real_type t67  = sin(X__[iX_x17]);
    result__[ 16  ] = -t67 * MU__[36] + 8;
    real_type t71  = sin(X__[iX_x18]);
    result__[ 17  ] = -t71 * MU__[37] + 6;
    real_type t75  = sin(X__[iX_x19]);
    result__[ 18  ] = -t75 * MU__[38] + 4;
    real_type t79  = sin(X__[iX_x20]);
    result__[ 19  ] = -t79 * MU__[39] + 2;
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
    real_type t81  = ModelPars[iM_xy_bound];
    real_type t82  = X__[iX_xx1];
    real_type t84  = ALIAS_xx1Limitation_min_DD(-t81 - t82);
    real_type t86  = ALIAS_xx1Limitation_max_DD(t82 - t81);
    real_type t88  = sin(t82);
    result__[ 40  ] = t84 + t86 - 0.2e0 * t88 * MU__[60];
    real_type t91  = X__[iX_xx2];
    real_type t93  = ALIAS_xx2Limitation_min_DD(-t81 - t91);
    real_type t95  = ALIAS_xx2Limitation_max_DD(t91 - t81);
    real_type t97  = sin(t91);
    result__[ 41  ] = t93 + t95 - 0.2e0 * t97 * MU__[61];
    real_type t100 = X__[iX_xx3];
    real_type t102 = ALIAS_xx3Limitation_min_DD(-t81 - t100);
    real_type t104 = ALIAS_xx3Limitation_max_DD(t100 - t81);
    real_type t106 = sin(t100);
    result__[ 42  ] = t102 + t104 - 0.2e0 * t106 * MU__[62];
    real_type t109 = X__[iX_xx4];
    real_type t111 = ALIAS_xx4Limitation_min_DD(-t81 - t109);
    real_type t113 = ALIAS_xx4Limitation_max_DD(t109 - t81);
    real_type t115 = sin(t109);
    result__[ 43  ] = t111 + t113 - 0.2e0 * t115 * MU__[63];
    real_type t118 = X__[iX_xx5];
    real_type t120 = ALIAS_xx5Limitation_min_DD(-t81 - t118);
    real_type t122 = ALIAS_xx5Limitation_max_DD(t118 - t81);
    real_type t124 = sin(t118);
    result__[ 44  ] = t120 + t122 - 0.2e0 * t124 * MU__[64];
    real_type t127 = X__[iX_xx6];
    real_type t129 = ALIAS_xx6Limitation_min_DD(-t81 - t127);
    real_type t131 = ALIAS_xx6Limitation_max_DD(t127 - t81);
    real_type t133 = sin(t127);
    result__[ 45  ] = t129 + t131 - 0.2e0 * t133 * MU__[65];
    real_type t137 = X__[iX_xx7];
    real_type t138 = sin(t137);
    real_type t142 = ALIAS_xx7Limitation_min_DD(-t81 - t137);
    real_type t144 = ALIAS_xx7Limitation_max_DD(t137 - t81);
    result__[ 46  ] = -0.2e0 * t138 * MU__[66] + t142 + t144;
    real_type t146 = X__[iX_xx8];
    real_type t147 = sin(t146);
    real_type t151 = ALIAS_xx8Limitation_min_DD(-t81 - t146);
    real_type t153 = ALIAS_xx8Limitation_max_DD(t146 - t81);
    result__[ 47  ] = -0.2e0 * t147 * MU__[67] + t151 + t153;
    real_type t155 = X__[iX_xx9];
    real_type t156 = sin(t155);
    real_type t160 = ALIAS_xx9Limitation_min_DD(-t81 - t155);
    real_type t162 = ALIAS_xx9Limitation_max_DD(t155 - t81);
    result__[ 48  ] = -0.2e0 * t156 * MU__[68] + t160 + t162;
    real_type t164 = X__[iX_xx10];
    real_type t165 = sin(t164);
    real_type t169 = ALIAS_xx10Limitation_min_DD(-t81 - t164);
    real_type t171 = ALIAS_xx10Limitation_max_DD(t164 - t81);
    result__[ 49  ] = -0.2e0 * t165 * MU__[69] + t169 + t171;
    real_type t173 = X__[iX_xx11];
    real_type t174 = sin(t173);
    real_type t178 = ALIAS_xx11Limitation_min_DD(-t81 - t173);
    real_type t180 = ALIAS_xx11Limitation_max_DD(t173 - t81);
    result__[ 50  ] = -0.2e0 * t174 * MU__[70] + t178 + t180;
    real_type t182 = X__[iX_xx12];
    real_type t183 = sin(t182);
    real_type t187 = ALIAS_xx12Limitation_min_DD(-t81 - t182);
    real_type t189 = ALIAS_xx12Limitation_max_DD(t182 - t81);
    result__[ 51  ] = -0.2e0 * t183 * MU__[71] + t187 + t189;
    real_type t191 = X__[iX_xx13];
    real_type t192 = sin(t191);
    real_type t196 = ALIAS_xx13Limitation_min_DD(-t81 - t191);
    real_type t198 = ALIAS_xx13Limitation_max_DD(t191 - t81);
    result__[ 52  ] = -0.2e0 * t192 * MU__[72] + t196 + t198;
    real_type t200 = X__[iX_xx14];
    real_type t201 = sin(t200);
    real_type t205 = ALIAS_xx14Limitation_min_DD(-t81 - t200);
    real_type t207 = ALIAS_xx14Limitation_max_DD(t200 - t81);
    result__[ 53  ] = -0.2e0 * t201 * MU__[73] + t205 + t207;
    real_type t209 = X__[iX_xx15];
    real_type t210 = sin(t209);
    real_type t214 = ALIAS_xx15Limitation_min_DD(-t81 - t209);
    real_type t216 = ALIAS_xx15Limitation_max_DD(t209 - t81);
    result__[ 54  ] = -0.2e0 * t210 * MU__[74] + t214 + t216;
    real_type t218 = X__[iX_xx16];
    real_type t219 = sin(t218);
    real_type t223 = ALIAS_xx16Limitation_min_DD(-t81 - t218);
    real_type t225 = ALIAS_xx16Limitation_max_DD(t218 - t81);
    result__[ 55  ] = -0.2e0 * t219 * MU__[75] + t223 + t225;
    real_type t227 = X__[iX_xx17];
    real_type t228 = sin(t227);
    real_type t232 = ALIAS_xx17Limitation_min_DD(-t81 - t227);
    real_type t234 = ALIAS_xx17Limitation_max_DD(t227 - t81);
    result__[ 56  ] = -0.2e0 * t228 * MU__[76] + t232 + t234;
    real_type t235 = X__[iX_xx18];
    real_type t237 = ALIAS_xx18Limitation_min_DD(-t81 - t235);
    real_type t239 = ALIAS_xx18Limitation_max_DD(t235 - t81);
    real_type t241 = sin(t235);
    result__[ 57  ] = t237 + t239 - 0.2e0 * t241 * MU__[77];
    real_type t244 = X__[iX_xx19];
    real_type t246 = ALIAS_xx19Limitation_min_DD(-t81 - t244);
    real_type t248 = ALIAS_xx19Limitation_max_DD(t244 - t81);
    real_type t250 = sin(t244);
    result__[ 58  ] = t246 + t248 - 0.2e0 * t250 * MU__[78];
    real_type t253 = X__[iX_xx20];
    real_type t255 = ALIAS_xx20Limitation_min_DD(-t81 - t253);
    real_type t257 = ALIAS_xx20Limitation_max_DD(t253 - t81);
    real_type t259 = sin(t253);
    result__[ 59  ] = t255 + t257 - 0.2e0 * t259 * MU__[79];
    real_type t262 = X__[iX_yy1];
    real_type t264 = ALIAS_yy1Limitation_min_DD(-t81 - t262);
    real_type t266 = ALIAS_yy1Limitation_max_DD(t262 - t81);
    result__[ 60  ] = t264 + t266;
    real_type t267 = X__[iX_yy2];
    real_type t269 = ALIAS_yy2Limitation_min_DD(-t81 - t267);
    real_type t271 = ALIAS_yy2Limitation_max_DD(t267 - t81);
    result__[ 61  ] = t269 + t271;
    real_type t272 = X__[iX_yy3];
    real_type t274 = ALIAS_yy3Limitation_max_DD(t272 - t81);
    real_type t276 = ALIAS_yy3Limitation_min_DD(-t81 - t272);
    result__[ 62  ] = t274 + t276;
    real_type t277 = X__[iX_yy4];
    real_type t279 = ALIAS_yy4Limitation_min_DD(-t81 - t277);
    real_type t281 = ALIAS_yy4Limitation_max_DD(t277 - t81);
    result__[ 63  ] = t279 + t281;
    real_type t282 = X__[iX_yy5];
    real_type t284 = ALIAS_yy5Limitation_min_DD(-t81 - t282);
    real_type t286 = ALIAS_yy5Limitation_max_DD(t282 - t81);
    result__[ 64  ] = t284 + t286;
    real_type t287 = X__[iX_yy6];
    real_type t289 = ALIAS_yy6Limitation_min_DD(-t81 - t287);
    real_type t291 = ALIAS_yy6Limitation_max_DD(t287 - t81);
    result__[ 65  ] = t289 + t291;
    real_type t292 = X__[iX_yy7];
    real_type t294 = ALIAS_yy7Limitation_min_DD(-t81 - t292);
    real_type t296 = ALIAS_yy7Limitation_max_DD(t292 - t81);
    result__[ 66  ] = t294 + t296;
    real_type t297 = X__[iX_yy8];
    real_type t299 = ALIAS_yy8Limitation_min_DD(-t81 - t297);
    real_type t301 = ALIAS_yy8Limitation_max_DD(t297 - t81);
    result__[ 67  ] = t299 + t301;
    real_type t302 = X__[iX_yy9];
    real_type t304 = ALIAS_yy9Limitation_min_DD(-t81 - t302);
    real_type t306 = ALIAS_yy9Limitation_max_DD(t302 - t81);
    result__[ 68  ] = t304 + t306;
    real_type t307 = X__[iX_yy10];
    real_type t309 = ALIAS_yy10Limitation_min_DD(-t81 - t307);
    real_type t311 = ALIAS_yy10Limitation_max_DD(t307 - t81);
    result__[ 69  ] = t309 + t311;
    real_type t312 = X__[iX_yy11];
    real_type t314 = ALIAS_yy11Limitation_min_DD(-t81 - t312);
    real_type t316 = ALIAS_yy11Limitation_max_DD(t312 - t81);
    result__[ 70  ] = t314 + t316;
    real_type t317 = X__[iX_yy12];
    real_type t319 = ALIAS_yy12Limitation_min_DD(-t81 - t317);
    real_type t321 = ALIAS_yy12Limitation_max_DD(t317 - t81);
    result__[ 71  ] = t319 + t321;
    real_type t322 = X__[iX_yy13];
    real_type t324 = ALIAS_yy13Limitation_min_DD(-t81 - t322);
    real_type t326 = ALIAS_yy13Limitation_max_DD(t322 - t81);
    result__[ 72  ] = t324 + t326;
    real_type t327 = X__[iX_yy14];
    real_type t329 = ALIAS_yy14Limitation_min_DD(-t81 - t327);
    real_type t331 = ALIAS_yy14Limitation_max_DD(t327 - t81);
    result__[ 73  ] = t329 + t331;
    real_type t332 = X__[iX_yy15];
    real_type t334 = ALIAS_yy15Limitation_min_DD(-t81 - t332);
    real_type t336 = ALIAS_yy15Limitation_max_DD(t332 - t81);
    result__[ 74  ] = t334 + t336;
    real_type t337 = X__[iX_yy16];
    real_type t339 = ALIAS_yy16Limitation_min_DD(-t81 - t337);
    real_type t341 = ALIAS_yy16Limitation_max_DD(t337 - t81);
    result__[ 75  ] = t339 + t341;
    real_type t342 = X__[iX_yy17];
    real_type t344 = ALIAS_yy17Limitation_min_DD(-t81 - t342);
    real_type t346 = ALIAS_yy17Limitation_max_DD(t342 - t81);
    result__[ 76  ] = t344 + t346;
    real_type t347 = X__[iX_yy18];
    real_type t349 = ALIAS_yy18Limitation_min_DD(-t81 - t347);
    real_type t351 = ALIAS_yy18Limitation_max_DD(t347 - t81);
    result__[ 77  ] = t349 + t351;
    real_type t352 = X__[iX_yy19];
    real_type t354 = ALIAS_yy19Limitation_min_DD(-t81 - t352);
    real_type t356 = ALIAS_yy19Limitation_max_DD(t352 - t81);
    result__[ 78  ] = t354 + t356;
    real_type t357 = X__[iX_yy20];
    real_type t359 = ALIAS_yy20Limitation_min_DD(-t81 - t357);
    real_type t361 = ALIAS_yy20Limitation_max_DD(t357 - t81);
    result__[ 79  ] = t359 + t361;
    real_type t362 = P__[iP_u1];
    real_type t364 = ALIAS_u1Limitation_min_DD(-10 - t362);
    real_type t366 = ALIAS_u1Limitation_max_DD(t362 - 10);
    result__[ 80  ] = t364 + t366;
    real_type t367 = P__[iP_u2];
    real_type t369 = ALIAS_u2Limitation_min_DD(-10 - t367);
    real_type t371 = ALIAS_u2Limitation_max_DD(t367 - 10);
    result__[ 81  ] = t369 + t371;
    real_type t372 = P__[iP_u3];
    real_type t374 = ALIAS_u3Limitation_min_DD(-10 - t372);
    real_type t376 = ALIAS_u3Limitation_max_DD(t372 - 10);
    result__[ 82  ] = t374 + t376;
    real_type t377 = P__[iP_u4];
    real_type t379 = ALIAS_u4Limitation_min_DD(-10 - t377);
    real_type t381 = ALIAS_u4Limitation_max_DD(t377 - 10);
    result__[ 83  ] = t379 + t381;
    real_type t382 = P__[iP_u5];
    real_type t384 = ALIAS_u5Limitation_max_DD(t382 - 10);
    real_type t386 = ALIAS_u5Limitation_min_DD(-10 - t382);
    result__[ 84  ] = t384 + t386;
    real_type t387 = P__[iP_u6];
    real_type t389 = ALIAS_u6Limitation_min_DD(-10 - t387);
    real_type t391 = ALIAS_u6Limitation_max_DD(t387 - 10);
    result__[ 85  ] = t389 + t391;
    real_type t392 = P__[iP_u7];
    real_type t394 = ALIAS_u7Limitation_min_DD(-10 - t392);
    real_type t396 = ALIAS_u7Limitation_max_DD(t392 - 10);
    result__[ 86  ] = t394 + t396;
    real_type t397 = P__[iP_u8];
    real_type t399 = ALIAS_u8Limitation_min_DD(-10 - t397);
    real_type t401 = ALIAS_u8Limitation_max_DD(t397 - 10);
    result__[ 87  ] = t399 + t401;
    real_type t402 = P__[iP_u9];
    real_type t404 = ALIAS_u9Limitation_min_DD(-10 - t402);
    real_type t406 = ALIAS_u9Limitation_max_DD(t402 - 10);
    result__[ 88  ] = t404 + t406;
    real_type t407 = P__[iP_u10];
    real_type t409 = ALIAS_u10Limitation_min_DD(-10 - t407);
    real_type t411 = ALIAS_u10Limitation_max_DD(t407 - 10);
    result__[ 89  ] = t409 + t411;
    real_type t412 = P__[iP_u11];
    real_type t414 = ALIAS_u11Limitation_min_DD(-10 - t412);
    real_type t416 = ALIAS_u11Limitation_max_DD(t412 - 10);
    result__[ 90  ] = t414 + t416;
    real_type t417 = P__[iP_u12];
    real_type t419 = ALIAS_u12Limitation_min_DD(-10 - t417);
    real_type t421 = ALIAS_u12Limitation_max_DD(t417 - 10);
    result__[ 91  ] = t419 + t421;
    real_type t422 = P__[iP_u13];
    real_type t424 = ALIAS_u13Limitation_max_DD(t422 - 10);
    real_type t426 = ALIAS_u13Limitation_min_DD(-10 - t422);
    result__[ 92  ] = t424 + t426;
    real_type t427 = P__[iP_u14];
    real_type t429 = ALIAS_u14Limitation_min_DD(-10 - t427);
    real_type t431 = ALIAS_u14Limitation_max_DD(t427 - 10);
    result__[ 93  ] = t429 + t431;
    real_type t432 = P__[iP_u15];
    real_type t434 = ALIAS_u15Limitation_min_DD(-10 - t432);
    real_type t436 = ALIAS_u15Limitation_max_DD(t432 - 10);
    result__[ 94  ] = t434 + t436;
    real_type t437 = P__[iP_u16];
    real_type t439 = ALIAS_u16Limitation_min_DD(-10 - t437);
    real_type t441 = ALIAS_u16Limitation_max_DD(t437 - 10);
    result__[ 95  ] = t439 + t441;
    real_type t442 = P__[iP_u17];
    real_type t444 = ALIAS_u17Limitation_min_DD(-10 - t442);
    real_type t446 = ALIAS_u17Limitation_max_DD(t442 - 10);
    result__[ 96  ] = t444 + t446;
    real_type t447 = P__[iP_u18];
    real_type t449 = ALIAS_u18Limitation_min_DD(-10 - t447);
    real_type t451 = ALIAS_u18Limitation_max_DD(t447 - 10);
    result__[ 97  ] = t449 + t451;
    real_type t452 = P__[iP_u19];
    real_type t454 = ALIAS_u19Limitation_min_DD(-10 - t452);
    real_type t456 = ALIAS_u19Limitation_max_DD(t452 - 10);
    result__[ 98  ] = t454 + t456;
    real_type t457 = P__[iP_u20];
    real_type t459 = ALIAS_u20Limitation_min_DD(-10 - t457);
    real_type t461 = ALIAS_u20Limitation_max_DD(t457 - 10);
    result__[ 99  ] = t459 + t461;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 100, i_segment );
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
