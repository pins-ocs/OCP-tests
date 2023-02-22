/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Crossroad::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Crossroad::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = jerkControl(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Crossroad::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = Tpositive(-X__[iX_Ts]);
    real_type t4   = X__[iX_a] * X__[iX_a];
    real_type t6   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t9   = X__[iX_v];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t10;
    real_type t13  = kappa(X__[iX_s]);
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t21  = AccBound(1.0 / t6 * t4 + 1.0 / t17 * t14 * t11 - 1);
    real_type t22  = VelBound_min(-t9);
    real_type t25  = VelBound_max(t9 - ModelPars[iM_v_max]);
    real_type result__ = t2 + t21 + t22 + t25;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JPxpu_numEqns() const { return 5; }

  void
  Crossroad::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JUxpu_numEqns() const { return 5; }

  void
  Crossroad::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = ALIAS_jerkControl_D_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LTxpu_numEqns() const { return 5; }

  void
  Crossroad::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_AccBound_D(t16 * t12 * t9 + t5 * t2 - 1);
    real_type t22  = kappa_D(t10);
    result__[ 0   ] = 2 * t22 * t16 * t11 * t9 * t19;
    real_type t30  = ALIAS_VelBound_min_D(-t7);
    real_type t33  = ALIAS_VelBound_max_D(t7 - ModelPars[iM_v_max]);
    result__[ 1   ] = 4 * t16 * t12 * t8 * t7 * t19 - t30 + t33;
    result__[ 2   ] = 2 * t5 * t1 * t19;
    real_type t37  = ALIAS_Tpositive_D(-X__[iX_Ts]);
    result__[ 3   ] = -t37;
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LTargs_numEqns() const { return 4; }

  void
  Crossroad::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_Ts];
    real_type t3   = X__[iX_a] * X__[iX_a];
    real_type t5   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t8   = X__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t12  = kappa(X__[iX_s]);
    real_type t13  = t12 * t12;
    real_type t16  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    result__[ 1   ] = 1.0 / t5 * t3 + 1.0 / t16 * t13 * t10 - 1;
    result__[ 2   ] = -t8;
    result__[ 3   ] = t8 - ModelPars[iM_v_max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::D2JPD2xpu_numRows() const { return 5; }
  integer Crossroad::D2JPD2xpu_numCols() const { return 5; }
  integer Crossroad::D2JPD2xpu_nnz()     const { return 0; }

  void
  Crossroad::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::D2LTD2xpu_numRows() const { return 5; }
  integer Crossroad::D2LTD2xpu_numCols() const { return 5; }
  integer Crossroad::D2LTD2xpu_nnz()     const { return 10; }

  void
  Crossroad::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 3   ;
  }


  void
  Crossroad::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t18  = t16 * t12 * t9 + t5 * t2 - 1;
    real_type t19  = ALIAS_AccBound_DD(t18);
    real_type t20  = t9 * t9;
    real_type t22  = t15 * t15;
    real_type t23  = 1.0 / t22;
    real_type t25  = kappa_D(t10);
    real_type t26  = t25 * t25;
    real_type t30  = ALIAS_AccBound_D(t18);
    real_type t31  = t9 * t30;
    real_type t35  = t16 * t11;
    real_type t36  = kappa_DD(t10);
    result__[ 0   ] = 4 * t26 * t23 * t12 * t20 * t19 + 2 * t16 * t26 * t31 + 2 * t36 * t35 * t31;
    real_type t40  = t8 * t7;
    result__[ 1   ] = 8 * t25 * t23 * t12 * t11 * t9 * t40 * t19 + 8 * t25 * t35 * t40 * t30;
    real_type t52  = t5 * t1 * t19;
    result__[ 2   ] = 4 * t25 * t16 * t11 * t9 * t52;
    result__[ 3   ] = result__[1];
    real_type t59  = t12 * t12;
    real_type t67  = ALIAS_VelBound_min_DD(-t7);
    real_type t70  = ALIAS_VelBound_max_DD(t7 - ModelPars[iM_v_max]);
    result__[ 4   ] = 16 * t23 * t59 * t9 * t8 * t19 + 12 * t16 * t12 * t8 * t30 + t67 + t70;
    result__[ 5   ] = 8 * t16 * t12 * t40 * t52;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t75  = t4 * t4;
    result__[ 8   ] = 4 / t75 * t2 * t19 + 2 * t5 * t30;
    result__[ 9   ] = ALIAS_Tpositive_DD(-X__[iX_Ts]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::D2JUD2xpu_numRows() const { return 5; }
  integer Crossroad::D2JUD2xpu_numCols() const { return 5; }
  integer Crossroad::D2JUD2xpu_nnz()     const { return 1; }

  void
  Crossroad::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
  }


  void
  Crossroad::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_jerkControl_D_1_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTargsDxpu_numRows() const { return 4; }
  integer Crossroad::DLTargsDxpu_numCols() const { return 5; }
  integer Crossroad::DLTargsDxpu_nnz()     const { return 6; }

  void
  Crossroad::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 1   ;
  }


  void
  Crossroad::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_s];
    real_type t5   = kappa(t4);
    real_type t8   = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t9   = 1.0 / t8;
    real_type t10  = kappa_D(t4);
    result__[ 1   ] = 2 * t10 * t9 * t5 * t3;
    real_type t14  = t5 * t5;
    result__[ 2   ] = 4 * t9 * t14 * t2 * t1;
    real_type t19  = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    result__[ 3   ] = 2 / t19 * X__[iX_a];
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 6, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::D2LTargsD2xpu_numRows() const { return 5; }
  integer Crossroad::D2LTargsD2xpu_numCols() const { return 5; }
  integer Crossroad::D2LTargsD2xpu_nnz()     const { return 5; }

  void
  Crossroad::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
  }


  void
  Crossroad::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_s];
    real_type t5   = kappa_D(t4);
    real_type t6   = t5 * t5;
    real_type t9   = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t10  = 1.0 / t9;
    real_type t11  = OMEGA__[1];
    real_type t12  = t11 * t10;
    real_type t14  = kappa(t4);
    real_type t16  = kappa_DD(t4);
    result__[ 0   ] = 2 * t10 * t11 * t14 * t16 * t3 + 2 * t12 * t3 * t6;
    result__[ 1   ] = 8 * t11 * t5 * t10 * t14 * t2 * t1;
    result__[ 2   ] = result__[1];
    real_type t26  = t14 * t14;
    result__[ 3   ] = 12 * t12 * t26 * t2;
    real_type t30  = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    result__[ 4   ] = 2 * t11 / t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 5, i_segment );
  }

}

// EOF: Crossroad_Methods_AdjointODE.cc
