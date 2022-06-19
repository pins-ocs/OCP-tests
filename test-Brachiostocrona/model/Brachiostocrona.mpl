restart:
with(plots):;
with(XOptima):;
EQ1    :=      diff(x(zeta),zeta)     = T*v(zeta)*cos(theta(zeta)):
EQ2    :=      diff(y(zeta),zeta)     = T*v(zeta)*sin(theta(zeta)):
EQ3    := mass*diff(v(zeta),zeta)     = -T*g*sin(theta(zeta)):
EQ4    :=      diff(theta(zeta),zeta) = vtheta(zeta):
EQNS_T := [ EQ||(1..4) ]: <%>;
qvars := [x(zeta),y(zeta),v(zeta),theta(zeta)] ;
cvars := [vtheta(zeta)] ;
low := x->y0_low+slope_low*x;
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [x=0,y=0,v=0],
  final   = [x=xf,y=yf]
);
infoBoundaryConditions() ;
addControlBound(
  vtheta,
  scale       = T,
  controlType = "U_QUADRATIC",
  maxabs      = 10,
  epsilon     = 0.001,
  tolerance   = 0.001
);
#addUnilateralConstraint( T > 0,
#                         TimePositive,
#                         scale     = 1,
#                         epsilon   = 0.1,
#                         tolerance = 0.01 ) ;
addUnilateralConstraint(
  y(zeta) > low(x(zeta)),
  LowBound,
  scale     = 1,
  epsilon   = 0,
  tolerance = low_tolerance
);
setTarget( mayer = T );
LEN  := evalf(sqrt(xf^2+yf^2));
TIME := evalf(sqrt(-2*yf/g));
VF   := evalf(LEN/TIME);
PARS := [
  mass           = 1,
  xf             = 5,
  yf             = -2,
  Vf             = VF,
  Tf             = TIME,
  g              = 9.81,
  y0_low         = -0.2,
  slope_low      = -1.5/4,
  low_tolerance0 = 0.1,
  low_tolerance1 = 1e-6,
  low_tolerance  = low_tolerance0
];
GUESS := [
  x     = zeta*xf,
  y     = zeta*yf,
  theta = -Pi/2, #arctan(yf,xf),
  v     = zeta*Vf
];
CONT :=[
  [
    [LowBound,"tolerance"] = pow_average__xo(s,low_tolerance0,low_tolerance1)
  ]
];
project_dir  := "../generated_code";
project_name := "Brachiostocrona";
generateOCProblem(
  project_name,
  admissible_region       = [T>0],
  post_processing         = [ [low(x(zeta)), "low" ] ],
  parameters              = PARS,
  mesh                    = [length=1,n=100],
  optimization_parameters = [T=Tf],
  continuation            = CONT,
  states_guess            = GUESS
) ;
# if used in batch mode use the comment to quit;
