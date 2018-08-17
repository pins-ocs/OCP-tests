/*-----------------------------------------------------------------------*\
 |  file: PathConstrained_dll_ruby.hh                                    |
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


#ifdef __GCC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wc99-extensions"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wclass-varargs"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdocumentation"
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


#include "PathConstrained.hh"
#include "PathConstrained_Pars.hh"

#ifdef MECHATRONIX_OS_WINDOWS
  //#pragma comment(lib, "IPHLPAPI.lib")
  //#pragma comment(lib, "ws2_32.lib")
  //#pragma comment(lib, "Shlwapi.lib")
  //#pragma comment(lib, "Advapi32.lib")
  //#pragma comment(lib, "Shell32.lib")
  //#pragma comment(lib, "kernel32.lib")
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#endif

#ifdef __GCC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif


namespace PathConstrainedDefine {

  using namespace std;
using namespace MechatronixCommon;

// user class in namespaces
using Mechatronix::MeshStd;

  using namespace PathConstrainedLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #ifndef MECHATRONIX_OS_WINDOWS
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class PathConstrained_Problem {

    PathConstrained model;

    // user defined Object instances (external)
    MeshStd    mesh;

    // block copy constructor
    PathConstrained_Problem( PathConstrained_Problem const & );
    PathConstrained_Problem const & operator = ( PathConstrained_Problem const & );

    // stored solution
    Splines::SplineSet splines;
    GenericContainer   gc_solution;

  public:

    PATHCONSTRAINED_API_DLL
    PathConstrained_Problem( std::basic_ostream<char> * pCout, indexType infoLevel )
    : model("PathConstrained",pCout,infoLevel)
    , mesh( "mesh" )
    {
      activate_ctrlC();
    }

    PATHCONSTRAINED_API_DLL
    ~PathConstrained_Problem()
    {}

    PATHCONSTRAINED_API_DLL
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
      catch ( exception const & exc ) {
        error = exc.what();
        ok    = false;
      }
      catch ( char const exc[] ) {
        error = exc;
        ok    = false;
      }
      catch (...) {
        error = "PathConstrained::solver, fatal: unknown error";
        ok    = false;
      }
      return ok;
    }

    PATHCONSTRAINED_API_DLL
    void
    guess( GenericContainer & gc_data ) {
      model.guess( gc_data );
    }

    PATHCONSTRAINED_API_DLL
    bool
    solve() {
      bool ok = model.solve();
      model.get_solution( gc_solution, splines );
      return ok;
    }

    PATHCONSTRAINED_API_DLL
    GenericContainer const &
    getSolution()
    { return gc_solution; }

    PATHCONSTRAINED_API_DLL
    void
    diagnostic( GenericContainer & gc_data )
    { return model.diagnostic( gc_data ); }

    PATHCONSTRAINED_API_DLL
    indexType
    numSplines() const
    { return splines.numSplines(); }

    // get the column of spline labelled `hdr`
    PATHCONSTRAINED_API_DLL
    indexType
    spline_getPosition( char const * hdr ) const
    { return splines.getPosition(hdr); }

    PATHCONSTRAINED_API_DLL
    valueType
    spline_min( indexType ipos ) const
    { return splines.yMin( ipos );}

    PATHCONSTRAINED_API_DLL
    valueType
    spline_max( indexType ipos ) const
    { return splines.yMax( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    PATHCONSTRAINED_API_DLL
    bool
    spline_isMonotone( indexType ipos ) const
    { return splines.isMonotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    PATHCONSTRAINED_API_DLL
    char const *
    spline_header( indexType ipos ) const
    { return splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    PATHCONSTRAINED_API_DLL
    void
    spline_eval( valueType val, vector<valueType> & values ) const
    { return splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    PATHCONSTRAINED_API_DLL
    void
    spline_eval2( indexType ipos, valueType val, vector<valueType> & values ) const
    { return splines.eval2(ipos,val,values); }

    PATHCONSTRAINED_API_DLL
    void
    changeInfoLevel( indexType infoLevel )
    { model.changeInfoLevel(infoLevel); }

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
  PATHCONSTRAINED_API_DLL
  bool
  PathConstrained_ocp_setup( char const id[],
                              GenericContainer & gc_data );

  EXTERN_C
  PATHCONSTRAINED_API_DLL
  bool
  PathConstrained_ocp_guess( char const id[],
                              GenericContainer & gc_data );

  EXTERN_C
  PATHCONSTRAINED_API_DLL
  bool
  PathConstrained_ocp_solve( char const id[],
                             GenericContainer & gc_data,
                             GenericContainer & gc_solution );

  EXTERN_C
  PATHCONSTRAINED_API_DLL
  void
  PathConstrained_write_ocp_solution( char const id[], char const fname[] );

}

// EOF: PathConstrained_dll_ruby.hh
