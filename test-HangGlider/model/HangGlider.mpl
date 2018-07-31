
# 
#            
# HANG GLIDER (Test 11 di COPS, pag 282 libro Betts)
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello Hang Glider nel tempo
EQ1  := diff(x(t),t)  = vx(t) :
EQ2  := diff(y(t),t)  = vy(t) :
EQ3  := diff(vx(t),t) = (-LL*sin_eta-DD*cos_eta)/m :
EQ4  := diff(vy(t),t) = (LL*cos_eta-DD*sin_eta)/m-g:
<EQ||(1..4)> ;
CD := C0 + k * CL(t)^2;
DD := (1/2) * CD * rho * S * vr^2 ;
LL := (1/2) * CL(t) * rho * S * vr^2 ;
Vy := vy(t) - theta*ua(x(t)) ;
vr := sqrt( vx(t)^2 + Vy^2 ) ;
sin_eta := Vy / vr ;
cos_eta := vx(t) / vr ;
# Cambio di coordinate da tempo a x come variabile indipendente
# Dalla condizione x(t(x)) = x --> vx(t(x)) t'(x) = 1 
# Inoltre diff( f(t(x)), x) = f'(t(x)) t'(x) = f'(t(x))/vx(x)
EQX1 := diff(t(x),x)  = 1/vx(x) :
EQX2 := diff(y(x),x)  = 1/vx(x)*subs(x(x)=x,subs(t=x,rhs(EQ2))) :
EQX3 := diff(vx(x),x) = 1/vx(x)*subs(x(x)=x,subs(t=x,rhs(EQ3))) :
EQX4 := diff(vy(x),x) = 1/vx(x)*subs(x(x)=x,subs(t=x,rhs(EQ4))) :
<EQX||(1..4)> ;
vr := subs(x(x)=x,subs(t=x,vr)) ;
# Cambio di coordinate x = zeta X
# Dalla condizione x = x0 + zeta * X(zeta) con X'(zeta) =0 
# Inoltre diff( f(x(zeta)), zeta) = f'(x(zeta)) x'(zeta) = f'(x(zeta)) X(zeta)
SUBS := t(x)=Tm(zeta),
        y(x)=y(zeta),
        vx(x)=vx(zeta),
        vy(x)=vy(zeta),
        CL(x)=CL(zeta) ;
EQXF1 := diff(Tm(zeta),zeta)  - L(zeta)*subs(SUBS,x=zeta*L(zeta),rhs(EQX1)) :
EQXF2 := diff(y(zeta),zeta)  - L(zeta)*subs(SUBS,x=zeta*L(zeta),rhs(EQX2)) :
EQXF3 := diff(vx(zeta),zeta) - L(zeta)*subs(SUBS,x=zeta*L(zeta),rhs(EQX3)) :
EQXF4 := diff(vy(zeta),zeta) - L(zeta)*subs(SUBS,x=zeta*L(zeta),rhs(EQX4)) :
EQXF5 := diff(L(zeta),zeta) :
<EQXF||(1..5)> ;
vr := subs(ua(x)=ua(zeta*L(zeta)),x=zeta,vr) ;
# Variabili del problema
Describe(addUserFunction);
addUserFunction(ua(x)) ;
# Variabili
xvars := [Tm(zeta),y(zeta),vx(zeta),vy(zeta),L(zeta)] ;
# Controlli
uvars := [CL(zeta)] ;
ode := [EQXF||(1..5)] :
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=ode,
                  controls=uvars,
                  states=xvars) ;
addBoundaryConditions(initial=[Tm,y,vx,vy],final=[y,vx,vy]);
infoBoundaryConditions() ;
addControlBound( CL,
                 controlType="U_COS_LOGARITHMIC", 
                 min=0, max=1.4,
                 tolerance = tol_max, epsilon=epsi_max,
                 scale=L(zeta)/1000 ) ;
addUnilateralConstraint( L(zeta) >0, positiveLen, 
                         tolerance = 1, epsilon=0.01 );
# Target function
setTarget( lagrange=0, mayer = -L(zeta_f)/1000 ) ;
#setFDorder([6],"backward"):
#setFDorderCoEquation([xtau(zeta)],"forward");
addModelExtraParameters([epsi_max,epsi_min,tol_max,tol_min]) ;
PARS := [ Tm_i     = 0,
          epsi_min = 0.0001,
          epsi_max = 0.01,
          tol_min  = 0.0001,
          tol_max  = 0.01,
          y_i      = 1000,
          y_f      = 900,
          vx_i     = 13.2275675,
          vx_f     = 13.2275675,
          vy_i     = -1.28750052,
          vy_f     = -1.28750052,
          m        = 100,
          S        = 14,
          C0       = 0.034,
          rho      = 1.13,
          k        = 0.069662,
          g        = 9.80665,
          theta    = 0 ];
POST := [  [ua(zeta*L(zeta)),"ua"],
  [vr,"vr"],
  [zeta*L(zeta),"x"]];
CONT := [  [theta=s],
  [[CL,"epsilon"]=(1-s)*epsi_max+s*epsi_min],
  [[CL,"tolerance"]=(1-s)*tol_max+s*tol_min]];
GUESS := [  Tm = zeta*100,
  y  = y_i+zeta*(y_f-y_i),
  vx = vx_i,
  vy = vy_i, 
  L  = 1000];
generateOCProblem( "HangGlider",
                   post_processing = POST,
                   parameters      = PARS,
                   continuation    = CONT,
                   # scalature
                   states_scaling    = [y=1000,Tm=100],
                   equations_scaling = [3=Iz],
                   #

                   mesh           = [length=1, n=400],
                   controls_guess = [CL=1],
                   states_guess   = GUESS
                ) ;

