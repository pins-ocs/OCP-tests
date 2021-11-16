restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = v(t) ;
EQ2 := diff(v(t),t) = clip(F(t),minClip,maxClip) ;
EQ3 := diff(F(t),t) = vF(t);

ode   := [EQ||(1..3)]: Vector(%);
xvars := [x(t),v(t),F(t)];
uvars := [vF(t)];
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(
  initial = [x=0,v=0,F=0],
  final   = [v=0,F=0]
);
infoBoundaryConditions() ;
addControlBound(
  vF,
  label   = controlForce,
  min     = -vFmax,
  max     = vFmax,
  epsilon = epsilon0
);
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithErf",
  [ h=h0, delta=0 ]
);
setTarget( mayer = -x(zeta_f) ) ;
CONTINUATION := [
  [
    [ "clip",         "h"       ] = h0*(1-s)+s*h1,
    [ "controlForce", "epsilon" ] = (1-s)*epsilon0+s*epsilon1
  ]
];
PARS := [
  vFmax    = 10,
  minClip  = -1,
  maxClip  = 1,
  epsilon0 = 0.1,
  epsilon1 = 1e-4,
  h0       = 0.1,
  h1       = 1e-10
];
addUserFunction(fun(x)=x^2);
generateOCProblem( clean=false,
  "BangBangFclip",
  post_processing = [[clip(F(zeta),minClip,maxClip),"F_clipped"]],
  parameters      = PARS,
  mesh            = [length=1,n=400],
  continuation    = CONTINUATION,
  states_guess    = [v=1]
);
;
