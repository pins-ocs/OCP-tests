restart:;
with(XOptima):;
EQ1 := diff(x(t),t) = u(t):
EQ2 := diff(z(t),t) = sqrt(1+u(t)^2):
ode := [EQ||(1..2)]: <%>;
xvars := [x(t),z(t)];
uvars := [u(t)];
loadDynamicSystem(
  equations = ode,
  controls  = uvars,
  states    = xvars
);
addUserFunction( x_guess(s) = (a+b)/2+WG*s*(s-1)*L );
addBoundaryConditions(
  initial = [ x=a, z=0 ],
  final   = [ x=b, z=L ]
);
infoBoundaryConditions();
setTarget(
  lagrange = W*x(zeta)*sqrt(1+u(zeta)^2)+
            (1-W)*((x(zeta)-x_guess(zeta))^2) +
            epsilon*u(zeta)^2,
  mayer    = 0
);
PARS := [
  a  = 1,
  b  = 3,
  L  = 4,
  WG = 4,
  W  = W0,
  W0 = 0,
  W1 = 1,
  epsilon = 1e-8
];
GUESS := [
  x = x_guess(zeta),
  z = zeta*L
];
CONT := [
  [ W = W0*(1-s) + W1*s ]
];
#addUserFunction(x_guess(x));
#Describe(generateOCProblem);
project_dir  := "../generated_code";
project_name := "HangingChain";
generateOCProblem(
  project_name, clean=true,
  parameters         = PARS,
  mesh               = [ length=1, n=40 ],
  controls_guess     = [ u=0 ],
  controls_iterative = true,
  continuation       = CONT,
  states_guess       = GUESS
);
res := XOptima:-getOCProblem();
indices(res);
eval(res["controls"]);
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
# if used in batch mode use the comment to quit;
