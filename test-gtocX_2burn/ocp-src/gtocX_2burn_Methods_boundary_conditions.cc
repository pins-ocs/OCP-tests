/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods.cc                                         |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t1   = XL__[0];
    real_type t2   = XL__[1];
    real_type t3   = XL__[2];
    real_type t4   = XL__[3];
    real_type t5   = XL__[4];
    real_type t6   = XL__[5];
    real_type t7   = ModelPars[5];
    real_type t8   = xPosition(t1, t2, t3, t4, t5, t6, t7);
    real_type t9   = ModelPars[2];
    real_type t10  = X_begin(t9);
    result__[ 0   ] = t8 - t10;
    real_type t11  = yPosition(t1, t2, t3, t4, t5, t6, t7);
    real_type t12  = Y_begin(t9);
    result__[ 1   ] = t11 - t12;
    real_type t13  = zPosition(t1, t2, t3, t4, t5, t6, t7);
    real_type t14  = Z_begin(t9);
    result__[ 2   ] = t13 - t14;
    real_type t15  = XR__[0];
    real_type t16  = XR__[1];
    real_type t17  = XR__[2];
    real_type t18  = XR__[3];
    real_type t19  = XR__[4];
    real_type t20  = XR__[5];
    real_type t21  = xPosition(t15, t16, t17, t18, t19, t20, t7);
    real_type t22  = ModelPars[1];
    real_type t23  = X_end(t22);
    result__[ 3   ] = t21 - t23;
    real_type t24  = yPosition(t15, t16, t17, t18, t19, t20, t7);
    real_type t25  = Y_end(t22);
    result__[ 4   ] = t24 - t25;
    real_type t26  = zPosition(t15, t16, t17, t18, t19, t20, t7);
    real_type t27  = Z_end(t22);
    result__[ 5   ] = t26 - t27;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  gtocX_2burn::DboundaryConditionsDx_numRows() const
  { return 6; }

  integer
  gtocX_2burn::DboundaryConditionsDx_numCols() const
  { return 12; }

  integer
  gtocX_2burn::DboundaryConditionsDx_nnz() const
  { return 36; }

  void
  gtocX_2burn::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 0   ; jIndex[ 4  ] = 4   ;
    iIndex[ 5  ] = 0   ; jIndex[ 5  ] = 5   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 1   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 1   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 1   ; jIndex[ 9  ] = 3   ;
    iIndex[ 10 ] = 1   ; jIndex[ 10 ] = 4   ;
    iIndex[ 11 ] = 1   ; jIndex[ 11 ] = 5   ;
    iIndex[ 12 ] = 2   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 2   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 2   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 2   ; jIndex[ 15 ] = 3   ;
    iIndex[ 16 ] = 2   ; jIndex[ 16 ] = 4   ;
    iIndex[ 17 ] = 2   ; jIndex[ 17 ] = 5   ;
    iIndex[ 18 ] = 3   ; jIndex[ 18 ] = 6   ;
    iIndex[ 19 ] = 3   ; jIndex[ 19 ] = 7   ;
    iIndex[ 20 ] = 3   ; jIndex[ 20 ] = 8   ;
    iIndex[ 21 ] = 3   ; jIndex[ 21 ] = 9   ;
    iIndex[ 22 ] = 3   ; jIndex[ 22 ] = 10  ;
    iIndex[ 23 ] = 3   ; jIndex[ 23 ] = 11  ;
    iIndex[ 24 ] = 4   ; jIndex[ 24 ] = 6   ;
    iIndex[ 25 ] = 4   ; jIndex[ 25 ] = 7   ;
    iIndex[ 26 ] = 4   ; jIndex[ 26 ] = 8   ;
    iIndex[ 27 ] = 4   ; jIndex[ 27 ] = 9   ;
    iIndex[ 28 ] = 4   ; jIndex[ 28 ] = 10  ;
    iIndex[ 29 ] = 4   ; jIndex[ 29 ] = 11  ;
    iIndex[ 30 ] = 5   ; jIndex[ 30 ] = 6   ;
    iIndex[ 31 ] = 5   ; jIndex[ 31 ] = 7   ;
    iIndex[ 32 ] = 5   ; jIndex[ 32 ] = 8   ;
    iIndex[ 33 ] = 5   ; jIndex[ 33 ] = 9   ;
    iIndex[ 34 ] = 5   ; jIndex[ 34 ] = 10  ;
    iIndex[ 35 ] = 5   ; jIndex[ 35 ] = 11  ;
  }

  void
  gtocX_2burn::DboundaryConditionsDx_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t1   = XL__[0];
    real_type t2   = XL__[1];
    real_type t3   = XL__[2];
    real_type t4   = XL__[3];
    real_type t5   = XL__[4];
    real_type t6   = XL__[5];
    real_type t7   = ModelPars[5];
    result__[ 0   ] = xPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 1   ] = xPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 2   ] = xPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 3   ] = xPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 4   ] = xPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 5   ] = xPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 6   ] = yPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 7   ] = yPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 8   ] = yPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 9   ] = yPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 10  ] = yPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 11  ] = yPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 12  ] = zPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 13  ] = zPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 14  ] = zPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 15  ] = zPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 16  ] = zPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 17  ] = zPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    real_type t8   = XR__[0];
    real_type t9   = XR__[1];
    real_type t10  = XR__[2];
    real_type t11  = XR__[3];
    real_type t12  = XR__[4];
    real_type t13  = XR__[5];
    result__[ 18  ] = xPosition_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 19  ] = xPosition_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 20  ] = xPosition_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 21  ] = xPosition_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 22  ] = xPosition_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 23  ] = xPosition_D_6(t8, t9, t10, t11, t12, t13, t7);
    result__[ 24  ] = yPosition_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 25  ] = yPosition_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 26  ] = yPosition_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 27  ] = yPosition_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 28  ] = yPosition_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 29  ] = yPosition_D_6(t8, t9, t10, t11, t12, t13, t7);
    result__[ 30  ] = zPosition_D_1(t8, t9, t10, t11, t12, t13, t7);
    result__[ 31  ] = zPosition_D_2(t8, t9, t10, t11, t12, t13, t7);
    result__[ 32  ] = zPosition_D_3(t8, t9, t10, t11, t12, t13, t7);
    result__[ 33  ] = zPosition_D_4(t8, t9, t10, t11, t12, t13, t7);
    result__[ 34  ] = zPosition_D_5(t8, t9, t10, t11, t12, t13, t7);
    result__[ 35  ] = zPosition_D_6(t8, t9, t10, t11, t12, t13, t7);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",36);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  gtocX_2burn::DboundaryConditionsDp_numRows() const
  { return 6; }

  integer
  gtocX_2burn::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  gtocX_2burn::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  gtocX_2burn::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  gtocX_2burn::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t1   = OMEGA__[0];
    real_type t2   = XL__[0];
    real_type t3   = XL__[1];
    real_type t4   = XL__[2];
    real_type t5   = XL__[3];
    real_type t6   = XL__[4];
    real_type t7   = XL__[5];
    real_type t8   = ModelPars[5];
    real_type t9   = xPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = yPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = zPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14 + LL__[0];
    real_type t18  = xPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t20  = yPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = zPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t18 * t1 + t20 * t11 + t22 * t14 + LL__[1];
    real_type t25  = xPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = yPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t29  = zPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t25 * t1 + t27 * t11 + t29 * t14 + LL__[2];
    real_type t32  = xPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t34  = yPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t36  = zPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t32 * t1 + t34 * t11 + t36 * t14 + LL__[3];
    real_type t39  = xPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t41  = yPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = zPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t39 * t1 + t41 * t11 + t43 * t14 + LL__[4];
    real_type t46  = xPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t48  = yPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t50  = zPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t1 * t46 + t11 * t48 + t14 * t50 + LL__[5];
    real_type t53  = OMEGA__[3];
    real_type t54  = XR__[0];
    real_type t55  = XR__[1];
    real_type t56  = XR__[2];
    real_type t57  = XR__[3];
    real_type t58  = XR__[4];
    real_type t59  = XR__[5];
    real_type t60  = xPosition_D_1(t54, t55, t56, t57, t58, t59, t8);
    real_type t62  = OMEGA__[4];
    real_type t63  = yPosition_D_1(t54, t55, t56, t57, t58, t59, t8);
    real_type t65  = OMEGA__[5];
    real_type t66  = zPosition_D_1(t54, t55, t56, t57, t58, t59, t8);
    result__[ 6   ] = t53 * t60 + t62 * t63 + t65 * t66 - LR__[0];
    real_type t69  = xPosition_D_2(t54, t55, t56, t57, t58, t59, t8);
    real_type t71  = yPosition_D_2(t54, t55, t56, t57, t58, t59, t8);
    real_type t73  = zPosition_D_2(t54, t55, t56, t57, t58, t59, t8);
    result__[ 7   ] = t53 * t69 + t62 * t71 + t65 * t73 - LR__[1];
    real_type t76  = xPosition_D_3(t54, t55, t56, t57, t58, t59, t8);
    real_type t78  = yPosition_D_3(t54, t55, t56, t57, t58, t59, t8);
    real_type t80  = zPosition_D_3(t54, t55, t56, t57, t58, t59, t8);
    result__[ 8   ] = t53 * t76 + t62 * t78 + t65 * t80 - LR__[2];
    real_type t83  = xPosition_D_4(t54, t55, t56, t57, t58, t59, t8);
    real_type t85  = yPosition_D_4(t54, t55, t56, t57, t58, t59, t8);
    real_type t87  = zPosition_D_4(t54, t55, t56, t57, t58, t59, t8);
    result__[ 9   ] = t53 * t83 + t62 * t85 + t65 * t87 - LR__[3];
    real_type t90  = xPosition_D_5(t54, t55, t56, t57, t58, t59, t8);
    real_type t92  = yPosition_D_5(t54, t55, t56, t57, t58, t59, t8);
    real_type t94  = zPosition_D_5(t54, t55, t56, t57, t58, t59, t8);
    result__[ 10  ] = t53 * t90 + t62 * t92 + t65 * t94 - LR__[4];
    real_type t97  = xPosition_D_6(t54, t55, t56, t57, t58, t59, t8);
    real_type t99  = yPosition_D_6(t54, t55, t56, t57, t58, t59, t8);
    real_type t101 = zPosition_D_6(t54, t55, t56, t57, t58, t59, t8);
    result__[ 11  ] = t101 * t65 + t53 * t97 + t62 * t99 - LR__[5];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",12);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  gtocX_2burn::DadjointBCDx_numRows() const
  { return 12; }

  integer
  gtocX_2burn::DadjointBCDx_numCols() const
  { return 12; }

  integer
  gtocX_2burn::DadjointBCDx_nnz() const
  { return 72; }

  void
  gtocX_2burn::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 0   ; jIndex[ 4  ] = 4   ;
    iIndex[ 5  ] = 0   ; jIndex[ 5  ] = 5   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 1   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 1   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 1   ; jIndex[ 9  ] = 3   ;
    iIndex[ 10 ] = 1   ; jIndex[ 10 ] = 4   ;
    iIndex[ 11 ] = 1   ; jIndex[ 11 ] = 5   ;
    iIndex[ 12 ] = 2   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 2   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 2   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 2   ; jIndex[ 15 ] = 3   ;
    iIndex[ 16 ] = 2   ; jIndex[ 16 ] = 4   ;
    iIndex[ 17 ] = 2   ; jIndex[ 17 ] = 5   ;
    iIndex[ 18 ] = 3   ; jIndex[ 18 ] = 0   ;
    iIndex[ 19 ] = 3   ; jIndex[ 19 ] = 1   ;
    iIndex[ 20 ] = 3   ; jIndex[ 20 ] = 2   ;
    iIndex[ 21 ] = 3   ; jIndex[ 21 ] = 3   ;
    iIndex[ 22 ] = 3   ; jIndex[ 22 ] = 4   ;
    iIndex[ 23 ] = 3   ; jIndex[ 23 ] = 5   ;
    iIndex[ 24 ] = 4   ; jIndex[ 24 ] = 0   ;
    iIndex[ 25 ] = 4   ; jIndex[ 25 ] = 1   ;
    iIndex[ 26 ] = 4   ; jIndex[ 26 ] = 2   ;
    iIndex[ 27 ] = 4   ; jIndex[ 27 ] = 3   ;
    iIndex[ 28 ] = 4   ; jIndex[ 28 ] = 4   ;
    iIndex[ 29 ] = 4   ; jIndex[ 29 ] = 5   ;
    iIndex[ 30 ] = 5   ; jIndex[ 30 ] = 0   ;
    iIndex[ 31 ] = 5   ; jIndex[ 31 ] = 1   ;
    iIndex[ 32 ] = 5   ; jIndex[ 32 ] = 2   ;
    iIndex[ 33 ] = 5   ; jIndex[ 33 ] = 3   ;
    iIndex[ 34 ] = 5   ; jIndex[ 34 ] = 4   ;
    iIndex[ 35 ] = 5   ; jIndex[ 35 ] = 5   ;
    iIndex[ 36 ] = 6   ; jIndex[ 36 ] = 6   ;
    iIndex[ 37 ] = 6   ; jIndex[ 37 ] = 7   ;
    iIndex[ 38 ] = 6   ; jIndex[ 38 ] = 8   ;
    iIndex[ 39 ] = 6   ; jIndex[ 39 ] = 9   ;
    iIndex[ 40 ] = 6   ; jIndex[ 40 ] = 10  ;
    iIndex[ 41 ] = 6   ; jIndex[ 41 ] = 11  ;
    iIndex[ 42 ] = 7   ; jIndex[ 42 ] = 6   ;
    iIndex[ 43 ] = 7   ; jIndex[ 43 ] = 7   ;
    iIndex[ 44 ] = 7   ; jIndex[ 44 ] = 8   ;
    iIndex[ 45 ] = 7   ; jIndex[ 45 ] = 9   ;
    iIndex[ 46 ] = 7   ; jIndex[ 46 ] = 10  ;
    iIndex[ 47 ] = 7   ; jIndex[ 47 ] = 11  ;
    iIndex[ 48 ] = 8   ; jIndex[ 48 ] = 6   ;
    iIndex[ 49 ] = 8   ; jIndex[ 49 ] = 7   ;
    iIndex[ 50 ] = 8   ; jIndex[ 50 ] = 8   ;
    iIndex[ 51 ] = 8   ; jIndex[ 51 ] = 9   ;
    iIndex[ 52 ] = 8   ; jIndex[ 52 ] = 10  ;
    iIndex[ 53 ] = 8   ; jIndex[ 53 ] = 11  ;
    iIndex[ 54 ] = 9   ; jIndex[ 54 ] = 6   ;
    iIndex[ 55 ] = 9   ; jIndex[ 55 ] = 7   ;
    iIndex[ 56 ] = 9   ; jIndex[ 56 ] = 8   ;
    iIndex[ 57 ] = 9   ; jIndex[ 57 ] = 9   ;
    iIndex[ 58 ] = 9   ; jIndex[ 58 ] = 10  ;
    iIndex[ 59 ] = 9   ; jIndex[ 59 ] = 11  ;
    iIndex[ 60 ] = 10  ; jIndex[ 60 ] = 6   ;
    iIndex[ 61 ] = 10  ; jIndex[ 61 ] = 7   ;
    iIndex[ 62 ] = 10  ; jIndex[ 62 ] = 8   ;
    iIndex[ 63 ] = 10  ; jIndex[ 63 ] = 9   ;
    iIndex[ 64 ] = 10  ; jIndex[ 64 ] = 10  ;
    iIndex[ 65 ] = 10  ; jIndex[ 65 ] = 11  ;
    iIndex[ 66 ] = 11  ; jIndex[ 66 ] = 6   ;
    iIndex[ 67 ] = 11  ; jIndex[ 67 ] = 7   ;
    iIndex[ 68 ] = 11  ; jIndex[ 68 ] = 8   ;
    iIndex[ 69 ] = 11  ; jIndex[ 69 ] = 9   ;
    iIndex[ 70 ] = 11  ; jIndex[ 70 ] = 10  ;
    iIndex[ 71 ] = 11  ; jIndex[ 71 ] = 11  ;
  }

  void
  gtocX_2burn::DadjointBCDx_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t1   = OMEGA__[0];
    real_type t2   = XL__[0];
    real_type t3   = XL__[1];
    real_type t4   = XL__[2];
    real_type t5   = XL__[3];
    real_type t6   = XL__[4];
    real_type t7   = XL__[5];
    real_type t8   = ModelPars[5];
    real_type t9   = xPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = yPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = zPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14;
    real_type t17  = xPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = yPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t21  = zPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t17 * t1 + t19 * t11 + t21 * t14;
    real_type t23  = xPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = yPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = zPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t23 * t1 + t25 * t11 + t27 * t14;
    real_type t29  = xPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = yPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t33  = zPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t29 * t1 + t31 * t11 + t33 * t14;
    real_type t35  = xPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = yPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t39  = zPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t35 * t1 + t37 * t11 + t39 * t14;
    real_type t41  = xPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = yPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = zPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t41 * t1 + t43 * t11 + t45 * t14;
    result__[ 6   ] = result__[1];
    real_type t47  = xPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = yPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = zPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 7   ] = t47 * t1 + t49 * t11 + t51 * t14;
    real_type t53  = xPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = yPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t57  = zPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 8   ] = t53 * t1 + t55 * t11 + t57 * t14;
    real_type t59  = xPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t61  = yPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t63  = zPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 9   ] = t59 * t1 + t61 * t11 + t63 * t14;
    real_type t65  = xPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t67  = yPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t69  = zPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 10  ] = t65 * t1 + t67 * t11 + t69 * t14;
    real_type t71  = xPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t73  = yPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = zPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 11  ] = t71 * t1 + t73 * t11 + t75 * t14;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[8];
    real_type t77  = xPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t79  = yPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t81  = zPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 14  ] = t77 * t1 + t79 * t11 + t81 * t14;
    real_type t83  = xPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = yPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = zPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 15  ] = t83 * t1 + t85 * t11 + t87 * t14;
    real_type t89  = xPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = yPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = zPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 16  ] = t89 * t1 + t91 * t11 + t93 * t14;
    real_type t95  = xPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = yPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t99  = zPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 17  ] = t95 * t1 + t97 * t11 + t99 * t14;
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[9];
    result__[ 20  ] = result__[15];
    real_type t101 = xPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = yPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = zPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 21  ] = t101 * t1 + t103 * t11 + t105 * t14;
    real_type t107 = xPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = yPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t111 = zPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 22  ] = t107 * t1 + t109 * t11 + t111 * t14;
    real_type t113 = xPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t115 = yPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t117 = zPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 23  ] = t113 * t1 + t115 * t11 + t117 * t14;
    result__[ 24  ] = result__[4];
    result__[ 25  ] = result__[10];
    result__[ 26  ] = result__[16];
    result__[ 27  ] = result__[22];
    real_type t119 = xPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t121 = yPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t123 = zPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 28  ] = t119 * t1 + t121 * t11 + t123 * t14;
    real_type t125 = xPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t127 = yPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = zPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 29  ] = t125 * t1 + t127 * t11 + t129 * t14;
    result__[ 30  ] = result__[5];
    result__[ 31  ] = result__[11];
    result__[ 32  ] = result__[17];
    result__[ 33  ] = result__[23];
    result__[ 34  ] = result__[29];
    real_type t131 = xPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t133 = yPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t135 = zPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 35  ] = t131 * t1 + t133 * t11 + t135 * t14;
    real_type t137 = OMEGA__[3];
    real_type t138 = XR__[0];
    real_type t139 = XR__[1];
    real_type t140 = XR__[2];
    real_type t141 = XR__[3];
    real_type t142 = XR__[4];
    real_type t143 = XR__[5];
    real_type t144 = xPosition_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    real_type t146 = OMEGA__[4];
    real_type t147 = yPosition_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    real_type t149 = OMEGA__[5];
    real_type t150 = zPosition_D_1_1(t138, t139, t140, t141, t142, t143, t8);
    result__[ 36  ] = t144 * t137 + t147 * t146 + t150 * t149;
    real_type t152 = xPosition_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t154 = yPosition_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t156 = zPosition_D_1_2(t138, t139, t140, t141, t142, t143, t8);
    result__[ 37  ] = t152 * t137 + t154 * t146 + t156 * t149;
    real_type t158 = xPosition_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t160 = yPosition_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t162 = zPosition_D_1_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 38  ] = t158 * t137 + t160 * t146 + t162 * t149;
    real_type t164 = xPosition_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t166 = yPosition_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t168 = zPosition_D_1_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 39  ] = t164 * t137 + t166 * t146 + t168 * t149;
    real_type t170 = xPosition_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t172 = yPosition_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t174 = zPosition_D_1_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 40  ] = t170 * t137 + t172 * t146 + t174 * t149;
    real_type t176 = xPosition_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t178 = yPosition_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t180 = zPosition_D_1_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 41  ] = t176 * t137 + t178 * t146 + t180 * t149;
    result__[ 42  ] = result__[37];
    real_type t182 = xPosition_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t184 = yPosition_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    real_type t186 = zPosition_D_2_2(t138, t139, t140, t141, t142, t143, t8);
    result__[ 43  ] = t182 * t137 + t184 * t146 + t186 * t149;
    real_type t188 = xPosition_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t190 = yPosition_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t192 = zPosition_D_2_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 44  ] = t188 * t137 + t190 * t146 + t192 * t149;
    real_type t194 = xPosition_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t196 = yPosition_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t198 = zPosition_D_2_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 45  ] = t194 * t137 + t196 * t146 + t198 * t149;
    real_type t200 = xPosition_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t202 = yPosition_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t204 = zPosition_D_2_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 46  ] = t200 * t137 + t202 * t146 + t204 * t149;
    real_type t206 = xPosition_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t208 = yPosition_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t210 = zPosition_D_2_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 47  ] = t206 * t137 + t208 * t146 + t210 * t149;
    result__[ 48  ] = result__[38];
    result__[ 49  ] = result__[44];
    real_type t212 = xPosition_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t214 = yPosition_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    real_type t216 = zPosition_D_3_3(t138, t139, t140, t141, t142, t143, t8);
    result__[ 50  ] = t212 * t137 + t214 * t146 + t216 * t149;
    real_type t218 = xPosition_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t220 = yPosition_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t222 = zPosition_D_3_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 51  ] = t218 * t137 + t220 * t146 + t222 * t149;
    real_type t224 = xPosition_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t226 = yPosition_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t228 = zPosition_D_3_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 52  ] = t224 * t137 + t226 * t146 + t228 * t149;
    real_type t230 = xPosition_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t232 = yPosition_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t234 = zPosition_D_3_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 53  ] = t230 * t137 + t232 * t146 + t234 * t149;
    result__[ 54  ] = result__[39];
    result__[ 55  ] = result__[45];
    result__[ 56  ] = result__[51];
    real_type t236 = xPosition_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t238 = yPosition_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    real_type t240 = zPosition_D_4_4(t138, t139, t140, t141, t142, t143, t8);
    result__[ 57  ] = t236 * t137 + t238 * t146 + t240 * t149;
    real_type t242 = xPosition_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t244 = yPosition_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t246 = zPosition_D_4_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 58  ] = t242 * t137 + t244 * t146 + t246 * t149;
    real_type t248 = xPosition_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t250 = yPosition_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t252 = zPosition_D_4_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 59  ] = t248 * t137 + t250 * t146 + t252 * t149;
    result__[ 60  ] = result__[40];
    result__[ 61  ] = result__[46];
    result__[ 62  ] = result__[52];
    result__[ 63  ] = result__[58];
    real_type t254 = xPosition_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t256 = yPosition_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    real_type t258 = zPosition_D_5_5(t138, t139, t140, t141, t142, t143, t8);
    result__[ 64  ] = t254 * t137 + t256 * t146 + t258 * t149;
    real_type t260 = xPosition_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t262 = yPosition_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t264 = zPosition_D_5_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 65  ] = t260 * t137 + t262 * t146 + t264 * t149;
    result__[ 66  ] = result__[41];
    result__[ 67  ] = result__[47];
    result__[ 68  ] = result__[53];
    result__[ 69  ] = result__[59];
    result__[ 70  ] = result__[65];
    real_type t266 = xPosition_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t268 = yPosition_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    real_type t270 = zPosition_D_6_6(t138, t139, t140, t141, t142, t143, t8);
    result__[ 71  ] = t266 * t137 + t268 * t146 + t270 * t149;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DadjointBCDxp_sparse",72);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  gtocX_2burn::DadjointBCDp_numRows() const
  { return 12; }

  integer
  gtocX_2burn::DadjointBCDp_numCols() const
  { return 0; }

  integer
  gtocX_2burn::DadjointBCDp_nnz() const
  { return 0; }

  void
  gtocX_2burn::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  gtocX_2burn::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods.cc
