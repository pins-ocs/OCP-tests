/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz.cc                                            |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
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


// use pragma to include libraries
#include <MechatronixCore/MechatronixLibs.hh>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

#include <time.h> /* time_t, struct tm, time, localtime, asctime */

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace TwoPhaseSchwartzDefine {

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
    "x4",
    nullptr
  };

  char const *namesLvars[numLvars+1] = {
    "lambda1__xo",
    "lambda2__xo",
    "lambda3__xo",
    "lambda4__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "u1",
    "u2",
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
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "Time2",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "T2",
    "epsi0",
    "epsi1",
    "epsilon",
    "tol0",
    "tol1",
    "epsilon0",
    "epsilon1",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    "bound1",
    "bound2",
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "u1Control",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_x1",
    "initial_x2",
    "x13",
    "x24",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  TwoPhaseSchwartz::TwoPhaseSchwartz(
    string const & name,
    ThreadPool   * _TP,
    Console      * _pConsole
  )
  : Discretized_Indirect_OCP( name, _TP, _pConsole )
  // Controls
  , u1Control("u1Control")
  // Constraints 1D
  , bound1("bound1")
  , bound2("bound2")
  // Constraints 2D
  // User classes
  {
    this->U_solve_iterative = true;

    // continuation
    this->ns_continuation_begin = 0;
    this->ns_continuation_end   = 1;
    // Initialize to NaN all the ModelPars
    std::fill( ModelPars, ModelPars + numModelPars, alglin::NaN<real_type>() );

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
    //pSolver = &this->solverNewtonDumped;
    pSolver = &this->solverHyness;

    #ifdef LAPACK_WRAPPER_USE_OPENBLAS
    openblas_set_num_threads(1);
    goto_set_num_threads(1);
    #endif
  }

  TwoPhaseSchwartz::~TwoPhaseSchwartz() {
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
  TwoPhaseSchwartz::updateContinuation( integer phase, real_type s ) {
    LW_ASSERT(
      s >= 0 && s <= 1,
      "TwoPhaseSchwartz::updateContinuation( phase number = {}, s = {}) "
      "s must be in the interval [0,1]\n",
      phase, s
    );
    switch ( phase ) {
      case 0: continuationStep0( s ); break;
      default:
        LW_ERROR(
          "TwoPhaseSchwartz::updateContinuation( phase number = {}, s = {} )"
          " phase N.{} is not defined\n",
          phase, s, phase
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
  TwoPhaseSchwartz::setupParameters( GenericContainer const & gc_data ) {
    LW_ASSERT0(
      gc_data.exists("Parameters"),
      "TwoPhaseSchwartz::setupParameters: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Parameters");

    bool allfound = true;
    for ( integer i = 0; i < numModelPars; ++i ) {
      char const * namei = namesModelPars[i];
      if ( gc.exists( namei ) ) {
        ModelPars[i] = gc(namei).get_number();
      } else {
        pConsole->error( fmt::format( "Missing parameter: '{}'\n", namei ) );
        allfound = false;
      }
    }
    LW_ASSERT0(
      allfound, "in TwoPhaseSchwartz::setup not all parameters are set!\n"
    );
  }

  void
  TwoPhaseSchwartz::setupParameters( real_type const Pars[] ) {
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
  TwoPhaseSchwartz::setupClasses( GenericContainer const & gc_data ) {
    LW_ASSERT0(
      gc_data.exists("Constraints"),
      "TwoPhaseSchwartz::setupClasses: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    LW_ASSERT0(
      gc.exists("bound1"),
      "in TwoPhaseSchwartz::setupClasses(gc) missing key: ``bound1''\n"
    );
    bound1.setup( gc("bound1") );

    LW_ASSERT0(
      gc.exists("bound2"),
      "in TwoPhaseSchwartz::setupClasses(gc) missing key: ``bound2''\n"
    );
    bound2.setup( gc("bound2") );

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
  TwoPhaseSchwartz::setupUserClasses( GenericContainer const & gc ) {
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
  TwoPhaseSchwartz::setupUserMappedFunctions( GenericContainer const & gc_data ) {
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
  TwoPhaseSchwartz::setupControls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    LW_ASSERT0(
      gc_data.exists("Controls"),
      "TwoPhaseSchwartz::setupClasses: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    u1Control.setup( gc("u1Control") );
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
  TwoPhaseSchwartz::setupPointers( GenericContainer const & gc_data ) {

    LW_ASSERT0(
      gc_data.exists("Pointers"),
      "TwoPhaseSchwartz::setupPointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    LW_ASSERT0(
      gc.exists("pMesh"),
      "in TwoPhaseSchwartz::setupPointers(gc) cant find key `pMesh' in gc\n"
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
  TwoPhaseSchwartz::infoClasses() const {
    int msg_level = 3;
    ostringstream mstr;

    pConsole->message("\nControls\n",msg_level);
    mstr.str(""); u1Control.info(mstr);
    pConsole->message(mstr.str(),msg_level);

    pConsole->message("\nConstraints 1D\n",msg_level);
    mstr.str(""); bound1.info(mstr);
    pConsole->message(mstr.str(),msg_level);
    mstr.str(""); bound2.info(mstr);
    pConsole->message(mstr.str(),msg_level);

    pConsole->message("\nUser class (pointer)\n",msg_level);
    pConsole->message("User function `pMesh`: ",msg_level);
    mstr.str(""); pMesh->info(mstr);
    pConsole->message(mstr.str(),msg_level);

    pConsole->message("\nModel Parameters\n",msg_level);
    for ( integer i = 0; i < numModelPars; ++i ) {
      pConsole->message(
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
  TwoPhaseSchwartz::setup( GenericContainer const & gc ) {

    if ( gc.get_map_bool("RedirectStreamToString") ) {
      ss_redirected_stream.str("");
      pConsole->changeStream(&ss_redirected_stream);
    }

    this->setupParameters( gc );
    this->setupClasses( gc );
    this->setupUserMappedFunctions( gc );
    this->setupUserClasses( gc );
    this->setupPointers( gc );
    this->setupBC( gc );
    this->setupControls( gc );

    // setup nonlinear system with object handling mesh domain
    this->setup( pMesh, gc );
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
  TwoPhaseSchwartz::get_names( GenericContainer & out ) const {
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
  TwoPhaseSchwartz::diagnostic( GenericContainer const & gc ) {

    // DA RIFARE--------------

    // If required save function and jacobian
    //if ( gc.exists("DumpFile") )
    //  this->dumpFunctionAndJacobian( pSolver->solution(),
    //                                 gc("DumpFile").get_string() );

    //bool do_diagnosis = gc.get_map_bool("Doctor");
    //if ( do_diagnosis )
    //  this->diagnosis( pSolver->solution(), gc["diagnosis"] );

    real_type epsi = 1e-5;
    gc.get_if_exists("JacobianCheck_epsilon",epsi);
    if ( gc.get_map_bool("JacobianCheck") )
      this->checkJacobian( pSolver->solution(), epsi );
    if ( gc.get_map_bool("JacobianCheckFull") )
      this->checkJacobianFull( pSolver->solution(), epsi );
  }

  // save model parameters
  void
  TwoPhaseSchwartz::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: TwoPhaseSchwartz.cc
