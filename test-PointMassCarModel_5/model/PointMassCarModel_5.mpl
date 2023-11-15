restart:
with(plots):
with(XOptima):;
read("point_mass_model.mpl"):;
zvars  := subs(t=zeta, tvars):
zuvars := subs(t=zeta, uvars):
<zuvars>, <zvars>;
tToZeta := seq(
  diff(tvars[i],t) = subs(t=zeta, diff(tvars[i],t))/inv_zeta__dot(zeta),
  i=1..nops(tvars)
), s(t) = zeta, s(zeta) = zeta, t=zeta;
zeqns    := subs(tToZeta, eqns_t):
eqn_zeta := simplify(op(solve( zeqns[1], {inv_zeta__dot(zeta)} )));
zeqns    := simplify(simplify(zeqns,trig),size):
zeqns    := simplify(op(solve( zeqns[2..-1], diff(zvars[2..-1],zeta) ))):
<zeqns>;
eqn_zeta_def  := subs(Kappa(zeta)=Kappa,subs( map(x->x=op(0,x),zvars), rhs(eqn_zeta)));
#eqn_zeta_def := subs(V=sqrt(V_epsilon^2+V^2),eqn_zeta_def);
addUserFunction(inv_zeta__dot(V,alpha,n,Kappa)=eqn_zeta_def);
INVZDOT := inv_zeta__dot(V(zeta),alpha(zeta),n(zeta),Kappa(zeta));
ZDOT    := 1/INVZDOT;
zeqns := subs( inv_zeta__dot(zeta)=INVZDOT, zeqns ): <%>;
read("roads.mpl"):;
qvars := [
  Kappa(zeta)      = isoCurvature(zeta),
  leftWidth(zeta)  = leftWidth(zeta),
  rightWidth(zeta) = rightWidth(zeta),
  xLane(zeta)      = isoX(zeta), 
  yLane(zeta)      = isoY(zeta),
  theta(zeta)      = isoAngle(zeta),
  xL(zeta)         = isoLeftX(zeta),
  yL(zeta)         = isoLeftY(zeta),
  xR(zeta)         = isoRightX(zeta),
  yR(zeta)         = isoRightY(zeta)
]:
qextra := [
  xV(zeta,n) = isoX(zeta,n),
  yV(zeta,n) = isoY(zeta,n)
]:;
mapUserFunctionToObject(
  [op(qvars),op(qextra)],
  "*pRoad",             # istanza class tipo pointer
  "Mechatronix#Road2D", # classe (deve essere registrata)
  road_data_init
);
loadDynamicSystem(
  states        = zvars[2..-1],
  controls      = zuvars,
  equations     = zeqns,
  meshFunctions = map(lhs,qvars)
);
#Describe(addBoundaryConditions);
if true  then # CYCLIC ----
  addBoundaryConditions(
    initial = [V=V0],
    final   = [],
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
setTarget(
  lagrange = wT * INVZDOT,
  mayer    = wMC*Mayer_cyclic
);
penalties_opts      := scale = INVZDOT, epsilon = p_epsi0,  tolerance = p_tol0;
road_penalties_opts := scale = INVZDOT, epsilon = p_epsi0,  tolerance = road_tol0;
u_penalties_opts    := scale = INVZDOT, epsilon = up_epsi0, tolerance = up_tol0;
MU_X :=  subs(t=zeta, fx(t)/(mu__x__max*g) );
MU_Y :=  subs(t=zeta, fy/(mu__y__max*g) );
ellipse := (MU_X)^2 + (MU_Y)^2;
addUnilateralConstraint(
  ellipse< 1,
  AdherenceEllipse,
  penalties_opts
);
addUnilateralConstraint(
  n(zeta) < leftWidth(zeta),
  RoadLeftBorder,
  road_penalties_opts
);
addUnilateralConstraint(
  -n(zeta) < rightWidth(zeta),
  RoadRightBorder,
  road_penalties_opts
);
power := V(zeta)*fx(zeta)*m;
addUnilateralConstraint(
  power/Pmax < 1,
  PowerLimit,
  penalties_opts
);
addUnilateralConstraint(
  V(zeta) > 0,
  LimitMinSpeed,
  penalties_opts
);
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
  [INVZDOT, ["dtdzeta","t"]],
  [xV(zeta,n(zeta)), "xV"],              
  [yV(zeta,n(zeta)), "yV"],
  [subs(t=zeta,fy),  "fy"],
  [MU_X,             "mu_x"],
  [MU_Y,             "mu_y"],
  [INVZDOT,          "inv_zeta_dot"],
  [1/INVZDOT,        "zeta_dot_eq"]
]:
<%>;
other_params := [
  wT0       = 0.01,
  wT1       = 1.0,
  wT        = wT0, # Lagrange target weight
     wMC       = 1,
  V0        = 5,#10 ,
  p_epsi0   = 0.1, 
  p_tol0    = 0.1,
  up_epsi0  = 0.1,
  p_epsi1   = 1e-3, 
  up_epsi1  = 1e-2,
  up_tol0   = 1e-2,
  road_tol0 = 0.01,
  V_epsilon = 0.01
]: <%>;
admissible_region_expr := [ V(zeta) > 0 ]:
states_guess_expr      := [ V = V0 , Omega = V0/R0]:;
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
project_name := "PointMassCarModel_1";
generateOCProblem(
  project_name, 
  parameters        = [ op(point_mass_data), op(other_params) ] ,
  post_processing   = out_vars,
  continuation      = continuation_param,
  states_guess      = states_guess_expr,
  admissible_region = admissible_region_expr
);
;
