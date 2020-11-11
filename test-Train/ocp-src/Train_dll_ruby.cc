/*-----------------------------------------------------------------------*\
 |  file: Train_dll_ruby.cc                                              |
 |                                                                       |
 |  version: 1.0   date 12/11/2020                                       |
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


#include "Train_dll_ruby.hh"
#include <map>

namespace TrainDefine {

  using namespace std;

  static map< string, Train_Problem * > problems;

  static Console    * pConsole = nullptr;
  static ThreadPool * pTP      = nullptr;

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
  TRAIN_API_DLL
  bool
  Train_ocp_setup( char const id[], GenericContainer & gc_data ) {
    if ( pTP      == nullptr ) pTP      = new ThreadPool(std::thread::hardware_concurrency());
    if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);
    map< string, Train_Problem * >::iterator it = problems.find(id);
    string error;
    integer infoLevel = 1;
    gc_data.get_if_exists( "InfoLevel", infoLevel );
    pConsole->changeLevel( infoLevel );
    if ( it == problems.end() ) {
      problems[id] = new Train_Problem(pTP,pConsole);
      return problems[id]->setup(gc_data,error);
    } else {
      return it->second->setup(gc_data,error);
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  TRAIN_API_DLL
  bool
  Train_ocp_guess( char const id[], GenericContainer & gc_data ) {
    map< string, Train_Problem * >::iterator it = problems.find(id);
    if ( it == problems.end() ) {
      return false;
    } else {
      it->second->guess( gc_data("Guess", "Train_ocp_guess missing field `Guess`" ) );
      return true;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  TRAIN_API_DLL
  bool
  Train_ocp_solve( char const id[],
                   GenericContainer & gc_data,
                   GenericContainer & gc_solution ) {
    map< string, Train_Problem * >::iterator it = problems.find(id);
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
          fmt::format("Train_ocp_solve, ERROR: {}\n",errmsg)
        );
      }
      return ok;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  TRAIN_API_DLL
  void
  Train_write_ocp_solution( char const id[], char const fname[] ) {
    map< string, Train_Problem * >::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      pConsole->error("Train_write_ocp_solution, no solution found!\n" );
    } else {
      ofstream file( fname );
      Mechatronix::saveOCPsolutionToStream( it->second->getSolution(), file );
      file.close();
    }
  }
}

// EOF: Train_dll_ruby.cc
