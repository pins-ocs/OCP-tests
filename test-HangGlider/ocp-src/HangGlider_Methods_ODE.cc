/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_ODE.cc                                      |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  HangGlider::rhs_ode_numEqns() const
  { return 4; }

  void
  HangGlider::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vx];
    result__[ 0   ] = t2 * t1;
    real_type t3   = X__[iX_vy];
    result__[ 1   ] = t3 * t1;
    real_type t6   = 1.0 / ModelPars[iM_m] * t1;
    real_type t7   = X__[iX_x];
    real_type t8   = v(t7, t2, t3);
    real_type t9   = 1.0 / t8;
    real_type t10  = U__[iU_cL];
    real_type t11  = t10 * t10;
    real_type t16  = Dfun(t7, t2, t3);
    real_type t17  = t16 * (ModelPars[iM_c1] * t11 + ModelPars[iM_c0]);
    real_type t19  = Lfun(t7, t2, t3);
    real_type t20  = t19 * t10;
    real_type t21  = w(t7, t3);
    result__[ 2   ] = (-t2 * t17 - t21 * t20) * t9 * t6;
    result__[ 3   ] = (-t21 * t17 + t2 * t20) * t9 * t6 - ModelPars[iM_g] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::Drhs_odeDx_numRows() const
  { return 4; }

  integer
  HangGlider::Drhs_odeDx_numCols() const
  { return 4; }

  integer
  HangGlider::Drhs_odeDx_nnz() const
  { return 8; }

  void
  HangGlider::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = P__[iP_T];
    result__[ 1   ] = result__[0];
    real_type t3   = 1.0 / ModelPars[iM_m] * result__[1];
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_vx];
    real_type t6   = X__[iX_vy];
    real_type t7   = v(t4, t5, t6);
    real_type t8   = t7 * t7;
    real_type t9   = 1.0 / t8;
    real_type t11  = U__[iU_cL];
    real_type t12  = t11 * t11;
    real_type t15  = t12 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t16  = Dfun(t4, t5, t6);
    real_type t17  = t16 * t15;
    real_type t19  = Lfun(t4, t5, t6);
    real_type t20  = t19 * t11;
    real_type t21  = w(t4, t6);
    real_type t24  = (-t17 * t5 - t20 * t21) * t9;
    real_type t25  = v_D_1(t4, t5, t6);
    real_type t28  = 1.0 / t7;
    real_type t29  = Dfun_D_1(t4, t5, t6);
    real_type t30  = t29 * t15;
    real_type t32  = Lfun_D_1(t4, t5, t6);
    real_type t33  = t32 * t11;
    real_type t35  = w_D_1(t4, t6);
    result__[ 2   ] = -t25 * t24 * t3 + (-t20 * t35 - t21 * t33 - t30 * t5) * t28 * t3;
    real_type t40  = v_D_2(t4, t5, t6);
    real_type t43  = Dfun_D_2(t4, t5, t6);
    real_type t44  = t43 * t15;
    real_type t46  = Lfun_D_2(t4, t5, t6);
    real_type t47  = t46 * t11;
    result__[ 3   ] = -t40 * t24 * t3 + (-t21 * t47 - t44 * t5 - t17) * t28 * t3;
    real_type t52  = v_D_3(t4, t5, t6);
    real_type t55  = Dfun_D_3(t4, t5, t6);
    real_type t56  = t55 * t15;
    real_type t58  = Lfun_D_3(t4, t5, t6);
    real_type t59  = t58 * t11;
    real_type t61  = w_D_2(t4, t6);
    result__[ 4   ] = -t52 * t24 * t3 + (-t20 * t61 - t21 * t59 - t5 * t56) * t28 * t3;
    real_type t69  = (-t17 * t21 + t20 * t5) * t9;
    result__[ 5   ] = -t25 * t69 * t3 + (-t17 * t35 - t21 * t30 + t33 * t5) * t28 * t3;
    result__[ 6   ] = -t40 * t69 * t3 + (-t21 * t44 + t47 * t5 + t20) * t28 * t3;
    result__[ 7   ] = -t52 * t69 * t3 + (-t17 * t61 - t21 * t56 + t5 * t59) * t28 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::Drhs_odeDp_numRows() const
  { return 4; }

  integer
  HangGlider::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  HangGlider::Drhs_odeDp_nnz() const
  { return 4; }

  void
  HangGlider::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_vx];
    result__[ 1   ] = X__[iX_vy];
    real_type t3   = X__[iX_x];
    real_type t1   = result__[0];
    real_type t2   = result__[1];
    real_type t4   = v(t3, t1, t2);
    real_type t6   = 1.0 / t4 / ModelPars[iM_m];
    real_type t8   = U__[iU_cL];
    real_type t9   = t8 * t8;
    real_type t13  = Dfun(t3, t1, t2);
    real_type t14  = t13 * (t9 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t16  = Lfun(t3, t1, t2);
    real_type t17  = t16 * t8;
    real_type t18  = w(t3, t2);
    result__[ 2   ] = t6 * (-t14 * t1 - t18 * t17);
    result__[ 3   ] = t6 * (t17 * t1 - t18 * t14) - ModelPars[iM_g];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::Drhs_odeDu_numRows() const
  { return 4; }

  integer
  HangGlider::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  HangGlider::Drhs_odeDu_nnz() const
  { return 2; }

  void
  HangGlider::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = P__[iP_T] / ModelPars[iM_m];
    real_type t5   = X__[iX_x];
    real_type t6   = X__[iX_vx];
    real_type t7   = X__[iX_vy];
    real_type t8   = v(t5, t6, t7);
    real_type t9   = 1.0 / t8;
    real_type t12  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t13  = Dfun(t5, t6, t7);
    real_type t17  = Lfun(t5, t6, t7);
    real_type t18  = w(t5, t7);
    result__[ 0   ] = (-2 * t6 * t13 * t12 - t18 * t17) * t9 * t4;
    result__[ 1   ] = (-2 * t18 * t13 * t12 + t6 * t17) * t9 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 2, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  HangGlider::A_numRows() const
  { return 4; }

  integer
  HangGlider::A_numCols() const
  { return 4; }

  integer
  HangGlider::A_nnz() const
  { return 4; }

  void
  HangGlider::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: HangGlider_Methods_ODE.cc
