/*-----------------------------------------------------------------------*\
 |  file: Farmer.cc                                                      |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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

#include "Farmer.hh"
#include "Farmer_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace FarmerDefine {

  using GenericContainerNamespace::vec_string_type;

  /*
  //   _ __   __ _ _ __ ___   ___  ___
  //  | '_ \ / _` | '_ ` _ \ / _ \/ __|
  //  | | | | (_| | | | | | |  __/\__ \
  //  |_| |_|\__,_|_| |_| |_|\___||___/
  //
  */

  char const *namesXvars[numXvars+1] = {
    "x1",
    "x2",
    "x3",
    "res",
    "x4",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    "lambda2__xo",
    "lambda3__xo",
    "lambda4__xo",
    "lambda5__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "x1__o",
    "x2__o",
    "x3__o",
    "x4__o",
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
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "x1__oControl",
    "x2__oControl",
    "x3__oControl",
    "x4__oControl",
    "LimitX2X4",
    "power_delivered",
    "power_required",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "P1",
    "P2",
    "res0",
    "t1",
    "t2",
    "tau__1",
    "tau__2",
    "tau__3",
    "tau__4",
    "tau__5",
    "w1",
    "w2",
    "w3",
    "w4",
    "wJ1",
    "wJ2",
    "wJ3",
    "wJ4",
    "wP",
    "x10",
    "x20",
    "x30",
    "x40",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "LimitX2X4",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "x1__oControl",
    "x2__oControl",
    "x3__oControl",
    "x4__oControl",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_x1",
    "initial_x2",
    "initial_x3",
    "initial_res",
    "initial_x4",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  Farmer::Farmer(
    string const   & name,
    integer          n_threads,
    Console const  * console
  )
  : Discretized_Indirect_OCP( name, n_threads, console )
  // Controls
  , x1__oControl("x1__oControl")
  , x2__oControl("x2__oControl")
  , x3__oControl("x3__oControl")
  , x4__oControl("x4__oControl")
  // Constraints LT
  , LimitX2X4("LimitX2X4")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = true;

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

  Farmer::~Farmer() {
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
  Farmer::update_continuation(
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
  Farmer::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "Farmer::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in Farmer::setup not all parameters are set!\n"
    );
  }

  void
  Farmer::setup_parameters( real_type const Pars[] ) {
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
  Farmer::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "Farmer::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("LimitX2X4"),
      "in Farmer::setup_classes(gc) missing key: ``LimitX2X4''\n"
    );
    LimitX2X4.setup( gc("LimitX2X4") );

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
  Farmer::setup_user_classes( GenericContainer const & gc ) {
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
  Farmer::setup_user_mapped_functions( GenericContainer const & gc_data ) {
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
  Farmer::setup_controls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    UTILS_ASSERT0(
      gc_data.exists("Controls"),
      "Farmer::setup_classes: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    x1__oControl.setup( gc("x1__oControl") );
    x2__oControl.setup( gc("x2__oControl") );
    x3__oControl.setup( gc("x3__oControl") );
    x4__oControl.setup( gc("x4__oControl") );
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
  Farmer::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "Farmer::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pMesh"),
      "in Farmer::setup_pointers(gc) cant find key `pMesh' in gc\n"
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
  Farmer::info_classes() const {
    int msg_level = 3;

    m_console->message("\nControls\n",msg_level);
    m_console->message( x1__oControl.info(),msg_level);
    m_console->message( x2__oControl.info(),msg_level);
    m_console->message( x3__oControl.info(),msg_level);
    m_console->message( x4__oControl.info(),msg_level);

    m_console->message("\nConstraints LT\n",msg_level);
    m_console->message( LimitX2X4.info(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    m_console->message( "\nUser function `pMesh`\n",msg_level);
    m_console->message( pMesh->info(),msg_level);

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
  Farmer::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("Farmer::setup, Debug");

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
  Farmer::get_names( GenericContainer & out ) const {
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
  Farmer::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: Farmer.cc
