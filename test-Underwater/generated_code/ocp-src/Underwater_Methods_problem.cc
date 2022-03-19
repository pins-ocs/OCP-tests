/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_problem.cc                                  |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  Underwater::continuation_step_0( real_type s ) {
    ModelPars[iM_inertia] = 0.15e1 - 0.138e1 * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  Underwater::continuation_step_1( real_type s ) {
    real_type epsi = (1 - s) * ModelPars[iM_epsi_max] + s * ModelPars[iM_epsi_min];
    u1Control.update_epsilon(epsi);
    u2Control.update_epsilon(epsi);
    u3Control.update_epsilon(epsi);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Underwater::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t4   = X__[iX_vx];
    real_type t5   = X__[iX_theta];
    real_type t6   = cos(t5);
    real_type t8   = X__[iX_vz];
    real_type t9   = sin(t5);
    real_type t21  = X__[iX_Omega];
    real_type t26  = ModelPars[iM_m1];
    real_type t27  = 1.0 / t26;
    real_type t30  = ModelPars[iM_m3];
    real_type t38  = 1.0 / t30;
    real_type t49  = 1.0 / ModelPars[iM_inertia];
    real_type result__ = (t6 * t4 + t9 * t8) * t2 * L__[iL_lambda1__xo] + (-t9 * t4 + t6 * t8) * t2 * L__[iL_lambda2__xo] + t21 * t2 * L__[iL_lambda3__xo] + (-t27 * t30 * t21 * t8 + t27 * U__[iU_u1]) * t2 * L__[iL_lambda4__xo] + (t38 * t26 * t21 * t4 + t38 * U__[iU_u2]) * t2 * L__[iL_lambda5__xo] + (t49 * U__[iU_u3] + t49 * (t30 - t26) * t8 * t4) * t2 * L__[iL_lambda6__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  Underwater::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Underwater::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = u1Control(U__[iU_u1], -1, 1);
    real_type t6   = u2Control(U__[iU_u2], -1, 1);
    real_type t9   = u3Control(U__[iU_u3], -1, 1);
    real_type result__ = t3 * t1 + t6 * t1 + t9 * t1;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Underwater::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  Underwater::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  Underwater::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = P__[iP_T];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::DmayerDxxp_numEqns() const { return 13; }

  void
  Underwater::DmayerDxxp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 13, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer Underwater::DlagrangeDxup_numEqns() const { return 10; }

  void
  Underwater::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 10, i_segment );
  }

  /*\
   |   ___ ____   ___  ____ _____
   |  |_ _|  _ \ / _ \|  _ \_   _|
   |   | || |_) | | | | |_) || |
   |   | ||  __/| |_| |  __/ | |
   |  |___|_|    \___/|_|    |_|
  \*/
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::IPOPT_hess_numRows() const { return 10; }
  integer Underwater::IPOPT_hess_numCols() const { return 10; }
  integer Underwater::IPOPT_hess_nnz()     const { return 25; }

  void
  Underwater::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 3   ;
    iIndex[10] = 4   ; jIndex[10] = 5   ;
    iIndex[11] = 4   ; jIndex[11] = 9   ;
    iIndex[12] = 5   ; jIndex[12] = 3   ;
    iIndex[13] = 5   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 9   ;
    iIndex[15] = 6   ; jIndex[15] = 9   ;
    iIndex[16] = 7   ; jIndex[16] = 9   ;
    iIndex[17] = 8   ; jIndex[17] = 9   ;
    iIndex[18] = 9   ; jIndex[18] = 2   ;
    iIndex[19] = 9   ; jIndex[19] = 3   ;
    iIndex[20] = 9   ; jIndex[20] = 4   ;
    iIndex[21] = 9   ; jIndex[21] = 5   ;
    iIndex[22] = 9   ; jIndex[22] = 6   ;
    iIndex[23] = 9   ; jIndex[23] = 7   ;
    iIndex[24] = 9   ; jIndex[24] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::IPOPT_hess_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            sigma__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = sin(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = cos(t5);
    real_type t11  = -t4 * t6 - t8 * t9;
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t2 * t13;
    real_type t17  = -t4 * t9 + t6 * t8;
    result__[ 0   ] = t11 * t3 + t14 * t17;
    result__[ 1   ] = -t14 * t9 - t3 * t6;
    result__[ 2   ] = -t14 * t6 + t3 * t9;
    result__[ 3   ] = -t1 * t17 + t11 * t13;
    result__[ 4   ] = result__[1];
    real_type t26  = L__[iL_lambda6__xo];
    real_type t28  = ModelPars[iM_m3];
    real_type t29  = ModelPars[iM_m1];
    real_type t32  = 1.0 / ModelPars[iM_inertia];
    real_type t33  = t32 * (t28 - t29);
    result__[ 5   ] = t33 * t2 * t26;
    real_type t34  = L__[iL_lambda5__xo];
    real_type t36  = 1.0 / t28;
    real_type t37  = t36 * t29;
    result__[ 6   ] = t37 * t2 * t34;
    real_type t40  = X__[iX_Omega];
    result__[ 7   ] = t26 * t33 * t4 + t34 * t37 * t40 + t1 * t9 - t13 * t6;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    real_type t45  = L__[iL_lambda4__xo];
    real_type t47  = 1.0 / t29;
    real_type t48  = t47 * t28;
    result__[ 10  ] = -t48 * t2 * t45;
    result__[ 11  ] = t26 * t33 * t8 - t40 * t45 * t48 + t1 * t6 + t13 * t9;
    result__[ 12  ] = result__[6];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = t34 * t37 * t8 - t4 * t45 * t48 + L__[iL_lambda3__xo];
    result__[ 15  ] = t47 * t45;
    result__[ 16  ] = t36 * t34;
    result__[ 17  ] = t32 * t26;
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[7];
    result__[ 20  ] = result__[11];
    result__[ 21  ] = result__[14];
    result__[ 22  ] = result__[15];
    result__[ 23  ] = result__[16];
    result__[ 24  ] = result__[17];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 25, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  Underwater::q_numEqns() const
  { return 1; }

  void
  Underwater::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer Underwater::segmentLink_numEqns() const { return 0; }

  void
  Underwater::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::DsegmentLinkDxp_numRows() const { return 0; }
  integer Underwater::DsegmentLinkDxp_numCols() const { return 0; }
  integer Underwater::DsegmentLinkDxp_nnz() const { return 0; }

  void
  Underwater::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer Underwater::jump_numEqns() const { return 12; }

  void
  Underwater::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_x] - XL__[iX_x];
    result__[ 1   ] = XR__[iX_z] - XL__[iX_z];
    result__[ 2   ] = XR__[iX_theta] - XL__[iX_theta];
    result__[ 3   ] = XR__[iX_vx] - XL__[iX_vx];
    result__[ 4   ] = XR__[iX_vz] - XL__[iX_vz];
    result__[ 5   ] = XR__[iX_Omega] - XL__[iX_Omega];
    result__[ 6   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 7   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 8   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 9   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 10  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 11  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DjumpDxlxlp_numRows() const { return 12; }
  integer Underwater::DjumpDxlxlp_numCols() const { return 25; }
  integer Underwater::DjumpDxlxlp_nnz()     const { return 24; }

  void
  Underwater::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 12  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 13  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 14  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 16  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 17  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 18  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 19  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 20  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 21  ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 22  ;
    iIndex[22] = 11  ; jIndex[22] = 11  ;
    iIndex[23] = 11  ; jIndex[23] = 23  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    result__[ 20  ] = -1;
    result__[ 21  ] = 1;
    result__[ 22  ] = -1;
    result__[ 23  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 24, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer Underwater::post_numEqns() const { return 0; }

  void
  Underwater::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::integrated_post_numEqns() const { return 0; }

  void
  Underwater::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: Underwater_Methods_problem.cc
