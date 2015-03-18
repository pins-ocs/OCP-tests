# 
#            
# Underwater vehicle
# Inizializzazione
restart:
with(XOptima):
#XOptimaInfo() ;
# Equazioni del modello matematico del veicolo
g1 := u1(zeta)/m1 ;
g2 := u2(zeta)/m3 ;
g3 := u3(zeta)/inertia ;
EQ1    := diff(x(zeta),zeta)     = T(zeta)*(vx(zeta)*cos(theta(zeta))+vz(zeta)*sin(theta(zeta))):
EQ2    := diff(z(zeta),zeta)     = T(zeta)*(vz(zeta)*cos(theta(zeta))-vx(zeta)*sin(theta(zeta))):
EQ3    := diff(theta(zeta),zeta) = T(zeta)*Omega(zeta):
EQ4    := diff(vx(zeta),zeta)    = T(zeta)*(g1-vz(zeta)*Omega(zeta)*(m3/m1)):
EQ5    := diff(vz(zeta),zeta)    = T(zeta)*(g2+vx(zeta)*Omega(zeta)*(m1/m3)):
EQ6    := diff(Omega(zeta),zeta) = T(zeta)*(g3+vx(zeta)*vz(zeta)*(m3-m1)/inertia):
EQ7    := diff(T(zeta),zeta)     = 0 :
EQNS_T := [ EQ||(1..7) ]: <%> ;
# Variabili del problema e controlli
# Variabili
qvars := [x(zeta),z(zeta),theta(zeta),vx(zeta),vz(zeta),Omega(zeta),T(zeta)] ;
# Controlli
cvars := [u1(zeta),u2(zeta),u3(zeta)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x,z,vx,vz,theta],final=[x,z,vx,vz,theta]);
infoBoundaryConditions() ;
# Penalty
addControlBound( u1,
                 scale       = T(zeta),
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty,
                 scale       = T(zeta)) ;
addControlBound( u2,
                 scale       = T(zeta),
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty,
                 scale       = T(zeta) ) ;
addControlBound( u3,
                 scale       = T(zeta),
                 controlType = "U_COS_LOGARITHMIC",
                 maxabs      = 1,
                 epsilon     = epsi_penalty,
                 tolerance   = tol_penalty,
                 scale       = T(zeta) ) ;
addUnilateralConstraint( T(zeta) > 0,
                         TimePositive,
                         scale     = 1,
                         epsilon   = 0.01,
                         tolerance = 0.01,
                         barrier   = true ) ;
# Generazione del problema di controllo ottimo
#setFDorder([5],"backward"):
#setFDorderCoEquation([theta],"forward"):
# Post processing functions
setTarget( mayer = T(zeta_f) ) ;

pars := [ inertia      = 0.12,
          epsi_penalty = 0.1,
          tol_penalty  = 0.01,
          x_i = 0, x_f = 2,
          z_i = 1, z_f = 1,
          vx_i = 0, vx_f = 0,
          vz_i = 0, vz_f = 0,
          theta_i = 0, theta_f = 0,
          m1 = 13.2,
          m3 = 25.6,
          Tguess = 10 ] ;
cont := [# prima continuazione
         [inertia = (1-s)*1.5+s*0.12],
         # seconda continuazione
         [epsi = (1-s)*0.1+s*1e-7,
          [u1,"epsilon"] = epsi,
          [u2,"epsilon"] = epsi,
          [u3,"epsilon"] = epsi]
        ];
generateOCProblem( "Underwater",
                    #post_processing = [[T(zeta),"minTime"]],
                    parameters   = pars,
                    mesh         = [length=1,n=1000],
                    continuation = cont,
                    states_guess = [x     = x_i+zeta*(x_f-x_i),
                                    z     = z_i+zeta*(z_f-z_i),
                                    theta = 0,
                                    vx    = (x_f-x_i)/Tguess,
                                    vz    = sin(zeta*6.28)/Tguess,
                                    Omega = 0,
                                    T     = Tguess]) ;

