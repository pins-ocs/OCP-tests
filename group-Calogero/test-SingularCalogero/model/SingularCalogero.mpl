# 
#            
# Controllo Singolare
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) = u(t) :
EQNS_T := [ EQ1 ];
# Variabili del problema e controlli
# Variabili
qvars := [x(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
#addBoundaryConditions(initial=[x,v],final=[v]);
#setBCActivationStatus(initial=[x,v],final=[v]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
# Penalty
addControlBound( u, controlType="U_COS_LOGARITHMIC", maxabs=1 ) ;
setTarget( lagrange = (x(zeta)-1+zeta^2)^2 ) ;

generateOCProblem("SingularCalogero", mesh = [ length=2, n=100 ], mesh_s0=-1, states_guess = [ x= 0]) ;

