# 
#            
# Dubins Car Tests
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Model Equation
EQ1  := diff(x(zeta),zeta)     = T(zeta)*cos(theta(zeta)):
EQ2  := diff(y(zeta),zeta)     = T(zeta)*sin(theta(zeta)):
EQ3  := diff(theta(zeta),zeta) = T(zeta)*u(zeta) :
EQ4  := diff(T(zeta),zeta)     = 0:
EQNS := convert([EQ||(1..4)],Vector) ;
# Variabili del problema
# Variabili
xvars := [x(zeta),y(zeta),theta(zeta),T(zeta)] ;
# Controlli
uvars := [u(zeta)] ;
# OCP problem
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x,y,theta],final=[x,y]);
infoBoundaryConditions() ;
addControlBound( u, 
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=2,
                 epsilon=0.01,
                 tolerance=0.001,
                 scale=T(zeta) ) ;
addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T(zeta_f)) ;
Describe(setFDorder) ;
setFDorder( [3], "backward", true ) ;
generateOCProblem("DubinsCar",
                   parameters   = [ x_i=4, y_i=0, theta_i=evalf(Pi/2), x_f=0, y_f=0 ],
                   mesh         = [ length=1,n=1000], mesh_s0=0,
                   continuation = [[ [u,"epsilon"] = 0.01*(1-s)+s*1e-6]],
                   states_guess = [ x = x_i, y = y_i, theta = theta_i, T=1 ] ) ;

