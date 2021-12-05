/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Main.cc                                 |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace ICLOCS2_BatchFermentorLoad;
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

    ICLOCS2_BatchFermentor model("ICLOCS2_BatchFermentor",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type state_tol0 = 0.1;
    real_type W0 = 100;
    real_type W = W0;
    real_type WX0 = 1;
    real_type WX = WX0;
    real_type state_tol = state_tol0;
    real_type Tf = 126;
    real_type u_epsilon0 = 0.1;
    real_type u_epsilon = u_epsilon0;
    real_type u_tolerance0 = 0.1;
    real_type state_epsi0 = 0.1;
    real_type state_epsi = state_epsi0;
    real_type u_tolerance = u_tolerance0;
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
    gc_data["DumpFile"] = "ICLOCS2_BatchFermentor_dump";

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
    data_BoundaryConditions["initial_x"] = SET;
    data_BoundaryConditions["initial_p"] = SET;
    data_BoundaryConditions["initial_s"] = SET;
    data_BoundaryConditions["initial_v"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["K_degr"] = 0.01;
    data_Parameters["S_f"] = 500;
    data_Parameters["Tf"] = Tf;
    data_Parameters["W"] = W;
    data_Parameters["WX"] = WX;
    data_Parameters["Yes"] = 1.2;
    data_Parameters["Yxs"] = 0.47;
    data_Parameters["kappa_m"] = 0.1;
    data_Parameters["mu_s"] = 0.029;
    data_Parameters["p_f"] = 8.5;
    data_Parameters["p_i"] = 0;
    data_Parameters["s_f"] = 0;
    data_Parameters["s_i"] = 0;
    data_Parameters["v_f"] = 10;
    data_Parameters["v_i"] = 7;
    data_Parameters["x_f"] = 30;
    data_Parameters["x_i"] = 1.5;
    data_Parameters["state_tol"] = state_tol;

    // Guess Parameters

    // Boundary Conditions

    // Post Processing Parameters

    // User Function Parameters
    data_Parameters["kappa_p"] = 0.0001;
    data_Parameters["kappa_x"] = 0.006;
    data_Parameters["mu_max"] = 0.11;
    data_Parameters["rho_max"] = 0.0055;
    data_Parameters["kappa_in"] = 0.1;

    // Continuation Parameters
    data_Parameters["W0"] = W0;
    data_Parameters["W1"] = 0.0001;
    data_Parameters["WX0"] = WX0;
    data_Parameters["WX1"] = 0.01;
    data_Parameters["state_epsi0"] = state_epsi0;
    data_Parameters["state_epsi1"] = 0.001;
    data_Parameters["state_tol0"] = state_tol0;
    data_Parameters["state_tol1"] = 0.001;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_uControl = data_Controls["uControl"];
    data_uControl["type"]      = ;
    data_uControl["epsilon"]   = u_epsilon;
    data_uControl["tolerance"] = u_tolerance;



    // Constraint1D
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_x_Limit = data_Constraints["x_Limit"];
    data_x_Limit["subType"]   = "PENALTY_REGULAR";
    data_x_Limit["epsilon"]   = state_epsi;
    data_x_Limit["tolerance"] = state_tol;
    data_x_Limit["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_p_Limit = data_Constraints["p_Limit"];
    data_p_Limit["subType"]   = "PENALTY_REGULAR";
    data_p_Limit["epsilon"]   = state_epsi;
    data_p_Limit["tolerance"] = state_tol;
    data_p_Limit["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_s_Limit = data_Constraints["s_Limit"];
    data_s_Limit["subType"]   = "PENALTY_REGULAR";
    data_s_Limit["epsilon"]   = state_epsi;
    data_s_Limit["tolerance"] = state_tol;
    data_s_Limit["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_v_Limit = data_Constraints["v_Limit"];
    data_v_Limit["subType"]   = "PENALTY_REGULAR";
    data_v_Limit["epsilon"]   = state_epsi;
    data_v_Limit["tolerance"] = state_tol;
    data_v_Limit["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
ICLOCS2_BatchFermentor_data.Mesh["s0"] = 0;
ICLOCS2_BatchFermentor_data.Mesh["segments"][0]["length"] = Tf;
ICLOCS2_BatchFermentor_data.Mesh["segments"][0]["n"] = 800;


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
      file.open( "data/ICLOCS2_BatchFermentor_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/ICLOCS2_BatchFermentor_OCP_result_NOT_CONVERGED.txt" );
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
