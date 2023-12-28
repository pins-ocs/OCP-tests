restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = T*v(t):
EQ2 := diff(v(t),t) = T*F(t):;
ode := [EQ||(1..2)]:<%>;
xvars := [x(t),v(t)];
uvars := [F(t)];
loadDynamicSystem(equations=ode,controls=uvars,states=xvars);
addBoundaryConditions(initial=[x=x0,v=v0],final=[x=x1,v=v1]);
infoBoundaryConditions();
setTarget( mayer = T );
addControlBound(
  F,
  label  = Fcontrol,
  maxabs = 1,
  scale  = T
);
addUnilateralConstraint(
  T >= 0,
  T_limit,
  tolerance = 0.01,
  epsilon   = 0.01
);
PARS := [
  x0 = 0,
  v0 = 0,
  x1 = 2,
  v1 = 0,
  T_guess = 10 
];
POST := [
  [ zeta*T, "time" ]
];
CONTINUATION := [];
GUESS := [ x = zeta, v = 1 ];
MESH_DEF := [ length=1, n=100 ];
project_dir  := "../generated_code";
project_name := "BangBangFtmin";
generateOCProblem(
  project_name,
  admissible_region       = [ [ T > 0, "pars" ] ],
  optimization_parameters = [ T = T_guess ],
  post_processing         = POST,
  parameters              = PARS,
  continuation            = CONTINUATION,
  mesh                    = MESH_DEF,
  states_guess            = GUESS
);
# if used in batch mode use the comment to quit;
