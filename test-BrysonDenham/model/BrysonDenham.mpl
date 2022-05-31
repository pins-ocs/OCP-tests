restart:;
with(XOptima):;
;
EQ1 := diff(x(t),t) = v(t):
EQ2 := diff(v(t),t) = u(t):
ode := [ EQ||(1..2)]: <%>;
qvars := [x(t),v(t)];
cvars := [u(t)];
loadDynamicSystem(
  equations = ode,
  controls  = cvars,
  states    = qvars
) ;
addBoundaryConditions(
  initial=[x=0,v=1],
  final=[x=0,v=-1]
);
infoBoundaryConditions();
setTarget( lagrange = u(zeta)^2/2 );
addUnilateralConstraint(
  x(zeta) < 1/9, X1bound,
  barrier   = false,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1
);
;
pars := [
  epsi = 0.0001,
  tol  = 0.0001
];
POST := [
  [ x_exact(zeta), "x_exact" ],
  [ u_exact(zeta), "u_exact" ]
];
CONT := [];
GUESS := [ x = 0, v = 1-2*zeta ];
MESHP_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "BrysonDenham";
generateOCProblem(
  project_name,
  parameters   = pars,
  mesh         = [length=1,n=400],
  states_guess = GUESS
);
;
# if used in batch mode use the comment to quit;
