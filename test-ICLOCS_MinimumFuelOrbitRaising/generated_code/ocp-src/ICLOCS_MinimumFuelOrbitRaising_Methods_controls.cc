/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_controls.cc             |
 |                                                                       |
 |  version: 1.0   date 21/11/2022                                       |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS_MinimumFuelOrbitRaising::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_vr];
    real_type t3   = UM__[0];
    real_type t4   = t3 * t3;
    real_type t7   = LM__[0];
    real_type t9   = LM__[1];
    real_type t10  = XL__[iX_vt];
    real_type t11  = t10 * t10;
    real_type t12  = XL__[iX_r];
    real_type t13  = 1.0 / t12;
    real_type t15  = t12 * t12;
    real_type t17  = ModelPars[iM_T];
    real_type t18  = sin(t3);
    real_type t19  = t18 * t17;
    real_type t21  = mass(QL__[iQ_zeta]);
    real_type t22  = 1.0 / t21;
    real_type t26  = LM__[2];
    real_type t29  = cos(t3);
    real_type t30  = t29 * t17;
    real_type t34  = XR__[iX_vr];
    real_type t36  = XR__[iX_vt];
    real_type t37  = t36 * t36;
    real_type t38  = XR__[iX_r];
    real_type t39  = 1.0 / t38;
    real_type t41  = t38 * t38;
    real_type t44  = mass(QR__[iQ_zeta]);
    real_type t45  = 1.0 / t44;
    real_type result__ = -t1 + 2 * t4 * ModelPars[iM_epsilon] + t1 * t7 + (t13 * t11 - 1.0 / t15 + t22 * t19) * t9 + (-t13 * t10 * t1 + t22 * t30) * t26 - t34 + t34 * t7 + (t39 * t37 - 1.0 / t41 + t45 * t19) * t9 + (-t39 * t36 * t34 + t45 * t30) * t26;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::g_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_T];
    real_type t4   = UM__[0];
    real_type t5   = cos(t4);
    real_type t6   = t5 * t2 * LM__[1];
    real_type t9   = sin(t4);
    real_type t10  = t9 * t2 * LM__[2];
    real_type t12  = t4 * ModelPars[iM_epsilon];
    real_type t14  = mass(QL__[iQ_zeta]);
    real_type t21  = mass(QR__[iQ_zeta]);
    result__[ 0   ] = 1.0 / t14 * (2 * t14 * t12 - t10 + t6) + 1.0 / t21 * (2 * t21 * t12 - t10 + t6);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxlxlp_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxlxlp_numCols() const { return 12; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxlxlp_nnz()     const { return 4; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_T];
    real_type t2   = UM__[0];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t6   = mass(QL__[iQ_zeta]);
    real_type t7   = 1.0 / t6;
    real_type t11  = mass(QR__[iQ_zeta]);
    real_type t12  = 1.0 / t11;
    result__[ 0   ] = 0.5e0 * t7 * t4 + 0.5e0 * t12 * t4;
    real_type t15  = sin(t2);
    real_type t16  = t15 * t1;
    result__[ 1   ] = -0.5e0 * t7 * t16 - 0.5e0 * t12 * t16;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_numCols() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_nnz()     const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_T];
    real_type t4   = UM__[0];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t2 * LM__[1];
    real_type t9   = cos(t4);
    real_type t10  = t9 * t2 * LM__[2];
    real_type t11  = ModelPars[iM_epsilon];
    real_type t13  = mass(QL__[iQ_zeta]);
    real_type t20  = mass(QR__[iQ_zeta]);
    result__[ 0   ] = 1.0 / t13 * (2 * t13 * t11 - t10 - t6) + 1.0 / t20 * (2 * t20 * t11 - t10 - t6);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 1, i_segment );
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
  ICLOCS_MinimumFuelOrbitRaising::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "ICLOCS_MinimumFuelOrbitRaising::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  ICLOCS_MinimumFuelOrbitRaising::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_vr];
    real_type t4   = pow(V__[0] - t2, 2);
    real_type t6   = X__[iX_vt];
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_r];
    real_type t9   = 1.0 / t8;
    real_type t11  = t8 * t8;
    real_type t13  = ModelPars[iM_T];
    real_type t14  = U__[iU_theta];
    real_type t15  = sin(t14);
    real_type t18  = mass(Q__[iQ_zeta]);
    real_type t19  = 1.0 / t18;
    real_type t22  = pow(V__[1] - t9 * t7 + 1.0 / t11 - t19 * t15 * t13, 2);
    real_type t26  = cos(t14);
    real_type t30  = pow(-t19 * t26 * t13 + t9 * t6 * t2 + V__[2], 2);
    real_type result__ = t4 + t22 + t30;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::DmDu_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_vt];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_r];
    real_type t5   = 1.0 / t4;
    real_type t7   = t4 * t4;
    real_type t9   = ModelPars[iM_T];
    real_type t10  = U__[iU_theta];
    real_type t11  = sin(t10);
    real_type t14  = mass(Q__[iQ_zeta]);
    real_type t15  = 1.0 / t14;
    real_type t19  = cos(t10);
    result__[ 0   ] = -2 * t15 * t19 * t9 * (V__[1] - t5 * t3 + 1.0 / t7 - t15 * t11 * t9) + 2 * t15 * t11 * t9 * (-t15 * t19 * t9 + t5 * t2 * X__[iX_vr] + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DmDuu_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DmDuu_numCols() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DmDuu_nnz()     const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_T];
    real_type t2   = t1 * t1;
    real_type t3   = U__[iU_theta];
    real_type t4   = cos(t3);
    real_type t5   = t4 * t4;
    real_type t8   = mass(Q__[iQ_zeta]);
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t13  = X__[iX_vt];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_r];
    real_type t16  = 1.0 / t15;
    real_type t18  = t15 * t15;
    real_type t20  = sin(t3);
    real_type t22  = 1.0 / t8;
    real_type t28  = t20 * t20;
    result__[ 0   ] = 2 * t10 * t5 * t2 + 2 * t22 * t20 * t1 * (V__[1] - t16 * t14 + 1.0 / t18 - t22 * t20 * t1) + 2 * t10 * t28 * t2 + 2 * t22 * t4 * t1 * (-t22 * t4 * t1 + t16 * t13 * X__[iX_vr] + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_controls.cc
