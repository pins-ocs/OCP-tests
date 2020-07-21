/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods.cc                                       |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  MaximumAscent::g_numEqns() const
  { return 1; }

  void
  MaximumAscent::g_eval(
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
    real_type t4   = arctan2(-L__[1], -L__[2]);
    result__[ 0   ] = U__[0] - t4;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DgDxlp_numRows() const
  { return 1; }

  integer
  MaximumAscent::DgDxlp_numCols() const
  { return 8; }

  integer
  MaximumAscent::DgDxlp_nnz() const
  { return 2; }

  void
  MaximumAscent::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 5   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 6   ;
  }

  void
  MaximumAscent::DgDxlp_sparse(
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
    real_type t1   = L__[1];
    real_type t2   = L__[2];
    result__[ 0   ] = arctan2_D_1(-t1, -t2);
    result__[ 1   ] = arctan2_D_2(-t1, -t2);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DgDu_numRows() const
  { return 1; }

  integer
  MaximumAscent::DgDu_numCols() const
  { return 1; }

  integer
  MaximumAscent::DgDu_nnz() const
  { return 1; }

  void
  MaximumAscent::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
  }

  void
  MaximumAscent::DgDu_sparse(
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
    result__[ 0   ] = 1;
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
  MaximumAscent::u_numEqns() const
  { return 1; }

  void
  MaximumAscent::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_alpha ] = arctan2(-L__[1], -L__[2]);
  }

  void
  MaximumAscent::u_eval_analytic(
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
  MaximumAscent::DuDxlp_full_analytic(
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
    DuDxlp(0, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(0, 5) = -arctan2_D_1(-L__[1], -L__[2]);
    DuDxlp(0, 6) = -arctan2_D_2(-L__[1], -L__[2]);
    DuDxlp(0, 7) = 0;
  }

  void
  MaximumAscent::DuDxlp_full_analytic(
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
  MaximumAscent::DuDxlp_full_numeric(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    static integer DgDu_I[ 1 ], DgDu_J[ 1 ];
    static integer DgDxlp_I[ 2 ], DgDxlp_J[ 2 ];
    static bool    computed_pattern = false;
    if ( !computed_pattern ) {
      this->DgDu_pattern( DgDu_I, DgDu_J );
      this->DgDxlp_pattern( DgDxlp_I, DgDxlp_J );
      computed_pattern = true;
    }
    real_type DgDu_V[ 1 ], DgDxlp_V[ 2 ];
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
    integer info = alglin::gesv( 1, 8, DgDu.get_data(), 1, ipiv, DuDxlp.get_data(), 1 );
    return info == 0;
  }

  bool
  MaximumAscent::DuDxlp_full_numeric(
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
  MaximumAscent::segmentLink_numEqns() const
  { return 0; }

  void
  MaximumAscent::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  MaximumAscent::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  MaximumAscent::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  MaximumAscent::DsegmentLinkDxp_sparse(
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
  MaximumAscent::jump_numEqns() const
  { return 8; }

  void
  MaximumAscent::jump_eval(
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
  MaximumAscent::DjumpDxlp_numRows() const
  { return 8; }

  integer
  MaximumAscent::DjumpDxlp_numCols() const
  { return 16; }

  integer
  MaximumAscent::DjumpDxlp_nnz() const
  { return 16; }

  void
  MaximumAscent::DjumpDxlp_pattern(
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
  MaximumAscent::DjumpDxlp_sparse(
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

// EOF: MaximumAscent_Methods.cc
