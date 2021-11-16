restart: with(plots):;
with(XOptima):;
g1 := u1(zeta)/m1 ;
g2 := u2(zeta)/m3 ;
g3 := u3(zeta)/inertia ;
EQ1    := diff(x(zeta),zeta)     = T*(vx(zeta)*cos(theta(zeta))+vz(zeta)*sin(theta(zeta))):
EQ2    := diff(z(zeta),zeta)     = T*(vz(zeta)*cos(theta(zeta))-vx(zeta)*sin(theta(zeta))):
EQ3    := diff(theta(zeta),zeta) = T*Omega(zeta):
EQ4    := diff(vx(zeta),zeta)    = T*(g1-vz(zeta)*Omega(zeta)*(m3/m1)):
EQ5    := diff(vz(zeta),zeta)    = T*(g2+vx(zeta)*Omega(zeta)*(m1/m3)):
EQ6    := diff(Omega(zeta),zeta) = T*(g3+vx(zeta)*vz(zeta)*(m3-m1)/inertia):
EQNS_T := [ EQ||(1..6) ]: <%> ;
qvars := [x(zeta),z(zeta),theta(zeta),vx(zeta),vz(zeta),Omega(zeta)] ;
cvars := [u1(zeta),u2(zeta),u3(zeta)] ;
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(initial=[x,z,vx,vz,theta],final=[x,z,vx,vz,theta]);
infoBoundaryConditions() ;
addControlBound( u1,
                 scale       = T,
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty) ;
addControlBound( u2,
                 scale       = T,
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty) ;
addControlBound( u3,
                 scale       = T,
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty) ;
setTarget( mayer = T ) ;
pars := [
  inertia      = 0.12,
  epsi_penalty = 0.1,
  epsi_max     = epsi_penalty,
  epsi_min     = 1e-7,
  tol_penalty  = 0.01,
  x_i          = 0,
  x_f          = 2,
  z_i          = 1,
  z_f          = 1,
  vx_i         = 0,
  vx_f         = 0,
  vz_i         = 0,
  vz_f         = 0,
  theta_i      = 0,
  theta_f      = 0,
  m1           = 13.2,
  m3           = 25.6,
  Tguess       = 10
] ;
GUESS := [
  x     = x_i+zeta*(x_f-x_i),
  z     = z_i+zeta*(z_f-z_i),
  theta = 0,
  vx    = (x_f-x_i)/Tguess,
  vz    = sin(zeta*6.28)/Tguess,
  Omega = 0
];
CONTINUATION := [
  # prima continuazione
  [inertia = (1-s)*1.5+s*0.12],
  # seconda continuazione
  [
    epsi = (1-s)*epsi_max+s*epsi_min,
    [u1,"epsilon"] = epsi,
    [u2,"epsilon"] = epsi,
    [u3,"epsilon"] = epsi
  ]
];
generateOCProblem(
  "Underwater",
  #post_processing        = [[T(zeta),"minTime"]],
  parameters              = pars,
  mesh                    = [length=1,n=1000],
  continuation            = CONTINUATION,
  optimization_parameters = [ T = Tguess ],
  states_guess            = GUESS
) ;
;
