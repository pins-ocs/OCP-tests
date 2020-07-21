/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Main.cc                                           |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace TwoStageCSTRLoad;
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

    TwoStageCSTR     model("TwoStageCSTR",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
   real_type epsi = 0.0001;
   real_type tol = 0.0001;
    integer InfoLevel = 4;

    GenericContainer &  data_ControlSolver = gc_data["ControlSolver"];
    // ==============================================================
    // 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'MINIMIZATION'
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

    // Redirect output to GenericContainer["stream_output"]
    gc_data["RedirectStreamToString"] = false;

    // Dump Function and Jacobian if uncommented
    gc_data["DumpFile"] = "TwoStageCSTR_dump";

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
    data_Solver["ns_continuation_end"]   = 0;
    GenericContainer & data_Continuation = data_Solver["continuation"];
    data_Continuation["initial_step"]   = 0.2;   // initial step for continuation
    data_Continuation["min_step"]       = 0.001; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]  = 0.5;   // p fails, reduce step by this factor
    data_Continuation["augment_factor"] = 1.5;   // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"] = 8;

    // Boundary Conditions
     GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_x1"] = SET;
    data_BoundaryConditions["initial_x2"] = SET;
    data_BoundaryConditions["initial_x3"] = SET;
    data_BoundaryConditions["initial_x4"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["W"] = 0.1;
    data_Parameters["tau"] = 0.1;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["x1_i"] = 0.15;
    data_Parameters["x2_i"] = -0.03;
    data_Parameters["x3_i"] = 0.1;
    data_Parameters["x4_i"] = 0;

    // Post Processing Parameters

    // User Function Parameters

    // Continuation Parameters

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
    // Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', 'HYPERBOLIC'

    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_u1Control = data_Controls["u1Control"];
    data_u1Control["type"]      = "COS_LOGARITHMIC";
    data_u1Control["epsilon"]   = epsi;
    data_u1Control["tolerance"] = tol;


    GenericContainer & data_u2Control = data_Controls["u2Control"];
    data_u2Control["type"]      = "COS_LOGARITHMIC";
    data_u2Control["epsilon"]   = epsi;
    data_u2Control["tolerance"] = tol;



    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
TwoStageCSTR_data.Mesh["s0"] = 0;
TwoStageCSTR_data.Mesh["segments"][0]["length"] = 2;
TwoStageCSTR_data.Mesh["segments"][0]["n"] = 400;


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
      file.open( "data/TwoStageCSTR_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/TwoStageCSTR_OCP_not_converged.txt" );
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
