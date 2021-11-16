restart:
with(plots):;
with(XOptima):
interface(rtablesize=20):;
;
eq1    := diff(r(t),t)     = tf*u(t) :
eq2    := diff(u(t),t)     = tf*(v(t)^2/r(t)-mu/r(t)^2+T*sin(theta(t))/m(zeta)):
eq3    := diff(v(t),t)     = tf*(-v(t)*u(t)/r(t) + T*cos(theta(t))/m(zeta)):
eq4    := diff(m(t),t)     = -tf*mdot : # mass consumption
eq5    := diff(alpha(t),t) = tf*(v(t)/r(t)): # angle recostruction
eqns_t := [eq||(1..5)]: <%>;
xvars_t := [m(t),alpha(t),r(t),u(t),v(t)] ;
uvars_t := [theta(t)];
data := [
  mu   = 1,
  r0   = 1,
  m0   = 1,
  T    = 0.1 * m0*mu/r0^2*0.1405,
  mdot = 0.533*T*sqrt(mu/r0),
  v0   = sqrt(mu/r0),
  tf   = 5 * 3.32*sqrt(r0^3/mu)
];
loadDynamicSystem(controls=uvars_t,states=xvars_t,equations=eqns_t);
addBoundaryConditions(
  initial = [m=m0,alpha=0,r=r0,u=0,v=v0],
  final   = [u=0],
  generic = [[v(zeta_f)=sqrt(mu/r(zeta_f)),"v_final"]]
);
infoBoundaryConditions();
setTarget(lagrange=-0*tf*u(zeta),mayer=-r(zeta_f));
#pars := [op(data), tf0=tf] ;
USER_GUESS := [theta=arctan(-lambda2__xo(zeta),-lambda3__xo(zeta))];
STATES_GUESS := [ m=m0, alpha=tf*v0/r0*zeta, r=r0, v=v0, u=0, lambda3__xo=1e-8];
POST := [
  [r(zeta)*cos(alpha(zeta)), "X-pos"],
  [r(zeta)*sin(alpha(zeta)), "Y-pos"],
  [r0*cos(alpha(zeta)),      "X-pos0"],
  [r0*sin(alpha(zeta)),      "Y-pos0"]
];
generateOCProblem(
  "OrbitTransfer",
  parameters        = data,
  post_processing   = POST,
  admissible_region = [m(zeta)>0,r(zeta)>0],
  mesh              = [ [length=1, n=1000]],
  controls_guess    = USER_GUESS,
  states_guess      = STATES_GUESS
);
#OCP := getOCProblem() ;
#eval(OCP);
;
