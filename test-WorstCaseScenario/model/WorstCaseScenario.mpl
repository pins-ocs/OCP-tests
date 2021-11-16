restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    :=  diff(x(t),t) = (1-2*t)*u(t):
EQNS_T := [ EQ1 ] : <%> ;
qvars := [x(t)];
cvars := [u(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = 0.0001,
  tolerance   = 0.0001,
  scale       = 1
);
setTarget( mayer = x(zeta_f) ) ;
#Describe(generateOCProblem) ;
generateOCProblem(
  "WorstCaseScenario",
  parameters   = [ x_i = 0 ],
  mesh         = [ length=1, n=400 ],
  states_guess = [ x=x_i ]
);
;
