restart:
with(XOptima):
XOptimaInfo();
EQ1    := diff(y1(t),t) - y2(t):
EQ2    := diff(y2(t),t) - u(t):
EQNS_T := [ EQ||(1..2) ];
qvars := [y1(t),y2(t)] ;
cvars := [u(t)] ;
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[y1=0,y2=1]
);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = 1e-7,
  tolerance   = 1e-10,
  scale       = 1
);
setTarget( lagrange = y2(zeta)^2+y1(zeta)^2 );
generateOCProblem(
  "SecondOrderSingularRegulator", clean=true,
  parameters   = [ L=5 ],
  mesh         = [ length=L, n=500 ],
  states_guess = [ y2 = 1 ]
);
;
