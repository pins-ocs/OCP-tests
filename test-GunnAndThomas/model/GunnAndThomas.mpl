
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Gunn and Thomas
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# The problem was first posed by Gunn and Thomas (1965) and has been solved by Logsdon (1990), using orthogonal collocation on finite elements, and by Vas- siliadis (1993) using the control parameterization tech- nique.
# Gunn, D. J., & Thomas, W. J. (1965). Mass transport and chemical reaction in multifunctional catalyst systems. Chemical Engineering
# Science, 20, 89–100.
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamic system equations
EQ1    :=  diff(x1(t),t) = u(t)*(10*x2(t)-x1(t)) :
EQ2    :=  diff(x2(t),t) = u(t)*(x1(t)-10*x2(t))-(1-u(t))*x2(t) :
EQNS_T := [ EQ||(1..2) ] : <%>;
qvars := [x1(t),x2(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x1,x2]);
infoBoundaryConditions() ;
# Penalty
addControlBound(  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = 0.0001,
  tolerance   = 0.01);
setTarget( mayer = x1(zeta_f)+x2(zeta_f)-1 ) ;
generateOCProblem(  "GunnAndThomas",
  parameters   = [ x1_i = 1, x2_i=0 ],
  mesh         = [length=1, n=200],
  states_guess = [ x1 = x1_i ]);

