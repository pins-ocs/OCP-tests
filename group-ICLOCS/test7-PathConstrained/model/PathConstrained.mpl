
# Path Constrained (ICLOCS example 7)
# Inizializzazione
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
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
#Describe(addBoundaryConditions);
addBoundaryConditions(initial=[x1=0,x2=-1]);
infoBoundaryConditions() ;
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 min=-20,
                 max=20,
                 epsilon=epsi_ctrl,
                 tolerance=tol_ctrl,
                 scale=1 ) ;
addUnilateralConstraint(
  8*(zeta-0.5)^2-0.5-x2(zeta)>0,
  x2bound,
  epsilon = epsi_ctrl,
  tolerance = tol_ctrl);
setTarget( mayer    = 0,
           lagrange = 0.005*u(zeta)^2+x1(zeta)^2+x2(zeta)^2 );
pars := [
  epsi_ctrl = 0.0001,
  tol_ctrl  = 0.0001
] ;
GUESS := [
  x1 = 0,
  x2 = -1
];
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem( "PathConstrained",
                    #post_processing = [[T(zeta),"minTime"]],
                    parameters     = pars,
                    mesh           = [length=1,n=400],
                    continuation   = [],
                    controls_guess = [u=0],
                    states_guess   = GUESS,
                    admissible_region = REGION ) ;
ocp := getOCProblem();
eval(ocp["optimal_controls_equations"]);

