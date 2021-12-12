restart:;
with(XOptima):;
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = u(t):
EQNS_T := [ EQ||(1..2)]: <%>;;
qvars := [x1(t),x2(t)];
cvars := [u(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  generic=[
    [x1(zeta_i)-x1(zeta_f)=0,"x1_periodic"],
    [x2(zeta_i)-x2(zeta_f)=0,"x2_periodic"]
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = (x1(zeta)^2+x2(zeta)^4)/4-x2(zeta)^2/2+b/2*u(zeta)^2
);
;
;
PARS := [
  b0 = 0.01,
  b1 = 1e-5,
  b  = b0
];
POST := [
  [ x_exact(zeta), "x_exact" ],
  [ u_exact(zeta), "u_exact" ]
];
CONT := [
  [ b = b0*(1-s)+b1*s ]
];
GUESS := [
  x1 = sin(2*Pi*zeta),
  x2 = cos(2*Pi*zeta) # must be initialized
];
PGUESS := [
];
MESH_DEF := [length=1, n=1000];
project_dir  := "../generated_code";
project_name := "ICLOCS_Speyer";
generateOCProblem(
  project_name,
  parameters       = PARS,
  mesh             = MESH_DEF,
  continuation     = CONT,
  #controls_guess   = [u=1],
  states_guess     = GUESS
);
# if used in batch mode use the comment to quit;
# quit;
#launchSolver(project_dir,project_name);
compileSolver(project_dir,project_name);
runSolver(project_dir);
with(plots):;
XOptimaPlots:-loadSolution(project_dir,project_name); # load solution
hhdrs := XOptimaPlots:-getHeaders(): nops(%);
XOptimaPlots:-plotSolution(
  zeta,[x1,x2],
  line_opts  = [[color="Blue",thickness=3], [color="Red",thickness=1]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Speyer Problem"
);
XOptimaPlots:-plotSolution(
  zeta,[u],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Speyer Problem"
);
;
