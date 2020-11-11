
# 
#            
# Bryson Denham
# Bryson, A. E., Denham, W. F., and Dreyfus, S. E., 
# “Optimal Programming Problems with Inequality Constraints I: Necessary Conditions for Extremal Solutions,” 
# AIAA Journal, Vol. 1, No. 11, 1962, pp. 2544–2550.
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamical system
EQ1    := diff(x(t),t) = v(t):
EQ2    := diff(v(t),t) = u(t):
EQNS_T := [ EQ||(1..2)]: <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(t),v(t)] ;
# Controlli
cvars := [u(t)] ;
# Parametri
pars := [];
# Equazioni del modello matematico del carrello
loadDynamicSystem(
  equations  = EQNS_T,
  controls   = cvars,
  states     = qvars
) ;
# Inserisce condizioni al contorno
addBoundaryConditions(
  initial=[x=0,v=1],
  final=[x=0,v=-1]
);
infoBoundaryConditions() ;
# Penalty
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

