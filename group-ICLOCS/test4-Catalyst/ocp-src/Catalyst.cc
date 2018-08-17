/*-----------------------------------------------------------------------*\
 |  file: Catalyst.cc                                                    |
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


#ifdef __GCC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "Catalyst.hh"
#include "Catalyst_Pars.hh"

#include <time.h> /* time_t, struct tm, time, localtime, asctime */

#ifdef __GCC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace CatalystDefine {

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
    nullptr
  };

  char const *namesOMEGAvars[numOMEGAvars+1] = {
    "omega1__xo",
    "omega2__xo",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "x1_i",
    "x2_i",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "uControl",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_x1",
    "initial_x2",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  Catalyst::Catalyst( string const             & name,
                      std::basic_ostream<char> * _pCout,
                      indexType                  _infoLevel )
  : Discretized_Indirect_OCP(name,_pCout,_infoLevel)
  , solver("CatalystSolver",_pCout,_infoLevel)
  , redirectToGC(false)
  // Controls
  , uControl("uControl")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    // Initialize to NaN all the ModelPars
    std::fill( ModelPars, ModelPars + numModelPars, alglin::NaN<valueType>() );

    // Initialize string of names
    setupNames( numPvars,                 namesPvars,
                numXvars,                 namesXvars,
                numLvars,                 namesLvars,
                numUvars,                 namesUvars,
                numQvars,                 namesQvars,
                numPostProcess,           namesPostProcess,
                numIntegratedPostProcess, namesIntegratedPostProcess,
                numBc,                    namesBc );
  }

  Catalyst::~Catalyst() {
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
  Catalyst::updateContinuation( indexType phase, valueType s ) {
    ASSERT( s >= 0 && s <= 1.0,
            "Catalyst::updateContinuation( phase = " << phase <<
            ", s = " << s << ") s must be in the interval [0,1]" );
    ASSERT( phase >= 0 && phase < 0,
            "Catalyst::updateContinuation( phase = " << phase <<
            ", s = " << s << ") phase must be in [0..0)" );
    switch ( phase ) {
      default: break;
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
  Catalyst::setupParameters( GenericContainer const & gc ) {
    bool allfound = true;
    for ( indexType i = 0; i < numModelPars; ++i ) {
      bool ok = gc.exists( namesModelPars[i] );
      if ( !ok ) {
        cerr << "Missing parameter: '" << namesModelPars[i] << "'\n";
      } else {
        ModelPars[i] = gc(namesModelPars[i]).get_number();
      }
      allfound = allfound && ok;
    }
    ASSERT( allfound, "in Catalyst::setup not all parameters are set!");
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
  Catalyst::setupClasses( GenericContainer const & gc ) {
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
  Catalyst::setupUserClasses( GenericContainer const & gc ) {
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
  Catalyst::setupUserMappedFunctions( GenericContainer const & gc ) {
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
  Catalyst::setupControls( GenericContainer const & gc ) {
    // initialize Controls

    { uControl.setup( gc("uControl")  ); }
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
  Catalyst::setupPointers( GenericContainer const & gc_data ) {

    ASSERT( gc_data.exists("Pointers"), "Catalyst::setup: Missing key `Pointers` in data" );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    ASSERT( gc.exists("pMesh"), "in Catalyst::setupPointers(gc) cant find key `pMesh' in gc" );
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
  Catalyst::setupParameters( valueConstPointer Pars ) {
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
  Catalyst::infoClasses( basic_ostream<char> & stream ) const {

    stream << "\nControls\n";
    uControl . info(stream);

    stream << "\nUser class (pointer)\n";
    stream << "User function `pMesh`: ";
    pMesh -> info( stream );

    stream << "\nModel Parameters\n";
    for ( indexType i = 0; i < numModelPars; ++i )
      stream << setw(40) << setfill('.') << namesModelPars[i]
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
  Catalyst::setup( GenericContainer const & gc ) {

    redirectToGC = gc.exists("RedirectStreamToString") && gc("RedirectStreamToString").get_bool();

    if ( redirectToGC ) {
      ss_redirected_stream.str("");
      changeStream(&ss_redirected_stream);
    } else {
      changeStream(&cout);
    }


    this->setupParameters( gc("Parameters", "Catalyst::setup: Missing key `Parameters` in data" ) );
    this->setupClasses( gc("Constraints", "Catalyst::setup: Missing key `Constraints` in data" ) );
    // this->setupUserMappedFunctions( gc("MappedObjects","Catalyst::setup: Missing key `MappedObjects` in data") ); // no mapped objects
    this->setupControls( gc("Controls", "Catalyst::setup: Missing key `Controls` in data" ) );
    this->setupUserClasses( gc );
    this->setupPointers( gc );
    this->setupBC( gc("BoundaryConditions", "Catalyst::setup: Missing key `BoundaryConditions` in data") );

    // setup model
    if ( gc.exists("InfoLevel") ) this->changeInfoLevel(gc("InfoLevel").get_as_int("Catalyst::setup, InfoLevel "));
    if ( Indirect_OCP::infoLevel >= 2 ) this->infoBC( *Indirect_OCP::pCout );
    if ( Indirect_OCP::infoLevel >= 3 ) this->infoClasses( *Indirect_OCP::pCout );

    if ( gc.exists("ControlSolutionMethod") ) {
      this->setControlSolutionMethod(gc("ControlSolutionMethod").get_as_int("Catalyst::setup, ControlSolutionMethod "));
    }
    if ( gc.exists("ControlSolutionMaxIter") ) {
      this->setControlSolutionMaxIter(gc("ControlSolutionMaxIter").get_as_int("Catalyst::setup, ControlSolutionMaxIter "));
    }
    if ( gc.exists("ControlSolutionTolerance") ) {
      this->setControlSolutionTolerance(gc("ControlSolutionTolerance").get_number());
    }
    if ( gc.exists("ControlSolutionRcond") ) {
      this->setControlSolutionRcond(gc("ControlSolutionRcond").get_number());
    }

    // setup nonlinear system with object handling mesh domain
    indexType LU_method = 0, LU_final_block = 0;
    gc.get_if_exists("LU_method",LU_method);
    gc.get_if_exists("Last_block",LU_final_block);
    this->setup( pMesh, LU_method, LU_final_block );

    // setup solver
    solver.setup( this, Indirect_OCP::pCout, Indirect_OCP::infoLevel );
    solver.setSolverParameters( gc("Solver", "in Catalyst::solve") );
    solver.allocate();

    // chek if use Finite Differece
    bool useFD = gc.exists("FiniteDifferenceJacobian") ?
                  gc("FiniteDifferenceJacobian").get_bool() : false;
    this->use_finite_difference( useFD );

    if ( Indirect_OCP::infoLevel >= 2 ) this->info( *Indirect_OCP::pCout );
  }

  /* --------------------------------------------------------------------------
  //    ____
  //   / ___|_   _  ___  ___ ___
  //  | |  _| | | |/ _ \/ __/ __|
  //  | |_| | |_| |  __/\__ \__ \
  //   \____|\__,_|\___||___/___/
  */
  void
  Catalyst::guess( GenericContainer const & gc ) {
    using GenericContainerNamespace::vec_real_type;
    bool set_zero = gc.exists("ResetGuess") && gc("ResetGuess").get_bool();
    if ( gc.exists("Guess") ) {
      this->guess( gc("Guess"),
                   set_zero,
                   solver.solution() );
    } else if ( gc.exists("SplineGuess") && gc("SplineGuess").get_bool() ) {
      valueConstPointer pars  = nullptr;
      valueConstPointer omega = nullptr;
      if ( gc.exists("ParsGuess")  ) {
        vec_real_type const & v_pars = gc("ParsGuess").get_vec_real();
        ASSERT( indexType(v_pars.size()) == dim_p,
                "Catalyst::set_guess, ParsGuess size = " << v_pars.size() <<
                " expected to be " << dim_p );
        pars = &v_pars.front();
      }
      if ( gc.exists("OmegaGuess")  ) {
        vec_real_type const & o_pars = gc("OmegaGuess").get_vec_real();
        ASSERT( indexType(o_pars.size()) == this->numOMEGA(),
                "Catalyst::set_guess, OmegaGuess size = " << o_pars.size() <<
                " expected to be " << this->numOMEGA() );
        omega = &o_pars.front();
      }
      Splines::SplineSet const * pSplset = gc("SplineGuessPdata").get_pointer<Splines::SplineSet const *>();
      this->guess( *pSplset,
                   pars,
                   omega,
                   set_zero,
                   solver.solution() );
    } else if ( gc.exists("Warm") && gc("Warm").get_bool() ) {
      // nothing to do
    } else {
      solver.zeroGuess(); // ricordarsi di azzerare
      solver.setGuess(); // da cambiare
    }
  }

  /* --------------------------------------------------------------------------
  //             _
  //   ___  ___ | |_   _____
  //  / __|/ _ \| \ \ / / _ \
  //  \__ \ (_) | |\ V /  __/
  //  |___/\___/|_| \_/ \___|
  */
  bool
  Catalyst::solve() {
    bool ok   = false;
    lastError = "no error";
    try {

      // start timing
      solver.resetStatistic();
      solver.reset();
      solver.tic();

      // accrocchio
      try {
        solver.solve(solver.getMaxIter());
        solver.accumulateIter();
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
        lastError = "Catalyst::solver, fatal: unknown error";
        if ( Indirect_OCP::infoLevel >= 1 )
          (*Indirect_OCP::pCout)
            << "\n\n\nERROR: " << lastError << '\n';
      }

      ok = solver.isConverged();

      solver.toc(); // end timing
      if ( Indirect_OCP::infoLevel >= 1 ) solver.statistic(*Indirect_OCP::pCout);
    }
    catch ( exception const & exc ) {
      lastError = exc.what();
    }
    catch ( char const exc[] ) {
      lastError = exc;
    }
    catch (...) {
      lastError = "Catalyst::solver, fatal: unknown error";
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
  Catalyst::get_solution_base( GenericContainer & gc_solution ) {

    GenericContainer & nlss = gc_solution["nonlinear_system_solver"];
    GenericContainer & cont = nlss["continuation"];

    gc_solution["solver_message"]      = lastError;
    gc_solution["model_name"]          = "Catalyst";
    gc_solution["cpu_time"]            = solver.elapsedMilliseconds();
    gc_solution["converged"]           = solver.isConverged();
    gc_solution["lapack"]              = ALGLIN_LAPACK_NAME;
    gc_solution["num_equations"]       = solver.numEquations();
    gc_solution["solution_saved"]      = true;
    gc_solution["solver_type"]         = this->getSolutionMethod();
    gc_solution["control_solver_type"] = this->getControlSolutionMethod();

    nlss["iterations"]           = solver.totalIterations();
    nlss["tolerance"]            = solver.getTolerance();
    if ( solver.isConverged() ) nlss["message"] = "no message";
    else                        nlss["message"] = solver.whatHappened();
    nlss["max_iter"]             = solver.getMaxIter();
    nlss["max_step_iter"]        = solver.getMaxStepIter();
    nlss["max_accumulated_iter"] = solver.getMaxAccumulatedIter();
    cont["initial_step"]         = solver.getContinuationInitialStep();
    cont["min_step"]             = solver.getContinuationMinStep();
    cont["reduce_factor"]        = solver.getContinuationReduceFactor();
    cont["augment_factor"]       = solver.getContinuationAugmentFactor();
    cont["few_iterations"]       = solver.getContinuationFewIterations();
  }

  void
  Catalyst::get_solution( GenericContainer & gc_solution ) {
    get_solution_base( gc_solution );
    this->save( solver.solution(), gc_solution, nullptr );
  }

  void
  Catalyst::get_solution( GenericContainer   & gc_solution,
                          Splines::SplineSet & splines ) {
    get_solution_base( gc_solution );
    this->save( solver.solution(), gc_solution, &splines );
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
  Catalyst::get_names( GenericContainer & out ) const {
    GenericContainer::vec_string_type & X_names =
      out["state_names"].set_vec_string();
    for ( indexType i = 0; i < numXvars; ++i )
      X_names.push_back(namesXvars[i]);

    GenericContainer::vec_string_type & LM_names =
      out["lagrange_multiplier_names"].set_vec_string();
    for ( indexType i = 0; i < numLvars; ++i )
      LM_names.push_back(namesLvars[i]);

    GenericContainer::vec_string_type & U_names =
      out["control_names"].set_vec_string();
    for ( indexType i = 0; i < numUvars; ++i )
      U_names.push_back(namesUvars[i]);

    GenericContainer::vec_string_type & Q_names =
      out["mesh_variable_names"].set_vec_string();
    for ( indexType i = 0; i < numQvars; ++i )
      Q_names.push_back(namesQvars[i]);

    GenericContainer::vec_string_type & P_names =
      out["parameter_names"].set_vec_string();
    for ( indexType i = 0; i < numPvars; ++i )
      P_names.push_back(namesPvars[i]);

    GenericContainer::vec_string_type & OMEGA_names =
      out["bc_lagrange_multiplier_names"].set_vec_string();
    for ( indexType i = 0; i < numOMEGAvars; ++i )
      OMEGA_names.push_back(namesOMEGAvars[i]);

    GenericContainer::vec_string_type & PP_names =
      out["post_processing_names"].set_vec_string();
    for ( indexType i = 0; i < numPostProcess; ++i )
      PP_names.push_back(namesPostProcess[i]);

    for ( indexType i = 0; i < numIntegratedPostProcess; ++i )
      PP_names.push_back(namesIntegratedPostProcess[i]);

    GenericContainer::vec_string_type & model_names =
      out["model_names"].set_vec_string();
    for ( indexType i = 0; i < numModelPars; ++i )
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
  Catalyst::diagnostic( GenericContainer const & gc ) {

    // DA RIFARE--------------

    // If required save function and jacobian
    //if ( gc.exists("DumpFile") )
    //  this->dumpFunctionAndJacobian( solver.solution(),
    //                                  gc("DumpFile").get_string() );

    //bool do_diagnosis = gc.exists("Doctor") ? gc("Doctor").get_bool() : false;
    //if ( do_diagnosis )
    //  this->diagnosis( solver.solution(), gc["diagnosis"] );

    bool do_jac_check = gc.exists("JacobianCheck") ? gc("JacobianCheck").get_bool() : false;
    if ( do_jac_check ) {
      valueType epsi = 1e-5;
      gc.get_if_exists("JacobianCheck_epsilon",epsi);
      this->checkJacobian( solver.solution(), epsi, *Indirect_OCP::pCout );
    }
  }
}

// EOF: Catalyst.cc
