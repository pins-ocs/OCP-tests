
# 
#            
# Modello Massa
# 
# 1 controllo
# (Problema tempo fisso, tempo minimo)
# Inizializzazione
restart:
with(XOptima):
# ODE
EQ1 := diff(x(t),t) - T*v(t) ;
EQ2 := diff(v(t),t) - T*F(t) ;
ode   := <EQ1,EQ2> ;
uvars := [ F(t) ] ;
xvars := [ x(t), v(t) ] ;
pars  := [ T ] ;
# OCP
#Describe(loadDynamicSystem) ;
xvars ;
loadDynamicSystem(equations=ode,controls=uvars,states=xvars,parameters=pars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[x=0,v=0],final=[x=2,v=0]);
infoBoundaryConditions() ;
# Penalty
addControlBound( F, label=Fcontrol, maxabs=1, scale=T) ;
#addUnilateralConstraint( T>=0, "Tpos", barrier=true) ;
# Generazione del problema di controllo ottimo
setTarget(mayer = T) ;
generateOCProblem( "BangBangFtminP", clean=true,
                   parameters        = [ Tinit = 1 ],
                   mesh              = [[length=0.1,n=10],
                                        [length=0.4,n=40],
                                        [length=0.4,n=40],
                                        [length=0.1,n=10]],
                   states_guess      = [x=zeta,v=1],
                   admissible_region = [T>0],
                   parameters_guess  = [T=Tinit] ) ;

