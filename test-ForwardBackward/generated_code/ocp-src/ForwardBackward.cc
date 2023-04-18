/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward.cc                                             |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace ForwardBackwardDefine {

  using GenericContainerNamespace::vec_string_type;

  /*
  //   _ __   __ _ _ __ ___   ___  ___
  //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | | | | (_| | | | | | |  __/\__ \
  //  |_| |_|\__,_|_| |_| |_|\___||___/
  //
  */

  char const *namesXvars[numXvars+1] = {
    "v",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "a",
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
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "LimitV_min",
    "LimitV_max",
    "LimitA_min",
    "LimitA_max",
    "LimitE",
    "curvature",
    "xTrajectory",
    "yTrajectory",
    "heading",
    "ax",
    "ay",
    "ELL",
    "E_max",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    "time",
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "E_epsi0",
    "E_epsi1",
    "E_max",
    "E_tol0",
    "E_tol1",
    "WA",
    "a_max",
    "a_min",
    "c0",
    "c0_0",
    "c0_1",
    "c1",
    "c1_0",
    "c1_1",
    "epsilon",
    "v0",
    "v1",
    "v_max",
    "v_min",
    "wT",
    "epsilon0",
    "epsilon1",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "LimitV_min",
    "LimitV_max",
    "LimitA_min",
    "LimitA_max",
    "LimitE",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_v",
    "final_v",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  ForwardBackward::ForwardBackward(
    string const   & name,
    Console const  * console,
    ThreadPoolBase * TP
  )
  : Discretized_Indirect_OCP( name, console, TP )
  // Controls
  // Constraints LT
  , LimitV_min("LimitV_min")
  , LimitV_max("LimitV_max")
  , LimitA_min("LimitA_min")
  , LimitA_max("LimitA_max")
  , LimitE("LimitE")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = true;

    // continuation
    this->ns_continuation_begin = 1;
    this->ns_continuation_end   = 3;
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

  ForwardBackward::~ForwardBackward() {
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
  ForwardBackward::update_continuation(
    integer   phase,
    real_type old_s,
    real_type s
  ) {
    int msg_level = 3;
    m_console->message( fmt::format(
      "\nContinuation step N.{} s={}, ds={}, old_s={}\n",
      phase,
      fmt::format("{:.5}", s),
      fmt::format("{:.5}", s-old_s),
      fmt::format("{:.5}", old_s)
    ), msg_level );
    UTILS_ASSERT(
      0 <= old_s && old_s < s && s <= 1,
      "ForwardBackward::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 1: continuation_step_1( s ); break;
      case 2: continuation_step_2( s ); break;
      case 3: continuation_step_3( s ); break;
      default:
        UTILS_ERROR(
          "ForwardBackward::update_continuation( phase number={}, old_s={}, s={} )"
          " phase N.{} is not defined\n",
          phase, old_s, s, phase
        );
    }
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
  ForwardBackward::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "ForwardBackward::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in ForwardBackward::setup not all parameters are set!\n"
    );
  }

  void
  ForwardBackward::setup_parameters( real_const_ptr Pars ) {
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
  ForwardBackward::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "ForwardBackward::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("LimitV_min"),
      "in ForwardBackward::setup_classes(gc) missing key: ``LimitV_min''\n"
    );
    LimitV_min.setup( gc("LimitV_min") );

    UTILS_ASSERT0(
      gc.exists("LimitV_max"),
      "in ForwardBackward::setup_classes(gc) missing key: ``LimitV_max''\n"
    );
    LimitV_max.setup( gc("LimitV_max") );

    UTILS_ASSERT0(
      gc.exists("LimitA_min"),
      "in ForwardBackward::setup_classes(gc) missing key: ``LimitA_min''\n"
    );
    LimitA_min.setup( gc("LimitA_min") );

    UTILS_ASSERT0(
      gc.exists("LimitA_max"),
      "in ForwardBackward::setup_classes(gc) missing key: ``LimitA_max''\n"
    );
    LimitA_max.setup( gc("LimitA_max") );

    UTILS_ASSERT0(
      gc.exists("LimitE"),
      "in ForwardBackward::setup_classes(gc) missing key: ``LimitE''\n"
    );
    LimitE.setup( gc("LimitE") );

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
  ForwardBackward::setup_user_classes( GenericContainer const & gc ) {
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
  ForwardBackward::setup_user_mapped_functions( GenericContainer const & gc_data ) {
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
  ForwardBackward::setup_controls( GenericContainer const & gc_data ) {
    // no Control penalties
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
  ForwardBackward::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "ForwardBackward::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pTrajectory"),
      "in ForwardBackward::setup_pointers(gc) cant find key `pTrajectory' in gc\n"
    );
    pTrajectory = gc("pTrajectory").get_pointer<Path2D*>();
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  ForwardBackward::info_model( integer level ) const {
    if ( m_console == nullptr || m_console->get_level() < level ) return;

    // ==================================================================
    this->info( level );
    this->info_BC( level );

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No control penalties/barriers" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "Constraints type LT" ), level);
    m_console->message( LimitV_min.info(),level);
    m_console->message( LimitV_max.info(),level);
    m_console->message( LimitA_min.info(),level);
    m_console->message( LimitA_max.info(),level);
    m_console->message( LimitE.info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No constraints 1D" ), level);

    // ==================================================================

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No user class (local)" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "User class (pointer)" ), level);
    m_console->PINS_COLOR_REVERSED( fmt::format(
      "{:^73}\n", "User function `pTrajectory`"
    ), level );
    m_console->message( pTrajectory->info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No user mapped functions" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "MODEL PARAMETERS" ), level);
    for ( integer i = 0; i < numModelPars; ++i ) {
      m_console->PINS_COLOR_REVERSED( fmt::format(
        "|{:.>41} = {:.<27}|\n",
        fmt::format( " {}", namesModelPars[i] ),
        fmt::format( "{:.5} ", ModelPars[i] )
      ), level );
    }
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "END" ), level);

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
  ForwardBackward::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("ForwardBackward::setup, Debug");

    this->setup_parameters( gc );
    this->setup_classes( gc );
    this->setup_user_mapped_functions( gc );
    this->setup_user_classes( gc );
    this->setup_pointers( gc );
    this->setup_BC( gc );
    this->setup_controls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pTrajectory, gc );

    // Begin: User Setup Code
    // End: User Setup Code
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
  ForwardBackward::get_names( GenericContainer & out ) const {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & X_names = out["state_names"].set_vec_string();
    X_names.reserve(numXvars);
    for ( integer i = 0; i < numXvars; ++i ) X_names.push_back(namesXvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & LM_names = out["lagrange_multiplier_names"].set_vec_string();
    LM_names.reserve(numLvars);
    for ( integer i = 0; i < numLvars; ++i ) LM_names.push_back(namesLvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & U_names = out["control_names"].set_vec_string();
    U_names.reserve(numUvars);
    for ( integer i = 0; i < numUvars; ++i ) U_names.push_back(namesUvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & Q_names = out["mesh_variable_names"].set_vec_string();
    Q_names.reserve(numQvars);
    for ( integer i = 0; i < numQvars; ++i ) Q_names.push_back(namesQvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & P_names = out["parameter_names"].set_vec_string();
    P_names.reserve(numPvars);
    for ( integer i = 0; i < numPvars; ++i ) P_names.push_back(namesPvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & OMEGA_names = out["bc_lagrange_multiplier_names"].set_vec_string();
    OMEGA_names.reserve(numOMEGAvars);
    for ( integer i = 0; i < numOMEGAvars; ++i ) OMEGA_names.push_back(namesOMEGAvars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & PP_names = out["post_processing_names"].set_vec_string();
    PP_names.reserve(numPostProcess);
    for ( integer i = 0; i < numPostProcess; ++i ) PP_names.push_back(namesPostProcess[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    for ( integer i = 0; i < numIntegratedPostProcess; ++i )
      PP_names.push_back(namesIntegratedPostProcess[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    vec_string_type & model_names = out["model_names"].set_vec_string();
    model_names.reserve(numModelPars);
    for ( integer i = 0; i < numModelPars; ++i )
      model_names.push_back(namesModelPars[i]);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  }

  // save model parameters
  void
  ForwardBackward::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: ForwardBackward.cc
