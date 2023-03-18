/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_ODE.cc                                |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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
#define ALIAS_TimePositive_DD(__t1) TimePositive.DD( __t1)
#define ALIAS_TimePositive_D(__t1) TimePositive.D( __t1)


namespace Brachiostocrona2Define {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Brachiostocrona2::ode_numEqns() const { return 3; }

  void
  Brachiostocrona2::ode_eval(
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
    real_type t1   = P__[iP_T];
    real_type t3   = X__[iX_v] * t1;
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    result__[ 0   ] = t5 * t3 - V__[0];
    real_type t8   = sin(t4);
    result__[ 1   ] = t8 * t3 - V__[1];
    result__[ 2   ] = -t8 * ModelPars[iM_g] * t1 - ModelPars[iM_mass] * V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DodeDxpuv_numRows() const { return 3; }
  integer Brachiostocrona2::DodeDxpuv_numCols() const { return 8; }
  integer Brachiostocrona2::DodeDxpuv_nnz()     const { return 11; }

  void
  Brachiostocrona2::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DodeDxpuv_sparse(
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
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_theta];
    real_type t3   = cos(t2);
    result__[ 0   ] = t3 * t1;
    real_type t4   = X__[iX_v];
    result__[ 1   ] = t3 * t4;
    real_type t5   = t4 * t1;
    real_type t6   = sin(t2);
    result__[ 2   ] = -t6 * t5;
    result__[ 3   ] = -1;
    result__[ 4   ] = t6 * t1;
    result__[ 5   ] = t6 * t4;
    result__[ 6   ] = t3 * t5;
    result__[ 7   ] = -1;
    real_type t8   = ModelPars[iM_g];
    result__[ 8   ] = -t6 * t8;
    result__[ 9   ] = -t3 * t8 * t1;
    result__[ 10  ] = -ModelPars[iM_mass];
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
  integer Brachiostocrona2::A_numRows() const { return 3; }
  integer Brachiostocrona2::A_numCols() const { return 3; }
  integer Brachiostocrona2::A_nnz()     const { return 3; }

  void
  Brachiostocrona2::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::A_sparse(
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
    result__[ 2   ] = ModelPars[iM_mass];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: Brachiostocrona2_Methods_ODE.cc
