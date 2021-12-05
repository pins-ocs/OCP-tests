/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_problem.cc                         |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_ContinuousMP::continuation_step_0( real_type s ) {
    real_type t1   = ModelPars[iM_xy_eps0];
    real_type t5   = t1 + (ModelPars[iM_xy_eps1] - t1) * s;
    xx1Limitation.update_epsilon(t5);
    yy1Limitation.update_epsilon(t5);
    real_type t6   = ModelPars[iM_xy_tol0];
    real_type t10  = t6 + (ModelPars[iM_xy_tol1] - t6) * s;
    xx1Limitation.update_tolerance(t10);
    yy1Limitation.update_tolerance(t10);
    xx2Limitation.update_epsilon(t5);
    yy2Limitation.update_epsilon(t5);
    xx2Limitation.update_tolerance(t10);
    yy2Limitation.update_tolerance(t10);
    xx3Limitation.update_epsilon(t5);
    yy3Limitation.update_epsilon(t5);
    xx3Limitation.update_tolerance(t10);
    yy3Limitation.update_tolerance(t10);
    xx4Limitation.update_epsilon(t5);
    yy4Limitation.update_epsilon(t5);
    xx4Limitation.update_tolerance(t10);
    yy4Limitation.update_tolerance(t10);
    xx5Limitation.update_epsilon(t5);
    yy5Limitation.update_epsilon(t5);
    xx5Limitation.update_tolerance(t10);
    yy5Limitation.update_tolerance(t10);
    xx6Limitation.update_epsilon(t5);
    yy6Limitation.update_epsilon(t5);
    xx6Limitation.update_tolerance(t10);
    yy6Limitation.update_tolerance(t10);
    xx7Limitation.update_epsilon(t5);
    yy7Limitation.update_epsilon(t5);
    xx7Limitation.update_tolerance(t10);
    yy7Limitation.update_tolerance(t10);
    xx8Limitation.update_epsilon(t5);
    yy8Limitation.update_epsilon(t5);
    xx8Limitation.update_tolerance(t10);
    yy8Limitation.update_tolerance(t10);
    xx9Limitation.update_epsilon(t5);
    yy9Limitation.update_epsilon(t5);
    xx9Limitation.update_tolerance(t10);
    yy9Limitation.update_tolerance(t10);
    xx10Limitation.update_epsilon(t5);
    yy10Limitation.update_epsilon(t5);
    xx10Limitation.update_tolerance(t10);
    yy10Limitation.update_tolerance(t10);
    xx11Limitation.update_epsilon(t5);
    yy11Limitation.update_epsilon(t5);
    xx11Limitation.update_tolerance(t10);
    yy11Limitation.update_tolerance(t10);
    xx12Limitation.update_epsilon(t5);
    yy12Limitation.update_epsilon(t5);
    xx12Limitation.update_tolerance(t10);
    yy12Limitation.update_tolerance(t10);
    xx13Limitation.update_epsilon(t5);
    yy13Limitation.update_epsilon(t5);
    xx13Limitation.update_tolerance(t10);
    yy13Limitation.update_tolerance(t10);
    xx14Limitation.update_epsilon(t5);
    yy14Limitation.update_epsilon(t5);
    xx14Limitation.update_tolerance(t10);
    yy14Limitation.update_tolerance(t10);
    xx15Limitation.update_epsilon(t5);
    yy15Limitation.update_epsilon(t5);
    xx15Limitation.update_tolerance(t10);
    yy15Limitation.update_tolerance(t10);
    xx16Limitation.update_epsilon(t5);
    yy16Limitation.update_epsilon(t5);
    xx16Limitation.update_tolerance(t10);
    yy16Limitation.update_tolerance(t10);
    xx17Limitation.update_epsilon(t5);
    yy17Limitation.update_epsilon(t5);
    xx17Limitation.update_tolerance(t10);
    yy17Limitation.update_tolerance(t10);
    xx18Limitation.update_epsilon(t5);
    yy18Limitation.update_epsilon(t5);
    xx18Limitation.update_tolerance(t10);
    yy18Limitation.update_tolerance(t10);
    xx19Limitation.update_epsilon(t5);
    yy19Limitation.update_epsilon(t5);
    xx19Limitation.update_tolerance(t10);
    yy19Limitation.update_tolerance(t10);
    xx20Limitation.update_epsilon(t5);
    yy20Limitation.update_epsilon(t5);
    xx20Limitation.update_tolerance(t10);
    yy20Limitation.update_tolerance(t10);
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
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 * t1;
    real_type t4   = X__[iX_x19];
    real_type t5   = t4 * t4;
    real_type t7   = X__[iX_x20];
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_y1];
    real_type t10  = t9 * t9;
    real_type t12  = X__[iX_y2];
    real_type t13  = t12 * t12;
    real_type t15  = X__[iX_y3];
    real_type t16  = t15 * t15;
    real_type t18  = X__[iX_y5];
    real_type t19  = t18 * t18;
    real_type t21  = X__[iX_y6];
    real_type t22  = t21 * t21;
    real_type t24  = X__[iX_y7];
    real_type t25  = t24 * t24;
    real_type t27  = X__[iX_y8];
    real_type t28  = t27 * t27;
    real_type t30  = X__[iX_y9];
    real_type t31  = t30 * t30;
    real_type t33  = 20 * t2 + 2 * t5 + t8 + 20 * t10 + 19 * t13 + 18 * t16 + 16 * t19 + 15 * t22 + 14 * t25 + 13 * t28 + 12 * t31;
    real_type t34  = X__[iX_y10];
    real_type t35  = t34 * t34;
    real_type t37  = X__[iX_y11];
    real_type t38  = t37 * t37;
    real_type t40  = X__[iX_y12];
    real_type t41  = t40 * t40;
    real_type t43  = X__[iX_y13];
    real_type t44  = t43 * t43;
    real_type t46  = X__[iX_y14];
    real_type t47  = t46 * t46;
    real_type t49  = X__[iX_y15];
    real_type t50  = t49 * t49;
    real_type t52  = X__[iX_y16];
    real_type t53  = t52 * t52;
    real_type t55  = X__[iX_y17];
    real_type t56  = t55 * t55;
    real_type t58  = X__[iX_y18];
    real_type t59  = t58 * t58;
    real_type t61  = X__[iX_y19];
    real_type t62  = t61 * t61;
    real_type t64  = X__[iX_y20];
    real_type t65  = t64 * t64;
    real_type t66  = 11 * t35 + 10 * t38 + 9 * t41 + 8 * t44 + 7 * t47 + 6 * t50 + 5 * t53 + 4 * t56 + 3 * t59 + 2 * t62 + t65;
    real_type t68  = X__[iX_x8];
    real_type t69  = t68 * t68;
    real_type t71  = X__[iX_x9];
    real_type t72  = t71 * t71;
    real_type t74  = X__[iX_x10];
    real_type t75  = t74 * t74;
    real_type t77  = X__[iX_x11];
    real_type t78  = t77 * t77;
    real_type t80  = X__[iX_x13];
    real_type t81  = t80 * t80;
    real_type t83  = X__[iX_x14];
    real_type t84  = t83 * t83;
    real_type t86  = X__[iX_x15];
    real_type t87  = t86 * t86;
    real_type t89  = X__[iX_x16];
    real_type t90  = t89 * t89;
    real_type t92  = X__[iX_x17];
    real_type t93  = t92 * t92;
    real_type t95  = X__[iX_x18];
    real_type t96  = t95 * t95;
    real_type t98  = X__[iX_y4];
    real_type t99  = t98 * t98;
    real_type t101 = 13 * t69 + 12 * t72 + 11 * t75 + 10 * t78 + 8 * t81 + 7 * t84 + 6 * t87 + 5 * t90 + 4 * t93 + 3 * t96 + 17 * t99;
    real_type t102 = X__[iX_x12];
    real_type t103 = t102 * t102;
    real_type t105 = X__[iX_yy20];
    real_type t106 = yy20Limitation(t105);
    real_type t107 = X__[iX_x2];
    real_type t108 = t107 * t107;
    real_type t110 = X__[iX_x3];
    real_type t111 = t110 * t110;
    real_type t113 = X__[iX_x4];
    real_type t114 = t113 * t113;
    real_type t116 = X__[iX_x5];
    real_type t117 = t116 * t116;
    real_type t119 = X__[iX_x6];
    real_type t120 = t119 * t119;
    real_type t122 = X__[iX_x7];
    real_type t123 = t122 * t122;
    real_type t125 = X__[iX_yy14];
    real_type t126 = yy14Limitation(t125);
    real_type t127 = X__[iX_yy15];
    real_type t128 = yy15Limitation(t127);
    real_type t129 = X__[iX_yy16];
    real_type t130 = yy16Limitation(t129);
    real_type t131 = X__[iX_yy17];
    real_type t132 = yy17Limitation(t131);
    real_type t133 = 9 * t103 + t106 + 19 * t108 + 18 * t111 + 17 * t114 + 16 * t117 + 15 * t120 + 14 * t123 + t126 + t128 + t130 + t132;
    real_type t136 = X__[iX_yy18];
    real_type t137 = yy18Limitation(t136);
    real_type t138 = X__[iX_yy19];
    real_type t139 = yy19Limitation(t138);
    real_type t140 = X__[iX_yy7];
    real_type t141 = yy7Limitation(t140);
    real_type t142 = X__[iX_yy8];
    real_type t143 = yy8Limitation(t142);
    real_type t144 = X__[iX_yy9];
    real_type t145 = yy9Limitation(t144);
    real_type t146 = X__[iX_yy10];
    real_type t147 = yy10Limitation(t146);
    real_type t148 = X__[iX_yy11];
    real_type t149 = yy11Limitation(t148);
    real_type t150 = X__[iX_yy12];
    real_type t151 = yy12Limitation(t150);
    real_type t152 = X__[iX_yy13];
    real_type t153 = yy13Limitation(t152);
    real_type t154 = X__[iX_xx20];
    real_type t155 = xx20Limitation(t154);
    real_type t156 = X__[iX_yy1];
    real_type t157 = yy1Limitation(t156);
    real_type t158 = t137 + t139 + t141 + t143 + t145 + t147 + t149 + t151 + t153 + t155 + t157;
    real_type t159 = X__[iX_yy2];
    real_type t160 = yy2Limitation(t159);
    real_type t161 = X__[iX_yy3];
    real_type t162 = yy3Limitation(t161);
    real_type t163 = X__[iX_yy4];
    real_type t164 = yy4Limitation(t163);
    real_type t165 = X__[iX_yy5];
    real_type t166 = yy5Limitation(t165);
    real_type t167 = X__[iX_yy6];
    real_type t168 = yy6Limitation(t167);
    real_type t169 = X__[iX_xx13];
    real_type t170 = xx13Limitation(t169);
    real_type t171 = X__[iX_xx14];
    real_type t172 = xx14Limitation(t171);
    real_type t173 = X__[iX_xx15];
    real_type t174 = xx15Limitation(t173);
    real_type t175 = X__[iX_xx16];
    real_type t176 = xx16Limitation(t175);
    real_type t177 = X__[iX_xx17];
    real_type t178 = xx17Limitation(t177);
    real_type t179 = X__[iX_xx18];
    real_type t180 = xx18Limitation(t179);
    real_type t181 = t160 + t162 + t164 + t166 + t168 + t170 + t172 + t174 + t176 + t178 + t180;
    real_type t183 = X__[iX_xx19];
    real_type t184 = xx19Limitation(t183);
    real_type t185 = X__[iX_xx7];
    real_type t186 = xx7Limitation(t185);
    real_type t187 = X__[iX_xx8];
    real_type t188 = xx8Limitation(t187);
    real_type t189 = X__[iX_xx9];
    real_type t190 = xx9Limitation(t189);
    real_type t191 = X__[iX_xx10];
    real_type t192 = xx10Limitation(t191);
    real_type t193 = X__[iX_xx11];
    real_type t194 = xx11Limitation(t193);
    real_type t195 = X__[iX_xx12];
    real_type t196 = xx12Limitation(t195);
    real_type t197 = P__[iP_u20];
    real_type t198 = u20Limitation(t197);
    real_type t199 = X__[iX_xx1];
    real_type t200 = xx1Limitation(t199);
    real_type t201 = X__[iX_xx2];
    real_type t202 = xx2Limitation(t201);
    real_type t203 = X__[iX_xx3];
    real_type t204 = xx3Limitation(t203);
    real_type t205 = t184 + t186 + t188 + t190 + t192 + t194 + t196 + t198 + t200 + t202 + t204;
    real_type t206 = X__[iX_xx4];
    real_type t207 = xx4Limitation(t206);
    real_type t208 = X__[iX_xx5];
    real_type t209 = xx5Limitation(t208);
    real_type t210 = X__[iX_xx6];
    real_type t211 = xx6Limitation(t210);
    real_type t212 = P__[iP_u15];
    real_type t213 = u15Limitation(t212);
    real_type t214 = P__[iP_u16];
    real_type t215 = u16Limitation(t214);
    real_type t216 = P__[iP_u17];
    real_type t217 = u17Limitation(t216);
    real_type t218 = P__[iP_u18];
    real_type t219 = u18Limitation(t218);
    real_type t220 = P__[iP_u19];
    real_type t221 = u19Limitation(t220);
    real_type t222 = P__[iP_u8];
    real_type t223 = u8Limitation(t222);
    real_type t224 = P__[iP_u9];
    real_type t225 = u9Limitation(t224);
    real_type t226 = P__[iP_u10];
    real_type t227 = u10Limitation(t226);
    real_type t228 = P__[iP_u11];
    real_type t229 = u11Limitation(t228);
    real_type t230 = t207 + t209 + t211 + t213 + t215 + t217 + t219 + t221 + t223 + t225 + t227 + t229;
    real_type t234 = P__[iP_u12];
    real_type t235 = u12Limitation(t234);
    real_type t236 = P__[iP_u13];
    real_type t237 = u13Limitation(t236);
    real_type t238 = P__[iP_u14];
    real_type t239 = u14Limitation(t238);
    real_type t240 = P__[iP_u1];
    real_type t241 = u1Limitation(t240);
    real_type t242 = P__[iP_u2];
    real_type t243 = u2Limitation(t242);
    real_type t244 = P__[iP_u3];
    real_type t245 = u3Limitation(t244);
    real_type t246 = P__[iP_u4];
    real_type t247 = u4Limitation(t246);
    real_type t248 = P__[iP_u5];
    real_type t249 = u5Limitation(t248);
    real_type t250 = P__[iP_u6];
    real_type t251 = u6Limitation(t250);
    real_type t252 = P__[iP_u7];
    real_type t253 = u7Limitation(t252);
    real_type t255 = sin(t177);
    real_type t259 = t235 + t237 + t239 + t241 + t243 + t245 + t247 + t249 + t251 + t253 + (0.2e0 * t255 + t216) * L__[iL_lambda77__xo];
    real_type t261 = sin(t92);
    real_type t265 = sin(t179);
    real_type t270 = sin(t95);
    real_type t274 = sin(t183);
    real_type t279 = sin(t4);
    real_type t283 = sin(t154);
    real_type t288 = sin(t7);
    real_type t293 = Q__[iQ_zeta];
    real_type t294 = sin(t293);
    real_type t301 = sin(t293 + 1);
    real_type t308 = sin(t293 + 2);
    real_type t315 = sin(t293 + 3);
    real_type t319 = (t261 + t216) * L__[iL_lambda37__xo] + (0.2e0 * t265 + t218) * L__[iL_lambda78__xo] + (t270 + t218) * L__[iL_lambda38__xo] + (0.2e0 * t274 + t220) * L__[iL_lambda79__xo] + (t279 + t220) * L__[iL_lambda39__xo] + (0.2e0 * t283 + t197) * L__[iL_lambda80__xo] + (t288 + t197) * L__[iL_lambda40__xo] + (0.12e1 * t156 + 0.1e0 * t294) * L__[iL_lambda41__xo] + (0.12e1 * t159 + 0.1e0 * t301) * L__[iL_lambda42__xo] + (0.12e1 * t161 + 0.1e0 * t308) * L__[iL_lambda43__xo] + (0.12e1 * t163 + 0.1e0 * t315) * L__[iL_lambda44__xo];
    real_type t324 = sin(t293 + 4);
    real_type t348 = (0.12e1 * t165 + 0.1e0 * t324) * L__[iL_lambda45__xo] + t9 * L__[iL_lambda1__xo] + t12 * L__[iL_lambda2__xo] + t15 * L__[iL_lambda3__xo] + t98 * L__[iL_lambda4__xo] + t18 * L__[iL_lambda5__xo] + t21 * L__[iL_lambda6__xo] + t24 * L__[iL_lambda7__xo] + t27 * L__[iL_lambda8__xo] + t30 * L__[iL_lambda9__xo] + t34 * L__[iL_lambda10__xo];
    real_type t372 = sin(t293 + 16);
    real_type t379 = sin(t293 + 17);
    real_type t383 = t37 * L__[iL_lambda11__xo] + t40 * L__[iL_lambda12__xo] + t43 * L__[iL_lambda13__xo] + t46 * L__[iL_lambda14__xo] + t49 * L__[iL_lambda15__xo] + t52 * L__[iL_lambda16__xo] + t55 * L__[iL_lambda17__xo] + t58 * L__[iL_lambda18__xo] + t61 * L__[iL_lambda19__xo] + t64 * L__[iL_lambda20__xo] + (0.12e1 * t131 + 0.1e0 * t372) * L__[iL_lambda57__xo] + (0.12e1 * t136 + 0.1e0 * t379) * L__[iL_lambda58__xo];
    real_type t389 = sin(t293 + 18);
    real_type t396 = sin(t293 + 19);
    real_type t401 = sin(t1);
    real_type t405 = sin(t199);
    real_type t410 = sin(t107);
    real_type t414 = sin(t201);
    real_type t419 = sin(t110);
    real_type t423 = sin(t203);
    real_type t428 = sin(t113);
    real_type t432 = sin(t206);
    real_type t437 = sin(t116);
    real_type t440 = (0.12e1 * t138 + 0.1e0 * t389) * L__[iL_lambda59__xo] + (0.12e1 * t105 + 0.1e0 * t396) * L__[iL_lambda60__xo] + (t401 + t240) * L__[iL_lambda21__xo] + (0.2e0 * t405 + t240) * L__[iL_lambda61__xo] + (t410 + t242) * L__[iL_lambda22__xo] + (0.2e0 * t414 + t242) * L__[iL_lambda62__xo] + (t419 + t244) * L__[iL_lambda23__xo] + (0.2e0 * t423 + t244) * L__[iL_lambda63__xo] + (t428 + t246) * L__[iL_lambda24__xo] + (0.2e0 * t432 + t246) * L__[iL_lambda64__xo] + (t437 + t248) * L__[iL_lambda25__xo];
    real_type t442 = sin(t208);
    real_type t447 = sin(t119);
    real_type t451 = sin(t210);
    real_type t456 = sin(t122);
    real_type t460 = sin(t185);
    real_type t465 = sin(t68);
    real_type t469 = sin(t187);
    real_type t474 = sin(t71);
    real_type t478 = sin(t189);
    real_type t483 = sin(t74);
    real_type t487 = sin(t191);
    real_type t491 = (0.2e0 * t442 + t248) * L__[iL_lambda65__xo] + (t447 + t250) * L__[iL_lambda26__xo] + (0.2e0 * t451 + t250) * L__[iL_lambda66__xo] + (t456 + t252) * L__[iL_lambda27__xo] + (0.2e0 * t460 + t252) * L__[iL_lambda67__xo] + (t465 + t222) * L__[iL_lambda28__xo] + (0.2e0 * t469 + t222) * L__[iL_lambda68__xo] + (t474 + t224) * L__[iL_lambda29__xo] + (0.2e0 * t478 + t224) * L__[iL_lambda69__xo] + (t483 + t226) * L__[iL_lambda30__xo] + (0.2e0 * t487 + t226) * L__[iL_lambda70__xo];
    real_type t494 = sin(t77);
    real_type t498 = sin(t193);
    real_type t503 = sin(t102);
    real_type t507 = sin(t195);
    real_type t512 = sin(t80);
    real_type t516 = sin(t169);
    real_type t521 = sin(t83);
    real_type t525 = sin(t171);
    real_type t530 = sin(t173);
    real_type t535 = sin(t86);
    real_type t539 = sin(t175);
    real_type t543 = (t494 + t228) * L__[iL_lambda31__xo] + (0.2e0 * t498 + t228) * L__[iL_lambda71__xo] + (t503 + t234) * L__[iL_lambda32__xo] + (0.2e0 * t507 + t234) * L__[iL_lambda72__xo] + (t512 + t236) * L__[iL_lambda33__xo] + (0.2e0 * t516 + t236) * L__[iL_lambda73__xo] + (t521 + t238) * L__[iL_lambda34__xo] + (0.2e0 * t525 + t238) * L__[iL_lambda74__xo] + (0.2e0 * t530 + t212) * L__[iL_lambda75__xo] + (t535 + t212) * L__[iL_lambda35__xo] + (0.2e0 * t539 + t214) * L__[iL_lambda76__xo];
    real_type t545 = sin(t89);
    real_type t551 = sin(t293 + 5);
    real_type t558 = sin(t293 + 6);
    real_type t565 = sin(t293 + 7);
    real_type t572 = sin(t293 + 8);
    real_type t579 = sin(t293 + 9);
    real_type t586 = sin(t293 + 10);
    real_type t593 = sin(t293 + 11);
    real_type t600 = sin(t293 + 12);
    real_type t607 = sin(t293 + 13);
    real_type t614 = sin(t293 + 14);
    real_type t621 = sin(t293 + 15);
    real_type t625 = (t545 + t214) * L__[iL_lambda36__xo] + (0.12e1 * t167 + 0.1e0 * t551) * L__[iL_lambda46__xo] + (0.12e1 * t140 + 0.1e0 * t558) * L__[iL_lambda47__xo] + (0.12e1 * t142 + 0.1e0 * t565) * L__[iL_lambda48__xo] + (0.12e1 * t144 + 0.1e0 * t572) * L__[iL_lambda49__xo] + (0.12e1 * t146 + 0.1e0 * t579) * L__[iL_lambda50__xo] + (0.12e1 * t148 + 0.1e0 * t586) * L__[iL_lambda51__xo] + (0.12e1 * t150 + 0.1e0 * t593) * L__[iL_lambda52__xo] + (0.12e1 * t152 + 0.1e0 * t600) * L__[iL_lambda53__xo] + (0.12e1 * t125 + 0.1e0 * t607) * L__[iL_lambda54__xo] + (0.12e1 * t127 + 0.1e0 * t614) * L__[iL_lambda55__xo] + (0.12e1 * t129 + 0.1e0 * t621) * L__[iL_lambda56__xo];
    real_type result__ = t33 + t66 + t101 + t133 + t158 + t181 + t205 + t230 + t259 + t319 + t348 + t383 + t440 + t491 + t543 + t625;
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
  ICLOCS_ContinuousMP::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = yy14Limitation(X__[iX_yy14]);
    real_type t4   = yy15Limitation(X__[iX_yy15]);
    real_type t6   = yy16Limitation(X__[iX_yy16]);
    real_type t8   = yy17Limitation(X__[iX_yy17]);
    real_type t10  = yy18Limitation(X__[iX_yy18]);
    real_type t12  = yy19Limitation(X__[iX_yy19]);
    real_type t14  = yy20Limitation(X__[iX_yy20]);
    real_type t16  = yy7Limitation(X__[iX_yy7]);
    real_type t18  = yy8Limitation(X__[iX_yy8]);
    real_type t20  = yy9Limitation(X__[iX_yy9]);
    real_type t22  = yy10Limitation(X__[iX_yy10]);
    real_type t24  = yy11Limitation(X__[iX_yy11]);
    real_type t26  = yy12Limitation(X__[iX_yy12]);
    real_type t28  = yy13Limitation(X__[iX_yy13]);
    real_type t30  = xx19Limitation(X__[iX_xx19]);
    real_type t31  = t2 + t4 + t6 + t8 + t10 + t12 + t14 + t16 + t18 + t20 + t22 + t24 + t26 + t28 + t30;
    real_type t33  = xx20Limitation(X__[iX_xx20]);
    real_type t35  = yy1Limitation(X__[iX_yy1]);
    real_type t37  = yy2Limitation(X__[iX_yy2]);
    real_type t39  = yy3Limitation(X__[iX_yy3]);
    real_type t41  = yy4Limitation(X__[iX_yy4]);
    real_type t43  = yy5Limitation(X__[iX_yy5]);
    real_type t45  = yy6Limitation(X__[iX_yy6]);
    real_type t47  = xx12Limitation(X__[iX_xx12]);
    real_type t49  = xx13Limitation(X__[iX_xx13]);
    real_type t51  = xx14Limitation(X__[iX_xx14]);
    real_type t53  = xx15Limitation(X__[iX_xx15]);
    real_type t55  = xx16Limitation(X__[iX_xx16]);
    real_type t57  = xx17Limitation(X__[iX_xx17]);
    real_type t59  = xx18Limitation(X__[iX_xx18]);
    real_type t61  = xx5Limitation(X__[iX_xx5]);
    real_type t62  = t33 + t35 + t37 + t39 + t41 + t43 + t45 + t47 + t49 + t51 + t53 + t55 + t57 + t59 + t61;
    real_type t65  = xx6Limitation(X__[iX_xx6]);
    real_type t67  = xx7Limitation(X__[iX_xx7]);
    real_type t69  = xx8Limitation(X__[iX_xx8]);
    real_type t71  = xx9Limitation(X__[iX_xx9]);
    real_type t73  = xx10Limitation(X__[iX_xx10]);
    real_type t75  = xx11Limitation(X__[iX_xx11]);
    real_type t77  = u18Limitation(P__[iP_u18]);
    real_type t79  = u19Limitation(P__[iP_u19]);
    real_type t81  = u20Limitation(P__[iP_u20]);
    real_type t83  = xx1Limitation(X__[iX_xx1]);
    real_type t85  = xx2Limitation(X__[iX_xx2]);
    real_type t87  = xx3Limitation(X__[iX_xx3]);
    real_type t89  = xx4Limitation(X__[iX_xx4]);
    real_type t91  = u10Limitation(P__[iP_u10]);
    real_type t93  = u11Limitation(P__[iP_u11]);
    real_type t94  = t65 + t67 + t69 + t71 + t73 + t75 + t77 + t79 + t81 + t83 + t85 + t87 + t89 + t91 + t93;
    real_type t96  = u12Limitation(P__[iP_u12]);
    real_type t98  = u13Limitation(P__[iP_u13]);
    real_type t100 = u14Limitation(P__[iP_u14]);
    real_type t102 = u15Limitation(P__[iP_u15]);
    real_type t104 = u16Limitation(P__[iP_u16]);
    real_type t106 = u17Limitation(P__[iP_u17]);
    real_type t108 = u3Limitation(P__[iP_u3]);
    real_type t110 = u4Limitation(P__[iP_u4]);
    real_type t112 = u5Limitation(P__[iP_u5]);
    real_type t114 = u6Limitation(P__[iP_u6]);
    real_type t116 = u7Limitation(P__[iP_u7]);
    real_type t118 = u8Limitation(P__[iP_u8]);
    real_type t120 = u9Limitation(P__[iP_u9]);
    real_type t122 = u1Limitation(P__[iP_u1]);
    real_type t124 = u2Limitation(P__[iP_u2]);
    real_type t125 = t96 + t98 + t100 + t102 + t104 + t106 + t108 + t110 + t112 + t114 + t116 + t118 + t120 + t122 + t124;
    real_type result__ = t31 + t62 + t94 + t125;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ContinuousMP::control_penalties_eval(
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
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

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
    real_type t2   = X__[iX_x1] * X__[iX_x1];
    real_type t5   = X__[iX_y2] * X__[iX_y2];
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
    real_type t60  = 20 * t2 + 19 * t5 + 18 * t8 + 17 * t11 + 16 * t14 + 15 * t17 + 14 * t20 + 13 * t23 + 12 * t26 + 11 * t29 + 10 * t32 + 9 * t35 + 8 * t38 + 7 * t41 + 6 * t44 + 5 * t47 + 4 * t50 + 3 * t53 + 2 * t56 + t59;
    real_type t62  = X__[iX_x2] * X__[iX_x2];
    real_type t65  = X__[iX_x3] * X__[iX_x3];
    real_type t68  = X__[iX_x4] * X__[iX_x4];
    real_type t71  = X__[iX_x5] * X__[iX_x5];
    real_type t74  = X__[iX_x6] * X__[iX_x6];
    real_type t77  = X__[iX_x7] * X__[iX_x7];
    real_type t80  = X__[iX_x8] * X__[iX_x8];
    real_type t83  = X__[iX_x9] * X__[iX_x9];
    real_type t86  = X__[iX_x10] * X__[iX_x10];
    real_type t89  = X__[iX_x11] * X__[iX_x11];
    real_type t92  = X__[iX_x12] * X__[iX_x12];
    real_type t95  = X__[iX_x13] * X__[iX_x13];
    real_type t98  = X__[iX_x14] * X__[iX_x14];
    real_type t101 = X__[iX_x15] * X__[iX_x15];
    real_type t104 = X__[iX_x16] * X__[iX_x16];
    real_type t107 = X__[iX_x17] * X__[iX_x17];
    real_type t110 = X__[iX_x18] * X__[iX_x18];
    real_type t113 = X__[iX_x19] * X__[iX_x19];
    real_type t116 = X__[iX_x20] * X__[iX_x20];
    real_type t118 = X__[iX_y1] * X__[iX_y1];
    real_type t120 = 19 * t62 + 18 * t65 + 17 * t68 + 16 * t71 + 15 * t74 + 14 * t77 + 13 * t80 + 12 * t83 + 11 * t86 + 10 * t89 + 9 * t92 + 8 * t95 + 7 * t98 + 6 * t101 + 5 * t104 + 4 * t107 + 3 * t110 + 2 * t113 + t116 + 20 * t118;
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

  integer
  ICLOCS_ContinuousMP::DmayerDxxp_numEqns() const
  { return 180; }

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

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  ICLOCS_ContinuousMP::DlagrangeDxup_numEqns() const
  { return 100; }

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

  integer
  ICLOCS_ContinuousMP::DJDx_numEqns() const
  { return 80; }

  void
  ICLOCS_ContinuousMP::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
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
    result__[ 40  ] = ALIAS_xx1Limitation_D(X__[iX_xx1]);
    result__[ 41  ] = ALIAS_xx2Limitation_D(X__[iX_xx2]);
    result__[ 42  ] = ALIAS_xx3Limitation_D(X__[iX_xx3]);
    result__[ 43  ] = ALIAS_xx4Limitation_D(X__[iX_xx4]);
    result__[ 44  ] = ALIAS_xx5Limitation_D(X__[iX_xx5]);
    result__[ 45  ] = ALIAS_xx6Limitation_D(X__[iX_xx6]);
    result__[ 46  ] = ALIAS_xx7Limitation_D(X__[iX_xx7]);
    result__[ 47  ] = ALIAS_xx8Limitation_D(X__[iX_xx8]);
    result__[ 48  ] = ALIAS_xx9Limitation_D(X__[iX_xx9]);
    result__[ 49  ] = ALIAS_xx10Limitation_D(X__[iX_xx10]);
    result__[ 50  ] = ALIAS_xx11Limitation_D(X__[iX_xx11]);
    result__[ 51  ] = ALIAS_xx12Limitation_D(X__[iX_xx12]);
    result__[ 52  ] = ALIAS_xx13Limitation_D(X__[iX_xx13]);
    result__[ 53  ] = ALIAS_xx14Limitation_D(X__[iX_xx14]);
    result__[ 54  ] = ALIAS_xx15Limitation_D(X__[iX_xx15]);
    result__[ 55  ] = ALIAS_xx16Limitation_D(X__[iX_xx16]);
    result__[ 56  ] = ALIAS_xx17Limitation_D(X__[iX_xx17]);
    result__[ 57  ] = ALIAS_xx18Limitation_D(X__[iX_xx18]);
    result__[ 58  ] = ALIAS_xx19Limitation_D(X__[iX_xx19]);
    result__[ 59  ] = ALIAS_xx20Limitation_D(X__[iX_xx20]);
    result__[ 60  ] = ALIAS_yy1Limitation_D(X__[iX_yy1]);
    result__[ 61  ] = ALIAS_yy2Limitation_D(X__[iX_yy2]);
    result__[ 62  ] = ALIAS_yy3Limitation_D(X__[iX_yy3]);
    result__[ 63  ] = ALIAS_yy4Limitation_D(X__[iX_yy4]);
    result__[ 64  ] = ALIAS_yy5Limitation_D(X__[iX_yy5]);
    result__[ 65  ] = ALIAS_yy6Limitation_D(X__[iX_yy6]);
    result__[ 66  ] = ALIAS_yy7Limitation_D(X__[iX_yy7]);
    result__[ 67  ] = ALIAS_yy8Limitation_D(X__[iX_yy8]);
    result__[ 68  ] = ALIAS_yy9Limitation_D(X__[iX_yy9]);
    result__[ 69  ] = ALIAS_yy10Limitation_D(X__[iX_yy10]);
    result__[ 70  ] = ALIAS_yy11Limitation_D(X__[iX_yy11]);
    result__[ 71  ] = ALIAS_yy12Limitation_D(X__[iX_yy12]);
    result__[ 72  ] = ALIAS_yy13Limitation_D(X__[iX_yy13]);
    result__[ 73  ] = ALIAS_yy14Limitation_D(X__[iX_yy14]);
    result__[ 74  ] = ALIAS_yy15Limitation_D(X__[iX_yy15]);
    result__[ 75  ] = ALIAS_yy16Limitation_D(X__[iX_yy16]);
    result__[ 76  ] = ALIAS_yy17Limitation_D(X__[iX_yy17]);
    result__[ 77  ] = ALIAS_yy18Limitation_D(X__[iX_yy18]);
    result__[ 78  ] = ALIAS_yy19Limitation_D(X__[iX_yy19]);
    result__[ 79  ] = ALIAS_yy20Limitation_D(X__[iX_yy20]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DJDp_numEqns() const
  { return 20; }

  void
  ICLOCS_ContinuousMP::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Limitation_D(P__[iP_u1]);
    result__[ 1   ] = ALIAS_u2Limitation_D(P__[iP_u2]);
    result__[ 2   ] = ALIAS_u3Limitation_D(P__[iP_u3]);
    result__[ 3   ] = ALIAS_u4Limitation_D(P__[iP_u4]);
    result__[ 4   ] = ALIAS_u5Limitation_D(P__[iP_u5]);
    result__[ 5   ] = ALIAS_u6Limitation_D(P__[iP_u6]);
    result__[ 6   ] = ALIAS_u7Limitation_D(P__[iP_u7]);
    result__[ 7   ] = ALIAS_u8Limitation_D(P__[iP_u8]);
    result__[ 8   ] = ALIAS_u9Limitation_D(P__[iP_u9]);
    result__[ 9   ] = ALIAS_u10Limitation_D(P__[iP_u10]);
    result__[ 10  ] = ALIAS_u11Limitation_D(P__[iP_u11]);
    result__[ 11  ] = ALIAS_u12Limitation_D(P__[iP_u12]);
    result__[ 12  ] = ALIAS_u13Limitation_D(P__[iP_u13]);
    result__[ 13  ] = ALIAS_u14Limitation_D(P__[iP_u14]);
    result__[ 14  ] = ALIAS_u15Limitation_D(P__[iP_u15]);
    result__[ 15  ] = ALIAS_u16Limitation_D(P__[iP_u16]);
    result__[ 16  ] = ALIAS_u17Limitation_D(P__[iP_u17]);
    result__[ 17  ] = ALIAS_u18Limitation_D(P__[iP_u18]);
    result__[ 18  ] = ALIAS_u19Limitation_D(P__[iP_u19]);
    result__[ 19  ] = ALIAS_u20Limitation_D(P__[iP_u20]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDp_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DJDu_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
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

  integer
  ICLOCS_ContinuousMP::segmentLink_numEqns() const
  { return 0; }

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

  integer
  ICLOCS_ContinuousMP::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DsegmentLinkDxp_nnz() const
  { return 0; }

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

  integer
  ICLOCS_ContinuousMP::jump_numEqns() const
  { return 160; }

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

  integer
  ICLOCS_ContinuousMP::DjumpDxlxlp_numRows() const
  { return 160; }

  integer
  ICLOCS_ContinuousMP::DjumpDxlxlp_numCols() const
  { return 340; }

  integer
  ICLOCS_ContinuousMP::DjumpDxlxlp_nnz() const
  { return 320; }

  void
  ICLOCS_ContinuousMP::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
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

  integer
  ICLOCS_ContinuousMP::post_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::integrated_post_numEqns() const
  { return 0; }

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
