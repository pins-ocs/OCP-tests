
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# FlowInAchannel (COPS example 8)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
EQ1    := diff(u(t),t)  = u1(t):
EQ2    := diff(u1(t),t) = u2(t):
EQ3    := diff(u2(t),t) = u3(t):
EQ4    := diff(u3(t),t) = R*(u1(t)*u2(t)-u(t)*u3(t)):
EQNS_T := [ EQ||(1..4)]: <%>;
# State variables and controls
qvars := map([u,u1,u2,u3],(t));
cvars := [];
# Optimal Control: problem definition
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[u=0,u1=0],
  final=[u=1,u1=0]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = 0
);
pars := [
  R = 10000
];

GG := zeta^2*(3 - 2*zeta);
GUESS := [
  u  = GG,
  u1 = diff(GG,zeta),
  u2 = diff(GG,zeta,zeta),
  u3 = diff(GG,zeta,zeta,zeta)
];
CONT := [];
#Describe(generateOCProblem);
generateOCProblem(
  "FlowInAchannel",
  parameters       = pars,
  mesh             = [[length=1,n=100]],
  continuation     = CONT,
  #controls_guess   = [u=1],
  states_guess     = GUESS
);
#ocp := getOCProblem();
#eval(ocp);

