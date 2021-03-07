/*-----------------------------------------------------------------------*\
 |  file: HangGlider.hh                                                  |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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


#ifndef HANGGLIDER_DOT_HH
#define HANGGLIDER_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
// User Headers
#include <MechatronixCore/MechatronixCore.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef HANGGLIDER_API_DLL
    #ifdef HANGGLIDER_EXPORT
      #define HANGGLIDER_API_DLL __declspec(dllexport)
    #elif defined(HANGGLIDER_IMPORT)
      #define HANGGLIDER_API_DLL __declspec(dllimport)
    #else
      #define HANGGLIDER_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define HANGGLIDER_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace HangGliderDefine {

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

  class HangGlider : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[25];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU cLControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DGreaterThan Tbound;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    HangGlider( HangGlider const & );
    HangGlider const & operator = ( HangGlider const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuationStep0( real_type s );
    void continuationStep1( real_type s );

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

    HANGGLIDER_API_DLL
    explicit
    HangGlider(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    HANGGLIDER_API_DLL virtual
    ~HangGlider() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL virtual
    char const * model_name() const override
    { return "HangGlider"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    infoClasses() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    HANGGLIDER_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    HANGGLIDER_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    HANGGLIDER_API_DLL real_type r         ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type r_D       ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type r_DD      ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type u         ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type u_D       ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type u_DD      ( real_type xo__x ) const;
    HANGGLIDER_API_DLL real_type w         ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type w_D_1     ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type w_D_1_1   ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type w_D_1_2   ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type w_D_2     ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type w_D_2_2   ( real_type xo__x, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2        ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_1    ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_1_1  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_1_2  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_1_3  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_2    ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_2_2  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_2_3  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_3    ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v2_D_3_3  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v         ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_1     ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_1_1   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_1_2   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_1_3   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_2     ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_2_2   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_2_3   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_3     ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type v_D_3_3   ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun      ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_1  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_2  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_3  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Dfun_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun      ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_1  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_2  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_3  ( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;
    HANGGLIDER_API_DLL real_type Lfun_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    HANGGLIDER_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    HANGGLIDER_API_DLL
    void
    updateContinuation(
      integer   phase,
      real_type old_s,
      real_type s
    ) override;

    // save model parameters
    HANGGLIDER_API_DLL virtual
    void
    save_OCP_info( GenericContainer & gc ) const override;

  };
}

namespace HangGliderLoad {
  using HangGliderDefine::HangGlider;

}

#endif

// EOF: HangGlider.hh
