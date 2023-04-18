/*-----------------------------------------------------------------------*\
 |  file: CristianiMartinon_Methods_AdjointODE.cc                        |
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


#include "CristianiMartinon.hh"
#include "CristianiMartinon_Pars.hh"

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
#define ALIAS_pos_DD(__t1) pos.DD( __t1)
#define ALIAS_pos_D(__t1) pos.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace CristianiMartinonDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CristianiMartinon::Hxp_numEqns() const { return 3; }

  void
  CristianiMartinon::Hxp_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = cfun_D_1(t4, t5);
    real_type t7   = U__[iU_u];
    real_type t8   = cos(t7);
    real_type t11  = MU__[1];
    real_type t12  = t2 * t11;
    real_type t13  = sin(t7);
    result__[ 0   ] = t13 * t6 * t12 + t8 * t6 * t3;
    real_type t18  = yguess(Q__[iQ_zeta]);
    real_type t22  = cfun_D_2(t4, t5);
    result__[ 1   ] = 2 * (t5 - t18) * ModelPars[iM_WY] + t8 * t22 * t3 + t13 * t22 * t12;
    real_type t27  = ALIAS_Tpositive_D(-t2);
    real_type t28  = cfun(t4, t5);
    result__[ 2   ] = t8 * t28 * t1 + t13 * t28 * t11 - t27 + 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CristianiMartinon::DHxpDxpuv_numRows() const { return 3; }
  integer CristianiMartinon::DHxpDxpuv_numCols() const { return 6; }
  integer CristianiMartinon::DHxpDxpuv_nnz()     const { return 12; }

  void
  CristianiMartinon::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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


  void
  CristianiMartinon::DHxpDxpuv_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = cfun_D_1_1(t4, t5);
    real_type t7   = U__[iU_u];
    real_type t8   = cos(t7);
    real_type t11  = MU__[1];
    real_type t12  = t2 * t11;
    real_type t13  = sin(t7);
    result__[ 0   ] = t13 * t6 * t12 + t8 * t6 * t3;
    real_type t16  = cfun_D_1_2(t4, t5);
    result__[ 1   ] = t13 * t16 * t12 + t8 * t16 * t3;
    real_type t21  = cfun_D_1(t4, t5);
    result__[ 2   ] = t8 * t21 * t1 + t13 * t21 * t11;
    result__[ 3   ] = t8 * t21 * t12 - t13 * t21 * t3;
    result__[ 4   ] = result__[1];
    real_type t32  = cfun_D_2_2(t4, t5);
    result__[ 5   ] = t13 * t32 * t12 + t8 * t32 * t3 + 2 * ModelPars[iM_WY];
    real_type t37  = cfun_D_2(t4, t5);
    result__[ 6   ] = t8 * t37 * t1 + t13 * t37 * t11;
    result__[ 7   ] = t8 * t37 * t12 - t13 * t37 * t3;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = ALIAS_Tpositive_DD(-t2);
    real_type t46  = cfun(t4, t5);
    result__[ 11  ] = -t13 * t46 * t1 + t8 * t46 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 12, i_segment );
  }

}

// EOF: CristianiMartinon_Methods_AdjointODE.cc
