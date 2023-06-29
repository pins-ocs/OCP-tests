% ----------------------------------------
%% Create the road file
% ----------------------------------------
clc; clearvars; close all;

set(0,'DefaultFigureWindowStyle','docked');
set(0,'defaultAxesFontSize',18)
set(0,'DefaultLegendFontSize',18)

% Set LaTeX as default interpreter for axis labels, ticks and legends
set(0,'defaulttextinterpreter','latex')
set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

% ------------------
%% Load road data
% ------------------
Fiorano_xy = readtable('Fiorano_XY.txt');
XY = [Fiorano_xy.X, Fiorano_xy.Y];

% ------------------
%% Fitting with clothoids
% ------------------
x_road = [XY(1:4:end,1); XY(1,1)];
y_road = [XY(1:4:end,2); XY(1,2)];

% Fit the circuit with a list of G2 clothoids
SP_C = ClothoidSplineG2();
S_G2 = SP_C.buildP2(x_road,y_road);
% Evaluate the G2 spline list at the end points of each of the G2 clothoids composing the list 
[abscissa_G2,~,~] = S_G2.getSTK();
[x_ev,y_ev,theta_ev,~] = S_G2.evaluate(abscissa_G2);

% Rotate the points so as to make x_ev(1) = 0, y_ev(1) = 0, theta_ev(1) = 0
theta_rot = theta_ev(1);
RotMat = [cos(theta_rot) -sin(theta_rot); ...
          sin(theta_rot) cos(theta_rot)];
x_start = x_ev(1);
y_start = y_ev(1);
for jj=1:length(x_ev)      
    rotated_points = pinv(RotMat)*[x_ev(jj)-x_start; y_ev(jj)-y_start]; 
    x_ev(jj) = rotated_points(1);
    y_ev(jj) = rotated_points(2);
end
theta_ev = theta_ev - theta_rot;

% Fit with G1 clothoids, using the evaluation points obtained from the G2 clothoid list
S_G1 = ClothoidList();
for kk=1:length(abscissa_G2)-1
    S_G1.push_back_G1(x_ev(kk),y_ev(kk),theta_ev(kk), x_ev(kk+1),y_ev(kk+1),theta_ev(kk+1));
end
% Evaluate the G1 spline list at the end points of each of the G1 clothoids composing the list. 
% Notice that x_sampled == x_ev, y_sampled == y_ev
[abscissae_sampled,theta_sampled,kappa_sampled] = S_G1.getSTK();
[x_sampled,y_sampled] = S_G1.eval(abscissae_sampled);

% ------------------
%% Test the commands
% ------------------
% rebuild the clothoid list to verify that the result is ok
S_reconstr_build = ClothoidList; 
x0     = x_sampled(1);
y0     = y_sampled(1);
theta0 = theta_sampled(1);
S_reconstr_build.build(x0, y0, theta0, abscissae_sampled, kappa_sampled);  

% PROBLEMATIC POINT
x_test_A = 120.4931534459877;  
y_test_A = 4.259914232593045;

% ------------------
%% First test -- WRONG RESULTS
% ------------------
x_test = x_test_A;
y_test = y_test_A;

idx_segm = double(S_reconstr_build.closestSegment(x_test,y_test));
[x_cl_true_1,y_cl_true_1,s_cl_true_1,n_cl_true_1,iflag_true_1,dst_true_1] = S_reconstr_build.closestPoint(x_test,y_test);
[idx_segm_cl_1,x_cl_1,y_cl_1,s_cl_1,n_cl_1,iflag_1,dst_1] = S_reconstr_build.closestPointInRange(x_test,y_test,max(idx_segm-3,0),idx_segm+3);
% [idx_segm_cl_1,x_cl_1,y_cl_1,s_cl_1,n_cl_1,iflag_1,dst_1] = S_reconstr_build.closestPointInSRange(x_test,y_test,50,200);
 
figure('Name','Test 1 - WRONG','NumberTitle','off'), clf  
hold on
axis equal
plot(x_test,y_test,'ko','MarkerFaceColor','k','MarkerSize',10)
plot(x_cl_1,y_cl_1,'go','MarkerFaceColor','g','MarkerSize',10)
plot(x_cl_true_1,y_cl_true_1,'mo','MarkerFaceColor','m','MarkerSize',10)
S_reconstr_build.plot;
grid on
xlabel('x [m]')
ylabel('y [m]')
title('Circuit')
legend('original pt','closest pt in range','true closest pt','location','best')

% ------------------
%% Second test -- RESULTS OK
% ------------------
x_test = round(x_test_A,10);
y_test = y_test_A;

% [idx_segm_cl_2,x_cl_2,y_cl_2,s_cl_2,n_cl_2,iflag_2,dst_2] = S_reconstr_build.closestPointInRange(x_test,y_test,max(idx_segm-1,0),idx_segm);
[x_cl_true_2,y_cl_true_2,s_cl_true_2,n_cl_true_2,iflag_true_2,dst_true_2] = S_reconstr_build.closestPoint(x_test,y_test);
[idx_segm_cl_2,x_cl_2,y_cl_2,s_cl_2,n_cl_2,iflag_2,dst_2] = S_reconstr_build.closestPointInSRange(x_test,y_test,50,200);
 
figure('Name','Test 2 - OK','NumberTitle','off'), clf  
hold on
axis equal
plot(x_test,y_test,'ko','MarkerFaceColor','k','MarkerSize',10)
plot(x_cl_2,y_cl_2,'go','MarkerFaceColor','g','MarkerSize',10)
plot(x_cl_true_2,y_cl_true_2,'mo','MarkerFaceColor','m','MarkerSize',10)
S_reconstr_build.plot;
grid on
xlabel('x [m]')
ylabel('y [m]')
title('Circuit')
legend('original pt','closest pt in range','true closest pt','location','best')
