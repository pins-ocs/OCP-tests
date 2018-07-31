
# 
#            
# Problema di Rao e Mease
# 1 controllo
# Inizializzazione
restart:
with(XOptima);
# Equazioni del modello matematico del veicolo
EQ1 := diff(y(t),t)+y(t)^3 = u(t); 
ode   := Vector([EQ1]);
xvars := [y(t)];
uvars := [u(t)];
# Equazioni del modello controllo ottimo
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
# Inserisce condizioni al contorno
addBoundaryConditions(initial=[y],final=[y]);
infoBoundaryConditions() ;
setTarget( lagrange = y(zeta)^2+u(zeta)^2 );

# Target function
MESH1 := [[length=10, n=100],[length=10000-20,n=100],[length=10, n=100]] ;
MESH2 := [["length"=10000, "density_function"=["cheb"=100]]];
MESH3 := [["length"=10000, "density_function"=["C"=50,rho=0.8]]];
generateOCProblem( "RaoAndMease",
                   parameters = [ y_i  = 1.5, y_f  = 1 ],
                   mesh       = MESH3 ) ;

