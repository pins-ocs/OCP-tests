# 
# 
# XOptima
# Solution of Optimal Control Problems (c) 
# University of Trento
# Optimal Control of a point car model
# Author:       
# Date:         
# Load library
# Load MBSymba(c) Multibody library and others
restart: with(plots):
# Problem description
# bla bla 
# 
# Model
# System of equations:
alpha(t),      # imbardata relativa
ss(t),sn(t),   # ascissa e ordinata curvilinea
kappa(t);  #           curvatura
# curvilinear coordinates equations (aggiornare figura)
psi[dot](t) := u(t)*Delta(t): # curvatura traiettoria

e1 := (1-sn(t)*kappa(t))*diff(ss(t),t)-u(t)*cos(alpha(t));
e2 := diff(alpha(t),t)+kappa(t)*diff(ss(t),t)- psi[dot](t);
e3 := diff(sn(t),t)-u(t)*sin(alpha(t));
#collect( op(solve([e||(1..3)],diff([ss(t),sn(t),alpha(t)],t))), theta(t)): <%>;
e4 := diff(Delta(t),t) -kDelta*jDelta(t);
e5 := diff(u(t),t)+a0+a2*u(t)^2-pedalMap(p(t));
e6 := diff(p(t),t) -jp(t);
# Point car model equations in curvilinear coordinates:
teqns := [e||(1..6)]: <%>;
# Variabili di stato:
tvars := [ss(t),sn(t),alpha(t),u(t), Delta(t), p(t)]; nv := nops(%): # = nops(eqns);
# Controls
tuvars := [jp(t), jDelta(t)];
# Change to curvilinear abscisaa domain
# Conversion from time domain to s domain (free time problem)
# Equations are rewritten in space domain
svars0 := [op(subs(t=zeta, tvars[2..nv]))]; nsv := nops(svars);svars0;
SS :=diff(ss(t),t)=zeta_dot(zeta), 
      seq( diff(tvars[i],t) = diff(subs(t=zeta,tvars[i]),zeta)*zeta_dot(zeta), i=1..nv),  ss(t)=zeta,  t=zeta;
seqns0 := [op(subs(SS,t=zeta, teqns[2..-1] ) )]: <%>;
# zeta_dot speed definition
SSZDOT := solve(subs(SS,t=zeta,{teqns[1]}),{zeta_dot(zeta)});
# Equations of motion in time domain:
seqns0 := subs(SSZDOT,seqns0):<%>;
# Time equation (used only if necessary since it increases the problem dimension)
seqTime := subs( SSZDOT, diff(t(zeta),zeta)*zeta_dot(zeta) - 1);

# State variable list:
svars := [op(svars0),t(zeta)]; 
# Control input list
uvars := subs(t=zeta,tuvars);
# List of equations: including time
seqns := [op(seqns0),seqTime]: #<%>;
# riscrivo l'equazione del tempo, cioe la prima
# for i from 1 to nv do i=svars[i]; seqns[i]; end do;
seqns:=simplify(convert(convert(map(numer,seqns),list),Vector),size): <%>;
# Linearized model
ff := (C1,C2,x,h)->+( (C1-C2)/2*sin(arctan(x/h))+(C1+C2)/2 ):
ffi := unapply(int(ff(C1,C2,x,h),x),[C1,C2,x,h]);
ss_pedalMap      := pedalMap(p(zeta)) = ffi(C1,C2,p(zeta),h_p);
data := [kDelta = 1.0/15.2/2.6,
         a0     = 0,
         a2     = 0,
         C1 = 1.5, C2 = 10, h_p = 0.01 ];
plot(subs(ss_pedalMap,data,p(zeta)=p,pedalMap(p(zeta))),p=-1..1,gridlines=true,thickness=2,labels=[pedal, a[x]]);
save(seqns,svars,uvars,SSZDOT,ss_pedalMap,data,"model.maplemodel");
# Optimal control
restart: with(plots):
# Load optimal control library
with(XOptima):
interface(rtablesize=20):
read("model.maplemodel"):
# Optimal control problem definition
# Load dynamic system
# Load the ODE dynamic system: list of controls, state variables and differential equations.
# By default the command set the indepenedent variable equal to "zeta".
uvars;svars;
qvars := [kappa(zeta)         = isoCurvature(zeta),
          leftWidth(zeta)     = leftWidth(zeta),
          rightWidth(zeta)    = rightWidth(zeta),
          xLane(zeta)         = isoX(zeta),
          yLane(zeta)         = isoY(zeta),
          theta(zeta)         = isoAngle(zeta),
          sectionSpeedLimit() = speedLimit(),
          adherence()         = adherence()]:          

# Map Maple mesh functions to methods of C++ objects 
mapUserFunctionToObject(qvars,
                        "*pRoad",              # istanza class tipo pointer
                        "Mechatronix#Road2D"); # classe (deve essere registrata)
QSUBS;
Describe(loadDynamicSystem) ;
loadDynamicSystem( equations     = seqns,
                   states        = svars, 
                   controls      = uvars,
                   meshFunctions = [kappa(zeta)]) ;
# Boundary conditions and jump conditions
# Longitudinal and lateral accelerations as a function respectivelly of pedal  and steer angle.:
accLong := -a0-a2*u(zeta)^2+pedalMap(p(zeta));
accLat  := u(zeta)^2*Delta(zeta);
#setBoundaryConditions();
#setBoundaryConditions(generic=[[ax_i  = subs(zeta=zeta_i,accLong),"initial_long_acc"],
#                               [ay_i  = subs(zeta=zeta_i,accLat), "initial_lat_acc" ],
#                               [ax_f  = subs(zeta=zeta_f,accLong),"final_long_acc"],
#                               [ay_f  = subs(zeta=zeta_f,accLat), "final_lat_acc" ]]);
addBoundaryConditions(initial=[sn,alpha,u,Delta,p,t],
                      final  =[sn,alpha,Delta,p]);
#bc_vec;
# Dispaly the bounddary condition activation status:
infoBoundaryConditions();
# Target: performance criterion
# A small quantity epsilon is added to the denominator to avoid singularities
subs( SSZDOT ,1/(zeta_dot(zeta)+epsilon^2));
penScale := collect(simplify( %) ,epsilon):
# Path constraints
# Right road boarder
addUnilateralConstraint( sn(zeta)-vehHalfWidth >= -(rightWidth(zeta)), roadRightLateralBoundaries,scale=penScale );
# Left road boarder
addUnilateralConstraint( sn(zeta)+vehHalfWidth <= leftWidth(zeta), roadLeftLateralBoundaries,scale=penScale );
# Pedal limits between [-1,1]
addBilateralConstraint(p(zeta),
                       pedalLims,
                       scale = penScale );
# Limits on forward velocity: 
addUnilateralConstraint( u(zeta) <= sectionSpeedLimit(zeta),
                         sectionSpeedConstraint,
                         scale=penScale*0);
addUnilateralConstraint( u(zeta) >= minimumSpeed,
                         minimumSpeedConstraint,
                         scale=penScale*0);
# Control constraints
uvars ;
addControlBound( jp,
                 maxabs      = jDelta_max,
                 epsilon     = 0.01,
                 tolerance   = 0.01,
                 controlType = "U_PARABOLA",
                 scale       = penScale ) ;
addControlBound( jDelta,
                 maxabs      = jp_max,
                 epsilon     = 0.01,
                 tolerance   = 0.01,
                 controlType = "U_PARABOLA",
                 scale       = penScale ) ;
# User defined functions
# In this section the user defined functions are defined. The user defined functions can be linked to methods of a C++ class that has been registered, or can be a C function that will be defined later on in the code or can be a mathematical expression that is automatically converted in C by XOptima.
addUserFunction(pedalMap(p) = subs( ss_pedalMap, p(zeta)=p,pedalMap(p(zeta))  ));
#addUserFunction(pedalMap(p)  );
# Generation of optimal control equations and C++ code
dataOCP := [
  vehHalfWidth = 0.75,
  Delta_f      = 0, 
  Delta_i      = 0, 
  ax_f         = 0,
  ax_i         = 0, 
  ay_f         = 0,
  ay_i         = 0, 
  alpha_f      = 0,
  alpha_i      = 0, 
  p_f          = 0, 
  p_i          = 0, 
  sn_f         = 0, 
  sn_i         = 0, 
  t_f          = 0,
  t_i          = 0, 
  u_f          = 10,
  u_i          = 10, 
  jp_max       = 2, 
  jDelta_max   = 1.5,
  wT           = 1,
  epsilon      = 0.1,
  v0           = 10,
  minimumSpeed = 0.1 
];
# Left and right wheel position:
xLeftEdge  := xLane(zeta)-sin(theta(zeta))*(leftWidth(zeta)):
yLeftEdge  := yLane(zeta)+cos(theta(zeta))*(leftWidth(zeta)):
xRightEdge := xLane(zeta)+sin(theta(zeta))*(rightWidth(zeta)):
yRightEdge := yLane(zeta)-cos(theta(zeta))*(rightWidth(zeta)):
xLeftCar  := xLane(zeta)-sin(theta(zeta))*(sn(zeta)+vehHalfWidth):
yLeftCar  := yLane(zeta)+cos(theta(zeta))*(sn(zeta)+vehHalfWidth):
xRightCar := xLane(zeta)-sin(theta(zeta))*(sn(zeta)-vehHalfWidth):
yRightCar := yLane(zeta)+cos(theta(zeta))*(sn(zeta)-vehHalfWidth):
setTarget( lagrange = wT*penScale ) ;

# A guess solution can be specified for some or all state variables. The guess solution can be a function of the indepenedent variable "zeta". Piecewise solution are not allowed.
# Define default road
#Describe(addRoadSegment);
initRoad(roadWidth=3.70,theta0=0,is_SAE=false);
addRoadSegment(length=50,gridSize=1);
addRoadSegment(length=Pi*50,radius=50,gridSize=1);
addRoadSegment(length=50,gridSize=1);
#initRoad(roadWidth=3.70,theta0=0,is_SAE=false) ; 
#addRoadSegment(length=10,gridSize=1) ;
#addRoadSegment(length=40,gridSize=5) ; 
#addRoadSegment(length=Pi*100,gridSize=5,radius=100) ; 
#addRoadSegment(length=40,gridSize=5) ; 
#addRoadSegment(length=10,gridSize=1) ; 
Describe(generateOCProblem) ;
generateOCProblem( "Monocar",
                   post_processing = [[pedalMap(p(zeta)),          "pedalMap"],
                                     [accLong,  "ax"],
                                     [accLat,   "ay"],
                                     [xLane(zeta)-sin(theta(zeta))*sn(zeta),         "xTrajectory"],
                                     [yLane(zeta)+cos(theta(zeta))*sn(zeta),         "yTrajectory"],
                                     [xLeftCar,         "xLeftCar"],
                                     [yLeftCar,         "yLeftCar"],
                                     [xRightCar,         "xRightCar"],
                                     [yRightCar,         "yRightCar"],
                                     [xLane(zeta)-sin(theta(zeta))*leftWidth(zeta),  "xLeft"],
                                     [yLane(zeta)+cos(theta(zeta))*leftWidth(zeta),  "yLeft"],
                                     [xLane(zeta)+sin(theta(zeta))*rightWidth(zeta), "xRight"],
                                     [yLane(zeta)-cos(theta(zeta))*rightWidth(zeta), "yRight"],
                                     [xLeftEdge,  "xLeftEdge"],
                                     [yLeftEdge,  "yLeftEdge"],
                                     [xRightEdge, "xRightEdge"],
                                     [yRightEdge, "yRightEdge"],
                                     [subs(SSZDOT,1/zeta_dot(zeta)), "dtdzeta"]
                           ],
                    parameters = [op(dataOCP),op(data)],
                    states_guess    = [ u = v0, t = 1/v0*zeta, sn=(leftWidth(zeta)-rightWidth(zeta))/2] ) ;

