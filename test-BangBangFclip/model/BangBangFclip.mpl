
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
# Description
# Single mass moved by a bounded force from initial position to maximum distance in fixed time.
# Initial and final velocity fixed.Bounded force is clipped with a regularized function. Force rate is the actual control and bounded.In this example it is shwon the mapping of user function with Mechatronix regularized function.
# 
# Inizializzazione
restart:
with(XOptima):
# Equations of motion
EQ1 := diff(x(t),t) = v(t) ;
EQ2 := diff(v(t),t) = clip(F(t),minClip,maxClip) ;
EQ3 := diff(F(t),t) = vF(t) - 0*(F(t)-clip(F(t),minClip,maxClip))/tau ;ode   := [EQ||(1..3)]: Vector(%);
xvars := [x(t),v(t),F(t)];
uvars := [vF(t)];
# Optimal control problem formulation
# Dynamic system
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Boundary conditions
addBoundaryConditions(initial=[x=0,v=0,F=0],final=[v=0,F=0]);
infoBoundaryConditions() ;
# Constraints
addControlBound( vF, label=controlForce, min = -vFmax, max = vFmax ) ;
# Mapping of User function with Mechatronix regularized function
mapUserFunctionToRegularized( clip, "ClipIntervalWithErf", [h=0.1,delta=0.1] ) ;
# Target
setTarget( mayer = -x(zeta_f) ) ;
# Code generation
generateOCProblem( "BangBangFclip",
                    post_processing = [[clip(F(zeta),minClip,maxClip),"F_clipped"]],
                    parameters = [vFmax   = 10,
                                  minClip = -1,
                                  maxClip = 1],
                    mesh = [[length=0.1,n=10],[length=0.4,n=40],[length=0.4,n=40],[length=0.1,n=10]],
                    states_guess = [v=1]) ;

