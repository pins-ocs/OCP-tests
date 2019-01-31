
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: orbit transfer
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Load library
# Load XOptima(c)  library and others
restart:
with(plots):
# Load optimal control library
with(XOptima):
interface(rtablesize=20):

# Problem description
# Given a rocket engine with given thrust T, operating for a given length of time tf, we wish to find the thrust direction hisotory theta(t) to transfer a SpaceCraft from a given initial circular orbit to to the largest possible circular orbit.
# r = radial distance from attarcting center
# v = tangential component of velocity
# u = radial component of velocity
# m = mass of spacecraft
# -m' = mass onsumption rate (constant)
# theta = thrust direction angle 
# mu = gravitational constant of attracting center
# 
# time is in unito of sqrt(r0^2/mu)/
# r in unit of r0, 
# u, v in unit of sqrt(mu/r0)
# m in unit of m0
# T in unit of mu m0/r0^2
# 
# Find theta(t) to maximise r(tf)
# 
# Bryson Ho, 1975, pag. 66
# 
# 
# Model
# System of equations:
eq1    := diff(r(t),t)     = tf*u(t) :
eq2    := diff(u(t),t)     = tf*(v(t)^2/r(t)-mu/r(t)^2+T*sin(theta(t))/m(zeta)):
eq3    := diff(v(t),t)     = tf*(-v(t)*u(t)/r(t) + T*cos(theta(t))/m(zeta)):
eq4    := diff(m(t),t)     = -tf*mdot : # mass consumption
eq5    := diff(alpha(t),t) = tf*(v(t)/r(t)): # angle recostruction
eqns_t := [eq||(1..5)]: <%>;
# List of variables
xvars_t := [m(t),alpha(t),r(t),u(t),v(t)] ;
# List of controls
uvars_t := [theta(t)];
# Data set:
data := [ mu   = 1,
          r0   = 1,
          m0   = 1,
          T    = 0.1 * m0*mu/r0^2*0.1405,
          mdot = 0.533*T*sqrt(mu/r0),
          v0   = sqrt(mu/r0),
          tf   = 5 * 3.32*sqrt(r0^3/mu)];
# Optimal control
# Optimal control problem definition
# Load dynamic system
# Load the ODE dynamic system: list of controls, state variables and differential equations.
# By defulat the command set the indepenedent variable equal to "zeta".
loadDynamicSystem(controls=uvars_t,states=xvars_t,equations=eqns_t);
# Boundary conditions and jump conditions
# Specify the standard boundary conditions and the additional boundary conditions if needed.
# Here it is possible to activate some boundary conditions for automatic generation of file data.
# It is still possible to change the baoundary conditions activation in the data file.
addBoundaryConditions(initial = [m=m0,alpha=0,r=r0,u=0,v=v0],
                      final   = [u=0],
                      generic = [[v(zeta_f)=sqrt(mu/r(zeta_f)),"v_final"]]);

# Dispaly the bounddary condition activation status:
infoBoundaryConditions();
# Target: performance criterion
# Specify the target function. There are three possible for to specify the target.
# Namely: 
# targetBolza(), targetLagrange(), targetMayer();
# Note that:
#  - the target must be specified as a function of the independent variable defined with loadDynamicSystem() command 
#  - the Mayer term must be specified as a function of the initial and/or finale value of the independent variable.
setTarget(lagrange=-0*tf*u(zeta),mayer=-r(zeta_f));
# Generation of optimal control equations and C++ code
# Generate Optimal Control Equations
# The command genereates the equations of the necessary optimality conditions approximating Pontriagyn Principle with the penalty functions.
# The jacobians of the optimality equations are also derived for numerical solution with Newton Solver.
#pars := [op(data), tf0=tf] ;
# Set the right guess for minimum!
USER_GUESS := [theta=arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))];
STATES_GUESS := [ m=m0, alpha=tf*v0/r0*zeta, r=r0, v=v0, u=0, lambda3__xo=1e-8];
POST := [ [r(zeta)*cos(alpha(zeta)), "X-pos"],
          [r(zeta)*sin(alpha(zeta)), "Y-pos"],
          [r0*cos(alpha(zeta)),      "X-pos0"],
          [r0*sin(alpha(zeta)),      "Y-pos0"] ] ;
          
addCheck( [m(zeta)>0,r(zeta)>0], "node" ) ;
generateOCProblem( "OrbitTransfer",
                   parameters      = data,
                   post_processing = POST,
                   mesh            = [ [length=1, n=1000]],
                   controls_guess  = USER_GUESS,
                   states_guess    = STATES_GUESS ) ;
OCP := getOCProblem() ;
OCP["hamiltonian"] ;

