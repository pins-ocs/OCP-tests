/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_ODE.cc                             |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  ICLOCS_ContinuousMP::rhs_ode_numEqns() const
  { return 80; }

  void
  ICLOCS_ContinuousMP::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_y1];
    result__[ 1   ] = X__[iX_y2];
    result__[ 2   ] = X__[iX_y3];
    result__[ 3   ] = X__[iX_y4];
    result__[ 4   ] = X__[iX_y5];
    result__[ 5   ] = X__[iX_y6];
    result__[ 6   ] = X__[iX_y7];
    result__[ 7   ] = X__[iX_y8];
    result__[ 8   ] = X__[iX_y9];
    result__[ 9   ] = X__[iX_y10];
    result__[ 10  ] = X__[iX_y11];
    result__[ 11  ] = X__[iX_y12];
    result__[ 12  ] = X__[iX_y13];
    result__[ 13  ] = X__[iX_y14];
    result__[ 14  ] = X__[iX_y15];
    result__[ 15  ] = X__[iX_y16];
    result__[ 16  ] = X__[iX_y17];
    result__[ 17  ] = X__[iX_y18];
    result__[ 18  ] = X__[iX_y19];
    result__[ 19  ] = X__[iX_y20];
    real_type t2   = sin(X__[iX_x1]);
    real_type t3   = P__[iP_u1];
    result__[ 20  ] = t2 + t3;
    real_type t5   = sin(X__[iX_x2]);
    real_type t6   = P__[iP_u2];
    result__[ 21  ] = t5 + t6;
    real_type t8   = sin(X__[iX_x3]);
    real_type t9   = P__[iP_u3];
    result__[ 22  ] = t8 + t9;
    real_type t11  = sin(X__[iX_x4]);
    real_type t12  = P__[iP_u4];
    result__[ 23  ] = t11 + t12;
    real_type t14  = sin(X__[iX_x5]);
    real_type t15  = P__[iP_u5];
    result__[ 24  ] = t14 + t15;
    real_type t17  = sin(X__[iX_x6]);
    real_type t18  = P__[iP_u6];
    result__[ 25  ] = t17 + t18;
    real_type t20  = sin(X__[iX_x7]);
    real_type t21  = P__[iP_u7];
    result__[ 26  ] = t20 + t21;
    real_type t23  = sin(X__[iX_x8]);
    real_type t24  = P__[iP_u8];
    result__[ 27  ] = t23 + t24;
    real_type t26  = sin(X__[iX_x9]);
    real_type t27  = P__[iP_u9];
    result__[ 28  ] = t26 + t27;
    real_type t29  = sin(X__[iX_x10]);
    real_type t30  = P__[iP_u10];
    result__[ 29  ] = t29 + t30;
    real_type t32  = sin(X__[iX_x11]);
    real_type t33  = P__[iP_u11];
    result__[ 30  ] = t32 + t33;
    real_type t35  = sin(X__[iX_x12]);
    real_type t36  = P__[iP_u12];
    result__[ 31  ] = t35 + t36;
    real_type t38  = sin(X__[iX_x13]);
    real_type t39  = P__[iP_u13];
    result__[ 32  ] = t38 + t39;
    real_type t41  = sin(X__[iX_x14]);
    real_type t42  = P__[iP_u14];
    result__[ 33  ] = t41 + t42;
    real_type t44  = sin(X__[iX_x15]);
    real_type t45  = P__[iP_u15];
    result__[ 34  ] = t44 + t45;
    real_type t47  = sin(X__[iX_x16]);
    real_type t48  = P__[iP_u16];
    result__[ 35  ] = t47 + t48;
    real_type t50  = sin(X__[iX_x17]);
    real_type t51  = P__[iP_u17];
    result__[ 36  ] = t50 + t51;
    real_type t53  = sin(X__[iX_x18]);
    real_type t54  = P__[iP_u18];
    result__[ 37  ] = t53 + t54;
    real_type t56  = sin(X__[iX_x19]);
    real_type t57  = P__[iP_u19];
    result__[ 38  ] = t56 + t57;
    real_type t59  = sin(X__[iX_x20]);
    real_type t60  = P__[iP_u20];
    result__[ 39  ] = t59 + t60;
    real_type t63  = Q__[iQ_zeta];
    real_type t64  = sin(t63);
    result__[ 40  ] = 0.12e1 * X__[iX_yy1] + 0.1e0 * t64;
    real_type t69  = sin(t63 + 1);
    result__[ 41  ] = 0.12e1 * X__[iX_yy2] + 0.1e0 * t69;
    real_type t74  = sin(t63 + 2);
    result__[ 42  ] = 0.12e1 * X__[iX_yy3] + 0.1e0 * t74;
    real_type t79  = sin(t63 + 3);
    result__[ 43  ] = 0.12e1 * X__[iX_yy4] + 0.1e0 * t79;
    real_type t84  = sin(t63 + 4);
    result__[ 44  ] = 0.12e1 * X__[iX_yy5] + 0.1e0 * t84;
    real_type t89  = sin(t63 + 5);
    result__[ 45  ] = 0.12e1 * X__[iX_yy6] + 0.1e0 * t89;
    real_type t94  = sin(t63 + 6);
    result__[ 46  ] = 0.12e1 * X__[iX_yy7] + 0.1e0 * t94;
    real_type t99  = sin(t63 + 7);
    result__[ 47  ] = 0.12e1 * X__[iX_yy8] + 0.1e0 * t99;
    real_type t104 = sin(t63 + 8);
    result__[ 48  ] = 0.12e1 * X__[iX_yy9] + 0.1e0 * t104;
    real_type t109 = sin(t63 + 9);
    result__[ 49  ] = 0.12e1 * X__[iX_yy10] + 0.1e0 * t109;
    real_type t114 = sin(t63 + 10);
    result__[ 50  ] = 0.12e1 * X__[iX_yy11] + 0.1e0 * t114;
    real_type t119 = sin(t63 + 11);
    result__[ 51  ] = 0.12e1 * X__[iX_yy12] + 0.1e0 * t119;
    real_type t124 = sin(t63 + 12);
    result__[ 52  ] = 0.12e1 * X__[iX_yy13] + 0.1e0 * t124;
    real_type t129 = sin(t63 + 13);
    result__[ 53  ] = 0.12e1 * X__[iX_yy14] + 0.1e0 * t129;
    real_type t134 = sin(t63 + 14);
    result__[ 54  ] = 0.12e1 * X__[iX_yy15] + 0.1e0 * t134;
    real_type t139 = sin(t63 + 15);
    result__[ 55  ] = 0.12e1 * X__[iX_yy16] + 0.1e0 * t139;
    real_type t144 = sin(t63 + 16);
    result__[ 56  ] = 0.12e1 * X__[iX_yy17] + 0.1e0 * t144;
    real_type t149 = sin(t63 + 17);
    result__[ 57  ] = 0.12e1 * X__[iX_yy18] + 0.1e0 * t149;
    real_type t154 = sin(t63 + 18);
    result__[ 58  ] = 0.12e1 * X__[iX_yy19] + 0.1e0 * t154;
    real_type t159 = sin(t63 + 19);
    result__[ 59  ] = 0.12e1 * X__[iX_yy20] + 0.1e0 * t159;
    real_type t162 = sin(X__[iX_xx1]);
    result__[ 60  ] = 0.2e0 * t162 + t3;
    real_type t165 = sin(X__[iX_xx2]);
    result__[ 61  ] = 0.2e0 * t165 + t6;
    real_type t168 = sin(X__[iX_xx3]);
    result__[ 62  ] = 0.2e0 * t168 + t9;
    real_type t171 = sin(X__[iX_xx4]);
    result__[ 63  ] = 0.2e0 * t171 + t12;
    real_type t174 = sin(X__[iX_xx5]);
    result__[ 64  ] = 0.2e0 * t174 + t15;
    real_type t177 = sin(X__[iX_xx6]);
    result__[ 65  ] = 0.2e0 * t177 + t18;
    real_type t180 = sin(X__[iX_xx7]);
    result__[ 66  ] = 0.2e0 * t180 + t21;
    real_type t183 = sin(X__[iX_xx8]);
    result__[ 67  ] = 0.2e0 * t183 + t24;
    real_type t186 = sin(X__[iX_xx9]);
    result__[ 68  ] = 0.2e0 * t186 + t27;
    real_type t189 = sin(X__[iX_xx10]);
    result__[ 69  ] = 0.2e0 * t189 + t30;
    real_type t192 = sin(X__[iX_xx11]);
    result__[ 70  ] = 0.2e0 * t192 + t33;
    real_type t195 = sin(X__[iX_xx12]);
    result__[ 71  ] = 0.2e0 * t195 + t36;
    real_type t198 = sin(X__[iX_xx13]);
    result__[ 72  ] = 0.2e0 * t198 + t39;
    real_type t201 = sin(X__[iX_xx14]);
    result__[ 73  ] = 0.2e0 * t201 + t42;
    real_type t204 = sin(X__[iX_xx15]);
    result__[ 74  ] = 0.2e0 * t204 + t45;
    real_type t207 = sin(X__[iX_xx16]);
    result__[ 75  ] = 0.2e0 * t207 + t48;
    real_type t210 = sin(X__[iX_xx17]);
    result__[ 76  ] = 0.2e0 * t210 + t51;
    real_type t213 = sin(X__[iX_xx18]);
    result__[ 77  ] = 0.2e0 * t213 + t54;
    real_type t216 = sin(X__[iX_xx19]);
    result__[ 78  ] = 0.2e0 * t216 + t57;
    real_type t219 = sin(X__[iX_xx20]);
    result__[ 79  ] = 0.2e0 * t219 + t60;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::Drhs_odeDx_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDx_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDx_nnz() const
  { return 80; }

  void
  ICLOCS_ContinuousMP::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 20  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 21  ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 22  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 23  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 24  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 25  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 26  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 27  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 28  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 29  ;
    iIndex[10] = 10  ; jIndex[10] = 30  ;
    iIndex[11] = 11  ; jIndex[11] = 31  ;
    iIndex[12] = 12  ; jIndex[12] = 32  ;
    iIndex[13] = 13  ; jIndex[13] = 33  ;
    iIndex[14] = 14  ; jIndex[14] = 34  ;
    iIndex[15] = 15  ; jIndex[15] = 35  ;
    iIndex[16] = 16  ; jIndex[16] = 36  ;
    iIndex[17] = 17  ; jIndex[17] = 37  ;
    iIndex[18] = 18  ; jIndex[18] = 38  ;
    iIndex[19] = 19  ; jIndex[19] = 39  ;
    iIndex[20] = 20  ; jIndex[20] = 0   ;
    iIndex[21] = 21  ; jIndex[21] = 1   ;
    iIndex[22] = 22  ; jIndex[22] = 2   ;
    iIndex[23] = 23  ; jIndex[23] = 3   ;
    iIndex[24] = 24  ; jIndex[24] = 4   ;
    iIndex[25] = 25  ; jIndex[25] = 5   ;
    iIndex[26] = 26  ; jIndex[26] = 6   ;
    iIndex[27] = 27  ; jIndex[27] = 7   ;
    iIndex[28] = 28  ; jIndex[28] = 8   ;
    iIndex[29] = 29  ; jIndex[29] = 9   ;
    iIndex[30] = 30  ; jIndex[30] = 10  ;
    iIndex[31] = 31  ; jIndex[31] = 11  ;
    iIndex[32] = 32  ; jIndex[32] = 12  ;
    iIndex[33] = 33  ; jIndex[33] = 13  ;
    iIndex[34] = 34  ; jIndex[34] = 14  ;
    iIndex[35] = 35  ; jIndex[35] = 15  ;
    iIndex[36] = 36  ; jIndex[36] = 16  ;
    iIndex[37] = 37  ; jIndex[37] = 17  ;
    iIndex[38] = 38  ; jIndex[38] = 18  ;
    iIndex[39] = 39  ; jIndex[39] = 19  ;
    iIndex[40] = 40  ; jIndex[40] = 60  ;
    iIndex[41] = 41  ; jIndex[41] = 61  ;
    iIndex[42] = 42  ; jIndex[42] = 62  ;
    iIndex[43] = 43  ; jIndex[43] = 63  ;
    iIndex[44] = 44  ; jIndex[44] = 64  ;
    iIndex[45] = 45  ; jIndex[45] = 65  ;
    iIndex[46] = 46  ; jIndex[46] = 66  ;
    iIndex[47] = 47  ; jIndex[47] = 67  ;
    iIndex[48] = 48  ; jIndex[48] = 68  ;
    iIndex[49] = 49  ; jIndex[49] = 69  ;
    iIndex[50] = 50  ; jIndex[50] = 70  ;
    iIndex[51] = 51  ; jIndex[51] = 71  ;
    iIndex[52] = 52  ; jIndex[52] = 72  ;
    iIndex[53] = 53  ; jIndex[53] = 73  ;
    iIndex[54] = 54  ; jIndex[54] = 74  ;
    iIndex[55] = 55  ; jIndex[55] = 75  ;
    iIndex[56] = 56  ; jIndex[56] = 76  ;
    iIndex[57] = 57  ; jIndex[57] = 77  ;
    iIndex[58] = 58  ; jIndex[58] = 78  ;
    iIndex[59] = 59  ; jIndex[59] = 79  ;
    iIndex[60] = 60  ; jIndex[60] = 40  ;
    iIndex[61] = 61  ; jIndex[61] = 41  ;
    iIndex[62] = 62  ; jIndex[62] = 42  ;
    iIndex[63] = 63  ; jIndex[63] = 43  ;
    iIndex[64] = 64  ; jIndex[64] = 44  ;
    iIndex[65] = 65  ; jIndex[65] = 45  ;
    iIndex[66] = 66  ; jIndex[66] = 46  ;
    iIndex[67] = 67  ; jIndex[67] = 47  ;
    iIndex[68] = 68  ; jIndex[68] = 48  ;
    iIndex[69] = 69  ; jIndex[69] = 49  ;
    iIndex[70] = 70  ; jIndex[70] = 50  ;
    iIndex[71] = 71  ; jIndex[71] = 51  ;
    iIndex[72] = 72  ; jIndex[72] = 52  ;
    iIndex[73] = 73  ; jIndex[73] = 53  ;
    iIndex[74] = 74  ; jIndex[74] = 54  ;
    iIndex[75] = 75  ; jIndex[75] = 55  ;
    iIndex[76] = 76  ; jIndex[76] = 56  ;
    iIndex[77] = 77  ; jIndex[77] = 57  ;
    iIndex[78] = 78  ; jIndex[78] = 58  ;
    iIndex[79] = 79  ; jIndex[79] = 59  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
    result__[ 20  ] = cos(X__[iX_x1]);
    result__[ 21  ] = cos(X__[iX_x2]);
    result__[ 22  ] = cos(X__[iX_x3]);
    result__[ 23  ] = cos(X__[iX_x4]);
    result__[ 24  ] = cos(X__[iX_x5]);
    result__[ 25  ] = cos(X__[iX_x6]);
    result__[ 26  ] = cos(X__[iX_x7]);
    result__[ 27  ] = cos(X__[iX_x8]);
    result__[ 28  ] = cos(X__[iX_x9]);
    result__[ 29  ] = cos(X__[iX_x10]);
    result__[ 30  ] = cos(X__[iX_x11]);
    result__[ 31  ] = cos(X__[iX_x12]);
    result__[ 32  ] = cos(X__[iX_x13]);
    result__[ 33  ] = cos(X__[iX_x14]);
    result__[ 34  ] = cos(X__[iX_x15]);
    result__[ 35  ] = cos(X__[iX_x16]);
    result__[ 36  ] = cos(X__[iX_x17]);
    result__[ 37  ] = cos(X__[iX_x18]);
    result__[ 38  ] = cos(X__[iX_x19]);
    result__[ 39  ] = cos(X__[iX_x20]);
    result__[ 40  ] = 0.12e1;
    result__[ 41  ] = 0.12e1;
    result__[ 42  ] = 0.12e1;
    result__[ 43  ] = 0.12e1;
    result__[ 44  ] = 0.12e1;
    result__[ 45  ] = 0.12e1;
    result__[ 46  ] = 0.12e1;
    result__[ 47  ] = 0.12e1;
    result__[ 48  ] = 0.12e1;
    result__[ 49  ] = 0.12e1;
    result__[ 50  ] = 0.12e1;
    result__[ 51  ] = 0.12e1;
    result__[ 52  ] = 0.12e1;
    result__[ 53  ] = 0.12e1;
    result__[ 54  ] = 0.12e1;
    result__[ 55  ] = 0.12e1;
    result__[ 56  ] = 0.12e1;
    result__[ 57  ] = 0.12e1;
    result__[ 58  ] = 0.12e1;
    result__[ 59  ] = 0.12e1;
    real_type t22  = cos(X__[iX_xx1]);
    result__[ 60  ] = 0.2e0 * t22;
    real_type t24  = cos(X__[iX_xx2]);
    result__[ 61  ] = 0.2e0 * t24;
    real_type t26  = cos(X__[iX_xx3]);
    result__[ 62  ] = 0.2e0 * t26;
    real_type t28  = cos(X__[iX_xx4]);
    result__[ 63  ] = 0.2e0 * t28;
    real_type t30  = cos(X__[iX_xx5]);
    result__[ 64  ] = 0.2e0 * t30;
    real_type t32  = cos(X__[iX_xx6]);
    result__[ 65  ] = 0.2e0 * t32;
    real_type t34  = cos(X__[iX_xx7]);
    result__[ 66  ] = 0.2e0 * t34;
    real_type t36  = cos(X__[iX_xx8]);
    result__[ 67  ] = 0.2e0 * t36;
    real_type t38  = cos(X__[iX_xx9]);
    result__[ 68  ] = 0.2e0 * t38;
    real_type t40  = cos(X__[iX_xx10]);
    result__[ 69  ] = 0.2e0 * t40;
    real_type t42  = cos(X__[iX_xx11]);
    result__[ 70  ] = 0.2e0 * t42;
    real_type t44  = cos(X__[iX_xx12]);
    result__[ 71  ] = 0.2e0 * t44;
    real_type t46  = cos(X__[iX_xx13]);
    result__[ 72  ] = 0.2e0 * t46;
    real_type t48  = cos(X__[iX_xx14]);
    result__[ 73  ] = 0.2e0 * t48;
    real_type t50  = cos(X__[iX_xx15]);
    result__[ 74  ] = 0.2e0 * t50;
    real_type t52  = cos(X__[iX_xx16]);
    result__[ 75  ] = 0.2e0 * t52;
    real_type t54  = cos(X__[iX_xx17]);
    result__[ 76  ] = 0.2e0 * t54;
    real_type t56  = cos(X__[iX_xx18]);
    result__[ 77  ] = 0.2e0 * t56;
    real_type t58  = cos(X__[iX_xx19]);
    result__[ 78  ] = 0.2e0 * t58;
    real_type t60  = cos(X__[iX_xx20]);
    result__[ 79  ] = 0.2e0 * t60;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 80, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::Drhs_odeDp_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDp_numCols() const
  { return 20; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDp_nnz() const
  { return 40; }

  void
  ICLOCS_ContinuousMP::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 20  ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 21  ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 22  ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 23  ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 24  ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 25  ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 26  ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 27  ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 28  ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 29  ; jIndex[9 ] = 9   ;
    iIndex[10] = 30  ; jIndex[10] = 10  ;
    iIndex[11] = 31  ; jIndex[11] = 11  ;
    iIndex[12] = 32  ; jIndex[12] = 12  ;
    iIndex[13] = 33  ; jIndex[13] = 13  ;
    iIndex[14] = 34  ; jIndex[14] = 14  ;
    iIndex[15] = 35  ; jIndex[15] = 15  ;
    iIndex[16] = 36  ; jIndex[16] = 16  ;
    iIndex[17] = 37  ; jIndex[17] = 17  ;
    iIndex[18] = 38  ; jIndex[18] = 18  ;
    iIndex[19] = 39  ; jIndex[19] = 19  ;
    iIndex[20] = 60  ; jIndex[20] = 0   ;
    iIndex[21] = 61  ; jIndex[21] = 1   ;
    iIndex[22] = 62  ; jIndex[22] = 2   ;
    iIndex[23] = 63  ; jIndex[23] = 3   ;
    iIndex[24] = 64  ; jIndex[24] = 4   ;
    iIndex[25] = 65  ; jIndex[25] = 5   ;
    iIndex[26] = 66  ; jIndex[26] = 6   ;
    iIndex[27] = 67  ; jIndex[27] = 7   ;
    iIndex[28] = 68  ; jIndex[28] = 8   ;
    iIndex[29] = 69  ; jIndex[29] = 9   ;
    iIndex[30] = 70  ; jIndex[30] = 10  ;
    iIndex[31] = 71  ; jIndex[31] = 11  ;
    iIndex[32] = 72  ; jIndex[32] = 12  ;
    iIndex[33] = 73  ; jIndex[33] = 13  ;
    iIndex[34] = 74  ; jIndex[34] = 14  ;
    iIndex[35] = 75  ; jIndex[35] = 15  ;
    iIndex[36] = 76  ; jIndex[36] = 16  ;
    iIndex[37] = 77  ; jIndex[37] = 17  ;
    iIndex[38] = 78  ; jIndex[38] = 18  ;
    iIndex[39] = 79  ; jIndex[39] = 19  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::Drhs_odeDu_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDu_numCols() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::Drhs_odeDu_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  ICLOCS_ContinuousMP::A_numRows() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::A_numCols() const
  { return 80; }

  integer
  ICLOCS_ContinuousMP::A_nnz() const
  { return 80; }

  void
  ICLOCS_ContinuousMP::A_pattern(
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 80, i_segment );
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_ODE.cc
