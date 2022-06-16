/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Mex_user.cc                             |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_U(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('U', obj, xo__w ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__w" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->U(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_U_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('U_D', obj, xo__w ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__w" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->U_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_U_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('U_DD', obj, xo__w ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__w" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->U_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu_D_1', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu_D_1(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu_D_2', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu_D_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu_D_1_1', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu_D_1_1(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu_D_1_2', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu_D_1_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_mu_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('mu_D_2_2', obj, xo__s, xo__x ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__x" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->mu_D_2_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_rho(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('rho', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->rho(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_rho_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('rho_D', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->rho_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_rho_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('rho_DD', obj, xo__s ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->rho_DD(arg0[ii]);
  #undef CMD
}

// EOF: ICLOCS2_BatchFermentor_Mex_user.cc

