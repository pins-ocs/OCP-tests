
# 
#            
# Dadebo and McAuley 1995
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=  diff(x(t),t) - u(t) :
EQ2    :=  diff(y(t),t) - x(t)^2-u(t)^2 :

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
addBoundaryConditions(initial=[x=1,y=0],final=[x=1]);
infoBoundaryConditions() ;
#addDefaultParameters([]) ;
# Penalty
setTarget( mayer = y(zeta_f)) ;

#Describe(buildOCProblem) ;
generateOCProblem("Dadebo1",
                   mesh         = [ length=1,n=1000], mesh_s0=0,
                   states_guess = [ x = 1, y = 0, lambda2__xo = 1 ] ) ;

