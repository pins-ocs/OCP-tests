
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Dido problem
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Description
# 
# Load Packages

# Load maple packages
restart: with(plots):
with(XOptima):
with(plots):
# Dynamic system equations
ODE1 := diff(x(t),t)=cos(theta(t));
ODE2 := diff(y(t),t)=sin(theta(t));
# List of states and controls
uvars := [theta(zeta)] ;
xvars := [x(zeta),y(zeta)] ;
ode   := subs(t=zeta,Vector([ODE1,ODE2]));
# Optimal Contol Problem
#Describe(loadDynamicSystem) ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x=0,y=0],final=[y=0]);
setStatusBoundaryConditions(initial=[x,y],final=[y]);
infoBoundaryConditions() ;
# penalty che dipendono dagli ingressi
setTarget( lagrange = -y(zeta)*cos(theta(zeta)) ) ;
POST := [];
PARS := [];
UGUESS := [ theta = 0 ];
GUESS := [ x = zeta,y=1];
generateOCProblem(
  "Dido",
   post_processing = POST,
   parameters      = PARS,
   controls_guess  = UGUESS, # uncomment to force iterative control computation
   states_guess    = GUESS,
   mesh = [ [length=10, n=100]],
   clean=true
);
#Describe(generateOCProblem);

