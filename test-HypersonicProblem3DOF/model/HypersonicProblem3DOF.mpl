restart:;
with(XOptima):;
addUserFunction( CL(alpha)     = CL1*alpha+CL0 );
addUserFunction( CD(alpha)     = CD2*alpha^2+CD1*alpha+CD0 );
addUserFunction( rho(h)        = rho0*exp(-h/S) );
addUserFunction( LL(h,V,alpha) = rho(h)/2*V^2*CL(alpha)*Aref/mass );
addUserFunction( DD(h,V,alpha) = rho(h)/2*V^2*CD(alpha)*Aref/mass );
TF    := exp(logTf);
SCALE := 1;
r := re+h(t);
g := mu/r^2;
SG   := sin(G(t));     CG   := cos(G(t));
SPSI := sin(psi(t));   CPSI := cos(psi(t));
SPHI := sin(phi(t));   CPHI := cos(phi(t));
SS   := sin(sigma(t)); CS   := cos(sigma(t));
RHS1 := V(t)*SG:
RHS2 := V(t)*CG*CPSI/(r*CPHI):
RHS3 := V(t)*CG*SPSI/r:
RHS4 := -DD(h(t),V(t),alpha(t))-g*SG:
RHS5 := LL(h(t),V(t),alpha(t))*CS/V(t)+(V(t)/r-g/V(t))*CG:
RHS6 := LL(h(t),V(t),alpha(t))*SS/(CG*V(t))-(V(t)/r)*CG*CPSI*tan(phi(t)):
RHS7 := u2(t):

EQ1 := diff(h(t),t)     = TF*RHS1:
EQ2 := diff(theta(t),t) = TF*RHS2:
EQ3 := diff(phi(t),t)   = TF*RHS3:
EQ4 := diff(V(t),t)     = TF*RHS4:
EQ5 := diff(G(t),t)     = TF*RHS5:
EQ6 := diff(psi(t),t)   = TF*RHS6:
EQ7 := diff(sigma(t),t) = TF*RHS7:

EQNS_T := [ EQ||(1..7)]:#
<EQNS_T>;
qvars := map([h,theta,phi,V,G,psi,sigma],(t));
cvars := map([alpha,u2],(t));
loadDynamicSystem(
  equations = EQNS_T,
  controls  = cvars,
  states    = qvars
);
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial = [h,theta,phi,V,G,psi,sigma],
  #final   = [h,theta,phi]
  generic = [
    [h(zeta_f)-h_final,"h_final"],
    [to_deg*phi(zeta_f)-phi_final,"phi_final"],
    [to_deg*theta(zeta_f)-theta_final,"theta_final"]
  ]
);
infoBoundaryConditions();
TGUESS := 
  ( h(zeta)     - h_i     )^2 +
  ( theta(zeta) - theta_i )^2 +
  ( phi(zeta)   - phi_i   )^2 +
  ( V(zeta)     - V_i     )^2 +
  ( G(zeta)     - G_i     )^2 +
  ( psi(zeta)   - psi_i   )^2 +
  ( sigma(zeta) - sigma_i )^2;
#BCE := ( h(zeta_f)     - h_final     )^2 +
#       ( theta(zeta_f) - theta_final )^2 +
#       ( phi(zeta_f)   - phi_final   )^2;
BCE := ( h_final     - h_f            )^2 +
       ( theta_final - to_deg*theta_f )^2 +
       ( phi_final   - to_deg*phi_f   )^2;
setTarget(
  mayer    = W_TF*(exp(logTf)/Tf_guess-1)^2 + W_BC*BCE,
  lagrange = alpha(zeta)^2 + W_GUESS*TGUESS
):;
addControlBound(
  u2,
  controlType = "QUADRATIC",
  maxabs      = sigma_dot_max,
  epsilon     = u_epsilon0,
  tolerance   = u_tolerance0,
  scale       = SCALE
);
addControlBound(
  alpha,
  controlType = "U_COS_LOGARITHMIC",
  maxabs      = alpha_max,
  epsilon     = u_epsilon0,
  tolerance   = u_tolerance0,
  scale       = SCALE
);
addBilateralConstraint(
  G(zeta),
  G_bound,
  min       = -2*Pi,
  max       = 2*Pi,
  epsilon   = epsilon0,
  tolerance = tolerance0,
  scale     = SCALE, 
  barrier   = true
);
(*
addBilateralConstraint(
  phi(zeta),
  phi_bound,
  min       = -2*Pi,
  max       = 2*Pi,
  epsilon   = epsilon0,
  tolerance = tolerance0,
  scale     = SCALE, 
  barrier   = true
);
addBilateralConstraint(
  theta(zeta),
  theta_bound,
  min       = -2*Pi,
  max       = 2*Pi,
  epsilon   = epsilon0,
  tolerance = tolerance0,
  scale     = SCALE, 
  barrier   = true
);
*)
addBilateralConstraint(
  psi(zeta),
  psi_bound,
  min       = -2*Pi,
  max       = 2*Pi,
  epsilon   = epsilon0,
  tolerance = tolerance0,
  scale     = TF, 
  barrier   = true
);
addUnilateralConstraint(
  V(zeta) >= -v_tol,
  V_bound,
  epsilon   = epsilon0,
  tolerance = v_tol,
  scale     = TF, 
  barrier   = true
);
addUnilateralConstraint(
  h(zeta) >= h_tol,
  h_bound,
  epsilon   = epsilon0,
  tolerance = h_tol,
  scale     = TF, 
  barrier   = true
);
addBilateralConstraint(
  (theta(zeta)-theta_c)^2+(phi(zeta)-phi_c)^2,
  safety_bound,
  max       = R_max^2,
  min       = R_min^2,
  epsilon   = epsilon0,
  tolerance = tolerance0,
  scale     = TF, 
  barrier   = true
);
pars := [

  to_deg = 180.0/Pi,

  # units
  _m      = 1/1000.,
  _km     = 1,
  _s      = 1,
  _kg     = 1,
  _rad    = 1,
  _degree = Pi/180.0,

  h_tol   = 1*_km,
  v_tol   = 10*_m/_s,
 
  h_i     = 40*_km,
  theta_i = 0*_degree,
  phi_i   = 0*_degree,
  V_i     = 2*_km/_s,
  G_i     = -15*_degree,
  psi_i   = 0*_degree,
  sigma_i = 0*_degree,

  h_f     = 0*_km,
  theta_f = 2*_degree,
  phi_f   = 0.5*_degree,
  
  # non usati nelle BC
  V_f     = 2*_km,
  G_f     = -15*_degree,
  psi_f   = 0*_degree,

  mu      = 3.986e14*_m^3/_s^2,
  rho0    = 1.2*_kg/_m^3,
  S       = 7500*_km,
  mass    = 340.19*_kg,
  re      = 6378*_km,
  Aref    = 0.29186*_m^2,


  sigma_dot_max = 10*_degree/_s,
  alpha_max     = 40*_degree,

  # safety
  theta_c = 1*_degree,
  phi_c   = 0.25*_degree,
  R_min   = 0.35*_degree,
  R_max   = 25*_degree,
  CL1     = 2.5457,
  CL0     = -0.0448,

  CD2     = 3.7677,
  CD1     = -0.1427,
  CD0     = 0.1971,

  u_epsilon0   = 0.25,
  u_tolerance0 = 0.1,
  u_epsilon1   = 0.01,
  u_tolerance1 = 0.01,

  epsilon0   = 0.1,
  tolerance0 = 0.1,
  epsilon1   = 0.01,
  tolerance1 = 0.01,

  Tf_guess     = Tf_guess_min,
  Tf_guess_min = 1,
  Tf_guess_max = 100,

  W_TF0        = 1,
  W_TF1        = 0,
  W_TF         = W_TF0,

  W_GUESS0     = 1,
  W_GUESS1     = 0,
  W_GUESS      = W_GUESS0,

  W_BC0        = 0,
  W_BC1        = 1,
  W_BC2        = 100,
  W_BC         = W_BC0

]:<%>;
GUESS := [
  h     = h_i,
  theta = theta_i,
  phi   = phi_i,
  V     = V_i,
  G     = G_i,
  psi   = psi_i,
  sigma = sigma_i
]:<%>;
UGUESS := [
  alpha = 0,
  u2    = 0
];
PGUESS := [
  logTf       = log(Tf_guess),
  h_final     = h_f,
  phi_final   = to_deg*phi_f,
  theta_final = to_deg*theta_f
];
POST := [
  [ zeta*TF,            "time" ],
  [ h(zeta),            "altitude" ],
  [ V(zeta),            "velocity magnitude" ],
  [ alpha(zeta)*to_deg, "angle [deg]" ],
  [ theta(zeta)*to_deg, "longitude [deg]" ],
  [ phi(zeta)*to_deg,   "latitude [deg]" ],
  [ G(zeta)*to_deg,     "velocity flight-path angle [deg]" ],
  [ psi(zeta)*to_deg,   "velocity heading angle [deg]" ],
  [ sigma(zeta)*to_deg, "bank angle [deg]" ],
  [ CL(alpha(zeta)),    "CL" ],
  [ CD(alpha(zeta)),    "CD" ],
  [ G(zeta)/Pi,         "G_PI" ]
]:<%>;
CONT := [
  # pesa BC
  [ W_BC = (1-s)*W_BC0 + s * W_BC1],
  # rimuove peso guess
  [ W_GUESS = (1-s)*W_GUESS0 + s * W_GUESS1 ],
  # pesa BC
  [ W_BC = (1-s)*W_BC1 + s * W_BC2]
  #[ Tf_guess = (1-s)*Tf_guess_min + s * Tf_guess_max ],
  #[ W_TF = (1-s)*W_TF0 + s * W_TF1 ],
]:<%>;

AAAA := [
  [
    ["G_bound","epsilon"]       = (1-s)*epsilon0   + s * epsilon1,
    ["G_bound","tolerance"]     = (1-s)*tolerance0 + s * tolerance1,
    #["phi_bound","epsilon"]     = (1-s)*epsilon0   + s * epsilon1,
    #["phi_bound","tolerance"]   = (1-s)*tolerance0 + s * tolerance1,
    #["theta_bound","epsilon"]   = (1-s)*epsilon0   + s * epsilon1,
    #["theta_bound","tolerance"] = (1-s)*tolerance0 + s * tolerance1,
    ["psi_bound","epsilon"]     = (1-s)*epsilon0   + s * epsilon1,
    ["psi_bound","tolerance"]   = (1-s)*tolerance0 + s * tolerance1,


    ["V_bound","epsilon"]       = (1-s)*epsilon0 + s * epsilon1,
    ["h_bound","epsilon"]       = (1-s)*epsilon0 + s * epsilon1,

    ["u2","epsilon"]            = (1-s)*u_epsilon0   + s * u_epsilon1,
    ["u2","tolerance"]          = (1-s)*u_tolerance0 + s * u_tolerance1
  ]
]:;
project_dir  := "../generated_code";
project_name := "HypersonicProblem3DOF";
generateOCProblem(
  project_name,
  parameters              = pars,
  optimization_parameters = PGUESS,
  mesh                    = [[length=1,n=400]],
  post_processing         = POST,
  continuation            = CONT,
  states_guess            = GUESS,
  controls_iterative      = true,
  controls_guess          = UGUESS
);
ocp := getOCProblem();
indices(ocp);
ocp["Hamiltonian"];
# if used in batch mode use the comment to quit;
