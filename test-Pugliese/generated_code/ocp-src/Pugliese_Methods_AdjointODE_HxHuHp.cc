/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_AdjointODE.cc                                 |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Pugliese::Hxp_numEqns() const { return 5; }

  void
  Pugliese::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t6   = X__[iX_C];
    real_type t7   = X__[iX_T];
    real_type t8   = T_lim_D(t7);
    real_type t10  = ModelPars[iM_kappa__AC];
    real_type t11  = X__[iX_I__p];
    real_type t12  = t11 * t10;
    real_type t16  = MU__[1];
    real_type t17  = t6 * t16;
    real_type t18  = IL(t7, t6);
    real_type t19  = IL_lim_D(t18);
    real_type t20  = IL_D_1(t7, t6);
    real_type t23  = MU__[2];
    real_type t25  = ModelPars[iM_a__IL] * t23;
    result__[ 0   ] = 1 + (-ModelPars[iM_r] / ModelPars[iM_K] - t8 * t6 - t6 * t12) * t1 - t20 * t19 * t17 + t20 * t25;
    real_type t27  = T_lim(t7);
    real_type t32  = IL_lim(t18);
    real_type t33  = ModelPars[iM_kappa__R];
    real_type t37  = IL_D_2(t7, t6);
    result__[ 1   ] = (-t7 * t12 - t27) * t1 + (-t37 * t19 * t6 - X__[iX_R] * t33 - t32 - ModelPars[iM_mu__C]) * t16 + t37 * t25;
    result__[ 2   ] = -t33 * t17 - t23 * ModelPars[iM_mu__R];
    real_type t46  = D_lim_D(X__[iX_DD]);
    result__[ 3   ] = t46 * t16 + ModelPars[iM_a__R] * t23 - MU__[3] * ModelPars[iM_mu__D];
    real_type t55  = ModelPars[iM_w2] * ModelPars[iM_a];
    real_type t56  = t11 * t11;
    real_type t58  = t56 + ModelPars[iM_b];
    real_type t64  = t58 * t58;
    result__[ 4   ] = 2 / t58 * t11 * t55 - 2 / t64 * t56 * t11 * t55 - t7 * t6 * t10 * t1 - MU__[4] * ModelPars[iM_lambda];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::DHxpDxpuv_numRows() const { return 5; }
  integer Pugliese::DHxpDxpuv_numCols() const { return 10; }
  integer Pugliese::DHxpDxpuv_nnz()     const { return 12; }

  void
  Pugliese::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 0   ;
    iIndex[10] = 4   ; jIndex[10] = 1   ;
    iIndex[11] = 4   ; jIndex[11] = 4   ;
  }


  void
  Pugliese::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t2   = X__[iX_C];
    real_type t4   = X__[iX_T];
    real_type t5   = T_lim_DD(t4);
    real_type t7   = MU__[1];
    real_type t8   = t2 * t7;
    real_type t9   = IL(t4, t2);
    real_type t10  = IL_lim_DD(t9);
    real_type t11  = IL_D_1(t4, t2);
    real_type t12  = t11 * t11;
    real_type t15  = IL_lim_D(t9);
    real_type t16  = IL_D_1_1(t4, t2);
    real_type t21  = ModelPars[iM_a__IL] * MU__[2];
    result__[ 0   ] = -t5 * t2 * t1 - t12 * t10 * t8 - t16 * t15 * t8 + t16 * t21;
    real_type t23  = T_lim_D(t4);
    real_type t24  = ModelPars[iM_kappa__AC];
    real_type t25  = X__[iX_I__p];
    real_type t28  = (-t25 * t24 - t23) * t1;
    real_type t31  = IL_D_2(t4, t2);
    real_type t35  = IL_D_1_2(t4, t2);
    real_type t38  = t35 * t21;
    result__[ 1   ] = -t11 * t31 * t10 * t8 - t11 * t15 * t7 - t35 * t15 * t8 + t28 + t38;
    real_type t39  = t24 * t1;
    result__[ 2   ] = -t2 * t39;
    real_type t42  = t10 * t2;
    real_type t45  = t15 * t2;
    result__[ 3   ] = t28 + (-t31 * t11 * t42 - t11 * t15 - t35 * t45) * t7 + t38;
    real_type t51  = t31 * t31;
    real_type t53  = IL_D_2_2(t4, t2);
    result__[ 4   ] = (-2 * t31 * t15 - t51 * t42 - t53 * t45) * t7 + t53 * t21;
    result__[ 5   ] = -ModelPars[iM_kappa__R] * t7;
    result__[ 6   ] = -t4 * t39;
    result__[ 7   ] = result__[5];
    real_type t62  = D_lim_DD(X__[iX_DD]);
    result__[ 8   ] = t62 * t7;
    result__[ 9   ] = result__[2];
    result__[ 10  ] = result__[6];
    real_type t65  = ModelPars[iM_w2] * ModelPars[iM_a];
    real_type t66  = t25 * t25;
    real_type t68  = t66 + ModelPars[iM_b];
    real_type t72  = t68 * t68;
    real_type t77  = t66 * t66;
    result__[ 11  ] = 2 / t68 * t65 - 10 / t72 * t66 * t65 + 8 / t72 / t68 * t77 * t65;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 12, i_segment );
  }

}

// EOF: Pugliese_Methods_AdjointODE.cc
