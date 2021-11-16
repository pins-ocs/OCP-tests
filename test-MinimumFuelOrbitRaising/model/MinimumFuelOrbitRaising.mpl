restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = x3(t)^3/x1(t)-1/x1(t)^2+T*sin(u(t))/(1-md*t):
EQ3    := diff(x3(t),t) = -x2(t)*x3(t)/x1(t)+T*cos(u(t))/(1-md*t):
EQNS_T := [ EQ||(1..3)]: <%> ;
qvars := [x1(t),x2(t),x3(t)] ;
cvars := [u(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[
    x1=1,
    x2=0,
    x3=1
  ],
  final=[
    x2=0
  ],
  generic=[
    [x1(zeta_f)*x3(zeta_f)^2=1,"x3x1"]
  ]
);
infoBoundaryConditions() ;
setTarget(
  mayer    = 0,
  lagrange = -x2(zeta)
);
pars := [
  epsi_ctrl = 0.001,
  tol_ctrl  = 0.001,
  T         = 0.1405,
  md        = 0.0749,
  tf        = 3.32
] ;
GUESS := [
  x1 = 1,
  x2 = 0,
  x3 = 1,
  lambda3__xo = -1e-10 # must be initialized <> 0
];
REGION := [
];
U_SOLVED := [u = arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))];
#Describe(generateOCProblem);
generateOCProblem(
  "MinimumFuelOrbitRaising",
  #post_processing = [[T(zeta),"minTime"]],
  parameters        = pars,
  mesh              = [length=tf,n=400],
  continuation      = [],
  #controls_iterative = true,
  #controls_guess    = [u=Pi],
  controls_user_defined = U_SOLVED,
  states_guess      = GUESS,
  admissible_region = REGION
);
ocp := getOCProblem();
indices(ocp);
eval(ocp["controls"]["g"]); solve( %[1], {u(zeta)} );
SOL := eval(ocp["controls"]["u"][1]);
subs(u=SOL,diff(subs(u(zeta)=u,ocp["Hamiltonian"]),u,u)); simplify(expand(%));
;
