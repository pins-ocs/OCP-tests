restart:;
with(XOptima):;
EQ1 := diff(x(t),t) - v(t);
EQ2 := diff(v(t),t) - (Fp(t)-Fm(t));
EQNS_T := [EQ||(1..2)];
qvars := [x(t),v(t)];
cvars := [Fp(t),Fm(t)];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [x=0,v=0],
  final   = [x=1,v=0]
);
infoBoundaryConditions();
setTarget( lagrange = Fp(zeta)+Fm(zeta) );
addControlBound(
  Fp,
  label       = "controlP",
  min         = 0,
  max         = FpMax,
  controlType = "U_CUBIC"
) ;
addControlBound(
  Fm,
  label       = "controlM",
  min         = 0,
  max         = FmMax,
  controlType = "U_CUBIC"
);
PARS := [FmMax = 10, FpMax = 10];
POST := [
  [controlP(Fp(zeta),0,FpMax),"ForceP"],
  [controlM(Fm(zeta),0,FmMax),"ForceM"],
  [Fp(zeta)-Fm(zeta),"F"]
];
CONT := [];
UGUESS := [ Fm = FmMax/2, Fp = FpMax/2 ];
GUESS  := [ x = zeta ];
MESH_DEF := [ length=1, n=100 ];
project_dir  := "../generated_code";
project_name := "BangBangFmodule";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESH_DEF,
  states_guess    = GUESS,
  controls_guess  = UGUESS
);
# if used in batch mode use the comment to quit;
