/*-----------------------------------------------------------------------*\
 |  file: BangBangFclip_dll_ruby.hh                                      |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "BangBangFclip.hh"
#include "BangBangFclip_Pars.hh"

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


namespace BangBangFclipDefine {

    using namespace std;
  using namespace MechatronixLoad;

  // user class in namespaces
  using Mechatronix::MeshStd;

  using namespace BangBangFclipLoad;
  using GenericContainerNamespace::GenericContainer;

  #define EXTERN_C extern "C"

  #include <sstream>

  #if !defined(MECHATRONIX_OS_WINDOWS) && !defined(MECHATRONIX_OS_MINGW)
    #include <signal.h>
    #include <execinfo.h>
  #endif

  class BangBangFclip_Problem {

    BangBangFclip m_model;

    // user defined Object instances (external)
    MeshStd    m_mesh;

    // block copy constructor
    BangBangFclip_Problem( BangBangFclip_Problem const & );
    BangBangFclip_Problem const & operator = ( BangBangFclip_Problem const & );

    // stored solution
    Splines::SplineSet m_splines;
    GenericContainer   m_gc_solution;

  public:

    BANGBANGFCLIP_API_DLL
    BangBangFclip_Problem(
      Console const  * console,
      ThreadPoolBase * TP
    )
    : m_model("BangBangFclip",console,TP)
    , m_mesh( "mesh" )
    {
      Mechatronix::activate_ctrlC();
    }

    BANGBANGFCLIP_API_DLL
    ~BangBangFclip_Problem()
    {}

    BANGBANGFCLIP_API_DLL
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
        m_mesh.setup(gc_data("Mesh"));
        ptrs[ "pMesh" ] = &m_mesh;

        m_model.setup( gc_data );
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
        error = "BangBangFclip::solver, fatal: unknown error";
        ok    = false;
      }
      return ok;
    }

    BANGBANGFCLIP_API_DLL
    void
    guess( GenericContainer & gc_data ) {
      m_model.guess( gc_data );
      m_model.info();
    }

    BANGBANGFCLIP_API_DLL
    bool
    solve() {
      bool ok = m_model.solve();
      m_model.get_solution( m_gc_solution );
      m_model.get_solution_as_spline( m_splines );
      return ok;
    }

    BANGBANGFCLIP_API_DLL
    GenericContainer const &
    getSolution()
    { return m_gc_solution; }

    BANGBANGFCLIP_API_DLL
    void
    diagnostic( GenericContainer const & gc_data, GenericContainer & gc_solution )
    { return m_model.diagnostic( gc_data, gc_solution ); }

    BANGBANGFCLIP_API_DLL
    integer
    numSplines() const
    { return m_splines.numSplines(); }

    // get the column of spline labelled `hdr`
    BANGBANGFCLIP_API_DLL
    integer
    spline_getPosition( char const * hdr ) const
    { return m_splines.getPosition(hdr); }

    BANGBANGFCLIP_API_DLL
    real_type
    spline_min( integer ipos ) const
    { return m_splines.y_min( ipos );}

    BANGBANGFCLIP_API_DLL
    real_type
    spline_max( integer ipos ) const
    { return m_splines.y_max( ipos );}

    // check if spline at column `ipos` is monotone and can be used as independent
    BANGBANGFCLIP_API_DLL
    bool
    spline_isMonotone( integer ipos ) const
    { return m_splines.isMonotone(ipos) >= 0; }

    // get the label of the spline at column `ipos`
    BANGBANGFCLIP_API_DLL
    char const *
    spline_header( integer ipos ) const
    { return m_splines.header(ipos).c_str(); }

    // get values of splines at `val` of default independent
    BANGBANGFCLIP_API_DLL
    void
    spline_eval( real_type val, vector<real_type> & values ) const
    { return m_splines.eval(val,values); }

    // get values of splines at `val` using spline at ipos column as independent
    BANGBANGFCLIP_API_DLL
    void
    spline_eval2(
      integer             ipos,
      real_type           val,
      vector<real_type> & values
    ) const {
      return m_splines.eval2(ipos,val,values);
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
  BANGBANGFCLIP_API_DLL
  bool
  BangBangFclip_ocp_setup( char const id[], GenericContainer & gc_data );

  EXTERN_C
  BANGBANGFCLIP_API_DLL
  bool
  BangBangFclip_ocp_guess( char const id[], GenericContainer & gc_guess );

  EXTERN_C
  BANGBANGFCLIP_API_DLL
  bool
  BangBangFclip_ocp_solve( char const id[],
                           GenericContainer & gc_data,
                           GenericContainer & gc_solution );

  EXTERN_C
  BANGBANGFCLIP_API_DLL
  void
  BangBangFclip_write_ocp_solution( char const id[], char const fname[] );

}

// EOF: BangBangFclip_dll_ruby.hh
