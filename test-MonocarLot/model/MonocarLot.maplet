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
as(t) ]; # longitudinal acceleration [m/s2]
# inputs
uvar := js(t); # longitudinal jerk
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

as(zeta) ]; # longitudinal acceleration [m/s2]
# input
uvars := [js(zeta)]; # longitudinal jerk
# dynamic equations
sode := [  
diff(u(zeta),zeta)  = as(zeta)/u(zeta),  diff(as(zeta),zeta) = js(zeta)/u(zeta)
#u(zeta)*diff(u (zeta),zeta) - as(zeta),  u(zeta)*diff(as(zeta),zeta) - js(zeta)
]: <%>;
# formulation of the Minimum Time problem
# Lagrange Target
Lagrange_penalty := 1/u(s);
# circle of adherence
an(zeta) := u(zeta)^2*kappa(zeta);  # lateral acceleration [m/s2]
adherence := (as(zeta)^2+an(zeta)^2)/(mu*g)^2;
# OCP with XOptima 
with(XOptima);
reset(XOptima):
#Describe(XOptima);
Describe(loadDynamicSystem);
loadDynamicSystem(
   states=zvars, controls=uvars, equations=sode,
   meshFunctions=[kappa(zeta)]);
mapUserFunctionToObject( [kappa(zeta)=saeCurvature(zeta)], "*pRoad", "Mechatronix#Road2D");
addBoundaryConditions(initial=[u,as],final=[u,as]);
infoBoundaryConditions() ;
# bounded inputs penalties
addControlBound( js, controlType="U_COS_LOGARITHMIC",  tolerance = 0.005, min=-10, max=10 );
# Constraints
Describe(addUnilateralConstraint);
adherence ;
addUnilateralConstraint(adherence < 1, Adherence, barrier=true);
setTarget( lagrange = 1/u(zeta) ) ;
Describe(generateOCProblem) ;
initRoad(roadWidth=3.70,theta0=0,is_SAE=true);
addRoadSegment(length=10,gridSize=0.1);
addRoadSegment(length=Pi*50,radius=50,gridSize=1);
addRoadSegment(length=60,gridSize=0.5);
addRoadSegment(length=10,gridSize=0.1);

generateOCProblem( "MonoCarLot",
                    parameters = [ mu=0.8, g=9.81, u_i=10, u_f=10, as_i=0, as_f=0 ],
                    states_guess = [u=5]    ) ;
# 
