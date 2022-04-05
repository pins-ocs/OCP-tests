/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Main.cc                                            |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace TyreDynamicLoad;
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

    TyreDynamic      model("TyreDynamic",n_threads,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type eps_l = 0.01;
    real_type tol_c0 = 0.1;
    real_type tol_c = tol_c0;
    real_type rw = 0.3;
    real_type eps_c0 = 0.1;
    real_type eps_c = eps_c0;
    real_type tol_l = 0.01;
    real_type w__t0 = 1;
    real_type w__t = w__t0;
    real_type L = 300;
    real_type mesh_np = 2.000000000*L;
    real_type h__b = 1;
    real_type v__0 = 10;
    real_type omega__0 = 1/rw*v__0;
    real_type TT__max = 800;
    real_type E__pow = 60*TT__max;
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
    gc_data["DumpFile"] = "TyreDynamic_dump";

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
    data_Solver["max_accumulated_iter"]  = 1500;
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
    data_BoundaryConditions["initial_v"] = SET;
    data_BoundaryConditions["initial_b"] = SET;
    data_BoundaryConditions["final_v"] = SET;
    data_BoundaryConditions["lambda__i"] = SET;
    data_BoundaryConditions["p__i"] = SET;
    data_BoundaryConditions["omega__i"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["Iw"] = 0.4351;
    data_Parameters["b__lb"] = -1;
    data_Parameters["b__ub"] = 1;
    data_Parameters["l__x"] = 0.1;
    data_Parameters["m"] = 115;
    data_Parameters["p__lb"] = -1;
    data_Parameters["p__ub"] = 1;
    data_Parameters["rw"] = rw;
    data_Parameters["tau__b"] = 0.1;
    data_Parameters["tau__p"] = 0.1;
    data_Parameters["v__adm"] = 1;
    data_Parameters["v__lb"] = 0;
    data_Parameters["v__ub"] = 10000;
    data_Parameters["w__U"] = 0.0001;
    data_Parameters["w__t"] = w__t;
    data_Parameters["b__o__lb"] = -1;
    data_Parameters["b__o__ub"] = 1;
    data_Parameters["lambda__lb"] = -1;
    data_Parameters["lambda__ub"] = 1;
    data_Parameters["omega__lb"] = 0;
    data_Parameters["omega__ub"] = 10000;
    data_Parameters["p__o__lb"] = -1;
    data_Parameters["p__o__ub"] = 1;

    // Guess Parameters
    data_Parameters["p__ss"] = 0.175698;
    data_Parameters["lambda__ss"] = 0.000554;
    data_Parameters["omega__ss"] = 33.351785;

    // Boundary Conditions
    data_Parameters["b__ss"] = 0.1;
    data_Parameters["v__ss"] = 10;

    // Post Processing Parameters
    data_Parameters["g"] = 9.81;
    data_Parameters["h__b"] = h__b;
    data_Parameters["lambda__max"] = 1;

    // User Function Parameters
    data_Parameters["BT__max"] = 300;
    data_Parameters["Bx0"] = 10;
    data_Parameters["Cx0"] = 1.6;
    data_Parameters["E__pow"] = E__pow;
    data_Parameters["TB__max"] = 500;
    data_Parameters["TT__max"] = TT__max;
    data_Parameters["kD"] = 0.2;
    data_Parameters["kDo"] = 0.001;
    data_Parameters["mu__x0"] = 1;
    data_Parameters["rho_a"] = 1.1839;
    data_Parameters["BTv__max"] = 50;

    // Continuation Parameters
    data_Parameters["eps_c0"] = eps_c0;
    data_Parameters["eps_c1"] = 0.01;
    data_Parameters["tol_c0"] = tol_c0;
    data_Parameters["tol_c1"] = 0.01;
    data_Parameters["w__t0"] = w__t0;
    data_Parameters["w__t1"] = 1;

    // Constraints Parameters

    // functions mapped on objects
    GenericContainer & gc_MappedObjects = gc_data["MappedObjects"];

    // PositivePartRegularizedWithErf
    GenericContainer & data_posPart = gc_MappedObjects["posPart"];
    data_posPart["h"] = 0.01;

    // NegativePartRegularizedWithErf
    GenericContainer & data_negPart = gc_MappedObjects["negPart"];
    data_negPart["h"] = 0.01;

    // ClipSuperior
    GenericContainer & data_clipSup = gc_MappedObjects["clipSup"];
    data_clipSup["h"] = 0.01;

    // ClipIntervalWithErf
    GenericContainer & data_clipInt = gc_MappedObjects["clipInt"];
    data_clipInt["delta"] = 0;
    data_clipInt["delta2"] = 0;
    data_clipInt["h"] = 0.01;

    // SignRegularizedWithErf
    GenericContainer & data_sign_reg = gc_MappedObjects["sign_reg"];
    data_sign_reg["h"] = 0.01;

    // AbsoluteValueRegularizedWithErf
    GenericContainer & data_abs_reg = gc_MappedObjects["abs_reg"];
    data_abs_reg["h"] = 0.01;

    // Controls
    // Control Penalty type: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, QUARTIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_b__oControl = data_Controls["b__oControl"];
    data_b__oControl["type"]      = ;
    data_b__oControl["epsilon"]   = eps_c;
    data_b__oControl["tolerance"] = tol_c;


    GenericContainer & data_p__oControl = data_Controls["p__oControl"];
    data_p__oControl["type"]      = ;
    data_p__oControl["epsilon"]   = eps_c;
    data_p__oControl["tolerance"] = tol_c;



    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_OnlyBrakingRear = data_Constraints["OnlyBrakingRear"];
    data_OnlyBrakingRear["subType"]   = "PENALTY_PIECEWISE";
    data_OnlyBrakingRear["epsilon"]   = 0.001;
    data_OnlyBrakingRear["tolerance"] = h__b;
    data_OnlyBrakingRear["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_OnlyTractionRear = data_Constraints["OnlyTractionRear"];
    data_OnlyTractionRear["subType"]   = "PENALTY_PIECEWISE";
    data_OnlyTractionRear["epsilon"]   = 0.001;
    data_OnlyTractionRear["tolerance"] = h__b;
    data_OnlyTractionRear["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LongSlipRear_min = data_Constraints["LongSlipRear_min"];
    data_LongSlipRear_min["subType"]   = "PENALTY_PIECEWISE";
    data_LongSlipRear_min["epsilon"]   = eps_l;
    data_LongSlipRear_min["tolerance"] = tol_l;
    data_LongSlipRear_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_LongSlipRear_max = data_Constraints["LongSlipRear_max"];
    data_LongSlipRear_max["subType"]   = "PENALTY_PIECEWISE";
    data_LongSlipRear_max["epsilon"]   = eps_l;
    data_LongSlipRear_max["tolerance"] = tol_l;
    data_LongSlipRear_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_v_min = data_Constraints["v_min"];
    data_v_min["subType"]   = "BARRIER_LOG";
    data_v_min["epsilon"]   = eps_l;
    data_v_min["tolerance"] = tol_l;
    data_v_min["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
TyreDynamic_data.Mesh["s0"] = 0;
TyreDynamic_data.Mesh["segments"][0]["n"] = .4*mesh_np;
TyreDynamic_data.Mesh["segments"][0]["length"] = .1*L;
TyreDynamic_data.Mesh["segments"][1]["n"] = .8*mesh_np;
TyreDynamic_data.Mesh["segments"][1]["length"] = .8*L;
TyreDynamic_data.Mesh["segments"][2]["n"] = .4*mesh_np;
TyreDynamic_data.Mesh["segments"][2]["length"] = .1*L;


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
      file.open( "data/TyreDynamic_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/TyreDynamic_OCP_result_NOT_CONVERGED.txt" );
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
