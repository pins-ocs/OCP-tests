/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_ODE.cc                                      |
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


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace UnderwaterDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Underwater::ode_numEqns() const { return 6; }

  void
  Underwater::ode_eval(
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
    real_type t2   = X__[iX_vx];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vz];
    real_type t7   = sin(t3);
    result__[ 0   ] = (t4 * t2 + t7 * t6) * t1 - V__[0];
    result__[ 1   ] = (-t7 * t2 + t4 * t6) * t1 - V__[1];
    real_type t17  = X__[iX_Omega];
    result__[ 2   ] = t17 * t1 - V__[2];
    real_type t21  = ModelPars[iM_m1];
    real_type t22  = 1.0 / t21;
    real_type t25  = ModelPars[iM_m3];
    result__[ 3   ] = (-t22 * t25 * t17 * t6 + t22 * U__[iU_u1]) * t1 - V__[3];
    real_type t32  = 1.0 / t25;
    result__[ 4   ] = (t32 * t21 * t17 * t2 + t32 * U__[iU_u2]) * t1 - V__[4];
    real_type t42  = 1.0 / ModelPars[iM_inertia];
    result__[ 5   ] = (t42 * U__[iU_u3] + t42 * (t25 - t21) * t6 * t2) * t1 - V__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DodeDxpuv_numRows() const { return 6; }
  integer Underwater::DodeDxpuv_numCols() const { return 16; }
  integer Underwater::DodeDxpuv_nnz()     const { return 28; }

  void
  Underwater::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 11  ;
    iIndex[10] = 2   ; jIndex[10] = 5   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 2   ; jIndex[12] = 12  ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 3   ; jIndex[15] = 6   ;
    iIndex[16] = 3   ; jIndex[16] = 7   ;
    iIndex[17] = 3   ; jIndex[17] = 13  ;
    iIndex[18] = 4   ; jIndex[18] = 3   ;
    iIndex[19] = 4   ; jIndex[19] = 5   ;
    iIndex[20] = 4   ; jIndex[20] = 6   ;
    iIndex[21] = 4   ; jIndex[21] = 8   ;
    iIndex[22] = 4   ; jIndex[22] = 14  ;
    iIndex[23] = 5   ; jIndex[23] = 3   ;
    iIndex[24] = 5   ; jIndex[24] = 4   ;
    iIndex[25] = 5   ; jIndex[25] = 6   ;
    iIndex[26] = 5   ; jIndex[26] = 9   ;
    iIndex[27] = 5   ; jIndex[27] = 15  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DodeDxpuv_sparse(
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
    real_type t2   = X__[iX_vz];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vx];
    real_type t7   = sin(t3);
    real_type t9   = t4 * t2 - t7 * t6;
    result__[ 0   ] = t9 * t1;
    result__[ 1   ] = t4 * t1;
    result__[ 2   ] = t7 * t1;
    result__[ 3   ] = t7 * t2 + t6 * t4;
    result__[ 4   ] = -1;
    result__[ 5   ] = -result__[3] * t1;
    result__[ 6   ] = -result__[2];
    result__[ 7   ] = result__[1];
    result__[ 8   ] = t9;
    result__[ 9   ] = -1;
    result__[ 10  ] = t1;
    result__[ 11  ] = X__[iX_Omega];
    result__[ 12  ] = -1;
    real_type t13  = result__[11] * result__[10];
    real_type t14  = ModelPars[iM_m3];
    real_type t15  = ModelPars[iM_m1];
    real_type t16  = 1.0 / t15;
    real_type t17  = t16 * t14;
    result__[ 13  ] = -t17 * t13;
    real_type t19  = t2 * result__[10];
    result__[ 14  ] = -t17 * t19;
    result__[ 15  ] = -t17 * result__[11] * t2 + t16 * U__[iU_u1];
    result__[ 16  ] = t16 * result__[10];
    result__[ 17  ] = -1;
    real_type t25  = 1.0 / t14;
    real_type t26  = t25 * t15;
    result__[ 18  ] = t26 * t13;
    real_type t27  = t6 * result__[10];
    result__[ 19  ] = t26 * t27;
    result__[ 20  ] = t26 * result__[11] * t6 + t25 * U__[iU_u2];
    result__[ 21  ] = t25 * result__[10];
    result__[ 22  ] = -1;
    real_type t34  = 1.0 / ModelPars[iM_inertia];
    real_type t35  = t34 * (t14 - t15);
    result__[ 23  ] = t35 * t19;
    result__[ 24  ] = t35 * t27;
    result__[ 25  ] = t35 * t2 * t6 + t34 * U__[iU_u3];
    result__[ 26  ] = t34 * result__[10];
    result__[ 27  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 28, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::A_numRows() const { return 6; }
  integer Underwater::A_numCols() const { return 6; }
  integer Underwater::A_nnz()     const { return 6; }

  void
  Underwater::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::A_sparse(
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
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 6, i_segment );
  }

}

// EOF: Underwater_Methods_ODE.cc
