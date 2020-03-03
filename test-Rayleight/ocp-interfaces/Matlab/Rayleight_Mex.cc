/*-----------------------------------------------------------------------*\
 |  file: Rayleight_Mex.cc                                               |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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
#include "Rayleight.hh"
#include "Rayleight_Pars.hh"
#include <sstream>

#include "mex_utils.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace RayleightLoad;
using namespace GenericContainerNamespace;
using namespace MechatronixLoad;


static char const help_msg[] =
"%===========================================================================%\n"
"\n"
"Mex command has the following possible calls:\n"
"\n"
"  - Rayleight_Mex('setup', mstruct):\n"
"    initialise the problem with a matlab structure 'mstruct'\n"
"\n"
"  - Rayleight_Mex('solve'):\n"
"    solve the optimal control problem and store internally\n"
"    the solution found.\n"
"\n"
"  To get the solution there are various calling sequence:\n"
"  - sol = Rayleight_Mex('get_solution'):\n"
"    return the full solution as a matlab structure also with solver\n"
"    information (e.g. iteration taken, convergence, etc).\n"
"\n"
"  - sol1, sol2, ..., solN = Rayleight_Mex('get_solution',{var_nm}):\n"
"    return the full solution as a vector only for the desired variable\n"
"    'var_nm' or listed in the cell array {var_num}.\n"
"\n"
"  - sol = Rayleight_Mex('get_solution',t):\n"
"    return the solution as a vector for all output variables at desired\n"
"    instant 't'. 't' can be a vector or a scalar.\n"
"\n"
"  - sol1, sol2, ..., solN = Rayleight_Mex('get_solution',t,{var_nm}):\n"
"    return the solution as a matlab matrix for all output variables\n"
"    listed in the cell array {var_num} at instant 't'.%\n"
"    't' can be a vector or a scalar.\n"
"%===========================================================================%\n"
;

#define MODEL_NAME  "Rayleight"
#define MODEL_CLASS Rayleight

#define CHECK_IN(N) \
  MEX_ASSERT( nrhs == N, \
              CMD "Expected " << N << " argument(s), nrhs = "  << nrhs )

#define CHECK_OUT(N) \
  MEX_ASSERT( nlhs == N, \
              CMD "Expected " << N << " argument(s), nlhs = "  << nlhs )

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
    if ( fname.find_last_of(".rb") ) {
      Mechatronix::MrubyInterpreter mrb;
      MEX_ASSERT(
        mrb.load( fname.c_str() ) != EXIT_FAILURE,
        "Failed to load: ``" << fname << "''"
      );
      mrb.expr_to_GC( "Mechatronix.content", gc );
    } else if ( fname.find_last_of(".lua") ) {
      using GenericContainerNamespace::LuaInterpreter;
      LuaInterpreter lua;
      Mechatronix::lua_set_constants( lua );
      lua.do_file( fname.c_str() );
      lua.global_to_GC( "content", gc );
    } else {
      MEX_ASSERT(
        false,
        "unknown suffix for filename `" << fname << "` use `.rb` or `.lua`"
      );
    }
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
    MEX_ASSERT(
      mxIsChar(arg_in_2),
      CMD "filename must be a string, found " << mxGetClassName( arg_in_2 )
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
    if ( mxIsChar(arg_in_2) ) { // read from file
      string fname = mxArrayToString(arg_in_2);
      this->read( fname, gc_data );
    } else { // setup using MATLAB structure
      mxArray_to_GenericContainer( arg_in_2, gc_data );
    }


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    LW_ASSERT0(
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
  using MODEL_CLASS::guess;

  void
  mex_set_guess(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('set_guess',obj[,userguess]): "
    MEX_ASSERT( setup_ok, CMD "use 'setup' before to use 'set_guess'" );
    MEX_ASSERT( nrhs == 2 || nrhs == 3, CMD "Expected 2 or 3 input argument(s), nrhs = " << nrhs )
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
    CHECK_OUT( 1 );
    CHECK_IN( 2 );
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
    CHECK_OUT( 1 );
    CHECK_IN( 2 );
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
    #define CMD MODEL_NAME "_Mex('solve',obj): "
    MEX_ASSERT( guess_ok, CMD "use 'set_guess' before to use 'solve'" );
    CHECK_IN( 2 );
    CHECK_OUT( 1 );
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
    CHECK_IN( 2 );
    CHECK_OUT( 1 );
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
    CHECK_IN( 4 );
    CHECK_OUT( 0 );
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
    CHECK_IN( 2 );
    CHECK_OUT( 1 );
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
    CHECK_IN( 3 );
    CHECK_OUT( 0 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x");
    MEX_ASSERT(
      dimx == mwSize(this->numEquations()),
      CMD << " size(x) = " << dimx <<
      " must be equal to neq = " << this->numEquations()
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
    CHECK_IN( 3 );
    CHECK_OUT( 1 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    MEX_ASSERT(
      dimx == mwSize(this->numEquations()),
      CMD << " size(x) = " << dimx <<
      " must be equal to neq = " << this->numEquations()
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
    CHECK_IN( 4 );
    CHECK_OUT( 0 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
    real_type epsi = getScalarValue( arg_in_3, CMD "argument epsi" );
    MEX_ASSERT(
      dimx == mwSize(this->numEquations()),
      CMD << " size(x) = " << dimx <<
      " must be equal to neq = " << this->numEquations()
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
      MEX_ASSERT(
        idx.exists(cname),
        CMD << "data column `" << cname << "` do not exists"
      );
      integer icol = idx(cname).get_as_int();
      GenericContainer::mat_real_type const & data = gc_solution("data").get_mat_real();
      double * res = createMatrixValue( arg_out_0, data.numRows(), 1 );
      data.getColumn( icol, res );
    } else {
      MEX_ASSERT( false, CMD "use 2 or 3 arguments, nrhs = " << nrhs );
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
    CHECK_IN( 2 );
    CHECK_OUT( 1 );
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
    CHECK_IN( 3 );
    CHECK_OUT( 1 );
    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    MEX_ASSERT(
      dimx == mwSize(numEquations()),
      CMD << " size(x) = " << dimx <<
      " must be equal to neq = " << numEquations()
    );
    real_type * f = createMatrixValue( arg_out_0, dimx, 1 );
    MODEL_CLASS::eval_F( x, f );
    #undef CMD
  }

  void
  pattern( real_type I[], real_type J[] ) const {
    integer nnz = MODEL_CLASS::eval_JF_nnz();
    static std::vector<integer> i_row(nnz), j_col(nnz);
    MODEL_CLASS::eval_JF_pattern( &i_row.front(), &j_col.front(), 1 );
    for ( integer i = 0; i < nnz; ++i ) {
      I[i] = i_row[i];
      J[i] = j_col[i];
    }
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
    CHECK_IN( 3 );
    CHECK_OUT( 1 );

    mwSize dimx;
    real_type const * x = getVectorPointer( arg_in_2, dimx, CMD );
    MEX_ASSERT(
      dimx == mwSize(numEquations()),
      CMD << " size(x) = " << dimx <<
      " must be equal to neq = " << numEquations()
    );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    real_type * V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );
    pattern( I, J );
    MODEL_CLASS::eval_JF_values( x, V );
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD << "failed the call sparse(...)" );
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
    CHECK_IN( 2 );
    CHECK_OUT( 1 );

    mxArray *args[5];
    real_type * I = createMatrixValue( args[0], 1, nnz() );
    real_type * J = createMatrixValue( args[1], 1, nnz() );
    real_type * V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );
    pattern( I, J );
    std::fill( V, V+nnz(), 1 );
    int ok = mexCallMATLAB( 1, &arg_out_0, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, CMD << "failed the call sparse(...)" );
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
    CHECK_IN( 7 );
    CHECK_OUT( 1 );

    mwSize nrX, ncX, nrL, ncL, nP, nO, nrU, ncU;
    X_const_pointer_type     X(getMatrixPointer( arg_in_2, nrX, ncX, CMD "argument x" ));
    L_const_pointer_type     L(getMatrixPointer( arg_in_3, nrL, ncL, CMD "argument lambda" ));
    P_const_pointer_type     P(getVectorPointer( arg_in_4, nP,       CMD "argument pars" ));
    OMEGA_const_pointer_type O(getVectorPointer( arg_in_5, nO,       CMD "argument omega" ));
    U_const_pointer_type     U(getMatrixPointer( arg_in_6, nrU, ncU, CMD "argument U" ));
    integer nn = this->nNodes();
    LW_ASSERT(
      nrX == mwSize(this->dim_X()) && ncX == nn,
      "{} size(x) = {} x {} expected to be {} x {}\n",
      CMD, nrX, ncX, this->dim_X(), nn
    );
    LW_ASSERT(
      nrL == mwSize(this->dim_X()) && ncL == nn,
      "{} size(lambda) = {} x {} expected to be {} x {}\n",
      CMD, nrL, ncL, this->dim_X(), nn
    );
    LW_ASSERT(
      nP == mwSize(this->dim_Pars()),
      "{} length(pars) = {} expected to be {}\n",
      CMD, nP, this->dim_Pars()
    );
    LW_ASSERT(
      nO == mwSize(this->dim_Omega()),
      "{} length(omega) = {} expected to be {}\n",
      CMD, nO, this->dim_Omega()
    );
    LW_ASSERT(
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
    CHECK_IN( 3 );
    CHECK_OUT( 5 );

    integer nn = this->nNodes();
    mwSize nZ;
    real_type const * Z = getVectorPointer( arg_in_2, nZ, CMD "argument Z" );
    LW_ASSERT(
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
   |                  _       __     _                _
   |  _ __  _____ __ (_)_ _  / _|___| |   _____ _____| |
   | | '  \/ -_) \ / | | ' \|  _/ _ \ |__/ -_) V / -_) |
   | |_|_|_\___/_\_\_|_|_||_|_| \___/____\___|\_/\___|_|
   |              |___|
  \*/
  void
  mex_changeInfoLevel(
    int nlhs, mxArray       *plhs[],
    int nrhs, mxArray const *prhs[]
  ) {
    #define CMD MODEL_NAME "_Mex('infoLevel',obj,infoL): "
    CHECK_IN( 3 );
    CHECK_OUT( 0 );
    int64_t ilev = getInt( arg_in_2, CMD " infoL" );
    this->changeInfoLevel( ilev );
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

static
ProblemStorage *
DATA_NEW( mxArray * & mx_id, std::string const & name, ThreadPool * pTP, Console * pConsole ) {
  ProblemStorage * ptr = new ProblemStorage( name, pTP, pConsole );
  mx_id = convertPtr2Mat<ProblemStorage>(ptr);
  return ptr;
}

static
inline
ProblemStorage *
DATA_GET( mxArray const * & mx_id ) {
  return convertMat2Ptr<ProblemStorage>(mx_id);
}

static
void
DATA_DELETE( mxArray const * & mx_id ) {
  destroyObject<ProblemStorage>(mx_id);
}

/*\
 *                      _____                 _   _
 *  _ __ ___   _____  _|  ___|   _ _ __   ___| |_(_) ___  _ __
 * | '_ ` _ \ / _ \ \/ / |_ | | | | '_ \ / __| __| |/ _ \| '_ \
 * | | | | | |  __/>  <|  _|| |_| | | | | (__| |_| | (_) | | | |
 * |_| |_| |_|\___/_/\_\_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|
 *
\*/

typedef enum {
  CMD_NEW,
  CMD_HELP,
  CMD_DELETE,
  CMD_READ,
  CMD_SETUP,
  CMD_SET_GUESS,
  CMD_GET_GUESS,
  CMD_GET_SOLUTION_AS_GUESS,
  CMD_SOLVE,
  CMD_DIMS,
  CMD_NAMES,
  CMD_UPDATE_CONTINUATION,
  CMD_GET_RAW_SOLUTION,
  CMD_SET_RAW_SOLUTION,
  CMD_CHECK_RAW_SOLUTION,
  CMD_CHECK_JACOBIAN,
  CMD_GET_SOLUTION,
  CMD_GET_OCP_DATA,
  CMD_EVAL_F,
  CMD_EVAL_JF,
  CMD_EVAL_JF_PATTERN,
  CMD_PACK,
  CMD_UNPACK,
  CMD_INFO_LEVEL
} CMD_LIST;

static map<string,unsigned> cmd_to_idx = {
  {"new",CMD_NEW},
  {"help",CMD_HELP},
  {"delete",CMD_DELETE},
  {"read",CMD_READ},
  {"setup",CMD_SETUP},
  {"set_guess",CMD_SET_GUESS},
  {"get_guess",CMD_GET_GUESS},
  {"get_solution_as_guess",CMD_GET_SOLUTION_AS_GUESS},
  {"solve",CMD_SOLVE},
  {"dims",CMD_DIMS},
  {"names",CMD_NAMES},
  {"updateContinuation",CMD_UPDATE_CONTINUATION},
  {"get_raw_solution",CMD_GET_RAW_SOLUTION},
  {"set_raw_solution",CMD_SET_RAW_SOLUTION},
  {"check_raw_solution",CMD_CHECK_RAW_SOLUTION},
  {"check_jacobian",CMD_CHECK_JACOBIAN},
  {"get_solution",CMD_GET_SOLUTION},
  {"get_ocp_data",CMD_GET_OCP_DATA},
  {"eval_F",CMD_EVAL_F},
  {"eval_JF",CMD_EVAL_JF},
  {"eval_JF_pattern",CMD_EVAL_JF_PATTERN},
  {"pack",CMD_PACK},
  {"unpack",CMD_UNPACK},
  {"infoLevel",CMD_INFO_LEVEL}
};

void
mexFunction(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
) {

  static ThreadPool * pTP      = nullptr;
  static Console    * pConsole = nullptr;

  if ( pTP      == nullptr ) pTP      = new ThreadPool(std::thread::hardware_concurrency());
  if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);

  MEX_ASSERT(
    nrhs > 0,
    MODEL_NAME "_Mex: Missing Arguments!"
  );
  MEX_ASSERT(
    mxIsChar(arg_in_0),
    MODEL_NAME "_Mex: First argument must be a string"
  );

  try {

    string cmd = mxArrayToString(arg_in_0);

    ProblemStorage * ptr = nullptr;
    if ( cmd != "new" && cmd != "help" ) {
      MEX_ASSERT(
        nrhs > 1,
        MODEL_NAME "_Mex('" << cmd << "',...): " <<
        "expected at least 2 arguments, found nrhs = " << nrhs
      );
      ptr = DATA_GET(arg_in_1);
    }

    switch ( cmd_to_idx.at(cmd) ) {
    case CMD_NEW:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //   _ __   _____      __
      //  | '_ \ / _ \ \ /\ / /
      //  | | | |  __/\ V  V /
      //  |_| |_|\___| \_/\_/
      */
      #define CMD MODEL_NAME "_Mex('new',name): "
      CHECK_IN(2);
      CHECK_OUT(1);
      MEX_ASSERT(
        mxIsChar(arg_in_1), CMD "second argument must be a string"
      );
      ptr = DATA_NEW( arg_out_0, mxArrayToString(arg_in_1), pTP, pConsole );
      #undef CMD
      break;
    case CMD_HELP:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //   _          _
      //  | |__   ___| |_ __
      //  | '_ \ / _ \ | '_ \
      //  | | | |  __/ | |_) |
      //  |_| |_|\___|_| .__/
      //               |_|
      */
      #define CMD MODEL_NAME "_Mex('help'): "
      CHECK_IN(1);
      CHECK_OUT(0);
      mexPrintf( "%s", help_msg );
      #undef CMD
      break;
    case CMD_DELETE:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //       _      _      _
      //    __| | ___| | ___| |_ ___
      //   / _` |/ _ \ |/ _ \ __/ _ \
      //  | (_| |  __/ |  __/ ||  __/
      //   \__,_|\___|_|\___|\__\___|
      */
      #define CMD MODEL_NAME "_Mex('delete',obj): "
      CHECK_IN(2);
      CHECK_OUT(0);
      DATA_DELETE( arg_in_1 );
      #undef CMD
      break;
    case CMD_READ:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_read( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_SETUP:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_setup( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_SET_GUESS:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_set_guess( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_GUESS:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_get_guess( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_SOLUTION_AS_GUESS:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_get_solution_as_guess( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_SOLVE:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_solve( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_DIMS:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_dims( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_NAMES:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_names( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_UPDATE_CONTINUATION:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_updateContinuation( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_RAW_SOLUTION:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_get_raw_solution( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_SET_RAW_SOLUTION:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_set_raw_solution( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_CHECK_RAW_SOLUTION:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_check_raw_solution( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_CHECK_JACOBIAN:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_check_jacobian( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_SOLUTION:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_get_solution( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_GET_OCP_DATA:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_get_ocp_data( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_EVAL_F:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_eval_F( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_EVAL_JF:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_eval_JF( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_EVAL_JF_PATTERN:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_eval_JF_pattern( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_PACK:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_pack( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_UNPACK:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_unpack( nlhs, plhs, nrhs, prhs );
      break;
    case CMD_INFO_LEVEL:
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      ptr->mex_changeInfoLevel( nlhs, plhs, nrhs, prhs );
      break;
    }

    /*
    //  _
    // | |__ _ __ _ _ _ __ _ _ _  __ _ ___
    // | / _` / _` | '_/ _` | ' \/ _` / -_)
    // |_\__,_\__, |_| \__,_|_||_\__, \___|
    //        |___/              |___/
    */
    /*
    //  _ __  __ _ _  _ ___ _ _
    // | '  \/ _` | || / -_) '_|
    // |_|_|_\__,_|\_, \___|_|
    //             |__/
    */
    /*
    //   ___
    //  / _ \
    // | (_) |
    //  \__\_\
    */
    /*
    //  _
    // | |__  __
    // | '_ \/ _|
    // |_.__/\__|
    */
    /*
    //  ___  _        ___
    // |   \| |__  __|   \__ ___ __
    // | |) | '_ \/ _| |) \ \ / '_ \
    // |___/|_.__/\__|___//_\_\ .__/
    //                        |_|
    */
    /*
    //  _        ___ _
    // | |__  __| _ |_)__ _
    // | '_ \/ _| _ \ / _` |
    // |_.__/\__|___/_\__, |
    //                |___/
    */
    /*
    //  ___  _        ___ _      ___
    // |   \| |__  __| _ |_)__ _|   \__ ___ __
    // | |) | '_ \/ _| _ \ / _` | |) \ \ / '_ \
    // |___/|_.__/\__|___/_\__, |___//_\_\ .__/
    //                     |___/         |_|
    */
  }
  catch ( std::out_of_range const & exc ) {
    string errmsg = string("Unknown command: ")+exc.what();
    mexErrMsgTxt(errmsg.c_str());
  }
  catch ( std::exception const & exc ) {
    string errmsg = string("Error: ")+exc.what();
    mexErrMsgTxt(errmsg.c_str());
  }
  catch (...) {
    mexErrMsgTxt("Unknown error\n");
  }
}
