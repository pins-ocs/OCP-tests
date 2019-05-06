
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Economic Growth Model 2
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamical system equations
TT := T(zeta) ;
EQ1 := diff(x1(zeta),zeta) = y1(zeta)*TT :
EQ2 := diff(y1(zeta),zeta) = u(zeta)*Q(x1(zeta),x2(zeta))*TT:
EQ3 := diff(x2(zeta),zeta) = y2(zeta)*TT :
EQ4 := diff(y2(zeta),zeta) = (1-u(zeta))*Q(x1(zeta),x2(zeta))*TT:
EQ5 := diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ||(1..5) ] : <%> ;
# Variabili del problema e controlli
qvars := [x1(zeta),x2(zeta),y1(zeta),y2(zeta),T(zeta)] ;
cvars := [u(zeta)] ;
# Optimal Contol Problem
#infoRegisteredObjects();
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addUserFunction( Q(x,y)=x*y ) ;
addBoundaryConditions(
            [y1(zeta_f)=Yc,"FinalY1"],
            [y2(zeta_f)=Yc,"FinalY2"] ]
setStatusBoundaryConditions(
infoBoundaryConditions() ;
# Penalty
addControlBound(
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  epsilon     = 1e-2,
  tolerance   = 0.01,
  scale       = T(zeta)
addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T(zeta_f) ) ;
POST := [
PARS := [
CONT := [
addUserFunction( explog(a,b,s)=exp(log(a)*(1-s)+log(b)*s) );
generateOCProblem(
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = [length=1, n=5000],
  states_guess    = [ T=T_guess, x1=x1_i, x2=x2_i, y1=y1_i, y2=y2_i ]
