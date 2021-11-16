restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x1(t),t) = u(t)*( 10*x2(t) - x1(t) ):
EQ2    := diff(x2(t),t) = u(t)*( x1(t) - 10*x2(t) ) - (1-u(t))*x2(t):
EQNS_T := [ EQ||(1..2)]: <%> ;
qvars := [x1(t),x2(t)] ;
cvars := [u(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x1,x2]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
setTarget(
  mayer    = -1+x1(zeta_f)+x2(zeta_f),
  lagrange = 0
);
pars := [
  x1_i      = 1,
  x2_i      = 0,
  epsi_ctrl = 0.00001,
  tol_ctrl  = 0.00001
] ;
GUESS := [
  x1 = x1_i,
  x2 = x2_i
];
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem(
  "Catalyst",
  #post_processing = [[T(zeta),"minTime"]],
  parameters     = pars,
  mesh           = [length=1,n=400],
  continuation   = [],
  #controls_guess = [u=2+(zeta/126)*8],
  states_guess   = GUESS,
  admissible_region = REGION
);
#ocp := getOCProblem();
;
