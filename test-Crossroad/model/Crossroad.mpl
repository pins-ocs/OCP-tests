
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Crossroad problem
# Authors: E. Bertolazzi, M.Frego, P.Bevilacqua
# Date:
# 
# Load library
restart:
# Load optimal control library
with(plots):
with(XOptima):
interface(rtablesize=40):
# Equations of Dynamics
EQ1 := diff(s(zeta),zeta)  = Ts(zeta)*v(zeta):
EQ2 := diff(v(zeta),zeta)  = Ts(zeta)*a(zeta):
EQ3 := diff(a(zeta),zeta)  = Ts(zeta)*jerk(zeta):
EQ4 := diff(Ts(zeta),zeta) = 0:
eqns := [EQ||(1..4)]:<%>;
xvars := [s(zeta),v(zeta),a(zeta),Ts(zeta)] ;
uvars := [jerk(zeta)] ;
pars := [] ;
# Optimal control
# Optimal control problem definition
# Load dynamic system
# Load the ODE dynamic system: list of controls, state variables and differential equations.
# By default the command sets the independent variable to "zeta".
#Describe(loadDynamicSystem);
loadDynamicSystem(
  controls   = uvars,
  states     = xvars,
  parameters = pars,
  equations  = eqns
);
addBoundaryConditions(
  initial = [s,v,a],
  final   = [s,v,a]
);
infoBoundaryConditions();
setTarget(
  lagrange = (wT+wJ*jerk(zeta)^2)*Ts(zeta), mayer = 0
);
setInterfaceConditionFree(Ts);
setInterfaceConditionFixed(s,s(zeta_L)=L/2,s(zeta_R)=L/2);
tmp := piecewise(
   s < L/2, ((L/2-s)*kappa0+s*kappa1)/(L/2),
  ((L-s)*kappa1+(s-L/2)*kappa2)/(L/2)
);
tmp1 := piecewise(
   s < L/2, (kappa1-kappa0)/(L/2),
  (kappa2-kappa1)/(L/2)
);
addUserFunction( kappa(s)=tmp, derivatives=0);
addUserFunction( kappa_D(s)=tmp1, derivatives=0);
addUserFunction( kappa_DD(s)=0, derivatives=0);
addControlBound(
  jerk,
  scale       = 1,
  max         = jerk_max,
  min         = jerk_min,
  epsilon     = 0.01,
  tolerance   = 0.01,
  controlType = "U_LOGARITHMIC"
):
addUnilateralConstraint(
  Ts(zeta)>0, Tpositive,
  #barrier   = true,
  scale     = 1,
  epsilon   = 0.01,
  tolerance = 0.01
):
ELLISSE := (a(zeta)/along_max)^2+(v(zeta)^2*kappa(s(zeta))/alat_max)^2;
addUnilateralConstraint(
  ELLISSE <= 1, AccBound,
  #barrier   = true,
  scale     = 1,
  epsilon   = 0.01,
  tolerance = 0.01
):
addBilateralConstraint(
  v(zeta), VelBound,
  #barrier   = true,
  min       = 0,
  max       = v_max,
  scale     = 1,
  epsilon   = 0.01,
  tolerance = 0.01
):
# Optimal Control Problem
# Set guess solution (optional)
# A guess solution can be specified for some or all state variables. The guess solution can be a function of the independent variable "zeta". Piecewise solution are not allowed.
# Note that the lambda3 multiplier cannot vanish, otherwise the corresponding control goes to infinity.
PARS := [
  L         = 100,
  Vmean     = 2,
  s_i       = 0,
  v_i       = 0,
  a_i       = 0,
  s_f       = L,
  v_f       = 1,
  a_f       = 0,
  v_max     = 30,
  along_max = 4,
  alat_max  = 4,
  jerk_min  = -10,
  jerk_max  = 10,
  kappa0    = 0,
  kappa1    = 1/10,
  kappa2    = 1/10,
  wT        = 10,
  wJ        = 1/jerk_max^2
];
GUESS := [
  s = zeta*L,
  v = Vmean,
  a = 0,
  Ts = L/Vmean/2
];
POST := [
  [kappa(s(zeta)), "kappa"],
  [a(zeta)/along_max, "a_su_along"],
  [kappa(s(zeta))*v(zeta)^2/alat_max, "a_su_alat"]
];
ALIAS := [
  D(kappa)=kappa_D, (D@@2)(kappa)=kappa_DD
];
project_dir  := "../";
project_name := "Crossroad";
generateOCProblem(
  clean = false,
  project_name,
  parameters         = PARS,
  states_guess       = GUESS,
  post_processing    = POST,
  aliases            = ALIAS,
  controls_iterative = true,
  controls_guess     = [jerk = 0],
  mesh               = [[length = 0.5, n = 100],[length = 0.5, n = 100]]
); 
#tmp := getOCProblem();
#eval(tmp);
# Plotting
launchSolver(project_dir,project_name);
with(plots):
XOptimaPlots:-loadSolution(project_dir,project_name);# load solution
XOptimaPlots:-getHeaders();
z_sol      := XOptimaPlots:-getSolution(zeta):
jerk_sol   := XOptimaPlots:-getSolution(jerk):
s_sol      := XOptimaPlots:-getSolution(s):
v_sol      := XOptimaPlots:-getSolution(v):
a_sol      := XOptimaPlots:-getSolution(a):
a_su_along := XOptimaPlots:-getSolution(a_su_along):
a_su_alat  := XOptimaPlots:-getSolution(a_su_alat):
kappa      := XOptimaPlots:-getSolution(kappa):
Ts_sol     := XOptimaPlots:-getSolution(Ts):
lgr_sol    := XOptimaPlots:-getSolution("lagrange_target"):

printf("Ts = %g\n", Ts_sol[-1]);
printf("Ts = %g\n", Ts_sol[1]);
display(
  XOptimaPlots:-plotSolution(
    zeta, ["s"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=["s [m]",""]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[1000,200],
  view = -10..100
);
display(
  XOptimaPlots:-plotSolution(
    s, ["v"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=["s [m]",""]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[1000,200],
  view = 0..15
);
display(
  XOptimaPlots:-plotSolution(
    s, ["a"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=["acc [m/s^2]",""]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[1000,200],
  view = -5..5
);
display(
  XOptimaPlots:-plotSolution(
    s, ["jerk"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=[" jerk [m/s^3]",""]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[1000,200],
  view = -10..10
);
display(
  implicitplot(x^2+y^2-1,x=-1..1,y=-1..1),
  XOptimaPlots:-plotSolution(
    a_su_along, ["a_su_alat"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=["gg1","gg2"]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[400,400],
  view = [-1..1,-1..1]
);
display(
  XOptimaPlots:-plotSolution(
    s, ["kappa"],
    line_opts = [[color="Blue",thickness=1]],
    plot_opts = [labels=["s [m]",""]]
  ),
  axes=boxed,
  #axis[1] = [gridlines=[linestyle=dot]],
  size=[1000,200],
  view = -0.1..0.1
);
ell := a_su_alat^~2+a_su_along^~2;
plot([seq([s_sol[k],ell[k]],k=1..202)]);

