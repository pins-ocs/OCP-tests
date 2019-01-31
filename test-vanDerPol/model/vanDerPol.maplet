
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: van Der Pool
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    := diff(x1(zeta),zeta) = x2(zeta):
EQ2    := diff(x2(zeta),zeta) = (1-x1(zeta)^2)*x2(zeta)-x1(zeta)+u(zeta):
EQNS_T := [ EQ||(1..2) ]: <%> ;
# States and Controls
qvars := [x1(zeta),x2(zeta)] ;
cvars := [u(zeta)] ;
# Equations of the mathematical model of the cart
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# boundary conditions
addBoundaryConditions(initial=[x1=1,x2=0]);
infoBoundaryConditions() ;
# Post processing functions
setTarget( lagrange = (x1(zeta)^2+x2(zeta)^2+u(zeta)^2)/2 ) ;

generateOCProblem(  "vanDerPol",
  parameters   = [],
  mesh         = [length=5,n=1000],
  #continuation = cont,
  states_guess = []);

