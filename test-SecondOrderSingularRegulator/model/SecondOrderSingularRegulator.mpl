
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Second Order Singular Regulator
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# 
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
# M. S. Aronna, J. F. Bonnans, and P. Martinon, “A shooting algorithm for optimal control problems with singular arcs,
# ” J. Optim. Theory Appl., vol. 158, no. 2, pp. 419–459, 2013. 
# Available: https://doi.org/10.1007/s10957-012-0254-8
EQ1    :=  diff(y1(t),t) - y2(t) :
EQ2    :=  diff(y2(t),t) - u(t) :
EQNS_T := [ EQ||(1..2) ];
qvars := [y1(t),y2(t)] ;
cvars := [u(t)] ;
# Optimal Control: problem definition
# Load dynamical system
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
# Boundary conditions
addBoundaryConditions(
  initial=[y1=0,y2=1]
);
infoBoundaryConditions() ;
# Constraints on control
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = 1e-10,
  tolerance   = 1e-10,
  scale       = 1
);
# Cost function: target
setTarget( lagrange = y2(zeta)^2+y1(zeta)^2 );
# Problem generation
generateOCProblem(
  "SecondOrderSingularRegulator", clean=true,
  parameters   = [ L=5 ],
  mesh         = [ length=L, n=500 ],
  states_guess = [ y2 = 1 ]
);

