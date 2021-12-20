restart:;
with(XOptima):;
addUserFunction( fMax(zeta) = 1 + amp1*sin(zeta)+amp2*sin(10*zeta) );
EQ1    := diff(x(t),t) - v(t):
EQ2    := diff(v(t),t) - F(t):
EQNS_T := [ EQ||(1..2) ]: <%>;
qvars := [x(t),v(t)];
cvars := [F(t)];
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars);
addBoundaryConditions(initial=[x=0,v=0],final=[v=0]);
infoBoundaryConditions();
setTarget( mayer = -x(zeta_f) );
addControlBound( F, label=Fcontrol, min = -fMax(zeta), max = fMax(zeta) );
PARS := [amp1=0.25, amp2=0.1];
POST := [
  [fMax(zeta), "fMax"],
  [-fMax(zeta), "mfMax"]
];
CONTINUATION := [];
GUESS := [];
MESH_DEF := [ length=1, n=100 ];
project_dir  := "../generated_code";
project_name := "BangBangFwork";
generateOCProblem(
  project_name,
  standard_post_processing = true,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONTINUATION,
  mesh            = MESH_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
