
# 
#            
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Singular Control
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2 ];
# States and controls
qvars := [x(t),y(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x,y],final=[x,y]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
addControlBound(  u,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 1,
  scale       =(1/2)*x(zeta)^2+epsilon);
setTarget( lagrange = (1/2)*x(zeta)^2) ;

PARS  := [x_i=2, y_i = -2, x_f=2, y_f = 2, epsilon=1e-8];
GUESS := [ x = 0, y = 0];
generateOCProblem(  "SingularMarchal",
  parameters   = PARS,
  mesh         = [length=8,n=1000], mesh_s0=0,
  states_guess = GUESS) ;

