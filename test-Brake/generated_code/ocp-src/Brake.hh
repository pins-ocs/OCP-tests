/*-----------------------------------------------------------------------*\
 |  file: Brake.hh                                                       |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef BRAKE_DOT_HH
#define BRAKE_DOT_HH

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
  #ifndef BRAKE_API_DLL
    #ifdef BRAKE_EXPORT
      #define BRAKE_API_DLL __declspec(dllexport)
    #elif defined(BRAKE_IMPORT)
      #define BRAKE_API_DLL __declspec(dllimport)
    #else
      #define BRAKE_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define BRAKE_API_DLL
#endif

#define OCP_VIRTUAL          override
#define INDIRECT_OCP_VIRTUAL override

namespace BrakeDefine {

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

  using Mechatronix::X_p_type;
  using Mechatronix::L_p_type;
  using Mechatronix::Z_p_type;
  using Mechatronix::U_p_type;
  using Mechatronix::MU_p_type;
  using Mechatronix::V_p_type;
  using Mechatronix::Q_p_type;
  using Mechatronix::P_p_type;
  using Mechatronix::OMEGA_p_type;
  using Mechatronix::OMEGA_full_p_type;

  using Mechatronix::X_const_p_type;
  using Mechatronix::L_const_p_type;
  using Mechatronix::Z_const_p_type;
  using Mechatronix::U_const_p_type;
  using Mechatronix::MU_const_p_type;
  using Mechatronix::V_const_p_type;
  using Mechatronix::Q_const_p_type;
  using Mechatronix::P_const_p_type;
  using Mechatronix::OMEGA_const_p_type;
  using Mechatronix::OMEGA_full_const_p_type;

  using Mechatronix::NodeQX;
  using Mechatronix::NodeQXL;

  using Mechatronix::MatrixWrapper;

  using GenericContainerNamespace::GenericContainer;

  class Brake : public Mechatronix::Discretized_Indirect_OCP {

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[7];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints LT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    Brake( Brake const & );
    Brake const & operator = ( Brake const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;
    using Mechatronix::Discretized_Indirect_OCP::num_active_BC;

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

    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_nnz;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_pattern;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2_values;
    using Mechatronix::Discretized_Indirect_OCP::eval_JF2;

    using Mechatronix::Discretized_Indirect_OCP::get_solution;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_spline;
    using Mechatronix::Discretized_Indirect_OCP::get_solution_as_guess;

    using Mechatronix::Indirect_OCP::setup_BC;

    BRAKE_API_DLL
    explicit
    Brake(
      string  const  & name,
      Console const  * console,
      ThreadPoolBase * TP
    );

    ~Brake() override;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Begin: User Definitions
    // End: User Definitions

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    char const * model_name() const override
    { return "Brake"; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void info_classes() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    BRAKE_API_DLL
    void setup_parameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_parameters( real_const_ptr Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void
    update_parameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_user_classes( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_user_mapped_functions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_controls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BRAKE_API_DLL
    void setup_pointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)
    BRAKE_API_DLL real_type guess_x            ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_x_D          ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_x_DD         ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_v            ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_v_D          ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_v_DD         ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda1      ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda1_D    ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda1_DD   ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda2      ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda2_D    ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_lambda2_DD   ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_u            ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_u_D          ( real_type xo__s ) const;
    BRAKE_API_DLL real_type guess_u_DD         ( real_type xo__s ) const;

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    BRAKE_API_DLL
    void setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    BRAKE_API_DLL
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

namespace BrakeLoad {
  using BrakeDefine::Brake;

}

#endif

// EOF: Brake.hh
