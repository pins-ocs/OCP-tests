/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_ODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer gtocX_2burn::rhs_ode_numEqns() const { return 6; }

  void
  gtocX_2burn::rhs_ode_eval(
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
    real_type t3   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t4   = X__[iX_p];
    real_type t5   = sqrt(t4);
    real_type t7   = ModelPars[iM_muS];
    real_type t8   = sqrt(t7);
    real_type t10  = 1.0 / t8 * t5 * t3;
    real_type t12  = X__[iX_f];
    real_type t13  = X__[iX_g];
    real_type t14  = X__[iX_L];
    real_type t15  = ray(t4, t12, t13, t14);
    real_type t16  = acceleration_r(t15, t7);
    real_type t17  = t16 * ModelPars[iM_w_nonlin];
    real_type t18  = sin(t14);
    result__[ 1   ] = t18 * t17 * t10;
    real_type t20  = cos(t14);
    result__[ 2   ] = -t20 * t17 * t10;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    real_type t26  = pow(t20 * t12 + t18 * t13 + 1, 2);
    result__[ 5   ] = t8 / t5 / t4 * t26 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::Drhs_odeDxup_numRows() const { return 6; }
  integer gtocX_2burn::Drhs_odeDxup_numCols() const { return 6; }
  integer gtocX_2burn::Drhs_odeDxup_nnz()     const { return 12; }

  void
  gtocX_2burn::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 1   ;
    iIndex[10] = 5   ; jIndex[10] = 2   ;
    iIndex[11] = 5   ; jIndex[11] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t4   = X__[iX_p];
    real_type t5   = sqrt(t4);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 / t5 * t3;
    real_type t12  = ModelPars[iM_w_nonlin];
    real_type t13  = X__[iX_f];
    real_type t14  = X__[iX_g];
    real_type t15  = X__[iX_L];
    real_type t16  = ray(t4, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * t12;
    real_type t19  = sin(t15);
    real_type t20  = t19 * t18;
    real_type t24  = t10 * t5 * t3;
    real_type t25  = acceleration_r_D_1(t16, t8);
    real_type t26  = t25 * t12;
    real_type t27  = ray_D_1(t4, t13, t14, t15);
    result__[ 0   ] = t20 * t11 / 2 + t19 * t27 * t26 * t24;
    real_type t31  = ray_D_2(t4, t13, t14, t15);
    result__[ 1   ] = t19 * t31 * t26 * t24;
    real_type t34  = ray_D_3(t4, t13, t14, t15);
    result__[ 2   ] = t19 * t34 * t26 * t24;
    real_type t37  = ray_D_4(t4, t13, t14, t15);
    real_type t41  = cos(t15);
    real_type t42  = t41 * t18;
    result__[ 3   ] = t19 * t37 * t26 * t24 + t42 * t24;
    result__[ 4   ] = -t42 * t11 / 2 - t41 * t27 * t26 * t24;
    result__[ 5   ] = -t41 * t31 * t26 * t24;
    result__[ 6   ] = -t41 * t34 * t26 * t24;
    result__[ 7   ] = -t41 * t37 * t26 * t24 + t20 * t24;
    real_type t61  = t41 * t13 + t19 * t14 + 1;
    real_type t62  = t61 * t61;
    real_type t64  = t4 * t4;
    result__[ 8   ] = -3.0 / 2.0 * t9 / t5 / t64 * t62 * t3;
    real_type t70  = t61 * t3;
    real_type t73  = t9 / t5 / t4;
    result__[ 9   ] = 2 * t41 * t73 * t70;
    result__[ 10  ] = 2 * t19 * t73 * t70;
    result__[ 11  ] = 2 * (-t19 * t13 + t41 * t14) * t73 * t70;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 12, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::A_numRows() const { return 6; }
  integer gtocX_2burn::A_numCols() const { return 6; }
  integer gtocX_2burn::A_nnz()     const { return 6; }

  void
  gtocX_2burn::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::A_sparse(
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

// EOF: gtocX_2burn_Methods_ODE.cc
