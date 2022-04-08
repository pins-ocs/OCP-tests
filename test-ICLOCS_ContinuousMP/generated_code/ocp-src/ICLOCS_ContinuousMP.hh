/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP.hh                                         |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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

  class ICLOCS_ContinuousMP : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[5];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DLessThan u1Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u1Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u2Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u2Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u3Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u3Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u4Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u4Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u5Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u5Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u6Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u6Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u7Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u7Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u8Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u8Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u9Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u9Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u10Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u10Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u11Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u11Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u12Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u12Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u13Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u13Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u14Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u14Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u15Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u15Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u16Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u16Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u17Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u17Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u18Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u18Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u19Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u19Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan u20Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan u20Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx1Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx1Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy1Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy1Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx2Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx2Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy2Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy2Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx3Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx3Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy3Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy3Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx4Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx4Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy4Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy4Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx5Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx5Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy5Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy5Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx6Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx6Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy6Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy6Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx7Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx7Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy7Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy7Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx8Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx8Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy8Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy8Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx9Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx9Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy9Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy9Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx10Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx10Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy10Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy10Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx11Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx11Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy11Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy11Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx12Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx12Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy12Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy12Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx13Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx13Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy13Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy13Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx14Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx14Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy14Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy14Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx15Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx15Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy15Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy15Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx16Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx16Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy16Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy16Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx17Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx17Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy17Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy17Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx18Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx18Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy18Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy18Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx19Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx19Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy19Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy19Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan xx20Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan xx20Limitation_max;
    Mechatronix::PenaltyBarrier1DLessThan yy20Limitation_min;
    Mechatronix::PenaltyBarrier1DLessThan yy20Limitation_max;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

    ICLOCS_CONTINUOUSMP_API_DLL
    explicit
    ICLOCS_ContinuousMP(
      string const   & name,
      integer          n_threads,
      Console const  * console
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
    ICLOCS_CONTINUOUSMP_API_DLL real_type u1Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u1Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u1Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u2Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u2Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u2Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u3Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u3Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u3Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u4Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u4Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u4Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u5Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u5Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u5Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u6Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u6Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u6Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u7Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u7Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u7Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u8Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u8Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u8Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u9Limitation        ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u9Limitation_D      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u9Limitation_DD     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u10Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u10Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u10Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u11Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u11Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u11Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u12Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u12Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u12Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u13Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u13Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u13Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u14Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u14Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u14Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u15Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u15Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u15Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u16Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u16Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u16Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u17Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u17Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u17Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u18Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u18Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u18Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u19Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u19Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u19Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u20Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u20Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type u20Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx1Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx1Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx1Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy1Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy1Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy1Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx2Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx2Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx2Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy2Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy2Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy2Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx3Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx3Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx3Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy3Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy3Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy3Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx4Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx4Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx4Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy4Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy4Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy4Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx5Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx5Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx5Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy5Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy5Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy5Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx6Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx6Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx6Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy6Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy6Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy6Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx7Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx7Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx7Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy7Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy7Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy7Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx8Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx8Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx8Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy8Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy8Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy8Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx9Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx9Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx9Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy9Limitation       ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy9Limitation_D     ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy9Limitation_DD    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx10Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx10Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx10Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy10Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy10Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy10Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx11Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx11Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx11Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy11Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy11Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy11Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx12Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx12Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx12Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy12Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy12Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy12Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx13Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx13Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx13Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy13Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy13Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy13Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx14Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx14Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx14Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy14Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy14Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy14Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx15Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx15Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx15Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy15Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy15Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy15Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx16Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx16Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx16Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy16Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy16Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy16Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx17Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx17Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx17Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy17Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy17Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy17Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx18Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx18Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx18Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy18Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy18Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy18Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx19Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx19Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx19Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy19Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy19Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy19Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx20Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx20Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type xx20Limitation_DD   ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy20Limitation      ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy20Limitation_D    ( real_type xo___V ) const;
    ICLOCS_CONTINUOUSMP_API_DLL real_type yy20Limitation_DD   ( real_type xo___V ) const;

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
