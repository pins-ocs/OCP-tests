restart;
with(XOptima):
interface(rtablesize=20):;
mapUserFunctionToRegularized(
  clip, "ClipIntervalWithSinAtan",
  ["h"=h_clip0,"delta"=0]
);
addUserFunction(Tmax_normalized(v)=Pmax/(m*g)*(1-v/vmax));
#addUserFunction(clip(v,mi,ma)=Pmax/(m*g)*(1-v/vmax));
EQ1 := diff(x(t),t) = v(t);
EQ2 := diff(v(t),t) = g*(mur(t)+muf(t));
1/diff(t(x),x) - v(t) ;
EXPLICIT := false:
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
addBoundaryConditions( initial = [v=v_i], final = [v=v_f] );
infoBoundaryConditions();
penScale := 1/v(zeta);
setTarget( lagrange = penScale, mayer = 0 );
addControlBound(
  mur,
  min       = mur_min,
  max       = clip(Tmax_normalized(v(zeta)),0,mur_max),
  epsilon   = u_epsi0,
  tolerance = u_tol0,
  subtype   = "U_COS_LOGARITHMIC",
  scale     = penScale
);
addControlBound(
  muf,
  min       = muf_min,
  max       = 0,
  epsilon   = u_epsi0,
  tolerance = u_tol0,
  subtype   = "U_COS_LOGARITHMIC",
  scale     = penScale
);
addUnilateralConstraint(
  v(zeta) >= v_min,
  vMinLimit,
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
  vmax    = 100,
  h_clip0 = 0.1, h_clip1 = 0.01,
  u_epsi0 = 0.1, u_epsi1 = 0.001,
  u_tol0  = 0.1, u_tol1  = 0.001
];
POST := [
  [ 1/v(zeta), ["dtime", "time"] ],
  [ Tmax_normalized(v(zeta)), "Tmax_norma" ]
];
CLIST := ["mur", "muf"];
CONTINUATION := [
  [
    [ CLIST, "epsilon"   ] = u_epsi0*(1-s)+u_epsi1*s,
    [ CLIST, "tolerance" ] = u_tol0*(1-s)+u_tol1*s,
    [ "clip", "h" ]        = h_clip0*(1-s)+h_clip1*s
  ]
];
GUESS := [ v = v_i ];
MESH_DEF := [[ length=1000, n=200 ]];
project_dir  := "../generated_code";
project_name := "Bike1D";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONTINUATION,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
ocp := getOCProblem();
ocp["Hamiltonian"];
ocp["JU_penalty"];
eval(ocp["adjoint_ode"]["Hxp"]):<%>;
#eval(ocp);
# if used in batch mode use the comment to quit;
