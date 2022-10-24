/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Mex_class.cc                               |
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


#include "PointMassCarModel_4_Mex.hh"

ProblemStorage::ProblemStorage(
  std::string const & cname,
  Console const     * console,
  ThreadPoolBase    * TP
)
: MODEL_CLASS(cname,console,TP)
// user defined Object instances (external)
, road( "road" )
{}

ProblemStorage::~ProblemStorage() {}

void
ProblemStorage::done_setup() {
  setup_ok     = true;
  guess_ok     = false;
  solve_ok     = false;
  solution1_ok = false;
  solution2_ok = false;
  solution3_ok = false;
}

void
ProblemStorage::done_guess() {
  setup_ok     = true;
  guess_ok     = true;
  solve_ok     = false;
  solution1_ok = false;
  solution2_ok = false;
  solution3_ok = false;
}

void
ProblemStorage::done_solve() {
  setup_ok     = true;
  guess_ok     = true;
  solve_ok     = true;
  solution1_ok = false;
  solution2_ok = false;
  solution3_ok = false;
}

integer
ProblemStorage::nnz() const { return MODEL_CLASS::eval_JF_nnz(); }

void
ProblemStorage::read( string const & fname, GenericContainer & gc ) {
  // redirect output
  Mechatronix::STDOUT_redirect rd;
  rd.start();
  bool ok = Mechatronix::load_script( fname, gc );
  if ( !ok ) mexPrintf( "Mechatronix::load_script file not found\n" );
  rd.stop();
  if ( rd.str().length() > 0 )
    mexPrintf( "Mechatronix::load_script return:\n%s\n", rd.str().c_str() );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_LR2(
  char const      msg[],
  int             nrhs,
  mxArray const * prhs[],
  NodeType2     & L,
  NodeType2     & R
) {

  mwSize nQ, nX, nL;

  // -------------------
  L.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} L_segment", msg ) ) );
  UTILS_ASSERT(
    L.i_segment >= 0 && L.i_segment < this->num_segments(),
    "{} iseg_L = {} expected to be in [0,{})\n",
    msg, L.i_segment, this->num_segments()
  );

  // -------------------
  L.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q_L", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  L.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x_L", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );

  // -------------------
  L.lambda = Utils::mex_vector_pointer( arg_in_5, nL, fmt::format( "{} argument lambda_L", msg ) );
  UTILS_ASSERT(
    nL == this->dim_X(),
    "{} |lambda_L| = {} expected to be {}\n",
    msg, nL, this->dim_X()
  );

  // -------------------
  R.i_segment = integer( Utils::mex_get_int64( arg_in_6, fmt::format( "{} R_segment", msg ) ) );
  UTILS_ASSERT(
    R.i_segment >= 0 && R.i_segment < this->num_segments(),
    "{} iseg_R = {} expected to be in [0,{})\n",
    msg, R.i_segment, this->num_segments()
  );

  // -------------------
  R.q = Utils::mex_vector_pointer( arg_in_7, nQ, fmt::format( "{} argument q_R", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_R| = {} expected to be {}\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  R.x = Utils::mex_vector_pointer( arg_in_8, nX, fmt::format( "{} argument x_R", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_R| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );

  // -------------------
  R.lambda = Utils::mex_vector_pointer( arg_in_9, nL, fmt::format( "{} argument lambda_R", msg ) );
  UTILS_ASSERT(
    nL == this->dim_X(),
    "{} |lambda_R| = {} expected to be {}\n",
    msg, nL, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_N(
  char const      msg[],
  int             nrhs,
  mxArray const * prhs[],
  NodeType2     & N
) {

  mwSize nQ, nX, nL;

  // -------------------
  N.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
  UTILS_ASSERT(
    N.i_segment >= 0 && N.i_segment < this->num_segments(),
    "{} iseg_L = {} expected to be in [0,{})\n",
    msg, N.i_segment, this->num_segments()
  );

  // -------------------
  N.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q_M", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  N.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x_M", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );

  // -------------------
  N.lambda = Utils::mex_vector_pointer( arg_in_5, nL, fmt::format( "{} argument lambda_M", msg ) );
  UTILS_ASSERT(
    nL == this->dim_X(),
    "{} |lambda_L| = {} expected to be {}\n",
    msg, nL, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_qx(
  char const      msg[],
  int             nrhs,
  mxArray const * prhs[],
  NodeType      & N
) {

  mwSize nQ, nX;

  // -------------------
  N.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
  UTILS_ASSERT(
    N.i_segment >= 0 && N.i_segment < this->num_segments(),
    "{} iseg_L = {} expected to be in [0,{})\n",
    msg, N.i_segment, this->num_segments()
  );

  // -------------------
  N.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  N.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_LR(
  char const      msg[],
  int             nrhs,
  mxArray const * prhs[],
  NodeType      & L,
  NodeType      & R
) {

  string msg_str;
  mwSize nQ, nX, nL;

  // -------------------
  msg_str = fmt::format( "{} L_segment", msg );
  L.i_segment = integer( Utils::mex_get_int64( arg_in_2, msg_str.c_str() ) );
  UTILS_ASSERT(
    L.i_segment >= 0 && L.i_segment < this->num_segments(),
    "{} iseg_L = {} expected to be in [0,{})\n",
    msg, L.i_segment, this->num_segments()
  );

  // -------------------
  msg_str = fmt::format( "{} argument q_L", msg );
  L.q = Utils::mex_vector_pointer( arg_in_3, nQ, msg_str.c_str() );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  msg_str = fmt::format( "{} argument x_L", msg );
  L.x = Utils::mex_vector_pointer( arg_in_4, nX, msg_str.c_str() );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );

  // -------------------
  msg_str = fmt::format( "{} R_segment", msg );
  R.i_segment = integer( Utils::mex_get_int64( arg_in_5, msg_str.c_str() ) );
  UTILS_ASSERT(
    R.i_segment >= 0 && R.i_segment < this->num_segments(),
    "{} iseg_R = {} expected to be in [0,{})\n",
    msg, R.i_segment, this->num_segments()
  );

  // -------------------
  msg_str = fmt::format( "{} argument q_R", msg );
  R.q = Utils::mex_vector_pointer( arg_in_6, nQ, msg_str.c_str() );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_R| = {} expected to be {}\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  msg_str = fmt::format( "{} argument x_R", msg );
  R.x = Utils::mex_vector_pointer( arg_in_7, nX, msg_str.c_str() );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_R| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );
}

// EOF: PointMassCarModel_4_Mex_class.cc

