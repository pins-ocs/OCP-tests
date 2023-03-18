/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc                  |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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

  integer ICLOCS_MinimumFuelOrbitRaising::ode_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_vr];
    result__[ 0   ] = t1 - V__[0];
    real_type t3   = X__[iX_vt];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_r];
    real_type t6   = 1.0 / t5;
    real_type t8   = t5 * t5;
    real_type t10  = ModelPars[iM_T];
    real_type t11  = U__[iU_theta];
    real_type t12  = sin(t11);
    real_type t15  = mass(Q__[iQ_zeta]);
    real_type t16  = 1.0 / t15;
    result__[ 1   ] = t6 * t4 - 1.0 / t8 + t16 * t12 * t10 - V__[1];
    real_type t21  = cos(t11);
    result__[ 2   ] = -t6 * t3 * t1 + t16 * t21 * t10 - V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DodeDxpuv_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DodeDxpuv_numCols() const { return 7; }
  integer ICLOCS_MinimumFuelOrbitRaising::DodeDxpuv_nnz()     const { return 11; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
    iIndex[10] = 2   ; jIndex[10] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    real_type t1   = X__[iX_vt];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_r];
    real_type t4   = t3 * t3;
    real_type t5   = 1.0 / t4;
    result__[ 2   ] = -t5 * t2 + 2 / t4 / t3;
    real_type t10  = 1.0 / t3;
    real_type t11  = t10 * t1;
    result__[ 3   ] = 2 * t11;
    real_type t12  = ModelPars[iM_T];
    real_type t13  = U__[iU_theta];
    real_type t14  = cos(t13);
    real_type t17  = mass(Q__[iQ_zeta]);
    real_type t18  = 1.0 / t17;
    result__[ 4   ] = t18 * t14 * t12;
    result__[ 5   ] = -1;
    real_type t19  = X__[iX_vr];
    result__[ 6   ] = t5 * t1 * t19;
    result__[ 7   ] = -t11;
    result__[ 8   ] = -t10 * t19;
    real_type t22  = sin(t13);
    result__[ 9   ] = -t18 * t22 * t12;
    result__[ 10  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 11, i_segment );
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc
