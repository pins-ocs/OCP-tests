
# 
# XOPTIMA Automatic Code Generation for Optimal Control Problems 
# 
# Optimal Control Problem: single mass moved with bounded control 
# Authors: E. Bertolazzi, F. Biral
# Date:
# 
# Motorcycle model
restart:
# Dinamic system (in time domain)
EQ1 := diff(x(t),t) - v(t) ;
EQ2 := diff(v(t),t) - g*(mur(t)+muf(t)) ;

# Coordinate change, use x as independent coordinte
1/diff(t(x),x) - v(t) ;
EQ1 := v(x)*diff(v(x),x) - g*(mur(x)+muf(x)) ;
#EQ1 := diff(v(x),x) - g*(mur(x)+muf(x))/v(x) ; # avoid mass matrix
;
vars := [v(x)];
ctrl := [mur(x),muf(x)];
eqns := [EQ1];
# Optimal control
# Load MBSymba(c) Multibody library and others
# Load optimal control library
with(XOptima):
interface(rtablesize=20):
# Optimal control problem definition
# Load dynamic system
# Load the ODE dynamic system: list of controls, state variables and differential equations.
# By default the command set the indepenedent variable equal to "zeta".
# Map Maple mesh functions to methods of C++ objects 
loadDynamicSystem( equations     = eqns,
                   states        = vars, 
                   controls      = ctrl,
                   meshFunctions = []) ;
# Boundary conditions and jump conditions
# Longitudinal and lateral accelerations as a function respectivelly of pedal  and steer angle.:
addBoundaryConditions(initial = [v],
                      final   = [v]);
# Dispaly the bounddary condition activation status:
infoBoundaryConditions();
# Target: performance criterion
# A small quantity epsilon is added to the denominator to avoid singularities
penScale := 1/v(zeta);
setTarget( lagrange = penScale,
           mayer    = 0);
# Path constraints
# Ellipse of adherence
#addUnilateralConstraint( v(zeta)/vmax <= 2, vMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) <= mur_max, rearTyreAdherenceMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) >= mur_min, rearTyreAdherenceMinLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( muf(zeta) <= 0, frontTyreAdherenceMaxLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( muf(zeta) >= muf_min, frontTyreAdherenceMinLimit, tolerance=0.01, scale=penScale );
#addUnilateralConstraint( mur(zeta) <= Tmax_normalized(v(zeta)),maxTractionLimit,
#                         tolerance=0.01, scale = penScale );
# Control constraints
addControlBound( mur,
                 min = mur_min,
                 max = clip(Tmax_normalized(v(zeta)),0,mur_max),
                 controlType="U_LOGARITHMIC",
                 scale = penScale ) ;
addControlBound( muf,
                 min = muf_min,
                 max = 0,
                 controlType="U_LOGARITHMIC",
                 scale = penScale) ;
mapUserFunctionToRegularized(clip,"ClipIntervalWithSinAtan",["h"=0.01,"delta"=0]) ;
# User defined functions
addUserFunction(Tmax_normalized(v)=Pmax/(m*g)*(1-v/vmax));
#addUserFunction(clip(v,mi,ma)=Pmax/(m*g)*(1-v/vmax));
# Generation of optimal control equations and C++ code
# Set default parameters (optional)
# It is possible to define the default values for all parameters that appear in the full set of equations of the optimal control problem.
# This is an optional command that the user may need if he wish to automatically produce a file data. 
# The command can called more than onec with different arguments which will be added to a global list.
data := [
  g         = 9.81,
  m         = 275,
  mur_max   = 1,
  mur_min   = -1,
  muf_min   = -1,
  #vmur_min = -0.5,
  #vmur_max =  0.5,
  #vmuf_min = -0.5,
  #vmuf_max =  0.5,
  v_i       = 10,
  v_f       = 10,
  #mur_i    = 0,
  #mur_f    = 0,
  #muf_i    = 0,
  #muf_f    = 0,
  Pmax      = 50*1000, # Kwatt
  vmax      = 100
]:
# Post process variables
# Add standard post process variables in the output of the numerical solver: state variables, lagrange multipliers, controls, penalties and mesh variables.
post_list := [
  [Tmax_normalized(v(zeta)), "Tmax_norma"]
] :
# Select upwind
generateOCProblem(  "Bike1D",
  integral_post_processing = [[1/v(zeta),"time"]],
  post_processing          = post_list,
  parameters               = data,
  mesh                     = [ length=1000, n=1000 ],
  states_guess             = [ v = v_i]);

