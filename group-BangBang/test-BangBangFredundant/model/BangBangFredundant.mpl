
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
restart:
with(XOptima):
XOptimaInfo() ;
# Equations of motion
EQ1    :=  diff(x(t),t) - v(t) :
EQ2    :=  diff(v(t),t) - F1(t) - F2(t) :
EQ3    :=  diff(F1(t),t) - vF1(t) :
EQ4    :=  diff(F2(t),t) - vF2(t) :
EQ5    :=  diff(vF1(t),t) - aF1(t) :
EQ6    :=  diff(vF2(t),t) - aF2(t) :
EQNS_T := [ EQ||(1..6) ];
# States and Constrols
# States
qvars := [x(t),v(t),F1(t),F2(t),vF1(t),vF2(t)] ;
# Controls
cvars := [aF1(t), aF2(t)] ;
# Optimal control problem formulation
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Boundary conditions
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions() ;
addControlBound( aF1, controlType="U_COS_LOGARITHMIC", maxabs=maxAF ) ;
addControlBound( aF2, controlType="U_COS_LOGARITHMIC", maxabs=maxAF ) ;
addBilateralConstraint(F1(zeta)+F2(zeta),Flim,scale=w_F);#,barrier=true,subtype="BARRIER_LOG");
setTarget( mayer = -x(zeta_f)+Flim(F1(zeta_i)+F2(zeta_i))+
                              Flim(F1(zeta_f)+F2(zeta_f)) ) ;
#setFDorder([x],"forward") ;
#Describe(generateOCProblem) ;
generateOCProblem( "BangBangFredundant",
                   standard_post_processing = true,
                   post_processing = [ [F1(zeta)+F2(zeta),"F1+F2"]],
                   parameters   = [ maxAF=10,w_F=10],
                   mesh         = [ length=1, n=100],
                   states_guess = [ v = zeta*(1-zeta) ] ) ;
ocp := getOCProblem();
indices(ocp,'nolist');
#eval(ocp["ode"]);
#eval(ocp["adjoint_ode"]);
#eval(ocp["target"]);

