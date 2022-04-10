/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic.cc                                                 |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


// use pragma to include libraries
#include <MechatronixCore/MechatronixLibs.hh>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace TyreDynamicDefine {

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
    "omega",
    "lambda",
    "p",
    "b",
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
    "p__o",
    "b__o",
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
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    "b__oControl",
    "p__oControl",
    "OnlyBrakingRear",
    "OnlyTractionRear",
    "LongSlipRear_min",
    "LongSlipRear_max",
    "v_min",
    "Fx_norm",
    "kappa__w",
    "F__x",
    "p__pos",
    "p__neg",
    "b__pos",
    "b__neg",
    "TT__env",
    "BT__env",
    "TT",
    "TB",
    "Fa",
    "Ma",
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    "time",
    "x",
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "BT__max",
    "Bx0",
    "Cx0",
    "E__pow",
    "Iw",
    "TB__max",
    "TT__max",
    "b__lb",
    "b__ss",
    "b__ub",
    "eps_c0",
    "eps_c1",
    "g",
    "h__b",
    "kD",
    "kDo",
    "l__x",
    "m",
    "mu__x0",
    "p__lb",
    "p__ss",
    "p__ub",
    "rho_a",
    "rw",
    "tau__b",
    "tau__p",
    "tol_c0",
    "tol_c1",
    "v__adm",
    "v__lb",
    "v__ss",
    "v__ub",
    "w__U",
    "w__t",
    "w__t0",
    "w__t1",
    "BTv__max",
    "b__o__lb",
    "b__o__ub",
    "lambda__lb",
    "lambda__max",
    "lambda__ss",
    "lambda__ub",
    "omega__lb",
    "omega__ss",
    "omega__ub",
    "p__o__lb",
    "p__o__ub",
    nullptr
  };

  char const *namesConstraintLT[numConstraintLT+1] = {
    "OnlyBrakingRear",
    "OnlyTractionRear",
    "LongSlipRear_min",
    "LongSlipRear_max",
    "v_min",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    "b__oControl",
    "p__oControl",
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_v",
    "initial_b",
    "final_v",
    "lambda__i",
    "p__i",
    "omega__i",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  TyreDynamic::TyreDynamic(
    string const   & name,
    integer          n_threads,
    Console const  * console
  )
  : Discretized_Indirect_OCP( name, n_threads, console )
  // Controls
  , b__oControl("b__oControl")
  , p__oControl("p__oControl")
  // Constraints LT
  , OnlyBrakingRear("OnlyBrakingRear")
  , OnlyTractionRear("OnlyTractionRear")
  , LongSlipRear_min("LongSlipRear_min")
  , LongSlipRear_max("LongSlipRear_max")
  , v_min("v_min")
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = true;

    // continuation
    this->ns_continuation_begin = 0;
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

  TyreDynamic::~TyreDynamic() {
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
  TyreDynamic::update_continuation(
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
    UTILS_ASSERT(
      0 <= old_s && old_s < s && s <= 1,
      "TyreDynamic::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 0: continuation_step_0( s ); break;
      case 1: continuation_step_1( s ); break;
      default:
        UTILS_ERROR(
          "TyreDynamic::update_continuation( phase number={}, old_s={}, s={} )"
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
  TyreDynamic::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "TyreDynamic::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in TyreDynamic::setup not all parameters are set!\n"
    );
  }

  void
  TyreDynamic::setup_parameters( real_type const Pars[] ) {
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
  TyreDynamic::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "TyreDynamic::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("OnlyBrakingRear"),
      "in TyreDynamic::setup_classes(gc) missing key: ``OnlyBrakingRear''\n"
    );
    OnlyBrakingRear.setup( gc("OnlyBrakingRear") );

    UTILS_ASSERT0(
      gc.exists("OnlyTractionRear"),
      "in TyreDynamic::setup_classes(gc) missing key: ``OnlyTractionRear''\n"
    );
    OnlyTractionRear.setup( gc("OnlyTractionRear") );

    UTILS_ASSERT0(
      gc.exists("LongSlipRear_min"),
      "in TyreDynamic::setup_classes(gc) missing key: ``LongSlipRear_min''\n"
    );
    LongSlipRear_min.setup( gc("LongSlipRear_min") );

    UTILS_ASSERT0(
      gc.exists("LongSlipRear_max"),
      "in TyreDynamic::setup_classes(gc) missing key: ``LongSlipRear_max''\n"
    );
    LongSlipRear_max.setup( gc("LongSlipRear_max") );

    UTILS_ASSERT0(
      gc.exists("v_min"),
      "in TyreDynamic::setup_classes(gc) missing key: ``v_min''\n"
    );
    v_min.setup( gc("v_min") );

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
  TyreDynamic::setup_user_classes( GenericContainer const & gc ) {
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
  TyreDynamic::setup_user_mapped_functions( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("MappedObjects"),
      "TyreDynamic::setup_classes: Missing key `MappedObjects` in data\n"
    );
    GenericContainer const & gc = gc_data("MappedObjects");

    // Initialize user mapped functions

    UTILS_ASSERT0(
      gc.exists("posPart"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``posPart''\n"
    );
    posPart.setup( gc("posPart") );

    UTILS_ASSERT0(
      gc.exists("negPart"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``negPart''\n"
    );
    negPart.setup( gc("negPart") );

    UTILS_ASSERT0(
      gc.exists("clipSup"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``clipSup''\n"
    );
    clipSup.setup( gc("clipSup") );

    UTILS_ASSERT0(
      gc.exists("clipInt"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``clipInt''\n"
    );
    clipInt.setup( gc("clipInt") );

    UTILS_ASSERT0(
      gc.exists("sign_reg"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``sign_reg''\n"
    );
    sign_reg.setup( gc("sign_reg") );

    UTILS_ASSERT0(
      gc.exists("abs_reg"),
      "in TyreDynamic::setup_user_mapped_functions(gc) missing key: ``abs_reg''\n"
    );
    abs_reg.setup( gc("abs_reg") );
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
  TyreDynamic::setup_controls( GenericContainer const & gc_data ) {
    // initialize Control penalties
    UTILS_ASSERT0(
      gc_data.exists("Controls"),
      "TyreDynamic::setup_classes: Missing key `Controls` in data\n"
    );
    GenericContainer const & gc = gc_data("Controls");
    b__oControl.setup( gc("b__oControl") );
    p__oControl.setup( gc("p__oControl") );
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
  TyreDynamic::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "TyreDynamic::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pMesh"),
      "in TyreDynamic::setup_pointers(gc) cant find key `pMesh' in gc\n"
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
  TyreDynamic::info_classes() const {
    int msg_level = 3;
    ostringstream mstr;

    m_console->message("\nControls\n",msg_level);
    mstr.str("");
    b__oControl.info(mstr);
    p__oControl.info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nConstraints LT\n",msg_level);
    mstr.str("");
    OnlyBrakingRear.info(mstr);
    OnlyTractionRear.info(mstr);
    LongSlipRear_min.info(mstr);
    LongSlipRear_max.info(mstr);
    v_min.info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    mstr.str("");
    mstr << "\nUser function `pMesh`\n";
    pMesh->info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nUser mapped functions\n",msg_level);
    mstr.str("");
    mstr << "User function ``posPart'' mapped with: ";
    posPart.info(mstr);
    mstr << "User function ``negPart'' mapped with: ";
    negPart.info(mstr);
    mstr << "User function ``clipSup'' mapped with: ";
    clipSup.info(mstr);
    mstr << "User function ``clipInt'' mapped with: ";
    clipInt.info(mstr);
    mstr << "User function ``sign_reg'' mapped with: ";
    sign_reg.info(mstr);
    mstr << "User function ``abs_reg'' mapped with: ";
    abs_reg.info(mstr);
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
  TyreDynamic::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("TyreDynamic::setup, Debug");

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
  TyreDynamic::get_names( GenericContainer & out ) const {
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
  TyreDynamic::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: TyreDynamic.cc
