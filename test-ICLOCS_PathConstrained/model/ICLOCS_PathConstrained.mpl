restart:;
with(XOptima):;
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = -x2(t)+u(t):
EQNS_T := [ EQ||(1..2)]: <%>;
qvars := [x1(t),x2(t)];
cvars := [u(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x1=0,x2=-1]);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = 0.005*u(zeta)^2+x1(zeta)^2+x2(zeta)^2
);
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = -20,
  max         = 20,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
addUnilateralConstraint(
  8*(zeta-0.5)^2-0.5-x2(zeta)>0,
  x2bound,
  epsilon   = epsi_ctrl,
  tolerance = tol_ctrl
);
PARS := [
  epsi_ctrl0 = 0.01,
  tol_ctrl0  = 0.01,
  epsi_ctrl1 = 0.000001,
  tol_ctrl1  = 0.000001,
  epsi_ctrl  = epsi_ctrl0,
  tol_ctrl   = tol_ctrl0
];
CONT := [
  [
    ["x2bound", "epsilon"]   = epsi_ctrl0^(1-s)*epsi_ctrl1^s,
    ["x2bound", "tolerance"] = tol_ctrl0^(1-s)*tol_ctrl1^s,
    ["u",       "epsilon"]   = epsi_ctrl0^(1-s)*epsi_ctrl1^s,
    ["u",       "tolerance"] = tol_ctrl0^(1-s)*tol_ctrl1^s
  ]
];
GUESS := [
  x1 = 0,
  x2 = -1
];
MESH_DEF := [length=1, n=400];
project_dir  := "../generated_code";
project_name := "ICLOCS_PathConstrained";
generateOCProblem(
  project_name,
  #post_processing  = [[T(zeta),"minTime"]],
  parameters        = PARS,
  mesh              = MESH_DEF,
  continuation      = CONT,
  controls_guess    = [u=0],
  states_guess      = GUESS,
  continuation      = CONT
);
# if used in batch mode use the comment to quit;
