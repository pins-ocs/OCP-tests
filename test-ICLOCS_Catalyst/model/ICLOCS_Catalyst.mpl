restart:;
with(XOptima):;
EQ1    := diff(x1(t),t) = u(t)*( 10*x2(t) - x1(t) ):
EQ2    := diff(x2(t),t) = u(t)*( x1(t) - 10*x2(t) ) - (1-u(t))*x2(t):
EQNS_T := [ EQ||(1..2)]: <%>;
qvars := [x1(t),x2(t)];
cvars := [u(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x1,x2]);
infoBoundaryConditions();
setTarget(
  mayer    = -1+x1(zeta_f)+x2(zeta_f),
  lagrange = 0
);
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
;
PARS := [
  x1_i      = 1,
  x2_i      = 0,
  epsi_ctrl = 0.00001,
  tol_ctrl  = 0.00001
];
POST := [];
CONT := [];
GUESS := [
  x1 = x1_i,
  x2 = x2_i
];
MESH_DEF := [length=1, n=400];
project_dir  := "../generated_code";
project_name := "ICLOCS_Catalyst";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
