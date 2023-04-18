/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_dll_ruby.cc                                    |
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


#include "BangBangFmodule_dll_ruby.hh"
#include <map>

namespace BangBangFmoduleDefine {

  using namespace std;

  static map< string, BangBangFmodule_Problem * > problems;

  static Console * pConsole{nullptr};
  static ThreadPoolBase * pTP{nullptr};

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
  BANGBANGFMODULE_API_DLL
  bool
  BangBangFmodule_ocp_setup( char const id[], GenericContainer & gc_data ) {
    if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);
    if ( pTP      == nullptr ) pTP      = new ThreadPool1(std::thread::hardware_concurrency());

    map< string, BangBangFmodule_Problem * >::iterator it = problems.find(id);
    string error;
    integer infoLevel = 1;
    gc_data.get_if_exists( "InfoLevel", infoLevel );
    pConsole->change_level( infoLevel );
    if ( it == problems.end() ) {
      problems[id] = new BangBangFmodule_Problem(pConsole,pTP);
      return problems[id]->setup(gc_data,error);
    } else {
      return it->second->setup(gc_data,error);
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  BANGBANGFMODULE_API_DLL
  bool
  BangBangFmodule_ocp_guess( char const id[], GenericContainer & gc_data ) {
    map< string, BangBangFmodule_Problem * >::iterator it = problems.find(id);
    if ( it == problems.end() ) {
      return false;
    } else {
      it->second->guess( gc_data("Guess", "BangBangFmodule_ocp_guess" ) );
      return true;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  BANGBANGFMODULE_API_DLL
  bool
  BangBangFmodule_ocp_solve( char const id[],
                             GenericContainer & gc_data,
                             GenericContainer & gc_solution ) {
    map< string, BangBangFmodule_Problem * >::iterator it = problems.find(id);
    if ( it == problems.end() ) {
      return false;
    } else {
      string errmsg;
      bool ok = it->second->setup( gc_data, errmsg );
      if ( ok ) {
        ok = it->second->solve();
        gc_solution.load( it->second->getSolution() );
      } else {
        pConsole->error(
          fmt::format("BangBangFmodule_ocp_solve, ERROR: {}\n",errmsg)
        );
      }
      return ok;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  BANGBANGFMODULE_API_DLL
  void
  BangBangFmodule_write_ocp_solution( char const id[], char const fname[] ) {
    map< string, BangBangFmodule_Problem * >::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      pConsole->error("BangBangFmodule_write_ocp_solution, no solution found!\n" );
    } else {
      ofstream file( fname );
      Mechatronix::save_OCP_solution_to_stream( it->second->getSolution(), file );
      file.close();
    }
  }
}

// EOF: BangBangFmodule_dll_ruby.cc
