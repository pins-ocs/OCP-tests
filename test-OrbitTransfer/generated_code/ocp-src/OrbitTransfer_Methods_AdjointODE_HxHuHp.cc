/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


namespace OrbitTransferDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::Hxp_numEqns() const { return 5; }

  void
  OrbitTransfer::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = sin(t5);
    real_type t9   = X__[iX_m] * X__[iX_m];
    real_type t10  = 1.0 / t9;
    real_type t14  = t2 * L__[iL_lambda3__xo];
    real_type t15  = cos(t5);
    result__[ 0   ] = -t10 * t15 * t4 * t14 - t10 * t6 * t4 * t3;
    result__[ 1   ] = 0;
    real_type t19  = X__[iX_v];
    real_type t20  = t19 * t19;
    real_type t21  = X__[iX_r];
    real_type t22  = t21 * t21;
    real_type t23  = 1.0 / t22;
    real_type t32  = X__[iX_u];
    real_type t37  = t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = (-t23 * t20 + 2 / t22 / t21 * ModelPars[iM_mu]) * t3 + t23 * t32 * t19 * t14 - t23 * t19 * t37;
    real_type t42  = 1.0 / t21;
    real_type t43  = t42 * t19;
    result__[ 3   ] = -t43 * t14 + t2 * L__[iL_lambda1__xo];
    result__[ 4   ] = -t42 * t32 * t14 + 2 * t43 * t3 + t42 * t37;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DHxpDxpu_numRows() const { return 5; }
  integer OrbitTransfer::DHxpDxpu_numCols() const { return 6; }
  integer OrbitTransfer::DHxpDxpu_nnz()     const { return 10; }

  void
  OrbitTransfer::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 4   ;
  }


  void
  OrbitTransfer::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = sin(t5);
    real_type t7   = t6 * t4;
    real_type t8   = X__[iX_m];
    real_type t9   = t8 * t8;
    real_type t11  = 1.0 / t9 / t8;
    real_type t15  = t2 * L__[iL_lambda3__xo];
    real_type t16  = cos(t5);
    real_type t17  = t16 * t4;
    result__[ 0   ] = 2 * t11 * t17 * t15 + 2 * t11 * t7 * t3;
    real_type t21  = 1.0 / t9;
    result__[ 1   ] = t21 * t7 * t15 - t21 * t17 * t3;
    real_type t26  = X__[iX_v];
    real_type t27  = t26 * t26;
    real_type t28  = X__[iX_r];
    real_type t29  = t28 * t28;
    real_type t31  = 1.0 / t29 / t28;
    real_type t35  = t29 * t29;
    real_type t41  = X__[iX_u];
    real_type t47  = t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = (2 * t31 * t27 - 6 / t35 * ModelPars[iM_mu]) * t3 - 2 * t31 * t41 * t26 * t15 + 2 * t31 * t26 * t47;
    real_type t51  = 1.0 / t29;
    real_type t52  = t51 * t26;
    result__[ 3   ] = t52 * t15;
    result__[ 4   ] = t51 * t41 * t15 - 2 * t52 * t3 - t51 * t47;
    result__[ 5   ] = result__[3];
    real_type t58  = 1.0 / t28;
    result__[ 6   ] = -t58 * t15;
    result__[ 7   ] = result__[4];
    result__[ 8   ] = result__[6];
    result__[ 9   ] = 2 * t58 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 10, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::Hu_numEqns() const { return 1; }

  void
  OrbitTransfer::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t9   = 1.0 / X__[iX_m];
    real_type t14  = sin(t5);
    result__[ 0   ] = -t9 * t14 * t4 * t2 * L__[iL_lambda3__xo] + t9 * t6 * t4 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: OrbitTransfer_Methods_AdjointODE.cc
