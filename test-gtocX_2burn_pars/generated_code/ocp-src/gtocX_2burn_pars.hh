/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars.hh                                            |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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


#ifndef GTOCX_2BURN_PARS_DOT_HH
#define GTOCX_2BURN_PARS_DOT_HH

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
  #ifndef GTOCX_2BURN_PARS_API_DLL
    #ifdef GTOCX_2BURN_PARS_EXPORT
      #define GTOCX_2BURN_PARS_API_DLL __declspec(dllexport)
    #elif defined(GTOCX_2BURN_PARS_IMPORT)
      #define GTOCX_2BURN_PARS_API_DLL __declspec(dllimport)
    #else
      #define GTOCX_2BURN_PARS_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define GTOCX_2BURN_PARS_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace gtocX_2burn_parsDefine {

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

  class gtocX_2burn_pars : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[7];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DGreaterThan ray_positive;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    gtocX_2burn_pars( gtocX_2burn_pars const & );
    gtocX_2burn_pars const & operator = ( gtocX_2burn_pars const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    void continuation_step_0( real_type s );
    void continuation_step_1( real_type s );

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

    GTOCX_2BURN_PARS_API_DLL
    explicit
    gtocX_2burn_pars(
      string  const & name,
      ThreadPool    * TP,
      Console const * console
    );

    ~gtocX_2burn_pars() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "gtocX_2burn_pars"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    GTOCX_2BURN_PARS_API_DLL
    void
    setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    GTOCX_2BURN_PARS_API_DLL real_type cont                ( real_type xo__s, real_type xo__eps0, real_type xo__eps1 ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_position_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_position_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_position_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type x_velocity_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type y_velocity_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity          ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_1    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_1_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_2    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_2_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3_3    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_3_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_4      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_4_4    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_4_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_4_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_4_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_5      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_5_5    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_5_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_5_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_6      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_6_6    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_6_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_7      ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type z_velocity_D_7_7    ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg            ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_1        ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_1_1      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_1_2      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_1_3      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_2        ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_2_2      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_2_3      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_3        ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type norm_reg_D_3_3      ( real_type xo__x, real_type xo__y, real_type xo__z ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray                 ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_1             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_1_1           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_1_2           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_1_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_1_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_2             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_2_2           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_2_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_2_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_3             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_3_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_3_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_4             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type ray_D_4_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel                 ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1_1           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1_2           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_1_5           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_2             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_2_2           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_2_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_2_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_2_5           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_3             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_3_3           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_3_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_3_5           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_4             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_4_4           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_4_5           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_5             ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vel_D_5_5           ( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vc                  ( real_type xo__r ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vc_D                ( real_type xo__r ) const;
    GTOCX_2BURN_PARS_API_DLL real_type vc_DD               ( real_type xo__r ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r      ( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r_D_1  ( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r_D_1_1( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r_D_1_2( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r_D_2  ( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type acceleration_r_D_2_2( real_type xo__r, real_type xo__muS ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_begin             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_begin_D           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_begin_DD          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_begin             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_begin_D           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_begin_DD          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_begin             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_begin_D           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_begin_DD          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_begin            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_begin_D          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_begin_DD         ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_begin            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_begin_D          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_begin_DD         ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_begin            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_begin_D          ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_begin_DD         ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_end               ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_end_D             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type X_end_DD            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_end               ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_end_D             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Y_end_DD            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_end               ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_end_D             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type Z_end_DD            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_end              ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_end_D            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VX_end_DD           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_end              ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_end_D            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VY_end_DD           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_end              ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_end_D            ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type VZ_end_DD           ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type p_guess             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type f_guess             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type g_guess             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type h_guess             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type k_guess             ( real_type xo__t ) const;
    GTOCX_2BURN_PARS_API_DLL real_type L_guess             ( real_type xo__t, real_type xo__t0 ) const;
    GTOCX_2BURN_PARS_API_DLL real_type guess_setup         ( ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    GTOCX_2BURN_PARS_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    GTOCX_2BURN_PARS_API_DLL
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

namespace gtocX_2burn_parsLoad {
  using gtocX_2burn_parsDefine::gtocX_2burn_pars;

}

#endif

// EOF: gtocX_2burn_pars.hh