/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3.cc                                         |
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

#include "PointMassCarModel_3.hh"
#include "PointMassCarModel_3_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace PointMassCarModel_3Define {

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
    "alpha",
    "V",
    "Omega",
    "fx",
    "sqrt_inv_Vseg",
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
    "v__fx",
    "v__Omega",
    nullptr
  };

  char const *namesQvars[numQvars+1] = {
    "zeta",
    "L",
    "ssSegmentMin",
    "ssSegmentMax",
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
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "v__fxControl",
    "v__OmegaControl",
    "AdherenceEllipse",
    "RoadLeftBorder",
    "RoadRightBorder",
    "PowerLimit",
    "Kappa",
    "leftWidth",
    "rightWidth",
    "xLane",
    "yLane",
    "theta",
    "xV",
    "yV",
    "xL",
    "yL",
    "xR",
    "yR",
    "fy",
    "mu_x",
    "mu_y",
    "Vseg",
    "Tseg",
    "zeta_dot_eq",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    "t",
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "Pmax",
    "V0",
    "Vguess",
    "g",
    "kD",
    "m",
    "p_epsi0",
    "p_epsi1",
    "wT",
    "wT0",
    "wT1",
    "mu__x__max",
    "mu__y__max",
    "up_epsi0",
    "up_epsi1",
    "v__Omega__max",
    "v__fx__max",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "AdherenceEllipse",
    "RoadLeftBorder",
    "RoadRightBorder",
    "PowerLimit",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "v__fxControl",
    "v__OmegaControl",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_V",
    "initial_s",
    "final_s",
    "cyclic_n",
    "cyclic_alpha",
    "cyclic_V",
    "cyclic_fx",
    "cyclic_Omega",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  PointMassCarModel_3::PointMassCarModel_3(
    string const   & name,
    Console const  * console,
    ThreadPoolBase * TP
  )
  : Discretized_Indirect_OCP( name, console, TP )
  // Controls
  , v__fxControl("v__fxControl")
  , v__OmegaControl("v__OmegaControl")
  // Constraints LT
  , AdherenceEllipse("AdherenceEllipse")
  , RoadLeftBorder("RoadLeftBorder")
  , RoadRightBorder("RoadRightBorder")
  , PowerLimit("PowerLimit")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // continuation
    this->ns_continuation_begin = 1;
    this->ns_continuation_end   = 2;
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

  PointMassCarModel_3::~PointMassCarModel_3() {
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
  PointMassCarModel_3::update_continuation(
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
      "PointMassCarModel_3::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 1: continuation_step_1( s ); break;
      case 2: continuation_step_2( s ); break;
      default:
        UTILS_ERROR(
          "PointMassCarModel_3::update_continuation( phase number={}, old_s={}, s={} )"
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
  PointMassCarModel_3::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "PointMassCarModel_3::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in PointMassCarModel_3::setup not all parameters are set!\n"
    );
  }

  void
  PointMassCarModel_3::setup_parameters( real_const_ptr Pars ) {
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
  PointMassCarModel_3::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "PointMassCarModel_3::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("AdherenceEllipse"),
      "in PointMassCarModel_3::setup_classes(gc) missing key: ``AdherenceEllipse''\n"
    );
    AdherenceEllipse.setup( gc("AdherenceEllipse") );

    UTILS_ASSERT0(
      gc.exists("RoadLeftBorder"),
      "in PointMassCarModel_3::setup_classes(gc) missing key: ``RoadLeftBorder''\n"
    );
    RoadLeftBorder.setup( gc("RoadLeftBorder") );

    UTILS_ASSERT0(
      gc.exists("RoadRightBorder"),
      "in PointMassCarModel_3::setup_classes(gc) missing key: ``RoadRightBorder''\n"
    );
    RoadRightBorder.setup( gc("RoadRightBorder") );

    UTILS_ASSERT0(
      gc.exists("PowerLimit"),
      "in PointMassCarModel_3::setup_classes(gc) missing key: ``PowerLimit''\n"
    );
    PowerLimit.setup( gc("PowerLimit") );

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
  PointMassCarModel_3::setup_user_classes( GenericContainer const & gc ) {
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
  PointMassCarModel_3::setup_user_mapped_functions( GenericContainer const & gc_data ) {
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
  PointMassCarModel_3::setup_controls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    UTILS_ASSERT0(
      gc_data.exists("Controls"),
      "PointMassCarModel_3::setup_classes: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    v__fxControl.setup( gc("v__fxControl") );
    v__OmegaControl.setup( gc("v__OmegaControl") );
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
  PointMassCarModel_3::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "PointMassCarModel_3::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pRoad"),
      "in PointMassCarModel_3::setup_pointers(gc) cant find key `pRoad' in gc\n"
    );
    pRoad = gc("pRoad").get_pointer<Road2D*>();
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  PointMassCarModel_3::info_model( integer level ) const {
    if ( m_console == nullptr || m_console->get_level() < level ) return;

    // ==================================================================
    this->info( level );
    this->info_BC( level );

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "Controls penalties/barriers" ), level);
    m_console->message( v__fxControl.info(),level);
    m_console->message( v__OmegaControl.info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "Constraints type LT" ), level);
    m_console->message( AdherenceEllipse.info(),level);
    m_console->message( RoadLeftBorder.info(),level);
    m_console->message( RoadRightBorder.info(),level);
    m_console->message( PowerLimit.info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No constraints 1D" ), level);

    // ==================================================================

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No user class (local)" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "User class (pointer)" ), level);
    m_console->PINS_COLOR_REVERSED( fmt::format(
      "{:^73}\n", "User function `pRoad`"
    ), level );
    m_console->message( pRoad->info(),level);

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
  PointMassCarModel_3::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("PointMassCarModel_3::setup, Debug");

    this->setup_parameters( gc );
    this->setup_classes( gc );
    this->setup_user_mapped_functions( gc );
    this->setup_user_classes( gc );
    this->setup_pointers( gc );
    this->setup_BC( gc );
    this->setup_controls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pRoad, gc );

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
  PointMassCarModel_3::get_names( GenericContainer & out ) const {
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
  PointMassCarModel_3::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: PointMassCarModel_3.cc
