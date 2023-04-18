/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_dll_pins.hh                                       |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wc99-extensions"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wclass-varargs"
#endif
#ifdef _MSC_VER
#pragma warning( disable : 4200 )
#endif


#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>
#include <MechatronixInterfaceMruby/mruby_include.hh>

#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#endif

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif


namespace stirred_tankDefine {

    using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;

  using namespace stirred_tankLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #if !defined(MECHATRONIX_OS_WINDOWS) && !defined(MECHATRONIX_OS_MINGW)
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class stirred_tank_Problem {

    stirred_tank m_model;

    // user defined Object instances (external)

    MeshStd    mesh;

    // block copy constructor
    stirred_tank_Problem( stirred_tank_Problem const & );
    stirred_tank_Problem const & operator = ( stirred_tank_Problem const & );

    // stored solution
    Splines::SplineSet m_splines;
    GenericContainer   m_gc_solution;

  public:

    STIRRED_TANK_API_DLL
    stirred_tank_Problem(
      Console const  * console,
      ThreadPoolBase * TP
    )
    : m_model("stirred_tank",console,TP)
    , mesh( "mesh" )
    {
      Mechatronix::activate_ctrlC();
    }

    STIRRED_TANK_API_DLL
    ~stirred_tank_Problem()
    {}

    STIRRED_TANK_API_DLL
    bool
    setup( GenericContainer & gc_data, string & error ) {
      bool ok = false;
      error = "unknown error";
      try {
        /*
        // User object classes passed as pointers
        // are initialized outside the setup.
        // In mruby interface are initialized here.
        */
        GenericContainer & ptrs = gc_data["Pointers"];
        // setup user object classes
        mesh.setup(gc_data("Mesh"));
        ptrs[ "pMesh" ] = &mesh;

        m_model.setup( gc_data );
        ok    = true;
        error = "no error";
      }
      catch ( std::exception const & exc ) {
        error = exc.what();
      }
      catch ( char const exc[] ) {
        error = exc;
      }
      catch (...) {
        error = "stirred_tank::solver, fatal: unknown error";
      }
      return ok;
    }

    STIRRED_TANK_API_DLL
    void
    guess( GenericContainer const & gc_guess ) {
      m_model.guess( gc_guess );
      integer level = 2;
      m_model.info_model( level );
    }

    STIRRED_TANK_API_DLL
    bool
    solve() {
      bool ok = m_model.solve();
      m_model.get_solution( m_gc_solution );
      m_model.get_solution_as_spline( m_splines );
      return ok;
    }

    STIRRED_TANK_API_DLL
    GenericContainer const &
    getSolution()
    { return m_gc_solution; }

    STIRRED_TANK_API_DLL
    void
    diagnostic( GenericContainer const & gc_data, GenericContainer & gc_solution )
    { return m_model.diagnostic( gc_data, gc_solution ); }

    STIRRED_TANK_API_DLL
    integer
    numSplines() const
    { return m_splines.num_splines(); }

    // get the column of spline labelled `hdr`
    STIRRED_TANK_API_DLL
    integer
    spline_getPosition( char const * hdr ) const
    { return m_splines.get_position(hdr); }

    STIRRED_TANK_API_DLL
    real_type
    spline_min( integer ipos ) const
    { return m_splines.y_min( ipos );}

    STIRRED_TANK_API_DLL
    real_type
    spline_max( integer ipos ) const
    { return m_splines.y_max( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    STIRRED_TANK_API_DLL
    bool
    spline_isMonotone( integer ipos ) const
    { return m_splines.is_monotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    STIRRED_TANK_API_DLL
    char const *
    spline_header( integer ipos ) const
    { return m_splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    STIRRED_TANK_API_DLL
    void
    spline_eval( real_type val, vector<real_type> & values ) const
    { return m_splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    STIRRED_TANK_API_DLL
    void
    spline_eval2( integer ipos, real_type val, vector<real_type> & values ) const
    { return m_splines.eval2(ipos,val,values); }

  };

  /*
  ::         _             _       _             __
  ::   _ __ (_)_ __  ___  (_)_ __ | |_ ___ _ __ / _| __ _  ___ ___
  ::  | '_ \| | '_ \/ __| | | '_ \| __/ _ \ '__| |_ / _` |/ __/ _ \
  ::  | |_) | | | | \__ \ | | | | | ||  __/ |  |  _| (_| | (_|  __/
  ::  | .__/|_|_| |_|___/ |_|_| |_|\__\___|_|  |_|  \__,_|\___\___|
  ::  |_|
  */

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_ocp_setup( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_ocp_guess( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_ocp_solve( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_write_ocp_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_ocp_solution_range( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  mrb_value
  mrb_stirred_tank_ocp_eval_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  STIRRED_TANK_API_DLL
  void
  mrb_libstirred_tank_gem_init( mrb_state* mrb );

  EXTERN_C
  STIRRED_TANK_API_DLL
  void
  mrb_libstirred_tank_gem_final( mrb_state* mrb );

}

// EOF: stirred_tank_dll_pins.hh
