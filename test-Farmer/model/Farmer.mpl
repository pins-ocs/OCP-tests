
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: The Farmer Problem
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# The farmer problem
restart:
with(XOptima):
with(XOptimaPlots):
with(plots):
#with(Optimization):
eqn1 := diff(x1(t),t) + (x1(t) - x1__o(t))/tau__1: # PCr
eqn2 := diff(x2(t),t) + (x2(t) - x2__o(t))/tau__2: # O2
eqn3 := diff(x3(t),t) + (x3(t) - x3__o(t))/tau__3: # La
eqn4 := diff(res(t),t) + (- x3(t) + x4(t))/tau__4:
eqn5 := diff(x4(t),t) + (x4(t) - x4__o(t))/tau__5: 
model_data := [
  tau__1 = 3,
  tau__2 = 25,
  tau__3 = 10,
  tau__4 = 60,
  tau__5 = 120
]:
xvars := [x1(t), x2(t), x3(t), res(t), x4(t)]:
uvars := [x1__o(t), x2__o(t), x3__o(t), x4__o(t)]:
eqns := [eqn||(1..5)]:
subs_tt := [
  x1(t)    = x1,
  x2(t)    = x2,
  x3(t)    = x3,
  res(t)   = res, x4(t) = x4,
  x1__o(t) = x1__o,
  x2__o(t) = x2__o,
  x3__o(t) = x2__o,
  x4__o(t) = x4__o
];
vars_min := [x1, x2, x3, res, x4, x1__o, x2__o, x3__o, x4__o]:
loadDynamicSystem(
  equations = eqns,
  controls  = uvars,
  states    = xvars
);
addBoundaryConditions(
  initial = [
    x1  = x10,
    x2  = x20,
    x3  = x30,
    res = res0, 
    x4  = x40
  ], 
  final = []
):
mayer_target    := 0:
lagrange_target := wP * (1/w1 * x1(zeta)
                     +   1/w2 * x2(zeta)
                     +   1/w3 * x3(zeta) 
                     +   1/w4 * x4(zeta) - Ptot(zeta))^2
                     + w1 * x1(zeta)^2 + w2 * x2(zeta)^2 + w3 * x3(zeta)^2 + w4 * x4(zeta)^2 
                     + wJ1 * (- x1(zeta) + x1__o(zeta))^2 
                     + wJ2 * (- x2(zeta) + x2__o(zeta))^2 
                     + wJ3 * (- x3(zeta) + x3__o(zeta))^2 
                     + wJ4 * (- x4(zeta) + x4__o(zeta))^2:
setTarget(
  lagrange = lagrange_target, 
  mayer    = mayer_target
);
addUnilateralConstraint(
  x2(zeta) + x4(zeta) < 0.12,
  LimitX2X4,
  barrier = false
):
(*
addUnilateralConstraint(
  x3(zeta) >= 0,
  LimitX3,
  barrier = false
):
addUnilateralConstraint(
  x4(zeta) >= 0,
  LimitX4,
  barrier = false
):
*)
(*
addUnilateralConstraint(
  res(zeta) >= 0,
  LimitRes,
  barrier = false
):
addUnilateralConstraint(
  res(zeta) < 15,
  LimitResUp,
  barrier = false
):
*)
;
addControlBound(
  x1__o(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -0.001, 
  max         = 100
):
addControlBound(
  x2__o(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -0.001, 
  max         = 100
):
addControlBound(
  x3__o(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -0.001, 
  max         = 100
):
addControlBound(
  x4__o(zeta),
  controlType = "U_COS_LOGARITHMIC",
  min         = -0.001, 
  max         = 100
):
post_process_outputs := [
  [ 1/w1 * x1(zeta)
    + 1/w2 * x2(zeta)
    + 1/w3 * x3(zeta)
    + 1/w4 * x4(zeta), "power_delivered"],
  [Ptot(zeta),      "power_required"]
]:
(*
Ptot := zeta -> piecewise(zeta>0 and zeta <30,2,
                          zeta>60 and zeta <90,2,
                          zeta>120 and zeta <150,2,
                          0.5):
*)
;
Ptot1 := zeta -> piecewise(zeta>30,100):
Ptot1 := zeta ->  1 + 1 * sin(arctan(zeta - 10)) - 1 - 1 * sin(arctan(zeta - 40));
#plot(Ptot(zeta), zeta = 0..200)
;
Ptot := (zeta) -> simplify((P2-P1)/(t2-t1)* zeta + P1 - (P2-P1)/(t2-t1));
ocp_data := [
  wP  = 1,
  w1  = 1.3,
  w2  = 0.1,
  w3  = 1.2,
  w4  = 0.9,
  wJ1 = 1,
  wJ2 = 1,
  wJ3 = 1,
  wJ4 = 1,
  P1  = 0.1,
  P2  = 0.1,
  t1  = 0,
  t2  = 60
]:
ICs := [
  x10  = 0.001,
  x20  = 0.001, 
  x30  = 0.001, 
  res0 = 0.001, 
  x40  = 0.001
]:
s_guess := [
  x1  = 0.01,
  x2  = 0.01, 
  x3  = 0.01, 
  x4  = 0.01, 
  res = 0.01
]:
project_dir  := "../"; 
project_name := "Farmer";  
generateOCProblem(
  project_name,
  output_directory = project_dir,
  post_processing  = post_process_outputs,
  mesh             = [[length=2,n=400]],
  max_iter         = 120,
  #mesh         = [[length=0.1,n=100],
  #                [length=0.3,n=400],
  #                [length=0.6,n=200]],
  admissible_region = [
    x1(zeta) >=0,
    x2(zeta) >=0,
    x3(zeta) >=0,
    res(zeta)>=0,
    x4(zeta) >=0
  ],
  parameters   = [op(ocp_data), op(model_data), op(ICs)],
  #continuation = continuation_seq,
  states_guess = s_guess
);
launchSolver(project_dir,project_name);
XOptimaPlots:-loadSolution(project_dir,project_name);
display(
  plotSolution(    zeta,    ["res", "x1", "x2", "x3", "x4"],
    line_opts = [      [color="ForestGreen"],
      [color="Orange"],
      [color="Blue"], 
      [color="Red"],
      [color="Green"]    ]  ),
  view = -0.05..0.05,
  axes = boxed,
  size = [800,300]);
display(
  plotSolution(    zeta,    ["res"],
    line_opts = [[color="Orange"]]  ),
  view = 0..0.1,
  axes = boxed,
  size = [800,300]);
display(
  plotSolution(    zeta,    ["power_required", "power_delivered"],
    line_opts = [      [color="Orange"],
      [color="Blue"]    ]  ),
  view = 0..1,
  axes = boxed,
  size = [800,300]);
display(
  plotSolution(    zeta,    ["x1__o", "x2__o", "x3__o", "x4__o"],
    line_opts = [      [color="Black"],
      [color="Red"],
      [color="Green"],
      [color="Black"]    ]  ),
  view = 0..0.1,
  axes = boxed,
  size = [800,300]);

