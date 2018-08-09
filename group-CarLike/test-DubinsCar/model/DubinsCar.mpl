
# 
#            
# Dubins Car Tests
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Model Equation
EQ1  := diff(x(zeta),zeta)     = T*cos(theta(zeta)):
EQ2  := diff(y(zeta),zeta)     = T*sin(theta(zeta)):
EQ3  := diff(theta(zeta),zeta) = T*u(zeta) :
EQNS := convert([EQ||(1..3)],Vector) ;
# Variabili del problema
# Variabili
xvars := [x(zeta),y(zeta),theta(zeta)] ;
# Controlli
uvars := [u(zeta)] ;
# OCP problem
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars,parameters=[T]) ;
addBoundaryConditions(initial=[x,y,theta]);#,final=[x,y,theta]);
infoBoundaryConditions() ;
addControlBound( u, 
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=2,
                 epsilon=0.01,
                 tolerance=0.01,
                 scale=T) ;
#addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T, lagrange = 0 ) ;
#setTarget( mayer = mu*((x(zeta_f)-x_f)^2+(y(zeta_f)-y_f)^2+(theta(zeta_f)-theta_f)^2), lagrange = T(zeta) ) ;
#Describe(setFDorder) ;
#setFDorderEquations( [3], "backward", true ) ;
pars := [ mu       = 10,
          x_i      = -1, 
          y_i      =  0,
          x_f      =  0,
          y_f      =  0,
          dx       =  x_f - x_i,
          dy       =  y_f - y_i,
          theta0_i =  arctan(dy,dx),
          theta0_f =  theta0_i,
          theta1_i =  theta0_i+2*Pi,
          theta1_f =  theta0_f-2*Pi,
          theta_i  =  theta0_i,
          theta_f  =  theta0_f,
          T0       =  sqrt( dx^2+dy^2) ]  ;
guess := [ x     = x_i*(1-zeta) + zeta*x_f, 
           y     = y_i*(1-zeta) + zeta*y_f,
           theta = theta_i] ;
CONT := [ [theta_i = theta0_i + s*(theta1_i-theta0_i)],[theta_f = theta0_f + s*(theta1_f-theta0_f) ], [mu=10+s*100] ] ; 
generateOCProblem("DubinsCar", #language="MATLAB",
                   parameters   = pars,
                   continuation = CONT,
                   mesh         = [ length=1,n=400], mesh_s0=0,
                   parameters_guess = [ T=T0],
                   states_guess = guess ) ;
ocp := getOCProblem(verbose=true) ;
#ocp := _get_OCP_data();
#indices(ocp);
verosocp["g_vec"];
eval(ocp) ;
<<a,b>|<b,0>>^(-1) ;

