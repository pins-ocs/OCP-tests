restart:;
with(XOptima):;
EQ1    :=  diff(x(t),t) - v(t):
EQ2    :=  diff(v(t),t) - F(t):
EQNS_T := [ EQ||(1..2) ]: <%>;
qvars := [x(t),v(t)];
cvars := [F(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions();
setTarget( mayer = -x(zeta_f) );
addControlBound( F, controlType="U_COS_LOGARITHMIC", maxabs=1 );
PARS := [ x_i = 0, x_f=0, v_i=0, v_f=0 ];
POST := [];
CONT := [];
GUESS := [ v = zeta*(1-zeta) ];
MESH_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "BangBangF";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESH_DEF,
  states_guess    = GUESS
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
  zeta,[x,v],
  line_opts  = [[color="Blue",thickness=3], [color="Red",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Bang Bang"
);
XOptimaPlots:-plotSolution(
  zeta,[F],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Bang Bang"
);
;
