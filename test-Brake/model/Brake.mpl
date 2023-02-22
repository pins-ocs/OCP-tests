restart:;
with(plots):
with(XOptima):
interface(rtablesize=40):;
EQ1 := diff(x(t),t) = T*v(t):
EQ2 := diff(v(t),t) = T*a(t):;
eqns_t := [EQ||(1..2)]:<%>;
xvars_t := [x(t),v(t)];
uvars_t := [a(t)];
pars := [T]; # optimization parameters;
#Describe(loadDynamicSystem);
loadDynamicSystem(
  controls  = uvars_t,
  states    = xvars_t,
  equations = eqns_t
);
addBoundaryConditions(
  initial = [x,v],
  final   = [v]
);
infoBoundaryConditions();
setTarget(
  lagrange = -T*epsilon*log(cos(Pi/2*a(zeta)))
           + mu*(a(zeta)-guess_u(zeta))^2,
  mayer    = x(zeta_f)-epsilon2*log(T)
);
#addControlBound(
#  a,
#  scale       = T,
#  max         = 1,
#  min         = -1,
#  epsilon     = 0.01, # per convergere deve essere 0.0001,
#  tolerance   = 0.01,
#  controlType = "U_LOGARITHMIC"
#):;
#addUnilateralConstraint(
#  T>0, Tpositive,
#  #barrier   = true,
#  scale     = 1,
#  epsilon   = 0.01,
#  tolerance = 0.01
#):;
PARS := [
  x_i      = 0,
  v_i      = 1,
  v_f      = 0,
  Tguess   = 1,
  epsilon  = 0.1,
  epsilon2 = 0,
  mu       = 0
];
#Describe(addUserFunction):;
addUserFunction( guess_x(s)       = Tguess*s );
addUserFunction( guess_v(s)       = v_i      );
addUserFunction( guess_lambda1(s) = 1        );
addUserFunction( guess_lambda2(s) = 1-s      );
addUserFunction( guess_u(s)       = -1       );
GUESS := [
  x           = guess_x(zeta),
  v           = guess_v(zeta),
  lambda1__xo = guess_lambda1(zeta),
  lambda2__xo = guess_lambda2(zeta)
];
project_dir  := "../generated_code";
project_name := "Brake";
generateOCProblem(
  project_name,
  parameters              = PARS,
  states_guess            = GUESS,
  optimization_parameters = [ T = Tguess ],
  controls_guess          = [ a = 0 ],
  mesh                    = [[length = 1, n = 150]],
  clean                   = false
);
ocp := getOCProblem();
eval(ocp["adjoint_ode"]);
eval(ocp["controls"]);
eval(ocp["FD"]["bc"]);
eval(ocp["FD"]["fd_BC"]);
eval(ocp["FD"]["fd_ode"]);
eval(ocp["FD"]["fd_ode2"]);
eval(ocp["FD"]["fd_int"]);
# if used in batch mode use the comment to quit;
