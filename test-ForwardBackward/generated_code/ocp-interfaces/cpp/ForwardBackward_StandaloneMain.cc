/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Main.cc                                        |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Path2D;

using namespace ForwardBackwardLoad;
using GenericContainerNamespace::GenericContainer;

static bool SET  = true;
static bool FREE = false;

int
main() {

  #ifdef MECHATRONIX_OS_WINDOWS
  __try {
  #endif

  Mechatronix::Console     console(&std::cout,4);
  Mechatronix::ThreadPool1 TP(std::thread::hardware_concurrency());

  try {

    ForwardBackward  model("ForwardBackward",&console,&TP);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    Path2D           trajectory( "trajectory" );

    // Auxiliary values
    real_type E_tol0 = 0.25;
    real_type a_tol = 0.01;
    real_type c0_0 = 0;
    real_type a_epsi = 0.01;
    real_type c1_0 = 0;
    real_type c1 = c1_0;
    real_type E_tol = E_tol0;
    real_type epsilon0 = 0.1;
    real_type epsilon = epsilon0;
    real_type v_epsi = 0.01;
    real_type E_epsi0 = 0.25;
    real_type E_epsi = E_epsi0;
    real_type c0 = c0_0;
    real_type v_tol = 0.01;
    integer InfoLevel = 4;

    GenericContainer &  data_ControlSolver = gc_data["ControlSolver"];
    // ==============================================================
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    // :factorization => 'LU',
    // ==============================================================
    data_ControlSolver["Rcond"]     = 1e-14; // reciprocal condition number threshold for QR, SVD, LSS, LSY
    data_ControlSolver["MaxIter"]   = 50;
    data_ControlSolver["Tolerance"] = 1e-9;
    data_ControlSolver["Iterative"] = true;
    data_ControlSolver["InfoLevel"] = 1;

    // Enable doctor
    gc_data["Doctor"] = false;

    // Enable check jacobian
    gc_data["JacobianCheck"]            = false;
    gc_data["JacobianCheckFull"]        = false;
    gc_data["JacobianCheck_epsilon"]    = 1e-4;
    gc_data["FiniteDifferenceJacobian"] = false;

    // Dump Function and Jacobian if uncommented
    gc_data["DumpFile"] = "ForwardBackward_dump";

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
    data_Solver["tolerance"]             = 1e-09;

    // continuation parameters
    data_Solver["ns_continuation_begin"] = 0;
    data_Solver["ns_continuation_end"]   = 3;

    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_v"] = SET;
    data_BoundaryConditions["final_v"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["E_max"] = 5;
    data_Parameters["WA"] = 0;
    data_Parameters["a_max"] = 5;
    data_Parameters["a_min"] = -5;
    data_Parameters["c0"] = c0;
    data_Parameters["c1"] = c1;
    data_Parameters["epsilon"] = epsilon;
    data_Parameters["wT"] = 1;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["v0"] = 1;
    data_Parameters["v1"] = 1;

    // Post Processing Parameters
    data_Parameters["v_max"] = 50;
    data_Parameters["v_min"] = 0.5;

    // User Function Parameters

    // Continuation Parameters
    data_Parameters["E_epsi0"] = E_epsi0;
    data_Parameters["E_epsi1"] = 0.02;
    data_Parameters["E_tol0"] = E_tol0;
    data_Parameters["E_tol1"] = 0.02;
    data_Parameters["c0_0"] = c0_0;
    data_Parameters["c0_1"] = 0;
    data_Parameters["c1_0"] = c1_0;
    data_Parameters["c1_1"] = 0.005;
    data_Parameters["epsilon0"] = epsilon0;
    data_Parameters["epsilon1"] = 1e-05;

    // Constraints Parameters

    // functions mapped on objects

    // Controls: No penalties or barriers constraint defined

    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitV_min = data_Constraints["LimitV_min"];
    data_LimitV_min["subType"]   = "BARRIER_LOG0";
    data_LimitV_min["epsilon"]   = v_epsi;
    data_LimitV_min["tolerance"] = v_tol;
    data_LimitV_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitV_max = data_Constraints["LimitV_max"];
    data_LimitV_max["subType"]   = "BARRIER_LOG0";
    data_LimitV_max["epsilon"]   = v_epsi;
    data_LimitV_max["tolerance"] = v_tol;
    data_LimitV_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitA_min = data_Constraints["LimitA_min"];
    data_LimitA_min["subType"]   = "BARRIER_LOG0";
    data_LimitA_min["epsilon"]   = a_epsi;
    data_LimitA_min["tolerance"] = a_tol;
    data_LimitA_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitA_max = data_Constraints["LimitA_max"];
    data_LimitA_max["subType"]   = "BARRIER_LOG0";
    data_LimitA_max["epsilon"]   = a_epsi;
    data_LimitA_max["tolerance"] = a_tol;
    data_LimitA_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitE = data_Constraints["LimitE"];
    data_LimitE["subType"]   = "BARRIER_LOG0";
    data_LimitE["epsilon"]   = E_epsi;
    data_LimitE["tolerance"] = E_tol;
    data_LimitE["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: T R A J E C T O R Y


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
      gc_data.exists("Trajectory"),
      "missing key: ``Trajectory'' in gc_data\n"
    );
    trajectory.setup(gc_data("Trajectory"));
    ptrs[ "pTrajectory" ] = &trajectory;

    // setup model
    model.setup( gc_data );

    // initialize nonlinear system initial point
    model.guess( gc_data("Guess","main") );

    // print info about the solver setup
    model.info();

    // solve nonlinear system
    // model->set_timeout_ms( 100 );
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data, gc_solution );

    std::ofstream file;
    if ( ok ) {
      file.open( "data/ForwardBackward_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/ForwardBackward_OCP_result_NOT_CONVERGED.txt" );
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
