restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = v(t):
EQ2 := diff(v(t),t) = clip(F(t),minClip,maxClip):
EQ3 := diff(F(t),t) = vF(t):

ode := [EQ||(1..3)]: <%>;
xvars := [x(t),v(t),F(t)];
uvars := [vF(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [x=0,v=0,F=0],
  final   = [v=0,F=0]
);
infoBoundaryConditions();
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithErf",
  [ h=h0, delta=0 ]
);
setTarget( mayer = -x(zeta_f) );
addControlBound(
  vF,
  label     = controlForce,
  min       = -vFmax,
  max       = vFmax,
  epsilon   = epsilon0,
  tolerance = tolerance0
);
PARS := [
  vFmax      = 10,
  minClip    = -1,
  maxClip    = 1,
  epsilon0   = 0.1,
  epsilon1   = 1e-4,
  tolerance0 = 0.01,
  tolerance1 = 1e-4,
  h0         = 0.01,
  h1         = 1e-10
];
POST := [
  [clip(F(zeta),minClip,maxClip),"F_clipped"]
];
CONTINUATION := [
  [
    [ "clip",         "h"         ] = h0*(1-s)+s*h1,
    [ "controlForce", "epsilon"   ] = (1-s)*epsilon0+s*epsilon1,
    [ "controlForce", "tolerance" ] = (1-s)*tolerance0+s*tolerance1
  ]
];
GUESS := [v=1];
MESH_DEF := [length=1,n=100];
project_dir  := "../generated_code";
project_name := "BangBangFclip";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONTINUATION,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
