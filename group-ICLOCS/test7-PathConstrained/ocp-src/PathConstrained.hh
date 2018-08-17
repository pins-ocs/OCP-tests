/*-----------------------------------------------------------------------*\
 |  file: PathConstrained.hh                                             |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef PATHCONSTRAINED_HH
#define PATHCONSTRAINED_HH

// Macro definition to use Mechatronix Classes:
// - MechatronixRoad namespace
// - MechatronixVehicle namespace: it includes Tyre Class and Engine Class
// User has to uncomment each macro definition to use appropriate class

#define MECHATRONIX_U_ITERATIVE
// Mechatronix Headers
#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixSolver/MechatronixSolver.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>

// user headers
#include <MechatronixCore/MechatronixCore.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef PATHCONSTRAINED_API_DLL
    #ifdef PATHCONSTRAINED_EXPORT
      #define PATHCONSTRAINED_API_DLL __declspec(dllexport)
    #elif defined(PATHCONSTRAINED_IMPORT)
      #define PATHCONSTRAINED_API_DLL __declspec(dllimport)
    #else
      #define PATHCONSTRAINED_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define PATHCONSTRAINED_API_DLL
#endif

namespace PathConstrainedDefine {

  using namespace std;
  using namespace MechatronixCommon;

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
  using Mechatronix::Q_pointer_type;
  using Mechatronix::P_pointer_type;
  using Mechatronix::OMEGA_pointer_type;

  using Mechatronix::X_const_pointer_type;
  using Mechatronix::L_const_pointer_type;
  using Mechatronix::Z_const_pointer_type;
  using Mechatronix::U_const_pointer_type;
  using Mechatronix::Q_const_pointer_type;
  using Mechatronix::P_const_pointer_type;
  using Mechatronix::OMEGA_const_pointer_type;

  using GenericContainerNamespace::GenericContainer;

  class PathConstrained : public Mechatronix::Discretized_Indirect_OCP {

    // solver classes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //Mechatronix::Hyness       solver;
    Mechatronix::NewtonDumped solver;
    string                    lastError;

    // redirect output to a string in GenericContainer - - - - - - - - - - - - -
    bool         redirectToGC;
    stringstream ss_redirected_stream;

    // Model Paramaters  - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Controls  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::PenaltyU uControl;

    // Constraints 1D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::Penalty1DGreaterThan x2bound;

    // Constraints 2D  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User mapped functions - - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (internal) - - - - - - - - - - - - - - - - - - - - - - - - -

    // User classes (external) - - - - - - - - - - - - - - - - - - - - - - - - -
    Mechatronix::MeshStd * pMesh;

    // block copy constructor  - - - - - - - - - - - - - - - - - - - - - - - - -
    PathConstrained( PathConstrained const & );
    PathConstrained const & operator = ( PathConstrained const & );


    PATHCONSTRAINED_API_DLL
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

    PATHCONSTRAINED_API_DLL
    explicit
    PathConstrained( string const             & name,
                     std::basic_ostream<char> * _pCout,
                     indexType                  _infoLevel );

    PATHCONSTRAINED_API_DLL virtual
    ~PathConstrained();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    changeInfoLevel( indexType info ) {
      Mechatronix::Discretized_Indirect_OCP::infoLevel = info;
      solver.changeInfoLevel(info);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    changeStream( std::basic_ostream<char> * _pCout ) {
      Mechatronix::Discretized_Indirect_OCP::pCout = _pCout;
      solver.changeStream(_pCout);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    infoClasses( basic_ostream<char> & stream ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (raccolti in setup( gc ))
    PATHCONSTRAINED_API_DLL
    void
    setupParameters( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupParameters( valueConstPointer Pars );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    updateParameter( valueType, indexType )
    { } // no parameters to modify!

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupUserClasses( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupUserMappedFunctions( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupControls( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupPointers( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupBC( GenericContainer const & bc )
    { Indirect_OCP::setupBC( bc ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    setupBC( bool isActive[] )
    { Indirect_OCP::setupBC( isActive ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // user functions prototype (with derivative)

    #include <MechatronixSolver/OCP_methods.hxx>
    #include <MechatronixSolver/Indirect_OCP_methods.hxx>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // C++ initializer (all in one)
    PATHCONSTRAINED_API_DLL
    void
    setup( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // set initial solution of the nonlinear system
    PATHCONSTRAINED_API_DLL
    void
    guess( GenericContainer const & gc );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // solve nonlinear system
    PATHCONSTRAINED_API_DLL
    bool
    solve();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // store the solution
    PATHCONSTRAINED_API_DLL
    void
    get_solution( GenericContainer & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    get_solution( GenericContainer   & gc_solution,
                  Splines::SplineSet & splines );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void
    get_names( GenericContainer & out ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // do some check on the computed solution
    PATHCONSTRAINED_API_DLL
    void
    diagnostic( GenericContainer const & gc_solution );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    eval_F( valueConstPointer x, valuePointer f )
    { this->evaluateFunction( x, f ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    indexType
    eval_JF_nnz() const
    { return this->sparseNnz(); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    eval_JF_pattern( indexType i[], indexType j[], indexType offs ) const
    { this->sparsePattern( i, j, offs ); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    eval_JF_values( valueConstPointer x, valuePointer vals ) {
      this->loadJacobian( x );
      this->sparseValues( vals );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    eval_F( GenericContainer const & gc_x, GenericContainer & gc_F ) {
      GenericContainer::vec_real_type const & x = gc_x.get_vec_real();
      sizeType neq = sizeType(numEquations());
      ASSERT( x.size() == neq,
              "PathConstrained::eval_F, x.size() = " << x.size() <<
              " must be of size neq = " << neq );
      GenericContainer::vec_real_type & f = gc_F.set_vec_real(neq);
      evaluateFunction( &x.front(), &f.front() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    eval_JF( GenericContainer const & gc_x,
             GenericContainer       & gc_F,
             indexType                offs ) {
      GenericContainer::vec_real_type const & x = gc_x.get_vec_real();
      sizeType neq = sizeType(numEquations());
      ASSERT( x.size() == neq,
              "PathConstrained::eval_JF, x.size() = " << x.size() <<
              " must be of size neq = " << neq);

      this->loadJacobian( &x.front() );
      GenericContainer & gc_i = gc_F["i_row"];
      GenericContainer & gc_j = gc_F["j_col"];
      GenericContainer & gc_v = gc_F["values"];
      sizeType nnz = sizeType(this->sparseNnz());
      gc_F["nnz"] = nnz;
      gc_F["neq"] = neq;
      GenericContainer::vec_int_type  & i_vec = gc_i.set_vec_int( nnz );
      GenericContainer::vec_int_type  & j_vec = gc_j.set_vec_int( nnz );
      GenericContainer::vec_real_type & v_vec = gc_v.set_vec_real( nnz );

      this->sparsePattern( &i_vec.front(), &j_vec.front(), offs );
      this->sparseValues( &v_vec.front() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    get_raw_solution( valuePointer x ) const {
      std::copy_n( solver.solution(), this->numEquations(), x );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    void
    set_raw_solution( valueConstPointer x ) {
      std::copy_n( x, this->numEquations(), solver.solution() );
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    PATHCONSTRAINED_API_DLL
    bool
    check_raw_solution( valueConstPointer x ) {
      try {
        this->checkIfAdmissible( x );
      }
      catch ( exception const & exc ) {
        cerr << exc.what() << '\n';
        return false;
      }
      catch ( char const exc[] ) {
        cerr << exc << '\n';
        return false;
      } catch (...) {
        return false;
      }
      return true;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Continuation phase update
    PATHCONSTRAINED_API_DLL
    void
    updateContinuation( indexType phase, valueType s );

  };
}

namespace PathConstrainedLoad {
  using PathConstrainedDefine::PathConstrained;
}

#endif

// EOF: PathConstrained.hh
