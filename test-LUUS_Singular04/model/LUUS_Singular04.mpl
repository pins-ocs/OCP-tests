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
EQ1    :=  diff(x1(t),t) = x2(t):
EQ2    :=  diff(x2(t),t) = x3(t) :
EQ3    :=  diff(x3(t),t) = u(t):
EQNS_T := [ EQ1, EQ2, EQ3 ] : <%>;
xvars := map([x1,x2,x3],(t));
uvars := [u(t)];
loadDynamicSystem(
  equations = [EQ1,EQ2,EQ3],
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[x1,x2,x3]);
infoBoundaryConditions();
setTarget( lagrange = x1(zeta)^2 );
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsilon0,
  tolerance   = u_tolerance0,
  scale       = x1(zeta)^2+epsi_x^2
);
#addUserFunction();
#addUserFunction();
PARS := [
  u_epsilon0   = 0.01,
  u_tolerance0 = 0.01,
  u_epsilon1   = 1e-6,
  u_tolerance1 = 1e-6,
  epsi_x0      = 1e-2,
  epsi_x1      = 1e-6,
  epsi_x       = epsi_x0,
  x1_i         = 1,
  x2_i         = 0,
  x3_i         = 0,
  Tf           = 6
];
OPT_PARS := [];
POST := [ [x1(zeta)^2,"Target"] ];
GUESS := [ x1=x1_i, x2=x2_i, x3=x3_i ];
MESH_DEF := [ length=Tf, n=1000 ];
CONT := [
  [
    ["u","epsilon"]   = u_epsilon0*(1-s)+s*u_epsilon1,
    ["u","tolerance"] = u_tolerance0*(1-s)+s*u_tolerance1,
    epsi_x            = epsi_x0*(1-s)+s*epsi_x1
  ]
];
project_dir  := "../generated_code";
project_name := "LUUS_Singular04";
#Describe(generateOCProblem);
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
