restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = T*v(t);
EQ2 := diff(v(t),t) = T*F(t);
ode := [EQ||(1..2)] : Vector(%);
xvars := [x(t),v(t)];
pvars := [T];
uvars := [F(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [x=0,v=0],
  final   = [x=2,v=0]
);
infoBoundaryConditions() ;
addControlBound(
  F,
  label  = Fcontrol,
  maxabs = 1,
  scale  = T
);
setTarget( mayer = T );
Mesh := [
  [length=0.1,n=10],
  [length=0.4,n=40],
  [length=0.4,n=40],
  [length=0.1,n=10]
];
generateOCProblem(
  "BangBangFtminP", #clean = false,
  mesh                    = Mesh,
  admissible_region       = [ T > 0 ],
  states_guess            = [ x = zeta, v = 1 ],
  optimization_parameters = [ T = 1 ]
);
;
;
