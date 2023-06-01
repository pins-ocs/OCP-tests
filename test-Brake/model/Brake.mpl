restart:;
with(plots):
with(XOptima):
interface(rtablesize=40):;
EQ1 := diff(x(t),t) = T*v(t):
EQ2 := diff(v(t),t) = T*a(t):
EQ3 := tau*diff(a_tau(t),t) = T*(a(t)-a_tau(t)):;
eqns_t := [EQ||(1..3)]:<%>;
xvars_t := map([x,v,a_tau],(t));
uvars_t := [a(t)];
#Describe(loadDynamicSystem);
loadDynamicSystem(
  controls  = uvars_t,
  states    = xvars_t,
  equations = eqns_t
);
addBoundaryConditions(
  initial = [x,v,a_tau],
  final   = [v]
);
infoBoundaryConditions();
setTarget(
  lagrange = W_A_TAU*(a(zeta)-a_tau(zeta))^2,
  mayer    = x(zeta_f)
);
addControlBound(
  a,
  scale       = T,
  max         = 1,
  min         = -1,
  epsilon     = 0.1,
  tolerance   = 0.01,
  controlType = "U_COS_LOGARITHMIC"
):;
addUnilateralConstraint(
  T>0, Tpositive,
  #barrier   = true,
  scale     = 1,
  epsilon   = 0.1,
  tolerance = 0.01
):;
PARS := [
  x_i      = 0,
  v_i      = 1,
  v_f      = 0,
  a_tau_i  = 0,
  Tguess   = 1,
  tau      = 0.01,
  W_A_TAU0 = 0.1,
  W_A_TAU1 = 0,
  W_A_TAU  = W_A_TAU0
];
#Describe(addUserFunction):;
addUserFunction( guess_x(s)     = x_i );
addUserFunction( guess_v(s)     = v_i );
addUserFunction( guess_a_tau(s) = a_tau_i );
GUESS := [
  x     = guess_x(zeta),
  v     = guess_v(zeta),
  a_tau = guess_a_tau(zeta)
];
CONT := [
  [ W_A_TAU = W_A_TAU0*(1-s)+W_A_TAU1*s ]
];
project_dir  := "../generated_code";
project_name := "Brake";
generateOCProblem(
  project_name,
  parameters              = PARS,
  states_guess            = GUESS,
  optimization_parameters = [ T = Tguess ],
  #continuation            = CONT,
  controls_iterative      = true,
  controls_guess          = [ a = 0 ],
  mesh                    = [[length = 1, n = 50]],
  clean                   = false
);
#ocp := getOCProblem();
#eval(ocp["adjoint_ode"]);
#eval(ocp["controls"]);
#eval(ocp["FD"]["bc"]);
#eval(ocp["FD"]["fd_BC"]);
# if used in batch mode use the comment to quit;
