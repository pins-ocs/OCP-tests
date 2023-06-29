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
%% Create road data and fit with clothoids
% ------------------
x0     = 0;
y0     = 0;
theta0 = 0;

S = ClothoidList();

addseg  = @(l,c) S.push_back( -c, 0, l );
addseg1 = @(l) S.push_back( 0, 0, l );

S.push_back( x0, y0, theta0, 0, 0, 20 ); % 1

addseg1(333.56399);
% CORNER
addseg( 94.430509,-0.014788752);
% STRAIGHT LINE
addseg1(288.876735);
% CORNER
addseg(76.993736,-0.033496099);
% STRAIGHT LINE
addseg1(111.792956);
% CORNER
addseg(32.317242,-0.025091069);
% STRAIGHT LINE
addseg1(126.901826);
% CORNER
addseg(55.0546292,0.029835693);
% STRAIGHT LINE
addseg1(84.134941);
% CORNER
addseg(113.685868,53.072559^(-1))
% STRAIGHT LINE
addseg1(192.264108);
% CORNER
addseg(73.591598,-34.35873^(-1));
% STRAIGHT LINE														 
addseg1(292.868903);
% CORNER
addseg(26.988876,-61.753526^(-1));
% STRAIGHT LINE														 
addseg1(134.851756);
% CORNER
addseg(77.107342,-63.684985^(-1));
% CORNER
addseg(54.232517,-36.444969^(-1));
% STRAIGHT LINE
addseg1(105.707786);
% CORNER
addseg(68.235168,-85.046849^(-1));
% STRAIGHT LINE														 
addseg1(56.609801);
% CORNER
addseg(56.141288,67.287775^(-1));
% STRAIGHT LINE
addseg1(56.524823);
% CORNER
addseg(94.573034,35.332293^(-1));
% STRAIGHT LINE
addseg1(281.247571);
% CORNER
addseg(42.124813,35.485691^(-1));
% CORNER
addseg(476.610109,-241.713468^(-1));
% CORNER
addseg(59.981871,-31.11497^(-1));
% STRAIGHT LINE
addseg1(497.63868);

S.push_back_G1(x0,y0,theta0); 

absc_step_eval = 5;
abscissa_eval  = 0:absc_step_eval:S.length;
if (isempty(find(abscissa_eval==S.length,1)))
    abscissa_eval = [abscissa_eval,S.length];
end
[x_road,y_road] = S.evaluate(abscissa_eval);

% ------------------
%% Fit the circuit with a list of G2 clothoids
% ------------------
SP_C = ClothoidSplineG2();
S_G2 = SP_C.buildP2(x_road',y_road');
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

% Circuit width
width_L_road = 4;
width_R_road = 4;
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
% plot(x_road,y_road,'bo','MarkerSize',6)
grid on
xlabel('x [m]')
ylabel('y [m]')
title('Circuit')

% ------------------
%% ROAD FILE - Save the clothoids fitting data
% ------------------
circuitName = 'Valencia';
% -------------
% txt road file
% -------------
referenceRoad = fopen(strcat('road_',circuitName,'.txt'),'w');
% Headers
fprintf(referenceRoad,'%s\t%s\t%s\t%s\t%s\t%s\t%s\n','abscissa','curvature','X','Y','theta','width_L','width_R');
for ii=1:length(abscissae_sampled)
    fprintf(referenceRoad,'%.20e\t%.20e\t%.20e\t%.20e\t%.20e\t%.20e\t%.20e\n',abscissae_sampled(ii),kappa_sampled(ii),x_sampled(ii),y_sampled(ii),theta_sampled(ii),width_L_save(ii),width_R_save(ii));
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
    fprintf(referenceRoad,'%.20e\t%.20e\t%.20e\t%.20e\t%.20e\t%.20e\t%.20e\n',abscissae_sampled_MLT(ii),kappa_sampled_MLT(ii),x_sampled_MLT(ii),y_sampled_MLT(ii),theta_sampled_MLT(ii),width_L_save_MLT(ii),width_R_save_MLT(ii));
end
fclose(referenceRoad);

% -------------
% csv road file
% -------------
table_MLT_csv = array2table([abscissae_sampled_MLT',kappa_sampled_MLT',x_sampled_MLT',y_sampled_MLT',theta_sampled_MLT',width_L_save_MLT',width_R_save_MLT']);
table_MLT_csv.Properties.VariableNames = {'abscissa','curvature','X','Y','theta','width_L','width_R'};
writetable(table_MLT_csv,strcat('road_',circuitName,'_MLT.csv'));

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

