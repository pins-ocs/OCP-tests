/*-----------------------------------------------------------------------*\
 |  file: farmer_problem_dll_ruby.cc                                     |
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


#include "farmer_problem_dll_ruby.hh"
#include <map>

namespace farmer_problemDefine {

  using namespace std;

  static map< string, farmer_problem_Problem * > problems;

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
  FARMER_PROBLEM_API_DLL
  bool
  farmer_problem_ocp_setup( char const id[], GenericContainer & gc_data ) {
    map< string, farmer_problem_Problem * >::iterator it = problems.find(id);
    string error;
    integer infoLevel = 1;
    if ( gc_data.exists("InfoLevel") )
      infoLevel = gc_data("InfoLevel").get_as_int("farmer_problem_ocp_setup::InfoLevel ");
    if ( it == problems.end() ) {
      problems[id] = new farmer_problem_Problem(&cout,infoLevel);
      return problems[id]->setup(gc_data,error);
    } else {
      it->second->changeInfoLevel(infoLevel);
      return it->second->setup(gc_data,error);
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  FARMER_PROBLEM_API_DLL
  bool
  farmer_problem_ocp_guess( char const id[], GenericContainer & gc_data ) {
    map< string, farmer_problem_Problem * >::iterator it = problems.find(id);
    if ( it == problems.end() ) {
      return false;
    } else {
      it->second->guess( gc_data("Guess", "farmer_problem_ocp_guess missing field `Guess`" ) );
      return true;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  FARMER_PROBLEM_API_DLL
  bool
  farmer_problem_ocp_solve( char const id[],
                            GenericContainer & gc_data,
                            GenericContainer & gc_solution ) {
    map< string, farmer_problem_Problem * >::iterator it = problems.find(id);
    if ( it == problems.end() ) {
      return false;
    } else {
      string errmsg;
      bool ok = it->second->setup( gc_data, errmsg );
      if ( ok ) {
        ok = it->second->solve();
        gc_solution.load( it->second->getSolution() );
      } else {
        std::cerr
          << MSG_ERROR( "farmer_problem_ocp_solve, ERROR: " << errmsg )
          << '\n';
      }
      return ok;
    }
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  FARMER_PROBLEM_API_DLL
  void
  farmer_problem_write_ocp_solution( char const id[], char const fname[] ) {
    map< string, farmer_problem_Problem * >::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      std::cerr
        << MSG_ERROR( "farmer_problem_write_ocp_solution, no solution found!" )
        << '\n';
    } else {
      ofstream file( fname );
      Mechatronix::saveOCPsolutionToStream( it->second->getSolution(), file );
      file.close();
    }
  }
}

// EOF: farmer_problem_dll_ruby.cc
