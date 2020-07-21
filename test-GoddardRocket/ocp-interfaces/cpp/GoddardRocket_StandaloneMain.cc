/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Main.cc                                          |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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

  Mechatronix::Console    console(&std::cout,4);
  Mechatronix::ThreadPool TP(std::thread::hardware_concurrency());

  try {

    GoddardRocket    model("GoddardRocket",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
   real_type h_i = 1;
   real_type mc = 0.6;
   real_type vc = 620;
   real_type tol_mass = 0.01;
   real_type epsi_T = 0.01;
   real_type g0 = 1;
   real_type c = .5*(g0*h_i)^(1/2);
   real_type tol_TS = 0.01;
   real_type tol_T = 0.01;
   real_type epsi_mass = 0.01;
   real_type epsi_TS = 0.01;
   real_type epsi_v = 0.01;
   real_type m_i = 1;
   real_type Dc = .5*vc*m_i/g0;
   real_type Tmax = 3.5*g0*m_i;
   real_type m_f = mc*m_i;
   real_type tol_v = 0.01;
    integer InfoLevel = 4;

    GenericContainer &  data_ControlSolver = gc_data["ControlSolver"];
    // ==============================================================
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'MINIMIZATION'
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

    // Redirect output to GenericContainer["stream_output"]
    gc_data["RedirectStreamToString"] = false;

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
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY'
    // ==============================================
    data_Solver["last_factorization"] = "LU";
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
    data_Solver["ns_continuation_end"]   = 1;
    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]   = 0.2;   // initial step for continuation
    data_Continuation["min_step"]       = 0.001; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]  = 0.5;   // p fails, reduce step by this factor
    data_Continuation["augment_factor"] = 1.5;   // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"] = 8;

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
    data_Parameters["Tmax"] = Tmax;
    data_Parameters["c"] = c;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["h_i"] = h_i;
    data_Parameters["m_f"] = m_f;
    data_Parameters["m_i"] = m_i;
    data_Parameters["v_i"] = 0;

    // Post Processing Parameters

    // User Function Parameters
    data_Parameters["Dc"] = Dc;
    data_Parameters["g0"] = g0;
    data_Parameters["hc"] = 500;

    // Continuation Parameters
    data_Parameters["epsi_T"] = epsi_T;
    data_Parameters["epsi_TS"] = epsi_TS;
    data_Parameters["tol_T"] = tol_T;
    data_Parameters["tol_TS"] = tol_TS;
    data_Parameters["epsi_TSmin"] = 1e-10;
    data_Parameters["epsi_Tmin"] = 1e-07;
    data_Parameters["tol_TSmin"] = 0.001;
    data_Parameters["tol_Tmin"] = 0.0001;

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
    // Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', 'HYPERBOLIC'

    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_TControl = data_Controls["TControl"];
    data_TControl["type"]      = "QUADRATIC";
    data_TControl["epsilon"]   = epsi_T;
    data_TControl["tolerance"] = tol_T;



    // Constraint1D
    // Penalty subtype: 'PENALTY_REGULAR', 'PENALTY_SMOOTH', 'PENALTY_PIECEWISE'
    // Barrier subtype: 'BARRIER_LOG', 'BARRIER_LOG_EXP', 'BARRIER_LOG0'
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_massPositive = data_Constraints["massPositive"];
    data_massPositive["subType"]   = 'BARRIER_LOG';
    data_massPositive["epsilon"]   = epsi_mass;
    data_massPositive["tolerance"] = tol_mass;
    data_massPositive["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_vPositive = data_Constraints["vPositive"];
    data_vPositive["subType"]   = 'PENALTY_REGULAR';
    data_vPositive["epsilon"]   = epsi_v;
    data_vPositive["tolerance"] = tol_v;
    data_vPositive["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_TSPositive = data_Constraints["TSPositive"];
    data_TSPositive["subType"]   = 'BARRIER_LOG';
    data_TSPositive["epsilon"]   = epsi_TS;
    data_TSPositive["tolerance"] = tol_TS;
    data_TSPositive["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
GoddardRocket_data.Mesh["s0"] = 0;
GoddardRocket_data.Mesh["segments"][0]["length"] = 1;
GoddardRocket_data.Mesh["segments"][0]["n"] = 1000;


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    LW_ASSERT0(
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
    // pModel->set_timeout_ms( 100 );
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data );

    ofstream file;
    if ( ok ) {
      file.open( "data/GoddardRocket_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/GoddardRocket_OCP_not_converged.txt" );
    }
    file.precision(18);
    Mechatronix::saveOCPsolutionToStream(gc_solution,file);
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
      cout << "Parameters:\n";
      gc_solution("parameters").print(cout);
    }
    if ( gc_solution.exists("diagnosis") ) gc_solution("diagnosis").print(cout);
  }
  catch ( exception const & exc ) {
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
