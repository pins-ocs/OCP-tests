restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    := diff(u(t),t)  = u1(t):
EQ2    := diff(u1(t),t) = u2(t):
EQ3    := diff(u2(t),t) = u3(t):
EQ4    := diff(u3(t),t) = R*(u1(t)*u2(t)-u(t)*u3(t)):
EQNS_T := [ EQ||(1..4)]: <%>;
qvars := map([u,u1,u2,u3],(t));
cvars := [];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions( initial=[u=0,u1=0], final=[u=1,u1=0] );
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = 0
);
pars := [ 
  R0 = 1,
  R1 = 10000,
  R  = R0
];
GG := 1-zeta; #zeta^2*(3 - 2*zeta);
GUESS := [
  u  = GG,
  u1 = diff(GG,zeta),
  u2 = diff(GG,zeta,zeta),
  u3 = diff(GG,zeta,zeta,zeta)
];
CONT := [
  [ R = R0+s*(R1-R0) ]
];
#Describe(generateOCProblem);
project_dir  := "../generated_code";
project_name := "FlowInAchannel";
generateOCProblem(
  project_name,
  parameters   = pars,
  mesh         = [[length=1,n=100]],
  continuation = CONT,
  states_guess = GUESS
);
# if used in batch mode use the comment to quit;
