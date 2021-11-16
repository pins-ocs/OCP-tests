restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = u(t):
EQ2 := diff(z(t),t) = sqrt(1+u(t)^2):
ode := [EQ||(1..2)]: <%>;
xvars := [x(t),z(t)] ;
uvars := [u(t)] ;
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [ x=a, z=0 ],
  final   = [ x=b ] # z=L must be set least squares in mayer term!
);
infoBoundaryConditions();
setTarget(
  lagrange = x(zeta)*sqrt(1+u(zeta)^2),
  mayer    = (z(zeta_f)-L)^2 # BC z(1) = L
);
PARS := [
  a  = 1,
  b  = 3,
  u0 = b-a,
  L0 = sqrt(1+u0^2),
  L1 = 4,
  L  = L0
];
GUESS := [
  x = a+zeta*(b-a),
  z = zeta*L
];
CONT := [
  [ L = L0*(1-s)+L1*s ]
];
#addUserFunction(x_guess(x));
#Describe(generateOCProblem);
generateOCProblem(
  "HangingChain", clean=true,
  parameters         = PARS,
  mesh               = [ length=1, n=400 ],
  controls_guess     = [ u=2*u0 ],
  controls_iterative = true,
  continuation       = CONT,
  states_guess       = GUESS
);
#res := XOptima:-getOCProblem();
#indices(res);
#eval(res["controls"]);
#gg := subs(u(zeta)=u,
#           x(zeta)=x,
#           lambda1__xo(zeta)=lambda1,
#           lambda2__xo(zeta)=lambda2,
#           res["controls"]["g"][1]);
#solve( sqrt(u^2+1)=z, {u} ) ;
#Dgg := simplify(diff(gg,u));
#RES := solve( gg, {u} );
#simplify(subs(RES[1],Dgg)) assuming x::real, lambda1::real, lambda2::real;
#simplify(subs(RES[2],Dgg)) assuming x::real, lambda1::real, lambda2::real;
;
