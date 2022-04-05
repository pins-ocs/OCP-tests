/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_ODE.cc                                   |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


namespace OrbitTransferDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer OrbitTransfer::rhs_ode_numEqns() const { return 5; }

  void
  OrbitTransfer::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_tf];
    real_type t2   = X__[iX_u];
    result__[ 0   ] = t2 * t1;
    real_type t3   = X__[iX_v];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_r];
    real_type t6   = 1.0 / t5;
    real_type t9   = t5 * t5;
    real_type t12  = ModelPars[iM_T];
    real_type t13  = U__[iU_theta];
    real_type t14  = sin(t13);
    real_type t17  = 1.0 / X__[iX_m];
    result__[ 1   ] = (t6 * t4 - 1.0 / t9 * ModelPars[iM_mu] + t17 * t14 * t12) * t1;
    real_type t22  = cos(t13);
    result__[ 2   ] = (t17 * t22 * t12 - t6 * t2 * t3) * t1;
    result__[ 3   ] = -ModelPars[iM_mdot] * t1;
    result__[ 4   ] = t6 * t3 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::Drhs_odeDxup_numRows() const { return 5; }
  integer OrbitTransfer::Drhs_odeDxup_numCols() const { return 6; }
  integer OrbitTransfer::Drhs_odeDxup_nnz()     const { return 12; }

  void
  OrbitTransfer::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_tf];
    real_type t2   = ModelPars[iM_T] * result__[0];
    real_type t3   = U__[iU_theta];
    real_type t4   = sin(t3);
    real_type t5   = X__[iX_m];
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    result__[ 1   ] = -t7 * t4 * t2;
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t12  = X__[iX_r];
    real_type t13  = t12 * t12;
    real_type t14  = 1.0 / t13;
    result__[ 2   ] = (-t14 * t11 + 2 / t13 / t12 * ModelPars[iM_mu]) * result__[0];
    real_type t22  = t10 * result__[0];
    real_type t23  = 1.0 / t12;
    real_type t24  = t23 * t22;
    result__[ 3   ] = 2 * t24;
    real_type t25  = cos(t3);
    real_type t26  = 1.0 / t5;
    result__[ 4   ] = t26 * t25 * t2;
    result__[ 5   ] = -t7 * t25 * t2;
    real_type t30  = X__[iX_u];
    result__[ 6   ] = t14 * t30 * t22;
    result__[ 7   ] = -t24;
    result__[ 8   ] = -t23 * t30 * result__[0];
    result__[ 9   ] = -t26 * t4 * t2;
    result__[ 10  ] = -t14 * t22;
    result__[ 11  ] = t23 * result__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 12, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::A_numRows() const { return 5; }
  integer OrbitTransfer::A_numCols() const { return 5; }
  integer OrbitTransfer::A_nnz()     const { return 5; }

  void
  OrbitTransfer::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 5, i_segment );
  }

}

// EOF: OrbitTransfer_Methods_ODE.cc
