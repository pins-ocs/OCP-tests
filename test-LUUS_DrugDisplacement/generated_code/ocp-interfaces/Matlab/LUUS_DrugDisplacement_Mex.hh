/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Mex.cc                                   |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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

#include "GenericContainerMatlabInterface.hh"
#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"
#include <sstream>

#include <MechatronixCore/Utils_mex.hh>

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace LUUS_DrugDisplacementLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;

#define MODEL_NAME  "LUUS_DrugDisplacement"
#define MODEL_CLASS LUUS_DrugDisplacement

#define CHECK_IN(N) \
  UTILS_MEX_ASSERT( nrhs == N, CMD "Expected {} argument(s), nrhs = {}\n", N, nrhs )

#define CHECK_OUT(N) \
  UTILS_MEX_ASSERT( nlhs == N, CMD "Expected {} argument(s), nlhs = {}\n", N, nlhs )

#define CHECK_IN_OUT(N,M) CHECK_IN(N); CHECK_OUT(M)

#define MEX_CHECK_DIMS(A,B,C,D) \
  UTILS_MEX_ASSERT0( A == C && B == D, CMD "Argument dimensions must be the same\n" )

#define GET_ARG_P(ARG)                                                          \
  mwSize nP;                                                                    \
  string msg_nP = fmt::format( "{} argument pars", CMD );                       \
  P_const_pointer_type P(Utils::mex_vector_pointer( ARG, nP, msg_nP.c_str() )); \
  UTILS_MEX_ASSERT(                                                             \
    nP == this->dim_Pars(),                                                     \
    "{} |pars| = {} expected to be {}\n", CMD, nP, this->dim_Pars()             \
  );

#define GET_ARG_U(ARG)                                                          \
  mwSize nU;                                                                    \
  string msg_nU = fmt::format( "{} argument pars", CMD );                       \
  U_const_pointer_type U(Utils::mex_vector_pointer( ARG, nU, msg_nU.c_str() )); \
  UTILS_MEX_ASSERT(                                                             \
    nU == this->dim_U(),                                                        \
    "{} |U| = {} expected to be {}\n", CMD, nU, this->dim_U()                   \
  );

#define GET_ARG_OMEGA(ARG)                                                              \
  mwSize nO;                                                                            \
  string msg_nO = fmt::format( "{} argument pars", CMD );                               \
  OMEGA_const_pointer_type Omega(Utils::mex_vector_pointer( ARG, nO, msg_nO.c_str() )); \
  UTILS_MEX_ASSERT(                                                                     \
    nO == this->num_active_BC(),                                                        \
    "{} |Omega| = {} expected to be {}\n", CMD, nO, this->num_active_BC()               \
  );

#define GET_ARG_OMEGA_FULL(ARG)                                        \
  mwSize nOmega;                                                       \
  string msg_Omega = fmt::format( "{} argument pars", CMD );           \
  OMEGA_full_const_pointer_type Omega( Utils::mex_vector_pointer(      \
    ARG, nOmega,  msg_Omega.c_str()                                    \
  ));                                                                  \
  UTILS_MEX_ASSERT(                                                    \
    nOmega == this->dim_BC(),                                          \
    "{} |Omega| = {} expected to be {}\n", CMD, nOmega, this->dim_BC() \
  );

#define GET_ARG_V(ARG)                                                          \
  mwSize nV;                                                                    \
  string msg_nV = fmt::format( "{} argument pars", CMD );                       \
  V_const_pointer_type V(Utils::mex_vector_pointer( ARG, nV, msg_nV.c_str() )); \
  UTILS_MEX_ASSERT(                                                             \
    nV == this->dim_X(),                                                        \
    "{} |V| = {} expected to be {}\n", CMD, nV, this->dim_X()                   \
  );

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

  bool setup_ok     = false;
  bool guess_ok     = false;
  bool solve_ok     = false;
  bool solution1_ok = false;
  bool solution2_ok = false;
  bool solution3_ok = false;

  GenericContainer gc_data;
  GenericContainer gc_solution1;
  GenericContainer gc_solution2;
  GenericContainer gc_solution3;

  // user defined Object instances (external)

  MeshStd              mesh;

public:

  using MODEL_CLASS::guess;

  ProblemStorage(
    std::string const & cname,
    integer             n_threads,
    Console const *     console
  );

  ~ProblemStorage();

  void done_setup();
  void done_guess();
  void done_solve();

  integer nnz() const;

  void do_info( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_read( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_setup( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_remesh( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_set_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution_as_guess( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_solve( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dims( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Q( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_X( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Pars( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_BC( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Post( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_Ipost( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_full_bc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_dim_ineq( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_active_BC( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_nodes( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_equations( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_num_segments( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_names( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_update_continuation( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_set_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_check_raw_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_check_jacobian( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_solution3( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_get_ocp_data( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_init_U( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_U( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_F( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eval_JF_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_pack( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_pack_for_direct( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_unpack( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_unpack_for_direct( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_estimate_multipliers( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_ac( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_hc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_u( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_rhs_ode( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_eta( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_nu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Hxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Hu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_LT( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JP( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_JU( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_LTargs( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_bc( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_jump( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_lagrange_target( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DlagrangeDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_mayer_target( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DmayerDxxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_fd_ode( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_mesh_functions( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_nodes( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_node_to_segment( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DacDxlxlpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DhcDxlxlop( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DuDxlxlp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

  void do_Drhs_odeDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Drhs_odeDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_A( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_A_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DetaDxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DetaDxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DnuDxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DnuDxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DHxpDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DHxpDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTargsDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTargsDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DJPDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DJPDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DLTDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DJUDxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DJUDxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTargsD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTargsD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JPD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JPD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2LTD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JUD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2JUD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DbcDxxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DbcDxxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2bcD2xxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2bcD2xxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DjumpDxlxlp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_DjumpDxlxlp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2lagrangeD2xpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2lagrangeD2xpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2mayerD2xxp( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2mayerD2xxp_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Dfd_odeDxxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_Dfd_odeDxxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2fd_odeD2xxpu( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_D2fd_odeD2xxpu_pattern( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

  void read( string const & fname, GenericContainer & gc );

  // --------------------------------------------------------------------------

  void
  get_LR2(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType2     & L,
    NodeType2     & R
  );

  // --------------------------------------------------------------------------

  void
  get_N(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType2     & N
  );

  // --------------------------------------------------------------------------

  void
  get_qx(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType      & N
  );

  // --------------------------------------------------------------------------

  void
  get_LR(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType      & L,
    NodeType      & R
  );

  // --------------------------------------------------------------------------

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  void do_g2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g2_D_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g2_D_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g2_D_1_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g2_D_1_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g2_D_2_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3_D_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3_D_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3_D_1_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3_D_1_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g3_D_2_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4_D_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4_D_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4_D_1_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4_D_1_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g4_D_2_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1_D_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1_D_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1_D_1_1( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1_D_1_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );
  void do_g1_D_2_2( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );

};

