restart:;
with(XOptima);
addUserFunction(mass(t)=1-md*t);
EQ1    := diff(r(t),t)  = vr(t):
EQ2    := diff(vr(t),t) = vt(t)^2/r(t)-1/r(t)^2+T*sin(theta(t))/mass(t):
EQ3    := diff(vt(t),t) = -vr(t)*vt(t)/r(t)+T*cos(theta(t))/mass(t):
EQNS_T := [ EQ||(1..3)]: <%>;
qvars := [r(t),vr(t),vt(t)] ;
cvars := [theta(t)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial=[r=1,vr=0,vt=1],
  final=[vr=0],
  generic=[
    [r(zeta_f)*vt(zeta_f)^2=1,"rvt"]
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = -vr(zeta)
);
;
;
PARS := [
  theta_max = Pi,
  T         = 0.1405,
  md        = 0.0749,
  tf        = 3.32
];
POST := [
  [ theta(zeta) - floor(theta(zeta)/(2*Pi))*(2*Pi), "THETA" ],
  [ mass(zeta), "MASS" ]
];
CONT := [
];
GUESS := [
  r  = 1,
  vr = 0,
  vt = 1,
  lambda3__xo = -1e-10
];
REGION := [
  [ theta(zeta) >= -theta_max, "u" ],
  [ theta(zeta) <=  theta_max, "u" ]
];
MESH_DEF := [length=tf,n=400];
project_dir  := "../generated_code";
project_name := "ICLOCS_MinimumFuelOrbitRaising";
U_SOLVED := [theta = arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))];
generateOCProblem(
  project_name, clean = false,
  post_processing       = POST,
  parameters            = PARS,
  user_parameters       = [ theta_max ],
  mesh                  = MESH_DEF,
  continuation          = CONT,
  controls_iterative    = false,
  controls_guess        = U_SOLVED,
  controls_user_defined = U_SOLVED,
  states_guess          = GUESS,
  admissible_region     = REGION
);
ocp := getOCProblem();
eval(ocp["controls"]);
collect(ocp["controls"]["g_fun"],[sin,cos,theta]);
subs(theta(zeta_M)=TH,%):
simplify(diff(%,TH));
ocp["controls"]["g"];
#eval(ocp);
# if used in batch mode use the comment to quit;
# quit;
#launchSolver(project_dir,project_name);
compileSolver(project_dir,project_name);
runSolver(project_dir);
with(plots):;
XOptimaPlots:-loadSolution(project_dir,project_name); # load solution
hhdrs := XOptimaPlots:-getHeaders(): nops(%);
zeta_sol := XOptimaPlots:-getSolution( zeta ):
u_sol    := XOptimaPlots:-getSolution( theta ):
MASS_sol := XOptimaPlots:-getSolution( MASS ):;
MASS_sol[1];MASS_sol[-1];
XOptimaPlots:-plotSolution(
  zeta,[r,vr,vt],
  line_opts  = [[color="Blue",thickness=3],
                [color="Red",thickness=3],
                [color="Green",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Minimum Fuel Orbit Raising"
);
XOptimaPlots:-plotSolution(
  zeta,[theta,THETA],
  line_opts  = [[color="Blue",thickness=4],[color="Red",thickness=2,style=pointline]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Minimum Fuel Orbit Raising"
);
XOptimaPlots:-plotSolution(
  zeta,[lambda1__xo,lambda2__xo,lambda3__xo],
  line_opts  = [[color="Blue",thickness=3],
                [color="Red",thickness=3],
                [color="Green",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Minimum Fuel Orbit Raising"
);
XOptimaPlots:-plotSolution(
  zeta,[MASS],
  line_opts  = [[color="Blue",thickness=4]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Minimum Fuel Orbit Raising"
);
