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
Custom_Maneuver_xy = readtable('Custom_Maneuver_XY.csv');

% Add a straight at the end of the circuit
length_straight  = 250;  % [m]
x_final_straight = ((Custom_Maneuver_xy.x(end)+0.1):0.1:(Custom_Maneuver_xy.x(end)+length_straight))';
y_final_straight = ones(size(x_final_straight))*Custom_Maneuver_xy.y(end);
points_x = [Custom_Maneuver_xy.x; x_final_straight];
points_y = [Custom_Maneuver_xy.y; y_final_straight];
XY = [points_x, points_y];

% Avoid duplicates
XY_unique = unique(XY,'rows','stable');   

% ------------------
%% Down-sampling of the total number of points
% ------------------
% Fit the circuit with a list of G2 clothoids
SP_C_tmp = ClothoidSplineG2();
S_G2_tmp = SP_C_tmp.buildP2(XY_unique(:,1),XY_unique(:,2));
% Evaluate the G2 spline list with a certain sampling
ds_sampling = 2;  % [m]
abscissa_ev = 0:ds_sampling:S_G2_tmp.length();
[x_road_new,y_road_new,~,~] = S_G2_tmp.evaluate(abscissa_ev);

% figure(10)
% hold on
% plot(XY_unique(:,1),XY_unique(:,2),'bo')
% plot(x_road_new,y_road_new,'ro','MarkerFaceColor','r')
% plot(XY_unique(end-1000:end,1),XY_unique(end-1000:end,2),'go','HandleVisibility','off')
% grid on
% legend('original','down-sampled','location','best')
% 
% figure(11)
% plot(Custom_Maneuver_xy.speed,'o')
% grid on

% ------------------
%% Fitting with clothoids
% ------------------
% Fit the circuit with a list of G2 clothoids
SP_C = ClothoidSplineG2();
S_G2 = SP_C.buildP2(x_road_new,y_road_new);
% Evaluate the G2 spline list at the end points of each of the G2 clothoids composing the list 
[abscissa_G2,~,~] = S_G2.getSTK();
[x_ev,y_ev,theta_ev,~] = S_G2.evaluate(abscissa_G2);

% Rotate the points so as to make x_ev(1) = 0, y_ev(1) = 0, theta_ev(1) = 0
theta_rot = 0; %theta_ev(1);
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

% Exclude the first and the last points to avoid abrupt changes of the heading angles
indices_pts = 4:length(abscissa_G2)-4;

% Fit with G1 clothoids, using the evaluation points obtained from the G2 clothoid list
S_G1 = ClothoidList();
for kk=indices_pts
    S_G1.push_back_G1(x_ev(kk),y_ev(kk),theta_ev(kk), x_ev(kk+1),y_ev(kk+1),theta_ev(kk+1));
end
% Evaluate the G1 spline list at the end points of each of the G1 clothoids composing the list. 
% Notice that x_sampled == x_ev, y_sampled == y_ev
[abscissae_sampled,theta_sampled,kappa_sampled] = S_G1.getSTK();
[x_sampled,y_sampled] = S_G1.eval(abscissae_sampled);

% Circuit width
width_L_road = 2;
width_R_road = 2;
width_L_save = ones(size(abscissae_sampled))*width_L_road(1);
width_R_save = ones(size(abscissae_sampled))*width_R_road(1);

% Mesh step of curvilinear abscissa
mesh_step = 1;

% ------------------
%% Plot the circuit 
% ------------------
% rebuild the clothoid list to verify that the result is ok
S_reconstr_build = ClothoidList; 
x0     = x_sampled(1);
y0     = y_sampled(1);
theta0 = theta_sampled(1);
S_reconstr_build.build(x0, y0, theta0, abscissae_sampled, kappa_sampled);  

figure('Name','Circuit','NumberTitle','off'), clf  
hold on
axis equal
% S_G2.plot;
S_reconstr_build.plot;
% plot(x_ev,y_ev,'ko','MarkerSize',8)
% plot(x_sampled,y_sampled,'go','MarkerSize',8);
% plot(x_road_new,y_road_new,'bo','MarkerSize',6)
grid on
xlabel('x [m]')
ylabel('y [m]')
title('Circuit')

% ------------------
%% ROAD FILE - Save the clothoids fitting data
% ------------------
circuitName = 'Custom_Maneuver';
% -------------
% txt road file
% -------------
referenceRoad = fopen(strcat('road_',circuitName,'.txt'),'w');
% Headers
fprintf(referenceRoad,'%s\t%s\t%s\t%s\t%s\t%s\t%s\n','abscissa','curvature','X','Y','theta','width_L','width_R');
% Values
for ii=1:length(abscissae_sampled)
    fprintf(referenceRoad,'%.12f\t%.12f\t%.12f\t%.12f\t%.12f\t%.12f\t%.12f\n',abscissae_sampled(ii),kappa_sampled(ii),x_sampled(ii),y_sampled(ii),theta_sampled(ii),width_L_save(ii),width_R_save(ii));
end
fclose(referenceRoad);

% -------------
% csv road file
% -------------
table_csv = array2table([abscissae_sampled',kappa_sampled',x_sampled',y_sampled',theta_sampled',width_L_save',width_R_save']);
table_csv.Properties.VariableNames = {'abscissa','curvature','X','Y','theta','width_L','width_R'};
writetable(table_csv,strcat('road_',circuitName,'.csv'));

% ------------------
%% ROAD FILE for off-line MLT 
% ------------------
numExtraPts_MLT = 200;  % n° of extra points to include in the MLT road file, so that the vehicle is driven for more than 1 lap
abscissae_sampled_MLT = [abscissae_sampled, abscissae_sampled(end)+abscissae_sampled(2:numExtraPts_MLT)];
kappa_sampled_MLT     = [kappa_sampled, kappa_sampled(2:numExtraPts_MLT)];
x_sampled_MLT         = [x_sampled, x_sampled(2:numExtraPts_MLT)];
y_sampled_MLT         = [y_sampled, y_sampled(2:numExtraPts_MLT)];
theta_sampled_MLT     = [theta_sampled, theta_sampled(2:numExtraPts_MLT)];
width_L_save_MLT      = ones(size(abscissae_sampled_MLT))*width_L_road(1);
width_R_save_MLT      = ones(size(abscissae_sampled_MLT))*width_R_road(1);
% -------------
% txt road file
% -------------
referenceRoad = fopen(strcat('road_',circuitName,'_MLT.txt'),'w');
% Headers
fprintf(referenceRoad,'%s\t%s\t%s\t%s\t%s\t%s\t%s\n','abscissa','curvature','X','Y','theta','width_L','width_R');
% Values
for ii=1:length(abscissae_sampled_MLT)
    fprintf(referenceRoad,'%.12f\t%.12f\t%.12f\t%.12f\t%.12f\t%.12f\t%.12f\n',abscissae_sampled_MLT(ii),kappa_sampled_MLT(ii),x_sampled_MLT(ii),y_sampled_MLT(ii),theta_sampled_MLT(ii),width_L_save_MLT(ii),width_R_save_MLT(ii));
end
fclose(referenceRoad);

% ------------------
%% Set the initial conditions for the vehicle
% ------------------
x_veh0     = x0;
y_veh0     = y0;
psi_veh0   = theta0;
delta_veh0 = 0;
z_veh0     = 0;
phi_veh0   = 0;
mu_veh0    = 0;
file_IC = fopen(strcat('./Mesh_and_initialCondits_',circuitName,'/IC/',circuitName,'_IC.txt'),'w');
fprintf(file_IC,'pose,x0,y0,psi0,delta0,z0,phi0,mu0\n');
fprintf(file_IC,'%s,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f\n',strcat(circuitName,'_IC'),x_veh0,y_veh0,psi_veh0,delta_veh0,z_veh0,phi_veh0,mu_veh0);
fclose(file_IC);
