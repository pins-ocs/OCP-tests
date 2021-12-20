/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP.cc                                         |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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

#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace ICLOCS_ContinuousMPDefine {

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
    "x5",
    "x6",
    "x7",
    "x8",
    "x9",
    "x10",
    "x11",
    "x12",
    "x13",
    "x14",
    "x15",
    "x16",
    "x17",
    "x18",
    "x19",
    "x20",
    "y1",
    "y2",
    "y3",
    "y4",
    "y5",
    "y6",
    "y7",
    "y8",
    "y9",
    "y10",
    "y11",
    "y12",
    "y13",
    "y14",
    "y15",
    "y16",
    "y17",
    "y18",
    "y19",
    "y20",
    "xx1",
    "xx2",
    "xx3",
    "xx4",
    "xx5",
    "xx6",
    "xx7",
    "xx8",
    "xx9",
    "xx10",
    "xx11",
    "xx12",
    "xx13",
    "xx14",
    "xx15",
    "xx16",
    "xx17",
    "xx18",
    "xx19",
    "xx20",
    "yy1",
    "yy2",
    "yy3",
    "yy4",
    "yy5",
    "yy6",
    "yy7",
    "yy8",
    "yy9",
    "yy10",
    "yy11",
    "yy12",
    "yy13",
    "yy14",
    "yy15",
    "yy16",
    "yy17",
    "yy18",
    "yy19",
    "yy20",
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
    "lambda8__xo",
    "lambda9__xo",
    "lambda10__xo",
    "lambda11__xo",
    "lambda12__xo",
    "lambda13__xo",
    "lambda14__xo",
    "lambda15__xo",
    "lambda16__xo",
    "lambda17__xo",
    "lambda18__xo",
    "lambda19__xo",
    "lambda20__xo",
    "lambda21__xo",
    "lambda22__xo",
    "lambda23__xo",
    "lambda24__xo",
    "lambda25__xo",
    "lambda26__xo",
    "lambda27__xo",
    "lambda28__xo",
    "lambda29__xo",
    "lambda30__xo",
    "lambda31__xo",
    "lambda32__xo",
    "lambda33__xo",
    "lambda34__xo",
    "lambda35__xo",
    "lambda36__xo",
    "lambda37__xo",
    "lambda38__xo",
    "lambda39__xo",
    "lambda40__xo",
    "lambda41__xo",
    "lambda42__xo",
    "lambda43__xo",
    "lambda44__xo",
    "lambda45__xo",
    "lambda46__xo",
    "lambda47__xo",
    "lambda48__xo",
    "lambda49__xo",
    "lambda50__xo",
    "lambda51__xo",
    "lambda52__xo",
    "lambda53__xo",
    "lambda54__xo",
    "lambda55__xo",
    "lambda56__xo",
    "lambda57__xo",
    "lambda58__xo",
    "lambda59__xo",
    "lambda60__xo",
    "lambda61__xo",
    "lambda62__xo",
    "lambda63__xo",
    "lambda64__xo",
    "lambda65__xo",
    "lambda66__xo",
    "lambda67__xo",
    "lambda68__xo",
    "lambda69__xo",
    "lambda70__xo",
    "lambda71__xo",
    "lambda72__xo",
    "lambda73__xo",
    "lambda74__xo",
    "lambda75__xo",
    "lambda76__xo",
    "lambda77__xo",
    "lambda78__xo",
    "lambda79__xo",
    "lambda80__xo",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    nullptr
  };

  char const *namesQvars[numQvars+1] = {
    "zeta",
    nullptr
  };

  char const *namesPvars[numPvars+1] = {
    "u1",
    "u2",
    "u3",
    "u4",
    "u5",
    "u6",
    "u7",
    "u8",
    "u9",
    "u10",
    "u11",
    "u12",
    "u13",
    "u14",
    "u15",
    "u16",
    "u17",
    "u18",
    "u19",
    "u20",
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
    "omega13__xo",
    "omega14__xo",
    "omega15__xo",
    "omega16__xo",
    "omega17__xo",
    "omega18__xo",
    "omega19__xo",
    "omega20__xo",
    "omega21__xo",
    "omega22__xo",
    "omega23__xo",
    "omega24__xo",
    "omega25__xo",
    "omega26__xo",
    "omega27__xo",
    "omega28__xo",
    "omega29__xo",
    "omega30__xo",
    "omega31__xo",
    "omega32__xo",
    "omega33__xo",
    "omega34__xo",
    "omega35__xo",
    "omega36__xo",
    "omega37__xo",
    "omega38__xo",
    "omega39__xo",
    "omega40__xo",
    "omega41__xo",
    "omega42__xo",
    "omega43__xo",
    "omega44__xo",
    "omega45__xo",
    "omega46__xo",
    "omega47__xo",
    "omega48__xo",
    "omega49__xo",
    "omega50__xo",
    "omega51__xo",
    "omega52__xo",
    "omega53__xo",
    "omega54__xo",
    "omega55__xo",
    "omega56__xo",
    "omega57__xo",
    "omega58__xo",
    "omega59__xo",
    "omega60__xo",
    "omega61__xo",
    "omega62__xo",
    "omega63__xo",
    "omega64__xo",
    "omega65__xo",
    "omega66__xo",
    "omega67__xo",
    "omega68__xo",
    "omega69__xo",
    "omega70__xo",
    "omega71__xo",
    "omega72__xo",
    "omega73__xo",
    "omega74__xo",
    "omega75__xo",
    "omega76__xo",
    "omega77__xo",
    "omega78__xo",
    "omega79__xo",
    "omega80__xo",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    nullptr
  };

  char const *namesIntegratedPostProcess[numIntegratedPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "xy_eps0",
    "xy_eps1",
    "xy_tol0",
    "xy_tol1",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    "u1Limitation",
    "u2Limitation",
    "u3Limitation",
    "u4Limitation",
    "u5Limitation",
    "u6Limitation",
    "u7Limitation",
    "u8Limitation",
    "u9Limitation",
    "u10Limitation",
    "u11Limitation",
    "u12Limitation",
    "u13Limitation",
    "u14Limitation",
    "u15Limitation",
    "u16Limitation",
    "u17Limitation",
    "u18Limitation",
    "u19Limitation",
    "u20Limitation",
    "xx1Limitation",
    "yy1Limitation",
    "xx2Limitation",
    "yy2Limitation",
    "xx3Limitation",
    "yy3Limitation",
    "xx4Limitation",
    "yy4Limitation",
    "xx5Limitation",
    "yy5Limitation",
    "xx6Limitation",
    "yy6Limitation",
    "xx7Limitation",
    "yy7Limitation",
    "xx8Limitation",
    "yy8Limitation",
    "xx9Limitation",
    "yy9Limitation",
    "xx10Limitation",
    "yy10Limitation",
    "xx11Limitation",
    "yy11Limitation",
    "xx12Limitation",
    "yy12Limitation",
    "xx13Limitation",
    "yy13Limitation",
    "xx14Limitation",
    "yy14Limitation",
    "xx15Limitation",
    "yy15Limitation",
    "xx16Limitation",
    "yy16Limitation",
    "xx17Limitation",
    "yy17Limitation",
    "xx18Limitation",
    "yy18Limitation",
    "xx19Limitation",
    "yy19Limitation",
    "xx20Limitation",
    "yy20Limitation",
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  char const *namesConstraintU[numConstraintU+1] = {
    nullptr
  };

  char const *namesBc[numBc+1] = {
    "initial_xx1",
    "initial_yy1",
    "X1_continuity",
    "X2_continuity",
    "X3_continuity",
    "X4_continuity",
    "X5_continuity",
    "X6_continuity",
    "X7_continuity",
    "X8_continuity",
    "X9_continuity",
    "X10_continuity",
    "X11_continuity",
    "X12_continuity",
    "X13_continuity",
    "X14_continuity",
    "X15_continuity",
    "X16_continuity",
    "X17_continuity",
    "X18_continuity",
    "X19_continuity",
    "Y1_continuity",
    "Y2_continuity",
    "Y3_continuity",
    "Y4_continuity",
    "Y5_continuity",
    "Y6_continuity",
    "Y7_continuity",
    "Y8_continuity",
    "Y9_continuity",
    "Y10_continuity",
    "Y11_continuity",
    "Y12_continuity",
    "Y13_continuity",
    "Y14_continuity",
    "Y15_continuity",
    "Y16_continuity",
    "Y17_continuity",
    "Y18_continuity",
    "Y19_continuity",
    "X1_initial",
    "X2_initial",
    "X3_initial",
    "X4_initial",
    "X5_initial",
    "X6_initial",
    "X7_initial",
    "X8_initial",
    "X9_initial",
    "X10_initial",
    "X11_initial",
    "X12_initial",
    "X13_initial",
    "X14_initial",
    "X15_initial",
    "X16_initial",
    "X17_initial",
    "X18_initial",
    "X19_initial",
    "X20_initial",
    "Y1_initial",
    "Y2_initial",
    "Y3_initial",
    "Y4_initial",
    "Y5_initial",
    "Y6_initial",
    "Y7_initial",
    "Y8_initial",
    "Y9_initial",
    "Y10_initial",
    "Y11_initial",
    "Y12_initial",
    "Y13_initial",
    "Y14_initial",
    "Y15_initial",
    "Y16_initial",
    "Y17_initial",
    "Y18_initial",
    "Y19_initial",
    "Y20_initial",
    nullptr
  };

  /* --------------------------------------------------------------------------
  //    ___             _               _
  //   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _
  //  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_|
  //   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_|
  */
  ICLOCS_ContinuousMP::ICLOCS_ContinuousMP(
    string const &  name,
    ThreadPool *    TP,
    Console const * console
  )
  : Discretized_Indirect_OCP( name, TP, console )
  // Controls
  // Constraints 1D
  , u1Limitation("u1Limitation")
  , u2Limitation("u2Limitation")
  , u3Limitation("u3Limitation")
  , u4Limitation("u4Limitation")
  , u5Limitation("u5Limitation")
  , u6Limitation("u6Limitation")
  , u7Limitation("u7Limitation")
  , u8Limitation("u8Limitation")
  , u9Limitation("u9Limitation")
  , u10Limitation("u10Limitation")
  , u11Limitation("u11Limitation")
  , u12Limitation("u12Limitation")
  , u13Limitation("u13Limitation")
  , u14Limitation("u14Limitation")
  , u15Limitation("u15Limitation")
  , u16Limitation("u16Limitation")
  , u17Limitation("u17Limitation")
  , u18Limitation("u18Limitation")
  , u19Limitation("u19Limitation")
  , u20Limitation("u20Limitation")
  , xx1Limitation("xx1Limitation")
  , yy1Limitation("yy1Limitation")
  , xx2Limitation("xx2Limitation")
  , yy2Limitation("yy2Limitation")
  , xx3Limitation("xx3Limitation")
  , yy3Limitation("yy3Limitation")
  , xx4Limitation("xx4Limitation")
  , yy4Limitation("yy4Limitation")
  , xx5Limitation("xx5Limitation")
  , yy5Limitation("yy5Limitation")
  , xx6Limitation("xx6Limitation")
  , yy6Limitation("yy6Limitation")
  , xx7Limitation("xx7Limitation")
  , yy7Limitation("yy7Limitation")
  , xx8Limitation("xx8Limitation")
  , yy8Limitation("yy8Limitation")
  , xx9Limitation("xx9Limitation")
  , yy9Limitation("yy9Limitation")
  , xx10Limitation("xx10Limitation")
  , yy10Limitation("yy10Limitation")
  , xx11Limitation("xx11Limitation")
  , yy11Limitation("yy11Limitation")
  , xx12Limitation("xx12Limitation")
  , yy12Limitation("yy12Limitation")
  , xx13Limitation("xx13Limitation")
  , yy13Limitation("yy13Limitation")
  , xx14Limitation("xx14Limitation")
  , yy14Limitation("yy14Limitation")
  , xx15Limitation("xx15Limitation")
  , yy15Limitation("yy15Limitation")
  , xx16Limitation("xx16Limitation")
  , yy16Limitation("yy16Limitation")
  , xx17Limitation("xx17Limitation")
  , yy17Limitation("yy17Limitation")
  , xx18Limitation("xx18Limitation")
  , yy18Limitation("yy18Limitation")
  , xx19Limitation("xx19Limitation")
  , yy19Limitation("yy19Limitation")
  , xx20Limitation("xx20Limitation")
  , yy20Limitation("yy20Limitation")
  // Constraints 2D
  // User classes
  {
    m_U_solve_iterative = false;

    // continuation
    this->ns_continuation_begin = 0;
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

    #ifdef LAPACK_WRAPPER_USE_OPENBLAS
    openblas_set_num_threads(1);
    goto_set_num_threads(1);
    m_console->message( lapack_wrapper::openblas_info(), 1 );
    #endif
  }

  ICLOCS_ContinuousMP::~ICLOCS_ContinuousMP() {
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
  ICLOCS_ContinuousMP::update_continuation(
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
      "ICLOCS_ContinuousMP::update_continuation( phase number={}, old_s={}, s={} ) "
      "must be 0 <= old_s < s <= 1\n",
      phase, old_s, s
    );
    switch ( phase ) {
      case 0: continuation_step_0( s ); break;
      default:
        UTILS_ERROR(
          "ICLOCS_ContinuousMP::update_continuation( phase number={}, old_s={}, s={} )"
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
  ICLOCS_ContinuousMP::setup_parameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "ICLOCS_ContinuousMP::setup_parameters: Missing key `Parameters` in data\n"
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
      allfound, "in ICLOCS_ContinuousMP::setup not all parameters are set!\n"
    );
  }

  void
  ICLOCS_ContinuousMP::setup_parameters( real_type const Pars[] ) {
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
  ICLOCS_ContinuousMP::setup_classes( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "ICLOCS_ContinuousMP::setup_classes: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
    // Initialize Constraints 1D
    UTILS_ASSERT0(
      gc.exists("u1Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u1Limitation''\n"
    );
    u1Limitation.setup( gc("u1Limitation") );

    UTILS_ASSERT0(
      gc.exists("u2Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u2Limitation''\n"
    );
    u2Limitation.setup( gc("u2Limitation") );

    UTILS_ASSERT0(
      gc.exists("u3Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u3Limitation''\n"
    );
    u3Limitation.setup( gc("u3Limitation") );

    UTILS_ASSERT0(
      gc.exists("u4Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u4Limitation''\n"
    );
    u4Limitation.setup( gc("u4Limitation") );

    UTILS_ASSERT0(
      gc.exists("u5Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u5Limitation''\n"
    );
    u5Limitation.setup( gc("u5Limitation") );

    UTILS_ASSERT0(
      gc.exists("u6Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u6Limitation''\n"
    );
    u6Limitation.setup( gc("u6Limitation") );

    UTILS_ASSERT0(
      gc.exists("u7Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u7Limitation''\n"
    );
    u7Limitation.setup( gc("u7Limitation") );

    UTILS_ASSERT0(
      gc.exists("u8Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u8Limitation''\n"
    );
    u8Limitation.setup( gc("u8Limitation") );

    UTILS_ASSERT0(
      gc.exists("u9Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u9Limitation''\n"
    );
    u9Limitation.setup( gc("u9Limitation") );

    UTILS_ASSERT0(
      gc.exists("u10Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u10Limitation''\n"
    );
    u10Limitation.setup( gc("u10Limitation") );

    UTILS_ASSERT0(
      gc.exists("u11Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u11Limitation''\n"
    );
    u11Limitation.setup( gc("u11Limitation") );

    UTILS_ASSERT0(
      gc.exists("u12Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u12Limitation''\n"
    );
    u12Limitation.setup( gc("u12Limitation") );

    UTILS_ASSERT0(
      gc.exists("u13Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u13Limitation''\n"
    );
    u13Limitation.setup( gc("u13Limitation") );

    UTILS_ASSERT0(
      gc.exists("u14Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u14Limitation''\n"
    );
    u14Limitation.setup( gc("u14Limitation") );

    UTILS_ASSERT0(
      gc.exists("u15Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u15Limitation''\n"
    );
    u15Limitation.setup( gc("u15Limitation") );

    UTILS_ASSERT0(
      gc.exists("u16Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u16Limitation''\n"
    );
    u16Limitation.setup( gc("u16Limitation") );

    UTILS_ASSERT0(
      gc.exists("u17Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u17Limitation''\n"
    );
    u17Limitation.setup( gc("u17Limitation") );

    UTILS_ASSERT0(
      gc.exists("u18Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u18Limitation''\n"
    );
    u18Limitation.setup( gc("u18Limitation") );

    UTILS_ASSERT0(
      gc.exists("u19Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u19Limitation''\n"
    );
    u19Limitation.setup( gc("u19Limitation") );

    UTILS_ASSERT0(
      gc.exists("u20Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``u20Limitation''\n"
    );
    u20Limitation.setup( gc("u20Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx1Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx1Limitation''\n"
    );
    xx1Limitation.setup( gc("xx1Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy1Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy1Limitation''\n"
    );
    yy1Limitation.setup( gc("yy1Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx2Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx2Limitation''\n"
    );
    xx2Limitation.setup( gc("xx2Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy2Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy2Limitation''\n"
    );
    yy2Limitation.setup( gc("yy2Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx3Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx3Limitation''\n"
    );
    xx3Limitation.setup( gc("xx3Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy3Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy3Limitation''\n"
    );
    yy3Limitation.setup( gc("yy3Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx4Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx4Limitation''\n"
    );
    xx4Limitation.setup( gc("xx4Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy4Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy4Limitation''\n"
    );
    yy4Limitation.setup( gc("yy4Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx5Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx5Limitation''\n"
    );
    xx5Limitation.setup( gc("xx5Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy5Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy5Limitation''\n"
    );
    yy5Limitation.setup( gc("yy5Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx6Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx6Limitation''\n"
    );
    xx6Limitation.setup( gc("xx6Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy6Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy6Limitation''\n"
    );
    yy6Limitation.setup( gc("yy6Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx7Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx7Limitation''\n"
    );
    xx7Limitation.setup( gc("xx7Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy7Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy7Limitation''\n"
    );
    yy7Limitation.setup( gc("yy7Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx8Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx8Limitation''\n"
    );
    xx8Limitation.setup( gc("xx8Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy8Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy8Limitation''\n"
    );
    yy8Limitation.setup( gc("yy8Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx9Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx9Limitation''\n"
    );
    xx9Limitation.setup( gc("xx9Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy9Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy9Limitation''\n"
    );
    yy9Limitation.setup( gc("yy9Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx10Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx10Limitation''\n"
    );
    xx10Limitation.setup( gc("xx10Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy10Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy10Limitation''\n"
    );
    yy10Limitation.setup( gc("yy10Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx11Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx11Limitation''\n"
    );
    xx11Limitation.setup( gc("xx11Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy11Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy11Limitation''\n"
    );
    yy11Limitation.setup( gc("yy11Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx12Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx12Limitation''\n"
    );
    xx12Limitation.setup( gc("xx12Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy12Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy12Limitation''\n"
    );
    yy12Limitation.setup( gc("yy12Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx13Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx13Limitation''\n"
    );
    xx13Limitation.setup( gc("xx13Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy13Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy13Limitation''\n"
    );
    yy13Limitation.setup( gc("yy13Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx14Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx14Limitation''\n"
    );
    xx14Limitation.setup( gc("xx14Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy14Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy14Limitation''\n"
    );
    yy14Limitation.setup( gc("yy14Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx15Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx15Limitation''\n"
    );
    xx15Limitation.setup( gc("xx15Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy15Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy15Limitation''\n"
    );
    yy15Limitation.setup( gc("yy15Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx16Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx16Limitation''\n"
    );
    xx16Limitation.setup( gc("xx16Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy16Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy16Limitation''\n"
    );
    yy16Limitation.setup( gc("yy16Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx17Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx17Limitation''\n"
    );
    xx17Limitation.setup( gc("xx17Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy17Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy17Limitation''\n"
    );
    yy17Limitation.setup( gc("yy17Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx18Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx18Limitation''\n"
    );
    xx18Limitation.setup( gc("xx18Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy18Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy18Limitation''\n"
    );
    yy18Limitation.setup( gc("yy18Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx19Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx19Limitation''\n"
    );
    xx19Limitation.setup( gc("xx19Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy19Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy19Limitation''\n"
    );
    yy19Limitation.setup( gc("yy19Limitation") );

    UTILS_ASSERT0(
      gc.exists("xx20Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``xx20Limitation''\n"
    );
    xx20Limitation.setup( gc("xx20Limitation") );

    UTILS_ASSERT0(
      gc.exists("yy20Limitation"),
      "in ICLOCS_ContinuousMP::setup_classes(gc) missing key: ``yy20Limitation''\n"
    );
    yy20Limitation.setup( gc("yy20Limitation") );

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
  ICLOCS_ContinuousMP::setup_user_classes( GenericContainer const & gc ) {
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
  ICLOCS_ContinuousMP::setup_user_mapped_functions( GenericContainer const & gc_data ) {
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
  ICLOCS_ContinuousMP::setup_controls( GenericContainer const & gc_data ) {
    // no Control penalties, setup only iterative solver
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
  ICLOCS_ContinuousMP::setup_pointers( GenericContainer const & gc_data ) {

    UTILS_ASSERT0(
      gc_data.exists("Pointers"),
      "ICLOCS_ContinuousMP::setup_pointers: Missing key `Pointers` in data\n"
    );
    GenericContainer const & gc = gc_data("Pointers");

    // Initialize user classes

    UTILS_ASSERT0(
      gc.exists("pMesh"),
      "in ICLOCS_ContinuousMP::setup_pointers(gc) cant find key `pMesh' in gc\n"
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
  ICLOCS_ContinuousMP::info_classes() const {
    int msg_level = 3;
    ostringstream mstr;

    m_console->message("\nConstraints 1D\n",msg_level);
    mstr.str("");
    u1Limitation  .info(mstr);
    u2Limitation  .info(mstr);
    u3Limitation  .info(mstr);
    u4Limitation  .info(mstr);
    u5Limitation  .info(mstr);
    u6Limitation  .info(mstr);
    u7Limitation  .info(mstr);
    u8Limitation  .info(mstr);
    u9Limitation  .info(mstr);
    u10Limitation .info(mstr);
    u11Limitation .info(mstr);
    u12Limitation .info(mstr);
    u13Limitation .info(mstr);
    u14Limitation .info(mstr);
    u15Limitation .info(mstr);
    u16Limitation .info(mstr);
    u17Limitation .info(mstr);
    u18Limitation .info(mstr);
    u19Limitation .info(mstr);
    u20Limitation .info(mstr);
    xx1Limitation .info(mstr);
    yy1Limitation .info(mstr);
    xx2Limitation .info(mstr);
    yy2Limitation .info(mstr);
    xx3Limitation .info(mstr);
    yy3Limitation .info(mstr);
    xx4Limitation .info(mstr);
    yy4Limitation .info(mstr);
    xx5Limitation .info(mstr);
    yy5Limitation .info(mstr);
    xx6Limitation .info(mstr);
    yy6Limitation .info(mstr);
    xx7Limitation .info(mstr);
    yy7Limitation .info(mstr);
    xx8Limitation .info(mstr);
    yy8Limitation .info(mstr);
    xx9Limitation .info(mstr);
    yy9Limitation .info(mstr);
    xx10Limitation.info(mstr);
    yy10Limitation.info(mstr);
    xx11Limitation.info(mstr);
    yy11Limitation.info(mstr);
    xx12Limitation.info(mstr);
    yy12Limitation.info(mstr);
    xx13Limitation.info(mstr);
    yy13Limitation.info(mstr);
    xx14Limitation.info(mstr);
    yy14Limitation.info(mstr);
    xx15Limitation.info(mstr);
    yy15Limitation.info(mstr);
    xx16Limitation.info(mstr);
    yy16Limitation.info(mstr);
    xx17Limitation.info(mstr);
    yy17Limitation.info(mstr);
    xx18Limitation.info(mstr);
    yy18Limitation.info(mstr);
    xx19Limitation.info(mstr);
    yy19Limitation.info(mstr);
    xx20Limitation.info(mstr);
    yy20Limitation.info(mstr);
    m_console->message(mstr.str(),msg_level);

    m_console->message("\nUser class (pointer)\n",msg_level);
    mstr.str("");
    mstr << "\nUser function `pMesh`\n";
    pMesh->info(mstr);
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
  ICLOCS_ContinuousMP::setup( GenericContainer const & gc ) {

    m_debug = false;
    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("ICLOCS_ContinuousMP::setup, Debug");

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
  ICLOCS_ContinuousMP::get_names( GenericContainer & out ) const {
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
  ICLOCS_ContinuousMP::save_OCP_info( GenericContainer & gc ) const {
    for ( integer i = 0; i < numModelPars; ++i )
      gc[namesModelPars[i]] = ModelPars[i];

  }

}

// EOF: ICLOCS_ContinuousMP.cc
