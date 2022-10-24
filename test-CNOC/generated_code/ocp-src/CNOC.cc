/*-----------------------------------------------------------------------*\
 |  file: CNOC.cc                                                        |
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


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "CNOC.hh"
#include "CNOC_Pars.hh"

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
    "jsControl",
    "jnControl",
    "timePositive",
    "vLimit",
    "PathFollowingTolerance_min",
    "PathFollowingTolerance_max",
    "as_limit_min",
    "as_limit_max",
    "an_limit_min",
    "an_limit_max",
    "ax_limit_min",
    "ax_limit_max",
    "ay_limit_min",
    "ay_limit_max",
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

  char const *namesConstraintLT[numConstraintLT+1] = {
    "timePositive",
    "vLimit",
    "PathFollowingTolerance_min",
    "PathFollowingTolerance_max",
    "as_limit_min",
    "as_limit_max",
    "an_limit_min",
    "an_limit_max",
    "ax_limit_min",
    "ax_limit_max",
    "ay_limit_min",
    "ay_limit_max",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
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
    string const   & name,
    Console const  * console,
    ThreadPoolBase * TP
  )
  : Discretized_Indirect_OCP( name, console, TP )
  // Controls
  , jsControl("jsControl")
  , jnControl("jnControl")
  // Constraints LT
  , timePositive("timePositive")
  , vLimit("vLimit")
  , PathFollowingTolerance_min("PathFollowingTolerance_min")
  , PathFollowingTolerance_max("PathFollowingTolerance_max")
  , as_limit_min("as_limit_min")
  , as_limit_max("as_limit_max")
  , an_limit_min("an_limit_min")
  , an_limit_max("an_limit_max")
  , ax_limit_min("ax_limit_min")
  , ax_limit_max("ax_limit_max")
  , ay_limit_min("ay_limit_min")
  , ay_limit_max("ay_limit_max")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // Initialize to NaN all the ModelPars
    std::fill_n( ModelPars, numModelPars, Utils::NaN<real_type>() );

    // Initialize string of names
    setup_names(
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
  }

  CNOC::~CNOC() {
    // Begin: User Exit Code
    // End: User Exit Code
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
  CNOC::update_continuation(
    integer   phase,
    real_type old_s,
    real_type s
  ) {
    int msg_level = 3;
    m_console->message(
      fmt::format(
        "\nContinuation step N.{} s={:.5}, ds={:.5}, old_s={:5}\n",
        phase+1, s, s-old_s, old_s
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
  CNOC::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "CNOC::setup_parameters: Missing key `Parameters` in data\n"
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
  CNOC::setup_parameters( real_type const Pars[] ) {
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
  CNOC::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "CNOC::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("timePositive"),
      "in CNOC::setup_classes(gc) missing key: ``timePositive''\n"
    );
    timePositive.setup( gc("timePositive") );

    UTILS_ASSERT0(
      gc.exists("vLimit"),
      "in CNOC::setup_classes(gc) missing key: ``vLimit''\n"
    );
    vLimit.setup( gc("vLimit") );

    UTILS_ASSERT0(
      gc.exists("PathFollowingTolerance_min"),
      "in CNOC::setup_classes(gc) missing key: ``PathFollowingTolerance_min''\n"
    );
    PathFollowingTolerance_min.setup( gc("PathFollowingTolerance_min") );

    UTILS_ASSERT0(
      gc.exists("PathFollowingTolerance_max"),
      "in CNOC::setup_classes(gc) missing key: ``PathFollowingTolerance_max''\n"
    );
    PathFollowingTolerance_max.setup( gc("PathFollowingTolerance_max") );

    UTILS_ASSERT0(
      gc.exists("as_limit_min"),
      "in CNOC::setup_classes(gc) missing key: ``as_limit_min''\n"
    );
    as_limit_min.setup( gc("as_limit_min") );

    UTILS_ASSERT0(
      gc.exists("as_limit_max"),
      "in CNOC::setup_classes(gc) missing key: ``as_limit_max''\n"
    );
    as_limit_max.setup( gc("as_limit_max") );

    UTILS_ASSERT0(
      gc.exists("an_limit_min"),
      "in CNOC::setup_classes(gc) missing key: ``an_limit_min''\n"
    );
    an_limit_min.setup( gc("an_limit_min") );

    UTILS_ASSERT0(
      gc.exists("an_limit_max"),
      "in CNOC::setup_classes(gc) missing key: ``an_limit_max''\n"
    );
    an_limit_max.setup( gc("an_limit_max") );

    UTILS_ASSERT0(
      gc.exists("ax_limit_min"),
      "in CNOC::setup_classes(gc) missing key: ``ax_limit_min''\n"
    );
    ax_limit_min.setup( gc("ax_limit_min") );

    UTILS_ASSERT0(
      gc.exists("ax_limit_max"),
      "in CNOC::setup_classes(gc) missing key: ``ax_limit_max''\n"
    );
    ax_limit_max.setup( gc("ax_limit_max") );

    UTILS_ASSERT0(
      gc.exists("ay_limit_min"),
      "in CNOC::setup_classes(gc) missing key: ``ay_limit_min''\n"
    );
    ay_limit_min.setup( gc("ay_limit_min") );

    UTILS_ASSERT0(
      gc.exists("ay_limit_max"),
      "in CNOC::setup_classes(gc) missing key: ``ay_limit_max''\n"
    );
    ay_limit_max.setup( gc("ay_limit_max") );

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
  CNOC::setup_user_classes( GenericContainer const & gc ) {
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
  CNOC::setup_user_mapped_functions( GenericContainer const & gc_data ) {
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
  CNOC::setup_controls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    UTILS_ASSERT0(
      gc_data.exists("Controls"),
      "CNOC::setup_classes: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    jsControl.setup( gc("jsControl") );
    jnControl.setup( gc("jnControl") );
    // setup iterative solver
    this->setup_control_solver( gc_data );
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
  CNOC::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "CNOC::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pToolPath2D"),
      "in CNOC::setup_pointers(gc) cant find key `pToolPath2D' in gc\n"
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
  CNOC::info_classes() const {
    int msg_level = 3;

    m_console->message("\nControls\n",msg_level);
    m_console->message( jsControl.info(),msg_level);
    m_console->message( jnControl.info(),msg_level);

    m_console->message("\nConstraints LT\n",msg_level);
    m_console->message( timePositive.info(),msg_level);
    m_console->message( vLimit.info(),msg_level);
    m_console->message( PathFollowingTolerance_min.info(),msg_level);
    m_console->message( PathFollowingTolerance_max.info(),msg_level);
    m_console->message( as_limit_min.info(),msg_level);
    m_console->message( as_limit_max.info(),msg_level);
    m_console->message( an_limit_min.info(),msg_level);
    m_console->message( an_limit_max.info(),msg_level);
    m_console->message( ax_limit_min.info(),msg_level);
    m_console->message( ax_limit_max.info(),msg_level);
    m_console->message( ay_limit_min.info(),msg_level);
    m_console->message( ay_limit_max.info(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    m_console->message( "\nUser function `pToolPath2D`\n",msg_level);
    m_console->message( pToolPath2D->info(),msg_level);

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

    this->setup_parameters( gc );
    this->setup_classes( gc );
    this->setup_user_mapped_functions( gc );
    this->setup_user_classes( gc );
    this->setup_pointers( gc );
    this->setup_BC( gc );
    this->setup_controls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pToolPath2D, gc );

    // Begin: User Setup Code
    // End: User Setup Code

    this->info_BC();
    this->info_classes();
    // this->info(); stampato dopo GUESS
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

  // save model parameters
  void
  CNOC::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: CNOC.cc
