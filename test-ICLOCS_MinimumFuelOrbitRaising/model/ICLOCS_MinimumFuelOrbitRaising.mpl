restart:;
with(XOptima);
addUserFunction(mass(t)=1-md*t);
EQ1    := diff(r(t),t)  = vr(t):
EQ2    := diff(vr(t),t) = vt(t)^2/r(t)-1/r(t)^2+T*sin(theta(t))/mass(t):
EQ3    := diff(vt(t),t) = -vr(t)*vt(t)/r(t)+T*cos(theta(t))/mass(t):
EQNS_T := [ EQ||(1..3)]: <%>;
qvars := [r(t),vr(t),vt(t)] ;
cvars := [theta(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[r=1,vr=0,vt=1],
  final=[vr=0],
  generic=[
    [r(zeta_f)*vt(zeta_f)^2=1,"rvt"]
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = -vr(zeta)
);
;
;
PARS := [
  theta_max = Pi,
  T         = 0.1405,
  md        = 0.0749,
  tf        = 3.32
];
POST := [
  [ theta(zeta) - floor(theta(zeta)/(2*Pi))*(2*Pi), "THETA" ],
  [ mass(zeta), "MASS" ]
];
CONT := [
];
GUESS := [
  r  = 1,
  vr = 0,
  vt = 1,
  lambda3__xo = -1e-10
];
REGION := [
  [ theta(zeta) >= -theta_max, "u" ],
  [ theta(zeta) <=  theta_max, "u" ]
];
MESH_DEF := [length=tf,n=400];
project_dir  := "../generated_code";
project_name := "ICLOCS_MinimumFuelOrbitRaising";
U_SOLVED := [theta = arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))];
generateOCProblem(
  project_name, clean = false,
  post_processing       = POST,
  parameters            = PARS,
  user_parameters       = [ theta_max ],
  mesh                  = MESH_DEF,
  continuation          = CONT,
  controls_iterative    = false,
  controls_guess        = U_SOLVED,
  controls_user_defined = U_SOLVED,
  states_guess          = GUESS,
  admissible_region     = REGION
);
ocp := getOCProblem();
eval(ocp["controls"]);
collect(ocp["controls"]["g_fun"],[sin,cos,theta]);
subs(theta(zeta_M)=TH,%):
simplify(diff(%,TH));
ocp["controls"]["g"];
#eval(ocp);
# if used in batch mode use the comment to quit;
