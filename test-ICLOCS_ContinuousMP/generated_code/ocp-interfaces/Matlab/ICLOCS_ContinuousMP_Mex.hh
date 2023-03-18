/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Mex.cc                                     |
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

#include "GenericContainerMatlabInterface.hh"
#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"
#include <sstream>

#include <MechatronixCore/Utils_mex.hh>

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace ICLOCS_ContinuousMPLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;

#define MODEL_NAME  "ICLOCS_ContinuousMP"
#define MODEL_CLASS ICLOCS_ContinuousMP

#define CHECK_IN(N)              UTILS_MEX_ASSERT( nrhs == N, CMD "Expected {} argument(s), nrhs = {}\n", N, nrhs )
#define CHECK_OUT(N)             UTILS_MEX_ASSERT( nlhs == N, CMD "Expected {} argument(s), nlhs = {}\n", N, nlhs )
#define CHECK_IN_OUT(N,M)        CHECK_IN(N); CHECK_OUT(M)
#define MEX_CHECK_DIMS(A,B,C,D)  UTILS_MEX_ASSERT0( A == C && B == D, CMD "Argument dimensions must be the same\n" )

#define RETURN_SPARSE(MATNAME,...)                                    \
  size_t nnz = size_t(this->MATNAME##_nnz());                         \
  mxArray *args[5];                                                   \
  real_ptr Irow = Utils::mex_create_matrix_value( args[0], 1, nnz );  \
  real_ptr Jcol = Utils::mex_create_matrix_value( args[1], 1, nnz );  \
  real_ptr VALS = Utils::mex_create_matrix_value( args[2], 1, nnz );  \
  Utils::mex_set_scalar_value( args[3], this->MATNAME##_numRows() );  \
  Utils::mex_set_scalar_value( args[4], this->MATNAME##_numCols() );  \
                                                                      \
  Mechatronix::Malloc<integer> mem("mex_" #MATNAME );                 \
  mem.allocate( 2*nnz, #MATNAME );                                    \
  integer_ptr i_row = mem( nnz );                                     \
  integer_ptr j_col = mem( nnz );                                     \
  this->MATNAME##_pattern( i_row, j_col );                            \
  for ( size_t i = 0; i < nnz; ++i )                                  \
    { Irow[i] = i_row[i]+1; Jcol[i] = j_col[i]+1; }                   \
  this->MATNAME##_sparse( __VA_ARGS__, VALS );                        \
                                                                      \
  int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );         \
  UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" )

/*\
 |  ___         _    _           ___ _
 | | _ \_ _ ___| |__| |___ _ __ / __| |_ ___ _ _ __ _ __ _ ___
 | |  _/ '_/ _ \ '_ \ / -_) '  \\__ \  _/ _ \ '_/ _` / _` / -_)
 | |_| |_| \___/_.__/_\___|_|_|_|___/\__\___/_| \__,_\__, \___|
 |                                                   |___/
\*/
class ProblemStorage : public MODEL_CLASS {

  bool m_setup_ok     = false;
  bool m_guess_ok     = false;
  bool m_solve_ok     = false;
  bool m_solution1_ok = false;
  bool m_solution2_ok = false;
  bool m_solution3_ok = false;

  GenericContainer m_gc_data;
  GenericContainer m_gc_solution1;
  GenericContainer m_gc_solution2;
  GenericContainer m_gc_solution3;

  // user defined Object instances (external)

  MeshStd              m_mesh;

public:

  using MODEL_CLASS::guess;

  ProblemStorage(
    std::string const & cname,
    Console const     * console,
    ThreadPoolBase    * TP
  );

  ~ProblemStorage();

  void done_setup();
  void done_guess();
  void done_solve();

  integer nnz() const;

  void do_ode( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_bc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_abc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_hc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_fd_BC( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eta( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Hxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JP( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JPxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JU( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JUxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_LT( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_LTargs( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_LTxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_jump( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_lagrange_target( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_mayer_target( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_BC( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_full_bc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_ineq( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Ipost( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Pars( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Post( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Q( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_X( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_active_BC( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_equations( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_nodes( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_segments( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_check_jacobian( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_check_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dims( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DlagrangeDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DmayerDxxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DabcDxlxlpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DhcDxlxlop( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_MU_U_eval_Dxlxlp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_F( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF2_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_MU_U( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_ocp_data( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution_as_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution3( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_guess_MU_U( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_info( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_mesh_functions( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_names( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_node_to_segment( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_nodes( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_pack( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_read( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_remesh( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_set_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_set_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_setup( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_solve( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_unpack( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_update_continuation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_A( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_A_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JPD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JPD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JUD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JUD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2lagrangeD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2lagrangeD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTargsD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTargsD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2mayerD2xxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2mayerD2xxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DbcDxxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DbcDxxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DetaDxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DetaDxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Dfd_BCDxlxlp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Dfd_BCDxlxlp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DgDu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DgDu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DgDxpm( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DgDxpm_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DHxpDxpuv( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DHxpDxpuv_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DjumpDxlxlp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DjumpDxlxlp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTargsDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTargsDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DodeDxpuv( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DodeDxpuv_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

  void read  ( string const & fname, GenericContainer & gc );
  void get   ( char const msg[], mxArray const * prhs, NodeQX & N );
  void get   ( char const msg[], mxArray const * prhs, NodeQXL & N );
  void get_Q ( char const msg[], mxArray const * prhs, Q_const_p_type & Q );
  void get_X ( char const msg[], mxArray const * prhs, X_const_p_type & X );
  void get_L ( char const msg[], mxArray const * prhs, L_const_p_type & L );
  void get_MU( char const msg[], mxArray const * prhs, MU_const_p_type & L );
  void get_U ( char const msg[], mxArray const * prhs, U_const_p_type & U );
  void get_P ( char const msg[], mxArray const * prhs, P_const_p_type & P );
  void get_V ( char const msg[], mxArray const * prhs, V_const_p_type & V );
  void get_OMEGA( char const msg[], mxArray const * prhs, OMEGA_const_p_type & OMEGA );
  void get_OMEGA_full( char const msg[], mxArray const * prhs, OMEGA_full_const_p_type & OMEGA_full );
  void get_ptr( char const msg[], mxArray const * prhs, real_const_ptr & ptr );

  // --------------------------------------------------------------------------

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  void do_u1Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u1Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u1Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u2Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u2Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u2Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u3Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u3Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u3Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u4Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u4Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u4Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u5Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u5Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u5Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u6Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u6Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u6Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u7Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u7Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u7Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u8Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u8Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u8Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u9Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u9Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u9Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u10Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u10Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u10Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u11Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u11Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u11Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u12Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u12Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u12Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u13Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u13Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u13Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u14Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u14Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u14Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u15Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u15Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u15Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u16Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u16Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u16Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u17Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u17Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u17Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u18Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u18Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u18Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u19Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u19Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u19Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u20Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u20Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u20Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx1Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx1Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx1Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy1Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy1Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy1Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx2Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx2Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx2Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy2Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy2Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy2Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx3Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx3Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx3Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy3Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy3Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy3Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx4Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx4Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx4Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy4Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy4Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy4Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx5Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx5Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx5Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy5Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy5Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy5Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx6Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx6Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx6Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy6Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy6Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy6Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx7Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx7Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx7Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy7Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy7Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy7Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx8Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx8Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx8Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy8Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy8Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy8Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx9Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx9Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx9Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy9Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy9Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy9Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx10Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx10Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx10Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy10Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy10Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy10Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx11Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx11Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx11Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy11Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy11Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy11Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx12Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx12Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx12Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy12Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy12Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy12Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx13Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx13Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx13Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy13Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy13Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy13Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx14Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx14Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx14Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy14Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy14Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy14Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx15Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx15Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx15Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy15Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy15Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy15Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx16Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx16Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx16Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy16Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy16Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy16Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx17Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx17Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx17Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy17Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy17Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy17Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx18Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx18Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx18Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy18Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy18Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy18Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx19Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx19Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx19Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy19Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy19Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy19Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx20Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx20Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_xx20Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy20Limitation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy20Limitation_D( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_yy20Limitation_DD( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

};

extern Mechatronix::Console        * pConsole;
extern Mechatronix::ThreadPoolBase * pTP;
