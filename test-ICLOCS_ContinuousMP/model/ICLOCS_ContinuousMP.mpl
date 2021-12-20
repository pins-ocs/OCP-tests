restart:;
with(XOptima):;
NSEG := 20;
for k from 1 to NSEG do
  EQXX||k := diff(x||k(t),t) = y||k(t):
  EQYY||k := diff(y||k(t),t) = sin(x||k(t))+u||k:

  EQX||k := diff(xx||k(t),t) = 1.2*yy||k(t)+0.1*sin(t+k-1):
  EQY||k := diff(yy||k(t),t) = 0.2*sin(xx||k(t))+u||k:

  print(<EQXX||k,EQYY||k,EQX||k,EQY||k>);
od:
EQNS_T := [ EQXX||(1..NSEG),
            EQYY||(1..NSEG),
            EQX||(1..NSEG),
            EQY||(1..NSEG) ]:;
qvars := map([x||(1..NSEG),
              y||(1..NSEG),
              xx||(1..NSEG),
              yy||(1..NSEG)],(t));
cvars := [];
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
):;
addBoundaryConditions(
  initial = [xx1=1,yy1=1],
  generic = [
    # trajectory continuity

    seq( [ xx||k(zeta_f)-xx||(k+1)(zeta_i),
           cat("X",k,"_continuity") ],
           k=1..NSEG-1),

    seq( [ yy||k(zeta_f)-yy||(k+1)(zeta_i),
           cat("Y",k,"_continuity") ],
           k=1..NSEG-1),

    #----------------------------------


    seq( [ x||k(zeta_i)-xx||k(zeta_i),
           cat("X",k,"_initial") ],
           k=1..NSEG),

    seq( [ y||k(zeta_i)-yy||k(zeta_i),
           cat("Y",k,"_initial") ],
           k=1..NSEG)
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = add( (NSEG-k+1)* ( x||k(zeta)^2 +
                                y||k(zeta)^2 +
                                0*u||k(zeta)^2 ), k=1..NSEG)
);
;
for k from 1 to NSEG do
  addBilateralConstraint(
    u||k,
    u||k||Limitation,
    min       = -10,
    max       =  10,
    epsilon   =  epsi_ctrl,
    tolerance =  tol_ctrl,
    scale     = 1,
    barrier   = true
  );
od:;
for k from 1 to NSEG do
  addBilateralConstraint(
    xx||k(zeta),
    xx||k||Limitation,
    min       = -xy_bound,
    max       = xy_bound,
    epsilon   = xy_eps,
    tolerance = xy_tol,
    scale     = 1,
    barrier   = true
  );
  addBilateralConstraint(
    yy||k(zeta),
    yy||k||Limitation,
    min       = -xy_bound,
    max       = xy_bound,
    epsilon   = xy_eps,
    tolerance = xy_tol,
    scale     = 1,
    barrier   = true
  );
od:;
PARS := [
  xy_tol0   = 0.1,
  xy_tol1   = 0.001,
  xy_tol    = xy_tol0,
  xy_eps0   = 0.1,
  xy_eps1   = 0.001,
  xy_eps    = xy_eps0,
  xy_bound  = 2,
  epsi_ctrl = 0.01,
  tol_ctrl  = 0.01
];
POST := [];
CONT := [
  [
    seq(
      op([
      [cat(xx,k,Limitation),"epsilon"]   = xy_eps0+s*(xy_eps1-xy_eps0), 

      [cat(yy,k,Limitation),"epsilon"]   = xy_eps0+s*(xy_eps1-xy_eps0), 
      [cat(xx,k,Limitation),"tolerance"] = xy_tol0+s*(xy_tol1-xy_tol0),

      [cat(yy,k,Limitation),"tolerance"] = xy_tol0+s*(xy_tol1-xy_tol0)
      ]),
      k=1..NSEG
    )
  ]
]:;
GUESS := [ seq( x||k = 1, k=1..NSEG), seq( y||k = 1, k=1..10) ];
PGUESS := [ seq( u||k = 0, k=1..NSEG) ];
MESHP_DEF := [length=1, n=50];
project_dir  := "../generated_code";
project_name := "ICLOCS_ContinuousMP";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESHP_DEF,
  states_guess    = GUESS,
  optimization_parameters = PGUESS
);
# if used in batch mode use the comment to quit;
