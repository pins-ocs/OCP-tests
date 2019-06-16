
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
EQ1 := diff(x(t),t) = T*v(t);
EQ2 := diff(v(t),t) = T*F(t);
ode := [EQ||(1..2)] : Vector(%);
xvars := [x(t),v(t)];
pvars := [T];uvars := [F(t)];
# Optimal Contol Problem
loadDynamicSystem(  equations  = ode,  controls   = uvars,  states     = xvars,  parameters = pvars);
# Inserisce condizioni al contorno
addBoundaryConditions(  initial = [x=0,v=0],  final   = [x=2,v=0]);
infoBoundaryConditions() ;
# Penalty
addControlBound(
  F,
  label  = Fcontrol,
  maxabs = 1,
  scale  = T
);
# Generazione del problema di controllo ottimo
setTarget( mayer = T ) ;
Mesh := [
  [length=0.1,n=10],
  [length=0.4,n=40],
  [length=0.4,n=40],
  [length=0.1,n=10]
];
generateOCProblem(
  "BangBangFtminP", #clean = false,
  mesh              = Mesh,
  admissible_region = [ T > 0 ],
  states_guess      = [ x = zeta, v = 1 ],
  parameters_guess  = [ T = 1 ]
);


