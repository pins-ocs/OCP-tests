
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: HANGING CHAIN (Test 4 of COPS3)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamical system equations
EQ1  := diff(x1(t),t) = u(t) :
EQ2  := diff(x2(t),t) = x1(t)*sqrt(1+u(t)*2) :
EQ3  := diff(x3(t),t) = sqrt(1+u(t)*2):
ode  := [EQ||(1..3)]: <%>;
# States and Controls
# States
xvars := [x1(t),x2(t),x3(t)] ;
# Controls
uvars := [u(t)] ;
# Optimal Contol Problem
loadDynamicSystem(  equations = ode,
  controls  = uvars,
  states    = xvars);
addBoundaryConditions(
  initial=[x1=a,x2=0,x3=0],
  final=[x1=b,x3=L]
);
infoBoundaryConditions() ;
setTarget( lagrange = 0, mayer = x2(zeta_f) ) ;
PARS := [
  a = 1,
  b = 3,
  L = 4
];
GUESS := [
  x1 = a+(b-a)*zeta,
  x2 = 0,
  x3 = 0,
  lambda1__xo = 1
];
generateOCProblem(
  "HangingChain",
  parameters   = PARS,
  mesh         = [length=1, n=400],
  states_guess = GUESS
);

