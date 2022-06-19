/*-----------------------------------------------------------------------*\
 |  file: BangBangFclip_Mex.cc                                           |
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


#include "BangBangFclip_Mex.hh"


static char const help_msg[] =
"%===========================================================================%\n"
"Mex command has the following possible calls:\n"
"BangBangFclip_Mex('command', arguments ):\n"
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

static Console * pConsole  = nullptr;
static integer   n_threads = std::thread::hardware_concurrency();

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
  #define CMD MODEL_NAME "_Mex('new',name): "
  CHECK_IN_OUT( 2, 1 );
  UTILS_MEX_ASSERT0( mxIsChar(arg_in_1), CMD "second argument must be a string" );
  ProblemStorage * ptr = new ProblemStorage( mxArrayToString(arg_in_1), n_threads, pConsole );
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
typedef void (ProblemStorage::*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
typedef void (*DO_CMD2)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static std::map<std::string,DO_CMD> cmd_to_fun = {
  {"info",&ProblemStorage::do_info},
  {"read",&ProblemStorage::do_read},
  {"setup",&ProblemStorage::do_setup},
  {"remesh",&ProblemStorage::do_remesh},
  {"set_guess",&ProblemStorage::do_set_guess},
  {"get_guess",&ProblemStorage::do_get_guess},
  {"get_solution_as_guess",&ProblemStorage::do_get_solution_as_guess},
  {"solve",&ProblemStorage::do_solve},
  {"dims",&ProblemStorage::do_dims},
  {"dim_Q",&ProblemStorage::do_dim_Q},
  {"dim_X",&ProblemStorage::do_dim_X},
  {"dim_Pars",&ProblemStorage::do_dim_Pars},
  {"dim_BC",&ProblemStorage::do_dim_BC},
  {"dim_Post",&ProblemStorage::do_dim_Post},
  {"dim_Ipost",&ProblemStorage::do_dim_Ipost},
  {"dim_full_bc",&ProblemStorage::do_dim_full_bc},
  {"dim_ineq",&ProblemStorage::do_dim_ineq},
  {"num_active_BC",&ProblemStorage::do_num_active_BC},
  {"num_nodes",&ProblemStorage::do_num_nodes},
  {"num_equations",&ProblemStorage::do_num_equations},
  {"num_segments",&ProblemStorage::do_num_segments},
  {"names",&ProblemStorage::do_names},
  {"update_continuation",&ProblemStorage::do_update_continuation},
  {"get_raw_solution",&ProblemStorage::do_get_raw_solution},
  {"set_raw_solution",&ProblemStorage::do_set_raw_solution},
  {"check_raw_solution",&ProblemStorage::do_check_raw_solution},
  {"check_jacobian",&ProblemStorage::do_check_jacobian},
  {"get_solution",&ProblemStorage::do_get_solution},
  {"get_solution2",&ProblemStorage::do_get_solution2},
  {"get_solution3",&ProblemStorage::do_get_solution3},
  {"get_ocp_data",&ProblemStorage::do_get_ocp_data},
  {"init_U",&ProblemStorage::do_init_U},
  {"eval_U",&ProblemStorage::do_eval_U},
  {"eval_F",&ProblemStorage::do_eval_F},
  {"eval_JF",&ProblemStorage::do_eval_JF},
  {"eval_JF_pattern",&ProblemStorage::do_eval_JF_pattern},
  {"pack",&ProblemStorage::do_pack},
  {"pack_for_direct",&ProblemStorage::do_pack_for_direct},
  {"unpack",&ProblemStorage::do_unpack},
  {"unpack_for_direct",&ProblemStorage::do_unpack_for_direct},
  {"estimate_multipliers",&ProblemStorage::do_estimate_multipliers},
  {"ac",&ProblemStorage::do_ac},
  {"hc",&ProblemStorage::do_hc},
  {"u",&ProblemStorage::do_u},
  {"rhs_ode",&ProblemStorage::do_rhs_ode},
  {"eta",&ProblemStorage::do_eta},
  {"nu",&ProblemStorage::do_nu},
  {"Hxp",&ProblemStorage::do_Hxp},
  {"Hu",&ProblemStorage::do_Hu},
  {"LT",&ProblemStorage::do_LT},
  {"JP",&ProblemStorage::do_JP},
  {"JU",&ProblemStorage::do_JU},
  {"LTargs",&ProblemStorage::do_LTargs},
  {"bc",&ProblemStorage::do_bc},
  {"jump",&ProblemStorage::do_jump},
  {"lagrange_target",&ProblemStorage::do_lagrange_target},
  {"DlagrangeDxpu",&ProblemStorage::do_DlagrangeDxpu},
  {"mayer_target",&ProblemStorage::do_mayer_target},
  {"DmayerDxxp",&ProblemStorage::do_DmayerDxxp},
  {"fd_ode",&ProblemStorage::do_fd_ode},
  {"mesh_functions",&ProblemStorage::do_mesh_functions},
  {"nodes",&ProblemStorage::do_nodes},
  {"node_to_segment",&ProblemStorage::do_node_to_segment},
  {"DacDxlxlpu",&ProblemStorage::do_DacDxlxlpu},
  {"DhcDxlxlop",&ProblemStorage::do_DhcDxlxlop},
  {"DuDxlxlp",&ProblemStorage::do_DuDxlxlp},
  {"Drhs_odeDxpu",&ProblemStorage::do_Drhs_odeDxpu},
  {"Drhs_odeDxpu_pattern",&ProblemStorage::do_Drhs_odeDxpu_pattern},
  {"A",&ProblemStorage::do_A},
  {"A_pattern",&ProblemStorage::do_A_pattern},
  {"DetaDxp",&ProblemStorage::do_DetaDxp},
  {"DetaDxp_pattern",&ProblemStorage::do_DetaDxp_pattern},
  {"DnuDxp",&ProblemStorage::do_DnuDxp},
  {"DnuDxp_pattern",&ProblemStorage::do_DnuDxp_pattern},
  {"DHxpDxpu",&ProblemStorage::do_DHxpDxpu},
  {"DHxpDxpu_pattern",&ProblemStorage::do_DHxpDxpu_pattern},
  {"DLTargsDxpu",&ProblemStorage::do_DLTargsDxpu},
  {"DLTargsDxpu_pattern",&ProblemStorage::do_DLTargsDxpu_pattern},
  {"DJPDxpu",&ProblemStorage::do_DJPDxpu},
  {"DJPDxpu_pattern",&ProblemStorage::do_DJPDxpu_pattern},
  {"DLTDxpu",&ProblemStorage::do_DLTDxpu},
  {"DLTDxpu_pattern",&ProblemStorage::do_DLTDxpu_pattern},
  {"DJUDxpu",&ProblemStorage::do_DJUDxpu},
  {"DJUDxpu_pattern",&ProblemStorage::do_DJUDxpu_pattern},
  {"D2LTargsD2xpu",&ProblemStorage::do_D2LTargsD2xpu},
  {"D2LTargsD2xpu_pattern",&ProblemStorage::do_D2LTargsD2xpu_pattern},
  {"D2JPD2xpu",&ProblemStorage::do_D2JPD2xpu},
  {"D2JPD2xpu_pattern",&ProblemStorage::do_D2JPD2xpu_pattern},
  {"D2LTD2xpu",&ProblemStorage::do_D2LTD2xpu},
  {"D2LTD2xpu_pattern",&ProblemStorage::do_D2LTD2xpu_pattern},
  {"D2JUD2xpu",&ProblemStorage::do_D2JUD2xpu},
  {"D2JUD2xpu_pattern",&ProblemStorage::do_D2JUD2xpu_pattern},
  {"DbcDxxp",&ProblemStorage::do_DbcDxxp},
  {"DbcDxxp_pattern",&ProblemStorage::do_DbcDxxp_pattern},
  {"D2bcD2xxp",&ProblemStorage::do_D2bcD2xxp},
  {"D2bcD2xxp_pattern",&ProblemStorage::do_D2bcD2xxp_pattern},
  {"DjumpDxlxlp",&ProblemStorage::do_DjumpDxlxlp},
  {"DjumpDxlxlp_pattern",&ProblemStorage::do_DjumpDxlxlp_pattern},
  {"D2lagrangeD2xpu",&ProblemStorage::do_D2lagrangeD2xpu},
  {"D2lagrangeD2xpu_pattern",&ProblemStorage::do_D2lagrangeD2xpu_pattern},
  {"D2mayerD2xxp",&ProblemStorage::do_D2mayerD2xxp},
  {"D2mayerD2xxp_pattern",&ProblemStorage::do_D2mayerD2xxp_pattern},
  {"Dfd_odeDxxpu",&ProblemStorage::do_Dfd_odeDxxpu},
  {"Dfd_odeDxxpu_pattern",&ProblemStorage::do_Dfd_odeDxxpu_pattern},
  {"D2fd_odeD2xxpu",&ProblemStorage::do_D2fd_odeD2xxpu},
  {"D2fd_odeD2xxpu_pattern",&ProblemStorage::do_D2fd_odeD2xxpu_pattern}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static std::map<std::string,DO_CMD2> cmd_to_fun2 = {
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

static mstream          mout1, mout2;
static std::streambuf * outbuf = nullptr;
static std::streambuf * errbuf = nullptr;

void
mexFunction(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {

  if ( outbuf   == nullptr ) outbuf   = std::cout.rdbuf(&mout1); // Redirect COUT
  if ( errbuf   == nullptr ) errbuf   = std::cerr.rdbuf(&mout2); // Redirect COUT
  if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);

  try {
    pConsole->setOff(); // do not colorize
    UTILS_MEX_ASSERT0( nrhs > 0, MODEL_NAME "_Mex: Missing Arguments!" );
    UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), MODEL_NAME "_Mex: First argument must be a string" );
    string cmd = mxArrayToString(arg_in_0);
    auto it = cmd_to_fun2.find(cmd);
    if ( it != cmd_to_fun2.end() ) {
      it->second( nlhs, plhs, nrhs, prhs );
    } else {
      UTILS_MEX_ASSERT(
        nrhs >= 2,
        "BangBangFclip_Mex('{}',obj,...): Expected at least 2 argument(s), nrhs = {}\n",
        cmd, nrhs
      );
      DO_CMD pfun = cmd_to_fun.at(cmd);
      ProblemStorage * ptr = Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1);
      // string msg = fmt::format( "CALL {} addr {}->{}\n", cmd, fmt::ptr(ptr), pfun );
      // mexPrintf("%s\n", msg.c_str());
      // mexEvalString("disp('end')");
      // mexEvalString("drawnow;");
      (ptr->*pfun)( nlhs, plhs, nrhs, prhs );
      // mexPrintf( "CALL done\n" );
    }
  }
  catch ( std::out_of_range const & exc ) {
    mexErrMsgTxt(
      fmt::format( "BangBangFclip_Mex, unknown command: {}",
      exc.what() ).c_str()
    );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt(
      fmt::format( "BangBangFclip_Mex, error: {}",
      exc.what() ).c_str()
    );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
