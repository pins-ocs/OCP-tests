/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Mex.cc                                        |
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


#include "gtocX_2burn_pars_Mex.hh"

#include <unordered_map>


static char const help_msg[] =
"%===========================================================================%\n"
"Mex command has the following possible calls:\n"
"gtocX_2burn_pars_Mex('command', arguments ):\n"
"%===========================================================================%\n"
;

/*\
 |  ____    _  _____  _
 | |  _ \  / \|_   _|/ \
 | | | | |/ _ \ | | / _ \
 | | |_| / ___ \| |/ ___ \
 | |____/_/   \_\_/_/   \_\
 |
\*/

Mechatronix::Console        * pConsole{nullptr};
Mechatronix::ThreadPoolBase * pTP{nullptr};

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   _ __   _____      __
//  | '_ \ / _ \ \ /\ / /
//  | | | |  __/\ V  V /
//  |_| |_|\___| \_/\_/
*/
static
void
do_new(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD "obj = " MODEL_NAME "_Mex('new',name): "
  CHECK_IN_OUT( 2, 1 );
  UTILS_MEX_ASSERT0( mxIsChar(arg_in_1), CMD "second argument must be a string" );
  ProblemStorage * ptr = new ProblemStorage( mxArrayToString(arg_in_1), pConsole, pTP );
  arg_out_0 = Utils::mex_convert_ptr_to_mx<ProblemStorage>(ptr);
  #undef CMD
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   _          _
//  | |__   ___| |_ __
//  | '_ \ / _ \ | '_ \
//  | | | |  __/ | |_) |
//  |_| |_|\___|_| .__/
//               |_|
*/
static
void
do_help(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('help'): "
  CHECK_IN_OUT( 1, 0 );
  mexPrintf( "%s", help_msg );
  #undef CMD
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   _        __       _                   _
//  (_)_ __  / _| ___ | |    _____   _____| |
//  | | '_ \| |_ / _ \| |   / _ \ \ / / _ \ |
//  | | | | |  _| (_) | |__|  __/\ V /  __/ |
//  |_|_| |_|_|  \___/|_____\___| \_/ \___|_|
*/
static
void
do_set_info_level(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('set_info_level',obj,infoL): "
  CHECK_IN_OUT( 3, 0 );
  int64_t ilev = Utils::mex_get_int64( arg_in_2, CMD " infoL" );
  pConsole->changeLevel( ilev );
  #undef CMD
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//   _   _    _   _                        _
//  | \ | |  | |_| |__  _ __ ___  __ _  __| |___
//  |  \| |  | __| '_ \| '__/ _ \/ _` |/ _` / __|
//  | |\  |  | |_| | | | | |  __/ (_| | (_| \__ \
//  |_| \_|___\__|_| |_|_|  \___|\__,_|\__,_|___/
//       |_____|
*/
static
void
do_set_max_threads(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('set_max_threads',obj,nt): "
  CHECK_IN_OUT( 3, 0 );
  int64_t N_threads = Utils::mex_get_int64( arg_in_2, CMD " nt" );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->
    set_N_threads( Mechatronix::num_threads_bound( N_threads ) );
  #undef CMD
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//       _      _      _
//    __| | ___| | ___| |_ ___
//   / _` |/ _ \ |/ _ \ __/ _ \
//  | (_| |  __/ |  __/ ||  __/
//   \__,_|\___|_|\___|\__\___|
*/
static
void
do_delete(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('delete',obj): "
  CHECK_IN_OUT( 2, 0 );
  Utils::mex_destroy_object<ProblemStorage>( arg_in_1 );
  #undef CMD
}

/*\
 *                      _____                 _   _
 *  _ __ ___   _____  _|  ___|   _ _ __   ___| |_(_) ___  _ __
 * | '_ ` _ \ / _ \ \/ / |_ | | | | '_ \ / __| __| |/ _ \| '_ \
 * | | | | | |  __/>  <|  _|| |_| | | | | (__| |_| | (_) | | | |
 * |_| |_| |_|\___/_/\_\_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|
 *
\*/

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//typedef void (ProblemStorage::*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
typedef void (*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#define DO_COMMAND_REMAP_TO_CLASS_METHOD(NAME)                            \
static                                                                    \
void                                                                      \
do_##NAME( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] ) { \
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_##NAME(      \
    nlhs, plhs, nrhs, prhs                                                \
  );                                                                      \
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
DO_COMMAND_REMAP_TO_CLASS_METHOD(ode);
DO_COMMAND_REMAP_TO_CLASS_METHOD(bc);
DO_COMMAND_REMAP_TO_CLASS_METHOD(abc);
DO_COMMAND_REMAP_TO_CLASS_METHOD(hc);
DO_COMMAND_REMAP_TO_CLASS_METHOD(fd_BC);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eta);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Hxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(JP);
DO_COMMAND_REMAP_TO_CLASS_METHOD(JPxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(JU);
DO_COMMAND_REMAP_TO_CLASS_METHOD(JUxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(LT);
DO_COMMAND_REMAP_TO_CLASS_METHOD(LTargs);
DO_COMMAND_REMAP_TO_CLASS_METHOD(LTxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(jump);
DO_COMMAND_REMAP_TO_CLASS_METHOD(lagrange_target);
DO_COMMAND_REMAP_TO_CLASS_METHOD(mayer_target);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_BC);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_full_bc);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_ineq);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_Ipost);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_Pars);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_Post);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_Q);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dim_X);
DO_COMMAND_REMAP_TO_CLASS_METHOD(num_active_BC);
DO_COMMAND_REMAP_TO_CLASS_METHOD(num_equations);
DO_COMMAND_REMAP_TO_CLASS_METHOD(num_nodes);
DO_COMMAND_REMAP_TO_CLASS_METHOD(num_segments);
DO_COMMAND_REMAP_TO_CLASS_METHOD(check_jacobian);
DO_COMMAND_REMAP_TO_CLASS_METHOD(check_raw_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(dims);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DlagrangeDxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DmayerDxxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DabcDxlxlpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DhcDxlxlop);
DO_COMMAND_REMAP_TO_CLASS_METHOD(MU_U_eval_Dxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_F);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF2_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_MU_U);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_ocp_data);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_raw_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution_as_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(guess_MU_U);
DO_COMMAND_REMAP_TO_CLASS_METHOD(info);
DO_COMMAND_REMAP_TO_CLASS_METHOD(mesh_functions);
DO_COMMAND_REMAP_TO_CLASS_METHOD(names);
DO_COMMAND_REMAP_TO_CLASS_METHOD(node_to_segment);
DO_COMMAND_REMAP_TO_CLASS_METHOD(nodes);
DO_COMMAND_REMAP_TO_CLASS_METHOD(pack);
DO_COMMAND_REMAP_TO_CLASS_METHOD(read);
DO_COMMAND_REMAP_TO_CLASS_METHOD(remesh);
DO_COMMAND_REMAP_TO_CLASS_METHOD(set_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(set_raw_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(setup);
DO_COMMAND_REMAP_TO_CLASS_METHOD(solve);
DO_COMMAND_REMAP_TO_CLASS_METHOD(unpack);
DO_COMMAND_REMAP_TO_CLASS_METHOD(update_continuation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(A);
DO_COMMAND_REMAP_TO_CLASS_METHOD(A_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JPD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JPD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JUD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JUD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2lagrangeD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2lagrangeD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTargsD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTargsD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2mayerD2xxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2mayerD2xxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DbcDxxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DbcDxxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DetaDxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DetaDxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Dfd_BCDxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Dfd_BCDxlxlp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDxpm);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDxpm_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DHxpDxpuv);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DHxpDxpuv_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DjumpDxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DjumpDxlxlp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DLTargsDxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DLTargsDxpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DodeDxpuv);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DodeDxpuv_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(cont);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_position_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_position_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_position_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(x_velocity_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(y_velocity_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_1_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_2_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_3_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_4_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_4_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_5_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_5_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_6_6);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_6_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(z_velocity_D_7_7);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(norm_reg_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(ray_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_1_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_2_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_2_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_2_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_3_3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_3_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_3_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_4_4);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_4_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vel_D_5_5);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vc);
DO_COMMAND_REMAP_TO_CLASS_METHOD(vc_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r_D_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r_D_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r_D_1_1);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r_D_1_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(acceleration_r_D_2_2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(X_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(X_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Y_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Y_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Z_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Z_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VX_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VX_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VY_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VY_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VZ_begin);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VZ_begin_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(X_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(X_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Y_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Y_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Z_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Z_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VX_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VX_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VY_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VY_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VZ_end);
DO_COMMAND_REMAP_TO_CLASS_METHOD(VZ_end_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(p_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(f_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(g_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(h_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(k_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(L_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(guess_setup);

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static std::unordered_map<std::string,DO_CMD> cmd_to_fun = {
  {"ode",do_ode},
  {"bc",do_bc},
  {"abc",do_abc},
  {"hc",do_hc},
  {"fd_BC",do_fd_BC},
  {"eta",do_eta},
  {"Hxp",do_Hxp},
  {"JP",do_JP},
  {"JPxpu",do_JPxpu},
  {"JU",do_JU},
  {"JUxpu",do_JUxpu},
  {"LT",do_LT},
  {"LTargs",do_LTargs},
  {"LTxpu",do_LTxpu},
  {"jump",do_jump},
  {"lagrange_target",do_lagrange_target},
  {"mayer_target",do_mayer_target},
  {"u",do_u},
  {"dim_BC",do_dim_BC},
  {"dim_full_bc",do_dim_full_bc},
  {"dim_ineq",do_dim_ineq},
  {"dim_Ipost",do_dim_Ipost},
  {"dim_Pars",do_dim_Pars},
  {"dim_Post",do_dim_Post},
  {"dim_Q",do_dim_Q},
  {"dim_X",do_dim_X},
  {"num_active_BC",do_num_active_BC},
  {"num_equations",do_num_equations},
  {"num_nodes",do_num_nodes},
  {"num_segments",do_num_segments},
  {"check_jacobian",do_check_jacobian},
  {"check_raw_solution",do_check_raw_solution},
  {"dims",do_dims},
  {"DlagrangeDxpu",do_DlagrangeDxpu},
  {"DmayerDxxp",do_DmayerDxxp},
  {"DabcDxlxlpu",do_DabcDxlxlpu},
  {"DhcDxlxlop",do_DhcDxlxlop},
  {"MU_U_eval_Dxlxlp",do_MU_U_eval_Dxlxlp},
  {"eval_F",do_eval_F},
  {"eval_JF",do_eval_JF},
  {"eval_JF_pattern",do_eval_JF_pattern},
  {"eval_JF2",do_eval_JF2},
  {"eval_JF2_pattern",do_eval_JF2_pattern},
  {"eval_MU_U",do_eval_MU_U},
  {"get_guess",do_get_guess},
  {"get_ocp_data",do_get_ocp_data},
  {"get_raw_solution",do_get_raw_solution},
  {"get_solution",do_get_solution},
  {"get_solution_as_guess",do_get_solution_as_guess},
  {"get_solution2",do_get_solution2},
  {"get_solution3",do_get_solution3},
  {"guess_MU_U",do_guess_MU_U},
  {"info",do_info},
  {"mesh_functions",do_mesh_functions},
  {"names",do_names},
  {"node_to_segment",do_node_to_segment},
  {"nodes",do_nodes},
  {"pack",do_pack},
  {"read",do_read},
  {"remesh",do_remesh},
  {"set_guess",do_set_guess},
  {"set_raw_solution",do_set_raw_solution},
  {"setup",do_setup},
  {"solve",do_solve},
  {"unpack",do_unpack},
  {"update_continuation",do_update_continuation},
  {"A",do_A},
  {"A_pattern",do_A_pattern},
  {"D2JPD2xpu",do_D2JPD2xpu},
  {"D2JPD2xpu_pattern",do_D2JPD2xpu_pattern},
  {"D2JUD2xpu",do_D2JUD2xpu},
  {"D2JUD2xpu_pattern",do_D2JUD2xpu_pattern},
  {"D2lagrangeD2xpu",do_D2lagrangeD2xpu},
  {"D2lagrangeD2xpu_pattern",do_D2lagrangeD2xpu_pattern},
  {"D2LTargsD2xpu",do_D2LTargsD2xpu},
  {"D2LTargsD2xpu_pattern",do_D2LTargsD2xpu_pattern},
  {"D2LTD2xpu",do_D2LTD2xpu},
  {"D2LTD2xpu_pattern",do_D2LTD2xpu_pattern},
  {"D2mayerD2xxp",do_D2mayerD2xxp},
  {"D2mayerD2xxp_pattern",do_D2mayerD2xxp_pattern},
  {"DbcDxxp",do_DbcDxxp},
  {"DbcDxxp_pattern",do_DbcDxxp_pattern},
  {"DetaDxp",do_DetaDxp},
  {"DetaDxp_pattern",do_DetaDxp_pattern},
  {"Dfd_BCDxlxlp",do_Dfd_BCDxlxlp},
  {"Dfd_BCDxlxlp_pattern",do_Dfd_BCDxlxlp_pattern},
  {"DgDu",do_DgDu},
  {"DgDu_pattern",do_DgDu_pattern},
  {"DgDxpm",do_DgDxpm},
  {"DgDxpm_pattern",do_DgDxpm_pattern},
  {"DHxpDxpuv",do_DHxpDxpuv},
  {"DHxpDxpuv_pattern",do_DHxpDxpuv_pattern},
  {"DjumpDxlxlp",do_DjumpDxlxlp},
  {"DjumpDxlxlp_pattern",do_DjumpDxlxlp_pattern},
  {"DLTargsDxpu",do_DLTargsDxpu},
  {"DLTargsDxpu_pattern",do_DLTargsDxpu_pattern},
  {"DodeDxpuv",do_DodeDxpuv},
  {"DodeDxpuv_pattern",do_DodeDxpuv_pattern},
  {"cont",do_cont},
  {"x_position",do_x_position},
  {"x_position_D_1",do_x_position_D_1},
  {"x_position_D_2",do_x_position_D_2},
  {"x_position_D_3",do_x_position_D_3},
  {"x_position_D_4",do_x_position_D_4},
  {"x_position_D_5",do_x_position_D_5},
  {"x_position_D_6",do_x_position_D_6},
  {"x_position_D_7",do_x_position_D_7},
  {"x_position_D_1_1",do_x_position_D_1_1},
  {"x_position_D_1_2",do_x_position_D_1_2},
  {"x_position_D_1_3",do_x_position_D_1_3},
  {"x_position_D_1_4",do_x_position_D_1_4},
  {"x_position_D_1_5",do_x_position_D_1_5},
  {"x_position_D_1_6",do_x_position_D_1_6},
  {"x_position_D_1_7",do_x_position_D_1_7},
  {"x_position_D_2_2",do_x_position_D_2_2},
  {"x_position_D_2_3",do_x_position_D_2_3},
  {"x_position_D_2_4",do_x_position_D_2_4},
  {"x_position_D_2_5",do_x_position_D_2_5},
  {"x_position_D_2_6",do_x_position_D_2_6},
  {"x_position_D_2_7",do_x_position_D_2_7},
  {"x_position_D_3_3",do_x_position_D_3_3},
  {"x_position_D_3_4",do_x_position_D_3_4},
  {"x_position_D_3_5",do_x_position_D_3_5},
  {"x_position_D_3_6",do_x_position_D_3_6},
  {"x_position_D_3_7",do_x_position_D_3_7},
  {"x_position_D_4_4",do_x_position_D_4_4},
  {"x_position_D_4_5",do_x_position_D_4_5},
  {"x_position_D_4_6",do_x_position_D_4_6},
  {"x_position_D_4_7",do_x_position_D_4_7},
  {"x_position_D_5_5",do_x_position_D_5_5},
  {"x_position_D_5_6",do_x_position_D_5_6},
  {"x_position_D_5_7",do_x_position_D_5_7},
  {"x_position_D_6_6",do_x_position_D_6_6},
  {"x_position_D_6_7",do_x_position_D_6_7},
  {"x_position_D_7_7",do_x_position_D_7_7},
  {"y_position",do_y_position},
  {"y_position_D_1",do_y_position_D_1},
  {"y_position_D_2",do_y_position_D_2},
  {"y_position_D_3",do_y_position_D_3},
  {"y_position_D_4",do_y_position_D_4},
  {"y_position_D_5",do_y_position_D_5},
  {"y_position_D_6",do_y_position_D_6},
  {"y_position_D_7",do_y_position_D_7},
  {"y_position_D_1_1",do_y_position_D_1_1},
  {"y_position_D_1_2",do_y_position_D_1_2},
  {"y_position_D_1_3",do_y_position_D_1_3},
  {"y_position_D_1_4",do_y_position_D_1_4},
  {"y_position_D_1_5",do_y_position_D_1_5},
  {"y_position_D_1_6",do_y_position_D_1_6},
  {"y_position_D_1_7",do_y_position_D_1_7},
  {"y_position_D_2_2",do_y_position_D_2_2},
  {"y_position_D_2_3",do_y_position_D_2_3},
  {"y_position_D_2_4",do_y_position_D_2_4},
  {"y_position_D_2_5",do_y_position_D_2_5},
  {"y_position_D_2_6",do_y_position_D_2_6},
  {"y_position_D_2_7",do_y_position_D_2_7},
  {"y_position_D_3_3",do_y_position_D_3_3},
  {"y_position_D_3_4",do_y_position_D_3_4},
  {"y_position_D_3_5",do_y_position_D_3_5},
  {"y_position_D_3_6",do_y_position_D_3_6},
  {"y_position_D_3_7",do_y_position_D_3_7},
  {"y_position_D_4_4",do_y_position_D_4_4},
  {"y_position_D_4_5",do_y_position_D_4_5},
  {"y_position_D_4_6",do_y_position_D_4_6},
  {"y_position_D_4_7",do_y_position_D_4_7},
  {"y_position_D_5_5",do_y_position_D_5_5},
  {"y_position_D_5_6",do_y_position_D_5_6},
  {"y_position_D_5_7",do_y_position_D_5_7},
  {"y_position_D_6_6",do_y_position_D_6_6},
  {"y_position_D_6_7",do_y_position_D_6_7},
  {"y_position_D_7_7",do_y_position_D_7_7},
  {"z_position",do_z_position},
  {"z_position_D_1",do_z_position_D_1},
  {"z_position_D_2",do_z_position_D_2},
  {"z_position_D_3",do_z_position_D_3},
  {"z_position_D_4",do_z_position_D_4},
  {"z_position_D_5",do_z_position_D_5},
  {"z_position_D_6",do_z_position_D_6},
  {"z_position_D_7",do_z_position_D_7},
  {"z_position_D_1_1",do_z_position_D_1_1},
  {"z_position_D_1_2",do_z_position_D_1_2},
  {"z_position_D_1_3",do_z_position_D_1_3},
  {"z_position_D_1_4",do_z_position_D_1_4},
  {"z_position_D_1_5",do_z_position_D_1_5},
  {"z_position_D_1_6",do_z_position_D_1_6},
  {"z_position_D_1_7",do_z_position_D_1_7},
  {"z_position_D_2_2",do_z_position_D_2_2},
  {"z_position_D_2_3",do_z_position_D_2_3},
  {"z_position_D_2_4",do_z_position_D_2_4},
  {"z_position_D_2_5",do_z_position_D_2_5},
  {"z_position_D_2_6",do_z_position_D_2_6},
  {"z_position_D_2_7",do_z_position_D_2_7},
  {"z_position_D_3_3",do_z_position_D_3_3},
  {"z_position_D_3_4",do_z_position_D_3_4},
  {"z_position_D_3_5",do_z_position_D_3_5},
  {"z_position_D_3_6",do_z_position_D_3_6},
  {"z_position_D_3_7",do_z_position_D_3_7},
  {"z_position_D_4_4",do_z_position_D_4_4},
  {"z_position_D_4_5",do_z_position_D_4_5},
  {"z_position_D_4_6",do_z_position_D_4_6},
  {"z_position_D_4_7",do_z_position_D_4_7},
  {"z_position_D_5_5",do_z_position_D_5_5},
  {"z_position_D_5_6",do_z_position_D_5_6},
  {"z_position_D_5_7",do_z_position_D_5_7},
  {"z_position_D_6_6",do_z_position_D_6_6},
  {"z_position_D_6_7",do_z_position_D_6_7},
  {"z_position_D_7_7",do_z_position_D_7_7},
  {"x_velocity",do_x_velocity},
  {"x_velocity_D_1",do_x_velocity_D_1},
  {"x_velocity_D_2",do_x_velocity_D_2},
  {"x_velocity_D_3",do_x_velocity_D_3},
  {"x_velocity_D_4",do_x_velocity_D_4},
  {"x_velocity_D_5",do_x_velocity_D_5},
  {"x_velocity_D_6",do_x_velocity_D_6},
  {"x_velocity_D_7",do_x_velocity_D_7},
  {"x_velocity_D_1_1",do_x_velocity_D_1_1},
  {"x_velocity_D_1_2",do_x_velocity_D_1_2},
  {"x_velocity_D_1_3",do_x_velocity_D_1_3},
  {"x_velocity_D_1_4",do_x_velocity_D_1_4},
  {"x_velocity_D_1_5",do_x_velocity_D_1_5},
  {"x_velocity_D_1_6",do_x_velocity_D_1_6},
  {"x_velocity_D_1_7",do_x_velocity_D_1_7},
  {"x_velocity_D_2_2",do_x_velocity_D_2_2},
  {"x_velocity_D_2_3",do_x_velocity_D_2_3},
  {"x_velocity_D_2_4",do_x_velocity_D_2_4},
  {"x_velocity_D_2_5",do_x_velocity_D_2_5},
  {"x_velocity_D_2_6",do_x_velocity_D_2_6},
  {"x_velocity_D_2_7",do_x_velocity_D_2_7},
  {"x_velocity_D_3_3",do_x_velocity_D_3_3},
  {"x_velocity_D_3_4",do_x_velocity_D_3_4},
  {"x_velocity_D_3_5",do_x_velocity_D_3_5},
  {"x_velocity_D_3_6",do_x_velocity_D_3_6},
  {"x_velocity_D_3_7",do_x_velocity_D_3_7},
  {"x_velocity_D_4_4",do_x_velocity_D_4_4},
  {"x_velocity_D_4_5",do_x_velocity_D_4_5},
  {"x_velocity_D_4_6",do_x_velocity_D_4_6},
  {"x_velocity_D_4_7",do_x_velocity_D_4_7},
  {"x_velocity_D_5_5",do_x_velocity_D_5_5},
  {"x_velocity_D_5_6",do_x_velocity_D_5_6},
  {"x_velocity_D_5_7",do_x_velocity_D_5_7},
  {"x_velocity_D_6_6",do_x_velocity_D_6_6},
  {"x_velocity_D_6_7",do_x_velocity_D_6_7},
  {"x_velocity_D_7_7",do_x_velocity_D_7_7},
  {"y_velocity",do_y_velocity},
  {"y_velocity_D_1",do_y_velocity_D_1},
  {"y_velocity_D_2",do_y_velocity_D_2},
  {"y_velocity_D_3",do_y_velocity_D_3},
  {"y_velocity_D_4",do_y_velocity_D_4},
  {"y_velocity_D_5",do_y_velocity_D_5},
  {"y_velocity_D_6",do_y_velocity_D_6},
  {"y_velocity_D_7",do_y_velocity_D_7},
  {"y_velocity_D_1_1",do_y_velocity_D_1_1},
  {"y_velocity_D_1_2",do_y_velocity_D_1_2},
  {"y_velocity_D_1_3",do_y_velocity_D_1_3},
  {"y_velocity_D_1_4",do_y_velocity_D_1_4},
  {"y_velocity_D_1_5",do_y_velocity_D_1_5},
  {"y_velocity_D_1_6",do_y_velocity_D_1_6},
  {"y_velocity_D_1_7",do_y_velocity_D_1_7},
  {"y_velocity_D_2_2",do_y_velocity_D_2_2},
  {"y_velocity_D_2_3",do_y_velocity_D_2_3},
  {"y_velocity_D_2_4",do_y_velocity_D_2_4},
  {"y_velocity_D_2_5",do_y_velocity_D_2_5},
  {"y_velocity_D_2_6",do_y_velocity_D_2_6},
  {"y_velocity_D_2_7",do_y_velocity_D_2_7},
  {"y_velocity_D_3_3",do_y_velocity_D_3_3},
  {"y_velocity_D_3_4",do_y_velocity_D_3_4},
  {"y_velocity_D_3_5",do_y_velocity_D_3_5},
  {"y_velocity_D_3_6",do_y_velocity_D_3_6},
  {"y_velocity_D_3_7",do_y_velocity_D_3_7},
  {"y_velocity_D_4_4",do_y_velocity_D_4_4},
  {"y_velocity_D_4_5",do_y_velocity_D_4_5},
  {"y_velocity_D_4_6",do_y_velocity_D_4_6},
  {"y_velocity_D_4_7",do_y_velocity_D_4_7},
  {"y_velocity_D_5_5",do_y_velocity_D_5_5},
  {"y_velocity_D_5_6",do_y_velocity_D_5_6},
  {"y_velocity_D_5_7",do_y_velocity_D_5_7},
  {"y_velocity_D_6_6",do_y_velocity_D_6_6},
  {"y_velocity_D_6_7",do_y_velocity_D_6_7},
  {"y_velocity_D_7_7",do_y_velocity_D_7_7},
  {"z_velocity",do_z_velocity},
  {"z_velocity_D_1",do_z_velocity_D_1},
  {"z_velocity_D_2",do_z_velocity_D_2},
  {"z_velocity_D_3",do_z_velocity_D_3},
  {"z_velocity_D_4",do_z_velocity_D_4},
  {"z_velocity_D_5",do_z_velocity_D_5},
  {"z_velocity_D_6",do_z_velocity_D_6},
  {"z_velocity_D_7",do_z_velocity_D_7},
  {"z_velocity_D_1_1",do_z_velocity_D_1_1},
  {"z_velocity_D_1_2",do_z_velocity_D_1_2},
  {"z_velocity_D_1_3",do_z_velocity_D_1_3},
  {"z_velocity_D_1_4",do_z_velocity_D_1_4},
  {"z_velocity_D_1_5",do_z_velocity_D_1_5},
  {"z_velocity_D_1_6",do_z_velocity_D_1_6},
  {"z_velocity_D_1_7",do_z_velocity_D_1_7},
  {"z_velocity_D_2_2",do_z_velocity_D_2_2},
  {"z_velocity_D_2_3",do_z_velocity_D_2_3},
  {"z_velocity_D_2_4",do_z_velocity_D_2_4},
  {"z_velocity_D_2_5",do_z_velocity_D_2_5},
  {"z_velocity_D_2_6",do_z_velocity_D_2_6},
  {"z_velocity_D_2_7",do_z_velocity_D_2_7},
  {"z_velocity_D_3_3",do_z_velocity_D_3_3},
  {"z_velocity_D_3_4",do_z_velocity_D_3_4},
  {"z_velocity_D_3_5",do_z_velocity_D_3_5},
  {"z_velocity_D_3_6",do_z_velocity_D_3_6},
  {"z_velocity_D_3_7",do_z_velocity_D_3_7},
  {"z_velocity_D_4_4",do_z_velocity_D_4_4},
  {"z_velocity_D_4_5",do_z_velocity_D_4_5},
  {"z_velocity_D_4_6",do_z_velocity_D_4_6},
  {"z_velocity_D_4_7",do_z_velocity_D_4_7},
  {"z_velocity_D_5_5",do_z_velocity_D_5_5},
  {"z_velocity_D_5_6",do_z_velocity_D_5_6},
  {"z_velocity_D_5_7",do_z_velocity_D_5_7},
  {"z_velocity_D_6_6",do_z_velocity_D_6_6},
  {"z_velocity_D_6_7",do_z_velocity_D_6_7},
  {"z_velocity_D_7_7",do_z_velocity_D_7_7},
  {"norm_reg",do_norm_reg},
  {"norm_reg_D_1",do_norm_reg_D_1},
  {"norm_reg_D_2",do_norm_reg_D_2},
  {"norm_reg_D_3",do_norm_reg_D_3},
  {"norm_reg_D_1_1",do_norm_reg_D_1_1},
  {"norm_reg_D_1_2",do_norm_reg_D_1_2},
  {"norm_reg_D_1_3",do_norm_reg_D_1_3},
  {"norm_reg_D_2_2",do_norm_reg_D_2_2},
  {"norm_reg_D_2_3",do_norm_reg_D_2_3},
  {"norm_reg_D_3_3",do_norm_reg_D_3_3},
  {"ray",do_ray},
  {"ray_D_1",do_ray_D_1},
  {"ray_D_2",do_ray_D_2},
  {"ray_D_3",do_ray_D_3},
  {"ray_D_4",do_ray_D_4},
  {"ray_D_1_1",do_ray_D_1_1},
  {"ray_D_1_2",do_ray_D_1_2},
  {"ray_D_1_3",do_ray_D_1_3},
  {"ray_D_1_4",do_ray_D_1_4},
  {"ray_D_2_2",do_ray_D_2_2},
  {"ray_D_2_3",do_ray_D_2_3},
  {"ray_D_2_4",do_ray_D_2_4},
  {"ray_D_3_3",do_ray_D_3_3},
  {"ray_D_3_4",do_ray_D_3_4},
  {"ray_D_4_4",do_ray_D_4_4},
  {"vel",do_vel},
  {"vel_D_1",do_vel_D_1},
  {"vel_D_2",do_vel_D_2},
  {"vel_D_3",do_vel_D_3},
  {"vel_D_4",do_vel_D_4},
  {"vel_D_5",do_vel_D_5},
  {"vel_D_1_1",do_vel_D_1_1},
  {"vel_D_1_2",do_vel_D_1_2},
  {"vel_D_1_3",do_vel_D_1_3},
  {"vel_D_1_4",do_vel_D_1_4},
  {"vel_D_1_5",do_vel_D_1_5},
  {"vel_D_2_2",do_vel_D_2_2},
  {"vel_D_2_3",do_vel_D_2_3},
  {"vel_D_2_4",do_vel_D_2_4},
  {"vel_D_2_5",do_vel_D_2_5},
  {"vel_D_3_3",do_vel_D_3_3},
  {"vel_D_3_4",do_vel_D_3_4},
  {"vel_D_3_5",do_vel_D_3_5},
  {"vel_D_4_4",do_vel_D_4_4},
  {"vel_D_4_5",do_vel_D_4_5},
  {"vel_D_5_5",do_vel_D_5_5},
  {"vc",do_vc},
  {"vc_D",do_vc_D},
  {"acceleration_r",do_acceleration_r},
  {"acceleration_r_D_1",do_acceleration_r_D_1},
  {"acceleration_r_D_2",do_acceleration_r_D_2},
  {"acceleration_r_D_1_1",do_acceleration_r_D_1_1},
  {"acceleration_r_D_1_2",do_acceleration_r_D_1_2},
  {"acceleration_r_D_2_2",do_acceleration_r_D_2_2},
  {"X_begin",do_X_begin},
  {"X_begin_D",do_X_begin_D},
  {"Y_begin",do_Y_begin},
  {"Y_begin_D",do_Y_begin_D},
  {"Z_begin",do_Z_begin},
  {"Z_begin_D",do_Z_begin_D},
  {"VX_begin",do_VX_begin},
  {"VX_begin_D",do_VX_begin_D},
  {"VY_begin",do_VY_begin},
  {"VY_begin_D",do_VY_begin_D},
  {"VZ_begin",do_VZ_begin},
  {"VZ_begin_D",do_VZ_begin_D},
  {"X_end",do_X_end},
  {"X_end_D",do_X_end_D},
  {"Y_end",do_Y_end},
  {"Y_end_D",do_Y_end_D},
  {"Z_end",do_Z_end},
  {"Z_end_D",do_Z_end_D},
  {"VX_end",do_VX_end},
  {"VX_end_D",do_VX_end_D},
  {"VY_end",do_VY_end},
  {"VY_end_D",do_VY_end_D},
  {"VZ_end",do_VZ_end},
  {"VZ_end_D",do_VZ_end_D},
  {"p_guess",do_p_guess},
  {"f_guess",do_f_guess},
  {"g_guess",do_g_guess},
  {"h_guess",do_h_guess},
  {"k_guess",do_k_guess},
  {"L_guess",do_L_guess},
  {"guess_setup",do_guess_setup},
  {"new",do_new},
  {"delete",do_delete},
  {"set_info_level",do_set_info_level},
  {"set_max_threads",do_set_max_threads},
  {"help",do_help}
};

//
// redirect stream
// https://www.programmerall.com/article/32541581315/
//

class mstream : public std::streambuf {
public:
protected:

  std::streamsize
  xsputn (const char *s, std::streamsize n) override {
    mexPrintf ("%.*s", n, s);
    return n;
  }

  int
  overflow (int c = EOF) override {
    if (c != EOF) mexPrintf ("%.1s", &c);
    return 1;
  }
};


void
mexFunction(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  static bool             first_run{true};
  static mstream          mout1, mout2;
  static std::streambuf * outbuf{nullptr};
  static std::streambuf * errbuf{nullptr};

  char cmd[256];

  if ( first_run ) {
    outbuf   = std::cout.rdbuf(&mout1); // Redirect COUT
    errbuf   = std::cerr.rdbuf(&mout2); // Redirect COUT
    pConsole = new Console(&std::cout,4);
    pTP      = new ThreadPool1( std::thread::hardware_concurrency());
    Mechatronix::set_PINS_running_in_a_mex(true);
    first_run = false;
  }

  try {
    pConsole->setOff(); // do not colorize
    UTILS_MEX_ASSERT0( nrhs > 0, MODEL_NAME "_Mex: Missing Arguments!" );
    UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), MODEL_NAME "_Mex: First argument must be a string" );
    mxGetString( arg_in_0, cmd, 256 );
    cmd_to_fun.at(cmd)( nlhs, plhs, nrhs, prhs );
  }
  catch ( std::out_of_range const & exc ) {
    mexErrMsgTxt(
      fmt::format( "gtocX_2burn_pars_Mex, unknown command: {}",
      exc.what() ).c_str()
    );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt(
      fmt::format( "gtocX_2burn_pars_Mex, error: {}",
      exc.what() ).c_str()
    );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
