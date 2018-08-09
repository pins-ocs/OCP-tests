
# 
#            
# Optimal Control Problem: single mass 
# Authors: E. Bertolazzi, F. Biral
# Description
# SIngle mass moved by a bounded force from initial position to maximum distance in fixed time.
# Initial and final velocity fixed.
# Initialization
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
EQ1    :=  diff(x(t),t) - v(t) :
EQ2    :=  diff(v(t),t) - F(t) :
EQNS_T := [ EQ||(1..2) ];
# State variables and controls
# Variabili
qvars := [x(t),v(t)] ;
# Controlli
cvars := [F(t)] ;
# Optimal COntrol: problem definition
# Load dynamical system
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Boundary conditions
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions() ;
# Constraints on control
addControlBound( F, controlType="U_COS_LOGARITHMIC", maxabs=1 ) ;
# Cost function: target
setTarget( mayer = -x(zeta_f) ) ;
# Problem generation
#setFDorder([x],"forward") ;
generateOCProblem( "BangBangF", clean=false,
                   language="C++",
                   #parameters   = [ x_i = 0, x_f=0, v_i=0,v_f=0],
                   mesh         = [length=1, n=100],
                   states_guess = [ v = zeta*(1-zeta) ] ) ;

