
# 
#            
# Modello Massa
# 
# 2 controllo ridondanti
# (Problema tempo fisso, massima distanza)
# Inizializzazione
restart:
with(XOptima):
XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) - v(t) :
EQ2    :=  diff(v(t),t) - F1(t) - F2(t) :
EQ3    :=  diff(F1(t),t) - vF1(t) :
EQ4    :=  diff(F2(t),t) - vF2(t) :
EQ5    :=  diff(vF1(t),t) - aF1(t) :
EQ6    :=  diff(vF2(t),t) - aF2(t) :
EQNS_T := [ EQ||(1..6) ];
# Variabili del problema e controlli
# Variabili
qvars := [x(t),v(t),F1(t),F2(t),vF1(t),vF2(t)] ;
# Controlli
cvars := [aF1(t), aF2(t)] ;
# Equazioni del modello matematico del carrello
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions() ;
# Penalty
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
ocp["optimal_controls_equations"];
ocp["dynamics_system_equations"];
ocp["adjoint_equations"];
ocp["mayer_target"];

