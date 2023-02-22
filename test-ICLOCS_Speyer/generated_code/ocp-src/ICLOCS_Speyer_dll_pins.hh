/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_Speyer_dll_pins.hh                                      |
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

#include "ICLOCS_Speyer.hh"
#include "ICLOCS_Speyer_Pars.hh"

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


namespace ICLOCS_SpeyerDefine {

    using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;

  using namespace ICLOCS_SpeyerLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #if !defined(MECHATRONIX_OS_WINDOWS) && !defined(MECHATRONIX_OS_MINGW)
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class ICLOCS_Speyer_Problem {

    ICLOCS_Speyer model;

    // user defined Object instances (external)

    MeshStd    mesh;

    // block copy constructor
    ICLOCS_Speyer_Problem( ICLOCS_Speyer_Problem const & );
    ICLOCS_Speyer_Problem const & operator = ( ICLOCS_Speyer_Problem const & );

    // stored solution
    Splines::SplineSet splines;
    GenericContainer   gc_solution;

  public:

    ICLOCS_SPEYER_API_DLL
    ICLOCS_Speyer_Problem(
      Console const  * console,
      ThreadPoolBase * TP
    )
    : model("ICLOCS_Speyer",console,TP)
    , mesh( "mesh" )
    {
      Mechatronix::activate_ctrlC();
    }

    ICLOCS_SPEYER_API_DLL
    ~ICLOCS_Speyer_Problem()
    {}

    ICLOCS_SPEYER_API_DLL
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

        model.setup( gc_data );
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
        error = "ICLOCS_Speyer::solver, fatal: unknown error";
      }
      return ok;
    }

    ICLOCS_SPEYER_API_DLL
    void
    guess( GenericContainer const & gc_guess ) {
      model.guess( gc_guess );
      model.info();
    }

    ICLOCS_SPEYER_API_DLL
    bool
    solve() {
      bool ok = model.solve();
      model.get_solution( gc_solution );
      model.get_solution_as_spline( splines );
      return ok;
    }

    ICLOCS_SPEYER_API_DLL
    GenericContainer const &
    getSolution()
    { return gc_solution; }

    ICLOCS_SPEYER_API_DLL
    void
    diagnostic( GenericContainer const & gc_data, GenericContainer & gc_solution )
    { return model.diagnostic( gc_data, gc_solution ); }

    ICLOCS_SPEYER_API_DLL
    integer
    numSplines() const
    { return splines.numSplines(); }

    // get the column of spline labelled `hdr`
    ICLOCS_SPEYER_API_DLL
    integer
    spline_getPosition( char const * hdr ) const
    { return splines.getPosition(hdr); }

    ICLOCS_SPEYER_API_DLL
    real_type
    spline_min( integer ipos ) const
    { return splines.yMin( ipos );}

    ICLOCS_SPEYER_API_DLL
    real_type
    spline_max( integer ipos ) const
    { return splines.yMax( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    ICLOCS_SPEYER_API_DLL
    bool
    spline_isMonotone( integer ipos ) const
    { return splines.isMonotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    ICLOCS_SPEYER_API_DLL
    char const *
    spline_header( integer ipos ) const
    { return splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    ICLOCS_SPEYER_API_DLL
    void
    spline_eval( real_type val, vector<real_type> & values ) const
    { return splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    ICLOCS_SPEYER_API_DLL
    void
    spline_eval2( integer ipos, real_type val, vector<real_type> & values ) const
    { return splines.eval2(ipos,val,values); }

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
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_ocp_setup( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_ocp_guess( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_ocp_solve( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_write_ocp_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_ocp_solution_range( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  mrb_value
  mrb_ICLOCS_Speyer_ocp_eval_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  void
  mrb_libICLOCS_Speyer_gem_init( mrb_state* mrb );

  EXTERN_C
  ICLOCS_SPEYER_API_DLL
  void
  mrb_libICLOCS_Speyer_gem_final( mrb_state* mrb );

}

// EOF: ICLOCS_Speyer_dll_pins.hh
