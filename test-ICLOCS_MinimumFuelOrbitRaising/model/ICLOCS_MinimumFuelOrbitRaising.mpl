restart:;
with(XOptima):;
addUserFunction(mass(t)=1-md*t);
addUserFunction(guess_r(t)=1);
addUserFunction(guess_vr(t)=0);
addUserFunction(guess_vt(t)=1);
addUserFunction(guess_theta(t)=(t/tf)*(theta_max-theta_min)+theta_min);
EQ1    := diff(r(t),t)  = vr(t):
EQ2    := diff(vr(t),t) = vt(t)^2/r(t)-1/r(t)^2+T*sin(theta(t))/mass(t):
EQ3    := diff(vt(t),t) = -vr(t)*vt(t)/r(t)+T*cos(theta(t))/mass(t):
EQNS_T := [ EQ||(1..3)]: <%>;
qvars := [r(t),vr(t),vt(t)];
cvars := [theta(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [r=1,vr=0,vt=1],
  final   = [vr=0],
  generic = [[r(zeta_f)*vt(zeta_f)^2=1,"rvt"]]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = -vr(zeta)+epsilon*(theta(zeta)-guess_theta(zeta))^2 +
             WG*( (r(zeta)-guess_r(zeta))^2 + 
                  (vr(zeta)-guess_vr(zeta))^2 + 
                  (vt(zeta)-guess_vt(zeta))^2 )
);
;
;
PARS := [
  WG0         = 1,
  WG          = WG0,
  theta_max   = 5,
  T           = 0.1405,
  md          = 0.0749,
  tf          = 3.32,
  epsilon     = epsilon_max,
  epsilon_max = 1,
  epsilon_min = 0,
  theta_min   = 1,
  theta_max   = 4
];
POST := [
  [ guess_theta(zeta), "THETA_guess" ],
  [ theta_max,         "THETA_max" ],
  [ theta_min,         "THETA_min" ],
  [ mass(zeta),        "MASS" ],
  [ cos(theta(zeta)),  "COSTHETA" ],
  [ sin(theta(zeta)),  "SINTHETA" ]
];
CONT := [
  [ WG      = WG0*(1-s) ],
  [ epsilon = epsilon_max*(1-s)+epsilon_min*s ]
];
GUESS := [
  r  = guess_r(zeta),
  vr = guess_vr(zeta),
  vt = guess_vt(zeta)
];
REGION := [
];
MESH_DEF := [length=tf,n=400];
project_dir  := "../generated_code";
project_name := "ICLOCS_MinimumFuelOrbitRaising";
U_SOLVED := [
  theta = arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))
];
generateOCProblem(
  project_name, clean = false,
  post_processing       = POST,
  parameters            = PARS,
  user_parameters       = [ theta_max ],
  mesh                  = MESH_DEF,
  continuation          = CONT,
  controls_iterative    = false,
  controls_guess        = [theta=0],
  #controls_user_defined = U_SOLVED,
  states_guess          = GUESS,
  admissible_region     = REGION
);
# if used in batch mode use the comment to quit;
