restart:;
with(XOptima):;
addUserFunction(interpLog(s,v0,v1)=v0^(1-s)*v1^s);
ODE1 := diff(x1(t),t)=x2(t);
ODE2 := diff(x2(t),t)=u(t);
ode := subs(t=zeta,Vector([ODE1,ODE2]));
xvars := [x1(zeta),x2(zeta)];
uvars := [u(zeta)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[x1,x2],final=[x1,x2]);
infoBoundaryConditions();
setTarget( lagrange = u(zeta)^2/2 + c/2 * x1(zeta)^2 );
;
addUnilateralConstraint(
  x1(zeta) <= 1/9, x1Limitation,
  epsilon   = epsi,
  tolerance = tol,
  scale     = 1+0*u(zeta)^2/2
);
PARS := [
  max_epsi = 0.1,      max_tol = 0.1,
  min_epsi = 1e-8,     min_tol = 1e-8,
  epsi     = max_epsi, tol     = max_tol,
  x1_i     = 0,
  x2_i     = 1,
  x1_f     = 0,
  x2_f     = -1,
  c        = 0
];
POST := [];
CONT :=[
  [ 
    [x1Limitation,"epsilon"]   = interpLog(s,max_epsi,min_epsi), 
    [x1Limitation,"tolerance"] = interpLog(s,max_tol,min_tol)
  ]
];
GUESS := [ ];
MESHF := [
  [length=0.3, n=10],
  [length=0.1, n=500],
  [length=0.2, n=10],
  [length=0.1, n=500],
  [length=0.3, n=10]
];
MESHF1 := [
  [length=1, n=1000]
];
project_dir  := "../generated_code";
project_name := "MinimumEnergyProblem";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESHF1,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
