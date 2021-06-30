/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Main.cc                                     |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace ICLOCS_StirredTankLoad;
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

    ICLOCS_StirredTank model("ICLOCS_StirredTank",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type w_exp_min = 0;
    real_type epsi_ctrl = 0.001;
    real_type tol_T = 1;
    real_type epsi_T = 0.001;
    real_type x_epsi = 0.1;
    real_type x_tol = 0.01;
    real_type tol_ctrl = 0.001;
    real_type w = exp(w_exp_min);
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
    gc_data["DumpFile"] = "ICLOCS_StirredTank_dump";

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
    data_Solver["ns_continuation_end"]   = 1;
    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]   = 0.2;   // initial step for continuation
    data_Continuation["min_step"]       = 0.001; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]  = 0.5;   // p fails, reduce step by this factor
    data_Continuation["augment_factor"] = 1.5;   // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"] = 8;

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["En"] = 5;
    data_Parameters["Tc"] = 0.38158;
    data_Parameters["Tf"] = 0.3947;
    data_Parameters["a"] = 0.117;
    data_Parameters["k"] = 300;
    data_Parameters["theta"] = 20;
    data_Parameters["wT"] = 0.001;

    // Guess Parameters
    data_Parameters["T_guess"] = 90;
    data_Parameters["u_f"] = 0.76;

    // Boundary Conditions
    data_Parameters["w"] = w;
    data_Parameters["x1_f"] = 0.26;
    data_Parameters["x1_i"] = 0.98;
    data_Parameters["x2_f"] = 0.65;
    data_Parameters["x2_i"] = 0.39;

    // Post Processing Parameters

    // User Function Parameters

    // Continuation Parameters
    data_Parameters["w_exp_max"] = 15;
    data_Parameters["w_exp_min"] = w_exp_min;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_uControl = data_Controls["uControl"];
    data_uControl["type"]      = ;
    data_uControl["epsilon"]   = epsi_ctrl;
    data_uControl["tolerance"] = tol_ctrl;



    // Constraint1D
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DInterval
    GenericContainer & data_tfbound = data_Constraints["tfbound"];
    data_tfbound["subType"]   = "BARRIER_LOG";
    data_tfbound["epsilon"]   = epsi_T;
    data_tfbound["tolerance"] = tol_T;
    data_tfbound["min"]       = 10;
    data_tfbound["max"]       = 200;
    data_tfbound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_x1bound = data_Constraints["x1bound"];
    data_x1bound["subType"]   = "BARRIER_LOG";
    data_x1bound["epsilon"]   = x_epsi;
    data_x1bound["tolerance"] = x_tol;
    data_x1bound["min"]       = 0;
    data_x1bound["max"]       = 1;
    data_x1bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_x2bound = data_Constraints["x2bound"];
    data_x2bound["subType"]   = "BARRIER_LOG";
    data_x2bound["epsilon"]   = x_epsi;
    data_x2bound["tolerance"] = x_tol;
    data_x2bound["min"]       = 0;
    data_x2bound["max"]       = 1;
    data_x2bound["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
ICLOCS_StirredTank_data.Mesh["s0"] = 0;
ICLOCS_StirredTank_data.Mesh["segments"][0]["n"] = 100;
ICLOCS_StirredTank_data.Mesh["segments"][0]["length"] = 1;


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
    model.guess( gc_data("Guess","Missing `Guess` field") );

    // solve nonlinear system
    // model->set_timeout_ms( 100 );
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data, gc_solution );

    std::ofstream file;
    if ( ok ) {
      file.open( "data/ICLOCS_StirredTank_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/ICLOCS_StirredTank_OCP_not_converged.txt" );
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
  catch ( char const exc[] ) {
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
