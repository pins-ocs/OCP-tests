/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF.hh                                       |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#ifndef HYPERSONICPROBLEM3DOF_DOT_HH
#define HYPERSONICPROBLEM3DOF_DOT_HH

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
  #ifndef HYPERSONICPROBLEM3DOF_API_DLL
    #ifdef HYPERSONICPROBLEM3DOF_EXPORT
      #define HYPERSONICPROBLEM3DOF_API_DLL __declspec(dllexport)
    #elif defined(HYPERSONICPROBLEM3DOF_IMPORT)
      #define HYPERSONICPROBLEM3DOF_API_DLL __declspec(dllimport)
    #else
      #define HYPERSONICPROBLEM3DOF_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define HYPERSONICPROBLEM3DOF_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace HypersonicProblem3DOFDefine {

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
  extern char const *namesConstraintLT[];
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

  class HypersonicProblem3DOF : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[36];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU u2Control;

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DLessThan G_bound_min;
    Mechatronix::PenaltyBarrier1DLessThan G_bound_max;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    HypersonicProblem3DOF( HypersonicProblem3DOF const & );
    HypersonicProblem3DOF const & operator = ( HypersonicProblem3DOF const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuation_step_0( real_type s );
    void continuation_step_1( real_type s );
    void continuation_step_2( real_type s );

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;

    using Mechatronix::Discretized_Indirect_OCP::num_active_BC;

    using Mechatronix::Discretized_Indirect_OCP::bc_map;
    using Mechatronix::Discretized_Indirect_OCP::bc_inv_map;

    using Mechatronix::Discretized_Indirect_OCP::dim_Q;
    using Mechatronix::Discretized_Indirect_OCP::dim_X;
    using Mechatronix::Discretized_Indirect_OCP::dim_U;
    using Mechatronix::Discretized_Indirect_OCP::dim_Pars;
    using Mechatronix::Discretized_Indirect_OCP::dim_BC;
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

    HYPERSONICPROBLEM3DOF_API_DLL
    explicit
    HypersonicProblem3DOF(
      string  const  & name,
      Console const  * console,
      ThreadPoolBase * TP
    );

    ~HypersonicProblem3DOF() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "HypersonicProblem3DOF"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    HYPERSONICPROBLEM3DOF_API_DLL real_type h_guess          ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type h_guess_D        ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type h_guess_DD       ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type theta_guess      ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type theta_guess_D    ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type theta_guess_DD   ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type phi_guess        ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type phi_guess_D      ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type phi_guess_DD     ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type V_guess          ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type V_guess_D        ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type V_guess_DD       ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_guess          ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_guess_D        ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_guess_DD       ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type psi_guess        ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type psi_guess_D      ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type psi_guess_DD     ( real_type xo__s ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_bound          ( real_type xo___V ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_bound_D        ( real_type xo___V ) const;
    HYPERSONICPROBLEM3DOF_API_DLL real_type G_bound_DD       ( real_type xo___V ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    HYPERSONICPROBLEM3DOF_API_DLL
    void setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    HYPERSONICPROBLEM3DOF_API_DLL
    void
    update_continuation(
      integer   phase,
      real_type old_s,
      real_type s
    ) override;

    // save model parameters
    void save_OCP_info( GenericContainer & gc ) const override;

  };
}

namespace HypersonicProblem3DOFLoad {
  using HypersonicProblem3DOFDefine::HypersonicProblem3DOF;

}

#endif

// EOF: HypersonicProblem3DOF.hh