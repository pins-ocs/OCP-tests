
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Robot Arm (COPS example 8)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Rein Luus. Iterative Dynamic Programming. Chapman & Hall/CRC Monographs and Surveys in Pure and Applied Mathematics, 2000.
restart:
with(XOptima):
#XOptimaInfo() ;
# Equations of motion
addUserFunction(I_phi(rho)=((L-rho)^3+rho^3)/3);addUserFunction(I_theta(rho,phi)=I_phi(rho)*sin(phi)^2);
EQ1 := L*diff(rho1(t),t)                        = T*u_rho(t):
EQ2 := I_theta(rho(t),phi(t))*diff(theta1(t),t) = T*u_theta(t):
EQ3 := I_phi(rho(t))*diff(phi1(t),t)            = T*u_phi(t):
EQ4 := diff(rho(t),t)                           = T*rho1(t):
EQ5 := diff(theta(t),t)                         = T*theta1(t):
EQ6 := diff(phi(t),t)                           = T*phi1(t):
EQNS_T := [ EQ||(1..6)]: <%>;
# State variables and controls
qvars := [rho(t),theta(t),phi(t),rho1(t),theta1(t),phi1(t)];
cvars := [u_rho(t),u_theta(t),u_phi(t)];
pars := [T];
# Optimal Control: problem definition
loadDynamicSystem(
  equations  = EQNS_T,
  controls   = cvars,
  states     = qvars,
  parameters = pars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial = [    rho    = 4.5,    theta  = 0,    phi    = Pi/4,    rho1   = 0,
    theta1 = 0,
    phi1   = 0
  ],
  final = [
    rho    = 4.5,
    theta  = 2*Pi/3,
    phi    = Pi/4,
    rho1   = 0,
    theta1 = 0,
    phi1   = 0
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = W*T+(1-W)*T^2,
  lagrange = 0
);
addControlBound(
  u_rho,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = T
);addControlBound(
  u_theta,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = T
);addControlBound(
  u_phi,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = T
);
pars := [
  L            = 5,  u_epsilon0   = 0.01,
  u_tolerance0 = 0.01,
  u_epsilon1   = 0.00001,
  u_tolerance1 = 0.00001,
  u_epsilon    = u_epsilon0,
  u_tolerance  = u_tolerance0,
  Tguess       = 1,
  W            = 0];
GUESS := [
  rho   = 4.5,
  theta = zeta*2*Pi/3,
  phi   = Pi/4];
PGUESS := [
  T = Tguess
];
CONT := [
  [
    W = s,    ["u_rho","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u_rho","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s,
    ["u_theta","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u_theta","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s,
    ["u_phi","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u_phi","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s
  ]
];
#Describe(generateOCProblem);
generateOCProblem(
  "RobotArm",
  parameters       = pars,
  mesh             = [[length=1,n=400]],
  continuation     = CONT,
  states_guess     = GUESS,
  parameters_guess = PGUESS
);
#ocp := getOCProblem();
#eval(ocp);

