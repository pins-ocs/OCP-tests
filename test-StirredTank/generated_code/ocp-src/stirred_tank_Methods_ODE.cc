/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_ODE.cc                                    |
 |                                                                       |
 |  version: 1.0   date 20/1/2023                                        |
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


#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

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
#define ALIAS_u4Control_D_3(__t1, __t2, __t3) u4Control.D_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2(__t1, __t2, __t3) u4Control.D_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1(__t1, __t2, __t3) u4Control.D_1( __t1, __t2, __t3)
#define ALIAS_u4Control_D_3_3(__t1, __t2, __t3) u4Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_3(__t1, __t2, __t3) u4Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_2(__t1, __t2, __t3) u4Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_3(__t1, __t2, __t3) u4Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_2(__t1, __t2, __t3) u4Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_1(__t1, __t2, __t3) u4Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace stirred_tankDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer stirred_tank::rhs_ode_numEqns() const { return 8; }

  void
  stirred_tank::rhs_ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u4];
    real_type t2   = U__[iU_u1];
    real_type t3   = U__[iU_u2];
    real_type t4   = t2 + t3 + t1;
    real_type t5   = X__[iX_x1];
    real_type t6   = t5 * t4;
    real_type t7   = X__[iX_x2];
    real_type t8   = t7 * t5;
    real_type t9   = 0.176e2 * t8;
    real_type t10  = X__[iX_x6];
    real_type t12  = U__[iU_u3];
    real_type t13  = t12 * t10 * t5;
    real_type t14  = 23 * t13;
    result__[ 0   ] = t1 - t6 - t9 - t14;
    real_type t16  = X__[iX_x3];
    real_type t17  = t16 * t7;
    result__[ 1   ] = -t7 * t4 - 146 * t17 + t2 - t9;
    result__[ 2   ] = -t16 * t4 - 73 * t17 + t3;
    real_type t21  = X__[iX_x4];
    real_type t24  = X__[iX_x5];
    real_type t25  = t24 * t21;
    real_type t26  = 0.513e2 * t25;
    result__[ 3   ] = -t21 * t4 + 0.352e2 * t8 - t26;
    result__[ 4   ] = -t24 * t4 + 219 * t17 - t26;
    result__[ 5   ] = -t10 * t4 - t14 + 102 * t25;
    real_type t31  = X__[iX_x7];
    result__[ 6   ] = -t31 * t4 + 46 * t13;
    real_type t44  = t12 * t12;
    result__[ 7   ] = 0.58e1 * t6 - 0.58e1 * t1 - 0.37e1 * t2 - 0.41e1 * t3 + (23 * t21 + 11 * t24 + 28 * t10 + 35 * t31) * t4 - 5 * t44 - 0.9e-1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::Drhs_odeDxpu_numRows() const { return 8; }
  integer stirred_tank::Drhs_odeDxpu_numCols() const { return 12; }
  integer stirred_tank::Drhs_odeDxpu_nnz()     const { return 56; }

  void
  stirred_tank::Drhs_odeDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 11  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 8   ;
    iIndex[11] = 1   ; jIndex[11] = 9   ;
    iIndex[12] = 1   ; jIndex[12] = 11  ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 8   ;
    iIndex[16] = 2   ; jIndex[16] = 9   ;
    iIndex[17] = 2   ; jIndex[17] = 11  ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 1   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 3   ; jIndex[21] = 4   ;
    iIndex[22] = 3   ; jIndex[22] = 8   ;
    iIndex[23] = 3   ; jIndex[23] = 9   ;
    iIndex[24] = 3   ; jIndex[24] = 11  ;
    iIndex[25] = 4   ; jIndex[25] = 1   ;
    iIndex[26] = 4   ; jIndex[26] = 2   ;
    iIndex[27] = 4   ; jIndex[27] = 3   ;
    iIndex[28] = 4   ; jIndex[28] = 4   ;
    iIndex[29] = 4   ; jIndex[29] = 8   ;
    iIndex[30] = 4   ; jIndex[30] = 9   ;
    iIndex[31] = 4   ; jIndex[31] = 11  ;
    iIndex[32] = 5   ; jIndex[32] = 0   ;
    iIndex[33] = 5   ; jIndex[33] = 3   ;
    iIndex[34] = 5   ; jIndex[34] = 4   ;
    iIndex[35] = 5   ; jIndex[35] = 5   ;
    iIndex[36] = 5   ; jIndex[36] = 8   ;
    iIndex[37] = 5   ; jIndex[37] = 9   ;
    iIndex[38] = 5   ; jIndex[38] = 10  ;
    iIndex[39] = 5   ; jIndex[39] = 11  ;
    iIndex[40] = 6   ; jIndex[40] = 0   ;
    iIndex[41] = 6   ; jIndex[41] = 5   ;
    iIndex[42] = 6   ; jIndex[42] = 6   ;
    iIndex[43] = 6   ; jIndex[43] = 8   ;
    iIndex[44] = 6   ; jIndex[44] = 9   ;
    iIndex[45] = 6   ; jIndex[45] = 10  ;
    iIndex[46] = 6   ; jIndex[46] = 11  ;
    iIndex[47] = 7   ; jIndex[47] = 0   ;
    iIndex[48] = 7   ; jIndex[48] = 3   ;
    iIndex[49] = 7   ; jIndex[49] = 4   ;
    iIndex[50] = 7   ; jIndex[50] = 5   ;
    iIndex[51] = 7   ; jIndex[51] = 6   ;
    iIndex[52] = 7   ; jIndex[52] = 8   ;
    iIndex[53] = 7   ; jIndex[53] = 9   ;
    iIndex[54] = 7   ; jIndex[54] = 10  ;
    iIndex[55] = 7   ; jIndex[55] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::Drhs_odeDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = U__[iU_u2];
    real_type t3   = U__[iU_u4];
    real_type t4   = X__[iX_x2];
    real_type t5   = 0.176e2 * t4;
    real_type t6   = X__[iX_x6];
    real_type t7   = U__[iU_u3];
    real_type t8   = t7 * t6;
    real_type t9   = 23 * t8;
    result__[ 0   ] = -t1 - t2 - t3 - t5 - t9;
    real_type t10  = X__[iX_x1];
    result__[ 1   ] = -0.176e2 * t10;
    real_type t12  = t7 * t10;
    result__[ 2   ] = -23 * t12;
    result__[ 3   ] = -t10;
    result__[ 4   ] = result__[3];
    real_type t14  = t6 * t10;
    result__[ 5   ] = -23 * t14;
    result__[ 6   ] = 1 + result__[4];
    result__[ 7   ] = -t5;
    real_type t16  = X__[iX_x3];
    result__[ 8   ] = -t1 - t2 - t3 + result__[1] - 146 * t16;
    result__[ 9   ] = -146 * t4;
    result__[ 10  ] = 1 - t4;
    result__[ 11  ] = -t4;
    result__[ 12  ] = result__[11];
    result__[ 13  ] = -73 * t16;
    result__[ 14  ] = -t1 - t2 - t3 - 73 * t4;
    result__[ 15  ] = -t16;
    result__[ 16  ] = 1 + result__[15];
    result__[ 17  ] = result__[15];
    result__[ 18  ] = 0.352e2 * t4;
    result__[ 19  ] = 0.352e2 * t10;
    real_type t21  = X__[iX_x5];
    real_type t22  = 0.513e2 * t21;
    result__[ 20  ] = -t1 - t2 - t3 - t22;
    real_type t23  = X__[iX_x4];
    result__[ 21  ] = -0.513e2 * t23;
    result__[ 22  ] = -t23;
    result__[ 23  ] = result__[22];
    result__[ 24  ] = result__[23];
    result__[ 25  ] = 219 * t16;
    result__[ 26  ] = 219 * t4;
    result__[ 27  ] = -t22;
    result__[ 28  ] = -t1 - t2 - t3 + result__[21];
    result__[ 29  ] = -t21;
    result__[ 30  ] = result__[29];
    result__[ 31  ] = result__[30];
    result__[ 32  ] = -t9;
    result__[ 33  ] = 102 * t21;
    result__[ 34  ] = 102 * t23;
    result__[ 35  ] = result__[2] - t1 - t2 - t3;
    result__[ 36  ] = -t6;
    result__[ 37  ] = result__[36];
    result__[ 38  ] = result__[5];
    result__[ 39  ] = result__[37];
    result__[ 40  ] = 46 * t8;
    result__[ 41  ] = 46 * t12;
    result__[ 42  ] = -t1 - t2 - t3;
    real_type t25  = X__[iX_x7];
    result__[ 43  ] = -t25;
    result__[ 44  ] = result__[43];
    result__[ 45  ] = 46 * t14;
    result__[ 46  ] = result__[44];
    result__[ 47  ] = 0.58e1 * t1 + 0.58e1 * t2 + 0.58e1 * t3;
    real_type t29  = -result__[42];
    result__[ 48  ] = 23 * t29;
    result__[ 49  ] = 11 * t29;
    result__[ 50  ] = 28 * t29;
    result__[ 51  ] = 35 * t29;
    real_type t30  = 0.58e1 * t10;
    real_type t31  = 23 * t23;
    real_type t32  = 11 * t21;
    real_type t33  = 28 * t6;
    real_type t34  = 35 * t25;
    result__[ 52  ] = t30 - 0.37e1 + t31 + t32 + t33 + t34;
    result__[ 53  ] = t30 - 0.41e1 + t31 + t32 + t33 + t34;
    result__[ 54  ] = -10 * t7;
    result__[ 55  ] = t30 - 0.58e1 + t31 + t32 + t33 + t34;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxpu_sparse", 56, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::A_numRows() const { return 8; }
  integer stirred_tank::A_numCols() const { return 8; }
  integer stirred_tank::A_nnz()     const { return 8; }

  void
  stirred_tank::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::A_sparse(
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
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 8, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::eta_numEqns() const { return 8; }

  void
  stirred_tank::eta_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    result__[ 7   ] = L__[iL_lambda8__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DetaDxp_numRows() const { return 8; }
  integer stirred_tank::DetaDxp_numCols() const { return 8; }
  integer stirred_tank::DetaDxp_nnz()     const { return 0; }

  void
  stirred_tank::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::DetaDxp_sparse(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::nu_numEqns() const { return 8; }

  void
  stirred_tank::nu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    result__[ 7   ] = V__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DnuDxp_numRows() const { return 8; }
  integer stirred_tank::DnuDxp_numCols() const { return 8; }
  integer stirred_tank::DnuDxp_nnz()     const { return 0; }

  void
  stirred_tank::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::DnuDxp_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: stirred_tank_Methods_ODE.cc
