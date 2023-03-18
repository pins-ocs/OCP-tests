/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Mex_class.cc                               |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "PointMassCarModel_2_Mex.hh"

ProblemStorage::ProblemStorage(
  std::string const & cname,
  Console const     * console,
  ThreadPoolBase    * TP
)
: MODEL_CLASS(cname,console,TP)
// user defined Object instances (external)
, m_road( "road" )
{}

ProblemStorage::~ProblemStorage() {}

void
ProblemStorage::done_setup() {
  m_setup_ok     = true;
  m_guess_ok     = false;
  m_solve_ok     = false;
  m_solution1_ok = false;
  m_solution2_ok = false;
  m_solution3_ok = false;
}

void
ProblemStorage::done_guess() {
  m_setup_ok     = true;
  m_guess_ok     = true;
  m_solve_ok     = false;
  m_solution1_ok = false;
  m_solution2_ok = false;
  m_solution3_ok = false;
}

void
ProblemStorage::done_solve() {
  m_setup_ok     = true;
  m_guess_ok     = true;
  m_solve_ok     = true;
  m_solution1_ok = false;
  m_solution2_ok = false;
  m_solution3_ok = false;
}

void
ProblemStorage::read( string const & fname, GenericContainer & gc ) {
  // redirect output
  Mechatronix::STDOUT_redirect rd;
  rd.start();
  bool ok = Mechatronix::load_script( fname, gc );
  if ( !ok ) {
    std::string msg = fmt::format( "Mechatronix::load_script file:'{}' file not found\n", fname );
    mexErrMsgTxt( msg.c_str() );
  }
  rd.stop();
  if ( rd.str().length() > 0 ) {
    std::string msg = fmt::format( "Mechatronix::load_script file:'{}' return:\n``{}''\n", fname, rd.str() );
    pConsole->message( msg, 0 );
  }
}

// --------------------------------------------------------------------------

void
ProblemStorage::get(
  char const    * msg,
  mxArray const * prhs,
  NodeQXL       & S
) {

  UTILS_ASSERT( mxIsStruct( prhs ), "ProblemStorage::get, argument must be a struct" );

  mwSize nQ, nX, nL;

  mxArray const * mx_segment = mxGetField( prhs, 0, "i_segment" );
  mxArray const * mx_q       = mxGetField( prhs, 0, "q"         );
  mxArray const * mx_X       = mxGetField( prhs, 0, "x"         );
  mxArray const * mx_L       = mxGetField( prhs, 0, "lambda"    );

  UTILS_ASSERT( mx_segment != nullptr, "ProblemStorage::get, missing field `i_segment`" );
  UTILS_ASSERT( mx_q       != nullptr, "ProblemStorage::get, missing field `q`"         );
  UTILS_ASSERT( mx_X       != nullptr, "ProblemStorage::get, missing field `x`"         );
  UTILS_ASSERT( mx_L       != nullptr, "ProblemStorage::get, missing field `lambda`"    );

  // -------------------
  S.i_segment = integer( Utils::mex_get_int64( mx_segment, fmt::format( "{} S.i_segment", msg ) ) );
  UTILS_ASSERT(
    S.i_segment >= 0 && S.i_segment < this->num_segments(),
    "{} i_segment = {} expected to be in [0,{})\n",
    msg, S.i_segment, this->num_segments()
  );

  // -------------------
  S.q = Utils::mex_vector_pointer( mx_q, nQ, fmt::format( "{} S.q", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  S.x = Utils::mex_vector_pointer( mx_X, nX, fmt::format( "{} S.x", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );

  // -------------------
  S.lambda = Utils::mex_vector_pointer( mx_L, nL, fmt::format( "{} S.lambda", msg ) );
  UTILS_ASSERT(
    nL == this->dim_X(),
    "{} |lambda_L| = {} expected to be {}\n",
    msg, nL, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get(
  char const    * msg,
  mxArray const * prhs,
  NodeQX        & S
) {

  UTILS_ASSERT( mxIsStruct( prhs ), "ProblemStorage::get, argument must be a struct" );

  mwSize nQ, nX, nL;

  mxArray const * mx_segment = mxGetField( prhs, 0, "i_segment" );
  mxArray const * mx_q       = mxGetField( prhs, 0, "q"         );
  mxArray const * mx_X       = mxGetField( prhs, 0, "x"         );

  UTILS_ASSERT( mx_segment != nullptr, "ProblemStorage::get, missing field `i_segment`" );
  UTILS_ASSERT( mx_q       != nullptr, "ProblemStorage::get, missing field `q`"         );
  UTILS_ASSERT( mx_X       != nullptr, "ProblemStorage::get, missing field `x`"         );

  // -------------------
  S.i_segment = integer( Utils::mex_get_int64( mx_segment, fmt::format( "{} S.i_segment", msg ) ) );
  UTILS_ASSERT(
    S.i_segment >= 0 && S.i_segment < this->num_segments(),
    "{} i_segment = {} expected to be in [0,{})\n",
    msg, S.i_segment, this->num_segments()
  );

  // -------------------
  S.q = Utils::mex_vector_pointer( mx_q, nQ, fmt::format( "{} S.q", msg ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
    msg, nQ, this->dim_Q()
  );

  // -------------------
  S.x = Utils::mex_vector_pointer( mx_X, nX, fmt::format( "{} S.x", msg ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x_L| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_Q(
  char const       msg[],
  mxArray const  * mx_q,
  Q_const_p_type & Q
) {
  mwSize nQ;
  Q.set( Utils::mex_vector_pointer( mx_q, nQ, fmt::format( "get_Q {}", msg ) ) );
  UTILS_ASSERT(
    nQ == this->dim_Q(),
    "{} |q| = {} expected to be {}\n",
    msg, nQ, this->dim_Q()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_X(
  char const       msg[],
  mxArray const  * mx_X,
  X_const_p_type & X
) {
  mwSize nX;
  X.set( Utils::mex_vector_pointer( mx_X, nX, fmt::format( "get_X {}", msg ) ) );
  UTILS_ASSERT(
    nX == this->dim_X(),
    "{} |x| = {} expected to be {}\n",
    msg, nX, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_L(
  char const       msg[],
  mxArray const  * mx_L,
  L_const_p_type & L
) {
  mwSize nL;
  L.set( Utils::mex_vector_pointer( mx_L, nL, fmt::format( "get_L {}", msg ) ) );
  UTILS_ASSERT(
    nL == this->dim_X(),
    "{} |lambda| = {} expected to be {}\n",
    msg, nL, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_MU(
  char const        msg[],
  mxArray const   * mx_MU,
  MU_const_p_type & MU
) {
  mwSize nMU;
  MU.set( Utils::mex_vector_pointer( mx_MU, nMU, fmt::format( "get_MU {}", msg ) ) );
  UTILS_ASSERT(
    nMU == this->dim_X(), // MU = X in dimensione
    "{} |lambda| = {} expected to be {}\n",
    msg, nMU, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_U(
  char const       msg[],
  mxArray const  * mx_U,
  U_const_p_type & U
) {
  mwSize nU;
  U.set( Utils::mex_vector_pointer( mx_U, nU, fmt::format( "get_U {}", msg ) ) );
  UTILS_ASSERT(
    nU == this->dim_U(),
    "{} |U| = {} expected to be {}\n",
    msg, nU, this->dim_U()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_P(
  char const       msg[],
  mxArray const  * mx_P,
  P_const_p_type & P
) {
  mwSize nP;
  P.set( Utils::mex_vector_pointer( mx_P, nP, fmt::format( "get_P {}", msg ) ) );
  UTILS_ASSERT(
    nP == this->dim_Pars(),
    "{} |P| = {} expected to be {}\n",
    msg, nP, this->dim_Pars()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_V(
  char const       msg[],
  mxArray const  * mx_V,
  V_const_p_type & V
) {
  mwSize nV;
  V.set( Utils::mex_vector_pointer( mx_V, nV, fmt::format( "get_V {}", msg ) ) );
  UTILS_ASSERT(
    nV == this->dim_X(),
    "{} |V| = {} expected to be {}\n",
    msg, nV, this->dim_X()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_OMEGA(
  char const           msg[],
  mxArray const      * mx_OMEGA,
  OMEGA_const_p_type & OMEGA
) {
  mwSize nOMEGA;
  OMEGA.set( Utils::mex_vector_pointer( mx_OMEGA, nOMEGA, fmt::format( "get_OMEGA {}", msg ) ) );
  UTILS_ASSERT(
    nOMEGA == this->dim_BC(),
    "{} |OMEGA| = {} expected to be {}\n",
    msg, nOMEGA, this->dim_BC()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_OMEGA_full(
  char const                msg[],
  mxArray const           * mx_OMEGA_full,
  OMEGA_full_const_p_type & OMEGA_full
) {
  mwSize nOMEGA_full;
  OMEGA_full.set( Utils::mex_vector_pointer( mx_OMEGA_full, nOMEGA_full, fmt::format( "get_OMEGA_full {}", msg ) ) );
  UTILS_ASSERT(
    nOMEGA_full == this->dim_BC(),
    "{} |OMEGA_full| = {} expected to be {}\n",
    msg, nOMEGA_full, this->dim_BC()
  );
}

// --------------------------------------------------------------------------

void
ProblemStorage::get_ptr(
  char const       msg[],
  mxArray const  * mx_ptr,
  real_const_ptr & ptr
) {
  mwSize n;
  ptr = Utils::mex_vector_pointer( mx_ptr, n, fmt::format( "get_ptr {}", msg ) );
}

// --------------------------------------------------------------------------

// EOF: PointMassCarModel_2_Mex_class.cc
