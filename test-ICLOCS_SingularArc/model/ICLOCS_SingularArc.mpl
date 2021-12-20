restart:
with(plots):
interface(rtablesize=20):
plots[setcolors]("spring"):
c_set := ColorTools:-GetPalette("spring");
	
FONT_TYPE := "Helvetica":
plots[setoptions](axes            = boxed,
                  size            = [800,400],
                  axis[2]         = [gridlines = [linestyle=dot]],
                  legendstyle     = [location="top",font=[FONT_TYPE,10]],
                  labelfont       = [FONT_TYPE,10], 
                  axesfont        = [FONT_TYPE,10], 
                  titlefont       = [FONT_TYPE,bold,12], 
                  captionfont     = [FONT_TYPE,italic, 12],
                  labeldirections = [horizontal , vertical]
);
with(XOptima):;
EQ1    := diff(x1(t),t) = T*u(t):
EQ2    := diff(x2(t),t) = T*cos(x1(t)):
EQ3    := diff(x3(t),t) = T*sin(x1(t)):
EQNS_T := [ EQ||(1..3)]: <%> ;
xvars := map([x1,x2,x3],(t));
uvars := [u(t)];
loadDynamicSystem(
  equations = [EQ1,EQ2,EQ3],
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial=[x1,x2,x3],
  final=[x2=0,x3=0]
);
infoBoundaryConditions();
setTarget( mayer = T, lagrange = 0 );
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = -2,
  max         = 2,
  epsilon     = epsi_ctrl,
  tolerance   = tol_ctrl,
  scale       = 1
);
addUnilateralConstraint(
  T>0,
  tfbound,
  epsilon   = epsi_T,
  tolerance = tol_T,
  barrier   = true
);
#addUserFunction();
#addUserFunction();
PARS :=  [
  epsi_ctrl0 = 0.01,
  tol_ctrl0  = 0.01,
  epsi_ctrl1 = 0.0001,
  tol_ctrl1  = 0.0001,
  epsi_ctrl  = epsi_ctrl0,
  tol_ctrl   = tol_ctrl0,
  epsi_T     = 0.01,
  tol_T      = 0.1,
  x1_i       = Pi/2,
  x2_i       = 4,
  x3_i       = 0,
  T_init     = 100
];
OPT_PARS := [];
POST := [[ zeta*T, "time"] ];
IPOST := [[x1(zeta)^2+x2(zeta)^2,"intTarget"]];
GUESS := [
  x1 = x1_i*(1-zeta),
  x2 = x2_i*(1-zeta),
  x3 = 0,
  lambda3__xo = -1 # must be initialized
];
PGUESS := [
  T = T_init
];
MESH_DEF := [length=1,n=400];
CONT := [
  [ 
    ["u","epsilon"]   = epsi_ctrl0^(1-s)*epsi_ctrl1^s,
    ["u","tolerance"] = tol_ctrl0^(1-s)*tol_ctrl1^s
  ]
];
project_dir  := "../generated_code";
project_name := "ICLOCS_SingularArc";
#Describe(generateOCProblem);
generateOCProblem(
  project_name,
  post_processing          = POST,
  integral_post_processing = IPOST,
  parameters               = PARS,
  continuation             = CONT,
  mesh                     = MESH_DEF,
  states_guess             = GUESS,
  optimization_parameters  = PGUESS
);
# if used in batch mode use the comment to quit;
