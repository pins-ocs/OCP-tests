
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Controllo Singolare
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    :=  diff(x(t),t) = u(t) :
EQNS_T := [ EQ1 ];
# States and contros
qvars := [x(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
#addBoundaryConditions(initial=[x,v],final=[v]);
#setBCActivationStatus(initial=[x,v],final=[v]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
# Penalty
addControlBound(  u,  controlType = "U_COS_LOGARITHMIC",  maxabs      = 1);
setTarget( lagrange = (x(zeta)-1+zeta^2)^2 ) ;

generateOCProblem(  "SingularCalogero",  mesh = [ length=2, n=100 ], mesh_s0=-1,  states_guess = [ x= 0]);

