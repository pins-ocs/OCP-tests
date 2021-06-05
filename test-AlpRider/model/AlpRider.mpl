
# 
# XOPTIMA Automatic Code Generationfor Optimal Control Problems 
# 
# Optimal Control Problem: Alp Rider 
# Authors: E. Bertolazzi, F. Biral
# 
# A Collection of Optimal Control Test Problems
# John T. Betts 1 November 17, 2015
restart:
with(XOptima):
XOptimaInfo();
# Equations of motion
EQ1    := diff(y1(t),t) = -10*y1(t) + u1(t)   + u2(t):
EQ2    := diff(y2(t),t) = -2*y2(t)  + u1(t)   + 2*u2(t):
EQ3    := diff(y3(t),t) = -3*y3(t)  + 5*y4(t) + u1(t) - u2(t):
EQ4    := diff(y4(t),t) =  5*y3(t)  - 3*y4(t) + u1(t) + 3*u2(t):EQNS_T := [ EQ||(1..4) ]:<%>;
qvars := map([y1,y2,y3,y4],(t));
cvars := map([u1,u2],(t));
# Optimal Control: problem definition
# Load dynamical system
#infoRegisteredObjects() ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
# Boundary conditions
addBoundaryConditions(
  initial = [ y1, y2, y3, y4 ],
  final   = [ y1, y2, y3, y4 ]
);
infoBoundaryConditions() ;
pp := (t,a,b)->exp(-b*(t-a)^2);qq := 3*pp(t,3,12)+3*pp(t,6,10)+3*pp(t,10,6)+8*pp(t,15,4)+0.01;
plot(qq,t=0..20);
100*int(qq,t=0..20);
addUserFunction(p(t,a,b)=exp(-b*(t-a)^2));
addUserFunction(q(t)=3*p(t,3,12)+3*p(t,6,10)+3*p(t,10,6)+8*p(t,15,4)+0.01);
# Constraints on control
SUMQ := y1(zeta)^2+y2(zeta)^2+y3(zeta)^2+y4(zeta)^2;
addUnilateralConstraint(
  SUMQ >= q(zeta),
  Ybound,
  barrier   = false,  epsilon   = epsi,
  tolerance = tol,
  scale     = 1+SUMQ
);
# Cost function: target
TARGET1 := SUMQ;
TARGET2 := u1(zeta)^2+u2(zeta)^2;
setTarget( lagrange = W*TARGET1 + TARGET2/100 );
PARS := [
  y1_i  = 2, y2_i = 1, y3_i = 2, y4_i = 1,
  y1_f  = 2, y2_f = 3, y3_f = 1, y4_f = -2,
  W     = W0,  W0    = 0,  W1    = 100,  epsi0 = 0.1,
  epsi1 = 0.001,
  epsi  = epsi0,
  tol0  = 0.1,
  tol1  = 0.001,
  tol   = tol0
];
GUESS := [
  y1 = y1_i + zeta*(y1_f-y1_i),
  y2 = y2_i + zeta*(y2_f-y2_i),
  y3 = y3_i + zeta*(y3_f-y3_i),
  y4 = y4_i + zeta*(y4_f-y4_i)
];
CONT := [
  [
    ["Ybound","epsilon"]   = epsi0*(1-s)+epsi1*s,
    ["Ybound","tolerance"] = tol0*(1-s)+tol1*s,
    W = (1-s)*W0+s*W1  ]
];
# Problem generation
#Describe(generateOCProblem);
POST := [
  [ SUMQ, "sumy^2" ],
  [ q(zeta), "q" ]
];
Mesh := [
  [length=1,  n=400],
  [length=18, n=400],
  [length=1,  n=400]
];
Mesh2 := [length=20, n=4000];
generateOCProblem(
  "AlpRider", clean=true,
  parameters           = PARS,
  mesh                 = Mesh2,
  states_guess         = GUESS,
  continuation         = CONT,
  post_processing      = POST,
  max_accumulated_iter = 4000
);

