
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Single mass moved by a bounded force from initial position to maximum distance in fixed time.
# Initial and final velocity fixed.
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
EQ1    :=  diff(x(t),t) - v(t) :
EQ2    :=  diff(v(t),t) - F(t) :
EQNS_T := [ EQ||(1..2) ];
qvars := [x(t),v(t)] ;
cvars := [F(t)] ;
# Optimal Control: problem definition
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
generateOCProblem(  "BangBangF", clean=false,
  #parameters   = [ x_i = 0, x_f=0, v_i=0,v_f=0],
  mesh         = [length=1, n=100],
  states_guess = [ v = zeta*(1-zeta) ]);

