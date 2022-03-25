/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Mex.cc                                        |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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
#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"
#include <sstream>

#include <MechatronixCore/Utils_mex.hh>
#include <MechatronixCore/Utils/mex_workaround.hxx>

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace gtocX_2burn_parsLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;


static char const help_msg[] =
"%===========================================================================%\n"
"Mex command has the following possible calls:\n"
"gtocX_2burn_pars_Mex('command', arguments ):\n"
"%===========================================================================%\n"
;

#define MODEL_NAME  "gtocX_2burn_pars"
#define MODEL_CLASS gtocX_2burn_pars

#define CHECK_IN(N) \
  UTILS_MEX_ASSERT( nrhs == N, CMD "Expected {} argument(s), nrhs = {}\n", N, nrhs )

#define CHECK_OUT(N) \
  UTILS_MEX_ASSERT( nlhs == N, CMD "Expected {} argument(s), nlhs = {}\n", N, nlhs )

#define CHECK_IN_OUT(N,M) CHECK_IN(N); CHECK_OUT(M)

#define MEX_CHECK_DIMS(A,B,C,D) \
  UTILS_MEX_ASSERT0( A == C && B == D, CMD "Argument dimensions must be the same\n" )

#define GET_ARG_P(ARG)                                              \
  mwSize nP;                                                        \
  string msg_nP = fmt::format( "{} argument pars", CMD );           \
  P_const_pointer_type P(Utils::mex_vector_pointer(                 \
    ARG, nP, msg_nP.c_str()                                         \
  ));                                                               \
  UTILS_MEX_ASSERT(                                                 \
    nP == this->dim_Pars(),                                         \
    "{} |pars| = {} expected to be {}\n", CMD, nP, this->dim_Pars() \
  );

#define GET_ARG_U(ARG)                                         \
  mwSize nU;                                                   \
  string msg_nU = fmt::format( "{} argument pars", CMD );      \
  U_const_pointer_type U(Utils::mex_vector_pointer(            \
    ARG, nU, msg_nU.c_str()                                    \
  ));                                                          \
  UTILS_MEX_ASSERT(                                            \
    nU == this->dim_U(),                                       \
    "{} |U| = {} expected to be {}\n", CMD, nU, this->dim_U()  \
  );

#define GET_ARG_OMEGA(ARG)                                            \
  mwSize nO;                                                          \
  string msg_nO = fmt::format( "{} argument pars", CMD );             \
  OMEGA_const_pointer_type Omega(Utils::mex_vector_pointer(           \
    ARG, nO, msg_nO.c_str()                                           \
  ));                                                                 \
  UTILS_MEX_ASSERT(                                                   \
    nO == this->dim_Omega(),                                          \
    "{} |Omega| = {} expected to be {}\n", CMD, nO, this->dim_Omega() \
  );

#define GET_ARG_OMEGA_FULL(ARG)                                             \
  mwSize nOmega;                                                            \
  string msg_Omega = fmt::format( "{} argument pars", CMD );                \
  OMEGA_full_const_pointer_type Omega( Utils::mex_vector_pointer(           \
    ARG, nOmega,  msg_Omega.c_str()                                         \
  ));                                                                       \
  UTILS_MEX_ASSERT(                                                         \
    nOmega == this->dim_full_BC(),                                          \
    "{} |Omega| = {} expected to be {}\n", CMD, nOmega, this->dim_full_BC() \
  );

#define GET_ARG_V(ARG)                                         \
  mwSize nV;                                                   \
  string msg_nV = fmt::format( "{} argument pars", CMD );      \
  V_const_pointer_type V(Utils::mex_vector_pointer(            \
    ARG, nV, msg_nV.c_str()                                    \
  ));                                                          \
  UTILS_MEX_ASSERT(                                            \
    nV == this->dim_X(),                                       \
    "{} |V| = {} expected to be {}\n", CMD, nV, this->dim_X()  \
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

  bool setup_ok;
  bool guess_ok;
  bool solve_ok;
  bool solution1_ok;
  bool solution2_ok;
  bool solution3_ok;

  GenericContainer gc_data;
  GenericContainer gc_solution1;
  GenericContainer gc_solution2;
  GenericContainer gc_solution3;

  // user defined Object instances (external)

  MeshStd              mesh;

public:

  using MODEL_CLASS::guess;

  ProblemStorage( std::string const & cname, integer n_threads, Console const * console )
  : MODEL_CLASS(cname,n_threads,console)
  , setup_ok(false)
  , guess_ok(false)
  , solve_ok(false)
  , solution1_ok(false)
  , solution2_ok(false)
  , solution3_ok(false)
  // user defined Object instances (external)

  , mesh( "mesh" )
  {}

  ~ProblemStorage() {}

  void
  done_setup() {
    setup_ok     = true;
    guess_ok     = false;
    solve_ok     = false;
    solution1_ok = false;
    solution2_ok = false;
    solution3_ok = false;
  }

  void
  done_guess() {
    setup_ok     = true;
    guess_ok     = true;
    solve_ok     = false;
    solution1_ok = false;
    solution2_ok = false;
    solution3_ok = false;
  }

  void
  done_solve() {
    setup_ok     = true;
    guess_ok     = true;
    solve_ok     = true;
    solution1_ok = false;
    solution2_ok = false;
    solution3_ok = false;
  }

  integer nnz() const { return MODEL_CLASS::eval_JF_nnz(); }

  void
  read( string const & fname, GenericContainer & gc ) {
    UTILS_MEX_ASSERT(
      Utils::check_if_file_exists( fname.c_str() ),
      "Cant find: ``{}''\n", fname
    );
    // redirect output
    Mechatronix::STDOUT_redirect rd;
    rd.start();
    Mechatronix::load_script( fname, gc );
    rd.stop();
    if ( rd.str().length() > 0 )
      mexPrintf( "Mechatronix::load_script return:\n%s\n", rd.str().c_str() );
  }

  /*\
   |                          _
   |  _ __  _____ __  ___ ___| |_ _  _ _ __
   | | '  \/ -_) \ / (_-</ -_)  _| || | '_ \
   | |_|_|_\___/_\_\_/__/\___|\__|\_,_| .__/
   |              |___|               |_|
  \*/
  void
  do_read(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('read',obj,filename): "
    CHECK_IN_OUT(3,1);
    UTILS_MEX_ASSERT(
      mxIsChar(arg_in_2),
      CMD "filename must be a string, found ``{}''\n", mxGetClassName( arg_in_2 )
    );
    string fname = mxArrayToString(arg_in_2);
    GenericContainer gc;
    this->read( fname, gc );
    GenericContainer_to_mxArray( gc, arg_out_0 );
    #undef CMD
  }

  /*\
   |                          _
   |  _ __  _____ __  ___ ___| |_ _  _ _ __
   | | '  \/ -_) \ / (_-</ -_)  _| || | '_ \
   | |_|_|_\___/_\_\_/__/\___|\__|\_,_| .__/
   |              |___|               |_|
  \*/
  void
  do_setup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('setup',obj,struct_or_filename): "
    CHECK_IN_OUT(3,0);
    gc_data.clear(); // clear data for rewrite it
    if ( mxIsStruct(arg_in_2) ) { // read from file
      mxArray_to_GenericContainer( arg_in_2, gc_data );
    } else if ( mxIsChar(arg_in_2) ) {
      string fname = mxArrayToString(arg_in_2);
      this->read( fname, gc_data );
    } else { // setup using MATLAB structure
      UTILS_MEX_ASSERT(
        "{} 3rd argument must be a struct or a string, found: ``{}''\n",
        MODEL_NAME, mxGetClassName(arg_in_2)
      );
    }

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_MEX_ASSERT0(
      gc_data.exists("Mesh"),
      "missing key: ``Mesh'' in gc_data\n"
    );
    mesh.setup( gc_data("Mesh") );
    ptrs[ "pMesh" ] = &mesh;

    // setup model
    MODEL_CLASS::setup( gc_data );

    this->done_setup();

    #undef CMD
  }

  /*\
   |                               _
   |  _ __  _____ __  _ __  ___ __| |_
   | | '  \/ -_) \ / | '  \/ -_|_-< ' \
   | |_|_|_\___/_\_\_|_|_|_\___/__/_||_|
   |              |___|
  \*/
  void
  do_remesh(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('remesh',obj,new_mesh): "
    UTILS_MEX_ASSERT0(
      setup_ok,
      CMD "use 'setup' before to use 'remesh'"
    );
    UTILS_MEX_ASSERT(
      nrhs == 3,
      CMD " Expected 2 or 3 input argument(s), nrhs = {}\n", nrhs
    );
    CHECK_OUT( 0 );

    GenericContainer & gc_mesh = gc_data["Mesh"];
    GenericContainer & ptrs    = gc_data["Pointers"];
    MeshStd * pMesh = ptrs("pMesh").get_pointer<MeshStd*>();

    // Erase old guess
    gc_mesh.erase("initialize");
    gc_mesh.erase("guess_type");
    gc_mesh.erase("spline_set");
    gc_mesh.erase("omega");
    gc_mesh.erase("pars");
    gc_mesh.erase("initialize_controls");
    gc_mesh.erase("initialize_multipliers");

    // overwrite guess
    mxArray_to_GenericContainer( arg_in_2, gc_mesh );

    pMesh->setup( gc_mesh );

    MODEL_CLASS::setup( gc_data );
    this->done_setup();
    #undef CMD
  }

  /*\
   |  _ __  _____ __   __ _ _  _ ___ ______
   | | '  \/ -_) \ /  / _` | || / -_|_-<_-<
   | |_|_|_\___/_\_\__\__, |\_,_\___/__/__/
   |              |___|___/
  \*/
  void
  do_set_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('set_guess',obj[,userguess]): "
    UTILS_MEX_ASSERT0(
      setup_ok,
      CMD "use 'setup' before to use 'set_guess'"
    );
    UTILS_MEX_ASSERT(
      nrhs == 2 || nrhs == 3,
      CMD "Expected 2 or 3 input argument(s), nrhs = {}\n", nrhs
    );
    CHECK_OUT( 0 );
    try {
      GenericContainer & gc_guess = gc_data["Guess"];
      gc_guess.clear();
      if ( nrhs == 2 ) {
        // inizializza guess di default
        gc_guess["initialize"]             = "zero";
        gc_guess["guess_type"]             = "default";
        gc_guess["initialize_multipliers"] = false;
        gc_guess["initialize_controls"]    = "use_guess";
      } else {
        // sovrascrive guess nei dati del problema
        mxArray_to_GenericContainer( arg_in_2, gc_guess );
      }
      MODEL_CLASS::guess( gc_guess );
      this->done_guess();
    }
    catch ( std::exception const & exc ) {
      mexErrMsgTxt(
        fmt::format(
          "gtocX_2burn_pars_Mex('set_guess',...), error: {}",
          exc.what()
        ).c_str()
      );
    }
    catch (...) {
      mexErrMsgTxt( "gtocX_2burn_pars_Mex('set_guess',...), Unknown error\n" );
    }
    #undef CMD
  }

  void
  do_get_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_guess',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'guess'" );
    CHECK_IN_OUT(2,1);
    GenericContainer_to_mxArray( gc_data("Guess"), arg_out_0 );
    #undef CMD
  }

  void
  do_get_solution_as_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_solution_as_guess',obj): "
    UTILS_MEX_ASSERT0(
      setup_ok,
      CMD "use 'setup' before to use 'get_solution_as_guess'"
    );
    CHECK_IN_OUT( 2, 1 );
    GenericContainer gc;
    this->get_solution_as_guess( gc );
    GenericContainer_to_mxArray( gc, arg_out_0 );
    #undef CMD
  }

  /*\
   |                           _
   |   _ __  _____ __  ___ ___| |_ _____
   |  | '  \/ -_) \ / (_-</ _ \ \ V / -_)
   |  |_|_|_\___/_\_\_/__/\___/_|\_/\___|
   |               |___|
  \*/
  void
  do_solve(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('solve',obj[,timeout]): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'solve'"
    );
    UTILS_MEX_ASSERT(
      nrhs == 2 || nrhs == 3,
      CMD "Expected 2 or 3 argument(s), nrhs = {}", nrhs
    );
    CHECK_OUT( 1 );
    if ( nrhs == 3 ) {
      real_type ms = Utils::mex_get_scalar_value( arg_in_2, CMD " timeout" );
      MODEL_CLASS::set_timeout_ms( ms );
    }
    solve_ok = MODEL_CLASS::solve();
    Utils::mex_set_scalar_bool( arg_out_0, solve_ok );
    this->done_solve();
    #undef CMD
  }

  /*\
   |                     _ _
   |  _ __  _____ __  __| (_)_ __  ___
   | | '  \/ -_) \ / / _` | | '  \(_-<
   | |_|_|_\___/_\_\_\__,_|_|_|_|_/__/
   |              |___|
  \*/
  void
  do_dims(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('dims',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dims'" );
    CHECK_IN_OUT( 2, 1 );
    GenericContainer gc;
    gc["dim_q"]       = MODEL_CLASS::dim_Q();
    gc["dim_x"]       = MODEL_CLASS::dim_X();
    gc["dim_u"]       = MODEL_CLASS::dim_U();
    gc["dim_pars"]    = MODEL_CLASS::dim_Pars();
    gc["dim_omega"]   = MODEL_CLASS::dim_Omega();
    gc["dim_bc"]      = MODEL_CLASS::dim_BC();
    gc["dim_full_bc"] = MODEL_CLASS::dim_full_BC();
    gc["num_nodes"]   = MODEL_CLASS::num_nodes();
    gc["neq"]         = MODEL_CLASS::num_equations();
    GenericContainer_to_mxArray( gc, arg_out_0 );
    #undef CMD
  }

  /*\
   |  _ __  _____ __  _ _  __ _ _ __  ___ ___
   | | '  \/ -_) \ / | ' \/ _` | '  \/ -_|_-<
   | |_|_|_\___/_\_\_|_||_\__,_|_|_|_\___/__/
   |              |___|
  \*/
  void
  do_names(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('names',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'names'" );
    CHECK_IN_OUT( 2, 1 );
    GenericContainer gc;
    this->get_names( gc );
    GenericContainer_to_mxArray( gc, arg_out_0 );
    #undef CMD
  }

  /*\
   |                               _      _        ___         _   _               _   _
   |  _ __  _____ __ _  _ _ __  __| |__ _| |_ ___ / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | '  \/ -_) \ /| || | '_ \/ _` / _` |  _/ -_) (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   | |_|_|_\___/_\_\_\_,_| .__/\__,_\__,_|\__\___|\___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
   |              |___|  |_|
  \*/
  void
  do_update_continuation(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('update_continuation',obj,nphase,old_s,s): "
    UTILS_MEX_ASSERT0(
      setup_ok,
      CMD "use 'setup' before to use 'update_continuation'"
    );
    CHECK_IN_OUT( 5, 0 );
    int64_t nphase  = Utils::mex_get_int64( arg_in_2, CMD " nphase number" );
    real_type old_s = Utils::mex_get_scalar_value( arg_in_3, CMD " old_s" );
    real_type s     = Utils::mex_get_scalar_value( arg_in_4, CMD " s" );
    this->update_continuation( nphase, old_s, s );
    #undef CMD
  }

  /*\
   |                            _                              _      _   _
   |  _ __  _____ __   __ _ ___| |_   _ _ __ ___ __ __ ___ ___| |_  _| |_(_)___ _ _
   | | '  \/ -_) \ /  / _` / -_)  _| | '_/ _` \ V  V /(_-</ _ \ | || |  _| / _ \ ' \
   | |_|_|_\___/_\_\__\__, \___|\__|_|_| \__,_|\_/\_/_/__/\___/_|\_,_|\__|_\___/_||_|
   |              |___|___/       |___|            |___|
  \*/
  void
  do_get_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_raw_solution',obj): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'get_raw_solution'"
    );
    CHECK_IN_OUT( 2, 2 );
    real_ptr x = Utils::mex_create_matrix_value( arg_out_0, this->num_equations(), 1 );
    real_ptr u = Utils::mex_create_matrix_value( arg_out_1, this->num_parameters(), 1 );
    this->get_raw_solution( x, u );
    #undef CMD
  }

  /*\
   |                          _                              _      _   _
   |  _ __  _____ __  ___ ___| |_   _ _ __ ___ __ __ ___ ___| |_  _| |_(_)___ _ _
   | | '  \/ -_) \ / (_-</ -_)  _| | '_/ _` \ V  V /(_-</ _ \ | || |  _| / _ \ ' \
   | |_|_|_\___/_\_\_/__/\___|\__|_|_| \__,_|\_/\_/_/__/\___/_|\_,_|\__|_\___/_||_|
   |              |___|         |___|            |___|
  \*/
  void
  do_set_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('set_raw_solution',obj,x,u): "
    UTILS_MEX_ASSERT0(
      setup_ok,
      CMD "use 'setup' before to use 'set_raw_solution'"
    );
    CHECK_IN_OUT( 4, 0 );
    mwSize dimx,dimu;
    real_const_ptr x = Utils::mex_vector_pointer( arg_in_2, dimx, CMD "argument x");
    real_const_ptr u = Utils::mex_vector_pointer( arg_in_3, dimu, CMD "argument u");
    mwSize neq = this->num_equations();
    UTILS_MEX_ASSERT(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    mwSize npar = this->num_parameters();
    UTILS_MEX_ASSERT(
      dimu == npar,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimu, npar
    );
    this->set_raw_solution( x, u );
    this->done_guess(); // is equivalent to set guess
    #undef CMD
  }

  /*\
   |                     _           _                              _      _   _
   |  _ __  _____ __  __| |_  ___ __| |__  _ _ __ ___ __ __ ___ ___| |_  _| |_(_)___ _ _
   | | '  \/ -_) \ / / _| ' \/ -_) _| / / | '_/ _` \ V  V /(_-</ _ \ | || |  _| / _ \ ' \
   | |_|_|_\___/_\_\_\__|_||_\___\__|_\_\_|_| \__,_|\_/\_/_/__/\___/_|\_,_|\__|_\___/_||_|
   |              |___|                |___|            |___|
  \*/
  void
  do_check_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('check_raw_solution',obj,x): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'check_raw_solution'"
    );
    CHECK_IN_OUT( 3, 1 );
    mwSize dimx, dimp;
    real_const_ptr x = Utils::mex_vector_pointer( arg_in_2, dimx, CMD "argument x" );
    mwSize neq = this->num_equations();
    UTILS_MEX_ASSERT(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    Utils::mex_set_scalar_bool( arg_out_0, this->check_raw_solution(x) );
    #undef CMD
  }

  /*\
   |                     _           _        _             _    _
   |  _ __  _____ __  __| |_  ___ __| |__    (_)__ _ __ ___| |__(_)__ _ _ _
   | | '  \/ -_) \ / / _| ' \/ -_) _| / /    | / _` / _/ _ \ '_ \ / _` | ' \
   | |_|_|_\___/_\_\_\__|_||_\___\__|_\_\__ _/ \__,_\__\___/_.__/_\__,_|_||_|
   |              |___|                |___|__/
  \*/
  void
  do_check_jacobian(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('check_jacobian',obj,x,u,epsi): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'check_jacobian'"
    );
    CHECK_IN_OUT( 5, 0 );
    mwSize dimx,dimu;
    real_const_ptr x = Utils::mex_vector_pointer( arg_in_2, dimx, CMD "argument x" );
    real_const_ptr u = Utils::mex_vector_pointer( arg_in_3, dimx, CMD "argument u" );
    real_type epsi = Utils::mex_get_scalar_value( arg_in_4, CMD "argument epsi" );
    mwSize neq = this->num_equations();
    UTILS_MEX_ASSERT(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    mwSize npar = this->num_parameters();
    UTILS_MEX_ASSERT(
      dimu == npar,
      CMD " size(x) = {} must be equal to npars = {}\n",
      dimu, npar
    );
    this->check_jacobian(x,u,epsi);
    #undef CMD
  }

  /*\
   |                            _             _      _   _
   |  _ __  _____ __   __ _ ___| |_   ___ ___| |_  _| |_(_)___ _ _
   | | '  \/ -_) \ /  / _` / -_)  _| (_-</ _ \ | || |  _| / _ \ ' \
   | |_|_|_\___/_\_\__\__, \___|\__|_/__/\___/_|\_,_|\__|_\___/_||_|
   |              |___|___/       |___|
  \*/
  void
  do_get_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_solution',obj[,column_name]): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'get_solution'"
    );
    CHECK_OUT( 1 );
    if ( !solution1_ok ) {
      MODEL_CLASS::get_solution( gc_solution1 );
      MODEL_CLASS::diagnostic( gc_data, gc_solution1 );
      solution1_ok = true;
    }
    if ( nrhs == 2 ) {
      GenericContainer_to_mxArray( gc_solution1, arg_out_0 );
    } else if ( nrhs == 3 ) {
      UTILS_MEX_ASSERT0(
        mxIsChar(arg_in_2),
        CMD " Third argument must be a string"
      );
      string const & cname = mxArrayToString(arg_in_2);
      GenericContainer const & idx = gc_solution1("idx");
      UTILS_MEX_ASSERT(
        idx.exists(cname),
        CMD "data column `{}` do not exists", cname
      );
      integer icol = idx(cname).get_as_int();
      GenericContainer::mat_real_type const & data = gc_solution1("data").get_mat_real();
      real_ptr res = Utils::mex_create_matrix_value( arg_out_0, data.numRows(), 1 );
      data.getColumn( icol, res );
    } else {
      UTILS_MEX_ASSERT( "{} use 2 or 3 arguments, nrhs = {}\n", CMD, nrhs );
    }
    #undef CMD
  }

  void
  do_get_solution2(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_solution2',obj): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'get_solution2'"
    );
    CHECK_IN_OUT( 2, 1 );
    if ( !solution2_ok ) {
      MODEL_CLASS::get_solution2( gc_solution2 );
      MODEL_CLASS::diagnostic( gc_data, gc_solution2 );
      solution2_ok = true;
    }
    GenericContainer_to_mxArray( gc_solution2, arg_out_0 );
    #undef CMD
  }

  void
  do_get_solution3(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_solution3',obj): "
    UTILS_MEX_ASSERT0(
      guess_ok,
      CMD "use 'set_guess' before to use 'get_solution3'"
    );
    CHECK_IN_OUT( 2, 1 );
    if ( !solution3_ok ) {
      MODEL_CLASS::get_solution3( gc_solution3 );
      MODEL_CLASS::diagnostic( gc_data, gc_solution3 );
      solution3_ok = true;
    }
    GenericContainer_to_mxArray( gc_solution3, arg_out_0 );
    #undef CMD
  }

  /*\
   |                            _                       _      _
   |  _ __  _____ __   __ _ ___| |_   ___  __ _ __   __| |__ _| |_ __ _
   | | '  \/ -_) \ /  / _` / -_)  _| / _ \/ _| '_ \ / _` / _` |  _/ _` |
   | |_|_|_\___/_\_\__\__, \___|\__|_\___/\__| .__/_\__,_\__,_|\__\__,_|
   |              |___|___/       |___|      |_| |___|
  \*/
  void
  do_get_ocp_data(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('get_ocp_data',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'get_ocp_data'" );
    CHECK_IN_OUT( 2, 1 );
    GenericContainer_to_mxArray( gc_data, arg_out_0 );
    #undef CMD
  }

  /*\
   |                           _       _ _
   |   _ __ ___   _____  __   (_)_ __ (_) |_    _   _
   |  | '_ ` _ \ / _ \ \/ /   | | '_ \| | __|  | | | |
   |  | | | | | |  __/>  <    | | | | | | |_   | |_| |
   |  |_| |_| |_|\___/_/\_\___|_|_| |_|_|\__|___\__,_|
   |                     |_____|           |_____|
  \*/

  void
  do_init_U(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('init_U',obj,x,do_minimize): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'init_U'" );
    CHECK_IN_OUT( 4, 1 );
    mwSize dimx;
    real_const_ptr x = Utils::mex_vector_pointer( arg_in_2, dimx, CMD );
    mwSize neq = this->num_equations();
    UTILS_MEX_ASSERT(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    bool do_minimize = Utils::mex_get_bool( arg_in_3, CMD );
    real_ptr u = Utils::mex_create_matrix_value( arg_out_0, this->num_parameters(), 1 );
    MODEL_CLASS::UC_initialize( x, u, do_minimize );
    #undef CMD
  }

  /*\
   |                                          _
   |   _ __ ___   _____  __    _____   ____ _| |   _   _
   |  | '_ ` _ \ / _ \ \/ /   / _ \ \ / / _` | |  | | | |
   |  | | | | | |  __/>  <   |  __/\ V / (_| | |  | |_| |
   |  |_| |_| |_|\___/_/\_\___\___| \_/ \__,_|_|___\__,_|
   |                     |_____|              |_____|
  \*/

  void
  do_eval_U(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_U',obj,Z,u_guess): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'eval_U'" );
    CHECK_IN_OUT( 4, 1 );
    mwSize dimZ, dimU;
    real_const_ptr Z = Utils::mex_vector_pointer( arg_in_2, dimZ, CMD );
    mwSize neq = this->num_equations();
    UTILS_MEX_ASSERT(
      dimZ == neq,
      CMD " size(Z) = {} must be equal to neq = {}\n",
      dimZ, neq
    );
    real_const_ptr u_guess = Utils::mex_vector_pointer( arg_in_3, dimU, CMD );
    mwSize nU = this->num_parameters();
    UTILS_MEX_ASSERT(
      dimU == nU,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimU, nU
    );
    real_ptr U = Utils::mex_create_matrix_value( arg_out_0, nU, 1 );
    std::copy_n( u_guess, nU, U );
    MODEL_CLASS::UC_eval( Z, U );
    #undef CMD
  }

  /*\
   |                               _   ___
   |  _ __  _____ __  _____ ____ _| | | __|
   | | '  \/ -_) \ / / -_) V / _` | | | _|
   | |_|_|_\___/_\_\_\___|\_/\__,_|_|_|_|
   |              |___|            |___|
  \*/
  void
  do_eval_F(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_F',obj,Z,U): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'eval_F'" );
    CHECK_IN_OUT( 4, 2 );
    mwSize dimZ, dimU;
    real_const_ptr Z = Utils::mex_vector_pointer( arg_in_2, dimZ, CMD );
    real_const_ptr U = Utils::mex_vector_pointer( arg_in_3, dimU, CMD );
    mwSize neq  = this->num_equations();
    mwSize npar = this->num_parameters();
    UTILS_MEX_ASSERT(
      dimZ == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimZ, neq
    );
    UTILS_MEX_ASSERT(
      dimU == npar,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimU, npar
    );
    real_ptr f = Utils::mex_create_matrix_value( arg_out_0, neq, 1 );
    bool ok = true;
    try {
      MODEL_CLASS::eval_F( Z, U, f );
    } catch ( std::exception const & exc ) {
      string msg = fmt::format( "gtocX_2burn_pars_Mex('eval_F',...) error: {}", exc.what() );
      mexWarnMsgTxt( msg.c_str() );
      ok = false;
    } catch ( ... ) {
      mexWarnMsgTxt( "gtocX_2burn_pars_Mex('eval_F',...) unkown error\n" );
      ok = false;
    }
    Utils::mex_set_scalar_bool( arg_out_1, ok );
    #undef CMD
  }

  /*\
   |                               _     _ ___
   |  _ __  _____ __  _____ ____ _| | _ | | __|
   | | '  \/ -_) \ / / -_) V / _` | || || | _|
   | |_|_|_\___/_\_\_\___|\_/\__,_|_|_\__/|_|
   |              |___|            |___|
  \*/
  void
  do_eval_JF(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_JF',obj,Z,U): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'eval_JF'" );
    CHECK_IN_OUT( 4, 2 );
    mwSize dimZ, dimU;
    real_const_ptr Z = Utils::mex_vector_pointer( arg_in_2, dimZ, CMD );
    real_const_ptr U = Utils::mex_vector_pointer( arg_in_3, dimU, CMD );
    mwSize neq  = this->num_equations();
    mwSize npar = this->num_parameters();
    UTILS_MEX_ASSERT(
      dimZ == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimZ, neq
    );
    UTILS_MEX_ASSERT(
      dimU == npar,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimU, npar
    );

    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz() );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz() );
    real_ptr V = Utils::mex_create_matrix_value( args[2], 1, nnz() );
    Utils::mex_set_scalar_value( args[3], neq );
    Utils::mex_set_scalar_value( args[4], neq );

    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz(), "eval_JF" );
    integer_ptr i_row = mem( nnz() );
    integer_ptr j_col = mem( nnz() );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz(); ++i ) {
      I[i] = static_cast<real_type>(i_row[i]);
      J[i] = static_cast<real_type>(j_col[i]);
      UTILS_MEX_ASSERT(
        I[i] > 0 && I[i] <= num_equations() &&
        J[i] > 0 && J[i] <= num_equations(),
        CMD " index I = {} J = {} must be in the range = [1,{}]\n",
        I[i], J[i], num_equations()
      );
    }

    bool ok_value = true;
    try {
      MODEL_CLASS::eval_JF_values( Z, U, V );
    } catch ( std::exception const & exc ) {
      mexWarnMsgTxt( fmt::format( "gtocX_2burn_pars_Mex('eval_JF',...) error: {}", exc.what() ).c_str() );
      ok_value = false;
    } catch ( ... ) {
      mexWarnMsgTxt( "gtocX_2burn_pars_Mex('eval_JF',...) unkown error\n" );
      ok_value = false;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    Utils::mex_set_scalar_bool( arg_out_1, ok_value );
    #undef CMD
  }

  /*\
   |                               _     _ ___             _   _
   |  _ __  _____ __  _____ ____ _| | _ | | __| _ __  __ _| |_| |_ ___ _ _ _ _
   | | '  \/ -_) \ / / -_) V / _` | || || | _| | '_ \/ _` |  _|  _/ -_) '_| ' \
   | |_|_|_\___/_\_\_\___|\_/\__,_|_|_\__/|_|__| .__/\__,_|\__|\__\___|_| |_||_|
   |              |___|            |___|   |___|_|
  \*/
  void
  do_eval_JF_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_JF_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_JF_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz() );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz() );
    Utils::mex_set_scalar_value( args[2], 1 );
    Utils::mex_set_scalar_value( args[3], num_equations() );
    Utils::mex_set_scalar_value( args[4], num_equations() );

    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz(), "eval_JF_pattern" );
    integer_ptr i_row = mem( nnz() );
    integer_ptr j_col = mem( nnz() );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz(); ++i ) {
      I[i] = static_cast<real_type>(i_row[i]);
      J[i] = static_cast<real_type>(j_col[i]);
      UTILS_MEX_ASSERT(
        I[i] > 0 && I[i] <= num_equations() &&
        J[i] > 0 && J[i] <= num_equations(),
        CMD " index I = {} J = {} must be in the range = [1,{}]\n",
        I[i], J[i], num_equations()
      );
    }

    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  /*\
   |                                 _
   |  _ __  _____ __   _ __  __ _ __| |__
   | | '  \/ -_) \ /  | '_ \/ _` / _| / /
   | |_|_|_\___/_\_\__| .__/\__,_\__|_\_\
   |              |___|_|
  \*/
  void
  do_pack(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('pack',obj,x,lambda,pars,omega): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'pack'" );
    CHECK_IN_OUT( 6, 1 );

    mwSize nrX, ncX, nrL, ncL, nP, nO;
    X_const_pointer_type     X(Utils::mex_matrix_pointer( arg_in_2, nrX, ncX, CMD "argument x" ));
    L_const_pointer_type     L(Utils::mex_matrix_pointer( arg_in_3, nrL, ncL, CMD "argument lambda" ));
    P_const_pointer_type     P(Utils::mex_vector_pointer( arg_in_4, nP,       CMD "argument pars" ));
    OMEGA_const_pointer_type O(Utils::mex_vector_pointer( arg_in_5, nO,       CMD "argument omega" ));
    integer nn = this->num_nodes();
    UTILS_ASSERT(
      nrX == mwSize(this->dim_X()) && ncX == nn,
      "{} size(x) = {} x {} expected to be {} x {}\n",
      CMD, nrX, ncX, this->dim_X(), nn
    );
    UTILS_ASSERT(
      nrL == mwSize(this->dim_X()) && ncL == nn,
      "{} size(lambda) = {} x {} expected to be {} x {}\n",
      CMD, nrL, ncL, this->dim_X(), nn
    );
    UTILS_ASSERT(
      nP == mwSize(this->dim_Pars()),
      "{} length(pars) = {} expected to be {}\n",
      CMD, nP, this->dim_Pars()
    );
    UTILS_ASSERT(
      nO == mwSize(this->dim_Omega()),
      "{} length(omega) = {} expected to be {}\n",
      CMD, nO, this->dim_Omega()
    );
    real_ptr Z = Utils::mex_create_matrix_value( arg_out_0, 1, this->num_equations() );
    this->pack( X, L, P, O, Z );
    #undef CMD
  }

  void
  do_pack_for_direct(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('pack_for_direct',obj,X,U,Pars): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'pack_for_direct'" );
    CHECK_IN_OUT( 5, 1 );

    mwSize nrX, ncX, nrU, ncU, nP;
    X_const_pointer_type     X(Utils::mex_matrix_pointer( arg_in_2, nrX, ncX, CMD "argument X" ));
    U_const_pointer_type     U(Utils::mex_matrix_pointer( arg_in_3, nrU, ncU, CMD "argument U" ));
    P_const_pointer_type     P(Utils::mex_vector_pointer( arg_in_4, nP,       CMD "argument Pars" ));
    mwSize nn = mwSize(this->num_nodes());
    UTILS_ASSERT(
      nrX == mwSize(this->dim_X()) && ncX == nn,
      "{} size(X) = {} x {} expected to be {} x {}\n",
      CMD, nrX, ncX, this->dim_X(), nn
    );
    UTILS_ASSERT(
      nrU == mwSize(this->dim_U()) && ncU == nn-1,
      "{} size(U) = {} x {} expected to be {} x {}\n",
      CMD, nrU, ncU, this->dim_U(), nn
    );
    UTILS_ASSERT(
      nP == mwSize(this->dim_Pars()),
      "{} length(pars) = {} expected to be {}\n",
      CMD, nP, this->dim_Pars()
    );
    mwSize dim = nrX*ncX + nrU*ncU + nP;
    real_ptr Z   = Utils::mex_create_matrix_value( arg_out_0, 1, dim );
    this->pack_for_direct( X, U, P, Z );
    #undef CMD
  }

  /*\
   |                                         _
   |  _ __  _____ __ _  _ _ _  _ __  __ _ __| |__
   | | '  \/ -_) \ /| || | ' \| '_ \/ _` / _| / /
   | |_|_|_\___/_\_\_\_,_|_||_| .__/\__,_\__|_\_\
   |              |___|       |_|
  \*/
  void
  do_unpack(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('unpack',obj,Z): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'unpack'" );
    CHECK_IN_OUT( 3, 4 );

    integer nn = this->num_nodes();
    mwSize nZ;
    real_const_ptr Z = Utils::mex_vector_pointer( arg_in_2, nZ, CMD "argument Z" );
    UTILS_ASSERT(
      nZ == mwSize(this->num_equations()),
      "{} length(Z) = {} expected to be {}\n",
      CMD, nZ, this->num_equations()
    );

    X_pointer_type     X(Utils::mex_create_matrix_value( arg_out_0, this->dim_X(), nn ));
    L_pointer_type     L(Utils::mex_create_matrix_value( arg_out_1, this->dim_X(), nn ));
    P_pointer_type     P(Utils::mex_create_matrix_value( arg_out_2, 1, this->dim_Pars() ));
    OMEGA_pointer_type O(Utils::mex_create_matrix_value( arg_out_3, 1, this->dim_Omega() ));

    this->unpack( Z, X, L, P, O );
    #undef CMD
  }

  void
  do_unpack_for_direct(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('unpack_for_direct',obj,Z): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'unpack_for_direct'" );
    CHECK_IN_OUT( 3, 3 );

    mwSize nn   = mwSize( this->num_nodes() );
    mwSize dimZ = this->dim_X()*nn +
                  this->dim_U()*(nn-1) +
                  this->dim_Pars();

    mwSize nZ;
    real_const_ptr Z = Utils::mex_vector_pointer( arg_in_2, nZ, CMD "argument Z" );
    UTILS_ASSERT(
      nZ == dimZ,
      "{} length(Z) = {} expected to be {}\n",
      CMD, nZ, dimZ
    );

    X_pointer_type X(Utils::mex_create_matrix_value( arg_out_0, this->dim_X(), nn ));
    U_pointer_type U(Utils::mex_create_matrix_value( arg_out_1, this->dim_U(), nn-1 ));
    P_pointer_type P(Utils::mex_create_matrix_value( arg_out_2, 1, this->dim_Pars() ));

    this->unpack_for_direct( Z, X, U, P );
    #undef CMD
  }

  /*\
   |          _   _            _                   _ _   _      _
   |   ___ __| |_(_)_ __  __ _| |_ ___   _ __ _  _| | |_(_)_ __| |___ _ _ ___
   |  / -_|_-<  _| | '  \/ _` |  _/ -_) | '  \ || | |  _| | '_ \ / -_) '_(_-<
   |  \___/__/\__|_|_|_|_\__,_|\__\___|_|_|_|_\_,_|_|\__|_| .__/_\___|_| /__/
   |                                 |___|                |_|
  \*/
  void
  do_estimate_multipliers(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('estimate_multipliers', obj, X, U, Pars, method): "
    UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'estimate_multipliers'" );
    CHECK_IN_OUT( 6, 2 );

    mwSize nrX, ncX, nrU, ncU, nP;
    X_const_pointer_type X(Utils::mex_matrix_pointer( arg_in_2, nrX, ncX, CMD "argument X" ));
    U_const_pointer_type U(Utils::mex_matrix_pointer( arg_in_3, nrU, ncU, CMD "argument U" ));
    P_const_pointer_type P(Utils::mex_vector_pointer( arg_in_4, nP,       CMD "argument Pars" ));
    mwSize nn = mwSize(this->num_nodes());
    UTILS_ASSERT(
      nrX == mwSize(this->dim_X()) && ncX == nn,
      "{} size(X) = {} x {} expected to be {} x {}\n",
      CMD, nrX, ncX, this->dim_X(), nn
    );
    UTILS_ASSERT(
      nrU == mwSize(this->dim_U()) && ncU == nn-1,
      "{} size(U) = {} x {} expected to be {} x {}\n",
      CMD, nrU, ncU, this->dim_U(), nn
    );
    UTILS_ASSERT(
      nP == mwSize(this->dim_Pars()),
      "{} length(pars) = {} expected to be {}\n",
      CMD, nP, this->dim_Pars()
    );

    L_pointer_type     L(Utils::mex_create_matrix_value( arg_out_0, this->dim_X(), nn ));
    OMEGA_pointer_type OMEGA(Utils::mex_create_matrix_value( arg_out_1, this->dim_Omega(), 1 ));

    this->estimate_multipliers( X, U, P, L, OMEGA );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  get_LR2(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType2     & L,
    NodeType2     & R
  ) {

    mwSize nQ, nX, nL;

    // -------------------
    L.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} L_segment", msg ) ) );
    UTILS_ASSERT(
      L.i_segment >= 0 && L.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, L.i_segment, this->num_segments()
    );

    // -------------------
    L.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q_L", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    L.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x_L", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    L.lambda = Utils::mex_vector_pointer( arg_in_5, nL, fmt::format( "{} argument lambda_L", msg ) );
    UTILS_ASSERT(
      nL == this->dim_X(),
      "{} |lambda_L| = {} expected to be {}\n",
      msg, nL, this->dim_X()
    );

    // -------------------
    R.i_segment = integer( Utils::mex_get_int64( arg_in_6, fmt::format( "{} R_segment", msg ) ) );
    UTILS_ASSERT(
      R.i_segment >= 0 && R.i_segment < this->num_segments(),
      "{} iseg_R = {} expected to be in [0,{})\n",
      msg, R.i_segment, this->num_segments()
    );

    // -------------------
    R.q = Utils::mex_vector_pointer( arg_in_7, nQ, fmt::format( "{} argument q_R", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_R| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    R.x = Utils::mex_vector_pointer( arg_in_8, nX, fmt::format( "{} argument x_R", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_R| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    R.lambda = Utils::mex_vector_pointer( arg_in_9, nL, fmt::format( "{} argument lambda_R", msg ) );
    UTILS_ASSERT(
      nL == this->dim_X(),
      "{} |lambda_R| = {} expected to be {}\n",
      msg, nL, this->dim_X()
    );
  }

  // --------------------------------------------------------------------------

  void
  get_N(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType2     & N
  ) {

    mwSize nQ, nX, nL;

    // -------------------
    N.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
    UTILS_ASSERT(
      N.i_segment >= 0 && N.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, N.i_segment, this->num_segments()
    );

    // -------------------
    N.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q_M", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    N.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x_M", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    N.lambda = Utils::mex_vector_pointer( arg_in_5, nL, fmt::format( "{} argument lambda_M", msg ) );
    UTILS_ASSERT(
      nL == this->dim_X(),
      "{} |lambda_L| = {} expected to be {}\n",
      msg, nL, this->dim_X()
    );
  }

  /*\
   |   _ __  _____ __  __ _
   |  | '  \/ -_) \ / / _` |
   |  |_|_|_\___/_\_\_\__,_|
   |               |___|
  \*/
  void
  do_ac(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('ac', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_U( arg_in_11 );

    integer n_thread = 0;

    real_ptr a = Utils::mex_create_matrix_value( arg_out_0, 2*this->dim_X(), 1 );
    real_ptr c = Utils::mex_create_matrix_value( arg_out_1, this->dim_Pars(), 1 );

    this->ac_eval( n_thread, L, R, P, U, a, c );

    #undef CMD
  }

  /*\
   |                      _             _    _
   |   _ __  _____ __    (_)__ _ __ ___| |__(_)__ _ _ _    __ _
   |  | '  \/ -_) \ /    | / _` / _/ _ \ '_ \ / _` | ' \  / _` |
   |  |_|_|_\___/_\_\__ _/ \__,_\__\___/_.__/_\__,_|_||_|_\__,_|
   |               |___|__/                            |___|
  \*/
  void
  do_DacDxlxlpu(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('DacDxlxlpu', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

    CHECK_IN_OUT( 12, 4 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_U( arg_in_11 );

    mwSize nXLP;
    real_const_ptr DuDxlxlp_ptr = Utils::mex_matrix_pointer( arg_in_12, nU, nXLP,
      fmt::format( "{} argument DuDxlxlp", CMD )
    );

    integer dim_X = this->dim_X();
    integer dim_U = this->dim_U();
    integer dim_P = this->dim_Pars();

    UTILS_ASSERT(
      nU == dim_U && nXLP == 4*dim_X+dim_P,
      "{} size(DuDxlxlp) = {} x {} expected to be {} x {}\n",
      CMD, nU, nXLP, dim_U, 4*dim_X+dim_P
    );

    integer n_thread = 0;
    integer nCOL     = 4*dim_X+dim_P;
    integer nR       = 2*dim_X;
    real_ptr DaDxlxlp_mem = Utils::mex_create_matrix_value( arg_out_0, nR,    nCOL  );
    real_ptr DaDu_mem     = Utils::mex_create_matrix_value( arg_out_1, nR,    dim_U );
    real_ptr DcDxlxlp_mem = Utils::mex_create_matrix_value( arg_out_2, dim_P, nCOL  );
    real_ptr DcDu_mem     = Utils::mex_create_matrix_value( arg_out_3, dim_P, dim_U );

    MatrixWrapper<real_type> DaDxlxlp( DaDxlxlp_mem, nR,    nCOL,  nR    );
    MatrixWrapper<real_type> DaDu    ( DaDu_mem,     nR,    dim_U, nR    );
    MatrixWrapper<real_type> DcDxlxlp( DcDxlxlp_mem, dim_P, nCOL,  dim_P );
    MatrixWrapper<real_type> DcDu    ( DcDu_mem,     dim_P, dim_U, dim_P );

    this->DacDxlxlp_eval( n_thread, L, R, P, U, DaDxlxlp, DaDu, DcDxlxlp, DcDu );

    #undef CMD
  }

  /*\
   |                   _
   |   _ __  _____ __ | |_  __
   |  | '  \/ -_) \ / | ' \/ _|
   |  |_|_|_\___/_\_\_|_||_\__|
   |               |___|
  \*/
  void
  do_hc(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('hc', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, omega ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA( arg_in_11 );

    real_ptr h = Utils::mex_create_matrix_value( arg_out_0, 2*this->dim_X(), 1 );
    real_ptr c = Utils::mex_create_matrix_value( arg_out_1, this->dim_Pars(), 1 );

    this->hc_eval( L, R, Omega, P, h, c );

    #undef CMD
  }

  /*\
   |                      _             _    _             _
   |   _ __  _____ __    (_)__ _ __ ___| |__(_)__ _ _ _   | |_  __
   |  | '  \/ -_) \ /    | / _` / _/ _ \ '_ \ / _` | ' \  | ' \/ _|
   |  |_|_|_\___/_\_\__ _/ \__,_\__\___/_.__/_\__,_|_||_|_|_||_\__|
   |               |___|__/                            |___|
  \*/
  void
  do_DhcDxlxlop(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('DhcDxlxlop', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, omega ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA( arg_in_11 );

    mwSize nCOL = 4*this->dim_X()+this->dim_Pars();
    mwSize nR   = 2*this->dim_X();
    real_ptr h = Utils::mex_create_matrix_value( arg_out_0, nR, nCOL );
    real_ptr c = Utils::mex_create_matrix_value( arg_out_1, this->dim_Pars(), nCOL );

    MatrixWrapper<real_type> DhDxlop( h, nR, nCOL, nR );
    MatrixWrapper<real_type> DcDxlop( c, this->dim_Pars(), nCOL, this->dim_Pars() );

    this->DhcDxlxlop_eval( L, R, Omega, P, DhDxlop, DcDxlop );

    #undef CMD
  }

  /*\
   |   _   _
   |  | | | |
   |  | |_| |
   |   \___/
  \*/
  void
  do_u(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('u', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ): "

    CHECK_IN_OUT( 11, 1 );

    mwSize nCOL;
    Mechatronix::U_solver & US = this->m_U_control_solver[0];

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );

    U_pointer_type U( Utils::mex_create_matrix_value( arg_out_0, this->dim_U(), 1 ) );
    if ( m_U_solve_iterative ) {
      this->u_guess_eval( L, R, P, U );
      US.eval( m_console, L, R, P, U, U );
    } else {
      this->u_eval_analytic( L, R, P, U );
    }
    #undef CMD
  }
  /*\
   |   ____        ____       _      _
   |  |  _ \ _   _|  _ \__  _| |_  _| |_ __
   |  | | | | | | | | | \ \/ / \ \/ / | '_ \
   |  | |_| | |_| | |_| |>  <| |>  <| | |_) |
   |  |____/ \__,_|____//_/\_\_/_/\_\_| .__/
   |                                  |_|
  \*/
  void
  do_DuDxlxlp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('DuDxlxlp', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

    CHECK_IN_OUT( 11, 1 );

    mwSize nCOL;
    Mechatronix::U_solver & US = this->m_U_control_solver[0];

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_U( arg_in_11 );

    nCOL = 4*this->dim_X() + this->dim_Pars();
    real_ptr DuDxlxlp_ptr = Utils::mex_create_matrix_value( arg_out_0, this->dim_U(), nCOL );

    MatrixWrapper<real_type> DuDxlxlp( DuDxlxlp_ptr, this->dim_U(), nCOL, this->dim_U() );

    if ( m_U_solve_iterative ) {
      US.u_eval_DuDxlxlp( L, R, P, U, DuDxlxlp );
    } else {
      this->DuDxlxlp_full_analytic( L, R, P, U, DuDxlxlp );
    }

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  get_qx(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType      & N
  ) {

    mwSize nQ, nX;

    // -------------------
    N.i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
    UTILS_ASSERT(
      N.i_segment >= 0 && N.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, N.i_segment, this->num_segments()
    );

    // -------------------
    N.q = Utils::mex_vector_pointer( arg_in_3, nQ, fmt::format( "{} argument q", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    N.x = Utils::mex_vector_pointer( arg_in_4, nX, fmt::format( "{} argument x", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );
  }

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/
  void
  do_rhs_ode(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('rhs_ode', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->rhs_ode_numEqns(), 1 );
    this->rhs_ode_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_Drhs_odeDxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('Drhs_odeDxup', i_seg, obj, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( Drhs_odeDxup, N, U, P );
    #undef CMD
  }

  /*\
   |     _
   |    /_\
   |   / _ \
   |  /_/ \_\
  \*/

  void
  do_A(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('A', obj, i_seg, q, x, pars ): "

    CHECK_IN_OUT( 6, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_5 );

    RETURN_SPARSE( A, N, P );

    #undef CMD
  }

  /*\
   |       _
   |   ___| |_ __ _
   |  / -_)  _/ _` |
   |  \___|\__\__,_|
  \*/

  void
  do_eta(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eta', obj, i_seg, q, x, lambda, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->eta_numEqns(), 1 );
    this->eta_eval( N, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DetaDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DetaDxp', obj, i_seg, q, x, lambda, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DetaDxp, N, P );

    #undef CMD
  }

  /*\
   |   _ _ _  _
   |  | ' \ || |
   |  |_||_\_,_|
  \*/

  void
  do_nu(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('nu', obj, i_seg, q, x, V, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->nu_numEqns(), 1 );
    this->nu_eval( N, V, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DnuDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DnuDxp', obj, i_seg, q, x, V, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DnuDxp, N, V, P );

    #undef CMD
  }

  /*\
   |     _      _  _     _     _
   |    /_\  __| |(_)___(_)_ _| |_
   |   / _ \/ _` || / _ \ | ' \  _|
   |  /_/ \_\__,_|/ \___/_|_||_\__|
   |            |__/
  \*/
  /*\
   |   _  _
   |  | || |_ __
   |  | __ \ \ /
   |  |_||_/_\_\
  \*/

  void
  do_Hx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('Hx', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->Hx_numEqns(), 1 );
    this->Hx_eval( N, V, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHxDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DHxDxp', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DHxDxp, N, V, U, P );

    #undef CMD
  }

  /*\
   |   _  _
   |  | || |_  _
   |  | __ | || |
   |  |_||_|\_,_|
  \*/

  void
  do_Hu(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('Hu', obj, i_seg, q, x, lambda, u, pars ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_6 );
    GET_ARG_P( arg_in_7 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->Hu_numEqns(), 1 );
    this->Hu_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHuDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DHuDxp', obj, i_seg, q, x, lambda, u, pars ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_6 );
    GET_ARG_P( arg_in_7 );

    RETURN_SPARSE( DHuDxp, N, U, P );

    #undef CMD
  }

  /*\
   |   _  _
   |  | || |_ __
   |  | __ | '_ \
   |  |_||_| .__/
   |       |_|
  \*/

  void
  do_Hp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('Hp', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->Hp_numEqns(), 1 );
    this->Hp_eval( N, V, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHpDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DHpDp', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DHpDp, N, V, U, P );

    #undef CMD
  }

  /*\
   |       _ ____        _ _   _
   |      | |  _ \      | | | | |
   |   _  | | |_) |  _  | | | | |
   |  | |_| |  __/  | |_| | |_| |
   |   \___/|_|      \___/ \___/
  \*/

  void
  do_JPx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JPx', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JPx_numEqns(), 1 );
    this->JPx_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_LTx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('LTx', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->LTx_numEqns(), 1 );
    this->LTx_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_JUx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JUx', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JUx_numEqns(), 1 );
    this->JUx_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_JPp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JPp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JPp_numEqns(), 1 );
    this->JPp_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_LTp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('LTp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->LTp_numEqns(), 1 );
    this->LTp_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_JUp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JUp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JUp_numEqns(), 1 );
    this->JUp_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_LTargs(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('LTargs', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );
    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->LTargs_numEqns(), 1 );
    this->LTargs_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------


  // --------------------------------------------------------------------------

  void
  do_DJPxDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJPxDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJPxDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DLTxDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DLTxDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DLTxDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DJUxDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJUxDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJUxDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DJPuDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJPuDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJPuDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DLTuDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DLTuDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DLTuDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DJUuDxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJUuDxp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJUuDxp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DJPpDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJPpDp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJPpDp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DLTpDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DLTpDp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DLTpDp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DJUpDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DJUpDp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DJUpDp, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DLTargsDxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DLTargsDxup', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DLTargsDxup, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------


  void
  do_D2LTargsD2xup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('D2LTargsD2xup', obj, i_seg, q, x, u, pars, omega ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    mwSize nO;
    real_const_ptr OMEGA = Utils::mex_vector_pointer(
      arg_in_7, nO, CMD " argument omega"
    );

    RETURN_SPARSE( D2LTargsD2xup, N, U, P, OMEGA );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  /*\
   |   _                      _                                _ _ _   _
   |  | |__  ___ _  _ _ _  __| |__ _ _ _ _  _   __ ___ _ _  __| (_) |_(_)___ _ _  ___
   |  | '_ \/ _ \ || | ' \/ _` / _` | '_| || | / _/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |  |_.__/\___/\_,_|_||_\__,_\__,_|_|  \_, |_\__\___/_||_\__,_|_|\__|_\___/_||_/__/
   |                                     |__/___|
  \*/

  // --------------------------------------------------------------------------

  void
  get_LR(
    char const      msg[],
    int             nrhs,
    mxArray const * prhs[],
    NodeType      & L,
    NodeType      & R
  ) {

    string msg_str;
    mwSize nQ, nX, nL;

    // -------------------
    msg_str = fmt::format( "{} L_segment", msg );
    L.i_segment = integer( Utils::mex_get_int64( arg_in_2, msg_str.c_str() ) );
    UTILS_ASSERT(
      L.i_segment >= 0 && L.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, L.i_segment, this->num_segments()
    );

    // -------------------
    msg_str = fmt::format( "{} argument q_L", msg );
    L.q = Utils::mex_vector_pointer( arg_in_3, nQ, msg_str.c_str() );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    msg_str = fmt::format( "{} argument x_L", msg );
    L.x = Utils::mex_vector_pointer( arg_in_4, nX, msg_str.c_str() );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    msg_str = fmt::format( "{} R_segment", msg );
    R.i_segment = integer( Utils::mex_get_int64( arg_in_5, msg_str.c_str() ) );
    UTILS_ASSERT(
      R.i_segment >= 0 && R.i_segment < this->num_segments(),
      "{} iseg_R = {} expected to be in [0,{})\n",
      msg, R.i_segment, this->num_segments()
    );

    // -------------------
    msg_str = fmt::format( "{} argument q_R", msg );
    R.q = Utils::mex_vector_pointer( arg_in_6, nQ, msg_str.c_str() );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_R| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    msg_str = fmt::format( "{} argument x_R", msg );
    R.x = Utils::mex_vector_pointer( arg_in_7, nX, msg_str.c_str() );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_R| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );
  }

  // --------------------------------------------------------------------------

  void
  do_boundaryConditions(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('boundaryConditions', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    real_ptr bc = Utils::mex_create_matrix_value( arg_out_0, this->dim_BC(), 1 );

    this->boundaryConditions_eval( L, R, P, bc );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DbcDxxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DbcDxxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DbcDxxp, L, R, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_D2bcD2xxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('D2bcD2xxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, omega ): "

    CHECK_IN_OUT( 10, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );
    GET_ARG_OMEGA( arg_in_9 );

    RETURN_SPARSE( D2bcD2xxp, L, R, P, Omega );

    #undef CMD
  }

  /*\
   |           _  _     _     _   ___  ___
   |   __ _ __| |(_)___(_)_ _| |_| _ )/ __|
   |  / _` / _` || / _ \ | ' \  _| _ \ (__
   |  \__,_\__,_|/ \___/_|_||_\__|___/\___|
   |           |__/
  \*/
  void
  do_adjointBC(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('adjointBC', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, Omega ): "

    CHECK_IN_OUT( 10, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );
    GET_ARG_OMEGA_FULL( arg_in_9 );

    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, this->adjointBC_numEqns(), 1 );
    this->adjointBC_eval( L, R, P, Omega, res );

    #undef CMD
  }

  /*\
   |   ____            _  _       _       _   ____   ____ ____
   |  |  _ \  __ _  __| |(_) ___ (_)_ __ | |_| __ ) / ___|  _ \__  ____  ___ __
   |  | | | |/ _` |/ _` || |/ _ \| | '_ \| __|  _ \| |   | | | \ \/ /\ \/ / '_ \
   |  | |_| | (_| | (_| || | (_) | | | | | |_| |_) | |___| |_| |>  <  >  <| |_) |
   |  |____/ \__,_|\__,_|/ |\___/|_|_| |_|\__|____/ \____|____//_/\_\/_/\_\ .__/
   |                   |__/                                               |_|
  \*/
  void
  do_DadjointBCDxxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('DadjointBCDxxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, Omega ): "

    CHECK_IN_OUT( 10, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );
    GET_ARG_OMEGA_FULL( arg_in_9 );

    RETURN_SPARSE( DadjointBCDxxp, L, R, P, Omega );

    #undef CMD
  }

  /*\
   |     _
   |    (_)_  _ _ __  _ __
   |    | | || | '  \| '_ \
   |   _/ |\_,_|_|_|_| .__/
   |  |__/           |_|
  \*/
  void
  do_jump(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('jump', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ): "

    CHECK_IN_OUT( 11, 1 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );

    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, this->jump_numEqns(), 1 );
    this->jump_eval( L, R, P, res );

    #undef CMD
  }

  /*\
   |   ___  _                 ___      _
   |  |   \(_)_  _ _ __  _ __|   \__ _| |_ __
   |  | |) | | || | '  \| '_ \ |) \ \ / | '_ \
   |  |___// |\_,_|_|_|_| .__/___//_\_\_| .__/
   |     |__/           |_|             |_|
  \*/
  void
  do_DjumpDxlxlp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('DjumpDxlxlp', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ): "

    CHECK_IN_OUT( 11, 1 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );

    RETURN_SPARSE( DjumpDxlxlp, L, R, P );

    #undef CMD
  }

  /*\
   |                       _ _   _
   |   _ __  ___ _ _  __ _| | |_(_)___ ___
   |  | '_ \/ -_) ' \/ _` | |  _| / -_|_-<
   |  | .__/\___|_||_\__,_|_|\__|_\___/__/
   |  |_|
  \*/
  void
  do_JP(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JP', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    Utils::mex_set_scalar_value( arg_out_0, this->JP_eval( N, U, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_JU(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('JU', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    Utils::mex_set_scalar_value( arg_out_0, this->JU_eval( N, U, P ) );

    #undef CMD
  }

  /*\
   |   _                     _
   |  | |_ __ _ _ _ __ _ ___| |_
   |  |  _/ _` | '_/ _` / -_)  _|
   |   \__\__,_|_| \__, \___|\__|
   |               |___/
  \*/

  void
  do_lagrange_target(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('lagrange_target', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    Utils::mex_set_scalar_value( arg_out_0, this->lagrange_target( N, U, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DlagrangeDxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DlagrangeDxup', obj, iseg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    // Gradient is a row vector
    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, 1, this->DlagrangeDxup_numEqns() );
    this->DlagrangeDxup_eval( N, U, P , res );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_D2lagrangeD2xup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('D2lagrangeD2xup', obj, iseg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( D2lagrangeD2xup, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_mayer_target(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('mayer_target', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    Utils::mex_set_scalar_value( arg_out_0, this->mayer_target( L, R, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DmayerDxxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('DmayerDxxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    // Gradient is a row vector
    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, 1, this->DmayerDxxp_numEqns() );
    this->DmayerDxxp_eval( L, R, P , res );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_D2mayerD2xxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('D2mayerD2xxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( D2mayerD2xxp, L, R, P );

    #undef CMD
  }

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/

  void
  do_fd_ode(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('fd_ode', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars ): "

    CHECK_IN_OUT( 10, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_U( arg_in_8 );
    GET_ARG_P( arg_in_9 );

    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, this->dim_X(), 1 );

    this->fd_ode_eval( L, R, P, U, res );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_Dfd_odeDxxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('Dfd_odeDxxup', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars ): "

    CHECK_IN_OUT( 10, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_U( arg_in_8 );
    GET_ARG_P( arg_in_9 );

    RETURN_SPARSE( Dfd_odeDxxup, L, R, P, U );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_D2fd_odeD2xxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME \
    "_Mex('D2fd_odeD2xxup', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars, lambda ): "

    CHECK_IN_OUT( 11, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_U( arg_in_8 );
    GET_ARG_P( arg_in_9 );

    mwSize nL;
    L_const_pointer_type lambda(Utils::mex_vector_pointer( arg_in_10, nL, CMD " argument lambda" ));
    UTILS_MEX_ASSERT(
      nL == this->dim_X(),
      "{} |lambda| = {} expected to be {}\n", CMD, nL, this->dim_X()
    );

    RETURN_SPARSE( D2fd_odeD2xxup, L, R, P, U, lambda );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_mesh_functions(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('mesh_functions', obj, i_segment, s ): "

    CHECK_IN_OUT( 4, 1 );

    // -------------------
    integer i_segment = integer( Utils::mex_get_int64( arg_in_2, fmt::format( "{} i_segment", CMD ) ) );
    UTILS_ASSERT(
      i_segment >= 0 && i_segment < this->num_segments(),
      CMD "i_segment = {} expected to be in [0,{})\n",
      i_segment, this->num_segments()
    );

    // -------------------
    real_type s = Utils::mex_get_scalar_value( arg_in_3, fmt::format( "{} s", CMD ) );

    Q_pointer_type rhs( Utils::mex_create_matrix_value( arg_out_0, this->dim_Q(), 1 ) );
    this->q_eval( i_segment, s, rhs );
    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_nodes(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('nodes', obj ): "

    CHECK_IN_OUT( 2, 1 );

    integer n = m_mesh_base->num_nodes();
    real_ptr nodes = Utils::mex_create_matrix_value( arg_out_0, n, 1 );

    for ( integer i = 0; i < n; ++i ) nodes[i] = m_mesh_base->ss_node( i );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_node_to_segment(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('node_to_segment', obj ): "

    CHECK_IN_OUT( 2, 1 );

    integer n = m_mesh_base->num_nodes();
    int32_t * node_to_segment = Utils::mex_create_matrix_int32( arg_out_0, n, 1 );

    for ( integer i = 0; i < n; ++i )
      node_to_segment[i] = m_mesh_base->node_to_segment( i );

    #undef CMD
  }

  /*\
   |   ____       _   _
   |  |  _ \ __ _| |_| |_ ___ _ __ _ __
   |  | |_) / _` | __| __/ _ \ '__| '_ \
   |  |  __/ (_| | |_| ||  __/ |  | | | |
   |  |_|   \__,_|\__|\__\___|_|  |_| |_|
  \*/
  void
  do_eval_A_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_A_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_A_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = A_nnz();
    integer nr  = A_numRows();
    integer nc  = A_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_A");
    mem.allocate( 2*nnz, "A" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::A_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DadjointBCDxxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DadjointBCDxxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DadjointBCDxxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DadjointBCDxxp_nnz();
    integer nr  = DadjointBCDxxp_numRows();
    integer nc  = DadjointBCDxxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DadjointBCDxxp");
    mem.allocate( 2*nnz, "DadjointBCDxxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DadjointBCDxxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DbcDxxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DbcDxxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DbcDxxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DbcDxxp_nnz();
    integer nr  = DbcDxxp_numRows();
    integer nc  = DbcDxxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DbcDxxp");
    mem.allocate( 2*nnz, "DbcDxxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DbcDxxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_D2bcD2xxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_D2bcD2xxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_D2bcD2xxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = D2bcD2xxp_nnz();
    integer nr  = D2bcD2xxp_numRows();
    integer nc  = D2bcD2xxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_D2bcD2xxp");
    mem.allocate( 2*nnz, "D2bcD2xxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::D2bcD2xxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_Drhs_odeDxup_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_Drhs_odeDxup_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_Drhs_odeDxup_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = Drhs_odeDxup_nnz();
    integer nr  = Drhs_odeDxup_numRows();
    integer nc  = Drhs_odeDxup_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_Drhs_odeDxup");
    mem.allocate( 2*nnz, "Drhs_odeDxup" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::Drhs_odeDxup_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DsegmentLinkDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DsegmentLinkDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DsegmentLinkDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DsegmentLinkDxp_nnz();
    integer nr  = DsegmentLinkDxp_numRows();
    integer nc  = DsegmentLinkDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DsegmentLinkDxp");
    mem.allocate( 2*nnz, "DsegmentLinkDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DsegmentLinkDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DjumpDxlxlp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DjumpDxlxlp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DjumpDxlxlp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DjumpDxlxlp_nnz();
    integer nr  = DjumpDxlxlp_numRows();
    integer nc  = DjumpDxlxlp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DjumpDxlxlp");
    mem.allocate( 2*nnz, "DjumpDxlxlp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DjumpDxlxlp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DHxDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DHxDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DHxDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DHxDxp_nnz();
    integer nr  = DHxDxp_numRows();
    integer nc  = DHxDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DHxDxp");
    mem.allocate( 2*nnz, "DHxDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DHxDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJPxDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJPxDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJPxDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJPxDxp_nnz();
    integer nr  = DJPxDxp_numRows();
    integer nc  = DJPxDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJPxDxp");
    mem.allocate( 2*nnz, "DJPxDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJPxDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DLTxDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DLTxDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DLTxDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DLTxDxp_nnz();
    integer nr  = DLTxDxp_numRows();
    integer nc  = DLTxDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DLTxDxp");
    mem.allocate( 2*nnz, "DLTxDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DLTxDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJUxDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJUxDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJUxDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJUxDxp_nnz();
    integer nr  = DJUxDxp_numRows();
    integer nc  = DJUxDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJUxDxp");
    mem.allocate( 2*nnz, "DJUxDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJUxDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DHuDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DHuDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DHuDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DHuDxp_nnz();
    integer nr  = DHuDxp_numRows();
    integer nc  = DHuDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DHuDxp");
    mem.allocate( 2*nnz, "DHuDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DHuDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJPuDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJPuDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJPuDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJPuDxp_nnz();
    integer nr  = DJPuDxp_numRows();
    integer nc  = DJPuDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJPuDxp");
    mem.allocate( 2*nnz, "DJPuDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJPuDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DLTuDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DLTuDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DLTuDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DLTuDxp_nnz();
    integer nr  = DLTuDxp_numRows();
    integer nc  = DLTuDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DLTuDxp");
    mem.allocate( 2*nnz, "DLTuDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DLTuDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJUuDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJUuDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJUuDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJUuDxp_nnz();
    integer nr  = DJUuDxp_numRows();
    integer nc  = DJUuDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJUuDxp");
    mem.allocate( 2*nnz, "DJUuDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJUuDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DHpDp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DHpDp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DHpDp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DHpDp_nnz();
    integer nr  = DHpDp_numRows();
    integer nc  = DHpDp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DHpDp");
    mem.allocate( 2*nnz, "DHpDp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DHpDp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJPpDp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJPpDp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJPpDp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJPpDp_nnz();
    integer nr  = DJPpDp_numRows();
    integer nc  = DJPpDp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJPpDp");
    mem.allocate( 2*nnz, "DJPpDp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJPpDp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DLTpDp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DLTpDp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DLTpDp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DLTpDp_nnz();
    integer nr  = DLTpDp_numRows();
    integer nc  = DLTpDp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DLTpDp");
    mem.allocate( 2*nnz, "DLTpDp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DLTpDp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DJUpDp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DJUpDp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DJUpDp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DJUpDp_nnz();
    integer nr  = DJUpDp_numRows();
    integer nc  = DJUpDp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DJUpDp");
    mem.allocate( 2*nnz, "DJUpDp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DJUpDp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DLTargsDxup_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DLTargsDxup_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DLTargsDxup_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DLTargsDxup_nnz();
    integer nr  = DLTargsDxup_numRows();
    integer nc  = DLTargsDxup_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DLTargsDxup");
    mem.allocate( 2*nnz, "DLTargsDxup" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DLTargsDxup_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_D2LTargsD2xup_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_D2LTargsD2xup_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_D2LTargsD2xup_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = D2LTargsD2xup_nnz();
    integer nr  = D2LTargsD2xup_numRows();
    integer nc  = D2LTargsD2xup_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_D2LTargsD2xup");
    mem.allocate( 2*nnz, "D2LTargsD2xup" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::D2LTargsD2xup_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DnuDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DnuDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DnuDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DnuDxp_nnz();
    integer nr  = DnuDxp_numRows();
    integer nc  = DnuDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DnuDxp");
    mem.allocate( 2*nnz, "DnuDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DnuDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DetaDxp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DetaDxp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DetaDxp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DetaDxp_nnz();
    integer nr  = DetaDxp_numRows();
    integer nc  = DetaDxp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DetaDxp");
    mem.allocate( 2*nnz, "DetaDxp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DetaDxp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DgDxlxlp_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DgDxlxlp_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DgDxlxlp_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DgDxlxlp_nnz();
    integer nr  = DgDxlxlp_numRows();
    integer nc  = DgDxlxlp_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DgDxlxlp");
    mem.allocate( 2*nnz, "DgDxlxlp" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DgDxlxlp_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DgDu_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DgDu_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DgDu_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DgDu_nnz();
    integer nr  = DgDu_numRows();
    integer nc  = DgDu_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DgDu");
    mem.allocate( 2*nnz, "DgDu" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DgDu_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------

  void
  do_eval_DmDuu_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
    #define CMD MODEL_NAME "_Mex('eval_DmDuu_pattern',obj): "
    UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'eval_DmDuu_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    integer nnz = DmDuu_nnz();
    integer nr  = DmDuu_numRows();
    integer nc  = DmDuu_numCols();
    mxArray *args[5];
    real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
    real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
    Utils::mex_set_scalar_value( args[2], 1  );
    Utils::mex_set_scalar_value( args[3], nr );
    Utils::mex_set_scalar_value( args[4], nc );

    Mechatronix::Malloc<integer> mem("mex_DmDuu");
    mem.allocate( 2*nnz, "DmDuu" );
    integer_ptr i_row = mem( nnz );
    integer_ptr j_col = mem( nnz );
    MODEL_CLASS::DmDuu_pattern( i_row, j_col );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]+1;
      J[i] = j_col[i]+1;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    UTILS_MEX_ASSERT0( ok == 0, CMD "failed the call sparse(...)" );
    #undef CMD
  }

  //---------------------------------------------------------------------


  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  void
  do_cont(
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
  do_x_position(
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
  do_x_position_D_1(
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
  do_x_position_D_2(
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
  do_x_position_D_3(
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
  do_x_position_D_4(
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
  do_x_position_D_5(
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
  do_x_position_D_6(
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
  do_x_position_D_7(
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
  do_x_position_D_1_1(
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
  do_x_position_D_1_2(
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
  do_x_position_D_1_3(
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
  do_x_position_D_1_4(
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
  do_x_position_D_1_5(
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
  do_x_position_D_1_6(
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
  do_x_position_D_1_7(
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
  do_x_position_D_2_2(
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
  do_x_position_D_2_3(
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
  do_x_position_D_2_4(
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
  do_x_position_D_2_5(
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
  do_x_position_D_2_6(
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
  do_x_position_D_2_7(
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
  do_x_position_D_3_3(
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
  do_x_position_D_3_4(
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
  do_x_position_D_3_5(
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
  do_x_position_D_3_6(
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
  do_x_position_D_3_7(
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
  do_x_position_D_4_4(
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
  do_x_position_D_4_5(
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
  do_x_position_D_4_6(
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
  do_x_position_D_4_7(
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
  do_x_position_D_5_5(
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
  do_x_position_D_5_6(
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
  do_x_position_D_5_7(
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
  do_x_position_D_6_6(
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
  do_x_position_D_6_7(
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
  do_x_position_D_7_7(
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
  do_y_position(
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
  do_y_position_D_1(
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
  do_y_position_D_2(
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
  do_y_position_D_3(
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
  do_y_position_D_4(
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
  do_y_position_D_5(
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
  do_y_position_D_6(
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
  do_y_position_D_7(
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
  do_y_position_D_1_1(
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
  do_y_position_D_1_2(
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
  do_y_position_D_1_3(
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
  do_y_position_D_1_4(
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
  do_y_position_D_1_5(
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
  do_y_position_D_1_6(
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
  do_y_position_D_1_7(
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
  do_y_position_D_2_2(
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
  do_y_position_D_2_3(
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
  do_y_position_D_2_4(
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
  do_y_position_D_2_5(
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
  do_y_position_D_2_6(
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
  do_y_position_D_2_7(
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
  do_y_position_D_3_3(
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
  do_y_position_D_3_4(
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
  do_y_position_D_3_5(
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
  do_y_position_D_3_6(
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
  do_y_position_D_3_7(
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
  do_y_position_D_4_4(
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
  do_y_position_D_4_5(
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
  do_y_position_D_4_6(
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
  do_y_position_D_4_7(
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
  do_y_position_D_5_5(
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
  do_y_position_D_5_6(
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
  do_y_position_D_5_7(
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
  do_y_position_D_6_6(
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
  do_y_position_D_6_7(
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
  do_y_position_D_7_7(
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
  do_z_position(
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
  do_z_position_D_1(
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
  do_z_position_D_2(
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
  do_z_position_D_3(
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
  do_z_position_D_4(
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
  do_z_position_D_5(
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
  do_z_position_D_6(
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
  do_z_position_D_7(
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
  do_z_position_D_1_1(
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
  do_z_position_D_1_2(
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
  do_z_position_D_1_3(
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
  do_z_position_D_1_4(
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
  do_z_position_D_1_5(
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
  do_z_position_D_1_6(
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
  do_z_position_D_1_7(
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
  do_z_position_D_2_2(
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
  do_z_position_D_2_3(
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
  do_z_position_D_2_4(
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
  do_z_position_D_2_5(
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
  do_z_position_D_2_6(
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
  do_z_position_D_2_7(
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
  do_z_position_D_3_3(
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
  do_z_position_D_3_4(
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
  do_z_position_D_3_5(
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
  do_z_position_D_3_6(
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
  do_z_position_D_3_7(
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
  do_z_position_D_4_4(
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
  do_z_position_D_4_5(
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
  do_z_position_D_4_6(
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
  do_z_position_D_4_7(
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
  do_z_position_D_5_5(
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
  do_z_position_D_5_6(
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
  do_z_position_D_5_7(
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
  do_z_position_D_6_6(
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
  do_z_position_D_6_7(
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
  do_z_position_D_7_7(
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
  do_x_velocity(
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
  do_x_velocity_D_1(
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
  do_x_velocity_D_2(
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
  do_x_velocity_D_3(
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
  do_x_velocity_D_4(
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
  do_x_velocity_D_5(
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
  do_x_velocity_D_6(
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
  do_x_velocity_D_7(
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
  do_x_velocity_D_1_1(
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
  do_x_velocity_D_1_2(
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
  do_x_velocity_D_1_3(
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
  do_x_velocity_D_1_4(
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
  do_x_velocity_D_1_5(
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
  do_x_velocity_D_1_6(
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
  do_x_velocity_D_1_7(
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
  do_x_velocity_D_2_2(
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
  do_x_velocity_D_2_3(
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
  do_x_velocity_D_2_4(
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
  do_x_velocity_D_2_5(
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
  do_x_velocity_D_2_6(
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
  do_x_velocity_D_2_7(
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
  do_x_velocity_D_3_3(
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
  do_x_velocity_D_3_4(
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
  do_x_velocity_D_3_5(
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
  do_x_velocity_D_3_6(
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
  do_x_velocity_D_3_7(
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
  do_x_velocity_D_4_4(
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
  do_x_velocity_D_4_5(
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
  do_x_velocity_D_4_6(
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
  do_x_velocity_D_4_7(
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
  do_x_velocity_D_5_5(
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
  do_x_velocity_D_5_6(
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
  do_x_velocity_D_5_7(
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
  do_x_velocity_D_6_6(
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
  do_x_velocity_D_6_7(
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
  do_x_velocity_D_7_7(
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
  do_y_velocity(
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
  do_y_velocity_D_1(
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
  do_y_velocity_D_2(
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
  do_y_velocity_D_3(
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
  do_y_velocity_D_4(
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
  do_y_velocity_D_5(
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
  do_y_velocity_D_6(
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
  do_y_velocity_D_7(
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
  do_y_velocity_D_1_1(
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
  do_y_velocity_D_1_2(
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
  do_y_velocity_D_1_3(
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
  do_y_velocity_D_1_4(
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
  do_y_velocity_D_1_5(
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
  do_y_velocity_D_1_6(
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
  do_y_velocity_D_1_7(
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
  do_y_velocity_D_2_2(
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
  do_y_velocity_D_2_3(
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
  do_y_velocity_D_2_4(
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
  do_y_velocity_D_2_5(
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
  do_y_velocity_D_2_6(
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
  do_y_velocity_D_2_7(
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
  do_y_velocity_D_3_3(
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
  do_y_velocity_D_3_4(
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
  do_y_velocity_D_3_5(
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
  do_y_velocity_D_3_6(
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
  do_y_velocity_D_3_7(
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
  do_y_velocity_D_4_4(
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
  do_y_velocity_D_4_5(
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
  do_y_velocity_D_4_6(
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
  do_y_velocity_D_4_7(
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
  do_y_velocity_D_5_5(
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
  do_y_velocity_D_5_6(
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
  do_y_velocity_D_5_7(
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
  do_y_velocity_D_6_6(
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
  do_y_velocity_D_6_7(
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
  do_y_velocity_D_7_7(
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
  do_z_velocity(
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
  do_z_velocity_D_1(
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
  do_z_velocity_D_2(
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
  do_z_velocity_D_3(
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
  do_z_velocity_D_4(
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
  do_z_velocity_D_5(
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
  do_z_velocity_D_6(
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
  do_z_velocity_D_7(
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
  do_z_velocity_D_1_1(
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
  do_z_velocity_D_1_2(
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
  do_z_velocity_D_1_3(
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
  do_z_velocity_D_1_4(
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
  do_z_velocity_D_1_5(
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
  do_z_velocity_D_1_6(
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
  do_z_velocity_D_1_7(
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
  do_z_velocity_D_2_2(
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
  do_z_velocity_D_2_3(
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
  do_z_velocity_D_2_4(
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
  do_z_velocity_D_2_5(
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
  do_z_velocity_D_2_6(
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
  do_z_velocity_D_2_7(
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
  do_z_velocity_D_3_3(
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
  do_z_velocity_D_3_4(
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
  do_z_velocity_D_3_5(
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
  do_z_velocity_D_3_6(
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
  do_z_velocity_D_3_7(
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
  do_z_velocity_D_4_4(
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
  do_z_velocity_D_4_5(
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
  do_z_velocity_D_4_6(
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
  do_z_velocity_D_4_7(
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
  do_z_velocity_D_5_5(
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
  do_z_velocity_D_5_6(
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
  do_z_velocity_D_5_7(
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
  do_z_velocity_D_6_6(
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
  do_z_velocity_D_6_7(
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
  do_z_velocity_D_7_7(
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
  do_norm_reg(
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
  do_norm_reg_D_1(
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
  do_norm_reg_D_2(
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
  do_norm_reg_D_3(
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
  do_norm_reg_D_1_1(
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
  do_norm_reg_D_1_2(
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
  do_norm_reg_D_1_3(
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
  do_norm_reg_D_2_2(
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
  do_norm_reg_D_2_3(
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
  do_norm_reg_D_3_3(
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
  do_ray(
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
  do_ray_D_1(
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
  do_ray_D_2(
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
  do_ray_D_3(
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
  do_ray_D_4(
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
  do_ray_D_1_1(
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
  do_ray_D_1_2(
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
  do_ray_D_1_3(
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
  do_ray_D_1_4(
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
  do_ray_D_2_2(
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
  do_ray_D_2_3(
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
  do_ray_D_2_4(
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
  do_ray_D_3_3(
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
  do_ray_D_3_4(
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
  do_ray_D_4_4(
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
  do_vel(
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
  do_vel_D_1(
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
  do_vel_D_2(
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
  do_vel_D_3(
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
  do_vel_D_4(
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
  do_vel_D_5(
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
  do_vel_D_1_1(
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
  do_vel_D_1_2(
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
  do_vel_D_1_3(
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
  do_vel_D_1_4(
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
  do_vel_D_1_5(
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
  do_vel_D_2_2(
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
  do_vel_D_2_3(
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
  do_vel_D_2_4(
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
  do_vel_D_2_5(
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
  do_vel_D_3_3(
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
  do_vel_D_3_4(
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
  do_vel_D_3_5(
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
  do_vel_D_4_4(
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
  do_vel_D_4_5(
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
  do_vel_D_5_5(
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
  do_vc(
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
  do_vc_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_vc_DD(
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
  do_acceleration_r(
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
  do_acceleration_r_D_1(
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
  do_acceleration_r_D_2(
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
  do_acceleration_r_D_1_1(
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
  do_acceleration_r_D_1_2(
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
  do_acceleration_r_D_2_2(
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
  do_X_begin(
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
  do_X_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_X_begin_DD(
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
  do_Y_begin(
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
  do_Y_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_Y_begin_DD(
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
  do_Z_begin(
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
  do_Z_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_Z_begin_DD(
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
  do_VX_begin(
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
  do_VX_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VX_begin_DD(
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
  do_VY_begin(
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
  do_VY_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VY_begin_DD(
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
  do_VZ_begin(
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
  do_VZ_begin_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VZ_begin_DD(
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
  do_X_end(
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
  do_X_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_X_end_DD(
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
  do_Y_end(
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
  do_Y_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_Y_end_DD(
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
  do_Z_end(
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
  do_Z_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_Z_end_DD(
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
  do_VX_end(
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
  do_VX_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VX_end_DD(
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
  do_VY_end(
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
  do_VY_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VY_end_DD(
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
  do_VZ_end(
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
  do_VZ_end_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  )
  {
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
  do_VZ_end_DD(
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
  do_p_guess(
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
  do_f_guess(
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
  do_g_guess(
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
  do_h_guess(
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
  do_k_guess(
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
  do_L_guess(
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
  do_guess_setup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('guess_setup', obj,  ): "
    CHECK_IN_OUT( 2, 1 );

    real_ptr res = Utils::mex_create_matrix_value( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->guess_setup();
    #undef CMD
  }


};

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
typedef void (*DO_CMD)( int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[] );


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_read(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('read',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_read( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_setup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('setup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_setup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_remesh(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('remesh',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_remesh( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_set_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('set_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_set_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution_as_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution_as_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_solution_as_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_solve(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('solve',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_solve( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_dims(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('dims',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_dims( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_names(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('names',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_names( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_update_continuation(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('update_continuation',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_update_continuation( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_set_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('set_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_set_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_check_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('check_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_check_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_check_jacobian(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('check_jacobian',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_check_jacobian( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_solution2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_solution3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_ocp_data(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_ocp_data',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_get_ocp_data( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_init_U(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('init_U',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_init_U( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_U(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_U',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_U( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_F(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_F',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_F( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_JF(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_JF',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_JF( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_JF_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_JF_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_JF_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_pack(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('pack',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_pack( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_pack_for_direct(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('pack_for_direct',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_pack_for_direct( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_unpack(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('unpack',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_unpack( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_unpack_for_direct(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('unpack_for_direct',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_unpack_for_direct( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_estimate_multipliers(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('estimate_multipliers',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_estimate_multipliers( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ac(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ac',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ac( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DacDxlxlpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DacDxlxlpu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DacDxlxlpu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_hc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('hc',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_hc( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DhcDxlxlop(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DhcDxlxlop',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DhcDxlxlop( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_u(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('u',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_u( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DuDxlxlp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DuDxlxlp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DuDxlxlp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_rhs_ode(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('rhs_ode',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_rhs_ode( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Drhs_odeDxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Drhs_odeDxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Drhs_odeDxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_A(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('A',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_A( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eta(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eta',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eta( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DetaDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DetaDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DetaDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_nu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('nu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_nu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DnuDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DnuDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DnuDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Hx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHxDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHxDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DHxDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Hu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHuDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHuDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DHuDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Hp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHpDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHpDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DHpDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JPx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JPx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JPx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_LTx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('LTx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_LTx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JUx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JUx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JUx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JPp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JPp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JPp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_LTp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('LTp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_LTp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JUp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JUp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JUp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_LTargs(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('LTargs',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_LTargs( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJPxDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJPxDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJPxDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DLTxDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DLTxDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DLTxDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJUxDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJUxDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJUxDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJPuDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJPuDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJPuDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DLTuDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DLTuDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DLTuDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJUuDxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJUuDxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJUuDxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJPpDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJPpDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJPpDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DLTpDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DLTpDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DLTpDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DJUpDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DJUpDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DJUpDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DLTargsDxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DLTargsDxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DLTargsDxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_D2LTargsD2xup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('D2LTargsD2xup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_D2LTargsD2xup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_boundaryConditions(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('boundaryConditions',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_boundaryConditions( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DbcDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DbcDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DbcDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_D2bcD2xxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('D2bcD2xxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_D2bcD2xxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_adjointBC(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('adjointBC',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_adjointBC( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DadjointBCDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DadjointBCDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DadjointBCDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_jump(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('jump',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_jump( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DjumpDxlxlp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DjumpDxlxlp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DjumpDxlxlp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JP(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JP',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JP( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_JU(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('JU',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_JU( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_lagrange_target(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('lagrange_target',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_lagrange_target( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DlagrangeDxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DlagrangeDxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DlagrangeDxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_D2lagrangeD2xup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('D2lagrangeD2xup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_D2lagrangeD2xup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_mayer_target(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('mayer_target',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_mayer_target( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DmayerDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('DmayerDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_DmayerDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_D2mayerD2xxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('D2mayerD2xxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_D2mayerD2xxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_fd_ode(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('fd_ode',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_fd_ode( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Dfd_odeDxxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Dfd_odeDxxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Dfd_odeDxxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_D2fd_odeD2xxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('D2fd_odeD2xxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_D2fd_odeD2xxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_mesh_functions(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('mesh_functions',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_mesh_functions( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_nodes(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('nodes',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_nodes( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_node_to_segment(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('node_to_segment',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_node_to_segment( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_A_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_A_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_A_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DadjointBCDxxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DadjointBCDxxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DadjointBCDxxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DbcDxxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DbcDxxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DbcDxxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_D2bcD2xxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_D2bcD2xxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_D2bcD2xxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_Drhs_odeDxup_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_Drhs_odeDxup_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_Drhs_odeDxup_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DsegmentLinkDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DsegmentLinkDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DsegmentLinkDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DjumpDxlxlp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DjumpDxlxlp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DjumpDxlxlp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DHxDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DHxDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DHxDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJPxDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJPxDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJPxDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DLTxDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DLTxDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DLTxDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJUxDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJUxDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJUxDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DHuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DHuDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DHuDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJPuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJPuDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJPuDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DLTuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DLTuDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DLTuDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJUuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJUuDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJUuDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DHpDp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DHpDp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DHpDp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJPpDp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJPpDp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJPpDp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DLTpDp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DLTpDp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DLTpDp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DJUpDp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DJUpDp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DJUpDp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DLTargsDxup_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DLTargsDxup_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DLTargsDxup_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_D2LTargsD2xup_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_D2LTargsD2xup_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_D2LTargsD2xup_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DnuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DnuDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DnuDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DetaDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DetaDxp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DetaDxp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DgDxlxlp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DgDxlxlp_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DgDxlxlp_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DgDu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DgDu_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DgDu_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_DmDuu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_DmDuu_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_eval_DmDuu_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_cont(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('cont',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_cont( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_position_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_position_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_position_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_position_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_position_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_position_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_position_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_x_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('x_velocity_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_x_velocity_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_y_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('y_velocity_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_y_velocity_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_1_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_1_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_1_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_2_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_2_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_2_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_3_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_3_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_3_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_4_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_4_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_4_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_4_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_4_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_4_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_5_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_5_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_5_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_5_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_5_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_5_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_6_6(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_6_6',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_6_6( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_6_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_6_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_6_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_z_velocity_D_7_7(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('z_velocity_D_7_7',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_z_velocity_D_7_7( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_norm_reg_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('norm_reg_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_norm_reg_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ray_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('ray_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_ray_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_1_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_1_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_1_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_2_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_2_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_2_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_2_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_2_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_2_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_3_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_3_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_3_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_3_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_3_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_3_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_4_4(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_4_4',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_4_4( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_4_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_4_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_4_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vel_D_5_5(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vel_D_5_5',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vel_D_5_5( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vc',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vc( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vc_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vc_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vc_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_vc_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('vc_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_vc_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_acceleration_r_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('acceleration_r_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_acceleration_r_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_begin(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_begin',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_begin( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_begin_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_begin_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_begin_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_begin_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_begin_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_begin_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_X_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('X_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_X_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Y_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Y_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Y_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Z_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('Z_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_Z_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VX_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VX_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VX_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VY_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VY_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VY_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_end(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_end',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_end( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_end_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_end_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_end_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_VZ_end_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('VZ_end_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_VZ_end_DD( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_p_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_f_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('f_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_f_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_g_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('g_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_g_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_h_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('h_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_h_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_k_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('k_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_k_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_L_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('L_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_L_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_guess_setup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  UTILS_MEX_ASSERT(
    nrhs >= 2,
    MODEL_NAME "_Mex('guess_setup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  Utils::mex_convert_mx_to_ptr<ProblemStorage>(arg_in_1)->do_guess_setup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static std::map<std::string,DO_CMD> cmd_to_fun = {
  {"read",do_read},
  {"setup",do_setup},
  {"remesh",do_remesh},
  {"set_guess",do_set_guess},
  {"get_guess",do_get_guess},
  {"get_solution_as_guess",do_get_solution_as_guess},
  {"solve",do_solve},
  {"dims",do_dims},
  {"names",do_names},
  {"update_continuation",do_update_continuation},
  {"get_raw_solution",do_get_raw_solution},
  {"set_raw_solution",do_set_raw_solution},
  {"check_raw_solution",do_check_raw_solution},
  {"check_jacobian",do_check_jacobian},
  {"get_solution",do_get_solution},
  {"get_solution2",do_get_solution2},
  {"get_solution3",do_get_solution3},
  {"get_ocp_data",do_get_ocp_data},
  {"init_U",do_init_U},
  {"eval_U",do_eval_U},
  {"eval_F",do_eval_F},
  {"eval_JF",do_eval_JF},
  {"eval_JF_pattern",do_eval_JF_pattern},
  {"pack",do_pack},
  {"pack_for_direct",do_pack_for_direct},
  {"unpack",do_unpack},
  {"unpack_for_direct",do_unpack_for_direct},
  {"estimate_multipliers",do_estimate_multipliers},
  {"ac",do_ac},
  {"DacDxlxlpu",do_DacDxlxlpu},
  {"hc",do_hc},
  {"DhcDxlxlop",do_DhcDxlxlop},
  {"u",do_u},
  {"DuDxlxlp",do_DuDxlxlp},
  {"rhs_ode",do_rhs_ode},
  {"Drhs_odeDxup",do_Drhs_odeDxup},
  {"A",do_A},
  {"eta",do_eta},
  {"DetaDxp",do_DetaDxp},
  {"nu",do_nu},
  {"DnuDxp",do_DnuDxp},
  {"Hx",do_Hx},
  {"DHxDxp",do_DHxDxp},
  {"Hu",do_Hu},
  {"DHuDxp",do_DHuDxp},
  {"Hp",do_Hp},
  {"DHpDp",do_DHpDp},
  {"JPx",do_JPx},
  {"LTx",do_LTx},
  {"JUx",do_JUx},
  {"JPp",do_JPp},
  {"LTp",do_LTp},
  {"JUp",do_JUp},
  {"LTargs",do_LTargs},
  {"DJPxDxp",do_DJPxDxp},
  {"DLTxDxp",do_DLTxDxp},
  {"DJUxDxp",do_DJUxDxp},
  {"DJPuDxp",do_DJPuDxp},
  {"DLTuDxp",do_DLTuDxp},
  {"DJUuDxp",do_DJUuDxp},
  {"DJPpDp",do_DJPpDp},
  {"DLTpDp",do_DLTpDp},
  {"DJUpDp",do_DJUpDp},
  {"DLTargsDxup",do_DLTargsDxup},
  {"D2LTargsD2xup",do_D2LTargsD2xup},
  {"boundaryConditions",do_boundaryConditions},
  {"DbcDxxp",do_DbcDxxp},
  {"D2bcD2xxp",do_D2bcD2xxp},
  {"adjointBC",do_adjointBC},
  {"DadjointBCDxxp",do_DadjointBCDxxp},
  {"jump",do_jump},
  {"DjumpDxlxlp",do_DjumpDxlxlp},
  {"JP",do_JP},
  {"JU",do_JU},
  {"lagrange_target",do_lagrange_target},
  {"DlagrangeDxup",do_DlagrangeDxup},
  {"D2lagrangeD2xup",do_D2lagrangeD2xup},
  {"mayer_target",do_mayer_target},
  {"DmayerDxxp",do_DmayerDxxp},
  {"D2mayerD2xxp",do_D2mayerD2xxp},
  {"fd_ode",do_fd_ode},
  {"Dfd_odeDxxup",do_Dfd_odeDxxup},
  {"D2fd_odeD2xxup",do_D2fd_odeD2xxup},
  {"mesh_functions",do_mesh_functions},
  {"nodes",do_nodes},
  {"node_to_segment",do_node_to_segment},
  {"eval_A_pattern",do_eval_A_pattern},
  {"eval_DadjointBCDxxp_pattern",do_eval_DadjointBCDxxp_pattern},
  {"eval_DbcDxxp_pattern",do_eval_DbcDxxp_pattern},
  {"eval_D2bcD2xxp_pattern",do_eval_D2bcD2xxp_pattern},
  {"eval_Drhs_odeDxup_pattern",do_eval_Drhs_odeDxup_pattern},
  {"eval_DsegmentLinkDxp_pattern",do_eval_DsegmentLinkDxp_pattern},
  {"eval_DjumpDxlxlp_pattern",do_eval_DjumpDxlxlp_pattern},
  {"eval_DHxDxp_pattern",do_eval_DHxDxp_pattern},
  {"eval_DJPxDxp_pattern",do_eval_DJPxDxp_pattern},
  {"eval_DLTxDxp_pattern",do_eval_DLTxDxp_pattern},
  {"eval_DJUxDxp_pattern",do_eval_DJUxDxp_pattern},
  {"eval_DHuDxp_pattern",do_eval_DHuDxp_pattern},
  {"eval_DJPuDxp_pattern",do_eval_DJPuDxp_pattern},
  {"eval_DLTuDxp_pattern",do_eval_DLTuDxp_pattern},
  {"eval_DJUuDxp_pattern",do_eval_DJUuDxp_pattern},
  {"eval_DHpDp_pattern",do_eval_DHpDp_pattern},
  {"eval_DJPpDp_pattern",do_eval_DJPpDp_pattern},
  {"eval_DLTpDp_pattern",do_eval_DLTpDp_pattern},
  {"eval_DJUpDp_pattern",do_eval_DJUpDp_pattern},
  {"eval_DLTargsDxup_pattern",do_eval_DLTargsDxup_pattern},
  {"eval_D2LTargsD2xup_pattern",do_eval_D2LTargsD2xup_pattern},
  {"eval_DnuDxp_pattern",do_eval_DnuDxp_pattern},
  {"eval_DetaDxp_pattern",do_eval_DetaDxp_pattern},
  {"eval_DgDxlxlp_pattern",do_eval_DgDxlxlp_pattern},
  {"eval_DgDu_pattern",do_eval_DgDu_pattern},
  {"eval_DmDuu_pattern",do_eval_DmDuu_pattern},
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
  {"vc_DD",do_vc_DD},
  {"acceleration_r",do_acceleration_r},
  {"acceleration_r_D_1",do_acceleration_r_D_1},
  {"acceleration_r_D_2",do_acceleration_r_D_2},
  {"acceleration_r_D_1_1",do_acceleration_r_D_1_1},
  {"acceleration_r_D_1_2",do_acceleration_r_D_1_2},
  {"acceleration_r_D_2_2",do_acceleration_r_D_2_2},
  {"X_begin",do_X_begin},
  {"X_begin_D",do_X_begin_D},
  {"X_begin_DD",do_X_begin_DD},
  {"Y_begin",do_Y_begin},
  {"Y_begin_D",do_Y_begin_D},
  {"Y_begin_DD",do_Y_begin_DD},
  {"Z_begin",do_Z_begin},
  {"Z_begin_D",do_Z_begin_D},
  {"Z_begin_DD",do_Z_begin_DD},
  {"VX_begin",do_VX_begin},
  {"VX_begin_D",do_VX_begin_D},
  {"VX_begin_DD",do_VX_begin_DD},
  {"VY_begin",do_VY_begin},
  {"VY_begin_D",do_VY_begin_D},
  {"VY_begin_DD",do_VY_begin_DD},
  {"VZ_begin",do_VZ_begin},
  {"VZ_begin_D",do_VZ_begin_D},
  {"VZ_begin_DD",do_VZ_begin_DD},
  {"X_end",do_X_end},
  {"X_end_D",do_X_end_D},
  {"X_end_DD",do_X_end_DD},
  {"Y_end",do_Y_end},
  {"Y_end_D",do_Y_end_D},
  {"Y_end_DD",do_Y_end_DD},
  {"Z_end",do_Z_end},
  {"Z_end_D",do_Z_end_D},
  {"Z_end_DD",do_Z_end_DD},
  {"VX_end",do_VX_end},
  {"VX_end_D",do_VX_end_D},
  {"VX_end_DD",do_VX_end_DD},
  {"VY_end",do_VY_end},
  {"VY_end_D",do_VY_end_D},
  {"VY_end_DD",do_VY_end_DD},
  {"VZ_end",do_VZ_end},
  {"VZ_end_D",do_VZ_end_D},
  {"VZ_end_DD",do_VZ_end_DD},
  {"p_guess",do_p_guess},
  {"f_guess",do_f_guess},
  {"g_guess",do_g_guess},
  {"h_guess",do_h_guess},
  {"k_guess",do_k_guess},
  {"L_guess",do_L_guess},
  {"guess_setup",do_guess_setup},
  {"new",do_new},
  {"set_info_level",do_set_info_level},
  {"set_max_threads",do_set_max_threads},
  {"help",do_help},
  {"delete",do_delete}
};

void
mexFunction(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {

  if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);

  pConsole->setOff();

  try {
    UTILS_MEX_ASSERT0( nrhs > 0, MODEL_NAME "_Mex: Missing Arguments!" );
    UTILS_MEX_ASSERT0( mxIsChar(arg_in_0), MODEL_NAME "_Mex: First argument must be a string" );
    string cmd = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun( nlhs, plhs, nrhs, prhs );
  }
  catch ( std::out_of_range const & exc ) {
    mexErrMsgTxt( fmt::format( "gtocX_2burn_pars_Mex, unknown command: {}", exc.what() ).c_str() );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt( fmt::format( "gtocX_2burn_pars_Mex, error: {}", exc.what() ).c_str() );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
