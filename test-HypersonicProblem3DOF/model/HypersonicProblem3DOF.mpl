restart:;
with(XOptima):;
#mapUserFunctionToObject(
#  [penalization(x)=evaluate(x)],
#  "Pen1D",
#  "Mechatronix#PenaltyBarrier1DGreaterThan",
#  #["epsilon"=pen_epsi,"tolerance"=pen_tol,"subType"="\134"BARRIER_LOG0\134"","active"=true]
#  ["epsilon"=pen_epsi,"tolerance"=pen_tol,"subType"="\134"WALL_TANH_POWER2\134"","active"=true]
#);
#P := x-> -epsilon*log(cos(Pi/2*x));
#M := w-> 2/Pi*arctan(w/epsilon);
CL := CL1*alpha(t)+CL0;
CD := CD2*alpha(t)^2+CD1*alpha(t)+CD0;
LL := rho/2*V(t)^2*CL*Aref/m;
DD := rho/2*V(t)^2*CD*Aref/m;
eta := simplify(sqrt(LL^2+DD^2)) assuming m>0, Aref>0, rho>0;
r   := re+h(t);
g   := mu/r^2;
rho := rho0*exp(-h(t)/S);
SG   := sin(G(t));     CG   := cos(G(t));
SPSI := sin(psi(t));   CPSI := cos(psi(t));
SPHI := sin(phi(t));   CPHI := cos(phi(t));
SS   := sin(sigma(t)); CS   := cos(sigma(t));
RHS1 := V(t)*SG:
RHS2 := V(t)*CG*CPSI/(r*CPHI):
RHS3 := V(t)*CG*SPSI/r:
RHS4 := -DD-g*SG:
RHS5 := LL*CS/V(t)+(V(t)/r-g/V(t))*CG:
RHS6 := LL*SS/(CG*V(t))-(V(t)/r)*CG*CPSI*tan(phi(t)):
RHS7 := sigma_dot_max*u2(t):

EQ1 := diff(h(t),t)     = Tf*( ODE*RHS1 + CTRL*c_h(t)     ):
EQ2 := diff(theta(t),t) = Tf*( ODE*RHS2 + CTRL*c_theta(t) ):
EQ3 := diff(phi(t),t)   = Tf*( ODE*RHS3 + CTRL*c_phi(t)   ):
EQ4 := diff(V(t),t)     = Tf*( ODE*RHS4 + CTRL*c_V(t)     ):
EQ5 := diff(G(t),t)     = Tf*( ODE*RHS5 + CTRL*c_G(t)     ):
EQ6 := diff(psi(t),t)   = Tf*( ODE*RHS6 + CTRL*c_psi(t)   ):
EQ7 := diff(sigma(t),t) = Tf*( ODE*RHS7 + CTRL*c_sigma(t) ):


#EQ1 := diff(h(t),t)     = Tf*( c_h(t)     ):
#EQ2 := diff(theta(t),t) = Tf*( c_theta(t) ):
#EQ3 := diff(phi(t),t)   = Tf*( c_phi(t)   ):
#EQ4 := diff(V(t),t)     = Tf*( c_V(t)     ):
#EQ5 := diff(G(t),t)     = Tf*( c_G(t)     ):
#EQ6 := diff(psi(t),t)   = Tf*( c_psi(t)   ):
#EQ7 := diff(sigma(t),t) = Tf*( c_sigma(t) ):

EQNS_T := [ EQ||(1..7)]:#
#<RHS||(1..7)>;
<EQNS_T>;
qvars := map([h,theta,phi,V,G,psi,sigma],(t));
cvars := map([alpha,u2,c_h,c_theta,c_phi,c_V,c_G,c_psi,c_sigma],(t));
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial = [h,theta,phi,V,G,psi,sigma],
  final   = [h,theta,phi]
);
infoBoundaryConditions();
addUserFunction( h_guess(s)     = h_i*(1-s)+h_f*s         );
addUserFunction( theta_guess(s) = theta_i*(1-s)+theta_f*s );
addUserFunction( phi_guess(s)   = phi_i*(1-s)+phi_f*s     );
addUserFunction( V_guess(s)     = V_i*(1-s)+V_f*s         );
addUserFunction( G_guess(s)     = G_i*(1-s)+G_f*s         );
addUserFunction( psi_guess(s)   = psi_i*(1-s)+psi_f*s     );
setTarget(
  mayer    = WTF*(Tf/Tf_guess-1)^2,
  lagrange = Tf*alpha(zeta)^2-Tf*log(cos(G(zeta)/2))+
             Tf*(c_h(zeta)^2+
                 c_theta(zeta)^2+
                 c_phi(zeta)^2+
                 c_V(zeta)^2+
                 c_G(zeta)^2+
                 c_psi(zeta)^2+
                 c_sigma(zeta)^2)
):;
addControlBound(
  u2,
  controlType = "U_COS_LOGARITHMIC",
  epsilon     = u_epsilon,
  tolerance   = u_tolerance,
  scale       = Tf
);
addBilateralConstraint(
  G(zeta),
  G_bound,
  min       = -Pi,
  max       = Pi,
  epsilon   = 0.1, 
  tolerance = 0.1,
  scale     = Tf, 
  barrier   = true
);
(*
addBilateralConstraint(
  phi(zeta),
  phi_bound,
  min       = -Pi,
  max       = Pi,
  epsilon   = 0.1, 
  tolerance = 0.1,
  scale     = Tf, 
  barrier   = true
);
addBilateralConstraint(
  theta(zeta),
  theta_bound,
  min       = -Pi,
  max       = Pi,
  epsilon   = 0.1, 
  tolerance = 0.1,
  scale     = Tf, 
  barrier   = true
);
addBilateralConstraint(
  psi(zeta),
  psi_bound,
  min       = -Pi,
  max       = Pi,
  epsilon   = 0.1, 
  tolerance = 0.1,
  scale     = Tf, 
  barrier   = true
);
addUnilateralConstraint(
  V(zeta) >= 0,
  V_bound,
  epsilon   = 0.1, 
  tolerance = 0.1,
  scale     = Tf, 
  barrier   = true
);
*);
pars := [

  to_rad  = Pi/180.0,
  to_deg  = 180.0/Pi,
  one_km  = 1000,
  h_i     = 40*one_km,
  theta_i = 0,
  phi_i   = 0,
  V_i     = 2*one_km,
  G_i     = -15*to_rad,
  psi_i   = 0,
  sigma_i = 0,

  h_f     = 0,
  theta_f = 2*to_rad,
  phi_f   = 0.5*to_rad,
  V_f     = 2*one_km,
  G_f     = -15*to_rad,
  psi_f   = 0,
  sigma_f = 0,

  mu      = 3.986e14,
  rho0    = 1.2,
  S       = 7500*one_km,
  m       = 340.19,
  re      = 6378*one_km,
  Aref    = 0.29186,
  sigma_dot_max = 10*to_rad,

  CL1     = 2.5457,
  CL0     = -0.0448,


  CD2     = 3.7677,
  CD1     = -0.1427,
  CD0     = 0.1971,

  pen_epsi    = 0.01,
  pen_tol     = 0.01,
  u_epsilon   = 0.1,
  u_tolerance = 0.1,

  Tf_guess = 100,
  WTF0     = 1,
  WTF1     = 0,
  WTF      = WTF0,

  ODE0 = 0,
  ODE1 = 1,
  ODE  = ODE0,


  CTRL0 = 1,
  CTRL1 = 0,
  CTRL  = CTRL0

];
GUESS := [
  h     = h_guess(zeta),
  theta = theta_guess(zeta),
  phi   = phi_guess(zeta),
  V     = V_guess(zeta),
  G     = G_guess(zeta),
  psi   = psi_guess(zeta),
  sigma = sigma_i
];
UGUESS := [
  alpha = 0,
  u2    = 0
];
POST := [
  [h(zeta),"altitude"],
  [V(zeta),"velocity magnitude"],
  [alpha(zeta)*to_deg,"angle [deg]"],
  [theta(zeta)*to_deg,"longitude [deg]"],
  [phi(zeta)*to_deg,"latitude [deg]"],
  [G(zeta)*to_deg,"velocity flight-path angle [deg]"],
  [psi(zeta)*to_deg,"velocity heading angle [deg]"],
  [sigma(zeta)*to_deg,"bank angle [deg]"],
  [subs(t=zeta,CL),"CL"],
  [subs(t=zeta,CD),"CD"],
  [G(zeta)/Pi,"G_PI"]
]:<%>;
CONT := [
  [ ODE  = ODE0*(1-s) + ODE1 * s ],
  [ WTF  = WTF0*(1-s) + WTF1 * s ],
  [ CTRL = CTRL0*(1-s) + CTRL1 * s ]
];
project_dir  := "../generated_code";
project_name := "HypersonicProblem3DOF";
generateOCProblem(
  project_name,
  parameters              = pars,
  optimization_parameters = [ Tf = Tf_guess ],
  mesh                    = [[length=1,n=400]],
  post_processing         = POST,
  continuation            = CONT,
  states_guess            = GUESS,
  controls_iterative      = true,
  controls_guess          = UGUESS
  #admissible_region       = [ [G(zeta)>-Pi,"node"], [G(zeta)<Pi,"node"] ]
);
# if used in batch mode use the comment to quit;
