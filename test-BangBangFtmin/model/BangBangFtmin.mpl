
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
EQ1 := diff(x(t),t) = T(t)*v(t);
EQ2 := diff(v(t),t) = T(t)*F(t);
EQ3 := diff(T(t),t) = 0;
ode := [EQ||(1..3)] :Vector(%);
xvars := [x(t),v(t),T(t)];
uvars := [F(t)];
# Optimal Contol Problem
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,v=0],final=[x=2,v=0]);
infoBoundaryConditions() ;
# Penalty
addControlBound(
  F,
  label  = Fcontrol,
  maxabs = 1,
  scale  = T(zeta)
);
# Generazione del problema di controllo ottimo
setTarget( mayer = T(zeta_f) ) ;
Mesh := [
  [length=0.1,n=10],
  [length=0.4,n=40],
  [length=0.4,n=40],
  [length=0.1,n=10]
];
generateOCProblem(
  "BangBangFtmin",
  mesh              = Mesh,
  admissible_region = [ T(zeta) > 0 ],
  states_guess      = [ x = zeta, v = 1, T = 1 ]
);

