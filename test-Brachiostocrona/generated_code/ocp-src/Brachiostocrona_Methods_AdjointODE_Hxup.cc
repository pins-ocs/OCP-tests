/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_AdjointODE.cc                          |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#define ALIAS_LowBound_DD(__t1) LowBound.DD( __t1)
#define ALIAS_LowBound_D(__t1) LowBound.D( __t1)
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::Hxp_numEqns() const { return 5; }

  void
  Brachiostocrona::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_slope_low];
    real_type t7   = ALIAS_LowBound_D(X__[iX_x] * t1 - X__[iX_y] + ModelPars[iM_y0_low]);
    result__[ 0   ] = t1 * t7;
    result__[ 1   ] = -t7;
    real_type t8   = MU__[0];
    real_type t9   = P__[iP_T];
    real_type t10  = t9 * t8;
    real_type t11  = X__[iX_theta];
    real_type t12  = cos(t11);
    real_type t14  = MU__[1];
    real_type t15  = t9 * t14;
    real_type t16  = sin(t11);
    result__[ 2   ] = t12 * t10 + t16 * t15;
    real_type t18  = X__[iX_v];
    real_type t23  = MU__[2];
    real_type t25  = ModelPars[iM_g];
    result__[ 3   ] = -t12 * t25 * t9 * t23 - t16 * t18 * t10 + t12 * t18 * t15;
    real_type t29  = vthetaControl(U__[iU_vtheta], -10, 10);
    result__[ 4   ] = t12 * t18 * t8 + t16 * t18 * t14 - t16 * t25 * t23 + t29;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DHxpDxpuv_numRows() const { return 5; }
  integer Brachiostocrona::DHxpDxpuv_numCols() const { return 10; }
  integer Brachiostocrona::DHxpDxpuv_nnz()     const { return 12; }

  void
  Brachiostocrona::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 2   ;
    iIndex[10] = 4   ; jIndex[10] = 3   ;
    iIndex[11] = 4   ; jIndex[11] = 5   ;
  }


  void
  Brachiostocrona::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_slope_low];
    real_type t7   = ALIAS_LowBound_DD(X__[iX_x] * t1 - X__[iX_y] + ModelPars[iM_y0_low]);
    real_type t8   = t1 * t1;
    result__[ 0   ] = t8 * t7;
    result__[ 1   ] = -t1 * t7;
    result__[ 2   ] = result__[1];
    result__[ 3   ] = t7;
    real_type t10  = MU__[0];
    real_type t11  = P__[iP_T];
    real_type t12  = t11 * t10;
    real_type t13  = X__[iX_theta];
    real_type t14  = sin(t13);
    real_type t16  = MU__[1];
    real_type t17  = t11 * t16;
    real_type t18  = cos(t13);
    result__[ 4   ] = -t14 * t12 + t18 * t17;
    result__[ 5   ] = t18 * t10 + t14 * t16;
    result__[ 6   ] = result__[4];
    real_type t22  = X__[iX_v];
    real_type t27  = MU__[2];
    real_type t29  = ModelPars[iM_g];
    result__[ 7   ] = t14 * t29 * t11 * t27 - t18 * t22 * t12 - t14 * t22 * t17;
    result__[ 8   ] = -t14 * t22 * t10 + t18 * t22 * t16 - t18 * t29 * t27;
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = ALIAS_vthetaControl_D_1(U__[iU_vtheta], -10, 10);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 12, i_segment );
  }

}

// EOF: Brachiostocrona_Methods_AdjointODE.cc
