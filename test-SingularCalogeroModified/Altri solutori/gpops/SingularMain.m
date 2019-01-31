
% SINGULAR CONTROL PROBLEM
% min int((x-1+t^2)^2,t=-1..1)
% subject to
% x'=u
% |u|<= 1

clear all
close all
clc

global CONSTANTS 

CONSTANTS.g = 9.81;
t0 = -1.0 ;
tf =  1.0 ;
x0 = 3/16;
% y0 = 0;
% v0 = 0;
 xf = 1+19/16;
% yf = -3;
  xmin = 0;
  xmax =  3;
% ymin = -5;
% ymax =  1;
% vmin = -0.1;
% vmax = xmax;
param_min = [];
param_max = [];
path_min = [];
path_max = [];
event_min = [];
event_max = [];
duration_min = [];
duration_max = [];

iphase = 1;
limits(iphase).time.min = [t0 tf];
limits(iphase).time.max = [t0 tf];
 limits(iphase).state.min(1,:) = [x0 xmin xf ];
 limits(iphase).state.max(1,:) = [x0 xmax xf ];
% limits(iphase).state.min(2,:) = [y0 ymin yf];
% limits(iphase).state.max(2,:) = [y0 ymax yf];
% limits(iphase).state.min(3,:) = [v0 vmin vmin];
% limits(iphase).state.max(3,:) = [v0 vmax vmax];
limits(iphase).control.min    = -1;
limits(iphase).control.max    =  1;
limits(iphase).parameter.min  = param_min;
limits(iphase).parameter.max  = param_max;
limits(iphase).path.min       = path_min;
limits(iphase).path.max       = path_max;
limits(iphase).event.min      = event_min;
limits(iphase).event.max      = event_max;
limits(iphase).duration.min    = duration_min;
limits(iphase).duration.max    = duration_max;
guess(iphase).time             = [t0; tf];
 guess(iphase).state(:,1)      = [0; 0];
% guess(iphase).state(:,2)      = [y0; yf];
% guess(iphase).state(:,3)      = [v0; 10];
guess(iphase).control         = [0; 0];
guess(iphase).parameter       = [];

setup.name  = 'Singular control Problem';
setup.funcs.cost = 'SingularCost';
setup.funcs.dae = 'SingularDae';
setup.limits = limits;
setup.guess = guess;
setup.linkages = [];
setup.derivatives = 'finite-difference';
setup.autoscale = 'off';
setup.mesh.tolerance = 1e-4;
setup.mesh.iteration = 20;
setup.mesh.nodesPerInterval.min = 4;
setup.mesh.nodesPerInterval.max = 12;

[output,gpopsHistory] = gpops(setup);
solution = output.solution;
solutionPlot = output.solutionPlot;

subplot(2,1,1);
plot( solutionPlot.time,  ...
      solutionPlot.state, ...
      '-o','DisplayName', ...
      'solutionPlot.state', ...
      'YDataSource',  ...
      'solutionPlot.state');

subplot(2,1,2);
plot( solutionPlot.time,  ...
      solutionPlot.control, ...
      '-o','DisplayName', ...
      'solutionPlot.state', ...
      'YDataSource',  ...
      'solutionPlot.state');

