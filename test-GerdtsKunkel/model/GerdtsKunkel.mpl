restart:;
with(XOptima):;
#`diff/h`   := proc() h_1(args[1])*diff(args[1],args[2]) end:;
#`diff/h_1` := proc() h_2(args[1])*diff(args[1],args[2]) end:;
with(plots):;
ODE1 := diff(x1(t),t)=x2(t);
ODE2 := diff(x2(t),t)=u(t);
ODE3 := diff(x3(t),t)=u(t)^2/2;
ode   := subs(t=zeta,Vector([ODE1,ODE2,ODE3]));
xvars := [x1(zeta),x2(zeta),x3(zeta)] ;
uvars := [u(zeta)] ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x1,x2,x3],final=[x1,x2]);
infoBoundaryConditions() ;
addUnilateralConstraint(
  x1(zeta) <= 1/9, x1Limitation,
  epsilon   = epsilon,
  tolerance = tolerance,
  scale = 1+0*u(zeta)^2/2
);
setTarget( mayer = x3(zeta_f) ) ;
PARS := [
  x1_i = 0,
  x2_i = 1,
  x3_i = 0,
  x1_f = 0,
  x2_f = -1,
  epsilon_max   = 1e-4,
  epsilon_min   = 1e-8,
  epsilon       = epsilon_max,
  tolerance_max = 1e-4,
  tolerance_min = 1e-8,
  tolerance     = tolerance_max
];
GUESS := [
  lambda2__xo=0,
  lambda3__xo=-1
];
CONT := [
  [
    ["x1Limitation","epsilon"]   = (1-s)*epsilon_max+s*epsilon_min,
    ["x1Limitation","tolerance"] = (1-s)*tolerance_max+s*tolerance_min
  ]
];
project_dir  := "../generated_code";
project_name := "GerdtsKunkel";
generateOCProblem(
  project_name,
  parameters   = PARS,
  continuation = CONT,
  mesh         = [length=1, n=100],
  states_guess = GUESS
);
# if used in batch mode use the comment to quit;
