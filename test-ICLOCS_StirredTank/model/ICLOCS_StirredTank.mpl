
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Continuously-stirred tank reactor (ICLOCS example 8)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
REACT := k*x1(t)*exp(-En/x2(t));
EQ1 := diff(x1(t),t) = T*((1-x1(t))/theta - REACT):
EQ2 := diff(x2(t),t) = T*((Tf-x2(t))/theta + REACT-a*u(t)*(x2(t)-Tc)):
EQNS_T := [ EQ||(1..2)]: <%> ;
# State variables and controls
qvars := [x1(t),x2(t)];
cvars := [u(t)];
optimization_pars := [T];
# Optimal Control: problem definition
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
#addBoundaryConditions(
  #initial = [x1,x2],
  #final   = [x1,x2]
#);
infoBoundaryConditions();
addControlBound(
  u,
  controlType = "U_LOGARITHMIC",
  min         = 0,
  max         = 2,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
addBilateralConstraint(
  T,
  tfbound,
  min       = 10,
  max       = 200,
  epsilon   = epsi_T,
  tolerance = tol_T,
  barrier   = true
);
addBilateralConstraint(
  x1(zeta),
  x1bound,
  min       = 0,
  max       = 1,
  epsilon   = x_epsi,
  tolerance = x_tol,
  barrier   = true
);
addBilateralConstraint(
  x2(zeta),
  x2bound,
  min       = 0,
  max       = 1,
  epsilon   = x_epsi,
  tolerance = x_tol,
  barrier   = true
);
setTarget(
  mayer    = w*(x1(zeta_i)-x1_i)^2+w*(x2(zeta_i)-x2_i)^2+
             w*(x1(zeta_f)-x1_f)^2+w*(x2(zeta_f)-x2_f)^2,
  lagrange = wT*T
);
PARS := [
  x_epsi    = 0.1,
  x_tol     = 0.01,
  epsi_ctrl = 0.001,
  tol_ctrl  = 0.001,
  epsi_T    = 0.001,
  tol_T     = 1,

  a         = 0.000195*600,
  theta     = 20,
  k         = 300,
  En        = 5,
  Tc        = 0.38158,
  Tf        = 0.3947,

  x1_i      = 0.98,
  x2_i      = 0.39,
  x1_f      = 0.26,
  x2_f      = 0.65,
  u_f       = 0.76,


  T_guess   = 90,
  w_exp_min = 0,
  w_exp_max = 15,
  w         = exp(w_exp_min),
  wT        = 0.001
];

GUESS := [
  x1 = x1_f,
  x2 = x2_f
];
PGUESS := [ T = T_guess ];
CONT := [
  [ w = exp(w_exp_max*s+w_exp_min*(1-s)) ]
]
;
#Describe(generateOCProblem);
generateOCProblem(
  "ICLOCS_StirredTank",
  parameters              = PARS,
  mesh                    = [length=1,n=100],
  controls_iterative      = true,
  controls_guess          = [u=u_f],
  states_guess            = GUESS,
  optimization_parameters = PGUESS,
  continuation            = CONT
);

