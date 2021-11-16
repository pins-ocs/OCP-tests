restart:;
with(XOptima):;
TT := T(zeta) ;
EQ1 := diff(x1(zeta),zeta) = y1(zeta)*TT :
EQ2 := diff(y1(zeta),zeta) = u(zeta)*Q(x1(zeta),x2(zeta))*TT:
EQ3 := diff(x2(zeta),zeta) = y2(zeta)*TT :
EQ4 := diff(y2(zeta),zeta) = (1-u(zeta))*Q(x1(zeta),x2(zeta))*TT:
EQ5 := diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ||(1..5) ] : <%> ;
qvars := [x1(zeta),x2(zeta),y1(zeta),y2(zeta),T(zeta)] ;
cvars := [u(zeta)] ;
#infoRegisteredObjects();
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addUserFunction( Q(x,y)=x*y ) ;
addBoundaryConditions(
  initial=[x1,x2,y1,y2],
  generic=[ [x1(zeta_f)=x2(zeta_f),"FinalX"],
            [y1(zeta_f)=Yc,"FinalY1"],
            [y2(zeta_f)=Yc,"FinalY2"] ]
);
setStatusBoundaryConditions(
  generic=["FinalX","FinalY1","FinalY2"]
);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  min         = 0,
  max         = 1,
  epsilon     = 1e-2,
  tolerance   = 0.01,
  scale       = T(zeta)
);
addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T(zeta_f) ) ;
POST := [
  [lambda4__xo(zeta)-lambda2__xo(zeta),"switching"]
];
PARS := [
  epsi_max = 0.01,
  epsi_min = 1e-9,
  x1_i     = 1,
  x2_i     = 2,
  y1_i     = 1,
  y2_i     = 2,
  Yc       = 10,
  T_guess  = 1
];
CONT := [
  [ [u,"epsilon"] = explog(epsi_max,epsi_min,s) ]
];
addUserFunction( explog(a,b,s)=exp(log(a)*(1-s)+log(b)*s) );
generateOCProblem(
  "EconomicGrowthModel2",
  post_processing     = POST,
  parameters          = PARS,
  continuation        = CONT,
  mesh                = [length=1, n=5000],
  controls_guess      = [u = 0.1],
  controls_iterative  = false,
  states_guess        = [ T=T_guess, x1=x1_i, x2=x2_i, y1=y1_i, y2=y2_i ]
);
#Describe(generateOCProblem);
;
