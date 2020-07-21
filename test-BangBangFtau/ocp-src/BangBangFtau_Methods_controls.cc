/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods.cc                                        |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vsTBInterval_DD(__t1) vsTBInterval.DD( __t1)
#define ALIAS_vsTBInterval_D(__t1) vsTBInterval.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


namespace BangBangFtauDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  BangBangFtau::g_numEqns() const
  { return 2; }

  void
  BangBangFtau::g_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[0];
    real_type t2   = ALIAS_vsTpositive_D(t1);
    real_type t5   = ALIAS_vsTmax_D(ModelPars[2] - t1);
    real_type t6   = U__[1];
    real_type t8   = ALIAS_vsTBInterval_D(t1 - t6);
    real_type t9   = ModelPars[0];
    result__[ 0   ] = t2 - t5 + t8 + 2 * t1 * t9 + L__[2] / ModelPars[5];
    real_type t16  = ALIAS_vsBpositive_D(t6);
    result__[ 1   ] = t16 - t8 + 2 * t6 * t9 + L__[3] / ModelPars[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DgDxlp_numRows() const
  { return 2; }

  integer
  BangBangFtau::DgDxlp_numCols() const
  { return 8; }

  integer
  BangBangFtau::DgDxlp_nnz() const
  { return 2; }

  void
  BangBangFtau::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 6   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 7   ;
  }

  void
  BangBangFtau::DgDxlp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1.0 / ModelPars[5];
    result__[ 1   ] = 1.0 / ModelPars[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DgDu_numRows() const
  { return 2; }

  integer
  BangBangFtau::DgDu_numCols() const
  { return 2; }

  integer
  BangBangFtau::DgDu_nnz() const
  { return 4; }

  void
  BangBangFtau::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 1   ;
  }

  void
  BangBangFtau::DgDu_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[0];
    real_type t2   = ALIAS_vsTpositive_DD(t1);
    real_type t5   = ALIAS_vsTmax_DD(ModelPars[2] - t1);
    real_type t6   = U__[1];
    real_type t8   = ALIAS_vsTBInterval_DD(t1 - t6);
    real_type t10  = 2 * ModelPars[0];
    result__[ 0   ] = t2 + t5 + t8 + t10;
    result__[ 1   ] = -t8;
    result__[ 2   ] = result__[1];
    real_type t11  = ALIAS_vsBpositive_DD(t6);
    result__[ 3   ] = t11 + t8 + t10;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDu_sparse",4);
    #endif
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/
  integer
  BangBangFtau::u_numEqns() const
  { return 2; }

  void
  BangBangFtau::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_vsT ] = 0;
    U__[ iU_vsB ] = 0;
  }

  void
  BangBangFtau::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    this->u_eval_analytic( NODE__, P__, U__ );
  }

  /*\
   |   ___       ___      _                       _      _   _
   |  |   \ _  _|   \__ _| |_ __   __ _ _ _  __ _| |_  _| |_(_)__
   |  | |) | || | |) \ \ / | '_ \ / _` | ' \/ _` | | || |  _| / _|
   |  |___/ \_,_|___//_\_\_| .__/ \__,_|_||_\__,_|_|\_, |\__|_\__|
   |                       |_|                      |__/
  \*/
  void
  BangBangFtau::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = 0;
    DuDxlp(1, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
  }

  void
  BangBangFtau::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
   |   ___       ___      _                               _
   |  |   \ _  _|   \__ _| |_ __   _ _ _  _ _ __  ___ _ _(_)__
   |  | |) | || | |) \ \ / | '_ \ | ' \ || | '  \/ -_) '_| / _|
   |  |___/ \_,_|___//_\_\_| .__/ |_||_\_,_|_|_|_\___|_| |_\__|
   |                       |_|
  \*/

  bool
  BangBangFtau::DuDxlp_full_numeric(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    static integer DgDu_I[ 4 ], DgDu_J[ 4 ];
    static integer DgDxlp_I[ 2 ], DgDxlp_J[ 2 ];
    static bool    computed_pattern = false;
    if ( !computed_pattern ) {
      this->DgDu_pattern( DgDu_I, DgDu_J );
      this->DgDxlp_pattern( DgDxlp_I, DgDxlp_J );
      computed_pattern = true;
    }
    real_type DgDu_V[ 4 ], DgDxlp_V[ 2 ];
    this->DgDu_sparse( NODE__, U__, P__, DgDu_V );
    this->DgDxlp_sparse( NODE__, U__, P__, DgDxlp_V );

    integer   ipiv[ 2 ];
    real_type DgDu_storage[ 4 ];
    MatrixWrapper<real_type> DgDu( DgDu_storage, 2, 2, 2 );
    DgDu.zero_fill();
    DuDxlp.zero_fill();

    // fill DgDu
    DgDu( DgDu_I[ 0 ], DgDu_J[ 0 ] ) = DgDu_V[0];
    DgDu( DgDu_I[ 1 ], DgDu_J[ 1 ] ) = DgDu_V[1];
    DgDu( DgDu_I[ 2 ], DgDu_J[ 2 ] ) = DgDu_V[2];
    DgDu( DgDu_I[ 3 ], DgDu_J[ 3 ] ) = DgDu_V[3];
    // fill DgDxlp
    DuDxlp( DgDxlp_I[ 0 ], DgDxlp_J[ 0] ) = -DgDxlp_V[0];
    DuDxlp( DgDxlp_I[ 1 ], DgDxlp_J[ 1] ) = -DgDxlp_V[1];
    integer info = alglin::gesv( 2, 8, DgDu.get_data(), 2, ipiv, DuDxlp.get_data(), 2 );
    return info == 0;
  }

  bool
  BangBangFtau::DuDxlp_full_numeric(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    return this->DuDxlp_full_numeric( NODE__, P__, U__, DuDxlp );
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  BangBangFtau::segmentLink_numEqns() const
  { return 0; }

  void
  BangBangFtau::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  BangBangFtau::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  BangBangFtau::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  BangBangFtau::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  BangBangFtau::jump_numEqns() const
  { return 8; }

  void
  BangBangFtau::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XR__[0] - XL__[0];
    result__[ 1   ] = XR__[1] - XL__[1];
    result__[ 2   ] = XR__[2] - XL__[2];
    result__[ 3   ] = XR__[3] - XL__[3];
    result__[ 4   ] = LR__[0] - LL__[0];
    result__[ 5   ] = LR__[1] - LL__[1];
    result__[ 6   ] = LR__[2] - LL__[2];
    result__[ 7   ] = LR__[3] - LL__[3];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"jump_eval",8);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DjumpDxlp_numRows() const
  { return 8; }

  integer
  BangBangFtau::DjumpDxlp_numCols() const
  { return 16; }

  integer
  BangBangFtau::DjumpDxlp_nnz() const
  { return 16; }

  void
  BangBangFtau::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 8   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 9   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 10  ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 11  ;
    iIndex[ 8  ] = 4   ; jIndex[ 8  ] = 4   ;
    iIndex[ 9  ] = 4   ; jIndex[ 9  ] = 12  ;
    iIndex[ 10 ] = 5   ; jIndex[ 10 ] = 5   ;
    iIndex[ 11 ] = 5   ; jIndex[ 11 ] = 13  ;
    iIndex[ 12 ] = 6   ; jIndex[ 12 ] = 6   ;
    iIndex[ 13 ] = 6   ; jIndex[ 13 ] = 14  ;
    iIndex[ 14 ] = 7   ; jIndex[ 14 ] = 7   ;
    iIndex[ 15 ] = 7   ; jIndex[ 15 ] = 15  ;
  }

  void
  BangBangFtau::DjumpDxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DjumpDxlp_sparse",16);
    #endif
  }

}

// EOF: BangBangFtau_Methods.cc
