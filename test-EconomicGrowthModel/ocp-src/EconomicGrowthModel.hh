/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel.hh                                         |
 |                                                                       |
 |  version: 1.0   date 14/7/2021                                        |
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


#ifndef ECONOMICGROWTHMODEL_DOT_HH
#define ECONOMICGROWTHMODEL_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
// User Headers
#include <MechatronixCore/MechatronixCore.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef ECONOMICGROWTHMODEL_API_DLL
    #ifdef ECONOMICGROWTHMODEL_EXPORT
      #define ECONOMICGROWTHMODEL_API_DLL __declspec(dllexport)
    #elif defined(ECONOMICGROWTHMODEL_IMPORT)
      #define ECONOMICGROWTHMODEL_API_DLL __declspec(dllimport)
    #else
      #define ECONOMICGROWTHMODEL_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define ECONOMICGROWTHMODEL_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace EconomicGrowthModelDefine {

  using namespace MechatronixLoad;

  using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;


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

  class EconomicGrowthModel : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[10];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU uControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DGreaterThan Tpositive;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    EconomicGrowthModel( EconomicGrowthModel const & );
    EconomicGrowthModel const & operator = ( EconomicGrowthModel const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuationStep0( real_type s );

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

    ECONOMICGROWTHMODEL_API_DLL
    explicit
    EconomicGrowthModel(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    ECONOMICGROWTHMODEL_API_DLL virtual
    ~EconomicGrowthModel() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL virtual
    char const * model_name() const override
    { return "EconomicGrowthModel"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    infoClasses() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    ECONOMICGROWTHMODEL_API_DLL real_type Q        ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type Q_D_1    ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type Q_D_1_1  ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type Q_D_1_2  ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type Q_D_2    ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type Q_D_2_2  ( real_type xo__x, real_type xo__y ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1L      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1L_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1L_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2L      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2L_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2L_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1L      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1L_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1L_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2L      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2L_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2L_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1R      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1R_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x1R_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2R      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2R_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type x2R_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1R      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1R_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l1R_DD   ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2R      ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2R_D    ( real_type xo__t ) const;
    ECONOMICGROWTHMODEL_API_DLL real_type l2R_DD   ( real_type xo__t ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    ECONOMICGROWTHMODEL_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    ECONOMICGROWTHMODEL_API_DLL
    void
    update_continuation(
      integer   phase,
      real_type old_s,
      real_type s
    ) override;

    // save model parameters
    ECONOMICGROWTHMODEL_API_DLL virtual
    void
    save_OCP_info( GenericContainer & gc ) const override;

  };
}

namespace EconomicGrowthModelLoad {
  using EconomicGrowthModelDefine::EconomicGrowthModel;

}

#endif

// EOF: EconomicGrowthModel.hh
