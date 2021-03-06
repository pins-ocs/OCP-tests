/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket.hh                                               |
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


#ifndef GODDARDROCKET_HH
#define GODDARDROCKET_HH

// Mechatronix Headers
#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>

// user headers
#include <MechatronixCore/MechatronixCore.hh>


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

#define OCP_VIRTUAL          MECHATRONIX_OVERRIDE
#define INDIRECT_OCP_VIRTUAL MECHATRONIX_OVERRIDE

namespace GoddardRocketDefine {

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

  class GoddardRocket : public Mechatronix::Discretized_Indirect_OCP {

    // redirect output to a string in GenericContainer - - - - - - - - - - - - -
    stringstream ss_redirected_stream;

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[17];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU TControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DGreaterThan massPositive;
    Mechatronix::PenaltyBarrier1DGreaterThan vPositive;
    Mechatronix::PenaltyBarrier1DGreaterThan TSPositive;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    GoddardRocket( GoddardRocket const & );
    GoddardRocket const & operator = ( GoddardRocket const & );

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

    GODDARDROCKET_API_DLL
    explicit
    GoddardRocket(
      string const & name,
      ThreadPool   * _TP,
      Console      * _pConsole
    );

    GODDARDROCKET_API_DLL virtual
    ~GoddardRocket() MECHATRONIX_OVERRIDE;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL virtual
    char const * model_name() const MECHATRONIX_OVERRIDE
    { return "GoddardRocket"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    infoClasses() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    GODDARDROCKET_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GODDARDROCKET_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    GODDARDROCKET_API_DLL real_type DD          ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1      ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1_1    ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type DD_D_1_2    ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type DD_D_2      ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type DD_D_2_2    ( real_type h__XO, real_type v__XO ) const;
    GODDARDROCKET_API_DLL real_type gg          ( real_type h__XO ) const;
    GODDARDROCKET_API_DLL real_type gg_D        ( real_type h__XO ) const;
    GODDARDROCKET_API_DLL real_type gg_DD       ( real_type h__XO ) const;
    GODDARDROCKET_API_DLL real_type explog      ( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1  ( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_1( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_2( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_1_3( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2  ( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2_2( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_2_3( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_3  ( real_type s__XO, real_type a__XO, real_type b__XO ) const;
    GODDARDROCKET_API_DLL real_type explog_D_3_3( real_type s__XO, real_type a__XO, real_type b__XO ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    GODDARDROCKET_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // do some check on the computed solution
    GODDARDROCKET_API_DLL
    void
    diagnostic( GenericContainer const & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    GODDARDROCKET_API_DLL
    void
    updateContinuation( integer phase, real_type s ) MECHATRONIX_OVERRIDE;

    // save model parameters
    GODDARDROCKET_API_DLL virtual
    void
    save_OCP_info( GenericContainer & gc ) const MECHATRONIX_OVERRIDE;

  };
}

namespace GoddardRocketLoad {
  using GoddardRocketDefine::GoddardRocket;

}

#endif

// EOF: GoddardRocket.hh
