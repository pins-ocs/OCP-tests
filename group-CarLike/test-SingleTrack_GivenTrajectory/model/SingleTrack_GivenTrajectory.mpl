
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Minimum time problem for single track with given trajectory
# Author: Francesco Biral
# Date:        13/07/2016
# 
# Optimal control with road and fixed space (free time)
# Solve the minimum time problem (free time) given a reference trajecory  constraining the deviation from it. 
# Vehicle is a single track model with tyre ellipse of adherence.  Vehicle power is constrained. 
# Longitudinal force is split between front and rear and traction is applied to rear only.
# The reference trajectory is given  functions are mapped to methods of Mechatronics library C++ road class. 
# What you can learn from this tutorial?
# 1. Change of coordinate: from time domain to space domain (curvlinear path)
# 2. Define mesh and reference trajectory  using a set o points (path coordinate,curvature) that is transformed into a spline associated to a mesh. 
#      This is done mapping the curvature to  methods of C++ Trajecory2D class which is a mesh class. Input data file is also shown.
#      The same can be achived using the dataSet class which is a  mesh class. 
# 3. how to setup continuation on a parameter.
# 4. map functions with regularized mathematical functions coded in Mechatronix library.
# 5. define state and control constraints of various types
# 6. define post processing espressions for output
# OC problem setup
# Load maple packages
restart:
with(plots):
with(XOptima):
interface(rtablesize=20):
# Dynamic system
# Vehicle data
vehicle_data := [Lf = 1.3, Lr = 1.5, h = .5, 
                 m = 2100, Izz = 3900, 
                 sigma__yr = .3, sigma__yf = .3, 
                 kv = 0, g = 9.82];
# Linear Slip definition
# #attention: minus sign goes in force model
eqns_slips := [alpha__r(t) = (v(t)-Omega(t)*Lr)/u(t), 
               alpha__f(t) = (Lf*Omega(t)+v(t))/u(t)-delta(t)]: <%>;
# Vertical loads with Load transfer
eq_loads:= [fzr(t) = (1/2)*Lf*m*g/(Lf+Lr)+S(t)/(Lf+Lr)*h, 
            fzf(t) = (1/2)*Lr*m*g/(Lf+Lr)-S(t)/(Lf+Lr)*h]: <%>;
# static loads
eq_loads_static := [fzr(t) = (1/2)*Lf*m*g/(Lf+Lr), fzf(t) = (1/2)*Lr*m*g/(Lf+Lr)]: <%>;
# Power 
veh_power := fxr(t)*u(t); 
# Linear model of tyre.
# Lonbgitudinbal force is split beween positive and negative part. Negative part (braking) is split between rear and front via kS ratio and positive part is applied only to rear axle.
# negPart(.) and posPart(.) are mapped to regularized functions available from mechatronics.
tyre_model_LIN := 
 [fxr(t)= negPart(S(t))*kS+posPart(S(t)),
  fyr(t)=-KYr*alpha__r(t)*fzr(t),
  fxf(t)= negPart(S(t))*(1-kS),
  fyf(t)=-KYf*alpha__f(t)*fzf(t)]:
# Single track model without wheel dynamics but with slip dynamics
STk_eqns := [
  (-Omega(t)*v(t)+diff(u(t), t))*m+kv*u(t)^2-2*cos(delta(t))*fxf(t)+2*sin(delta(t))*fyf(t)-2*fxr(t), 
  (Omega(t)*u(t)+diff(v(t), t))*m-2*sin(delta(t))*fxf(t)-2*cos(delta(t))*fyf(t)-2*fyr(t), 
  (-2*sin(delta(t))*fxf(t)-2*cos(delta(t))*fyf(t))*Lf+Izz*(diff(Omega(t), t))+2*Lr*fyr(t), 
   sigma__yr*(diff(alpha__r(t), t))+u(t)*(alpha__r(t)-subs(eqns_slips,alpha__r(t))), 
   sigma__yf*(diff(alpha__f(t), t))+u(t)*(alpha__f(t)-subs(eqns_slips,alpha__f(t)))]: <%>;
# Substitute tyre model functions in vehicle dynamic model
STk_eqns := subs( tyre_model_LIN, eq_loads, STk_eqns ): <%>;
# 
# Curvilinear coordinates
eqns_curv_coord := [diff(s(t),t)*(1-Curv(s(t))*n(t))=cos(xi(t))*u(t)-sin(xi(t))*v(t),
                    diff(n(t),t)=sin(xi(t))*u(t)+cos(xi(t))*v(t),
                    Omega(t)-diff(xi(t),t)= Curv(s(t))*diff(s(t),t)]: <%>;

sol_vs := solve(eqns_curv_coord[1],{diff(s(t),t)});

# Equations of motion of dynamical system. An additional equation has been added to each control in order to limit the control rate of change. Therfore the new controls are the rate of change of longitudinal force (related to longitudinal jerk) and steering angel rate of change (related to lateral jerk) 
eqns_t := [op(eqns_curv_coord[1..3]),
           op(STk_eqns), #kv is normalized with mass
           diff(delta(t),t)-v__delta(t), 
           diff(S(t),t)-vS(t)]:  
          <%>;

#Describe(changeOfIndependentVariable);
xvars_t := [s(t), n(t), xi(t), u(t), v(t), Omega(t), alpha__r(t), alpha__f(t), delta(t), S(t)];
uvars_t := [v__delta(t),vS(t)];
# Reformulation as free time with space as fixed domain
eqns_s, xvars_s, uvars_s , eqn_vs:= changeOfIndependentVariable(1,t,s,xvars_t,uvars_t,eqns_t):
eqn_vs;
# Load dynamic equations
# List of functions that describes road geometrical properties and can ne mapped to road class methods. Curvature is defined separatelly as a spline.
# This is actually not needed (since curvature is a property of road segments) but here used to show the possibility to combine road and spline data set.
# List of functions which depend on mesh 
qvars := [Curv(s)        = curvature(s),
          xLane(s)       = xTrajectory(s), 
          yLane(s)       = yTrajectory(s),
          theta(s)       = heading(s)]:
#Describe(mapUserFunctionToObject);
# XOptima function that lists the registered objects and related methods available from classes of Mechatronix library. 
#infoRegisteredObjects();
# Map Maple mesh functions to methods of C++ objects 
#mapUserFunctionToObject(qvars,
#                        "*pRoad",              # istanza class tipo pointer
#                        "Mechatronix#Road2D", # classe (deve essere registrata)
#                        "../model/road_data.rb");
mapUserFunctionToObject(qvars,
                        "*pTrajectory",       # istanza class tipo pointer
                        "Mechatronix#Path2D", # classe (deve essere registrata)
                        "../model/trajectory_data.rb");
# By specifying the mesh functions those will be pre-computed once for all at initialization phase reducing the computational costs.
#Describe(loadDynamicSystem);
loadDynamicSystem(states        = xvars_s,
                  controls      = uvars_s,
                  equations     = eqns_s,
                  meshFunctions = map(lhs,qvars)) ;
# Lateral acceleration
eq_ay :=  u(zeta)^2*Curv(zeta);
# Boundary conditions
# Initial and final state fixed: 
#Describe(addBoundaryConditions);
addBoundaryConditions(initial=[n=0,xi=0,u=u0,v=0,Omega=0, alpha__r=0, alpha__f=0, delta=0], 
                      final  =[n=0,xi=0]);
infoBoundaryConditions();
# Target
# Definition of target
#Describe(setTarget);
# Mayer target: 
mayer_target :=   0;                                              # final steady state front slip
#                                     
# Lagrange target
pen_scale := subs( eqn_vs, s=zeta,1/s_dot(s)); #Scale factor for penalties
lagrange_target := pen_scale*(1*wT+0*(n(zeta)/n_max)^2);
# 
setTarget(lagrange=  lagrange_target, mayer = mayer_target);
# Constraints on states and controls
addBilateralConstraint(delta(zeta),SteeringLimit,
                        min       = -delta_max,
                        max       = delta_max,
                        epsilon   = 0.1e-4, 
                        tolerance = 0.1e-4,
                        scale     = pen_scale);
# Path constraints
# Road boundaries
# Right road boarder
addUnilateralConstraint( n(zeta) >= -n_max,
                         roadRightLateralBoundaries,
                         epsilon   = epsi0, 
                         tolerance = 0.1,    
                         scale     = pen_scale );
# Left road boarder
addUnilateralConstraint( n(zeta) <= n_max, 
                         roadLeftLateralBoundaries,
                         epsilon   = epsi0, 
                         tolerance = 0.1, 
                         scale     = pen_scale );
# Ellipse of adherence approximated
# Ellipse of adherence
(fyr(t)/(mu__yr*fzr(t)))^2+(fxr(t)/(mu__xr*fzr(t)))^2:
ellipse_r := subs(tyre_model_LIN,eq_loads,t=zeta,%);

(fyf(t)/(mu__yf*fzf(t)))^2+(fxf(t)/(mu__xf*fzf(t)))^2:
ellipse_f := subs(tyre_model_LIN,eq_loads,t=zeta,%);
addUnilateralConstraint( ellipse_r<= 1,
                         rearEllipse,
                         epsilon   = epsi0, 
                         tolerance = 0.01, #tol_max,
                         scale     = pen_scale );
addUnilateralConstraint( ellipse_f<= 1,
                         frontEllipse,
                         epsilon   = epsi0, 
                         tolerance = 0.01, #tol_max,
                         scale     = pen_scale );
# Constraint maximum power
veh_power_s := subs(tyre_model_LIN,t=zeta,veh_power):
addUnilateralConstraint(veh_power_s<=max_power,
                        "MaxPowerLimit",
                         epsilon   = epsi0, 
                         tolerance = 0.01, #tol_max,
                         scale=pen_scale);
# Control constraints
addControlBound(v__delta(zeta),
                controlType="U_COS_LOGARITHMIC",
                min        = -vDelta_max, 
                max        = vDelta_max,
                #epsilon   = epsi_max, 
                #tolerance = tol_max,
                scale      = pen_scale);
addControlBound(vS(zeta),
                controlType="U_COS_LOGARITHMIC",
                min        = -vS_max, 
                max         =  vS_max,
#                #epsilon   = epsi_max, 
#                #tolerance = tol_max,
                scale       = pen_scale);

# User Defined function
mapUserFunctionToRegularized(posPart,"PositivePartRegularizedWithErf",[h=0.01]);
mapUserFunctionToRegularized(negPart,"NegativePartRegularizedWithErf",[h=0.01]);
# Post processing output expressions
# we can also monitor some post processing variables. Variable, or espression can be also integrated: these are known as integral post processing expression.
# Left and right road edges:
xLEdge  := xLane(zeta)-sin(theta(zeta))*n_max:
yLEdge  := yLane(zeta)+cos(theta(zeta))*n_max:
xREdge  := xLane(zeta)+sin(theta(zeta))*n_max:
yREdge  := yLane(zeta)-cos(theta(zeta))*n_max:
# Left and right wheel position
xCoM  := xLane(zeta)-sin(theta(zeta)+xi(zeta))*(n(zeta)):
yCoM  := yLane(zeta)+cos(theta(zeta)+xi(zeta))*(n(zeta)):
xLCar := xLane(zeta)-sin(theta(zeta)+xi(zeta))*(n(zeta)+vehHalfWidth):
yLCar := yLane(zeta)+cos(theta(zeta)+xi(zeta))*(n(zeta)+vehHalfWidth):
xRCar := xLane(zeta)-sin(theta(zeta)+xi(zeta))*(n(zeta)-vehHalfWidth):
yRCar := yLane(zeta)+cos(theta(zeta)+xi(zeta))*(n(zeta)-vehHalfWidth):

# we can also monitor some post processing variables as follows
# Time is obtained from the integration of the inverse of the velocity over the space domain.
post_process_outputs :=[]:
int_post_process_outputs := [[pen_scale,"time"]]:
post_process_outputs := [
  [Omega(zeta)*u(zeta),"ay"],
  [xCoM,   "xCoMCar"],
  [yCoM,   "yCoMCar"],
  [xLCar,  "xLeftCar"],
  [yLCar,  "yLeftCar"],
  [xRCar,  "xRightCar"],
  [yRCar,  "yRightCar"],
  [xLEdge, "xLeftEdge"],
  [yLEdge, "yLeftEdge"],
  [xREdge, "xRightEdge"],
  [yREdge, "yRightEdge"],
  [arctan(v(zeta),u(zeta)),   "beta"],
  [sqrt(u(zeta)^2+v(zeta)^2),  "VG"],
  seq([subs(t=zeta,rhs(eq_loads[i])),convert(op(0,lhs(eq_loads[i])),string)],i=1..2),
  seq([subs(eq_loads,t=zeta,rhs(tyre_model_LIN[i])),convert(op(0,lhs(tyre_model_LIN[i])),string)],i=1..4),
  [subs(tyre_model_LIN,eq_loads,t=zeta,fxr(t)/fzr(t)), "mu_xr"],
  [subs(tyre_model_LIN,eq_loads,t=zeta,fyr(t)/fzr(t)), "mu_yr"],
  [subs(tyre_model_LIN,eq_loads,t=zeta,fxf(t)/fzf(t)), "mu_xf"],
  [subs(tyre_model_LIN,eq_loads,t=zeta,fyf(t)/fzf(t)), "mu_yf"],
  [veh_power_s, "vehicle_power"]]:
#<%>;
#<post_process_outputs[1..10]>;
# Parameters
# Default values for list of parameters
# New tyre data set from Tyredataset2
tyre_data :=   
  mu__xf = 1.20,  mu__xr = 1.20, 
  mu__yf = .935,  mu__yr = .961, 
  KYf    = 8.86*1.7*0.935,  
  KYr    = 7.0*1.7*0.961:
pars := [op(vehicle_data),vehHalfWidth = 0.8,
         tyre_data,
         delta_max      = evalf(75*Pi/180),
         vDelta_max     = evalf(60*Pi/180),
         u0             = 50/3.6,         # initial velocity
         wT             = 0.01,
         vS_max         = 2*1000,
         kS             = 0.4,
         max_power      = 150*10^3,
         n_max          = 1,
         epsi0          = 1e-2,
         epsi_max       = 1e-4
          ] :



# Guess
# Guess for state variables
x_guess := [n        = 0,
            xi       = 0, 
            u        = u0,
            Omega    = u0*Curv(zeta),
            alpha__r = 0,  
            alpha__f = 0, 
            delta    = 0, 
            S        = 0.0];
# Continuation on minimum time 
# We want to start with a problem with low weight of minimum time and the progressively increase the weight to 1 (pure minimum time problem).
# s in [0,1] is a local variable to implement the continuation. Standard continuation problem uses linear expression to change the parameter from initial to a final desired values. Values can be hard coded or parameters can be used.
# The continuation is a list of list, where each list is executed in sequence and each list may contain more than one definition of parameter that can be changed at the same time.
cont := [[wT = 0.01*(1-s)+1*s,
          epsi = epsi0*(1-s)+epsi_max*s,
           ["MaxPowerLimit",             "epsilon"] = epsi,
           ["frontEllipse",              "epsilon"] = epsi,
           ["rearEllipse",               "epsilon"] = epsi]];

# OCP generation
# Since we mapped the road object, which is also derived form mesh class, the mesh defintion is not necessary.
#Describe(generateOCProblem);
project_dir  := ".." ; #"../ocp-road/";     # project dir: where code is generated

project_name := "SingleTrack_GivenTrajectory";  # project name
generateOCProblem(project_name,           
                  clean                    = false,
                  BVP_only                 = false,
                  max_accumulated_iter     = 1000,
                  output_directory         = project_dir,
                  post_processing          = post_process_outputs,
                  standard_post_processing = true,
                  integral_post_processing = int_post_process_outputs,
                  #mesh                     = [[length=tf*0.1,n=200],[length=tf*0.8,n=1000],[length=tf*0.1,n=200]],
                  states_guess = x_guess,
                  continuation = cont,
                  parameters   = pars
                  );


