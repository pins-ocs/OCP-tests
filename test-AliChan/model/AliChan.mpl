
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Ali Chan 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# 
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
# G. M. Aly and W. C. Chan, “Application of a modified quasi- linearization technique to totally singular optimal problems,”
#  International Journal of Control, vol. 17, pp. 809–815, 1973.
EQ1    :=  diff(y1(t),t) - y2(t) :
EQ2    :=  diff(y2(t),t) - u(t) :
EQNS_T := [ EQ||(1..2) ];
qvars := [y1(t),y2(t)] ;
cvars := [u(t)] ;
# Optimal Control: problem definition
# Load dynamical system
#infoRegisteredObjects() ;
loadDynamicSystem(
# Boundary conditions
addBoundaryConditions(
infoBoundaryConditions() ;
# Constraints on control
addControlBound(
  scale       = 1
# Cost function: target
setTarget( lagrange = y2(zeta)^2-y1(zeta)^2 );
# Problem generation
#setFDorder([x],"forward") ;
generateOCProblem(
  "AliChan", clean=true,
  parameters   = [ epsilon=1e-4, L=Pi/2 ],
  states_guess = [ y2 = 1 ]
);
