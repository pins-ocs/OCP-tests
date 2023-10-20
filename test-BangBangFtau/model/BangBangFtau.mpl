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
infoBoundaryConditions();
setTarget(
  mayer    = -x(zeta_f),
  lagrange = epsiTB*(vsT(zeta)^2+vsB(zeta)^2)
);
cpars := epsilon = epsi0, tolerance = tol0;
addUnilateralConstraint( vsT(zeta) >= 0, vsTpositive, cpars );
addUnilateralConstraint( vsB(zeta) >= 0, vsBpositive, cpars );
addUnilateralConstraint( vsT(zeta) <= maxT, vsTmax, cpars );
addBilateralConstraint( vsT(zeta)-vsB(zeta), vsTBInterval, cpars );
PARS := [
  epsiTB  = 0.001,
  tauT    = 0.02,
  tauB    = 0.001,
  epsi0   = 0.01, epsi1 = 0.0001,
  tol0    = 0.01, tol1  = 0.0001,
  maxT    = 2,
  minClip = -1,
  maxClip = 1
];
POST := [
  [sT(zeta)-sB(zeta),"F"],
  [clip(sT(zeta)-sB(zeta),minClip,maxClip),"clipF"]
];
CONTINUATION := [
  [
    epsi = epsi0*(1-s) + epsi1*s,
    tol  = tol0*(1-s) + tol1*s,

    [ "vsTpositive", "epsilon"   ] = epsi,
    [ "vsTpositive", "tolerance" ] = tol,
    [ "vsBpositive", "epsilon"   ] = epsi,
    [ "vsBpositive", "tolerance" ] = tol,


    [ "vsTmax", "epsilon"   ] = epsi,
    [ "vsTmax", "tolerance" ] = tol,


    [ "vsTBInterval", "epsilon"   ] = epsi,
    [ "vsTBInterval", "tolerance" ] = tol
  ]
];
GUESS  := [ v = zeta*(1-zeta) ];
UGUESS := [ vsT = epsi0, vsB = epsi0 ];
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
