/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_ODE.cc                                         |
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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Zermelo::ode_numEqns() const { return 5; }

  void
  Zermelo::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_T];
    real_type t3   = X__[iX_x];
    real_type t4   = X__[iX_y];
    real_type t5   = velX(t3, t4);
    result__[ 0   ] = (X__[iX_vx] + t5) * t1 - V__[0];
    real_type t10  = velY(t3, t4);
    result__[ 1   ] = (X__[iX_vy] + t10) * t1 - V__[1];
    real_type t15  = ModelPars[iM_S] * t1;
    real_type t16  = U__[iU_u];
    real_type t17  = cos(t16);
    result__[ 2   ] = t17 * t15 - V__[2];
    real_type t20  = sin(t16);
    result__[ 3   ] = t20 * t15 - V__[3];
    result__[ 4   ] = -V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DodeDxpuv_numRows() const { return 5; }
  integer Zermelo::DodeDxpuv_numCols() const { return 11; }
  integer Zermelo::DodeDxpuv_nnz()     const { return 17; }

  void
  Zermelo::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 7   ;
    iIndex[10] = 2   ; jIndex[10] = 4   ;
    iIndex[11] = 2   ; jIndex[11] = 5   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 3   ; jIndex[15] = 9   ;
    iIndex[16] = 4   ; jIndex[16] = 10  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_T];
    real_type t2   = X__[iX_x];
    real_type t3   = X__[iX_y];
    real_type t4   = velX_D_1(t2, t3);
    result__[ 0   ] = t4 * t1;
    real_type t5   = velX_D_2(t2, t3);
    result__[ 1   ] = t5 * t1;
    result__[ 2   ] = t1;
    real_type t7   = velX(t2, t3);
    result__[ 3   ] = X__[iX_vx] + t7;
    result__[ 4   ] = -1;
    real_type t8   = velY_D_1(t2, t3);
    result__[ 5   ] = t8 * result__[2];
    real_type t9   = velY_D_2(t2, t3);
    result__[ 6   ] = t9 * result__[2];
    result__[ 7   ] = result__[2];
    real_type t11  = velY(t2, t3);
    result__[ 8   ] = X__[iX_vy] + t11;
    result__[ 9   ] = -1;
    real_type t12  = ModelPars[iM_S];
    real_type t13  = U__[iU_u];
    real_type t14  = cos(t13);
    result__[ 10  ] = t14 * t12;
    real_type t15  = t12 * result__[7];
    real_type t16  = sin(t13);
    result__[ 11  ] = -t16 * t15;
    result__[ 12  ] = -1;
    result__[ 13  ] = t16 * t12;
    result__[ 14  ] = t14 * t15;
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
  integer Zermelo::A_numRows() const { return 5; }
  integer Zermelo::A_numCols() const { return 5; }
  integer Zermelo::A_nnz()     const { return 5; }

  void
  Zermelo::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
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

// EOF: Zermelo_Methods_ODE.cc
