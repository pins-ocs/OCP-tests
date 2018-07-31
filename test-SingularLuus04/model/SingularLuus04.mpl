# 
#            
# Controllo Singolare LuusExample 4
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = z(t) :
EQ3    :=  diff(z(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2, EQ3 ] : <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(t),y(t),z(t)] ;
# Controlli
cvars := [u(t)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x,y,z]);
infoBoundaryConditions() ;
addModelExtraParameters( [u_epsi, u_tol, epsilon_X, min_u_epsi] ) ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=1,
                 epsilon=u_epsi,
                 tolerance=u_tol,
                 scale=(x(zeta)^2+epsilon_X) ) ;
setTarget( lagrange = x(zeta)^2 ) ;

generateOCProblem( "SingularLuus04",
                   integral_post_processing = [[x(zeta)^2,"intTarget"]],
                   parameters   = [ u_epsi=0.01, u_tol=0.01, epsilon_X=1e-7, min_u_epsi=1e-7, x_i = 1, y_i = 0, z_i=0, Tf=6],
                   continuation = [[[u,"epsilon"]=u_epsi*(1-s)+s*min_u_epsi]],
                   mesh         = [ length=Tf, n=2000 ],
                   states_guess = [ x=x_i, y=y_i, z=z_i ] ) ;

