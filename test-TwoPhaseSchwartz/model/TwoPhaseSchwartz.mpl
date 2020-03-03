
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: TwoPhaseSchwartz
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# 
# Users Guide for dyn.Opt, Example 4
# Schwartz, A. L., Theory and Implementation of Numerical Methods based on Runge-Kutta Integration for Solving Optimal Control Problems. 
# Ph.D. Dissertation, University of California, Berkeley, 1989
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = u1(t)-0.1*(1+2*x1(t)^2)*x2(t):
EQ3    := diff(x3(t),t) = T2*(x4(t)):
EQ4    := diff(x4(t),t) = T2*(u2(t)-0.1*(1+2*x3(t)^2)*x4(t)):
EQNS_T := [ EQ||(1..4) ]:<%>;
qvars := map([x1,x2,x3,x4],(t));
cvars := [u1(t),u2(t)];
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
  initial = [ x1=1, x2=1 ],
  generic = [
    [x1(zeta_f)=x3(zeta_i), "x13"],
    [x2(zeta_f)=x4(zeta_i), "x24"]
  ]
);
infoBoundaryConditions() ;
# Constraints on control
addControlBound(
  u1,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 1,
  epsilon     = epsi,
  tolerance   = tol,
  scale       = 1
);
# 
addUnilateralConstraint(
  1-9*(x1(zeta)-1)^2-((x2(zeta)-0.4)/0.3)^2<=0,
  bound1,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1
);
addUnilateralConstraint(
  -0.8-x2(zeta) <= 0,
  bound2,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1
);
# Cost function: target
setTarget(
  lagrange = epsilon*u2(zeta)^2, 
  mayer    = 5*(x3(zeta_f)^2+x4(zeta_f)^2)
);
PARS := [
  epsi0    = 0.1,
  epsi1    = 0.001,
  epsi     = epsi0,
  tol0     = 0.1,
  tol1     = 0.001,
  tol      = tol0,
  T2       = 1.9,
  epsilon0 = 0.001,
  epsilon1 = 1e-10,
  epsilon  = epsilon0
];
GUESS := [
  x1 = 1,
  x2 = 1,
  x3 = 1,
  x4 = 1
];
CONT := [
  [
    epsilon = epsilon0^(1-s)*epsilon1^s,
    ["bound1","epsilon"]   = epsi0*(1-s)+epsi1*s,
    ["bound1","tolerance"] = tol0*(1-s)+tol1*s,
    ["bound2","epsilon"]   = epsi0*(1-s)+epsi1*s,
    ["bound2","tolerance"] = tol0*(1-s)+tol1*s,
    ["u1","epsilon"]       = epsi0*(1-s)+epsi1*s,
    ["u1","tolerance"]     = tol0*(1-s)+tol1*s
  ]
];
# Problem generation
#Describe(generateOCProblem);
POST := [
  [1+T2*zeta, "Time2"]
];
Mesh := [
  [length=1, n=100]
];
generateOCProblem(
  "TwoPhaseSchwartz", clean=true,
  parameters           = PARS,
  post_processing      = POST,
  mesh                 = Mesh,
  states_guess         = GUESS,
  controls_guess       = [u1=0,u2=0],
  controls_iterative   = true,
  continuation         = CONT,
  post_processing      = POST,
  max_accumulated_iter = 4000
);
ocp := getOCProblem();
eval(ocp["controls"]);

