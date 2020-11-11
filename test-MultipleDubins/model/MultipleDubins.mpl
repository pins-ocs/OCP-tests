
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Multiple Dubins
# Authors: E. Bertolazzi, P.Bevilacqua, M.Frego
# Date:
# 
restart:
with(XOptima):
# Model Equations
EQ1  := diff(x1(zeta),zeta)     = L1*cos(theta1(zeta)):
EQ2  := diff(y1(zeta),zeta)     = L1*sin(theta1(zeta)):
EQ3  := diff(theta1(zeta),zeta) = L1*kappa1:

EQ4  := diff(x2(zeta),zeta)     = L2*cos(theta2(zeta)):
EQ5  := diff(y2(zeta),zeta)     = L2*sin(theta2(zeta)):
EQ6  := diff(theta2(zeta),zeta) = L2*kappa2:

EQ7  := diff(x3(zeta),zeta)     = L3*cos(theta3(zeta)):
EQ8  := diff(y3(zeta),zeta)     = L3*sin(theta3(zeta)):
EQ9  := diff(theta3(zeta),zeta) = L3*kappa3:
EQNS := convert([EQ||(1..9)],Vector);
# Variabili del problema
# Variabili
xvars := map([
  x1,y1,theta1,
  x2,y2,theta2,
  x3,y3,theta3
],(zeta));
# Controlli
uvars := [];
# Parametri di ottimizzazione
pvars := [
  L1,kappa1,
  L2,kappa2,
  L3,kappa3
];
# BVP
loadDynamicSystem(
  equations = EQNS,
  controls  = uvars,
  states    = xvars
);
mapUserFunctionToRegularized(
  diff2pi, "DiffModuleN", ["N" = 2*Pi]
);
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithErf", ["h" = 0.001, "delta"= 0]
);
addBoundaryConditions(
  initial = [x1=x_i,y1=y_i,theta1=theta_i],
  final   = [x3=x_f,y3=y_f],
  generic = [
    [diff2pi(theta3(zeta_f)-theta_f)=0,"final_theta"],
    [x1(zeta_f)=x2(zeta_i),"internal_x1"],
    [y1(zeta_f)=y2(zeta_i),"internal_y1"],
    [theta1(zeta_f)=theta2(zeta_i),"internal_theta1"],
    [x2(zeta_f)=x3(zeta_i),"internal_x2"],
    [y2(zeta_f)=y3(zeta_i),"internal_y2"],
    [theta2(zeta_f)=theta3(zeta_i),"internal_theta2"]
  ]
);
infoBoundaryConditions() ;
setTarget(
  lagrange = L1+L2+L3
           +epsilon_L*( L1^2+L2^2+L3^2 )
           +epsilon_K*( kappa1^2+kappa2^2+kappa3^2 )
);
#addBilateralConstraint(
#  kappa1,
#  "k1_limit",
#  epsilon   = kappa_epsi,
#  tolerance = kappa_tol,
#  min       = -kappa_max,
#  max       =  kappa_max,
#  barrier   = true
#);
#addBilateralConstraint(
#  kappa2,
#  "k2_limit",
#  epsilon   = kappa_epsi,
#  tolerance = kappa_tol,
#  min       = -kappa_max,
#  max       =  kappa_max,
#  barrier   = true
#);
#addBilateralConstraint(
#  kappa3,
#  "k3_limit",
#  epsilon   = kappa_epsi,
#  tolerance = kappa_tol,
#  min       = -kappa_max,
#  max       =  kappa_max,
#  barrier   = true
#);
#addUnilateralConstraint(
#  L1>=0, "L1_limit",
#  epsilon   = L_epsi,
#  tolerance = L_tol,
#  barrier   = false
#);
#addUnilateralConstraint(
#  L2>=0, "L2_limit",
#  epsilon   = L_epsi,
#  tolerance = L_tol,
#  barrier   = false
#);
#addUnilateralConstraint(
#  L3>=0, "L3_limit",
#  epsilon   = L_epsi,
#  tolerance = L_tol,
#  barrier   = false
#);
# Control deduced minimizing Hamiltonian
GUESS := [
  x1     = x_i+(zeta/3)*(x_f-x_i),
  y1     = y_i+(zeta/3)*(y_f-y_i),
  x2     = x_i+((1+zeta)/3)*(x_f-x_i),
  y2     = y_i+((1+zeta)/3)*(y_f-y_i),
  x3     = x_i+((2+zeta)/3)*(x_f-x_i),
  y3     = y_i+((2+zeta)/3)*(y_f-y_i),
  theta1 = arctan(y_f-y_i,x_f-x_i),
  theta2 = arctan(y_f-y_i,x_f-x_i),
  theta3 = arctan(y_f-y_i,x_f-x_i)
];
PGUESS := [
  L1     = sqrt((x_f-x_i)^2+(y_f-y_i)^2)/3,
  L2     = sqrt((x_f-x_i)^2+(y_f-y_i)^2)/3,
  L3     = sqrt((x_f-x_i)^2+(y_f-y_i)^2)/3,
  kappa1 = 0,
  kappa2 = 0,
  kappa3 = 0
];
# parameters
PARAMETERS := [
  x_i         = 0,
  y_i         = 0,
  theta_i     = -Pi/3,
  x_f         = 0.4,
  y_f         = 0.4,
  theta_f     = -Pi/6,
  kappa_max   = 3,
  kappa_epsi  = 0.01,
  kappa_tol   = 0.01,
  L_epsi      = 0.01,
  L_tol       = 0.01,
  #epsi_min   = 1e-20,
  #tol_min    = 1e-20,
  epsilon_L   = 0.001,
  epsilon_K   = 0.001,
  wkappa      = 0
];
CONT := [
  [ wkappa = s ]
  #[ wp  = s ],
  #[ epsilon = (1-s)*0.1+s*espilon_min]
  #[ [u1,"epsilon"]   = epsi_max*(1-s) + epsi_min*s],
  #  [u1,"tolerance"] = tol_max*(1-s) + tol_min*s ]
];
#Describe(generateOCProblem) ;
generateOCProblem(
  "MultipleDubins",
  parameters              = PARAMETERS,
  mesh                    = [ [length=1, n=40] ],
  states_guess            = GUESS,
  optimization_parameters = PGUESS,
  #continuation           = CONT
  #controls_guess         = [u1 = 0],
  #controls_iterative     = true,
  admissible_region  = [
    [L1>0,"pars"],
    [L2>0,"pars"],
    [L3>0,"pars"]
  ]
);
0.959433382891686781+
0.385803211640063759+
0.785233630246244263;

