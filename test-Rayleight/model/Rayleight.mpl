restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x1(zeta),zeta) = x2(zeta):
EQ2    := diff(x2(zeta),zeta) = -x1(zeta)+(1.4-0.14*x2(zeta)^2)*x2(zeta)+4*u(zeta):
EQNS_T := [ EQ||(1..2) ]: <%> ;
qvars := [x1(zeta),x2(zeta)] ;
cvars := [u(zeta)] ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x1=-5,x2=-5]);
infoBoundaryConditions() ;
setTarget( lagrange = x1(zeta)^2+u(zeta)^2 ) ;
generateOCProblem(
  "Rayleight",
  parameters   = [],
  mesh         = [length=2.5,n=1000],
  #continuation = cont,
  states_guess = []
);
;
