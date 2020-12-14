/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods.cc                                    |
 |                                                                       |
 |  version: 1.0   date 14/12/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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


namespace gtocX_2burn_parsDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  gtocX_2burn_pars::Hx_numEqns() const
  { return 3; }

  void
  gtocX_2burn_pars::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[2];
    real_type t3   = cos(t2);
    real_type t5   = X__[1];
    real_type t6   = sin(t2);
    real_type t8   = t3 * t1 + t6 * t5 + 1;
    real_type t9   = ALIAS_ray_positive_D(t8);
    real_type t12  = 1 - ModelPars[3];
    real_type t13  = Q__[0];
    real_type t15  = ModelPars[2];
    real_type t17  = ModelPars[1];
    real_type t19  = t15 * (1 - t13) + t17 * t13;
    real_type t20  = f_guess(t19);
    real_type t25  = t17 - t15;
    real_type t26  = t25 * L__[0];
    real_type t27  = P__[0];
    real_type t28  = sqrt(t27);
    real_type t29  = ModelPars[0];
    real_type t30  = sqrt(t29);
    real_type t31  = 1.0 / t30;
    real_type t32  = t31 * t28;
    real_type t33  = t32 * t26;
    real_type t34  = ModelPars[6];
    real_type t35  = ray(t27, t1, t5, t2);
    real_type t36  = acceleration_r_D_1(t35, t29);
    real_type t37  = t36 * t34;
    real_type t38  = ray_D_2(t27, t1, t5, t2);
    real_type t43  = t25 * L__[1];
    real_type t44  = t32 * t43;
    real_type t50  = t8 * t25 * L__[2];
    real_type t53  = t30 / t28 / t27;
    result__[ 0   ] = t3 * t9 + (2 * t1 - 2 * t20) * t12 + t6 * t38 * t37 * t33 - t3 * t38 * t37 * t44 + 2 * t3 * t53 * t50;
    real_type t58  = g_guess(t19);
    real_type t62  = ray_D_3(t27, t1, t5, t2);
    result__[ 1   ] = t6 * t9 + (2 * t5 - 2 * t58) * t12 + t6 * t62 * t37 * t33 - t3 * t62 * t37 * t44 + 2 * t6 * t53 * t50;
    real_type t74  = -t6 * t1 + t3 * t5;
    real_type t76  = L_guess(t19, t15);
    real_type t80  = ray_D_4(t27, t1, t5, t2);
    real_type t85  = t34 * t31;
    real_type t86  = acceleration_r(t35, t29);
    result__[ 2   ] = t74 * t9 + (2 * t2 - 2 * t76) * t12 + t6 * t80 * t37 * t33 + t3 * t86 * t85 * t28 * t26 - t3 * t80 * t37 * t44 + t6 * t86 * t85 * t28 * t43 + 2 * t74 * t53 * t50;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DHxDx_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHxDx_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHxDx_nnz() const
  { return 9; }

  void
  gtocX_2burn_pars::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
  }

  void
  gtocX_2burn_pars::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[2];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t5   = X__[1];
    real_type t6   = sin(t2);
    real_type t7   = t6 * t5;
    real_type t8   = 1 + t4 + t7;
    real_type t9   = ALIAS_ray_positive_DD(t8);
    real_type t10  = t3 * t3;
    real_type t13  = 2 * ModelPars[3];
    real_type t17  = ModelPars[1] - ModelPars[2];
    real_type t18  = t17 * L__[0];
    real_type t19  = P__[0];
    real_type t20  = sqrt(t19);
    real_type t21  = ModelPars[0];
    real_type t22  = sqrt(t21);
    real_type t23  = 1.0 / t22;
    real_type t24  = t23 * t20;
    real_type t25  = t24 * t18;
    real_type t26  = ModelPars[6];
    real_type t27  = ray(t19, t1, t5, t2);
    real_type t28  = acceleration_r_D_1_1(t27, t21);
    real_type t29  = t28 * t26;
    real_type t30  = ray_D_2(t19, t1, t5, t2);
    real_type t31  = t30 * t30;
    real_type t35  = acceleration_r_D_1(t27, t21);
    real_type t36  = t35 * t26;
    real_type t37  = ray_D_2_2(t19, t1, t5, t2);
    real_type t42  = t17 * L__[1];
    real_type t43  = t24 * t42;
    real_type t51  = t17 * L__[2];
    real_type t53  = 1.0 / t20 / t19;
    result__[ 0   ] = 2 * t10 * t22 * t51 * t53 + t25 * t29 * t31 * t6 + t25 * t36 * t37 * t6 - t29 * t3 * t31 * t43 - t3 * t36 * t37 * t43 + t10 * t9 - t13 + 2;
    real_type t60  = ray_D_3(t19, t1, t5, t2);
    real_type t61  = t30 * t60;
    real_type t65  = ray_D_2_3(t19, t1, t5, t2);
    real_type t76  = t22 * t53;
    real_type t77  = t3 * t76;
    result__[ 1   ] = t25 * t29 * t6 * t61 + t25 * t36 * t6 * t65 - t29 * t3 * t43 * t61 - t3 * t36 * t43 * t65 + t3 * t6 * t9 + 2 * t51 * t6 * t77;
    real_type t82  = -t1 * t6 + t3 * t5;
    real_type t83  = t82 * t9;
    real_type t85  = ALIAS_ray_positive_D(t8);
    real_type t87  = ray_D_4(t19, t1, t5, t2);
    real_type t88  = t30 * t87;
    real_type t92  = ray_D_2_4(t19, t1, t5, t2);
    real_type t108 = t82 * t51;
    real_type t111 = t8 * t51;
    real_type t112 = t6 * t76;
    result__[ 2   ] = t25 * t29 * t6 * t88 + t25 * t3 * t30 * t36 + t25 * t36 * t6 * t92 - t29 * t3 * t43 * t88 - t3 * t36 * t43 * t92 + t30 * t36 * t43 * t6 + 2 * t108 * t77 - 2 * t111 * t112 + t3 * t83 - t6 * t85;
    result__[ 3   ] = result__[1];
    real_type t115 = t6 * t6;
    real_type t117 = t60 * t60;
    real_type t121 = ray_D_3_3(t19, t1, t5, t2);
    result__[ 4   ] = 2 * t115 * t22 * t51 * t53 + t117 * t25 * t29 * t6 - t117 * t29 * t3 * t43 + t121 * t25 * t36 * t6 - t121 * t3 * t36 * t43 + t115 * t9 - t13 + 2;
    real_type t137 = t60 * t87;
    real_type t141 = ray_D_3_4(t19, t1, t5, t2);
    result__[ 5   ] = t137 * t25 * t29 * t6 - t137 * t29 * t3 * t43 + t141 * t25 * t36 * t6 - t141 * t3 * t36 * t43 + t25 * t3 * t36 * t60 + t36 * t43 * t6 * t60 + 2 * t108 * t112 + 2 * t111 * t77 + t3 * t85 + t6 * t83;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t161 = t82 * t82;
    real_type t163 = -t4 - t7;
    real_type t165 = t87 * t87;
    real_type t169 = ray_D_4_4(t19, t1, t5, t2);
    real_type t178 = t26 * t23;
    real_type t179 = acceleration_r(t27, t21);
    result__[ 8   ] = -t178 * t179 * t18 * t20 * t6 + t178 * t179 * t20 * t3 * t42 + 2 * t161 * t22 * t51 * t53 + t165 * t25 * t29 * t6 - t165 * t29 * t3 * t43 + t169 * t25 * t36 * t6 - t169 * t3 * t36 * t43 + 2 * t25 * t3 * t36 * t87 + 2 * t36 * t43 * t6 * t87 + 2 * t111 * t163 * t76 + t161 * t9 + t163 * t85 - t13 + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DHxDp_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHxDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHxDp_nnz() const
  { return 3; }

  void
  gtocX_2burn_pars::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = ModelPars[1] - ModelPars[2];
    real_type t5   = t4 * L__[0];
    real_type t6   = P__[0];
    real_type t7   = sqrt(t6);
    real_type t8   = 1.0 / t7;
    real_type t9   = ModelPars[0];
    real_type t10  = sqrt(t9);
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t8;
    real_type t13  = t12 * t5;
    real_type t14  = ModelPars[6];
    real_type t15  = X__[0];
    real_type t16  = X__[1];
    real_type t17  = X__[2];
    real_type t18  = ray(t6, t15, t16, t17);
    real_type t19  = acceleration_r_D_1(t18, t9);
    real_type t20  = t19 * t14;
    real_type t21  = ray_D_2(t6, t15, t16, t17);
    real_type t22  = sin(t17);
    real_type t27  = t11 * t7;
    real_type t28  = t27 * t5;
    real_type t29  = acceleration_r_D_1_1(t18, t9);
    real_type t30  = t29 * t14;
    real_type t31  = ray_D_1(t6, t15, t16, t17);
    real_type t32  = t21 * t31;
    real_type t36  = ray_D_1_2(t6, t15, t16, t17);
    real_type t41  = t4 * L__[1];
    real_type t42  = t12 * t41;
    real_type t43  = cos(t17);
    real_type t48  = t27 * t41;
    real_type t60  = (t43 * t15 + t22 * t16 + 1) * t4 * L__[2];
    real_type t61  = t6 * t6;
    real_type t64  = t10 / t7 / t61;
    result__[ 0   ] = t22 * t21 * t20 * t13 / 2 + t22 * t32 * t30 * t28 + t22 * t36 * t20 * t28 - t43 * t21 * t20 * t42 / 2 - t43 * t32 * t30 * t48 - t43 * t36 * t20 * t48 - 3 * t43 * t64 * t60;
    real_type t68  = ray_D_3(t6, t15, t16, t17);
    real_type t73  = t68 * t31;
    real_type t77  = ray_D_1_3(t6, t15, t16, t17);
    result__[ 1   ] = t22 * t68 * t20 * t13 / 2 + t22 * t73 * t30 * t28 + t22 * t77 * t20 * t28 - t43 * t68 * t20 * t42 / 2 - t43 * t73 * t30 * t48 - t43 * t77 * t20 * t48 - 3 * t22 * t64 * t60;
    real_type t94  = ray_D_4(t6, t15, t16, t17);
    real_type t99  = t94 * t31;
    real_type t103 = ray_D_1_4(t6, t15, t16, t17);
    real_type t108 = t14 * t11;
    real_type t109 = acceleration_r(t18, t9);
    result__[ 2   ] = t22 * t94 * t20 * t13 / 2 + t22 * t99 * t30 * t28 + t22 * t103 * t20 * t28 + t43 * t109 * t108 * t8 * t5 / 2 + t43 * t31 * t20 * t28 - t43 * t94 * t20 * t42 / 2 - t43 * t99 * t30 * t48 - t43 * t103 * t20 * t48 + t22 * t109 * t108 * t8 * t41 / 2 + t22 * t31 * t20 * t48 - 3 * (-t22 * t15 + t43 * t16) * t64 * t60;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 3, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  gtocX_2burn_pars::Hu_numEqns() const
  { return 0; }

  void
  gtocX_2burn_pars::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DHuDx_numRows() const
  { return 0; }

  integer
  gtocX_2burn_pars::DHuDx_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHuDx_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DHuDp_numRows() const
  { return 0; }

  integer
  gtocX_2burn_pars::DHuDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHuDp_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  gtocX_2burn_pars::Hp_numEqns() const
  { return 3; }

  void
  gtocX_2burn_pars::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = 1 - ModelPars[3];
    real_type t3   = P__[0];
    real_type t4   = p_guess(0);
    real_type t5   = 1.0 / t4;
    real_type t14  = ModelPars[1] - ModelPars[2];
    real_type t15  = t14 * L__[0];
    real_type t16  = sqrt(t3);
    real_type t17  = 1.0 / t16;
    real_type t19  = ModelPars[0];
    real_type t20  = sqrt(t19);
    real_type t21  = 1.0 / t20;
    real_type t22  = ModelPars[6];
    real_type t23  = t22 * t21;
    real_type t24  = X__[0];
    real_type t25  = X__[1];
    real_type t26  = X__[2];
    real_type t27  = ray(t3, t24, t25, t26);
    real_type t28  = acceleration_r(t27, t19);
    real_type t29  = sin(t26);
    real_type t34  = t21 * t16;
    real_type t36  = acceleration_r_D_1(t27, t19);
    real_type t37  = t36 * t22;
    real_type t38  = ray_D_1(t3, t24, t25, t26);
    real_type t43  = t14 * L__[1];
    real_type t45  = cos(t26);
    real_type t59  = pow(t45 * t24 + t29 * t25 + 1, 2);
    real_type t60  = t3 * t3;
    result__[ 0   ] = 2 * t5 * (t3 * t5 - 1) * t2 + t29 * t28 * t23 * t17 * t15 / 2 + t29 * t38 * t37 * t34 * t15 - t45 * t28 * t23 * t17 * t43 / 2 - t45 * t38 * t37 * t34 * t43 - 3.0 / 2.0 * t20 / t16 / t60 * t59 * t14 * L__[2];
    real_type t68  = h_guess(0);
    result__[ 1   ] = (2 * P__[1] - 2 * t68) * t2;
    real_type t72  = k_guess(0);
    result__[ 2   ] = (2 * P__[2] - 2 * t72) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DHpDp_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHpDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DHpDp_nnz() const
  { return 3; }

  void
  gtocX_2burn_pars::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = 1 - ModelPars[3];
    real_type t3   = p_guess(0);
    real_type t4   = t3 * t3;
    real_type t11  = ModelPars[1] - ModelPars[2];
    real_type t12  = t11 * L__[0];
    real_type t13  = P__[0];
    real_type t14  = sqrt(t13);
    real_type t16  = 1.0 / t14 / t13;
    real_type t18  = ModelPars[0];
    real_type t19  = sqrt(t18);
    real_type t20  = 1.0 / t19;
    real_type t21  = ModelPars[6];
    real_type t22  = t21 * t20;
    real_type t23  = X__[0];
    real_type t24  = X__[1];
    real_type t25  = X__[2];
    real_type t26  = ray(t13, t23, t24, t25);
    real_type t27  = acceleration_r(t26, t18);
    real_type t28  = sin(t25);
    real_type t34  = t20 / t14;
    real_type t36  = acceleration_r_D_1(t26, t18);
    real_type t37  = t36 * t21;
    real_type t38  = ray_D_1(t13, t23, t24, t25);
    real_type t42  = t20 * t14;
    real_type t43  = t42 * t12;
    real_type t44  = acceleration_r_D_1_1(t26, t18);
    real_type t45  = t44 * t21;
    real_type t46  = t38 * t38;
    real_type t50  = ray_D_1_1(t13, t23, t24, t25);
    real_type t55  = t11 * L__[1];
    real_type t57  = cos(t25);
    real_type t66  = t42 * t55;
    real_type t78  = pow(t57 * t23 + t28 * t24 + 1, 2);
    real_type t79  = t13 * t13;
    result__[ 0   ] = 2 / t4 * t2 - t28 * t27 * t22 * t16 * t12 / 4 + t28 * t38 * t37 * t34 * t12 + t28 * t46 * t45 * t43 + t28 * t50 * t37 * t43 + t57 * t27 * t22 * t16 * t55 / 4 - t57 * t38 * t37 * t34 * t55 - t57 * t46 * t45 * t66 - t57 * t50 * t37 * t66 + 0.15e2 / 4.0 * t19 / t14 / t79 / t13 * t78 * t11 * L__[2];
    result__[ 1   ] = 2 * t2;
    result__[ 2   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse" ,3, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  integer
  gtocX_2burn_pars::eta_numEqns() const
  { return 3; }

  void
  gtocX_2burn_pars::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DetaDx_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DetaDx_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DetaDx_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DetaDp_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DetaDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DetaDp_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  gtocX_2burn_pars::nu_numEqns() const
  { return 3; }

  void
  gtocX_2burn_pars::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DnuDx_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DnuDx_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DnuDx_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DnuDp_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::DnuDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::DnuDp_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_pars_Methods.cc
