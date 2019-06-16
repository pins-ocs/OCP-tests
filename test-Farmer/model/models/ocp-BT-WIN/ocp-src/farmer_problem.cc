/*-----------------------------------------------------------------------*\
 |  file: farmer_problem.cc                                              |
 |                                                                       |
 |  version: 1.0   date 16/6/2019                                        |
 |                                                                       |
 |  Copyright (C) 2019                                                   |
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

#include "farmer_problem.hh"
#include "farmer_problem_Pars.hh"

#include <time.h> /* time_t, struct tm, time, localtime, asctime */

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace farmer_problemDefine {

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

  char const *namesConstraint1D[numConstraint1D+1] = {
    "LimitX2X4",
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
  farmer_problem::farmer_problem(
    string const & name,
    ostream_type * _pCout,
    integer        _infoLevel
  )
  : Discretized_Indirect_OCP(name,_pCout,_infoLevel)
  , pSolver(nullptr)
  , redirectToGC(false)
  , u_solve_iterative(true)
  // Controls
  , x1__oControl("x1__oControl")
  , x2__oControl("x2__oControl")
  , x3__oControl("x3__oControl")
  , x4__oControl("x4__oControl")
  // Constraints 1D
  , LimitX2X4("LimitX2X4")
  // Constraints 2D
  // User classes
  {
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
  }

  farmer_problem::~farmer_problem() {
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
  farmer_problem::updateContinuation( integer phase, real_type s ) {
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
  farmer_problem::setupParameters( GenericContainer const & gc ) {
    bool allfound = true;
    for ( integer i = 0; i < numModelPars; ++i ) {
      bool ok = gc.exists( namesModelPars[i] );
      if ( !ok ) {
        std::cerr
          << MSG_ERROR( "Missing parameter: '" << namesModelPars[i] << "'" )
          << '\n';
      } else {
        ModelPars[i] = gc(namesModelPars[i]).get_number();
      }
      allfound = allfound && ok;
    }
    ASSERT(
      allfound,
      "in farmer_problem::setup not all parameters are set!"
    );
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
  farmer_problem::setupClasses( GenericContainer const & gc ) {

    // Initialize Constraints 1D
    ASSERT(
      gc.exists("LimitX2X4"),
      "in farmer_problem::setupClasses(gc) missing key: ``LimitX2X4''"
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
  farmer_problem::setupUserClasses( GenericContainer const & gc ) {
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
  farmer_problem::setupUserMappedFunctions( GenericContainer const & gc ) {
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
  farmer_problem::setupControls( GenericContainer const & gc ) {
    // initialize Controls
    x1__oControl.setup( gc("x1__oControl") );
    x2__oControl.setup( gc("x2__oControl") );
    x3__oControl.setup( gc("x3__oControl") );
    x4__oControl.setup( gc("x4__oControl") );
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
  farmer_problem::setupPointers( GenericContainer const & gc_data ) {

    ASSERT(
      gc_data.exists("Pointers"),
      "farmer_problem::setupPointers: Missing key `Pointers` in data"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    ASSERT(
      gc.exists("pMesh"),
      "in farmer_problem::setupPointers(gc) cant find key `pMesh' in gc"
    );
    pMesh = gc("pMesh").get_pointer<MeshStd*>();
  }

  /* --------------------------------------------------------------------------
  //            _               ____                                _
  //   ___  ___| |_ _   _ _ __ |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  //  / __|/ _ \ __| | | | '_ \| |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  //  \__ \  __/ |_| |_| | |_) |  __/ (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  //  |___/\___|\__|\__,_| .__/|_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  //                     |_|
  */
  void
  farmer_problem::setupParameters( real_type const Pars[] ) {
    std::copy( Pars, Pars + numModelPars, ModelPars );
  }

  /* --------------------------------------------------------------------------
  //   _        __        ____ _
  //  (_)_ __  / _| ___  / ___| | __ _ ___ ___  ___  ___
  //  | | '_ \| |_ / _ \| |   | |/ _` / __/ __|/ _ \/ __|
  //  | | | | |  _| (_) | |___| | (_| \__ \__ \  __/\__ \
  //  |_|_| |_|_|  \___/ \____|_|\__,_|___/___/\___||___/
  */
  void
  farmer_problem::infoClasses( ostream_type & stream ) const {

    stream << "\nControls\n";
    x1__oControl . info(stream);
    x2__oControl . info(stream);
    x3__oControl . info(stream);
    x4__oControl . info(stream);

    stream << "\nConstraints 1D\n";
    LimitX2X4 . info(stream);

    stream << "\nUser class (pointer)\n";
    stream << "User function `pMesh`: ";
    pMesh->info( stream );

    stream << "\nModel Parameters\n";
    for ( integer i = 0; i < numModelPars; ++i )
      stream
        << setw(40) << setfill('.') << namesModelPars[i]
        << " = " << ModelPars[i] << setfill(' ') << '\n';

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
  farmer_problem::setup( GenericContainer const & gc ) {

    redirectToGC = gc.exists("RedirectStreamToString") && gc("RedirectStreamToString").get_bool();

    if ( redirectToGC ) {
      ss_redirected_stream.str("");
      changeStream(&ss_redirected_stream);
    } else {
      changeStream(&cout);
    }


    this->setupParameters( gc("Parameters", "farmer_problem::setup: Missing key `Parameters` in data" ) );
    this->setupClasses( gc("Constraints", "farmer_problem::setup: Missing key `Constraints` in data" ) );
    // this->setupUserMappedFunctions( gc("MappedObjects","farmer_problem::setup: Missing key `MappedObjects` in data") ); // no mapped objects
    this->setupControls( gc("Controls", "farmer_problem::setup: Missing key `Controls` in data" ) );
    this->setupUserClasses( gc );
    this->setupPointers( gc );
    this->setupBC( gc("BoundaryConditions", "farmer_problem::setup: Missing key `BoundaryConditions` in data") );

    // setup model
    if ( gc.exists("InfoLevel") ) this->changeInfoLevel(gc("InfoLevel").get_as_int("farmer_problem::setup, InfoLevel "));
    if ( Indirect_OCP::infoLevel >= 2 ) this->infoBC( *Indirect_OCP::pCout );
    if ( Indirect_OCP::infoLevel >= 3 ) this->infoClasses( *Indirect_OCP::pCout );
    GenericContainer const & gc_control = gc("ControlSolver");
    this->setupControlSolver(gc_control);
    gc_control.get_if_exists( "Iterative", this->u_solve_iterative );

    // setup nonlinear system with object handling mesh domain
    GenericContainer const & gc_solver = gc("Solver");
    gc_solver.get_if_exists( "ns_continuation_begin", this->ns_continuation_begin );
    gc_solver.get_if_exists( "ns_continuation_end", this->ns_continuation_end );
    this->setup( pMesh, gc_solver );

    // setup solver
    if ( gc_solver("solver").get_string() == "Hyness" ) pSolver = &this->solverHyness;
    else                                                pSolver = &this->solverNewtonDumped;

    pSolver->setup( this, Indirect_OCP::pCout, Indirect_OCP::infoLevel );
    pSolver->setSolverParameters( gc_solver );
    pSolver->allocate();

    // chek if use Finite Differece
    bool useFD = gc.exists("FiniteDifferenceJacobian") ?
                 gc("FiniteDifferenceJacobian").get_bool() : false;
    this->use_finite_difference( useFD );

    if ( Indirect_OCP::infoLevel >= 2 ) this->info( *Indirect_OCP::pCout );
  }

  /* --------------------------------------------------------------------------
  //             _
  //   ___  ___ | |_   _____
  //  / __|/ _ \| \ \ / / _ \
  //  \__ \ (_) | |\ V /  __/
  //  |___/\___/|_| \_/ \___|
  */
  bool
  farmer_problem::solve() {
    bool ok   = false;
    lastError = "no error";
    try {

      // start timing
      pSolver->resetStatistic();
      pSolver->reset();
      pSolver->tic();

      // accrocchio
      try {
        pSolver->solve(pSolver->getMaxIter());
        pSolver->accumulateIter();
      }
      catch ( exception const & exc ) {
        lastError = exc.what();
        if ( Indirect_OCP::infoLevel >= 1 )
          (*Indirect_OCP::pCout)
            << "\n\n\nERROR: " << lastError << '\n';
      }
      catch ( char const exc[] ) {
        lastError = exc;
        if ( Indirect_OCP::infoLevel >= 1 )
          (*Indirect_OCP::pCout)
            << "\n\n\nERROR: " << lastError << '\n';
      }
      catch (...) {
        lastError = "farmer_problem::solver, fatal: unknown error";
        if ( Indirect_OCP::infoLevel >= 1 )
          (*Indirect_OCP::pCout)
            << "\n\n\nERROR: " << lastError << '\n';
      }

      ok = pSolver->isConverged();

      pSolver->toc(); // end timing
      if ( Indirect_OCP::infoLevel >= 1 ) pSolver->statistic(*Indirect_OCP::pCout);
    }
    catch ( exception const & exc ) {
      lastError = exc.what();
    }
    catch ( char const exc[] ) {
      lastError = exc;
    }
    catch (...) {
      lastError = "farmer_problem::solver, fatal: unknown error";
    }
    return ok;
  }

  /* --------------------------------------------------------------------------
  //              _                 _       _   _
  //    __ _  ___| |_     ___  ___ | |_   _| |_(_) ___  _ __
  //   / _` |/ _ \ __|   / __|/ _ \| | | | | __| |/ _ \| '_ \
  //  | (_| |  __/ |_    \__ \ (_) | | |_| | |_| | (_) | | | |
  //   \__, |\___|\__|___|___/\___/|_|\__,_|\__|_|\___/|_| |_|
  //   |___/        |_____|
  */
  void
  farmer_problem::get_solution_base( GenericContainer & gc_solution ) {

    GenericContainer & nlss = gc_solution["nonlinear_system_solver"];
    GenericContainer & cont = nlss["continuation"];

    gc_solution["solver_message"] = lastError;
    gc_solution["model_name"]     = "farmer_problem";
    gc_solution["cpu_time"]       = pSolver->elapsedMilliseconds();
    gc_solution["converged"]      = pSolver->isConverged();
    gc_solution["lapack"]         = ALGLIN_LAPACK_NAME;
    gc_solution["num_equations"]  = pSolver->numEquations();
    gc_solution["solution_saved"] = true;
    gc_solution["solver_type"]    = this->getSolutionMethod();

    nlss["iterations"]           = pSolver->totalIterations();
    nlss["tolerance"]            = pSolver->getTolerance();
    if ( pSolver->isConverged() ) nlss["message"] = "no message";
    else                          nlss["message"] = pSolver->whatHappened();
    nlss["max_iter"]             = pSolver->getMaxIter();
    nlss["max_step_iter"]        = pSolver->getMaxStepIter();
    nlss["max_accumulated_iter"] = pSolver->getMaxAccumulatedIter();
    cont["initial_step"]         = pSolver->getContinuationInitialStep();
    cont["min_step"]             = pSolver->getContinuationMinStep();
    cont["reduce_factor"]        = pSolver->getContinuationReduceFactor();
    cont["augment_factor"]       = pSolver->getContinuationAugmentFactor();
    cont["few_iterations"]       = pSolver->getContinuationFewIterations();
  }

  void
  farmer_problem::get_solution( GenericContainer & gc_solution ) {
    get_solution_base( gc_solution );
    this->save( pSolver->solution(), gc_solution );
  }

  void
  farmer_problem::get_solution_as_spline( Splines::SplineSet & SplineSet ) {
    GenericContainer gc;
    this->save_as_data_for_spline( pSolver->solution(), gc );
    SplineSet.build( gc );
  }

  void
  farmer_problem::get_solution_as_guess( GenericContainer & gc_guess ) {
    this->save_as_guess( pSolver->solution(), gc_guess );
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
  farmer_problem::get_names( GenericContainer & out ) const {
    GenericContainer::vec_string_type & X_names =
      out["state_names"].set_vec_string();
    for ( integer i = 0; i < numXvars; ++i )
      X_names.push_back(namesXvars[i]);

    GenericContainer::vec_string_type & LM_names =
      out["lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numLvars; ++i )
      LM_names.push_back(namesLvars[i]);

    GenericContainer::vec_string_type & U_names =
      out["control_names"].set_vec_string();
    for ( integer i = 0; i < numUvars; ++i )
      U_names.push_back(namesUvars[i]);

    GenericContainer::vec_string_type & Q_names =
      out["mesh_variable_names"].set_vec_string();
    for ( integer i = 0; i < numQvars; ++i )
      Q_names.push_back(namesQvars[i]);

    GenericContainer::vec_string_type & P_names =
      out["parameter_names"].set_vec_string();
    for ( integer i = 0; i < numPvars; ++i )
      P_names.push_back(namesPvars[i]);

    GenericContainer::vec_string_type & OMEGA_names =
      out["bc_lagrange_multiplier_names"].set_vec_string();
    for ( integer i = 0; i < numOMEGAvars; ++i )
      OMEGA_names.push_back(namesOMEGAvars[i]);

    GenericContainer::vec_string_type & PP_names =
      out["post_processing_names"].set_vec_string();
    for ( integer i = 0; i < numPostProcess; ++i )
      PP_names.push_back(namesPostProcess[i]);

    for ( integer i = 0; i < numIntegratedPostProcess; ++i )
      PP_names.push_back(namesIntegratedPostProcess[i]);

    GenericContainer::vec_string_type & model_names =
      out["model_names"].set_vec_string();
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
  farmer_problem::diagnostic( GenericContainer const & gc ) {

    // DA RIFARE--------------

    // If required save function and jacobian
    //if ( gc.exists("DumpFile") )
    //  this->dumpFunctionAndJacobian( pSolver->solution(),
    //                                 gc("DumpFile").get_string() );

    //bool do_diagnosis = gc.exists("Doctor") ? gc("Doctor").get_bool() : false;
    //if ( do_diagnosis )
    //  this->diagnosis( pSolver->solution(), gc["diagnosis"] );

    bool do_jac_check = gc.exists("JacobianCheck") ? gc("JacobianCheck").get_bool() : false;
    if ( do_jac_check ) {
      real_type epsi = 1e-5;
      gc.get_if_exists("JacobianCheck_epsilon",epsi);
      this->checkJacobian( pSolver->solution(), epsi, *Indirect_OCP::pCout );
    }
  }

  // save model parameters
  void
  farmer_problem::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i]; 

  }

}

// EOF: farmer_problem.cc
