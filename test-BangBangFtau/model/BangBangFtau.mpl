restart:;
with(XOptima):;
mapUserFunctionToRegularized( clip, "ClipIntervalWithErf" );
EQ1 := diff(x(t),t) - v(t):
EQ2 := diff(v(t),t) - clip(sT(t)-sB(t),minClip,maxClip):
EQ3 := diff(sT(t),t) + (sT(t) - vsT(t))/tauT:
EQ4 := diff(sB(t),t) + (sB(t) - vsB(t))/tauB:
EQNS_T := [ EQ||(1..4) ]:<%>;
qvars := [x(t),v(t),sT(t),sB(t)];
cvars := [vsT(t),vsB(t)];
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars);
addBoundaryConditions(initial=[x=0,v=0,sT=0,sB=0],final=[v=0]);
infoBoundaryConditions() ;
setTarget(
  mayer    = -x(zeta_f),
  lagrange = epsiTB*(vsT(zeta)^2+vsB(zeta)^2)
);
addUnilateralConstraint( vsT(zeta) >= 0, vsTpositive );
addUnilateralConstraint( vsB(zeta) >= 0, vsBpositive );
addUnilateralConstraint( vsT(zeta) <= maxT, vsTmax );
addBilateralConstraint( vsT(zeta)-vsB(zeta), vsTBInterval );
PARS := [
  epsiTB  = 0.001,
  tauT    = 0.02,
  tauB    = 0.001,
  maxT    = 2,
  minClip = -1,
  maxClip = 1
];
POST := [
  [sT(zeta)-sB(zeta),"F"],
  [clip(sT(zeta)-sB(zeta),minClip,maxClip),"clipF"]
];
CONTINUATION := [];
GUESS  := [ v = zeta*(1-zeta) ];
UGUESS := [ vsT = 0, vsB = 0 ];
MESH_DEF := [ [length=1,n=400] ];
project_dir  := "../generated_code";
project_name := "BangBangFtau";
generateOCProblem(
  project_name,
  standard_post_processing = true,
  post_processing    = POST,
  parameters         = PARS,
  continuation       = CONTINUATION,
  mesh               = MESH_DEF,
  controls_iterative = true,
  controls_guess     = UGUESS,
  states_guess       = GUESS
);
# if used in batch mode use the comment to quit;
