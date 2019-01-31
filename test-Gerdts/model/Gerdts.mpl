
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Bryson-Ho Problem
# Authors: E. Bertolazzi
# Date:
# 
# Description
# MinimumEnergyProblem used in 
# Structure Exploitation in an Interior- Point Method for Fully Discretized, State Constrained Optimal Control Problems
# by Andreas Huber, Matth ias Gerdts & Enrico Bertolazzi
# Vietnam Journal of Mathematics 2018
# Reference: Bryson, A.E., Ho, Y.-C.: Applied Optimal Control: Optimization, Estimation and Control. CRC Press, Washington (1973)
restart:
with(XOptima):
#`diff/h`   := proc() h_1(args[1])*diff(args[1],args[2]) end:
#`diff/h_1` := proc() h_2(args[1])*diff(args[1],args[2]) end:
with(plots):
# Equations
ODE1 := diff(x1(t),t)=x2(t);
ODE2 := diff(x2(t),t)=u(t);
ODE3 := diff(x3(t),t)=u(t)^2/2;
# ODE+TARGET
xvars := [x1(zeta),x2(zeta),x3(zeta)] ;
uvars := [u(zeta)] ;
ode   := subs(t=zeta,Vector([ODE1,ODE2,ODE3]));
# Problem code generation
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x1,x2,x3],final=[x1,x2]);
infoBoundaryConditions() ;
# Penalty description
addUnilateralConstraint( x1(zeta) <= 1/9, x1Limitation,
                         epsilon = maxEpsi,
                         tolerance = maxTol,
                         scale = 1+0*u(zeta)^2/2 );
setTarget( mayer = x3(zeta_f) ) ;
CONT :=[
  [ 
    [x1Limitation,"epsilon"]   = exp(log(maxEpsi)*(1-s) + log(minEpsi)*s), 
    [x1Limitation,"tolerance"] = exp(log(maxTol)*(1-s) + log(minTol)*s)
  ]
];
MESHF := [
  [length=0.3, n=100],
  [length=0.1, n=50000],
  [length=0.2, n=100],
  [length=0.1, n=50000],
  [length=0.3, n=100]
];
MESHF := [
  [length=1, n=20000]
];
PARS := [
  maxEpsi = 1e-1,
  maxTol  = 1e-1,
  minEpsi = 1e-8,
  minTol  = 1e-8,
  x1_i    = 0,
  x2_i    = 1,
  x3_i    = 0,
  x1_f    = 0,
  x2_f    = -1]
;
generateOCProblem(
  "Gerdts",
  parameters   = PARS,
  mesh         = MESHF,
  continuation = CONT,
  states_guess = [lambda2__xo=0, lambda3__xo=-1 ]
) ;

