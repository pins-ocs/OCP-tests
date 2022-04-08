/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_Guess.cc                              |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


using namespace std;

namespace gtocX_2burn_parsDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer gtocX_2burn_pars::fd_ode_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::fd_ode_eval(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t5   = P__[iP_p];
    real_type t6   = sqrt(t5);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t11  = 1.0 / t9 * t6 * t4;
    real_type t13  = XM__[0];
    real_type t14  = XM__[1];
    real_type t15  = XM__[2];
    real_type t16  = ray(t5, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * ModelPars[iM_w_nonlin];
    real_type t19  = sin(t15);
    result__[ 0   ] = -t11 * t18 * t19 + V__[0];
    real_type t23  = cos(t15);
    result__[ 1   ] = t11 * t18 * t23 + V__[1];
    real_type t30  = pow(t13 * t23 + t14 * t19 + 1, 2);
    result__[ 2   ] = V__[2] - t9 / t6 / t5 * t30 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::Dfd_odeDxxup_numRows() const { return 3; }
  integer gtocX_2burn_pars::Dfd_odeDxxup_numCols() const { return 9; }
  integer gtocX_2burn_pars::Dfd_odeDxxup_nnz()     const { return 21; }

  void
  gtocX_2burn_pars::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
  }


  void
  gtocX_2burn_pars::Dfd_odeDxxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t4   = P__[iP_p];
    real_type t5   = sqrt(t4);
    real_type t7   = ModelPars[iM_muS];
    real_type t8   = sqrt(t7);
    real_type t9   = 1.0 / t8;
    real_type t10  = t9 * t5 * t3;
    real_type t11  = ModelPars[iM_w_nonlin];
    real_type t12  = XM__[0];
    real_type t13  = XM__[1];
    real_type t14  = XM__[2];
    real_type t15  = ray(t4, t12, t13, t14);
    real_type t16  = acceleration_r_D_1(t15, t7);
    real_type t17  = t16 * t11;
    real_type t18  = ray_D_2(t4, t12, t13, t14);
    real_type t19  = sin(t14);
    real_type t23  = 0.5e0 * t19 * t18 * t17 * t10;
    result__[ 0   ] = -t23 - __INV_DZETA;
    real_type t24  = ray_D_3(t4, t12, t13, t14);
    result__[ 1   ] = -0.5e0 * t19 * t24 * t17 * t10;
    real_type t29  = ray_D_4(t4, t12, t13, t14);
    real_type t34  = acceleration_r(t15, t7);
    real_type t35  = t34 * t11;
    real_type t36  = cos(t14);
    real_type t37  = t36 * t35;
    result__[ 2   ] = -0.5e0 * t19 * t29 * t17 * t10 - 0.5e0 * t37 * t10;
    result__[ 3   ] = -t23 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t42  = t9 / t5 * t3;
    real_type t43  = t19 * t35;
    real_type t46  = ray_D_1(t4, t12, t13, t14);
    result__[ 6   ] = -t43 * t42 / 2 - t19 * t46 * t17 * t10;
    result__[ 7   ] = 0.5e0 * t36 * t18 * t17 * t10;
    real_type t56  = 0.5e0 * t36 * t24 * t17 * t10;
    result__[ 8   ] = t56 - __INV_DZETA;
    result__[ 9   ] = 0.5e0 * t36 * t29 * t17 * t10 - 0.5e0 * t43 * t10;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = t56 + __INV_DZETA;
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t37 * t42 / 2 + t36 * t46 * t17 * t10;
    real_type t70  = t36 * t12 + t19 * t13 + 1;
    real_type t71  = t70 * t3;
    real_type t74  = t8 / t5 / t4;
    result__[ 14  ] = -0.10e1 * t36 * t74 * t71;
    result__[ 15  ] = -0.10e1 * t19 * t74 * t71;
    real_type t86  = 0.10e1 * (-t19 * t12 + t36 * t13) * t74 * t71;
    result__[ 16  ] = -t86 - __INV_DZETA;
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = -t86 + __INV_DZETA;
    real_type t87  = t70 * t70;
    real_type t89  = t4 * t4;
    result__[ 20  ] = 3.0 / 2.0 * t8 / t5 / t89 * t87 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 21, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::D2fd_odeD2xxup_numRows() const { return 9; }
  integer gtocX_2burn_pars::D2fd_odeD2xxup_numCols() const { return 9; }
  integer gtocX_2burn_pars::D2fd_odeD2xxup_nnz()     const { return 49; }

  void
  gtocX_2burn_pars::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 0   ;
    iIndex[22] = 3   ; jIndex[22] = 1   ;
    iIndex[23] = 3   ; jIndex[23] = 2   ;
    iIndex[24] = 3   ; jIndex[24] = 3   ;
    iIndex[25] = 3   ; jIndex[25] = 4   ;
    iIndex[26] = 3   ; jIndex[26] = 5   ;
    iIndex[27] = 3   ; jIndex[27] = 6   ;
    iIndex[28] = 4   ; jIndex[28] = 0   ;
    iIndex[29] = 4   ; jIndex[29] = 1   ;
    iIndex[30] = 4   ; jIndex[30] = 2   ;
    iIndex[31] = 4   ; jIndex[31] = 3   ;
    iIndex[32] = 4   ; jIndex[32] = 4   ;
    iIndex[33] = 4   ; jIndex[33] = 5   ;
    iIndex[34] = 4   ; jIndex[34] = 6   ;
    iIndex[35] = 5   ; jIndex[35] = 0   ;
    iIndex[36] = 5   ; jIndex[36] = 1   ;
    iIndex[37] = 5   ; jIndex[37] = 2   ;
    iIndex[38] = 5   ; jIndex[38] = 3   ;
    iIndex[39] = 5   ; jIndex[39] = 4   ;
    iIndex[40] = 5   ; jIndex[40] = 5   ;
    iIndex[41] = 5   ; jIndex[41] = 6   ;
    iIndex[42] = 6   ; jIndex[42] = 0   ;
    iIndex[43] = 6   ; jIndex[43] = 1   ;
    iIndex[44] = 6   ; jIndex[44] = 2   ;
    iIndex[45] = 6   ; jIndex[45] = 3   ;
    iIndex[46] = 6   ; jIndex[46] = 4   ;
    iIndex[47] = 6   ; jIndex[47] = 5   ;
    iIndex[48] = 6   ; jIndex[48] = 6   ;
  }


  void
  gtocX_2burn_pars::D2fd_odeD2xxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t4   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t5   = t4 * t1;
    real_type t6   = P__[iP_p];
    real_type t7   = sqrt(t6);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 * t7;
    real_type t12  = t11 * t5;
    real_type t13  = ModelPars[iM_w_nonlin];
    real_type t17  = XR__[iX_f] / 2 + XL__[iX_f] / 2;
    real_type t21  = XR__[iX_g] / 2 + XL__[iX_g] / 2;
    real_type t25  = XR__[iX_L] / 2 + XL__[iX_L] / 2;
    real_type t26  = ray(t6, t17, t21, t25);
    real_type t27  = acceleration_r_D_1_1(t26, t8);
    real_type t28  = t27 * t13;
    real_type t29  = ray_D_2(t6, t17, t21, t25);
    real_type t30  = t29 * t29;
    real_type t31  = sin(t25);
    real_type t36  = acceleration_r_D_1(t26, t8);
    real_type t37  = t36 * t13;
    real_type t38  = ray_D_2_2(t6, t17, t21, t25);
    real_type t43  = LM__[1];
    real_type t44  = t4 * t43;
    real_type t45  = t11 * t44;
    real_type t46  = cos(t25);
    real_type t56  = t4 * LM__[2];
    real_type t57  = t46 * t46;
    real_type t59  = 1.0 / t7 / t6;
    result__[ 0   ] = -t31 * t30 * t28 * t12 / 4 - t31 * t38 * t37 * t12 / 4 + t46 * t30 * t28 * t45 / 4 + t46 * t38 * t37 * t45 / 4 - t9 * t59 * t57 * t56 / 2;
    real_type t64  = ray_D_3(t6, t17, t21, t25);
    real_type t65  = t29 * t64;
    real_type t70  = ray_D_2_3(t6, t17, t21, t25);
    real_type t84  = t9 * t59;
    real_type t85  = t46 * t84;
    result__[ 1   ] = -t31 * t65 * t28 * t12 / 4 - t31 * t70 * t37 * t12 / 4 + t46 * t65 * t28 * t45 / 4 + t46 * t70 * t37 * t45 / 4 - t85 * t31 * t56 / 2;
    real_type t88  = ray_D_4(t6, t17, t21, t25);
    real_type t89  = t29 * t88;
    real_type t94  = ray_D_2_4(t6, t17, t21, t25);
    real_type t96  = t31 * t94 * t37;
    real_type t100 = t46 * t29 * t37;
    real_type t108 = t46 * t94 * t37;
    real_type t112 = t31 * t29 * t37;
    real_type t118 = -t31 * t17 / 2 + t46 * t21 / 2;
    real_type t119 = t118 * t56;
    real_type t120 = t85 * t119;
    real_type t121 = t46 * t17;
    real_type t122 = t31 * t21;
    real_type t123 = 1 + t121 + t122;
    real_type t124 = t123 * t56;
    real_type t125 = t31 * t84;
    real_type t127 = t125 * t124 / 2;
    result__[ 2   ] = -t31 * t89 * t28 * t12 / 4 - t96 * t12 / 4 - t100 * t12 / 4 + t46 * t89 * t28 * t45 / 4 + t108 * t45 / 4 - t112 * t45 / 4 - t120 + t127;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t128 = 1.0 / t7;
    real_type t129 = t10 * t128;
    real_type t130 = t129 * t5;
    real_type t133 = ray_D_1(t6, t17, t21, t25);
    real_type t134 = t29 * t133;
    real_type t139 = ray_D_1_2(t6, t17, t21, t25);
    real_type t144 = t129 * t44;
    real_type t155 = t6 * t6;
    real_type t158 = t9 / t7 / t155;
    result__[ 6   ] = -t112 * t130 / 4 - t31 * t134 * t28 * t12 / 2 - t31 * t139 * t37 * t12 / 2 + t100 * t144 / 4 + t46 * t134 * t28 * t45 / 2 + t46 * t139 * t37 * t45 / 2 + 3.0 / 2.0 * t46 * t158 * t124;
    result__[ 7   ] = result__[4];
    real_type t162 = t64 * t64;
    real_type t167 = ray_D_3_3(t6, t17, t21, t25);
    real_type t180 = t31 * t31;
    result__[ 8   ] = -t31 * t162 * t28 * t12 / 4 - t31 * t167 * t37 * t12 / 4 + t46 * t162 * t28 * t45 / 4 + t46 * t167 * t37 * t45 / 4 - t9 * t59 * t180 * t56 / 2;
    real_type t185 = t64 * t88;
    real_type t190 = ray_D_3_4(t6, t17, t21, t25);
    real_type t192 = t31 * t190 * t37;
    real_type t196 = t46 * t64 * t37;
    real_type t204 = t46 * t190 * t37;
    real_type t208 = t31 * t64 * t37;
    real_type t211 = t125 * t119;
    real_type t213 = t85 * t124 / 2;
    result__[ 9   ] = -t31 * t185 * t28 * t12 / 4 - t192 * t12 / 4 - t196 * t12 / 4 + t46 * t185 * t28 * t45 / 4 + t204 * t45 / 4 - t208 * t45 / 4 - t211 - t213;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    real_type t216 = t64 * t133;
    real_type t221 = ray_D_1_3(t6, t17, t21, t25);
    result__[ 13  ] = -t208 * t130 / 4 - t31 * t216 * t28 * t12 / 2 - t31 * t221 * t37 * t12 / 2 + t196 * t144 / 4 + t46 * t216 * t28 * t45 / 2 + t46 * t221 * t37 * t45 / 2 + 3.0 / 2.0 * t31 * t158 * t124;
    result__[ 14  ] = result__[5];
    result__[ 15  ] = result__[12];
    real_type t239 = t7 * t4;
    real_type t240 = t10 * t239;
    real_type t241 = t88 * t88;
    real_type t246 = ray_D_4_4(t6, t17, t21, t25);
    real_type t251 = t46 * t88;
    real_type t252 = t251 * t37;
    real_type t255 = acceleration_r(t26, t8);
    real_type t256 = t255 * t13;
    real_type t257 = t31 * t256;
    real_type t270 = t31 * t88;
    real_type t271 = t270 * t37;
    real_type t274 = t46 * t256;
    real_type t279 = t118 * t118;
    result__[ 16  ] = (-t31 * t241 * t28 * t240 / 4 - t31 * t246 * t37 * t240 / 4 - t252 * t240 / 2 + t257 * t240 / 4) * t1 + (t46 * t241 * t28 * t240 / 4 + t46 * t246 * t37 * t240 / 4 - t271 * t240 / 2 - t274 * t240 / 4) * t43 - 2 * t9 * t59 * t279 * t56 - 2 * (-t121 / 4 - t122 / 4) * t84 * t124;
    real_type t290 = t13 * t10 * t239;
    real_type t291 = t29 * t27;
    result__[ 17  ] = (-t270 * t291 * t290 / 4 - t100 * t240 / 4 - t96 * t240 / 4) * t1 + (t251 * t291 * t290 / 4 + t108 * t240 / 4 - t112 * t240 / 4) * t43 - t120 + t127;
    real_type t306 = t64 * t27;
    result__[ 18  ] = (-t270 * t306 * t290 / 4 - t192 * t240 / 4 - t196 * t240 / 4) * t1 + (t251 * t306 * t290 / 4 + t204 * t240 / 4 - t208 * t240 / 4) * t43 - t211 - t213;
    result__[ 19  ] = result__[16];
    real_type t322 = t10 * t128 * t4;
    real_type t325 = t133 * t27;
    real_type t329 = ray_D_1_4(t6, t17, t21, t25);
    real_type t337 = t46 * t133 * t37;
    real_type t354 = t31 * t133 * t37;
    result__[ 20  ] = (-t271 * t322 / 4 - t270 * t325 * t290 / 2 - t31 * t329 * t37 * t240 / 2 - t274 * t322 / 4 - t337 * t240 / 2) * t1 + (t252 * t322 / 4 + t251 * t325 * t290 / 2 + t46 * t329 * t37 * t240 / 2 - t257 * t322 / 4 - t354 * t240 / 2) * t43 + 3 * t118 * t158 * t124;
    result__[ 21  ] = result__[3];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = result__[21];
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[14];
    result__[ 27  ] = result__[6];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[11];
    result__[ 30  ] = result__[18];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[29];
    result__[ 33  ] = result__[15];
    result__[ 34  ] = result__[13];
    result__[ 35  ] = result__[26];
    result__[ 36  ] = result__[33];
    result__[ 37  ] = result__[19];
    result__[ 38  ] = result__[35];
    result__[ 39  ] = result__[36];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[20];
    result__[ 42  ] = result__[27];
    result__[ 43  ] = result__[34];
    result__[ 44  ] = result__[41];
    result__[ 45  ] = result__[42];
    result__[ 46  ] = result__[43];
    result__[ 47  ] = result__[44];
    real_type t363 = t10 * t59 * t4;
    real_type t367 = t133 * t133;
    real_type t371 = ray_D_1_1(t6, t17, t21, t25);
    real_type t388 = t123 * t123;
    result__[ 48  ] = (t257 * t363 / 4 - t354 * t322 - t31 * t367 * t28 * t240 - t31 * t371 * t37 * t240) * t1 + (-t274 * t363 / 4 + t337 * t322 + t46 * t367 * t28 * t240 + t46 * t371 * t37 * t240) * t43 - 0.15e2 / 4.0 * t9 / t7 / t155 / t6 * t388 * t56;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 49, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: gtocX_2burn_pars_Methods_Guess.cc
