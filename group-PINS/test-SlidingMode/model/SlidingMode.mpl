# 
#            
# Sliding Mode
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) = u(t) :
EQ2    :=  diff(y(t),t) = x(t)^2 :
EQNS_T := [ EQ||(1..2) ];
# Variabili del problema e controlli
# Variabili
qvars := [x(t),y(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x,y],final=[x]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u, controlType="U_COS_LOGARITHMIC", maxabs=1 ) ;
setTarget( mayer = y(zeta_f) ) ;
#setFDorder([x],"forward") ;
generateOCProblem( "SlidingMode",
                   parameters   = [ x_i = 1, x_f=1, y_i=0],
                   mesh         = [length=3, n=100],
                   states_guess = [] ) ;

