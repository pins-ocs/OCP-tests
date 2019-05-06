
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Singular control
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Calogero appunti pag. 188
# Inizializzazione
restart:
with(XOptima);
#XOptimaInfo() ;
# Dynamic system equations
EQ1 := diff(x(t),t) = u(t) ;
EQNS_T := [ EQ1 ] : <%> ;
# States and controls
qvars := [ x(t) ] ;
cvars := [ u(t) ] ;
# Optimal Contol Problem
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x],final=[x]);
infoBoundaryConditions() ;
# Penalty
addControlBound(
  controlType ="U_QUADRATIC",#"U_COS_LOGARITHMIC",
  min         = 0,
  max         = 2,
  epsilon     = 0.01,
  tolerance   = 0.01
addModelExtraParameters([epsi_max,tol_max,epsi_min,tol_min]) ;
addUnilateralConstraint(
  uMaxBound,
  epsilon   = epsi_max,
  tolerance = tol_max
setTarget( lagrange = u(zeta)*(zeta-4) ) ;

#setFDorder([2],"backward"):
#setFDorderCoEquation([u],"forward");
#Describe(generateOCProblem) ;
PARS := [
  epsi_max = 0.01,
  tol_max  = 0.01,
CONT := [
    [uMaxBound,"tolerance"] = tol_max*(1-s)+s*tol_min ]
U_GUESS := [ u = min(1.9,max(0.1,(x(zeta)+1-zeta)/2)+1) ];
Describe(generateOCProblem):
generateOCProblem(
  integral_post_processing = [ [u(zeta)*(zeta-4), "int_target"] ],
  post_processing          = [ [x(zeta)+1-zeta, "ineq_arg"] ],
  mesh                     = [ length=3, n=600 ],
  parameters               = PARS,
  continuation             = CONT,
  controls_iterative       = true,
  states_guess             = [ x = zeta]
