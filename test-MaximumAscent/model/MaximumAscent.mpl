
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Maximum Ascent Problem
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Model Equations
# mdot > 0!
TF   := tf(days);
TBAR := Tbar(TF) ;
ETA  := eta(TF) ;
k := TBAR/(m0-zeta*mdot*TF);
EQ1 := diff(r(zeta),zeta)     = ETA*u(zeta):
EQ2 := diff(u(zeta),zeta)     = ETA*((v(zeta)^2)/r(zeta)-(1/r(zeta)^2)) + k*sin(alpha(zeta)):
EQ3 := diff(v(zeta),zeta)     = -(ETA*u(zeta)*v(zeta)/r(zeta)) + k*cos(alpha(zeta)):
EQ4 := diff(theta(zeta),zeta) = ETA*(v(zeta)/r(zeta)) :
EQNS := convert([EQ||(1..4)],Vector) ;
#simplify(EQ6*lambda_u(zeta)+EQ7*lambda_v(zeta),size);
# Variabili del problema
# Variabili
xvars := [r(zeta),u(zeta),v(zeta),theta(zeta)] ;
# Controlli
uvars := [alpha(zeta)] ;
# BVP
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars,parameters=[]) ;
# Initial conditions
# Launch from zero altitude with zero initial velocity
# All Boundary Conditions are non-dimensional
addFunction(arctan2(y,x),2) ;
addUserFunction(eta(tf)=v0*tf/r0) ;
addUserFunction(Tbar(tf)=T*tf/v0) ;
addUserFunction(tf(days)=days*24*3600);

#Describe(addBoundaryConditions) ;
addBoundaryConditions(initial=[r=r0_bar,u=u0_bar,v=v0_bar,theta=theta0],
                      final=[u=uf_bar],
                      generic=[[v(zeta_f)*sqrt(r(zeta_f))-1,"final_velocity"]]);
infoBoundaryConditions() ;
setTarget( mayer = -r(zeta_f), lagrange = 0) ;
# Control deduced minimizing Hamiltonian
CONTROL := [alpha = arctan2(-lambda2__xo(zeta),-lambda3__xo(zeta))] ;
GUESS := [ r=r0_bar, u=u0_bar, v=v0_bar, theta=theta0, lambda2__xo = -1 ] ;
# parameters
model_params := [ T       = 0.68,
                  m0      = 5000,
                  g0      = 9.80665,
                  Isp     = 1500,
                  r0      = 6678.14e3,
                  mu      = 398600.4418e9,
                  u0      = 0,
                  v0      = sqrt(mu/r0),
                  days    = 1,
                  days0   = 1,
                  days1   = 30,
                  tf      = days*24*3600,
                  mdot    = T/(g0*Isp),
                  r_earth = 6378.14e3 ] ;
bc_params := [ uf_bar = 0, r0_bar = r0/r0, u0_bar = u0/v0, v0_bar = v0/v0, theta0 = 0] ;
PARAMETERS := [op(model_params), op(bc_params)] ;
POST := [ [sqrt(lambda2__xo(zeta)^2+lambda3__xo(zeta)^2),"sqrtl12"],
          [r(zeta)*r0, "R"],
          [u(zeta)*v0, "U"],
          [v(zeta)*v0, "V"]] ;
#Describe(generateOCProblem) ;
generateOCProblem(  "MaximumAscent",
  parameters      = PARAMETERS,
  post_processing = POST,
  continuation    = [[days=(1-s)*days0+s*days1]],
  mesh            = [ [length=1, n=1000*days1] ],
  controls_user_defined = CONTROL,
  #controls_guess = [ theta = arctan2(-lambda2__xo(zeta),-lambda1__xo(zeta)) ],
  #parameters_guess = [ T=sqrt((x1-x0)^2+(y1-y0)^2)/V],
  states_guess    = GUESS);
