/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking.hh                                      |
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


#ifndef ICLOCS_PARALLELPARKING_DOT_HH
#define ICLOCS_PARALLELPARKING_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
// User Headers
#include <MechatronixCore/MechatronixCore.hh>


// User Header (begin)
// User Header (end)

#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef ICLOCS_PARALLELPARKING_API_DLL
    #ifdef ICLOCS_PARALLELPARKING_EXPORT
      #define ICLOCS_PARALLELPARKING_API_DLL __declspec(dllexport)
    #elif defined(ICLOCS_PARALLELPARKING_IMPORT)
      #define ICLOCS_PARALLELPARKING_API_DLL __declspec(dllimport)
    #else
      #define ICLOCS_PARALLELPARKING_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define ICLOCS_PARALLELPARKING_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace ICLOCS_ParallelParkingDefine {

  using namespace MechatronixLoad;

  using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;


  // User Namespaces (begin)
  // User Namespaces (end)

  extern char const *namesBc[];
  extern char const *namesXvars[];
  extern char const *namesLvars[];
  extern char const *namesUvars[];
  extern char const *namesQvars[];
  extern char const *namesPvars[];
  extern char const *namesOMEGAvars[];

  extern char const *namesModelPars[];

  extern char const *namesPostProcess[];
  extern char const *namesIntegratedPostProcess[];
  extern char const *namesConstraint1D[];
  extern char const *namesConstraint2D[];
  extern char const *namesConstraintU[];

  using Mechatronix::X_pointer_type;
  using Mechatronix::L_pointer_type;
  using Mechatronix::Z_pointer_type;
  using Mechatronix::U_pointer_type;
  using Mechatronix::V_pointer_type;
  using Mechatronix::Q_pointer_type;
  using Mechatronix::P_pointer_type;
  using Mechatronix::OMEGA_pointer_type;
  using Mechatronix::OMEGA_full_pointer_type;

  using Mechatronix::X_const_pointer_type;
  using Mechatronix::L_const_pointer_type;
  using Mechatronix::Z_const_pointer_type;
  using Mechatronix::U_const_pointer_type;
  using Mechatronix::V_const_pointer_type;
  using Mechatronix::Q_const_pointer_type;
  using Mechatronix::P_const_pointer_type;
  using Mechatronix::OMEGA_const_pointer_type;
  using Mechatronix::OMEGA_full_const_pointer_type;

  using Mechatronix::MatrixWrapper;

  using GenericContainerNamespace::GenericContainer;

  class ICLOCS_ParallelParking : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[14];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU u1Control;
    Mechatronix::PenaltyBarrierU u2Control;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DInterval A_bound;
    Mechatronix::PenaltyBarrier1DInterval B_bound;
    Mechatronix::PenaltyBarrier1DInterval C_bound;
    Mechatronix::PenaltyBarrier1DInterval D_bound;
    Mechatronix::PenaltyBarrier1DGreaterThan EXTRA1_bound;
    Mechatronix::PenaltyBarrier1DGreaterThan EXTRA2_bound;
    Mechatronix::PenaltyBarrier1DInterval vel_bound;
    Mechatronix::PenaltyBarrier1DInterval acc_bound;
    Mechatronix::PenaltyBarrier1DInterval phi_bound;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_ParallelParking( ICLOCS_ParallelParking const & );
    ICLOCS_ParallelParking const & operator = ( ICLOCS_ParallelParking const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;

    using Mechatronix::Discretized_Indirect_OCP::num_active_BC;
    using Mechatronix::Discretized_Indirect_OCP::num_initial_BC;
    using Mechatronix::Discretized_Indirect_OCP::num_final_BC;
    using Mechatronix::Discretized_Indirect_OCP::num_cyclic_BC;

    using Mechatronix::Discretized_Indirect_OCP::num_OMEGA;
    using Mechatronix::Discretized_Indirect_OCP::num_initial_OMEGA;
    using Mechatronix::Discretized_Indirect_OCP::num_final_OMEGA;
    using Mechatronix::Discretized_Indirect_OCP::num_cyclic_OMEGA;

    using Mechatronix::Discretized_Indirect_OCP::bc_map;
    using Mechatronix::Discretized_Indirect_OCP::bc_inv_map;

    using Mechatronix::Discretized_Indirect_OCP::omega_map;
    using Mechatronix::Discretized_Indirect_OCP::omega_inv_map;

    using Mechatronix::Discretized_Indirect_OCP::dim_Q;
    using Mechatronix::Discretized_Indirect_OCP::dim_X;
    using Mechatronix::Discretized_Indirect_OCP::dim_U;
    using Mechatronix::Discretized_Indirect_OCP::dim_Pars;
    using Mechatronix::Discretized_Indirect_OCP::dim_Omega;
    using Mechatronix::Discretized_Indirect_OCP::dim_BC;
    using Mechatronix::Discretized_Indirect_OCP::dim_full_BC;
    using Mechatronix::Discretized_Indirect_OCP::num_nodes;

    using Mechatronix::Discretized_Indirect_OCP::num_equations;
    using Mechatronix::Discretized_Indirect_OCP::num_parameters;
    using Mechatronix::Discretized_Indirect_OCP::eval_F;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_nnz;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_pattern;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_values;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF;

    using Mechatronix::Discretized_Indirect_OCP::get_solution;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_spline;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_guess;

    using Mechatronix::Indirect_OCP::setup_BC;

    ICLOCS_PARALLELPARKING_API_DLL
    explicit
    ICLOCS_ParallelParking(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    ~ICLOCS_ParallelParking() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "ICLOCS_ParallelParking"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ax_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ay_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Bx_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type By_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cx_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Cy_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dx_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Dy_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ox_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Oy_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ex_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey          ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_1      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_1_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_1_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_1_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_2      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_2_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_2_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_3      ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type Ey_D_3_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area        ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_1    ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_1_1  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_1_2  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_1_3  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_2    ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_2_2  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_2_3  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_3    ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area_D_3_3  ( real_type xo__a, real_type xo__b, real_type xo__c ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2       ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_1 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_2 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_3 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_4 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_5 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_1_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2_2 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2_3 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2_4 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2_5 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_2_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_3   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_3_3 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_3_4 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_3_5 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_3_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_4   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_4_4 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_4_5 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_4_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_5   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_5_5 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_5_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_6   ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type area2_D_6_6 ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ       ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_1   ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_1_1 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_1_2 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_1_3 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_1_4 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_2   ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_2_2 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_2_3 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_2_4 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_3   ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_3_3 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_3_4 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_4   ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ_D_4_4 ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2      ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_1( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_1_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_2_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_3_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_4_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_5  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_5_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_5_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_5_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_5_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_6  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_6_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_6_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_6_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_7  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_7_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_7_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_8  ( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type areaQ2_D_8_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AEB_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BEC_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type CED_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DEA_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type AOB_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type BOC_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type COD_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA         ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_1     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_1_1   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_1_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_1_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_2     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_2_2   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_2_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_3     ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type DOA_D_3_3   ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD        ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_1    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_1_1  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_1_2  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_1_3  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_2    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_2_2  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_2_3  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_3    ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type ABCD_D_3_3  ( real_type xo__x, real_type xo__y, real_type xo__theta ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type f_slot      ( real_type xo__x ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type f_slot_D    ( real_type xo__x ) const;
    ICLOCS_PARALLELPARKING_API_DLL real_type f_slot_DD   ( real_type xo__x ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    ICLOCS_PARALLELPARKING_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    ICLOCS_PARALLELPARKING_API_DLL
    void
    update_continuation(
      integer   phase,
      real_type old_s,
      real_type s
    ) override;

    // save model parameters
    void
    save_OCP_info( GenericContainer & gc ) const override;

  };
}

namespace ICLOCS_ParallelParkingLoad {
  using ICLOCS_ParallelParkingDefine::ICLOCS_ParallelParking;

}

#endif

// EOF: ICLOCS_ParallelParking.hh
