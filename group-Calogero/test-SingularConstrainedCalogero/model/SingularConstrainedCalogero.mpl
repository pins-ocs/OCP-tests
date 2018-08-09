
# 
#            
# Controllo Singolare
# Calogero appunti pag. 188
# Inizializzazione
restart:
with(XOptima);
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
EQ1 := diff(x(t),t) = u(t) ;
EQNS_T := [ EQ1 ] : <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [ x(t) ] ;
# Controlli
cvars := [ u(t) ] ;
# Equazioni del modello matematico del carrello
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x],final=[x]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u,
                 controlType="U_QUADRATIC",#"U_COS_LOGARITHMIC",
                 min       = 0,
                 max       = 2,
                 epsilon   = 0.01,
                 tolerance = 0.01 ) ;
addModelExtraParameters([epsi_max,tol_max,epsi_min,tol_min]) ;
addUnilateralConstraint( x(zeta)-zeta <= u(zeta)-1,
                         uMaxBound,
                         epsilon=epsi_max,
                         tolerance=tol_max ) ;
setTarget( lagrange = u(zeta)*(zeta-4) ) ;

#setFDorder([2],"backward"):
#setFDorderCoEquation([u],"forward");
#Describe(generateOCProblem) ;
generateOCProblem( "SingularConstrainedCalogero",
                   integral_post_processing = [ [u(zeta)*(zeta-4), "int_target"] ],
                   post_processing = [ [x(zeta)+1-zeta, "ineq_arg"] ],
                   mesh            = [ length=3, n=600 ],
                   parameters      = [ x_i = 0, x_f=3,
                                       epsi_max=0.01, epsi_min=0.001,
                                       tol_max=0.01, tol_min=0.001 ],
                   continuation    = [ [[uMaxBound,"epsilon"] = epsi_max*(1-s)+s*epsi_min,
                                        [uMaxBound,"tolerance"] = tol_max*(1-s)+s*tol_min]],
                   controls_guess  = [ u = min(1.9,max(0.1,(x(zeta)+1-zeta)/2)+1) ],
                   states_guess    = [ x = zeta] ) ;

