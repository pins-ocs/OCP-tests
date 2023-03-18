/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Main.cc                                    |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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

  Mechatronix::Console     console(&std::cout,4);
  Mechatronix::ThreadPool1 TP(std::thread::hardware_concurrency());

  try {

    ICLOCS_ContinuousMP model("ICLOCS_ContinuousMP",&console,&TP);
    GenericContainer gc_data;
    GenericContainer gc_solution;

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    // Auxiliary values
    real_type epsi_ctrl = 0.01;
    real_type xy_tol0 = 0.1;
    real_type xy_tol = xy_tol0;
    real_type tol_ctrl = 0.01;
    real_type xy_eps0 = 0.1;
    real_type xy_eps = xy_eps0;
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
    data_Solver["ns_continuation_begin"] = 1;
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
    data_Parameters["xy_bound"] = 2;

    // User Function Parameters

    // Continuation Parameters
    data_Parameters["xy_eps0"] = xy_eps0;
    data_Parameters["xy_eps1"] = 0.001;
    data_Parameters["xy_tol0"] = xy_tol0;
    data_Parameters["xy_tol1"] = 0.001;

    // Constraints Parameters

    // functions mapped on objects

    // Controls: No penalties or barriers constraint defined

    // ConstraintLT
    // Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
    // Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    GenericContainer & data_Constraints = gc_data["Constraints"];
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u1Limitation_min = data_Constraints["u1Limitation_min"];
    data_u1Limitation_min["subType"]   = "BARRIER_LOG";
    data_u1Limitation_min["epsilon"]   = epsi_ctrl;
    data_u1Limitation_min["tolerance"] = tol_ctrl;
    data_u1Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u1Limitation_max = data_Constraints["u1Limitation_max"];
    data_u1Limitation_max["subType"]   = "BARRIER_LOG";
    data_u1Limitation_max["epsilon"]   = epsi_ctrl;
    data_u1Limitation_max["tolerance"] = tol_ctrl;
    data_u1Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u2Limitation_min = data_Constraints["u2Limitation_min"];
    data_u2Limitation_min["subType"]   = "BARRIER_LOG";
    data_u2Limitation_min["epsilon"]   = epsi_ctrl;
    data_u2Limitation_min["tolerance"] = tol_ctrl;
    data_u2Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u2Limitation_max = data_Constraints["u2Limitation_max"];
    data_u2Limitation_max["subType"]   = "BARRIER_LOG";
    data_u2Limitation_max["epsilon"]   = epsi_ctrl;
    data_u2Limitation_max["tolerance"] = tol_ctrl;
    data_u2Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u3Limitation_min = data_Constraints["u3Limitation_min"];
    data_u3Limitation_min["subType"]   = "BARRIER_LOG";
    data_u3Limitation_min["epsilon"]   = epsi_ctrl;
    data_u3Limitation_min["tolerance"] = tol_ctrl;
    data_u3Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u3Limitation_max = data_Constraints["u3Limitation_max"];
    data_u3Limitation_max["subType"]   = "BARRIER_LOG";
    data_u3Limitation_max["epsilon"]   = epsi_ctrl;
    data_u3Limitation_max["tolerance"] = tol_ctrl;
    data_u3Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u4Limitation_min = data_Constraints["u4Limitation_min"];
    data_u4Limitation_min["subType"]   = "BARRIER_LOG";
    data_u4Limitation_min["epsilon"]   = epsi_ctrl;
    data_u4Limitation_min["tolerance"] = tol_ctrl;
    data_u4Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u4Limitation_max = data_Constraints["u4Limitation_max"];
    data_u4Limitation_max["subType"]   = "BARRIER_LOG";
    data_u4Limitation_max["epsilon"]   = epsi_ctrl;
    data_u4Limitation_max["tolerance"] = tol_ctrl;
    data_u4Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u5Limitation_min = data_Constraints["u5Limitation_min"];
    data_u5Limitation_min["subType"]   = "BARRIER_LOG";
    data_u5Limitation_min["epsilon"]   = epsi_ctrl;
    data_u5Limitation_min["tolerance"] = tol_ctrl;
    data_u5Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u5Limitation_max = data_Constraints["u5Limitation_max"];
    data_u5Limitation_max["subType"]   = "BARRIER_LOG";
    data_u5Limitation_max["epsilon"]   = epsi_ctrl;
    data_u5Limitation_max["tolerance"] = tol_ctrl;
    data_u5Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u6Limitation_min = data_Constraints["u6Limitation_min"];
    data_u6Limitation_min["subType"]   = "BARRIER_LOG";
    data_u6Limitation_min["epsilon"]   = epsi_ctrl;
    data_u6Limitation_min["tolerance"] = tol_ctrl;
    data_u6Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u6Limitation_max = data_Constraints["u6Limitation_max"];
    data_u6Limitation_max["subType"]   = "BARRIER_LOG";
    data_u6Limitation_max["epsilon"]   = epsi_ctrl;
    data_u6Limitation_max["tolerance"] = tol_ctrl;
    data_u6Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u7Limitation_min = data_Constraints["u7Limitation_min"];
    data_u7Limitation_min["subType"]   = "BARRIER_LOG";
    data_u7Limitation_min["epsilon"]   = epsi_ctrl;
    data_u7Limitation_min["tolerance"] = tol_ctrl;
    data_u7Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u7Limitation_max = data_Constraints["u7Limitation_max"];
    data_u7Limitation_max["subType"]   = "BARRIER_LOG";
    data_u7Limitation_max["epsilon"]   = epsi_ctrl;
    data_u7Limitation_max["tolerance"] = tol_ctrl;
    data_u7Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u8Limitation_min = data_Constraints["u8Limitation_min"];
    data_u8Limitation_min["subType"]   = "BARRIER_LOG";
    data_u8Limitation_min["epsilon"]   = epsi_ctrl;
    data_u8Limitation_min["tolerance"] = tol_ctrl;
    data_u8Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u8Limitation_max = data_Constraints["u8Limitation_max"];
    data_u8Limitation_max["subType"]   = "BARRIER_LOG";
    data_u8Limitation_max["epsilon"]   = epsi_ctrl;
    data_u8Limitation_max["tolerance"] = tol_ctrl;
    data_u8Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u9Limitation_min = data_Constraints["u9Limitation_min"];
    data_u9Limitation_min["subType"]   = "BARRIER_LOG";
    data_u9Limitation_min["epsilon"]   = epsi_ctrl;
    data_u9Limitation_min["tolerance"] = tol_ctrl;
    data_u9Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u9Limitation_max = data_Constraints["u9Limitation_max"];
    data_u9Limitation_max["subType"]   = "BARRIER_LOG";
    data_u9Limitation_max["epsilon"]   = epsi_ctrl;
    data_u9Limitation_max["tolerance"] = tol_ctrl;
    data_u9Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u10Limitation_min = data_Constraints["u10Limitation_min"];
    data_u10Limitation_min["subType"]   = "BARRIER_LOG";
    data_u10Limitation_min["epsilon"]   = epsi_ctrl;
    data_u10Limitation_min["tolerance"] = tol_ctrl;
    data_u10Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u10Limitation_max = data_Constraints["u10Limitation_max"];
    data_u10Limitation_max["subType"]   = "BARRIER_LOG";
    data_u10Limitation_max["epsilon"]   = epsi_ctrl;
    data_u10Limitation_max["tolerance"] = tol_ctrl;
    data_u10Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u11Limitation_min = data_Constraints["u11Limitation_min"];
    data_u11Limitation_min["subType"]   = "BARRIER_LOG";
    data_u11Limitation_min["epsilon"]   = epsi_ctrl;
    data_u11Limitation_min["tolerance"] = tol_ctrl;
    data_u11Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u11Limitation_max = data_Constraints["u11Limitation_max"];
    data_u11Limitation_max["subType"]   = "BARRIER_LOG";
    data_u11Limitation_max["epsilon"]   = epsi_ctrl;
    data_u11Limitation_max["tolerance"] = tol_ctrl;
    data_u11Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u12Limitation_min = data_Constraints["u12Limitation_min"];
    data_u12Limitation_min["subType"]   = "BARRIER_LOG";
    data_u12Limitation_min["epsilon"]   = epsi_ctrl;
    data_u12Limitation_min["tolerance"] = tol_ctrl;
    data_u12Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u12Limitation_max = data_Constraints["u12Limitation_max"];
    data_u12Limitation_max["subType"]   = "BARRIER_LOG";
    data_u12Limitation_max["epsilon"]   = epsi_ctrl;
    data_u12Limitation_max["tolerance"] = tol_ctrl;
    data_u12Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u13Limitation_min = data_Constraints["u13Limitation_min"];
    data_u13Limitation_min["subType"]   = "BARRIER_LOG";
    data_u13Limitation_min["epsilon"]   = epsi_ctrl;
    data_u13Limitation_min["tolerance"] = tol_ctrl;
    data_u13Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u13Limitation_max = data_Constraints["u13Limitation_max"];
    data_u13Limitation_max["subType"]   = "BARRIER_LOG";
    data_u13Limitation_max["epsilon"]   = epsi_ctrl;
    data_u13Limitation_max["tolerance"] = tol_ctrl;
    data_u13Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u14Limitation_min = data_Constraints["u14Limitation_min"];
    data_u14Limitation_min["subType"]   = "BARRIER_LOG";
    data_u14Limitation_min["epsilon"]   = epsi_ctrl;
    data_u14Limitation_min["tolerance"] = tol_ctrl;
    data_u14Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u14Limitation_max = data_Constraints["u14Limitation_max"];
    data_u14Limitation_max["subType"]   = "BARRIER_LOG";
    data_u14Limitation_max["epsilon"]   = epsi_ctrl;
    data_u14Limitation_max["tolerance"] = tol_ctrl;
    data_u14Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u15Limitation_min = data_Constraints["u15Limitation_min"];
    data_u15Limitation_min["subType"]   = "BARRIER_LOG";
    data_u15Limitation_min["epsilon"]   = epsi_ctrl;
    data_u15Limitation_min["tolerance"] = tol_ctrl;
    data_u15Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u15Limitation_max = data_Constraints["u15Limitation_max"];
    data_u15Limitation_max["subType"]   = "BARRIER_LOG";
    data_u15Limitation_max["epsilon"]   = epsi_ctrl;
    data_u15Limitation_max["tolerance"] = tol_ctrl;
    data_u15Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u16Limitation_min = data_Constraints["u16Limitation_min"];
    data_u16Limitation_min["subType"]   = "BARRIER_LOG";
    data_u16Limitation_min["epsilon"]   = epsi_ctrl;
    data_u16Limitation_min["tolerance"] = tol_ctrl;
    data_u16Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u16Limitation_max = data_Constraints["u16Limitation_max"];
    data_u16Limitation_max["subType"]   = "BARRIER_LOG";
    data_u16Limitation_max["epsilon"]   = epsi_ctrl;
    data_u16Limitation_max["tolerance"] = tol_ctrl;
    data_u16Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u17Limitation_min = data_Constraints["u17Limitation_min"];
    data_u17Limitation_min["subType"]   = "BARRIER_LOG";
    data_u17Limitation_min["epsilon"]   = epsi_ctrl;
    data_u17Limitation_min["tolerance"] = tol_ctrl;
    data_u17Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u17Limitation_max = data_Constraints["u17Limitation_max"];
    data_u17Limitation_max["subType"]   = "BARRIER_LOG";
    data_u17Limitation_max["epsilon"]   = epsi_ctrl;
    data_u17Limitation_max["tolerance"] = tol_ctrl;
    data_u17Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u18Limitation_min = data_Constraints["u18Limitation_min"];
    data_u18Limitation_min["subType"]   = "BARRIER_LOG";
    data_u18Limitation_min["epsilon"]   = epsi_ctrl;
    data_u18Limitation_min["tolerance"] = tol_ctrl;
    data_u18Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u18Limitation_max = data_Constraints["u18Limitation_max"];
    data_u18Limitation_max["subType"]   = "BARRIER_LOG";
    data_u18Limitation_max["epsilon"]   = epsi_ctrl;
    data_u18Limitation_max["tolerance"] = tol_ctrl;
    data_u18Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u19Limitation_min = data_Constraints["u19Limitation_min"];
    data_u19Limitation_min["subType"]   = "BARRIER_LOG";
    data_u19Limitation_min["epsilon"]   = epsi_ctrl;
    data_u19Limitation_min["tolerance"] = tol_ctrl;
    data_u19Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u19Limitation_max = data_Constraints["u19Limitation_max"];
    data_u19Limitation_max["subType"]   = "BARRIER_LOG";
    data_u19Limitation_max["epsilon"]   = epsi_ctrl;
    data_u19Limitation_max["tolerance"] = tol_ctrl;
    data_u19Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u20Limitation_min = data_Constraints["u20Limitation_min"];
    data_u20Limitation_min["subType"]   = "BARRIER_LOG";
    data_u20Limitation_min["epsilon"]   = epsi_ctrl;
    data_u20Limitation_min["tolerance"] = tol_ctrl;
    data_u20Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_u20Limitation_max = data_Constraints["u20Limitation_max"];
    data_u20Limitation_max["subType"]   = "BARRIER_LOG";
    data_u20Limitation_max["epsilon"]   = epsi_ctrl;
    data_u20Limitation_max["tolerance"] = tol_ctrl;
    data_u20Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx1Limitation_min = data_Constraints["xx1Limitation_min"];
    data_xx1Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx1Limitation_min["epsilon"]   = xy_eps;
    data_xx1Limitation_min["tolerance"] = xy_tol;
    data_xx1Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx1Limitation_max = data_Constraints["xx1Limitation_max"];
    data_xx1Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx1Limitation_max["epsilon"]   = xy_eps;
    data_xx1Limitation_max["tolerance"] = xy_tol;
    data_xx1Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy1Limitation_min = data_Constraints["yy1Limitation_min"];
    data_yy1Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy1Limitation_min["epsilon"]   = xy_eps;
    data_yy1Limitation_min["tolerance"] = xy_tol;
    data_yy1Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy1Limitation_max = data_Constraints["yy1Limitation_max"];
    data_yy1Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy1Limitation_max["epsilon"]   = xy_eps;
    data_yy1Limitation_max["tolerance"] = xy_tol;
    data_yy1Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx2Limitation_min = data_Constraints["xx2Limitation_min"];
    data_xx2Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx2Limitation_min["epsilon"]   = xy_eps;
    data_xx2Limitation_min["tolerance"] = xy_tol;
    data_xx2Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx2Limitation_max = data_Constraints["xx2Limitation_max"];
    data_xx2Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx2Limitation_max["epsilon"]   = xy_eps;
    data_xx2Limitation_max["tolerance"] = xy_tol;
    data_xx2Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy2Limitation_min = data_Constraints["yy2Limitation_min"];
    data_yy2Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy2Limitation_min["epsilon"]   = xy_eps;
    data_yy2Limitation_min["tolerance"] = xy_tol;
    data_yy2Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy2Limitation_max = data_Constraints["yy2Limitation_max"];
    data_yy2Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy2Limitation_max["epsilon"]   = xy_eps;
    data_yy2Limitation_max["tolerance"] = xy_tol;
    data_yy2Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx3Limitation_min = data_Constraints["xx3Limitation_min"];
    data_xx3Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx3Limitation_min["epsilon"]   = xy_eps;
    data_xx3Limitation_min["tolerance"] = xy_tol;
    data_xx3Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx3Limitation_max = data_Constraints["xx3Limitation_max"];
    data_xx3Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx3Limitation_max["epsilon"]   = xy_eps;
    data_xx3Limitation_max["tolerance"] = xy_tol;
    data_xx3Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy3Limitation_min = data_Constraints["yy3Limitation_min"];
    data_yy3Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy3Limitation_min["epsilon"]   = xy_eps;
    data_yy3Limitation_min["tolerance"] = xy_tol;
    data_yy3Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy3Limitation_max = data_Constraints["yy3Limitation_max"];
    data_yy3Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy3Limitation_max["epsilon"]   = xy_eps;
    data_yy3Limitation_max["tolerance"] = xy_tol;
    data_yy3Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx4Limitation_min = data_Constraints["xx4Limitation_min"];
    data_xx4Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx4Limitation_min["epsilon"]   = xy_eps;
    data_xx4Limitation_min["tolerance"] = xy_tol;
    data_xx4Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx4Limitation_max = data_Constraints["xx4Limitation_max"];
    data_xx4Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx4Limitation_max["epsilon"]   = xy_eps;
    data_xx4Limitation_max["tolerance"] = xy_tol;
    data_xx4Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy4Limitation_min = data_Constraints["yy4Limitation_min"];
    data_yy4Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy4Limitation_min["epsilon"]   = xy_eps;
    data_yy4Limitation_min["tolerance"] = xy_tol;
    data_yy4Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy4Limitation_max = data_Constraints["yy4Limitation_max"];
    data_yy4Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy4Limitation_max["epsilon"]   = xy_eps;
    data_yy4Limitation_max["tolerance"] = xy_tol;
    data_yy4Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx5Limitation_min = data_Constraints["xx5Limitation_min"];
    data_xx5Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx5Limitation_min["epsilon"]   = xy_eps;
    data_xx5Limitation_min["tolerance"] = xy_tol;
    data_xx5Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx5Limitation_max = data_Constraints["xx5Limitation_max"];
    data_xx5Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx5Limitation_max["epsilon"]   = xy_eps;
    data_xx5Limitation_max["tolerance"] = xy_tol;
    data_xx5Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy5Limitation_min = data_Constraints["yy5Limitation_min"];
    data_yy5Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy5Limitation_min["epsilon"]   = xy_eps;
    data_yy5Limitation_min["tolerance"] = xy_tol;
    data_yy5Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy5Limitation_max = data_Constraints["yy5Limitation_max"];
    data_yy5Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy5Limitation_max["epsilon"]   = xy_eps;
    data_yy5Limitation_max["tolerance"] = xy_tol;
    data_yy5Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx6Limitation_min = data_Constraints["xx6Limitation_min"];
    data_xx6Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx6Limitation_min["epsilon"]   = xy_eps;
    data_xx6Limitation_min["tolerance"] = xy_tol;
    data_xx6Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx6Limitation_max = data_Constraints["xx6Limitation_max"];
    data_xx6Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx6Limitation_max["epsilon"]   = xy_eps;
    data_xx6Limitation_max["tolerance"] = xy_tol;
    data_xx6Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy6Limitation_min = data_Constraints["yy6Limitation_min"];
    data_yy6Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy6Limitation_min["epsilon"]   = xy_eps;
    data_yy6Limitation_min["tolerance"] = xy_tol;
    data_yy6Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy6Limitation_max = data_Constraints["yy6Limitation_max"];
    data_yy6Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy6Limitation_max["epsilon"]   = xy_eps;
    data_yy6Limitation_max["tolerance"] = xy_tol;
    data_yy6Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx7Limitation_min = data_Constraints["xx7Limitation_min"];
    data_xx7Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx7Limitation_min["epsilon"]   = xy_eps;
    data_xx7Limitation_min["tolerance"] = xy_tol;
    data_xx7Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx7Limitation_max = data_Constraints["xx7Limitation_max"];
    data_xx7Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx7Limitation_max["epsilon"]   = xy_eps;
    data_xx7Limitation_max["tolerance"] = xy_tol;
    data_xx7Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy7Limitation_min = data_Constraints["yy7Limitation_min"];
    data_yy7Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy7Limitation_min["epsilon"]   = xy_eps;
    data_yy7Limitation_min["tolerance"] = xy_tol;
    data_yy7Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy7Limitation_max = data_Constraints["yy7Limitation_max"];
    data_yy7Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy7Limitation_max["epsilon"]   = xy_eps;
    data_yy7Limitation_max["tolerance"] = xy_tol;
    data_yy7Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx8Limitation_min = data_Constraints["xx8Limitation_min"];
    data_xx8Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx8Limitation_min["epsilon"]   = xy_eps;
    data_xx8Limitation_min["tolerance"] = xy_tol;
    data_xx8Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx8Limitation_max = data_Constraints["xx8Limitation_max"];
    data_xx8Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx8Limitation_max["epsilon"]   = xy_eps;
    data_xx8Limitation_max["tolerance"] = xy_tol;
    data_xx8Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy8Limitation_min = data_Constraints["yy8Limitation_min"];
    data_yy8Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy8Limitation_min["epsilon"]   = xy_eps;
    data_yy8Limitation_min["tolerance"] = xy_tol;
    data_yy8Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy8Limitation_max = data_Constraints["yy8Limitation_max"];
    data_yy8Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy8Limitation_max["epsilon"]   = xy_eps;
    data_yy8Limitation_max["tolerance"] = xy_tol;
    data_yy8Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx9Limitation_min = data_Constraints["xx9Limitation_min"];
    data_xx9Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx9Limitation_min["epsilon"]   = xy_eps;
    data_xx9Limitation_min["tolerance"] = xy_tol;
    data_xx9Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx9Limitation_max = data_Constraints["xx9Limitation_max"];
    data_xx9Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx9Limitation_max["epsilon"]   = xy_eps;
    data_xx9Limitation_max["tolerance"] = xy_tol;
    data_xx9Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy9Limitation_min = data_Constraints["yy9Limitation_min"];
    data_yy9Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy9Limitation_min["epsilon"]   = xy_eps;
    data_yy9Limitation_min["tolerance"] = xy_tol;
    data_yy9Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy9Limitation_max = data_Constraints["yy9Limitation_max"];
    data_yy9Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy9Limitation_max["epsilon"]   = xy_eps;
    data_yy9Limitation_max["tolerance"] = xy_tol;
    data_yy9Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx10Limitation_min = data_Constraints["xx10Limitation_min"];
    data_xx10Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx10Limitation_min["epsilon"]   = xy_eps;
    data_xx10Limitation_min["tolerance"] = xy_tol;
    data_xx10Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx10Limitation_max = data_Constraints["xx10Limitation_max"];
    data_xx10Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx10Limitation_max["epsilon"]   = xy_eps;
    data_xx10Limitation_max["tolerance"] = xy_tol;
    data_xx10Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy10Limitation_min = data_Constraints["yy10Limitation_min"];
    data_yy10Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy10Limitation_min["epsilon"]   = xy_eps;
    data_yy10Limitation_min["tolerance"] = xy_tol;
    data_yy10Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy10Limitation_max = data_Constraints["yy10Limitation_max"];
    data_yy10Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy10Limitation_max["epsilon"]   = xy_eps;
    data_yy10Limitation_max["tolerance"] = xy_tol;
    data_yy10Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx11Limitation_min = data_Constraints["xx11Limitation_min"];
    data_xx11Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx11Limitation_min["epsilon"]   = xy_eps;
    data_xx11Limitation_min["tolerance"] = xy_tol;
    data_xx11Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx11Limitation_max = data_Constraints["xx11Limitation_max"];
    data_xx11Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx11Limitation_max["epsilon"]   = xy_eps;
    data_xx11Limitation_max["tolerance"] = xy_tol;
    data_xx11Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy11Limitation_min = data_Constraints["yy11Limitation_min"];
    data_yy11Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy11Limitation_min["epsilon"]   = xy_eps;
    data_yy11Limitation_min["tolerance"] = xy_tol;
    data_yy11Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy11Limitation_max = data_Constraints["yy11Limitation_max"];
    data_yy11Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy11Limitation_max["epsilon"]   = xy_eps;
    data_yy11Limitation_max["tolerance"] = xy_tol;
    data_yy11Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx12Limitation_min = data_Constraints["xx12Limitation_min"];
    data_xx12Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx12Limitation_min["epsilon"]   = xy_eps;
    data_xx12Limitation_min["tolerance"] = xy_tol;
    data_xx12Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx12Limitation_max = data_Constraints["xx12Limitation_max"];
    data_xx12Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx12Limitation_max["epsilon"]   = xy_eps;
    data_xx12Limitation_max["tolerance"] = xy_tol;
    data_xx12Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy12Limitation_min = data_Constraints["yy12Limitation_min"];
    data_yy12Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy12Limitation_min["epsilon"]   = xy_eps;
    data_yy12Limitation_min["tolerance"] = xy_tol;
    data_yy12Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy12Limitation_max = data_Constraints["yy12Limitation_max"];
    data_yy12Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy12Limitation_max["epsilon"]   = xy_eps;
    data_yy12Limitation_max["tolerance"] = xy_tol;
    data_yy12Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx13Limitation_min = data_Constraints["xx13Limitation_min"];
    data_xx13Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx13Limitation_min["epsilon"]   = xy_eps;
    data_xx13Limitation_min["tolerance"] = xy_tol;
    data_xx13Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx13Limitation_max = data_Constraints["xx13Limitation_max"];
    data_xx13Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx13Limitation_max["epsilon"]   = xy_eps;
    data_xx13Limitation_max["tolerance"] = xy_tol;
    data_xx13Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy13Limitation_min = data_Constraints["yy13Limitation_min"];
    data_yy13Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy13Limitation_min["epsilon"]   = xy_eps;
    data_yy13Limitation_min["tolerance"] = xy_tol;
    data_yy13Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy13Limitation_max = data_Constraints["yy13Limitation_max"];
    data_yy13Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy13Limitation_max["epsilon"]   = xy_eps;
    data_yy13Limitation_max["tolerance"] = xy_tol;
    data_yy13Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx14Limitation_min = data_Constraints["xx14Limitation_min"];
    data_xx14Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx14Limitation_min["epsilon"]   = xy_eps;
    data_xx14Limitation_min["tolerance"] = xy_tol;
    data_xx14Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx14Limitation_max = data_Constraints["xx14Limitation_max"];
    data_xx14Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx14Limitation_max["epsilon"]   = xy_eps;
    data_xx14Limitation_max["tolerance"] = xy_tol;
    data_xx14Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy14Limitation_min = data_Constraints["yy14Limitation_min"];
    data_yy14Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy14Limitation_min["epsilon"]   = xy_eps;
    data_yy14Limitation_min["tolerance"] = xy_tol;
    data_yy14Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy14Limitation_max = data_Constraints["yy14Limitation_max"];
    data_yy14Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy14Limitation_max["epsilon"]   = xy_eps;
    data_yy14Limitation_max["tolerance"] = xy_tol;
    data_yy14Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx15Limitation_min = data_Constraints["xx15Limitation_min"];
    data_xx15Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx15Limitation_min["epsilon"]   = xy_eps;
    data_xx15Limitation_min["tolerance"] = xy_tol;
    data_xx15Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx15Limitation_max = data_Constraints["xx15Limitation_max"];
    data_xx15Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx15Limitation_max["epsilon"]   = xy_eps;
    data_xx15Limitation_max["tolerance"] = xy_tol;
    data_xx15Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy15Limitation_min = data_Constraints["yy15Limitation_min"];
    data_yy15Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy15Limitation_min["epsilon"]   = xy_eps;
    data_yy15Limitation_min["tolerance"] = xy_tol;
    data_yy15Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy15Limitation_max = data_Constraints["yy15Limitation_max"];
    data_yy15Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy15Limitation_max["epsilon"]   = xy_eps;
    data_yy15Limitation_max["tolerance"] = xy_tol;
    data_yy15Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx16Limitation_min = data_Constraints["xx16Limitation_min"];
    data_xx16Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx16Limitation_min["epsilon"]   = xy_eps;
    data_xx16Limitation_min["tolerance"] = xy_tol;
    data_xx16Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx16Limitation_max = data_Constraints["xx16Limitation_max"];
    data_xx16Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx16Limitation_max["epsilon"]   = xy_eps;
    data_xx16Limitation_max["tolerance"] = xy_tol;
    data_xx16Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy16Limitation_min = data_Constraints["yy16Limitation_min"];
    data_yy16Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy16Limitation_min["epsilon"]   = xy_eps;
    data_yy16Limitation_min["tolerance"] = xy_tol;
    data_yy16Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy16Limitation_max = data_Constraints["yy16Limitation_max"];
    data_yy16Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy16Limitation_max["epsilon"]   = xy_eps;
    data_yy16Limitation_max["tolerance"] = xy_tol;
    data_yy16Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx17Limitation_min = data_Constraints["xx17Limitation_min"];
    data_xx17Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx17Limitation_min["epsilon"]   = xy_eps;
    data_xx17Limitation_min["tolerance"] = xy_tol;
    data_xx17Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx17Limitation_max = data_Constraints["xx17Limitation_max"];
    data_xx17Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx17Limitation_max["epsilon"]   = xy_eps;
    data_xx17Limitation_max["tolerance"] = xy_tol;
    data_xx17Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy17Limitation_min = data_Constraints["yy17Limitation_min"];
    data_yy17Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy17Limitation_min["epsilon"]   = xy_eps;
    data_yy17Limitation_min["tolerance"] = xy_tol;
    data_yy17Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy17Limitation_max = data_Constraints["yy17Limitation_max"];
    data_yy17Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy17Limitation_max["epsilon"]   = xy_eps;
    data_yy17Limitation_max["tolerance"] = xy_tol;
    data_yy17Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx18Limitation_min = data_Constraints["xx18Limitation_min"];
    data_xx18Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx18Limitation_min["epsilon"]   = xy_eps;
    data_xx18Limitation_min["tolerance"] = xy_tol;
    data_xx18Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx18Limitation_max = data_Constraints["xx18Limitation_max"];
    data_xx18Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx18Limitation_max["epsilon"]   = xy_eps;
    data_xx18Limitation_max["tolerance"] = xy_tol;
    data_xx18Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy18Limitation_min = data_Constraints["yy18Limitation_min"];
    data_yy18Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy18Limitation_min["epsilon"]   = xy_eps;
    data_yy18Limitation_min["tolerance"] = xy_tol;
    data_yy18Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy18Limitation_max = data_Constraints["yy18Limitation_max"];
    data_yy18Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy18Limitation_max["epsilon"]   = xy_eps;
    data_yy18Limitation_max["tolerance"] = xy_tol;
    data_yy18Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx19Limitation_min = data_Constraints["xx19Limitation_min"];
    data_xx19Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx19Limitation_min["epsilon"]   = xy_eps;
    data_xx19Limitation_min["tolerance"] = xy_tol;
    data_xx19Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx19Limitation_max = data_Constraints["xx19Limitation_max"];
    data_xx19Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx19Limitation_max["epsilon"]   = xy_eps;
    data_xx19Limitation_max["tolerance"] = xy_tol;
    data_xx19Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy19Limitation_min = data_Constraints["yy19Limitation_min"];
    data_yy19Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy19Limitation_min["epsilon"]   = xy_eps;
    data_yy19Limitation_min["tolerance"] = xy_tol;
    data_yy19Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy19Limitation_max = data_Constraints["yy19Limitation_max"];
    data_yy19Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy19Limitation_max["epsilon"]   = xy_eps;
    data_yy19Limitation_max["tolerance"] = xy_tol;
    data_yy19Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx20Limitation_min = data_Constraints["xx20Limitation_min"];
    data_xx20Limitation_min["subType"]   = "BARRIER_LOG";
    data_xx20Limitation_min["epsilon"]   = xy_eps;
    data_xx20Limitation_min["tolerance"] = xy_tol;
    data_xx20Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_xx20Limitation_max = data_Constraints["xx20Limitation_max"];
    data_xx20Limitation_max["subType"]   = "BARRIER_LOG";
    data_xx20Limitation_max["epsilon"]   = xy_eps;
    data_xx20Limitation_max["tolerance"] = xy_tol;
    data_xx20Limitation_max["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy20Limitation_min = data_Constraints["yy20Limitation_min"];
    data_yy20Limitation_min["subType"]   = "BARRIER_LOG";
    data_yy20Limitation_min["epsilon"]   = xy_eps;
    data_yy20Limitation_min["tolerance"] = xy_tol;
    data_yy20Limitation_min["active"]    = true;
    // PenaltyBarrier1DLessThan
    GenericContainer & data_yy20Limitation_max = data_Constraints["yy20Limitation_max"];
    data_yy20Limitation_max["subType"]   = "BARRIER_LOG";
    data_yy20Limitation_max["epsilon"]   = xy_eps;
    data_yy20Limitation_max["tolerance"] = xy_tol;
    data_yy20Limitation_max["active"]    = true;
    // Constraint1D: none defined
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
