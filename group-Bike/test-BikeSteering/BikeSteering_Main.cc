/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Main.cc                                           |
 |                                                                       |
 |  version: 1.0   date 7/8/2018                                         |
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


#define MECHATRONIX_USE_RUBY
//#define MECHATRONIX_USE_LUA

#include "BikeSteering.hh"
#include "BikeSteering_Pars.hh"

using namespace std ;
using namespace MechatronixCommon ;

// user class in namespaces
using Mechatronix::MeshStd ;

using namespace BikeSteeringLoad;
using GenericContainerNamespace::GenericContainer;

int
main() {
  BikeSteering         model("BikeSteering",&cout,1);
  GenericContainer     gc_data;
  GenericContainer     gc_solution;

  // user defined Object instances (external)
  MeshStd              mesh( "mesh" );

  try {
    #ifdef MECHATRONIX_USE_RUBY
    string fname = "./data/BikeSteering_Data.rb";
    #endif
    #ifdef MECHATRONIX_USE_LUA
    string fname = "./data/BikeSteering_Data.lua";
    #endif

    // read Ruby script
    if ( fname.find_last_of(".rb") ) {
      Mechatronix::MrubyInterpreter mrb;
      mrb.load( fname.c_str() );
      mrb.expr_to_GC( "Mechatronix.content", gc_data );
    } else if ( fname.find_last_of(".lua") ) {
      using GenericContainerNamespace::LuaInterpreter;
      LuaInterpreter lua;
      Mechatronix::lua_set_constants( lua );
      lua.do_file( fname.c_str() );
      lua.global_to_GC( "content", gc_data );
    } else {
      cerr << "unknown suffinx for filename `" << fname
           << "` use `.rb` or `.lua`";
      exit(1);
    }

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    ASSERT(gc_data.exists("Mesh"), "missing key: ``Mesh'' in gc_data");
    mesh.setup(gc_data("Mesh"));
    ptrs[ "pMesh" ] = &mesh;

    // setup model
    model.setup( gc_data );

    // initialize nonlinear system initial point
    model.guess( gc_data );

    // solve nonlinear system
    bool ok = model.solve(); // no spline

    // get solution (even if not converged)
    model.get_solution( gc_solution );
    model.diagnostic( gc_data );

    ofstream file;
    if ( ok ) {
      file.open( "data/BikeSteering_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/BikeSteering_OCP_not_converged.txt" );
    }
    Mechatronix::saveOCPsolutionToStream(gc_solution,file);
    file.close();
    cout.precision(18);
    GenericContainer const & target = gc_solution("target");
    cout << "Lagrange target    = " << target("lagrange").get_number()  << '\n'
         << "Mayer target       = " << target("mayer").get_number()     << '\n'
         << "Penalties+Barriers = " << target("penalties").get_number() << '\n'
         << "Control penalties  = " << target("control_penalties").get_number() << '\n';
    if ( gc_solution.exists("parameters") ) {
      cout << "Parameters:\n";
      gc_solution("parameters").print(cout);
    }
    if ( gc_solution.exists("diagnosis") ) gc_solution("diagnosis").print(cout);
  }
  catch ( exception const & exc ) {
    cerr << exc.what() << '\n';
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch ( char const exc[] ) {
    cerr << exc << '\n';
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch (...) {
    cout << "ERRORE SCONOSCIUTO\n";
    ALL_DONE_FOLKS;
    exit(0);
  }

  ALL_DONE_FOLKS;
}
