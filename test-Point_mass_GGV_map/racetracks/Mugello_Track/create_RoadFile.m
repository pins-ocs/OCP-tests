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
% STRAIGHT LINE      START GRID
S.push_back( x0, y0, theta0, 0, 0, 153.950959920426 ); % first segment

addseg  = @(a,r) S.push_back( -1/r, 0, abs(a*r) );
addseg1 = @(l) S.push_back( 0, 0, l );

% CORNER:
addseg(45.2707044337391/347.327792187656,347.327792187656);
% STRAIGHT LINE
addseg1(244.134389610089);
%  CORNER
addseg(59.358551236732/347.327792187656,-347.327792187656);
% STRAIGHT LINE
addseg1(201.644854584327);
% CORNER (San Donato)
addseg(142.894358535785/49.7836502135641,49.7836502135641);
% STRAIGHT LINE
addseg1(133.43893827313);
% CORNER (Luco) 
addseg(67.1863934651959/57.8879653646094,-57.8879653646094);
% STRAIGHT LINE
addseg1(45.9584134622707);
% CORNER (Poggio Secco)
addseg(75.6533188312851/46.3103722916875,46.3103722916875);
% STRAIGHT LINE
addseg1(334.716783157046);
% CORNER (Materassi) 													
addseg(71.4573675497968/69.4655584375313,-69.4655584375313);
% STRAIGHT LINE
addseg1(34.6598403824062);
% CORNER: (Borgo San Lorenzo)
addseg(79.9150308414277/69.4655584375313,69.4655584375313);
% STRAIGHT LINE
addseg1(263.472674871652);
% CORNER: (Casanova) 
addseg(81.3041104583168/81.0431515104532,81.0431515104532);
% STRAIGHT LINE
addseg1(48.7678321973459);
% CORNER: (Savelli) 
addseg(129.057513950613/92.6207445833751,-92.6207445833751);
% STRAIGHT LINE
addseg1(163.432545543426);
% CORNER: (Arrabbiata1)  
addseg(155.737382531577/92.6207445833751,92.6207445833751);
% STRAIGHT LINE
addseg1(132.80865410624);
% CORNER: (Arrabbiata2)
addseg(91.6653616029976/69.4655584375313,69.4655584375313);
% STRAIGHT LINE
addseg1(276.98025270983)
% CORNER: (Scarperia)
addseg(96.1313023549464/64.8345212083625,64.8345212083625);
% STRAIGHT LINE
addseg1(35.6152233627838)
% CORNER: (Palagio)
addseg(78.3247326569311/57.8879653646094,-57.8879653646094);
% STRAIGHT LINE
addseg1(323.774799943827)
% CORNER: (Correntaio)
addseg(218.995961770854/62.5190025937782,62.5190025937782);
% STRAIGHT LINE
addseg1(120.082100696761);
% CORNER: (Biondetti1)
addseg(35.1331323872273/57.8879653646094,-57.8879653646094);
% STRAIGHT LINE
addseg1(51.5168158965805);
% CORNER: (Biondetti2)
addseg(61.7963292341664/104.198337656297,104.198337656297);
% STRAIGHT LINE
addseg1(380.85511241567);
% CORNER: (Bucine)  
addseg(265.379041347039/78.7276328958688,-78.7276328958688);
% STRAIGHT LINE
%addseg1(543.929215677558);

S.push_back_G1( x0, y0, theta0 ); 

S.reverse;

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
circuitName = 'Mugello';

% -------------
% txt road file
% -------------
referenceRoad = fopen(strcat('road_',circuitName,'.txt'),'w');
% Headers
fprintf(referenceRoad,'%s\t%s\t%s\t%s\t%s\t%s\t%s\n','abscissa','curvature','X','Y','theta','width_L','width_R');
% Values
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
numExtraPts_MLT = min(200,length(abscissae_sampled));  % n° of extra points to include in the MLT road file, so that the vehicle is driven for more than 1 lap
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

