/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Main.cc                                 |
 |                                                                       |
 |  version: 1.0   date 5/12/2021                                        |
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


#include "ICLOCS_ParallelParking.hh"
#include "ICLOCS_ParallelParking_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace ICLOCS_ParallelParkingLoad;
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

    ICLOCS_ParallelParking model("ICLOCS_ParallelParking",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type epsi_ctrl = 0.01;
    real_type len_cl = 0;
    real_type tol_slot = 0.001;
    real_type len_a = 2.5;
    real_type epsi_slot = 0.01;
    real_type tol_ctrl = 0.001;
    real_type len_r = 0.7;
    real_type x_i = len_sl+len_r;
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
    gc_data["DumpFile"] = "ICLOCS_ParallelParking_dump";

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
    data_Solver["ns_continuation_end"]   = 0;

    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_x"] = SET;
    data_BoundaryConditions["initial_y"] = SET;
    data_BoundaryConditions["initial_theta"] = SET;
    data_BoundaryConditions["initial_phi"] = SET;
    data_BoundaryConditions["initial_v"] = SET;
    data_BoundaryConditions["initial_a"] = SET;
    data_BoundaryConditions["final_v"] = SET;
    data_BoundaryConditions["final_a"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["len_a"] = len_a;

    // Guess Parameters
    data_Parameters["T_guess"] = 10;

    // Boundary Conditions
    data_Parameters["a_f"] = 0;
    data_Parameters["a_i"] = 0;
    data_Parameters["phi_i"] = 0;
    data_Parameters["theta_i"] = 0;
    data_Parameters["v_f"] = 0;
    data_Parameters["v_i"] = 0;
    data_Parameters["x_i"] = x_i;
    data_Parameters["y_i"] = 1.5;

    // Post Processing Parameters

    // User Function Parameters
    data_Parameters["b"] = 0.8855;
    data_Parameters["len_SL"] = 0;
    data_Parameters["len_f"] = 0.8;
    data_Parameters["len_r"] = len_r;

    // Continuation Parameters

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_u1Control = data_Controls["u1Control"];
    data_u1Control["type"]      = ;
    data_u1Control["epsilon"]   = epsi_ctrl;
    data_u1Control["tolerance"] = tol_ctrl;


    GenericContainer & data_u2Control = data_Controls["u2Control"];
    data_u2Control["type"]      = ;
    data_u2Control["epsilon"]   = epsi_ctrl;
    data_u2Control["tolerance"] = tol_ctrl;



    // Constraint1D
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DInterval
    GenericContainer & data_A_bound = data_Constraints["A_bound"];
    data_A_bound["subType"]   = "BARRIER_LOG";
    data_A_bound["epsilon"]   = epsi_slot;
    data_A_bound["tolerance"] = tol_slot;
    data_A_bound["min"]       = f_slot(Ax(x(zeta),y(zeta),theta(zeta)));
    data_A_bound["max"]       = len_cl;
    data_A_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_B_bound = data_Constraints["B_bound"];
    data_B_bound["subType"]   = "BARRIER_LOG";
    data_B_bound["epsilon"]   = epsi_slot;
    data_B_bound["tolerance"] = tol_slot;
    data_B_bound["min"]       = f_slot(Bx(x(zeta),y(zeta),theta(zeta)));
    data_B_bound["max"]       = len_cl;
    data_B_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_C_bound = data_Constraints["C_bound"];
    data_C_bound["subType"]   = "BARRIER_LOG";
    data_C_bound["epsilon"]   = epsi_slot;
    data_C_bound["tolerance"] = tol_slot;
    data_C_bound["min"]       = f_slot(Cx(x(zeta),y(zeta),theta(zeta)));
    data_C_bound["max"]       = len_cl;
    data_C_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_D_bound = data_Constraints["D_bound"];
    data_D_bound["subType"]   = "BARRIER_LOG";
    data_D_bound["epsilon"]   = epsi_slot;
    data_D_bound["tolerance"] = tol_slot;
    data_D_bound["min"]       = f_slot(Dx(x(zeta),y(zeta),theta(zeta)));
    data_D_bound["max"]       = len_cl;
    data_D_bound["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_EXTRA1_bound = data_Constraints["EXTRA1_bound"];
    data_EXTRA1_bound["subType"]   = "BARRIER_LOG";
    data_EXTRA1_bound["epsilon"]   = epsi_slot;
    data_EXTRA1_bound["tolerance"] = tol_slot;
    data_EXTRA1_bound["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_EXTRA2_bound = data_Constraints["EXTRA2_bound"];
    data_EXTRA2_bound["subType"]   = "BARRIER_LOG";
    data_EXTRA2_bound["epsilon"]   = epsi_slot;
    data_EXTRA2_bound["tolerance"] = tol_slot;
    data_EXTRA2_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_vel_bound = data_Constraints["vel_bound"];
    data_vel_bound["subType"]   = "BARRIER_LOG";
    data_vel_bound["epsilon"]   = epsi_slot;
    data_vel_bound["tolerance"] = tol_slot;
    data_vel_bound["min"]       = -2;
    data_vel_bound["max"]       = 2;
    data_vel_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_acc_bound = data_Constraints["acc_bound"];
    data_acc_bound["subType"]   = "BARRIER_LOG";
    data_acc_bound["epsilon"]   = epsi_slot;
    data_acc_bound["tolerance"] = tol_slot;
    data_acc_bound["min"]       = -0.75;
    data_acc_bound["max"]       = 0.75;
    data_acc_bound["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_phi_bound = data_Constraints["phi_bound"];
    data_phi_bound["subType"]   = "BARRIER_LOG";
    data_phi_bound["epsilon"]   = epsi_slot;
    data_phi_bound["tolerance"] = tol_slot;
    data_phi_bound["min"]       = -11/60.0*Mechatronix::m_pi;
    data_phi_bound["max"]       = 11/60.0*Mechatronix::m_pi;
    data_phi_bound["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
ICLOCS_ParallelParking_data.Mesh["s0"] = 0;
ICLOCS_ParallelParking_data.Mesh["segments"][0]["n"] = 100;
ICLOCS_ParallelParking_data.Mesh["segments"][0]["length"] = 1;


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
      file.open( "data/ICLOCS_ParallelParking_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/ICLOCS_ParallelParking_OCP_result_NOT_CONVERGED.txt" );
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
