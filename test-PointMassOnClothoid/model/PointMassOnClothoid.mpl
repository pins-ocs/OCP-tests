
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Point mass obstacle avoidance
# Author: Francesco Biral
# Date:        15/08/2015
# 
# Vehicle model
restart:

xvars := [x(t),y(t),psi(t),u(t),Omega(t)];
Rv := <<cos(psi(t)),sin(psi(t)),0,0>|
       <-sin(psi(t)),cos(psi(t)),0,0>|
       <0,0,1,0>|
       <x(t),y(t),0,1>>;
# Equationso of centre of matrix kinematics: (no slip is with v(t) = 0)
map(diff,<x(t),y(t),0,1>,t) - Rv.<u(t),v(t),0,0>:
eq_kine := [%[1],%[2],diff(psi(t),t)-Omega(t)]: <%>;

# Equations for no-slip driving

eq_psi_dot := diff(psi(t),t) = tan(delta(t))*u(t)/L;

# Equations of curvilinear coordinates
eq_curv_coords := [
  -(diff(s(t), t))*kappa(s(t))*n(t)+diff(s(t), t) =
     cos(alpha(t))*u(t)-sin(alpha(t))*v(t),
  diff(n(t), t) =
     sin(alpha(t))*u(t)+cos(alpha(t))*v(t),
  (diff(psi(t), t)-(diff(alpha(t), t))) =
     diff(s(t), t)*kappa(s(t))]: <%>;


# Longitudinal dynamic equations
eq_u := diff(u(t),t) = a(t)-c0*u(t)-c1*u(t)^2;
# Clothoid:
eq_clothoid := [kappa(t) = kappa0+kappa1*s(t),
                theta(t) = (1/2)*s^2*kappa1+kappa0*s+theta0]: <%>;
# Case with no slip:
eqns_dyn_xy_no_slip := subs(v(t) = 0, [op(eq_kine),eq_u]): <%>;
eqns_dyn_sn_no_slip := collect(subs(v(t) = 0,
                               eq_psi_dot,
                               [op(eq_curv_coords),eq_u]),
                               diff): <%>;
# 
# 
# Case with no slip on reference trajectory: n(t) = 0, alpha(t) = 0:
subs( n(t) = 0, alpha(t) = 0, eqns_dyn_sn_no_slip): <%>;

save( eqns_dyn_xy_no_slip,
      eqns_dyn_sn_no_slip,
      eq_clothoid,
      eq_psi_dot,
      "system_model.mpl"):
# Optimal control with given clothoid
# Problem setup
# Load maple packages
restart:
with(plots):
with(XOptima):
# Dynamic system
# Equation of moving mass: 
# delta(t): steering angle
# v(t):       velocity
# psi(t):     yaw angle
# L:          distance from rear axle to front axle
# (x , y ):   midpoint position of rear axle of car
read("system_model.mpl"):
# Trajectory in x-y coordinates
sol_trj := op(solve([op(eqns_dyn_xy_no_slip[1..2])], diff([x(t),y(t)],t)));
eqns_t := subs( kappa(s(t))=kappa(t),eq_clothoid, 
           [op(eqns_dyn_sn_no_slip), 
            eq_psi_dot, 
           diff(delta(t),t)=v__delta(t),
           diff(a(t),t)=jax(t)]):
          #<%>;
xvars_t := [s(t),n(t),alpha(t),u(t),psi(t),a(t),delta(t)]:
uvars_t := [jax(t),v__delta(t)]:

eqns_t := simplify(simplify(op(solve(eqns_t, diff(xvars_t,t)))),size): <%>;
# 
# 
# Reformulation as free time
# Problem is automa
eqns_s, xvars_s, uvars_s := freeTime(<eqns_t>,xvars_t,uvars_t):
simplify(<eqns_s>,size), <xvars_s>,< uvars_s>;
# Guess solution:
#dsolve({op(eqns_t),
#                 {op(eqns[1..2]),v(0)=0,h(0)=1})):
#guess := {op(%),m(zeta)=m0+(mf-m0)*zeta};
# Load dynamic equations
#Describe(loadDynamicSystem);
loadDynamicSystem(states    = xvars_s,
                  controls  = uvars_s,
                  equations = eqns_s);
                  #,meshFunctions = [kappa(zeta)]) ;
# Lateral acceleration: da sistemare
eq_ay := subs(eq_clothoid,t=zeta, u(t)^2*kappa(t));
# Boundary conditions
# Initial and final state fixed: CoV must free
#Describe(addBoundaryConditions);
addBoundaryConditions(
  initial=[s=0,n=0,alpha=0,psi=0,u=u0,a=a0,delta=0], 
  final  =[s=L,n=0,alpha=0,u=uf,a=af,delta=0]
);
infoBoundaryConditions();
# Target
# 
# Definition of target
#Describe(setTarget);
#setTarget(lagrange= ax(zeta)^2+kappa(zeta)^2,mayer=0);
setTarget(lagrange= 0,mayer=TimeSize(zeta_f));
# Scale factor for penalties
pen_scale := TimeSize(zeta);
# Constraints on states and controls
# Time must be positive
#addCheck([TimeSize(zeta)>0,u(zeta)>=0]);
#addUnilateralConstraint(TimeSize(zeta)>0,PositiveTime,
#                        epsilon   = 0.1e-4, 
#                        tolerance = 0.1e-4,
#                        scale=0);
addBilateralConstraint(delta(zeta),SteeringLimit,
                        min = -delta_max,
                        max = +delta_max,
                        epsilon   = 0.1e-4, 
                        tolerance = 0.1e-4,
                        scale=pen_scale);
addBilateralConstraint(a(zeta),LongAccLimit,
                        active=false,
                        min = -ax_max,
                        max = +ax_max,
                        epsilon   = 0.1e-4, 
                        tolerance = 0.1e-4,
                        scale=pen_scale);
addBilateralConstraint(eq_ay,LateralAccLimit,
                        active=false,
                       min = -ay_max,
                        max = +ay_max,
                        epsilon   = 0.1e-4, 
                        tolerance = 0.1e-4,
                        scale=pen_scale);
# Path constraints
# Right road boarder
# Control constraints
addControlBound(v__delta(zeta),
                controlType="U_COS_LOGARITHMIC",
                min = -vDelta_max, 
                max = vDelta_max,
                #epsilon   = epsi_max, 
                #tolerance = tol_max,
                scale=pen_scale);
addControlBound(jax(zeta),
                controlType="U_COS_LOGARITHMIC",
                min = -jax_max, 
                max =  jax_max,
                #epsilon   = epsi_max, 
                #tolerance = tol_max,
                scale=pen_scale);
# Constraints on states and controls
# OCP generation
# Left and right road edges:
# Left and right wheel position
# we can also monitor some post processing variables as follows
post_process_outputs     := []:
int_post_process_outputs := subs(
  sol_trj, t=zeta, 
  [ [diff(x(t),t)*TimeSize(zeta),"x"],
    [diff(y(t),t)*TimeSize(zeta),"y"] ]
);
# Default values for list of parameters
pars := [
  kappa0     = 0,
  kappa1     = L/1000*0,
  L          = 100,
  jax_max    = 4,
  vDelta_max = evalf(30*Pi/180),
  delta_max  = evalf(30*Pi/180),
  ax_max     = 10,
  ay_max     = 10,
  u0         = 10,
  uf         = 10, 
  a0         = 0,
  af         = 0,
  c0         = 0.05/1000*0,
  c1         = 0.5/1000*0
];
# Guess for state variables
x_guess := [ s=zeta*L, n=0, u=u0, TimeSize=L/u0 ];
#Describe(generateOCProblem);
project_dir  := "../"; #"../ocp-time-domain/"; #cat(currentdir(),"/../ocp/");     # project dir: where code is generated

project_name := "PointMassOnClothoid";  # project name
generateOCProblem(
  project_name,
  #BVP_only                = true,
  output_directory         = project_dir,
  post_processing          = post_process_outputs,
  standard_post_processing = true,
  integral_post_processing = int_post_process_outputs,
  mesh                     = [[length=1,n=200]],
  #continuation            = CONTINUATION,
  states_guess             = x_guess,
  #controls_guess          = [a=0,vDelta = 0],
  parameters               = pars
);
# Analytical problem
interface(rtablesize=22):
ocps   := getOCProblem():
i_ocps := [indices(%,nolist)];

#for ii in i_ocps do:
#  convert(ii,symbol) = ocps[ii]; print(%)
#end:

#sol_u_ott := solve(convert(ocps["optimal_controls_equations"],list),{jax(zeta),jk(zeta)});

#ode_bvp := convert(<ocps["dynamics_system_equations"],ocps["adjoint_equations"]>,list): #<%>;

indices(ocps);
indices(ocps["bvp"]);
tmp := convert(<ocps["bvp"]["boundary_conditions"],
                ocps["bvp"]["transversality_conditions"]>,list): #<%>;
bcs := [op(tmp[1..10]),tmp[-3],tmp[-1]]:# <%>;
#bvp := subs( sol_u_ott, kv=0,[op(ode_bvp) ,op( subs( zeta_L=0, zeta_R=T, bcs))]):# <%>;
#sol_bvp := dsolve(%):

