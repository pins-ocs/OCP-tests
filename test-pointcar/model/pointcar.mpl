
# 
# XOPTIMA  Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control tutorial:
# Single-degree-of-freedom (SDF) car model
# Authors: Roberto Lot
# Date: 2nd January 2014
# 
# 
restart:
# SDF car model - time domain
# state variables
tvars := [
  s(t),    # travelled space [m]

  u(t),    # forward speed [m/s]
  as(t)    # longitudinal acceleration [m/s2]

];
# inputs
uvar := js(t); # longitudinal jerk
;
# dynamic equations
tode := [  
  diff(s(t),t)  = u(t),
  diff(u(t),t)  = as(t),
  diff(as(t),t) = js(t)
]: <%>;
# SDF car model - space domain
zeta;  # XOptima requires 'zeta' as independent variable
# state variables
zvars := [
  u(zeta),    # forward speed [m/s]

  as(zeta)    # longitudinal acceleration [m/s2]

];
# input
uvars := [js(zeta)]; # longitudinal jerk
;
# dynamic equations
sode := [  
  diff(u(zeta),zeta)  = as(zeta)/u(zeta),
  diff(as(zeta),zeta) = js(zeta)/u(zeta)
]: <%>;
# formulation of the Minimum Time problem
# Lagrange Target
Lagrange_penalty := 1/u(s);
# circle of adherence
an(zeta)  := u(zeta)^2*kappa(zeta);  # lateral acceleration [m/s2]
adherence := (as(zeta)^2+an(zeta)^2)/(mu*g)^2;
# OCP with XOptima 
with(XOptima):
#Describe(XOptima);
#Describe(loadDynamicSystem);
loadDynamicSystem(
   states    = zvars,
   controls  = uvars,
   equations = sode,
   meshFunctions = [kappa(zeta)]
);
ROAD := [
  "roadWidth" = 3.7,
  "gridSize"  = 0.1,
  "theta0"    = 0,
  "s0"        = 0,
  "x0"        = 0,
  "y0"        = 0,
  "is_SAE"    = true,
  "segments" = [
     [ "length" = 10,    "gridSize" = 0.1 ],
     [ "length" = Pi*50, "gridSize" = 1,  "radius" = 50 ],
     [ "length" = 60,    "gridSize" = 0.5 ],
     [ "length" = 10,    "gridSize" = 0.1 ]
   ]
];
methods :=  [
  theta(zeta) = saeAngle(zeta),  kappa(zeta) = saeCurvature(zeta),
  x(zeta)     = isoX(zeta),
  y(zeta)     = isoY(zeta)] ;
mapUserFunctionToObject(
  methods,
  "*pRoad",
  "Mechatronix#Road2D",
  "../model/pointcar_road2.rb"  #ROAD
);
addBoundaryConditions(
  initial = [u,as],
  final   = [u,as]
);
setStatusBoundaryConditions(
  initial = [u,as],
  final   = [u,as]
);
infoBoundaryConditions() ;
# bounded inputs penalties
addControlBound( js,
                 controlType = "U_COS_LOGARITHMIC",
                 min         = jsControlMinValue,
                 max         = jsControlMaxValue,
                 tolerance   = 0.005 );
# Constraints
#Describe(addUnilateralConstraint);
addUnilateralConstraint( adherence < 1, Adherence );
setTarget( lagrange = 1/u(zeta) ) ;
#Describe(generateOCProblem) ;
PARAMS := [
  mu   = 0.8,
  g    = 9.81, 
  u_i  = 10,
  u_f  = 10,
  as_i = 0,
  as_f = 0,
  jsControlMaxValue=10,
  jsControlMinValue=-10
];
POST := [  [x(zeta),"Xmiddle"],  [y(zeta),"Ymiddle"]
]
;
generateOCProblem( "pointcar",
                    parameters      = PARAMS,
                    post_processing = POST,                    states_guess    = [ u = 1, as=0 ],
                    excluded        = ["pointcar_Data.lua"] ,
                    output_directory = "../" ) ;

