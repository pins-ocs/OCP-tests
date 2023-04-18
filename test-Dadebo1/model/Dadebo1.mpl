restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    :=  diff(x(t),t) = u(t):
EQ2    :=  diff(y(t),t) = x(t)^2+u(t)^2:
EQNS_T := [ EQ1, EQ2 ]:<%>;
qvars := [x(t),y(t)];
cvars := [u(t)];
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x=1,y=0],final=[x=1]);
infoBoundaryConditions();
setTarget( mayer = y(zeta_f));
GUESS := [
  x = 1,
  y = 0,
  #lambda1__xo = -0.0001
  lambda2__xo = 1 # must be > 0
];
U_GUESS := [ u = 0 ];
#Describe(generateOCProblem);
project_dir  := "../generated_code";
project_name := "Dadebo1";
generateOCProblem(
  project_name,
  mesh           = [length=1,n=100], mesh_s0=0,
  states_guess   = GUESS,
  controls_guess = U_GUESS
);
# if used in batch mode use the comment to quit;
