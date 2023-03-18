restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = u(t):
EQNS_T := [ EQ1]: <%>;
qvars := [x(t)];
cvars := [u(t)];
pars  := [];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [x = 0],
  final   = [x = kappa]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = (zeta^2-x(zeta)^3)^2*u(zeta)^14+epsilon*u(zeta)^2
);
pars := [
  kappa    = 0.99,
  epsilon  = max(0,(2*kappa/3)^12*(1-kappa^3)*(13*kappa^3-7))
];
GUESS  := [x=kappa*zeta];
PGUESS := [];
UGUESS := [ u = 0 ];
CONT := [
  [
  ]
];
POST := [
  [ kappa*zeta^(2/3), "exact" ],
  [ kappa,            "kappa" ]
];
Mesh := [ [length=0.1,n=100], [length=0.9,n=100] ];
#Describe(generateOCProblem);
project_dir  := "../generated_code";
project_name := "ROSS_Ball_Mizel";
generateOCProblem(
  project_name,
  parameters              = pars,
  mesh                    = Mesh,
  continuation            = CONT,
  states_guess            = GUESS,
  optimization_parameters = PGUESS,
  post_processing         = POST,
  controls_iterative      = true,
  controls_guess          = UGUESS
);
ocp := getOCProblem();
eval(ocp["FD"]);
eval(ocp["ode"]);
eval(ocp["controls"]["u"]);
# if used in batch mode use the comment to quit;
