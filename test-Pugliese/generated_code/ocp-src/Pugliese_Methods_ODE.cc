/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_ODE.cc                                        |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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
#endif


namespace PuglieseDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Pugliese::rhs_ode_numEqns() const { return 5; }

  void
  Pugliese::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_T];
    real_type t8   = X__[iX_C];
    real_type t9   = T_lim(t2);
    real_type t12  = X__[iX_I__p];
    result__[ 0   ] = (1 - 1.0 / ModelPars[iM_K] * t2) * ModelPars[iM_r] - t9 * t8 - t2 * t8 * t12 * ModelPars[iM_kappa__AC];
    real_type t16  = X__[iX_DD];
    real_type t17  = D_lim(t16);
    real_type t19  = IL(t2, t8);
    real_type t20  = IL_lim(t19);
    real_type t22  = X__[iX_R];
    result__[ 1   ] = t17 - (t22 * ModelPars[iM_kappa__R] + t20 + ModelPars[iM_mu__C]) * t8;
    result__[ 2   ] = t16 * ModelPars[iM_a__R] + t19 * ModelPars[iM_a__IL] - t22 * ModelPars[iM_mu__R];
    result__[ 3   ] = -t16 * ModelPars[iM_mu__D] + ModelPars[iM_rho__D];
    result__[ 4   ] = -t12 * ModelPars[iM_lambda];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::Drhs_odeDxup_numRows() const { return 5; }
  integer Pugliese::Drhs_odeDxup_numCols() const { return 5; }
  integer Pugliese::Drhs_odeDxup_nnz()     const { return 13; }

  void
  Pugliese::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 3   ;
    iIndex[12] = 4   ; jIndex[12] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Pugliese::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type t17  = IL(t6, t5);
    real_type t18  = IL_lim_D(t17);
    real_type t19  = t18 * t5;
    real_type t20  = IL_D_1(t6, t5);
    result__[ 3   ] = -t20 * t19;
    real_type t23  = IL_lim(t17);
    real_type t24  = ModelPars[iM_kappa__R];
    real_type t27  = IL_D_2(t6, t5);
    result__[ 4   ] = -t27 * t19 - X__[iX_R] * t24 - t23 - ModelPars[iM_mu__C];
    result__[ 5   ] = -t24 * t5;
    result__[ 6   ] = D_lim_D(X__[iX_DD]);
    real_type t31  = ModelPars[iM_a__IL];
    result__[ 7   ] = t20 * t31;
    result__[ 8   ] = t27 * t31;
    result__[ 9   ] = -ModelPars[iM_mu__R];
    result__[ 10  ] = ModelPars[iM_a__R];
    result__[ 11  ] = -ModelPars[iM_mu__D];
    result__[ 12  ] = -ModelPars[iM_lambda];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 13, i_segment );
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 5, i_segment );
  }

}

// EOF: Pugliese_Methods_ODE.cc
