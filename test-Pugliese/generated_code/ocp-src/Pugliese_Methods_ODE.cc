/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_ODE.cc                                        |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "Pugliese.hh"
#include "Pugliese_Pars.hh"

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


namespace PuglieseDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Pugliese::ode_numEqns() const { return 5; }

  void
  Pugliese::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_T];
    real_type t8   = X__[iX_C];
    real_type t9   = T_lim(t2);
    real_type t12  = X__[iX_I__p];
    result__[ 0   ] = (1 - 1.0 / ModelPars[iM_K] * t2) * ModelPars[iM_r] - t9 * t8 - t2 * t8 * t12 * ModelPars[iM_kappa__AC] - V__[0];
    real_type t17  = X__[iX_DD];
    real_type t18  = D_lim(t17);
    real_type t20  = IL(t2, t8);
    real_type t21  = IL_lim(t20);
    real_type t23  = X__[iX_R];
    result__[ 1   ] = t18 - (t23 * ModelPars[iM_kappa__R] + t21 + ModelPars[iM_mu__C]) * t8 - V__[1];
    result__[ 2   ] = t17 * ModelPars[iM_a__R] + t20 * ModelPars[iM_a__IL] - t23 * ModelPars[iM_mu__R] - V__[2];
    result__[ 3   ] = -t17 * ModelPars[iM_mu__D] - V__[3] + ModelPars[iM_rho__D];
    result__[ 4   ] = -t12 * ModelPars[iM_lambda] - V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::DodeDxpuv_numRows() const { return 5; }
  integer Pugliese::DodeDxpuv_numCols() const { return 10; }
  integer Pugliese::DodeDxpuv_nnz()     const { return 18; }

  void
  Pugliese::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 1   ;
    iIndex[11] = 2   ; jIndex[11] = 2   ;
    iIndex[12] = 2   ; jIndex[12] = 3   ;
    iIndex[13] = 2   ; jIndex[13] = 7   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 8   ;
    iIndex[16] = 4   ; jIndex[16] = 4   ;
    iIndex[17] = 4   ; jIndex[17] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Pugliese::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t5   = X__[iX_C];
    real_type t6   = X__[iX_T];
    real_type t7   = T_lim_D(t6);
    real_type t9   = ModelPars[iM_kappa__AC];
    real_type t11  = X__[iX_I__p] * t9;
    result__[ 0   ] = -ModelPars[iM_r] / ModelPars[iM_K] - t7 * t5 - t5 * t11;
    real_type t13  = T_lim(t6);
    result__[ 1   ] = -t6 * t11 - t13;
    result__[ 2   ] = -t6 * t5 * t9;
    result__[ 3   ] = -1;
    real_type t17  = IL(t6, t5);
    real_type t18  = IL_lim_D(t17);
    real_type t19  = t18 * t5;
    real_type t20  = IL_D_1(t6, t5);
    result__[ 4   ] = -t20 * t19;
    real_type t23  = IL_lim(t17);
    real_type t24  = ModelPars[iM_kappa__R];
    real_type t27  = IL_D_2(t6, t5);
    result__[ 5   ] = -t27 * t19 - X__[iX_R] * t24 - t23 - ModelPars[iM_mu__C];
    result__[ 6   ] = -t24 * t5;
    result__[ 7   ] = D_lim_D(X__[iX_DD]);
    result__[ 8   ] = -1;
    real_type t31  = ModelPars[iM_a__IL];
    result__[ 9   ] = t20 * t31;
    result__[ 10  ] = t27 * t31;
    result__[ 11  ] = -ModelPars[iM_mu__R];
    result__[ 12  ] = ModelPars[iM_a__R];
    result__[ 13  ] = -1;
    result__[ 14  ] = -ModelPars[iM_mu__D];
    result__[ 15  ] = -1;
    result__[ 16  ] = -ModelPars[iM_lambda];
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
  integer Pugliese::A_numRows() const { return 5; }
  integer Pugliese::A_numCols() const { return 5; }
  integer Pugliese::A_nnz()     const { return 5; }

  void
  Pugliese::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Pugliese::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 5, i_segment );
  }

}

// EOF: Pugliese_Methods_ODE.cc
