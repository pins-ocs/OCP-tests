restart:;
with(XOptima):;
addUserFunction(DD(h,v)=Dc*v^2*exp(hc*(1-h/h_i)));
addUserFunction(gg(h)=g0*(h_i/h)^2);
addUserFunction(explog(s,a,b)=exp((1-s)*log(a)+s*log(b)));
addUserFunction(guess_h(s)=h_i);
addUserFunction(guess_v(s)=s*(1-s));
addUserFunction(guess_m(s)=m_i+s*(m_f-m_i));
EQ1 := diff(h(t),t) = TimeSize * v(t):
EQ2 := diff(v(t),t) = TimeSize * ( ((T(t)-DD(h(t),v(t)))/m(t)) - gg(h(t)) ):
EQ3 := diff(m(t),t) = -TimeSize * T(t)/c:;
EQNS := convert([EQ||(1..3)],Vector);
xvars := [h(t),v(t),m(t)];
uvars := [T(t)];
pars := [ TimeSize ]; # optimization parameters;
loadDynamicSystem(
  equations = EQNS,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(initial=[h,v,m],final=[m]);
infoBoundaryConditions();
setTarget(
  lagrange = WG*( (h(zeta)-guess_h(zeta))^2 + 
                  (v(zeta)-guess_v(zeta))^2 +
                  (m(zeta)-guess_m(zeta))^2 ),
  mayer = -h(zeta_f)
);
addControlBound(
  T,
  min         = 0,
  max         = Tmax,
  controlType = "COS_LOGARITHMIC",
  tolerance   = tol_T_max,
  epsilon     = epsi_T_max
);
addUnilateralConstraint(
  m(zeta) >= 0,
  massPositive,
  tolerance = tol_mass_max,
  epsilon   = epsi_mass_max,
  barrier   = true
);
addUnilateralConstraint(
  v(zeta) >= 0,
  vPositive,
  tolerance = tol_v_max,
  epsilon   = epsi_v_max,
  barrier   = true
);
addUnilateralConstraint(
  TimeSize >=0,
  TSPositive,
  tolerance = tol_TS_max,
  epsilon   = epsi_TS_max,
  barrier   = true
);
PARS := [
  v_i  = 0, #v_f  = 0,
  h_i  = 1, #h_f  = 0,
  m_i  = 1,
  m_f  = mc*m_i,
  g0   = 1,
  Tmax = 3.5*g0*m_i,
  c    = 0.5*sqrt(g0*h_i),

  mc = 0.6,
  hc = 500,
  vc = 620,
  Dc = 0.5*vc*m_i/g0,


  epsi_v_max = 0.01,   tol_v_max = 0.01,
  epsi_v_min = 0.0001, tol_v_min = 1e-4,

  epsi_T_max = 0.01,  tol_T_max = 0.01,
  epsi_T_min = 1e-7,  tol_T_min = 1e-4,

  epsi_TS_max = 0.01,  tol_TS_max = 0.01,
  epsi_TS_min = 1e-10, tol_TS_min = 1e-3,

  epsi_mass_max = 0.01,   tol_mass_max = 0.01,
  epsi_mass_min = 0.0001, tol_mass_min = 0.0001,

  WG     = WG_max,
  WG_max = 1
];
POST := [
  [zeta*TimeSize,"Time"],
  [v(zeta)*TimeSize,"target"]
];
CONT :=[
  [
    WG = (1-s)*WG_max
  ],
  [ [T,"epsilon"]              = explog(s,epsi_T_max,epsi_T_min),
    [T,"tolerance"]            = explog(s,tol_T_max,tol_T_min),
    [TSPositive,"epsilon"]     = explog(s,epsi_TS_max,epsi_TS_min),
    [TSPositive,"tolerance"]   = explog(s,tol_TS_max,tol_TS_min),
    [vPositive,"epsilon"]      = explog(s,epsi_v_max,epsi_v_min),
    [vPositive,"tolerance"]    = explog(s,tol_v_max,tol_v_min),
    [massPositive,"epsilon"]   = explog(s,epsi_mass_max,epsi_mass_min),
    [massPositive,"tolerance"] = explog(s,tol_mass_max,tol_mass_min)
  ]
 ];
GUESS := [
  h = guess_h(zeta),
  v = guess_v(zeta),
  m = guess_m(zeta)
];
MESHP_DEF := [length=1,n=400];
project_dir  := "../generated_code";
project_name := "GoddardRocket";
generateOCProblem(
  project_name,
  post_processing         = POST,
  parameters              = PARS,
  mesh                    = MESHP_DEF,
  continuation            = CONT,
  states_guess            = GUESS,
  optimization_parameters = [ TimeSize = Tmax ]
);
# if used in batch mode use the comment to quit;
