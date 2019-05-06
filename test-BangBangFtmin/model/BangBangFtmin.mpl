
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
EQ1 :=  diff(x(t),t) - v(t) ;
EQ2 :=  diff(v(t),t) - F(t) ;
EQNS_T := [EQ||(1..2)] :Vector(%);
ode, xvars, uvars := freeTime( Vector(EQNS_T), [x(t),v(t)], [F(t)], "log" );
# Optimal Contol Problem
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,v=0],final=[x=2,v=0]);
infoBoundaryConditions() ;
# Penalty
addControlBound( F, label=Fcontrol, maxabs=1, scale=exp(logTimeSize(zeta))) ;
# Generazione del problema di controllo ottimo
#set4order([1,2]) ;
setTarget(mayer = exp(logTimeSize(zeta_f)) ) ;
generateOCProblem(
  mesh         = [[length=0.1,n=10],[length=0.4,n=40],[length=0.4,n=40],[length=0.1,n=10]],
  states_guess = [logTimeSize = 0]
