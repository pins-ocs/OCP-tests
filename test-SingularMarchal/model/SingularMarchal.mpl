restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x(t),t) = y(t) :
EQ2    := diff(y(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2 ];
qvars := [x(t),y(t)] ;
cvars := [u(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x,y],final=[x,y]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 1,
  scale       = (1/2)*x(zeta)^2+epsilon
);
setTarget( lagrange = (1/2)*x(zeta)^2) ;
PARS := [
  x_i         = 2,
  y_i         = -2,
  x_f         = 2,
  y_f         = 2,
  epsilon_max = 1e-4,
  epsilon_min = 1e-10,
  epsilon     = epsilon_max
];
GUESS := [ x = 0, y = 0];
CONT := [
   [ epsilon = (1-s)*epsilon_max + s * epsilon_min ]
];
project_dir  := "../generated_code";
project_name := "SingularMarchal";
generateOCProblem(
  project_name,
  parameters   = PARS,
  mesh         = [length=8,n=1000], mesh_s0=0,
  continuation = CONT,
  states_guess = GUESS
) ;
# if used in batch mode use the comment to quit;
