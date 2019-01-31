
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: Goddard Rocket (from COPS3 test 10)
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Inizializzazione
restart:
with(XOptima):
# Dynamic system equations
addUserFunction(DD(h,v)=Dc*v^2*exp(hc*(1-h/h_i)));addUserFunction(gg(h)=g0*(h_i/h)^2);
EQ1 := diff(h(t),t) = TimeSize * v(t) ;
EQ2 := diff(v(t),t) = TimeSize * ( ((T(t)-DD(h(t),v(t)))/m(t)) - gg(h(t)) ) ;
EQ3 := diff(m(t),t) = -TimeSize * T(t)/c ;
EQNS := convert([EQ||(1..3)],Vector) ;
# States and Controls
xvars := [h(t),v(t),m(t)];
uvars := [T(t)];
pars := [ TimeSize ];
# Optimal Contol Problem
loadDynamicSystem(  equations  = EQNS,  controls   = uvars,  states     = xvars,  parameters = pars);
addBoundaryConditions(initial=[h,v,m],final=[m]);
infoBoundaryConditions() ;
addUnilateralConstraint(  m(zeta) >= 0,  massPositive,  tolerance = tol_mass,  epsilon   = epsi_mass,  barrier   = true);
addUnilateralConstraint(  v(zeta)>=0,  vPositive,  tolerance = tol_v,  epsilon   = epsi_v);
#addUnilateralConstraint(#  h(zeta) >= h_i,#  hPositive,#  tolerance = tol_h,#  epsilon   = epsi_h#);
addUnilateralConstraint(  TimeSize >=0,  TSPositive,  tolerance = tol_TS,  epsilon   = epsi_TS,  barrier   = true);
# penalty che dipendono dagli ingressi
addControlBound(  T,  min       = 0,  max       = Tmax,  tolerance = tol_T,  epsilon   = epsi_T);
setTarget( lagrange = 0, mayer = -h(zeta_f) );
POST := [[zeta*TimeSize,"Time"],[v(zeta)*TimeSize,"target"]] ;
PARS := [  v_i        = 0, #v_f  = 0,
  h_i        = 1, #h_f  = 0,
  m_i        = 1,
  m_f        = mc*m_i,
  g0         = 1,
  Tmax       = 3.5*g0*m_i,
  c          = 0.5*sqrt(g0*h_i),
  mc         = 0.6,  hc         = 500,  vc         = 620,  Dc         = 0.5*vc*m_i/g0,  tol_v      = 0.01,
  epsi_v     = 0.01,
  tol_T      = 0.01,
  epsi_T     = 0.01,
  tol_Tmin   = 1e-4,
  epsi_Tmin  = 1e-7,
  tol_mass   = 0.01,
  epsi_mass  = 0.01,
  tol_h      = 0.01,
  epsi_h     = 0.01,
  tol_TS     = 0.01,
  epsi_TS    = 0.01,
  tol_TSmin  = 1e-3,
  epsi_TSmin = 1e-10,
  tf         = 1];
GUESS := [  h = h_i,  v = zeta*(1-zeta),  m = m_i+zeta*(m_f-m_i)];
addUserFunction(explog(s,a,b)=exp((1-s)*log(a)+s*log(b)));
CONT :=[
  [ [T,"epsilon"]   = explog(s,epsi_T,epsi_Tmin),
    [T,"tolerance"] = explog(s,tol_T,tol_Tmin),    [TSPositive,"epsilon"]   = explog(s,epsi_TS,epsi_TSmin),
    [TSPositive,"tolerance"] = explog(s,tol_TS,tol_TSmin) ] ];
generateOCProblem(  "GoddardRocket",
  post_processing   = POST,
  parameters        = PARS,
  mesh              = [length=1, n=1000],
  continuation      = CONT,  states_guess      = GUESS,  parameters_guess  = [ TimeSize = Tmax ]);

