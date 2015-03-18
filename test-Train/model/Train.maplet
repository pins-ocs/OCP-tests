# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Train model
# Authors: E. Bertolazzi
# Date:
# 
# 
# Load Packages
# 
# Load maple packages
restart: with(plots):
with(XOptima):
#`diff/h`   := proc() h_1(args[1])*diff(args[1],args[2]) end:
#`diff/h_1` := proc() h_2(args[1])*diff(args[1],args[2]) end:
with(plots):
# Dynamic system equations
ODE1 := diff(x(t),t)=v(t);
ACC := h(x(t))-(alpha+beta*v(t)+gm*v(t)^2) + ua(t) - ub(t);
ODE2 := diff(v(t),t)=ACC;
# List of states and controls
uvars := [ua(zeta),ub(zeta)] ;
xvars := [x(zeta), v(zeta)] ;
ode   := subs(t=zeta,Vector([ODE1,ODE2]));
# Optimal Contol Problem
Describe(loadDynamicSystem) ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addUserFunction(h(x)) ;
addBoundaryConditions(initial=[x,v],final=[x,v]);
setStatusBoundaryConditions(initial=[x,v],final=[x,v]);
infoBoundaryConditions() ;
# penalty che dipendono dagli ingressi
addControlBound( ua, controlType="U_COS_LOGARITHMIC", min=0, max=uaMax, 
                 epsilon =epsi_max, tolerance = tol_max ) ;
addControlBound( ub, controlType="U_COS_LOGARITHMIC", min=0, max=ubMax,
                 epsilon =epsi_max, tolerance = tol_max ) ;
# Penalty description
#addPenaltyGT( v(zeta), positiveVelocity ):
setTarget( lagrange = ua(zeta)*v(zeta) ) ;
Describe(generateOCProblem) ;
addModelExtraParameters([epsi_max,epsi_min,tol_max,tol_min]) ;
generateOCProblem( "Train",
                    post_processing = [[uaControl(uvars[1],0, uaMax),"uaControl"],
                                       [ubControl(uvars[2],0, ubMax),"ubControl"],
                                       [h(x(zeta)),"Profile"]],
                    parameters = [ x_i   = 0,
                                   x_f   = 6,
                                   v_i   = 0,
                                   v_f   = 0,
                                   alpha = 0.3,
                                   beta  = 0.14,
                                   gm    = 0.16,
                                   uaMax = 10,
                                   uaMin = 0,
                                   ubMax = 2,
                                   ubMin = 0,
                                   epsi_max = 0.01, epsi_min = 0.0001,
                                   tol_max = 0.01,  tol_min = 0.001],
                    states_guess = [x=x_i+(x_f-x_i)*zeta/4.8,v=1],
                    continuation = [ [ [ua,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
                                       [ub,"epsilon"]   = epsi_max*(1-s) + epsi_min*s,
                                       [ua,"tolerance"] = tol_max*(1-s) + tol_min*s,
                                       [ub,"tolerance"] = tol_max*(1-s) + tol_min*s ] ],
                            mesh = [ [length=0.25, n=25],
                                     [length=0.75, n=3000],
                                     [length=3.8,  n=100]], clean=false) ;


# 
