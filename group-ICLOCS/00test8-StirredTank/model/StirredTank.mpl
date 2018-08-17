
# Continuously-stirred tank reactor (ICLOCS example 8)
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
EQ1    := diff(x1(t),t) = T*((1-x1(t))/q - k*exp(-En/x2(t))):
EQ2    := diff(x2(t),t) = T*((Tf-x2(t))/q+k*exp(-En/x2(t))-a*u(t)*(x2(t)-Tc)):
EQNS_T := [ EQ||(1..2)]: <%> ;
# State variables and controls
qvars := [x1(t),x2(t)] ;
cvars := [u(t)] ;
pars := [T] ;
# Optimal Control: problem definition
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars,parameters=pars) ;
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[x1,x2],
  final=[x1,x2]
);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType="U_COS_LOGARITHMIC",
  min       = 0,
  max       = 2,
  epsilon   = epsi_ctrl,
  tolerance = tol_ctrl,
  scale     = 1
) ;
addUnilateralConstraint(
  T >10,
  tfbound,
  epsilon   = epsi_T,
  tolerance = tol_T
);
setTarget( mayer    = 0,
           lagrange = (x1(zeta)-x1_f)^2+(x2(zeta)-x2_f)^2+(u(zeta)-u_f)^2 );
pars := [
  epsi_ctrl = 0.01,
  tol_ctrl  = 0.01,
  epsi_T    = 0.01,
  tol_T     = 0.01,
  a         = 0.000195*600,
  q         = 20,
  k         = 300,
  En        = 5,
  Tc        = 0.38158,
  Tf        = 0.3947,
  x1_i      = 0.98,
  x2_i      = 0.39,
  x1_f      = 0.26,
  x2_f      = 0.65,
  u_f       = 0.76
] ;

GUESS := [
  x1 = x1_i,
  x2 = x2_i,
  T  = 20
];
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem(
  "StirredTank",
  parameters        = pars,
  mesh              = [length=1,n=400],
  continuation      = [],
  controls_guess    = [u=1],
  states_guess      = GUESS,
  admissible_region = REGION
) ;
ocp := getOCProblem();
eval(ocp["optimal_controls_equations"]);

