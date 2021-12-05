/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP.hh                                         |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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


#ifndef ICLOCS_CONTINUOUSMP_DOT_HH
#define ICLOCS_CONTINUOUSMP_DOT_HH

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
  #ifndef ICLOCS_CONTINUOUSMP_API_DLL
    #ifdef ICLOCS_CONTINUOUSMP_EXPORT
      #define ICLOCS_CONTINUOUSMP_API_DLL __declspec(dllexport)
    #elif defined(ICLOCS_CONTINUOUSMP_IMPORT)
      #define ICLOCS_CONTINUOUSMP_API_DLL __declspec(dllimport)
    #else
      #define ICLOCS_CONTINUOUSMP_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define ICLOCS_CONTINUOUSMP_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace ICLOCS_ContinuousMPDefine {

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

  class ICLOCS_ContinuousMP : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[4];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DInterval u1Limitation;
    Mechatronix::PenaltyBarrier1DInterval u2Limitation;
    Mechatronix::PenaltyBarrier1DInterval u3Limitation;
    Mechatronix::PenaltyBarrier1DInterval u4Limitation;
    Mechatronix::PenaltyBarrier1DInterval u5Limitation;
    Mechatronix::PenaltyBarrier1DInterval u6Limitation;
    Mechatronix::PenaltyBarrier1DInterval u7Limitation;
    Mechatronix::PenaltyBarrier1DInterval u8Limitation;
    Mechatronix::PenaltyBarrier1DInterval u9Limitation;
    Mechatronix::PenaltyBarrier1DInterval u10Limitation;
    Mechatronix::PenaltyBarrier1DInterval u11Limitation;
    Mechatronix::PenaltyBarrier1DInterval u12Limitation;
    Mechatronix::PenaltyBarrier1DInterval u13Limitation;
    Mechatronix::PenaltyBarrier1DInterval u14Limitation;
    Mechatronix::PenaltyBarrier1DInterval u15Limitation;
    Mechatronix::PenaltyBarrier1DInterval u16Limitation;
    Mechatronix::PenaltyBarrier1DInterval u17Limitation;
    Mechatronix::PenaltyBarrier1DInterval u18Limitation;
    Mechatronix::PenaltyBarrier1DInterval u19Limitation;
    Mechatronix::PenaltyBarrier1DInterval u20Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx1Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy1Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx2Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy2Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx3Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy3Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx4Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy4Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx5Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy5Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx6Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy6Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx7Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy7Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx8Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy8Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx9Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy9Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx10Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy10Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx11Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy11Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx12Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy12Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx13Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy13Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx14Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy14Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx15Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy15Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx16Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy16Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx17Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy17Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx18Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy18Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx19Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy19Limitation;
    Mechatronix::PenaltyBarrier1DInterval xx20Limitation;
    Mechatronix::PenaltyBarrier1DInterval yy20Limitation;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_ContinuousMP( ICLOCS_ContinuousMP const & );
    ICLOCS_ContinuousMP const & operator = ( ICLOCS_ContinuousMP const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuation_step_0( real_type s );

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

    ICLOCS_CONTINUOUSMP_API_DLL
    explicit
    ICLOCS_ContinuousMP(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    ~ICLOCS_ContinuousMP() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "ICLOCS_ContinuousMP"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    ICLOCS_CONTINUOUSMP_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    ICLOCS_CONTINUOUSMP_API_DLL
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

namespace ICLOCS_ContinuousMPLoad {
  using ICLOCS_ContinuousMPDefine::ICLOCS_ContinuousMP;

}

#endif

// EOF: ICLOCS_ContinuousMP.hh
