restart;
with(XOptima):
interface(rtablesize=20):;
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithSinAtan",
  ["h"=0.01,"delta"=0]
);
addUserFunction(Tmax_normalized(v)=Pmax/(m*g)*(1-v/vmax));
#addUserFunction(clip(v,mi,ma)=Pmax/(m*g)*(1-v/vmax));
EQ1 := diff(x(t),t) = v(t);
EQ2 := diff(v(t),t) = g*(mur(t)+muf(t));
1/diff(t(x),x) - v(t) ;
EXPLICIT := true:
if EXPLICIT then 
  EQ1 := diff(v(x),x) - g*(mur(x)+muf(x))/v(x);
else
  EQ1 := v(x)*diff(v(x),x) - g*(mur(x)+muf(x));
end:;
vars := [v(x)];
ctrl := [mur(x),muf(x)];
eqns := [EQ1];
#eqns := op(solve(eqns,diff(vars,x)));
loadDynamicSystem(
  equations = eqns,
  states    = vars, 
  controls  = ctrl
);
addBoundaryConditions( initial = [v], final = [v] );
infoBoundaryConditions();
penScale := 1/v(zeta);
setTarget( lagrange = penScale, mayer = 0 );
addControlBound(
  mur,
  min         = mur_min,
  max         = clip(Tmax_normalized(v(zeta)),0,mur_max),
  controlType = "U_COS_LOGARITHMIC",
  scale       = penScale
);
addControlBound(
  muf,
  min         = muf_min,
  max         = 0,
  controlType = "U_COS_LOGARITHMIC",
  scale       = penScale
);
addUnilateralConstraint(
  v(zeta) >= v_min,
  vMinLimit,
  barrier   = true,
  tolerance = 0.1,
  epsilon   = 0.1,
  scale     = penScale
);
PARS := [
  g       = 9.81,
  m       = 275,
  mur_max = 1,
  mur_min = -1,
  muf_min = -1,
  v_i     = 10,
  v_f     = 10,
  v_min   = 1,
  Pmax    = 50*1000, # Kwatt
  vmax    = 100
];
POST := [
  [ Tmax_normalized(v(zeta)), "Tmax_norma" ]
];
IPOST := [
  [ 1/v(zeta), "time" ]
]:;
CONTINUATION := [];
GUESS := [ v = v_i ];
MESH_DEF := [[ length=1000, n=100 ]];
project_dir  := "../generated_code";
project_name := "Bike1D";
generateOCProblem(
  project_name,
  standard_post_processing = true,
  integral_post_processing = IPOST,
  post_processing          = POST,
  parameters               = PARS,
  continuation             = CONTINUATION,
  mesh                     = MESH_DEF,
  states_guess             = GUESS
);
ocp := getOCProblem();
#eval(ocp);
eval(ocp["FD"]);
eval(ocp["ode"]);
eval(ocp["controls"]["u"]);
# if used in batch mode use the comment to quit;
