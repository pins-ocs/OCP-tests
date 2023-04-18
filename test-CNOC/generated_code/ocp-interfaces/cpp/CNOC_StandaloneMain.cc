/*-----------------------------------------------------------------------*\
 |  file: CNOC_Main.cc                                                   |
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


#include "CNOC.hh"
#include "CNOC_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::ToolPath2D;

using namespace CNOCLoad;
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

    CNOC             model("CNOC",&console,&TP);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    ToolPath2D       toolPath2D( "toolPath2D" );

    // Auxiliary values
    real_type v_nom = 0.173;
    real_type tol_CTRL = 0.01;
    real_type epsi_VMAX = 0.01;
    real_type tol_COV = 0.01;
    real_type epsi_CTRL = 0.01;
    real_type js_max = 30;
    real_type jn_max = 65;
    real_type js_min = -50;
    real_type tol_VMAX = 0.01;
    real_type tol_PATH = 0.01;
    real_type epsi_COV = 0.01;
    real_type path_following_tolerance = 1.0e-05;
    real_type epsi_ACC = 0.01;
    real_type pf_error = path_following_tolerance;
    real_type epsi_PATH = 0.01;
    real_type tol_ACC = 0.01;
    real_type mesh_segments = 100;
    real_type deltaFeed = v_nom;
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
    gc_data["DumpFile"] = "CNOC_dump";

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
    data_BoundaryConditions["initial_n"] = SET;
    data_BoundaryConditions["initial_vs"] = SET;
    data_BoundaryConditions["initial_vn"] = SET;
    data_BoundaryConditions["initial_as"] = SET;
    data_BoundaryConditions["initial_an"] = SET;
    data_BoundaryConditions["final_n"] = SET;
    data_BoundaryConditions["final_vs"] = SET;
    data_BoundaryConditions["final_vn"] = SET;
    data_BoundaryConditions["final_as"] = SET;
    data_BoundaryConditions["final_an"] = SET;
    data_BoundaryConditions["initial_s"] = SET;
    data_BoundaryConditions["final_s"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters
    data_Parameters["jn_max"] = jn_max;
    data_Parameters["js_max"] = js_max;
    data_Parameters["js_min"] = js_min;
    data_Parameters["deltaFeed"] = deltaFeed;

    // Guess Parameters

    // Boundary Conditions
    data_Parameters["an_f"] = 0;
    data_Parameters["an_i"] = 0;
    data_Parameters["as_f"] = 0;
    data_Parameters["as_i"] = 0;
    data_Parameters["n_f"] = 0;
    data_Parameters["n_i"] = 0;
    data_Parameters["vn_f"] = 0;
    data_Parameters["vn_i"] = 0;
    data_Parameters["vs_f"] = 0;
    data_Parameters["vs_i"] = 0;

    // Post Processing Parameters
    data_Parameters["an_max"] = 1.2;
    data_Parameters["as_max"] = 2.1;
    data_Parameters["ax_max"] = 2.1;
    data_Parameters["ay_max"] = 2.1;
    data_Parameters["pf_error"] = pf_error;
    data_Parameters["path_following_tolerance"] = path_following_tolerance;

    // User Function Parameters

    // Continuation Parameters

    // Constraints Parameters

    // functions mapped on objects

    // Controls
    // Control Penalty type: QUADRATIC, PARABOLA, CUBIC, QUARTIC, BIPOWER
    // Control Barrier type: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
    GenericContainer & data_Controls = gc_data["Controls"];
    GenericContainer & data_jsControl = data_Controls["jsControl"];
    data_jsControl["type"]      = "LOGARITHMIC";
    data_jsControl["epsilon"]   = epsi_CTRL;
    data_jsControl["tolerance"] = tol_CTRL;


    GenericContainer & data_jnControl = data_Controls["jnControl"];
    data_jnControl["type"]      = "LOGARITHMIC";
    data_jnControl["epsilon"]   = epsi_CTRL;
    data_jnControl["tolerance"] = tol_CTRL;



    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_timePositive = data_Constraints["timePositive"];
    data_timePositive["subType"]   = "BARRIER_LOG";
    data_timePositive["epsilon"]   = epsi_COV;
    data_timePositive["tolerance"] = tol_COV;
    data_timePositive["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_vLimit = data_Constraints["vLimit"];
    data_vLimit["subType"]   = "PENALTY_PIECEWISE";
    data_vLimit["epsilon"]   = epsi_VMAX;
    data_vLimit["tolerance"] = tol_VMAX;
    data_vLimit["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_PathFollowingTolerance_min = data_Constraints["PathFollowingTolerance_min"];
    data_PathFollowingTolerance_min["subType"]   = "PENALTY_REGULAR";
    data_PathFollowingTolerance_min["epsilon"]   = epsi_PATH;
    data_PathFollowingTolerance_min["tolerance"] = tol_PATH;
    data_PathFollowingTolerance_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_PathFollowingTolerance_max = data_Constraints["PathFollowingTolerance_max"];
    data_PathFollowingTolerance_max["subType"]   = "PENALTY_REGULAR";
    data_PathFollowingTolerance_max["epsilon"]   = epsi_PATH;
    data_PathFollowingTolerance_max["tolerance"] = tol_PATH;
    data_PathFollowingTolerance_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_as_limit_min = data_Constraints["as_limit_min"];
    data_as_limit_min["subType"]   = "PENALTY_REGULAR";
    data_as_limit_min["epsilon"]   = epsi_ACC;
    data_as_limit_min["tolerance"] = tol_ACC;
    data_as_limit_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_as_limit_max = data_Constraints["as_limit_max"];
    data_as_limit_max["subType"]   = "PENALTY_REGULAR";
    data_as_limit_max["epsilon"]   = epsi_ACC;
    data_as_limit_max["tolerance"] = tol_ACC;
    data_as_limit_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_an_limit_min = data_Constraints["an_limit_min"];
    data_an_limit_min["subType"]   = "PENALTY_REGULAR";
    data_an_limit_min["epsilon"]   = epsi_ACC;
    data_an_limit_min["tolerance"] = tol_ACC;
    data_an_limit_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_an_limit_max = data_Constraints["an_limit_max"];
    data_an_limit_max["subType"]   = "PENALTY_REGULAR";
    data_an_limit_max["epsilon"]   = epsi_ACC;
    data_an_limit_max["tolerance"] = tol_ACC;
    data_an_limit_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_ax_limit_min = data_Constraints["ax_limit_min"];
    data_ax_limit_min["subType"]   = "PENALTY_REGULAR";
    data_ax_limit_min["epsilon"]   = epsi_ACC;
    data_ax_limit_min["tolerance"] = tol_ACC;
    data_ax_limit_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_ax_limit_max = data_Constraints["ax_limit_max"];
    data_ax_limit_max["subType"]   = "PENALTY_REGULAR";
    data_ax_limit_max["epsilon"]   = epsi_ACC;
    data_ax_limit_max["tolerance"] = tol_ACC;
    data_ax_limit_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_ay_limit_min = data_Constraints["ay_limit_min"];
    data_ay_limit_min["subType"]   = "PENALTY_REGULAR";
    data_ay_limit_min["epsilon"]   = epsi_ACC;
    data_ay_limit_min["tolerance"] = tol_ACC;
    data_ay_limit_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_ay_limit_max = data_Constraints["ay_limit_max"];
    data_ay_limit_max["subType"]   = "PENALTY_REGULAR";
    data_ay_limit_max["epsilon"]   = epsi_ACC;
    data_ay_limit_max["tolerance"] = tol_ACC;
    data_ay_limit_max["active"]    = true;
    // Constraint1D: none defined
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: T O O L P A T H 2 D
CNOC_data.ToolPath2D["segments"][0]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][0]["y0"] = 0;
CNOC_data.ToolPath2D["segments"][0]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][0]["y1"] = 0.002;
CNOC_data.ToolPath2D["segments"][0]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][0]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][0]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][0]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][0]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][1]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][1]["y0"] = 0.002;
CNOC_data.ToolPath2D["segments"][1]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][1]["y1"] = 0;
CNOC_data.ToolPath2D["segments"][1]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][1]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][1]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][1]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][1]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][2]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][2]["y0"] = 0;
CNOC_data.ToolPath2D["segments"][2]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][2]["y1"] = 0.01;
CNOC_data.ToolPath2D["segments"][2]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][2]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][2]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][2]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][2]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][2]["angle0"] = 0;
CNOC_data.ToolPath2D["segments"][2]["angle1"] = 3.1415;
CNOC_data.ToolPath2D["segments"][3]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][3]["y0"] = 0.01;
CNOC_data.ToolPath2D["segments"][3]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][3]["y1"] = 0.012;
CNOC_data.ToolPath2D["segments"][3]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][3]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][3]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][3]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][3]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][4]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][4]["y0"] = 0.012;
CNOC_data.ToolPath2D["segments"][4]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][4]["y1"] = 0.01;
CNOC_data.ToolPath2D["segments"][4]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][4]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][4]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][4]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][4]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][5]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][5]["y0"] = 0.01;
CNOC_data.ToolPath2D["segments"][5]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][5]["y1"] = 0.02;
CNOC_data.ToolPath2D["segments"][5]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][5]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][5]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][5]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][5]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][6]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][6]["y0"] = 0.02;
CNOC_data.ToolPath2D["segments"][6]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][6]["y1"] = 0.022;
CNOC_data.ToolPath2D["segments"][6]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][6]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][6]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][6]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][6]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][7]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][7]["y0"] = 0.022;
CNOC_data.ToolPath2D["segments"][7]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][7]["y1"] = 0.02;
CNOC_data.ToolPath2D["segments"][7]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][7]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][7]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][7]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][7]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][8]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][8]["y0"] = 0.02;
CNOC_data.ToolPath2D["segments"][8]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][8]["y1"] = 0.03;
CNOC_data.ToolPath2D["segments"][8]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][8]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][8]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][8]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][8]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][8]["angle0"] = 0;
CNOC_data.ToolPath2D["segments"][8]["angle1"] = 3.1415;
CNOC_data.ToolPath2D["segments"][9]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][9]["y0"] = 0.03;
CNOC_data.ToolPath2D["segments"][9]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][9]["y1"] = 0.032;
CNOC_data.ToolPath2D["segments"][9]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][9]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][9]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][9]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][9]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][10]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][10]["y0"] = 0.032;
CNOC_data.ToolPath2D["segments"][10]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][10]["y1"] = 0.03;
CNOC_data.ToolPath2D["segments"][10]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][10]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][10]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][10]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][10]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][11]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][11]["y0"] = 0.03;
CNOC_data.ToolPath2D["segments"][11]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][11]["y1"] = 0.04;
CNOC_data.ToolPath2D["segments"][11]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][11]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][11]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][11]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][11]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][12]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][12]["y0"] = 0.04;
CNOC_data.ToolPath2D["segments"][12]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][12]["y1"] = 0.042;
CNOC_data.ToolPath2D["segments"][12]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][12]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][12]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][12]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][12]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][13]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][13]["y0"] = 0.042;
CNOC_data.ToolPath2D["segments"][13]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][13]["y1"] = 0.04;
CNOC_data.ToolPath2D["segments"][13]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][13]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][13]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][13]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][13]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][14]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][14]["y0"] = 0.04;
CNOC_data.ToolPath2D["segments"][14]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][14]["y1"] = 0.05;
CNOC_data.ToolPath2D["segments"][14]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][14]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][14]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][14]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][14]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][14]["angle0"] = 0;
CNOC_data.ToolPath2D["segments"][14]["angle1"] = 3.1415;
CNOC_data.ToolPath2D["segments"][15]["x0"] = 0.05;
CNOC_data.ToolPath2D["segments"][15]["y0"] = 0.05;
CNOC_data.ToolPath2D["segments"][15]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][15]["y1"] = 0.052;
CNOC_data.ToolPath2D["segments"][15]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][15]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][15]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][15]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][15]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][16]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][16]["y0"] = 0.052;
CNOC_data.ToolPath2D["segments"][16]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][16]["y1"] = 0.05;
CNOC_data.ToolPath2D["segments"][16]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][16]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][16]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][16]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][16]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][17]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][17]["y0"] = 0.05;
CNOC_data.ToolPath2D["segments"][17]["x1"] = -0.01;
CNOC_data.ToolPath2D["segments"][17]["y1"] = 0.06;
CNOC_data.ToolPath2D["segments"][17]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][17]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][17]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][17]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][17]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][18]["x0"] = -0.01;
CNOC_data.ToolPath2D["segments"][18]["y0"] = 0.06;
CNOC_data.ToolPath2D["segments"][18]["x1"] = 0.02;
CNOC_data.ToolPath2D["segments"][18]["y1"] = 0.062;
CNOC_data.ToolPath2D["segments"][18]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][18]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][18]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][18]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][18]["n"] = mesh_segments;
CNOC_data.ToolPath2D["segments"][19]["x0"] = 0.02;
CNOC_data.ToolPath2D["segments"][19]["y0"] = 0.062;
CNOC_data.ToolPath2D["segments"][19]["x1"] = 0.05;
CNOC_data.ToolPath2D["segments"][19]["y1"] = 0.06;
CNOC_data.ToolPath2D["segments"][19]["feedRate"] = v_nom;
CNOC_data.ToolPath2D["segments"][19]["spindleRate"] = 3000;
CNOC_data.ToolPath2D["segments"][19]["crossSection"] = 1;
CNOC_data.ToolPath2D["segments"][19]["tolerance"] = path_following_tolerance;
CNOC_data.ToolPath2D["segments"][19]["n"] = mesh_segments;


    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
      gc_data.exists("ToolPath2D"),
      "missing key: ``ToolPath2D'' in gc_data\n"
    );
    toolPath2D.setup(gc_data("ToolPath2D"));
    ptrs[ "pToolPath2D" ] = &toolPath2D;

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
      file.open( "data/CNOC_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/CNOC_OCP_result_NOT_CONVERGED.txt" );
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
