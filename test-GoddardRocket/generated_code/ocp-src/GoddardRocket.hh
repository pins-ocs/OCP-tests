/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket.hh                                               |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#ifndef GODDARDROCKET_DOT_HH
#define GODDARDROCKET_DOT_HH

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
  #ifndef GODDARDROCKET_API_DLL
    #ifdef GODDARDROCKET_EXPORT
      #define GODDARDROCKET_API_DLL __declspec(dllexport)
    #elif defined(GODDARDROCKET_IMPORT)
      #define GODDARDROCKET_API_DLL __declspec(dllimport)
    #else
      #define GODDARDROCKET_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define GODDARDROCKET_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace GoddardRocketDefine {

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

  using Mechatronix::X_p_type;
  using Mechatronix::L_p_type;
  using Mechatronix::Z_p_type;
  using Mechatronix::U_p_type;
  using Mechatronix::MU_p_type;
  using Mechatronix::V_p_type;
  using Mechatronix::Q_p_type;
  using Mechatronix::P_p_type;
  using Mechatronix::OMEGA_p_type;
  using Mechatronix::OMEGA_full_p_type;

  using Mechatronix::X_const_p_type;
  using Mechatronix::L_const_p_type;
  using Mechatronix::Z_const_p_type;
  using Mechatronix::U_const_p_type;
  using Mechatronix::MU_const_p_type;
  using Mechatronix::V_const_p_type;
  using Mechatronix::Q_const_p_type;
  using Mechatronix::P_const_p_type;
  using Mechatronix::OMEGA_const_p_type;
  using Mechatronix::OMEGA_full_const_p_type;

  using Mechatronix::NodeQX;
  using Mechatronix::NodeQXL;

  using Mechatronix::MatrixWrapper;

  using GenericContainerNamespace::GenericContainer;

  class GoddardRocket : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[25];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU TControl;

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DLessThan massPositive;
    Mechatronix::PenaltyBarrier1DLessThan vPositive;
    Mechatronix::PenaltyBarrier1DLessThan TSPositive;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    GoddardRocket( GoddardRocket const & );
    GoddardRocket const & operator = ( GoddardRocket const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuation_step_0( real_type s );

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;
    using Mechatronix::Discretized_Indirect_OCP::num_active_BC;

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

    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_nnz;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_pattern;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_values;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2;

    using Mechatronix::Discretized_Indirect_OCP::get_solution;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_spline;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_guess;

    using Mechatronix::Indirect_OCP::setup_BC;

    GODDARDROCKET_API_DLL
    explicit
    GoddardRocket(
      string  const  & name,
      Console const  * console,
      ThreadPoolBase * TP
    );

    ~GoddardRocket() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "GoddardRocket"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    GODDARDROCKET_API_DLL
    void setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    GODDARDROCKET_API_DLL real_type DD          ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1      ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1_1    ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1_2    ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type DD_D_2      ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type DD_D_2_2    ( real_type xo__h, real_type xo__v ) const;
    GODDARDROCKET_API_DLL real_type gg          ( real_type xo__h ) const;
    GODDARDROCKET_API_DLL real_type gg_D        ( real_type xo__h ) const;
    GODDARDROCKET_API_DLL real_type gg_DD       ( real_type xo__h ) const;
    GODDARDROCKET_API_DLL real_type explog      ( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1  ( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_1( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_2( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_3( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2  ( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2_2( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2_3( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_3  ( real_type xo__s, real_type xo__a, real_type xo__b ) const;
    GODDARDROCKET_API_DLL real_type explog_D_3_3( real_type xo__s, real_type xo__a, real_type xo__b ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    GODDARDROCKET_API_DLL
    void setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    GODDARDROCKET_API_DLL
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

namespace GoddardRocketLoad {
  using GoddardRocketDefine::GoddardRocket;

}

#endif

// EOF: GoddardRocket.hh
