/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3.hh                                         |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#ifndef POINTMASSCARMODEL_3_DOT_HH
#define POINTMASSCARMODEL_3_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
// User Headers
#include <MechatronixRoad/MechatronixRoad.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef POINTMASSCARMODEL_3_API_DLL
    #ifdef POINTMASSCARMODEL_3_EXPORT
      #define POINTMASSCARMODEL_3_API_DLL __declspec(dllexport)
    #elif defined(POINTMASSCARMODEL_3_IMPORT)
      #define POINTMASSCARMODEL_3_API_DLL __declspec(dllimport)
    #else
      #define POINTMASSCARMODEL_3_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define POINTMASSCARMODEL_3_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace PointMassCarModel_3Define {

  using namespace MechatronixLoad;

  using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::Road2D;


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

  class PointMassCarModel_3 : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[17];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU v__fxControl;
    Mechatronix::PenaltyBarrierU v__OmegaControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DGreaterThan AdherenceEllipse;
    Mechatronix::PenaltyBarrier1DGreaterThan RoadLeftBorder;
    Mechatronix::PenaltyBarrier1DGreaterThan RoadRightBorder;
    Mechatronix::PenaltyBarrier1DGreaterThan PowerLimit;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::Road2D * pRoad;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    PointMassCarModel_3( PointMassCarModel_3 const & );
    PointMassCarModel_3 const & operator = ( PointMassCarModel_3 const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuationStep0( real_type s );
    void continuationStep1( real_type s );

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;

    using Mechatronix::Discretized_Indirect_OCP::num_OMEGA;

    using Mechatronix::Discretized_Indirect_OCP::bc_inv_map;
    using Mechatronix::Discretized_Indirect_OCP::bc_map;
    using Mechatronix::Discretized_Indirect_OCP::num_BC;

    using Mechatronix::Discretized_Indirect_OCP::dim_Q;
    using Mechatronix::Discretized_Indirect_OCP::dim_X;
    using Mechatronix::Discretized_Indirect_OCP::dim_U;
    using Mechatronix::Discretized_Indirect_OCP::dim_Pars;
    using Mechatronix::Discretized_Indirect_OCP::dim_Omega;
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

    POINTMASSCARMODEL_3_API_DLL
    explicit
    PointMassCarModel_3(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    POINTMASSCARMODEL_3_API_DLL virtual
    ~PointMassCarModel_3() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL virtual
    char const * model_name() const override
    { return "PointMassCarModel_3"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    infoClasses() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    POINTMASSCARMODEL_3_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    POINTMASSCARMODEL_3_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot      ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_1  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_1_1( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_1_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_1_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_1_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_2  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_2_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_2_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_2_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_3  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_3_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_3_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_4  ( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;
    POINTMASSCARMODEL_3_API_DLL real_type zeta__dot_D_4_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    POINTMASSCARMODEL_3_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    POINTMASSCARMODEL_3_API_DLL
    void
    update_continuation(
      integer   phase,
      real_type old_s,
      real_type s
    ) override;

    // save model parameters
    POINTMASSCARMODEL_3_API_DLL virtual
    void
    save_OCP_info( GenericContainer & gc ) const override;

  };
}

namespace PointMassCarModel_3Load {
  using PointMassCarModel_3Define::PointMassCarModel_3;

}

#endif

// EOF: PointMassCarModel_3.hh