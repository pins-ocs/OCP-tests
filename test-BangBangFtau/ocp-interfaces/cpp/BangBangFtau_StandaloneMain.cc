/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Main.cc                                           |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace BangBangFtauLoad;
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

    BangBangFtau     model("BangBangFtau",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
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
    gc_data["DumpFile"] = "BangBangFtau_dump";

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
    data_BoundaryConditions["initial_x"] = SET;
    data_BoundaryConditions["initial_v"] = SET;
    data_BoundaryConditions["initial_sT"] = SET;
    data_BoundaryConditions["initial_sB"] = SET;
    data_BoundaryConditions["final_v"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["epsiTB"] = 0.001;
    data_Parameters["maxClip"] = 1;
    data_Parameters["maxT"] = 2;
    data_Parameters["minClip"] = -1;
    data_Parameters["tauB"] = 0.001;
    data_Parameters["tauT"] = 0.02;

    // Guess Parameters

    // Boundary Conditions

    // Post Processing Parameters

    // User Function Parameters

    // Continuation Parameters

    // Constraints Parameters

    // functions mapped on objects

    // ClipIntervalWithErf
    GenericContainer & data_clip = dc_data("clip");
    data_clip["h"] = 0.1;
    data_clip["delta"] = 0;

    // Controls: No penalties or barriers constraint defined

    // Constraint1D
    // Penalty subtype: 'PENALTY_REGULAR', 'PENALTY_SMOOTH', 'PENALTY_PIECEWISE'
    // Barrier subtype: 'BARRIER_LOG', 'BARRIER_LOG_EXP', 'BARRIER_LOG0'
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_vsTpositive = data_Constraints["vsTpositive"];
    data_vsTpositive["subType"]   = 'PENALTY_REGULAR';
    data_vsTpositive["epsilon"]   = 0.001;
    data_vsTpositive["tolerance"] = 0.001;
    data_vsTpositive["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_vsBpositive = data_Constraints["vsBpositive"];
    data_vsBpositive["subType"]   = 'PENALTY_REGULAR';
    data_vsBpositive["epsilon"]   = 0.001;
    data_vsBpositive["tolerance"] = 0.001;
    data_vsBpositive["active"]    = true;
    // PenaltyBarrier1DGreaterThan
    GenericContainer & data_vsTmax = data_Constraints["vsTmax"];
    data_vsTmax["subType"]   = 'PENALTY_REGULAR';
    data_vsTmax["epsilon"]   = 0.001;
    data_vsTmax["tolerance"] = 0.001;
    data_vsTmax["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_vsTBInterval = data_Constraints["vsTBInterval"];
    data_vsTBInterval["subType"]   = "PENALTY_REGULAR";
    data_vsTBInterval["epsilon"]   = 0.001;
    data_vsTBInterval["tolerance"] = 0.001;
    data_vsTBInterval["min"]       = -1;
    data_vsTBInterval["max"]       = 1;
    data_vsTBInterval["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
BangBangFtau_data.Mesh["s0"] = 0;
BangBangFtau_data.Mesh["segments"][0]["n"] = 10;
BangBangFtau_data.Mesh["segments"][0]["length"] = 0.1;
BangBangFtau_data.Mesh["segments"][1]["n"] = 40;
BangBangFtau_data.Mesh["segments"][1]["length"] = 0.4;
BangBangFtau_data.Mesh["segments"][2]["n"] = 40;
BangBangFtau_data.Mesh["segments"][2]["length"] = 0.4;
BangBangFtau_data.Mesh["segments"][3]["n"] = 10;
BangBangFtau_data.Mesh["segments"][3]["length"] = 0.1;


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
      file.open( "data/BangBangFtau_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/BangBangFtau_OCP_not_converged.txt" );
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
