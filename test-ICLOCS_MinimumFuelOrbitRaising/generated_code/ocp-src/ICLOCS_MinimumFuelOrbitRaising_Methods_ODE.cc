/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc                  |
 |                                                                       |
 |  version: 1.0   date 15/11/2022                                       |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ICLOCS_MinimumFuelOrbitRaising::rhs_ode_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_vr];
    real_type t1   = X__[iX_vt];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_r];
    real_type t4   = 1.0 / t3;
    real_type t6   = t3 * t3;
    real_type t8   = ModelPars[iM_T];
    real_type t9   = U__[iU_theta];
    real_type t10  = sin(t9);
    real_type t13  = mass(Q__[iQ_zeta]);
    real_type t14  = 1.0 / t13;
    result__[ 1   ] = t4 * t2 - 1.0 / t6 + t14 * t10 * t8;
    real_type t18  = cos(t9);
    result__[ 2   ] = -t4 * t1 * result__[0] + t14 * t18 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDxpu_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDxpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDxpu_nnz()     const { return 8; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    real_type t1   = X__[iX_vt];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_r];
    real_type t4   = t3 * t3;
    real_type t5   = 1.0 / t4;
    result__[ 1   ] = -t5 * t2 + 2 / t4 / t3;
    real_type t10  = 1.0 / t3;
    real_type t11  = t10 * t1;
    result__[ 2   ] = 2 * t11;
    real_type t12  = ModelPars[iM_T];
    real_type t13  = U__[iU_theta];
    real_type t14  = cos(t13);
    real_type t17  = mass(Q__[iQ_zeta]);
    real_type t18  = 1.0 / t17;
    result__[ 3   ] = t18 * t14 * t12;
    real_type t19  = X__[iX_vr];
    result__[ 4   ] = t5 * t1 * t19;
    result__[ 5   ] = -t11;
    result__[ 6   ] = -t10 * t19;
    real_type t22  = sin(t13);
    result__[ 7   ] = -t18 * t22 * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxpu_sparse", 8, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::A_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::A_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::A_nnz()     const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::A_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::eta_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDxp_sparse(
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

  integer ICLOCS_MinimumFuelOrbitRaising::nu_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc
