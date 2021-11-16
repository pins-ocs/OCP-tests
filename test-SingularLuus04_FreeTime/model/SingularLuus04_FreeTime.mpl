restart:;
with(XOptima):;
#XOptimaInfo() ;
EQ1    :=  diff(x(zeta),zeta) = T(zeta)*y(zeta) :
EQ2    :=  diff(y(zeta),zeta) = T(zeta)*z(zeta) :
EQ3    :=  diff(z(zeta),zeta) = T(zeta)*u(zeta) :
EQ4    :=  diff(T(zeta),zeta) = 0 :
EQNS_T := [ EQ1, EQ2, EQ3, EQ4 ] : <%> ;
qvars := [x(zeta),y(zeta),z(zeta),T(zeta)] ;
cvars := [u(zeta)] ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x,y,z],final=[x,y,z]);
#setBCActivationStatus(initial=[x,y]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = 1,
  epsilon     = u_epsi,
  tolerance   = u_tol,
  scale       = T(zeta)
);
#addUnilateralConstraint( T(zeta) > 0,
#                         TimePositive,
#                         scale     = 1,
#                         epsilon   = 0.1,
#                         tolerance = 0.1,
#                         barrier   = true ) ;
setTarget( lagrange = T(zeta)*(T(zeta)*theta+x(zeta)^2), mayer = 0 ) ;
#setFDorder( [1,2,3], "4th", true ) ;
#setFDorder( [4], "backward", true ) ;
#setFDorderCoEquation( [z], "forward", true ) ;
pars := [ x_i=1, y_i=0, z_i=0, 
          x_f=0, y_f=0, z_f=0, 
          u_epsi     = 0.01,
          u_tol      = 0.01,
          min_u_epsi = 1e-3,
          theta      = theta0,
          theta0     = 1,
          theta1     = 0.01,
          T_guess    = 50 ] ;
CONTINUATION := [
  [ theta = theta0*(1-s)+s*theta1, 
    [u,"epsilon"]=u_epsi*(1-s)+s*min_u_epsi ]
] ;
generateOCProblem(
  "SingularLuus04_FreeTime",
  post_processing   = [[ zeta*T(zeta), "Time"]],
  parameters        = pars,
  admissible_region = [T(zeta)>0,T(zeta)<100],
  continuation      = CONTINUATION,
  #continuation = [[[u,"epsilon"]=u_epsi*(1-s)+s*min_u_epsi]],
  mesh              = [ length=1, n=5000 ],
  states_guess      = [ x=x_i, y=y_i ,z=z_i, T=T_guess]
);
;
