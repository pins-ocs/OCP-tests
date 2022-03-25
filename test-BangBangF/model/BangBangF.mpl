restart:;
with(XOptima):;
EQ1    :=  diff(x(t),t) - v(t):
EQ2    :=  diff(v(t),t) - F(t):
EQNS_T := [ EQ||(1..2) ]: <%>;
qvars := [x(t),v(t)];
cvars := [F(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x=x_i,v=v_i],final=[v=v_f]);
infoBoundaryConditions();
setTarget( mayer = -x(zeta_f) );
addControlBound( F, controlType="U_COS_LOGARITHMIC", maxabs=1 );
addUserFunction(C1(v) = -(v__max - v));
addUnilateralConstraint(
  C1(v(zeta)) <= 0,
  C1_constr,
  barrier   = false,
  epsilon   = 0.001,
  tolerance = 0.025,
  scale     = 1 
);
PARS := [ v__max=0.3, x_i = 0, v_i=0, v_f=0 ];
POST := [[ C1(v(zeta)), "C1" ]];
CONT := [];
GUESS := [ v = zeta*(1-zeta) ];
MESH_DEF := [length=1, n=100];
project_dir  := "../generated_code";
project_name := "BangBangF";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
