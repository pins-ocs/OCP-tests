
# 

# 
# GTOCX model 2 burn fixed time
# Authors: E. Bertolazzi
# Date:
# 
# Load Packages
# Load maple packages
restart:
interface(rtablesize=20);
with(XOptima):
# Dynamic system: Spacecraft equations
read "gtocX_user_functions.mpl";
ode[1];
ode[2];
ode[3];
ode[4];
ode[5];
ode[6];
# List of states and controls
uvars := []:
pvars := []:
xvars := map([p,f,g,h,k,L],(zeta)):
odes  := Vector(ode):
odes;
# Optimal Contol Problem
#Describe(loadDynamicSystem);
loadDynamicSystem(
  equations  = odes,
  controls   = uvars,
  parameters = pvars,
  states     = xvars
);
DELTAX0 := subs(zeta=zeta_i,XPOS-X0);
DELTAY0 := subs(zeta=zeta_i,YPOS-Y0);
DELTAZ0 := subs(zeta=zeta_i,ZPOS-Z0);
DELTAX1 := subs(zeta=zeta_f,XPOS-X1);
DELTAY1 := subs(zeta=zeta_f,YPOS-Y1);
DELTAZ1 := subs(zeta=zeta_f,ZPOS-Z1);
addBoundaryConditions(generic=[
  [DELTAX0,"initial_x"],
  [DELTAY0,"initial_y"],
  [DELTAZ0,"initial_z"],
  [DELTAX1,"final_x"],
  [DELTAY1,"final_y"],
  [DELTAZ1,"final_z"]
]);
infoBoundaryConditions() ;
addUnilateralConstraint(
  1+f(zeta)*cos(L(zeta))+g(zeta)*sin(L(zeta)) >= 0,
  ray_positive,
  epsilon   = ray_epsi,
  tolerance = ray_tol,
  barrier   = true
);
TGUESS := (1-zeta)*time_i+zeta*time_f;
LAGRANGE := 
  (p(zeta)/p_guess(TGUESS)-1)^2 +
  (f(zeta)-f_guess(TGUESS))^2 + 
  (g(zeta)-g_guess(TGUESS))^2 +
  (h(zeta)-h_guess(TGUESS))^2 +
  (k(zeta)-k_guess(TGUESS))^2 +
  (L(zeta)-L_guess(TGUESS,time_i))^2 ;
setTarget( lagrange = (1-w_guess)*LAGRANGE ):
addUserFunction(p_guess(t),derivatives=0);
addUserFunction(f_guess(t),derivatives=0);
addUserFunction(g_guess(t),derivatives=0);
addUserFunction(h_guess(t),derivatives=0);
addUserFunction(k_guess(t),derivatives=0);
addUserFunction(L_guess(t,t0),derivatives=0);

addUserFunction(guess_setup(),derivatives=0);
GUESS := [
  p = p_guess(TGUESS),
  f = f_guess(TGUESS),
  g = g_guess(TGUESS),
  h = h_guess(TGUESS),
  k = k_guess(TGUESS),
  L = L_guess(TGUESS,time_i)
];
PGUESS := [
];
CONTINUATION := [
  [ w_guess  = s ],
  [ w_nonlin = s ]
];
TIME := (1-zeta)*time_i+zeta*time_f;
POST := [
  [TIME,                                 "time" ],
  [ray(p(zeta),f(zeta),g(zeta),L(zeta)), "ray" ],

  [XPOS,"X"],
  [YPOS,"Y"],
  [ZPOS,"Z"],

  [XVEL,"VX"],
  [YVEL,"VY"],
  [ZVEL,"VZ"],

  op(COMMON_POST)
];
PARS := [
  op(COMMON_PARS),
  retrograde = -1,
  muS        = 0.575874,
  time_i     = 0,
  time_f     = 27
];
#Describe(generateOCProblem) ;
generateOCProblem(
  "gtocX_2burn",
  parameters          = PARS,
  post_processing     = POST,
  states_guess        = GUESS,
  parameters_guess    = PGUESS,
  continuation        = CONTINUATION,
  admissible_region   = [ p(zeta) > 0 ], 
  mesh                = [length=1, n=50],
  external_frameworks = ["MechatronixAstro"],
  clean               = false
);
NULL;

