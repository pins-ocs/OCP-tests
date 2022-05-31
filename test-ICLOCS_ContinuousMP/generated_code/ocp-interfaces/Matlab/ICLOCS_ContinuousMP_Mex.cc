/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Mex.cc                                     |
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


#include "ICLOCS_ContinuousMP_Mex.hh"


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
  {"D2fd_odeD2xxpu_pattern",&ProblemStorage::do_D2fd_odeD2xxpu_pattern},
  {"u1Limitation",&ProblemStorage::do_u1Limitation},
  {"u1Limitation_D",&ProblemStorage::do_u1Limitation_D},
  {"u2Limitation",&ProblemStorage::do_u2Limitation},
  {"u2Limitation_D",&ProblemStorage::do_u2Limitation_D},
  {"u3Limitation",&ProblemStorage::do_u3Limitation},
  {"u3Limitation_D",&ProblemStorage::do_u3Limitation_D},
  {"u4Limitation",&ProblemStorage::do_u4Limitation},
  {"u4Limitation_D",&ProblemStorage::do_u4Limitation_D},
  {"u5Limitation",&ProblemStorage::do_u5Limitation},
  {"u5Limitation_D",&ProblemStorage::do_u5Limitation_D},
  {"u6Limitation",&ProblemStorage::do_u6Limitation},
  {"u6Limitation_D",&ProblemStorage::do_u6Limitation_D},
  {"u7Limitation",&ProblemStorage::do_u7Limitation},
  {"u7Limitation_D",&ProblemStorage::do_u7Limitation_D},
  {"u8Limitation",&ProblemStorage::do_u8Limitation},
  {"u8Limitation_D",&ProblemStorage::do_u8Limitation_D},
  {"u9Limitation",&ProblemStorage::do_u9Limitation},
  {"u9Limitation_D",&ProblemStorage::do_u9Limitation_D},
  {"u10Limitation",&ProblemStorage::do_u10Limitation},
  {"u10Limitation_D",&ProblemStorage::do_u10Limitation_D},
  {"u11Limitation",&ProblemStorage::do_u11Limitation},
  {"u11Limitation_D",&ProblemStorage::do_u11Limitation_D},
  {"u12Limitation",&ProblemStorage::do_u12Limitation},
  {"u12Limitation_D",&ProblemStorage::do_u12Limitation_D},
  {"u13Limitation",&ProblemStorage::do_u13Limitation},
  {"u13Limitation_D",&ProblemStorage::do_u13Limitation_D},
  {"u14Limitation",&ProblemStorage::do_u14Limitation},
  {"u14Limitation_D",&ProblemStorage::do_u14Limitation_D},
  {"u15Limitation",&ProblemStorage::do_u15Limitation},
  {"u15Limitation_D",&ProblemStorage::do_u15Limitation_D},
  {"u16Limitation",&ProblemStorage::do_u16Limitation},
  {"u16Limitation_D",&ProblemStorage::do_u16Limitation_D},
  {"u17Limitation",&ProblemStorage::do_u17Limitation},
  {"u17Limitation_D",&ProblemStorage::do_u17Limitation_D},
  {"u18Limitation",&ProblemStorage::do_u18Limitation},
  {"u18Limitation_D",&ProblemStorage::do_u18Limitation_D},
  {"u19Limitation",&ProblemStorage::do_u19Limitation},
  {"u19Limitation_D",&ProblemStorage::do_u19Limitation_D},
  {"u20Limitation",&ProblemStorage::do_u20Limitation},
  {"u20Limitation_D",&ProblemStorage::do_u20Limitation_D},
  {"xx1Limitation",&ProblemStorage::do_xx1Limitation},
  {"xx1Limitation_D",&ProblemStorage::do_xx1Limitation_D},
  {"yy1Limitation",&ProblemStorage::do_yy1Limitation},
  {"yy1Limitation_D",&ProblemStorage::do_yy1Limitation_D},
  {"xx2Limitation",&ProblemStorage::do_xx2Limitation},
  {"xx2Limitation_D",&ProblemStorage::do_xx2Limitation_D},
  {"yy2Limitation",&ProblemStorage::do_yy2Limitation},
  {"yy2Limitation_D",&ProblemStorage::do_yy2Limitation_D},
  {"xx3Limitation",&ProblemStorage::do_xx3Limitation},
  {"xx3Limitation_D",&ProblemStorage::do_xx3Limitation_D},
  {"yy3Limitation",&ProblemStorage::do_yy3Limitation},
  {"yy3Limitation_D",&ProblemStorage::do_yy3Limitation_D},
  {"xx4Limitation",&ProblemStorage::do_xx4Limitation},
  {"xx4Limitation_D",&ProblemStorage::do_xx4Limitation_D},
  {"yy4Limitation",&ProblemStorage::do_yy4Limitation},
  {"yy4Limitation_D",&ProblemStorage::do_yy4Limitation_D},
  {"xx5Limitation",&ProblemStorage::do_xx5Limitation},
  {"xx5Limitation_D",&ProblemStorage::do_xx5Limitation_D},
  {"yy5Limitation",&ProblemStorage::do_yy5Limitation},
  {"yy5Limitation_D",&ProblemStorage::do_yy5Limitation_D},
  {"xx6Limitation",&ProblemStorage::do_xx6Limitation},
  {"xx6Limitation_D",&ProblemStorage::do_xx6Limitation_D},
  {"yy6Limitation",&ProblemStorage::do_yy6Limitation},
  {"yy6Limitation_D",&ProblemStorage::do_yy6Limitation_D},
  {"xx7Limitation",&ProblemStorage::do_xx7Limitation},
  {"xx7Limitation_D",&ProblemStorage::do_xx7Limitation_D},
  {"yy7Limitation",&ProblemStorage::do_yy7Limitation},
  {"yy7Limitation_D",&ProblemStorage::do_yy7Limitation_D},
  {"xx8Limitation",&ProblemStorage::do_xx8Limitation},
  {"xx8Limitation_D",&ProblemStorage::do_xx8Limitation_D},
  {"yy8Limitation",&ProblemStorage::do_yy8Limitation},
  {"yy8Limitation_D",&ProblemStorage::do_yy8Limitation_D},
  {"xx9Limitation",&ProblemStorage::do_xx9Limitation},
  {"xx9Limitation_D",&ProblemStorage::do_xx9Limitation_D},
  {"yy9Limitation",&ProblemStorage::do_yy9Limitation},
  {"yy9Limitation_D",&ProblemStorage::do_yy9Limitation_D},
  {"xx10Limitation",&ProblemStorage::do_xx10Limitation},
  {"xx10Limitation_D",&ProblemStorage::do_xx10Limitation_D},
  {"yy10Limitation",&ProblemStorage::do_yy10Limitation},
  {"yy10Limitation_D",&ProblemStorage::do_yy10Limitation_D},
  {"xx11Limitation",&ProblemStorage::do_xx11Limitation},
  {"xx11Limitation_D",&ProblemStorage::do_xx11Limitation_D},
  {"yy11Limitation",&ProblemStorage::do_yy11Limitation},
  {"yy11Limitation_D",&ProblemStorage::do_yy11Limitation_D},
  {"xx12Limitation",&ProblemStorage::do_xx12Limitation},
  {"xx12Limitation_D",&ProblemStorage::do_xx12Limitation_D},
  {"yy12Limitation",&ProblemStorage::do_yy12Limitation},
  {"yy12Limitation_D",&ProblemStorage::do_yy12Limitation_D},
  {"xx13Limitation",&ProblemStorage::do_xx13Limitation},
  {"xx13Limitation_D",&ProblemStorage::do_xx13Limitation_D},
  {"yy13Limitation",&ProblemStorage::do_yy13Limitation},
  {"yy13Limitation_D",&ProblemStorage::do_yy13Limitation_D},
  {"xx14Limitation",&ProblemStorage::do_xx14Limitation},
  {"xx14Limitation_D",&ProblemStorage::do_xx14Limitation_D},
  {"yy14Limitation",&ProblemStorage::do_yy14Limitation},
  {"yy14Limitation_D",&ProblemStorage::do_yy14Limitation_D},
  {"xx15Limitation",&ProblemStorage::do_xx15Limitation},
  {"xx15Limitation_D",&ProblemStorage::do_xx15Limitation_D},
  {"yy15Limitation",&ProblemStorage::do_yy15Limitation},
  {"yy15Limitation_D",&ProblemStorage::do_yy15Limitation_D},
  {"xx16Limitation",&ProblemStorage::do_xx16Limitation},
  {"xx16Limitation_D",&ProblemStorage::do_xx16Limitation_D},
  {"yy16Limitation",&ProblemStorage::do_yy16Limitation},
  {"yy16Limitation_D",&ProblemStorage::do_yy16Limitation_D},
  {"xx17Limitation",&ProblemStorage::do_xx17Limitation},
  {"xx17Limitation_D",&ProblemStorage::do_xx17Limitation_D},
  {"yy17Limitation",&ProblemStorage::do_yy17Limitation},
  {"yy17Limitation_D",&ProblemStorage::do_yy17Limitation_D},
  {"xx18Limitation",&ProblemStorage::do_xx18Limitation},
  {"xx18Limitation_D",&ProblemStorage::do_xx18Limitation_D},
  {"yy18Limitation",&ProblemStorage::do_yy18Limitation},
  {"yy18Limitation_D",&ProblemStorage::do_yy18Limitation_D},
  {"xx19Limitation",&ProblemStorage::do_xx19Limitation},
  {"xx19Limitation_D",&ProblemStorage::do_xx19Limitation_D},
  {"yy19Limitation",&ProblemStorage::do_yy19Limitation},
  {"yy19Limitation_D",&ProblemStorage::do_yy19Limitation_D},
  {"xx20Limitation",&ProblemStorage::do_xx20Limitation},
  {"xx20Limitation_D",&ProblemStorage::do_xx20Limitation_D},
  {"yy20Limitation",&ProblemStorage::do_yy20Limitation},
  {"yy20Limitation_D",&ProblemStorage::do_yy20Limitation_D}
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
        "ICLOCS_ContinuousMP_Mex('{}',obj,...): Expected at least 2 argument(s), nrhs = {}\n",
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
