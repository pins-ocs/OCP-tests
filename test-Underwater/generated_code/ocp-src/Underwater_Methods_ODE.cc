/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_ODE.cc                                      |
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

  integer Underwater::rhs_ode_numEqns() const { return 6; }

  void
  Underwater::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vx];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vz];
    real_type t7   = sin(t3);
    result__[ 0   ] = (t4 * t2 + t7 * t6) * t1;
    result__[ 1   ] = (-t7 * t2 + t4 * t6) * t1;
    real_type t13  = X__[iX_Omega];
    result__[ 2   ] = t13 * t1;
    real_type t15  = ModelPars[iM_m1];
    real_type t16  = 1.0 / t15;
    real_type t19  = ModelPars[iM_m3];
    result__[ 3   ] = (-t16 * t19 * t13 * t6 + t16 * U__[iU_u1]) * t1;
    real_type t24  = 1.0 / t19;
    result__[ 4   ] = (t24 * t15 * t13 * t2 + t24 * U__[iU_u2]) * t1;
    real_type t32  = 1.0 / ModelPars[iM_inertia];
    result__[ 5   ] = (t32 * U__[iU_u3] + t32 * (t19 - t15) * t6 * t2) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::Drhs_odeDxup_numRows() const { return 6; }
  integer Underwater::Drhs_odeDxup_numCols() const { return 10; }
  integer Underwater::Drhs_odeDxup_nnz()     const { return 22; }

  void
  Underwater::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 9   ;
    iIndex[10] = 3   ; jIndex[10] = 4   ;
    iIndex[11] = 3   ; jIndex[11] = 5   ;
    iIndex[12] = 3   ; jIndex[12] = 6   ;
    iIndex[13] = 3   ; jIndex[13] = 9   ;
    iIndex[14] = 4   ; jIndex[14] = 3   ;
    iIndex[15] = 4   ; jIndex[15] = 5   ;
    iIndex[16] = 4   ; jIndex[16] = 7   ;
    iIndex[17] = 4   ; jIndex[17] = 9   ;
    iIndex[18] = 5   ; jIndex[18] = 3   ;
    iIndex[19] = 5   ; jIndex[19] = 4   ;
    iIndex[20] = 5   ; jIndex[20] = 8   ;
    iIndex[21] = 5   ; jIndex[21] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
    result__[ 4   ] = -result__[3] * t1;
    result__[ 5   ] = -result__[2];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = t9;
    result__[ 8   ] = t1;
    result__[ 9   ] = X__[iX_Omega];
    real_type t13  = result__[9] * result__[8];
    real_type t14  = ModelPars[iM_m3];
    real_type t15  = ModelPars[iM_m1];
    real_type t16  = 1.0 / t15;
    real_type t17  = t16 * t14;
    result__[ 10  ] = -t17 * t13;
    real_type t19  = t2 * result__[8];
    result__[ 11  ] = -t17 * t19;
    result__[ 12  ] = t16 * result__[8];
    result__[ 13  ] = -t17 * result__[9] * t2 + t16 * U__[iU_u1];
    real_type t25  = 1.0 / t14;
    real_type t26  = t25 * t15;
    result__[ 14  ] = t26 * t13;
    real_type t27  = t6 * result__[8];
    result__[ 15  ] = t26 * t27;
    result__[ 16  ] = t25 * result__[8];
    result__[ 17  ] = t26 * result__[9] * t6 + t25 * U__[iU_u2];
    real_type t34  = 1.0 / ModelPars[iM_inertia];
    real_type t35  = t34 * (t14 - t15);
    result__[ 18  ] = t35 * t19;
    result__[ 19  ] = t35 * t27;
    result__[ 20  ] = t34 * result__[8];
    result__[ 21  ] = t35 * t2 * t6 + t34 * U__[iU_u3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 22, i_segment );
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
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 6, i_segment );
  }

}

// EOF: Underwater_Methods_ODE.cc
