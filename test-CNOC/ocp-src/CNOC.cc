/*-----------------------------------------------------------------------*\
 |  file: CNOC.cc                                                        |
 |                                                                       |
 |  version: 1.0   date 19/1/2021                                        |
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


// use pragma to include libraries
#include <MechatronixCore/MechatronixLibs.hh>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "CNOC.hh"
#include "CNOC_Pars.hh"

#include <time.h> /* time_t, struct tm, time, localtime, asctime */

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace CNOCDefine {

  using GenericContainerNamespace::vec_string_type;

  /*
  //   _ __   __ _ _ __ ___   ___  ___
  //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | | | | (_| | | | | | |  __/\__ \
  //  |_| |_|\__,_|_| |_| |_|\___||___/
  //
  */

  char const *namesXvars[numXvars+1] = {
    "s",
    "n",
    "vs",
    "vn",
    "as",
    "an",
    "coV",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    "lambda2__xo",
    "lambda3__xo",
    "lambda4__xo",
    "lambda5__xo",
    "lambda6__xo",
    "lambda7__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "js",
    "jn",
    nullptr
  };

  char const *namesQvars[numQvars+1] = {
    "zeta",
    nullptr
  };

  char const *namesPvars[numPvars+1] = {
    nullptr
  };

  char const *namesOMEGAvars[numOMEGAvars+1] = {
    "omega1__xo",
    "omega2__xo",
    "omega3__xo",
    "omega4__xo",
    "omega5__xo",
    "omega6__xo",
    "omega7__xo",
    "omega8__xo",
    "omega9__xo",
    "omega10__xo",
    "omega11__xo",
    "omega12__xo",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "feed",
    "acc",
    "jerk",
    "vx",
    "vy",
    "ax",
    "ay",
    "jx",
    "jy",
    "X-path",
    "Y-path",
    "X-traj",
    "Y-traj",
    "X-left",
    "Y-left",
    "X-right",
    "Y-right",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    "time",
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "an_f",
    "an_i",
    "an_max",
    "as_f",
    "as_i",
    "as_max",
    "ax_max",
    "ay_max",
    "jn_max",
    "js_max",
    "js_min",
    "n_f",
    "n_i",
    "vn_f",
    "vn_i",
    "vs_f",
    "vs_i",
    "deltaFeed",
    "pf_error",
    "path_following_tolerance",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    "timePositive",
    "vLimit",
    "PathFollowingTolerance",
    "as_limit",
    "an_limit",
    "ax_limit",
    "ay_limit",
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "jsControl",
    "jnControl",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_n",
    "initial_vs",
    "initial_vn",
    "initial_as",
    "initial_an",
    "final_n",
    "final_vs",
    "final_vn",
    "final_as",
    "final_an",
    "initial_s",
    "final_s",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  CNOC::CNOC(
    string  const & name,
    ThreadPool    * TP,
    Console const * console
  )
  : Discretized_Indirect_OCP( name, TP, console )
  // Controls
  , jsControl("jsControl")
  , jnControl("jnControl")
  // Constraints 1D
  , timePositive("timePositive")
  , vLimit("vLimit")
  , PathFollowingTolerance("PathFollowingTolerance")
  , as_limit("as_limit")
  , an_limit("an_limit")
  , ax_limit("ax_limit")
  , ay_limit("ay_limit")
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // Initialize to NaN all the ModelPars
    std::fill( ModelPars, ModelPars + numModelPars, Utils::NaN<real_type>() );

    // Initialize string of names
    setupNames(
      numPvars,                 namesPvars,
      numXvars,                 namesXvars,
      numLvars,                 namesLvars,
      numUvars,                 namesUvars,
      numQvars,                 namesQvars,
      numPostProcess,           namesPostProcess,
      numIntegratedPostProcess, namesIntegratedPostProcess,
      numBc,                    namesBc
    );
    //m_solver = &m_solver_NewtonDumped;
    m_solver = &m_solver_Hyness;

    #ifdef LAPACK_WRAPPER_USE_OPENBLAS
    openblas_set_num_threads(1);
    goto_set_num_threads(1);
    #endif
  }

  CNOC::~CNOC() {
  }

  /* --------------------------------------------------------------------------
  //                  _       _       ____  _
  //  _   _ _ __   __| | __ _| |_ ___|  _ \| |__   __ _ ___  ___
  // | | | | '_ \ / _` |/ _` | __/ _ \ |_) | '_ \ / _` / __|/ _ \
  // | |_| | |_) | (_| | (_| | ||  __/  __/| | | | (_| \__ \  __/
  //  \__,_| .__/ \__,_|\__,_|\__\___|_|   |_| |_|\__,_|___/\___|
  //       |_|
  */
  void
  CNOC::updateContinuation(
    integer   phase,
    real_type old_s,
    real_type s
  ) {
    int msg_level = 3;
    m_console->message(
      fmt::format(
        "\nContinuation step N.{} s={:.2}, ds={:.4}\n",
        phase+1, s, s-old_s
      ),
      msg_level
    );
  }

  /* --------------------------------------------------------------------------
  //           _               ____                                _
  //  ___  ___| |_ _   _ _ __ |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  // / __|/ _ \ __| | | | '_ \| |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  // \__ \  __/ |_| |_| | |_) |  __/ (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  // |___/\___|\__|\__,_| .__/|_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  //                    |_|
  // initialize parameters using associative array
  */
  void
  CNOC::setupParameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "CNOC::setupParameters: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Parameters");

    bool allfound = true;
    for ( integer i = 0; i < numModelPars; ++i ) {
      char const * namei = namesModelPars[i];
      if ( gc.exists( namei ) ) {
        ModelPars[i] = gc(namei).get_number();
      } else {
        m_console->error( fmt::format( "Missing parameter: '{}'\n", namei ) );
        allfound = false;
      }
    }
    UTILS_ASSERT0(
      allfound, "in CNOC::setup not all parameters are set!\n"
    );
  }

  void
  CNOC::setupParameters( real_type const Pars[] ) {
    std::copy( Pars, Pars + numModelPars, ModelPars );
  }

  /* --------------------------------------------------------------------------
  //            _                ____ _
  //   ___  ___| |_ _   _ _ __  / ___| | __ _ ___ ___  ___  ___
  //  / __|/ _ \ __| | | | '_ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  \__ \  __/ |_| |_| | |_) | |___| | (_| \__ \__ \  __/\__ \
  //  |___/\___|\__|\__,_| .__/ \____|_|\__,_|___/___/\___||___/
  //                     |_|
  */
  void
  CNOC::setupClasses( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "CNOC::setupClasses: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("timePositive"),
      "in CNOC::setupClasses(gc) missing key: ``timePositive''\n"
    );
    timePositive.setup( gc("timePositive") );

    UTILS_ASSERT0(
      gc.exists("vLimit"),
      "in CNOC::setupClasses(gc) missing key: ``vLimit''\n"
    );
    vLimit.setup( gc("vLimit") );

    UTILS_ASSERT0(
      gc.exists("PathFollowingTolerance"),
      "in CNOC::setupClasses(gc) missing key: ``PathFollowingTolerance''\n"
    );
    PathFollowingTolerance.setup( gc("PathFollowingTolerance") );

    UTILS_ASSERT0(
      gc.exists("as_limit"),
      "in CNOC::setupClasses(gc) missing key: ``as_limit''\n"
    );
    as_limit.setup( gc("as_limit") );

    UTILS_ASSERT0(
      gc.exists("an_limit"),
      "in CNOC::setupClasses(gc) missing key: ``an_limit''\n"
    );
    an_limit.setup( gc("an_limit") );

    UTILS_ASSERT0(
      gc.exists("ax_limit"),
      "in CNOC::setupClasses(gc) missing key: ``ax_limit''\n"
    );
    ax_limit.setup( gc("ax_limit") );

    UTILS_ASSERT0(
      gc.exists("ay_limit"),
      "in CNOC::setupClasses(gc) missing key: ``ay_limit''\n"
    );
    ay_limit.setup( gc("ay_limit") );

  }

  /* --------------------------------------------------------------------------
  //           _               _   _                ____ _
  //  ___  ___| |_ _   _ _ __ | | | |___  ___ _ __ / ___| | __ _ ___ ___  ___  ___
  // / __|/ _ \ __| | | | '_ \| | | / __|/ _ \ '__| |   | |/ _` / __/ __|/ _ \/ __|
  // \__ \  __/ |_| |_| | |_) | |_| \__ \  __/ |  | |___| | (_| \__ \__ \  __/\__ \
  // |___/\___|\__|\__,_| .__/ \___/|___/\___|_|   \____|_|\__,_|___/___/\___||___/
  //                    |_|
  */
  void
  CNOC::setupUserClasses( GenericContainer const & gc ) {
  }

  /* --------------------------------------------------------------------------
  //           _             _   _
  //   ___ ___| |_ _  _ _ __| | | |___ ___ _ _
  //  (_-</ -_)  _| || | '_ \ |_| (_-</ -_) '_|
  //  /__/\___|\__|\_,_| .__/\___//__/\___|_|
  //                   |_|
  //   __  __                        _ ___             _   _
  //  |  \/  |__ _ _ __ _ __  ___ __| | __|  _ _ _  __| |_(_)___ _ _  ___
  //  | |\/| / _` | '_ \ '_ \/ -_) _` | _| || | ' \/ _|  _| / _ \ ' \(_-<
  //  |_|  |_\__,_| .__/ .__/\___\__,_|_| \_,_|_||_\__|\__|_\___/_||_/__/
  //              |_|  |_|
  */
  void
  CNOC::setupUserMappedFunctions( GenericContainer const & gc_data ) {
  }
  /* --------------------------------------------------------------------------
  //            _                ____            _             _
  //   ___  ___| |_ _   _ _ __  / ___|___  _ __ | |_ _ __ ___ | |___
  //  / __|/ _ \ __| | | | '_ \| |   / _ \| '_ \| __| '__/ _ \| / __|
  //  \__ \  __/ |_| |_| | |_) | |__| (_) | | | | |_| | | (_) | \__ \
  //  |___/\___|\__|\__,_| .__/ \____\___/|_| |_|\__|_|  \___/|_|___/
  //                     |_|
  */
  void
  CNOC::setupControls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    UTILS_ASSERT0(
      gc_data.exists("Controls"),
      "CNOC::setupClasses: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    jsControl.setup( gc("jsControl") );
    jnControl.setup( gc("jnControl") );
    // setup iterative solver
    this->setupControlSolver( gc_data );
  }

  /* --------------------------------------------------------------------------
  //            _               ____       _       _
  //   ___  ___| |_ _   _ _ __ |  _ \ ___ (_)_ __ | |_ ___ _ __ ___
  //  / __|/ _ \ __| | | | '_ \| |_) / _ \| | '_ \| __/ _ \ '__/ __|
  //  \__ \  __/ |_| |_| | |_) |  __/ (_) | | | | | ||  __/ |  \__ \
  //  |___/\___|\__|\__,_| .__/|_|   \___/|_|_| |_|\__\___|_|  |___/
  //                     |_|
  */
  void
  CNOC::setupPointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "CNOC::setupPointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pToolPath2D"),
      "in CNOC::setupPointers(gc) cant find key `pToolPath2D' in gc\n"
    );
    pToolPath2D = gc("pToolPath2D").get_pointer<ToolPath2D*>();
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  CNOC::infoClasses() const {
    int msg_level = 3;
    ostringstream mstr;

    m_console->message("\nControls\n",msg_level);
    mstr.str("");
    jsControl.info(mstr);
    jnControl.info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nConstraints 1D\n",msg_level);
    mstr.str("");
    timePositive          .info(mstr);
    vLimit                .info(mstr);
    PathFollowingTolerance.info(mstr);
    as_limit              .info(mstr);
    an_limit              .info(mstr);
    ax_limit              .info(mstr);
    ay_limit              .info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    mstr.str("");
    mstr << "User function `pToolPath2D`: ";
    pToolPath2D->info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nModel Parameters\n",msg_level);
    for ( integer i = 0; i < numModelPars; ++i ) {
      m_console->message(
        fmt::format("{:.>40} = {}\n",namesModelPars[i], ModelPars[i]),
        msg_level
      );
    }

  }

  /* --------------------------------------------------------------------------
  //            _
  //   ___  ___| |_ _   _ _ __
  //  / __|/ _ \ __| | | | '_ \
  //  \__ \  __/ |_| |_| | |_) |
  //  |___/\___|\__|\__,_| .__/
  //                     |_|
  */
  void
  CNOC::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("CNOC::setup, Debug");

    this->setupParameters( gc );
    this->setupClasses( gc );
    this->setupUserMappedFunctions( gc );
    this->setupUserClasses( gc );
    this->setupPointers( gc );
    this->setupBC( gc );
    this->setupControls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pToolPath2D, gc );
    this->infoBC();
    this->infoClasses();
    this->info();
  }

  /* --------------------------------------------------------------------------
  //              _
  //    __ _  ___| |_     _ __   __ _ _ __ ___   ___  ___
  //   / _` |/ _ \ __|   | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | (_| |  __/ |_    | | | | (_| | | | | | |  __/\__ \
  //   \__, |\___|\__|___|_| |_|\__,_|_| |_| |_|\___||___/
  //   |___/        |_____|
  */
  void
  CNOC::get_names( GenericContainer & out ) const {
    vec_string_type & X_names = out["state_names"].set_vec_string();
    for ( integer i = 0; i < numXvars; ++i ) X_names.push_back(namesXvars[i]);

    vec_string_type & LM_names = out["lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numLvars; ++i ) LM_names.push_back(namesLvars[i]);

    vec_string_type & U_names = out["control_names"].set_vec_string();
    for ( integer i = 0; i < numUvars; ++i ) U_names.push_back(namesUvars[i]);

    vec_string_type & Q_names = out["mesh_variable_names"].set_vec_string();
    for ( integer i = 0; i < numQvars; ++i ) Q_names.push_back(namesQvars[i]);

    vec_string_type & P_names = out["parameter_names"].set_vec_string();
    for ( integer i = 0; i < numPvars; ++i ) P_names.push_back(namesPvars[i]);

    vec_string_type & OMEGA_names = out["bc_lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numOMEGAvars; ++i ) OMEGA_names.push_back(namesOMEGAvars[i]);

    vec_string_type & PP_names = out["post_processing_names"].set_vec_string();
    for ( integer i = 0; i < numPostProcess; ++i ) PP_names.push_back(namesPostProcess[i]);

    for ( integer i = 0; i < numIntegratedPostProcess; ++i )
      PP_names.push_back(namesIntegratedPostProcess[i]);

    vec_string_type & model_names = out["model_names"].set_vec_string();
    for ( integer i = 0; i < numModelPars; ++i )
      model_names.push_back(namesModelPars[i]);
  }

  /* --------------------------------------------------------------------------
  //      _ _                       _   _
  //   __| (_)__ _ __ _ _ _  ___ __| |_(_)__
  //  / _` | / _` / _` | ' \/ _ (_-<  _| / _|
  //  \__,_|_\__,_\__, |_||_\___/__/\__|_\__|
  //              |___/
  */
  void
  CNOC::diagnostic( GenericContainer const & gc ) {

    // DA RIFARE--------------

    // If required save function and jacobian
    //if ( gc.exists("DumpFile") )
    //  this->dumpFunctionAndJacobian( m_solver->solution(),
    //                                 gc("DumpFile").get_string() );

    //bool do_diagnosis = gc.get_map_bool("Doctor");
    //if ( do_diagnosis )
    //  this->diagnosis( m_solver->solution(), gc["diagnosis"] );

    real_type epsi = 1e-5;
    gc.get_if_exists("JacobianCheck_epsilon",epsi);
    if ( gc.get_map_bool("JacobianCheck") )
      this->checkJacobian( m_solver->solution(), epsi );
    if ( gc.get_map_bool("JacobianCheckFull") )
      this->checkJacobianFull( m_solver->solution(), epsi );
  }

  // save model parameters
  void
  CNOC::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: CNOC.cc
