restart:;
with(XOptima):;
addUserFunction(x_exact(t)=(2*exp(3*t)+exp(3))/(exp(3*t/2)*(2+exp(3))));
addUserFunction(u_exact(t)=2*(exp(3*t)-exp(3))/(exp(3*t/2)*(2+exp(3))));
ode := [diff(x(t),t) = x(t)/2+u(t)]: <%>;
xvars := [x(t)];
uvars := [u(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[x=1]);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = u(zeta)^2+2*x(zeta)^2
);
;
;
PARS := [];
POST := [
  [ x_exact(zeta), "x_exact" ],
  [ u_exact(zeta), "u_exact" ]
];
CONT := [];
GUESS := [ x = 1];
MESHP_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "Hager_2000";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESHP_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
