/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_AdjointODE.cc                                 |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::Hxp_numEqns() const { return 4; }

  void
  AlpRider::Hxp_eval(
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
    real_type t1   = ModelPars[iM_W];
    real_type t2   = X__[iX_y1];
    real_type t6   = q_lower(Q__[iQ_zeta]);
    real_type t7   = t2 * t2;
    real_type t8   = X__[iX_y2];
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_y3];
    real_type t11  = t10 * t10;
    real_type t12  = X__[iX_y4];
    real_type t13  = t12 * t12;
    real_type t15  = ALIAS_Ybound_D(t6 - t7 - t9 - t11 - t13);
    result__[ 0   ] = 2 * t2 * t1 - 2 * t2 * t15 - 10 * MU__[0];
    result__[ 1   ] = 2 * t8 * t1 - 2 * t8 * t15 - 2 * MU__[1];
    real_type t28  = MU__[2];
    real_type t30  = MU__[3];
    result__[ 2   ] = 2 * t10 * t1 - 2 * t10 * t15 - 3 * t28 + 5 * t30;
    result__[ 3   ] = 2 * t12 * t1 - 2 * t12 * t15 + 5 * t28 - 3 * t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DHxpDxpuv_numRows() const { return 4; }
  integer AlpRider::DHxpDxpuv_numCols() const { return 10; }
  integer AlpRider::DHxpDxpuv_nnz()     const { return 16; }

  void
  AlpRider::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
  }


  void
  AlpRider::DHxpDxpuv_sparse(
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
    real_type t2   = 2 * ModelPars[iM_W];
    real_type t4   = q_lower(Q__[iQ_zeta]);
    real_type t5   = X__[iX_y1];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y2];
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_y3];
    real_type t10  = t9 * t9;
    real_type t11  = X__[iX_y4];
    real_type t12  = t11 * t11;
    real_type t13  = t4 - t6 - t8 - t10 - t12;
    real_type t14  = ALIAS_Ybound_DD(t13);
    real_type t17  = ALIAS_Ybound_D(t13);
    real_type t18  = 2 * t17;
    result__[ 0   ] = 4 * t6 * t14 - t18 + t2;
    result__[ 1   ] = 4 * t5 * t7 * t14;
    real_type t21  = t9 * t14;
    result__[ 2   ] = 4 * t5 * t21;
    real_type t23  = t11 * t14;
    result__[ 3   ] = 4 * t5 * t23;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = 4 * t8 * t14 - t18 + t2;
    result__[ 6   ] = 4 * t7 * t21;
    result__[ 7   ] = 4 * t7 * t23;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = 4 * t10 * t14 - t18 + t2;
    result__[ 11  ] = 4 * t9 * t23;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = 4 * t12 * t14 - t18 + t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 16, i_segment );
  }

}

// EOF: AlpRider_Methods_AdjointODE.cc
