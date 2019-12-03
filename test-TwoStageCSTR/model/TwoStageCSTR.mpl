
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Two Stage CSTR
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# ITERATIVE DYNAMIC PROGRAMMING, REIN LUUS
# Section 6.3.1 Nonlinear two-stage CSTR system
# CHAPMAN & HALL/CRC Monographs and Surveys in Pure and Applied Mathematics
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
addUserFunction(R1(x1,x2)=(x1+0.5)*exp(25*x2/(x2+2)));
f1 := 0.5-x1(t)-R1(x1(t),x2(t));
EQ1    :=  diff(x1(t),t) = f1:
EQ2    :=  diff(x2(t),t) = f2:
EQ3    :=  diff(x3(t),t) = x1(t)-x3(t)-tau*f1-R2(x3(t),x4(t)) +0.25:
EQ4    :=  diff(x4(t),t) = x2(t)-2*x4(t)-u2(t)*(x4(t)+0.25)-tau*f2+R2(x3(t),x4(t))-0.25:
# States and controls
qvars := map([x1,x2,x3,x4],(t));
cvars := map([u1,u2],(t));
# Optimal Contol Problem
loadDynamicSystem(
addBoundaryConditions(
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
addControlBound(
  u1,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 0.5,
);
  u2,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 0.5,
  epsilon     = epsi,
  tolerance   = tol,
  scale       = 1
);
sumq := x1(zeta)^2+x2(zeta)^2+x3(zeta)^2+x4(zeta)^2;
setTarget(

PARS  := [
GUESS := [
generateOCProblem(
  "TwoStageCSTR", clean = true,
  parameters         = PARS,
  mesh               = [length=2,n=400],
  controls_iterative = true,
);
