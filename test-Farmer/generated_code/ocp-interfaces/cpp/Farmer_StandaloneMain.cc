/*-----------------------------------------------------------------------*\
 |  file: Farmer_Main.cc                                                 |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "Farmer.hh"
#include "Farmer_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace FarmerLoad;
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

    Farmer           model("Farmer",&console,&TP);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
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
    gc_data["DumpFile"] = "Farmer_dump";

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
    data_Solver["ns_continuation_begin"] = 1;
    data_Solver["ns_continuation_end"]   = 0;

    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_x1"] = SET;
    data_BoundaryConditions["initial_x2"] = SET;
    data_BoundaryConditions["initial_x3"] = SET;
    data_BoundaryConditions["initial_res"] = SET;
    data_BoundaryConditions["initial_x4"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["tau__1"] = 3;
    data_Parameters["tau__2"] = 25;
    data_Parameters["tau__3"] = 10;
    data_Parameters["tau__4"] = 60;
    data_Parameters["tau__5"] = 120;
    data_Parameters["w1"] = 1.3;
    data_Parameters["w2"] = 0.1;
    data_Parameters["w3"] = 1.2;
    data_Parameters["w4"] = 0.9;
    data_Parameters["wJ1"] = 1;
    data_Parameters["wJ2"] = 1;
    data_Parameters["wJ3"] = 1;
    data_Parameters["wJ4"] = 1;
    data_Parameters["wP"] = 1;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["res0"] = 0.001;
    data_Parameters["x10"] = 0.001;
    data_Parameters["x20"] = 0.001;
    data_Parameters["x30"] = 0.001;
    data_Parameters["x40"] = 0.001;

    // Post Processing Parameters

    // User Function Parameters
    data_Parameters["P1"] = 0.1;
    data_Parameters["P2"] = 0.1;
    data_Parameters["t1"] = 0;
    data_Parameters["t2"] = 60;

    // Continuation Parameters

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, PARABOLA, CUBIC, QUARTIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_x1__oControl = data_Controls["x1__oControl"];
    data_x1__oControl["type"]      = "COS_LOGARITHMIC";
    data_x1__oControl["epsilon"]   = 0.001;
    data_x1__oControl["tolerance"] = 0.001;


    GenericContainer & data_x2__oControl = data_Controls["x2__oControl"];
    data_x2__oControl["type"]      = "COS_LOGARITHMIC";
    data_x2__oControl["epsilon"]   = 0.001;
    data_x2__oControl["tolerance"] = 0.001;


    GenericContainer & data_x3__oControl = data_Controls["x3__oControl"];
    data_x3__oControl["type"]      = "COS_LOGARITHMIC";
    data_x3__oControl["epsilon"]   = 0.001;
    data_x3__oControl["tolerance"] = 0.001;


    GenericContainer & data_x4__oControl = data_Controls["x4__oControl"];
    data_x4__oControl["type"]      = "COS_LOGARITHMIC";
    data_x4__oControl["epsilon"]   = 0.001;
    data_x4__oControl["tolerance"] = 0.001;



    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LimitX2X4 = data_Constraints["LimitX2X4"];
    data_LimitX2X4["subType"]   = "PENALTY_REGULAR";
    data_LimitX2X4["epsilon"]   = 0.001;
    data_LimitX2X4["tolerance"] = 0.001;
    data_LimitX2X4["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
Farmer_data.Mesh["s0"] = 0;
Farmer_data.Mesh["segments"][0]["n"] = 400;
Farmer_data.Mesh["segments"][0]["length"] = 2;


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
      gc_data.exists("Mesh"),
      "missing key: ``Mesh'' in gc_data\n"
    );
    mesh.setup(gc_data("Mesh"));
    ptrs[ "pMesh" ] = &mesh;

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
      file.open( "data/Farmer_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/Farmer_OCP_result_NOT_CONVERGED.txt" );
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
