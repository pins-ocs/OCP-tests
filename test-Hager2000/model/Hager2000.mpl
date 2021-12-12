restart:;
with(XOptima):;
addUserFunction(x_exact(t)=(2*exp(3*t)+exp(3))/(exp(3*t/2)*(2+exp(3))));
addUserFunction(u_exact(t)=2*(exp(3*t)-exp(3))/(exp(3*t/2)*(2+exp(3))));
ode := [diff(x(t),t) = x(t)/2+u(t)]: <%>;
xvars := [x(t)];
uvars := [u(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[x=1]);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = u(zeta)^2+2*x(zeta)^2
);
;
;
PARS := [];
POST := [
  [ x_exact(zeta), "x_exact" ],
  [ u_exact(zeta), "u_exact" ]
];
CONT := [];
GUESS := [ x = 1];
MESHP_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "Hager_2000";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESHP_DEF,
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
  zeta,[x,x_exact],
  line_opts  = [[color="Blue",thickness=3], [color="Red",thickness=1]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Hager 2000"
);
XOptimaPlots:-plotSolution(
  zeta,[u,u_exact],
  line_opts  = [[color="Blue",thickness=3], [color="Red",thickness=1]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Hager 2000"
);
;
