
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
# ODE+TARGET
xvars := [x1(zeta),x2(zeta)] ;
uvars := [u(zeta)] ;
ode   := subs(t=zeta,Vector([ODE1,ODE2]));
# Problem code generation
loadDynamicSystem(  equations = ode,  controls  = uvars,  states    = xvars);
addBoundaryConditions(  initial=[x1,x2],  final=[x1,x2]);
infoBoundaryConditions() ;
# Penalty description
addUnilateralConstraint(  x1(zeta) <= 1/9, x1Limitation,
  epsilon   = maxEpsi,
  tolerance = maxTol,
  scale     = 1+0*u(zeta)^2/2);
setTarget( lagrange = u(zeta)^2/2 ) ;
addUserFunction(interpLog(s,v0,v1)=v0^(1-s)*v1^s);
CONT :=[
  [ 
    [x1Limitation,"epsilon"]   = interpLog(s,maxEpsi,minEpsi), 
    [x1Limitation,"tolerance"] = interpLog(s,maxTol,minTol)
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
  x1_f    = 0,
  x2_f    = -1];
generateOCProblem(
  "MinimumEnergyProblem",
  parameters   = PARS,
  mesh         = MESHF,
  continuation = CONT
) ;

