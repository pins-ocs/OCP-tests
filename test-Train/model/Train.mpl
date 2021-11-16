restart: with(plots):;
with(XOptima):;
#`diff/h`   := proc() h_1(args[1])*diff(args[1],args[2]) end:;
#`diff/h_1` := proc() h_2(args[1])*diff(args[1],args[2]) end:;
with(plots):;
ODE1 := diff(x(t),t)=v(t);
ACC := acc(x(t),v(t)) ; # h(x(t))-(alpha+beta*v(t)+gm*v(t)^2);
ODE2 := diff(v(t),t)=ACC + ua(t) - ub(t);
uvars := [ua(zeta),ub(zeta)] ;
xvars := [x(zeta), v(zeta)] ;
ode   := subs(t=zeta,Vector([ODE1,ODE2]));
#Describe(loadDynamicSystem) ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addUserFunction(acc(x,v)=h(x)-(alpha+beta*v+gm*v^2));#,["pippo",2,3]) ;
addUserFunction(h(x)) ;
addBoundaryConditions(initial=[x,v],final=[x,v]);
setStatusBoundaryConditions(initial=[x,v],final=[x,v]);
infoBoundaryConditions() ;
addControlBound( ua, controlType="U_COS_LOGARITHMIC", min=0, max=uaMax, 
                 epsilon =epsi_max, tolerance = tol_max ) ;
addControlBound( ub, controlType="U_COS_LOGARITHMIC", min=0, max=ubMax,
                 epsilon =epsi_max, tolerance = tol_max ) ;
#addPenaltyGT( v(zeta), positiveVelocity ):;
setTarget( lagrange = ua(zeta)*v(zeta) ) ;
#Describe(generateOCProblem) ;
POST := [
  [uaControl(uvars[1],0, uaMax),"uaControl"],
  [ubControl(uvars[2],0, ubMax),"ubControl"],
  [h(x(zeta)),"Profile"]
];
PARS := [
  x_i   = 0,
  x_f   = 6,
  v_i   = 0,
  v_f   = 0,
  alpha = 0.3,
  beta  = 0.14,
  gm    = 0.16,
  uaMax = 10,
  ubMax = 2,
  epsi_max = 0.01, epsi_min = 0.0001,
  tol_max = 0.01,  tol_min = 0.001
];
UGUESS := [ua = uaMax/2, ub = ubMax/2 ];
GUESS := [x=x_i+(x_f-x_i)*zeta/4.8,v=1];
CONT :=[
  [ [ua,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
    [ub,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
    [ua,"tolerance"] = tol_max*(1-s) + tol_min*s,
    [ub,"tolerance"] = tol_max*(1-s) + tol_min*s ] ];
generateOCProblem(
  "Train",
   post_processing = POST,
   parameters      = PARS,
   controls_guess  = UGUESS, # uncomment to force iterative control computation
   states_guess    = GUESS,
   continuation    = CONT,
   mesh = [ [length=0.25, n=25],
            [length=0.75, n=3000],
            [length=3.8,  n=100]],
   clean=true
);
#Describe(generateOCProblem);
