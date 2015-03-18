# 
#            
# Controllo Singolare
# Marchal
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = u(t) :
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
addBoundaryConditions(initial=[x,y],final=[x,y]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC", 
                 maxabs=1,
                 scale=(1/2)*x(zeta)^2+epsilon ) ;
setTarget( lagrange = (1/2)*x(zeta)^2) ;

generateOCProblem( "SingularMarchal",
                   parameters   = [x_i=2, y_i = -2, x_f=2, y_f = 2, epsilon=1e-8],
                   mesh         = [length=8,n=1000], mesh_s0=0,
                   states_guess = [ x = 0, y = 0] ) ;

