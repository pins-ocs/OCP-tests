/*-----------------------------------------------------------------------*\
 |  file: CNOC_dll_pins.hh                                               |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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

#include "CNOC.hh"
#include "CNOC_Pars.hh"

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


namespace CNOCDefine {

    using namespace std;
  using Mechatronix::real_type;
  using Mechatronix::integer;
  using Mechatronix::ostream_type;

  // user class in namespaces
  using Mechatronix::ToolPath2D;

  using namespace CNOCLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #ifndef MECHATRONIX_OS_WINDOWS
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class CNOC_Problem {

    CNOC       model;

    // user defined Object instances (external)

    ToolPath2D toolPath2D;

    // block copy constructor
    CNOC_Problem( CNOC_Problem const & );
    CNOC_Problem const & operator = ( CNOC_Problem const & );

    // stored solution
    Splines::SplineSet splines;
    GenericContainer   gc_solution;

  public:

    CNOC_API_DLL
    CNOC_Problem( ThreadPool * pTP, Console * pConsole )
    : model("CNOC",pTP,pConsole)
    , toolPath2D( "toolPath2D" )
    {
      Mechatronix::activate_ctrlC();
    }

    CNOC_API_DLL
    ~CNOC_Problem()
    {}

    CNOC_API_DLL
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
        toolPath2D.setup(gc_data("ToolPath2D"));
        ptrs[ "pToolPath2D" ] = &toolPath2D;

        model.setup( gc_data );
        ok    = true;
        error = "no error";
      }
      catch ( exception const & exc ) {
        error = exc.what();
      }
      catch ( char const exc[] ) {
        error = exc;
      }
      catch (...) {
        error = "CNOC::solver, fatal: unknown error";
      }
      return ok;
    }

    CNOC_API_DLL
    void
    guess( GenericContainer const & gc_guess ) {
      model.guess( gc_guess );
    }

    CNOC_API_DLL
    bool
    solve() {
      bool ok = model.solve();
      model.get_solution( gc_solution );
      model.get_solution_as_spline( splines );
      return ok;
    }

    CNOC_API_DLL
    GenericContainer const &
    getSolution()
    { return gc_solution; }

    CNOC_API_DLL
    void
    diagnostic( GenericContainer & gc_data )
    { return model.diagnostic( gc_data ); }

    CNOC_API_DLL
    integer
    numSplines() const
    { return splines.numSplines(); }

    // get the column of spline labelled `hdr`
    CNOC_API_DLL
    integer
    spline_getPosition( char const * hdr ) const
    { return splines.getPosition(hdr); }

    CNOC_API_DLL
    real_type
    spline_min( integer ipos ) const
    { return splines.yMin( ipos );}

    CNOC_API_DLL
    real_type
    spline_max( integer ipos ) const
    { return splines.yMax( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    CNOC_API_DLL
    bool
    spline_isMonotone( integer ipos ) const
    { return splines.isMonotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    CNOC_API_DLL
    char const *
    spline_header( integer ipos ) const
    { return splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    CNOC_API_DLL
    void
    spline_eval( real_type val, vector<real_type> & values ) const
    { return splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    CNOC_API_DLL
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
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_ocp_setup( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_ocp_guess( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_ocp_solve( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_write_ocp_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_ocp_solution_range( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  mrb_value
  mrb_CNOC_ocp_eval_solution( mrb_state *mrb, mrb_value self );

  EXTERN_C
  CNOC_API_DLL
  void
  mrb_libCNOC_gem_init( mrb_state* mrb );

  EXTERN_C
  CNOC_API_DLL
  void
  mrb_libCNOC_gem_final( mrb_state* mrb );

}

// EOF: CNOC_dll_pins.hh
