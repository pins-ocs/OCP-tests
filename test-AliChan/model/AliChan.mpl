#restart:;
with(XOptima):;
XOptimaInfo();
EQ1    := diff(y1(t),t) - y2(t):
EQ2    := diff(y2(t),t) - u(t):
EQNS_T := [ EQ||(1..2) ];
qvars := [y1(t),y2(t)];
cvars := [u(t)];
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[y1=0,y2=1]
);
infoBoundaryConditions();
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = 1e-10,
  tolerance   = 1e-10,
  scale       = 1
);
setTarget( lagrange = y2(zeta)^2-y1(zeta)^2 );
#setFDorder([x],"forward") ;
generateOCProblem(
  "AliChan", clean=true,
  parameters   = [ epsilon=1e-4, L=Pi/2 ],
  mesh         = [ length=L, n=1000 ],
  states_guess = [ y2 = 1 ]
);
quit;
