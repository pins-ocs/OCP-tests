
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# A worst case scenario
# Authors: E. Bertolazzi
# Date:
# 
# Universität der Bundeswehr München Fakultät für Luft­ und Raumfahrttechnik Institut für Mathematik und Rechneranwendung
# Nonsmooth Newton Methods and Convergence of Discretized Optimal Control Problems subject to DAEs
# Dipl.­Technomath. Martin Kunkel
# 4.4.3 A worst case scenario 
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamical system equations
EQ1    :=  diff(x(t),t) = (1-2*t)*u(t):
EQNS_T := [ EQ1 ] : <%> ;
# States and controls
qvars := [x(t)];
cvars := [u(t)];
# Optimal Contol Problem
loadDynamicSystem(  equations = EQNS_T,  controls  = cvars,  states    = qvars);
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x]);
infoBoundaryConditions() ;
# Penalty
addControlBound(  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = 0.0001,
  tolerance   = 0.0001,
  scale       = 1);
setTarget( mayer = x(zeta_f) ) ;

#Describe(generateOCProblem) ;
generateOCProblem(
  "WorstCaseScenario",
  parameters   = [ x_i = 0 ],
  mesh         = [ length=1, n=400 ],
  states_guess = [ x=x_i ]
);

