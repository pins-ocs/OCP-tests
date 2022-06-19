restart:
with(plots):;
with(XOptima):;
U := B*u(zeta);
EQ1    := diff(x1(zeta),zeta) = Tf*x2(zeta):
EQ2    := diff(x2(zeta),zeta) = Tf*(U-kappa*x2(zeta)^2-g):
EQ3    := diff(x3(zeta),zeta) = Tf*U:
EQNS_T := [ EQ||(1..3) ]: <%>;
qvars := map([x1,x2,x3],(zeta));
cvars := [u(zeta)];
#infoRegisteredObjects();
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions( initial = [x1=0,x2=0,x3=0], final = [x3] );
infoBoundaryConditions();
addControlBound(
  u,
  scale       = Tf,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = u_epsi,
  tolerance   = u_tolerance
);
setTarget( mayer = -x1(zeta_f) + W*(Tf-Tf_guess)^2, lagrange = 0 );
PARS := [
  x3_f = b,
  g    = 9.81,

  tol0  = 0.01,
  tol1  = 1e-6,
  epsi0 = 0.01,
  epsi1 = 1e-6,

  u_tolerance = tol0,
  u_epsi      = epsi0,

  B     = 4*g,
  kappa = 0.002,
  b     = 350,

  Tf_guess = 20,
  W0       = 1,
  W1       = 0,
  W        = W0

];
GUESS := [
  x1 = zeta*Tf_guess,
  x2 = 0,
  x3 = zeta*Tf_guess
];
UGUESS := [
  u = B/2
];
CONT :=[
  [
    W = W0*(1-s)+W1*s
  ],
  [
    ["u","epsilon"]   = pow_average__xo(s,epsi0,epsi1),
    ["u","tolerance"] = pow_average__xo(s,tol0,tol1)
  ]
];
POST := [
  [ zeta*Tf, "time" ],
  [ lambda2__xo(zeta)+lambda3__xo(zeta), "L2+L3" ]
];
project_dir  := "../generated_code";
project_name := "SoundingRocket";
generateOCProblem(
  project_name,
  admissible_region       = [Tf>0],
  post_processing         = POST,
  parameters              = PARS,
  mesh                    = [length=1,n=100],
  optimization_parameters = [Tf=Tf_guess],
  continuation            = CONT,
  states_guess            = GUESS,
  controls_guess          = UGUESS
  #admissible_region       = [[sz(zeta)>0,"node"]]
);
# if used in batch mode use the comment to quit;
