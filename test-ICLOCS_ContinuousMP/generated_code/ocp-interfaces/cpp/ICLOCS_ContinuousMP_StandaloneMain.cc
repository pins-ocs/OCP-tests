/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Main.cc                                    |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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


#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace ICLOCS_ContinuousMPLoad;
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

    ICLOCS_ContinuousMP model("ICLOCS_ContinuousMP",&TP,&console);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type xy_tol0 = 0.1;
    real_type xy_eps0 = 0.1;
    real_type xy_tol = xy_tol0;
    real_type epsi_ctrl = 0.01;
    real_type xy_bound = 2;
    real_type xy_eps = xy_eps0;
    real_type tol_ctrl = 0.01;
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
    gc_data["DumpFile"] = "ICLOCS_ContinuousMP_dump";

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
    data_Continuation["initial_step"]    = 0.2   ; // initial step for continuation
    data_Continuation["min_step"]        = 0.001 ; // minimum accepted step for continuation
    data_Continuation["reduce_factor"]   = 0.5   ; // if continuation step fails, reduce step by this factor
    data_Continuation["augment_factor"]  = 1.5   ; // if step successful in less than few_iteration augment step by this factor
    data_Continuation["few_iterations"]  = 8     ; // if step successful in less than few_iteration augment step by this factor

    // Boundary Conditions
    GenericContainer & data_BoundaryConditions = gc_data["BoundaryConditions"];
    data_BoundaryConditions["initial_xx1"] = SET;
    data_BoundaryConditions["initial_yy1"] = SET;
    data_BoundaryConditions["X1_continuity"] = SET;
    data_BoundaryConditions["X2_continuity"] = SET;
    data_BoundaryConditions["X3_continuity"] = SET;
    data_BoundaryConditions["X4_continuity"] = SET;
    data_BoundaryConditions["X5_continuity"] = SET;
    data_BoundaryConditions["X6_continuity"] = SET;
    data_BoundaryConditions["X7_continuity"] = SET;
    data_BoundaryConditions["X8_continuity"] = SET;
    data_BoundaryConditions["X9_continuity"] = SET;
    data_BoundaryConditions["X10_continuity"] = SET;
    data_BoundaryConditions["X11_continuity"] = SET;
    data_BoundaryConditions["X12_continuity"] = SET;
    data_BoundaryConditions["X13_continuity"] = SET;
    data_BoundaryConditions["X14_continuity"] = SET;
    data_BoundaryConditions["X15_continuity"] = SET;
    data_BoundaryConditions["X16_continuity"] = SET;
    data_BoundaryConditions["X17_continuity"] = SET;
    data_BoundaryConditions["X18_continuity"] = SET;
    data_BoundaryConditions["X19_continuity"] = SET;
    data_BoundaryConditions["Y1_continuity"] = SET;
    data_BoundaryConditions["Y2_continuity"] = SET;
    data_BoundaryConditions["Y3_continuity"] = SET;
    data_BoundaryConditions["Y4_continuity"] = SET;
    data_BoundaryConditions["Y5_continuity"] = SET;
    data_BoundaryConditions["Y6_continuity"] = SET;
    data_BoundaryConditions["Y7_continuity"] = SET;
    data_BoundaryConditions["Y8_continuity"] = SET;
    data_BoundaryConditions["Y9_continuity"] = SET;
    data_BoundaryConditions["Y10_continuity"] = SET;
    data_BoundaryConditions["Y11_continuity"] = SET;
    data_BoundaryConditions["Y12_continuity"] = SET;
    data_BoundaryConditions["Y13_continuity"] = SET;
    data_BoundaryConditions["Y14_continuity"] = SET;
    data_BoundaryConditions["Y15_continuity"] = SET;
    data_BoundaryConditions["Y16_continuity"] = SET;
    data_BoundaryConditions["Y17_continuity"] = SET;
    data_BoundaryConditions["Y18_continuity"] = SET;
    data_BoundaryConditions["Y19_continuity"] = SET;
    data_BoundaryConditions["X1_initial"] = SET;
    data_BoundaryConditions["X2_initial"] = SET;
    data_BoundaryConditions["X3_initial"] = SET;
    data_BoundaryConditions["X4_initial"] = SET;
    data_BoundaryConditions["X5_initial"] = SET;
    data_BoundaryConditions["X6_initial"] = SET;
    data_BoundaryConditions["X7_initial"] = SET;
    data_BoundaryConditions["X8_initial"] = SET;
    data_BoundaryConditions["X9_initial"] = SET;
    data_BoundaryConditions["X10_initial"] = SET;
    data_BoundaryConditions["X11_initial"] = SET;
    data_BoundaryConditions["X12_initial"] = SET;
    data_BoundaryConditions["X13_initial"] = SET;
    data_BoundaryConditions["X14_initial"] = SET;
    data_BoundaryConditions["X15_initial"] = SET;
    data_BoundaryConditions["X16_initial"] = SET;
    data_BoundaryConditions["X17_initial"] = SET;
    data_BoundaryConditions["X18_initial"] = SET;
    data_BoundaryConditions["X19_initial"] = SET;
    data_BoundaryConditions["X20_initial"] = SET;
    data_BoundaryConditions["Y1_initial"] = SET;
    data_BoundaryConditions["Y2_initial"] = SET;
    data_BoundaryConditions["Y3_initial"] = SET;
    data_BoundaryConditions["Y4_initial"] = SET;
    data_BoundaryConditions["Y5_initial"] = SET;
    data_BoundaryConditions["Y6_initial"] = SET;
    data_BoundaryConditions["Y7_initial"] = SET;
    data_BoundaryConditions["Y8_initial"] = SET;
    data_BoundaryConditions["Y9_initial"] = SET;
    data_BoundaryConditions["Y10_initial"] = SET;
    data_BoundaryConditions["Y11_initial"] = SET;
    data_BoundaryConditions["Y12_initial"] = SET;
    data_BoundaryConditions["Y13_initial"] = SET;
    data_BoundaryConditions["Y14_initial"] = SET;
    data_BoundaryConditions["Y15_initial"] = SET;
    data_BoundaryConditions["Y16_initial"] = SET;
    data_BoundaryConditions["Y17_initial"] = SET;
    data_BoundaryConditions["Y18_initial"] = SET;
    data_BoundaryConditions["Y19_initial"] = SET;
    data_BoundaryConditions["Y20_initial"] = SET;

    // Guess
    GenericContainer & data_Guess = gc_data["Guess"];
    // possible value: zero, default, none, warm
    data_Guess["initialize"] = "zero";
    // possible value: default, none, warm, spline, table
    data_Guess["guess_type"] = "default";

    GenericContainer & data_Parameters = gc_data["Parameters"];
    // Model Parameters

    // Guess Parameters

    // Boundary Conditions

    // Post Processing Parameters

    // User Function Parameters

    // Continuation Parameters
    data_Parameters["xy_eps0"] = xy_eps0;
    data_Parameters["xy_eps1"] = 0.001;
    data_Parameters["xy_tol0"] = xy_tol0;
    data_Parameters["xy_tol1"] = 0.001;

    // Constraints Parameters

    // functions mapped on objects

    // Controls: No penalties or barriers constraint defined

    // Constraint1D
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DInterval
    GenericContainer & data_u1Limitation = data_Constraints["u1Limitation"];
    data_u1Limitation["subType"]   = "BARRIER_LOG";
    data_u1Limitation["epsilon"]   = epsi_ctrl;
    data_u1Limitation["tolerance"] = tol_ctrl;
    data_u1Limitation["min"]       = -10;
    data_u1Limitation["max"]       = 10;
    data_u1Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u2Limitation = data_Constraints["u2Limitation"];
    data_u2Limitation["subType"]   = "BARRIER_LOG";
    data_u2Limitation["epsilon"]   = epsi_ctrl;
    data_u2Limitation["tolerance"] = tol_ctrl;
    data_u2Limitation["min"]       = -10;
    data_u2Limitation["max"]       = 10;
    data_u2Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u3Limitation = data_Constraints["u3Limitation"];
    data_u3Limitation["subType"]   = "BARRIER_LOG";
    data_u3Limitation["epsilon"]   = epsi_ctrl;
    data_u3Limitation["tolerance"] = tol_ctrl;
    data_u3Limitation["min"]       = -10;
    data_u3Limitation["max"]       = 10;
    data_u3Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u4Limitation = data_Constraints["u4Limitation"];
    data_u4Limitation["subType"]   = "BARRIER_LOG";
    data_u4Limitation["epsilon"]   = epsi_ctrl;
    data_u4Limitation["tolerance"] = tol_ctrl;
    data_u4Limitation["min"]       = -10;
    data_u4Limitation["max"]       = 10;
    data_u4Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u5Limitation = data_Constraints["u5Limitation"];
    data_u5Limitation["subType"]   = "BARRIER_LOG";
    data_u5Limitation["epsilon"]   = epsi_ctrl;
    data_u5Limitation["tolerance"] = tol_ctrl;
    data_u5Limitation["min"]       = -10;
    data_u5Limitation["max"]       = 10;
    data_u5Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u6Limitation = data_Constraints["u6Limitation"];
    data_u6Limitation["subType"]   = "BARRIER_LOG";
    data_u6Limitation["epsilon"]   = epsi_ctrl;
    data_u6Limitation["tolerance"] = tol_ctrl;
    data_u6Limitation["min"]       = -10;
    data_u6Limitation["max"]       = 10;
    data_u6Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u7Limitation = data_Constraints["u7Limitation"];
    data_u7Limitation["subType"]   = "BARRIER_LOG";
    data_u7Limitation["epsilon"]   = epsi_ctrl;
    data_u7Limitation["tolerance"] = tol_ctrl;
    data_u7Limitation["min"]       = -10;
    data_u7Limitation["max"]       = 10;
    data_u7Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u8Limitation = data_Constraints["u8Limitation"];
    data_u8Limitation["subType"]   = "BARRIER_LOG";
    data_u8Limitation["epsilon"]   = epsi_ctrl;
    data_u8Limitation["tolerance"] = tol_ctrl;
    data_u8Limitation["min"]       = -10;
    data_u8Limitation["max"]       = 10;
    data_u8Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u9Limitation = data_Constraints["u9Limitation"];
    data_u9Limitation["subType"]   = "BARRIER_LOG";
    data_u9Limitation["epsilon"]   = epsi_ctrl;
    data_u9Limitation["tolerance"] = tol_ctrl;
    data_u9Limitation["min"]       = -10;
    data_u9Limitation["max"]       = 10;
    data_u9Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u10Limitation = data_Constraints["u10Limitation"];
    data_u10Limitation["subType"]   = "BARRIER_LOG";
    data_u10Limitation["epsilon"]   = epsi_ctrl;
    data_u10Limitation["tolerance"] = tol_ctrl;
    data_u10Limitation["min"]       = -10;
    data_u10Limitation["max"]       = 10;
    data_u10Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u11Limitation = data_Constraints["u11Limitation"];
    data_u11Limitation["subType"]   = "BARRIER_LOG";
    data_u11Limitation["epsilon"]   = epsi_ctrl;
    data_u11Limitation["tolerance"] = tol_ctrl;
    data_u11Limitation["min"]       = -10;
    data_u11Limitation["max"]       = 10;
    data_u11Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u12Limitation = data_Constraints["u12Limitation"];
    data_u12Limitation["subType"]   = "BARRIER_LOG";
    data_u12Limitation["epsilon"]   = epsi_ctrl;
    data_u12Limitation["tolerance"] = tol_ctrl;
    data_u12Limitation["min"]       = -10;
    data_u12Limitation["max"]       = 10;
    data_u12Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u13Limitation = data_Constraints["u13Limitation"];
    data_u13Limitation["subType"]   = "BARRIER_LOG";
    data_u13Limitation["epsilon"]   = epsi_ctrl;
    data_u13Limitation["tolerance"] = tol_ctrl;
    data_u13Limitation["min"]       = -10;
    data_u13Limitation["max"]       = 10;
    data_u13Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u14Limitation = data_Constraints["u14Limitation"];
    data_u14Limitation["subType"]   = "BARRIER_LOG";
    data_u14Limitation["epsilon"]   = epsi_ctrl;
    data_u14Limitation["tolerance"] = tol_ctrl;
    data_u14Limitation["min"]       = -10;
    data_u14Limitation["max"]       = 10;
    data_u14Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u15Limitation = data_Constraints["u15Limitation"];
    data_u15Limitation["subType"]   = "BARRIER_LOG";
    data_u15Limitation["epsilon"]   = epsi_ctrl;
    data_u15Limitation["tolerance"] = tol_ctrl;
    data_u15Limitation["min"]       = -10;
    data_u15Limitation["max"]       = 10;
    data_u15Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u16Limitation = data_Constraints["u16Limitation"];
    data_u16Limitation["subType"]   = "BARRIER_LOG";
    data_u16Limitation["epsilon"]   = epsi_ctrl;
    data_u16Limitation["tolerance"] = tol_ctrl;
    data_u16Limitation["min"]       = -10;
    data_u16Limitation["max"]       = 10;
    data_u16Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u17Limitation = data_Constraints["u17Limitation"];
    data_u17Limitation["subType"]   = "BARRIER_LOG";
    data_u17Limitation["epsilon"]   = epsi_ctrl;
    data_u17Limitation["tolerance"] = tol_ctrl;
    data_u17Limitation["min"]       = -10;
    data_u17Limitation["max"]       = 10;
    data_u17Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u18Limitation = data_Constraints["u18Limitation"];
    data_u18Limitation["subType"]   = "BARRIER_LOG";
    data_u18Limitation["epsilon"]   = epsi_ctrl;
    data_u18Limitation["tolerance"] = tol_ctrl;
    data_u18Limitation["min"]       = -10;
    data_u18Limitation["max"]       = 10;
    data_u18Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u19Limitation = data_Constraints["u19Limitation"];
    data_u19Limitation["subType"]   = "BARRIER_LOG";
    data_u19Limitation["epsilon"]   = epsi_ctrl;
    data_u19Limitation["tolerance"] = tol_ctrl;
    data_u19Limitation["min"]       = -10;
    data_u19Limitation["max"]       = 10;
    data_u19Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_u20Limitation = data_Constraints["u20Limitation"];
    data_u20Limitation["subType"]   = "BARRIER_LOG";
    data_u20Limitation["epsilon"]   = epsi_ctrl;
    data_u20Limitation["tolerance"] = tol_ctrl;
    data_u20Limitation["min"]       = -10;
    data_u20Limitation["max"]       = 10;
    data_u20Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx1Limitation = data_Constraints["xx1Limitation"];
    data_xx1Limitation["subType"]   = "BARRIER_LOG";
    data_xx1Limitation["epsilon"]   = xy_eps;
    data_xx1Limitation["tolerance"] = xy_tol;
    data_xx1Limitation["min"]       = -xy_bound;
    data_xx1Limitation["max"]       = xy_bound;
    data_xx1Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy1Limitation = data_Constraints["yy1Limitation"];
    data_yy1Limitation["subType"]   = "BARRIER_LOG";
    data_yy1Limitation["epsilon"]   = xy_eps;
    data_yy1Limitation["tolerance"] = xy_tol;
    data_yy1Limitation["min"]       = -xy_bound;
    data_yy1Limitation["max"]       = xy_bound;
    data_yy1Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx2Limitation = data_Constraints["xx2Limitation"];
    data_xx2Limitation["subType"]   = "BARRIER_LOG";
    data_xx2Limitation["epsilon"]   = xy_eps;
    data_xx2Limitation["tolerance"] = xy_tol;
    data_xx2Limitation["min"]       = -xy_bound;
    data_xx2Limitation["max"]       = xy_bound;
    data_xx2Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy2Limitation = data_Constraints["yy2Limitation"];
    data_yy2Limitation["subType"]   = "BARRIER_LOG";
    data_yy2Limitation["epsilon"]   = xy_eps;
    data_yy2Limitation["tolerance"] = xy_tol;
    data_yy2Limitation["min"]       = -xy_bound;
    data_yy2Limitation["max"]       = xy_bound;
    data_yy2Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx3Limitation = data_Constraints["xx3Limitation"];
    data_xx3Limitation["subType"]   = "BARRIER_LOG";
    data_xx3Limitation["epsilon"]   = xy_eps;
    data_xx3Limitation["tolerance"] = xy_tol;
    data_xx3Limitation["min"]       = -xy_bound;
    data_xx3Limitation["max"]       = xy_bound;
    data_xx3Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy3Limitation = data_Constraints["yy3Limitation"];
    data_yy3Limitation["subType"]   = "BARRIER_LOG";
    data_yy3Limitation["epsilon"]   = xy_eps;
    data_yy3Limitation["tolerance"] = xy_tol;
    data_yy3Limitation["min"]       = -xy_bound;
    data_yy3Limitation["max"]       = xy_bound;
    data_yy3Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx4Limitation = data_Constraints["xx4Limitation"];
    data_xx4Limitation["subType"]   = "BARRIER_LOG";
    data_xx4Limitation["epsilon"]   = xy_eps;
    data_xx4Limitation["tolerance"] = xy_tol;
    data_xx4Limitation["min"]       = -xy_bound;
    data_xx4Limitation["max"]       = xy_bound;
    data_xx4Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy4Limitation = data_Constraints["yy4Limitation"];
    data_yy4Limitation["subType"]   = "BARRIER_LOG";
    data_yy4Limitation["epsilon"]   = xy_eps;
    data_yy4Limitation["tolerance"] = xy_tol;
    data_yy4Limitation["min"]       = -xy_bound;
    data_yy4Limitation["max"]       = xy_bound;
    data_yy4Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx5Limitation = data_Constraints["xx5Limitation"];
    data_xx5Limitation["subType"]   = "BARRIER_LOG";
    data_xx5Limitation["epsilon"]   = xy_eps;
    data_xx5Limitation["tolerance"] = xy_tol;
    data_xx5Limitation["min"]       = -xy_bound;
    data_xx5Limitation["max"]       = xy_bound;
    data_xx5Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy5Limitation = data_Constraints["yy5Limitation"];
    data_yy5Limitation["subType"]   = "BARRIER_LOG";
    data_yy5Limitation["epsilon"]   = xy_eps;
    data_yy5Limitation["tolerance"] = xy_tol;
    data_yy5Limitation["min"]       = -xy_bound;
    data_yy5Limitation["max"]       = xy_bound;
    data_yy5Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx6Limitation = data_Constraints["xx6Limitation"];
    data_xx6Limitation["subType"]   = "BARRIER_LOG";
    data_xx6Limitation["epsilon"]   = xy_eps;
    data_xx6Limitation["tolerance"] = xy_tol;
    data_xx6Limitation["min"]       = -xy_bound;
    data_xx6Limitation["max"]       = xy_bound;
    data_xx6Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy6Limitation = data_Constraints["yy6Limitation"];
    data_yy6Limitation["subType"]   = "BARRIER_LOG";
    data_yy6Limitation["epsilon"]   = xy_eps;
    data_yy6Limitation["tolerance"] = xy_tol;
    data_yy6Limitation["min"]       = -xy_bound;
    data_yy6Limitation["max"]       = xy_bound;
    data_yy6Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx7Limitation = data_Constraints["xx7Limitation"];
    data_xx7Limitation["subType"]   = "BARRIER_LOG";
    data_xx7Limitation["epsilon"]   = xy_eps;
    data_xx7Limitation["tolerance"] = xy_tol;
    data_xx7Limitation["min"]       = -xy_bound;
    data_xx7Limitation["max"]       = xy_bound;
    data_xx7Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy7Limitation = data_Constraints["yy7Limitation"];
    data_yy7Limitation["subType"]   = "BARRIER_LOG";
    data_yy7Limitation["epsilon"]   = xy_eps;
    data_yy7Limitation["tolerance"] = xy_tol;
    data_yy7Limitation["min"]       = -xy_bound;
    data_yy7Limitation["max"]       = xy_bound;
    data_yy7Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx8Limitation = data_Constraints["xx8Limitation"];
    data_xx8Limitation["subType"]   = "BARRIER_LOG";
    data_xx8Limitation["epsilon"]   = xy_eps;
    data_xx8Limitation["tolerance"] = xy_tol;
    data_xx8Limitation["min"]       = -xy_bound;
    data_xx8Limitation["max"]       = xy_bound;
    data_xx8Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy8Limitation = data_Constraints["yy8Limitation"];
    data_yy8Limitation["subType"]   = "BARRIER_LOG";
    data_yy8Limitation["epsilon"]   = xy_eps;
    data_yy8Limitation["tolerance"] = xy_tol;
    data_yy8Limitation["min"]       = -xy_bound;
    data_yy8Limitation["max"]       = xy_bound;
    data_yy8Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx9Limitation = data_Constraints["xx9Limitation"];
    data_xx9Limitation["subType"]   = "BARRIER_LOG";
    data_xx9Limitation["epsilon"]   = xy_eps;
    data_xx9Limitation["tolerance"] = xy_tol;
    data_xx9Limitation["min"]       = -xy_bound;
    data_xx9Limitation["max"]       = xy_bound;
    data_xx9Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy9Limitation = data_Constraints["yy9Limitation"];
    data_yy9Limitation["subType"]   = "BARRIER_LOG";
    data_yy9Limitation["epsilon"]   = xy_eps;
    data_yy9Limitation["tolerance"] = xy_tol;
    data_yy9Limitation["min"]       = -xy_bound;
    data_yy9Limitation["max"]       = xy_bound;
    data_yy9Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx10Limitation = data_Constraints["xx10Limitation"];
    data_xx10Limitation["subType"]   = "BARRIER_LOG";
    data_xx10Limitation["epsilon"]   = xy_eps;
    data_xx10Limitation["tolerance"] = xy_tol;
    data_xx10Limitation["min"]       = -xy_bound;
    data_xx10Limitation["max"]       = xy_bound;
    data_xx10Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy10Limitation = data_Constraints["yy10Limitation"];
    data_yy10Limitation["subType"]   = "BARRIER_LOG";
    data_yy10Limitation["epsilon"]   = xy_eps;
    data_yy10Limitation["tolerance"] = xy_tol;
    data_yy10Limitation["min"]       = -xy_bound;
    data_yy10Limitation["max"]       = xy_bound;
    data_yy10Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx11Limitation = data_Constraints["xx11Limitation"];
    data_xx11Limitation["subType"]   = "BARRIER_LOG";
    data_xx11Limitation["epsilon"]   = xy_eps;
    data_xx11Limitation["tolerance"] = xy_tol;
    data_xx11Limitation["min"]       = -xy_bound;
    data_xx11Limitation["max"]       = xy_bound;
    data_xx11Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy11Limitation = data_Constraints["yy11Limitation"];
    data_yy11Limitation["subType"]   = "BARRIER_LOG";
    data_yy11Limitation["epsilon"]   = xy_eps;
    data_yy11Limitation["tolerance"] = xy_tol;
    data_yy11Limitation["min"]       = -xy_bound;
    data_yy11Limitation["max"]       = xy_bound;
    data_yy11Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx12Limitation = data_Constraints["xx12Limitation"];
    data_xx12Limitation["subType"]   = "BARRIER_LOG";
    data_xx12Limitation["epsilon"]   = xy_eps;
    data_xx12Limitation["tolerance"] = xy_tol;
    data_xx12Limitation["min"]       = -xy_bound;
    data_xx12Limitation["max"]       = xy_bound;
    data_xx12Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy12Limitation = data_Constraints["yy12Limitation"];
    data_yy12Limitation["subType"]   = "BARRIER_LOG";
    data_yy12Limitation["epsilon"]   = xy_eps;
    data_yy12Limitation["tolerance"] = xy_tol;
    data_yy12Limitation["min"]       = -xy_bound;
    data_yy12Limitation["max"]       = xy_bound;
    data_yy12Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx13Limitation = data_Constraints["xx13Limitation"];
    data_xx13Limitation["subType"]   = "BARRIER_LOG";
    data_xx13Limitation["epsilon"]   = xy_eps;
    data_xx13Limitation["tolerance"] = xy_tol;
    data_xx13Limitation["min"]       = -xy_bound;
    data_xx13Limitation["max"]       = xy_bound;
    data_xx13Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy13Limitation = data_Constraints["yy13Limitation"];
    data_yy13Limitation["subType"]   = "BARRIER_LOG";
    data_yy13Limitation["epsilon"]   = xy_eps;
    data_yy13Limitation["tolerance"] = xy_tol;
    data_yy13Limitation["min"]       = -xy_bound;
    data_yy13Limitation["max"]       = xy_bound;
    data_yy13Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx14Limitation = data_Constraints["xx14Limitation"];
    data_xx14Limitation["subType"]   = "BARRIER_LOG";
    data_xx14Limitation["epsilon"]   = xy_eps;
    data_xx14Limitation["tolerance"] = xy_tol;
    data_xx14Limitation["min"]       = -xy_bound;
    data_xx14Limitation["max"]       = xy_bound;
    data_xx14Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy14Limitation = data_Constraints["yy14Limitation"];
    data_yy14Limitation["subType"]   = "BARRIER_LOG";
    data_yy14Limitation["epsilon"]   = xy_eps;
    data_yy14Limitation["tolerance"] = xy_tol;
    data_yy14Limitation["min"]       = -xy_bound;
    data_yy14Limitation["max"]       = xy_bound;
    data_yy14Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx15Limitation = data_Constraints["xx15Limitation"];
    data_xx15Limitation["subType"]   = "BARRIER_LOG";
    data_xx15Limitation["epsilon"]   = xy_eps;
    data_xx15Limitation["tolerance"] = xy_tol;
    data_xx15Limitation["min"]       = -xy_bound;
    data_xx15Limitation["max"]       = xy_bound;
    data_xx15Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy15Limitation = data_Constraints["yy15Limitation"];
    data_yy15Limitation["subType"]   = "BARRIER_LOG";
    data_yy15Limitation["epsilon"]   = xy_eps;
    data_yy15Limitation["tolerance"] = xy_tol;
    data_yy15Limitation["min"]       = -xy_bound;
    data_yy15Limitation["max"]       = xy_bound;
    data_yy15Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx16Limitation = data_Constraints["xx16Limitation"];
    data_xx16Limitation["subType"]   = "BARRIER_LOG";
    data_xx16Limitation["epsilon"]   = xy_eps;
    data_xx16Limitation["tolerance"] = xy_tol;
    data_xx16Limitation["min"]       = -xy_bound;
    data_xx16Limitation["max"]       = xy_bound;
    data_xx16Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy16Limitation = data_Constraints["yy16Limitation"];
    data_yy16Limitation["subType"]   = "BARRIER_LOG";
    data_yy16Limitation["epsilon"]   = xy_eps;
    data_yy16Limitation["tolerance"] = xy_tol;
    data_yy16Limitation["min"]       = -xy_bound;
    data_yy16Limitation["max"]       = xy_bound;
    data_yy16Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx17Limitation = data_Constraints["xx17Limitation"];
    data_xx17Limitation["subType"]   = "BARRIER_LOG";
    data_xx17Limitation["epsilon"]   = xy_eps;
    data_xx17Limitation["tolerance"] = xy_tol;
    data_xx17Limitation["min"]       = -xy_bound;
    data_xx17Limitation["max"]       = xy_bound;
    data_xx17Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy17Limitation = data_Constraints["yy17Limitation"];
    data_yy17Limitation["subType"]   = "BARRIER_LOG";
    data_yy17Limitation["epsilon"]   = xy_eps;
    data_yy17Limitation["tolerance"] = xy_tol;
    data_yy17Limitation["min"]       = -xy_bound;
    data_yy17Limitation["max"]       = xy_bound;
    data_yy17Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx18Limitation = data_Constraints["xx18Limitation"];
    data_xx18Limitation["subType"]   = "BARRIER_LOG";
    data_xx18Limitation["epsilon"]   = xy_eps;
    data_xx18Limitation["tolerance"] = xy_tol;
    data_xx18Limitation["min"]       = -xy_bound;
    data_xx18Limitation["max"]       = xy_bound;
    data_xx18Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy18Limitation = data_Constraints["yy18Limitation"];
    data_yy18Limitation["subType"]   = "BARRIER_LOG";
    data_yy18Limitation["epsilon"]   = xy_eps;
    data_yy18Limitation["tolerance"] = xy_tol;
    data_yy18Limitation["min"]       = -xy_bound;
    data_yy18Limitation["max"]       = xy_bound;
    data_yy18Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx19Limitation = data_Constraints["xx19Limitation"];
    data_xx19Limitation["subType"]   = "BARRIER_LOG";
    data_xx19Limitation["epsilon"]   = xy_eps;
    data_xx19Limitation["tolerance"] = xy_tol;
    data_xx19Limitation["min"]       = -xy_bound;
    data_xx19Limitation["max"]       = xy_bound;
    data_xx19Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy19Limitation = data_Constraints["yy19Limitation"];
    data_yy19Limitation["subType"]   = "BARRIER_LOG";
    data_yy19Limitation["epsilon"]   = xy_eps;
    data_yy19Limitation["tolerance"] = xy_tol;
    data_yy19Limitation["min"]       = -xy_bound;
    data_yy19Limitation["max"]       = xy_bound;
    data_yy19Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_xx20Limitation = data_Constraints["xx20Limitation"];
    data_xx20Limitation["subType"]   = "BARRIER_LOG";
    data_xx20Limitation["epsilon"]   = xy_eps;
    data_xx20Limitation["tolerance"] = xy_tol;
    data_xx20Limitation["min"]       = -xy_bound;
    data_xx20Limitation["max"]       = xy_bound;
    data_xx20Limitation["active"]    = true;
    // PenaltyBarrier1DInterval
    GenericContainer & data_yy20Limitation = data_Constraints["yy20Limitation"];
    data_yy20Limitation["subType"]   = "BARRIER_LOG";
    data_yy20Limitation["epsilon"]   = xy_eps;
    data_yy20Limitation["tolerance"] = xy_tol;
    data_yy20Limitation["min"]       = -xy_bound;
    data_yy20Limitation["max"]       = xy_bound;
    data_yy20Limitation["active"]    = true;
    // Constraint2D: none defined

    // User defined classes initialization
    // User defined classes: M E S H
ICLOCS_ContinuousMP_data.Mesh["s0"] = 0;
ICLOCS_ContinuousMP_data.Mesh["segments"][0]["n"] = 50;
ICLOCS_ContinuousMP_data.Mesh["segments"][0]["length"] = 1;


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
      file.open( "data/ICLOCS_ContinuousMP_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/ICLOCS_ContinuousMP_OCP_result_NOT_CONVERGED.txt" );
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
