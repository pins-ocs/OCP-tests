/*-----------------------------------------------------------------------*\
 |  file: Hager_2000_Mex_user.cc                                         |
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


#include "Hager_2000_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_x_exact(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_exact', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_exact(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_exact_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_exact_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_exact_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_exact_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_exact_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_exact_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_u_exact(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('u_exact', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->u_exact(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_u_exact_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('u_exact_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->u_exact_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_u_exact_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('u_exact_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->u_exact_DD(arg0[ii]);
  #undef CMD
}

// EOF: Hager_2000_Mex_user.cc
