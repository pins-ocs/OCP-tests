restart:;
with(XOptima):;
#XOptimaInfo() ;
C3 := cos(x3(t));
S3 := sin(x3(t));
U1 := u1(t);
U2 := u2(t);
den := 31/36+9/4*S3^2;
rhs1 := S3*((9/4)*C3*x1(t)^2+2*x2(t)^2) + 
        (4/3)*(U1-U2)-(3/2)*C3*U2;
rhs2 := S3*((7/2)*x1(t)^2+(9/4)*C3*x2(t)^2)-(7/3)*U2+
        (3/2)*C3*(U1-U2);
EQ1    := diff(x1(t),t) = T*rhs1/den:
EQ2    := diff(x2(t),t) = -T*rhs2/den:
EQ3    := diff(x3(t),t) = T*(x2(t)-x1(t)):
EQ4    := diff(x4(t),t) = T*x1(t):
EQNS_T := [ EQ||(1..4)]: <%>;
qvars := [x1(t),x2(t),x3(t),x4(t)];
cvars := [u1(t),u2(t)];
pars := [T]; # optimization parameters;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial = [x1=0,x2=0,x3=0.5,x4=0],
  final   = [x1=0,x2=0,x3=0.5,x4=0.522]
);
infoBoundaryConditions();
PEN := x1(zeta_f)^2+x2(zeta_f)^2+(x3(zeta_f)-0.5)^2+(x4(zeta_f)-0.522)^2;
setTarget(
  mayer    = W*T+(1-W)*(T-10)^2,
  lagrange = 0
);
addControlBound(
  u1,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = 1
);
addControlBound(
  u2,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = 1
);
pars := [
  u_epsilon0   = 0.01,
  u_tolerance0 = 0.01,
  u_epsilon1   = 0.00001,
  u_tolerance1 = 0.00001,
  u_epsilon    = u_epsilon0,
  u_tolerance  = u_tolerance0,
  Tguess       = 10,
  W            = 0
];
GUESS := [
  x3 = 0.5,
  x4 = zeta*0.522
];
PGUESS := [
  T = Tguess
];
CONT := [
  [ W = s ],
  [
    ["u1","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u1","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s,
    ["u2","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u2","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s
  ]
];
#Describe(generateOCProblem);
generateOCProblem(
  "TwoLinkRobotArm",
  parameters              = pars,
  mesh                    = [[length=1,n=400]],
  continuation            = CONT,
  states_guess            = GUESS,
  optimization_parameters = PGUESS
);
#ocp := getOCProblem();
#eval(ocp);
;
