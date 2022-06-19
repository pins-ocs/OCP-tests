/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Main.cc                                        |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "BangBangFmodule.hh"
#include "BangBangFmodule_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;

using namespace BangBangFmoduleLoad;
using GenericContainerNamespace::GenericContainer;

int
main() {

  // model cen be large and do not fit in stack, use new
  GenericContainer     gc_data, gc_solution;
  Mechatronix::Console console(&std::cout,4);
  Mechatronix::integer n_threads = std::thread::hardware_concurrency();

  try {
    BangBangFmodule * m_model = new BangBangFmodule("BangBangFmodule",n_threads,&console);

    // user defined Object instances (external)
    MeshStd          mesh( "mesh" );

    string fname = "./data/BangBangFmodule_Data"; // no .lua or .rb extension

    // read Ruby/Lua script
    {
      bool ok = Mechatronix::load_script( fname, gc_data );
      UTILS_ASSERT( ok, "Failed to load file: {}\n", fname );
    }

    // change info level
    if ( gc_data.exists( "InfoLevel" ) )
      console.changeLevel( gc_data("InfoLevel").get_as_int() );

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];
    // setup user object classes
    UTILS_ASSERT0(
      gc_data.exists("Mesh"),
      "missing key: ``Mesh'' in gc_data\n"
    );
    mesh.setup(gc_data("Mesh"));
    ptrs[ "pMesh" ] = &mesh;

    // setup model
    m_model->setup( gc_data );

    // initialize nonlinear system initial point
    m_model->guess( gc_data("Guess","main") );

    // print information about solver
    m_model->info();

    // solve nonlinear system
    // m_model->set_timeout_ms( 100 );
    bool ok = m_model->solve(); // no spline

    // get solution (even if not converged)
    m_model->get_solution( gc_solution );
    m_model->diagnostic( gc_data, gc_solution );

    std::ofstream file;
    if ( ok ) {
      file.open( "data/BangBangFmodule_OCP_result.txt" );
    } else {
      cout << gc_solution("solver_message").get_string() << '\n';
      // dump solution to file
      file.open( "data/BangBangFmodule_OCP_result_NOT_CONVERGED.txt" );
    }
    file.precision(18);
    Mechatronix::save_OCP_solution_to_stream(gc_solution,file);
    file.close();
    cout.precision(18);
    GenericContainer const & target = gc_solution("target");
    fmt::print(
      "target [Lagrange,Mayer]       = [ {}, {} ]\n"
      "[Penalties/Barriers,Controls] = [ {}, {} ]\n",
      fmt::format("{:.4}",target("lagrange").get_number()),
      fmt::format("{:.4}",target("mayer").get_number()),
      fmt::format("{:.4}",target("penalties").get_number()),
      fmt::format("{:.4}",target("control_penalties").get_number())
    );
    if ( gc_solution.exists("parameters") ) {
      cout << "Optimization parameters:\n";
      gc_solution("parameters").print(cout);
    }
    if ( gc_solution.exists("diagnosis") ) gc_solution("diagnosis").print(cout);

    delete m_model;
  }
  catch ( std::exception const & exc ) {
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
