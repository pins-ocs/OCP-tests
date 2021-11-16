restart:;
EQ1 := diff(x(t),t) = v(t);
EQ2 := diff(v(t),t) = g*(mur(t)+muf(t));
1/diff(t(x),x) - v(t) ;
EQ1 := v(x)*diff(v(x),x) - g*(mur(x)+muf(x));
vars := [v(x)];
ctrl := [mur(x),muf(x)];
eqns := [EQ1];
with(XOptima):
interface(rtablesize=20):;
loadDynamicSystem(
  equations     = eqns,
  states        = vars, 
  controls      = ctrl,
  meshFunctions = []
);
addBoundaryConditions( initial = [v], final = [v] );
infoBoundaryConditions();
penScale := 1/v(zeta);
setTarget( lagrange = penScale, mayer = 0 );
#addUnilateralConstraint( v(zeta)/vmax <= 2, vMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) <= mur_max, rearTyreAdherenceMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) >= mur_min, rearTyreAdherenceMinLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( muf(zeta) <= 0, frontTyreAdherenceMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( muf(zeta) >= muf_min, frontTyreAdherenceMinLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) <= Tmax_normalized(v(zeta)),maxTractionLimit,
#                         tolerance=0.01, scale = penScale );
addUnilateralConstraint(
  v(zeta) >= v_min,
  vMinLimit,
  barrier   = true,
  tolerance = 0.1,
  epsilon   = 0.1,
  scale     = penScale
);
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
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithSinAtan",
  ["h"=0.01,"delta"=0]
);
addUserFunction(Tmax_normalized(v)=Pmax/(m*g)*(1-v/vmax));
#addUserFunction(clip(v,mi,ma)=Pmax/(m*g)*(1-v/vmax));
data := [
  g         = 9.81,
  m         = 275,
  mur_max   = 1,
  mur_min   = -1,
  muf_min   = -1,
  #vmur_min = -0.5,
  #vmur_max =  0.5,
  #vmuf_min = -0.5,
  #vmuf_max =  0.5,
  v_i       = 10,
  v_f       = 10,
  v_min     = 1,
  #mur_i    = 0,
  #mur_f    = 0,
  #muf_i    = 0,
  #muf_f    = 0,
  Pmax      = 50*1000, # Kwatt
  vmax      = 100
]:;
Mesh := [[ length=1000, n=1000 ]];
;
;
;
post_list := [
  [Tmax_normalized(v(zeta)), "Tmax_norma"]
]:;
int_post_list := [
  [1/v(zeta),"time"]
]:;
generateOCProblem(
  "Bike1D",
  integral_post_processing = int_post_list,
  post_processing          = post_list,
  parameters               = data,
  mesh                     = Mesh,
  states_guess             = [ v = v_i]
);
;
