/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_problem.cc                                 |
 |                                                                       |
 |  version: 1.0   date 6/3/2021                                         |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burnDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn::continuationStep0( real_type s ) {
    ModelPars[iM_w_guess] = s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn::continuationStep1( real_type s ) {
    ModelPars[iM_w_nonlin] = s;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

#if 1
  real_type
  gtocX_2burn::H_eval(
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer        i_cell = CELL__.i_cell;
    real_type const * Q__ = CELL__.qM;
    real_type const * X__ = CELL__.xM;
    real_type const * L__ = CELL__.lambdaM;
    real_type const * U__ = CELL__.uM;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t8   = t3 * t1 + t6 * t5 + 1;
    real_type t9   = ray_positive(t8);
    real_type t12  = X__[iX_p];
    real_type t13  = Q__[iQ_zeta];
    real_type t15  = ModelPars[iM_time_i];
    real_type t17  = ModelPars[iM_time_f];
    real_type t19  = t15 * (1 - t13) + t17 * t13;
    real_type t20  = p_guess(t19);
    real_type t24  = pow(1.0 / t20 * t12 - 1, 2);
    real_type t25  = f_guess(t19);
    real_type t27  = pow(t1 - t25, 2);
    real_type t28  = g_guess(t19);
    real_type t30  = pow(t5 - t28, 2);
    real_type t32  = h_guess(t19);
    real_type t34  = pow(X__[iX_h] - t32, 2);
    real_type t36  = k_guess(t19);
    real_type t38  = pow(X__[iX_k] - t36, 2);
    real_type t39  = L_guess(t19, t15);
    real_type t41  = pow(t2 - t39, 2);
    real_type t45  = t17 - t15;
    real_type t47  = sqrt(t12);
    real_type t49  = ModelPars[iM_muS];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[iM_w_nonlin] / t50;
    real_type t54  = ray(t12, t1, t5, t2);
    real_type t55  = acceleration_r(t54, t49);
    real_type t67  = t8 * t8;
    real_type result__ = t9 + (t24 + t27 + t30 + t34 + t38 + t41) * (1 - ModelPars[iM_w_guess]) + t6 * t55 * t53 * t47 * t45 * L__[iL_lambda2__xo] - t3 * t55 * t53 * t47 * t45 * L__[iL_lambda3__xo] + t50 / t47 / t12 * t67 * t45 * L__[iL_lambda6__xo];
    return result__;
  }
#else
  real_type
  gtocX_2burn::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t8   = t3 * t1 + t6 * t5 + 1;
    real_type t9   = ray_positive(t8);
    real_type t12  = X__[iX_p];
    real_type t13  = Q__[iQ_zeta];
    real_type t15  = ModelPars[iM_time_i];
    real_type t17  = ModelPars[iM_time_f];
    real_type t19  = t15 * (1 - t13) + t17 * t13;
    real_type t20  = p_guess(t19);
    real_type t24  = pow(1.0 / t20 * t12 - 1, 2);
    real_type t25  = f_guess(t19);
    real_type t27  = pow(t1 - t25, 2);
    real_type t28  = g_guess(t19);
    real_type t30  = pow(t5 - t28, 2);
    real_type t32  = h_guess(t19);
    real_type t34  = pow(X__[iX_h] - t32, 2);
    real_type t36  = k_guess(t19);
    real_type t38  = pow(X__[iX_k] - t36, 2);
    real_type t39  = L_guess(t19, t15);
    real_type t41  = pow(t2 - t39, 2);
    real_type t45  = t17 - t15;
    real_type t47  = sqrt(t12);
    real_type t49  = ModelPars[iM_muS];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[iM_w_nonlin] / t50;
    real_type t54  = ray(t12, t1, t5, t2);
    real_type t55  = acceleration_r(t54, t49);
    real_type t67  = t8 * t8;
    real_type result__ = t9 + (t24 + t27 + t30 + t34 + t38 + t41) * (1 - ModelPars[iM_w_guess]) + t6 * t55 * t53 * t47 * t45 * L__[iL_lambda2__xo] - t3 * t55 * t53 * t47 * t45 * L__[iL_lambda3__xo] + t50 / t47 / t12 * t67 * t45 * L__[iL_lambda6__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }
#endif

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  gtocX_2burn::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    real_type result__ = ray_positive(t3 * X__[iX_f] + t6 * X__[iX_g] + 1);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  gtocX_2burn::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  gtocX_2burn::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t10  = t6 * (1 - t4) + ModelPars[iM_time_f] * t4;
    real_type t11  = p_guess(t10);
    real_type t15  = pow(1.0 / t11 * X__[iX_p] - 1, 2);
    real_type t17  = f_guess(t10);
    real_type t19  = pow(X__[iX_f] - t17, 2);
    real_type t21  = g_guess(t10);
    real_type t23  = pow(X__[iX_g] - t21, 2);
    real_type t25  = h_guess(t10);
    real_type t27  = pow(X__[iX_h] - t25, 2);
    real_type t29  = k_guess(t10);
    real_type t31  = pow(X__[iX_k] - t29, 2);
    real_type t33  = L_guess(t10, t6);
    real_type t35  = pow(X__[iX_L] - t33, 2);
    real_type result__ = (t15 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[iM_w_guess]);
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
  gtocX_2burn::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  gtocX_2burn::q_numEqns() const
  { return 1; }

  void
  gtocX_2burn::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
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

  integer
  gtocX_2burn::segmentLink_numEqns() const
  { return 0; }

  void
  gtocX_2burn::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  gtocX_2burn::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  gtocX_2burn::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  gtocX_2burn::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DsegmentLinkDxp_sparse(
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

  integer
  gtocX_2burn::jump_numEqns() const
  { return 12; }

  void
  gtocX_2burn::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XR__[iX_p] - XL__[iX_p];
    result__[ 1   ] = XR__[iX_f] - XL__[iX_f];
    result__[ 2   ] = XR__[iX_g] - XL__[iX_g];
    result__[ 3   ] = XR__[iX_h] - XL__[iX_h];
    result__[ 4   ] = XR__[iX_k] - XL__[iX_k];
    result__[ 5   ] = XR__[iX_L] - XL__[iX_L];
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

  integer
  gtocX_2burn::DjumpDxlp_numRows() const
  { return 12; }

  integer
  gtocX_2burn::DjumpDxlp_numCols() const
  { return 24; }

  integer
  gtocX_2burn::DjumpDxlp_nnz() const
  { return 24; }

  void
  gtocX_2burn::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
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
  gtocX_2burn::DjumpDxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
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
      Mechatronix::check_in_segment2( result__, "DjumpDxlp_sparse", 24, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  gtocX_2burn::post_numEqns() const
  { return 20; }

  void
  gtocX_2burn::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = Q__[iQ_zeta];
    result__[ 0   ] = ModelPars[iM_time_i] * (1 - t1) + ModelPars[iM_time_f] * t1;
    real_type t7   = X__[iX_p];
    real_type t8   = X__[iX_f];
    real_type t9   = X__[iX_g];
    real_type t10  = X__[iX_L];
    result__[ 1   ] = ray(t7, t8, t9, t10);
    real_type t11  = X__[iX_h];
    real_type t12  = X__[iX_k];
    real_type t13  = ModelPars[iM_retrograde];
    result__[ 2   ] = xPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 3   ] = yPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 4   ] = zPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 5   ] = xVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 6   ] = yVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 7   ] = zVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 8   ] = X_begin(result__[0]);
    result__[ 9   ] = Y_begin(result__[0]);
    result__[ 10  ] = Z_begin(result__[0]);
    result__[ 11  ] = VX_begin(result__[0]);
    result__[ 12  ] = VY_begin(result__[0]);
    result__[ 13  ] = VZ_begin(result__[0]);
    result__[ 14  ] = X_end(result__[0]);
    result__[ 15  ] = Y_end(result__[0]);
    result__[ 16  ] = Z_end(result__[0]);
    result__[ 17  ] = VX_end(result__[0]);
    result__[ 18  ] = VY_end(result__[0]);
    result__[ 19  ] = VZ_end(result__[0]);
    Mechatronix::check_in_segment( result__, "post_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::integrated_post_numEqns() const
  { return 0; }

  void
  gtocX_2burn::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_problem.cc
