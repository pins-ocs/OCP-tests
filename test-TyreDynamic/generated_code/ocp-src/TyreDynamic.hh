/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic.hh                                                 |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


#ifndef TYREDYNAMIC_DOT_HH
#define TYREDYNAMIC_DOT_HH

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
  #ifndef TYREDYNAMIC_API_DLL
    #ifdef TYREDYNAMIC_EXPORT
      #define TYREDYNAMIC_API_DLL __declspec(dllexport)
    #elif defined(TYREDYNAMIC_IMPORT)
      #define TYREDYNAMIC_API_DLL __declspec(dllimport)
    #else
      #define TYREDYNAMIC_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define TYREDYNAMIC_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace TyreDynamicDefine {

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

  class TyreDynamic : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[48];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrierU b__oControl;
    Mechatronix::PenaltyBarrierU p__oControl;

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyBarrier1DLessThan OnlyBrakingRear;
    Mechatronix::PenaltyBarrier1DLessThan OnlyTractionRear;
    Mechatronix::PenaltyBarrier1DLessThan LongSlipRear_min;
    Mechatronix::PenaltyBarrier1DLessThan LongSlipRear_max;
    Mechatronix::PenaltyBarrier1DLessThan v_min;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PositivePartRegularizedWithErf posPart;
    Mechatronix::NegativePartRegularizedWithErf negPart;
    Mechatronix::ClipSuperior clipSup;
    Mechatronix::ClipIntervalWithErf clipInt;
    Mechatronix::SignRegularizedWithErf sign_reg;
    Mechatronix::AbsoluteValueRegularizedWithErf abs_reg;

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    TyreDynamic( TyreDynamic const & );
    TyreDynamic const & operator = ( TyreDynamic const & );

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

    TYREDYNAMIC_API_DLL
    explicit
    TyreDynamic(
      string const   & name,
      integer          n_threads,
      Console const  * console
    );

    ~TyreDynamic() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "TyreDynamic"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    TYREDYNAMIC_API_DLL
    void
    setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    TYREDYNAMIC_API_DLL
    void
    setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    TYREDYNAMIC_API_DLL real_type LongSlipRear      ( real_type xo___V ) const;
    TYREDYNAMIC_API_DLL real_type LongSlipRear_D    ( real_type xo___V ) const;
    TYREDYNAMIC_API_DLL real_type LongSlipRear_DD   ( real_type xo___V ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w          ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w_D_1      ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w_D_1_1    ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w_D_1_2    ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w_D_2      ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type kappa__w_D_2_2    ( real_type xo__v, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type F__x              ( real_type xo__lambda ) const;
    TYREDYNAMIC_API_DLL real_type F__x_D            ( real_type xo__lambda ) const;
    TYREDYNAMIC_API_DLL real_type F__x_DD           ( real_type xo__lambda ) const;
    TYREDYNAMIC_API_DLL real_type p__pos            ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type p__pos_D          ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type p__pos_DD         ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type p__neg            ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type p__neg_D          ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type p__neg_DD         ( real_type xo__p ) const;
    TYREDYNAMIC_API_DLL real_type b__pos            ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type b__pos_D          ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type b__pos_DD         ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type b__neg            ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type b__neg_D          ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type b__neg_DD         ( real_type xo__b ) const;
    TYREDYNAMIC_API_DLL real_type TT__env           ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT__env_D         ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT__env_DD        ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type BT__env           ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type BT__env_D         ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type BT__env_DD        ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT                ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT_D_1            ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT_D_1_1          ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT_D_1_2          ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT_D_2            ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TT_D_2_2          ( real_type xo__p__pos, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB                ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB_D_1            ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB_D_1_1          ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB_D_1_2          ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB_D_2            ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type TB_D_2_2          ( real_type xo__b__neg, real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type Fa                ( real_type xo__v ) const;
    TYREDYNAMIC_API_DLL real_type Fa_D              ( real_type xo__v ) const;
    TYREDYNAMIC_API_DLL real_type Fa_DD             ( real_type xo__v ) const;
    TYREDYNAMIC_API_DLL real_type Ma                ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type Ma_D              ( real_type xo__omega ) const;
    TYREDYNAMIC_API_DLL real_type Ma_DD             ( real_type xo__omega ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    TYREDYNAMIC_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    TYREDYNAMIC_API_DLL
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

namespace TyreDynamicLoad {
  using TyreDynamicDefine::TyreDynamic;

}

#endif

// EOF: TyreDynamic.hh