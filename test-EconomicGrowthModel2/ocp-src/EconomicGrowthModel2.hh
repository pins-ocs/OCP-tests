/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2.hh                                        |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef ECONOMICGROWTHMODEL2_HH
#define ECONOMICGROWTHMODEL2_HH

// Mechatronix Headers
#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>

// user headers
#include <MechatronixCore/MechatronixCore.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef ECONOMICGROWTHMODEL2_API_DLL
    #ifdef ECONOMICGROWTHMODEL2_EXPORT
      #define ECONOMICGROWTHMODEL2_API_DLL __declspec(dllexport)
    #elif defined(ECONOMICGROWTHMODEL2_IMPORT)
      #define ECONOMICGROWTHMODEL2_API_DLL __declspec(dllimport)
    #else
      #define ECONOMICGROWTHMODEL2_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define ECONOMICGROWTHMODEL2_API_DLL
#endif

#define OCP_VIRTUAL          MECHATRONIX_OVERRIDE
#define INDIRECT_OCP_VIRTUAL MECHATRONIX_OVERRIDE

namespace EconomicGrowthModel2Define {

  using namespace MechatronixLoad;

  using namespace std;
  using Mechatronix::real_type;
  using Mechatronix::integer;
  using Mechatronix::ostream_type;

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

  class EconomicGrowthModel2 : public Mechatronix::Discretized_Indirect_OCP {

    // redirect output to a string in GenericContainer - - - - - - - - - - - - -
    stringstream ss_redirected_stream;

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[8];

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
    EconomicGrowthModel2( EconomicGrowthModel2 const & );
    EconomicGrowthModel2 const & operator = ( EconomicGrowthModel2 const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuationStep0( real_type s );

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;

    using Mechatronix::Discretized_Indirect_OCP::numOMEGA;

    using Mechatronix::Discretized_Indirect_OCP::bcInvMap;
    using Mechatronix::Discretized_Indirect_OCP::bcMap;
    using Mechatronix::Discretized_Indirect_OCP::numBC;

    using Mechatronix::Discretized_Indirect_OCP::dim_Q;
    using Mechatronix::Discretized_Indirect_OCP::dim_X;
    using Mechatronix::Discretized_Indirect_OCP::dim_U;
    using Mechatronix::Discretized_Indirect_OCP::dim_Pars;
    using Mechatronix::Discretized_Indirect_OCP::dim_Omega;
    using Mechatronix::Discretized_Indirect_OCP::dim_BC;
    using Mechatronix::Discretized_Indirect_OCP::nNodes;

    using Mechatronix::Discretized_Indirect_OCP::numEquations;
    using Mechatronix::Discretized_Indirect_OCP::eval_F;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_nnz;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_pattern;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF_values;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF;

    using Mechatronix::Discretized_Indirect_OCP::get_solution;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_spline;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_guess;

    using Mechatronix::Indirect_OCP::setupBC;

    ECONOMICGROWTHMODEL2_API_DLL
    explicit
    EconomicGrowthModel2(
      string const & name,
      ThreadPool   * _TP,
      Console      * _pConsole
    );

    ECONOMICGROWTHMODEL2_API_DLL virtual
    ~EconomicGrowthModel2() MECHATRONIX_OVERRIDE;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL virtual
    char const * model_name() const MECHATRONIX_OVERRIDE
    { return "EconomicGrowthModel2"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    infoClasses() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    ECONOMICGROWTHMODEL2_API_DLL real_type Q           ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type Q_D_1       ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type Q_D_1_1     ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type Q_D_1_2     ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type Q_D_2       ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type Q_D_2_2     ( real_type x__XO, real_type y__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog      ( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_1  ( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_1_1( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_1_2( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_1_3( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_2  ( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_2_2( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_2_3( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_3  ( real_type a__XO, real_type b__XO, real_type s__XO ) const;
    ECONOMICGROWTHMODEL2_API_DLL real_type explog_D_3_3( real_type a__XO, real_type b__XO, real_type s__XO ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    ECONOMICGROWTHMODEL2_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // do some check on the computed solution
    ECONOMICGROWTHMODEL2_API_DLL
    void
    diagnostic( GenericContainer const & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    ECONOMICGROWTHMODEL2_API_DLL
    void
    updateContinuation( integer phase, real_type s ) MECHATRONIX_OVERRIDE;

    // save model parameters
    ECONOMICGROWTHMODEL2_API_DLL virtual
    void
    save_OCP_info( GenericContainer & gc ) const MECHATRONIX_OVERRIDE;

  };
}

namespace EconomicGrowthModel2Load {
  using EconomicGrowthModel2Define::EconomicGrowthModel2;

}

#endif

// EOF: EconomicGrowthModel2.hh
