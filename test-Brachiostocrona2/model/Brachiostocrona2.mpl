
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Brachiostocrona
# Authors: E. Bertolazzi, F. Biral
# Date: December 18, 2018
# 
# Load Packages
# Load maple packages
restart: with(plots):
with(XOptima):
# Equations of motion
EQ1    :=      diff(x(zeta),zeta)     = T*v(zeta)*cos(theta(zeta)):
EQ2    :=      diff(y(zeta),zeta)     = T*v(zeta)*sin(theta(zeta)):
EQ3    := mass*diff(v(zeta),zeta)     = -T*g*sin(theta(zeta)):
EQNS_T := [ EQ||(1..3) ]: <%>;
# State variables and controls
qvars := [x(zeta),y(zeta),v(zeta)] ;
cvars := [theta(zeta)] ;
# OCP
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
#addUnilateralConstraint( T > 0,
#                         TimePositive,
#                         scale     = 1,
#                         epsilon   = 0.1,
#                         tolerance = 0.01 ) ;
# Generazione del problema di controllo ottimo
setTarget( mayer = T ) ;

LEN  := evalf(sqrt(xf^2+yf^2));
TIME := evalf(sqrt(-2*yf/g));
VF   := evalf(LEN/TIME);
PARS := [
  mass  = 1,
  xf    = 5,
  yf    = -2,
  Vf    = VF,
  Tf    = TIME,
  g     = 9.81,
  kappa = 1
];
GUESS := [
  x = zeta*xf,
  y = zeta*yf,
  v = zeta*Vf,
  lambda1__xo = 1e-6
];
addUserFunction( arctan2( y, x),derivatives=1 );
addUserFunction( theta_sol( v, l1, l2, l3) = kappa*Pi+arctan2(v*l2-l3*g,v*l1),derivatives=1);
USOL := [ theta = theta_sol( v(zeta),
                             lambda1__xo(zeta),
                             lambda2__xo(zeta),
                             lambda3__xo(zeta) )];
generateOCProblem(
  "Brachiostocrona2",
   admissible_region       = [T>0],
   parameters              = PARS,
   mesh                    = [length=1,n=500],
   optimization_parameters = [T=Tf],
   controls_user_defined   = USOL, 
   states_guess            = GUESS
) ;

