/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_controls.cc                                     |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#include "Farmer.hh"
#include "Farmer_Pars.hh"

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
#define ALIAS_LimitX2X4_DD(__t1) LimitX2X4.DD( __t1)
#define ALIAS_LimitX2X4_D(__t1) LimitX2X4.D( __t1)
#define ALIAS_x4__oControl_D_3(__t1, __t2, __t3) x4__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2(__t1, __t2, __t3) x4__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1(__t1, __t2, __t3) x4__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_3_3(__t1, __t2, __t3) x4__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_3(__t1, __t2, __t3) x4__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_2(__t1, __t2, __t3) x4__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_3(__t1, __t2, __t3) x4__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_2(__t1, __t2, __t3) x4__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_1(__t1, __t2, __t3) x4__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3(__t1, __t2, __t3) x3__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2(__t1, __t2, __t3) x3__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1(__t1, __t2, __t3) x3__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3_3(__t1, __t2, __t3) x3__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_3(__t1, __t2, __t3) x3__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_2(__t1, __t2, __t3) x3__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_3(__t1, __t2, __t3) x3__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_2(__t1, __t2, __t3) x3__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_1(__t1, __t2, __t3) x3__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3(__t1, __t2, __t3) x2__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2(__t1, __t2, __t3) x2__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1(__t1, __t2, __t3) x2__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3_3(__t1, __t2, __t3) x2__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_3(__t1, __t2, __t3) x2__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_2(__t1, __t2, __t3) x2__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_3(__t1, __t2, __t3) x2__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_2(__t1, __t2, __t3) x2__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_1(__t1, __t2, __t3) x2__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3(__t1, __t2, __t3) x1__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2(__t1, __t2, __t3) x1__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1(__t1, __t2, __t3) x1__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3_3(__t1, __t2, __t3) x1__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_3(__t1, __t2, __t3) x1__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_2(__t1, __t2, __t3) x1__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_3(__t1, __t2, __t3) x1__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_2(__t1, __t2, __t3) x1__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_1(__t1, __t2, __t3) x1__oControl.D_1_1( __t1, __t2, __t3)


namespace FarmerDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Farmer::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w1];
    real_type t4   = X__[iX_x1];
    real_type t6   = ModelPars[iM_w2];
    real_type t8   = X__[iX_x2];
    real_type t10  = ModelPars[iM_w3];
    real_type t12  = X__[iX_x3];
    real_type t14  = ModelPars[iM_w4];
    real_type t16  = X__[iX_x4];
    real_type t19  = Ptot(Q__[iQ_zeta]);
    real_type t21  = pow(t4 / t2 + t8 / t6 + t12 / t10 + t16 / t14 - t19, 2);
    real_type t23  = t4 * t4;
    real_type t25  = t8 * t8;
    real_type t27  = t12 * t12;
    real_type t29  = t16 * t16;
    real_type t32  = U__[iU_x1__o];
    real_type t33  = -t4 + t32;
    real_type t34  = t33 * t33;
    real_type t37  = U__[iU_x2__o];
    real_type t38  = -t8 + t37;
    real_type t39  = t38 * t38;
    real_type t42  = U__[iU_x3__o];
    real_type t43  = -t12 + t42;
    real_type t44  = t43 * t43;
    real_type t47  = U__[iU_x4__o];
    real_type t48  = -t16 + t47;
    real_type t49  = t48 * t48;
    real_type t51  = x1__oControl(t32, -0.1e-2, 100);
    real_type t52  = x2__oControl(t37, -0.1e-2, 100);
    real_type t53  = x3__oControl(t42, -0.1e-2, 100);
    real_type t54  = x4__oControl(t47, -0.1e-2, 100);
    real_type t56  = LimitX2X4(t8 + t16 - 0.12e0);
    real_type result__ = t21 * ModelPars[iM_wP] + t23 * t2 + t25 * t6 + t27 * t10 + t29 * t14 + t34 * ModelPars[iM_wJ1] + t39 * ModelPars[iM_wJ2] + t44 * ModelPars[iM_wJ3] + t49 * ModelPars[iM_wJ4] + t51 + t52 + t53 + t54 + t56 + 1.0 / ModelPars[iM_tau__1] * t33 * MU__[0] + 1.0 / ModelPars[iM_tau__2] * t38 * MU__[1] + 1.0 / ModelPars[iM_tau__3] * t43 * MU__[2] - 1.0 / ModelPars[iM_tau__4] * (-t12 + t16) * MU__[3] + 1.0 / ModelPars[iM_tau__5] * t48 * MU__[4];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::g_numEqns() const { return 4; }

  void
  Farmer::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = U__[iU_x1__o];
    real_type t7   = ALIAS_x1__oControl_D_1(t3, -0.1e-2, 100);
    result__[ 0   ] = 2 * (-X__[iX_x1] + t3) * ModelPars[iM_wJ1] + t7 + MU__[0] / ModelPars[iM_tau__1];
    real_type t14  = U__[iU_x2__o];
    real_type t18  = ALIAS_x2__oControl_D_1(t14, -0.1e-2, 100);
    result__[ 1   ] = 2 * (-X__[iX_x2] + t14) * ModelPars[iM_wJ2] + t18 + MU__[1] / ModelPars[iM_tau__2];
    real_type t25  = U__[iU_x3__o];
    real_type t29  = ALIAS_x3__oControl_D_1(t25, -0.1e-2, 100);
    result__[ 2   ] = 2 * (-X__[iX_x3] + t25) * ModelPars[iM_wJ3] + t29 + MU__[2] / ModelPars[iM_tau__3];
    real_type t36  = U__[iU_x4__o];
    real_type t40  = ALIAS_x4__oControl_D_1(t36, -0.1e-2, 100);
    result__[ 3   ] = 2 * (-X__[iX_x4] + t36) * ModelPars[iM_wJ4] + t40 + MU__[4] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DgDxpm_numRows() const { return 4; }
  integer Farmer::DgDxpm_numCols() const { return 10; }
  integer Farmer::DgDxpm_nnz()     const { return 8; }

  void
  Farmer::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -2 * ModelPars[iM_wJ1];
    result__[ 1   ] = 1.0 / ModelPars[iM_tau__1];
    result__[ 2   ] = -2 * ModelPars[iM_wJ2];
    result__[ 3   ] = 1.0 / ModelPars[iM_tau__2];
    result__[ 4   ] = -2 * ModelPars[iM_wJ3];
    result__[ 5   ] = 1.0 / ModelPars[iM_tau__3];
    result__[ 6   ] = -2 * ModelPars[iM_wJ4];
    result__[ 7   ] = 1.0 / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DgDu_numRows() const { return 4; }
  integer Farmer::DgDu_numCols() const { return 4; }
  integer Farmer::DgDu_nnz()     const { return 4; }

  void
  Farmer::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_x1__oControl_D_1_1(U__[iU_x1__o], -0.1e-2, 100);
    result__[ 0   ] = 2 * ModelPars[iM_wJ1] + t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(U__[iU_x2__o], -0.1e-2, 100);
    result__[ 1   ] = 2 * ModelPars[iM_wJ2] + t8;
    real_type t12  = ALIAS_x3__oControl_D_1_1(U__[iU_x3__o], -0.1e-2, 100);
    result__[ 2   ] = 2 * ModelPars[iM_wJ3] + t12;
    real_type t16  = ALIAS_x4__oControl_D_1_1(U__[iU_x4__o], -0.1e-2, 100);
    result__[ 3   ] = 2 * ModelPars[iM_wJ4] + t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 4, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  Farmer::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "Farmer::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: Farmer_Methods_controls.cc
