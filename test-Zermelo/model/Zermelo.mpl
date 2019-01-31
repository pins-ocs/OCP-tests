
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Particle Steering (test 9 di COPS)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamic system equations
EQ1  := diff(x(zeta),zeta)  = T(zeta)*(vx(zeta) + velX(x(zeta),y(zeta))) :
EQ2  := diff(y(zeta),zeta)  = T(zeta)*(vy(zeta) + velY(x(zeta),y(zeta))) :
EQ3  := diff(vx(zeta),zeta) = T(zeta)*(S*cos(u(zeta))) :
EQ4  := diff(vy(zeta),zeta) = T(zeta)*(S*sin(u(zeta))) :
EQ5  := diff(T(zeta),zeta)  = 0:
EQNS := convert([EQ||(1..5)],Vector) ;
# Satates and Controls
xvars := [x(zeta),y(zeta),vx(zeta),vy(zeta),T(zeta)] ;
uvars := [u(zeta)] ;
# Optimal Contol Problem
addUserFunction(velX(x,y)=-y);
addUserFunction(velY(x,y)=x);
addUserFunction(arctan2(y,x),derivatives=0) ; # definita un codice utente
;
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x=0,y=0,vx=0,vy=0],final=[y=5,vx=45,vy=0]);
infoBoundaryConditions() ;
setTarget( mayer = T(zeta_f), lagrange = 0 ) ;
addUnilateralConstraint( T(zeta)>=0, Tpositive, barrier=true ) ;
CONTROL_GUESS := [ u = arctan2(-lambda4__xo(zeta), -lambda3__xo(zeta)) ]; 
GUESS := [ x=5*zeta, y=45*zeta, lambda3__xo=1, T=1];
generateOCProblem(  "Zermelo",
  integral_post_processing = [[zeta*T(zeta),"Time"]],
  parameters     = [ S=50 ],
  #continuation   = [[epsi_u=1-s]],
  mesh           = [ length=1, n=1000 ],
  controls_guess = CONTROL_GUESS,
  states_guess   = GUESS);

