
#include <acado_optimal_control.hpp>
#include <include/acado_gnuplot/gnuplot_window.hpp>


int main( ){

    USING_NAMESPACE_ACADO


    // INTRODUCE THE VARIABLES:
    // -------------------------

    DifferentialState     x1,x2,x3,x4;
    Control               u    ;
    //Parameter             T    ;

    DifferentialEquation  f1( 0.0, 5.0 );
   // DifferentialEquation  f2( 0.0, T );
   // DifferentialEquation  f3( 0.0, T );
   // DifferentialEquation  f4( 0.0, T );


    // DEFINE A DIFFERENTIAL EQUATION:
    // -------------------------------

    f1 << dot(x1) == x2;

    f1 << dot(x2) == x3;
	
	f1 << dot(x3) == u;

	f1 << dot(x4) == x1*x1;
    


    // DEFINE AN OPTIMAL CONTROL PROBLEM:
    // ----------------------------------
    OCP ocp( 0.0, 5.0 ,300 );

    ocp.minimizeMayerTerm( x4);
    ocp.subjectTo( f1  );

    ocp.subjectTo( AT_START, x1 ==  1.0);
    ocp.subjectTo( AT_START, x2 ==  0.0 );
	ocp.subjectTo( AT_START, x3 ==  0.0 );
	ocp.subjectTo( AT_START, x4 ==  0.0 );
	
    //ocp.subjectTo( AT_END  , x ==  10.0 );
    //ocp.subjectTo( AT_END  , y == -3.0 );

    ocp.subjectTo( -1 <= u <=  1  );
    


    // VISUALIZE THE RESULTS IN A GNUPLOT WINDOW:
    // ------------------------------------------
    GnuplotWindow window;
        window.addSubplot( x1, "  x1"      );
        window.addSubplot( x2, "  x2"      );
    	window.addSubplot( x3, "  x3"      );
    	window.addSubplot( x4, "  x4"      );
       
                
        //window.addSubplot( m, "THE MASS m"          );
        window.addSubplot( u, "THE CONTROL INPUT u" );
        
    // DEFINE AN OPTIMIZATION ALGORITHM AND SOLVE THE OCP:
    // ---------------------------------------------------
    OptimizationAlgorithm algorithm(ocp);

    algorithm.set( MAX_NUM_ITERATIONS, 100 );
    algorithm.set( KKT_TOLERANCE , 1e-10 ) ;

    algorithm << window;



    algorithm.solve();

     algorithm.getDifferentialStates("sing04_states.txt");
     algorithm.getParameters("sing04_pars.txt");
     algorithm.getControls("sing04_controls.txt");

    return 0;
}



