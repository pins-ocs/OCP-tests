restart:
with(plots):
with(XOptima);
with(MBSymba_r6):;
Describe(addCheckParams);
interface(rtablesize=65):
interface(typesetting = extended):  # 'dot' notation for derivatives
interface(displayprecision = 5):    # number of decimal digits
plots[setcolors]("spring"):
plots[setoptions](axes=boxed,size=[1000,"golden"],axis[2]=[gridlines=[linestyle=dot]],
                  #,labelfont= [TIMES,32],
                  # axesfont= [TIMES,16], 
                  titlefont= [TIMES,16]
                  # captionfont= [TIMES,32]
                  );
project_name := "TyreDynamic";
project_dir  := "../generated_code/";
tyre_data := [mu__x0 = 1,  Cx0 = 1.6, Bx0 = 10]:;
MF := x->mu__x0*sin(Cx0*arctan(Bx0*x));
pMF := plot(subs(tyre_data, MF(x)),x=-1..1,axes=boxed,gridlines=true,labels=[kappa__w,F__x/F__z]):
display(pMF,size=[800,300]);
user_fncs_subs := [
  kappa__w(t) = kappa__w(v(t),omega(t)) ,       # slip algebraic definition
  F__x(t)     = F__x(lambda(t)),                # longitudinal force magic formula
  p__pos(t)   = p__pos(p(t)),                   # positive part state control traction
  p__neg(t)   = p__neg(p(t)),                   # negative part state control traction
  b__pos(t)   = b__pos(b(t)),                   # positive part state control braking
  b__neg(t)   = b__neg(b(t)),                   # negative part state control braking
  TT__env(t)  = TT__env(omega(t)),              # envelope engine torque traction
  BT__env(t)  = BT__env(omega(t)),              # envelope engine torque brake 
  TT(t)       = TT(p__pos(p(t)),omega(t)),      # torque applied on the wheel by the engine
  TB(t)       = TB(b__neg(b(t)),omega(t)),      # torque applied on the wheel by the brake
  Fa(t)       = Fa(v(t)),                       # aerodynamic longitudinal drag
  Ma(t)       = Ma(omega(t))                    # aerodynamic rotational drag
] : 
user_fncs_eqns := [
  kappa__w(v,omega)  = omega*rw/v-1,
  F__x(lambda)       = mu__x0*sin(Cx0*arctan(Bx0*lambda))*m*g,###mu__x0*sin(Cx0*arctan(Bx0*lambda))*m*g,
  p__pos(p)          = posPart(p),
  p__neg(p)          = negPart(p),
  b__pos(b)          = posPart(b),
  b__neg(b)          = negPart(b),
  TT__env(omega)     = clipSup(E__pow/abs_reg(omega), TT__max),
  BT__env(omega)     = -clipSup(BT__max/BTv__max*omega, BT__max),
  TT(p__pos,omega)   = p__pos * (TT__env(omega) - BT__env(omega) ) + BT__env(omega),
  TB(b__neg,omega)   = b__neg * TB__max * sign_reg(omega),
  Fa(v)              = 1/2*rho_a*kD*v^2,
  Ma(omega)          = -kDo*sign_reg(omega)*omega^2
]:
<user_fncs_subs>,<user_fncs_eqns>;
eqns_t := subs(
  user_fncs_subs,
  [
    m*diff(v(t),t)                 = F__x(t)-Fa(t),                     # longitudinal dynamic
    Iw*diff(omega(t),t)            = TT(t)+TB(t)-rw*F__x(t)+Ma(t),      # spinning dynamic
    l__x * diff(lambda(t),t)       = ( kappa__w(t)-lambda(t) ) * v(t),  # slip dynamic
    tau__p * diff(p(t),t)   + p(t) = p__o(t),                           # traction control first order dynamic
    tau__b * diff(b(t),t)   + b(t) = b__o(t)                            # braking  control first order dynamic
  ]
): 

<%>;
xvars_t := [v(t),omega(t),lambda(t),p(t),b(t)]: 
uvars_t := [p__o(t), b__o(t)]:;
time2space := proc(XVARS::list,UVARS::list,ODE::list,oldvar::symbol,newvar::symbol,d_new)
    local XVARS2SPACE, UVARS2SPACE, ODE2SPACE:
    local diff_subs:
    XVARS2SPACE := subs( oldvar = newvar, XVARS):
    UVARS2SPACE := subs( oldvar = newvar, UVARS):
    diff_subs := map(x-> diff(x,t) = diff(x,t)*d_new, XVARS):
    ODE2SPACE := subs( oldvar = newvar, s(newvar)=newvar ,subs(diff_subs, ODE  ) )  : 
    return XVARS2SPACE, UVARS2SPACE, ODE2SPACE
end:;
ODEwfunc  := eqns_t:<%>;
ODExvars := xvars_t;
ODEuvars := uvars_t;
dnew:= zeta__dot = v(t);
ODExvars, ODEuvars, ODEwfunc := time2space(ODExvars, ODEuvars, ODEwfunc,t,zeta, subs(dnew, zeta__dot) ):;
ODEwfunc: <%>;
ODExvars;
ODEuvars;
loadDynamicSystem(
  states    = ODExvars,  
  controls  = ODEuvars,
  equations = ODEwfunc 
);
penaltyScale := subs(dnew, t=zeta, 1/zeta__dot);
ICs := [v=v__ss, b=b__ss];
FCs := [v=v__ss];
EQGC := subs( diff(ODExvars,zeta)=~0, zeta=zeta_i, ODEwfunc[1..3]):
NameGC := ["lambda__i","p__i","omega__i"]:
GCs := [seq([EQGC[i],NameGC[i]],i=1..nops(EQGC))];
<%>;
addBoundaryConditions(initial = ICs, final = FCs, generic = GCs );
mayer_target    := 0 :
lagrange_target := subs( dnew, t=zeta, 1/zeta__dot) * ( w__t + w__U *( <ODEuvars>^%T . <ODEuvars> ) ):
setTarget(lagrange=  lagrange_target, mayer = mayer_target);
addControlBound(
  b__o(zeta),
  controlType="U_COS_LOGARITHMIC",
  min        = -1, 
  max        =  1,
  epsilon    = eps_c, 
  tolerance  = tol_c,
  scale      = penaltyScale
);
addControlBound(
  p__o(zeta),
  controlType="U_COS_LOGARITHMIC",
  min        = -1, 
  max        =  1,
  epsilon    = eps_c, 
  tolerance  = tol_c,
  scale      = penaltyScale
);
addUnilateralConstraint(
  b(zeta) <= h__b,
  "OnlyBrakingRear",
  subtype    = "PENALTY_PIECEWISE",
  active     = true, 
  tolerance  = h__b,
  scale      = penaltyScale
);

addUnilateralConstraint(
  p(zeta) >= -h__b,
  "OnlyTractionRear",
  subtype    = "PENALTY_PIECEWISE",
  active     = true,
  tolerance  = h__b,
  scale      = penaltyScale
);
addBilateralConstraint(
  lambda(zeta) / lambda__max,
  "LongSlipRear",
  min        = -1,
  max        =  1,
  active     = true,
  subtype    = "PENALTY_PIECEWISE",
  epsilon    = eps_l, 
  tolerance  = tol_l,
  scale      = penaltyScale
);
addUnilateralConstraint(
  v(zeta) - 1 >= 0,
  "v_min",
  barrier = true,
  subtype    = "BARRIER_LOG",
  epsilon    = eps_l, 
  tolerance  = tol_l,
  scale      = penaltyScale
);
constraints_params := [
  v__adm      = 1,
  lambda__max = 1
];
ADMISSIBLE_REGIONS := [ v(zeta) > v__adm ];
CONTINUATION := [

  [ w__t  = w__t0  + (w__t1  - w__t0 )*s ], # push the minimum time

  [ ["p__o",   "epsilon"]   = eps_c0 + (eps_c1 - eps_c0)*s ,
    ["p__o", "tolerance"]   = tol_c0 + (tol_c1 - tol_c0)*s ,
    ["b__o",   "epsilon"]   = eps_c0 + (eps_c1 - eps_c0)*s ,
    ["b__o", "tolerance"]   = tol_c0 + (tol_c1 - tol_c0)*s
  ]
] ;
ADD_PARAMS := [
  h__b = 1,

  eps_l = 0.01,
  tol_l = 0.01,

  eps_c =eps_c0,
  tol_c =tol_c0,
               
  eps_c0=0.1,
  tol_c0=0.1,
               
  eps_c1=0.01,
  tol_c1=0.01
];
WEIGHTS := [
  w__t = w__t0,
  w__t0 = 1, ### 0.01,
  w__t1 = 1,
  w__U  = 1E-4
];
for i from 1 to nops(user_fncs_eqns) do
   addUserFunction(user_fncs_eqns[i]):
end do:;
mapUserFunctionToRegularized( posPart,  "PositivePartRegularizedWithErf",  [h=0.01]);
mapUserFunctionToRegularized( negPart,  "NegativePartRegularizedWithErf",  [h=0.01]);
mapUserFunctionToRegularized( clipSup,  "ClipSuperior",                    [h=0.01]) ;
mapUserFunctionToRegularized( clipInt,  "ClipIntervalWithErf",             [h=0.01]) ;  
mapUserFunctionToRegularized( sign_reg, "SignRegularizedWithErf",          [h=0.01]) ;
mapUserFunctionToRegularized( abs_reg,  "AbsoluteValueRegularizedWithErf", [h=0.01]) ;
post_process_outputs :=[
  [F__x(lambda(zeta))/(m*g),  "Fx_norm"],
  seq([subs(t=zeta,rhs(user_fncs_subs[i])),convert(op(0,lhs(user_fncs_subs[i])),string)], i=1..nops(user_fncs_subs))
]:
<%>;
int_post_proc := [
  [ subs( t=zeta, eval( 1/zeta__dot , dnew ) )   ,   "time"      ],
  [ v(zeta)*penaltyScale, "x" ]
];
POW := 60*800: 
display(plot(min(800,POW/omega),omega=0.1..300),
        plot(1/2*1.1839*0.2*(omega*0.3)^2,omega=0.1..300,color="blue"),
        plot(-min(300/50*omega,300),omega=0.1..300,color="purple"),
        axes=boxed,view=[0..300,-400..1400],
        axis[2] = [gridlines=[linestyle=dot]],
        size    = [800,400]);
OCP_data := [# wheel data - - - - - - - - 
             m  = 230/2, 
             g  = 9.81, 
             Iw = 0.4351,
             tau__p = 0.1,
             tau__b = 0.1,
             l__x   = 0.1,
             op(tyre_data),
             rw = 0.3,
             kD = 0.2, #aerodynamic drag force splitted equal for each wheel
             kDo= 0.001,
             E__pow      = 60*TT__max, 
             TT__max     = 800,
             TB__max     = 500,
             BT__max     = 300,
             BTv__max   = 50,
 
             # initial and final conditiosn - - - - - - - 
             v__0     = 10, 
             omega__0 = v__0/rw,
             
             ## steady states
             v__ss = 10.0,
             omega__ss = 33.351785,
             lambda__ss = 0.000554,
             p__ss = 0.175698,
             b__ss = 0.1,


             ## other
             op(ADD_PARAMS),
             op(WEIGHTS),
             op(constraints_params),
             L = 300,
             mesh_np = L/0.5,
             rho_a = 1.1839         
];
PARAMETERS := OCP_data;
;
x_guess := [
 v      =  v__ss,
 omega  = omega__ss,
 lambda = lambda__ss,
 p      = p__ss,
 b      = b__ss
];

u_guess  := [p__o = p__ss, b__o = b__ss];
### addUserFunction(a(t)=0 , derivatives=0);
bound_data :=
[v__ub = 10^4 , omega__ub = 10^4 , lambda__ub = +1, p__ub = +1, b__ub = +1,
 v__lb = 0    , omega__lb = 0    , lambda__lb = -1, p__lb = -1, b__lb = -1,
 p__o__ub = +1, b__o__ub  = +1   ,
 p__o__lb = -1, b__o__lb  = -1   ];
map(x->cat(op(0,x),__ub),ODExvars);
map(x->cat(op(0,x),__lb),ODExvars);
map(x->cat(op(0,x),__ub),ODEuvars);
map(x->cat(op(0,x),__lb),ODEuvars);
map(x->cat(op(0,x),__ub)*cat(op(0,x),__lb),ODExvars);
map(x->cat(op(0,x),__ub)*cat(op(0,x),__lb),ODEuvars);
< op(%%), op(%) >:
tmp_F := B_data() = %^%T . %;
### addUserFunction( B_data(), derivatives = 1);
##  map(x-> addUserFunction( cat(B__,op(0,x),__ub)() = cat(op(0,x),__ub) ) ,ODExvars);
##  map(x-> addUserFunction( cat(B__,op(0,x),__lb)() = cat(op(0,x),__lb) ) ,ODExvars);
##  map(x-> addUserFunction( cat(B__,op(0,x),__ub)() = cat(op(0,x),__ub) ) ,ODEuvars);
##  map(x-> addUserFunction( cat(B__,op(0,x),__lb)() = cat(op(0,x),__lb) ) ,ODEuvars);
PARAMETERS := [op(PARAMETERS), op(bound_data)];
Mesh := [
  [length=0.1*L, n=round(0.1*mesh_np*4)],
  [length=0.8*L, n=round(0.8*mesh_np)],
  [length=0.1*L, n=round(0.1*mesh_np*4)]
];
generateOCProblem(
  project_name,           
  BVP_only                 = false,
  max_accumulated_iter     = 1500,
  max_step_iter            = 40,
  mesh                     = Mesh,
  standard_post_processing = true,
  integral_post_processing = int_post_proc,
  output_directory         = project_dir,
  states_guess             = x_guess,
  parameters               = PARAMETERS,
  user_parameters          = map(lhs,bound_data),
  continuation             = CONTINUATION,
  post_processing          = post_process_outputs,
  admissible_region        = ADMISSIBLE_REGIONS
);
