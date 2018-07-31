
# 
#            
# Modello Massa
# 
# 1 controllo
# (Problema tempo fisso, massima distanza)
# Inizializzazione
restart:
with(XOptima):
# Equazioni del modello matematico del veicolo
EQ1 := diff(x(t),t) - v(t) ;
EQ2 := diff(v(t),t) - (Fp(t)-Fm(t)) ;
EQNS_T := [EQ||(1..2)];
# Variabili del problema e controlli
# Variabili
qvars := [x(t),v(t)] ;
# Controlli
cvars := [Fp(t),Fm(t)] ;
# Equazioni del modello matematico del carrello
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,v=0],final=[x=1,v=0]);
infoBoundaryConditions() ;
# Penalty
addControlBound( Fp, label = "controlP", min = 0, max = FpMax, controlType="U_CUBIC" ) ;
addControlBound( Fm, label = "controlM", min = 0, max = FmMax, controlType="U_CUBIC" ) ;
setTarget(lagrange = Fp(zeta)+Fm(zeta)) ;
generateOCProblem( "BangBangFmodule",
                    post_processing = [[controlP(Fp(zeta),0,FpMax),"ForceP"],
                                       [controlM(Fm(zeta),0,FmMax),"ForceM"],
                                       [Fp(zeta)-Fm(zeta),"F"]],
                    parameters   = [FmMax = 10, FpMax = 10],
                    mesh         = [length=1, n=100],
                    states_guess = [ x = zeta ] ) ;

