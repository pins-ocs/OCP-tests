/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Mex.cc                          |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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


#include "ICLOCS_MinimumFuelOrbitRaising_Mex.hh"

void
ProblemStorage::do_info(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('info',obj): "
  CHECK_IN_OUT(2,0);
  this->info( 4 );
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
ProblemStorage::do_read(
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
ProblemStorage::do_setup(
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
  UTILS_MEX_ASSERT0( gc_data.exists("Mesh"), "missing key: ``Mesh'' in gc_data\n" );
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
ProblemStorage::do_remesh(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('remesh',obj,new_mesh): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'remesh'" );
  CHECK_IN_OUT( 3, 0 );
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
ProblemStorage::do_set_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('set_guess',obj[,userguess]): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'set_guess'" );
  UTILS_MEX_ASSERT( nrhs == 2 || nrhs == 3, CMD "Expected 2 or 3 input argument(s), nrhs = {}\n", nrhs );
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
    MODEL_CLASS::info();
    this->done_guess();
  }
  catch ( std::exception const & exc ) {
    mexErrMsgTxt(
      fmt::format(
        "ICLOCS_MinimumFuelOrbitRaising_Mex('set_guess',...), error: {}",
        exc.what()
      ).c_str()
    );
  }
  catch (...) {
    mexErrMsgTxt( "ICLOCS_MinimumFuelOrbitRaising_Mex('set_guess',...), Unknown error\n" );
  }
  #undef CMD
}

void
ProblemStorage::do_get_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_guess',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'get_guess'" );
  CHECK_IN_OUT(2,1);
  GenericContainer_to_mxArray( gc_data("Guess"), arg_out_0 );
  #undef CMD
}

void
ProblemStorage::do_get_solution_as_guess(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_solution_as_guess',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'get_solution_as_guess'" );
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
ProblemStorage::do_solve(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('solve',obj[,timeout]): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'solve'" );
  UTILS_MEX_ASSERT( nrhs == 2 || nrhs == 3, CMD "Expected 2 or 3 argument(s), nrhs = {}", nrhs );
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
ProblemStorage::do_dims(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dims',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dims'" );
  CHECK_IN_OUT( 2, 1 );
  GenericContainer gc;
  gc["dim_q"]             = MODEL_CLASS::dim_Q();
  gc["dim_x"]             = MODEL_CLASS::dim_X();
  gc["dim_u"]             = MODEL_CLASS::dim_U();
  gc["dim_pars"]          = MODEL_CLASS::dim_Pars();
  gc["num_defined_bc"]    = MODEL_CLASS::dim_BC();
  gc["num_active_BC"]     = MODEL_CLASS::num_active_BC();
  gc["dim_full_bc"]       = 2*MODEL_CLASS::dim_X()+MODEL_CLASS::num_active_BC();
  gc["num_nodes"]         = MODEL_CLASS::num_nodes();
  gc["neq"]               = MODEL_CLASS::num_equations();
  gc["num_equations"]     = MODEL_CLASS::num_equations();
  gc["num_segments"]      = MODEL_CLASS::num_segments();
  gc["dim_post"]          = MODEL_CLASS::dim_Post();
  gc["dim_Ipost"]         = MODEL_CLASS::dim_Ipost();
  gc["dim_ineq"]          = MODEL_CLASS::LTargs_numEqns();

  GenericContainer_to_mxArray( gc, arg_out_0 );
  #undef CMD
}

void
ProblemStorage::do_dim_Q(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_Q',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_Q'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_Q() );
  #undef CMD
}

void
ProblemStorage::do_dim_X(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_X',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_X'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_X() );
  #undef CMD
}

void
ProblemStorage::do_dim_Pars(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_Pars',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_Pars'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_Pars() );
  #undef CMD
}

void
ProblemStorage::do_dim_BC(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_BC',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_BC'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_BC() );
  #undef CMD
}

void
ProblemStorage::do_dim_Post(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_Post',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_Post'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_Post() );
  #undef CMD
}

void
ProblemStorage::do_dim_Ipost(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_Ipost',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_Ipost'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::dim_Ipost() );
  #undef CMD
}

void
ProblemStorage::do_num_active_BC(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('num_active_BC',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'num_active_BC'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::num_active_BC() );
  #undef CMD
}

void
ProblemStorage::do_num_nodes(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('num_nodes',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'num_nodes'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::num_nodes() );
  #undef CMD
}

void
ProblemStorage::do_num_equations(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('num_equations',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'num_equations'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::num_equations() );
  #undef CMD
}

void
ProblemStorage::do_num_segments(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('num_segments',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'num_segments'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::num_segments() );
  #undef CMD
}


void
ProblemStorage::do_dim_full_bc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_full_bc',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_full_bc'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, 2*MODEL_CLASS::dim_X()+MODEL_CLASS::num_active_BC() );
  #undef CMD
}

void
ProblemStorage::do_dim_ineq(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('dim_ineq',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'dim_ineq'" );
  CHECK_IN_OUT( 2, 1 );
  Utils::mex_set_scalar_value( arg_out_0, MODEL_CLASS::LTargs_numEqns() );
  #undef CMD
}

/*\
 |  _ __  _____ __  _ _  __ _ _ __  ___ ___
 | | '  \/ -_) \ / | ' \/ _` | '  \/ -_|_-<
 | |_|_|_\___/_\_\_|_||_\__,_|_|_|_\___/__/
 |              |___|
\*/
void
ProblemStorage::do_names(
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
ProblemStorage::do_update_continuation(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('update_continuation',obj,nphase,old_s,s): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'update_continuation'" );
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
ProblemStorage::do_get_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_raw_solution',obj): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'get_raw_solution'" );
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
ProblemStorage::do_set_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('set_raw_solution',obj,x,u): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'set_raw_solution'" );
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
ProblemStorage::do_check_raw_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('check_raw_solution',obj,x): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'check_raw_solution'" );
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
ProblemStorage::do_check_jacobian(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('check_jacobian',obj,x,u,epsi): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'check_jacobian'" );
  CHECK_IN_OUT( 5, 0 );
  mwSize dimx, dimu;
  real_const_ptr x = Utils::mex_vector_pointer( arg_in_2, dimx, CMD "argument x" );
  real_const_ptr u = Utils::mex_vector_pointer( arg_in_3, dimu, CMD "argument u" );
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
ProblemStorage::do_get_solution(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_solution',obj[,column_name]): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'get_solution'" );
  CHECK_OUT( 1 );
  if ( !solution1_ok ) {
    MODEL_CLASS::get_solution( gc_solution1 );
    MODEL_CLASS::diagnostic( gc_data, gc_solution1 );
    solution1_ok = true;
  }
  if ( nrhs == 2 ) {
    GenericContainer_to_mxArray( gc_solution1, arg_out_0 );
  } else if ( nrhs == 3 ) {
    UTILS_MEX_ASSERT0( mxIsChar(arg_in_2), CMD " Third argument must be a string" );
    string const & cname = mxArrayToString(arg_in_2);
    GenericContainer const & idx = gc_solution1("idx");
    UTILS_MEX_ASSERT( idx.exists(cname), CMD "data column `{}` do not exists", cname );
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
ProblemStorage::do_get_solution2(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_solution2',obj): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'get_solution2'" );
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
ProblemStorage::do_get_solution3(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('get_solution3',obj): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'get_solution3'" );
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
ProblemStorage::do_get_ocp_data(
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
ProblemStorage::do_init_U(
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
ProblemStorage::do_eval_U(
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
ProblemStorage::do_eval_F(
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
    string msg = fmt::format( "ICLOCS_MinimumFuelOrbitRaising_Mex('eval_F',...) error: {}", exc.what() );
    mexWarnMsgTxt( msg.c_str() );
    ok = false;
  } catch ( ... ) {
    mexWarnMsgTxt( "ICLOCS_MinimumFuelOrbitRaising_Mex('eval_F',...) unkown error\n" );
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
ProblemStorage::do_eval_JF(
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
    mexWarnMsgTxt( fmt::format( "ICLOCS_MinimumFuelOrbitRaising_Mex('eval_JF',...) error: {}", exc.what() ).c_str() );
    ok_value = false;
  } catch ( ... ) {
    mexWarnMsgTxt( "ICLOCS_MinimumFuelOrbitRaising_Mex('eval_JF',...) unkown error\n" );
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
ProblemStorage::do_eval_JF_pattern(
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
ProblemStorage::do_pack(
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
    nO == mwSize(this->num_active_BC()),
    "{} length(omega) = {} expected to be {}\n",
    CMD, nO, this->num_active_BC()
  );
  real_ptr Z = Utils::mex_create_matrix_value( arg_out_0, 1, this->num_equations() );
  this->pack( X, L, P, O, Z );
  #undef CMD
}

void
ProblemStorage::do_pack_for_direct(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('pack_for_direct',obj,X,U,Pars): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'pack_for_direct'" );
  CHECK_IN_OUT( 5, 1 );

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
ProblemStorage::do_unpack(
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
  OMEGA_pointer_type O(Utils::mex_create_matrix_value( arg_out_3, 1, this->num_active_BC() ));

  this->unpack( Z, X, L, P, O );
  #undef CMD
}

void
ProblemStorage::do_unpack_for_direct(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('unpack_for_direct',obj,Z): "
  UTILS_MEX_ASSERT0( guess_ok, CMD "use 'set_guess' before to use 'unpack_for_direct'" );
  CHECK_IN_OUT( 3, 3 );

  mwSize nn   = mwSize( this->num_nodes() );
  mwSize dimZ = this->dim_X()*nn + this->dim_U()*(nn-1) + this->dim_Pars();

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
ProblemStorage::do_estimate_multipliers(
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
  OMEGA_pointer_type OMEGA(Utils::mex_create_matrix_value( arg_out_1, this->num_active_BC(), 1 ));

  this->estimate_multipliers( X, U, P, L, OMEGA );

  #undef CMD
}

/*\
 |   _ __  _____ __  __ _
 |  | '  \/ -_) \ / / _` |
 |  |_|_|_\___/_\_\_\__,_|
 |               |___|
\*/
void
ProblemStorage::do_ac(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME \
  "_Mex('ac', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

  CHECK_IN_OUT( 12, 1 );

  NodeType2 L, R;
  get_LR2( CMD, nrhs, prhs, L, R );
  GET_ARG_P( arg_in_10 );
  GET_ARG_U( arg_in_11 );

  integer n_thread = 0;
  real_ptr ac = Utils::mex_create_matrix_value( arg_out_0, 2*this->dim_X()+this->dim_Pars(), 1 );
  this->ac_eval( n_thread, L, R, P, U, ac );

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
ProblemStorage::do_DacDxlxlpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME \
  "_Mex('DacDxlxlpu', obj, iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ): "

  CHECK_IN_OUT( 12, 2 );

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

  integer  n_thread      = 0;
  integer  nCOL          = 4*dim_X+dim_P;
  integer  nR            = 2*dim_X+dim_P;
  real_ptr DacDxlxlp_mem = Utils::mex_create_matrix_value( arg_out_0, nR, nCOL  );
  real_ptr DacDu_mem     = Utils::mex_create_matrix_value( arg_out_1, nR, dim_U );

  MatrixWrapper<real_type> DacDxlxlp( DacDxlxlp_mem, nR, nCOL,  nR );
  MatrixWrapper<real_type> DacDu    ( DacDu_mem,     nR, dim_U, nR );

  this->DacDxlxlp_eval( n_thread, L, R, P, U, DacDxlxlp, DacDu );

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
ProblemStorage::do_hc(
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
ProblemStorage::do_DhcDxlxlop(
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
ProblemStorage::do_u(
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
    US.u_eval( m_console, L, R, P, U );
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
ProblemStorage::do_DuDxlxlp(
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
  US.u_eval_DuDxlxlp( L, R, P, U, DuDxlxlp );

  #undef CMD
}

/*\
 |    ___  ___  ___
 |   / _ \|   \| __|
 |  | (_) | |) | _|
 |   \___/|___/|___|
\*/
void
ProblemStorage::do_rhs_ode(
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
ProblemStorage::do_Drhs_odeDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('Drhs_odeDxpu', i_seg, obj, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( Drhs_odeDxpu, N, U, P );
  #undef CMD
}

/*\
 |     _
 |    /_\
 |   / _ \
 |  /_/ \_\
\*/
void
ProblemStorage::do_A(
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
ProblemStorage::do_eta(
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
ProblemStorage::do_DetaDxp(
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
ProblemStorage::do_nu(
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
ProblemStorage::do_DnuDxp(
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
 |  | || |_ ___ __
 |  | __ \ \ / '_ \
 |  |_||_/_\_\ .__/
 |           |_|
\*/

void
ProblemStorage::do_Hxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('Hxp', obj, i_seg, q, x, lambda, V, u, pars ): "

  CHECK_IN_OUT( 9, 1 );

  NodeType2 N;
  get_N( CMD, nrhs, prhs, N );

  GET_ARG_V( arg_in_6 );
  GET_ARG_U( arg_in_7 );
  GET_ARG_P( arg_in_8 );

  real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->Hxp_numEqns(), 1 );
  this->Hxp_eval( N, V, U, P, rhs );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_DHxpDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DHxpDxpu', obj, i_seg, q, x, lambda, V, u, pars ): "

  CHECK_IN_OUT( 9, 1 );

  NodeType2 N;
  get_N( CMD, nrhs, prhs, N );

  GET_ARG_V( arg_in_6 );
  GET_ARG_U( arg_in_7 );
  GET_ARG_P( arg_in_8 );

  RETURN_SPARSE( DHxpDxpu, N, V, U, P );

  #undef CMD
}

/*\
 |   _  _
 |  | || |_  _
 |  | __ | || |
 |  |_||_|\_,_|
\*/
void
ProblemStorage::do_Hu(
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

/*\
 |                       _ _   _
 |   _ __  ___ _ _  __ _| | |_(_)___ ___
 |  | '_ \/ -_) ' \/ _` | |  _| / -_|_-<
 |  | .__/\___|_||_\__,_|_|\__|_\___/__/
 |  |_|
\*/
void
ProblemStorage::do_LT(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('LT', obj, i_seg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );
  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->LT_numEqns(), 1 );
  this->LT_eval( N, U, P, rhs );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_JP(
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

  real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JP_numEqns(), 1 );
  this->JP_eval( N, U, P, rhs );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_JU(
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

  real_ptr rhs = Utils::mex_create_matrix_value( arg_out_0, this->JU_numEqns(), 1 );
  this->JU_eval( N, U, P, rhs );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_LTargs(
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
ProblemStorage::do_DLTargsDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DLTargsDxpu', obj, i_seg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( DLTargsDxpu, N, U, P );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_DJPDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DJPDxpu', obj, i_seg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( DJPDxpu, N, U, P );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_DLTDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DLTDxpu', obj, i_seg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( DLTDxpu, N, U, P );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_DJUDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DJUDxpu', obj, i_seg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( DJUDxpu, N, U, P );

  #undef CMD
}

// --------------------------------------------------------------------------


void
ProblemStorage::do_D2LTargsD2xpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2LTargsD2xpu', obj, i_seg, q, x, u, pars, omega ): "

  CHECK_IN_OUT( 8, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  mwSize nO;
  real_const_ptr OMEGA = Utils::mex_vector_pointer(
    arg_in_7, nO, CMD " argument omega"
  );

  RETURN_SPARSE( D2LTargsD2xpu, N, U, P, OMEGA );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_D2JPD2xpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2JPD2xpu', obj, i_seg, q, x, u, pars, omega ): "

  CHECK_IN_OUT( 8, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  mwSize nO;
  real_const_ptr OMEGA = Utils::mex_vector_pointer(
    arg_in_7, nO, CMD " argument omega"
  );

  RETURN_SPARSE( D2JPD2xpu, N, U, P, OMEGA );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_D2LTD2xpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2LTD2xpu', obj, i_seg, q, x, u, pars, omega ): "

  CHECK_IN_OUT( 8, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  mwSize nO;
  real_const_ptr OMEGA = Utils::mex_vector_pointer(
    arg_in_7, nO, CMD " argument omega"
  );

  RETURN_SPARSE( D2LTD2xpu, N, U, P, OMEGA );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_D2JUD2xpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2JUD2xpu', obj, i_seg, q, x, u, pars, omega ): "

  CHECK_IN_OUT( 8, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  mwSize nO;
  real_const_ptr OMEGA = Utils::mex_vector_pointer(
    arg_in_7, nO, CMD " argument omega"
  );

  RETURN_SPARSE( D2JUD2xpu, N, U, P, OMEGA );

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

void
ProblemStorage::do_bc(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME \
  "_Mex('bc', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ): "

  CHECK_IN_OUT( 9, 1 );

  NodeType L, R;
  get_LR( CMD, nrhs, prhs, L, R );
  GET_ARG_P( arg_in_8 );

  real_ptr bc = Utils::mex_create_matrix_value( arg_out_0, this->dim_BC(), 1 );

  this->bc_eval( L, R, P, bc );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_DbcDxxp(
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
ProblemStorage::do_D2bcD2xxp(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2bcD2xxp', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, omega_full ): "

  CHECK_IN_OUT( 10, 1 );

  NodeType L, R;
  get_LR( CMD, nrhs, prhs, L, R );
  GET_ARG_P( arg_in_8 );
  GET_ARG_OMEGA_FULL( arg_in_9 );

  RETURN_SPARSE( D2bcD2xxp, L, R, P, Omega );

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
ProblemStorage::do_jump(
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
ProblemStorage::do_DjumpDxlxlp(
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
 |   _                     _
 |  | |_ __ _ _ _ __ _ ___| |_
 |  |  _/ _` | '_/ _` / -_)  _|
 |   \__\__,_|_| \__, \___|\__|
 |               |___/
\*/
void
ProblemStorage::do_lagrange_target(
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
ProblemStorage::do_DlagrangeDxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DlagrangeDxpu', obj, iseg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  // Gradient is a row vector
  real_ptr res = Utils::mex_create_matrix_value( arg_out_0, 1, this->DlagrangeDxpu_numEqns() );
  this->DlagrangeDxpu_eval( N, U, P , res );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_D2lagrangeD2xpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2lagrangeD2xpu', obj, iseg, q, x, u, pars ): "

  CHECK_IN_OUT( 7, 1 );

  NodeType N;
  get_qx( CMD, nrhs, prhs, N );

  GET_ARG_U( arg_in_5 );
  GET_ARG_P( arg_in_6 );

  RETURN_SPARSE( D2lagrangeD2xpu, N, U, P );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_mayer_target(
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
ProblemStorage::do_DmayerDxxp(
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
ProblemStorage::do_D2mayerD2xxp(
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
ProblemStorage::do_fd_ode(
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
ProblemStorage::do_Dfd_odeDxxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME \
  "_Mex('Dfd_odeDxxpu', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars ): "

  CHECK_IN_OUT( 10, 1 );

  NodeType L, R;
  get_LR( CMD, nrhs, prhs, L, R );
  GET_ARG_U( arg_in_8 );
  GET_ARG_P( arg_in_9 );

  RETURN_SPARSE( Dfd_odeDxxpu, L, R, P, U );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_D2fd_odeD2xxpu(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME \
  "_Mex('D2fd_odeD2xxpu', obj, iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars, lambda ): "

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

  RETURN_SPARSE( D2fd_odeD2xxpu, L, R, P, U, lambda );

  #undef CMD
}

// --------------------------------------------------------------------------

void
ProblemStorage::do_mesh_functions(
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
ProblemStorage::do_nodes(
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
ProblemStorage::do_node_to_segment(
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
ProblemStorage::do_D2mayerD2xxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2mayerD2xxp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2mayerD2xxp_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2mayerD2xxp_nnz();
  integer nr  = D2mayerD2xxp_numRows();
  integer nc  = D2mayerD2xxp_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2mayerD2xxp");
  mem.allocate( 2*nnz, "D2mayerD2xxp" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2mayerD2xxp_pattern( i_row, j_col );
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
ProblemStorage::do_Dfd_odeDxxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('Dfd_odeDxxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'Dfd_odeDxxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = Dfd_odeDxxpu_nnz();
  integer nr  = Dfd_odeDxxpu_numRows();
  integer nc  = Dfd_odeDxxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_Dfd_odeDxxpu");
  mem.allocate( 2*nnz, "Dfd_odeDxxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::Dfd_odeDxxpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2fd_odeD2xxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2fd_odeD2xxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2fd_odeD2xxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2fd_odeD2xxpu_nnz();
  integer nr  = D2fd_odeD2xxpu_numRows();
  integer nc  = D2fd_odeD2xxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2fd_odeD2xxpu");
  mem.allocate( 2*nnz, "D2fd_odeD2xxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2fd_odeD2xxpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2lagrangeD2xpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2lagrangeD2xpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2lagrangeD2xpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2lagrangeD2xpu_nnz();
  integer nr  = D2lagrangeD2xpu_numRows();
  integer nc  = D2lagrangeD2xpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2lagrangeD2xpu");
  mem.allocate( 2*nnz, "D2lagrangeD2xpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2lagrangeD2xpu_pattern( i_row, j_col );
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
ProblemStorage::do_A_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('A_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'A_pattern'" );
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
ProblemStorage::do_DbcDxxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DbcDxxp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DbcDxxp_pattern'" );
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
ProblemStorage::do_D2bcD2xxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2bcD2xxp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2bcD2xxp_pattern'" );
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
ProblemStorage::do_Drhs_odeDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('Drhs_odeDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'Drhs_odeDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = Drhs_odeDxpu_nnz();
  integer nr  = Drhs_odeDxpu_numRows();
  integer nc  = Drhs_odeDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_Drhs_odeDxpu");
  mem.allocate( 2*nnz, "Drhs_odeDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::Drhs_odeDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_DjumpDxlxlp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DjumpDxlxlp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DjumpDxlxlp_pattern'" );
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
ProblemStorage::do_DHxpDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DHxpDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DHxpDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = DHxpDxpu_nnz();
  integer nr  = DHxpDxpu_numRows();
  integer nc  = DHxpDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_DHxpDxpu");
  mem.allocate( 2*nnz, "DHxpDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::DHxpDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_DJPDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DJPDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DJPDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = DJPDxpu_nnz();
  integer nr  = DJPDxpu_numRows();
  integer nc  = DJPDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_DJPDxpu");
  mem.allocate( 2*nnz, "DJPDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::DJPDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_DLTDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DLTDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DLTDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = DLTDxpu_nnz();
  integer nr  = DLTDxpu_numRows();
  integer nc  = DLTDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_DLTDxpu");
  mem.allocate( 2*nnz, "DLTDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::DLTDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_DJUDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DJUDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DJUDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = DJUDxpu_nnz();
  integer nr  = DJUDxpu_numRows();
  integer nc  = DJUDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_DJUDxpu");
  mem.allocate( 2*nnz, "DJUDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::DJUDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2JPD2xpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2JPD2xpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2JPD2xpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2JPD2xpu_nnz();
  integer nr  = D2JPD2xpu_numRows();
  integer nc  = D2JPD2xpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2JPD2xpu");
  mem.allocate( 2*nnz, "D2JPD2xpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2JPD2xpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2LTD2xpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2LTD2xpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2LTD2xpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2LTD2xpu_nnz();
  integer nr  = D2LTD2xpu_numRows();
  integer nc  = D2LTD2xpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2LTD2xpu");
  mem.allocate( 2*nnz, "D2LTD2xpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2LTD2xpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2JUD2xpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2JUD2xpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2JUD2xpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2JUD2xpu_nnz();
  integer nr  = D2JUD2xpu_numRows();
  integer nc  = D2JUD2xpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2JUD2xpu");
  mem.allocate( 2*nnz, "D2JUD2xpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2JUD2xpu_pattern( i_row, j_col );
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
ProblemStorage::do_DLTargsDxpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DLTargsDxpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DLTargsDxpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = DLTargsDxpu_nnz();
  integer nr  = DLTargsDxpu_numRows();
  integer nc  = DLTargsDxpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_DLTargsDxpu");
  mem.allocate( 2*nnz, "DLTargsDxpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::DLTargsDxpu_pattern( i_row, j_col );
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
ProblemStorage::do_D2LTargsD2xpu_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('D2LTargsD2xpu_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'D2LTargsD2xpu_pattern'" );
  CHECK_IN_OUT( 2, 1 );

  integer nnz = D2LTargsD2xpu_nnz();
  integer nr  = D2LTargsD2xpu_numRows();
  integer nc  = D2LTargsD2xpu_numCols();
  mxArray *args[5];
  real_ptr I = Utils::mex_create_matrix_value( args[0], 1, nnz );
  real_ptr J = Utils::mex_create_matrix_value( args[1], 1, nnz );
  Utils::mex_set_scalar_value( args[2], 1  );
  Utils::mex_set_scalar_value( args[3], nr );
  Utils::mex_set_scalar_value( args[4], nc );

  Mechatronix::Malloc<integer> mem("mex_D2LTargsD2xpu");
  mem.allocate( 2*nnz, "D2LTargsD2xpu" );
  integer_ptr i_row = mem( nnz );
  integer_ptr j_col = mem( nnz );
  MODEL_CLASS::D2LTargsD2xpu_pattern( i_row, j_col );
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
ProblemStorage::do_DnuDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DnuDxp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DnuDxp_pattern'" );
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
ProblemStorage::do_DetaDxp_pattern(
  int nlhs, mxArray       *plhs[],
  int nrhs, mxArray const *prhs[]
)
{
  #define CMD MODEL_NAME "_Mex('DetaDxp_pattern',obj): "
  UTILS_MEX_ASSERT0( setup_ok, CMD "use 'setup' before to use 'DetaDxp_pattern'" );
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


// EOF: ICLOCS_MinimumFuelOrbitRaising_Mex.cc
