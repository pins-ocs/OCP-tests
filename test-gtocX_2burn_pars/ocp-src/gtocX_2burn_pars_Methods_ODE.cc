/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods.cc                                    |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  gtocX_2burn_pars::rhs_ode_numEqns() const
  { return 3; }

  void
  gtocX_2burn_pars::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = ModelPars[1] - ModelPars[2];
    real_type t4   = P__[0];
    real_type t5   = sqrt(t4);
    real_type t7   = ModelPars[0];
    real_type t8   = sqrt(t7);
    real_type t10  = 1.0 / t8 * t5 * t3;
    real_type t12  = X__[0];
    real_type t13  = X__[1];
    real_type t14  = X__[2];
    real_type t15  = ray(t4, t12, t13, t14);
    real_type t16  = acceleration_r(t15, t7);
    real_type t17  = t16 * ModelPars[6];
    real_type t18  = sin(t14);
    result__[ 0   ] = t18 * t17 * t10;
    real_type t20  = cos(t14);
    result__[ 1   ] = -t20 * t17 * t10;
    real_type t26  = pow(t20 * t12 + t18 * t13 + 1, 2);
    result__[ 2   ] = t8 / t5 / t4 * t26 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::Drhs_odeDx_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::Drhs_odeDx_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::Drhs_odeDx_nnz() const
  { return 9; }

  void
  gtocX_2burn_pars::Drhs_odeDx_pattern(
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = ModelPars[1] - ModelPars[2];
    real_type t4   = P__[0];
    real_type t5   = sqrt(t4);
    real_type t7   = ModelPars[0];
    real_type t8   = sqrt(t7);
    real_type t10  = 1.0 / t8 * t5 * t3;
    real_type t11  = ModelPars[6];
    real_type t12  = X__[0];
    real_type t13  = X__[1];
    real_type t14  = X__[2];
    real_type t15  = ray(t4, t12, t13, t14);
    real_type t16  = acceleration_r_D_1(t15, t7);
    real_type t17  = t16 * t11;
    real_type t18  = ray_D_2(t4, t12, t13, t14);
    real_type t19  = sin(t14);
    result__[ 0   ] = t19 * t18 * t17 * t10;
    real_type t22  = ray_D_3(t4, t12, t13, t14);
    result__[ 1   ] = t19 * t22 * t17 * t10;
    real_type t25  = ray_D_4(t4, t12, t13, t14);
    real_type t29  = acceleration_r(t15, t7);
    real_type t30  = t29 * t11;
    real_type t31  = cos(t14);
    result__[ 2   ] = t19 * t25 * t17 * t10 + t31 * t30 * t10;
    result__[ 3   ] = -t31 * t18 * t17 * t10;
    result__[ 4   ] = -t31 * t22 * t17 * t10;
    result__[ 5   ] = -t31 * t25 * t17 * t10 + t19 * t30 * t10;
    real_type t48  = (t31 * t12 + t19 * t13 + 1) * t3;
    real_type t51  = t8 / t5 / t4;
    result__[ 6   ] = 2 * t31 * t51 * t48;
    result__[ 7   ] = 2 * t19 * t51 * t48;
    result__[ 8   ] = 2 * (-t19 * t12 + t31 * t13) * t51 * t48;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::Drhs_odeDp_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::Drhs_odeDp_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::Drhs_odeDp_nnz() const
  { return 3; }

  void
  gtocX_2burn_pars::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = ModelPars[1] - ModelPars[2];
    real_type t4   = P__[0];
    real_type t5   = sqrt(t4);
    real_type t8   = ModelPars[0];
    real_type t9   = sqrt(t8);
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 / t5 * t3;
    real_type t12  = ModelPars[6];
    real_type t13  = X__[0];
    real_type t14  = X__[1];
    real_type t15  = X__[2];
    real_type t16  = ray(t4, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * t12;
    real_type t19  = sin(t15);
    real_type t24  = t10 * t5 * t3;
    real_type t25  = acceleration_r_D_1(t16, t8);
    real_type t26  = t25 * t12;
    real_type t27  = ray_D_1(t4, t13, t14, t15);
    result__[ 0   ] = t19 * t18 * t11 / 2 + t19 * t27 * t26 * t24;
    real_type t31  = cos(t15);
    result__[ 1   ] = -t31 * t18 * t11 / 2 - t31 * t27 * t26 * t24;
    real_type t41  = pow(t31 * t13 + t19 * t14 + 1, 2);
    real_type t43  = t4 * t4;
    result__[ 2   ] = -3.0 / 2.0 * t9 / t5 / t43 * t41 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::Drhs_odeDu_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::Drhs_odeDu_numCols() const
  { return 0; }

  integer
  gtocX_2burn_pars::Drhs_odeDu_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  gtocX_2burn_pars::A_numRows() const
  { return 3; }

  integer
  gtocX_2burn_pars::A_numCols() const
  { return 3; }

  integer
  gtocX_2burn_pars::A_nnz() const
  { return 3; }

  void
  gtocX_2burn_pars::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: gtocX_2burn_pars_Methods.cc
