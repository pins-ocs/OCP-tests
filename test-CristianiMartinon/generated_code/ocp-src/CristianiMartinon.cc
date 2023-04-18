/*-----------------------------------------------------------------------*\
 |  file: CristianiMartinon.cc                                           |
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

#include "CristianiMartinon.hh"
#include "CristianiMartinon_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace CristianiMartinonDefine {

  using GenericContainerNamespace::vec_string_type;

  /*
  //   _ __   __ _ _ __ ___   ___  ___
  //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | | | | (_| | | | | | |  __/\__ \
  //  |_| |_|\__,_|_| |_| |_|\___||___/
  //
  */

  char const *namesXvars[numXvars+1] = {
    "x",
    "y",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    "lambda2__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "u",
    nullptr
  };

  char const *namesQvars[numQvars+1] = {
    "zeta",
    nullptr
  };

  char const *namesPvars[numPvars+1] = {
    "T",
    nullptr
  };

  char const *namesOMEGAvars[numOMEGAvars+1] = {
    "omega1__xo",
    "omega2__xo",
    "omega3__xo",
    "omega4__xo",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "Tpositive",
    "Tpositive_D",
    "Tpositive_DD",
    "xguess",
    "yguess",
    "vel",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "Tguess",
    "WY",
    "x_f",
    "x_i",
    "y_f",
    "y_i",
    "ymax_guess",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "Tpositive",
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
    "initial_x",
    "initial_y",
    "final_x",
    "final_y",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  CristianiMartinon::CristianiMartinon(
    string const   & name,
    Console const  * console,
    ThreadPoolBase * TP
  )
  : Discretized_Indirect_OCP( name, console, TP )
  // Controls
  // Constraints LT
  , Tpositive("Tpositive")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // continuation
    this->ns_continuation_begin = 1;
    this->ns_continuation_end   = 1;
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

  CristianiMartinon::~CristianiMartinon() {
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
  CristianiMartinon::update_continuation(
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
      "CristianiMartinon::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 1: continuation_step_1( s ); break;
      default:
        UTILS_ERROR(
          "CristianiMartinon::update_continuation( phase number={}, old_s={}, s={} )"
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
  CristianiMartinon::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "CristianiMartinon::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in CristianiMartinon::setup not all parameters are set!\n"
    );
  }

  void
  CristianiMartinon::setup_parameters( real_const_ptr Pars ) {
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
  CristianiMartinon::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "CristianiMartinon::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("Tpositive"),
      "in CristianiMartinon::setup_classes(gc) missing key: ``Tpositive''\n"
    );
    Tpositive.setup( gc("Tpositive") );

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
  CristianiMartinon::setup_user_classes( GenericContainer const & gc ) {
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
  CristianiMartinon::setup_user_mapped_functions( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("MappedObjects"),
      "CristianiMartinon::setup_classes: Missing key `MappedObjects` in data\n"
    );
    GenericContainer const & gc = gc_data("MappedObjects");

    // Initialize user mapped functions

    UTILS_ASSERT0(
      gc.exists("pos"),
      "in CristianiMartinon::setup_user_mapped_functions(gc) missing key: ``pos''\n"
    );
    pos.setup( gc("pos") );
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
  CristianiMartinon::setup_controls( GenericContainer const & gc_data ) {
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
  CristianiMartinon::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "CristianiMartinon::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pMesh"),
      "in CristianiMartinon::setup_pointers(gc) cant find key `pMesh' in gc\n"
    );
    pMesh = gc("pMesh").get_pointer<MeshStd*>();
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  CristianiMartinon::info_model( integer level ) const {
    if ( m_console == nullptr || m_console->get_level() < level ) return;

    // ==================================================================
    this->info( level );
    this->info_BC( level );

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No control penalties/barriers" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "Constraints type LT" ), level);
    m_console->message( Tpositive.info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No constraints 1D" ), level);

    // ==================================================================

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "No user class (local)" ), level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "User class (pointer)" ), level);
    m_console->PINS_COLOR_REVERSED( fmt::format(
      "{:^73}\n", "User function `pMesh`"
    ), level );
    m_console->message( pMesh->info(),level);

    // ==================================================================
    m_console->PINS_COLOR_TITLE( fmt::format( "+{:.^71}+\n", "User mapped functions" ), level);
    m_console->message( fmt::format( "`pos' mapped with: {}\n",  pos.info() ), level );

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
  CristianiMartinon::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("CristianiMartinon::setup, Debug");

    this->setup_parameters( gc );
    this->setup_classes( gc );
    this->setup_user_mapped_functions( gc );
    this->setup_user_classes( gc );
    this->setup_pointers( gc );
    this->setup_BC( gc );
    this->setup_controls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pMesh, gc );

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
  CristianiMartinon::get_names( GenericContainer & out ) const {
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
  CristianiMartinon::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: CristianiMartinon.cc
