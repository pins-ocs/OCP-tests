restart:;
with(XOptima):;
XOptimaInfo() ;
EQ1    := diff(x(t),t) - v(t) :
EQ2    := diff(v(t),t) - F1(t) - F2(t) :
EQ3    := diff(F1(t),t) - vF1(t) :
EQ4    := diff(F2(t),t) - vF2(t) :
EQ5    := diff(vF1(t),t) - aF1(t) :
EQ6    := diff(vF2(t),t) - aF2(t) :
EQNS_T := [ EQ||(1..6) ]: <%>;
qvars := [x(t),v(t),F1(t),F2(t),vF1(t),vF2(t)];
cvars := [aF1(t), aF2(t)];
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars);
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions();
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithErf",
  [ h=h0, delta=0 ]
);
setTarget( mayer = -x(zeta_f)+Flim(F1(zeta_i)+F2(zeta_i))+
                              Flim(F1(zeta_f)+F2(zeta_f)) );
addControlBound(
  aF1,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = maxAF
);
addControlBound(
  aF2,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = maxAF
);
addBilateralConstraint(
  F1(zeta)+F2(zeta),
  Flim,
  scale = w_F
);#,barrier=true,subtype="BARRIER_LOG");
PARS := [ h0 = 0.01, maxAF=100, w_F=10 ];
POST := [
  [F1(zeta)+F2(zeta),"F1+F2"]
];
CONTINUATION := [];
GUESS := [ v = zeta*(1-zeta) ];
MESH_DEF := [ length=1, n=100 ];
project_dir  := "../generated_code";
project_name := "BangBangFredundant";
generateOCProblem(
  project_name,
  standard_post_processing = true,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONTINUATION,
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
  zeta,[F1,F2],
  line_opts  = [[color="Blue",thickness=3],[color="Red",thickness=2]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Bang Bang"
);
XOptimaPlots:-plotSolution(
  zeta,[vF1,vF2],
  line_opts  = [[color="Blue",thickness=3],[color="Red",thickness=2]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Bang Bang"
);
XOptimaPlots:-plotSolution(
  zeta,[aF1,aF2],
  line_opts  = [[color="Blue",thickness=3],[color="Red",thickness=2]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "Bang Bang"
);
;
