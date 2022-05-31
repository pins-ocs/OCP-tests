/*-----------------------------------------------------------------------*\
 |  file: SingularCalogeroModified_Methods_AdjointODE.cc                 |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "SingularCalogeroModified.hh"
#include "SingularCalogeroModified_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace SingularCalogeroModifiedDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogeroModified::JP_numEqns() const { return 0; }

  void
  SingularCalogeroModified::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogeroModified::LT_numEqns() const { return 0; }

  void
  SingularCalogeroModified::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogeroModified::JU_numEqns() const { return 1; }

  void
  SingularCalogeroModified::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = pow(ModelPars[iM_C] * t3 + X__[iX_x] - 1, 2);
    real_type t11  = uControl(U__[iU_u], -1, 1);
    result__[ 0   ] = t11 * (ModelPars[iM_epsilon] + t8);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogeroModified::LTargs_numEqns() const { return 0; }

  void
  SingularCalogeroModified::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::DJPDxpu_numRows() const { return 0; }
  integer SingularCalogeroModified::DJPDxpu_numCols() const { return 3; }
  integer SingularCalogeroModified::DJPDxpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::DLTDxpu_numRows() const { return 0; }
  integer SingularCalogeroModified::DLTDxpu_numCols() const { return 3; }
  integer SingularCalogeroModified::DLTDxpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::DJUDxpu_numRows() const { return 1; }
  integer SingularCalogeroModified::DJUDxpu_numCols() const { return 3; }
  integer SingularCalogeroModified::DJUDxpu_nnz()     const { return 2; }

  void
  SingularCalogeroModified::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
  }


  void
  SingularCalogeroModified::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_C] * t2 + X__[iX_x] - 1;
    real_type t8   = U__[iU_u];
    real_type t9   = uControl(t8, -1, 1);
    result__[ 0   ] = 2 * t9 * t6;
    real_type t11  = t6 * t6;
    real_type t13  = ALIAS_uControl_D_1(t8, -1, 1);
    result__[ 1   ] = t13 * (ModelPars[iM_epsilon] + t11);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::DLTargsDxpu_numRows() const { return 0; }
  integer SingularCalogeroModified::DLTargsDxpu_numCols() const { return 3; }
  integer SingularCalogeroModified::DLTargsDxpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::D2JPD2xpu_numRows() const { return 3; }
  integer SingularCalogeroModified::D2JPD2xpu_numCols() const { return 3; }
  integer SingularCalogeroModified::D2JPD2xpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::D2LTD2xpu_numRows() const { return 3; }
  integer SingularCalogeroModified::D2LTD2xpu_numCols() const { return 3; }
  integer SingularCalogeroModified::D2LTD2xpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::D2JUD2xpu_numRows() const { return 3; }
  integer SingularCalogeroModified::D2JUD2xpu_numCols() const { return 3; }
  integer SingularCalogeroModified::D2JUD2xpu_nnz()     const { return 4; }

  void
  SingularCalogeroModified::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
  }


  void
  SingularCalogeroModified::D2JUD2xpu_sparse(
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
    real_type t1   = U__[iU_u];
    real_type t2   = uControl(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = 2 * t3 * t2;
    real_type t6   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t10  = ModelPars[iM_C] * t6 + X__[iX_x] - 1;
    real_type t12  = ALIAS_uControl_D_1(t1, -1, 1);
    result__[ 1   ] = 2 * t3 * t12 * t10;
    result__[ 2   ] = result__[1];
    real_type t15  = t10 * t10;
    real_type t17  = ALIAS_uControl_D_1_1(t1, -1, 1);
    result__[ 3   ] = t3 * t17 * (ModelPars[iM_epsilon] + t15);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogeroModified::D2LTargsD2xpu_numRows() const { return 3; }
  integer SingularCalogeroModified::D2LTargsD2xpu_numCols() const { return 3; }
  integer SingularCalogeroModified::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  SingularCalogeroModified::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogeroModified::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: SingularCalogeroModified_Methods_AdjointODE.cc
