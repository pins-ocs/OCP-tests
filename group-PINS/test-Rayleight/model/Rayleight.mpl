
# 
#            
# Rayleight
# (Numerical solution of optimal control problems
# Francesca Mazzia and Donato Trigiante)
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    := diff(x1(zeta),zeta) = x2(zeta):
EQ2    := diff(x2(zeta),zeta) = -x1(zeta)+(1.4-0.14*x2(zeta)^2)*x2(zeta)+4*u(zeta):
EQNS_T := [ EQ||(1..2) ]: <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x1(zeta),x2(zeta)] ;
# Controlli
cvars := [u(zeta)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x1=-5,x2=-5]);
infoBoundaryConditions() ;
# Penalty
# Generazione del problema di controllo ottimo
#setFDorder([5],"backward"):
#setFDorderCoEquation([theta],"forward"):
# Post processing functions
setTarget( lagrange = x1(zeta)^2+u(zeta)^2 ) ;

pars := [ ] ;
generateOCProblem( "Rayleight",
                    #post_processing = [[T(zeta),"minTime"]],
                    parameters   = [],
                    mesh         = [length=2.5,n=1000],
                    #continuation = cont,
                    states_guess = []) ;

