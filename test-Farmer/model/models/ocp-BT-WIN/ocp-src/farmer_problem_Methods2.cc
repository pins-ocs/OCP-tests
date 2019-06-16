/*-----------------------------------------------------------------------*\
 |  file: farmer_problem_Methods.cc                                      |
 |                                                                       |
 |  version: 1.0   date 16/6/2019                                        |
 |                                                                       |
 |  Copyright (C) 2019                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "farmer_problem.hh"
#include "farmer_problem_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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


namespace farmer_problemDefine {

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  farmer_problem::H_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t1   = X__[1];
    real_type t2   = X__[4];
    real_type t4   = LimitX2X4(0.12e0 - t1 - t2);
    real_type t6   = ModelPars[10];
    real_type t8   = X__[0];
    real_type t10  = ModelPars[11];
    real_type t13  = ModelPars[12];
    real_type t15  = X__[2];
    real_type t17  = ModelPars[13];
    real_type t20  = ModelPars[3];
    real_type t21  = ModelPars[4];
    real_type t22  = Q__[0];
    real_type t34  = pow(t8 / t6 + t1 / t10 + t15 / t13 + t2 / t17 - 1.0 / (-t21 + t20) * (ModelPars[0] * (t20 - t21 + t22 - 1) - (t22 - 1) * ModelPars[1]), 2);
    real_type t36  = t8 * t8;
    real_type t38  = t1 * t1;
    real_type t40  = t15 * t15;
    real_type t42  = t2 * t2;
    real_type t46  = -t8 + U__[0];
    real_type t47  = t46 * t46;
    real_type t51  = -t1 + U__[1];
    real_type t52  = t51 * t51;
    real_type t56  = -t15 + U__[2];
    real_type t57  = t56 * t56;
    real_type t61  = -t2 + U__[3];
    real_type t62  = t61 * t61;
    return t4 + t34 * ModelPars[18] + t36 * t6 + t38 * t10 + t40 * t13 + t42 * t17 + t47 * ModelPars[14] + t52 * ModelPars[15] + t57 * ModelPars[16] + t62 * ModelPars[17] + 1.0 / ModelPars[5] * t46 * L__[0] + 1.0 / ModelPars[6] * t51 * L__[1] + 1.0 / ModelPars[7] * t56 * L__[2] - 1.0 / ModelPars[8] * (-t15 + t2) * L__[3] + 1.0 / ModelPars[9] * t61 * L__[4];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  farmer_problem::penalties_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    return LimitX2X4(0.12e0 - X__[1] - X__[4]);
  }

  real_type
  farmer_problem::control_penalties_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t2   = x1__oControl(U__[0], -0.1e-2, 100);
    real_type t4   = x2__oControl(U__[1], -0.1e-2, 100);
    real_type t6   = x3__oControl(U__[2], -0.1e-2, 100);
    real_type t8   = x4__oControl(U__[3], -0.1e-2, 100);
    return t2 + t4 + t6 + t8;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  farmer_problem::lagrange_target(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t2   = ModelPars[10];
    real_type t4   = X__[0];
    real_type t6   = ModelPars[11];
    real_type t8   = X__[1];
    real_type t10  = ModelPars[12];
    real_type t12  = X__[2];
    real_type t14  = ModelPars[13];
    real_type t16  = X__[4];
    real_type t18  = ModelPars[3];
    real_type t19  = ModelPars[4];
    real_type t20  = Q__[0];
    real_type t32  = pow(t4 / t2 + t8 / t6 + t12 / t10 + t16 / t14 - 1.0 / (-t19 + t18) * (ModelPars[0] * (t18 - t19 + t20 - 1) - (t20 - 1) * ModelPars[1]), 2);
    real_type t34  = t4 * t4;
    real_type t36  = t8 * t8;
    real_type t38  = t12 * t12;
    real_type t40  = t16 * t16;
    real_type t45  = pow(-t4 + U__[0], 2);
    real_type t50  = pow(-t8 + U__[1], 2);
    real_type t55  = pow(-t12 + U__[2], 2);
    real_type t60  = pow(-t16 + U__[3], 2);
    return t38 * t10 + t40 * t14 + t34 * t2 + t32 * ModelPars[18] + t36 * t6 + t45 * ModelPars[14] + t50 * ModelPars[15] + t55 * ModelPars[16] + t60 * ModelPars[17];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  farmer_problem::mayer_target(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    P_const_pointer_type P__
  ) const {
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    return 0;
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  farmer_problem::q_numEqns() const
  { return 1; }

  void
  farmer_problem::q_eval(
    integer        i_node,
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    result__[ 0   ] = s;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__.pointer(),"q_eval",1);
    #endif
  }

}

// EOF: farmer_problem_Methods.cc
