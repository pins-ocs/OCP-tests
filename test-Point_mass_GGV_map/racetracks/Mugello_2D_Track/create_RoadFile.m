% ----------------------------------------
%% Create the road file
% ----------------------------------------
% clc; clearvars; close all;

set(0,'DefaultFigureWindowStyle','docked');
set(0,'defaultAxesFontSize',18)
set(0,'DefaultLegendFontSize',18)

% Set LaTeX as default interpreter for axis labels, ticks and legends
set(0,'defaulttextinterpreter','latex')
set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

circuitName = 'Mugello_2D';

% Load the circuit data
circuit_data = readtable(strcat('road_',circuitName,'.txt'));
x_circuit         = circuit_data.X;
y_circuit         = circuit_data.Y;
theta_circuit     = circuit_data.theta;
abscissa_circuit  = circuit_data.abscissa;
curvature_circuit = circuit_data.curvature;
width_L_circuit   = circuit_data.width_L;
width_R_circuit   = circuit_data.width_R;
elevation_circuit = circuit_data.elevation;
banking_circuit   = circuit_data.banking;
slope_circuit     = circuit_data.slope;
upsilon_circuit   = circuit_data.upsilon;
torsion_circuit   = circuit_data.torsion;

% ------------------
%% ROAD FILE for off-line MLT 
% ------------------
numExtraPts_MLT = 500;  % n° of extra points to include in the MLT road file, so that the vehicle is driven for more than 1 lap
if (numExtraPts_MLT>2)
    x_MLT         = [x_circuit; x_circuit(2:numExtraPts_MLT)];
    y_MLT         = [y_circuit; y_circuit(2:numExtraPts_MLT)];
    theta_MLT     = [theta_circuit; theta_circuit(2:numExtraPts_MLT)];
    abscissa_MLT  = [abscissa_circuit; abscissa_circuit(end)+abscissa_circuit(2:numExtraPts_MLT)];
    curvature_MLT = [curvature_circuit; curvature_circuit(2:numExtraPts_MLT)];
    width_L_MLT   = [width_L_circuit; width_L_circuit(2:numExtraPts_MLT)];
    width_R_MLT   = [width_R_circuit; width_R_circuit(2:numExtraPts_MLT)];
    elevation_MLT = [elevation_circuit; elevation_circuit(2:numExtraPts_MLT)];
    banking_MLT   = [banking_circuit; banking_circuit(2:numExtraPts_MLT)];
    slope_MLT     = [slope_circuit; slope_circuit(2:numExtraPts_MLT)];
    upsilon_MLT   = [upsilon_circuit; upsilon_circuit(2:numExtraPts_MLT)];
    torsion_MLT   = [torsion_circuit; torsion_circuit(2:numExtraPts_MLT)];
else
    x_MLT         = x_circuit;
    y_MLT         = y_circuit;
    theta_MLT     = theta_circuit;
    abscissa_MLT  = abscissa_circuit;
    curvature_MLT = curvature_circuit;
    width_L_MLT   = width_L_circuit;
    width_R_MLT   = width_R_circuit;
    elevation_MLT = elevation_circuit;
    banking_MLT   = banking_circuit;
    slope_MLT     = slope_circuit;
    upsilon_MLT   = upsilon_circuit;
    torsion_MLT   = torsion_circuit;
end

% -------------
% txt road file
% -------------
referenceRoad = fopen(strcat('road_',circuitName,'_MLT.txt'),'w');
% Headers
fprintf(referenceRoad,'%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n','X','Y','theta','abscissa','curvature', ...
                                                                         'width_L','width_R','elevation','banking','slope','upsilon','torsion');
% Values
for ii=1:length(abscissa_MLT)
    fprintf(referenceRoad,'%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\t%3.14f\n', ...
                          x_MLT(ii),y_MLT(ii),theta_MLT(ii),abscissa_MLT(ii),curvature_MLT(ii),width_L_MLT(ii),width_R_MLT(ii), ...
                          elevation_MLT(ii),banking_MLT(ii),slope_MLT(ii),upsilon_MLT(ii),torsion_MLT(ii));
end
fclose(referenceRoad);


