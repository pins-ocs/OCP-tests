restart:
with(plots):;
with(XOptima):;
g1 := u1(zeta)/m1;
g2 := u2(zeta)/m3;
g3 := u3(zeta)/inertia;
EQ1    := diff(x(zeta),zeta)     = T*(vx(zeta)*cos(theta(zeta))+vz(zeta)*sin(theta(zeta))):
EQ2    := diff(z(zeta),zeta)     = T*(vz(zeta)*cos(theta(zeta))-vx(zeta)*sin(theta(zeta))):
EQ3    := diff(theta(zeta),zeta) = T*Omega(zeta):
EQ4    := diff(vx(zeta),zeta)    = T*(g1-vz(zeta)*Omega(zeta)*(m3/m1)):
EQ5    := diff(vz(zeta),zeta)    = T*(g2+vx(zeta)*Omega(zeta)*(m1/m3)):
EQ6    := diff(Omega(zeta),zeta) = T*(g3+vx(zeta)*vz(zeta)*(m3-m1)/inertia):
EQNS_T := [ EQ||(1..6) ]: <%> ;
qvars := map( [x,z,theta,vx,vz,Omega], (zeta) );
cvars := map( [u1,u2,u3], (zeta) );
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
addBoundaryConditions(
  initial = [x,z,vx,vz,theta,Omega],
  final   = [x,z,vx,vz,theta,Omega]
);
infoBoundaryConditions();
CTYPE := "{CTRL_TYPE}";
SCALE := T;
addControlBound(
  u1,
  scale       = SCALE,
  controlType = CTYPE,
  maxabs      = 1,
  epsilon     = epsi_max,
  tolerance   = tol_max
);
addControlBound(
  u2,
  scale       = SCALE,
  controlType = CTYPE,
  maxabs      = 1,
  epsilon     = epsi_max,
  tolerance   = tol_max
);
addControlBound(
  u3,
  scale       = SCALE,
  controlType = CTYPE,
  maxabs      = 1,
  epsilon     = epsi_max,
  tolerance   = tol_max
);
setTarget( mayer = T );
pars := [
  inertia = 0.12,

  epsi_max = 0.1,
  epsi_min = 1e-7,


  tol_max = 0.1,
  tol_min = 0.001,


  x_i     = 0,
  x_f     = 2,
  z_i     = 1,
  z_f     = 1,
  vx_i    = 0,
  vx_f    = 0,
  vz_i    = 0,
  vz_f    = 0,
  theta_i = 0,
  theta_f = 0,
  Omega_i = 0,
  Omega_f = 0,
  m1      = 13.2,
  m3      = 25.6,
  Tguess  = 10
] ;
GUESS := [
  x     = x_i+zeta*(x_f-x_i),
  z     = z_i+zeta*(z_f-z_i),
  theta = 0,
  vx    = (x_f-x_i)/Tguess,
  vz    = sin(zeta*6.28)/Tguess,
  Omega = 0
];
UGUESS := [
  u1 = 0,
  u2 = 0,
  u3 = 0
];
CONTINUATION := [
  [
    epsi = (1-s)*epsi_max + s*epsi_min,
    tol  = (1-s)*tol_max + s*tol_min,
    [u1,"epsilon"]   = epsi,
    [u2,"epsilon"]   = epsi,
    [u3,"epsilon"]   = epsi,
    [u1,"tolerance"] = tol,
    [u2,"tolerance"] = tol,
    [u3,"tolerance"] = tol
  ]
];
PREFIX := [
  "CTRL_TYPE = 'COS_LOGARITHMIC'"
];
project_dir  := "../generated_code";
project_name := "Underwater";
generateOCProblem(
  project_name,
  #post_processing        = [[T(zeta),"minTime"]],
  parameters              = pars,
  mesh                    = [length=1,n=1000],
  continuation            = CONTINUATION,
  optimization_parameters = [ T = Tguess ],
  states_guess            = GUESS,
  controls_guess          = UGUESS,
  data_file_header        = PREFIX
) ;
# if used in batch mode use the comment to quit;
