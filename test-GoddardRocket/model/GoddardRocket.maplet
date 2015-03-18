# 
#            
# Goddard Rocket (from COPS3)
# 
# 1 controllo
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello matematico
# Pressione dinamica
Dhv := CD*A*(rho0/2)*v(t)^2*exp(beta*(1-h(t)))/m0/g ;

Dhv := algsubs( rho0*CD*A/m0/g=CF,Dhv) ;
EQ1  := diff(h(t),t) - v(t) ;
EQ2  := diff(v(t),t) - ((T(t)-Dhv)/m(t)) + 1/h(t)^2 ;
EQ3  := diff(m(t),t) + T(t)/c ;
EQNS := convert([EQ||(1..3)],Vector) ;
# Variabili del problema
# Variabili
vars := [h(t),v(t),m(t)] ;
# Controlli
ctrls := [T(t)] ;
# Equazioni del modello matematico del razzo
ode, xvars, uvars := freeTime( EQNS, vars, ctrls, "log" ) ;
TS := exp(logTimeSize(zeta));
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[h,v,m],final=[m]);
infoBoundaryConditions() ;
# Penalty description
addUnilateralConstraint( m(zeta)>=0, massPositive, tolerance=0.01, epsilon=0.01 );
addUnilateralConstraint( v(zeta)>=0, vPositive, tolerance=0.01, epsilon=0.01 );
addUnilateralConstraint( h(zeta)>=1, hPositive,  tolerance=0.01, epsilon=0.01  );
# penalty che dipendono dagli ingressi
addControlBound( T, min=0, max=Tmax, tolerance = 0.01, epsilon=0.01) ;
setTarget( lagrange = -v(zeta)*TS);
generateOCProblem( "GoddardRocket",
                    post_processing    = [[zeta*TS,"Time"],[v(zeta)*TS,"target"]],
                    parameters = [ v_i  = 0,
                                   v_f  = 0,
                                   h_i  = 1,
                                   h_f  = 0,
                                   m_i  = 1,
                                   m_f  = 0.6,
                                   beta = 500,
                                   c    = 0.5,
                                   CF   = 620,
                                   Tmax = 3.5 ],
                     mesh     = [length=1, n=1000],
                     states_guess = [ h=h_i, v=v_i, m=m_i, logTimeSize=log(Tmax) ] ) ;

