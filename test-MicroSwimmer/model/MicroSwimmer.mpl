
# Optimal strokes for N-link micro-swimmer.
# Free time formulation in minimum time
# (Giraldi - Martinon - Zoppello)
restart:
# Load XOptima library
with(XOptima):
with(plots):
with(XOptimaPlots):
# States and controls 
# States
Pow:=(xx,pp)->xx^pp;
A:= Matrix([[(-(L2*xi*Pow(cos(theta(zeta)),2)) - L*xi*Pow(cos(beta1(zeta) + theta(zeta)),2) - L*xi*Pow(cos(beta3(zeta) + theta(zeta)),2) - L2*eta*Pow(sin(theta(zeta)),2) - L*eta*Pow(sin(beta1(zeta) + theta(zeta)),2) - L*eta*Pow(sin(beta3(zeta) + theta(zeta)),2),    (eta - xi)*(L2*cos(theta(zeta))*sin(theta(zeta)) + L*cos(beta1(zeta) - beta3(zeta))*sin(beta1(zeta) + beta3(zeta) + 2*theta(zeta))),(L*(L2*xi*cos(beta1(zeta) + theta(zeta))*sin(beta1(zeta)) - L2*xi*cos(beta3(zeta) + theta(zeta))*sin(beta3(zeta)) +          eta*(-((L + L2*cos(beta1(zeta)))*sin(beta1(zeta) + theta(zeta))) + (L + L2*cos(beta3(zeta)))*sin(beta3(zeta) + theta(zeta)))))/2)],[   ((eta - xi)*(L2*cos(theta(zeta))*sin(theta(zeta)) + L*cos(beta1(zeta) - beta3(zeta))*sin(beta1(zeta) + beta3(zeta) + 2*theta(zeta))),-(L2*eta*Pow(cos(theta(zeta)),2)) - L*eta*Pow(cos(beta1(zeta) + theta(zeta)),2) - L*eta*Pow(cos(beta3(zeta) + theta(zeta)),2) - L2*xi*Pow(sin(theta(zeta)),2) -      L*xi*Pow(sin(beta1(zeta) + theta(zeta)),2) - L*xi*Pow(sin(beta3(zeta) + theta(zeta)),2),(L*(eta*(L + L2*cos(beta1(zeta)))*cos(beta1(zeta) + theta(zeta)) - eta*(L + L2*cos(beta3(zeta)))*cos(beta3(zeta) + theta(zeta)) + L2*xi*sin(beta1(zeta) - beta3(zeta))*sin(beta1(zeta) + beta3(zeta) + theta(zeta))))/2)],[((L*(L2*xi*cos(beta1(zeta) + theta(zeta))*sin(beta1(zeta)) - L2*xi*cos(beta3(zeta) + theta(zeta))*sin(beta3(zeta)) + eta*(-((L + L2*cos(beta1(zeta)))*sin(beta1(zeta) + theta(zeta))) + (L + L2*cos(beta3(zeta)))*sin(beta3(zeta) + theta(zeta)))))/2,    (L*(eta*(L + L2*cos(beta1(zeta)))*cos(beta1(zeta) + theta(zeta)) - eta*(L + L2*cos(beta3(zeta)))*cos(beta3(zeta) + theta(zeta)) + L2*xi*sin(beta1(zeta) - beta3(zeta))*sin(beta1(zeta) + beta3(zeta) + theta(zeta))))/2,    (-8*Pow(L,3)*eta - Pow(L2,3)*eta - 6*Pow(L,2)*L2*eta*cos(beta1(zeta)) - 3*L*Pow(L2,2)*eta*Pow(cos(beta1(zeta)),2) - 6*Pow(L,2)*L2*eta*cos(beta3(zeta)) - 3*L*Pow(L2,2)*eta*Pow(cos(beta3(zeta)),2) - 3*L*Pow(L2,2)*xi*Pow(sin(beta1(zeta)),2) - 3*L*Pow(L2,2)*xi*Pow(sin(beta3(zeta)),2))/12)]]):
#A := simplify(subs(L=1,L2=2,xi=1,eta=2,beta1(zeta)=0,theta(zeta)=Pi/2,beta3(zeta)=0,A));
b1:=<((Pow(L,2)*eta*sin(beta1(zeta) + theta(zeta)))/2),-((Pow(L,2)*eta*cos(beta1(zeta) + theta(zeta)))/2),((eta*(Pow(L,3)/3 + (Pow(L,2)*L2*cos(beta1(zeta)))/4)))>;
b3:=<(-(Pow(L,2)*eta*sin(beta3(zeta) + theta(zeta)))/2),((Pow(L,2)*eta*cos(beta3(zeta) + theta(zeta)))/2),((eta*(Pow(L,3)/3 +(Pow(L,2)*L2*cos(beta3(zeta)))/4)))>;
sys3EQ := convert(A.<diff([x(zeta),y(zeta),theta(zeta)],zeta)>-T(zeta)*(b1*u1(zeta)+b3*u3(zeta)),list):
sys3EQlast := [diff(beta1(zeta),zeta)=T(zeta)*u1(zeta),diff(beta3(zeta),zeta)=T(zeta)*u3(zeta),diff(T(zeta),zeta)] ;
qvars := [x(zeta), y(zeta), theta(zeta), beta1(zeta), beta3(zeta), T(zeta)];
# Controls
cvars := [ u1(zeta), u3(zeta) ] ;
# Define the Dinamical System
EQz := [op(sys3EQ),op(sys3EQlast)]:
# Load dynamical system
loadDynamicSystem(equations=EQz,
                  controls=cvars,
                  states=qvars) ;
# Define the target
setTarget( lagrange = wT*T(zeta), mayer = 0*T(zeta_f)
                                +0*(beta1(zeta_i)^2+beta3(zeta_i)^2
                                    +beta1(zeta_f)^2+beta3(zeta_f)^2) ) ;


# Define boundary condition
#Describe(addBoundaryConditions) ;
addBoundaryConditions(initial = [x = xinit,  y = 0, theta = 0, beta1 = 0, beta3 = 0 ],
                      final   = [x = xend,  y = 0, theta = 0 ] ) ;
# Add control range
addControlBound( u1, controlType="U_COS_LOGARITHMIC",
                 maxabs    = 1,
                 epsilon   = epsi,
                 scale     = 1, 
                 tolerance = tol ) ;
addControlBound( u3, controlType="U_COS_LOGARITHMIC",
                 maxabs    = 1,
                 epsilon   = epsi,
                 scale     = 1, 
                 tolerance = tol ) ;
addBilateralConstraint( beta1(zeta),
                        BndBeta1,
                        min       = betamin1,
                        max       = betamax1,
                        epsilon   = epsi_beta1, 
                        tolerance = tol_beta1,
                        scale     = 1, 
                        barrier   = true );
addBilateralConstraint( beta3(zeta),
                        BndBeta3,
                        min       = betamin3,
                        max       = betamax3,
                        epsilon   = epsi_beta3, 
                        tolerance = tol_beta3,
                        scale     = 1, 
                        barrier   = true );
# During iteration avoid T <= 0
addCheck( [ T(zeta)>0] ) ;
project_dir  := "../";
project_name := "MicroSwimmer";  # project name
;
PARS := [ wT         = 0.1,
          L          = 1,
          L2         = 2,
          xi         = 1,
          eta        = 2,
          xinit      = 0,
          xend       = -0.25,
          tf         = 10,
          #b1i        = Pi/12,
          #b3i        = Pi/12,
          betamin1   = -Pi/12,
          betamax1   = Pi/12,
          betamin3   = -Pi/12,
          betamax3   = Pi/12, 
          epsi       = 0.02,
          tol        = 0.01, 
          tol_beta1  = 0.1,
          tol_beta3  = 0.1,
          epsi_beta1 = 0.01,
          epsi_beta3 = 0.01 ] ;
GUESS := [ beta1       = 0,#1/2*sin(2*zeta/tf+Pi/6),
           beta3       = 0,#-1/2*sin(2*zeta/tf+Pi/6),
           T           = tf,
           x           = xinit+zeta*(xend-xinit),
           y           = 0,
           lambda1__xo = 0,
           lambda2__xo = 0 ,
           lambda3__xo = 0,
           lambda4__xo = 0 ,
           lambda5__xo = 1,
           lambda6__xo = 0 ];
CONTINUATION := [ [ ["vLimit","epsilon"]   = (1-s)*0.1 + s*0.001,
                    ["a",     "epsilon"]   = (1-s)*0.1 + s*0.001,
                    ["a",     "tolerance"] = (1-s)*0.1 + s*0.001 ] ] ;
post_proc := [
  [xLane(zeta),"x"],
  [yLane(zeta),"y"],
  [kappa(zeta),"curvature"],
  [v(zeta)^2*abs(kappa(zeta)),        "ay" ],
  [v(zeta)^2*abs(kappa(zeta))-kv_max, "bound" ]
];


generateOCProblem( project_name, clean = false,
                   max_iter         = 1000,
                   tolerance        = 1e-9,
                   parameters       = PARS,
                   post_processing  = [],
                   mesh             = [ [length=1, n=1000]],
                   continuation     = [],
                   #controls_guess  = [ p = 0.5, b=1 ],
                   states_guess     = GUESS ) :
#OCP := getOCProblem() ;
#indices(OCP) ;
#interface(rtablesize=20):
# Compilation and numerical solution
# Open a terminal in the project folder (or windows compiler command prompt) then compile and run with the following command:
# mxint ./<project_name>_run.rb
# You can also lunch it within Maple as follows:
launchSolver(project_dir,project_name);
# Solution analysis
# When you have the solution you can load the result file and plot the result using some command of the package XOptimaPlots  as follows:
XOptimaPlots:-loadSolution(project_dir,project_name);# load solution
;
XOptimaPlots:-getHeaders();

z_sol        := XOptimaPlots:-getSolution(zeta):
#s_sol := XOptimaPlots:-getSolution(s):
v_sol   := XOptimaPlots:-getSolution(v):
a_sol   := XOptimaPlots:-getSolution(a):
time_sol       := XOptimaPlots:-getSolution(T):

XOptimaPlots:-plotSolution(zeta,["ay", "a"],line_opts=
 [[color="DarkOrange"],[color="Blue"]]):
XOptimaPlots:-plotSolution(zeta,["ay"],line_opts=
 [[color="DarkOrange"]]):

display(Array(1..2,[%%, %]));
XOptimaPlots:-plotSolution(zeta,["v"],line_opts=
 [[color="DarkOrange"]]):
XOptimaPlots:-plotSolution(T,["v"],line_opts=
 [[color="DarkOrange"]]):
display(%):

display(Array(1..2,[%%%, %]));
XOptimaPlots:-plotSolution(x,["y"],line_opts= [[color="DarkOrange"]]);
example(Pi);

