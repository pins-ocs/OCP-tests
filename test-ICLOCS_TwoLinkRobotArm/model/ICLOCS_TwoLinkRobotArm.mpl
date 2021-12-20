restart:;
with(XOptima):;
DEN := 31/36+9/4*sin(theta)^2;
if true then
  # wrong equations in ICLOCS?
  RHS1 := sin(theta)*((9/4)*cos(theta)*omega__alpha^2) +2*omega__beta^2 ####)
        + (4/3)*(u1-u2) - (3/2)*cos(theta)*u2;
  RHS2 := sin(theta)*((9/4)*cos(theta)*omega__beta^2) + (7/2)*omega__alpha^2####)
      - (7/3)*u2 + (3/2)*cos(theta)*(u1-u2);
else
  RHS1 := sin(theta)*((9/4)*cos(theta)*omega__alpha^2 + 2*omega__beta^2 )
        + (4/3)*(u1-u2) - (3/2)*cos(theta)*u2;
  RHS2 := sin(theta)*((9/4)*cos(theta)*omega__beta^2 + (7/2)*omega__alpha^2 )
      - (7/3)*u2 + (3/2)*cos(theta)*(u1-u2);
end;
SUBS := theta        = theta(t),
        omega__alpha = omega__alpha(t),
        omega__beta  = omega__beta(t),
        u1           = u1(t),
        u2           = u2(t);
EQ1    := diff(omega__alpha(t),t) = T*subs(SUBS,RHS1/DEN):
EQ2    := diff(omega__beta(t),t)  = T*subs(SUBS,-RHS2/DEN):
EQ3    := diff(theta(t),t)        = T*(omega__beta(t)-omega__alpha(t)):
EQ4    := diff(alpha(t),t)        = T*omega__alpha(t):
EQNS_T := [ EQ||(1..4)]: <%>;
qvars := [omega__alpha(t),omega__beta(t),theta(t),alpha(t)];
cvars := [u1(t),u2(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [omega__alpha,omega__beta,theta,alpha],
  final   = [omega__alpha,omega__beta,theta,alpha]
);
infoBoundaryConditions();
setTarget(
  mayer    = W*T+(1-W)*(T-T_guess)^2/T,
  lagrange = rho*T*(u1(zeta)^2+u2(zeta)^2)
);
addControlBound(
  u1,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = T
);
addControlBound(
  u2,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = T
);
;
PARS := [
  u_epsilon0     = 0.01,
  u_tolerance0   = 0.01,
  u_epsilon1     = 0.00001,
  u_tolerance1   = 0.00001,
  u_epsilon      = u_epsilon0,
  u_tolerance    = u_tolerance0,
  T_guess        = 3,
  W              = 0,

  rho            = 0.01,

  omega__alpha_i = 0,
  omega__beta_i  = 0,
  theta_i        = 0,
  alpha_i        = 0,


  omega__alpha_f = 0,
  omega__beta_f  = 0,
  theta_f        = 0.5,
  alpha_f        = 0.522
];
POST := [ [ zeta*T, "time" ] ];
CONT := [
  [ W = s ],
  [
    ["u1","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u1","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s,
    ["u2","epsilon"]   = u_epsilon0^(1-s)*u_epsilon1^s,
    ["u2","tolerance"] = u_tolerance0^(1-s)*u_tolerance1^s
  ]
];
GUESS := [
  omega__alpha = (1-zeta)*omega__alpha_i + zeta*omega__alpha_f,
  omega__beta  = (1-zeta)*omega__beta_i + zeta*omega__beta_f
];
PGUESS := [ T = T_guess ];
MESH_DEF := [[length=1,n=800]];
project_dir  := "../generated_code";
project_name := "ICLOCS_TwoLinkRobotArm";
generateOCProblem(
  project_name, clean=false,
  parameters              = PARS,
  post_processing         = POST,
  mesh                    = MESH_DEF,
  controls_iterative      = true,
  continuation            = CONT,
  states_guess            = GUESS,
  optimization_parameters = PGUESS
);
# if used in batch mode use the comment to quit;
