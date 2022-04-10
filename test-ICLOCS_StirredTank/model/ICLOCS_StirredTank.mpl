restart:;
with(XOptima):;
REACT := k*x1(t)*exp(-En/x2(t));
EQ1 := diff(x1(t),t) = TimeSize*((1-x1(t))/theta - REACT):
EQ2 := diff(x2(t),t) = TimeSize*((Tf-x2(t))/theta + REACT-a*u(t)*(x2(t)-Tc)):
EQNS_T := [ EQ||(1..2)]: <%>;
xvars := [x1(t),x2(t)];
uvars := [u(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [x1,x2],
  final   = [x1,x2]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = TimeSize*(w_time+(x1(zeta)-x1_f)^2+(x2(zeta)-x2_f)^2+(u(zeta)-u_f)^2)
);
addControlBound(
  u,
  controlType = "U_LOGARITHMIC",
  min         = 0,
  max         = 2,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
addUnilateralConstraint(
  TimeSize >= T_min,
  tfbound,
  epsilon   = epsi_T,
  tolerance = tol_T,
  barrier   = true
);
addBilateralConstraint(
  x1(zeta),
  x1bound,
  min       = 0,
  max       = 1,
  epsilon   = x_epsi,
  tolerance = x_tol,
  barrier   = true
);
addBilateralConstraint(
  x2(zeta),
  x2bound,
  min       = 0,
  max       = 1,
  epsilon   = x_epsi,
  tolerance = x_tol,
  barrier   = true
);
PARS := [


  epsi_ctrl0 = 0.1,
  epsi_ctrl1 = 0.001,
  epsi_ctrl  = epsi_ctrl0,


  tol_ctrl0  = 0.1,
  tol_ctrl1  = 0.001,
  tol_ctrl   = tol_ctrl0,

  x_epsi    = 0.01,
  x_tol     = 0.01,

  epsi_T    = 0.01,
  tol_T     = 1,

  a         = 600*0.000195,
  theta     = 20,
  k         = 300,
  En        = 5,


  Tc        = 0.38158,
  Tf        = 0.3947,

  x1_i      = 0.98,
  x2_i      = 0.39,


  x1_f      = 0.2632,
  x2_f      = 0.6519,


  u_f       = 0.76,

  T_guess   = 90,
  T_min     = 10,

  w_time_max = 1,
  w_time_min = 0.01,
  w_time     = w_time_max
];
POST := [
  [TimeSize*zeta, "time"]
];
CONT := [
  [
    w_time = w_time_max + s*(w_time_min-w_time_max)
  ],
  [ 
    ["u","epsilon"]   = epsi_ctrl0+s*(epsi_ctrl1-epsi_ctrl0),
    ["u","tolerance"] = tol_ctrl0+s*(tol_ctrl1-tol_ctrl0)
  ]
];
GUESS := [
  x1 = x1_f,
  x2 = x2_f
];
PGUESS := [ TimeSize = T_guess ];
REGION := [
#  [ x1(zeta) >= 0,     "node" ],
#  [ x1(zeta) <= 1,     "node" ],
#  [ x2(zeta) >= 0,     "node" ],
#  [ x2(zeta) <= 1,     "node" ],
#  [ TimeSize >= T_min, "pars" ]
];
MESHP_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "ICLOCS_StirredTank";
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  mesh                    = [length=1,n=400],
  controls_iterative      = true,
  controls_guess          = [u=u_f],
  states_guess            = GUESS,
  optimization_parameters = PGUESS,
  continuation            = CONT,
  admissible_region       = REGION
);
# if used in batch mode use the comment to quit;
