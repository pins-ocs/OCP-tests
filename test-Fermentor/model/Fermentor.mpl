# 
#            
# Fermentor (ICLOCS)
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    := diff(x1(t),t) = h1*x1(t)-u(t)*(x1(t)/(500*x4(t))):
EQ2    := diff(x2(t),t) = h2*x1(t)-0.01*x2(t)-u(t)*(x2(t)/(500*x4(t))):
EQ3    := diff(x3(t),t) = -h1*x1(t)/0.47 -h2*x1(t)/1.2-x1(t)*(0.029*x3(t)/(0.0001+x3(t)))+u(t)/x4(t)*(1-x3(t)/500):
EQ4    := diff(x4(t),t) = u(t)/500 :
EQNS_T := [ EQ||(1..4) ]: <%> ;
h1 := 0.11*(x3(t)/(0.006*x1(t)+x3(t)));
h2 := 0.0055*(x3(t)/(0.0001+x3(t)*(1+10*x3(t))));
# Variabili del problema e controlli
# Variabili
qvars := [x1(t),x2(t),x3(t),x4(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x1,x2,x3,x4]);
infoBoundaryConditions() ;
# Penalty
addUnilateralConstraint( x1(zeta) > 0, x1min,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = true ) ;
addUnilateralConstraint( x1(zeta) < 40, x1max,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
addUnilateralConstraint( x2(zeta) > 0, x2min,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
addUnilateralConstraint( x2(zeta) < 50, x2max,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
addUnilateralConstraint( x3(zeta) > 0, x3min,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
addUnilateralConstraint( x3(zeta) < 25, x3max,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
addUnilateralConstraint( x4(zeta) > 0, x4min,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = true ) ;
addUnilateralConstraint( x4(zeta) < 10, x4max,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.1,
                         barrier   = false ) ;
#addBilateralConstraint( x1(zeta), x1Range,
#                        min       = 0,
#                        max       = 40,
#                        scale     = 1,
#                        epsilon   = 0.01,
#                        tolerance = 0.01,
#                        barrier   = true ) ;
#addBilateralConstraint( x2(zeta), x2Range,
#                        min       = 0,
#                        max       = 50,
#                        scale     = 1,
#                        epsilon   = 0.01,
#                        tolerance = 0.01,
#                        barrier   = false ) ;
#addBilateralConstraint( x3(zeta), x3Range,
#                        min       = 0,
#                        max       = 25,
#                        scale     = 1,
#                        epsilon   = 0.01,
#                        tolerance = 0.01,
#                        barrier   = false ) ;
#addBilateralConstraint( x4(zeta), x4Range,
#                        min       = 0,
#                        max       = 10,
#                        scale     = 1,
#                        epsilon   = 0.01,
#                        tolerance = 0.01,
#                        barrier   = true ) ;
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 max=50,
                 min=0,
                 epsilon=0.01,
                 tolerance=0.01,
                 scale=1 ) ;
# Generazione del problema di controllo ottimo
#setFDorder([5],"backward"):
#setFDorderCoEquation([theta],"forward"):
# Post processing functions
setTarget( mayer    = -x2(zeta_f)*x4(zeta_f),
           lagrange = 0*0.00001*u(zeta)^2 ) ;

pars := [ x1_i = 1.5, x2_i = 0, x3_i = 0, x4_i = 7] ;
generateOCProblem( "Fermentor",
                    #post_processing = [[T(zeta),"minTime"]],
                    parameters     = pars,
                    mesh           = [length=126,n=400],
                    continuation   = [],
                    #controls_guess = [u=25],
                    states_guess   = [x1=x1_i,x2=x2_i,x3=x3_i,x4=x4_i]) ;
#eval(getOCProblem());

