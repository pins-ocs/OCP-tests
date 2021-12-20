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
addUserFunction( g2(x1,x2)=1+0.2*(x1+x2) );
addUserFunction( g3(x1,x2)=g2(x1,x2)^2+232+46.4*x2 );
addUserFunction( g4(x1,x2)=g2(x1,x2)^2+232+46.4*x1 );
addUserFunction( g1(x1,x2)=g2(x1,x2)^2/(g3(x1,x2)*g4(x1,x2)-2152.96*x1*x2));
EQ1 := diff(x1(t),t) = T*( g1(x1(t),x2(t))*(g4(x1(t),x2(t))*(0.02-x1(t))+46.4*x1(t)*(u(t)-2*x2(t))) );
EQ2 := diff(x2(t),t) = T*( g1(x1(t),x2(t))*(g3(x1(t),x2(t))*(u(t)-2*x2(t))+46.4*(0.02-x1(t))) );
xvars := map([x1,x2],(t));
uvars := [u(t)];
loadDynamicSystem(
  equations = [EQ1,EQ2],
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [x1 = 0.02, x2 = 0],
  final   = [x1 = 0.02, x2 = 2]
);
infoBoundaryConditions();
setTarget(
  mayer    = T,
  lagrange = 0
);
addControlBound(u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 8,
  epsilon     = pen_u_epsi0,
  tolerance   = pen_u_tol0,
  scale       = T
);
#addUserFunction();
#addUserFunction();
PARS := [
  TF          = 300,
  pen_u_epsi0 = 0.1,
  pen_u_tol0  = 0.1,
  pen_u_epsi1 = 1e-8,
  pen_u_tol1  = 1e-8
];
OPT_PARS := [T = 300];
POST := [[zeta*T, "time"]];
GUESS := [ x1 = 0.02, x2 = 2*zeta ];
MESHP_DEF := [length=1, n=200];
CONT := [
  [
    ["u","epsilon"]   = pen_u_epsi0*(1-s)+s*pen_u_epsi1,
    ["u","tolerance"] = pen_u_tol0*(1-s)+s*pen_u_tol1
  ]
];
project_dir  := "../generated_code";
project_name := "LUUS_DrugDisplacement";
#Describe(generateOCProblem);
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  optimization_parameters = OPT_PARS,
  continuation            = CONT,
  mesh                    = MESHP_DEF,
  states_guess            = GUESS
);
# if used in batch mode use the comment to quit;
