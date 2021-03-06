
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: OCP from 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Structure Exploitation in an Interior- Point Method for Fully Discretized, State Constrained Optimal Control Problems
# Andreas Huber, Matthias Gerdts & Enrico Bertolazzi
# Vietnam Journal of Mathematics, 2019
restart:
with(XOptima):
#`diff/h`   := proc() h_1(args[1])*diff(args[1],args[2]) end:
#`diff/h_1` := proc() h_2(args[1])*diff(args[1],args[2]) end:
with(plots):
# Dynamic system equations
ODE1 := diff(x1(t),t)=x2(t);
ODE2 := diff(x2(t),t)=u(t);
ODE3 := diff(x3(t),t)=u(t)^2/2;
ode   := subs(t=zeta,Vector([ODE1,ODE2,ODE3]));
xvars := [x1(zeta),x2(zeta),x3(zeta)] ;
uvars := [u(zeta)] ;

# Optimal Contol Problem
loadDynamicSystem(equations=ode,controls=uvars,states=xvars) ;
addBoundaryConditions(initial=[x1,x2,x3],final=[x1,x2]);
infoBoundaryConditions() ;
# Penalty description
addUnilateralConstraint( x1(zeta) <= 1/9, x1Limitation,
                         epsilon = 0.001,
                         tolerance = 0.001,
                         scale = 1+0*u(zeta)^2/2 );
setTarget( mayer = x3(zeta_f) ) ;
generateOCProblem( "GerdtsKunkel",
                   parameters = [ x1_i   = 0,
                                  x2_i   = 1,
                                  x3_i   = 0,
                                  x1_f   = 0,
                                  x2_f   = -1],
                   mesh         = [length=1, n=1000],
                   states_guess = [lambda2__xo=0, lambda3__xo=-1 ] ) ;

# penalty che dipendono dagli ingressi
