restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    :=  diff(x(t),t) = y(t) :
EQ2    :=  diff(y(t),t) = z(t) :
EQ3    :=  diff(z(t),t) = u(t) :
EQNS_T := [ EQ1, EQ2, EQ3 ] : <%> ;
qvars := [x(t),y(t),z(t)] ;
cvars := [u(t)] ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x,y,z]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsi,
  tolerance   = u_tol,
  scale       =(x(zeta)^2+epsilon_X)
);
setTarget( lagrange = x(zeta)^2 ) ;
PARS := [
  u_epsi     = 0.01,
  u_tol      = 0.01,
  epsilon_X  = 1e-7,
  min_u_epsi = 1e-7,
  x_i        = 1,
  y_i        = 0,
  z_i        = 0,
  Tf         = 6
];
CONT := [
  [[u,"epsilon"]=u_epsi*(1-s)+s*min_u_epsi]
];
generateOCProblem(
  "SingularLuus04",
  integral_post_processing = [[x(zeta)^2,"intTarget"]],
  parameters   = PARS,
  continuation = CONT,
  mesh         = [ length=Tf, n=2000 ],
  states_guess = [ x=x_i, y=y_i, z=z_i ]
);
;
