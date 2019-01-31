
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Sliding Mode
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamic system equations
EQ1    :=  diff(x(t),t) = u(t) :
EQ2    :=  diff(y(t),t) = x(t)^2 :
EQNS_T := [ EQ||(1..2) ];
# States and control
qvars := [x(t),y(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x,y],final=[x]);
infoBoundaryConditions() ;
# Penalty
addControlBound(  u,  controlType = "U_COS_LOGARITHMIC",  maxabs      = 1);
setTarget( mayer = y(zeta_f) ) ;
generateOCProblem(  "SlidingMode",
   parameters   = [ x_i = 1, x_f=1, y_i=0],
   mesh         = [length=3, n=100],
   states_guess = []);

