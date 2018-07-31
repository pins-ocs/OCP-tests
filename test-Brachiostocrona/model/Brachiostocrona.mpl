
# 
#            
# Brachiostocrona
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1    :=      diff(x(zeta),zeta)     =   T*v(zeta)*sin(theta(zeta)):
EQ2    :=      diff(y(zeta),zeta)     = - T*v(zeta)*cos(theta(zeta)):
EQ3    := mass*diff(v(zeta),zeta)     =   T*g*cos(theta(zeta)):
EQ4    :=      diff(theta(zeta),zeta) = vtheta(zeta):
EQNS_T := [ EQ||(1..4) ]: <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(zeta),y(zeta),v(zeta),theta(zeta)] ;
# Controlli
cvars := [vtheta(zeta)] ;
# OCP
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,
                  controls=cvars,
                  states=qvars,
                  parameters=[T]) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,y=0,v=0],final=[x=xf,y=yf]);
infoBoundaryConditions() ;
# Penalty
addControlBound( vtheta,
                 scale       = T,
                 controlType = "U_QUADRATIC",
                 maxabs      = 10,
                 epsilon     = 0.001,
                 tolerance   = 0.001 ) ;
#addUnilateralConstraint( T > 0,
#                         TimePositive,
#                         scale     = 1,
#                         epsilon   = 0.1,
#                         tolerance = 0.01 ) ;
# Generazione del problema di controllo ottimo
setTarget( mayer = T ) ;

# Calcolo tempo e velocità lungo piano inclinato
LEN  := evalf(sqrt(xf^2+yf^2)):
TIME := evalf(sqrt(-2*yf/g)) ; subs(g=9.81,%);
VF   := evalf(LEN/TIME) ; subs(g=9.81,%);
generateOCProblem( "Brachiostocrona",
                   admissible_region=[T>0],
                   parameters = [ mass=1,
                                  xf = 10,
                                  yf = -3,
                                  Vf = VF,
                                  Tf = TIME,
                                  g  = 9.81 ],
                    mesh         = [length=1,n=500],
                    parameters_guess = [T=Tf],
                    states_guess = [x=zeta*xf,
                                    y=-zeta*yf,
                                    v=Vf]) ;


