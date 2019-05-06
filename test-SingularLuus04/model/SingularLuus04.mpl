
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Controllo Singolare LuusExample 4
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamical system equations
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = z(t) :
EQ3    :=  diff(z(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2, EQ3 ] : <%> ;
# States and controls
qvars := [x(t),y(t),z(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x,y,z]);
infoBoundaryConditions() ;
# Penalty
addControlBound(
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsi,
  tolerance   = u_tol,
  scale       =(x(zeta)^2+epsilon_X)
setTarget( lagrange = x(zeta)^2 ) ;

PARS := [
CONT := [
generateOCProblem(
  integral_post_processing = [[x(zeta)^2,"intTarget"]],
  parameters   = PARS,
  continuation = CONT,
  mesh         = [ length=Tf, n=2000 ],
  states_guess = [ x=x_i, y=y_i, z=z_i ]
