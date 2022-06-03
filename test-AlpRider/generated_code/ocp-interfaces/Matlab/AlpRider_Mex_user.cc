/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Mex_user.cc                                           |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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


#include "AlpRider_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_p_base(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_1', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_1(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_2', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_3', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_1_1', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_1_1(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_1_2', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_1_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_1_3', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_1_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_2_2', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_2_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_2_3', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_2_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_base_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_base_D_3_3', obj, xo__t, xo__a, xo__b ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__a" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__b" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_base_D_3_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_q_lower(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('q_lower', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->q_lower(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_q_lower_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('q_lower_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->q_lower_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_q_lower_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('q_lower_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->q_lower_DD(arg0[ii]);
  #undef CMD
}

// EOF: AlpRider_Mex_user.cc

