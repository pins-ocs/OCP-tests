
# Minimum Fuel Orbit Raising (ICLOCS example 6)
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = x3(t)^3/x1(t)-1/x1(t)^2+T*sin(u(t))/(1-md*t):
EQ3    := diff(x3(t),t) = -x2(t)*x3(t)/x1(t)+T*cos(u(t))/(1-md*t):
EQNS_T := [ EQ||(1..3)]: <%> ;
# State variables and controls
qvars := [x1(t),x2(t),x3(t)] ;
cvars := [u(t)] ;
# Optimal Control: problem definition
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[x1=1,x2=0,x3=1],
  final=[x2=0],
  generic=[[x3(zeta_f)*sqrt(x1(zeta_f))-1=0,"x3x1"]]
);
infoBoundaryConditions() ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 min=0,
                 max=2*Pi,
                 epsilon=epsi_ctrl,
                 tolerance=tol_ctrl,
                 scale=1 ) ;
setTarget( mayer    = 0,
           lagrange = -x2(zeta) );

pars := [
  epsi_ctrl = 0.001,
  tol_ctrl  = 0.001,
  T         = 0.1405,
  md        = 0.0749
] ;
GUESS := [
  x1 = 1,
  x2 = 0,
  x3 = 1
]; #lambda3=-1
;
REGION := [
];
#Describe(generateOCProblem);
generateOCProblem( "MinimumFuelOrbitRaising",
                    #post_processing = [[T(zeta),"minTime"]],
                    parameters     = pars,
                    mesh           = [length=3.32,n=400],
                    continuation   = [],
                    controls_guess = [u=Pi],
                    states_guess   = GUESS,
                    admissible_region = REGION ) ;
ocp := getOCProblem();
eval(ocp["optimal_controls_equations"]);

