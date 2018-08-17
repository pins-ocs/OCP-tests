
# 
# Bike overtake
# Inizializzazione
restart:
with(XOptima):
XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
FX1 := fmax1*(1-v1(t)*gr/(rw*omega_max)) ;
FX2 := fmax2*(1-v2(t)*gr/(rw*omega_max)) ;
# Equazione prima bici (che deve superare)
EQ1 := diff(s1(t),t)    = v1(t) ;
EQ2 := m1*diff(v1(t),t) = u(t)*FX1 - K1*r(s1(t)-s2(t))*v1(t)^2 ;
# Equazione seconda bici
EQ3 := diff(s2(t),t)    = v2(t) ;
EQ4 := m2*diff(v2(t),t) = u(t)*FX2 - K2*r(s2(t)-s1(t))*v2(t)^2;
#Describe(freeTime) ;
ode, xvars, uvars := freeTime( [EQ||(1..4)], [s1(t),v1(t),s2(t),v2(t)], [u(t)], "lin" );
# Equazioni del modello matematico
#infoRegisteredObjects() ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[s1=0,s2=s2_0,v1=v0,v2=v0],
                      final=[s1=L]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u, controlType="U_COS_LOGARITHMIC", 
                 min=0, max=1,
                 epsilon=0.01, tolerance=0.01,
                 scale=1) ;
setTarget( mayer    = TimeSize(zeta_f)*s2(zeta_f)/L,
           lagrange = TimeSize(zeta)*epsilon*u(zeta) ) ;
#SCIA_DATA := [ "x" = [-10*lbike, -2*lbike, -lbike, -lbike/10, 0, lbike/2, lbike, 100*lbike],
#               "y" = [        1,        1,    1/2,       1/2, 1,     1.1,     1, 1 ] ] ;
#mapUserFunctionToObject([scia(zeta)=evaluate(zeta)],
#                         "SciaSpline",
#                         #"Mechatronix#PchipSpline",
#                         "Mechatronix#QuinticSpline",
#                         SCIA_DATA);
addUserFunction(r(x)=1+(33/25)*(x+lbike)/sqrt(1+(6*x+6*lbike)^2)-(11/25)*(x+scia)/sqrt(1+(2*x+2*scia)^2));
PARAMS := [ L         = 500,
            K1        = 0.004,
            K2        = 0.004,
            fmax1     = 650,
            fmax2     = 650,
            gr        = 3.8,
            m1        = 84,
            m2        = 84,
            rw        = 0.335,
            omega_max = 16,
            lbike     = 1.5,
            scia      = 3,
            epsilon   = e_max,
            v0        = 40/3.6,
            s2_0      = 1.1*lbike, # seconda bici un po avanti
            e_max     = 1,
            e_min     = 1e-6] ; 
            #w         = 0 ] ;
CONTINUATION := [ [ epsilon=e_max+s*(e_min-e_max) ]] ;
#setFDorder([x],"forward") ;
#Describe(generateOCProblem):
GUESS := [ v1       = v0,
           v2       = v0, 
           s1       = zeta*L,
           s2       = zeta*L+s2_0,
           TimeSize = L/v0 ] ;
POST := [ [r(-2*lbike+4*zeta*lbike), "r"]
];
ADMISSIBLE := [[TimeSize(zeta)>0,"cell"], v1(zeta)>0, v2(zeta)>0 ] ;
#Describe(generateOCProblem) ;
generateOCProblem( "BicycleOvertake", clean=false,
                   language          = "C++",
                   parameters        = PARAMS,
                   post_processing   = POST,
                   mesh              = [ length=1, n=1000 ],
                   admissible_region = ADMISSIBLE,
                   states_guess      = GUESS,
                   continuation      = CONTINUATION,
                   max_iter          = 500,
                   max_step_iter     = 50,
                   max_accumulated_iter = 2000 ) ;
#XOptimaSUBS:-info();

