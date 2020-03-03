/*-----------------------------------------------------------------------*\
 |  file: CNOC_Main.cc                                                   |
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


#define MECHATRONIX_USE_RUBY
//#define MECHATRONIX_USE_LUA

#include "CNOC.hh"
#include "CNOC_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
using Mechatronix::ToolPath2D;

using namespace CNOCLoad;
using GenericContainerNamespace::GenericContainer;

int
main() {

  // model cen be large and do not fit in stack, use new
  GenericContainer        gc_data, gc_solution;
  Mechatronix::Console    console(&std::cout,4);
  Mechatronix::ThreadPool TP(std::thread::hardware_concurrency());

  try {
    CNOC * pModel = new CNOC("CNOC",&TP,&console);

    // user defined Object instances (external)
    ToolPath2D       toolPath2D( "toolPath2D" );

    #ifdef MECHATRONIX_USE_RUBY
    string fname = "./data/CNOC_Data.rb";
    #endif
    #ifdef MECHATRONIX_USE_LUA
    string fname = "./data/CNOC_Data.lua";
    #endif

    // read Ruby/Lua script
    Mechatronix::load_script( fname, gc_data );

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes

    LW_ASSERT0(
      gc_data.exists("ToolPath2D"),
      "missing key: ``ToolPath2D'' in gc_data\n"
    );
    toolPath2D.setup(gc_data("ToolPath2D"));
    ptrs[ "pToolPath2D" ] = &toolPath2D;

    // setup model
    pModel->setup( gc_data );

    // initialize nonlinear system initial point
    pModel->guess( gc_data("Guess","Missing `Guess` field") );

    // solve nonlinear system
    bool ok = pModel->solve(); // no spline

    // get solution (even if not converged)
    pModel->get_solution( gc_solution );
    pModel->diagnostic( gc_data );

    ofstream file;
    if ( ok ) {
      file.open( "data/CNOC_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/CNOC_OCP_not_converged.txt" );
    }
    file.precision(18);
    Mechatronix::saveOCPsolutionToStream(gc_solution,file);
    file.close();
    cout.precision(18);
    GenericContainer const & target = gc_solution("target");
    fmt::print(
      "target [Lagrange,Mayer]        = [ {:12.6}, {:12.6}]\n"
      "[Penalties/Barriers, Controls] = [ {:12.6}, {:12.6}]\n",
      target("lagrange").get_number(),  target("mayer").get_number(),
      target("penalties").get_number(), target("control_penalties").get_number()
    );
    if ( gc_solution.exists("parameters") ) {
      cout << "Parameters:\n";
      gc_solution("parameters").print(cout);
    }
    if ( gc_solution.exists("diagnosis") ) gc_solution("diagnosis").print(cout);
  }
  catch ( exception const & exc ) {
    console.error(exc.what());
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch ( char const exc[] ) {
    console.error(exc);
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch (...) {
    console.error("ERRORE SCONOSCIUTO\n");
    ALL_DONE_FOLKS;
    exit(0);
  }

  ALL_DONE_FOLKS;

  return 0;
}
