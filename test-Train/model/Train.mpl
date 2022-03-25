
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Train model with two controls
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# The optimal control problem has to move a train along a railways with slope using two bounded controls: one for acceleration and the second for traction.with fixed initial and final conditions.
# The problem make use of user defined code that is provided by the user with addUserFunction() command. 
restart:
with(XOptima):
# Dynamical System
# User defined functions
addUserFunction(acc(x,v)=h(x)-(alpha+beta*v+gm*v^2));#,["pippo",2,3]);
addUserFunction(h(x));
# Dynamical system
ODE1 := diff(x(t),t)=v(t);
ACC := acc(x(t),v(t)) ; # h(x(t))-(alpha+beta*v(t)+gm*v(t)^2);
ODE2 := diff(v(t),t)=ACC + ua(t) - ub(t);
ode := [ODE1,ODE2]: <%>;
# OCP (PINS generation)
# Load Dynamical system
uvars := [ua(t),ub(t)]:
xvars := [x(t), v(t)]:
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
# Define BC
addBoundaryConditions(initial=[x,v],final=[x,v]);
setStatusBoundaryConditions(initial=[x,v],final=[x,v]);
infoBoundaryConditions() ;
# Mapped functions
# Define target
setTarget( lagrange = ua(zeta)*v(zeta) );
# Define control bounds
addControlBound(
  ua,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = uaMax, 
  epsilon     = epsi_max,
  tolerance   = tol_max
);
addControlBound(
  ub,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = ubMax,
  epsilon     = epsi_max,
  tolerance   = tol_max
);
# States bounds
# Generate C++ Code
# Parameters
PARS := [
  x_i   = 0,
  x_f   = 6,
  v_i   = 0,
  v_f   = 0,
  alpha = 0.3,
  beta  = 0.14,
  gm    = 0.16,
  uaMax = 10,
  ubMax = 2,
  epsi_max = 0.01,
  epsi_min = 0.0001,
  tol_max  = 0.01,
  tol_min  = 0.001
];
# Post Processing
POST := [
  # non serve, default salva penalty controlli  #[uaControl(ua(zeta), 0, uaMax),"uaControl"],
  #[ubControl(ub(zeta),0, ubMax),"ubControl"],
  [h(x(zeta)),"Profile"]
];
# Continuation
CONTINUATION := [
  [
    [ua,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
    [ub,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
    [ua,"tolerance"] = tol_max*(1-s) + tol_min*s,
    [ub,"tolerance"] = tol_max*(1-s) + tol_min*s
  ]
];
# Guess
UGUESS := [
  ua = uaMax/2,
  ub = ubMax/2
];
GUESS := [
  x = x_i+(x_f-x_i)*zeta/4.8,
  v = 1
];
# Mesh
MESH_DEF := [
  [length=0.25, n=25],
  [length=0.75, n=3000],
  [length=3.8,  n=100]
];
project_dir  := "../generated_code";
project_name := "Train";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  controls_guess  = UGUESS, # uncomment to force iterative control computation
  states_guess    = GUESS,
  continuation    = CONTINUATION,
  mesh            = MESH_DEF,
  clean           = true
);
# Execute Code and Numerical Solution
# if used in batch mode use the comment to quit
# quit
# Compile and execute
#launchSolver(project_dir,project_name);
compileSolver(project_dir,project_name);
runSolver(project_dir);
# Solution analysis
with(plots):
XOptimaPlots:-loadSolution(project_dir,project_name); # # load solution
hhdrs := XOptimaPlots:-getHeaders(): nops(%);
XOptimaPlots:-plotSolution(
  zeta,[v],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Train"
);
XOptimaPlots:-plotSolution(
  zeta,[ua,ub],
  line_opts  = [[color="Blue",thickness=3],[color="Red",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Train"
);

NULL;
