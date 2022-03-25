/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_AdjointODE.cc                                  |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JPx_numEqns() const { return 5; }

  void
  Zermelo::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
      Mechatronix::check_in_segment( result__, "JPx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::LTx_numEqns() const { return 5; }

  void
  Zermelo::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    real_type t2   = ALIAS_Tpositive_D(-X__[iX_T]);
    result__[ 4   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JUx_numEqns() const { return 5; }

  void
  Zermelo::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JPp_numEqns() const { return 0; }

  void
  Zermelo::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::LTp_numEqns() const { return 0; }

  void
  Zermelo::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JUp_numEqns() const { return 0; }

  void
  Zermelo::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JPu_numEqns() const { return 1; }

  void
  Zermelo::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::LTu_numEqns() const { return 1; }

  void
  Zermelo::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::JUu_numEqns() const { return 1; }

  void
  Zermelo::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::LTargs_numEqns() const { return 1; }

  void
  Zermelo::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJPxDxp_numRows() const { return 5; }
  integer Zermelo::DJPxDxp_numCols() const { return 5; }
  integer Zermelo::DJPxDxp_nnz()     const { return 0; }

  void
  Zermelo::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DLTxDxp_numRows() const { return 5; }
  integer Zermelo::DLTxDxp_numCols() const { return 5; }
  integer Zermelo::DLTxDxp_nnz()     const { return 1; }

  void
  Zermelo::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
  }


  void
  Zermelo::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_Tpositive_DD(-X__[iX_T]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJUxDxp_numRows() const { return 5; }
  integer Zermelo::DJUxDxp_numCols() const { return 5; }
  integer Zermelo::DJUxDxp_nnz()     const { return 0; }

  void
  Zermelo::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJPuDxp_numRows() const { return 1; }
  integer Zermelo::DJPuDxp_numCols() const { return 5; }
  integer Zermelo::DJPuDxp_nnz()     const { return 0; }

  void
  Zermelo::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DLTuDxp_numRows() const { return 1; }
  integer Zermelo::DLTuDxp_numCols() const { return 5; }
  integer Zermelo::DLTuDxp_nnz()     const { return 0; }

  void
  Zermelo::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJUuDxp_numRows() const { return 1; }
  integer Zermelo::DJUuDxp_numCols() const { return 5; }
  integer Zermelo::DJUuDxp_nnz()     const { return 0; }

  void
  Zermelo::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJPpDp_numRows() const { return 0; }
  integer Zermelo::DJPpDp_numCols() const { return 0; }
  integer Zermelo::DJPpDp_nnz()     const { return 0; }

  void
  Zermelo::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DLTpDp_numRows() const { return 0; }
  integer Zermelo::DLTpDp_numCols() const { return 0; }
  integer Zermelo::DLTpDp_nnz()     const { return 0; }

  void
  Zermelo::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DJUpDp_numRows() const { return 0; }
  integer Zermelo::DJUpDp_numCols() const { return 0; }
  integer Zermelo::DJUpDp_nnz()     const { return 0; }

  void
  Zermelo::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DLTargsDxup_numRows() const { return 1; }
  integer Zermelo::DLTargsDxup_numCols() const { return 6; }
  integer Zermelo::DLTargsDxup_nnz()     const { return 1; }

  void
  Zermelo::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  Zermelo::DLTargsDxup_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 1, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::D2LTargsD2xup_numRows() const { return 6; }
  integer Zermelo::D2LTargsD2xup_numCols() const { return 6; }
  integer Zermelo::D2LTargsD2xup_nnz()     const { return 0; }

  void
  Zermelo::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::Hx_numEqns() const { return 5; }

  void
  Zermelo::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t6 * t3;
    real_type t12  = velX_D_2(t4, t5);
    real_type t14  = velY_D_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    result__[ 2   ] = t2 * t1;
    result__[ 3   ] = t2 * t8;
    real_type t17  = velX(t4, t5);
    real_type t21  = velY(t4, t5);
    real_type t25  = ModelPars[iM_S];
    real_type t27  = U__[iU_u];
    real_type t28  = cos(t27);
    real_type t32  = sin(t27);
    result__[ 4   ] = (X__[iX_vx] + t17) * t1 + (X__[iX_vy] + t21) * t8 + t28 * t25 * L__[iL_lambda3__xo] + t32 * t25 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::Hp_numEqns() const { return 0; }

  void
  Zermelo::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DHxDxp_numRows() const { return 5; }
  integer Zermelo::DHxDxp_numCols() const { return 5; }
  integer Zermelo::DHxDxp_nnz()     const { return 12; }

  void
  Zermelo::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 1   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 3   ;
  }


  void
  Zermelo::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t3 * t6;
    real_type t12  = velX_D_1_2(t4, t5);
    real_type t14  = velY_D_1_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    real_type t16  = velX_D_1(t4, t5);
    real_type t18  = velY_D_1(t4, t5);
    result__[ 2   ] = t1 * t16 + t18 * t8;
    result__[ 3   ] = result__[1];
    real_type t20  = velX_D_2_2(t4, t5);
    real_type t22  = velY_D_2_2(t4, t5);
    result__[ 4   ] = t20 * t3 + t22 * t9;
    real_type t24  = velX_D_2(t4, t5);
    real_type t26  = velY_D_2(t4, t5);
    result__[ 5   ] = t1 * t24 + t26 * t8;
    result__[ 6   ] = t1;
    result__[ 7   ] = t8;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DHpDp_numRows() const { return 0; }
  integer Zermelo::DHpDp_numCols() const { return 0; }
  integer Zermelo::DHpDp_nnz()     const { return 0; }

  void
  Zermelo::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::Hu_numEqns() const { return 1; }

  void
  Zermelo::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_T];
    real_type t4   = ModelPars[iM_S];
    real_type t5   = U__[iU_u];
    real_type t6   = sin(t5);
    real_type t11  = cos(t5);
    result__[ 0   ] = t11 * t4 * t2 * L__[iL_lambda4__xo] - t6 * t4 * t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DHuDxp_numRows() const { return 1; }
  integer Zermelo::DHuDxp_numCols() const { return 5; }
  integer Zermelo::DHuDxp_nnz()     const { return 1; }

  void
  Zermelo::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  Zermelo::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_S];
    real_type t4   = U__[iU_u];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * L__[iL_lambda3__xo] + t9 * t2 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 1, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::eta_numEqns() const { return 5; }

  void
  Zermelo::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DetaDxp_numRows() const { return 5; }
  integer Zermelo::DetaDxp_numCols() const { return 5; }
  integer Zermelo::DetaDxp_nnz()     const { return 0; }

  void
  Zermelo::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::nu_numEqns() const { return 5; }

  void
  Zermelo::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DnuDxp_numRows() const { return 5; }
  integer Zermelo::DnuDxp_numCols() const { return 5; }
  integer Zermelo::DnuDxp_nnz()     const { return 0; }

  void
  Zermelo::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Zermelo::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Zermelo_Methods_AdjointODE.cc
