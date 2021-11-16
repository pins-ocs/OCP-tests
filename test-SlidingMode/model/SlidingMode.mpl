restart:;
with(XOptima):;
EQ1    :=  diff(x(t),t) = u(t) :
EQ2    :=  diff(y(t),t) = x(t)^2 :
EQNS_T := [ EQ||(1..2) ];
qvars := [x(t),y(t)] ;
cvars := [u(t)] ;
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x,y],final=[x]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1
);
setTarget( mayer = y(zeta_f) ) ;
generateOCProblem(
  "SlidingMode",
   parameters   = [ x_i = 1, x_f=1, y_i=0],
   mesh         = [length=3, n=100],
   states_guess = []
);
;
