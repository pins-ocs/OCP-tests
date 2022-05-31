/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1.hh                                         |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#ifndef POINTMASSCARMODEL_1_DOT_HH
#define POINTMASSCARMODEL_1_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
// User Headers
#include <MechatronixRoad/MechatronixRoad.hh>


// User Header (begin)
// User Header (end)

#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef POINTMASSCARMODEL_1_API_DLL
    #ifdef POINTMASSCARMODEL_1_EXPORT
      #define POINTMASSCARMODEL_1_API_DLL __declspec(dllexport)
    #elif defined(POINTMASSCARMODEL_1_IMPORT)
      #define POINTMASSCARMODEL_1_API_DLL __declspec(dllimport)
    #else
      #define POINTMASSCARMODEL_1_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define POINTMASSCARMODEL_1_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace PointMassCarModel_1Define {

  using namespace MechatronixLoad;

  using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::Road2D;


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

  class PointMassCarModel_1 : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[16];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU v__fxControl;
    Mechatronix::PenaltyBarrierU v__OmegaControl;

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DLessThan AdherenceEllipse;
    Mechatronix::PenaltyBarrier1DLessThan RoadLeftBorder;
    Mechatronix::PenaltyBarrier1DLessThan RoadRightBorder;
    Mechatronix::PenaltyBarrier1DLessThan PowerLimit;
    Mechatronix::PenaltyBarrier1DLessThan LimitMinSpeed;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::Road2D * pRoad;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    PointMassCarModel_1( PointMassCarModel_1 const & );
    PointMassCarModel_1 const & operator = ( PointMassCarModel_1 const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuation_step_0( real_type s );
    void continuation_step_1( real_type s );

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

    POINTMASSCARMODEL_1_API_DLL
    explicit
    PointMassCarModel_1(
      string const   & name,
      integer          n_threads,
      Console const  * console
    );

    ~PointMassCarModel_1() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "PointMassCarModel_1"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    POINTMASSCARMODEL_1_API_DLL
    void setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_1_API_DLL
    void setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot      ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_1  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_1_1( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_1_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_1_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_1_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_2  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_2_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_2_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_2_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_3  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_3_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_3_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_4  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_1_API_DLL real_type inv_zeta__dot_D_4_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    POINTMASSCARMODEL_1_API_DLL
    void setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    POINTMASSCARMODEL_1_API_DLL
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

namespace PointMassCarModel_1Load {
  using PointMassCarModel_1Define::PointMassCarModel_1;

}

#endif

// EOF: PointMassCarModel_1.hh
