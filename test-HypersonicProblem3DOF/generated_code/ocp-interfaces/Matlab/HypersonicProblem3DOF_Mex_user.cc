/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Mex_user.cc                              |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "HypersonicProblem3DOF_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_h_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('h_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->h_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_h_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('h_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->h_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_h_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('h_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->h_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_theta_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('theta_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->theta_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_theta_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('theta_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->theta_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_theta_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('theta_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->theta_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_phi_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('phi_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->phi_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_phi_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('phi_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->phi_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_phi_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('phi_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->phi_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_V_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('V_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->V_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_V_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('V_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->V_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_V_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('V_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->V_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_psi_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('psi_guess', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->psi_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_psi_guess_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('psi_guess_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->psi_guess_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_psi_guess_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('psi_guess_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->psi_guess_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_bound(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_bound', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_bound(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_bound_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_bound_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_bound_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_G_bound_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('G_bound_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->G_bound_DD(arg0[ii]);
  #undef CMD
}

// EOF: HypersonicProblem3DOF_Mex_user.cc

