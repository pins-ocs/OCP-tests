# 
#            
# Controllo Singolare Luus
# ch.10 Example 4 (versione free time)
# Inizializzazione
restart:
with(XOptima);
#XOptimaInfo() ;
# Equazioni del modello
EQ1    :=  diff(x(zeta),zeta) = T(zeta)*y(zeta) :
EQ2    :=  diff(y(zeta),zeta) = T(zeta)*z(zeta) :
EQ3    :=  diff(z(zeta),zeta) = T(zeta)*u(zeta) :
EQ4    :=  diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ1, EQ2, EQ3, EQ4 ] : <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(zeta),y(zeta),z(zeta),T(zeta)] ;
# Controlli
cvars := [u(zeta)] ;
# Equazioni
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x,y,z],final=[x,y,z]);
#setBCActivationStatus(initial=[x,y]);
infoBoundaryConditions() ;
#addModelExtraParameters( [u_epsi, u_tol, min_u_epsi, T_guess] ) ;
# Penalty
addControlBound( u,
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=1,
                 epsilon=u_epsi,
                 tolerance=u_tol,
                 scale=T(zeta)*(x(zeta)^2+epsilon_T) ) ;
addUnilateralConstraint( T(zeta) > 0,
                         TimePositive,
                         scale     = 1,
                         epsilon   = 0.1,
                         tolerance = 0.1,
                         barrier   = true ) ;
setTarget( lagrange = T(zeta)*x(zeta)^2 ) ;

#setFDorder( [1,2,3], "4th", true ) ;
#setFDorder( [4], "backward", true ) ;
#setFDorderCoEquation( [z], "forward", true ) ;
generateOCProblem( "SingularLuus04_FreeTime",
                    post_processing = [[ zeta*T(zeta), "Time"]],
                    parameters   = [ x_i=1, y_i=0, z_i=0, x_f=0, y_f=0, z_f=0, 
                                     u_epsi = 0.01, u_tol = 0.01, epsilon_T = 1e-6, 
                                      min_u_epsi=1e-3, T_guess=40],
                    continuation = [[[u,"epsilon"]=u_epsi*(1-s)+s*min_u_epsi]],
                    mesh         = [ length=1, n=5000 ],
                    states_guess = [ x=x_i, y=y_i ,z=z_i, T=T_guess] ) ;

