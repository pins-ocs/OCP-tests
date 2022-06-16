/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Main.cc                                          |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace GoddardRocketLoad;
using GenericContainerNamespace::GenericContainer;

static bool SET  = true;
static bool FREE = false;

int
main() {

  #ifdef MECHATRONIX_OS_WINDOWS
  __try {
  #endif

  Mechatronix::Console console(&std::cout,4);
  Mechatronix::integer n_threads = std::thread::hardware_concurrency();

  try {

    GoddardRocket    model("GoddardRocket",n_threads,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type tol_v_max = 0.01;
    real_type epsi_TS_max = 0.025;
    real_type epsi_TS = epsi_TS_max;
    real_type tol_TS_max = 0.0001;
    real_type tol_u_max = 0.01;
    real_type tol_u = tol_u_max;
    real_type epsi_u_max = 0.01;
    real_type epsi_u = epsi_u_max;
    real_type tol_v = tol_v_max;
    real_type tol_TS = tol_TS_max;
    real_type tol_mass_max = 0.01;
    real_type tol_mass = tol_mass_max;
    real_type epsi_v_max = 0.1;
    real_type epsi_v = epsi_v_max;
    real_type epsi_mass_max = 0.025;
    real_type epsi_mass = epsi_mass_max;
    real_type mu0 = 0;
    real_type mu = mu0;
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
    gc_data["DumpFile"] = "GoddardRocket_dump";

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
    data_Solver["ns_continuation_end"]   = 2;

    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_h"] = SET;
    data_BoundaryConditions["initial_v"] = SET;
    data_BoundaryConditions["initial_m"] = SET;
    data_BoundaryConditions["final_m"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["Hscale"] = 23800;
    data_Parameters["Ve"] = 1580.9425;
    data_Parameters["g"] = 32.174;
    data_Parameters["mu"] = mu;

    // Guess Parameters
    data_Parameters["TimeSize_guess"] = 40;

    // Boundary Conditions
    data_Parameters["h_i"] = 0;
    data_Parameters["m_f"] = 1;
    data_Parameters["m_i"] = 3;
    data_Parameters["v_i"] = 0;

    // Post Processing Parameters
    data_Parameters["Tmax"] = 193;

    // User Function Parameters
    data_Parameters["D0"] = 5.49153485e-05;

    // Continuation Parameters
    data_Parameters["mu0"] = mu0;
    data_Parameters["mu1"] = 0;
    data_Parameters["epsi_TS_max"] = epsi_TS_max;
    data_Parameters["epsi_TS_min"] = 1e-10;
    data_Parameters["epsi_mass_max"] = epsi_mass_max;
    data_Parameters["epsi_mass_min"] = 0.0001;
    data_Parameters["epsi_u_max"] = epsi_u_max;
    data_Parameters["epsi_u_min"] = 1e-07;
    data_Parameters["epsi_v_max"] = epsi_v_max;
    data_Parameters["epsi_v_min"] = 0.0001;
    data_Parameters["tol_TS_max"] = tol_TS_max;
    data_Parameters["tol_TS_min"] = 0.001;
    data_Parameters["tol_mass_max"] = tol_mass_max;
    data_Parameters["tol_mass_min"] = 0.0001;
    data_Parameters["tol_u_max"] = tol_u_max;
    data_Parameters["tol_u_min"] = 0.0001;
    data_Parameters["tol_v_max"] = tol_v_max;
    data_Parameters["tol_v_min"] = 0.0001;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, QUARTIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_uControl = data_Controls["uControl"];
    data_uControl["type"]      = "COS_LOGARITHMIC";
    data_uControl["epsilon"]   = epsi_u;
    data_uControl["tolerance"] = tol_u;



    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_massPositive = data_Constraints["massPositive"];
    data_massPositive["subType"]   = "BARRIER_LOG";
    data_massPositive["epsilon"]   = epsi_mass;
    data_massPositive["tolerance"] = tol_mass;
    data_massPositive["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_vPositive = data_Constraints["vPositive"];
    data_vPositive["subType"]   = "BARRIER_LOG";
    data_vPositive["epsilon"]   = epsi_v;
    data_vPositive["tolerance"] = tol_v;
    data_vPositive["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_TSPositive = data_Constraints["TSPositive"];
    data_TSPositive["subType"]   = "BARRIER_LOG";
    data_TSPositive["epsilon"]   = epsi_TS;
    data_TSPositive["tolerance"] = tol_TS;
    data_TSPositive["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
GoddardRocket_data.Mesh["s0"] = 0;
GoddardRocket_data.Mesh["segments"][0]["length"] = 1;
GoddardRocket_data.Mesh["segments"][0]["n"] = 100;


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
      file.open( "data/GoddardRocket_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/GoddardRocket_OCP_result_NOT_CONVERGED.txt" );
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
