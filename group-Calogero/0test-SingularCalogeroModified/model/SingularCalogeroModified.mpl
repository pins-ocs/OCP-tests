# 
#            
# Controllo Singolare
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) - y(t) :
EQ2    :=  diff(y(t),t) - u(t) :
EQNS_T := [ EQ1, EQ2 ];
# Variabili del problema e controlli
# Variabili
qvars := [x(t),y(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[y],final=[y]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=1,
                 scale=epsilon+(x(zeta)-1+C*zeta^2)^2 ) ;
setTarget( lagrange = (x(zeta)-1+C*zeta^2)^2 ) ;

generateOCProblem( "SingularCalogeroModified",
                   mesh         = [ length=2,n=100 ], mesh_s0=-1,
                   parameters   = [y_i=0, y_f=0, C=0.25, epsilon=1e-8],
                   states_guess = [ x = 0, y=0] ) ;

