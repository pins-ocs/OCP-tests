
# Monobike OCP
# Controllo OTTIMO
restart:
with(XOptima);
interface(rtablesize=20):
# Rear model
read("model.maplemodel"):
# Calculate accelerations:
svars; nops(%);
#<seqns>;
# 2. Load ODE system
seqns := map(numer,seqns): <%>;
Describe(loadDynamicSystem) ;
qvars := [ kappa(zeta)         = saeCurvature(zeta),
           leftWidth(zeta)     = leftWidth(zeta),
           rightWidth(zeta)    = rightWidth(zeta),
           sectionSpeedLimit() = speedLimit(),
           adherence()         = adherence(),
           xLane(zeta)         = saeX(zeta),
           yLane(zeta)         = saeY(zeta),
           theta(zeta)         = saeAngle(zeta)] ;
loadDynamicSystem( equations     = seqns,
                   states        = svars, 
                   controls      = suvars,
                   meshFunctions = map(lhs,qvars) ) ;
# 1. List of abscissa dependent variables
#initRoad(roadWidth=3.70,theta0=0,is_SAE=false) ; 
#addRoadSegment(length=10,gridSize=1) ;
#addRoadSegment(length=40,gridSize=5) ; 
#addRoadSegment(length=Pi*100,gridSize=5,radius=100) ; 
#addRoadSegment(length=40,gridSize=5) ; 
#addRoadSegment(length=10,gridSize=1) ; 
ROAD_DATA := [
  "roadWidth" = 3.7,
  "theta0"    = 0,
  "is_SAE"    = false,
  "x0"        = 0,
  "y0"        = 0,
  "s0"        = 0,
  "width"     = 6,
  "segments" = [
     ["length" = 10,     "gridSize" = 1 ],
     ["length" = 40,     "gridSize" = 5 ],
     ["length" = Pi*100, "gridSize" = 5, "radius"=100 ],
     ["length" = 40,     "gridSize" = 5 ],
     ["length" = 10,     "gridSize" = 1 ]
  ]
] ;
#Describe(mapUserFunctionToObject);
mapUserFunctionToObject( qvars, "*pRoad", "Mechatronix#Road2D", ROAD_DATA ) ;
# 3. Boundary and jump conditions
#Describe(setBoundaryConditions) ;
addBoundaryConditions(initial=[t,sn,alpha,u,phi,u_dot,psi_dot,phi_dot,psi_acc],
                      final=[sn,alpha,phi,u_dot,psi_dot,phi_dot,psi_acc]);
infoBoundaryConditions() ;
def_pars := [ V0           = 10,
              VEL_i        = 20,
              VEL_f        = 10.0/3.6,
              t_i          = 0,
              sn_i         = 0,
              alpha_i      = 0,
              u_i          = VEL_i,
              phi_i        = 0,
              u_dot_i      = 0,
              psi_dot_i    = 0,
              phi_dot_i    = 0,
              psi_acc_i    = 0,
              t_f          = 1.0/VEL_i,
              sn_f         = 0,
              alpha_f      = 0,
              u_f          = VEL_f,
              phi_f        = 0,
              u_dot_f      = 0,
              psi_dot_f    = 0,
              phi_dot_f    = 0,
              psi_acc_f    = 0,
              Lr           = 0.653,  # CoM longitudinal position from rear axle
              L            = 1.533,
              Lf           = L-Lr,   # CoM longitudinal position from front axle
              H            = 0.5,    # Vertical position of CoM
              MASS         = 329.0,  # Vehicle total mass
              G            = 9.81,   # gravity acceleration
              R_WHEEL      = 0.3,    # E N G I N E
              wheelRadius  = R_WHEEL,
              FACTOR       = 1.0/MASS,
              AX_MAX       = 13.0,
              AY_MAX       = 13.0,
              wT           = 0.05,
              IX           = 26,
              IY           = 16*R_WHEEL**2,
              g            = G,
              h1           = H,
              m            = MASS,
              minimumSpeed = 1,
              rr           = R_WHEEL,
              rt           = 0.1,
              ax_max       = AX_MAX,
              ay_max       = AY_MAX ] ;


# 4. Target function
# posso ottenere il tempo tramite integrazione
penaltyScale := subs(SSZDOT,1/zeta_dot(zeta)); #*wScale;  + (1-wScale)/V0; 
tl := subs(SSZDOT,1/zeta_dot(zeta)*wT ); 
# 
tm := 0*((u(zeta_i)-ui)/Delta_u)^2 +
            0*((alpha(zeta_i)-alphai)/Delta_alpha)^2 +
            0*((phi(zeta_i)-phii)/Delta_phi)^2 +
            0*((u_dot(zeta_i)-axi)/Delta_acc)^2 +
            
            0*((u(zeta_f)-uf)/Delta_u)^2 +
            0*((alpha(zeta_f)-alphaf)/Delta_alpha)^2 +
            0*((phi(zeta_f)-phif)/Delta_phi)^2 +
            0*((u(zeta_f)*psi_dot(zeta_f)-ayf)/Delta_acc)^2
            ; #t(zeta_f) ;
#targetBolza(mayer=tm,lagrange=tl) ;
# 5. Constraints
# Road
# Right side (SAE)
addUnilateralConstraint( sn(zeta) <= rightWidth(zeta),
                         roadRightLateralBoundaries,
                         tolerance=0.1,
                         epsilon=0.1,
                         scale=penaltyScale ) ; 
# Left side (SAE)
addUnilateralConstraint( sn(zeta) >= -leftWidth(zeta),
                         roadLeftLateralBoundaries,
                         tolerance=0.1,
                         epsilon=0.1,
                         scale=penaltyScale ) ; 
# Rear and Front ellipse
SSACC := [AX=u_dot(t),AY=u(zeta)*psi_dot(zeta)];
(AX/ax_max)^2 + (AY/ay_max)^2 :
ellisse := subs(SSACC,t=zeta,%);
# ellisse delle accelerazioni
addUnilateralConstraint( ellisse <= 1,
                         AdherenceEllipse,
                         tolerance=0.05,
                         epsilon=0.01,
                         scale=penaltyScale );

# Penalità sull'accelerazione 
addPenaltyRhomb( subs(SSACC,t=zeta,AX),
                 subs(SSACC,t=zeta,AY),
                 acceptedAcceleration,
                 scale   = penaltyScale,
                 epsilon = 0.01,
                 xlimit  = AX_MAX,
                 ylimit  = AY_MAX,
                 xpsy    = 6,
                 ypsy    = 3.5 ) ;

# spinta disponibile (tolleranza relativa)
addUnilateralConstraint( subs(SSACC,t=zeta,AX)/maxAcceleration(u(zeta)) <= 1, 
                         longitudinalAccelerationLimit,
                         tolerance=0.1, 
                         epsilon=0.1,
                         scale=penaltyScale );

# limiti di velocita minimo e massimo
addUnilateralConstraint( u(zeta) <= sectionSpeedLimit(zeta),
                         sectionSpeedConstraint,
                         tolerance=1, 
                         epsilon=0.1,
                         scale=penaltyScale*0 );
addUnilateralConstraint( u(zeta) >= minimumSpeed,
                         minimumSpeedConstraint,
                         tolerance=2, 
                         epsilon=0.1,
                         scale=penaltyScale );

# Steer angle
#addPenaltyINTERVAL( delta(zeta), steerConstraint, penaltyScale ):
# Control limits
op(0,suvars[2]);penaltyScale;
addControlBound( suvars[1],
                 #type      = "U_QUADRATIC2",
                 epsilon    = 0.01,
                 tolerance  = 0.01,
                 scale      = penaltyScale ) ;
addControlBound( suvars[2], 
                 #type      = "U_QUADRATIC2",
                 epsilon    = 0.01,
                 tolerance  = 0.01,
                 scale      = penaltyScale ) ;
# 6. User Functions
addUserFunction(maxAcceleration(vel)=maxTorqueOnWheelHub(vel/wheelRadius)/(m*wheelRadius));     

TORQUE := [1.00, 30.0, 35.0, 40.0, 60.0, 73.2, 75.3,
           75.9, 75.9, 77.3, 81.4, 86.8, 88.1, 88.1,
           89.5, 89.5, 89.5, 88.1, 86.8, 85.4, 85.4,
           85.4, 85.8, 85.1, 85.1, 85.8, 85.4, 80.1,
           74.1, 71.4, 60.4, 1.0] ;
GEAR_RATIO := [4.5, 2.5, 1.75, 1.35, 1.1, 0.9, 0.78 ] ;
RPM        := [0, 400, 800, 1200, 1600, 2000, 2200, 
               2400, 2600, 2800, 3000, 3200, 3400, 3600,
               3800, 4000, 4200, 4400, 4600, 4800, 5000,
               5200, 5400, 5600, 5800, 6000, 6200, 6400,
               6800, 7000, 7200, 8000] ;
ENGINE_DATA := [ "Gear_ratio" = GEAR_RATIO, "Rpm" = RPM, "Torque" = TORQUE] :
mapUserFunctionToObject( maxTorqueOnWheelHub(vel)=maxTorqueOnWheelHub(vel),
                         "*pEngine","Mechatronix#Engine",
                         ENGINE_DATA ) ;
# 8. Generate Optimal Control Equations and C++ code
setTarget( mayer = tm, lagrange = tl ) ;
POST_PROCESS := [
  [subs(SSACC, t=zeta,AX ),                       "ax"],
  [subs(SSACC, t=zeta,AY ),                       "ay"],
  #[subs(SSACC_true, t=zeta,AX ),                 "axTrue"],
  #[subs(SSACC_true, t=zeta,AY ),                 "ayTrue"],
  [maxAcceleration(u(zeta)),                      "maxLogitudinalAcceleration"],
  [xLane(zeta)-sin(theta(zeta))*sn(zeta),         "xTrajectory"],
  [yLane(zeta)+cos(theta(zeta))*sn(zeta),         "yTrajectory"],
  [xLane(zeta)+sin(theta(zeta))*leftWidth(zeta),  "xLeft"],
  [yLane(zeta)-cos(theta(zeta))*leftWidth(zeta),  "yLeft"],
  [xLane(zeta)-sin(theta(zeta))*rightWidth(zeta), "xRight"],
  [yLane(zeta)+cos(theta(zeta))*rightWidth(zeta), "yRight"]
] ;
generateOCProblem( "Monobike", clean = false,
                   post_processing = POST_PROCESS,
                   parameters   = def_pars,
                   states_guess = [ u = V0, t = zeta/V0 ] ) ;

