restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = v(t):
EQ2 := diff(v(t),t) = u(t):
EQNS_T := [ EQ1, EQ2 ]: <%>;
qvars := [x(t), v(t)];
cvars := [u(t)];
pars  := [];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [x = 0, v=1],
  final   = [x = 0, v=0]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = x(zeta)^2
);
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = u_max,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = 1
);
pars := [
  u_epsilon_max   = 1e-4,
  u_tolerance_max = 1e-4,
  u_epsilon_min   = 1e-10,
  u_tolerance_min = 1e-10,
  u_epsilon       = u_epsilon_max,
  u_tolerance     = u_tolerance_max,
  u_max           = 1
];
GUESS  := [x=0,v=0];
PGUESS := [];
UGUESS := [ u = 0 ];
CONT := [
  [
    [ "u", "epsilon"   ] = pow_average__xo( s, u_epsilon_max, u_epsilon_min ),
    [ "u", "tolerance" ] = pow_average__xo( s, u_tolerance_max, u_tolerance_min )
  ]
];
POST := [];
Mesh := [
  [length=2,n=200],
  [length=0.8,n=200],
  [length=0.4,n=200],
  [length=0.2,n=200],
  [length=0.1,n=200]
];
#Describe(generateOCProblem);
project_dir  := "../generated_code";
project_name := "ROSS_Fuller";
generateOCProblem(
  project_name,
  parameters              = pars,
  mesh                    = Mesh,
  continuation            = CONT,
  states_guess            = GUESS,
  optimization_parameters = PGUESS,
  post_processing         = POST,
  controls_iterative      = true,
  controls_guess          = UGUESS
);
ocp := getOCProblem();
eval(ocp["FD"]);
eval(ocp["ode"]);
eval(ocp["controls"]["u"]);
# if used in batch mode use the comment to quit;
