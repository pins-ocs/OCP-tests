restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = T*v(t):
EQ2 := diff(v(t),t) = T*F(t)/mass:
ode := [EQ||(1..2)]: <%>;
xvars := [x(t),v(t)];
uvars := [F(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [x=0,v=0],
  final   = [x=1,v=0]
);
infoBoundaryConditions();
setTarget( lagrange = T*F(zeta)^2, mayer = T );
PARS := [ mass = 1 ];
POST := [
];
CONTINUATION := [
];
GUESS  := [v=1];
PGUESS := [T=1];
MESH_DEF := [length=1,n=100];
project_dir  := "../generated_code";
project_name := "BertolazziCorsoExample1";
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  continuation            = CONTINUATION,
  mesh                    = MESH_DEF,
  states_guess            = GUESS,
  optimization_parameters = PGUESS
);
# if used in batch mode use the comment to quit;
