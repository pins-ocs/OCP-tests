restart:
with(XOptima):
#with(XOptimaPlots):
#with(plots):
#with(Optimization):;
#addUserFunction(ax(u)=(a_max+a_min)/2+(a_max-a_min)*arctan(u/epsilon)/Pi);
#addUserFunction(P(u)=epsilon*log(1+u^2/epsilon^2));
#addUserFunction(P(u)=u^2/epsilon);
eqn1 := diff(v(s),s) = a(s)/v(s)-c0-c1*v(s):;
eqns := [eqn1]: <%>;
xvars := map([v],(s));
uvars := map([a],(s));
loadDynamicSystem(
  equations = eqns,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [ v=v0 ], 
  final   = [ v=v1 ]
):;
setTarget(
  lagrange = wT/v(zeta)+epsilon*a(zeta)^2,
  mayer    = 0
);
#addControlBound(
#  a(zeta),
#  controlType = "U_COS_LOGARITHMIC",
#  epsilon     = a_epsi,
#  tolerance   = a_tol,
#  min         = a_min, 
#  max         = a_max
#):;
addBilateralConstraint(
  v(zeta),
  LimitV,
  min       = v_min,
  max       = v_max,
  epsilon   = v_epsi,
  tolerance = v_tol,
  subtype   = "BARRIER_LOG0",
  barrier   = true
):;
addBilateralConstraint(
  a(zeta),
  LimitA,
  min       = a_min,
  max       = a_max,
  epsilon   = a_epsi,
  tolerance = a_tol,
  subtype   = "BARRIER_LOG0",
  barrier   = true
):;
ELL2 := WA*a(zeta)^2+(kappa(zeta)*v(zeta)^2)^2;
addUnilateralConstraint(
  ELL2/E_max^2 <= 1,
  LimitE,
  epsilon   = E_epsi,
  tolerance = E_tol,
  subtype   = "BARRIER_LOG0",
  barrier   = true
):;
PARS := [

  v0       = 1,
  v1       = 1,

  v_epsi   = 0.01,
  v_tol    = 0.01,


  a_epsi   = 0.01,
  a_tol    = 0.01,

  v_max    = 50,
  v_min    = 0.5,

  a_max    = 5,
  a_min    = -5,


  c0_0     = 0, c0_1 = 0,     c0 = c0_0,
  c1_0     = 0, c1_1 = 0.005, c1 = c1_0,


  wT       = 1,
  WA       = 0,

  E_max    = 5,

  epsilon0 = 0.1,
  epsilon1 = 1e-5,
  epsilon  = epsilon0,

  #E_max0  = 1000, E_max1  = 15,   E_max  = E_max0,
  E_epsi0 = 0.25, E_epsi1 = 0.02, E_epsi = E_epsi0,

  E_tol0  = 0.25, E_tol1  = 0.02, E_tol  = E_tol0
]:;
POST := [
  [ kappa(zeta),           "curvature"   ],
  [ xLane(zeta),           "xTrajectory" ], 
  [ yLane(zeta),           "yTrajectory" ],
  [ theta(zeta),           "heading"     ],
  [ a(zeta)-c0*v(zeta)
           -c1*v(zeta)^2,  "ax"          ],
  [ kappa(zeta)*v(zeta)^2, "ay"          ],
  [ sqrt(ELL2),            "ELL"         ],
  [ E_max,                 "E_max"       ],
  [ 1/v(zeta),             ["dtime_dzeta", "time"] ]
];
CONT := [
  [
    c0 = c0_0*(1-s)+c0_1*s,
    c1 = c1_0*(1-s)+c1_1*s
  ],
  #[
  #  WE = WE0*(1-s)+WE1*s
  #],
  [
    ["LimitE","epsilon"]   = E_epsi0*(1-s)+E_epsi1*s,
    ["LimitE","tolerance"] = E_tol0*(1-s)+E_tol1*s
  ],
  [
    epsilon = epsilon0*(1-s)+epsilon1*s
  ]
];
GUESS  := [ v = v0+zeta*(v1-v0) ]:;
UGUESS := [ a = 0 ]:;
REGION := [
  [ ELL2 < E_max^2, "u" ]
];
MESH_DEF := [[length=10,n=400]];
qvars := [
  kappa(zeta) = curvature(zeta),
  xLane(zeta) = xTrajectory(zeta), 
  yLane(zeta) = yTrajectory(zeta),
  theta(zeta) = heading(zeta)
]:;
mapUserFunctionToObject(
  qvars,
  "*pTrajectory",       # istanza class tipo pointer
  "Mechatronix#Path2D", # classe (deve essere registrata)
  "../../model/trajectory_data.rb"
);
project_dir  := "../generated_code";
project_name := "ForwardBackward";
generateOCProblem(
  project_name,
  post_processing          = POST,
  parameters               = PARS,
  #optimization_parameters  = [ E_max = 1000 ],
  continuation             = CONT,
  admissible_region        = REGION,
  #mesh                    = MESH_DEF,
  states_guess             = GUESS,
  controls_guess           = UGUESS
);
# if used in batch mode use the comment to quit;
