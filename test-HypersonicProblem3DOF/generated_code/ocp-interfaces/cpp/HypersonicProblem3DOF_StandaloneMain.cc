/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Main.cc                                  |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace HypersonicProblem3DOFLoad;
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

    HypersonicProblem3DOF model("HypersonicProblem3DOF",&console,&TP);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type u_tolerance = 0.1;
    real_type WTF0 = 1;
    real_type to_rad = 0.01745329252;
    real_type phi_f = 0.5*to_rad;
    real_type theta_f = 2*to_rad;
    real_type ODE0 = 0;
    real_type ODE = ODE0;
    real_type u_epsilon = 0.1;
    real_type G_i = -15*to_rad;
    real_type one_km = 1000;
    real_type S = 7500*one_km;
    real_type re = 6378*one_km;
    real_type h_i = 40*one_km;
    real_type WTF = WTF0;
    real_type CTRL0 = 1;
    real_type CTRL = CTRL0;
    real_type V_i = 2*one_km;
    real_type V_f = 2*one_km;
    real_type G_f = -15*to_rad;
    real_type sigma_dot_max = 10*to_rad;
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
    gc_data["DumpFile"] = "HypersonicProblem3DOF_dump";

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
    data_Solver["ns_continuation_end"]   = 3;

    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_h"] = SET;
    data_BoundaryConditions["initial_theta"] = SET;
    data_BoundaryConditions["initial_phi"] = SET;
    data_BoundaryConditions["initial_V"] = SET;
    data_BoundaryConditions["initial_G"] = SET;
    data_BoundaryConditions["initial_psi"] = SET;
    data_BoundaryConditions["initial_sigma"] = SET;
    data_BoundaryConditions["final_h"] = SET;
    data_BoundaryConditions["final_theta"] = SET;
    data_BoundaryConditions["final_phi"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["Aref"] = 0.29186;
    data_Parameters["CD0"] = 0.1971;
    data_Parameters["CD1"] = -0.1427;
    data_Parameters["CD2"] = 3.7677;
    data_Parameters["CL0"] = -0.0448;
    data_Parameters["CL1"] = 2.5457;
    data_Parameters["CTRL"] = CTRL;
    data_Parameters["ODE"] = ODE;
    data_Parameters["S"] = S;
    data_Parameters["WTF"] = WTF;
    data_Parameters["m"] = 340.19;
    data_Parameters["mu"] = 398600000000000;
    data_Parameters["re"] = re;
    data_Parameters["rho0"] = 1.2;
    data_Parameters["Tf_guess"] = 100;
    data_Parameters["sigma_dot_max"] = sigma_dot_max;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["G_i"] = G_i;
    data_Parameters["V_i"] = V_i;
    data_Parameters["h_f"] = 0;
    data_Parameters["h_i"] = h_i;
    data_Parameters["phi_f"] = phi_f;
    data_Parameters["phi_i"] = 0;
    data_Parameters["psi_i"] = 0;
    data_Parameters["sigma_i"] = 0;
    data_Parameters["theta_f"] = theta_f;
    data_Parameters["theta_i"] = 0;

    // Post Processing Parameters
    data_Parameters["to_deg"] = 57.29577951;

    // User Function Parameters
    data_Parameters["G_f"] = G_f;
    data_Parameters["V_f"] = V_f;
    data_Parameters["psi_f"] = 0;

    // Continuation Parameters
    data_Parameters["CTRL0"] = CTRL0;
    data_Parameters["CTRL1"] = 0;
    data_Parameters["ODE0"] = ODE0;
    data_Parameters["ODE1"] = 1;
    data_Parameters["WTF0"] = WTF0;
    data_Parameters["WTF1"] = 0;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, PARABOLA, CUBIC, QUARTIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_u2Control = data_Controls["u2Control"];
    data_u2Control["type"]      = "COS_LOGARITHMIC";
    data_u2Control["epsilon"]   = u_epsilon;
    data_u2Control["tolerance"] = u_tolerance;



    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_G_bound_min = data_Constraints["G_bound_min"];
    data_G_bound_min["subType"]   = "BARRIER_LOG";
    data_G_bound_min["epsilon"]   = 0.1;
    data_G_bound_min["tolerance"] = 0.1;
    data_G_bound_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_G_bound_max = data_Constraints["G_bound_max"];
    data_G_bound_max["subType"]   = "BARRIER_LOG";
    data_G_bound_max["epsilon"]   = 0.1;
    data_G_bound_max["tolerance"] = 0.1;
    data_G_bound_max["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
HypersonicProblem3DOF_data.Mesh["s0"] = 0;
HypersonicProblem3DOF_data.Mesh["segments"][0]["length"] = 1;
HypersonicProblem3DOF_data.Mesh["segments"][0]["n"] = 400;


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
    integer level = 2;
    model.info_model( level );

    // solve nonlinear system
    // model->set_timeout_ms( 100 );
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data, gc_solution );

    std::ofstream file;
    if ( ok ) {
      file.open( "data/HypersonicProblem3DOF_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/HypersonicProblem3DOF_OCP_result_NOT_CONVERGED.txt" );
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
