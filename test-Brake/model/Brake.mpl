
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Maximum Brake problem
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Load library
restart:
# Load optimal control library
with(plots):
with(XOptima):
interface(rtablesize=40):
# Equations of Dynamics
EQ1 := diff(x(t),t) = T*v(t):
EQ2 := diff(v(t),t) = T*a(t):
eqns_t := [EQ||(1..2)]:<%> ;
xvars_t := [x(t),v(t)];
uvars_t := [a(t)];
pars := [T]; # optimization parameters
;
# Problem description
# It is a simple CN milling machine with two axes, X-Y
# kappa = curvature
# s          = curvilinear abscissa
# Fx, Fy = Forces along pysical axes
# Fu       = Force along tangential direction (u)
# Fv       = Force along lateral direction (v)
# theta  = angle of (u,v) in (X,Y) frame
# r         = orthogonal distance from the nominal path
# emx   = effective mass along x axes
# emy   = effective mass along y axes
# 
# Note that the toolpath is made of straight segments and circular arcs, so kappa is a piecewise function.

# Optimal control
# Optimal control problem definition
# Load dynamic system
# Load the ODE dynamic system: list of controls, state variables and differential equations.
# By default the command sets the independent variable to "zeta".
#Describe(loadDynamicSystem);
loadDynamicSystem(
  controls   = uvars_t,
  states     = xvars_t,
  equations  = eqns_t
);
addBoundaryConditions(  initial = [x,v],
  final   = [v]);
infoBoundaryConditions();
setTarget(  lagrange = 0,  mayer    = x(zeta_f));
# Constraints on Controls
# The following command sets the limits to the controls. If the control variable does not appear in the taget function nor in the other constraints, it is very likely that an explicit solution of the controls can be obtained from the hamiltonian with respect to the controls.
# Otherwise, a numerical solution is mandatory to solve the controls.
addControlBound(
  a,
  scale       = 1,
  max         = 1,
  min         = -1,
  epsilon     = 0.01,
  tolerance   = 0.01,
  controlType = "U_LOGARITHMIC"
):
addUnilateralConstraint(
  T>0, Tpositive,
  #barrier   = true,
  scale     = 1,
  epsilon   = 0.01,
  tolerance = 0.01
):
# Optimal Contol Problem
# Set guess solution (optional)
# A guess solution can be specified for some or all state variables. The guess solution can be a function of the independent variable "zeta". Piecewise solution are not allowed.
# Note that the lambda3 multiplier cannot vanish, otherwise the corresponding control goes to infinity.
PARS := [ x_i = 0, v_i = 1, v_f = 0];
GUESS := [ x = 0, v = 1];
generateOCProblem(  "Brake",
  parameters              = PARS,
  states_guess            = GUESS,
  optimization_parameters = [ T = 1 ],  mesh                    = [[length = 1, n = 400]],
  clean                   = false); 

