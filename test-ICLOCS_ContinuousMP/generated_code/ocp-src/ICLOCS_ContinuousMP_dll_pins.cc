/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_dll_pins.cc                                |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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


#include "ICLOCS_ContinuousMP_dll_pins.hh"
#include <map>

static Mechatronix::Console * pConsole  = nullptr;
static Mechatronix::integer   n_threads = std::thread::hardware_concurrency();

/*
::         _             _       _             __
::   _ __ (_)_ __  ___  (_)_ __ | |_ ___ _ __ / _| __ _  ___ ___
::  | '_ \| | '_ \/ __| | | '_ \| __/ _ \ '__| |_ / _` |/ __/ _ \
::  | |_) | | | | \__ \ | | | | | ||  __/ |  |  _| (_| | (_|  __/
::  | .__/|_|_| |_|___/ |_|_| |_|\__\___|_|  |_|  \__,_|\___\___|
::  |_|
*/

#define E_SPLINE_ERROR (mrb_class_get(mrb, "SplineError"))
#define E_OCP_ERROR (mrb_class_get(mrb, "OCPError"))

#define MAP_PROBLEM map< string, ICLOCS_ContinuousMP_Problem * >

namespace ICLOCS_ContinuousMPDefine {

  using namespace std;

  static MAP_PROBLEM problems;

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_ocp_setup( mrb_state *mrb, mrb_value self ) {
    if ( pConsole == nullptr ) pConsole = new Console(&std::cout,4);

    mrb_sym m_sym_id   = mrb_intern_lit( mrb,"@id" );
    mrb_sym m_sym_data = mrb_intern_lit( mrb,"@data" );

    // ruby parameters
    mrb_value id_value   = mrb_iv_get( mrb, self, m_sym_id );
    mrb_value data_value = mrb_iv_get( mrb, self, m_sym_data );

    // check parameters
    if ( !mrb_string_p(id_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_setup, missing first parameter or is nota a string (id)\n"
      );
    }
    if ( mrb_nil_p(data_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_setup, missing second parameter (data)\n"
      );
    }

    // get parameters
    string id = mrb_str_to_cstr( mrb, id_value );

    // to C++ parameters
    GenericContainer gc_data;
    Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );

    integer infoLevel = 1;
    gc_data.get_if_exists( "InfoLevel", infoLevel );
    pConsole->changeLevel( infoLevel );

    // setup the solver
    //bool ok = ocp.setup( id.c_str(), ocp.gc_data );
    bool   ok;
    string error;
    MAP_PROBLEM::iterator it = problems.find( id.c_str() );
    if ( it == problems.end() ) {
      problems[id] = new ICLOCS_ContinuousMP_Problem( n_threads, pConsole );
      ok           = problems[id]->setup( gc_data, error );
    } else {
      ok = it->second->setup( gc_data, error );
    }

    // return values
    if ( !ok ) mrb_raise( mrb, E_OCP_ERROR, error.c_str() );

    return mrb_str_new_cstr( mrb, "setup done" );
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_ocp_guess( mrb_state *mrb, mrb_value self ) {

    mrb_sym m_sym_id   = mrb_intern_lit( mrb,"@id" );
    mrb_sym m_sym_data = mrb_intern_lit( mrb,"@data" );

    // ruby parameters
    mrb_value id_value   = mrb_iv_get( mrb, self, m_sym_id );
    mrb_value data_value = mrb_iv_get( mrb, self, m_sym_data );

    // check parameters
    if ( !mrb_string_p(id_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_guess, missing first parameter or is not a string (id)\n"
      );
    }
    if ( mrb_nil_p(data_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_guess, missing second parameter (data)\n"
      );
    }

    // launch the solver
    string id = mrb_str_to_cstr( mrb, id_value );
    MAP_PROBLEM::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_guess, you must do setup first!\n"
      );
    } else {
      // to C++ parameters
      GenericContainer gc_data;
      Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );
      it->second->guess(
        gc_data(
          "Guess",
          "mrb_ICLOCS_ContinuousMP_ocp_guess Missing field `Guess`"
        )
      );
    }
    return mrb_str_new_cstr( mrb, "guess done" );
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_ocp_solve( mrb_state *mrb, mrb_value self ) {

    mrb_sym m_sym_id   = mrb_intern_lit( mrb,"@id" );
    mrb_sym m_sym_data = mrb_intern_lit( mrb,"@data" );

    // ruby parameters
    mrb_value id_value   = mrb_iv_get( mrb, self, m_sym_id );
    mrb_value data_value = mrb_iv_get( mrb, self, m_sym_data );

    // check parameters
    if ( !mrb_string_p(id_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_solve, missing first parameter or is not a string (id)\n"
      );
    }
    if ( mrb_nil_p(data_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_solve, missing second parameter (data)\n"
      );
    }

    // launch the solver
    string id = mrb_str_to_cstr( mrb, id_value );
    MAP_PROBLEM::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_solve, you must do setup first!\n"
      );
    } else {
      // to C++ parameters
      GenericContainer gc_data;
      Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );

      bool ok = it->second->solve();
      if ( !ok )
        pConsole->error( "ICLOCS_ContinuousMP_ocp_solve, solution failed!\n" );
      it->second->diagnostic( gc_data, gc_data );
    }

    // return values
    mrb_value res = mrb_hash_new( mrb );
    Mechatronix::mrb_from_GC(
      mrb,
      it->second->getSolution(),
      res,
      "mrb_from_GC:"
    );
    mrb_iv_set( mrb, self, mrb_intern_cstr( mrb, "@ocp_solution" ), res );
    return res;
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_write_ocp_solution( mrb_state *mrb, mrb_value self ) {
    mrb_value a_string;

    mrb_sym m_sym_id   = mrb_intern_lit( mrb,"@id" );

    // ruby parameters
    mrb_value id_value = mrb_iv_get( mrb, self, m_sym_id );

    // check parameters
    if ( !mrb_string_p(id_value) )  {
      mrb_raise(
        mrb,
        E_OCP_ERROR,
        "ICLOCS_ContinuousMP_ocp_solve, missing first parameter or is not a string (id)\n"
      );
    }

    // ruby parameters
    mrb_get_args( mrb, "S", &a_string );

    // to C++ parameters
    string id = mrb_str_to_cstr( mrb, id_value );
    MAP_PROBLEM::const_iterator it = problems.find(id);
    if ( it == problems.end() ) {
      pConsole->error( "ICLOCS_ContinuousMP_ocp_write_to_file, no solution found!\n" );
    } else {
      ofstream file( mrb_str_to_cstr( mrb, a_string ) );
      Mechatronix::save_OCP_solution_to_stream( it->second->getSolution(), file );
      file.close();
    }

    return mrb_nil_value();
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_ocp_solution_range( mrb_state *mrb, mrb_value self ) {
    // ruby arguments: symbol for independent var, value of independent var
    mrb_sym   _var_name;
    mrb_value res;

    mrb_get_args( mrb, "n", &_var_name );
    char const * var_name = mrb_str_to_cstr( mrb, mrb_sym2str( mrb, _var_name ) );

    // problem id
    mrb_value id_value = mrb_iv_get( mrb, self, mrb_intern_cstr( mrb, "@id" ) );
    string id = mrb_str_to_cstr( mrb, id_value );
    MAP_PROBLEM::const_iterator it = problems.find( id );

    try {
      integer ipos = it->second->spline_getPosition(var_name);
      if ( ipos < 0 )
        mrb_raisef(
          mrb,
          E_SPLINE_ERROR,
          "Independent variable '%S' does not exist",
          mrb_symbol_value(_var_name)
        );

      if ( !it->second->spline_isMonotone( ipos ) )
        mrb_raisef(
          mrb,
          E_SPLINE_ERROR,
          "Independent variable '%S' is not monotone",
          mrb_symbol_value(_var_name)
        );

      res = mrb_range_new(
        mrb,
        mrb_float_value( mrb, it->second->spline_min(ipos) ),
        mrb_float_value( mrb, it->second->spline_max(ipos) ),
        MRB_TT_FALSE
      );

    } catch ( std::exception const & err ) {
      mrb_raisef(
        mrb,
        E_SPLINE_ERROR,
        "SplineSet Error: '%S'",
        mrb_str_new_cstr(mrb,err.what())
      );
    } catch ( ... ) {
      mrb_raise(
        mrb,
        E_SPLINE_ERROR,
        "SplineSet Unknown error\n"
      );
    }
    return res;
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  mrb_value
  mrb_ICLOCS_ContinuousMP_ocp_eval_solution( mrb_state *mrb, mrb_value self ) {

    // ruby arguments: symbol for independent var, value od independent var
    mrb_sym      _var_name;
    mrb_float    var_value;
    const char * var_name;

    mrb_get_args( mrb, "nf", &_var_name, &var_value );
    var_name = mrb_str_to_cstr( mrb, mrb_sym2str( mrb, _var_name ) );

    // problem id
    mrb_value id_value = mrb_iv_get( mrb, self, mrb_intern_cstr(mrb, "@id" ) );
    string id = mrb_str_to_cstr( mrb, id_value );
    MAP_PROBLEM::const_iterator it = problems.find(id);
    mrb_value res = mrb_hash_new(mrb);

    try {
      integer ipos = it->second->spline_getPosition(var_name);
      if ( ipos < 0 )
        mrb_raisef(
          mrb,
          E_SPLINE_ERROR,
          "Independent variable '%S' does not exist",
          mrb_symbol_value(_var_name)
        );

      if ( !it->second->spline_isMonotone( ipos ) )
        mrb_raisef(
          mrb,
          E_SPLINE_ERROR,
          "Independent variable '%S' is not monotone",
          mrb_symbol_value(_var_name)
        );

      vector<real_type> values;
      it->second->spline_eval2( ipos, var_value, values );

      for ( integer i = 0; i < it->second->numSplines(); ++i )
        mrb_hash_set(
          mrb,
          res,
          mrb_symbol_value(
            mrb_intern_cstr(mrb, it->second->spline_header(i))
          ),
          mrb_float_value(mrb, values[i])
        );
    } catch ( std::exception const & err ) {
      mrb_raisef(
        mrb,
        E_SPLINE_ERROR,
        "SplineSet Error: '%S'",
        mrb_str_new_cstr(mrb, err.what())
      );
    } catch ( ... ) {
      mrb_raise(
        mrb,
        E_SPLINE_ERROR,
        "SplineSet Unknown error\n"
      );
    }

    return res;
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  void
  mrb_libICLOCS_ContinuousMP_gem_init(mrb_state* mrb) {
    struct RClass *ocp_class;
    struct RClass *mechatronix;

    mechatronix = mrb_module_get(mrb, "Mechatronix");
    ocp_class = mrb_class_get_under(mrb, mechatronix, "OCPSolver");

    mrb_define_const(
      mrb,
      ocp_class,
      "NAME",
      mrb_str_new_cstr(mrb, "ICLOCS_ContinuousMP")
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "setup",
      mrb_ICLOCS_ContinuousMP_ocp_setup,
      MRB_ARGS_NONE()
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "guess",
      mrb_ICLOCS_ContinuousMP_ocp_guess,
      MRB_ARGS_NONE()
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "solve",
      mrb_ICLOCS_ContinuousMP_ocp_solve,
      MRB_ARGS_NONE()
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "write_ocp_solution",
      mrb_ICLOCS_ContinuousMP_write_ocp_solution,
      MRB_ARGS_REQ(1)
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "eval_solution",
      mrb_ICLOCS_ContinuousMP_ocp_eval_solution,
      MRB_ARGS_REQ(2)
    );

    mrb_define_method(
      mrb,
      ocp_class,
      "solution_range",
      mrb_ICLOCS_ContinuousMP_ocp_solution_range,
      MRB_ARGS_REQ(1)
    );

    mrb_define_class(
      mrb,
      "SplineError",
      mrb_class_get(mrb, "Exception")
    );

    mrb_define_class(
      mrb,
      "OCPError",
      mrb_class_get(mrb, "Exception")
    );
  }

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  EXTERN_C
  ICLOCS_CONTINUOUSMP_API_DLL
  void
  mrb_libICLOCS_ContinuousMP_gem_final(mrb_state* mrb)
  {
  }
}

// EOF: ICLOCS_ContinuousMP_dll_pins.cc
