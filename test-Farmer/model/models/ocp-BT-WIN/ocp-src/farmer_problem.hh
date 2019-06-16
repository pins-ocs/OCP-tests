/*-----------------------------------------------------------------------*\
 |  file: farmer_problem.hh                                              |
 |                                                                       |
 |  version: 1.0   date 16/6/2019                                        |
 |                                                                       |
 |  Copyright (C) 2019                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef FARMER_PROBLEM_HH
#define FARMER_PROBLEM_HH

// Mechatronix Headers
#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>

// user headers
#include <MechatronixCore/MechatronixCore.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef FARMER_PROBLEM_API_DLL
    #ifdef FARMER_PROBLEM_EXPORT
      #define FARMER_PROBLEM_API_DLL __declspec(dllexport)
    #elif defined(FARMER_PROBLEM_IMPORT)
      #define FARMER_PROBLEM_API_DLL __declspec(dllimport)
    #else
      #define FARMER_PROBLEM_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define FARMER_PROBLEM_API_DLL
#endif

namespace farmer_problemDefine {

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

  using Mechatronix::X_const_pointer_type;
  using Mechatronix::L_const_pointer_type;
  using Mechatronix::Z_const_pointer_type;
  using Mechatronix::U_const_pointer_type;
  using Mechatronix::V_const_pointer_type;
  using Mechatronix::Q_const_pointer_type;
  using Mechatronix::P_const_pointer_type;
  using Mechatronix::OMEGA_const_pointer_type;

  using Mechatronix::MatrixWrapper;

  using GenericContainerNamespace::GenericContainer;

  class farmer_problem : public Mechatronix::Discretized_Indirect_OCP {

    // solver classes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::NonlinearSolverBase * pSolver;

    // redirect output to a string in GenericContainer - - - - - - - - - - - - -
    bool         redirectToGC;
    bool         u_solve_iterative;
    stringstream ss_redirected_stream;

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    real_type ModelPars[23];

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyU x1__oControl;
    Mechatronix::PenaltyU x2__oControl;
    Mechatronix::PenaltyU x3__oControl;
    Mechatronix::PenaltyU x4__oControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::Penalty1DGreaterThan LimitX2X4;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    farmer_problem( farmer_problem const & );
    farmer_problem const & operator = ( farmer_problem const & );

    // subclass for continuation - - - - - - - - - - - - - - - - - - - - - - - -
    integer ns_continuation_begin;
    integer ns_continuation_end;

    FARMER_PROBLEM_API_DLL
    void
    get_solution_base( GenericContainer & gc_solution );

  public:

    using Mechatronix::Discretized_Indirect_OCP::setup;
    using Mechatronix::Discretized_Indirect_OCP::guess;

    using Mechatronix::Discretized_Indirect_OCP::omegaInvMap;
    using Mechatronix::Discretized_Indirect_OCP::omegaMap;
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

    FARMER_PROBLEM_API_DLL
    explicit
    farmer_problem(
      string const & name,
      ostream_type * _pCout,
      integer        _infoLevel
    );

    FARMER_PROBLEM_API_DLL virtual
    ~farmer_problem();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    changeInfoLevel( integer info ) {
      Mechatronix::Discretized_Indirect_OCP::infoLevel = info;
      pSolver->changeInfoLevel(info);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    changeStream( ostream_type * _pCout ) {
      Mechatronix::Discretized_Indirect_OCP::pCout = _pCout;
      pSolver->changeStream(_pCout);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    infoClasses( ostream_type & stream ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    FARMER_PROBLEM_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupParameters( real_type const Pars[] );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    updateParameter( real_type val, integer idx )
    { ModelPars[idx] = val; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupBC( GenericContainer const & bc )
    { Indirect_OCP::setupBC( bc ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    setupBC( bool isActive[] )
    { Indirect_OCP::setupBC( isActive ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    FARMER_PROBLEM_API_DLL
    void
    setup( GenericContainer const & gc );

    /* --------------------------------------------------------------------------
    //    ____
    //   / ___|_   _  ___  ___ ___
    //  | |  _| | | |/ _ \/ __/ __|
    //  | |_| | |_| |  __/\__ \__ \
    //   \____|\__,_|\___||___/___/
    */
    // set initial solution of the nonlinear system
    FARMER_PROBLEM_API_DLL
    void
    guess( GenericContainer const & gc_guess ) {
      this->guess( gc_guess, pSolver->solution() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // solve nonlinear system
    FARMER_PROBLEM_API_DLL
    bool
    solve();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // store the solution
    FARMER_PROBLEM_API_DLL
    void
    get_solution( GenericContainer & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    get_solution_as_spline( Splines::SplineSet & SplineSet );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    get_solution_as_guess( GenericContainer & gc_guess );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // do some check on the computed solution
    FARMER_PROBLEM_API_DLL
    void
    diagnostic( GenericContainer const & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    eval_F( real_type const x[], real_type f[] )
    { this->evaluateFunction( x, f ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    integer
    eval_JF_nnz() const
    { return this->sparseNnz(); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    eval_JF_pattern( integer i[], integer j[], integer offs ) const
    { this->sparsePattern( i, j, offs ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    eval_JF_values( real_type const x[], real_type vals[] ) {
      this->loadJacobian( x );
      this->sparseValues( vals );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    eval_F( GenericContainer const & gc_x, GenericContainer & gc_F ) {
      GenericContainer::vec_real_type const & x = gc_x.get_vec_real();
      integer neq = numEquations();
      ASSERT(
        x.size() == size_t(neq),
        "farmer_problem::eval_F, x.size() = " << x.size() <<
        " must be of size neq = " << neq
      );
      GenericContainer::vec_real_type & f = gc_F.set_vec_real(unsigned(neq));
      evaluateFunction( &x.front(), &f.front() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    eval_JF(
      GenericContainer const & gc_x,
      GenericContainer       & gc_F,
      integer                  offs
    ) {
      GenericContainer::vec_real_type const & x = gc_x.get_vec_real();
      integer neq = numEquations();
      ASSERT(
        x.size() == size_t(neq),
        "farmer_problem::eval_JF, x.size() = " << x.size() <<
        " must be of size neq = " << neq
      );

      this->loadJacobian( &x.front() );
      GenericContainer & gc_i = gc_F["i_row"];
      GenericContainer & gc_j = gc_F["j_col"];
      GenericContainer & gc_v = gc_F["values"];
      integer nnz = this->sparseNnz();
      gc_F["nnz"] = nnz;
      gc_F["neq"] = neq;
      GenericContainer::vec_int_type  & i_vec = gc_i.set_vec_int( unsigned(nnz) );
      GenericContainer::vec_int_type  & j_vec = gc_j.set_vec_int( unsigned(nnz) );
      GenericContainer::vec_real_type & v_vec = gc_v.set_vec_real( unsigned(nnz) );

      this->sparsePattern( &i_vec.front(), &j_vec.front(), offs );
      this->sparseValues( &v_vec.front() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    get_raw_solution( real_type x[] ) const {
      std::copy_n( pSolver->solution(), this->numEquations(), x );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    void
    set_raw_solution( real_type const x[] ) {
      std::copy_n( x, this->numEquations(), pSolver->solution() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    FARMER_PROBLEM_API_DLL
    bool
    check_raw_solution( real_type const x[] ) {
      try {
        this->checkIfAdmissible( x );
      }
      catch ( exception const & exc ) {
        std::cerr << MSG_ERROR( exc.what() ) << '\n';
        return false;
      }
      catch ( char const exc[] ) {
        std::cerr << MSG_ERROR( exc ) << '\n';
        return false;
      } catch (...) {
        return false;
      }
      return true;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    FARMER_PROBLEM_API_DLL
    void
    updateContinuation( integer phase, real_type s );

    // save model parameters
    FARMER_PROBLEM_API_DLL
    virtual
    void
    save_OCP_info( GenericContainer & gc ) const;

  };
}

namespace farmer_problemLoad {
  using farmer_problemDefine::farmer_problem;

}

#endif

// EOF: farmer_problem.hh
