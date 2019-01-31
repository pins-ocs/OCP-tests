
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Economic Growth Model
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamic system equations
EQ1 := diff(x1(zeta),zeta) = u(zeta)*Q(x1(zeta),x2(zeta))*T(zeta):
EQ2 := diff(x2(zeta),zeta) = (1-u(zeta))*Q(x1(zeta),x2(zeta))*T(zeta):
EQ3 := diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ||(1..3) ] : <%> ;
# States and Controls
qvars := [x1(zeta),x2(zeta),T(zeta)] ;
cvars := [u(zeta)] ;
# Optimal Contol Problem
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addUserFunction( Q(x,y)=x*y ) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x1,x2],generic=[[Q(x1(zeta_f),x2(zeta_f))=Qc,"final"]]);
setStatusBoundaryConditions(generic=["final"]);
infoBoundaryConditions() ;
# Penalty
addControlBound(  u, 
  controlType="U_COS_LOGARITHMIC",
  min=0, max=1,
  epsilon=1e-6,  tolerance=1e-2,  scale=T(zeta));
addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T(zeta_f) ) ;
#setFDorder([x],"forward") ;
generateOCProblem(  "EconomicGrowthModel",
  post_processing = [[lambda1__xo(zeta)-lambda2__xo(zeta),"switching"]],
  parameters      = [x1_i = 1, x2_i=2, Qc=10],
  mesh            = [length=1, n=1000],
  states_guess    = [ T=1, x1=x1_i, x2=x2_i ]);

