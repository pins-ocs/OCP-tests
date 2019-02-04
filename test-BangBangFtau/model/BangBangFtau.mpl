
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
restart:
with(XOptima):
# Equations of motion
EQ1 := diff(x(t),t) - v(t);
EQ2 := diff(v(t),t) - clip(sT(t)-sB(t),minClip,maxClip);
EQ3 := diff(sT(t),t) + (sT(t) - vsT(t))/tauT ;
EQ4 := diff(sB(t),t) + (sB(t) - vsB(t))/tauB ;
EQNS_T := [ EQ||(1..4) ];
# States and Controls
# States
qvars := [x(t),v(t),sT(t),sB(t)] ;
# Controls
cvars := [vsT(t),vsB(t)] ;
# Optimal control problem formulation
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
mapUserFunctionToRegularized( clip, "ClipIntervalWithErf" ) ;
# Boundary conditions
addBoundaryConditions(initial=[x=0,v=0,sT=0,sB=0],final=[v=0]);
infoBoundaryConditions() ;
addUnilateralConstraint( vsT(zeta) >= 0, vsTpositive );
addUnilateralConstraint( vsB(zeta) >= 0, vsBpositive );
addUnilateralConstraint( vsT(zeta) <= maxT, vsTmax );
addBilateralConstraint( vsT(zeta)-vsB(zeta), vsTBInterval );
setTarget(
  mayer    = -x(zeta_f),
  lagrange = epsiTB*(vsT(zeta)^2+vsB(zeta)^2)
) ;
POST := [
  [sT(zeta)-sB(zeta),"F"],
  [clip(sT(zeta)-sB(zeta),minClip,maxClip),"clipF"]
];
PARAMS := [
  epsiTB  = 0.001,
  tauT    = 0.02,
  tauB    = 0.001,
  maxT    = 2,
  minClip = -1,
  maxClip = 1
];
MESH_PRB := [
  [length=0.1,n=10],
  [length=0.4,n=40],
  [length=0.4,n=40],
  [length=0.1,n=10]
];
generateOCProblem(
  "BangBangFtau",
  post_processing    = POST,
  parameters         = PARAMS,
  controls_iterative = true,
  controls_guess     = [vsT=0,vsB=0],
  mesh               = MESH_PRB
) ;

