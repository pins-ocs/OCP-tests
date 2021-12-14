/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_dll_ruby.hh                              |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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


namespace LUUS_DrugDisplacementDefine {

    using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;

  using namespace LUUS_DrugDisplacementLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #if !defined(MECHATRONIX_OS_WINDOWS) && !defined(MECHATRONIX_OS_MINGW)
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class LUUS_DrugDisplacement_Problem {

    LUUS_DrugDisplacement model;

    // user defined Object instances (external)
    MeshStd    mesh;

    // block copy constructor
    LUUS_DrugDisplacement_Problem( LUUS_DrugDisplacement_Problem const & );
    LUUS_DrugDisplacement_Problem const & operator = ( LUUS_DrugDisplacement_Problem const & );

    // stored solution
    Splines::SplineSet splines;
    GenericContainer   gc_solution;

  public:

    LUUS_DRUGDISPLACEMENT_API_DLL
    LUUS_DrugDisplacement_Problem( ThreadPool * TP, Console const * console )
    : model("LUUS_DrugDisplacement",TP,console)
    , mesh( "mesh" )
    {
      Mechatronix::activate_ctrlC();
    }

    LUUS_DRUGDISPLACEMENT_API_DLL
    ~LUUS_DrugDisplacement_Problem()
    {}

    LUUS_DRUGDISPLACEMENT_API_DLL
    bool
    setup( GenericContainer & gc_data, string & error ) {
      bool ok = true;
      try {
        /*
        // User object classes passed as pointers are initialized outside
        // the setup. In ruby interface are initialized here.
        */
        GenericContainer & ptrs = gc_data["Pointers"];
        // setup user object classes
        mesh.setup(gc_data("Mesh"));
        ptrs[ "pMesh" ] = &mesh;

        model.setup( gc_data );
      }
      catch ( std::exception const & exc ) {
        error = exc.what();
        ok    = false;
      }
      catch ( char const exc[] ) {
        error = exc;
        ok    = false;
      }
      catch (...) {
        error = "LUUS_DrugDisplacement::solver, fatal: unknown error";
        ok    = false;
      }
      return ok;
    }

    LUUS_DRUGDISPLACEMENT_API_DLL
    void
    guess( GenericContainer & gc_data ) {
      model.guess( gc_data );
    }

    LUUS_DRUGDISPLACEMENT_API_DLL
    bool
    solve() {
      bool ok = model.solve();
      model.get_solution( gc_solution );
      model.get_solution_as_spline( splines );
      return ok;
    }

    LUUS_DRUGDISPLACEMENT_API_DLL
    GenericContainer const &
    getSolution()
    { return gc_solution; }

    LUUS_DRUGDISPLACEMENT_API_DLL
    void
    diagnostic( GenericContainer const & gc_data, GenericContainer & gc_solution )
    { return model.diagnostic( gc_data, gc_solution ); }

    LUUS_DRUGDISPLACEMENT_API_DLL
    integer
    numSplines() const
    { return splines.numSplines(); }

    // get the column of spline labelled `hdr`
    LUUS_DRUGDISPLACEMENT_API_DLL
    integer
    spline_getPosition( char const * hdr ) const
    { return splines.getPosition(hdr); }

    LUUS_DRUGDISPLACEMENT_API_DLL
    real_type
    spline_min( integer ipos ) const
    { return splines.yMin( ipos );}

    LUUS_DRUGDISPLACEMENT_API_DLL
    real_type
    spline_max( integer ipos ) const
    { return splines.yMax( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    LUUS_DRUGDISPLACEMENT_API_DLL
    bool
    spline_isMonotone( integer ipos ) const
    { return splines.isMonotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    LUUS_DRUGDISPLACEMENT_API_DLL
    char const *
    spline_header( integer ipos ) const
    { return splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    LUUS_DRUGDISPLACEMENT_API_DLL
    void
    spline_eval( real_type val, vector<real_type> & values ) const
    { return splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    LUUS_DRUGDISPLACEMENT_API_DLL
    void
    spline_eval2(
      integer             ipos,
      real_type           val,
      vector<real_type> & values
    ) const {
      return splines.eval2(ipos,val,values);
    }
  };

  /*
  ::  ____        _             _____ _____ ___
  :: |  _ \ _   _| |__  _   _  |  ___|  ___|_ _|
  :: | |_) | | | | '_ \| | | | | |_  | |_   | |
  :: |  _ <| |_| | |_) | |_| | |  _| |  _|  | |
  :: |_| \_\\__,_|_.__/ \__, | |_|   |_|   |___|
  ::                    |___/
  ::  ___       _             __
  :: |_ _|_ __ | |_ ___ _ __ / _| __ _  ___ ___
  ::  | || '_ \| __/ _ \ '__| |_ / _` |/ __/ _ \
  ::  | || | | | ||  __/ |  |  _| (_| | (_|  __/
  :: |___|_| |_|\__\___|_|  |_|  \__,_|\___\___|
  */

  EXTERN_C
  LUUS_DRUGDISPLACEMENT_API_DLL
  bool
  LUUS_DrugDisplacement_ocp_setup( char const id[], GenericContainer & gc_data );

  EXTERN_C
  LUUS_DRUGDISPLACEMENT_API_DLL
  bool
  LUUS_DrugDisplacement_ocp_guess( char const id[], GenericContainer & gc_guess );

  EXTERN_C
  LUUS_DRUGDISPLACEMENT_API_DLL
  bool
  LUUS_DrugDisplacement_ocp_solve( char const id[],
                                   GenericContainer & gc_data,
                                   GenericContainer & gc_solution );

  EXTERN_C
  LUUS_DRUGDISPLACEMENT_API_DLL
  void
  LUUS_DrugDisplacement_write_ocp_solution( char const id[], char const fname[] );

}

// EOF: LUUS_DrugDisplacement_dll_ruby.hh