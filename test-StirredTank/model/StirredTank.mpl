restart:;
with(XOptima):
with(plots):;
cf1 := 176/10;
cf2 := 23;
cf3 := 146;
cf4 := 73;
cf5 := 352/10;
cf6 := 513/10;
cf7 := 219;
cf8 := 102;
cf9 := 46;
cf10 := 58/10;
cf11 := 37/10;
cf12 := 41/10;
cf13 := 11;
cf14 := 28;
cf15 := 35;
cf16 := 5;
cf17 := 9/100;
q := u1(t) + u2(t) + u4(t);
eqns := [
  diff(x1(t),t) = u4(t) - q*x1(t) - cf1*x1(t)*x2(t)-cf2*x1(t)*x6(t)*u3(t),
  
  diff(x2(t),t) = u1(t) - q*x2(t) - cf1*x1(t)*x2(t)-cf3*x2(t)*x3(t), 
  
  diff(x3(t),t) = u2(t) - q*x3(t) - cf4*x2(t)*x3(t),
  
  diff(x4(t),t) = -q*x4(t) + cf5*x1(t)*x2(t) - cf6*x4(t)*x5(t),
  
  diff(x5(t),t) = -q*x5(t) + cf7*x2(t)*x3(t) - cf6*x4(t)*x5(t),
  
  diff(x6(t),t) = -q*x6(t) + cf8*x4(t)*x5(t) - cf2*x1(t)*x6(t)*u3(t),
  
  diff(x7(t),t) = -q*x7(t) + cf9*x1(t)*x6(t)*u3(t),

  diff(x8(t),t) = cf10*(q*x1(t) - u4(t))
                - cf11*u1(t) - cf12*u2(t)
                + q*(cf2*x4(t) + cf13*x5(t) + cf14*x6(t) + cf15*x7(t))
                - cf16*u3(t)^2 - cf17]: <%>;
simplify(expand(add( eqns[i],i=1..8 )));
x0 := [0.1883, 0.2507, 0.0467, 0.0899, 0.1804, 0.1394, 0.1046, 0.0];
qvars := [seq(x||i(t),i=1..8)];
cvars := [seq(u||i(t),i=1..4)] ;
;
loadDynamicSystem( equations = eqns,controls = cvars ,states = qvars ) ;
addBoundaryConditions(
  initial = [seq(x||i=x0[i],i=1..8)],
  final   = []
);
setTarget(
  lagrange = 0,
  mayer    = -x8(zeta_f)
);
UTYPE := "COS_LOGARITHMIC";
addControlBound(
  u1,
  controlType = UTYPE,
  epsilon     = epsi_max,
  tolerance   = tol_max,
  min         = 0,
  max         = 20
);

addControlBound(
  u2,
  controlType = UTYPE,
  epsilon     = epsi_max,
  tolerance   = tol_max,
  min         = 0,
  max         = 6
);

addControlBound(
  u3,
  controlType = UTYPE,
  epsilon     = epsi_max,
  tolerance   = tol_max,
  min         = 0,
  max         = 4
);

addControlBound(
  u4,
  controlType = UTYPE,
  epsilon     = epsi_max,
  tolerance   = tol_max,
  min         = 0,
  max         = 20
);
guess  := [ seq(x||i=1,i=1..8)];
uguess := [u1 = 1, u2 = 1, u3 = 1, u4 =1];
project_dir  := "../generated_code";
project_name := "stirred_tank";
pars := [
  tf       = 0.2,
  epsi_max = 0.1,
  epsi_min = 0.001,
  tol_max  = 0.1,
  tol_min  = 0.001
];
CONTINUATION := [
  [
    epsi = (1-s)*epsi_max+s*epsi_min,
    tol  = (1-s)*tol_max+s*tol_min,
    [u1,"epsilon"] = epsi,
    [u2,"epsilon"] = epsi,
    [u3,"epsilon"] = epsi,
    [u4,"epsilon"] = epsi,
    [u1,"tolerance"] = tol,
    [u2,"tolerance"] = tol,
    [u3,"tolerance"] = tol,
    [u4,"tolerance"] = tol
  ]
];
#Describe(generateOCProblem);
post_proc_list := [];
generateOCProblem(
  project_name, clean = true,
  mesh               = [ length = tf, n =1000 ],
  states_guess       = guess,
  controls_iterative = true,
  controls_guess     = uguess,
  post_processing    = post_proc_list,
  continuation       = CONTINUATION,
  parameters         = pars
):;
compileSolver( project_dir, project_name );
runSolver(project_dir);
XOptimaPlots:-loadSolution(project_dir,project_name);
hhdrs := XOptimaPlots:-getHeaders(): nops(%);
XOptimaPlots:-plotSolution(
  zeta,["u1"],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);

XOptimaPlots:-plotSolution(
  zeta,["u2"],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);

XOptimaPlots:-plotSolution(
  zeta,["u3"],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);

XOptimaPlots:-plotSolution(
  zeta,["u4"],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);
XOptimaPlots:-plotSolution(
  zeta,["x8"],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);


XOptimaPlots:-plotSolution(
  zeta,["x1", "x2"],
  line_opts  = [[color="Blue",thickness=3],[color="DeepPink",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);


XOptimaPlots:-plotSolution(
    zeta,["x3", "x4"],
  line_opts  = [[color="Blue",thickness=3],[color="DeepPink",thickness=3]],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);

XOptimaPlots:-plotSolution(
    zeta,["x5", "x6"],
  line_opts  = [[color="Blue",thickness=3],[color="DeepPink",thickness=3]],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);

XOptimaPlots:-plotSolution(
    zeta,["x7", "x8"],
  line_opts  = [[color="Blue",thickness=3],[color="DeepPink",thickness=3]],
  line_opts  = [[color="Blue",thickness=3]],
  plot_opts  = [gridlines=true, axes=boxed,labels=["Time","States"],scaling=unconstrained],
  plot_title = "control u1"
);
;
