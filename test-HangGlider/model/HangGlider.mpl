
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: HANG GLIDER (Test 11 di COPS, pag 282 libro Betts)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# ODE model
addUserFunction(r(x)=(x/rc-2.5)^2);addUserFunction(u(x)=uc*(1-r(x))*exp(-r(x)));
addUserFunction(w(x,y1)=y1-u(x));addUserFunction(v2(x,x1,y1)=x1^2+w(x,y1)^2);addUserFunction(v(x,x1,y1)=sqrt(v2(x,x1,y1)));
addUserFunction(Dfun(x,x1,y1)=0.5*rho*S*v2(x,x1,y1));
addUserFunction(Lfun(x,x1,y1)=0.5*rho*S*v2(x,x1,y1));
sin_eta := w(x(t),vy(t)) / v(x(t),vx(t),vy(t));
cos_eta := vx(t) / v(x(t),vx(t),vy(t));DD      := (c0+c1*cL(t)^2)*Dfun(x(t),vx(t),vy(t));LL      := cL(t)*Lfun(x(t),vx(t),vy(t));

EQ1 := diff(x(t),t)  = T*vx(t):
EQ2 := diff(y(t),t)  = T*vy(t):
EQ3 := diff(vx(t),t) = T/m*simplify(-LL*sin_eta-DD*cos_eta):
EQ4 := diff(vy(t),t) = T/m*simplify(LL*cos_eta-DD*sin_eta)-T*g:
ode := [EQ||(1..4)]: <%>;
# OCP variables
xvars := map([x,y,vx,vy],(t));
uvars := [cL(t)];
pvars := [T];
# OCP
loadDynamicSystem(
  equations  = ode,
  controls   = uvars,
  states     = xvars,
  parameters = pvars);
addBoundaryConditions(  initial=[x,y,vx,vy],  final=[y,vx,vy]);
infoBoundaryConditions() ;
addControlBound(
  cL,
  controlType = "QUADRATIC2", 
  min         = cL_min,
  max         = cL_max,
  tolerance   = tol_max,  epsilon     = epsi_max,
  scale       = 1
);
#addUnilateralConstraint(
#  vx(zeta)>=0,
#  VXbound,
#  epsilon   = epsi_max, 
#  tolerance = tol_max,
#  scale     = 1, 
#  barrier   = true
#);
addUnilateralConstraint(
  T>=0,
  Tbound,
  epsilon   = 0.1, 
  tolerance = 0.5,
  scale     = 1, 
  barrier   = true
);
# Target function
setTarget(  lagrange = W*(cL(zeta)-0.7)^2,  mayer    = -x(zeta_f));
PARS := [
  uc       = 2.5,  rc       = 100,  c0       = 0.034,
  c1       = 0.069662,
  S        = 14,
  rho      = 1.13,
  m        = 100,
  g        = 9.80665,
  Tguess   = 105,
  epsi_min = 0.0001,
  epsi_max = 0.01,
  tol_min  = 0.0001,
  tol_max  = 0.01,  #  cL_min   = 0,  cL_max   = 1.4,  # BC
  x_i      = 0,  y_i      = 1000,
  y_f      = 900,
  vx_i     = 13.2275675,
  vx_f     = 13.2275675,
  vy_i     = -1.28750052,
  vy_f     = -1.28750052,  W0       = 1000,
  W1       = 0,
  W        = W0
];
POST := [];
CONT := [
  [ W = (1-s)*W0+s*W1 ],
  [    [cL,"epsilon"]   = epsi_max^(1-s)*epsi_min^s,
    [cL,"tolerance"] = tol_max^(1-s)*tol_min^s  ] 
];
GUESS := [
  x  = x_i+zeta*Tguess*vx_i,
  y  = y_i+zeta*Tguess*vy_i,
  vx = vx_i,
  vy = vy_i
  #lambda2__xo = -10,  #lambda3__xo = -10
];PGUESS := [  T = Tguess];
generateOCProblem(
  "HangGlider",
  post_processing    = POST,
  parameters         = PARS,
  continuation       = CONT,
  # scalature
  #states_scaling    = [y=1000,Tm=100],
  #equations_scaling = [3=Iz],
  #
  mesh               = [length=1, n=400],
  controls_iterative = true,
  controls_guess     = [cL=0.7],
  states_guess       = GUESS,
  parameters_guess   = PGUESS
);
ocp := getOCProblem();
eval(ocp["controls"]);
CF1 := simplify(epsilon/log(cos(m_pi_2*(1-h))));P   := CF1*log(cos(m_pi_2*x));
simplify(diff(P,x))/CF1;

