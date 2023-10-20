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
EQNS_T := [ EQ||(1..3)]: <%>;
xvars := map([x1,x2,x3],(t));
uvars := [u(t)];
loadDynamicSystem(
  equations = [EQ1,EQ2,EQ3],
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial=[x1,x2,x3],
  final=[x2,x3]
);
infoBoundaryConditions();
setTarget(
  mayer    = T,
  lagrange = T*WG*( (x1(zeta)-guess_x1(zeta))^2+
                    (x2(zeta)-guess_x2(zeta))^2+
                    (x3(zeta)-guess_x3(zeta))^2 )
);
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = -2,
  max         = 2,
  epsilon     = u_epsi_max,
  tolerance   = u_tol_max,
  scale       = 1
);
addUnilateralConstraint(
  T>0,
  Tbound,
  epsilon   = T_epsi_max,
  tolerance = T_tol_max,
  barrier   = true
);
addUserFunction( guess_x1(s) = x1_i*(1-s)        );
addUserFunction( guess_x2(s) = x2_i*(1-s)+x2_f*s );
addUserFunction( guess_x3(s) = x3_i*(1-s)+x3_f*s );
PARS :=  [
  u_epsi_max = 0.01, u_epsi_min = 1e-4,
  u_tol_max  = 0.01, u_tol_min  = 1e-4,
  T_epsi_max = 0.01, T_epsi_min = 1e-4,
  T_tol_max  = 0.01, T_tol_min  = 1e-4,


  x1_i = Pi/2,
  x2_i = 4,
  x3_i = 0,


  x2_f = 0,
  x3_f = 0,


  T_init = 100,
  WG0    = 1,
  WG     = WG0
];
OPT_PARS := [];
POST := [
  [ zeta*T,                "time"   ],
  [ x1(zeta)^2+x2(zeta)^2, "Target" ]
];
GUESS := [
  x1 = guess_x1(zeta),
  x2 = guess_x2(zeta),
  x3 = guess_x3(zeta)
];
PGUESS := [
  T = T_init
];
MESH_DEF := [length=1,n=400];
CONT := [
  [ WG = WG0*(1-s) ],
  [ 
    ["u","epsilon"]        = u_epsi_max^(1-s)*u_epsi_min^s,
    ["u","tolerance"]      = u_tol_max^(1-s)*u_tol_min^s,
    ["Tbound","epsilon"]   = T_epsi_max^(1-s)*T_epsi_min^s,
    ["Tbound","tolerance"] = T_tol_max^(1-s)*T_tol_min^s
  ]
];
project_dir  := "../generated_code";
project_name := "ICLOCS_SingularArc";
#Describe(generateOCProblem);
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  continuation            = CONT,
  mesh                    = MESH_DEF,
  states_guess            = GUESS,
  optimization_parameters = PGUESS
);
# if used in batch mode use the comment to quit;
