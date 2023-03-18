/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_UserFunctions.cc                   |
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
#include <cmath>

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
  using std::acos;
  using std::acosh;
  using std::asin;
  using std::asinh;
  using std::atan;
  using std::atan2;
  using std::atanh;
  using std::cbrt;
  using std::ceil;
  using std::abs;
  using std::cos;
  using std::cosh;
  using std::exp;
  using std::exp2;
  using std::expm1;
  using std::floor;
  using std::log;
  using std::log10;
  using std::log1p;
  using std::log2;
  using std::logb;
  using std::pow;
  using std::hypot;
  using std::floor;
  using std::round;
  using std::sin;
  using std::sinh;
  using std::sqrt;
  using std::tan;
  using std::tanh;
  using std::trunc;
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  ICLOCS_ContinuousMP::u1Limitation( real_type xo___V ) const {
    real_type t2   = u1Limitation_min(-10 - xo___V);
    real_type t4   = u1Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u1Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u1Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u1Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u1Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u1Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u1Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u1Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u1Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u1Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u2Limitation( real_type xo___V ) const {
    real_type t2   = u2Limitation_min(-10 - xo___V);
    real_type t4   = u2Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u2Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u2Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u2Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u2Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u2Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u2Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u2Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u2Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u2Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u3Limitation( real_type xo___V ) const {
    real_type t2   = u3Limitation_min(-10 - xo___V);
    real_type t4   = u3Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u3Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u3Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u3Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u3Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u3Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u3Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u3Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u3Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u3Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u4Limitation( real_type xo___V ) const {
    real_type t2   = u4Limitation_min(-10 - xo___V);
    real_type t4   = u4Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u4Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u4Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u4Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u4Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u4Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u4Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u4Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u4Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u4Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u5Limitation( real_type xo___V ) const {
    real_type t2   = u5Limitation_min(-10 - xo___V);
    real_type t4   = u5Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u5Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u5Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u5Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u5Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u5Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u5Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u5Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u5Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u5Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u6Limitation( real_type xo___V ) const {
    real_type t2   = u6Limitation_min(-10 - xo___V);
    real_type t4   = u6Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u6Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u6Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u6Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u6Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u6Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u6Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u6Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u6Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u6Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u7Limitation( real_type xo___V ) const {
    real_type t2   = u7Limitation_min(-10 - xo___V);
    real_type t4   = u7Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u7Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u7Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u7Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u7Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u7Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u7Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u7Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u7Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u7Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u8Limitation( real_type xo___V ) const {
    real_type t2   = u8Limitation_min(-10 - xo___V);
    real_type t4   = u8Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u8Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u8Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u8Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u8Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u8Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u8Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u8Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u8Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u8Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u9Limitation( real_type xo___V ) const {
    real_type t2   = u9Limitation_min(-10 - xo___V);
    real_type t4   = u9Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u9Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u9Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u9Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u9Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u9Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u9Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u9Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u9Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u9Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u10Limitation( real_type xo___V ) const {
    real_type t2   = u10Limitation_min(-10 - xo___V);
    real_type t4   = u10Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u10Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u10Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u10Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u10Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u10Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u10Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u10Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u10Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u10Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u11Limitation( real_type xo___V ) const {
    real_type t2   = u11Limitation_min(-10 - xo___V);
    real_type t4   = u11Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u11Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u11Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u11Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u11Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u11Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u11Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u11Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u11Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u11Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u12Limitation( real_type xo___V ) const {
    real_type t2   = u12Limitation_min(-10 - xo___V);
    real_type t4   = u12Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u12Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u12Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u12Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u12Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u12Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u12Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u12Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u12Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u12Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u13Limitation( real_type xo___V ) const {
    real_type t2   = u13Limitation_min(-10 - xo___V);
    real_type t4   = u13Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u13Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u13Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u13Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u13Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u13Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u13Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u13Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u13Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u13Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u14Limitation( real_type xo___V ) const {
    real_type t2   = u14Limitation_min(-10 - xo___V);
    real_type t4   = u14Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u14Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u14Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u14Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u14Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u14Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u14Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u14Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u14Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u14Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u15Limitation( real_type xo___V ) const {
    real_type t2   = u15Limitation_min(-10 - xo___V);
    real_type t4   = u15Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u15Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u15Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u15Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u15Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u15Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u15Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u15Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u15Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u15Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u16Limitation( real_type xo___V ) const {
    real_type t2   = u16Limitation_min(-10 - xo___V);
    real_type t4   = u16Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u16Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u16Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u16Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u16Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u16Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u16Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u16Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u16Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u16Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u17Limitation( real_type xo___V ) const {
    real_type t2   = u17Limitation_min(-10 - xo___V);
    real_type t4   = u17Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u17Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u17Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u17Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u17Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u17Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u17Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u17Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u17Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u17Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u18Limitation( real_type xo___V ) const {
    real_type t2   = u18Limitation_min(-10 - xo___V);
    real_type t4   = u18Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u18Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u18Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u18Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u18Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u18Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u18Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u18Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u18Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u18Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u19Limitation( real_type xo___V ) const {
    real_type t2   = u19Limitation_min(-10 - xo___V);
    real_type t4   = u19Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u19Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u19Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u19Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u19Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u19Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u19Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u19Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u19Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u19Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u20Limitation( real_type xo___V ) const {
    real_type t2   = u20Limitation_min(-10 - xo___V);
    real_type t4   = u20Limitation_max(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u20Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u20Limitation_D( real_type xo___V ) const {
    real_type t2   = ALIAS_u20Limitation_min_D(-10 - xo___V);
    real_type t4   = ALIAS_u20Limitation_max_D(xo___V - 10);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u20Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::u20Limitation_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_u20Limitation_min_DD(-10 - xo___V);
    real_type t4   = ALIAS_u20Limitation_max_DD(xo___V - 10);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_u20Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx1Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx1Limitation_min(-t1 - xo___V);
    real_type t5   = xx1Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx1Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx1Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx1Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx1Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx1Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx1Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx1Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx1Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx1Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy1Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy1Limitation_min(-t1 - xo___V);
    real_type t5   = yy1Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy1Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy1Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy1Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy1Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy1Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy1Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy1Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy1Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy1Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx2Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx2Limitation_min(-t1 - xo___V);
    real_type t5   = xx2Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx2Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx2Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx2Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx2Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx2Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx2Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx2Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx2Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx2Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy2Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy2Limitation_min(-t1 - xo___V);
    real_type t5   = yy2Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy2Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy2Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy2Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy2Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy2Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy2Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy2Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy2Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy2Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx3Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx3Limitation_min(-t1 - xo___V);
    real_type t5   = xx3Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx3Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx3Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx3Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx3Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx3Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx3Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx3Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx3Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx3Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy3Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy3Limitation_min(-t1 - xo___V);
    real_type t5   = yy3Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy3Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy3Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy3Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy3Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy3Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy3Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy3Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy3Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy3Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx4Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx4Limitation_min(-t1 - xo___V);
    real_type t5   = xx4Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx4Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx4Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx4Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx4Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx4Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx4Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx4Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx4Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx4Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy4Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy4Limitation_min(-t1 - xo___V);
    real_type t5   = yy4Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy4Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy4Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy4Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy4Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy4Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy4Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy4Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy4Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy4Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx5Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx5Limitation_min(-t1 - xo___V);
    real_type t5   = xx5Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx5Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx5Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx5Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx5Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx5Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx5Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx5Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx5Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx5Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy5Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy5Limitation_min(-t1 - xo___V);
    real_type t5   = yy5Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy5Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy5Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy5Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy5Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy5Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy5Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy5Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy5Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy5Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx6Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx6Limitation_min(-t1 - xo___V);
    real_type t5   = xx6Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx6Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx6Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx6Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx6Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx6Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx6Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx6Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx6Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx6Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy6Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy6Limitation_min(-t1 - xo___V);
    real_type t5   = yy6Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy6Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy6Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy6Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy6Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy6Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy6Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy6Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy6Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy6Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx7Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx7Limitation_min(-t1 - xo___V);
    real_type t5   = xx7Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx7Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx7Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx7Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx7Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx7Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx7Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx7Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx7Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx7Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy7Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy7Limitation_min(-t1 - xo___V);
    real_type t5   = yy7Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy7Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy7Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy7Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy7Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy7Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy7Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy7Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy7Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy7Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx8Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx8Limitation_min(-t1 - xo___V);
    real_type t5   = xx8Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx8Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx8Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx8Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx8Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx8Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx8Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx8Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx8Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx8Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy8Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy8Limitation_min(-t1 - xo___V);
    real_type t5   = yy8Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy8Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy8Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy8Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy8Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy8Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy8Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy8Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy8Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy8Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx9Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx9Limitation_min(-t1 - xo___V);
    real_type t5   = xx9Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx9Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx9Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx9Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx9Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx9Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx9Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx9Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx9Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx9Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy9Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy9Limitation_min(-t1 - xo___V);
    real_type t5   = yy9Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy9Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy9Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy9Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy9Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy9Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy9Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy9Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy9Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy9Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx10Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx10Limitation_min(-t1 - xo___V);
    real_type t5   = xx10Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx10Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx10Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx10Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx10Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx10Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx10Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx10Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx10Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx10Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy10Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy10Limitation_min(-t1 - xo___V);
    real_type t5   = yy10Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy10Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy10Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy10Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy10Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy10Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy10Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy10Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy10Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy10Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx11Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx11Limitation_min(-t1 - xo___V);
    real_type t5   = xx11Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx11Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx11Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx11Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx11Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx11Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx11Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx11Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx11Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx11Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy11Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy11Limitation_min(-t1 - xo___V);
    real_type t5   = yy11Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy11Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy11Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy11Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy11Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy11Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy11Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy11Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy11Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy11Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx12Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx12Limitation_min(-t1 - xo___V);
    real_type t5   = xx12Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx12Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx12Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx12Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx12Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx12Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx12Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx12Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx12Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx12Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy12Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy12Limitation_min(-t1 - xo___V);
    real_type t5   = yy12Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy12Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy12Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy12Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy12Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy12Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy12Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy12Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy12Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy12Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx13Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx13Limitation_min(-t1 - xo___V);
    real_type t5   = xx13Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx13Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx13Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx13Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx13Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx13Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx13Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx13Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx13Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx13Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy13Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy13Limitation_min(-t1 - xo___V);
    real_type t5   = yy13Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy13Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy13Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy13Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy13Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy13Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy13Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy13Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy13Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy13Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx14Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx14Limitation_min(-t1 - xo___V);
    real_type t5   = xx14Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx14Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx14Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx14Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx14Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx14Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx14Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx14Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx14Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx14Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy14Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy14Limitation_min(-t1 - xo___V);
    real_type t5   = yy14Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy14Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy14Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy14Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy14Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy14Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy14Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy14Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy14Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy14Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx15Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx15Limitation_min(-t1 - xo___V);
    real_type t5   = xx15Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx15Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx15Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx15Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx15Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx15Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx15Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx15Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx15Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx15Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy15Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy15Limitation_min(-t1 - xo___V);
    real_type t5   = yy15Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy15Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy15Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy15Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy15Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy15Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy15Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy15Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy15Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy15Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx16Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx16Limitation_min(-t1 - xo___V);
    real_type t5   = xx16Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx16Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx16Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx16Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx16Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx16Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx16Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx16Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx16Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx16Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy16Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy16Limitation_min(-t1 - xo___V);
    real_type t5   = yy16Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy16Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy16Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy16Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy16Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy16Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy16Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy16Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy16Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy16Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx17Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx17Limitation_min(-t1 - xo___V);
    real_type t5   = xx17Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx17Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx17Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx17Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx17Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx17Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx17Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx17Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx17Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx17Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy17Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy17Limitation_min(-t1 - xo___V);
    real_type t5   = yy17Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy17Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy17Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy17Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy17Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy17Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy17Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy17Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy17Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy17Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx18Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx18Limitation_min(-t1 - xo___V);
    real_type t5   = xx18Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx18Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx18Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx18Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx18Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx18Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx18Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx18Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx18Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx18Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy18Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy18Limitation_min(-t1 - xo___V);
    real_type t5   = yy18Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy18Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy18Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy18Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy18Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy18Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy18Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy18Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy18Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy18Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx19Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx19Limitation_min(-t1 - xo___V);
    real_type t5   = xx19Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx19Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx19Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx19Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx19Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx19Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx19Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx19Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx19Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx19Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy19Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy19Limitation_min(-t1 - xo___V);
    real_type t5   = yy19Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy19Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy19Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy19Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy19Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy19Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy19Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy19Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy19Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy19Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx20Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = xx20Limitation_min(-t1 - xo___V);
    real_type t5   = xx20Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx20Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx20Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx20Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_xx20Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx20Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::xx20Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_xx20Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_xx20Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xx20Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy20Limitation( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = yy20Limitation_min(-t1 - xo___V);
    real_type t5   = yy20Limitation_max(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy20Limitation( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy20Limitation_D( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy20Limitation_min_D(-t1 - xo___V);
    real_type t5   = ALIAS_yy20Limitation_max_D(xo___V - t1);
    real_type result__ = -t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy20Limitation_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ContinuousMP::yy20Limitation_DD( real_type xo___V ) const {
    real_type t1   = ModelPars[iM_xy_bound];
    real_type t3   = ALIAS_yy20Limitation_min_DD(-t1 - xo___V);
    real_type t5   = ALIAS_yy20Limitation_max_DD(xo___V - t1);
    real_type result__ = t3 + t5;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yy20Limitation_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_UserFunctions.cc
