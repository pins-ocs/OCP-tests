restart:;
with(plots):
with(XOptima):
interface(rtablesize=40):;
Tdir := [cos(theta(s(t))),sin(theta(s(t)))];
Ndir := [-sin(theta(s(t))),cos(theta(s(t)))];
EQ1 := diff(s(t),t) - vs(t)/(1-n(t)*kappa(s(t))) :
EQ2 := diff(n(t),t) - vn(t) :
EQ3 := diff(vs(t),t) - (as(t)+vs(t)*vn(t)*kappa(s(t))/(1-n(t)*kappa(s(t)))) :
EQ4 := diff(vn(t),t) - (an(t)-vs(t)^2*kappa(s(t))/(1-n(t)*kappa(s(t)))) :
EQ5 := diff(as(t),t) - (js(t)+vs(t)*an(t)*kappa(s(t))/(1-n(t)*kappa(s(t)))) :
EQ6 := diff(an(t),t) - (jn(t)-vs(t)*as(t)*kappa(s(t))/(1-n(t)*kappa(s(t)))) :;
eqns_CNOC := subs([],[EQ||(1..6)]):<%> ;
xvars_CNOC := [s(t),n(t),vs(t),vn(t),as(t),an(t)] ;
uvars_CNOC := [js(t),jn(t)] ;
SS := seq( diff(xvars_CNOC[i],t)=diff(op(0,xvars_CNOC[i])(zeta),zeta)/coV(zeta),i=1..nops(xvars_CNOC)), t=zeta : <%>;
eqns_s := [seq( collect( subs( SS,eqns_CNOC[i]*coV(zeta)), coV(zeta)),
                i=1..nops(xvars_CNOC))
           ,diff(coV(zeta),zeta)
           ] : <%> ;
x_vars := [op(subs(t=zeta,xvars_CNOC)), coV(zeta)] ;
u_vars := subs(t=zeta,uvars_CNOC) ;
#Describe(loadDynamicSystem);
loadDynamicSystem(
  controls  = u_vars,
  states    = x_vars,
  equations = eqns_s
);
VX := subs(t=zeta,vs(t)*Tdir[1] + vn(t)*Ndir[1]) ;
VY := subs(t=zeta,vs(t)*Tdir[2] + vn(t)*Ndir[2]) ;
AX := subs(t=zeta,as(t)*Tdir[1] + an(t)*Ndir[1]) ;
AY := subs(t=zeta,as(t)*Tdir[2] + an(t)*Ndir[2]) ;
JX := subs(t=zeta,js(t)*Tdir[1] + jn(t)*Ndir[1]) ;
JY := subs(t=zeta,js(t)*Tdir[2] + jn(t)*Ndir[2]) ;
addBoundaryConditions(
  initial = [n,vs,vn,as,an],
  final   = [n,vs,vn,as,an],
  generic = [
    [s(zeta_i)-zeta_i,"initial_s"],
    [s(zeta_f)-zeta_f,"final_s"]
  ]
);
setStatusBoundaryConditions(generic=["initial_s"="enabled","final_s"="enabled"]);
infoBoundaryConditions();
penScale := coV(zeta);
lgr := coV(zeta)*((sqrt(vs(zeta)^2+vn(zeta)^2)-nominalFeed())/deltaFeed)^2:
myr := 0 ;
setTarget(lagrange=lgr,mayer=myr);
#Describe(addUnilateralConstraint);
addUnilateralConstraint(
  coV(zeta) > 0,
  timePositive,
  epsilon   = 0.01, 
  tolerance = 0.01,
  barrier   = true
);
addUnilateralConstraint(
  sqrt(vs(zeta)^2+vn(zeta)^2)/nominalFeed() <= 1+0.01,
  vLimit,
  subtype   = "PENALTY_PIECEWISE",
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.01
);
addBilateralConstraint(
  n(zeta)/path_following_tolerance,
  PathFollowingTolerance,
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.1
);
addBilateralConstraint(
  as(zeta)/as_max,
  as_limit,
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.01
);
addBilateralConstraint(
  an(zeta)/an_max,
  an_limit,
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.01
);
addBilateralConstraint(
  AX/ax_max,
  ax_limit,
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.01
);
addBilateralConstraint(
  AY/ay_max,
  ay_limit,
  scale     = penScale,
  epsilon   = 0.01,
  tolerance = 0.01
);
addControlBound(
  js(zeta),
  scale       = penScale,
  max         = js_max, # 30.0,
  min         = js_min, #-50.0,
  epsilon     = 0.01,
  tolerance   = 0.01,
  controlType = "U_LOGARITHMIC"
):
addControlBound(
  jn(zeta),
  scale       = penScale,
  maxabs      = jn_max, # 65,
  epsilon     = 0.01,
  tolerance   = 0.01,
  controlType = "U_LOGARITHMIC"
):;
PTS := [[0,0],[-10,0], [20,2], [50,0 ,0],[50,10,3.1415],[20,12],[-10,10],
              [-10,20],[20,22],[50,20,0],[50,30,3.1415],[20,32],[-10,30],
              [-10,40],[20,42],[50,40,0],[50,50,3.1415],[20,52],[-10,50],
              [-10,60],[20,62],[50,60]] ;
path       := []:
totlen     := 0:
scale_path := 1/1000.0:
for i from 2 to 21 do
  tmp := ["x0"           = PTS[i][1]*scale_path,
          "y0"           = PTS[i][2]*scale_path,
          "x1"           = PTS[i+1][1]*scale_path,
          "y1"           = PTS[i+1][2]*scale_path,
          "feedRate"     = v_nom,
          "spindleRate"  = 3000,
          "crossSection" = 1,
          "tolerance"    = path_following_tolerance,
          "n"            = mesh_segments]:
  SS  := [x0=PTS[i][1]*scale_path,   y0=PTS[i][2]*scale_path,
          x1=PTS[i+1][1]*scale_path, y1=PTS[i+1][2]*scale_path]:
  if nops(PTS[i]) = 3 and nops(PTS[i+1]) = 3 then
    totlen := totlen + subs( SS, evalf((Pi/2)*sqrt((x1-x0)^2+(y1-y0)^2),50) ) ;
    tmp := [op(tmp),"angle0"=PTS[i][3],"angle1"=PTS[i+1][3]];
  else
    totlen := totlen + subs( SS, evalf(sqrt((x1-x0)^2+(y1-y0)^2),50) ) ;
    tmp := [op(tmp)];
  end ;
  path := [op(path),tmp]:
end:;
totlen; # lunghezza totale;
qvars := [
  lenSeg()                   = ssLength(),
  kappa(zeta)                = curvature(zeta),
  theta(zeta)                = angle(zeta),
  xPath(zeta)                = x(zeta),
  yPath(zeta)                = y(zeta),
  xTraj(zeta,tt)             = x_ISO(zeta,tt),
  yTraj(zeta,tt)             = y_ISO(zeta,tt),
  xLimitLeft(zeta,pf_error)  = x_ISO(zeta,pf_error),
  yLimitLeft(zeta,pf_error)  = y_ISO(zeta,pf_error),
  xLimitRight(zeta,pf_error) = x_ISO(zeta,pf_error),
  yLimitRight(zeta,pf_error) = y_ISO(zeta,pf_error),
  nominalFeed()              = feedReferenceRate()
]:;
mapUserFunctionToObject(
  qvars,
  "*pToolPath2D",
  "Mechatronix#ToolPath2D",
  ["segments"=path]
);
#infoRegisteredObjects();
DX := subs(theta(s(t))=theta_L(zeta_L),SL*Tdir[1] + NL*Ndir[1]) ;
DY := subs(theta(s(t))=theta_L(zeta_L),SL*Tdir[2] + NL*Ndir[2]) ;
EQJUMP1 := SR=combine(collect(subs(theta(s(t))=theta_R(zeta_R),
                      DX*Tdir[1]+DY*Tdir[2]),{SL,NL})) ;
EQJUMP2 := NR=combine(collect(subs(theta(s(t))=theta_R(zeta_R),
                      DX*Ndir[1]+DY*Ndir[2]),{SL,NL})) ;
jump_VEL := subs(SR=vs(zeta_R),NR=vn(zeta_R),
                 SL=vs(zeta_L),NL=vn(zeta_L),
                 [EQJUMP1,EQJUMP2]) ;
jump_ACC := subs(SR=as(zeta_R),NR=an(zeta_R),
                 SL=as(zeta_L),NL=an(zeta_L),
                 [EQJUMP1,EQJUMP2]) ;
#Describe(setJumpConditionFreeLeft);
#Describe(setJumpConditionAlgebraic) ;
jump_VEL;
setInterfaceConditionFree(coV);
setInterfaceConditionFixed(s,s(zeta_L)-zeta_L,s(zeta_R)-zeta_R);
setInterfaceConditionFixed(n,n(zeta_L)-0,n(zeta_R)-0);
setInterfaceConditionAlgebraic(jump_VEL);
setInterfaceConditionAlgebraic(jump_ACC);
Describe(setFDorder);
#setFDorderEquations([5,6],"backward"):
#setFDorderCoEquation([as,an],"forward"):;
guess_list := [
  s   = zeta,
  n   = 0,
  vs  = nominalFeed(),
  vn  = 0,
  as  = 0,
  an  = 0,
  coV = 1/nominalFeed()
];
dataOCP := [
  as_max    = 2.1,   # m/s^2 
  an_max    = 1.2,   # m/s^2
  ax_max    = 2.1,   # m/s^2 
  ay_max    = 2.1,   # m/s^2
  v_nom     = 0.173, # m/s
  deltaFeed = v_nom,
  n_i       = 0,
  vs_i      = 0,
  vn_i      = 0,
  as_i      = 0,
  an_i      = 0,
  n_f       = 0,
  vs_f      = 0,
  vn_f      = 0,
  as_f      = 0,
  an_f      = 0,
  js_min    = -50,
  js_max    = 30,
  jn_max    = 65,
  mesh_segments            = 100,
  path_following_tolerance = 10e-6,
  pf_error                 = path_following_tolerance
];
post_int_list := [ [coV(zeta),"time"] ] ;
post_list := [
  [sqrt(vs(zeta)^2+vn(zeta)^2),"feed"],
  [sqrt(as(zeta)^2+an(zeta)^2),"acc"],
  [sqrt(js(zeta)^2+jn(zeta)^2),"jerk"],
  [VX, "vx"], [VY, "vy"],
  [AX, "ax"], [AY, "ay"],
  [JX, "jx"], [JY, "jy"],
  #[VX*60000,              "vx_mm_min"],
  #[VY*60000,              "vy_mm_min"],
  #[AX/ax_max,             "ax_normalized"],
  #[AY/ay_max,             "ay_normalized"],
  #[xPath(s(zeta))*1000,   "X-path [mm]"],
  #[yPath(s(zeta))*1000,   "Y-path [mm]"],
  [xPath(s(zeta)),         "X-path"],
  [yPath(s(zeta)),         "Y-path"],
  [xTraj(s(zeta),n(zeta)), "X-traj"],
  [yTraj(s(zeta),n(zeta)), "Y-traj"],
  [xLimitLeft(s(zeta),pf_error),  "X-left"],
  [yLimitLeft(s(zeta),pf_error),  "Y-left"],
  [xLimitRight(s(zeta),pf_error), "X-right"],
  [yLimitRight(s(zeta),pf_error), "Y-right"]
];
#Describe(generateOCProblem):;
generateOCProblem(
  "CNOC", 
  integral_post_processing  = post_int_list,
  post_processing           = post_list,
  parameters                = dataOCP,
  #controls_guess           = [js=0,jn=0],
  states_guess              = guess_list,
  clean                     = false
);
;
