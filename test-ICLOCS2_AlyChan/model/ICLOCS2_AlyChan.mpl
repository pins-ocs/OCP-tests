#restart:;
with(XOptima):;
XOptimaInfo();
EQ1    := diff(x1(t),t) = x2(t):
EQ2    := diff(x2(t),t) = u(t):
EQ3    := diff(x3(t),t) = (x2(zeta)^2-x1(zeta)^2)/2:
EQNS_T := [ EQ||(1..3) ]: <%>;
qvars := map([x1,x2,x3],(t));
cvars := [u(t)];
#infoRegisteredObjects();
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[x1=x1_i,x2=x2_i,x3=x3_i]
);
infoBoundaryConditions();
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsi,
  tolerance   = u_tol,
  scale       = 1
);
#setTarget( lagrange = x2(zeta)^2-x1(zeta)^2 );
setTarget( mayer = x3(zeta_f) );
PARS := [
  x1_i       = 0,
  x2_i       = 1,
  x3_i       = 0,
  u_epsi_max = 1e-6,
  u_tol_max  = 1e-6,
  u_epsi_min = 1e-10,
  u_tol_min  = 1e-10,
  u_epsi     = u_epsi_max,
  u_tol      = u_tol_max
 ];
GUESS := [ x1 = x1_i, x2 = x2_i, x3 = x3_i ];
CONT :=[
  [
    [u,"epsilon"]   = u_epsi_max*(1-s) + u_epsi_min*s,
    [u,"tolerance"] = u_tol_max*(1-s)  + u_tol_min*s 
  ] 
];
project_dir  := "../generated_code";
project_name := "ICLOCS2_AlyChan";
generateOCProblem(
  project_name, clean=true,
  parameters   = PARS,
  mesh         = [ length = Pi/2, n = 400 ],
  states_guess = GUESS,
  continuation = CONT
);
# if used in batch mode use the comment to quit;
# quit;
#launchSolver(project_dir,project_name);
compileSolver(project_dir,project_name);
runSolver(project_dir);
with(plots):;
XOptimaPlots:-loadSolution(project_dir,project_name);
hhdrs := XOptimaPlots:-getHeaders(): nops(%);
interface(rtablesize=50):;
z_sol       := XOptimaPlots:-getSolution(zeta):
u_sol       := XOptimaPlots:-getSolution(u):
x1_sol      := XOptimaPlots:-getSolution(x1):
x2_sol      := XOptimaPlots:-getSolution(x2):
x3_sol      := XOptimaPlots:-getSolution(x3):
lambda1_sol := XOptimaPlots:-getSolution(lambda1__xo):
lambda2_sol := XOptimaPlots:-getSolution(lambda2__xo):
lambda3_sol := XOptimaPlots:-getSolution(lambda3__xo):;
XOptimaPlots:-plotSolution(
  zeta,[x1,x2,x3],
  line_opts  = [[color="Red",thickness=1],[color="Green",thickness=1],[color="Blue",thickness=1]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=constrained],
  plot_title = "Aly Chan problem"
);
XOptimaPlots:-plotSolution(
  zeta,[u],
  line_opts  = [[color="Blue",thickness=1]],

  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","Control"],scaling=constrained],
  plot_title = "Aly Chan problem"
);
;
;
