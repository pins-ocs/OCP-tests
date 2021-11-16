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
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations  = EQNS_T,
  controls   = cvars,
  states     = qvars
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
setTarget( mayer = T ) ;
LEN  := evalf(sqrt(xf^2+yf^2));
TIME := evalf(sqrt(-2*yf/g));
VF   := evalf(LEN/TIME);
PARS := [
  mass = 1,
  xf   = 5,
  yf   = -2,
  Vf   = VF,
  Tf   = TIME,
  g    = 9.81
];
GUESS := [
  x     = zeta*xf,
  y     = zeta*yf,
  theta = -Pi/2, #arctan(yf,xf),
  v     = zeta*Vf
];
generateOCProblem(
  "Brachiostocrona",
   admissible_region       = [T>0],
   parameters              = PARS,
   mesh                    = [length=1,n=500],
   optimization_parameters = [T=Tf],
   states_guess            = GUESS
) ;
;
