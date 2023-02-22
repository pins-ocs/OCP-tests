/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Mex.cc                                     |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "ICLOCS_ContinuousMP_Mex.hh"

#include <unordered_map>


static char const help_msg[] =
"%===========================================================================%\n"
"Mex command has the following possible calls:\n"
"ICLOCS_ContinuousMP_Mex('command', arguments ):\n"
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

static Mechatronix::Console        * pConsole{nullptr};
static Mechatronix::ThreadPoolBase * pTP{nullptr};

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
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_F);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_JF2_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(eval_U);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_ocp_data);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_raw_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution_as_guess);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution2);
DO_COMMAND_REMAP_TO_CLASS_METHOD(get_solution3);
DO_COMMAND_REMAP_TO_CLASS_METHOD(guess_U);
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
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDxpm);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DgDxpm_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DodeDxpuv);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DodeDxpuv_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DbcDxxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DbcDxxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DabcDxlxlpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DabcDxlxlpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DhcDxlxlop);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DhcDxlxlop_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Dfd_BCDxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(Dfd_BCDxlxlp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DetaDxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DetaDxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DHxpDxpuv);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DHxpDxpuv_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JPD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JPD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JUD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2JUD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DLTargsDxpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DLTargsDxpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTargsD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTargsD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2LTD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DjumpDxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DjumpDxlxlp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2lagrangeD2xpu);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2lagrangeD2xpu_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2mayerD2xxp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(D2mayerD2xxp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DuDxlxlp);
DO_COMMAND_REMAP_TO_CLASS_METHOD(DuDxlxlp_pattern);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u1Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u1Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u2Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u2Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u3Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u3Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u4Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u4Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u5Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u5Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u6Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u6Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u7Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u7Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u8Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u8Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u9Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u9Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u10Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u10Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u11Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u11Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u12Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u12Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u13Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u13Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u14Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u14Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u15Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u15Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u16Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u16Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u17Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u17Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u18Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u18Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u19Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u19Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u20Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(u20Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx1Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx1Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy1Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy1Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx2Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx2Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy2Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy2Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx3Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx3Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy3Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy3Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx4Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx4Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy4Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy4Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx5Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx5Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy5Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy5Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx6Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx6Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy6Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy6Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx7Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx7Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy7Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy7Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx8Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx8Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy8Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy8Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx9Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx9Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy9Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy9Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx10Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx10Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy10Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy10Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx11Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx11Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy11Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy11Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx12Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx12Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy12Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy12Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx13Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx13Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy13Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy13Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx14Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx14Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy14Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy14Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx15Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx15Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy15Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy15Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx16Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx16Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy16Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy16Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx17Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx17Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy17Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy17Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx18Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx18Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy18Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy18Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx19Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx19Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy19Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy19Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx20Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(xx20Limitation_D);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy20Limitation);
DO_COMMAND_REMAP_TO_CLASS_METHOD(yy20Limitation_D);

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
  {"eval_F",do_eval_F},
  {"eval_JF",do_eval_JF},
  {"eval_JF_pattern",do_eval_JF_pattern},
  {"eval_JF2",do_eval_JF2},
  {"eval_JF2_pattern",do_eval_JF2_pattern},
  {"eval_U",do_eval_U},
  {"get_guess",do_get_guess},
  {"get_ocp_data",do_get_ocp_data},
  {"get_raw_solution",do_get_raw_solution},
  {"get_solution",do_get_solution},
  {"get_solution_as_guess",do_get_solution_as_guess},
  {"get_solution2",do_get_solution2},
  {"get_solution3",do_get_solution3},
  {"guess_U",do_guess_U},
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
  {"DgDu",do_DgDu},
  {"DgDu_pattern",do_DgDu_pattern},
  {"DgDxpm",do_DgDxpm},
  {"DgDxpm_pattern",do_DgDxpm_pattern},
  {"DodeDxpuv",do_DodeDxpuv},
  {"DodeDxpuv_pattern",do_DodeDxpuv_pattern},
  {"DbcDxxp",do_DbcDxxp},
  {"DbcDxxp_pattern",do_DbcDxxp_pattern},
  {"DabcDxlxlpu",do_DabcDxlxlpu},
  {"DabcDxlxlpu_pattern",do_DabcDxlxlpu_pattern},
  {"DhcDxlxlop",do_DhcDxlxlop},
  {"DhcDxlxlop_pattern",do_DhcDxlxlop_pattern},
  {"Dfd_BCDxlxlp",do_Dfd_BCDxlxlp},
  {"Dfd_BCDxlxlp_pattern",do_Dfd_BCDxlxlp_pattern},
  {"DetaDxp",do_DetaDxp},
  {"DetaDxp_pattern",do_DetaDxp_pattern},
  {"DHxpDxpuv",do_DHxpDxpuv},
  {"DHxpDxpuv_pattern",do_DHxpDxpuv_pattern},
  {"D2JPD2xpu",do_D2JPD2xpu},
  {"D2JPD2xpu_pattern",do_D2JPD2xpu_pattern},
  {"D2JUD2xpu",do_D2JUD2xpu},
  {"D2JUD2xpu_pattern",do_D2JUD2xpu_pattern},
  {"DLTargsDxpu",do_DLTargsDxpu},
  {"DLTargsDxpu_pattern",do_DLTargsDxpu_pattern},
  {"D2LTargsD2xpu",do_D2LTargsD2xpu},
  {"D2LTargsD2xpu_pattern",do_D2LTargsD2xpu_pattern},
  {"D2LTD2xpu",do_D2LTD2xpu},
  {"D2LTD2xpu_pattern",do_D2LTD2xpu_pattern},
  {"DjumpDxlxlp",do_DjumpDxlxlp},
  {"DjumpDxlxlp_pattern",do_DjumpDxlxlp_pattern},
  {"D2lagrangeD2xpu",do_D2lagrangeD2xpu},
  {"D2lagrangeD2xpu_pattern",do_D2lagrangeD2xpu_pattern},
  {"D2mayerD2xxp",do_D2mayerD2xxp},
  {"D2mayerD2xxp_pattern",do_D2mayerD2xxp_pattern},
  {"DuDxlxlp",do_DuDxlxlp},
  {"DuDxlxlp_pattern",do_DuDxlxlp_pattern},
  {"u1Limitation",do_u1Limitation},
  {"u1Limitation_D",do_u1Limitation_D},
  {"u2Limitation",do_u2Limitation},
  {"u2Limitation_D",do_u2Limitation_D},
  {"u3Limitation",do_u3Limitation},
  {"u3Limitation_D",do_u3Limitation_D},
  {"u4Limitation",do_u4Limitation},
  {"u4Limitation_D",do_u4Limitation_D},
  {"u5Limitation",do_u5Limitation},
  {"u5Limitation_D",do_u5Limitation_D},
  {"u6Limitation",do_u6Limitation},
  {"u6Limitation_D",do_u6Limitation_D},
  {"u7Limitation",do_u7Limitation},
  {"u7Limitation_D",do_u7Limitation_D},
  {"u8Limitation",do_u8Limitation},
  {"u8Limitation_D",do_u8Limitation_D},
  {"u9Limitation",do_u9Limitation},
  {"u9Limitation_D",do_u9Limitation_D},
  {"u10Limitation",do_u10Limitation},
  {"u10Limitation_D",do_u10Limitation_D},
  {"u11Limitation",do_u11Limitation},
  {"u11Limitation_D",do_u11Limitation_D},
  {"u12Limitation",do_u12Limitation},
  {"u12Limitation_D",do_u12Limitation_D},
  {"u13Limitation",do_u13Limitation},
  {"u13Limitation_D",do_u13Limitation_D},
  {"u14Limitation",do_u14Limitation},
  {"u14Limitation_D",do_u14Limitation_D},
  {"u15Limitation",do_u15Limitation},
  {"u15Limitation_D",do_u15Limitation_D},
  {"u16Limitation",do_u16Limitation},
  {"u16Limitation_D",do_u16Limitation_D},
  {"u17Limitation",do_u17Limitation},
  {"u17Limitation_D",do_u17Limitation_D},
  {"u18Limitation",do_u18Limitation},
  {"u18Limitation_D",do_u18Limitation_D},
  {"u19Limitation",do_u19Limitation},
  {"u19Limitation_D",do_u19Limitation_D},
  {"u20Limitation",do_u20Limitation},
  {"u20Limitation_D",do_u20Limitation_D},
  {"xx1Limitation",do_xx1Limitation},
  {"xx1Limitation_D",do_xx1Limitation_D},
  {"yy1Limitation",do_yy1Limitation},
  {"yy1Limitation_D",do_yy1Limitation_D},
  {"xx2Limitation",do_xx2Limitation},
  {"xx2Limitation_D",do_xx2Limitation_D},
  {"yy2Limitation",do_yy2Limitation},
  {"yy2Limitation_D",do_yy2Limitation_D},
  {"xx3Limitation",do_xx3Limitation},
  {"xx3Limitation_D",do_xx3Limitation_D},
  {"yy3Limitation",do_yy3Limitation},
  {"yy3Limitation_D",do_yy3Limitation_D},
  {"xx4Limitation",do_xx4Limitation},
  {"xx4Limitation_D",do_xx4Limitation_D},
  {"yy4Limitation",do_yy4Limitation},
  {"yy4Limitation_D",do_yy4Limitation_D},
  {"xx5Limitation",do_xx5Limitation},
  {"xx5Limitation_D",do_xx5Limitation_D},
  {"yy5Limitation",do_yy5Limitation},
  {"yy5Limitation_D",do_yy5Limitation_D},
  {"xx6Limitation",do_xx6Limitation},
  {"xx6Limitation_D",do_xx6Limitation_D},
  {"yy6Limitation",do_yy6Limitation},
  {"yy6Limitation_D",do_yy6Limitation_D},
  {"xx7Limitation",do_xx7Limitation},
  {"xx7Limitation_D",do_xx7Limitation_D},
  {"yy7Limitation",do_yy7Limitation},
  {"yy7Limitation_D",do_yy7Limitation_D},
  {"xx8Limitation",do_xx8Limitation},
  {"xx8Limitation_D",do_xx8Limitation_D},
  {"yy8Limitation",do_yy8Limitation},
  {"yy8Limitation_D",do_yy8Limitation_D},
  {"xx9Limitation",do_xx9Limitation},
  {"xx9Limitation_D",do_xx9Limitation_D},
  {"yy9Limitation",do_yy9Limitation},
  {"yy9Limitation_D",do_yy9Limitation_D},
  {"xx10Limitation",do_xx10Limitation},
  {"xx10Limitation_D",do_xx10Limitation_D},
  {"yy10Limitation",do_yy10Limitation},
  {"yy10Limitation_D",do_yy10Limitation_D},
  {"xx11Limitation",do_xx11Limitation},
  {"xx11Limitation_D",do_xx11Limitation_D},
  {"yy11Limitation",do_yy11Limitation},
  {"yy11Limitation_D",do_yy11Limitation_D},
  {"xx12Limitation",do_xx12Limitation},
  {"xx12Limitation_D",do_xx12Limitation_D},
  {"yy12Limitation",do_yy12Limitation},
  {"yy12Limitation_D",do_yy12Limitation_D},
  {"xx13Limitation",do_xx13Limitation},
  {"xx13Limitation_D",do_xx13Limitation_D},
  {"yy13Limitation",do_yy13Limitation},
  {"yy13Limitation_D",do_yy13Limitation_D},
  {"xx14Limitation",do_xx14Limitation},
  {"xx14Limitation_D",do_xx14Limitation_D},
  {"yy14Limitation",do_yy14Limitation},
  {"yy14Limitation_D",do_yy14Limitation_D},
  {"xx15Limitation",do_xx15Limitation},
  {"xx15Limitation_D",do_xx15Limitation_D},
  {"yy15Limitation",do_yy15Limitation},
  {"yy15Limitation_D",do_yy15Limitation_D},
  {"xx16Limitation",do_xx16Limitation},
  {"xx16Limitation_D",do_xx16Limitation_D},
  {"yy16Limitation",do_yy16Limitation},
  {"yy16Limitation_D",do_yy16Limitation_D},
  {"xx17Limitation",do_xx17Limitation},
  {"xx17Limitation_D",do_xx17Limitation_D},
  {"yy17Limitation",do_yy17Limitation},
  {"yy17Limitation_D",do_yy17Limitation_D},
  {"xx18Limitation",do_xx18Limitation},
  {"xx18Limitation_D",do_xx18Limitation_D},
  {"yy18Limitation",do_yy18Limitation},
  {"yy18Limitation_D",do_yy18Limitation_D},
  {"xx19Limitation",do_xx19Limitation},
  {"xx19Limitation_D",do_xx19Limitation_D},
  {"yy19Limitation",do_yy19Limitation},
  {"yy19Limitation_D",do_yy19Limitation_D},
  {"xx20Limitation",do_xx20Limitation},
  {"xx20Limitation_D",do_xx20Limitation_D},
  {"yy20Limitation",do_yy20Limitation},
  {"yy20Limitation_D",do_yy20Limitation_D},
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

  static mstream          mout1, mout2;
  static std::streambuf * outbuf{nullptr};
  static std::streambuf * errbuf{nullptr};

  char cmd[256];

  if ( outbuf   == nullptr ) outbuf   = std::cout.rdbuf(&mout1); // Redirect COUT
  if ( errbuf   == nullptr ) errbuf   = std::cerr.rdbuf(&mout2); // Redirect COUT
  if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);
  if ( pTP      == nullptr ) pTP      = new ThreadPool1( std::thread::hardware_concurrency());

  try {
    pConsole->setOff(); // do not colorize
    UTILS_MEX_ASSERT0( nrhs > 0, MODEL_NAME "_Mex: Missing Arguments!" );
    UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), MODEL_NAME "_Mex: First argument must be a string" );
    mxGetString( arg_in_0, cmd, 256 );
    cmd_to_fun.at(cmd)( nlhs, plhs, nrhs, prhs );
  }
  catch ( std::out_of_range const & exc ) {
    mexErrMsgTxt(
      fmt::format( "ICLOCS_ContinuousMP_Mex, unknown command: {}",
      exc.what() ).c_str()
    );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt(
      fmt::format( "ICLOCS_ContinuousMP_Mex, error: {}",
      exc.what() ).c_str()
    );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
