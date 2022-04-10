restart:;
with(XOptima):;
addUserFunction(DD(h,v)=Dc*v^2*exp(hc*(1-h/h_i)));
addUserFunction(gg(h)=g0*(h_i/h)^2);
addUserFunction(explog(s,a,b)=exp((1-s)*log(a)+s*log(b)));
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
setTarget( lagrange = 0, mayer = -h(zeta_f) );
addControlBound(
  T,
  min         = 0,
  max         = Tmax,
  controlType = "COS_LOGARITHMIC",
  tolerance   = tol_T,
  epsilon     = epsi_T
);
addUnilateralConstraint(
  m(zeta) >= 0,
  massPositive,
  tolerance = tol_mass,
  epsilon   = epsi_mass,
  barrier   = true
);
addUnilateralConstraint(
  v(zeta)>=0,
  vPositive,
  tolerance = tol_v,
  epsilon   = epsi_v,
  barrier   = true
);
addUnilateralConstraint(
  TimeSize >=0,
  TSPositive,
  tolerance = tol_TS,
  epsilon   = epsi_TS,
  barrier   = true
);
PARS := [
  v_i        = 0, #v_f  = 0,
  h_i        = 1, #h_f  = 0,
  m_i        = 1,
  m_f        = mc*m_i,
  g0         = 1,
  Tmax       = 3.5*g0*m_i,
  c          = 0.5*sqrt(g0*h_i),

  mc         = 0.6,
  hc         = 500,
  vc         = 620,
  Dc         = 0.5*vc*m_i/g0,


  epsi_v_min = 0.0001,     tol_v_min = 1e-4,
  epsi_v_max = 0.1,        tol_v_max = 0.01,
  epsi_v     = epsi_v_max, tol_v     = tol_v_max,

  epsi_T_max = 0.1,        tol_T_max = 0.01,
  epsi_T_min = 1e-7,       tol_T_min = 1e-4,
  epsi_T     = epsi_T_max, tol_T     = tol_T_max,

  epsi_TS_min = 1e-10,       tol_TS_min = 1e-3,
  epsi_TS_max = 0.025,       tol_TS_max = 0.0001,

  epsi_TS     = epsi_TS_max, tol_TS     = tol_TS_max,

  epsi_mass_max = 0.025,         tol_mass_max = 0.01,

  epsi_mass_min = 0.0001,        tol_mass_min = 0.0001,
  epsi_mass     = epsi_mass_max, tol_mass     = tol_mass_max,

  #epsi_h_max   = 0.025,          tol_h_max  = 0.01,
  #epsi_h_min   = 0.0001,         tol_h_min  = 0.0001,
  #epsi_h       = epsi_h_max,     tol_h      = tol_h_max,

  tf         = 1
];
POST := [
  [zeta*TimeSize,"Time"],
  [v(zeta)*TimeSize,"target"]
];
CONT :=[
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
  h = h_i,
  v = zeta*(1-zeta),
  m = m_i+zeta*(m_f-m_i)
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
