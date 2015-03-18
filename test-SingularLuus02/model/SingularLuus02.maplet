# 
#            
# Controllo Singolare Luus
# 10.2.2 Example 2
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2 ] : <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(t),y(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x,y]);
#setBCActivationStatus(initial=[x,y]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=1,
                 epsilon=0.001,
                 tolerance=0.001,
                 scale=x(zeta)^2+epsi_x^2 ) ;
setTarget( lagrange = x(zeta)^2 ) ;

#Describe(generateOCProblem) ;
generateOCProblem( "SingularLuus02",
                   integral_post_processing = [[x(zeta)^2,"intTarget"]],
                   parameters   = [ epsi_x=1e-4, x_i = 0, y_i = 1, Tf=5],
                   mesh         = [ length=Tf, n=400 ],
                   states_guess = [ x=x_i, y=y_i ] ) ;

