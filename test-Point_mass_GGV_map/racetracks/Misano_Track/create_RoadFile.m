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
theta0 = pi+pi/4;

S = ClothoidList();

addseg  = @(a,r) S.push_back( -1/r, 0, abs(a*r) );
addseg1 = @(l) S.push_back( 0, 0, l );
													      
S.push_back(x0,y0,theta0, 0,0,257); 

% CORNER  (1. Variante del parco, dx)
addseg(1.17560115144983,33.6446932777513);

% STRAIGHT LINE
addseg1(69.3886020301746);

% CORNER (2, cambio direzione sx)
addseg(1.08225183870547,-28.0372443981261);

% STRAIGHT LINE
addseg1(156.891281546505);

% CORNER (3. Curva del Rio, dx)
addseg(1.12076347287888,56.0744887962522);

% STRAIGHT LINE
addseg1(177.150952012352);

% CORNER (4, cambio direzione dx)
addseg(2.14495670467292,16.8223466388757);

% STRAIGHT LINE
addseg1(54.2676483865244);

% CORNER (5, cambio direzione dx) 
addseg(1.28777721372631,22.4297955185009);

% STRAIGHT LINE
addseg1(66.2725918538787);

% CORNER (6, cambio direzione sx)
addseg(1.19008632273402,-39.2521421573765);

% STRAIGHT LINE
addseg1(334.525723771273);

% CORNER (congiungente sx)
addseg(0.192440673730988,-123.363875351755);

% STRAIGHT LINE
addseg1(255.294862398743);

% CORNER (7. Quercia, sx)
addseg(2.4598907976498,-35.8876728296014);

% STRAIGHT LINE
addseg1(83.8848390576514);

% CORNER (congiungente sx)
addseg(0.181868025357458,-100.934079833254);

% STRAIGHT LINE
addseg1(213.852827215533);

% CORNER (congiungente dx)
addseg(0.497651064634048,44.8595910370017);

% STRAIGHT LINE
addseg1(53.4220652374333);

% CORNER (8. Tramonto, dx)
addseg(2.61087521037001,33.6446932777513);

% STRAIGHT LINE
addseg1(52.7112234886856);

% CORNER (congiungente dx)
addseg(0.151521126772546,67.2893865555026);

% STRAIGHT LINE
addseg1(481.340920785153);

% CORNER (9. Curvone, dx)
addseg(0.558770009523482,106.541528712879);

% STRAIGHT LINE
addseg1(227.492188959158);

% CORNER (10, cambio direzione dx)
addseg(0.559644334132245,95.3266309536287);

% STRAIGHT LINE
addseg1(118.653844587077);

% CORNER (11, cambio direzione dx)
addseg(1.11496041368553,39.2521421573765);

% STRAIGHT LINE
addseg1(123.384733469072);

% CORNER (12. Curva del Carro, dx)
addseg(2.69586365772195,23.5512852944259);

% STRAIGHT LINE
addseg1(150.56420705133);

% CORNER (13, cambio di direzione sx)
addseg(1.1002346592359,-39.2521421573765);

% STRAIGHT LINE
addseg1(223.404077635714);

% CORNER (14, cambio direzione sx)
addseg(1.42844614134274,-26.915754622201);

% STRAIGHT LINE
%addseg1(283.563770397571);
S.push_back_G1( x0, y0, theta0); 

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
circuitName = 'Misano';
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

