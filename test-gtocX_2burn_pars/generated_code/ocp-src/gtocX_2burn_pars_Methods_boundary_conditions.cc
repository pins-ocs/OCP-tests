/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_boundary_conditions.cc                |
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


namespace gtocX_2burn_parsDefine {

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

  integer gtocX_2burn_pars::bc_numEqns() const { return 6; }

  void
  gtocX_2burn_pars::bc_eval(
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
    real_type t1   = P__[iP_p];
    real_type t2   = XL__[iX_f];
    real_type t3   = XL__[iX_g];
    real_type t4   = P__[iP_h];
    real_type t5   = P__[iP_k];
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
    real_type t15  = XR__[iX_f];
    real_type t16  = XR__[iX_g];
    real_type t17  = XR__[iX_L];
    real_type t18  = x_position(t1, t15, t16, t4, t5, t17, t7);
    real_type t19  = ModelPars[iM_time_f];
    real_type t20  = X_end(t19);
    result__[ 3   ] = t18 - t20;
    real_type t21  = y_position(t1, t15, t16, t4, t5, t17, t7);
    real_type t22  = Y_end(t19);
    result__[ 4   ] = t21 - t22;
    real_type t23  = z_position(t1, t15, t16, t4, t5, t17, t7);
    real_type t24  = Z_end(t19);
    result__[ 5   ] = t23 - t24;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DbcDxxp_numRows() const { return 6; }
  integer gtocX_2burn_pars::DbcDxxp_numCols() const { return 9; }
  integer gtocX_2burn_pars::DbcDxxp_nnz()     const { return 36; }

  void
  gtocX_2burn_pars::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 1   ; jIndex[10] = 7   ;
    iIndex[11] = 1   ; jIndex[11] = 8   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 7   ;
    iIndex[17] = 2   ; jIndex[17] = 8   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 3   ; jIndex[20] = 5   ;
    iIndex[21] = 3   ; jIndex[21] = 6   ;
    iIndex[22] = 3   ; jIndex[22] = 7   ;
    iIndex[23] = 3   ; jIndex[23] = 8   ;
    iIndex[24] = 4   ; jIndex[24] = 3   ;
    iIndex[25] = 4   ; jIndex[25] = 4   ;
    iIndex[26] = 4   ; jIndex[26] = 5   ;
    iIndex[27] = 4   ; jIndex[27] = 6   ;
    iIndex[28] = 4   ; jIndex[28] = 7   ;
    iIndex[29] = 4   ; jIndex[29] = 8   ;
    iIndex[30] = 5   ; jIndex[30] = 3   ;
    iIndex[31] = 5   ; jIndex[31] = 4   ;
    iIndex[32] = 5   ; jIndex[32] = 5   ;
    iIndex[33] = 5   ; jIndex[33] = 6   ;
    iIndex[34] = 5   ; jIndex[34] = 7   ;
    iIndex[35] = 5   ; jIndex[35] = 8   ;
  }


  void
  gtocX_2burn_pars::DbcDxxp_sparse(
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
    real_type t1   = P__[iP_p];
    real_type t2   = XL__[iX_f];
    real_type t3   = XL__[iX_g];
    real_type t4   = P__[iP_h];
    real_type t5   = P__[iP_k];
    real_type t6   = XL__[iX_L];
    real_type t7   = ModelPars[iM_retrograde];
    result__[ 0   ] = x_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 1   ] = x_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 2   ] = x_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 3   ] = x_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 4   ] = x_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 5   ] = x_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 6   ] = y_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 7   ] = y_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 8   ] = y_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 9   ] = y_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 10  ] = y_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 11  ] = y_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 12  ] = z_position_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 13  ] = z_position_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 14  ] = z_position_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 15  ] = z_position_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 16  ] = z_position_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 17  ] = z_position_D_5(t1, t2, t3, t4, t5, t6, t7);
    real_type t8   = XR__[iX_f];
    real_type t9   = XR__[iX_g];
    real_type t10  = XR__[iX_L];
    result__[ 18  ] = x_position_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 19  ] = x_position_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 20  ] = x_position_D_6(t1, t8, t9, t4, t5, t10, t7);
    result__[ 21  ] = x_position_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 22  ] = x_position_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 23  ] = x_position_D_5(t1, t8, t9, t4, t5, t10, t7);
    result__[ 24  ] = y_position_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 25  ] = y_position_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 26  ] = y_position_D_6(t1, t8, t9, t4, t5, t10, t7);
    result__[ 27  ] = y_position_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 28  ] = y_position_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 29  ] = y_position_D_5(t1, t8, t9, t4, t5, t10, t7);
    result__[ 30  ] = z_position_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 31  ] = z_position_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 32  ] = z_position_D_6(t1, t8, t9, t4, t5, t10, t7);
    result__[ 33  ] = z_position_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 34  ] = z_position_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 35  ] = z_position_D_5(t1, t8, t9, t4, t5, t10, t7);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 36, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::D2bcD2xxp_numRows() const { return 9; }
  integer gtocX_2burn_pars::D2bcD2xxp_numCols() const { return 9; }
  integer gtocX_2burn_pars::D2bcD2xxp_nnz()     const { return 63; }

  void
  gtocX_2burn_pars::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 1   ; jIndex[10] = 7   ;
    iIndex[11] = 1   ; jIndex[11] = 8   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 7   ;
    iIndex[17] = 2   ; jIndex[17] = 8   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 3   ; jIndex[20] = 5   ;
    iIndex[21] = 3   ; jIndex[21] = 6   ;
    iIndex[22] = 3   ; jIndex[22] = 7   ;
    iIndex[23] = 3   ; jIndex[23] = 8   ;
    iIndex[24] = 4   ; jIndex[24] = 3   ;
    iIndex[25] = 4   ; jIndex[25] = 4   ;
    iIndex[26] = 4   ; jIndex[26] = 5   ;
    iIndex[27] = 4   ; jIndex[27] = 6   ;
    iIndex[28] = 4   ; jIndex[28] = 7   ;
    iIndex[29] = 4   ; jIndex[29] = 8   ;
    iIndex[30] = 5   ; jIndex[30] = 3   ;
    iIndex[31] = 5   ; jIndex[31] = 4   ;
    iIndex[32] = 5   ; jIndex[32] = 5   ;
    iIndex[33] = 5   ; jIndex[33] = 6   ;
    iIndex[34] = 5   ; jIndex[34] = 7   ;
    iIndex[35] = 5   ; jIndex[35] = 8   ;
    iIndex[36] = 6   ; jIndex[36] = 0   ;
    iIndex[37] = 6   ; jIndex[37] = 1   ;
    iIndex[38] = 6   ; jIndex[38] = 2   ;
    iIndex[39] = 6   ; jIndex[39] = 3   ;
    iIndex[40] = 6   ; jIndex[40] = 4   ;
    iIndex[41] = 6   ; jIndex[41] = 5   ;
    iIndex[42] = 6   ; jIndex[42] = 6   ;
    iIndex[43] = 6   ; jIndex[43] = 7   ;
    iIndex[44] = 6   ; jIndex[44] = 8   ;
    iIndex[45] = 7   ; jIndex[45] = 0   ;
    iIndex[46] = 7   ; jIndex[46] = 1   ;
    iIndex[47] = 7   ; jIndex[47] = 2   ;
    iIndex[48] = 7   ; jIndex[48] = 3   ;
    iIndex[49] = 7   ; jIndex[49] = 4   ;
    iIndex[50] = 7   ; jIndex[50] = 5   ;
    iIndex[51] = 7   ; jIndex[51] = 6   ;
    iIndex[52] = 7   ; jIndex[52] = 7   ;
    iIndex[53] = 7   ; jIndex[53] = 8   ;
    iIndex[54] = 8   ; jIndex[54] = 0   ;
    iIndex[55] = 8   ; jIndex[55] = 1   ;
    iIndex[56] = 8   ; jIndex[56] = 2   ;
    iIndex[57] = 8   ; jIndex[57] = 3   ;
    iIndex[58] = 8   ; jIndex[58] = 4   ;
    iIndex[59] = 8   ; jIndex[59] = 5   ;
    iIndex[60] = 8   ; jIndex[60] = 6   ;
    iIndex[61] = 8   ; jIndex[61] = 7   ;
    iIndex[62] = 8   ; jIndex[62] = 8   ;
  }


  void
  gtocX_2burn_pars::D2bcD2xxp_sparse(
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
    real_type t1   = OMEGA__[0];
    real_type t2   = P__[iP_p];
    real_type t3   = XL__[iX_f];
    real_type t4   = XL__[iX_g];
    real_type t5   = P__[iP_h];
    real_type t6   = P__[iP_k];
    real_type t7   = XL__[iX_L];
    real_type t8   = ModelPars[iM_retrograde];
    real_type t9   = x_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = y_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = z_position_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t1 * t9 + t11 * t12 + t14 * t15;
    real_type t17  = x_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = y_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t21  = z_position_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t1 * t17 + t11 * t19 + t14 * t21;
    real_type t23  = x_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = y_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = z_position_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t1 * t23 + t11 * t25 + t14 * t27;
    real_type t29  = x_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = y_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t33  = z_position_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t1 * t29 + t11 * t31 + t14 * t33;
    real_type t35  = x_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = y_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t39  = z_position_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t1 * t35 + t11 * t37 + t14 * t39;
    real_type t41  = x_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = y_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = z_position_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t1 * t41 + t11 * t43 + t14 * t45;
    result__[ 6   ] = result__[1];
    real_type t47  = x_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = y_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = z_position_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 7   ] = t1 * t47 + t11 * t49 + t14 * t51;
    real_type t53  = x_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = y_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t57  = z_position_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 8   ] = t1 * t53 + t11 * t55 + t14 * t57;
    real_type t59  = x_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t61  = y_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t63  = z_position_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 9   ] = t1 * t59 + t11 * t61 + t14 * t63;
    real_type t65  = x_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t67  = y_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t69  = z_position_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 10  ] = t1 * t65 + t11 * t67 + t14 * t69;
    real_type t71  = x_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t73  = y_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = z_position_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 11  ] = t1 * t71 + t11 * t73 + t14 * t75;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[8];
    real_type t77  = x_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t79  = y_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t81  = z_position_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 14  ] = t1 * t77 + t11 * t79 + t14 * t81;
    real_type t83  = x_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = y_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = z_position_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 15  ] = t1 * t83 + t11 * t85 + t14 * t87;
    real_type t89  = x_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = y_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = z_position_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 16  ] = t1 * t89 + t11 * t91 + t14 * t93;
    real_type t95  = x_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = y_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t99  = z_position_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 17  ] = t1 * t95 + t11 * t97 + t14 * t99;
    real_type t101 = OMEGA__[3];
    real_type t102 = XR__[iX_f];
    real_type t103 = XR__[iX_g];
    real_type t104 = XR__[iX_L];
    real_type t105 = x_position_D_2_2(t2, t102, t103, t5, t6, t104, t8);
    real_type t107 = OMEGA__[4];
    real_type t108 = y_position_D_2_2(t2, t102, t103, t5, t6, t104, t8);
    real_type t110 = OMEGA__[5];
    real_type t111 = z_position_D_2_2(t2, t102, t103, t5, t6, t104, t8);
    result__[ 18  ] = t101 * t105 + t107 * t108 + t110 * t111;
    real_type t113 = x_position_D_2_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t115 = y_position_D_2_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t117 = z_position_D_2_3(t2, t102, t103, t5, t6, t104, t8);
    result__[ 19  ] = t101 * t113 + t107 * t115 + t110 * t117;
    real_type t119 = x_position_D_2_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t121 = y_position_D_2_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t123 = z_position_D_2_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 20  ] = t101 * t119 + t107 * t121 + t110 * t123;
    real_type t125 = x_position_D_1_2(t2, t102, t103, t5, t6, t104, t8);
    real_type t127 = y_position_D_1_2(t2, t102, t103, t5, t6, t104, t8);
    real_type t129 = z_position_D_1_2(t2, t102, t103, t5, t6, t104, t8);
    result__[ 21  ] = t101 * t125 + t107 * t127 + t110 * t129;
    real_type t131 = x_position_D_2_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t133 = y_position_D_2_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t135 = z_position_D_2_4(t2, t102, t103, t5, t6, t104, t8);
    result__[ 22  ] = t101 * t131 + t107 * t133 + t110 * t135;
    real_type t137 = x_position_D_2_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t139 = y_position_D_2_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t141 = z_position_D_2_5(t2, t102, t103, t5, t6, t104, t8);
    result__[ 23  ] = t101 * t137 + t107 * t139 + t110 * t141;
    result__[ 24  ] = result__[19];
    real_type t143 = x_position_D_3_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t145 = y_position_D_3_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t147 = z_position_D_3_3(t2, t102, t103, t5, t6, t104, t8);
    result__[ 25  ] = t101 * t143 + t107 * t145 + t110 * t147;
    real_type t149 = x_position_D_3_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t151 = y_position_D_3_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t153 = z_position_D_3_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 26  ] = t101 * t149 + t107 * t151 + t110 * t153;
    real_type t155 = x_position_D_1_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t157 = y_position_D_1_3(t2, t102, t103, t5, t6, t104, t8);
    real_type t159 = z_position_D_1_3(t2, t102, t103, t5, t6, t104, t8);
    result__[ 27  ] = t101 * t155 + t107 * t157 + t110 * t159;
    real_type t161 = x_position_D_3_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t163 = y_position_D_3_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t165 = z_position_D_3_4(t2, t102, t103, t5, t6, t104, t8);
    result__[ 28  ] = t101 * t161 + t107 * t163 + t110 * t165;
    real_type t167 = x_position_D_3_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t169 = y_position_D_3_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t171 = z_position_D_3_5(t2, t102, t103, t5, t6, t104, t8);
    result__[ 29  ] = t101 * t167 + t107 * t169 + t110 * t171;
    result__[ 30  ] = result__[20];
    result__[ 31  ] = result__[26];
    real_type t173 = x_position_D_6_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t175 = y_position_D_6_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t177 = z_position_D_6_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 32  ] = t101 * t173 + t107 * t175 + t110 * t177;
    real_type t179 = x_position_D_1_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t181 = y_position_D_1_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t183 = z_position_D_1_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 33  ] = t101 * t179 + t107 * t181 + t110 * t183;
    real_type t185 = x_position_D_4_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t187 = y_position_D_4_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t189 = z_position_D_4_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 34  ] = t101 * t185 + t107 * t187 + t110 * t189;
    real_type t191 = x_position_D_5_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t193 = y_position_D_5_6(t2, t102, t103, t5, t6, t104, t8);
    real_type t195 = z_position_D_5_6(t2, t102, t103, t5, t6, t104, t8);
    result__[ 35  ] = t101 * t191 + t107 * t193 + t110 * t195;
    result__[ 36  ] = result__[3];
    result__[ 37  ] = result__[9];
    result__[ 38  ] = result__[15];
    result__[ 39  ] = result__[21];
    result__[ 40  ] = result__[27];
    result__[ 41  ] = result__[33];
    real_type t197 = x_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t199 = y_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t201 = z_position_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t203 = x_position_D_1_1(t2, t102, t103, t5, t6, t104, t8);
    real_type t205 = y_position_D_1_1(t2, t102, t103, t5, t6, t104, t8);
    real_type t207 = z_position_D_1_1(t2, t102, t103, t5, t6, t104, t8);
    result__[ 42  ] = t1 * t197 + t101 * t203 + t107 * t205 + t11 * t199 + t110 * t207 + t14 * t201;
    real_type t209 = x_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t211 = y_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t213 = z_position_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t215 = x_position_D_1_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t217 = y_position_D_1_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t219 = z_position_D_1_4(t2, t102, t103, t5, t6, t104, t8);
    result__[ 43  ] = t1 * t209 + t101 * t215 + t107 * t217 + t11 * t211 + t110 * t219 + t14 * t213;
    real_type t221 = x_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t223 = y_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t225 = z_position_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t227 = x_position_D_1_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t229 = y_position_D_1_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t231 = z_position_D_1_5(t2, t102, t103, t5, t6, t104, t8);
    result__[ 44  ] = t1 * t221 + t101 * t227 + t107 * t229 + t11 * t223 + t110 * t231 + t14 * t225;
    result__[ 45  ] = result__[4];
    result__[ 46  ] = result__[10];
    result__[ 47  ] = result__[16];
    result__[ 48  ] = result__[22];
    result__[ 49  ] = result__[28];
    result__[ 50  ] = result__[34];
    result__[ 51  ] = result__[43];
    real_type t233 = x_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t235 = y_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t237 = z_position_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t239 = x_position_D_4_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t241 = y_position_D_4_4(t2, t102, t103, t5, t6, t104, t8);
    real_type t243 = z_position_D_4_4(t2, t102, t103, t5, t6, t104, t8);
    result__[ 52  ] = t1 * t233 + t101 * t239 + t107 * t241 + t11 * t235 + t110 * t243 + t14 * t237;
    real_type t245 = x_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t247 = y_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t249 = z_position_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t251 = x_position_D_4_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t253 = y_position_D_4_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t255 = z_position_D_4_5(t2, t102, t103, t5, t6, t104, t8);
    result__[ 53  ] = t1 * t245 + t101 * t251 + t107 * t253 + t11 * t247 + t110 * t255 + t14 * t249;
    result__[ 54  ] = result__[5];
    result__[ 55  ] = result__[11];
    result__[ 56  ] = result__[17];
    result__[ 57  ] = result__[23];
    result__[ 58  ] = result__[29];
    result__[ 59  ] = result__[35];
    result__[ 60  ] = result__[44];
    result__[ 61  ] = result__[53];
    real_type t257 = x_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t259 = y_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t261 = z_position_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t263 = x_position_D_5_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t265 = y_position_D_5_5(t2, t102, t103, t5, t6, t104, t8);
    real_type t267 = z_position_D_5_5(t2, t102, t103, t5, t6, t104, t8);
    result__[ 62  ] = t1 * t257 + t101 * t263 + t107 * t265 + t11 * t259 + t110 * t267 + t14 * t261;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2bcD2xxp_sparse", 63, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: gtocX_2burn_pars_Methods_boundary_conditions.cc
