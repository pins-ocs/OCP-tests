
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# Path Constrained (ICLOCS example 7)
# Authors: E. Bertolazzi, F. Biral
# Date:
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = -x2(t)+u(t):
EQNS_T := [ EQ||(1..2)]: <%> ;
# State variables and controls
qvars := [x1(t),x2(t)] ;
cvars := [u(t)] ;
# Optimal Control: problem definition
loadDynamicSystem(
#Describe(addBoundaryConditions);
addBoundaryConditions(initial=[x1=0,x2=-1]);
infoBoundaryConditions() ;
addControlBound(
  controlType = "U_COS_LOGARITHMIC",
  min         = -20,
  max         = 20,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
addUnilateralConstraint(
  8*(zeta-0.5)^2-0.5-x2(zeta)>0,
  x2bound,
  epsilon   = epsi_ctrl,
  tolerance = tol_ctrl
setTarget(
  lagrange = 0.005*u(zeta)^2+x1(zeta)^2+x2(zeta)^2
pars := [
  epsi_ctrl0 = 0.01,
  tol_ctrl0  = 0.01,
  epsi_ctrl1 = 0.000001,
  tol_ctrl1  = 0.000001,
  epsi_ctrl  = epsi_ctrl0,
  tol_ctrl   = tol_ctrl0
] ;
GUESS := [
  x1 = 0,
  x2 = -1
];
CONT := [
    ["u", "epsilon"]   = epsi_ctrl0^(1-s)*epsi_ctrl1^s,
    ["u", "tolerance"] = tol_ctrl0^(1-s)*tol_ctrl1^s
]
;
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem(
  #post_processing  = [[T(zeta),"minTime"]],
  parameters        = pars,
  mesh              = [length=1,n=400],
  continuation      = [],
  controls_guess    = [u=0],
  states_guess      = GUESS,
  continuation      = CONT,
ocp := getOCProblem();
eval(ocp["optimal_controls_equations"]);
