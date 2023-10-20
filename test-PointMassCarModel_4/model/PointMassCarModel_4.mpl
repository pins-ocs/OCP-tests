restart:
with(plots):
with(XOptima):;
read("point_mass_model.mpl"):;
zvars  := subs(t=zeta, tvars):
zuvars := subs(t=zeta, uvars):
<zuvars>, <zvars>;
tToT := seq(
  diff(tvars[i],t) = subs(t=zeta, diff(tvars[i],t))/exp(log_inv_Vseg(zeta)),
  i=1..nops(tvars)
), t=zeta;
addUserFunction(zeta__dot(V,alpha,n,Kappa)=V*cos(alpha)/(1-Kappa*n));
ZDOT := zeta__dot(V(zeta),alpha(zeta),n(zeta),Kappa(s(zeta)));
eqns_t;
eqns_t[1] := diff(s(t),t) = zeta__dot(V(t),alpha(t),n(t),Kappa(s(t)));
zeqns := subs(tToT, eqns_t):
zeqns := simplify(simplify(zeqns,trig),size):
zeqns := simplify(zeqns);
zeqns := [op(simplify(op(solve( zeqns, diff(zvars,zeta) )))),
         diff(log_inv_Vseg(zeta),zeta)=0]:
<zeqns>;
zvars := [op(subs(t=zeta, tvars)),log_inv_Vseg(zeta)];
read("roads.mpl"):;
qvars := [
  L()              = ssLength(),
  ssSegmentMin()   = ssSegmentMin(),
  ssSegmentMax()   = ssSegmentMax()
]:
qextra := [
  Kappa(zeta)        = isoCurvature(zeta),
  xV(zeta,n)         = isoX(zeta,n),
  yV(zeta,n)         = isoY(zeta,n),
  leftWidth(zeta)    = leftWidth(zeta),
  rightWidth(zeta)   = rightWidth(zeta),
  xLane(zeta)        = isoX(zeta), 
  yLane(zeta)        = isoY(zeta),
  theta(zeta)        = isoAngle(zeta),
  xL(zeta)           = isoLeftX(zeta),
  yL(zeta)           = isoLeftY(zeta),
  xR(zeta)           = isoRightX(zeta),
  yR(zeta)           = isoRightY(zeta)
]:;
mapUserFunctionToObject(
  [op(qvars),op(qextra)],
  "*pRoad",             # istanza class tipo pointer
  "Mechatronix#Road2D", # classe (deve essere registrata)
  road_data_init
);
ALIASES := [];#  [ D(leftWidth)=leftWidth_D, D(rightWidth)=rightWidth_D];
loadDynamicSystem(
  states        = zvars,
  controls      = zuvars,
  equations     = zeqns,
  meshFunctions = map(lhs,qvars)
);
#Describe(addBoundaryConditions);
if true  then # CYCLIC ----
  addBoundaryConditions(
    #initial = [V=V0,s=ssSegmentMin_L()],
    #final   = [s=ssSegmentMax_R()],
    initial = [V=V0,s=zeta_L],
    final   = [s=zeta_R],
    cyclic  = [ n, alpha, V, fx, Omega ]
  );
  Mayer_cyclic := 0:
else           # MAYER CYCLIC ----
  init_bcs := [
    n     = 0,
    alpha = 0,
    V     = V0,
    fx    = 0,
    Omega = 0
  ]:
  addBoundaryConditions(
    initial = [V=V0], init_bcs,
    final   = [],  #fin_bcs,
    cyclic  = []
  );

  Mayer_cyclic := ( (n(zeta_i) - n(zeta_f))/0.1 )^2
                + ( (alpha(zeta_i) - alpha(zeta_f))/0.02 )^2
                + ( (V(zeta_i) - V(zeta_f) )/30 )^2
                + ( (fx(zeta_i) - fx(zeta_f))/1 )^2
                + ( (Omega(zeta_i) - Omega(zeta_f))/0.1 )^2;
end:;
setInterfaceConditionFixed(
  s,
  s(zeta_L)-zeta_L, #ssSegmentMax_L(),
  s(zeta_R)-zeta_R  #ssSegmentMin_R()
);
setInterfaceConditionFree( log_inv_Vseg );
SCALE := exp(log_inv_Vseg(zeta));
setTarget(
  lagrange = wT * SCALE,
  mayer    = wMC*Mayer_cyclic
);
penalties_opts      := scale = SCALE, epsilon = p_epsi0,  tolerance = p_tol0;
road_penalties_opts := scale = SCALE, epsilon = p_epsi0,  tolerance = road_tol0;
u_penalties_opts    := scale = SCALE, epsilon = up_epsi0, tolerance = up_tol0;
MU_X :=  subs(t=zeta, fx(t)/(mu__x__max*g) );
MU_Y :=  subs(t=zeta, fy/(mu__y__max*g) );
ellipse := (MU_X)^2 + (MU_Y)^2;
addUnilateralConstraint(
  ellipse< 1,
  AdherenceEllipse,
  penalties_opts
);
addUnilateralConstraint(
  n(zeta) < leftWidth(s(zeta)),
  RoadLeftBorder,
  road_penalties_opts
);
addUnilateralConstraint(
  -n(zeta) < rightWidth(s(zeta)),
  RoadRightBorder,
  road_penalties_opts
);
power := V(zeta)*fx(zeta)*m;
addUnilateralConstraint(
  power/Pmax < 1,
  PowerLimit,
  penalties_opts
);
#addUnilateralConstraint(
#  zeta__dot(V(zeta),alpha(zeta),n(zeta),Kappa(s(zeta)))>0,
#  Spos,
#  penalties_opts
#);
addControlBound(
  v__fx(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -1,
  max         = 1,
  u_penalties_opts
);
addControlBound(
  v__Omega(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -1,
  max         = 1,
  u_penalties_opts
);
out_vars := [
  [exp(log_inv_Vseg(zeta)), ["dtdzeta","t"] ],
  [Kappa(s(zeta)),      "Kappa"],
  [leftWidth(s(zeta)),  "leftWidth"],
  [rightWidth(s(zeta)), "rightWidth"],
  [xLane(s(zeta)),      "xLane"],
  [yLane(s(zeta)),      "yLane"],
  [theta(s(zeta)),      "theta"],
  [xV(s(zeta),n(zeta)), "xV"],
  [yV(s(zeta),n(zeta)), "yV"],
  [xL(s(zeta)),         "xL"],
  [yL(s(zeta)),         "yL"],
  [xR(s(zeta)),         "xR"],
  [yR(s(zeta)),         "yR"],
  [subs(t=zeta,fy),     "fy"],
  [MU_X,                "mu_x"],
  [MU_Y,                "mu_y"],
  [exp(log_inv_Vseg(zeta)),   "Vseg"],
  [L()*exp(-log_inv_Vseg(zeta)), "Tseg"],
  [ZDOT,                      "zeta_dot_eq"]
]:
<%>;
other_params := [
  wT0       = 0.01,
  wT1       = 1.0,
  wT        = wT0, # Lagrange target weight
    wMC       = 1,
  V0        = 0,
  Vguess    = 10,
  p_epsi0   = 0.1, 
  p_tol0    = 0.1,
  up_epsi0  = 0.1,
  p_epsi1   = 1e-3, 
  up_epsi1  = 1e-2,
  up_tol0   = 1e-2,
  road_tol0 = 0.01
]: <%>;
admissible_region_expr := []:
states_guess_expr := [
  V            = Vguess,
  Omega        = Vguess/R0,
  log_inv_Vseg = log(1/Vguess),
  s            = zeta
]:;
continuation_param := [ 
  [ wT = wT0 + s*(wT1-wT0)],
  [ 
   ["AdherenceEllipse","epsilon"] = p_epsi0  + s * (p_epsi1 - p_epsi0),
   ["RoadRightBorder","epsilon"]  = p_epsi0  + s * (p_epsi1 - p_epsi0),
   ["RoadLeftBorder","epsilon"]   = p_epsi0  + s * (p_epsi1 - p_epsi0),
   ["PowerLimit","epsilon"]       = p_epsi0  + s * (p_epsi1 - p_epsi0),
   ["v__fx","epsilon"]            = up_epsi0 + s * (up_epsi1 - up_epsi0),
   ["v__Omega","epsilon"]         = up_epsi0 + s * (up_epsi1 - up_epsi0)
  ]
];
project_name := "PointMassCarModel_4";
generateOCProblem( clean=false,
  project_name, 
  parameters               = [ op(point_mass_data), op(other_params) ],
  standard_post_processing = true,
  post_processing          = out_vars,
  continuation             = continuation_param,
  states_guess             = states_guess_expr,
  admissible_region        = admissible_region_expr,
  aliases                  = ALIASES
  #controls_guess         = controls_guess_expression,
  #mesh = [[length = 1, n = Num_mesh_points]],
  #excluded = [ "Main.cc", "Data.lua", "run_ffi.rb"]#, "run.rb"]#, "Data.rb" ]
);
;
