/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods.cc                                    |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
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


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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

  integer
  gtocX_2burn_pars::boundaryConditions_numEqns() const
  { return 6; }

  void
  gtocX_2burn_pars::boundaryConditions_eval(
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
    real_type t1   = P__[0];
    real_type t2   = XL__[0];
    real_type t3   = XL__[1];
    real_type t4   = P__[1];
    real_type t5   = P__[2];
    real_type t6   = XL__[2];
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
    real_type t18  = xPosition(t1, t15, t16, t4, t5, t17, t7);
    real_type t19  = ModelPars[1];
    real_type t20  = X_end(t19);
    result__[ 3   ] = t18 - t20;
    real_type t21  = yPosition(t1, t15, t16, t4, t5, t17, t7);
    real_type t22  = Y_end(t19);
    result__[ 4   ] = t21 - t22;
    real_type t23  = zPosition(t1, t15, t16, t4, t5, t17, t7);
    real_type t24  = Z_end(t19);
    result__[ 5   ] = t23 - t24;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DboundaryConditionsDx_numRows() const
  { return 6; }

  integer
  gtocX_2burn_pars::DboundaryConditionsDx_numCols() const
  { return 6; }

  integer
  gtocX_2burn_pars::DboundaryConditionsDx_nnz() const
  { return 18; }

  void
  gtocX_2burn_pars::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 3   ;
    iIndex[ 10 ] = 3   ; jIndex[ 10 ] = 4   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 5   ;
    iIndex[ 12 ] = 4   ; jIndex[ 12 ] = 3   ;
    iIndex[ 13 ] = 4   ; jIndex[ 13 ] = 4   ;
    iIndex[ 14 ] = 4   ; jIndex[ 14 ] = 5   ;
    iIndex[ 15 ] = 5   ; jIndex[ 15 ] = 3   ;
    iIndex[ 16 ] = 5   ; jIndex[ 16 ] = 4   ;
    iIndex[ 17 ] = 5   ; jIndex[ 17 ] = 5   ;
  }

  void
  gtocX_2burn_pars::DboundaryConditionsDx_sparse(
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
    real_type t1   = P__[0];
    real_type t2   = XL__[0];
    real_type t3   = XL__[1];
    real_type t4   = P__[1];
    real_type t5   = P__[2];
    real_type t6   = XL__[2];
    real_type t7   = ModelPars[5];
    result__[ 0   ] = xPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 1   ] = xPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 2   ] = xPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 3   ] = yPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 4   ] = yPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 5   ] = yPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    result__[ 6   ] = zPosition_D_2(t1, t2, t3, t4, t5, t6, t7);
    result__[ 7   ] = zPosition_D_3(t1, t2, t3, t4, t5, t6, t7);
    result__[ 8   ] = zPosition_D_6(t1, t2, t3, t4, t5, t6, t7);
    real_type t8   = XR__[0];
    real_type t9   = XR__[1];
    real_type t10  = XR__[2];
    result__[ 9   ] = xPosition_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 10  ] = xPosition_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 11  ] = xPosition_D_6(t1, t8, t9, t4, t5, t10, t7);
    result__[ 12  ] = yPosition_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 13  ] = yPosition_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 14  ] = yPosition_D_6(t1, t8, t9, t4, t5, t10, t7);
    result__[ 15  ] = zPosition_D_2(t1, t8, t9, t4, t5, t10, t7);
    result__[ 16  ] = zPosition_D_3(t1, t8, t9, t4, t5, t10, t7);
    result__[ 17  ] = zPosition_D_6(t1, t8, t9, t4, t5, t10, t7);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",18);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DboundaryConditionsDp_numRows() const
  { return 6; }

  integer
  gtocX_2burn_pars::DboundaryConditionsDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DboundaryConditionsDp_nnz() const
  { return 18; }

  void
  gtocX_2burn_pars::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 0   ;
    iIndex[ 10 ] = 3   ; jIndex[ 10 ] = 1   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 2   ;
    iIndex[ 12 ] = 4   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 4   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 4   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 5   ; jIndex[ 15 ] = 0   ;
    iIndex[ 16 ] = 5   ; jIndex[ 16 ] = 1   ;
    iIndex[ 17 ] = 5   ; jIndex[ 17 ] = 2   ;
  }

  void
  gtocX_2burn_pars::DboundaryConditionsDp_sparse(
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
    real_type t1   = P__[0];
    real_type t2   = XL__[0];
    real_type t3   = XL__[1];
    real_type t4   = P__[1];
    real_type t5   = P__[2];
    real_type t6   = XL__[2];
    real_type t7   = ModelPars[5];
    result__[ 0   ] = xPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 1   ] = xPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 2   ] = xPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 3   ] = yPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 4   ] = yPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 5   ] = yPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    result__[ 6   ] = zPosition_D_1(t1, t2, t3, t4, t5, t6, t7);
    result__[ 7   ] = zPosition_D_4(t1, t2, t3, t4, t5, t6, t7);
    result__[ 8   ] = zPosition_D_5(t1, t2, t3, t4, t5, t6, t7);
    real_type t8   = XR__[0];
    real_type t9   = XR__[1];
    real_type t10  = XR__[2];
    result__[ 9   ] = xPosition_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 10  ] = xPosition_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 11  ] = xPosition_D_5(t1, t8, t9, t4, t5, t10, t7);
    result__[ 12  ] = yPosition_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 13  ] = yPosition_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 14  ] = yPosition_D_5(t1, t8, t9, t4, t5, t10, t7);
    result__[ 15  ] = zPosition_D_1(t1, t8, t9, t4, t5, t10, t7);
    result__[ 16  ] = zPosition_D_4(t1, t8, t9, t4, t5, t10, t7);
    result__[ 17  ] = zPosition_D_5(t1, t8, t9, t4, t5, t10, t7);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",18);
    #endif

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::adjointBC_numEqns() const
  { return 9; }

  void
  gtocX_2burn_pars::adjointBC_eval(
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
    real_type t2   = P__[0];
    real_type t3   = XL__[0];
    real_type t4   = XL__[1];
    real_type t5   = P__[1];
    real_type t6   = P__[2];
    real_type t7   = XL__[2];
    real_type t8   = ModelPars[5];
    real_type t9   = xPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = yPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = zPosition_D_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14 + LL__[0];
    real_type t18  = xPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t20  = yPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = zPosition_D_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t18 * t1 + t20 * t11 + t22 * t14 + LL__[1];
    real_type t25  = xPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = yPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t29  = zPosition_D_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t25 * t1 + t27 * t11 + t29 * t14 + LL__[2];
    real_type t32  = OMEGA__[3];
    real_type t33  = XR__[0];
    real_type t34  = XR__[1];
    real_type t35  = XR__[2];
    real_type t36  = xPosition_D_2(t2, t33, t34, t5, t6, t35, t8);
    real_type t38  = OMEGA__[4];
    real_type t39  = yPosition_D_2(t2, t33, t34, t5, t6, t35, t8);
    real_type t41  = OMEGA__[5];
    real_type t42  = zPosition_D_2(t2, t33, t34, t5, t6, t35, t8);
    result__[ 3   ] = t36 * t32 + t39 * t38 + t42 * t41 - LR__[0];
    real_type t45  = xPosition_D_3(t2, t33, t34, t5, t6, t35, t8);
    real_type t47  = yPosition_D_3(t2, t33, t34, t5, t6, t35, t8);
    real_type t49  = zPosition_D_3(t2, t33, t34, t5, t6, t35, t8);
    result__[ 4   ] = t45 * t32 + t47 * t38 + t49 * t41 - LR__[1];
    real_type t52  = xPosition_D_6(t2, t33, t34, t5, t6, t35, t8);
    real_type t54  = yPosition_D_6(t2, t33, t34, t5, t6, t35, t8);
    real_type t56  = zPosition_D_6(t2, t33, t34, t5, t6, t35, t8);
    result__[ 5   ] = t52 * t32 + t54 * t38 + t56 * t41 - LR__[2];
    real_type t59  = xPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t61  = yPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t63  = zPosition_D_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t65  = xPosition_D_1(t2, t33, t34, t5, t6, t35, t8);
    real_type t67  = yPosition_D_1(t2, t33, t34, t5, t6, t35, t8);
    real_type t69  = zPosition_D_1(t2, t33, t34, t5, t6, t35, t8);
    result__[ 6   ] = t59 * t1 + t61 * t11 + t63 * t14 + t65 * t32 + t67 * t38 + t69 * t41;
    real_type t71  = xPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t73  = yPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = zPosition_D_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t77  = xPosition_D_4(t2, t33, t34, t5, t6, t35, t8);
    real_type t79  = yPosition_D_4(t2, t33, t34, t5, t6, t35, t8);
    real_type t81  = zPosition_D_4(t2, t33, t34, t5, t6, t35, t8);
    result__[ 7   ] = t71 * t1 + t73 * t11 + t75 * t14 + t77 * t32 + t79 * t38 + t81 * t41;
    real_type t83  = xPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = yPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = zPosition_D_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t89  = xPosition_D_5(t2, t33, t34, t5, t6, t35, t8);
    real_type t91  = yPosition_D_5(t2, t33, t34, t5, t6, t35, t8);
    real_type t93  = zPosition_D_5(t2, t33, t34, t5, t6, t35, t8);
    result__[ 8   ] = t83 * t1 + t85 * t11 + t87 * t14 + t89 * t32 + t91 * t38 + t93 * t41;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",9);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DadjointBCDx_numRows() const
  { return 9; }

  integer
  gtocX_2burn_pars::DadjointBCDx_numCols() const
  { return 6; }

  integer
  gtocX_2burn_pars::DadjointBCDx_nnz() const
  { return 36; }

  void
  gtocX_2burn_pars::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 3   ;
    iIndex[ 10 ] = 3   ; jIndex[ 10 ] = 4   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 5   ;
    iIndex[ 12 ] = 4   ; jIndex[ 12 ] = 3   ;
    iIndex[ 13 ] = 4   ; jIndex[ 13 ] = 4   ;
    iIndex[ 14 ] = 4   ; jIndex[ 14 ] = 5   ;
    iIndex[ 15 ] = 5   ; jIndex[ 15 ] = 3   ;
    iIndex[ 16 ] = 5   ; jIndex[ 16 ] = 4   ;
    iIndex[ 17 ] = 5   ; jIndex[ 17 ] = 5   ;
    iIndex[ 18 ] = 6   ; jIndex[ 18 ] = 0   ;
    iIndex[ 19 ] = 6   ; jIndex[ 19 ] = 1   ;
    iIndex[ 20 ] = 6   ; jIndex[ 20 ] = 2   ;
    iIndex[ 21 ] = 6   ; jIndex[ 21 ] = 3   ;
    iIndex[ 22 ] = 6   ; jIndex[ 22 ] = 4   ;
    iIndex[ 23 ] = 6   ; jIndex[ 23 ] = 5   ;
    iIndex[ 24 ] = 7   ; jIndex[ 24 ] = 0   ;
    iIndex[ 25 ] = 7   ; jIndex[ 25 ] = 1   ;
    iIndex[ 26 ] = 7   ; jIndex[ 26 ] = 2   ;
    iIndex[ 27 ] = 7   ; jIndex[ 27 ] = 3   ;
    iIndex[ 28 ] = 7   ; jIndex[ 28 ] = 4   ;
    iIndex[ 29 ] = 7   ; jIndex[ 29 ] = 5   ;
    iIndex[ 30 ] = 8   ; jIndex[ 30 ] = 0   ;
    iIndex[ 31 ] = 8   ; jIndex[ 31 ] = 1   ;
    iIndex[ 32 ] = 8   ; jIndex[ 32 ] = 2   ;
    iIndex[ 33 ] = 8   ; jIndex[ 33 ] = 3   ;
    iIndex[ 34 ] = 8   ; jIndex[ 34 ] = 4   ;
    iIndex[ 35 ] = 8   ; jIndex[ 35 ] = 5   ;
  }

  void
  gtocX_2burn_pars::DadjointBCDx_sparse(
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
    real_type t2   = P__[0];
    real_type t3   = XL__[0];
    real_type t4   = XL__[1];
    real_type t5   = P__[1];
    real_type t6   = P__[2];
    real_type t7   = XL__[2];
    real_type t8   = ModelPars[5];
    real_type t9   = xPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = yPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = zPosition_D_2_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14;
    real_type t17  = xPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = yPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t21  = zPosition_D_2_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t17 * t1 + t19 * t11 + t21 * t14;
    real_type t23  = xPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = yPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = zPosition_D_2_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t23 * t1 + t25 * t11 + t27 * t14;
    result__[ 3   ] = result__[1];
    real_type t29  = xPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = yPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t33  = zPosition_D_3_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t29 * t1 + t31 * t11 + t33 * t14;
    real_type t35  = xPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = yPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t39  = zPosition_D_3_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t35 * t1 + t37 * t11 + t39 * t14;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t41  = xPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = yPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = zPosition_D_6_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 8   ] = t41 * t1 + t43 * t11 + t45 * t14;
    real_type t47  = OMEGA__[3];
    real_type t48  = XR__[0];
    real_type t49  = XR__[1];
    real_type t50  = XR__[2];
    real_type t51  = xPosition_D_2_2(t2, t48, t49, t5, t6, t50, t8);
    real_type t53  = OMEGA__[4];
    real_type t54  = yPosition_D_2_2(t2, t48, t49, t5, t6, t50, t8);
    real_type t56  = OMEGA__[5];
    real_type t57  = zPosition_D_2_2(t2, t48, t49, t5, t6, t50, t8);
    result__[ 9   ] = t51 * t47 + t54 * t53 + t57 * t56;
    real_type t59  = xPosition_D_2_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t61  = yPosition_D_2_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t63  = zPosition_D_2_3(t2, t48, t49, t5, t6, t50, t8);
    result__[ 10  ] = t59 * t47 + t61 * t53 + t63 * t56;
    real_type t65  = xPosition_D_2_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t67  = yPosition_D_2_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t69  = zPosition_D_2_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 11  ] = t65 * t47 + t67 * t53 + t69 * t56;
    result__[ 12  ] = result__[10];
    real_type t71  = xPosition_D_3_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t73  = yPosition_D_3_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t75  = zPosition_D_3_3(t2, t48, t49, t5, t6, t50, t8);
    result__[ 13  ] = t71 * t47 + t73 * t53 + t75 * t56;
    real_type t77  = xPosition_D_3_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t79  = yPosition_D_3_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t81  = zPosition_D_3_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 14  ] = t77 * t47 + t79 * t53 + t81 * t56;
    result__[ 15  ] = result__[11];
    result__[ 16  ] = result__[14];
    real_type t83  = xPosition_D_6_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t85  = yPosition_D_6_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t87  = zPosition_D_6_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 17  ] = t83 * t47 + t85 * t53 + t87 * t56;
    real_type t89  = xPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = yPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = zPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 18  ] = t89 * t1 + t91 * t11 + t93 * t14;
    real_type t95  = xPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = yPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t99  = zPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 19  ] = t95 * t1 + t97 * t11 + t99 * t14;
    real_type t101 = xPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = yPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = zPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 20  ] = t101 * t1 + t103 * t11 + t105 * t14;
    real_type t107 = xPosition_D_1_2(t2, t48, t49, t5, t6, t50, t8);
    real_type t109 = yPosition_D_1_2(t2, t48, t49, t5, t6, t50, t8);
    real_type t111 = zPosition_D_1_2(t2, t48, t49, t5, t6, t50, t8);
    result__[ 21  ] = t107 * t47 + t109 * t53 + t111 * t56;
    real_type t113 = xPosition_D_1_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t115 = yPosition_D_1_3(t2, t48, t49, t5, t6, t50, t8);
    real_type t117 = zPosition_D_1_3(t2, t48, t49, t5, t6, t50, t8);
    result__[ 22  ] = t113 * t47 + t115 * t53 + t117 * t56;
    real_type t119 = xPosition_D_1_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t121 = yPosition_D_1_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t123 = zPosition_D_1_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 23  ] = t119 * t47 + t121 * t53 + t123 * t56;
    real_type t125 = xPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t127 = yPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = zPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 24  ] = t125 * t1 + t127 * t11 + t129 * t14;
    real_type t131 = xPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t133 = yPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t135 = zPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 25  ] = t131 * t1 + t133 * t11 + t135 * t14;
    real_type t137 = xPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t139 = yPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t141 = zPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 26  ] = t1 * t137 + t11 * t139 + t14 * t141;
    real_type t143 = xPosition_D_2_4(t2, t48, t49, t5, t6, t50, t8);
    real_type t145 = yPosition_D_2_4(t2, t48, t49, t5, t6, t50, t8);
    real_type t147 = zPosition_D_2_4(t2, t48, t49, t5, t6, t50, t8);
    result__[ 27  ] = t143 * t47 + t145 * t53 + t147 * t56;
    real_type t149 = xPosition_D_3_4(t2, t48, t49, t5, t6, t50, t8);
    real_type t151 = yPosition_D_3_4(t2, t48, t49, t5, t6, t50, t8);
    real_type t153 = zPosition_D_3_4(t2, t48, t49, t5, t6, t50, t8);
    result__[ 28  ] = t149 * t47 + t151 * t53 + t153 * t56;
    real_type t155 = xPosition_D_4_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t157 = yPosition_D_4_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t159 = zPosition_D_4_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 29  ] = t155 * t47 + t157 * t53 + t159 * t56;
    real_type t161 = xPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t163 = yPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t165 = zPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 30  ] = t1 * t161 + t11 * t163 + t14 * t165;
    real_type t167 = xPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t169 = yPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t171 = zPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 31  ] = t1 * t167 + t11 * t169 + t14 * t171;
    real_type t173 = xPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t175 = yPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t177 = zPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 32  ] = t1 * t173 + t11 * t175 + t14 * t177;
    real_type t179 = xPosition_D_2_5(t2, t48, t49, t5, t6, t50, t8);
    real_type t181 = yPosition_D_2_5(t2, t48, t49, t5, t6, t50, t8);
    real_type t183 = zPosition_D_2_5(t2, t48, t49, t5, t6, t50, t8);
    result__[ 33  ] = t179 * t47 + t181 * t53 + t183 * t56;
    real_type t185 = xPosition_D_3_5(t2, t48, t49, t5, t6, t50, t8);
    real_type t187 = yPosition_D_3_5(t2, t48, t49, t5, t6, t50, t8);
    real_type t189 = zPosition_D_3_5(t2, t48, t49, t5, t6, t50, t8);
    result__[ 34  ] = t185 * t47 + t187 * t53 + t189 * t56;
    real_type t191 = xPosition_D_5_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t193 = yPosition_D_5_6(t2, t48, t49, t5, t6, t50, t8);
    real_type t195 = zPosition_D_5_6(t2, t48, t49, t5, t6, t50, t8);
    result__[ 35  ] = t191 * t47 + t193 * t53 + t195 * t56;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DadjointBCDxp_sparse",36);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DadjointBCDp_numRows() const
  { return 9; }

  integer
  gtocX_2burn_pars::DadjointBCDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DadjointBCDp_nnz() const
  { return 27; }

  void
  gtocX_2burn_pars::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 0   ;
    iIndex[ 10 ] = 3   ; jIndex[ 10 ] = 1   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 2   ;
    iIndex[ 12 ] = 4   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 4   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 4   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 5   ; jIndex[ 15 ] = 0   ;
    iIndex[ 16 ] = 5   ; jIndex[ 16 ] = 1   ;
    iIndex[ 17 ] = 5   ; jIndex[ 17 ] = 2   ;
    iIndex[ 18 ] = 6   ; jIndex[ 18 ] = 0   ;
    iIndex[ 19 ] = 6   ; jIndex[ 19 ] = 1   ;
    iIndex[ 20 ] = 6   ; jIndex[ 20 ] = 2   ;
    iIndex[ 21 ] = 7   ; jIndex[ 21 ] = 0   ;
    iIndex[ 22 ] = 7   ; jIndex[ 22 ] = 1   ;
    iIndex[ 23 ] = 7   ; jIndex[ 23 ] = 2   ;
    iIndex[ 24 ] = 8   ; jIndex[ 24 ] = 0   ;
    iIndex[ 25 ] = 8   ; jIndex[ 25 ] = 1   ;
    iIndex[ 26 ] = 8   ; jIndex[ 26 ] = 2   ;
  }

  void
  gtocX_2burn_pars::DadjointBCDp_sparse(
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
    real_type t2   = P__[0];
    real_type t3   = XL__[0];
    real_type t4   = XL__[1];
    real_type t5   = P__[1];
    real_type t6   = P__[2];
    real_type t7   = XL__[2];
    real_type t8   = ModelPars[5];
    real_type t9   = xPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t11  = OMEGA__[1];
    real_type t12  = yPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    real_type t14  = OMEGA__[2];
    real_type t15  = zPosition_D_1_2(t2, t3, t4, t5, t6, t7, t8);
    result__[ 0   ] = t9 * t1 + t12 * t11 + t15 * t14;
    real_type t17  = xPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = yPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t21  = zPosition_D_2_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 1   ] = t17 * t1 + t19 * t11 + t21 * t14;
    real_type t23  = xPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = yPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t27  = zPosition_D_2_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 2   ] = t23 * t1 + t25 * t11 + t27 * t14;
    real_type t29  = xPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = yPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    real_type t33  = zPosition_D_1_3(t2, t3, t4, t5, t6, t7, t8);
    result__[ 3   ] = t29 * t1 + t31 * t11 + t33 * t14;
    real_type t35  = xPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = yPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t39  = zPosition_D_3_4(t2, t3, t4, t5, t6, t7, t8);
    result__[ 4   ] = t35 * t1 + t37 * t11 + t39 * t14;
    real_type t41  = xPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = yPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = zPosition_D_3_5(t2, t3, t4, t5, t6, t7, t8);
    result__[ 5   ] = t41 * t1 + t43 * t11 + t45 * t14;
    real_type t47  = xPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = yPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = zPosition_D_1_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 6   ] = t47 * t1 + t49 * t11 + t51 * t14;
    real_type t53  = xPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = yPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t57  = zPosition_D_4_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 7   ] = t53 * t1 + t55 * t11 + t57 * t14;
    real_type t59  = xPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t61  = yPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    real_type t63  = zPosition_D_5_6(t2, t3, t4, t5, t6, t7, t8);
    result__[ 8   ] = t59 * t1 + t61 * t11 + t63 * t14;
    real_type t65  = OMEGA__[3];
    real_type t66  = XR__[0];
    real_type t67  = XR__[1];
    real_type t68  = XR__[2];
    real_type t69  = xPosition_D_1_2(t2, t66, t67, t5, t6, t68, t8);
    real_type t71  = OMEGA__[4];
    real_type t72  = yPosition_D_1_2(t2, t66, t67, t5, t6, t68, t8);
    real_type t74  = OMEGA__[5];
    real_type t75  = zPosition_D_1_2(t2, t66, t67, t5, t6, t68, t8);
    result__[ 9   ] = t69 * t65 + t72 * t71 + t75 * t74;
    real_type t77  = xPosition_D_2_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t79  = yPosition_D_2_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t81  = zPosition_D_2_4(t2, t66, t67, t5, t6, t68, t8);
    result__[ 10  ] = t77 * t65 + t79 * t71 + t81 * t74;
    real_type t83  = xPosition_D_2_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t85  = yPosition_D_2_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t87  = zPosition_D_2_5(t2, t66, t67, t5, t6, t68, t8);
    result__[ 11  ] = t83 * t65 + t85 * t71 + t87 * t74;
    real_type t89  = xPosition_D_1_3(t2, t66, t67, t5, t6, t68, t8);
    real_type t91  = yPosition_D_1_3(t2, t66, t67, t5, t6, t68, t8);
    real_type t93  = zPosition_D_1_3(t2, t66, t67, t5, t6, t68, t8);
    result__[ 12  ] = t89 * t65 + t91 * t71 + t93 * t74;
    real_type t95  = xPosition_D_3_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t97  = yPosition_D_3_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t99  = zPosition_D_3_4(t2, t66, t67, t5, t6, t68, t8);
    result__[ 13  ] = t95 * t65 + t97 * t71 + t99 * t74;
    real_type t101 = xPosition_D_3_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t103 = yPosition_D_3_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t105 = zPosition_D_3_5(t2, t66, t67, t5, t6, t68, t8);
    result__[ 14  ] = t101 * t65 + t103 * t71 + t105 * t74;
    real_type t107 = xPosition_D_1_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t109 = yPosition_D_1_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t111 = zPosition_D_1_6(t2, t66, t67, t5, t6, t68, t8);
    result__[ 15  ] = t107 * t65 + t109 * t71 + t111 * t74;
    real_type t113 = xPosition_D_4_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t115 = yPosition_D_4_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t117 = zPosition_D_4_6(t2, t66, t67, t5, t6, t68, t8);
    result__[ 16  ] = t113 * t65 + t115 * t71 + t117 * t74;
    real_type t119 = xPosition_D_5_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t121 = yPosition_D_5_6(t2, t66, t67, t5, t6, t68, t8);
    real_type t123 = zPosition_D_5_6(t2, t66, t67, t5, t6, t68, t8);
    result__[ 17  ] = t119 * t65 + t121 * t71 + t123 * t74;
    real_type t125 = xPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t127 = yPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = zPosition_D_1_1(t2, t3, t4, t5, t6, t7, t8);
    real_type t131 = xPosition_D_1_1(t2, t66, t67, t5, t6, t68, t8);
    real_type t133 = yPosition_D_1_1(t2, t66, t67, t5, t6, t68, t8);
    real_type t135 = zPosition_D_1_1(t2, t66, t67, t5, t6, t68, t8);
    result__[ 18  ] = t125 * t1 + t127 * t11 + t129 * t14 + t131 * t65 + t133 * t71 + t135 * t74;
    real_type t137 = xPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t139 = yPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t141 = zPosition_D_1_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t143 = xPosition_D_1_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t145 = yPosition_D_1_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t147 = zPosition_D_1_4(t2, t66, t67, t5, t6, t68, t8);
    result__[ 19  ] = t1 * t137 + t11 * t139 + t14 * t141 + t143 * t65 + t145 * t71 + t147 * t74;
    real_type t149 = xPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t151 = yPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t153 = zPosition_D_1_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t155 = xPosition_D_1_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t157 = yPosition_D_1_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t159 = zPosition_D_1_5(t2, t66, t67, t5, t6, t68, t8);
    result__[ 20  ] = t149 * t1 + t151 * t11 + t153 * t14 + t155 * t65 + t157 * t71 + t159 * t74;
    result__[ 21  ] = result__[19];
    real_type t161 = xPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t163 = yPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t165 = zPosition_D_4_4(t2, t3, t4, t5, t6, t7, t8);
    real_type t167 = xPosition_D_4_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t169 = yPosition_D_4_4(t2, t66, t67, t5, t6, t68, t8);
    real_type t171 = zPosition_D_4_4(t2, t66, t67, t5, t6, t68, t8);
    result__[ 22  ] = t1 * t161 + t11 * t163 + t14 * t165 + t167 * t65 + t169 * t71 + t171 * t74;
    real_type t173 = xPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t175 = yPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t177 = zPosition_D_4_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t179 = xPosition_D_4_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t181 = yPosition_D_4_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t183 = zPosition_D_4_5(t2, t66, t67, t5, t6, t68, t8);
    result__[ 23  ] = t1 * t173 + t11 * t175 + t14 * t177 + t179 * t65 + t181 * t71 + t183 * t74;
    result__[ 24  ] = result__[20];
    result__[ 25  ] = result__[23];
    real_type t185 = xPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t187 = yPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t189 = zPosition_D_5_5(t2, t3, t4, t5, t6, t7, t8);
    real_type t191 = xPosition_D_5_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t193 = yPosition_D_5_5(t2, t66, t67, t5, t6, t68, t8);
    real_type t195 = zPosition_D_5_5(t2, t66, t67, t5, t6, t68, t8);
    result__[ 26  ] = t185 * t1 + t187 * t11 + t189 * t14 + t191 * t65 + t193 * t71 + t195 * t74;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DadjointBCDxp_sparse",27);
    #endif
  }

}

// EOF: gtocX_2burn_pars_Methods.cc
