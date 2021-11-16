restart:;
with(XOptima);
#XOptimaInfo() ;
EQ1 := diff(x(t),t) = u(t) ;
EQNS_T := [ EQ1 ] : <%> ;
qvars := [ x(t) ] ;
cvars := [ u(t) ] ;
loadDynamicSystem(equations=EQNS_T,controls=cvars,states=qvars) ;
addBoundaryConditions(initial=[x],final=[x]);
infoBoundaryConditions() ;
addControlBound(
  u,
  controlType ="U_QUADRATIC",#"U_COS_LOGARITHMIC",
  min         = 0,
  max         = 2,
  epsilon     = 0.01,
  tolerance   = 0.01
);
addModelExtraParameters([epsi_max,tol_max,epsi_min,tol_min]) ;
addUnilateralConstraint(
  x(zeta)-zeta <= u(zeta)-1,
  uMaxBound,
  epsilon   = epsi_max,
  tolerance = tol_max
);
setTarget( lagrange = u(zeta)*(zeta-4) ) ;
#setFDorder([2],"backward"):
#setFDorderCoEquation([u],"forward");
#Describe(generateOCProblem) ;
PARS := [
  x_i      = 0,
  x_f      = 3,
  epsi_max = 0.01,
  epsi_min = 0.001,
  tol_max  = 0.01,
  tol_min  = 0.001
];
CONT := [
  [ [uMaxBound,"epsilon"] = epsi_max*(1-s)+s*epsi_min,
    [uMaxBound,"tolerance"] = tol_max*(1-s)+s*tol_min ]
];
U_GUESS := [ u = min(1.9,max(0.1,(x(zeta)+1-zeta)/2)+1) ];
Describe(generateOCProblem):;
generateOCProblem(
  "SingularConstrainedCalogero",
  integral_post_processing = [ [u(zeta)*(zeta-4), "int_target"] ],
  post_processing          = [ [x(zeta)+1-zeta, "ineq_arg"] ],
  mesh                     = [ length=3, n=600 ],
  parameters               = PARS,
  continuation             = CONT,
  controls_iterative       = true,
  controls_guess           = U_GUESS,
  states_guess             = [ x = zeta]
);
;
