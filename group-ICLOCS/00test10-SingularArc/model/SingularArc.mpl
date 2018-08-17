
# Singular Arc problem (ICLOCS example 10)
# Inizializzazione
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
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars,parameters=pars) ;
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[x1=Pi/2,x2=4,x3=0],
  final=[x2=0,x3=0]
);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType="U_COS_LOGARITHMIC",
  min       = -2,
  max       = 2,
  epsilon   = epsi_ctrl,
  tolerance = tol_ctrl,
  scale     = 1
) ;
addUnilateralConstraint(
  T >0,
  tfbound,
  epsilon   = epsi_T,
  tolerance = tol_T
);
# Post processing functions
setTarget( mayer    = T,
           lagrange = 0 );
pars := [
  epsi_ctrl = 0.01,
  tol_ctrl  = 0.01,
  epsi_T    = 0.01,
  tol_T     = 0.01
] ;

GUESS := [
  x1 = Pi/2,
  x2 = 4,
  x3 = 0,
  T  = 20
];
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem(
  "SingularArc",
  parameters        = pars,
  mesh              = [length=1,n=400],
  continuation      = [],
  #controls_guess    = [u=1],
  states_guess      = GUESS,
  admissible_region = REGION
) ;
#ocp := getOCProblem();
#eval(ocp);

