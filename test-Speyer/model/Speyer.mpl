restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = u(t):
EQNS_T := [ EQ||(1..2)]: <%>;
qvars := [x1(t),x2(t)];
cvars := [u(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  generic=[
    [x1(zeta_i)-x1(zeta_f)=0,"x1_periodic"],
    [x2(zeta_i)-x2(zeta_f)=0,"x2_periodic"]
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = (x1(zeta)^2+x2(zeta)^4)/4-x2(zeta)^2/2+b/2*u(zeta)^2
);
pars := [
  b0 = 0.01,
  b1 = 1e-5,
  b  = b0
];
GUESS := [
  x1 = sin(2*Pi*zeta),
  x2 = cos(2*Pi*zeta) # must be initialized
];
PGUESS := [
];
CONT := [
  [ b = b0*(1-s)+b1*s ]
];
#Describe(generateOCProblem);
generateOCProblem(
  "Speyer",
  parameters       = pars,
  mesh             = [[length=1,n=1000]],
  continuation     = CONT,
  #controls_guess   = [u=1],
  states_guess     = GUESS
);
#ocp := getOCProblem();
#eval(ocp);
;
