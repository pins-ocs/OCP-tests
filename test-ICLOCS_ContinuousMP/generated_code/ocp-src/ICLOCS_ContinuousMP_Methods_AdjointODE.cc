/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
#define ALIAS_yy20Limitation_DD(__t1) yy20Limitation.DD( __t1)
#define ALIAS_yy20Limitation_D(__t1) yy20Limitation.D( __t1)
#define ALIAS_xx20Limitation_DD(__t1) xx20Limitation.DD( __t1)
#define ALIAS_xx20Limitation_D(__t1) xx20Limitation.D( __t1)
#define ALIAS_yy19Limitation_DD(__t1) yy19Limitation.DD( __t1)
#define ALIAS_yy19Limitation_D(__t1) yy19Limitation.D( __t1)
#define ALIAS_xx19Limitation_DD(__t1) xx19Limitation.DD( __t1)
#define ALIAS_xx19Limitation_D(__t1) xx19Limitation.D( __t1)
#define ALIAS_yy18Limitation_DD(__t1) yy18Limitation.DD( __t1)
#define ALIAS_yy18Limitation_D(__t1) yy18Limitation.D( __t1)
#define ALIAS_xx18Limitation_DD(__t1) xx18Limitation.DD( __t1)
#define ALIAS_xx18Limitation_D(__t1) xx18Limitation.D( __t1)
#define ALIAS_yy17Limitation_DD(__t1) yy17Limitation.DD( __t1)
#define ALIAS_yy17Limitation_D(__t1) yy17Limitation.D( __t1)
#define ALIAS_xx17Limitation_DD(__t1) xx17Limitation.DD( __t1)
#define ALIAS_xx17Limitation_D(__t1) xx17Limitation.D( __t1)
#define ALIAS_yy16Limitation_DD(__t1) yy16Limitation.DD( __t1)
#define ALIAS_yy16Limitation_D(__t1) yy16Limitation.D( __t1)
#define ALIAS_xx16Limitation_DD(__t1) xx16Limitation.DD( __t1)
#define ALIAS_xx16Limitation_D(__t1) xx16Limitation.D( __t1)
#define ALIAS_yy15Limitation_DD(__t1) yy15Limitation.DD( __t1)
#define ALIAS_yy15Limitation_D(__t1) yy15Limitation.D( __t1)
#define ALIAS_xx15Limitation_DD(__t1) xx15Limitation.DD( __t1)
#define ALIAS_xx15Limitation_D(__t1) xx15Limitation.D( __t1)
#define ALIAS_yy14Limitation_DD(__t1) yy14Limitation.DD( __t1)
#define ALIAS_yy14Limitation_D(__t1) yy14Limitation.D( __t1)
#define ALIAS_xx14Limitation_DD(__t1) xx14Limitation.DD( __t1)
#define ALIAS_xx14Limitation_D(__t1) xx14Limitation.D( __t1)
#define ALIAS_yy13Limitation_DD(__t1) yy13Limitation.DD( __t1)
#define ALIAS_yy13Limitation_D(__t1) yy13Limitation.D( __t1)
#define ALIAS_xx13Limitation_DD(__t1) xx13Limitation.DD( __t1)
#define ALIAS_xx13Limitation_D(__t1) xx13Limitation.D( __t1)
#define ALIAS_yy12Limitation_DD(__t1) yy12Limitation.DD( __t1)
#define ALIAS_yy12Limitation_D(__t1) yy12Limitation.D( __t1)
#define ALIAS_xx12Limitation_DD(__t1) xx12Limitation.DD( __t1)
#define ALIAS_xx12Limitation_D(__t1) xx12Limitation.D( __t1)
#define ALIAS_yy11Limitation_DD(__t1) yy11Limitation.DD( __t1)
#define ALIAS_yy11Limitation_D(__t1) yy11Limitation.D( __t1)
#define ALIAS_xx11Limitation_DD(__t1) xx11Limitation.DD( __t1)
#define ALIAS_xx11Limitation_D(__t1) xx11Limitation.D( __t1)
#define ALIAS_yy10Limitation_DD(__t1) yy10Limitation.DD( __t1)
#define ALIAS_yy10Limitation_D(__t1) yy10Limitation.D( __t1)
#define ALIAS_xx10Limitation_DD(__t1) xx10Limitation.DD( __t1)
#define ALIAS_xx10Limitation_D(__t1) xx10Limitation.D( __t1)
#define ALIAS_yy9Limitation_DD(__t1) yy9Limitation.DD( __t1)
#define ALIAS_yy9Limitation_D(__t1) yy9Limitation.D( __t1)
#define ALIAS_xx9Limitation_DD(__t1) xx9Limitation.DD( __t1)
#define ALIAS_xx9Limitation_D(__t1) xx9Limitation.D( __t1)
#define ALIAS_yy8Limitation_DD(__t1) yy8Limitation.DD( __t1)
#define ALIAS_yy8Limitation_D(__t1) yy8Limitation.D( __t1)
#define ALIAS_xx8Limitation_DD(__t1) xx8Limitation.DD( __t1)
#define ALIAS_xx8Limitation_D(__t1) xx8Limitation.D( __t1)
#define ALIAS_yy7Limitation_DD(__t1) yy7Limitation.DD( __t1)
#define ALIAS_yy7Limitation_D(__t1) yy7Limitation.D( __t1)
#define ALIAS_xx7Limitation_DD(__t1) xx7Limitation.DD( __t1)
#define ALIAS_xx7Limitation_D(__t1) xx7Limitation.D( __t1)
#define ALIAS_yy6Limitation_DD(__t1) yy6Limitation.DD( __t1)
#define ALIAS_yy6Limitation_D(__t1) yy6Limitation.D( __t1)
#define ALIAS_xx6Limitation_DD(__t1) xx6Limitation.DD( __t1)
#define ALIAS_xx6Limitation_D(__t1) xx6Limitation.D( __t1)
#define ALIAS_yy5Limitation_DD(__t1) yy5Limitation.DD( __t1)
#define ALIAS_yy5Limitation_D(__t1) yy5Limitation.D( __t1)
#define ALIAS_xx5Limitation_DD(__t1) xx5Limitation.DD( __t1)
#define ALIAS_xx5Limitation_D(__t1) xx5Limitation.D( __t1)
#define ALIAS_yy4Limitation_DD(__t1) yy4Limitation.DD( __t1)
#define ALIAS_yy4Limitation_D(__t1) yy4Limitation.D( __t1)
#define ALIAS_xx4Limitation_DD(__t1) xx4Limitation.DD( __t1)
#define ALIAS_xx4Limitation_D(__t1) xx4Limitation.D( __t1)
#define ALIAS_yy3Limitation_DD(__t1) yy3Limitation.DD( __t1)
#define ALIAS_yy3Limitation_D(__t1) yy3Limitation.D( __t1)
#define ALIAS_xx3Limitation_DD(__t1) xx3Limitation.DD( __t1)
#define ALIAS_xx3Limitation_D(__t1) xx3Limitation.D( __t1)
#define ALIAS_yy2Limitation_DD(__t1) yy2Limitation.DD( __t1)
#define ALIAS_yy2Limitation_D(__t1) yy2Limitation.D( __t1)
#define ALIAS_xx2Limitation_DD(__t1) xx2Limitation.DD( __t1)
#define ALIAS_xx2Limitation_D(__t1) xx2Limitation.D( __t1)
#define ALIAS_yy1Limitation_DD(__t1) yy1Limitation.DD( __t1)
#define ALIAS_yy1Limitation_D(__t1) yy1Limitation.D( __t1)
#define ALIAS_xx1Limitation_DD(__t1) xx1Limitation.DD( __t1)
#define ALIAS_xx1Limitation_D(__t1) xx1Limitation.D( __t1)
#define ALIAS_u20Limitation_DD(__t1) u20Limitation.DD( __t1)
#define ALIAS_u20Limitation_D(__t1) u20Limitation.D( __t1)
#define ALIAS_u19Limitation_DD(__t1) u19Limitation.DD( __t1)
#define ALIAS_u19Limitation_D(__t1) u19Limitation.D( __t1)
#define ALIAS_u18Limitation_DD(__t1) u18Limitation.DD( __t1)
#define ALIAS_u18Limitation_D(__t1) u18Limitation.D( __t1)
#define ALIAS_u17Limitation_DD(__t1) u17Limitation.DD( __t1)
#define ALIAS_u17Limitation_D(__t1) u17Limitation.D( __t1)
#define ALIAS_u16Limitation_DD(__t1) u16Limitation.DD( __t1)
#define ALIAS_u16Limitation_D(__t1) u16Limitation.D( __t1)
#define ALIAS_u15Limitation_DD(__t1) u15Limitation.DD( __t1)
#define ALIAS_u15Limitation_D(__t1) u15Limitation.D( __t1)
#define ALIAS_u14Limitation_DD(__t1) u14Limitation.DD( __t1)
#define ALIAS_u14Limitation_D(__t1) u14Limitation.D( __t1)
#define ALIAS_u13Limitation_DD(__t1) u13Limitation.DD( __t1)
#define ALIAS_u13Limitation_D(__t1) u13Limitation.D( __t1)
#define ALIAS_u12Limitation_DD(__t1) u12Limitation.DD( __t1)
#define ALIAS_u12Limitation_D(__t1) u12Limitation.D( __t1)
#define ALIAS_u11Limitation_DD(__t1) u11Limitation.DD( __t1)
#define ALIAS_u11Limitation_D(__t1) u11Limitation.D( __t1)
#define ALIAS_u10Limitation_DD(__t1) u10Limitation.DD( __t1)
#define ALIAS_u10Limitation_D(__t1) u10Limitation.D( __t1)
#define ALIAS_u9Limitation_DD(__t1) u9Limitation.DD( __t1)
#define ALIAS_u9Limitation_D(__t1) u9Limitation.D( __t1)
#define ALIAS_u8Limitation_DD(__t1) u8Limitation.DD( __t1)
#define ALIAS_u8Limitation_D(__t1) u8Limitation.D( __t1)
#define ALIAS_u7Limitation_DD(__t1) u7Limitation.DD( __t1)
#define ALIAS_u7Limitation_D(__t1) u7Limitation.D( __t1)
#define ALIAS_u6Limitation_DD(__t1) u6Limitation.DD( __t1)
#define ALIAS_u6Limitation_D(__t1) u6Limitation.D( __t1)
#define ALIAS_u5Limitation_DD(__t1) u5Limitation.DD( __t1)
#define ALIAS_u5Limitation_D(__t1) u5Limitation.D( __t1)
#define ALIAS_u4Limitation_DD(__t1) u4Limitation.DD( __t1)
#define ALIAS_u4Limitation_D(__t1) u4Limitation.D( __t1)
#define ALIAS_u3Limitation_DD(__t1) u3Limitation.DD( __t1)
#define ALIAS_u3Limitation_D(__t1) u3Limitation.D( __t1)
#define ALIAS_u2Limitation_DD(__t1) u2Limitation.DD( __t1)
#define ALIAS_u2Limitation_D(__t1) u2Limitation.D( __t1)
#define ALIAS_u1Limitation_DD(__t1) u1Limitation.DD( __t1)
#define ALIAS_u1Limitation_D(__t1) u1Limitation.D( __t1)


namespace ICLOCS_ContinuousMPDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS_ContinuousMP::Hx_numEqns() const
  { return 80; }

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
    real_type t2   = X__[iX_x1];
    real_type t3   = cos(t2);
    result__[ 0   ] = t3 * L__[iL_lambda21__xo] + 40 * t2;
    real_type t7   = X__[iX_x2];
    real_type t8   = cos(t7);
    result__[ 1   ] = t8 * L__[iL_lambda22__xo] + 38 * t7;
    real_type t12  = X__[iX_x3];
    real_type t13  = cos(t12);
    result__[ 2   ] = t13 * L__[iL_lambda23__xo] + 36 * t12;
    real_type t17  = X__[iX_x4];
    real_type t18  = cos(t17);
    result__[ 3   ] = t18 * L__[iL_lambda24__xo] + 34 * t17;
    real_type t22  = X__[iX_x5];
    real_type t23  = cos(t22);
    result__[ 4   ] = t23 * L__[iL_lambda25__xo] + 32 * t22;
    real_type t27  = X__[iX_x6];
    real_type t28  = cos(t27);
    result__[ 5   ] = t28 * L__[iL_lambda26__xo] + 30 * t27;
    real_type t32  = X__[iX_x7];
    real_type t33  = cos(t32);
    result__[ 6   ] = t33 * L__[iL_lambda27__xo] + 28 * t32;
    real_type t37  = X__[iX_x8];
    real_type t38  = cos(t37);
    result__[ 7   ] = t38 * L__[iL_lambda28__xo] + 26 * t37;
    real_type t42  = X__[iX_x9];
    real_type t43  = cos(t42);
    result__[ 8   ] = t43 * L__[iL_lambda29__xo] + 24 * t42;
    real_type t47  = X__[iX_x10];
    real_type t48  = cos(t47);
    result__[ 9   ] = t48 * L__[iL_lambda30__xo] + 22 * t47;
    real_type t52  = X__[iX_x11];
    real_type t53  = cos(t52);
    result__[ 10  ] = t53 * L__[iL_lambda31__xo] + 20 * t52;
    real_type t57  = X__[iX_x12];
    real_type t58  = cos(t57);
    result__[ 11  ] = t58 * L__[iL_lambda32__xo] + 18 * t57;
    real_type t62  = X__[iX_x13];
    real_type t63  = cos(t62);
    result__[ 12  ] = t63 * L__[iL_lambda33__xo] + 16 * t62;
    real_type t67  = X__[iX_x14];
    real_type t68  = cos(t67);
    result__[ 13  ] = t68 * L__[iL_lambda34__xo] + 14 * t67;
    real_type t72  = X__[iX_x15];
    real_type t73  = cos(t72);
    result__[ 14  ] = t73 * L__[iL_lambda35__xo] + 12 * t72;
    real_type t77  = X__[iX_x16];
    real_type t78  = cos(t77);
    result__[ 15  ] = t78 * L__[iL_lambda36__xo] + 10 * t77;
    real_type t82  = X__[iX_x17];
    real_type t83  = cos(t82);
    result__[ 16  ] = t83 * L__[iL_lambda37__xo] + 8 * t82;
    real_type t87  = X__[iX_x18];
    real_type t88  = cos(t87);
    result__[ 17  ] = t88 * L__[iL_lambda38__xo] + 6 * t87;
    real_type t92  = X__[iX_x19];
    real_type t93  = cos(t92);
    result__[ 18  ] = t93 * L__[iL_lambda39__xo] + 4 * t92;
    real_type t97  = X__[iX_x20];
    real_type t98  = cos(t97);
    result__[ 19  ] = t98 * L__[iL_lambda40__xo] + 2 * t97;
    result__[ 20  ] = L__[iL_lambda1__xo] + 40 * X__[iX_y1];
    result__[ 21  ] = L__[iL_lambda2__xo] + 38 * X__[iX_y2];
    result__[ 22  ] = L__[iL_lambda3__xo] + 36 * X__[iX_y3];
    result__[ 23  ] = L__[iL_lambda4__xo] + 34 * X__[iX_y4];
    result__[ 24  ] = L__[iL_lambda5__xo] + 32 * X__[iX_y5];
    result__[ 25  ] = L__[iL_lambda6__xo] + 30 * X__[iX_y6];
    result__[ 26  ] = L__[iL_lambda7__xo] + 28 * X__[iX_y7];
    result__[ 27  ] = L__[iL_lambda8__xo] + 26 * X__[iX_y8];
    result__[ 28  ] = L__[iL_lambda9__xo] + 24 * X__[iX_y9];
    result__[ 29  ] = L__[iL_lambda10__xo] + 22 * X__[iX_y10];
    result__[ 30  ] = L__[iL_lambda11__xo] + 20 * X__[iX_y11];
    result__[ 31  ] = L__[iL_lambda12__xo] + 18 * X__[iX_y12];
    result__[ 32  ] = L__[iL_lambda13__xo] + 16 * X__[iX_y13];
    result__[ 33  ] = L__[iL_lambda14__xo] + 14 * X__[iX_y14];
    result__[ 34  ] = L__[iL_lambda15__xo] + 12 * X__[iX_y15];
    result__[ 35  ] = L__[iL_lambda16__xo] + 10 * X__[iX_y16];
    result__[ 36  ] = L__[iL_lambda17__xo] + 8 * X__[iX_y17];
    result__[ 37  ] = L__[iL_lambda18__xo] + 6 * X__[iX_y18];
    result__[ 38  ] = L__[iL_lambda19__xo] + 4 * X__[iX_y19];
    result__[ 39  ] = L__[iL_lambda20__xo] + 2 * X__[iX_y20];
    real_type t162 = X__[iX_xx1];
    real_type t163 = cos(t162);
    real_type t166 = ALIAS_xx1Limitation_D(t162);
    result__[ 40  ] = 0.2e0 * t163 * L__[iL_lambda61__xo] + t166;
    real_type t168 = X__[iX_xx2];
    real_type t169 = cos(t168);
    real_type t172 = ALIAS_xx2Limitation_D(t168);
    result__[ 41  ] = 0.2e0 * t169 * L__[iL_lambda62__xo] + t172;
    real_type t174 = X__[iX_xx3];
    real_type t175 = cos(t174);
    real_type t178 = ALIAS_xx3Limitation_D(t174);
    result__[ 42  ] = 0.2e0 * t175 * L__[iL_lambda63__xo] + t178;
    real_type t180 = X__[iX_xx4];
    real_type t181 = cos(t180);
    real_type t184 = ALIAS_xx4Limitation_D(t180);
    result__[ 43  ] = 0.2e0 * t181 * L__[iL_lambda64__xo] + t184;
    real_type t186 = X__[iX_xx5];
    real_type t187 = cos(t186);
    real_type t190 = ALIAS_xx5Limitation_D(t186);
    result__[ 44  ] = 0.2e0 * t187 * L__[iL_lambda65__xo] + t190;
    real_type t192 = X__[iX_xx6];
    real_type t193 = cos(t192);
    real_type t196 = ALIAS_xx6Limitation_D(t192);
    result__[ 45  ] = 0.2e0 * t193 * L__[iL_lambda66__xo] + t196;
    real_type t198 = X__[iX_xx7];
    real_type t199 = cos(t198);
    real_type t202 = ALIAS_xx7Limitation_D(t198);
    result__[ 46  ] = 0.2e0 * t199 * L__[iL_lambda67__xo] + t202;
    real_type t204 = X__[iX_xx8];
    real_type t205 = cos(t204);
    real_type t208 = ALIAS_xx8Limitation_D(t204);
    result__[ 47  ] = 0.2e0 * t205 * L__[iL_lambda68__xo] + t208;
    real_type t210 = X__[iX_xx9];
    real_type t211 = cos(t210);
    real_type t214 = ALIAS_xx9Limitation_D(t210);
    result__[ 48  ] = 0.2e0 * t211 * L__[iL_lambda69__xo] + t214;
    real_type t216 = X__[iX_xx10];
    real_type t217 = cos(t216);
    real_type t220 = ALIAS_xx10Limitation_D(t216);
    result__[ 49  ] = 0.2e0 * t217 * L__[iL_lambda70__xo] + t220;
    real_type t222 = X__[iX_xx11];
    real_type t223 = cos(t222);
    real_type t226 = ALIAS_xx11Limitation_D(t222);
    result__[ 50  ] = 0.2e0 * t223 * L__[iL_lambda71__xo] + t226;
    real_type t228 = X__[iX_xx12];
    real_type t229 = cos(t228);
    real_type t232 = ALIAS_xx12Limitation_D(t228);
    result__[ 51  ] = 0.2e0 * t229 * L__[iL_lambda72__xo] + t232;
    real_type t234 = X__[iX_xx13];
    real_type t235 = cos(t234);
    real_type t238 = ALIAS_xx13Limitation_D(t234);
    result__[ 52  ] = 0.2e0 * t235 * L__[iL_lambda73__xo] + t238;
    real_type t240 = X__[iX_xx14];
    real_type t241 = cos(t240);
    real_type t244 = ALIAS_xx14Limitation_D(t240);
    result__[ 53  ] = 0.2e0 * t241 * L__[iL_lambda74__xo] + t244;
    real_type t246 = X__[iX_xx15];
    real_type t247 = cos(t246);
    real_type t250 = ALIAS_xx15Limitation_D(t246);
    result__[ 54  ] = 0.2e0 * t247 * L__[iL_lambda75__xo] + t250;
    real_type t252 = X__[iX_xx16];
    real_type t253 = cos(t252);
    real_type t256 = ALIAS_xx16Limitation_D(t252);
    result__[ 55  ] = 0.2e0 * t253 * L__[iL_lambda76__xo] + t256;
    real_type t258 = X__[iX_xx17];
    real_type t259 = cos(t258);
    real_type t262 = ALIAS_xx17Limitation_D(t258);
    result__[ 56  ] = 0.2e0 * t259 * L__[iL_lambda77__xo] + t262;
    real_type t264 = X__[iX_xx18];
    real_type t265 = cos(t264);
    real_type t268 = ALIAS_xx18Limitation_D(t264);
    result__[ 57  ] = 0.2e0 * t265 * L__[iL_lambda78__xo] + t268;
    real_type t270 = X__[iX_xx19];
    real_type t271 = cos(t270);
    real_type t274 = ALIAS_xx19Limitation_D(t270);
    result__[ 58  ] = 0.2e0 * t271 * L__[iL_lambda79__xo] + t274;
    real_type t276 = X__[iX_xx20];
    real_type t277 = cos(t276);
    real_type t280 = ALIAS_xx20Limitation_D(t276);
    result__[ 59  ] = 0.2e0 * t277 * L__[iL_lambda80__xo] + t280;
    real_type t284 = ALIAS_yy1Limitation_D(X__[iX_yy1]);
    result__[ 60  ] = 0.12e1 * L__[iL_lambda41__xo] + t284;
    real_type t288 = ALIAS_yy2Limitation_D(X__[iX_yy2]);
    result__[ 61  ] = 0.12e1 * L__[iL_lambda42__xo] + t288;
    real_type t292 = ALIAS_yy3Limitation_D(X__[iX_yy3]);
    result__[ 62  ] = 0.12e1 * L__[iL_lambda43__xo] + t292;
    real_type t296 = ALIAS_yy4Limitation_D(X__[iX_yy4]);
    result__[ 63  ] = 0.12e1 * L__[iL_lambda44__xo] + t296;
    real_type t300 = ALIAS_yy5Limitation_D(X__[iX_yy5]);
    result__[ 64  ] = 0.12e1 * L__[iL_lambda45__xo] + t300;
    real_type t304 = ALIAS_yy6Limitation_D(X__[iX_yy6]);
    result__[ 65  ] = 0.12e1 * L__[iL_lambda46__xo] + t304;
    real_type t308 = ALIAS_yy7Limitation_D(X__[iX_yy7]);
    result__[ 66  ] = 0.12e1 * L__[iL_lambda47__xo] + t308;
    real_type t312 = ALIAS_yy8Limitation_D(X__[iX_yy8]);
    result__[ 67  ] = 0.12e1 * L__[iL_lambda48__xo] + t312;
    real_type t316 = ALIAS_yy9Limitation_D(X__[iX_yy9]);
    result__[ 68  ] = 0.12e1 * L__[iL_lambda49__xo] + t316;
    real_type t320 = ALIAS_yy10Limitation_D(X__[iX_yy10]);
    result__[ 69  ] = 0.12e1 * L__[iL_lambda50__xo] + t320;
    real_type t324 = ALIAS_yy11Limitation_D(X__[iX_yy11]);
    result__[ 70  ] = 0.12e1 * L__[iL_lambda51__xo] + t324;
    real_type t328 = ALIAS_yy12Limitation_D(X__[iX_yy12]);
    result__[ 71  ] = 0.12e1 * L__[iL_lambda52__xo] + t328;
    real_type t332 = ALIAS_yy13Limitation_D(X__[iX_yy13]);
    result__[ 72  ] = 0.12e1 * L__[iL_lambda53__xo] + t332;
    real_type t336 = ALIAS_yy14Limitation_D(X__[iX_yy14]);
    result__[ 73  ] = 0.12e1 * L__[iL_lambda54__xo] + t336;
    real_type t340 = ALIAS_yy15Limitation_D(X__[iX_yy15]);
    result__[ 74  ] = 0.12e1 * L__[iL_lambda55__xo] + t340;
    real_type t344 = ALIAS_yy16Limitation_D(X__[iX_yy16]);
    result__[ 75  ] = 0.12e1 * L__[iL_lambda56__xo] + t344;
    real_type t348 = ALIAS_yy17Limitation_D(X__[iX_yy17]);
    result__[ 76  ] = 0.12e1 * L__[iL_lambda57__xo] + t348;
    real_type t352 = ALIAS_yy18Limitation_D(X__[iX_yy18]);
    result__[ 77  ] = 0.12e1 * L__[iL_lambda58__xo] + t352;
    real_type t356 = ALIAS_yy19Limitation_D(X__[iX_yy19]);
    result__[ 78  ] = 0.12e1 * L__[iL_lambda59__xo] + t356;
    real_type t360 = ALIAS_yy20Limitation_D(X__[iX_yy20]);
    result__[ 79  ] = 0.12e1 * L__[iL_lambda60__xo] + t360;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DHxDx_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DHxDx_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DHxDx_nnz() const
  { return 80; }

  void
  ICLOCS_ContinuousMP::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
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

  void
  ICLOCS_ContinuousMP::DHxDx_sparse(
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
    real_type t82  = X__[iX_xx1];
    real_type t83  = sin(t82);
    real_type t86  = ALIAS_xx1Limitation_DD(t82);
    result__[ 40  ] = -0.2e0 * t83 * L__[iL_lambda61__xo] + t86;
    real_type t88  = X__[iX_xx2];
    real_type t89  = sin(t88);
    real_type t92  = ALIAS_xx2Limitation_DD(t88);
    result__[ 41  ] = -0.2e0 * t89 * L__[iL_lambda62__xo] + t92;
    real_type t94  = X__[iX_xx3];
    real_type t95  = sin(t94);
    real_type t98  = ALIAS_xx3Limitation_DD(t94);
    result__[ 42  ] = -0.2e0 * t95 * L__[iL_lambda63__xo] + t98;
    real_type t100 = X__[iX_xx4];
    real_type t101 = sin(t100);
    real_type t104 = ALIAS_xx4Limitation_DD(t100);
    result__[ 43  ] = -0.2e0 * t101 * L__[iL_lambda64__xo] + t104;
    real_type t106 = X__[iX_xx5];
    real_type t107 = sin(t106);
    real_type t110 = ALIAS_xx5Limitation_DD(t106);
    result__[ 44  ] = -0.2e0 * t107 * L__[iL_lambda65__xo] + t110;
    real_type t112 = X__[iX_xx6];
    real_type t113 = sin(t112);
    real_type t116 = ALIAS_xx6Limitation_DD(t112);
    result__[ 45  ] = -0.2e0 * t113 * L__[iL_lambda66__xo] + t116;
    real_type t118 = X__[iX_xx7];
    real_type t119 = sin(t118);
    real_type t122 = ALIAS_xx7Limitation_DD(t118);
    result__[ 46  ] = -0.2e0 * t119 * L__[iL_lambda67__xo] + t122;
    real_type t124 = X__[iX_xx8];
    real_type t125 = sin(t124);
    real_type t128 = ALIAS_xx8Limitation_DD(t124);
    result__[ 47  ] = -0.2e0 * t125 * L__[iL_lambda68__xo] + t128;
    real_type t130 = X__[iX_xx9];
    real_type t131 = sin(t130);
    real_type t134 = ALIAS_xx9Limitation_DD(t130);
    result__[ 48  ] = -0.2e0 * t131 * L__[iL_lambda69__xo] + t134;
    real_type t136 = X__[iX_xx10];
    real_type t137 = sin(t136);
    real_type t140 = ALIAS_xx10Limitation_DD(t136);
    result__[ 49  ] = -0.2e0 * t137 * L__[iL_lambda70__xo] + t140;
    real_type t142 = X__[iX_xx11];
    real_type t143 = sin(t142);
    real_type t146 = ALIAS_xx11Limitation_DD(t142);
    result__[ 50  ] = -0.2e0 * t143 * L__[iL_lambda71__xo] + t146;
    real_type t148 = X__[iX_xx12];
    real_type t149 = sin(t148);
    real_type t152 = ALIAS_xx12Limitation_DD(t148);
    result__[ 51  ] = -0.2e0 * t149 * L__[iL_lambda72__xo] + t152;
    real_type t154 = X__[iX_xx13];
    real_type t155 = sin(t154);
    real_type t158 = ALIAS_xx13Limitation_DD(t154);
    result__[ 52  ] = -0.2e0 * t155 * L__[iL_lambda73__xo] + t158;
    real_type t160 = X__[iX_xx14];
    real_type t161 = sin(t160);
    real_type t164 = ALIAS_xx14Limitation_DD(t160);
    result__[ 53  ] = -0.2e0 * t161 * L__[iL_lambda74__xo] + t164;
    real_type t166 = X__[iX_xx15];
    real_type t167 = sin(t166);
    real_type t170 = ALIAS_xx15Limitation_DD(t166);
    result__[ 54  ] = -0.2e0 * t167 * L__[iL_lambda75__xo] + t170;
    real_type t172 = X__[iX_xx16];
    real_type t173 = sin(t172);
    real_type t176 = ALIAS_xx16Limitation_DD(t172);
    result__[ 55  ] = -0.2e0 * t173 * L__[iL_lambda76__xo] + t176;
    real_type t178 = X__[iX_xx17];
    real_type t179 = sin(t178);
    real_type t182 = ALIAS_xx17Limitation_DD(t178);
    result__[ 56  ] = -0.2e0 * t179 * L__[iL_lambda77__xo] + t182;
    real_type t184 = X__[iX_xx18];
    real_type t185 = sin(t184);
    real_type t188 = ALIAS_xx18Limitation_DD(t184);
    result__[ 57  ] = -0.2e0 * t185 * L__[iL_lambda78__xo] + t188;
    real_type t190 = X__[iX_xx19];
    real_type t191 = sin(t190);
    real_type t194 = ALIAS_xx19Limitation_DD(t190);
    result__[ 58  ] = -0.2e0 * t191 * L__[iL_lambda79__xo] + t194;
    real_type t196 = X__[iX_xx20];
    real_type t197 = sin(t196);
    real_type t200 = ALIAS_xx20Limitation_DD(t196);
    result__[ 59  ] = -0.2e0 * t197 * L__[iL_lambda80__xo] + t200;
    result__[ 60  ] = ALIAS_yy1Limitation_DD(X__[iX_yy1]);
    result__[ 61  ] = ALIAS_yy2Limitation_DD(X__[iX_yy2]);
    result__[ 62  ] = ALIAS_yy3Limitation_DD(X__[iX_yy3]);
    result__[ 63  ] = ALIAS_yy4Limitation_DD(X__[iX_yy4]);
    result__[ 64  ] = ALIAS_yy5Limitation_DD(X__[iX_yy5]);
    result__[ 65  ] = ALIAS_yy6Limitation_DD(X__[iX_yy6]);
    result__[ 66  ] = ALIAS_yy7Limitation_DD(X__[iX_yy7]);
    result__[ 67  ] = ALIAS_yy8Limitation_DD(X__[iX_yy8]);
    result__[ 68  ] = ALIAS_yy9Limitation_DD(X__[iX_yy9]);
    result__[ 69  ] = ALIAS_yy10Limitation_DD(X__[iX_yy10]);
    result__[ 70  ] = ALIAS_yy11Limitation_DD(X__[iX_yy11]);
    result__[ 71  ] = ALIAS_yy12Limitation_DD(X__[iX_yy12]);
    result__[ 72  ] = ALIAS_yy13Limitation_DD(X__[iX_yy13]);
    result__[ 73  ] = ALIAS_yy14Limitation_DD(X__[iX_yy14]);
    result__[ 74  ] = ALIAS_yy15Limitation_DD(X__[iX_yy15]);
    result__[ 75  ] = ALIAS_yy16Limitation_DD(X__[iX_yy16]);
    result__[ 76  ] = ALIAS_yy17Limitation_DD(X__[iX_yy17]);
    result__[ 77  ] = ALIAS_yy18Limitation_DD(X__[iX_yy18]);
    result__[ 78  ] = ALIAS_yy19Limitation_DD(X__[iX_yy19]);
    result__[ 79  ] = ALIAS_yy20Limitation_DD(X__[iX_yy20]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DHxDp_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DHxDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DHxDp_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DHxDp_sparse(
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

  integer
  ICLOCS_ContinuousMP::Hu_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DHuDx_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DHuDx_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DHuDx_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DHuDp_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DHuDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DHuDp_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  ICLOCS_ContinuousMP::Hp_numEqns() const
  { return 20; }

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
    real_type t4   = ALIAS_u1Limitation_D(P__[iP_u1]);
    result__[ 0   ] = L__[iL_lambda61__xo] + L__[iL_lambda21__xo] + t4;
    real_type t8   = ALIAS_u2Limitation_D(P__[iP_u2]);
    result__[ 1   ] = L__[iL_lambda62__xo] + L__[iL_lambda22__xo] + t8;
    real_type t12  = ALIAS_u3Limitation_D(P__[iP_u3]);
    result__[ 2   ] = L__[iL_lambda63__xo] + L__[iL_lambda23__xo] + t12;
    real_type t16  = ALIAS_u4Limitation_D(P__[iP_u4]);
    result__[ 3   ] = L__[iL_lambda64__xo] + L__[iL_lambda24__xo] + t16;
    real_type t20  = ALIAS_u5Limitation_D(P__[iP_u5]);
    result__[ 4   ] = L__[iL_lambda65__xo] + L__[iL_lambda25__xo] + t20;
    real_type t24  = ALIAS_u6Limitation_D(P__[iP_u6]);
    result__[ 5   ] = L__[iL_lambda66__xo] + L__[iL_lambda26__xo] + t24;
    real_type t28  = ALIAS_u7Limitation_D(P__[iP_u7]);
    result__[ 6   ] = L__[iL_lambda67__xo] + L__[iL_lambda27__xo] + t28;
    real_type t32  = ALIAS_u8Limitation_D(P__[iP_u8]);
    result__[ 7   ] = L__[iL_lambda28__xo] + L__[iL_lambda68__xo] + t32;
    real_type t36  = ALIAS_u9Limitation_D(P__[iP_u9]);
    result__[ 8   ] = L__[iL_lambda69__xo] + L__[iL_lambda29__xo] + t36;
    real_type t40  = ALIAS_u10Limitation_D(P__[iP_u10]);
    result__[ 9   ] = L__[iL_lambda70__xo] + L__[iL_lambda30__xo] + t40;
    real_type t44  = ALIAS_u11Limitation_D(P__[iP_u11]);
    result__[ 10  ] = L__[iL_lambda71__xo] + L__[iL_lambda31__xo] + t44;
    real_type t48  = ALIAS_u12Limitation_D(P__[iP_u12]);
    result__[ 11  ] = L__[iL_lambda72__xo] + L__[iL_lambda32__xo] + t48;
    real_type t52  = ALIAS_u13Limitation_D(P__[iP_u13]);
    result__[ 12  ] = L__[iL_lambda73__xo] + L__[iL_lambda33__xo] + t52;
    real_type t56  = ALIAS_u14Limitation_D(P__[iP_u14]);
    result__[ 13  ] = L__[iL_lambda74__xo] + L__[iL_lambda34__xo] + t56;
    real_type t60  = ALIAS_u15Limitation_D(P__[iP_u15]);
    result__[ 14  ] = L__[iL_lambda75__xo] + L__[iL_lambda35__xo] + t60;
    real_type t64  = ALIAS_u16Limitation_D(P__[iP_u16]);
    result__[ 15  ] = L__[iL_lambda76__xo] + L__[iL_lambda36__xo] + t64;
    real_type t68  = ALIAS_u17Limitation_D(P__[iP_u17]);
    result__[ 16  ] = L__[iL_lambda77__xo] + L__[iL_lambda37__xo] + t68;
    real_type t72  = ALIAS_u18Limitation_D(P__[iP_u18]);
    result__[ 17  ] = L__[iL_lambda78__xo] + L__[iL_lambda38__xo] + t72;
    real_type t76  = ALIAS_u19Limitation_D(P__[iP_u19]);
    result__[ 18  ] = L__[iL_lambda79__xo] + L__[iL_lambda39__xo] + t76;
    real_type t80  = ALIAS_u20Limitation_D(P__[iP_u20]);
    result__[ 19  ] = L__[iL_lambda80__xo] + L__[iL_lambda40__xo] + t80;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DHpDp_numRows() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DHpDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DHpDp_nnz() const
  { return 20; }

  void
  ICLOCS_ContinuousMP::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DHpDp_sparse(
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
    result__[ 0   ] = ALIAS_u1Limitation_DD(P__[iP_u1]);
    result__[ 1   ] = ALIAS_u2Limitation_DD(P__[iP_u2]);
    result__[ 2   ] = ALIAS_u3Limitation_DD(P__[iP_u3]);
    result__[ 3   ] = ALIAS_u4Limitation_DD(P__[iP_u4]);
    result__[ 4   ] = ALIAS_u5Limitation_DD(P__[iP_u5]);
    result__[ 5   ] = ALIAS_u6Limitation_DD(P__[iP_u6]);
    result__[ 6   ] = ALIAS_u7Limitation_DD(P__[iP_u7]);
    result__[ 7   ] = ALIAS_u8Limitation_DD(P__[iP_u8]);
    result__[ 8   ] = ALIAS_u9Limitation_DD(P__[iP_u9]);
    result__[ 9   ] = ALIAS_u10Limitation_DD(P__[iP_u10]);
    result__[ 10  ] = ALIAS_u11Limitation_DD(P__[iP_u11]);
    result__[ 11  ] = ALIAS_u12Limitation_DD(P__[iP_u12]);
    result__[ 12  ] = ALIAS_u13Limitation_DD(P__[iP_u13]);
    result__[ 13  ] = ALIAS_u14Limitation_DD(P__[iP_u14]);
    result__[ 14  ] = ALIAS_u15Limitation_DD(P__[iP_u15]);
    result__[ 15  ] = ALIAS_u16Limitation_DD(P__[iP_u16]);
    result__[ 16  ] = ALIAS_u17Limitation_DD(P__[iP_u17]);
    result__[ 17  ] = ALIAS_u18Limitation_DD(P__[iP_u18]);
    result__[ 18  ] = ALIAS_u19Limitation_DD(P__[iP_u19]);
    result__[ 19  ] = ALIAS_u20Limitation_DD(P__[iP_u20]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse" ,20, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  ICLOCS_ContinuousMP::eta_numEqns() const
  { return 80; }

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

  integer
  ICLOCS_ContinuousMP::DetaDx_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DetaDx_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DetaDp_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DetaDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DetaDp_sparse(
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

  integer
  ICLOCS_ContinuousMP::nu_numEqns() const
  { return 80; }

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

  integer
  ICLOCS_ContinuousMP::DnuDx_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DnuDx_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DnuDp_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::DnuDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_AdjointODE.cc
