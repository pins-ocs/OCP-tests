/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Mex_user.cc                                |
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


#include "PointMassCarModel_3_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_zeta__dot(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_1', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_2', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_3', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_4', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_1_1', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_1_2', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_1_3', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_1_4', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_2_2', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_2_3', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_2_4', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_3_3', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_3_4', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_zeta__dot_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "res = " MODEL_NAME "_Mex('zeta__dot_D_4_4', obj, xo__V, xo__alpha, xo__n, xo__Kappa ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__V" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__alpha" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__n" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__Kappa" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->zeta__dot_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

// EOF: PointMassCarModel_3_Mex_user.cc

