/*-----------------------------------------------------------------------*\
 |  file: Dido_Methods.cc                                                |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#include "Dido.hh"
#include "Dido_Pars.hh"

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


namespace DidoDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Dido::g_numEqns() const
  { return 1; }

  void
  Dido::g_eval(
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
    real_type t2   = U__[0];
    real_type t3   = sin(t2);
    real_type t8   = cos(t2);
    result__[ 0   ] = -t3 * L__[0] + t3 * X__[1] + t8 * L__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Dido::DgDxlp_numRows() const
  { return 1; }

  integer
  Dido::DgDxlp_numCols() const
  { return 4; }

  integer
  Dido::DgDxlp_nnz() const
  { return 3; }

  void
  Dido::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 1   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 2   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 3   ;
  }

  void
  Dido::DgDxlp_sparse(
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
    result__[ 0   ] = sin(t1);
    result__[ 1   ] = -result__[0];
    result__[ 2   ] = cos(t1);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Dido::DgDu_numRows() const
  { return 1; }

  integer
  Dido::DgDu_numCols() const
  { return 1; }

  integer
  Dido::DgDu_nnz() const
  { return 1; }

  void
  Dido::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
  }

  void
  Dido::DgDu_sparse(
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
    real_type t2   = U__[0];
    real_type t3   = cos(t2);
    real_type t8   = sin(t2);
    result__[ 0   ] = -t3 * L__[0] + t3 * X__[1] - t8 * L__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDu_sparse",1);
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
  Dido::u_numEqns() const
  { return 1; }

  void
  Dido::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_theta ] = atan(L__[1] / (-X__[1] + L__[0]));
  }

  void
  Dido::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  Dido::DuDxlp_full_analytic(
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
    DuDxlp(0, 1) = L__[1] * pow(-X__[1] + L__[0], -2) / (L__[1] * L__[1] * pow(-X__[1] + L__[0], -2) + 1);
    DuDxlp(0, 2) = -L__[1] * pow(-X__[1] + L__[0], -2) / (L__[1] * L__[1] * pow(-X__[1] + L__[0], -2) + 1);
    DuDxlp(0, 3) = 1.0 / (-X__[1] + L__[0]) / (L__[1] * L__[1] * pow(-X__[1] + L__[0], -2) + 1);
  }

  void
  Dido::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  Dido::DuDxlp_full_numeric(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    static integer DgDu_I[ 1 ], DgDu_J[ 1 ];
    static integer DgDxlp_I[ 3 ], DgDxlp_J[ 3 ];
    static bool    computed_pattern = false;
    if ( !computed_pattern ) {
      this->DgDu_pattern( DgDu_I, DgDu_J );
      this->DgDxlp_pattern( DgDxlp_I, DgDxlp_J );
      computed_pattern = true;
    }
    real_type DgDu_V[ 1 ], DgDxlp_V[ 3 ];
    this->DgDu_sparse( NODE__, U__, P__, DgDu_V );
    this->DgDxlp_sparse( NODE__, U__, P__, DgDxlp_V );

    integer   ipiv[ 1 ];
    real_type DgDu_storage[ 1 ];
    MatrixWrapper<real_type> DgDu( DgDu_storage, 1, 1, 1 );
    DgDu.zero_fill();
    DuDxlp.zero_fill();

    // fill DgDu
    DgDu( DgDu_I[ 0 ], DgDu_J[ 0 ] ) = DgDu_V[0];
    // fill DgDxlp
    DuDxlp( DgDxlp_I[ 0 ], DgDxlp_J[ 0] ) = -DgDxlp_V[0];
    DuDxlp( DgDxlp_I[ 1 ], DgDxlp_J[ 1] ) = -DgDxlp_V[1];
    DuDxlp( DgDxlp_I[ 2 ], DgDxlp_J[ 2] ) = -DgDxlp_V[2];
    integer info = alglin::gesv( 1, 4, DgDu.get_data(), 1, ipiv, DuDxlp.get_data(), 1 );
    return info == 0;
  }

  bool
  Dido::DuDxlp_full_numeric(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  Dido::segmentLink_numEqns() const
  { return 0; }

  void
  Dido::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Dido::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  Dido::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  Dido::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  Dido::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  Dido::DsegmentLinkDxp_sparse(
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
  Dido::jump_numEqns() const
  { return 4; }

  void
  Dido::jump_eval(
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
    result__[ 2   ] = LR__[0] - LL__[0];
    result__[ 3   ] = LR__[1] - LL__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"jump_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Dido::DjumpDxlp_numRows() const
  { return 4; }

  integer
  Dido::DjumpDxlp_numCols() const
  { return 8; }

  integer
  Dido::DjumpDxlp_nnz() const
  { return 8; }

  void
  Dido::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 4   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 5   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 6   ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 7   ;
  }

  void
  Dido::DjumpDxlp_sparse(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DjumpDxlp_sparse",8);
    #endif
  }

}

// EOF: Dido_Methods.cc
