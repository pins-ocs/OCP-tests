restart:;
with(XOptima):;
EQ1 := diff(x1(zeta),zeta) = u(zeta)*Q(x1(zeta),x2(zeta))*T(zeta):
EQ2 := diff(x2(zeta),zeta) = (1-u(zeta))*Q(x1(zeta),x2(zeta))*T(zeta):
EQ3 := diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ||(1..3) ] : <%> ;
qvars := [x1(zeta),x2(zeta),T(zeta)] ;
cvars := [u(zeta)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addUserFunction( Q(x,y)=x*y );
addUserFunction( x1L(t)=x1_i*exp(x2_i*t) );
addUserFunction( x2L(t)=x2_i );
addUserFunction( l1L(t)=l1_i*exp(-x2_i*t) );
addUserFunction( l2L(t)=l2_i-x1_i*l1_i*t );
addUserFunction( x1R(t)=x2_i/(1+x2_i*(t0-t)/2));
addUserFunction( x2R(t)=x1R(t) );
addUserFunction( l1R(t)=l1L(t0)*(x2_i*(t-t0)/2-1)^2);
addUserFunction( l2R(t)=l1R(t) );
addBoundaryConditions(
  initial = [x1,x2],
  generic = [[Q(x1(zeta_f),x2(zeta_f))=Qc,"final"]]
);
setStatusBoundaryConditions(generic=["final"]);
infoBoundaryConditions() ;
addControlBound(
  u, 
  controlType="U_COS_LOGARITHMIC",
  min=0, max=1,
  epsilon   = u_epsi,
  tolerance = u_tol,
  scale     = T(zeta)
);
addUnilateralConstraint( T(zeta)>=0, Tpositive ) ;
setTarget( mayer = T(zeta_f) );
PARS := [
  x1_i    = 1,
  x2_i    = 2,
  Qc      = 10,
  l1_i    = -1/(x1_i*x2_i),
  l2_i    = l1_i*(x1_i*t0+exp(-t0*x2_i)),
  t0      = -log(x1_i/x2_i)/x2_i,
  u_epsi  = u_epsi0,
  u_tol   = u_tol0,
  u_epsi0 = 0.1,
  u_tol0  = 0.1,
  u_epsi1 = 1e-8,
  u_tol1  = 1e-3
]:<%>;
POST := [
  [piecewise( zeta*T(zeta) < t0, x1L(zeta*T(zeta)), x1R(zeta*T(zeta))), "X1-exact"],
  [piecewise( zeta*T(zeta) < t0, x2L(zeta*T(zeta)), x2R(zeta*T(zeta))), "X2-exact"],
  [piecewise( zeta*T(zeta) < t0, l1L(zeta*T(zeta)), l1R(zeta*T(zeta))), "L1-exact"],
  [piecewise( zeta*T(zeta) < t0, l2L(zeta*T(zeta)), l2R(zeta*T(zeta))), "L2-exact"],
  [piecewise( zeta*T(zeta) < t0, 1, 0.5), "U-exact"]
];
CONT := [
  [
    [uControl,"epsilon"]   = u_epsi0*(1-s)+u_epsi1*s,
    [uControl,"tolerance"] = u_tol0*(1-s)+u_tol1*s
  ]
];
generateOCProblem(
  "EconomicGrowthModel",
  post_processing = POST,
  parameters      = PARS,
  mesh            = [ length=1, n=1000 ],
  continuation    = CONT,
  states_guess    = [ T=1, x1=x1_i, x2=x2_i ]
);
;
