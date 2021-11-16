/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Main.cc                                    |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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


#include "PointMassCarModel_1.hh"
#include "PointMassCarModel_1_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Road2D;

using namespace PointMassCarModel_1Load;
using GenericContainerNamespace::GenericContainer;

static bool SET  = true;
static bool FREE = false;

int
main() {

  #ifdef MECHATRONIX_OS_WINDOWS
  __try {
  #endif

  Mechatronix::Console    console(&std::cout,4);
  Mechatronix::ThreadPool TP(std::thread::hardware_concurrency());

  try {

    PointMassCarModel_1 model("PointMassCarModel_1",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    Road2D           road( "road" );

    // Auxiliary values
    real_type m = 700;
    real_type road_tol0 = 0.01;
    real_type p_tol0 = 0.1;
    real_type up_tol0 = 0.01;
    real_type up_epsi0 = 0.1;
    real_type kD = 0.2500000000/m;
    real_type p_epsi0 = 0.1;
    real_type wT0 = 0.01;
    real_type wT = wT0;
    integer InfoLevel = 4;

    GenericContainer &  data_ControlSolver = gc_data["ControlSolver"];
    // ==============================================================
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    // :factorization => 'LU',
    // ==============================================================
    data_ControlSolver["Rcond"]     = 1e-14; // reciprocal condition number threshold for QR, SVD, LSS, LSY
    data_ControlSolver["MaxIter"]   = 50;
    data_ControlSolver["Tolerance"] = 1e-9;
    data_ControlSolver["Iterative"] = false;
    data_ControlSolver["InfoLevel"] = 1;

    // Enable doctor
    gc_data["Doctor"] = false;

    // Enable check jacobian
    gc_data["JacobianCheck"]            = false;
    gc_data["JacobianCheckFull"]        = false;
    gc_data["JacobianCheck_epsilon"]    = 1e-4;
    gc_data["FiniteDifferenceJacobian"] = false;

    // Dump Function and Jacobian if uncommented
    gc_data["DumpFile"] = "PointMassCarModel_1_dump";

    // spline output (all values as function of "s")
    gc_data["OutputSplines"] = "s";

    // setup solver
    GenericContainer & data_Solver = gc_data["Solver"];
    // Linear algebra factorization selection:
    // 'LU', 'QR', 'QRP', 'SUPERLU'
    // =================
    data_Solver["factorization"] = "LU";
    // =================

    // Last Block selection:
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    // ==============================================
    data_Solver["last_factorization"] = "PINV";
    // ==============================================

    // choose solver: Hyness, NewtonDumped
    // ===================================
    data_Solver["solver"] = "Hyness";
    // ===================================

    // solver parameters
    data_Solver["max_iter"]              = 300;
    data_Solver["max_step_iter"]         = 40;
    data_Solver["max_accumulated_iter"]  = 800;
    data_Solver["tolerance"]             = 9.999999999999999e-10;
    // continuation parameters
    data_Solver["ns_continuation_begin"] = 0;
    data_Solver["ns_continuation_end"]   = 2;
    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]   = 0.2;   // initial step for continuation
    data_Continuation["min_step"]       = 0.001; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]  = 0.5;   // p fails, reduce step by this factor
    data_Continuation["augment_factor"] = 1.5;   // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"] = 8;

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_V"] = SET;
    data_BoundaryConditions["cyclic_n"] = SET;
    data_BoundaryConditions["cyclic_alpha"] = SET;
    data_BoundaryConditions["cyclic_V"] = SET;
    data_BoundaryConditions["cyclic_fx"] = SET;
    data_BoundaryConditions["cyclic_Omega"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["Pmax"] = 200000;
    data_Parameters["g"] = 9.806;
    data_Parameters["kD"] = kD;
    data_Parameters["m"] = m;
    data_Parameters["wT"] = wT;
    data_Parameters["mu__x__max"] = 1;
    data_Parameters["mu__y__max"] = 1.5;
    data_Parameters["v__Omega__max"] = 5;
    data_Parameters["v__fx__max"] = 30;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["V0"] = 5;

    // Post Processing Parameters

    // User Function Parameters

    // Continuation Parameters
    data_Parameters["p_epsi0"] = p_epsi0;
    data_Parameters["p_epsi1"] = 0.001;
    data_Parameters["wT0"] = wT0;
    data_Parameters["wT1"] = 1;
    data_Parameters["up_epsi0"] = up_epsi0;
    data_Parameters["up_epsi1"] = 0.01;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_v__fxControl = data_Controls["v__fxControl"];
    data_v__fxControl["type"]      = ;
    data_v__fxControl["epsilon"]   = up_epsi0;
    data_v__fxControl["tolerance"] = up_tol0;


    GenericContainer & data_v__OmegaControl = data_Controls["v__OmegaControl"];
    data_v__OmegaControl["type"]      = ;
    data_v__OmegaControl["epsilon"]   = up_epsi0;
    data_v__OmegaControl["tolerance"] = up_tol0;



    // Constraint1D
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_AdherenceEllipse = data_Constraints["AdherenceEllipse"];
    data_AdherenceEllipse["subType"]   = "PENALTY_REGULAR";
    data_AdherenceEllipse["epsilon"]   = p_epsi0;
    data_AdherenceEllipse["tolerance"] = p_tol0;
    data_AdherenceEllipse["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_RoadLeftBorder = data_Constraints["RoadLeftBorder"];
    data_RoadLeftBorder["subType"]   = "PENALTY_REGULAR";
    data_RoadLeftBorder["epsilon"]   = p_epsi0;
    data_RoadLeftBorder["tolerance"] = road_tol0;
    data_RoadLeftBorder["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_RoadRightBorder = data_Constraints["RoadRightBorder"];
    data_RoadRightBorder["subType"]   = "PENALTY_REGULAR";
    data_RoadRightBorder["epsilon"]   = p_epsi0;
    data_RoadRightBorder["tolerance"] = road_tol0;
    data_RoadRightBorder["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_PowerLimit = data_Constraints["PowerLimit"];
    data_PowerLimit["subType"]   = "PENALTY_REGULAR";
    data_PowerLimit["epsilon"]   = p_epsi0;
    data_PowerLimit["tolerance"] = p_tol0;
    data_PowerLimit["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_LimitMinSpeed = data_Constraints["LimitMinSpeed"];
    data_LimitMinSpeed["subType"]   = "PENALTY_REGULAR";
    data_LimitMinSpeed["epsilon"]   = p_epsi0;
    data_LimitMinSpeed["tolerance"] = p_tol0;
    data_LimitMinSpeed["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: R O A D
PointMassCarModel_1_data.Road["theta0"] = 0;
PointMassCarModel_1_data.Road["s0"] = 0;
PointMassCarModel_1_data.Road["x0"] = 0;
PointMassCarModel_1_data.Road["y0"] = 0;
PointMassCarModel_1_data.Road["is_SAE"] = false;
PointMassCarModel_1_data.Road["segments"][0]["leftWidth"] = 15/2;
PointMassCarModel_1_data.Road["segments"][0]["rightWidth"] = 60;
PointMassCarModel_1_data.Road["segments"][0]["length"] = 190;
PointMassCarModel_1_data.Road["segments"][0]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][0]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][1]["leftWidth"] = 60;
PointMassCarModel_1_data.Road["segments"][1]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][1]["length"] = 973.8937227;
PointMassCarModel_1_data.Road["segments"][1]["curvature"] = 0.003225806452;
PointMassCarModel_1_data.Road["segments"][1]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][2]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][2]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][2]["length"] = 180;
PointMassCarModel_1_data.Road["segments"][2]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][2]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][3]["leftWidth"] = 20;
PointMassCarModel_1_data.Road["segments"][3]["rightWidth"] = 15;
PointMassCarModel_1_data.Road["segments"][3]["length"] = 235.619449;
PointMassCarModel_1_data.Road["segments"][3]["curvature"] = 0.006666666667;
PointMassCarModel_1_data.Road["segments"][3]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][4]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][4]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][4]["length"] = 240;
PointMassCarModel_1_data.Road["segments"][4]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][4]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][5]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][5]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][5]["length"] = 235.619449;
PointMassCarModel_1_data.Road["segments"][5]["curvature"] = -1/150;
PointMassCarModel_1_data.Road["segments"][5]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][6]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][6]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][6]["length"] = 200;
PointMassCarModel_1_data.Road["segments"][6]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][6]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][7]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][7]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][7]["length"] = 125.6637062;
PointMassCarModel_1_data.Road["segments"][7]["curvature"] = 0.025;
PointMassCarModel_1_data.Road["segments"][7]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][8]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][8]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][8]["length"] = 480;
PointMassCarModel_1_data.Road["segments"][8]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][8]["gridSize"] = 1;
PointMassCarModel_1_data.Road["segments"][9]["leftWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][9]["rightWidth"] = 30;
PointMassCarModel_1_data.Road["segments"][9]["length"] = 10;
PointMassCarModel_1_data.Road["segments"][9]["curvature"] = 0;
PointMassCarModel_1_data.Road["segments"][9]["gridSize"] = 0.1;


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
      gc_data.exists("Road"),
      "missing key: ``Road'' in gc_data\n"
    );
    road.setup(gc_data("Road"));
    ptrs[ "pRoad" ] = &road;

    // setup model
    model.setup( gc_data );

    // initialize nonlinear system initial point
    model.guess( gc_data("Guess","Missing `Guess` field") );

    // solve nonlinear system
    // model->set_timeout_ms( 100 );
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data, gc_solution );

    std::ofstream file;
    if ( ok ) {
      file.open( "data/PointMassCarModel_1_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/PointMassCarModel_1_OCP_result_NOT_CONVERGED.txt" );
    }
    file.precision(18);
    Mechatronix::save_OCP_solution_to_stream(gc_solution,file);
    file.close();
    cout.precision(18);
    GenericContainer const & target = gc_solution("target");
    fmt::print(
      "Lagrange target    = {}\n"
      "Mayer target       = {}\n"
      "Penalties+Barriers = {}\n"
      "Control penalties  = {}\n",
      target("lagrange").get_number(),  target("mayer").get_number(),
      target("penalties").get_number(), target("control_penalties").get_number()
    );
    if ( gc_solution.exists("parameters") ) {
      cout << "Optimization parameters:\n";
      gc_solution("parameters").print(cout);
    }
    if ( gc_solution.exists("diagnosis") ) gc_solution("diagnosis").print(cout);
  }
  catch ( std::exception const & exc ) {
    console.error(exc.what());
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch ( char const * exc ) {
    console.error(exc);
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch (...) {
    console.error("ERRORE SCONOSCIUTO\n");
    ALL_DONE_FOLKS;
    exit(0);
  }

  ALL_DONE_FOLKS;

  #ifdef MECHATRONIX_OS_WINDOWS
  } __finally {
    cerr << "Unknown windows error found, exiting\n";
  }
  #endif

  return 0;
}
