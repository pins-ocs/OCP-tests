restart:;
with(XOptima):;
EQ1  := diff(x(zeta),zeta)  = T*(vx(zeta) + velX(x(zeta),y(zeta))):
EQ2  := diff(y(zeta),zeta)  = T*(vy(zeta) + velY(x(zeta),y(zeta))):
EQ3  := diff(vx(zeta),zeta) = T*(S*cos(u(zeta))):
EQ4  := diff(vy(zeta),zeta) = T*(S*sin(u(zeta))):
EQNS := convert([EQ||(1..4)],Vector);
xvars := map([x,y,vx,vy],(zeta));
uvars := [u(zeta)];
addUserFunction(velX(x,y)=-y);
addUserFunction(velY(x,y)=x);
addUserFunction(arctan2(y,x),derivatives=0) ; # definita un codice utente;
loadDynamicSystem(equations=EQNS,controls=uvars,states=xvars);
addBoundaryConditions(
  initial=[x,y,vx,vy],
  final=[
    x  = WG*x_guess(1)+(1-WG)*x_f,
    y  = WG*y_guess(1)+(1-WG)*y_f,
    vx = WG*vx_guess(1)+(1-WG)*vx_f,
    vy = WG*vy_guess(1)+(1-WG)*vy_f
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = T+WG*(T/Tguess-1)^2,
  lagrange = WG * T * ( 
     (x(zeta)-x_guess(zeta))^2 + 
     (y(zeta)-y_guess(zeta))^2 +
     (vx(zeta)-vx_guess(zeta))^2 + 
     (vy(zeta)-vy_guess(zeta))^2
  )
);
addUnilateralConstraint( T>=0, Tpositive, barrier=true );
CONTROL_GUESS := [ u = arctan2(-mu4__xo(zeta), -mu3__xo(zeta)) ];
addUserFunction(x_guess(zeta)=x_i+zeta*Tguess*vx_i);
addUserFunction(y_guess(zeta)=y_i+zeta*Tguess*vy_i);
addUserFunction(vx_guess(zeta)=vx_i);
addUserFunction(vy_guess(zeta)=vy_i);
GUESS := [
  x           = x_guess(zeta),
  y           = y_guess(zeta),
  vx          = vx_guess(zeta),
  vy          = vy_guess(zeta),
  lambda3__xo = 1
];
PARS := [
  S      = 50,
  x_i    = 0,
  y_i    = 0,
  vx_i   = 0,
  vy_i   = 0,
  x_f    = 0, # only for guess
  y_f    = 5,
  vx_f   = 45,
  vy_f   = 0,
  Tguess = 1,
  WG0    = 1,
  WG     = WG0
];
CONT := [
  [ WG = (1-s)*WG0 ]
];
project_dir  := "../generated_code";
project_name := "Zermelo";
generateOCProblem(
  project_name,
  integral_post_processing = [[zeta*T,"Time"]],
  optimization_parameters  = [ T = Tguess],
  parameters               = PARS,
  continuation             = CONT,
  mesh                     = [ length=1, n=1000 ],
  controls_guess           = CONTROL_GUESS,
  states_guess             = GUESS
);
# if used in batch mode use the comment to quit;
