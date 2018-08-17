/*-----------------------------------------------------------------------*\
 |  file: Catalyst_Mex.cc                                                |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
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
#include "Catalyst.hh"
#include "Catalyst_Pars.hh"
#include <sstream>

#include "mex_utils.hh"

using namespace std;
using namespace MechatronixCommon;

// user class in namespaces
using Mechatronix::MeshStd;


using namespace CatalystLoad;
using namespace GenericContainerNamespace;


static char const help_msg[] =
"%===========================================================================%\n"
"\n"
"Mex command has the following possible calls:\n"
"\n"
"  - Catalyst_Mex('setup', mstruct):\n"
"    initialise the problem with a matlab structure 'mstruct'\n"
"\n"
"  - Catalyst_Mex('solve'):\n"
"    solve the optimal control problem and store internally\n"
"    the solution found.\n"
"\n"
"  To get the solution there are various calling sequence:\n"
"  - sol = Catalyst_Mex('get_solution'):\n"
"    return the full solution as a matlab structure also with solver\n"
"    information (e.g. iteration taken, convergence, etc).\n"
"\n"
"  - sol1, sol2, ..., solN = Catalyst_Mex('get_solution',{var_nm}):\n"
"    return the full solution as a vector only for the desired variable\n"
"    'var_nm' or listed in the cell array {var_num}.\n"
"\n"
"  - sol = Catalyst_Mex('get_solution',t):\n"
"    return the solution as a vector for all output variables at desired\n"
"    instant 't'. 't' can be a vector or a scalar.\n"
"\n"
"  - sol1, sol2, ..., solN = Catalyst_Mex('get_solution',t,{var_nm}):\n"
"    return the solution as a matlab matrix for all output variables\n"
"    listed in the cell array {var_num} at instant 't'.%\n"
"    't' can be a vector or a scalar.\n"
"%===========================================================================%\n"
;

#define MODEL_NAME  "Catalyst"
#define MODEL_CLASS Catalyst

#define CHECK_IN(N) \
  MEX_ASSERT( nrhs == N, \
              CMD "Expected " << N << " argument(s), nrhs = "  << nrhs )

#define CHECK_OUT(N) \
  MEX_ASSERT( nlhs == N, \
              CMD "Expected " << N << " argument(s), nlhs = "  << nlhs )
/*\
 |
 |  ____            _     _                ____  _
 | |  _ \ _ __ ___ | |__ | | ___ _ __ ___ / ___|| |_ ___  _ __ __ _  __ _  ___
 | | |_) | '__/ _ \| '_ \| |/ _ \ '_ ` _ \\___ \| __/ _ \| '__/ _` |/ _` |/ _ \
 | |  __/| | | (_) | |_) | |  __/ | | | | |___) | || (_) | | | (_| | (_| |  __/
 | |_|   |_|  \___/|_.__/|_|\___|_| |_| |_|____/ \__\___/|_|  \__,_|\__, |\___|
 |                                                                  |___/
 |
\*/
class ProblemStorage : public MODEL_CLASS {

  bool setup_ok;
  bool guess_ok;
  bool solve_ok;
  bool solution_ok;

  GenericContainer   gc_data, gc_solution;
  Splines::SplineSet splines;
  // user defined Object instances (external)
  MeshStd              mesh;
public:

  ProblemStorage( std::string const & cname, indexType infoLevel )
  : MODEL_CLASS(cname,&cout,infoLevel)
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

  bool isDoneSetup() const { return setup_ok; }
  bool isDoneGuess() const { return guess_ok; }
  bool isDoneSolve() const { return solve_ok; }

  void
  setup( string const & fname ) {
    if ( fname.find_last_of(".rb") ) {
      Mechatronix::MrubyInterpreter mrb;
      mrb.load( fname.c_str() );
      mrb.expr_to_GC( "Mechatronix.content", gc_data );
    } else if ( fname.find_last_of(".lua") ) {
      using GenericContainerNamespace::LuaInterpreter;
      LuaInterpreter lua;
      Mechatronix::lua_set_constants( lua );
      lua.do_file( fname.c_str() );
      lua.global_to_GC( "content", gc_data );
    } else {
      MEX_ASSERT( false,
                  "unknown suffix for filename `" << fname <<
                  "` use `.rb` or `.lua`" );
    }
    setup();
  }

  void
  setup( mxArray const * & arg ) {
    mxArray_to_GenericContainer( arg, gc_data );
    setup();
  }

  void
  setup() {

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    ASSERT(gc_data.exists("Mesh"), "missing key: ``Mesh'' in gc_data");
    mesh.setup(gc_data("Mesh"));
    ptrs[ "pMesh" ] = &mesh;

    // setup model
    MODEL_CLASS::setup( gc_data );
  }

  using MODEL_CLASS::guess;

  void
  guess() {
    MODEL_CLASS::guess( gc_data );
  }

  bool
  solve() {
    solve_ok = MODEL_CLASS::solve();
    return solve_ok;
  }

  void
  dims( mxArray * & out ) {
    GenericContainer gc;
    gc["dim_q"]     = MODEL_CLASS::dim_Q();
    gc["dim_x"]     = MODEL_CLASS::dim_X();
    gc["dim_u"]     = MODEL_CLASS::dim_U();
    gc["dim_pars"]  = MODEL_CLASS::dim_Pars();
    gc["dim_omega"] = MODEL_CLASS::dim_Omega();
    gc["dim_bc"]    = MODEL_CLASS::dim_BC();
    gc["num_nodes"] = MODEL_CLASS::nNodes();
    gc["neq"]       = MODEL_CLASS::numEquations();
    GenericContainer_to_mxArray( gc, out );
  }

  GenericContainer const &
  get_solution() const
  { return gc_solution; }

  GenericContainer const &
  get_data() const
  { return gc_data; }

  Splines::SplineSet const &
  get_splines() const
  { return splines; }

  void
  get_solution( char const cmd[],
                string const & cname,
                mxArray * & out ) {
    if ( !solution_ok ) {
      MODEL_CLASS::get_solution( gc_solution, splines );
      solution_ok = true;
    }
    GenericContainer const & idx = gc_solution("idx");
    MEX_ASSERT( idx.exists(cname),
                cmd << "data column `" << cname << "` do not exists" );
    indexType icol = idx(cname).get_as_int();
    GenericContainer::mat_real_type const & data = gc_solution("data").get_mat_real();
    double * res = createMatrixValue( out, data.numRows(), 1 );
    data.getColumn( icol, res );
  }

  void
  get_solution( mxArray * & out ) {
    if ( !solution_ok ) {
      MODEL_CLASS::get_solution( gc_solution, splines );
      solution_ok = true;
    }
    GenericContainer_to_mxArray( gc_solution, out );
  }

  void
  diagnostic()
  { MODEL_CLASS::diagnostic( gc_data ); }

  void
  eval_F( mxArray const * & arg,
          mxArray       * & out,
          char const        cmd[] ) {
    mwSize dimx;
    real_type const * x = getVectorPointer( arg, dimx, cmd );
    MEX_ASSERT( dimx == mwSize(numEquations()),
                cmd << " size(x) = " << dimx <<
                " must be equal to neq = " << numEquations() );
    real_type * f = createMatrixValue( out, dimx, 1 );
    MODEL_CLASS::eval_F( x, f );
  }

  indexType nnz() const { return MODEL_CLASS::eval_JF_nnz(); }

  void
  pattern( valuePointer I, valuePointer J ) const {
    indexType nnz = MODEL_CLASS::eval_JF_nnz();
    static std::vector<indexType> i_row(nnz), j_col(nnz);
    MODEL_CLASS::eval_JF_pattern( &i_row.front(), &j_col.front(), 1 );
    for ( indexType i = 0; i < nnz; ++i ) {
      I[i] = i_row[i];
      J[i] = j_col[i];
    }
  }

  void
  eval_JF( mxArray const * & arg,
           mxArray       * & out,
           char const        cmd[] ) {
    mwSize dimx;
    real_type const * x = getVectorPointer( arg, dimx, cmd );
    MEX_ASSERT( dimx == mwSize(numEquations()),
                cmd << " size(x) = " << dimx <<
                " must be equal to neq = " << numEquations() );

    mxArray *args[5];
    valuePointer I = createMatrixValue( args[0], 1, nnz() );
    valuePointer J = createMatrixValue( args[1], 1, nnz() );
    valuePointer V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );
    pattern( I, J );
    MODEL_CLASS::eval_JF_values( x, V );
    int ok = mexCallMATLAB( 1, &out, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, cmd << "failed the call sparse(...)" );
  }

  void
  eval_JF_pattern( mxArray * & out, char const cmd[] ) {
    mxArray *args[5];
    valuePointer I = createMatrixValue( args[0], 1, nnz() );
    valuePointer J = createMatrixValue( args[1], 1, nnz() );
    valuePointer V = createMatrixValue( args[2], 1, nnz() );
    setScalarValue( args[3], numEquations() );
    setScalarValue( args[4], numEquations() );
    pattern( I, J );
    std::fill( V, V+nnz(), 1 );
    int ok = mexCallMATLAB( 1, &out, 5, args, "sparse" );
    MEX_ASSERT( ok == 0, cmd << "failed the call sparse(...)" );
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
DATA_NEW( mxArray * & mx_id, std::string const & name, indexType infoLevel ) {
  ProblemStorage * ptr = new ProblemStorage( name, infoLevel );
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
  CMD_SETUP,
  CMD_GUESS,
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
  CMD_UNPACK
} CMD_LIST;

static map<string,unsigned> cmd_to_idx = {
  {"new",CMD_NEW},
  {"help",CMD_HELP},
  {"delete",CMD_DELETE},
  {"setup",CMD_SETUP},
  {"guess",CMD_GUESS},
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
  {"unpack",CMD_UNPACK}
};

void
mexFunction( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {

  MEX_ASSERT( nrhs > 0,
              MODEL_NAME "_Mex: Missing Arguments!" );
  MEX_ASSERT( mxIsChar(arg_in_0),
              MODEL_NAME "_Mex: First argument must be a string" );

  try {

    string cmd = mxArrayToString(arg_in_0);

    ProblemStorage * ptr = nullptr;
    if ( cmd != "new" && cmd != "help" ) {
      MEX_ASSERT( nrhs > 1,
                  MODEL_NAME "_Mex('" << cmd <<
                  "',...): expected at least 2 arguments, found nrhs = " << nrhs );
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
      #define CMD MODEL_NAME "_Mex('new',name,info_level): "
      CHECK_IN(3);
      CHECK_OUT(1);
      MEX_ASSERT( mxIsChar(arg_in_1),
                  CMD "second argument must be a string" );
      ptr = DATA_NEW(
              arg_out_0,
              mxArrayToString(arg_in_1),
              getInt( arg_in_2, CMD "third argument must be an integer" )
            );
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
    case CMD_SETUP:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //            _
      //   ___  ___| |_ _   _ _ __
      //  / __|/ _ \ __| | | | '_ \
      //  \__ \  __/ |_| |_| | |_) |
      //  |___/\___|\__|\__,_| .__/
      //                     |_|
      */
      #define CMD MODEL_NAME "_Mex('setup',obj,struct_or_filename): "
      CHECK_IN(3);
      CHECK_OUT(0);
      if ( mxIsChar(arg_in_2) ) {
        ptr->setup( mxArrayToString(arg_in_2) );
      } else {
        ptr->setup( arg_in_2 );
      }
      ptr->doneSetup();
      #undef CMD
      break;
    case CMD_GUESS:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //    ____
      //   / ___|_   _  ___  ___ ___
      //  | |  _| | | |/ _ \/ __/ __|
      //  | |_| | |_| |  __/\__ \__ \
      //   \____|\__,_|\___||___/___/
      */
      #define CMD MODEL_NAME "_Mex('guess',obj[,guess]): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'guess'" );
      CHECK_OUT( 0 );
      if ( nrhs == 3 ) {
        GenericContainer gc;
        mxArray_to_GenericContainer( arg_in_2, gc );
        ptr->guess( gc );
      } else if ( nrhs == 2 ) {
        ptr->guess();
      } else {
        MEX_ASSERT( false,
                    CMD "Expected 2 or 3 argument(s), nrhs = "  << nrhs );
      }
      ptr->doneGuess();
      #undef CMD
      break;
    case CMD_SOLVE:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //             _
      //   ___  ___ | |_   _____
      //  / __|/ _ \| \ \ / / _ \
      //  \__ \ (_) | |\ V /  __/
      //  |___/\___/|_| \_/ \___|
      */
      #define CMD MODEL_NAME "_Mex('solve',obj): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'solve'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      setScalarBool( arg_out_0, ptr->solve() );
      ptr->doneSolve();
      #undef CMD
      break;
    case CMD_DIMS:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //      _ _
      //   __| (_)_ __ ___  ___
      //  / _` | | '_ ` _ \/ __|
      // | (_| | | | | | | \__ \
      //  \__,_|_|_| |_| |_|___/
      */
      #define CMD MODEL_NAME "_Mex('dims',obj): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'dims'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      ptr->dims( arg_out_0 );
      #undef CMD
      break;
    case CMD_NAMES:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //   _ __   __ _ _ __ ___   ___  ___
      //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
      //  | | | | (_| | | | | | |  __/\__ \
      //  |_| |_|\__,_|_| |_| |_|\___||___/
      */
      #define CMD MODEL_NAME "_Mex('names',obj): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'names'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      {
        GenericContainer gc;
        ptr->get_names( gc );
        GenericContainer_to_mxArray( gc, arg_out_0 );
      }
      #undef CMD
      break;
    case CMD_UPDATE_CONTINUATION:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //                   _       _       ____  _
      //   _   _ _ __   __| | __ _| |_ ___|  _ \| |__   __ _ ___  ___
      //  | | | | '_ \ / _` |/ _` | __/ _ \ |_) | '_ \ / _` / __|/ _ \
      //  | |_| | |_) | (_| | (_| | ||  __/  __/| | | | (_| \__ \  __/
      //   \__,_| .__/ \__,_|\__,_|\__\___|_|   |_| |_|\__,_|___/\___|
      //        |_|
      */
      #define CMD MODEL_NAME "_Mex('updateContinuation',obj,nphase,s): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'updateContinuation'" );
      CHECK_IN( 4 );
      CHECK_OUT( 0 );
      {
        int64_t nphase = getInt( arg_in_2, CMD " nphase number" );
        valueType s    = getScalarValue( arg_in_3, CMD " s" );
        ptr->updateContinuation( nphase, s );
      }
      #undef CMD
      break;
    case CMD_GET_RAW_SOLUTION:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //              _                                      _       _   _
      //    __ _  ___| |_     _ __ __ ___      __  ___  ___ | |_   _| |_(_) ___  _ __
      //   / _` |/ _ \ __|   | '__/ _` \ \ /\ / / / __|/ _ \| | | | | __| |/ _ \| '_ \
      //  | (_| |  __/ |_    | | | (_| |\ V  V /  \__ \ (_) | | |_| | |_| | (_) | | | |
      //   \__, |\___|\__|___|_|  \__,_| \_/\_/___|___/\___/|_|\__,_|\__|_|\___/|_| |_|
      //   |___/        |_____|              |_____|
      */
      #define CMD MODEL_NAME "_Mex('get_raw_solution',obj): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'get_raw_solution'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      {
        real_type * x = createMatrixValue( arg_out_0, ptr->numEquations(), 1 );
        ptr->get_raw_solution( x );
      }
      #undef CMD
      break;
    case CMD_SET_RAW_SOLUTION:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //            _                                      _       _   _
      //   ___  ___| |_     _ __ __ ___      __  ___  ___ | |_   _| |_(_) ___  _ __
      //  / __|/ _ \ __|   | '__/ _` \ \ /\ / / / __|/ _ \| | | | | __| |/ _ \| '_ \
      //  \__ \  __/ |_    | | | (_| |\ V  V /  \__ \ (_) | | |_| | |_| | (_) | | | |
      //  |___/\___|\__|___|_|  \__,_| \_/\_/___|___/\___/|_|\__,_|\__|_|\___/|_| |_|
      //              |_____|              |_____|
      */
      #define CMD MODEL_NAME "_Mex('set_raw_solution',obj,x): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'set_raw_solution'" );
      CHECK_IN( 3 );
      CHECK_OUT( 0 );
      {
        mwSize dimx;
        real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x");
        MEX_ASSERT( dimx == mwSize(ptr->numEquations()),
                    CMD << " size(x) = " << dimx <<
                    " must be equal to neq = " << ptr->numEquations() );
        ptr->set_raw_solution( x );
      }
      ptr->doneGuess(); // is equivalent to set guess
      #undef CMD
      break;
    case CMD_CHECK_RAW_SOLUTION:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //      _           _                              _      _   _
      //   __| |_  ___ __| |__  _ _ __ ___ __ __ ___ ___| |_  _| |_(_)___ _ _
      //  / _| ' \/ -_) _| / / | '_/ _` \ V  V /(_-</ _ \ | || |  _| / _ \ ' \
      //  \__|_||_\___\__|_\_\_|_| \__,_|\_/\_/_/__/\___/_|\_,_|\__|_\___/_||_|
      //                    |___|            |___|
      */
      #define CMD MODEL_NAME "_Mex('check_raw_solution',obj,x): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'check_raw_solution'" );
      CHECK_IN( 3 );
      CHECK_OUT( 1 );
      {
        mwSize dimx;
        real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
        MEX_ASSERT( dimx == mwSize(ptr->numEquations()),
                    CMD << " size(x) = " << dimx <<
                    " must be equal to neq = " << ptr->numEquations() );
        setScalarBool( arg_out_0, ptr->check_raw_solution(x) );
      }
      #undef CMD
      break;
    case CMD_CHECK_JACOBIAN:
      /*
      //        _               _       _                 _     _
      //    ___| |__   ___  ___| | __  | | __ _  ___ ___ | |__ (_) __ _ _ __
      //   / __| '_ \ / _ \/ __| |/ /  | |/ _` |/ __/ _ \| '_ \| |/ _` | '_ \
      //  | (__| | | |  __/ (__|   < |_| | (_| | (_| (_) | |_) | | (_| | | | |
      //   \___|_| |_|\___|\___|_|\_\___/ \__,_|\___\___/|_.__/|_|\__,_|_| |_|
      */
      #define CMD MODEL_NAME "_Mex('check_jacobian',obj,x,epsi): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'check_jacobian'" );
      CHECK_IN( 4 );
      CHECK_OUT( 0 );
      {
        mwSize dimx;
        real_type const * x = getVectorPointer( arg_in_2, dimx, CMD "argument x" );
        real_type epsi = getScalarValue( arg_in_3, CMD "argument epsi" );
        MEX_ASSERT( dimx == mwSize(ptr->numEquations()),
                    CMD << " size(x) = " << dimx <<
                    " must be equal to neq = " << ptr->numEquations() );
        ptr->checkJacobian(x,epsi,cout);
      }
      #undef CMD
      break;
    case CMD_GET_SOLUTION:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //             _                 _       _   _
      //   __ _  ___| |_     ___  ___ | |_   _| |_(_) ___  _ __
      //  / _` |/ _ \ __|   / __|/ _ \| | | | | __| |/ _ \| '_ \
      // | (_| |  __/ |_    \__ \ (_) | | |_| | |_| | (_) | | | |
      //  \__, |\___|\__|___|___/\___/|_|\__,_|\__|_|\___/|_| |_|
      //  |___/        |_____|
      */
      #define CMD MODEL_NAME "_Mex('get_solution',obj[,column_name]): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'get_solution'" );
      CHECK_OUT( 1 );
      if ( nrhs == 2 ) {
        ptr->get_solution( arg_out_0 );
      } else if ( nrhs == 3 ) {
        MEX_ASSERT( mxIsChar(arg_in_2), CMD " Third argument must be a string" );
        ptr->get_solution( CMD, mxArrayToString(arg_in_2), arg_out_0 );
      } else {
        MEX_ASSERT( false, CMD "use 2 or 3 arguments, nrhs = " << nrhs );
      }
      #undef CMD
      break;
    case CMD_GET_OCP_DATA:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //              _                             _       _
      //    __ _  ___| |_     ___   ___ _ __     __| | __ _| |_ __ _
      //   / _` |/ _ \ __|   / _ \ / __| '_ \   / _` |/ _` | __/ _` |
      //  | (_| |  __/ |_   | (_) | (__| |_) | | (_| | (_| | || (_| |
      //   \__, |\___|\__|___\___/ \___| .__/___\__,_|\__,_|\__\__,_|
      //   |___/        |_____|        |_| |_____|
      */
      #define CMD MODEL_NAME "_Mex('get_ocp_data',obj): "
      MEX_ASSERT( ptr->isDoneSetup(),
                  CMD "use 'setup' before to use 'get_ocp_data'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      GenericContainer_to_mxArray( ptr->get_data(), arg_out_0 );
      #undef CMD
      break;
    case CMD_EVAL_F:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //                   _     _____
      //    _____   ____ _| |   |  ___|
      //   / _ \ \ / / _` | |   | |_
      //  |  __/\ V / (_| | |   |  _|
      //   \___| \_/ \__,_|_|___|_|
      //                   |_____|
      */
      #define CMD MODEL_NAME "_Mex('eval_F',obj,x): "
      MEX_ASSERT( ptr->isDoneGuess(),
                  CMD "use 'guess' before to use 'eval_F'" );
      CHECK_IN( 3 );
      CHECK_OUT( 1 );
      ptr->eval_F( arg_in_2, arg_out_0, CMD " argument x");
      #undef CMD
      break;
    case CMD_EVAL_JF:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //                   _        _ _____
      //    _____   ____ _| |      | |  ___|
      //   / _ \ \ / / _` | |   _  | | |_
      //  |  __/\ V / (_| | |  | |_| |  _|
      //   \___| \_/ \__,_|_|___\___/|_|
      //                   |_____|
      */
      #define CMD MODEL_NAME "_Mex('eval_JF',obj,x): "
      MEX_ASSERT( ptr->isDoneGuess(), CMD "use 'guess' before to use 'eval_JF'" );
      CHECK_IN( 3 );
      CHECK_OUT( 1 );
      ptr->eval_JF( arg_in_2, arg_out_0, CMD );
      #undef CMD
      break;
    case CMD_EVAL_JF_PATTERN:
      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      //                   _        _ _____              _   _
      //    _____   ____ _| |      | |  ___| _ __   __ _| |_| |_ ___ _ __ _ __
      //   / _ \ \ / / _` | |   _  | | |_   | '_ \ / _` | __| __/ _ \ '__| '_ \
      //  |  __/\ V / (_| | |  | |_| |  _|  | |_) | (_| | |_| ||  __/ |  | | | |
      //   \___| \_/ \__,_|_|___\___/|_|____| .__/ \__,_|\__|\__\___|_|  |_| |_|
      //                   |_____|    |_____|_|
      */
      #define CMD MODEL_NAME "_Mex('eval_JF_pattern',obj): "
      MEX_ASSERT( ptr->isDoneSetup(), CMD "use 'setup' before to use 'eval_JF_pattern'" );
      CHECK_IN( 2 );
      CHECK_OUT( 1 );
      ptr->eval_JF_pattern( arg_out_0, CMD );
      #undef CMD
      break;
    case CMD_PACK:
      /*
      //  ____            _
      // |  _ \ __ _  ___| | __
      // | |_) / _` |/ __| |/ /
      // |  __/ (_| | (__|   <
      // |_|   \__,_|\___|_|\_\
      */
      #define CMD MODEL_NAME "_Mex('pack',obj,x,lambda,pars,omega): "
      MEX_ASSERT( ptr->isDoneGuess(), CMD "use 'setup' before to use 'pack'" );
      CHECK_IN( 6 );
      CHECK_OUT( 1 );
      {
        mwSize nrX, ncX, nrL, ncL, nP, nO;
        real_type const * X = getMatrixPointer( arg_in_2, nrX, ncX, CMD "argument x" );
        real_type const * L = getMatrixPointer( arg_in_3, nrL, ncL, CMD "argument lambda" );
        real_type const * P = getVectorPointer( arg_in_4, nP, CMD "argument pars" );
        real_type const * O = getVectorPointer( arg_in_5, nO, CMD "argument omega" );
        indexType nn = ptr->nNodes();
        ASSERT( nrX == mwSize(ptr->dim_X()) && ncX == nn,
                CMD << "size(x) = " << nrX << " x " << ncX <<
                " expected to be " << ptr->dim_X() << " x " << nn );
        ASSERT( nrL == mwSize(ptr->dim_X()) && ncL == nn,
                CMD << "size(lambda) = " << nrL << " x " << ncL <<
                " expected to be " << ptr->dim_X() << " x " << nn );
        ASSERT( nP == mwSize(ptr->dim_Pars()),
                CMD << "length(pars) = " << nP <<
                " expected to be " << ptr->dim_Pars() );
        ASSERT( nO == mwSize(ptr->dim_Omega()),
                CMD << "length(omega) = " << nO <<
                " expected to be " << ptr->dim_Omega() );
        real_type * Z = createMatrixValue( arg_out_0, 1, ptr->numEquations() );
        ptr->pack( X, L, P, O, Z );
      }
      #undef CMD
      break;
    case CMD_UNPACK:
      /*
      //  _   _                        _
      // | | | |_ __  _ __   __ _  ___| | __
      // | | | | '_ \| '_ \ / _` |/ __| |/ /
      // | |_| | | | | |_) | (_| | (__|   <
      //  \___/|_| |_| .__/ \__,_|\___|_|\_\
      //             |_|
      */
      #define CMD MODEL_NAME "_Mex('unpack',obj,Z): "
      MEX_ASSERT( ptr->isDoneGuess(), CMD "use 'setup' before to use 'unpack'" );
      CHECK_IN( 3 );
      CHECK_OUT( 4 );
      {
        indexType nn = ptr->nNodes();
        mwSize nZ;
        real_type const * Z = getVectorPointer( arg_in_2, nZ, CMD "argument Z" );
        ASSERT( nZ == mwSize(ptr->numEquations()),
                CMD << "length(Z) = " << nZ <<
                " expected to be " << ptr->numEquations() );

        real_type * X = createMatrixValue( arg_out_0, ptr->dim_X(), nn );
        real_type * L = createMatrixValue( arg_out_1, ptr->dim_X(), nn );
        real_type * P = createMatrixValue( arg_out_2, 1, ptr->dim_Pars() );
        real_type * O = createMatrixValue( arg_out_3, 1, ptr->dim_Omega() );

        ptr->unpack( Z, X, L, P, O );
      }
      #undef CMD
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
