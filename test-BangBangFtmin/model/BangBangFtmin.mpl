restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = T(t)*v(t);
EQ2 := diff(v(t),t) = T(t)*F(t);
EQ3 := diff(T(t),t) = 0;
ode := [EQ||(1..3)] :Vector(%);
xvars := [x(t),v(t),T(t)];
uvars := [F(t)];
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x=0,v=0],final=[x=2,v=0]);
infoBoundaryConditions() ;
addControlBound(
  F,
  label  = Fcontrol,
  maxabs = 1,
  scale  = T(zeta)
);
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
;
