restart:
with(XOptima):
XOptimaInfo();
EQ1    :=  diff(x(t),t) - v(t) :
EQ2    :=  diff(v(t),t) - F(t) :
EQNS_T := [ EQ||(1..2) ];
qvars := [x(t),v(t)] ;
cvars := [F(t)] ;
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions() ;
addControlBound( F, controlType="U_COS_LOGARITHMIC", maxabs=1 ) ;
setTarget( mayer = -x(zeta_f) ) ;
#setFDorder([x],"forward") ;
generateOCProblem(
  "BangBangF", clean=false,
  #parameters   = [ x_i = 0, x_f=0, v_i=0,v_f=0],
  mesh         = [length=1, n=100],
  states_guess = [ v = zeta*(1-zeta) ]
);
;
