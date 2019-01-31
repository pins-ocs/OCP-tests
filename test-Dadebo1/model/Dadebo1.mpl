
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Dadebo and McAuley 1995
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    :=  diff(x(t),t) - u(t) :
EQ2    :=  diff(y(t),t) - x(t)^2-u(t)^2 :

EQNS_T := [ EQ1, EQ2 ];
# States and controls
qvars := [x(t),y(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x=1,y=0],final=[x=1]);
infoBoundaryConditions() ;
setTarget( mayer = y(zeta_f)) ;

#Describe(buildOCProblem) ;
GUESS := [ x = 1, y = 0, lambda2__xo = 1 ];
generateOCProblem(  "Dadebo1",
  mesh         = [ length=1,n=1000], mesh_s0=0,
  states_guess = GUESS);

