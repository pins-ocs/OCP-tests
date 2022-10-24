restart:;
with(XOptima):;
EQ1    :=  diff(x1(t),t) = T*(-x2(t)):
EQ2    :=  diff(x2(t),t) = T*(x3(t)+WU2*u2(t)):
EQ3    :=  diff(x3(t),t) = T*(u(t)-kappa*x2(t)^5):
EQNS_T := [ EQ||(1..3) ]: <%>;
qvars := map([x1,x2,x3],(t));
cvars := [u(t),u2(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[x1,x2,x3],
  final=[x1,x2,x3]
);
infoBoundaryConditions();
setTarget(
  mayer    = T,
  lagrange = 0*(1-kappa)*T*u(zeta)^2+WC*T*(u2(zeta)^2) #
);
addControlBound( 
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  scale       = T,
  epsilon     = u_epsi,
  tolerance   = u_tol
);
addUnilateralConstraint( 
  T>=0, Tbarrier,
  subtype     = "BARRIER_LOG0",
  epsilon     = 0,
  tolerance   = 0.01,
  barrier     = true
);
PARS := [

  x1_i   = 0,
  x2_i   = -1.3,
  x3_i   = -1.3,

  x1_f   = 0,
  x2_f   = 0,
  x3_f   = 0,

  T_guess = 10,

  kappa   = 0,
  u_epsi0 = 0.1, u_epsi1 = 1e-5,  u_epsi = u_epsi0,
  u_tol0  = 0.1, u_tol1  = 1e-5,  u_tol  = u_tol0,

  WU2     = 1,

  WC0    = 1,
  WC1    = 100000,
  WC     = WC0

];
POST := [
  [ zeta*T, "Time" ]
];
CONT := [
  [ WC = WC0*(1-s)+WC1*s ],
  [ WU2 = 0,
    ["u","epsilon"] = (1-s)*u_epsi0 + s * u_epsi1,
    ["u","tolerance"] = (1-s)*u_tol0 + s * u_tol1
  ],
  [ kappa = s ]
];
GUESS := [
  x1 = (1-zeta)*x1_i+zeta*x1_f, 
  x2 = (1-zeta)*x2_i+zeta*x2_f,
  x3 = (1-zeta)*x3_i+zeta*x3_f
];
MESH_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "BangBangFork";
#Describe(generateOCProblem);
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  continuation            = CONT,
  mesh                    = MESH_DEF,
  states_guess            = GUESS,
  optimization_parameters = [ T = T_guess ]
);
# if used in batch mode use the comment to quit;
