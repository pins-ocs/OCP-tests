


#include <acado_optimal_control.hpp>
#include <include/acado_gnuplot/gnuplot_window.hpp>


int main( ){

    USING_NAMESPACE_ACADO


    // INTRODUCE THE VARIABLES:
    // -------------------------

    DifferentialState     x;
    Control               u    ;
   // Parameter             t    ;
    TIME t;
    DifferentialEquation  f( -1.0, 1.0 );


    // DEFINE A DIFFERENTIAL EQUATION:
    // -------------------------------

    f << dot(x) == u;
    //f << dot(y) == -v*cos(theta);
    //f << dot(v) == 9.81*cos(theta);


    // DEFINE AN OPTIMAL CONTROL PROBLEM:
    // ----------------------------------
    OCP ocp( -1.0, 1.0,500 );

    //ocp.minimizeMayerTerm( T );
    ocp.minimizeLagrangeTerm( (x-1+t*t)*(x-1+t*t) );

    ocp.subjectTo( f );

    //ocp.subjectTo( AT_START, x ==  0.0 );
    //ocp.subjectTo( AT_START, y ==  0.0 );
    //ocp.subjectTo( AT_START, v ==  0.0 );

    //ocp.subjectTo( AT_END  , x ==  10.0 );
    //ocp.subjectTo( AT_END  , y == -3.0 );

    ocp.subjectTo( -1.0 <= u <=  1.0  );
    //ocp.subjectTo( -01 <= theta <=  3.15  );
    //ocp.subjectTo(  -1.0 <= t <= 1.0  );


    // VISUALIZE THE RESULTS IN A GNUPLOT WINDOW:
    // ------------------------------------------
    GnuplotWindow window;
        window.addSubplot( x, "THE STATE x"      );
        //window.addSubplot( y, "THE DISTANCE y"      );
        //window.addSubplot( v, "THE VELOCITY v"      );
        //window.addSubplot( m, "THE MASS m"          );
        window.addSubplot( u, "THE CONTROL INPUT u" );


    // DEFINE AN OPTIMIZATION ALGORITHM AND SOLVE THE OCP:
    // ---------------------------------------------------
    OptimizationAlgorithm algorithm(ocp);

    algorithm.set( MAX_NUM_ITERATIONS, 100 );

    algorithm << window;


//     algorithm.initializeDifferentialStates("tor_states.txt");
//     algorithm.initializeParameters("tor_pars.txt");
//     algorithm.initializeControls("tor_controls.txt");

    algorithm.solve();

     algorithm.getDifferentialStates("singcontrol_states.txt");
     algorithm.getParameters("singcontrol_pars.txt");
     algorithm.getControls("singcontrol_controls.txt");

    return 0;
}



