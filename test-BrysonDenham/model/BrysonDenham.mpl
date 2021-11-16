restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x(t),t) = v(t):
EQ2    := diff(v(t),t) = u(t):
EQNS_T := [ EQ||(1..2)]: <%> ;
qvars := [x(t),v(t)] ;
cvars := [u(t)] ;
pars := [];
loadDynamicSystem(
  equations  = EQNS_T,
  controls   = cvars,
  states     = qvars
) ;
addBoundaryConditions(
  initial=[x=0,v=1],
  final=[x=0,v=-1]
);
infoBoundaryConditions() ;
setTarget( lagrange = u(zeta)^2/2 );
addUnilateralConstraint(
  x(zeta) < 1/9, X1bound,
  barrier   = false,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1
);
pars := [
  epsi = 0.0001,
  tol  = 0.0001
];
GUESS := [
  x = 0,
  v = 1-2*zeta
];
REGION := [
];
generateOCProblem(
  "BrysonDenham",
  parameters        = pars,
  mesh              = [length=1,n=400],
  states_guess      = GUESS,
  admissible_region = REGION
);
;
