
# 
#            
# Particle Steering (test 9 di COPS)
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello matematico del veicolo
EQ1  := diff(x(zeta),zeta)  = T(zeta)*(vx(zeta) + velX(x(zeta),y(zeta))) :
EQ2  := diff(y(zeta),zeta)  = T(zeta)*(vy(zeta) + velY(x(zeta),y(zeta))) :
EQ3  := diff(vx(zeta),zeta) = T(zeta)*(S*cos(u(zeta))) :
EQ4  := diff(vy(zeta),zeta) = T(zeta)*(S*sin(u(zeta))) :
EQ5  := diff(T(zeta),zeta)  = 0:
EQNS := convert([EQ||(1..5)],Vector) ;
# Variabili del problema
# Variabili
xvars := [x(zeta),y(zeta),vx(zeta),vy(zeta),T(zeta)] ;
# Controlli
uvars := [u(zeta)] ;
# BVP
addUserFunction(velX(x,y)=-y) ;
addUserFunction(velY(x,y)=x) ;
addUserFunction(arctan2(y,x),0) ; # definita un codice utente
;
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x=0,y=0,vx=0,vy=0],final=[y=5,vx=45,vy=0]);
infoBoundaryConditions() ;
setTarget( mayer = T(zeta_f), lagrange = 0 ) ;
addUnilateralConstraint( T(zeta)>=0, Tpositive, barrier=true ) ;
generateOCProblem( "Zermelo",
                    integral_post_processing = [[zeta*T(zeta),"Time"]],
                    parameters     = [ S=50 ],
                    #continuation   = [[epsi_u=1-s]],
                    mesh           = [ length=1, n=1000 ],
                    controls_guess = [ u = arctan2(-lambda4__xo(zeta),
                                                   -lambda3__xo(zeta)) ],
                    states_guess   = [ x=5*zeta, y=45*zeta, lambda3__xo=1, T=1] ) ;
# Riscrivo il controllo con arctan2 e cambio g_vec
#u_vec[1] := arctan2(numer(tan(u_vec[1])),denom(tan(u_vec[1]))) ;
#g_vec[1] := u_vars[1] - u_vec[1] ;

