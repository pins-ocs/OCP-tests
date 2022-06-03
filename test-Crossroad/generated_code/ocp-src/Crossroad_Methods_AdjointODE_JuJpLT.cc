/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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

  integer Crossroad::JP_numEqns() const { return 0; }

  void
  Crossroad::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LT_numEqns() const { return 4; }

  void
  Crossroad::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = Tpositive(-X__[iX_Ts]);
    real_type t3   = X__[iX_a] * X__[iX_a];
    real_type t5   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t8   = X__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t12  = kappa(X__[iX_s]);
    real_type t13  = t12 * t12;
    real_type t16  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    result__[ 1   ] = AccBound(1.0 / t5 * t3 + 1.0 / t16 * t13 * t10 - 1);
    result__[ 2   ] = VelBound_min(-t8);
    result__[ 3   ] = VelBound_max(t8 - ModelPars[iM_v_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JU_numEqns() const { return 1; }

  void
  Crossroad::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = jerkControl(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LTargs_numEqns() const { return 4; }

  void
  Crossroad::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  integer Crossroad::DJPDxpu_numRows() const { return 0; }
  integer Crossroad::DJPDxpu_numCols() const { return 5; }
  integer Crossroad::DJPDxpu_nnz()     const { return 0; }

  void
  Crossroad::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTDxpu_numRows() const { return 4; }
  integer Crossroad::DLTDxpu_numCols() const { return 5; }
  integer Crossroad::DLTDxpu_nnz()     const { return 6; }

  void
  Crossroad::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 1   ;
  }


  void
  Crossroad::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_Tpositive_D(-X__[iX_Ts]);
    result__[ 0   ] = -t2;
    real_type t3   = X__[iX_a];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t7   = 1.0 / t6;
    real_type t9   = X__[iX_v];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t10;
    real_type t12  = X__[iX_s];
    real_type t13  = kappa(t12);
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t18  = 1.0 / t17;
    real_type t21  = ALIAS_AccBound_D(t18 * t14 * t11 + t7 * t4 - 1);
    real_type t24  = kappa_D(t12);
    result__[ 1   ] = 2 * t24 * t18 * t13 * t11 * t21;
    result__[ 2   ] = 4 * t18 * t14 * t10 * t9 * t21;
    result__[ 3   ] = 2 * t7 * t3 * t21;
    real_type t33  = ALIAS_VelBound_min_D(-t9);
    result__[ 4   ] = -t33;
    result__[ 5   ] = ALIAS_VelBound_max_D(t9 - ModelPars[iM_v_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJUDxpu_numRows() const { return 1; }
  integer Crossroad::DJUDxpu_numCols() const { return 5; }
  integer Crossroad::DJUDxpu_nnz()     const { return 1; }

  void
  Crossroad::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  Crossroad::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_jerkControl_D_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 1, i_segment );
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  integer Crossroad::D2JPD2xpu_numRows() const { return 5; }
  integer Crossroad::D2JPD2xpu_numCols() const { return 5; }
  integer Crossroad::D2JPD2xpu_nnz()     const { return 0; }

  void
  Crossroad::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    real_type t23  = t15 * t15;
    real_type t24  = 1.0 / t23;
    real_type t25  = kappa_D(t10);
    real_type t26  = t25 * t25;
    real_type t28  = OMEGA__[1];
    real_type t32  = ALIAS_AccBound_D(t18);
    real_type t33  = t9 * t32;
    real_type t39  = kappa_DD(t10);
    result__[ 0   ] = 4 * t28 * t26 * t24 * t12 * t20 * t19 + 2 * t28 * t39 * t16 * t11 * t33 + 2 * t28 * t16 * t26 * t33;
    real_type t44  = t8 * t7;
    result__[ 1   ] = 8 * t28 * t25 * t24 * t12 * t11 * t9 * t44 * t19 + 8 * t28 * t25 * t16 * t11 * t44 * t32;
    real_type t58  = t1 * t19;
    result__[ 2   ] = 4 * t28 * t25 * t16 * t11 * t9 * t5 * t58;
    result__[ 3   ] = result__[1];
    real_type t67  = t12 * t12;
    real_type t77  = ALIAS_VelBound_min_DD(-t7);
    real_type t82  = ALIAS_VelBound_max_DD(t7 - ModelPars[iM_v_max]);
    result__[ 4   ] = 16 * t28 * t24 * t67 * t9 * t8 * t19 + 12 * t28 * t16 * t12 * t8 * t32 + OMEGA__[2] * t77 + OMEGA__[3] * t82;
    result__[ 5   ] = 8 * t28 * t16 * t12 * t44 * t5 * t58;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t91  = t4 * t4;
    result__[ 8   ] = 4 * t28 / t91 * t2 * t19 + 2 * t28 * t5 * t32;
    real_type t100 = ALIAS_Tpositive_DD(-X__[iX_Ts]);
    result__[ 9   ] = OMEGA__[0] * t100;
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_jerkControl_D_1_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    result__[ 0   ] = OMEGA__[0] * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    result__[ 0   ] = 2 * t11 * t16 * t10 * t14 * t3 + 2 * t12 * t6 * t3;
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
