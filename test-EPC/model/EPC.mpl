# Michelangelo
# (in controllo in velocità)
# Modello senza dinamica degli assi e dello spindle. Sono presenti le equazioni ma non sono usate.
# Sono usate due funzioni obiettivo: massimizzazione MRR (tempo minimo) e minimizzazione della rugosità
# Optimize a block of code of milling process
restart:
# Load optimal control library
with(XOptima):with(plottools):with(plots):
interface(rtablesize=20):
# System dynamics
# Feed dynamics is simulated as a second order system
ode := diff(f(t),t,t) + 2*w*diff(f(t),t) + w^2*(f(t)-cos(10*t)) ;
SOL := dsolve( {ode, f(0)=0, D(f)(0)=0} ) ;
plot( [subs(w=10,subs(SOL,f(t))),cos(10*t)], t=0..5) ;

# Mandrel dynamics is simulated as a second order system
ode := diff(f(t),t,t)/w^2 + 2*zeta/w*diff(f(t),t) + f(t) - 100;
SOL := dsolve( {ode, f(0)=0, D(f)(0)=0} ) ;
plot( [subs(w=26.7668, zeta = 0.1178, subs(SOL,f(t))),100], t=0..5) ;
# Equazione di avanzamento: feed f(t) and curvilinear abscissa s(t)
EQ1_t := diff(s(t),t) - f(t) ;
# Feed dynamics
# Feed dynamics: it is the combination of all machine axes
# f'' + 2 w f'+w^2 f=w^2 fn
EQ1 := f(zeta)*diff(af(zeta),zeta) + wnf*(2*af(zeta) + wnf*(f(zeta)-fn(zeta)));
EQ2 := f(zeta)*diff(f(zeta),zeta) - af(zeta) ;
# Spindle dynamics
# omega'' + 2 wns omega'+wns^2 omega=wns^2 omegan
EQ3 := f(zeta)*diff(as(zeta),zeta) + wn_s*(2*dmp_s*as(zeta) + wn_s*(omega(zeta)-omega_n(zeta)));
EQ4 := f(zeta)*diff(omega(zeta),zeta) - as(zeta) ;
EQ5 := f(zeta)*diff(omega_n(zeta),zeta) - vOmega(zeta) ;
# Equazione del tempo: si può evitare di usare e integrare a posteriori. risparmio un'equazione
#EQ3 := f(zeta)*diff(t(zeta),zeta) - 1 ;
# Aggiungo controllo in velocità sia del feed che dello spindle
#EQ5 := f(zeta)*diff(fn(zeta),zeta)-vfn(zeta);
#EQ6 := f(zeta)*diff(omega_n(zeta),zeta)-vOmega_n(zeta);
# Simplified dynamics
# Caso con solo dinamica del controllo (limitazione in accelerazione). La dinamica è molto rapida quindi é sufficiente quest'approssimazione
EQ1 := f(zeta)*diff(f(zeta),zeta)-vf(zeta);
EQ2 := f(zeta)*diff(omega(zeta),zeta)-vOmega(zeta);
EQNS := [EQ1,EQ2]: <%>;
#EQNS := [EQ1, EQ3, EQ4, EQ5]: <%>;
# Funzione obiettivo
# 1. Material removal rate
# w        = cut width
# d         = cut depth
# fr_n  = feed rate (m/s). Nominal feed rate.
# fr_o  = override of feed rate (m/s). 
# TM = manoeuvre time
# Actual feed rate: 
MRR := crossSection(zeta)*f(zeta);
# Cutting force, Torque and power
Pc := MRR*us/eta;       # cutting power

Tc := Pc/omega(zeta); #             cutting torque

Fc := Tc/r;             # cutting force
# 2. Roughness: Cutting torque and cutting power
# Tool tip rotation
alpha := Fc*l^2/(2*E*J);
# Roughness:
Ra := r*alpha;
# Maximum roughness value:
ss_c_Ra_max := c_Ra_max = max_cross_sec()*max_feed/min_omega;
# Maximum roughness value:
Ra_max := 1/2*c_Ra_max*us*l^2/(eta*E*J) ;
# normalized surface roughness:
Ra_norm := subs(ss_c_Ra_max,  Ra/Ra_max );
# 3. Normalized tool wear
# Simplified formula
vc := omega(zeta)*r;
wear := (1.0e-6*(vc-4.5)^2+100.0e-6*(vc-4.5)^2+1e-1*f(zeta)^2.68)*crossSection(zeta)/max_cross_sec();
#wear := (1.0e-6*(vc-1.5)^2+100.0e-6*(vc-1.5)^2)*crossSection(zeta)/max_cross_sec();

tool_wear_norm := wear/1e-5;
f_wear := subs( omega(zeta)=Omega,f(zeta)=F,r = 31.5/1000,crossSection(zeta)=max_cross_sec(), tool_wear_norm);
min_sol := Optimization[Minimize](f_wear,[],Omega=evalf(100*Pi/30)..evalf(1500*Pi/30),F=0.00001..0.166667);
plot3d(f_wear, Omega=evalf(100*Pi/30)..evalf(1500*Pi/30),F=0.0001..0.166667,axes=boxed,style=surfacecontour,contours=20);

evalf(subs(min_sol[2],Omega)*31.5/1000*60);
# Complete formula: Taylor's expanded model
#   nt: number of teeth
#   c, n, a, b : coefficients of Taylor's extended wear formula
#   cs: (m/s) cutting speed
N := omega(zeta)*30/Pi; # rpm, omega(zeta) is in rad/s
vc := r*2*Pi*N/1000; # m/min
fz := 60000*f(zeta)/(nt*N); # mm/tooth, note that feed(zeta) is given in m/s (and not mm/min)
life := nt*c^(1/n)*vc^(-1/n)*crossSection(zeta)^(-b/n)*fz^(-a/n):
# life := nt*( c/( vc*crossSection(zeta)^b*fz^a  ) )^(1/n);
wear := 1/life:

life_min := subs( omega(zeta)=max_omega,
                  crossSection(zeta)=max_cross_sec(),
                  f(zeta)= max_feed , life):
wear_max := 1/life_min:

tool_wear_norm := simplify(wear/wear_max);



f_wear := evalf( subs( max_feed = evalf(1/6), max_omega = evalf(1500*Pi/30), nt = 5, c = 400, n = 0.17, a= 0.77, b = 0.37, omega(zeta)=Omega,crossSection(zeta)=max_cross_sec(), max_cross_sec()= evalf(0.01*0.01), f(zeta)=F, r = 31.5/1000, tool_wear_norm) );

min_sol := Optimization[Minimize]( f_wear,[],Omega=evalf(100*Pi/30)..evalf(1500*Pi/30),F=0.00001..10000);
max_cs := 0.01*0.01:
evalf( subs( max_feed = evalf(1/6), max_omega = evalf(1500*Pi/30), nt = 5, c = 400, n = 0.17, a= 0.77, b = 0.37, omega(zeta)=Omega, crossSection(zeta) = cs, max_cross_sec()= max_cs, f(zeta)=F, r = 31.5/1000, tool_wear_norm) ):

animate(plot3d, [%, Omega=evalf(100*Pi/30)..evalf(1500*Pi/30),F=0..evalf(1/6), axes = boxed, labels = ["S (rad/s)", "F (m/s)", "ool_wear_norm"], shading=zhue, grid = [40,40]], cs = 0..max_cs, style = surfacecontour);
# 4. Limit energy consumption
# Terms whose effect is prevalent when the mill is not cutting: the spindle speed shuold be low
 f_enc := omega(zeta)^2/max_omega^2*(1-on_off(1E6*crossSection(zeta))); # the multiplier 1e6 is associated to the convertion of the unit of measurement from m^2 to mm^2

f_enc_plot := omega(zeta)^2/max_omega^2*(-sin(arctan(1e6*crossSection(zeta)))+1);

pl1 := plot([subs(max_omega = 1500*Pi/30, omega(zeta) = evalf(0*Pi/30), crossSection(zeta) = cs, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = evalf(500*Pi/30), crossSection(zeta) = cs, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = evalf(1000*Pi/30), crossSection(zeta) = cs, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = evalf(1500*Pi/30), crossSection(zeta) = cs, f_enc_plot)],
       cs=0..0.01*0.01, legend=["Omega = 0", "Omega = 500", "Omega = 1000", "Omega = 1500"] ):
pl2 := plot([subs(max_omega = 1500*Pi/30, omega(zeta) = Omega, crossSection(zeta) = 0, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = Omega, crossSection(zeta) = 0.0025*0.0025, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = Omega, crossSection(zeta) = 0.005*0.005, f_enc_plot),
             subs(max_omega = 1500*Pi/30, omega(zeta) = Omega, crossSection(zeta) = 0.01*0.01, f_enc_plot)],
       Omega=evalf(0*Pi/30)..evalf(1500*Pi/30), view = 0..0.5, legend=["cs = 0", "cs = 0.0025*0.0025", "cs = 0.005*0.005", "cs = 0.01*0.01"]):
pl3 := plot3d(subs(max_omega = 1500*Pi/30, omega(zeta) = Omega, crossSection(zeta) = cs, f_enc_plot), Omega=evalf(0*Pi/30)..evalf(1500*Pi/30),cs=0..0.01*0.01,axes=boxed,style=surfacecontour,contours=20, shading=zhue):


display(array([pl1,pl2,pl3]));

# Optimal control
# List of equations:
seqns := EQNS : <%>;
# List of variables:
svars := [ f(zeta),omega(zeta)];
#svars := [ f(zeta),omega(zeta), as(zeta), omega_n(zeta)]; 
# List of controls
uvars := [ vf(zeta), vOmega(zeta) ] ;
# 1. List of abscissa dependent variables
qvars := []: 
# 2. ODE system
loadDynamicSystem( equations     = seqns,
                   states        = svars, 
                   controls      = uvars,
                   meshFunctions = qvars) ;
# 3. Boundary conditions
addBoundaryConditions(initial=[f,omega] ,
                      final=[f,omega] , 
                      generic=[]) ;

setStatusBoundaryConditions(initial=[f,omega] ,
                            final=[f,omega] , 
                            generic=[]);
# Display the bounddary condition activation status:
infoBoundaryConditions();
# 4. Target function
# posso ottenere il tempo tramite integrazione
penaltyScale := 1/f(zeta) ; #1/sqrt(f(zeta)^2+min_feed^2); 


plot([1/(x+0.001^2),1/(x+0.001),1/(sqrt(x^2+0.001^2))], x = 0.0..0.01,
     view=0..1e3,thickness=3,color=[red,"SteelBlue","Orange"],
     title="Comparison among different regularized penalty scales");
# Complete target
target_min_time  := wT_min/f(zeta);
target_roughness := wT_Ra*Ra_norm/f(zeta);
target_tool_wear := wT_tw*tool_wear_norm/f(zeta) ;
target_min_energy := wT_en*f_enc/f(zeta);
setTarget(mayer=wi*((f(zeta_i)-f_i)/min_feed)^2, 
          lagrange=target_min_time+target_roughness+target_tool_wear+target_min_energy) ;

# 5. Constraints
# Feed rate (imposta dalla dinamica se non c'è overshoot)
Describe(addUnilateralConstraint);
# Cutting torque limit
addUnilateralConstraint( Tc < Tc_max,
                         barrier = true,
                         CuttingTorqueLimit,
                         tolerance=1.0,
                         epsilon=0.1,
                         scale=penaltyScale*CuttingTorque_weight ) :
# Cutting power
addUnilateralConstraint( Pc < Pc_max,
                         barrier = true,
                         CuttingPowerLimit,
                         tolerance = 10,
                         epsilon   = 0.1,
                         scale     = penaltyScale ) ;
addBilateralConstraint( f(zeta),
                        fRange,
                        barrier=true,
                        tolerance = 0.0001,
                        epsilon   = 0.01,
                        min       = min_feed,
                        max       = max_feed,
                        scale     = penaltyScale ) ;


addBilateralConstraint( omega(zeta),
                        omegaRange,
                        barrier   = true,
                        tolerance = 1,
                        epsilon   = 0.01,
                        min       = min_omega,
                        max       = max_omega,
                        scale     = penaltyScale*omegaRange_weight ) ;


eq_max_fz := (f(zeta) - 0.6*rf*omega(zeta)/(2*Pi)); # rf : fillet radius

addUnilateralConstraint( eq_max_fz <= 0,
                         barrier = false,
                         FeedRateLimit,
                         tolerance = 10,
                         epsilon   = 0.1,
                         scale     = penaltyScale*(on_off(1E6*crossSection(zeta))) ) ;
# Control limits
#Describe(addControlBound);
addControlBound( uvars[1],
                 controlType  = "U_LOGARITHMIC",
                 #controlType = "U_QUADRATIC2",
                 epsilon      = 0.01,
                 tolerance    = 0.1,
                 maxabs       = max_feed_acc,
                 scale        = penaltyScale ) ;

addControlBound( uvars[2],
                 controlType  = "U_LOGARITHMIC",
                 #controlType = "U_QUADRATIC2",
                 epsilon      = 0.01,
                 tolerance    = 0.1,
                 maxabs       = max_omega_acc,
                 scale        = penaltyScale ) ;
# Jump conditions: la mesh è formata da segmenti, tra un segmento e l'altro posso avere: continuità, una variabile libera e l'altra imposta oppure entrambe sono libere
# Condizione sul feed rate
setJumpConditionFreeLeft(f,f(zeta_R)-initialEstimatedFeedRate_R()) ;
#setJumpConditionFreeLeft(omega,omega(zeta_R)-initialEstimatedSpindleRate_R()) ;
# 8. Guess solution
addUserFunction(f_max(rf,mf),0);
o_guess := omega_i; #(maxSpindleRate()+minSpindleRate())/2 ;
rec_f1 := 1/solve(Pc/Pc_max - 1,f(zeta)) ;

rec_f2 := subs(omega(zeta)=o_guess,1/solve(Tc/Tc_max - 1,f(zeta))) ;
fguess := f_i; #f_factor * f_max(max(rec_f1,rec_f2),maxFeedRate()) ;
# Upwind: è un modo per settare come vengono discretizzate le equazioni, in questo caso discretizzo la variabili in avanti con eulero, mentre l'equazione corrispondente al motiplicatore all'indietro
setFDorder([1,2],"backward"):
setFDorderCoEquation([f(zeta),omega(zeta)],"forward");
# 6. User Functions
# None
#Describe(mapUserFunctionToObject);
#infoRegisteredObjects() ;
mapUserFunctionToObject([nominalFeedRate()             = nominalFeedRate(),
                         initialEstimatedFeedRate()    = initialEstimatedFeedRate(),
                         finalEstimatedFeedRate()      = finalEstimatedFeedRate(),
                         minFeedRate()                 = minFeedRate(),
                         maxFeedRate()                 = maxFeedRate(),
                         initialEstimatedSpindleRate() = initialEstimatedSpindleRate(),
                         finalEstimatedSpindleRate()   = finalEstimatedSpindleRate(),
                         minSpindleRate()              = minSpindleRate(),
                         maxSpindleRate()              = maxSpindleRate(),
                         crossSection(zeta)            = crossSection(zeta),
                         crossSection_D(zeta)          = crossSection_D(zeta),
                         crossSection_DD(zeta)         = crossSection_DD(zeta),
                         max_cross_sec()                = maxCrossSection()],
                         "*pToolPath1D",
                         "Mechatronix#ToolPath1D");
#Describe(mapUserFunctionToRegularized);
mapUserFunctionToRegularized(on_off,"SignRegularizedWithErf");
# 8. Generate Optimal Control Equations and C++ code
defs := [
    M      = 1.0,
    MM     = 0.001,
    CM     = 0.01,
    S      = 1.0,
    MIN    = 60.0,
    KG     = 1.0,
    RAD    = 1.,
    RADS   = 1.,
    RPM    = evalf(Pi/30.0),
    HZ     = 1./S,
    NM     = KG*(M/S)^2,
    WATT   = NM/S,


    nt     = 5,
    Pc_max = 11000*WATT,
    Tc_max = 57.3*NM,
    w_max  = 1500*RPM,
    eta    = 0.9,
    us     = 12.56 * WATT * S / MM^3,
    r      = 31.5*MM,
    min_feed = 0.00001,
    max_feed = 0.166667,
    min_omega =  100*RPM,
    max_omega = 1500*RPM,
    max_feed_acc  = 0.55,
    max_omega_acc = 100,
    f_i           = min_feed*10,
    omega_i       = min_omega,
    f_f           = min_feed,
    omega_f       = min_omega,
    wi            = 0,
    wT_min        = 1.0,
    wT_en         = 1.0,
    wT_Ra         = 1,
    wT_tw         = 1,
    a             = 0.17,
    b             = 0.77,
    n             = 0.37,
    rf            = 0.8,

    CuttingTorque_weight = 1e-4,
    omegaRange_weight    = 1e-4
];
#Describe(generateOCProblem);
generateOCProblem(
   "EPC",
    integral_post_processing     = [
        [target_min_time , "t"],
        [target_roughness, "integralNormalizedRoughness"],
        [target_tool_wear, "integralNormalizedToolWear"]
    ],
    post_processing        = [
        [target_min_time,       "time"],
        [target_roughness,      "roughness"],
        [target_tool_wear,      "toolWear"],
        [vc,                    "cuttingSpeed"],
        [Pc,                    "CuttingPower"],
        [Pc_max,                "maxCuttingPower"],
        [Tc,                    "CuttingTorque"],
        [Tc_max,                "maxCuttingTorque"],
        [max_feed_acc,          "maxFeedAcc"],
        [max_omega_acc,         "maxOmegaAcc"],
        [minFeedRate(),         "minFeedRate"],
        [maxFeedRate(),         "maxFeedRate"],
        [minSpindleRate(),      "minSpindleRate"],
        [maxSpindleRate(),      "maxSpindleRate"],
        [crossSection(zeta),    "crossSection"],
        [crossSection_D(zeta),  "crossSection_D"],
        [crossSection_DD(zeta), "crossSection_DD"],
        [nominalFeedRate(),     "nominalFeedRate"],
        [fguess,                "feedGuess"],
        [o_guess,               "omegaGuess"]
    ],
    parameters   = defs,
    #mesh         = [[length=0.1,n=10],[length=0.4,n=40],[length=0.4,n=40],[length=0.1,n=10]],
    states_guess = [f=fguess, omega=o_guess],
    clean        = false
); #[f=fguess, omega=o_guess]

