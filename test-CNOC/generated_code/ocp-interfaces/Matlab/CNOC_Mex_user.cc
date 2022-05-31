/*-----------------------------------------------------------------------*\
 |  file: CNOC_Mex_user.cc                                               |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "CNOC_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_PathFollowingTolerance(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('PathFollowingTolerance', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->PathFollowingTolerance(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_PathFollowingTolerance_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('PathFollowingTolerance_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->PathFollowingTolerance_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_PathFollowingTolerance_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('PathFollowingTolerance_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->PathFollowingTolerance_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_as_limit(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('as_limit', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->as_limit(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_as_limit_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('as_limit_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->as_limit_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_as_limit_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('as_limit_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->as_limit_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_an_limit(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('an_limit', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->an_limit(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_an_limit_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('an_limit_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->an_limit_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_an_limit_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('an_limit_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->an_limit_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ax_limit(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ax_limit', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ax_limit(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ax_limit_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ax_limit_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ax_limit_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ax_limit_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ax_limit_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ax_limit_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ay_limit(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ay_limit', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ay_limit(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ay_limit_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ay_limit_D', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ay_limit_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_ay_limit_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ay_limit_DD', obj, xo___V ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo___V" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ay_limit_DD(arg0[ii]);
  #undef CMD
}

// EOF: CNOC_Mex_user.cc

