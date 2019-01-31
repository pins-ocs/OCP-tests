
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Controllo Singolare Luus
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Controllo Singolare Luus, 10.2.3 Example 3
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Dynamical system equations
EQ1    :=  diff(x1(t),t) - x2(t) :
EQ2    :=  diff(x2(t),t) - u(t) :
EQ3    :=  diff(x3(t),t) - (x1(t)^2+x2(t)^2):
EQNS_T := [ EQ1, EQ2, EQ3 ] : <%> ;
# States and controls
qvars := [x1(t),x2(t),x3(t)] ;
cvars := [u(t)] ;
# Optimal Contol Problem
#infoRegisteredObjects() ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno (tutte libere)
addBoundaryConditions(initial=[x1,x2,x3]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u, 
                 controlType="U_COS_LOGARITHMIC",
                 maxabs=1,
                 epsilon=0.0001, tolerance=0.00001 ) ;
setTarget( mayer = x3(zeta_f) ) ;

generateOCProblem(  "SingularLuus03",
  parameters   = [ x1_i = 0, x2_i = 1, x3_i = 0, Tf=5],
  mesh         = [ length=Tf, n=5000 ],
  states_guess = [ x1=x1_i, x2=x2_i, x3=x3_i ]);

