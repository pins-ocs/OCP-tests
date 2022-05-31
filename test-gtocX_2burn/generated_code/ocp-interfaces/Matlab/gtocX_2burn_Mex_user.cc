/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Mex_user.cc                                        |
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


#include "gtocX_2burn_Mex.hh"

/*\
 |  _   _               ___             _   _
 | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
 | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
\*/

// user defined functions which has a body defined in MAPLE


void
ProblemStorage::do_cont(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('cont', obj, xo__s, xo__eps0, xo__eps1 ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__s" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__eps0" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__eps1" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->cont(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_position_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_position_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_position_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_position_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_position_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_position_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_x_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('x_velocity_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->x_velocity_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_y_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('y_velocity_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->y_velocity_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_1', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_1_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_1_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_2', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_2_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_2_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3_3', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_3_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_3_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_4_4', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_4_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_4_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_4_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_4_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_4_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_5_5', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_5_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_5_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_5_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_5_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_6_6', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_6_6(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_6_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_6_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_z_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('z_velocity_D_7_7', obj, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde ): "
  CHECK_IN_OUT( 9, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__h" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__k" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);
  mwSize N5, M5;
  real_const_ptr arg5 = Utils::mex_matrix_pointer( arg_in_7, N5, M5, CMD " xo__L" );
  MEX_CHECK_DIMS(N5,M5,N0,M0);
  mwSize N6, M6;
  real_const_ptr arg6 = Utils::mex_matrix_pointer( arg_in_8, N6, M6, CMD " xo__retrograde" );
  MEX_CHECK_DIMS(N6,M6,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->z_velocity_D_7_7(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii],arg5[ii],arg6[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_1', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_1(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_2', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_3', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_1_1', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_1_1(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_1_2', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_1_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_1_3', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_1_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_2_2', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_2_2(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_2_3', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_2_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_norm_reg_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('norm_reg_D_3_3', obj, xo__x, xo__y, xo__z ): "
  CHECK_IN_OUT( 5, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__x" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__y" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__z" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->norm_reg_D_3_3(arg0[ii],arg1[ii],arg2[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_1', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_2', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_3', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_4', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_1_1', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_1_2', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_1_3', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_1_4', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_2_2', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_2_3', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_2_4', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_3_3', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_3_4', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_ray_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('ray_D_4_4', obj, xo__p, xo__f, xo__g, xo__L ): "
  CHECK_IN_OUT( 6, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->ray_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_2', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_3', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_4', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1_1', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1_1(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1_2', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1_3', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1_4', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_1_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_1_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_2_2', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_2_2(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_2_3', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_2_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_2_4', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_2_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_2_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_2_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_3_3', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_3_3(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_3_4', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_3_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_3_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_3_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_4_4', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_4_4(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_4_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_4_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vel_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vel_D_5_5', obj, xo__p, xo__f, xo__g, xo__L, xo__muS ): "
  CHECK_IN_OUT( 7, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__p" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__f" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);
  mwSize N2, M2;
  real_const_ptr arg2 = Utils::mex_matrix_pointer( arg_in_4, N2, M2, CMD " xo__g" );
  MEX_CHECK_DIMS(N2,M2,N0,M0);
  mwSize N3, M3;
  real_const_ptr arg3 = Utils::mex_matrix_pointer( arg_in_5, N3, M3, CMD " xo__L" );
  MEX_CHECK_DIMS(N3,M3,N0,M0);
  mwSize N4, M4;
  real_const_ptr arg4 = Utils::mex_matrix_pointer( arg_in_6, N4, M4, CMD " xo__muS" );
  MEX_CHECK_DIMS(N4,M4,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vel_D_5_5(arg0[ii],arg1[ii],arg2[ii],arg3[ii],arg4[ii]);
  #undef CMD
}

void
ProblemStorage::do_vc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vc', obj, xo__r ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vc(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_vc_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vc_D', obj, xo__r ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vc_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_vc_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('vc_DD', obj, xo__r ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->vc_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r_D_1', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r_D_1(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r_D_2', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r_D_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r_D_1_1', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r_D_1_1(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r_D_1_2', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r_D_1_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_acceleration_r_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('acceleration_r_D_2_2', obj, xo__r, xo__muS ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__r" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__muS" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->acceleration_r_D_2_2(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_begin', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_begin(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_begin_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_begin_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_begin_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_begin_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_X_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('X_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->X_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Y_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Y_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Y_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_Z_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('Z_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->Z_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VX_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VX_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VX_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VY_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VY_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VY_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_end', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_end(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_end_D', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_end_D(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_VZ_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('VZ_end_DD', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->VZ_end_DD(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_p_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('p_guess', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->p_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_f_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('f_guess', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->f_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_g_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('g_guess', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->g_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_h_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('h_guess', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->h_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_k_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('k_guess', obj, xo__t ): "
  CHECK_IN_OUT( 3, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->k_guess(arg0[ii]);
  #undef CMD
}

void
ProblemStorage::do_L_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('L_guess', obj, xo__t, xo__t0 ): "
  CHECK_IN_OUT( 4, 1 );
  mwSize N0, M0;
  real_const_ptr arg0 = Utils::mex_matrix_pointer( arg_in_2, N0, M0, CMD " xo__t" );
  mwSize N1, M1;
  real_const_ptr arg1 = Utils::mex_matrix_pointer( arg_in_3, N1, M1, CMD " xo__t0" );
  MEX_CHECK_DIMS(N1,M1,N0,M0);

  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
  for ( mwSize ii = 0; ii < N0*M0; ++ii )
    res[ii] = this->L_guess(arg0[ii],arg1[ii]);
  #undef CMD
}

void
ProblemStorage::do_guess_setup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('guess_setup', obj,  ): "
  CHECK_IN_OUT( 2, 1 );

  Utils::mex_set_scalar_value( arg_out_0, this->guess_setup() );
  #undef CMD
}

// EOF: gtocX_2burn_Mex_user.cc

