
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Alp Rider 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# A Collection of Optimal Control Test Problems
# John T. Betts 1 November 17, 2015
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
EQ1    := diff(y1(t),t) = -10*y1(t) + u1(t) + u2(t):
EQ2    := diff(y2(t),t) = -2*y2(t)  + u1(t) + 2*u2(t):
EQ3    := diff(y3(t),t) = -3*y3(t)  + 5*y4(t)+ u1(t) - u2(t):
EQ4    := diff(y4(t),t) =  5*y3(t)  - 3*y4(t)+ u1(t) + 3*u2(t):
EQNS_T := [ EQ||(1..4) ]:<%>;
qvars := map([y1,y2,y3,y4],(t));
cvars := map([u1,u2],(t));
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
  initial = [ y1, y2, y3, y4 ],
  final   = [ y1, y2, y3, y4 ]
infoBoundaryConditions() ;
addUserFunction(p(t,a,b)=exp(-b*(t-a)^2));
# Constraints on control
SUMQ := y1(zeta)^2+y2(zeta)^2+y3(zeta)^2+y4(zeta)^2;
addUnilateralConstraint(
  SUMQ >= q(zeta),
  Ybound,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1
);
# Cost function: target
TARGET1 := SUMQ;
TARGET2 := u1(zeta)^2+u2(zeta)^2;
setTarget(
PARS := [
  y2_i  = 1,
  y3_i  = 2,
  y4_i  = 1,
  y1_f  = 2,
  y2_f  = 3,
  y3_f  = 1,
  y4_f  = -2,
  W1    = 100,
  W     = 0,
  epsi0 = 0.1,
  epsi  = epsi0,
  tol1  = 0.001,
  tol   = tol0
];
GUESS := [
  y3 = y3_i + zeta*(y3_f-y3_i),
  y4 = y4_i + zeta*(y4_f-y4_i)
];
CONT := [
  [
  ]
];
# Problem generation
#Describe(generateOCProblem);
POST := [
Mesh := [
generateOCProblem(
  "AlpRider", clean=true,
  parameters           = PARS,
  mesh                 = Mesh,
  states_guess         = GUESS,
);
