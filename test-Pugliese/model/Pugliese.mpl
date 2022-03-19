restart:;
with(XOptima):;
addUserFunction(T_lim(T)=e__C*T/(s__C+T));
addUserFunction(D_lim(DD)=e__D*DD/(s__D+DD));
addUserFunction(IL_lim(IL)=e__IL*IL/(s__IL+IL));
addUserFunction(IL(T,C)=i0+e*C*T/(s+T));
SUBS := T    = T(zeta),
        C    = C(zeta),
        R    = R(zeta),
        DD   = DD(zeta),
        I__p = I__p(zeta);
EQ1  := diff(T(zeta),zeta)    = subs(SUBS,r*(1-T/K)-C*T_lim(T)-kappa__AC*I__p*C*T):
EQ2  := diff(C(zeta),zeta)    = subs(SUBS,D_lim(DD)-C*(mu__C+IL_lim(IL(T,C))+kappa__R*R)):
EQ3  := diff(R(zeta),zeta)    = subs(SUBS,a__R*DD-mu__R*R+a__IL*IL(T,C)):
EQ4  := diff(DD(zeta),zeta)   = subs(SUBS,rho__D-mu__D*DD):
EQ5  := diff(I__p(zeta),zeta) = subs(SUBS,-lambda*I__p):
EQNS := convert([EQ||(1..5)],Vector);
xvars := map([T,C,R,DD,I__p],(zeta));
uvars := [];
loadDynamicSystem(
  equations = EQNS,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial=[
    T=T0,
    C=C0,
    R=R0,
    DD=D0,
    I__p=Ip0
  ]
);
infoBoundaryConditions();
setTarget(
  mayer    = 0,
  lagrange = T(zeta)+w2*(a*I__p(zeta)^2/(b+I__p(zeta)^2))
);
;
;
PARS := [
  r         = 0.006,   # [1/day]
                       # Proliferation rate of CRPC cells
  K         = 107,     # [billion of cells]
  e__C      = 0.75,    # 1/day
                       # Maximal killing rate of tumor by CTL in untreated case
  s__C      = 10,      # [billion of cells]
                       # CTL saturation level for tumor cells inhibition
  kappa__AC = 5.44,    # [1/(day\302\267mg\302\267billion of cells)]
                       # Maximal killing rate of tumor by CTL 
                       # due to the drug ipilimumab
  e__D      = 0.02,    # [billion of cells]/day
                       # Maximal activation rate of CTL by dendritic cells
  s__D      = 0.4,     # [billion of cells]
                       # Dendritic cells saturation level for T cell clonal expansion
  mu__C     = 0.03,    # [1/day]
                       # Death rate of CTL
  e__IL     = 0.1245,  # [1/day]
                       # Maximal activation rate of CTL by IL-2
  s__IL     = 1000,    # [ng/mL]
                       # IL-2 saturation level for T cell clonal expansion
  kappa__R  = 32.81,   # [1/(day*[billion of cells])]
                       # Inactivation rate of CTL by Tregs
  a__R      = 0.072,   # [1/day]
                       # Activation rate of Treg by mature dendritic cells
  mu__R     = 0.72,    # [1/day]
                       # Death rate of Treg
  a__IL     = 131.26,  # [[billion of cells] mL]/(day*ng)]
                       # Activation rate of Treg by IL-2
  rho__D    = 0.00686, # [[billion of cells]/day]
                       # Source of dendritic cells
  mu__D     = 0.14,    # [1/day]
                       # Death rate of dendritic cells
  lambda    = 0.055,   # [1/day]
                       # Ipilimumab death rate
  i0        = 0.00299, # [ng/mL]
                       # Baseline level of IL-2
  e         = 5000,    # ng/[mL\302\267day\302\267[billion of cells]]
                       # Maximal activation rate of IL-2 by CTL
  s         = 10,      # [billion of cells]
                       # Tumor cells saturation level for CTL stimulation

  # toxicity
  t__M = 38.15,
  t__S = 45.15,
  g__M = 1.5,
  g__S = 3.5,

  C__M = (1-1/t__M)*g__M*p__M,
  C__S = (1-1/t__S)*g__S*p__S,

  a = 4.02e-3, #
  b = 4.66,    # mg
  n = 2,       #

  w2 = 500,

  # initial conditions
  T0  = 47,      # billions of cells
  C0  = 2.63e-5, # billions of cells
  R0  = 2.53,    # billions of cells
  D0  = 4.9e-2,  # billions of cells
  Ip0 = 0,       # mg

  YEAR = 365.25
];
POST := [
];
CONT := [];
GUESS := [ T = T0, C = C0, R = R0, DD = D0, I__p = Ip0 ];
MESHP_DEF := [length=5*YEAR, n=400];
project_dir  := "../generated_code";
project_name := "Pugliese";
generateOCProblem(
  project_name,
  post_processing = POST,
  parameters      = PARS,
  continuation    = CONT,
  mesh            = MESHP_DEF,
  states_guess    = GUESS
);
# if used in batch mode use the comment to quit;
