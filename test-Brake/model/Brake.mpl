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
  controls   = uvars_t,
  states     = xvars_t,
  equations  = eqns_t
);
addBoundaryConditions(
  initial = [x,v],
  final   = [v]
);
infoBoundaryConditions();
setTarget(
  lagrange = 0,
  mayer    = x(zeta_f)+v(zeta_f)^2 # v aiuta nella convergenza
);
addControlBound(
  a,
  scale       = 1,
  max         = 1,
  min         = -1,
  epsilon     = 0.01, # per convergere deve essere 0.0001,
  tolerance   = 0.01,
  controlType = "U_LOGARITHMIC"
):;
addUnilateralConstraint(
  T>0, Tpositive,
  #barrier   = true,
  scale     = 1,
  epsilon   = 0.01,
  tolerance = 0.01
):;
PARS := [ x_i = 0, v_i = 1, v_f = 0];
GUESS := [ x = 0, v = 1];
project_dir  := "../generated_code";
project_name := "Brake";
generateOCProblem(
  project_name,
  parameters              = PARS,
  states_guess            = GUESS,
  optimization_parameters = [ T = 1 ],
  mesh                    = [[length = 1, n = 400]],
  clean                   = false
);
# if used in batch mode use the comment to quit;
