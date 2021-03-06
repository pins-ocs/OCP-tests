
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Dynamic system equations
EQ1    := diff(x(t),t) - v(t) :
EQ2    := diff(v(t),t) - F(t) :
EQNS_T := [ EQ||(1..2) ];
# States and Controls
qvars := [x(t),v(t)] ;
cvars := [F(t)] ;
# Optimal Contol Problem
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions() ;
addControlBound( F, label=Fcontrol, min = -fMax(zeta), max = fMax(zeta) ) ;
# Target
#Describe(addUserFunction);
addUserFunction( fMax(zeta) = 1 + amp1*sin(zeta)+amp2*sin(10*zeta) ) ;
setTarget( mayer = -x(zeta_f) );
generateOCProblem( "BangBangFwork",
                   parameters   = [amp1=0.1, amp2=0.01],
                   mesh         = [[length=0.1,n=10],[length=0.4,n=40],[length=0.4,n=40],[length=0.1,n=10]],
                   states_guess = []) ;

