/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Mex.cc                                                |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
#include "AlpRider.hh"
#include "AlpRider_Pars.hh"
#include <sstream>

#include "mex_utils.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace AlpRiderLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;

/*
// redirect stdout, found at
// https://it.mathworks.com/matlabcentral/answers/132527-in-mex-files-where-does-output-to-stdout-and-stderr-go
*/

#ifdef MECHATRONIX_OS_LINUX

class mystream : public std::streambuf {
protected:

  std::streamsize
  xsputn(const char *s, std::streamsize n) override
  { mexPrintf("%.*s", n, s); mexEvalString("drawnow;"); return n; }

  int
  overflow(int c=EOF) override
  { if (c != EOF) { mexPrintf("%.1s", &c); } return 1; }

};

class scoped_redirect_cout {
public:
  scoped_redirect_cout()
  { old_buf = std::cout.rdbuf(); std::cout.rdbuf(&mout); }
  ~scoped_redirect_cout()
  { std::cout.rdbuf(old_buf); }
private:
  mystream mout;
  std::streambuf *old_buf;
};
static scoped_redirect_cout mycout_redirect;

#endif


static char const help_msg[] =
"%===========================================================================%\n"
"Mex command has the following possible calls:\n"
"AlpRider_Mex('command', arguments ):\n"
"%===========================================================================%\n"
;

#define MODEL_NAME  "AlpRider"
#define MODEL_CLASS AlpRider

#define CHECK_IN(N) \
  MEX_ASSERT2( nrhs == N, CMD "Expected {} argument(s), nrhs = {}\n", N, nrhs )

#define CHECK_OUT(N) \
  MEX_ASSERT2( nlhs == N, CMD "Expected {} argument(s), nlhs = {}\n", N, nlhs )

#define CHECK_IN_OUT(N,M) CHECK_IN(N); CHECK_OUT(M)

#define MEX_CHECK_DIMS(A,B,C,D) \
  MEX_ASSERT( A == C && B == D, CMD "Argument dimensions must be the same\n" )

#define GET_ARG_P(ARG)                                              \
  mwSize nP;                                                        \
  P_const_pointer_type P(getVectorPointer( ARG, nP,                 \
    fmt::format( "{} argument pars", CMD )                          \
  ) );                                                              \
  UTILS_ASSERT(                                                     \
    nP == this->dim_Pars(),                                         \
    "{} |pars| = {} expected to be {}\n", CMD, nP, this->dim_Pars() \
  );

#define GET_ARG_U(ARG)                                              \
  mwSize nU;                                                        \
  U_const_pointer_type U(getVectorPointer( ARG, nU,                 \
    fmt::format( "{} argument pars", CMD )                          \
  ) );                                                              \
  UTILS_ASSERT(                                                     \
    nU == this->dim_U(),                                            \
    "{} |U| = {} expected to be {}\n", CMD, nU, this->dim_U()       \
  );

#define GET_ARG_OMEGA(ARG)                                             \
  mwSize nO;                                                           \
  OMEGA_const_pointer_type Omega(getVectorPointer( ARG, nO,            \
    fmt::format( "{} argument pars", CMD )                             \
  ) );                                                                 \
  UTILS_ASSERT(                                                        \
    nO == this->dim_Omega(),                                           \
    "{} |Omega| = {} expected to be {}\n", CMD, nO, this->dim_Omega()  \
  );

#define GET_ARG_OMEGA_FULL(ARG)                                         \
  mwSize nO;                                                            \
  OMEGA_full_const_pointer_type Omega(getVectorPointer( ARG, nO,        \
    fmt::format( "{} argument pars", CMD )                              \
  ) );                                                                  \
  UTILS_ASSERT(                                                         \
    nO == this->dim_full_BC(),                                          \
    "{} |Omega| = {} expected to be {}\n", CMD, nO, this->dim_full_BC() \
  );

#define GET_ARG_V(ARG)                                              \
  mwSize nV;                                                        \
  V_const_pointer_type V(getVectorPointer( ARG, nV,                 \
    fmt::format( "{} argument pars", CMD )                          \
  ) );                                                              \
  UTILS_ASSERT(                                                     \
    nV == this->dim_X(),                                            \
    "{} |V| = {} expected to be {}\n", CMD, nV, this->dim_X()       \
  );

#define RETURN_SPARSE(MATNAME,...)                                     \
  size_t nnz = size_t(this->MATNAME##_nnz());                          \
  mxArray *args[5];                                                    \
  real_type * Irow = createMatrixValue( args[0], 1, nnz );             \
  real_type * Jcol = createMatrixValue( args[1], 1, nnz );             \
  real_type * VALS = createMatrixValue( args[2], 1, nnz );             \
  setScalarValue( args[3], this->MATNAME##_numRows() );                \
  setScalarValue( args[4], this->MATNAME##_numCols() );                \
                                                                       \
  Mechatronix::Malloc<integer> mem("mex_" #MATNAME );                  \
  mem.allocate( 2*nnz, #MATNAME );                                     \
  integer * i_row = mem( nnz );                                        \
  integer * j_col = mem( nnz );                                        \
  this->MATNAME##_pattern( i_row, j_col );                             \
  for ( size_t i = 0; i < nnz; ++i )                                   \
    { Irow[i] = i_row[i]+1; Jcol[i] = j_col[i]+1; }                    \
  this->MATNAME##_sparse( __VA_ARGS__, VALS );                         \
                                                                       \
  int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );          \
  MEX_ASSERT( ok == 0, CMD "failed the call sparse(...)" )


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

  ProblemStorage( std::string const & cname, ThreadPool * TP, Console const * console )
  : MODEL_CLASS(cname,TP,console)
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
    MEX_ASSERT2(
      Mechatronix::check_if_file_exists( fname.c_str() ),
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
  ) {
    #define CMD MODEL_NAME "_Mex('read',obj,filename): "
    CHECK_IN_OUT(3,1);
    MEX_ASSERT2(
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
  ) {
    #define CMD MODEL_NAME "_Mex('setup',obj,struct_or_filename): "
    CHECK_IN_OUT(3,0);
    gc_data.clear(); // clear data for rewrite it
    if ( mxIsStruct(arg_in_2) ) { // read from file
      mxArray_to_GenericContainer( arg_in_2, gc_data );
    } else if ( mxIsChar(arg_in_2) ) {
      string fname = mxArrayToString(arg_in_2);
      this->read( fname, gc_data );
    } else { // setup using MATLAB structure
      MEX_ERROR2(
        MODEL_NAME "3rd argument must be a struct or a string, found: ``{}''\n",
        mxGetClassName(arg_in_2)
      );
    }

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
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
  ) {
    #define CMD MODEL_NAME "_Mex('remesh',obj,new_mesh): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'remesh'" );
    MEX_ASSERT2(
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
  ) {
    #define CMD MODEL_NAME "_Mex('set_guess',obj[,userguess]): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'set_guess'" );
    MEX_ASSERT2(
      nrhs == 2 || nrhs == 3,
      CMD "Expected 2 or 3 input argument(s), nrhs = {}\n", nrhs
    );
    CHECK_OUT( 0 );
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
    #undef CMD
  }

  void
  do_get_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_guess',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'guess'" );
    CHECK_IN_OUT(2,1);
    GenericContainer_to_mxArray( gc_data("Guess"), arg_out_0 );
    #undef CMD
  }

  void
  do_get_solution_as_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution_as_guess',obj): "
    MEX_ASSERT(
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
  ) {
    #define CMD MODEL_NAME "_Mex('solve',obj[,timeout]): "
    MEX_ASSERT(
      guess_ok,
      CMD "use 'set_guess' before to use 'solve'"
    );
    MEX_ASSERT2(
      nrhs == 2 || nrhs == 3,
      CMD "Expected 2 or 3 argument(s), nrhs = {}", nrhs
    );
    CHECK_OUT( 1 );
    if ( nrhs == 3 ) {
      real_type ms = getScalarValue( arg_in_2, CMD " timeout" );
      MODEL_CLASS::set_timeout_ms( ms );
    }
    solve_ok = MODEL_CLASS::solve();
    setScalarBool( arg_out_0, solve_ok );
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
  ) {
    #define CMD MODEL_NAME "_Mex('dims',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'dims'" );
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
  ) {
    #define CMD MODEL_NAME "_Mex('names',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'names'" );
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
  ) {
    #define CMD MODEL_NAME "_Mex('update_continuation',obj,nphase,old_s,s): "
    MEX_ASSERT(
      setup_ok,
      CMD "use 'setup' before to use 'update_continuation'"
    );
    CHECK_IN_OUT( 5, 0 );
    int64_t nphase  = getInt( arg_in_2, CMD " nphase number" );
    real_type old_s = getScalarValue( arg_in_3, CMD " old_s" );
    real_type s     = getScalarValue( arg_in_4, CMD " s" );
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
  ) {
    #define CMD MODEL_NAME "_Mex('get_raw_solution',obj): "
    MEX_ASSERT(
      guess_ok,
      CMD "use 'set_guess' before to use 'get_raw_solution'"
    );
    CHECK_IN_OUT( 2, 2 );
    real_type * x = createMatrixValue( arg_out_0, this->num_equations(), 1 );
    real_type * u = createMatrixValue( arg_out_1, this->num_parameters(), 1 );
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
  ) {
    #define CMD MODEL_NAME "_Mex('set_raw_solution',obj,x,u): "
    MEX_ASSERT(
      setup_ok,
      CMD "use 'setup' before to use 'set_raw_solution'"
    );
    CHECK_IN_OUT( 4, 0 );
    mwSize dimx,dimu;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x");
    real_type const * u = getVectorPointer( arg_in_3, dimu, CMD "argument u");
    mwSize neq = this->num_equations();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    mwSize npar = this->num_parameters();
    MEX_ASSERT2(
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
  ) {
    #define CMD MODEL_NAME "_Mex('check_raw_solution',obj,x): "
    MEX_ASSERT(
      guess_ok,
      CMD "use 'set_guess' before to use 'check_raw_solution'"
    );
    CHECK_IN_OUT( 3, 1 );
    mwSize dimx, dimp;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    mwSize neq = this->num_equations();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    setScalarBool( arg_out_0, this->check_raw_solution(x) );
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
  ) {
    #define CMD MODEL_NAME "_Mex('check_jacobian',obj,x,u,epsi): "
    MEX_ASSERT(
      guess_ok,
      CMD "use 'set_guess' before to use 'check_jacobian'"
    );
    CHECK_IN_OUT( 5, 0 );
    mwSize dimx,dimu;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    real_type const * u = getVectorPointer( arg_in_3, dimx, CMD "argument u" );
    real_type epsi = getScalarValue( arg_in_4, CMD "argument epsi" );
    mwSize neq = this->num_equations();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    mwSize npar = this->num_parameters();
    MEX_ASSERT2(
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
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution',obj[,column_name]): "
    MEX_ASSERT(
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
      MEX_ASSERT(
        mxIsChar(arg_in_2),
        CMD " Third argument must be a string"
      );
      string const & cname = mxArrayToString(arg_in_2);
      GenericContainer const & idx = gc_solution1("idx");
      MEX_ASSERT2(
        idx.exists(cname),
        CMD "data column `{}` do not exists", cname
      );
      integer icol = idx(cname).get_as_int();
      GenericContainer::mat_real_type const & data = gc_solution1("data").get_mat_real();
      real_type * res = createMatrixValue( arg_out_0, data.numRows(), 1 );
      data.getColumn( icol, res );
    } else {
      MEX_ERROR2( CMD "use 2 or 3 arguments, nrhs = {}\n", nrhs );
    }
    #undef CMD
  }

  void
  do_get_solution2(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution2',obj): "
    MEX_ASSERT(
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
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution3',obj): "
    MEX_ASSERT(
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
  ) {
    #define CMD MODEL_NAME "_Mex('get_ocp_data',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'get_ocp_data'" );
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
  ) {
    #define CMD MODEL_NAME "_Mex('init_U',obj,x,do_minimize): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'init_U'" );
    CHECK_IN_OUT( 4, 1 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    mwSize neq = this->num_equations();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    bool do_minimize = getBool( arg_in_3, CMD );
    real_type * u = createMatrixValue( arg_out_0, this->num_parameters(), 1 );
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
  ) {
    #define CMD MODEL_NAME "_Mex('eval_U',obj,x,u_guess): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'eval_U'" );
    CHECK_IN_OUT( 4, 1 );
    mwSize dimx, dimu;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    mwSize neq = this->num_equations();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    real_type const * u_guess = getVectorPointer( arg_in_3, dimu, CMD );
    mwSize nu = this->num_parameters();
    MEX_ASSERT2(
      dimu == nu,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimu, nu
    );
    real_type * u = createMatrixValue( arg_out_0, this->num_parameters(), 1 );
    std::copy_n( u_guess, nu, u );
    MODEL_CLASS::UC_eval( x, u );
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
  ) {
    #define CMD MODEL_NAME "_Mex('eval_F',obj,x,u): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'eval_F'" );
    CHECK_IN_OUT( 4, 2 );
    mwSize dimx, dimu;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    real_type const * u = getVectorPointer( arg_in_3, dimu, CMD );
    mwSize neq  = this->num_equations();
    mwSize npar = this->num_parameters();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    MEX_ASSERT2(
      dimu == npar,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimu, npar
    );
    real_type * f = createMatrixValue( arg_out_0, this->num_equations(), 1 );
    bool ok = true;
    try {
      MODEL_CLASS::eval_F( x, u, f );
    } catch ( std::exception const & exc ) {
      mexWarnMsgTxt( fmt::format( "AlpRider_Mex('eval_F',...) error: {}", exc.what() ).c_str() );
      ok = false;
    } catch ( ... ) {
      mexWarnMsgTxt( "AlpRider_Mex('eval_F',...) unkown error\n" );
      ok = false;
    }
    setScalarBool( arg_out_1, ok );
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
  ) {
    #define CMD MODEL_NAME "_Mex('eval_JF',obj,x,u): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'eval_JF'" );
    CHECK_IN_OUT( 4, 2 );
    mwSize dimx, dimu;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    real_type const * u = getVectorPointer( arg_in_3, dimu, CMD );
    mwSize neq  = this->num_equations();
    mwSize npar = this->num_parameters();
    MEX_ASSERT2(
      dimx == neq,
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, neq
    );
    MEX_ASSERT2(
      dimu == npar,
      CMD " size(u) = {} must be equal to npars = {}\n",
      dimu, npar
    );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    real_type * V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], num_equations() );
    setScalarValue( args[4], num_equations() );

    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz(), "eval_JF" );
    integer * i_row = mem( nnz() );
    integer * j_col = mem( nnz() );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz(); ++i ) {
      I[i] = static_cast<real_type>(i_row[i]);
      J[i] = static_cast<real_type>(j_col[i]);
      MEX_ASSERT2(
        I[i] > 0 && I[i] <= num_equations() &&
        J[i] > 0 && J[i] <= num_equations(),
        CMD " index I = {} J = {} must be in the range = [1,{}]\n",
        I[i], J[i], num_equations()
      );
    }

    bool ok_value = true;
    try {
      MODEL_CLASS::eval_JF_values( x, u, V );
    } catch ( std::exception const & exc ) {
      mexWarnMsgTxt( fmt::format( "AlpRider_Mex('eval_JF',...) error: {}", exc.what() ).c_str() );
      ok_value = false;
    } catch ( ... ) {
      mexWarnMsgTxt( "AlpRider_Mex('eval_JF',...) unkown error\n" );
      ok_value = false;
    }
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD "failed the call sparse(...)" );
    setScalarBool( arg_out_1, ok_value );
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
  ) {
    #define CMD MODEL_NAME "_Mex('eval_JF_pattern',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'eval_JF_pattern'" );
    CHECK_IN_OUT( 2, 1 );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    setScalarValue( args[2], 1 );
    setScalarValue( args[3], num_equations() );
    setScalarValue( args[4], num_equations() );

    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz(), "eval_JF_pattern" );
    integer * i_row = mem( nnz() );
    integer * j_col = mem( nnz() );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz(); ++i ) {
      I[i] = static_cast<real_type>(i_row[i]);
      J[i] = static_cast<real_type>(j_col[i]);
      MEX_ASSERT2(
        I[i] > 0 && I[i] <= num_equations() &&
        J[i] > 0 && J[i] <= num_equations(),
        CMD " index I = {} J = {} must be in the range = [1,{}]\n",
        I[i], J[i], num_equations()
      );
    }

    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD "failed the call sparse(...)" );
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
  ) {
    #define CMD MODEL_NAME "_Mex('pack',obj,x,lambda,pars,omega): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'pack'" );
    CHECK_IN_OUT( 6, 1 );

    mwSize nrX, ncX, nrL, ncL, nP, nO;
    X_const_pointer_type     X(getMatrixPointer( arg_in_2, nrX, ncX, CMD "argument x" ));
    L_const_pointer_type     L(getMatrixPointer( arg_in_3, nrL, ncL, CMD "argument lambda" ));
    P_const_pointer_type     P(getVectorPointer( arg_in_4, nP,       CMD "argument pars" ));
    OMEGA_const_pointer_type O(getVectorPointer( arg_in_5, nO,       CMD "argument omega" ));
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
    real_type * Z = createMatrixValue( arg_out_0, 1, this->num_equations() );
    this->pack( X, L, P, O, Z );
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
  ) {
    #define CMD MODEL_NAME "_Mex('unpack',obj,Z): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'unpack'" );
    CHECK_IN_OUT( 3, 4 );

    integer nn = this->num_nodes();
    mwSize nZ;
    real_type const * Z = getVectorPointer( arg_in_2, nZ, CMD "argument Z" );
    UTILS_ASSERT(
      nZ == mwSize(this->num_equations()),
      "{} length(Z) = {} expected to be {}\n",
      CMD, nZ, this->num_equations()
    );

    X_pointer_type     X(createMatrixValue( arg_out_0, this->dim_X(), nn ));
    L_pointer_type     L(createMatrixValue( arg_out_1, this->dim_X(), nn ));
    P_pointer_type     P(createMatrixValue( arg_out_2, 1, this->dim_Pars() ));
    OMEGA_pointer_type O(createMatrixValue( arg_out_3, 1, this->dim_Omega() ));

    this->unpack( Z, X, L, P, O );
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
    L.i_segment = integer( getInt( arg_in_2, fmt::format( "{} L_segment", msg ) ) );
    UTILS_ASSERT(
      L.i_segment >= 0 && L.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, L.i_segment, this->num_segments()
    );

    // -------------------
    L.q = getVectorPointer( arg_in_3, nQ, fmt::format( "{} argument q_L", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    L.x = getVectorPointer( arg_in_4, nX, fmt::format( "{} argument x_L", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    L.lambda = getVectorPointer( arg_in_5, nL, fmt::format( "{} argument lambda_L", msg ) );
    UTILS_ASSERT(
      nL == this->dim_X(),
      "{} |lambda_L| = {} expected to be {}\n",
      msg, nL, this->dim_X()
    );

    // -------------------
    R.i_segment = integer( getInt( arg_in_6, fmt::format( "{} R_segment", msg ) ) );
    UTILS_ASSERT(
      R.i_segment >= 0 && R.i_segment < this->num_segments(),
      "{} iseg_R = {} expected to be in [0,{})\n",
      msg, R.i_segment, this->num_segments()
    );

    // -------------------
    R.q = getVectorPointer( arg_in_7, nQ, fmt::format( "{} argument q_R", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_R| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    R.x = getVectorPointer( arg_in_8, nX, fmt::format( "{} argument x_R", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_R| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    R.lambda = getVectorPointer( arg_in_9, nL, fmt::format( "{} argument lambda_R", msg ) );
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
    N.i_segment = integer( getInt( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
    UTILS_ASSERT(
      N.i_segment >= 0 && N.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, N.i_segment, this->num_segments()
    );

    // -------------------
    N.q = getVectorPointer( arg_in_3, nQ, fmt::format( "{} argument q_M", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n[try to call eval_q]\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    N.x = getVectorPointer( arg_in_4, nX, fmt::format( "{} argument x_M", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    N.lambda = getVectorPointer( arg_in_5, nL, fmt::format( "{} argument lambda_M", msg ) );
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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('ac', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_U( arg_in_11 );

    integer n_thread = 0;

    real_type * a = createMatrixValue( arg_out_0, 2*this->dim_X(), 1 );
    real_type * c = createMatrixValue( arg_out_1, this->dim_Pars(), 1 );

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
  do_DacDxlxlp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME \
    "_Mex('DacDxlxlp', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U, DuDxlxlp ): "

    CHECK_IN_OUT( 13, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_U( arg_in_11 );

    mwSize nXLP;
    real_type const * DuDxlxlp_ptr = getMatrixPointer( arg_in_12, nU, nXLP,
      fmt::format( "{} argument DuDxlxlp", CMD )
    );
    UTILS_ASSERT(
      nU == this->dim_U() && nXLP == 4*this->dim_X()+this->dim_Pars(),
      "{} size(DuDxlxlp) = {} x {} expected to be {} x {}\n",
      CMD, nU, nXLP,
      this->dim_U(), 4*this->dim_X()+this->dim_Pars()
    );

    integer n_thread = 0;
    integer nCOL     = 4*this->dim_X()+this->dim_Pars();
    integer nR       = 2*this->dim_X();
    real_type * a = createMatrixValue( arg_out_0, nR, nCOL );
    real_type * c = createMatrixValue( arg_out_1, this->dim_Pars(), nCOL );

    MatrixWrapper<real_type> DuDxlxlp( const_cast<real_type*>(DuDxlxlp_ptr), nU, nXLP, nU );
    MatrixWrapper<real_type> DaDxlxlp( a, nR, nCOL, nR );
    MatrixWrapper<real_type> DcDxlxlp( c, this->dim_Pars(), nCOL, this->dim_Pars() );

    this->DacDxlxlp_eval( n_thread, L, R, P, U, DuDxlxlp, DaDxlxlp, DcDxlxlp );

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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('hc', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, omega ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA( arg_in_11 );

    real_type * h = createMatrixValue( arg_out_0, 2*this->dim_X(), 1 );
    real_type * c = createMatrixValue( arg_out_1, this->dim_Pars(), 1 );

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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('DhcDxlxlop', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, omega ): "

    CHECK_IN_OUT( 12, 2 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA( arg_in_11 );

    mwSize nCOL = 4*this->dim_X()+this->dim_Pars();
    mwSize nR   = 2*this->dim_X();
    real_type * h = createMatrixValue( arg_out_0, nR, nCOL );
    real_type * c = createMatrixValue( arg_out_1, this->dim_Pars(), nCOL );

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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('u', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ): "

    CHECK_IN_OUT( 11, 1 );

    mwSize nCOL;
    Mechatronix::U_solver & US = this->m_U_control_solver[0];

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );

    U_pointer_type U( createMatrixValue( arg_out_0, this->dim_U(), 1 ) );
    if ( m_U_solve_iterative ) {
      this->u_guess_eval( L, R, P, U );
      US.eval( L, R, P, U, U );
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
  ) {
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
    real_type * DuDxlxlp_ptr = createMatrixValue( arg_out_0, this->dim_U(), nCOL );

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
    N.i_segment = integer( getInt( arg_in_2, fmt::format( "{} i_segment", msg ) ) );
    UTILS_ASSERT(
      N.i_segment >= 0 && N.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, N.i_segment, this->num_segments()
    );

    // -------------------
    N.q = getVectorPointer( arg_in_3, nQ, fmt::format( "{} argument q", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    N.x = getVectorPointer( arg_in_4, nX, fmt::format( "{} argument x", msg ) );
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
  ) {
    #define CMD MODEL_NAME "_Mex('rhs_ode', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_type * rhs = createMatrixValue( arg_out_0, this->rhs_ode_numEqns(), 1 );
    this->rhs_ode_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_Drhs_odeDx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('Drhs_odeDx', i_seg, obj, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( Drhs_odeDx, N, U, P );
    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_Drhs_odeDu(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('Drhs_odeDu', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( Drhs_odeDu, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_Drhs_odeDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('Drhs_odeDp', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( Drhs_odeDp, N, U, P );

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
  ) {
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
  ) {
    #define CMD MODEL_NAME "_Mex('eta', obj, i_seg, q, x, lambda, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_6 );

    real_type * rhs = createMatrixValue( arg_out_0, this->eta_numEqns(), 1 );
    this->eta_eval( N, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DetaDx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DetaDx', obj, i_seg, q, x, lambda, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DetaDx, N, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DetaDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DetaDp', obj, i_seg, q, lambda, x, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DetaDp, N, P );

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
  ) {
    #define CMD MODEL_NAME "_Mex('nu', obj, i_seg, q, x, V, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    real_type * rhs = createMatrixValue( arg_out_0, this->nu_numEqns(), 1 );
    this->nu_eval( N, V, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DnuDx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DnuDx', obj, i_seg, q, x, V, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DnuDx, N, V, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DnuDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DnuDp', obj, i_seg, q, x, V, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    RETURN_SPARSE( DnuDp, N, V, P );

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
  ) {
    #define CMD MODEL_NAME "_Mex('Hx', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    real_type * rhs = createMatrixValue( arg_out_0, this->Hx_numEqns(), 1 );
    this->Hx_eval( N, V, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHxDx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DHxDx', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DHxDx, N, V, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHxDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DHxDp', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DHxDp, N, V, U, P );

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
  ) {
    #define CMD MODEL_NAME "_Mex('Hu', obj, i_seg, q, x, lambda, u, pars ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_6 );
    GET_ARG_P( arg_in_7 );

    real_type * rhs = createMatrixValue( arg_out_0, this->Hu_numEqns(), 1 );
    this->Hu_eval( N, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHuDx(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DHuDx', obj, i_seg, q, x, lambda, u, pars ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_6 );
    GET_ARG_P( arg_in_7 );

    RETURN_SPARSE( DHuDx, N, U, P );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHuDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DHuDp', obj, i_seg, q, x, lambda, u, pars ): "

    CHECK_IN_OUT( 8, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_6 );
    GET_ARG_P( arg_in_7 );

    RETURN_SPARSE( DHuDp, N, U, P );

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
  ) {
    #define CMD MODEL_NAME "_Mex('Hp', obj, i_seg, q, x, lambda, V, u, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType2 N;
    get_N( CMD, nrhs, prhs, N );

    GET_ARG_V( arg_in_6 );
    GET_ARG_U( arg_in_7 );
    GET_ARG_P( arg_in_8 );

    real_type * rhs = createMatrixValue( arg_out_0, this->Hp_numEqns(), 1 );
    this->Hp_eval( N, V, U, P, rhs );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DHpDp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
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

    mwSize nQ, nX, nL;

    // -------------------
    L.i_segment = integer( getInt( arg_in_2, fmt::format( "{} L_segment", msg ) ) );
    UTILS_ASSERT(
      L.i_segment >= 0 && L.i_segment < this->num_segments(),
      "{} iseg_L = {} expected to be in [0,{})\n",
      msg, L.i_segment, this->num_segments()
    );

    // -------------------
    L.q = getVectorPointer( arg_in_3, nQ, fmt::format( "{} argument q_L", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_L| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    L.x = getVectorPointer( arg_in_4, nX, fmt::format( "{} argument x_L", msg ) );
    UTILS_ASSERT(
      nX == this->dim_X(),
      "{} |x_L| = {} expected to be {}\n",
      msg, nX, this->dim_X()
    );

    // -------------------
    R.i_segment = integer( getInt( arg_in_5, fmt::format( "{} R_segment", msg ) ) );
    UTILS_ASSERT(
      R.i_segment >= 0 && R.i_segment < this->num_segments(),
      "{} iseg_R = {} expected to be in [0,{})\n",
      msg, R.i_segment, this->num_segments()
    );

    // -------------------
    R.q = getVectorPointer( arg_in_6, nQ, fmt::format( "{} argument q_R", msg ) );
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "{} |q_R| = {} expected to be {}\n",
      msg, nQ, this->dim_Q()
    );

    // -------------------
    R.x = getVectorPointer( arg_in_7, nX, fmt::format( "{} argument x_R", msg ) );
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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('boundaryConditions', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    real_type * bc = createMatrixValue( arg_out_0, this->dim_BC(), 1 );

    this->boundaryConditions_eval( L, R, P, bc );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DboundaryConditionsDxxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DboundaryConditionsDxxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    RETURN_SPARSE( DboundaryConditionsDxxp, L, R, P );

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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('adjointBC', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ): "

    CHECK_IN_OUT( 12, 1 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA_FULL( arg_in_11 );

    real_type * res = createMatrixValue( arg_out_0, this->adjointBC_numEqns(), 1 );
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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('DadjointBCDxxp', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ): "

    CHECK_IN_OUT( 12, 1 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );
    GET_ARG_OMEGA_FULL( arg_in_11 );

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
  ) {
    #define CMD MODEL_NAME \
    "_Mex('jump', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ): "

    CHECK_IN_OUT( 11, 1 );

    NodeType2 L, R;
    get_LR2( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_10 );

    real_type * res = createMatrixValue( arg_out_0, this->jump_numEqns(), 1 );
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
  ) {
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
  do_penalties(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('penalties', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    setScalarValue( arg_out_0, this->penalties_eval( N, U, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_control_penalties(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('control_penalties', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    setScalarValue( arg_out_0, this->control_penalties_eval( N, U, P ) );

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
  ) {
    #define CMD MODEL_NAME "_Mex('lagrange_target', obj, i_seg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    setScalarValue( arg_out_0, this->lagrange_target( N, U, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DlagrangeDxup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DlagrangeDxup', obj, iseg, q, x, u, pars ): "

    CHECK_IN_OUT( 7, 1 );

    NodeType N;
    get_qx( CMD, nrhs, prhs, N );

    GET_ARG_U( arg_in_5 );
    GET_ARG_P( arg_in_6 );

    // Gradient is a row vector
    real_type * res = createMatrixValue( arg_out_0, 1, this->DlagrangeDxup_numEqns() );
    this->DlagrangeDxup_eval( N, U, P , res );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_mayer_target(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('mayer_target', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    setScalarValue( arg_out_0, this->mayer_target( L, R, P ) );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_DmayerDxxp(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('DmayerDxxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

    CHECK_IN_OUT( 9, 1 );

    NodeType L, R;
    get_LR( CMD, nrhs, prhs, L, R );
    GET_ARG_P( arg_in_8 );

    // Gradient is a row vector
    real_type * res = createMatrixValue( arg_out_0, 1, this->DmayerDxxp_numEqns() );
    this->DmayerDxxp_eval( L, R, P , res );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_mesh_functions(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('mesh_functions', obj, i_segment, s ): "

    CHECK_IN_OUT( 4, 1 );

    // -------------------
    integer i_segment = integer( getInt( arg_in_2, fmt::format( "{} i_segment", CMD ) ) );
    UTILS_ASSERT(
      i_segment >= 0 && i_segment < this->num_segments(),
      CMD "i_segment = {} expected to be in [0,{})\n",
      i_segment, this->num_segments()
    );

    // -------------------
    real_type s = getScalarValue( arg_in_3, fmt::format( "{} s", CMD ) );

    Q_pointer_type rhs( createMatrixValue( arg_out_0, this->dim_Q(), 1 ) );
    this->q_eval( i_segment, s, rhs );
    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_nodes(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('nodes', obj ): "

    CHECK_IN_OUT( 2, 1 );

    integer n = m_mesh_base->num_nodes();
    real_type * nodes = createMatrixValue( arg_out_0, n, 1 );

    for ( integer i = 0; i < n; ++i ) nodes[i] = m_mesh_base->ss_node( i );

    #undef CMD
  }

  // --------------------------------------------------------------------------

  void
  do_node_to_segment(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('node_to_segment', obj ): "

    CHECK_IN_OUT( 2, 1 );

    integer n = m_mesh_base->num_nodes();
    int32_t * node_to_segment = createMatrixInt32( arg_out_0, n, 1 );

    for ( integer i = 0; i < n; ++i )
      node_to_segment[i] = m_mesh_base->node_to_segment( i );

    #undef CMD
  }

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  void
  do_p(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_1(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_1', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_1(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_2(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_2', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_2(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_3(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_3', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_3(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_1_1(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_1_1', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_1_1(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_1_2(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_1_2', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_1_2(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_1_3(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_1_3', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_1_3(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_2_2(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_2_2', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_2_2(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_2_3(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_2_3', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_2_3(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_p_D_3_3(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('p_D_3_3', obj, xo__t, xo__a, xo__b ): "
    CHECK_IN_OUT( 5, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );
    mwSize N1, M1;
    real_type const * arg1 = getMatrixPointer( arg_in_3, N1, M1, CMD " xo__a" );
    MEX_CHECK_DIMS(N1,M1,N0,M0);
    mwSize N2, M2;
    real_type const * arg2 = getMatrixPointer( arg_in_4, N2, M2, CMD " xo__b" );
    MEX_CHECK_DIMS(N2,M2,N0,M0);

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->p_D_3_3(arg0[ii],arg1[ii],arg2[ii]);
    #undef CMD
  }

  void
  do_q(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('q', obj, xo__t ): "
    CHECK_IN_OUT( 3, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->q(arg0[ii]);
    #undef CMD
  }

  void
  do_q_D(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('q_D', obj, xo__t ): "
    CHECK_IN_OUT( 3, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->q_D(arg0[ii]);
    #undef CMD
  }
  void
  do_q_DD(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('q_DD', obj, xo__t ): "
    CHECK_IN_OUT( 3, 1 );
    mwSize N0, M0;
    real_type const * arg0 = getMatrixPointer( arg_in_2, N0, M0, CMD " xo__t" );

    real_type * res = createMatrixValue( arg_out_0, N0, M0 );
    for ( mwSize ii = 0; ii < N0*M0; ++ii )
      res[ii] = this->q_DD(arg0[ii]);
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

static ThreadPool * pTP      = nullptr;
static Console    * pConsole = nullptr;

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
  MEX_ASSERT( mxIsChar(arg_in_1), CMD "second argument must be a string" );
  ProblemStorage * ptr = new ProblemStorage( mxArrayToString(arg_in_1), pTP, pConsole );
  arg_out_0 = convertPtr2Mat<ProblemStorage>(ptr);
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
do_infoLevel(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('infoLevel',obj,infoL): "
  CHECK_IN_OUT( 3, 0 );
  int64_t ilev = getInt( arg_in_2, CMD " infoL" );
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
  int64_t N_threads = getInt( arg_in_2, CMD " nt" );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->
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
  destroyObject<ProblemStorage>( arg_in_1 );
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
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('read',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_read( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_setup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('setup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_setup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_remesh(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('remesh',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_remesh( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_set_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('set_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_set_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution_as_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution_as_guess',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_solution_as_guess( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_solve(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('solve',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_solve( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_dims(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('dims',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_dims( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_names(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('names',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_names( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_update_continuation(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('update_continuation',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_update_continuation( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_set_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('set_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_set_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_check_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('check_raw_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_check_raw_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_check_jacobian(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('check_jacobian',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_check_jacobian( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_solution( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_solution2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_solution3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_solution3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_solution3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_get_ocp_data(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('get_ocp_data',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_get_ocp_data( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_init_U(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('init_U',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_init_U( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_U(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_U',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_eval_U( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_F(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_F',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_eval_F( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_JF(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_JF',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_eval_JF( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eval_JF_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('eval_JF_pattern',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_eval_JF_pattern( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_pack(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('pack',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_pack( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_unpack(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('unpack',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_unpack( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_ac(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('ac',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_ac( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DacDxlxlp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DacDxlxlp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DacDxlxlp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_hc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('hc',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_hc( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DhcDxlxlop(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DhcDxlxlop',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DhcDxlxlop( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_u(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('u',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_u( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DuDxlxlp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DuDxlxlp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DuDxlxlp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_rhs_ode(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('rhs_ode',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_rhs_ode( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Drhs_odeDx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Drhs_odeDx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Drhs_odeDx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Drhs_odeDu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Drhs_odeDu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Drhs_odeDu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Drhs_odeDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Drhs_odeDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Drhs_odeDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_A(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('A',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_A( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_eta(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('eta',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_eta( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DetaDx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DetaDx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DetaDx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DetaDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DetaDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DetaDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_nu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('nu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_nu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DnuDx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DnuDx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DnuDx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DnuDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DnuDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DnuDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Hx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHxDx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHxDx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DHxDx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHxDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHxDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DHxDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hu',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Hu( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHuDx(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHuDx',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DHuDx( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHuDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHuDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DHuDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_Hp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('Hp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_Hp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DHpDp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DHpDp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DHpDp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_boundaryConditions(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('boundaryConditions',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_boundaryConditions( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DboundaryConditionsDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DboundaryConditionsDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DboundaryConditionsDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_adjointBC(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('adjointBC',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_adjointBC( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DadjointBCDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DadjointBCDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DadjointBCDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_jump(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('jump',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_jump( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DjumpDxlxlp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DjumpDxlxlp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DjumpDxlxlp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_penalties(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('penalties',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_penalties( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_control_penalties(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('control_penalties',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_control_penalties( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_lagrange_target(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('lagrange_target',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_lagrange_target( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DlagrangeDxup(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DlagrangeDxup',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DlagrangeDxup( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_mayer_target(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('mayer_target',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_mayer_target( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_DmayerDxxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('DmayerDxxp',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_DmayerDxxp( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_mesh_functions(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('mesh_functions',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_mesh_functions( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_nodes(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('nodes',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_nodes( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_node_to_segment(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('node_to_segment',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_node_to_segment( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_1_1(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_1_1',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_1_1( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_1_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_1_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_1_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_1_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_1_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_1_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_2_2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_2_2',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_2_2( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_2_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_2_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_2_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_p_D_3_3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('p_D_3_3',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_p_D_3_3( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_q(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('q',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_q( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_q_D(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('q_D',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_q_D( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_q_DD(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('q_DD',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->do_q_DD( nlhs, plhs, nrhs, prhs );
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
  {"unpack",do_unpack},
  {"ac",do_ac},
  {"DacDxlxlp",do_DacDxlxlp},
  {"hc",do_hc},
  {"DhcDxlxlop",do_DhcDxlxlop},
  {"u",do_u},
  {"DuDxlxlp",do_DuDxlxlp},
  {"rhs_ode",do_rhs_ode},
  {"Drhs_odeDx",do_Drhs_odeDx},
  {"Drhs_odeDu",do_Drhs_odeDu},
  {"Drhs_odeDp",do_Drhs_odeDp},
  {"A",do_A},
  {"eta",do_eta},
  {"DetaDx",do_DetaDx},
  {"DetaDp",do_DetaDp},
  {"nu",do_nu},
  {"DnuDx",do_DnuDx},
  {"DnuDp",do_DnuDp},
  {"Hx",do_Hx},
  {"DHxDx",do_DHxDx},
  {"DHxDp",do_DHxDp},
  {"Hu",do_Hu},
  {"DHuDx",do_DHuDx},
  {"DHuDp",do_DHuDp},
  {"Hp",do_Hp},
  {"DHpDp",do_DHpDp},
  {"boundaryConditions",do_boundaryConditions},
  {"DboundaryConditionsDxxp",do_DboundaryConditionsDxxp},
  {"adjointBC",do_adjointBC},
  {"DadjointBCDxxp",do_DadjointBCDxxp},
  {"jump",do_jump},
  {"DjumpDxlxlp",do_DjumpDxlxlp},
  {"penalties",do_penalties},
  {"control_penalties",do_control_penalties},
  {"lagrange_target",do_lagrange_target},
  {"DlagrangeDxup",do_DlagrangeDxup},
  {"mayer_target",do_mayer_target},
  {"DmayerDxxp",do_DmayerDxxp},
  {"mesh_functions",do_mesh_functions},
  {"nodes",do_nodes},
  {"node_to_segment",do_node_to_segment},
  {"p",do_p},
  {"p_D_1",do_p_D_1},
  {"p_D_2",do_p_D_2},
  {"p_D_3",do_p_D_3},
  {"p_D_1_1",do_p_D_1_1},
  {"p_D_1_2",do_p_D_1_2},
  {"p_D_1_3",do_p_D_1_3},
  {"p_D_2_2",do_p_D_2_2},
  {"p_D_2_3",do_p_D_2_3},
  {"p_D_3_3",do_p_D_3_3},
  {"q",do_q},
  {"q_D",do_q_D},
  {"q_DD",do_q_DD},
  {"new",do_new},
  {"infoLevel",do_infoLevel},
  {"set_max_threads",do_set_max_threads},
  {"help",do_help},
  {"delete",do_delete}
};

void
mexFunction(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {

  if ( pTP      == nullptr ) pTP      = new ThreadPool(std::thread::hardware_concurrency());
  if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);

  pConsole->setOff();

  try {
    MEX_ASSERT( nrhs > 0, MODEL_NAME "_Mex: Missing Arguments!" );
    MEX_ASSERT( mxIsChar(arg_in_0), MODEL_NAME "_Mex: First argument must be a string" );
    string cmd = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun( nlhs, plhs, nrhs, prhs );
  }
  catch ( std::out_of_range const & exc ) {
    mexErrMsgTxt( fmt::format( "AlpRider_Mex, unknown command: {}", exc.what() ).c_str() );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt( fmt::format( "AlpRider_Mex, error: {}", exc.what() ).c_str() );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
