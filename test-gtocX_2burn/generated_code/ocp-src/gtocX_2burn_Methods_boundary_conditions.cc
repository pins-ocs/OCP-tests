/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_boundary_conditions.cc                     |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burnDefine {

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

  integer
  gtocX_2burn::boundaryConditions_numEqns() const
  { return 6; }

  void
  gtocX_2burn::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XL__[iX_p];
    real_type t2   = XL__[iX_f];
    real_type t3   = XL__[iX_g];
    real_type t4   = XL__[iX_h];
    real_type t5   = XL__[iX_k];
    real_type t6   = XL__[iX_L];
    real_type t7   = ModelPars[iM_retrograde];
    real_type t8   = x_position(t1, t2, t3, t4, t5, t6, t7);
    real_type t9   = ModelPars[iM_time_i];
    real_type t10  = X_begin(t9);
    result__[ 0   ] = t8 - t10;
    real_type t11  = y_position(t1, t2, t3, t4, t5, t6, t7);
    real_type t12  = Y_begin(t9);
    result__[ 1   ] = t11 - t12;
    real_type t13  = z_position(t1, t2, t3, t4, t5, t6, t7);
    real_type t14  = Z_begin(t9);
    result__[ 2   ] = t13 - t14;
    real_type t15  = XR__[iX_p];
    real_type t16  = XR__[iX_f];
    real_type t17  = XR__[iX_g];
    real_type t18  = XR__[iX_h];
    real_type t19  = XR__[iX_k];
    real_type t20  = XR__[iX_L];
    real_type t21  = x_position(t15, t16, t17, t18, t19, t20, t7);
    real_type t22  = ModelPars[iM_time_f];
    real_type t23  = X_end(t22);
    result__[ 3   ] = t21 - t23;
    real_type t24  = y_position(t15, t16, t17, t18, t19, t20, t7);
    real_type t25  = Y_end(t22);
    result__[ 4   ] = t24 - t25;
    real_type t26  = z_position(t15, t16, t17, t18, t19, t20, t7);
    real_type t27  = Z_end(t22);
    result__[ 5   ] = t26 - t27;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::DboundaryConditionsDxxp_numRows() const
  { return 6; }

  integer
  gtocX_2burn::DboundaryConditionsDxxp_numCols() const
  { return 12; }

  integer
  gtocX_2burn::DboundaryConditionsDxxp_nnz() const
  { return 36; }

  void
  gtocX_2burn::DboundaryConditionsDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 4   ;
    iIndex[11] = 1   ; jIndex[11] = 5   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 3   ;
    iIndex[16] = 2   ; jIndex[16] = 4   ;
    iIndex[17] = 2   ; jIndex[17] = 5   ;
    iIndex[18] = 3   ; jIndex[18] = 6   ;
    iIndex[19] = 3   ; jIndex[19] = 7   ;
    iIndex[20] = 3   ; jIndex[20] = 8   ;
    iIndex[21] = 3   ; jIndex[21] = 9   ;
    iIndex[22] = 3   ; jIndex[22] = 10  ;
    iIndex[23] = 3   ; jIndex[23] = 11  ;
    iIndex[24] = 4   ; jIndex[24] = 6   ;
    iIndex[25] = 4   ; jIndex[25] = 7   ;
    iIndex[26] = 4   ; jIndex[26] = 8   ;
    iIndex[27] = 4   ; jIndex[27] = 9   ;
    iIndex[28] = 4   ; jIndex[28] = 10  ;
    iIndex[29] = 4   ; jIndex[29] = 11  ;
    iIndex[30] = 5   ; jIndex[30] = 6   ;
    iIndex[31] = 5   ; jIndex[31] = 7   ;
    iIndex[32] = 5   ; jIndex[32] = 8   ;
    iIndex[33] = 5   ; jIndex[33] = 9   ;
    iIndex[34] = 5   ; jIndex[34] = 10  ;
    iIndex[35] = 5   ; jIndex[35] = 11  ;
  }

  void
  gtocX_2burn::DboundaryConditionsDxxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XL__[iX_p];
    real_type t2   = XL__[iX_f];
    real_type t3   = XL__[iX_g];
    real_type t4   = XL__[iX_h];
    real_type t5   = XL__[iX_k];
    real_type t6   = XL__[iX_L];
    real_type t7   = ModelPars[iM_retrograde];
    result__[ 0   ] = x_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 1   ] = x_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 2   ] = x_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 3   ] = x_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 4   ] = x_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 5   ] = x_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 6   ] = y_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 7   ] = y_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 8   ] = y_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 9   ] = y_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 10  ] = y_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 11  ] = y_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 12  ] = z_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 13  ] = z_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 14  ] = z_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 15  ] = z_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 16  ] = z_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 17  ] = z_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    real_type t8   = XR__[iX_p];
    real_type t9   = XR__[iX_f];
    real_type t10  = XR__[iX_g];
    real_type t11  = XR__[iX_h];
    real_type t12  = XR__[iX_k];
    real_type t13  = XR__[iX_L];
    result__[ 18  ] = x_position_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 19  ] = x_position_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 20  ] = x_position_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 21  ] = x_position_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 22  ] = x_position_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 23  ] = x_position_D_6(t8, t9, t10, t11, t12, t13, t7);
    result__[ 24  ] = y_position_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 25  ] = y_position_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 26  ] = y_position_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 27  ] = y_position_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 28  ] = y_position_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 29  ] = y_position_D_6(t8, t9, t10, t11, t12, t13, t7);
    result__[ 30  ] = z_position_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 31  ] = z_position_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 32  ] = z_position_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 33  ] = z_position_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 34  ] = z_position_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 35  ] = z_position_D_6(t8, t9, t10, t11, t12, t13, t7);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxxp_sparse", 36, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::adjointBC_numEqns() const
  { return 12; }

  void
  gtocX_2burn::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = OMEGA__[0];
    real_type t2   = XL__[iX_p];
    real_type t3   = XL__[iX_f];
    real_type t4   = XL__[iX_g];
    real_type t5   = XL__[iX_h];
    real_type t6   = XL__[iX_k];
    real_type t7   = XL__[iX_L];
    real_type t8   = ModelPars[iM_retrograde];
    real_type t9   = x_position_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = y_position_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = z_position_D_1(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14 + LL__[iL_lambda1__xo];
    real_type t18  = x_position_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t20  = y_position_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = z_position_D_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t18 * t1 + t20 * t11 + t22 * t14 + LL__[iL_lambda2__xo];
    real_type t25  = x_position_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = y_position_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t29  = z_position_D_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t25 * t1 + t27 * t11 + t29 * t14 + LL__[iL_lambda3__xo];
    real_type t32  = x_position_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t34  = y_position_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t36  = z_position_D_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t32 * t1 + t34 * t11 + t36 * t14 + LL__[iL_lambda4__xo];
    real_type t39  = x_position_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t41  = y_position_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = z_position_D_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t39 * t1 + t41 * t11 + t43 * t14 + LL__[iL_lambda5__xo];
    real_type t46  = x_position_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t48  = y_position_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t50  = z_position_D_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t46 * t1 + t48 * t11 + t50 * t14 + LL__[iL_lambda6__xo];
    real_type t53  = OMEGA__[3];
    real_type t54  = XR__[iX_p];
    real_type t55  = XR__[iX_f];
    real_type t56  = XR__[iX_g];
    real_type t57  = XR__[iX_h];
    real_type t58  = XR__[iX_k];
    real_type t59  = XR__[iX_L];
    real_type t60  = x_position_D_1(t54, t55, t56, t57, t58, t59, t8);
    real_type t62  = OMEGA__[4];
    real_type t63  = y_position_D_1(t54, t55, t56, t57, t58, t59, t8);
    real_type t65  = OMEGA__[5];
    real_type t66  = z_position_D_1(t54, t55, t56, t57, t58, t59, t8);
    result__[ 6   ] = t53 * t60 + t62 * t63 + t65 * t66 - LR__[iL_lambda1__xo];
    real_type t69  = x_position_D_2(t54, t55, t56, t57, t58, t59, t8);
    real_type t71  = y_position_D_2(t54, t55, t56, t57, t58, t59, t8);
    real_type t73  = z_position_D_2(t54, t55, t56, t57, t58, t59, t8);
    result__[ 7   ] = t53 * t69 + t62 * t71 + t65 * t73 - LR__[iL_lambda2__xo];
    real_type t76  = x_position_D_3(t54, t55, t56, t57, t58, t59, t8);
    real_type t78  = y_position_D_3(t54, t55, t56, t57, t58, t59, t8);
    real_type t80  = z_position_D_3(t54, t55, t56, t57, t58, t59, t8);
    result__[ 8   ] = t53 * t76 + t62 * t78 + t65 * t80 - LR__[iL_lambda3__xo];
    real_type t83  = x_position_D_4(t54, t55, t56, t57, t58, t59, t8);
    real_type t85  = y_position_D_4(t54, t55, t56, t57, t58, t59, t8);
    real_type t87  = z_position_D_4(t54, t55, t56, t57, t58, t59, t8);
    result__[ 9   ] = t53 * t83 + t62 * t85 + t65 * t87 - LR__[iL_lambda4__xo];
    real_type t90  = x_position_D_5(t54, t55, t56, t57, t58, t59, t8);
    real_type t92  = y_position_D_5(t54, t55, t56, t57, t58, t59, t8);
    real_type t94  = z_position_D_5(t54, t55, t56, t57, t58, t59, t8);
    result__[ 10  ] = t53 * t90 + t62 * t92 + t65 * t94 - LR__[iL_lambda5__xo];
    real_type t97  = x_position_D_6(t54, t55, t56, t57, t58, t59, t8);
    real_type t99  = y_position_D_6(t54, t55, t56, t57, t58, t59, t8);
    real_type t101 = z_position_D_6(t54, t55, t56, t57, t58, t59, t8);
    result__[ 11  ] = t101 * t65 + t53 * t97 + t62 * t99 - LR__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::DadjointBCDxxp_numRows() const
  { return 12; }

  integer
  gtocX_2burn::DadjointBCDxxp_numCols() const
  { return 12; }

  integer
  gtocX_2burn::DadjointBCDxxp_nnz() const
  { return 72; }

  void
  gtocX_2burn::DadjointBCDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 4   ;
    iIndex[11] = 1   ; jIndex[11] = 5   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 3   ;
    iIndex[16] = 2   ; jIndex[16] = 4   ;
    iIndex[17] = 2   ; jIndex[17] = 5   ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 1   ;
    iIndex[20] = 3   ; jIndex[20] = 2   ;
    iIndex[21] = 3   ; jIndex[21] = 3   ;
    iIndex[22] = 3   ; jIndex[22] = 4   ;
    iIndex[23] = 3   ; jIndex[23] = 5   ;
    iIndex[24] = 4   ; jIndex[24] = 0   ;
    iIndex[25] = 4   ; jIndex[25] = 1   ;
    iIndex[26] = 4   ; jIndex[26] = 2   ;
    iIndex[27] = 4   ; jIndex[27] = 3   ;
    iIndex[28] = 4   ; jIndex[28] = 4   ;
    iIndex[29] = 4   ; jIndex[29] = 5   ;
    iIndex[30] = 5   ; jIndex[30] = 0   ;
    iIndex[31] = 5   ; jIndex[31] = 1   ;
    iIndex[32] = 5   ; jIndex[32] = 2   ;
    iIndex[33] = 5   ; jIndex[33] = 3   ;
    iIndex[34] = 5   ; jIndex[34] = 4   ;
    iIndex[35] = 5   ; jIndex[35] = 5   ;
    iIndex[36] = 6   ; jIndex[36] = 6   ;
    iIndex[37] = 6   ; jIndex[37] = 7   ;
    iIndex[38] = 6   ; jIndex[38] = 8   ;
    iIndex[39] = 6   ; jIndex[39] = 9   ;
    iIndex[40] = 6   ; jIndex[40] = 10  ;
    iIndex[41] = 6   ; jIndex[41] = 11  ;
    iIndex[42] = 7   ; jIndex[42] = 6   ;
    iIndex[43] = 7   ; jIndex[43] = 7   ;
    iIndex[44] = 7   ; jIndex[44] = 8   ;
    iIndex[45] = 7   ; jIndex[45] = 9   ;
    iIndex[46] = 7   ; jIndex[46] = 10  ;
    iIndex[47] = 7   ; jIndex[47] = 11  ;
    iIndex[48] = 8   ; jIndex[48] = 6   ;
    iIndex[49] = 8   ; jIndex[49] = 7   ;
    iIndex[50] = 8   ; jIndex[50] = 8   ;
    iIndex[51] = 8   ; jIndex[51] = 9   ;
    iIndex[52] = 8   ; jIndex[52] = 10  ;
    iIndex[53] = 8   ; jIndex[53] = 11  ;
    iIndex[54] = 9   ; jIndex[54] = 6   ;
    iIndex[55] = 9   ; jIndex[55] = 7   ;
    iIndex[56] = 9   ; jIndex[56] = 8   ;
    iIndex[57] = 9   ; jIndex[57] = 9   ;
    iIndex[58] = 9   ; jIndex[58] = 10  ;
    iIndex[59] = 9   ; jIndex[59] = 11  ;
    iIndex[60] = 10  ; jIndex[60] = 6   ;
    iIndex[61] = 10  ; jIndex[61] = 7   ;
    iIndex[62] = 10  ; jIndex[62] = 8   ;
    iIndex[63] = 10  ; jIndex[63] = 9   ;
    iIndex[64] = 10  ; jIndex[64] = 10  ;
    iIndex[65] = 10  ; jIndex[65] = 11  ;
    iIndex[66] = 11  ; jIndex[66] = 6   ;
    iIndex[67] = 11  ; jIndex[67] = 7   ;
    iIndex[68] = 11  ; jIndex[68] = 8   ;
    iIndex[69] = 11  ; jIndex[69] = 9   ;
    iIndex[70] = 11  ; jIndex[70] = 10  ;
    iIndex[71] = 11  ; jIndex[71] = 11  ;
  }

  void
  gtocX_2burn::DadjointBCDxxp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = OMEGA__[0];
    real_type t2   = XL__[iX_p];
    real_type t3   = XL__[iX_f];
    real_type t4   = XL__[iX_g];
    real_type t5   = XL__[iX_h];
    real_type t6   = XL__[iX_k];
    real_type t7   = XL__[iX_L];
    real_type t8   = ModelPars[iM_retrograde];
    real_type t9   = x_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = y_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = z_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t1 * t9 + t11 * t12 + t14 * t15;
    real_type t17  = x_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = y_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t21  = z_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t1 * t17 + t11 * t19 + t14 * t21;
    real_type t23  = x_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = y_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = z_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t1 * t23 + t11 * t25 + t14 * t27;
    real_type t29  = x_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = y_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t33  = z_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t1 * t29 + t11 * t31 + t14 * t33;
    real_type t35  = x_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = y_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t39  = z_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t1 * t35 + t11 * t37 + t14 * t39;
    real_type t41  = x_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = y_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = z_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t1 * t41 + t11 * t43 + t14 * t45;
    result__[ 6   ] = result__[1];
    real_type t47  = x_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = y_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = z_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 7   ] = t1 * t47 + t11 * t49 + t14 * t51;
    real_type t53  = x_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = y_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t57  = z_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 8   ] = t1 * t53 + t11 * t55 + t14 * t57;
    real_type t59  = x_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t61  = y_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t63  = z_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 9   ] = t1 * t59 + t11 * t61 + t14 * t63;
    real_type t65  = x_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t67  = y_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t69  = z_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 10  ] = t1 * t65 + t11 * t67 + t14 * t69;
    real_type t71  = x_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t73  = y_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = z_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 11  ] = t1 * t71 + t11 * t73 + t14 * t75;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[8];
    real_type t77  = x_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t79  = y_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t81  = z_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 14  ] = t1 * t77 + t11 * t79 + t14 * t81;
    real_type t83  = x_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = y_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = z_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 15  ] = t1 * t83 + t11 * t85 + t14 * t87;
    real_type t89  = x_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = y_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = z_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 16  ] = t1 * t89 + t11 * t91 + t14 * t93;
    real_type t95  = x_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = y_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t99  = z_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 17  ] = t1 * t95 + t11 * t97 + t14 * t99;
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[9];
    result__[ 20  ] = result__[15];
    real_type t101 = x_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = y_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = z_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 21  ] = t1 * t101 + t103 * t11 + t105 * t14;
    real_type t107 = x_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = y_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t111 = z_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 22  ] = t1 * t107 + t109 * t11 + t111 * t14;
    real_type t113 = x_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t115 = y_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t117 = z_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 23  ] = t1 * t113 + t11 * t115 + t117 * t14;
    result__[ 24  ] = result__[4];
    result__[ 25  ] = result__[10];
    result__[ 26  ] = result__[16];
    result__[ 27  ] = result__[22];
    real_type t119 = x_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t121 = y_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t123 = z_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 28  ] = t1 * t119 + t11 * t121 + t123 * t14;
    real_type t125 = x_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t127 = y_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = z_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 29  ] = t1 * t125 + t11 * t127 + t129 * t14;
    result__[ 30  ] = result__[5];
    result__[ 31  ] = result__[11];
    result__[ 32  ] = result__[17];
    result__[ 33  ] = result__[23];
    result__[ 34  ] = result__[29];
    real_type t131 = x_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t133 = y_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t135 = z_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 35  ] = t1 * t131 + t11 * t133 + t135 * t14;
    real_type t137 = OMEGA__[3];
    real_type t138 = XR__[iX_p];
    real_type t139 = XR__[iX_f];
    real_type t140 = XR__[iX_g];
    real_type t141 = XR__[iX_h];
    real_type t142 = XR__[iX_k];
    real_type t143 = XR__[iX_L];
    real_type t144 = x_position_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    real_type t146 = OMEGA__[4];
    real_type t147 = y_position_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    real_type t149 = OMEGA__[5];
    real_type t150 = z_position_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    result__[ 36  ] = t137 * t144 + t146 * t147 + t149 * t150;
    real_type t152 = x_position_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t154 = y_position_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t156 = z_position_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    result__[ 37  ] = t137 * t152 + t146 * t154 + t149 * t156;
    real_type t158 = x_position_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t160 = y_position_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t162 = z_position_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 38  ] = t137 * t158 + t146 * t160 + t149 * t162;
    real_type t164 = x_position_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t166 = y_position_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t168 = z_position_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 39  ] = t137 * t164 + t146 * t166 + t149 * t168;
    real_type t170 = x_position_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t172 = y_position_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t174 = z_position_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 40  ] = t137 * t170 + t146 * t172 + t149 * t174;
    real_type t176 = x_position_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t178 = y_position_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t180 = z_position_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 41  ] = t137 * t176 + t146 * t178 + t149 * t180;
    result__[ 42  ] = result__[37];
    real_type t182 = x_position_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t184 = y_position_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t186 = z_position_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    result__[ 43  ] = t137 * t182 + t146 * t184 + t149 * t186;
    real_type t188 = x_position_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t190 = y_position_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t192 = z_position_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 44  ] = t137 * t188 + t146 * t190 + t149 * t192;
    real_type t194 = x_position_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t196 = y_position_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t198 = z_position_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 45  ] = t137 * t194 + t146 * t196 + t149 * t198;
    real_type t200 = x_position_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t202 = y_position_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t204 = z_position_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 46  ] = t137 * t200 + t146 * t202 + t149 * t204;
    real_type t206 = x_position_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t208 = y_position_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t210 = z_position_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 47  ] = t137 * t206 + t146 * t208 + t149 * t210;
    result__[ 48  ] = result__[38];
    result__[ 49  ] = result__[44];
    real_type t212 = x_position_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t214 = y_position_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t216 = z_position_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 50  ] = t137 * t212 + t146 * t214 + t149 * t216;
    real_type t218 = x_position_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t220 = y_position_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t222 = z_position_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 51  ] = t137 * t218 + t146 * t220 + t149 * t222;
    real_type t224 = x_position_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t226 = y_position_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t228 = z_position_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 52  ] = t137 * t224 + t226 * t146 + t228 * t149;
    real_type t230 = x_position_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t232 = y_position_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t234 = z_position_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 53  ] = t230 * t137 + t232 * t146 + t234 * t149;
    result__[ 54  ] = result__[39];
    result__[ 55  ] = result__[45];
    result__[ 56  ] = result__[51];
    real_type t236 = x_position_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t238 = y_position_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t240 = z_position_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 57  ] = t236 * t137 + t238 * t146 + t240 * t149;
    real_type t242 = x_position_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t244 = y_position_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t246 = z_position_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 58  ] = t242 * t137 + t244 * t146 + t246 * t149;
    real_type t248 = x_position_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t250 = y_position_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t252 = z_position_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 59  ] = t248 * t137 + t250 * t146 + t252 * t149;
    result__[ 60  ] = result__[40];
    result__[ 61  ] = result__[46];
    result__[ 62  ] = result__[52];
    result__[ 63  ] = result__[58];
    real_type t254 = x_position_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t256 = y_position_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t258 = z_position_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 64  ] = t254 * t137 + t256 * t146 + t258 * t149;
    real_type t260 = x_position_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t262 = y_position_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t264 = z_position_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 65  ] = t260 * t137 + t262 * t146 + t264 * t149;
    result__[ 66  ] = result__[41];
    result__[ 67  ] = result__[47];
    result__[ 68  ] = result__[53];
    result__[ 69  ] = result__[59];
    result__[ 70  ] = result__[65];
    real_type t266 = x_position_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t268 = y_position_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t270 = z_position_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 71  ] = t266 * t137 + t268 * t146 + t270 * t149;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 72, i_segment_left, i_segment_right );
  }
}

// EOF: gtocX_2burn_Methods_boundary_conditions.cc
