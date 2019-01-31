
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Singular Control
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    :=  diff(x(t),t) - y(t) :
EQ2    :=  diff(y(t),t) - u(t) :
EQNS_T := [ EQ1, EQ2 ];
# States and control
# States
qvars := [x(t),y(t)] ;
# Control
cvars := [u(t)] ;
# Optimal Contol Problem
loadDynamicSystem( equations=EQNS_T, controls=cvars, states=qvars ) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[y],final=[y]);
infoBoundaryConditions() ;
lagrange_target := (x(zeta)-1+C*zeta^2)^2 ;
# Penalty
addControlBound(  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  scale       = epsilon+lagrange_target);
setTarget( lagrange = lagrange_target ) ;

generateOCProblem(
  "SingularCalogeroModified",
  mesh         = [ length=2,n=100 ], mesh_s0=-1,
  parameters   = [ y_i=0, y_f=0, C=0.25, epsilon=0.01, epsilon_min=1e-10],
  continuation = [ [epsilon=epsilon*exp(s*log(epsilon_min/epsilon))] ],
  states_guess = [ x = 0, y=0]
) ;

