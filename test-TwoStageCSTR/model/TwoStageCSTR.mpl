restart:;
with(XOptima);
addUserFunction(R1(x1,x2)=(x1+0.5)*exp(25*x2/(x2+2)));
addUserFunction(R2(x3,x4)=(x3+0.25)*exp(25*x4/(x4+2)));
f1 := 0.5-x1(t)-R1(x1(t),x2(t));
f2 := R1(x1(t),x2(t))-(x2(t)+0.25)*(2+u1(t));
EQ1    := diff(x1(t),t) = f1:
EQ2    := diff(x2(t),t) = f2:
EQ3    := diff(x3(t),t) = x1(t)-x3(t)-tau*f1-R2(x3(t),x4(t)) +0.25:
EQ4    := diff(x4(t),t) = x2(t)-2*x4(t)-u2(t)*(x4(t)+0.25)-tau*f2+R2(x3(t),x4(t))-0.25:
EQNS_T := [ EQ||(1..4) ]:<%>;
qvars := map([x1,x2,x3,x4],(t));
cvars := map([u1,u2],(t));
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions( initial=[x1,x2,x3,x4] );
infoBoundaryConditions() ;
sumq := x1(zeta)^2+x2(zeta)^2+x3(zeta)^2+x4(zeta)^2;
setTarget(
  lagrange = sumq+W*(u1(zeta)^2+u2(zeta)^2)
);
addControlBound(
  u1,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 0.5,
  epsilon     = epsi,
  tolerance   = tol,
  scale       = 1
);
addControlBound(
  u2,
  controlType = "U_COS_LOGARITHMIC", 
  maxabs      = 0.5,
  epsilon     = epsi,
  tolerance   = tol,
  scale       = 1
);
;
PARS := [
  x1_i = 0.15,
  x2_i = -0.03,
  x3_i = 0.1,
  x4_i = 0,
  tau  = 0.1,
  W    = 0.1,
  epsi = 0.0001,
  tol  = 0.0001
];
POST := [];
CONT := [];
GUESS  := [ x1 = x1_i, x2 = x2_i ];
CGUESS := [u1=0,u2=0];
MESHP_DEF := [length=2,n=400];
project_dir  := "../generated_code";
project_name := "TwoStageCSTR";
generateOCProblem(
  "TwoStageCSTR", clean = true,
  parameters         = PARS,
  mesh               = MESHP_DEF,
  controls_iterative = true,
  controls_guess     = CGUESS,
  states_guess       = GUESS
);
# if used in batch mode use the comment to quit;
