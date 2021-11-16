restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1 := diff(phi(t),t) - omega(t) :
EQ2 := Ix*diff(omega(t),t) - m*g*h*phi(t) + h*Fy(t):
ode := <EQ||(1..2)>;
qvars := [omega(t),phi(t)] ;
cvars := [Fy(t)] ;
#Describe(freeTime);
eqns_S, vars_S, ctrl_S := freeTime( ode, qvars, cvars, "lin") ;
#infoRegisteredObjects() ;
loadDynamicSystem(equations=eqns_S,controls=ctrl_S,states=vars_S) ;
addBoundaryConditions(initial=[omega,phi],final=[omega,phi]);
infoBoundaryConditions() ;
addControlBound( Fy, controlType="U_COS_LOGARITHMIC", maxabs=Fmax, scale=TimeSize(zeta) ) ;
addUnilateralConstraint( TimeSize(zeta) >= 0, minimumTimeSize,scale=1);
#addPostProcess(exp(logTimeSize(zeta)),"minTime");
#addPostProcess(exp(logTimeSize(zeta))*sqrt(m*g*h/Ix),"Talpha");
setTarget( mayer = TimeSize(zeta_f) ) ;
PARS := [
  omega_i = 0,
  phi_i   = 0,
  omega_f = 0,
  phi_f   = evalf(Pi/18),
  Ix      = 40,
  g       = 9.81,
  h       = 0.6,
  mu      = 1,
  Fmax    = m*g*mu,
  m       = 250
];
MESH0 := [
  [length=0.1,n=10],
  [length=0.4,n=40],
  [length=0.4,n=40],
  [length=0.1,n=10]
];
POST := [
  [TimeSize(zeta),"minTime"],
  [TimeSize(zeta)*sqrt(m*g*h/Ix),"Talpha"]
];
generateOCProblem(
  "BikeSteering",
  post_processing = POST,
  parameters      = PARS,
  mesh            = MESH0,
  states_guess    = [TimeSize = 1]
);
;
