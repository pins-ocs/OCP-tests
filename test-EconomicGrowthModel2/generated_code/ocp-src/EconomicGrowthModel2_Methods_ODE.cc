/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_ODE.cc                            |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer EconomicGrowthModel2::ode_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::ode_eval(
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
    real_type t2   = X__[iX_T];
    result__[ 0   ] = t2 * X__[iX_y1] - V__[0];
    real_type t5   = U__[iU_u];
    real_type t8   = Q(X__[iX_x1], X__[iX_x2]);
    result__[ 1   ] = t2 * t8 * t5 - V__[2];
    result__[ 2   ] = t2 * X__[iX_y2] - V__[1];
    result__[ 3   ] = t2 * t8 * (1 - t5) - V__[3];
    result__[ 4   ] = -V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DodeDxpuv_numRows() const { return 5; }
  integer EconomicGrowthModel2::DodeDxpuv_numCols() const { return 11; }
  integer EconomicGrowthModel2::DodeDxpuv_nnz()     const { return 17; }

  void
  EconomicGrowthModel2::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 7   ;
    iIndex[11] = 3   ; jIndex[11] = 0   ;
    iIndex[12] = 3   ; jIndex[12] = 1   ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 3   ; jIndex[15] = 9   ;
    iIndex[16] = 4   ; jIndex[16] = 10  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DodeDxpuv_sparse(
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
    result__[ 0   ] = X__[iX_T];
    result__[ 1   ] = X__[iX_y1];
    result__[ 2   ] = -1;
    real_type t1   = U__[iU_u];
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = Q_D_1(t2, t3);
    result__[ 3   ] = result__[0] * t4 * t1;
    real_type t6   = Q_D_2(t2, t3);
    result__[ 4   ] = result__[0] * t6 * t1;
    real_type t8   = Q(t2, t3);
    result__[ 5   ] = t8 * t1;
    result__[ 6   ] = result__[0] * t8;
    result__[ 7   ] = -1;
    result__[ 8   ] = result__[0];
    result__[ 9   ] = X__[iX_y2];
    result__[ 10  ] = -1;
    real_type t9   = 1 - t1;
    result__[ 11  ] = result__[8] * t4 * t9;
    result__[ 12  ] = result__[8] * t6 * t9;
    result__[ 13  ] = t8 * t9;
    result__[ 14  ] = -result__[6];
    result__[ 15  ] = -1;
    result__[ 16  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 17, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::A_numRows() const { return 5; }
  integer EconomicGrowthModel2::A_numCols() const { return 5; }
  integer EconomicGrowthModel2::A_nnz()     const { return 5; }

  void
  EconomicGrowthModel2::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::A_sparse(
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
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 5, i_segment );
  }

}

// EOF: EconomicGrowthModel2_Methods_ODE.cc
