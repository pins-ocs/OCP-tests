/*-----------------------------------------------------------------------*\
 |  file: HyperSensitive_Mex.cc                                          |
 |                                                                       |
 |  version: 1.0   date 12/11/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
#include "HyperSensitive.hh"
#include "HyperSensitive_Pars.hh"
#include <sstream>

#include "mex_utils.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace HyperSensitiveLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;

/*
// redirect stdout, found at
// https://it.mathworks.com/matlabcentral/answers/132527-in-mex-files-where-does-output-to-stdout-and-stderr-go
*/

#ifdef MECHATRONIX_OS_LINUX

class mystream : public std::streambuf {
protected:
  virtual
  std::streamsize
  xsputn(const char *s, std::streamsize n) override
  { mexPrintf("%.*s", n, s); mexEvalString("drawnow;"); return n; }

  virtual
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
"\n"
"Mex command has the following possible calls:\n"
"\n"
"  - HyperSensitive_Mex('setup', mstruct):\n"
"    initialise the problem with a matlab structure 'mstruct'\n"
"\n"
"  - HyperSensitive_Mex('solve'):\n"
"    solve the optimal control problem and store internally\n"
"    the solution found.\n"
"\n"
"  To get the solution there are various calling sequence:\n"
"  - sol = HyperSensitive_Mex('get_solution'):\n"
"    return the full solution as a matlab structure also with solver\n"
"    information (e.g. iteration taken, convergence, etc).\n"
"\n"
"  - sol1, sol2, ..., solN = HyperSensitive_Mex('get_solution',{var_nm}):\n"
"    return the full solution as a vector only for the desired variable\n"
"    'var_nm' or listed in the cell array {var_num}.\n"
"\n"
"  - sol = HyperSensitive_Mex('get_solution',t):\n"
"    return the solution as a vector for all output variables at desired\n"
"    instant 't'. 't' can be a vector or a scalar.\n"
"\n"
"  - sol1, sol2, ..., solN = HyperSensitive_Mex('get_solution',t,{var_nm}):\n"
"    return the solution as a matlab matrix for all output variables\n"
"    listed in the cell array {var_num} at instant 't'.%\n"
"    't' can be a vector or a scalar.\n"
"%===========================================================================%\n"
;

#define MODEL_NAME  "HyperSensitive"
#define MODEL_CLASS HyperSensitive

#define CHECK_IN(N) \
  MEX_ASSERT2( nrhs == N, CMD "Expected {} argument(s), nrhs = {}\n", N, nrhs )

#define CHECK_OUT(N) \
  MEX_ASSERT2( nlhs == N, CMD "Expected {} argument(s), nlhs = {}\n", N, nlhs )

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
  bool solution_ok;

  GenericContainer gc_data, gc_solution;

  // user defined Object instances (external)

  MeshStd              mesh;

public:

  using MODEL_CLASS::guess;

  ProblemStorage( std::string const & cname, ThreadPool * pTP, Console * pConsole )
  : MODEL_CLASS(cname,pTP,pConsole)
  , setup_ok(false)
  , guess_ok(false)
  , solve_ok(false)
  , solution_ok(false)
  // user defined Object instances (external)

  , mesh( "mesh" )
  {}

  ~ProblemStorage() {}

  void
  doneSetup() {
    setup_ok    = true;
    guess_ok    = false;
    solve_ok    = false;
    solution_ok = false;
  }

  void
  doneGuess() {
    setup_ok    = true;
    guess_ok    = true;
    solve_ok    = false;
    solution_ok = false;
  }

  void
  doneSolve() {
    setup_ok    = true;
    guess_ok    = true;
    solve_ok    = true;
    solution_ok = false;
  }

  void
  diagnostic()
  { MODEL_CLASS::diagnostic( gc_data ); }

  integer nnz() const { return MODEL_CLASS::eval_JF_nnz(); }

  void
  read( string const & fname, GenericContainer & gc ) {
    MEX_ASSERT2(
      Mechatronix::checkIfFileExists( fname.c_str() ),
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
  mex_read(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('read',obj,filename): "
    CHECK_IN(3);
    CHECK_OUT(1);
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
  mex_setup(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('setup',obj,struct_or_filename): "
    CHECK_IN(3);
    CHECK_OUT(0);
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

    this->doneSetup();

    #undef CMD
  }

  /*\
   |  _ __  _____ __   __ _ _  _ ___ ______
   | | '  \/ -_) \ /  / _` | || / -_|_-<_-<
   | |_|_|_\___/_\_\__\__, |\_,_\___/__/__/
   |              |___|___/
  \*/
  void
  mex_set_guess(
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
      gc_guess["initialize"] = "zero";
      gc_guess["guess_type"] = "default";
    } else {
      // sovrascrive guess nei dati del problema
      mxArray_to_GenericContainer( arg_in_2, gc_guess );
    }
    MODEL_CLASS::guess( gc_guess );
    this->doneGuess();
    #undef CMD
  }

  void
  mex_get_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_guess',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'guess'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );
    GenericContainer_to_mxArray( gc_data("Guess"), arg_out_0 );
    #undef CMD
  }

  void
  mex_get_solution_as_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution_as_guess',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'get_solution_as_guess'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );
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
  mex_solve(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('solve',obj[,timeout]): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'solve'" );
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
    this->doneSolve();
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
  mex_dims(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('dims',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'dims'" );
    CHECK_IN( 2 );
    CHECK_OUT( 1 );
    GenericContainer gc;
    gc["dim_q"]     = MODEL_CLASS::dim_Q();
    gc["dim_x"]     = MODEL_CLASS::dim_X();
    gc["dim_u"]     = MODEL_CLASS::dim_U();
    gc["dim_pars"]  = MODEL_CLASS::dim_Pars();
    gc["dim_omega"] = MODEL_CLASS::dim_Omega();
    gc["dim_bc"]    = MODEL_CLASS::dim_BC();
    gc["num_nodes"] = MODEL_CLASS::nNodes();
    gc["neq"]       = MODEL_CLASS::numEquations();
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
  mex_names(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('names',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'names'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );
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
  mex_updateContinuation(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('updateContinuation',obj,nphase,s): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'updateContinuation'" );
    CHECK_IN( 4 ); CHECK_OUT( 0 );
    int64_t nphase = getInt( arg_in_2, CMD " nphase number" );
    real_type s    = getScalarValue( arg_in_3, CMD " s" );
    this->updateContinuation( nphase, s );
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
  mex_get_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_raw_solution',obj): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'get_raw_solution'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );
    real_type * x = createMatrixValue( arg_out_0, this->numEquations(), 1 );
    this->get_raw_solution( x );
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
  mex_set_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('set_raw_solution',obj,x): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'set_raw_solution'" );
    CHECK_IN( 3 ); CHECK_OUT( 0 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x");
    MEX_ASSERT2(
      dimx == mwSize(this->numEquations()),
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, this->numEquations()
    );
    this->set_raw_solution( x );
    this->doneGuess(); // is equivalent to set guess
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
  mex_check_raw_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('check_raw_solution',obj,x): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'check_raw_solution'" );
    CHECK_IN( 3 ); CHECK_OUT( 1 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    MEX_ASSERT2(
      dimx == mwSize(this->numEquations()),
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, this->numEquations()
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
  mex_check_jacobian(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('check_jacobian',obj,x,epsi): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'check_jacobian'" );
    CHECK_IN( 4 ); CHECK_OUT( 0 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    real_type epsi = getScalarValue( arg_in_3, CMD "argument epsi" );
    MEX_ASSERT2(
      dimx == mwSize(this->numEquations()),
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, this->numEquations()
    );
    this->checkJacobian(x,epsi);
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
  mex_get_solution(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_solution',obj[,column_name]): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'get_solution'" );
    CHECK_OUT( 1 );
    if ( !solution_ok ) {
      MODEL_CLASS::get_solution( gc_solution );
      solution_ok = true;
    }
    if ( nrhs == 2 ) {
      GenericContainer_to_mxArray( gc_solution, arg_out_0 );
    } else if ( nrhs == 3 ) {
      MEX_ASSERT( mxIsChar(arg_in_2), CMD " Third argument must be a string" );
      string const & cname = mxArrayToString(arg_in_2);
      GenericContainer const & idx = gc_solution("idx");
      MEX_ASSERT2(
        idx.exists(cname),
        CMD "data column `{}` do not exists", cname
      );
      integer icol = idx(cname).get_as_int();
      GenericContainer::mat_real_type const & data = gc_solution("data").get_mat_real();
      double * res = createMatrixValue( arg_out_0, data.numRows(), 1 );
      data.getColumn( icol, res );
    } else {
      MEX_ERROR2( CMD "use 2 or 3 arguments, nrhs = {}\n", nrhs );
    }
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
  mex_get_ocp_data(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('get_ocp_data',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'get_ocp_data'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );
    GenericContainer_to_mxArray( gc_data, arg_out_0 );
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
  mex_eval_F(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('eval_F',obj,x): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'eval_F'" );
    CHECK_IN( 3 ); CHECK_OUT( 1 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    MEX_ASSERT2(
      dimx == mwSize(numEquations()),
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, numEquations()
    );
    real_type * f = createMatrixValue( arg_out_0, dimx, 1 );
    MODEL_CLASS::eval_F( x, f );
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
  mex_eval_JF(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('eval_JF',obj,x): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'eval_JF'" );
    CHECK_IN( 3 ); CHECK_OUT( 1 );

    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    MEX_ASSERT2(
      dimx == mwSize(numEquations()),
      CMD " size(x) = {} must be equal to neq = {}\n",
      dimx, numEquations()
    );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    real_type * V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );

    size_t nnz = size_t(MODEL_CLASS::eval_JF_nnz());
    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz );
    integer * i_row = mem( nnz );
    integer * j_col = mem( nnz );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]; J[i] = j_col[i];
    }

    MODEL_CLASS::eval_JF_values( x, V );
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD "failed the call sparse(...)" );
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
  mex_eval_JF_pattern(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('eval_JF_pattern',obj): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'eval_JF_pattern'" );
    CHECK_IN( 2 ); CHECK_OUT( 1 );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    real_type * V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );

    size_t nnz = size_t(MODEL_CLASS::eval_JF_nnz());
    Mechatronix::Malloc<integer> mem("mex_eval_JF");
    mem.allocate( 2*nnz );
    integer * i_row = mem( nnz );
    integer * j_col = mem( nnz );
    MODEL_CLASS::eval_JF_pattern( i_row, j_col, 1 );
    for ( size_t i = 0; i < nnz; ++i ) {
      I[i] = i_row[i]; J[i] = j_col[i]; V[i] = 1;
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
  mex_pack(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('pack',obj,x,lambda,pars,omega): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'pack'" );
    CHECK_IN( 7 ); CHECK_OUT( 1 );

    mwSize nrX, ncX, nrL, ncL, nP, nO, nrU, ncU;
    X_const_pointer_type     X(getMatrixPointer( arg_in_2, nrX, ncX, CMD "argument x" ));
    L_const_pointer_type     L(getMatrixPointer( arg_in_3, nrL, ncL, CMD "argument lambda" ));
    P_const_pointer_type     P(getVectorPointer( arg_in_4, nP,       CMD "argument pars" ));
    OMEGA_const_pointer_type O(getVectorPointer( arg_in_5, nO,       CMD "argument omega" ));
    U_const_pointer_type     U(getMatrixPointer( arg_in_6, nrU, ncU, CMD "argument U" ));
    integer nn = this->nNodes();
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
    UTILS_ASSERT(
      nrU == mwSize(this->dim_U()) && ncU == nn-1,
      "{} size(u) = {} x {} expected to be {} x {}\n",
      CMD, nrU, ncU, this->dim_U(), nn-1
    );
    real_type * Z = createMatrixValue( arg_out_0, 1, this->numEquations() );
    this->pack( X, L, P, O, U, Z );
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
  mex_unpack(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('unpack',obj,Z): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'unpack'" );
    CHECK_IN( 3 ); CHECK_OUT( 5 );

    integer nn = this->nNodes();
    mwSize nZ;
    real_type const * Z = getVectorPointer( arg_in_2, nZ, CMD "argument Z" );
    UTILS_ASSERT(
      nZ == mwSize(this->numEquations()),
      "{} length(Z) = {} expected to be {}\n",
      CMD, nZ, this->numEquations()
    );

    X_pointer_type     X(createMatrixValue( arg_out_0, this->dim_X(), nn ));
    L_pointer_type     L(createMatrixValue( arg_out_1, this->dim_X(), nn ));
    P_pointer_type     P(createMatrixValue( arg_out_2, 1, this->dim_Pars() ));
    OMEGA_pointer_type O(createMatrixValue( arg_out_3, 1, this->dim_Omega() ));
    U_pointer_type     U(createMatrixValue( arg_out_4, this->dim_U(), nn-1 ));

    this->unpack( Z, X, L, P, O, U );
    #undef CMD
  }

  /*\
   |   _ __  _____ __  __ _
   |  | '  \/ -_) \ / / _` |
   |  |_|_|_\___/_\_\_\__,_|
   |               |___|
  \*/
  void
  mex_a(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('a', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "
    CHECK_IN( 12 );
    CHECK_OUT( 2 );

    mwSize nQ, nX, nL, nP, nU;
    Q_const_pointer_type QL(getVectorPointer( arg_in_3, nQ, CMD "argument q_L" ));
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "|q_L| = {} expected to be {}\n", CMD, nQ, this->dim_Q()
    );
    X_const_pointer_type XL(getVectorPointer( arg_in_4, nX, CMD "argument x_L" ));
    UTILS_ASSERT(
      nX == this->dim_X(),
      "|x_L| = {} expected to be {}\n", CMD, nX, this->dim_X()
    );

    L_const_pointer_type LL(getVectorPointer( arg_in_5, nL, CMD "argument lambda_L" ));
    UTILS_ASSERT(
      nL == this->dim_X(),
      "|lambda_L| = {} expected to be {}\n", CMD, nL, this->dim_X()
    );

    Q_const_pointer_type QR(getVectorPointer( arg_in_7, nQ, CMD "argument q_R" ));
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "|q_R| = {} expected to be {}\n", CMD, nQ, this->dim_Q()
    );

    X_const_pointer_type XR(getVectorPointer( arg_in_8, nX, CMD "argument x_R" ));
    UTILS_ASSERT(
      nX == this->dim_X(),
      "|x_R| = {} expected to be {}\n", CMD, nX, this->dim_X()
    );

    L_const_pointer_type LR(getVectorPointer( arg_in_9, nL, CMD "argument lambda_R" ));
    UTILS_ASSERT(
      nL == this->dim_X(),
      "|lambda_R| = {} expected to be {}\n", CMD, nL, this->dim_X()
    );

    P_const_pointer_type P(getVectorPointer( arg_in_10, nP, CMD "argument pars" ));
    UTILS_ASSERT(
      nP == this->dim_Pars(),
      "|pars| = {} expected to be {}\n", CMD, nP, this->dim_Pars()
    );

    U_const_pointer_type U(getVectorPointer( arg_in_11, nU, CMD "argument U" ));
    UTILS_ASSERT(
      nU == this->dim_U(),
      "|U| = {} expected to be {}\n", CMD, nU, this->dim_U()
    );

    integer n_thread = 0;
    integer L_i_segment = integer( getInt( arg_in_2, CMD " L_segment" ) );
    integer R_i_segment = integer( getInt( arg_in_6, CMD " R_segment" ) );

    UTILS_ASSERT(
      L_i_segment >= 0 && L_i_segment < this->nNodes(),
      "iseg_L = {} expected to be in [0,{})\n", CMD, L_i_segment, this->nNodes()
    );

    UTILS_ASSERT(
      R_i_segment >= 0 && R_i_segment < this->nNodes(),
      "iseg_R = {} expected to be in [0,{})\n", CMD, R_i_segment, this->nNodes()
    );

    NodeType2 L;
    L.i_segment = L_i_segment;
    L.q         = QL.pointer();
    L.x         = XL.pointer();
    L.lambda    = LL.pointer();
    NodeType2 R;
    R.i_segment = R_i_segment;
    R.q         = QR.pointer();
    R.x         = XR.pointer();
    R.lambda    = LR.pointer();

    double * a = createMatrixValue( arg_out_0, 2*this->dim_X(), 1 );
    double * c = createMatrixValue( arg_out_1, this->dim_Pars(), 1 );

    this->ac_eval( n_thread, L, R, P, U, a, c );

    // void
    // DacDxlp_eval(
    //   integer                    n_thread,
    //   integer                    i_cell,
    //   NodeType2 const          & L,
    //   NodeType2 const          & R,
    //   P_const_pointer_type       p,
    //   U_const_pointer_type       uM, // passato da altro calcolo
    //   MatrixWrapper<real_type> & DaDxlp,
    //   MatrixWrapper<real_type> & DcDxlp
    // ) const;

    #undef CMD
  }

  void
  mex_hc(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('hc', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, omega ): "
    CHECK_IN( 12 );
    CHECK_OUT( 2 );

    mwSize nQ, nX, nL, nP, nO;
    Q_const_pointer_type QL(getVectorPointer( arg_in_3, nQ, CMD "argument q_L" ));
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "|q_L| = {} expected to be {}\n", CMD, nQ, this->dim_Q()
    );
    X_const_pointer_type XL(getVectorPointer( arg_in_4, nX, CMD "argument x_L" ));
    UTILS_ASSERT(
      nX == this->dim_X(),
      "|x_L| = {} expected to be {}\n", CMD, nX, this->dim_X()
    );

    L_const_pointer_type LL(getVectorPointer( arg_in_5, nL, CMD "argument lambda_L" ));
    UTILS_ASSERT(
      nL == this->dim_X(),
      "|lambda_L| = {} expected to be {}\n", CMD, nL, this->dim_X()
    );

    Q_const_pointer_type QR(getVectorPointer( arg_in_7, nQ, CMD "argument q_R" ));
    UTILS_ASSERT(
      nQ == this->dim_Q(),
      "|q_R| = {} expected to be {}\n", CMD, nQ, this->dim_Q()
    );

    X_const_pointer_type XR(getVectorPointer( arg_in_8, nX, CMD "argument x_R" ));
    UTILS_ASSERT(
      nX == this->dim_X(),
      "|x_R| = {} expected to be {}\n", CMD, nX, this->dim_X()
    );

    L_const_pointer_type LR(getVectorPointer( arg_in_9, nL, CMD "argument lambda_R" ));
    UTILS_ASSERT(
      nL == this->dim_X(),
      "|lambda_R| = {} expected to be {}\n", CMD, nL, this->dim_X()
    );

    P_const_pointer_type P(getVectorPointer( arg_in_10, nP, CMD "argument pars" ));
    UTILS_ASSERT(
      nP == this->dim_Pars(),
      "|pars| = {} expected to be {}\n", CMD, nP, this->dim_Pars()
    );

    OMEGA_const_pointer_type Omega(getVectorPointer( arg_in_11, nO, CMD "argument omega" ));
    UTILS_ASSERT(
      nP == this->dim_Omega(),
      "|omega| = {} expected to be {}\n", CMD, nP, this->dim_Pars()
    );

    integer n_thread = 0;
    integer L_i_segment = integer( getInt( arg_in_2, CMD " L_segment" ) );
    integer R_i_segment = integer( getInt( arg_in_6, CMD " R_segment" ) );

    UTILS_ASSERT(
      L_i_segment >= 0 && L_i_segment < this->nNodes(),
      "iseg_L = {} expected to be in [0,{})\n", CMD, L_i_segment, this->nNodes()
    );

    UTILS_ASSERT(
      R_i_segment >= 0 && R_i_segment < this->nNodes(),
      "iseg_R = {} expected to be in [0,{})\n", CMD, R_i_segment, this->nNodes()
    );

    NodeType2 L;
    L.i_segment = L_i_segment;
    L.q         = QL.pointer();
    L.x         = XL.pointer();
    L.lambda    = LL.pointer();
    NodeType2 R;
    R.i_segment = R_i_segment;
    R.q         = QR.pointer();
    R.x         = XR.pointer();
    R.lambda    = LR.pointer();

    double * h = createMatrixValue( arg_out_0, 2*this->dim_X(), 1 );
    double * c = createMatrixValue( arg_out_1, this->dim_Pars(), 1 );

    this->hc_eval( L, R, Omega, P, h, c );

    // void
    // DacDxlp_eval(
    //   integer                    n_thread,
    //   integer                    i_cell,
    //   NodeType2 const          & L,
    //   NodeType2 const          & R,
    //   P_const_pointer_type       p,
    //   U_const_pointer_type       uM, // passato da altro calcolo
    //   MatrixWrapper<real_type> & DaDxlp,
    //   MatrixWrapper<real_type> & DcDxlp
    // ) const;

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
  CHECK_IN(2);
  CHECK_OUT(1);
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
  CHECK_IN(1);
  CHECK_OUT(0);
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
  CHECK_IN( 3 );
  CHECK_OUT( 0 );
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
do_N_threads(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  #define CMD MODEL_NAME "_Mex('N_threads',obj,nt): "
  CHECK_IN( 3 );
  CHECK_OUT( 0 );
  int64_t N_threads = getInt( arg_in_2, CMD " nt" );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->
    set_N_threads( Mechatronix::numThreads_bound( N_threads ) );
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
  CHECK_IN(2);
  CHECK_OUT(0);
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_read( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_setup( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_set_guess( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_get_guess( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_get_solution_as_guess( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_solve( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_dims( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_names( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_updateContinuation(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('updateContinuation',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_updateContinuation( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_get_raw_solution( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_set_raw_solution( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_check_raw_solution( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_check_jacobian( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_get_solution( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_get_ocp_data( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_eval_F( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_eval_JF( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_eval_JF_pattern( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_pack( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_unpack( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static
void
do_a(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {
  MEX_ASSERT2(
    nrhs >= 2,
    MODEL_NAME "_Mex('a',...): Expected at least {} argument(s), nrhs = {}\n", nrhs
  );
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_a( nlhs, plhs, nrhs, prhs );
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
  convertMat2Ptr<ProblemStorage>(arg_in_1)->mex_hc( nlhs, plhs, nrhs, prhs );
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
static std::map<std::string,DO_CMD> cmd_to_fun = {
  {"read",do_read},
  {"setup",do_setup},
  {"set_guess",do_set_guess},
  {"get_guess",do_get_guess},
  {"get_solution_as_guess",do_get_solution_as_guess},
  {"solve",do_solve},
  {"dims",do_dims},
  {"names",do_names},
  {"updateContinuation",do_updateContinuation},
  {"get_raw_solution",do_get_raw_solution},
  {"set_raw_solution",do_set_raw_solution},
  {"check_raw_solution",do_check_raw_solution},
  {"check_jacobian",do_check_jacobian},
  {"get_solution",do_get_solution},
  {"get_ocp_data",do_get_ocp_data},
  {"eval_F",do_eval_F},
  {"eval_JF",do_eval_JF},
  {"eval_JF_pattern",do_eval_JF_pattern},
  {"pack",do_pack},
  {"unpack",do_unpack},
  {"a",do_a},
  {"hc",do_hc},
  {"new",do_new},
  {"infoLevel",do_infoLevel},
  {"N_threads",do_N_threads},
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
    mexErrMsgTxt( fmt::format( "HyperSensitive_Mex, unknown command: {}", exc.what() ).c_str() );
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt( fmt::format( "HyperSensitive_Mex, error: {}", exc.what() ).c_str() );
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
