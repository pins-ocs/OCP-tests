restart:;
with(XOptima):;
addUserFunction(cfun(x,y)=1+pos(y-1)^2);
mapUserFunctionToRegularized(pos,"PositivePartRegularizedWithErf",[h=1e-4]);
addUserFunction(yguess(zeta)=ymax_guess*4*zeta*(1-zeta));
addUserFunction(xguess(zeta)=x_i+zeta*(x_f-x_i));
ODE1 := diff(x(t),t)=T*cfun(x(t),y(t))*cos(u(t));
ODE2 := diff(y(t),t)=T*cfun(x(t),y(t))*sin(u(t));
ode := [ODE1,ODE2]: <%>;
uvars := [u(t)]:
xvars := [x(t),y(t)]:
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[x,y],final=[x,y]);
setStatusBoundaryConditions(initial=[x,y],final=[x,y]);
infoBoundaryConditions();
setTarget(
  lagrange = T + WY*(y(zeta)-yguess(zeta))^2, # to exit from local minima
  mayer    = 0
);
addUnilateralConstraint(
  T >= 0,
  Tpositive,
  subtype     = "PENALTY_PIECEWISE",
  epsilon     = T_epsi,
  tolerance   = T_tol
);
PARS := [
  x_i        = -2.5,
  y_i        = 0,
  x_f        = 3,
  y_f        = 0,
  T_epsi     = 0,
  T_tol      = 0.01,
  Tguess     = 1,
  WY         = 1,
  ymax_guess = 1.48001
];
POST := [
  #[ Tpositive(-T), "Tpositive" ],
  [ Tpositive_D(-T), "Tpositive_D" ],
  [ Tpositive_DD(-T), "Tpositive_DD" ],
  [ xguess(zeta), "xguess" ],
  [ yguess(zeta), "yguess" ],
  [ cfun(x(zeta),y(zeta)), "vel" ]
];
CONTINUATION := [
  [ WY = 1-s ]
];
UGUESS := [ u = 0 ];
GUESS := [
  x = xguess(zeta),
  y = yguess(zeta)
];
MESH_DEF := [
  [length=1, n=100]
];
project_dir  := "../generated_code";
project_name := "CristianiMartinon";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  optimization_parameters = [T=Tguess], # uncomment to force iterative control computation
  controls_guess  = UGUESS, # uncomment to force iterative control computation
  states_guess    = GUESS,
  continuation    = CONTINUATION,
  mesh            = MESH_DEF,
  clean           = true
);
ocp := getOCProblem();
eval(ocp["FD"]);
eval(ocp["adjoint_ode"]);
eval(ocp["Hamiltonian"]);
eval(ocp["LT_penalty"]);
eval(ocp["JP_penalty"]);
eval(ocp["JU_penalty"]);
indices(ocp);
# if used in batch mode use the comment to quit;
