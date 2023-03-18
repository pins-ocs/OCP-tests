/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_ODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
#pragma warning( disable : 4189 )
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

  integer gtocX_2burn::ode_numEqns() const { return 6; }

  void
  gtocX_2burn::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -V__[0];
    real_type t4   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t5   = X__[iX_p];
    real_type t6   = sqrt(t5);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t11  = 1.0 / t9 * t6 * t4;
    real_type t13  = X__[iX_f];
    real_type t14  = X__[iX_g];
    real_type t15  = X__[iX_L];
    real_type t16  = ray(t5, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * ModelPars[iM_w_nonlin];
    real_type t19  = sin(t15);
    result__[ 1   ] = t19 * t18 * t11 - V__[1];
    real_type t23  = cos(t15);
    result__[ 2   ] = -t23 * t18 * t11 - V__[2];
    result__[ 3   ] = -V__[3];
    result__[ 4   ] = -V__[4];
    real_type t32  = pow(t23 * t13 + t19 * t14 + 1, 2);
    result__[ 5   ] = t9 / t6 / t5 * t32 * t4 - V__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DodeDxpuv_numRows() const { return 6; }
  integer gtocX_2burn::DodeDxpuv_numCols() const { return 12; }
  integer gtocX_2burn::DodeDxpuv_nnz()     const { return 18; }

  void
  gtocX_2burn::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 2   ; jIndex[10] = 8   ;
    iIndex[11] = 3   ; jIndex[11] = 9   ;
    iIndex[12] = 4   ; jIndex[12] = 10  ;
    iIndex[13] = 5   ; jIndex[13] = 0   ;
    iIndex[14] = 5   ; jIndex[14] = 1   ;
    iIndex[15] = 5   ; jIndex[15] = 2   ;
    iIndex[16] = 5   ; jIndex[16] = 5   ;
    iIndex[17] = 5   ; jIndex[17] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
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
    result__[ 1   ] = t20 * t11 / 2 + t19 * t27 * t26 * t24;
    real_type t31  = ray_D_2(t4, t13, t14, t15);
    result__[ 2   ] = t19 * t31 * t26 * t24;
    real_type t34  = ray_D_3(t4, t13, t14, t15);
    result__[ 3   ] = t19 * t34 * t26 * t24;
    real_type t37  = ray_D_4(t4, t13, t14, t15);
    real_type t41  = cos(t15);
    real_type t42  = t41 * t18;
    result__[ 4   ] = t19 * t37 * t26 * t24 + t42 * t24;
    result__[ 5   ] = -1;
    result__[ 6   ] = -t42 * t11 / 2 - t41 * t27 * t26 * t24;
    result__[ 7   ] = -t41 * t31 * t26 * t24;
    result__[ 8   ] = -t41 * t34 * t26 * t24;
    result__[ 9   ] = -t41 * t37 * t26 * t24 + t20 * t24;
    result__[ 10  ] = -1;
    result__[ 11  ] = -1;
    result__[ 12  ] = -1;
    real_type t61  = t41 * t13 + t19 * t14 + 1;
    real_type t62  = t61 * t61;
    real_type t64  = t4 * t4;
    result__[ 13  ] = -3.0 / 2.0 * t9 / t5 / t64 * t62 * t3;
    real_type t70  = t61 * t3;
    real_type t73  = t9 / t5 / t4;
    result__[ 14  ] = 2 * t41 * t73 * t70;
    result__[ 15  ] = 2 * t19 * t73 * t70;
    result__[ 16  ] = 2 * (-t19 * t13 + t41 * t14) * t73 * t70;
    result__[ 17  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 18, i_segment );
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
