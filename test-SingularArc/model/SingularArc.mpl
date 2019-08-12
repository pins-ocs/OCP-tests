
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Singular Arc problem (ICLOCS example 10)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
EQ1    := diff(x1(t),t) = T*u(t):
EQ2    := diff(x2(t),t) = T*cos(x1(t)):
EQ3    := diff(x3(t),t) = T*sin(x1(t)):
EQNS_T := [ EQ||(1..3)]: <%> ;
# State variables and controls
qvars := [x1(t),x2(t),x3(t)] ;
cvars := [u(t)] ;
pars := [T] ;
# Optimal Control: problem definition
loadDynamicSystem(
  equations  = EQNS_T,
  controls   = cvars,
  states     = qvars,
  parameters = pars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[x1,x2,x3],
  final=[x2=0,x3=0]
);
infoBoundaryConditions();
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = -2,
  max         = 2,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
addUnilateralConstraint(
  T>0,
  tfbound,
  epsilon   = epsi_T,
  tolerance = tol_T,
  barrier   = true
);
# Post processing functions
setTarget( mayer = T, lagrange = 0 );
pars := [
  epsi_ctrl0 = 0.01,
  tol_ctrl0  = 0.01,
  epsi_ctrl1 = 0.0001,
  tol_ctrl1  = 0.0001,
  epsi_ctrl  = epsi_ctrl0,
  tol_ctrl   = tol_ctrl0,
  epsi_T     = 0.01,
  tol_T      = 0.1,
  x1_i       = Pi/2,
  x2_i       = 4,
  x3_i       = 0,
  T_init     = 100
] ;

GUESS := [
  x1 = x1_i*(1-zeta),
  x2 = x2_i*(1-zeta),
  x3 = 0,
  lambda3__xo = -1 # must be initialized
];
PGUESS := [
  T = T_init
];
CONT := [
  [ 
    ["u","epsilon"]   = epsi_ctrl0^(1-s)*epsi_ctrl1^s,
    ["u","tolerance"] = tol_ctrl0^(1-s)*tol_ctrl1^s
  ]
];
#Describe(generateOCProblem);
generateOCProblem(
  "SingularArc",
  parameters        = pars,
  mesh              = [length=1,n=400],
  continuation      = CONT,
  #controls_guess    = [u=1],
  states_guess      = GUESS,
  parameters_guess  = PGUESS
) ;
#ocp := getOCProblem();
#eval(ocp);

