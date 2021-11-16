restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    :=  diff(x(t),t) = u(t) :
EQNS_T := [ EQ1 ];
qvars := [x(t)] ;
cvars := [u(t)] ;
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
#addBoundaryConditions(initial=[x,v],final=[v]);
#setBCActivationStatus(initial=[x,v],final=[v]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1
);
setTarget( lagrange = (x(zeta)-1+zeta^2)^2 ) ;
generateOCProblem(
  "SingularCalogero",
  mesh = [ length=2, n=100 ], mesh_s0=-1,
  states_guess = [ x= 0]
);
;
