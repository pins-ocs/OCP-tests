
# 
#            
# Zermelo Boat problem
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello matematico del veicolo
EQ1  := diff(x(zeta),zeta) = T*(V*cos(theta(zeta)) + velX(x(zeta),y(zeta))) :
EQ2  := diff(y(zeta),zeta) = T*(V*sin(theta(zeta)) + velY(x(zeta),y(zeta))) :
EQNS := convert([EQ||(1..2)],Vector) ;
# Variabili del problema
# Variabili
xvars := [x(zeta),y(zeta)] ;
# Controlli
uvars := [theta(zeta)] ;
# BVP
addUserFunction(velX(x,y)=y/sqrt(x^2+y^2+epsilon^2)) ;
addUserFunction(velY(x,y)=-x/sqrt(x^2+y^2+epsilon^2)) ;
addFunction(arctan2(y,x),2) ;
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars,parameters=[T]) ;
addBoundaryConditions(initial=[x=x0,y=y0],final=[x=x1,y=y1]);
infoBoundaryConditions() ;
setTarget( mayer = T, lagrange = 0) ;
#addUnilateralConstraint( T(zeta)>=0, Tpositive, tolerance=0.1 ) ;
Describe(setFDorder) ;
#setFDorder([3],"backward") ;
#setFDorderCoEquation([theta],"forward") ;
# Control deduced minimizing Hamiltonian
CONTROL := [theta = arctan2(-lambda2__xo(zeta),-lambda1__xo(zeta))] ;
GUESS := [ x=x0*(1-zeta)+x1*zeta, y=y0*(1-zeta)+y1*zeta,
           lambda1__xo=-1,lambda2__xo=-0.01,lambda2__xo=-1 ] ;
#Describe(generateOCProblem) ;
generateOCProblem( "ZermeloSimple",#language="MATLAB",clean=false,
                    parameters     = [ V=1, x0=0, y0=0,x1=101,y1=0,epsilon=0.001],
                    #continuation  = [[epsi_u=1-s]],
                    mesh           = [ [length=0.1, n=1000],[length=0.8, n=1000],[length=0.1, n=1000] ],
                    controls_user_defined = CONTROL,
                    #controls_guess = [ theta = arctan2(-lambda2__xo(zeta),-lambda1__xo(zeta)) ],
                    parameters_guess = [ T=sqrt((x1-x0)^2+(y1-y0)^2)/V],
                    states_guess   = GUESS ) ;
# Riscrivo il controllo con arctan2 e cambio g_vec
#u_vec[1] := arctan2(numer(tan(u_vec[1])),denom(tan(u_vec[1]))) ;
#g_vec[1] := u_vars[1] - u_vec[1] ;
#OCP := getOCProblem(verbose=true) ;

