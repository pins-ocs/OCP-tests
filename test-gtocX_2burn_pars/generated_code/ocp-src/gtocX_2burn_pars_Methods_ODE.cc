/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_ODE.cc                                |
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

  integer gtocX_2burn_pars::rhs_ode_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::rhs_ode_eval(
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
    real_type t4   = P__[iP_p];
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
    result__[ 0   ] = t18 * t17 * t10;
    real_type t20  = cos(t14);
    result__[ 1   ] = -t20 * t17 * t10;
    real_type t26  = pow(t12 * t20 + t13 * t18 + 1, 2);
    result__[ 2   ] = t8 / t5 / t4 * t26 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::Drhs_odeDxup_numRows() const { return 3; }
  integer gtocX_2burn_pars::Drhs_odeDxup_numCols() const { return 6; }
  integer gtocX_2burn_pars::Drhs_odeDxup_nnz()     const { return 12; }

  void
  gtocX_2burn_pars::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::Drhs_odeDxup_sparse(
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
    real_type t4   = P__[iP_p];
    real_type t5   = sqrt(t4);
    real_type t7   = ModelPars[iM_muS];
    real_type t8   = sqrt(t7);
    real_type t9   = 1.0 / t8;
    real_type t10  = t9 * t5 * t3;
    real_type t11  = ModelPars[iM_w_nonlin];
    real_type t12  = X__[iX_f];
    real_type t13  = X__[iX_g];
    real_type t14  = X__[iX_L];
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
    real_type t32  = t31 * t30;
    result__[ 2   ] = t19 * t25 * t17 * t10 + t32 * t10;
    real_type t36  = t9 / t5 * t3;
    real_type t37  = t19 * t30;
    real_type t40  = ray_D_1(t4, t12, t13, t14);
    result__[ 3   ] = t37 * t36 / 2 + t19 * t40 * t17 * t10;
    result__[ 4   ] = -t31 * t18 * t17 * t10;
    result__[ 5   ] = -t31 * t22 * t17 * t10;
    result__[ 6   ] = -t31 * t25 * t17 * t10 + t37 * t10;
    result__[ 7   ] = -t32 * t36 / 2 - t31 * t40 * t17 * t10;
    real_type t61  = t31 * t12 + t19 * t13 + 1;
    real_type t62  = t61 * t3;
    real_type t65  = t8 / t5 / t4;
    result__[ 8   ] = 2 * t31 * t65 * t62;
    result__[ 9   ] = 2 * t19 * t65 * t62;
    result__[ 10  ] = 2 * (-t19 * t12 + t31 * t13) * t65 * t62;
    real_type t75  = t61 * t61;
    real_type t77  = t4 * t4;
    result__[ 11  ] = -3.0 / 2.0 * t8 / t5 / t77 * t75 * t3;
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
  integer gtocX_2burn_pars::A_numRows() const { return 3; }
  integer gtocX_2burn_pars::A_numCols() const { return 3; }
  integer gtocX_2burn_pars::A_nnz()     const { return 3; }

  void
  gtocX_2burn_pars::A_pattern( integer iIndex[], integer jIndex[] ) const {
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
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: gtocX_2burn_pars_Methods_ODE.cc
