%% Tool Initial Conditions

clc
clear all
close all
addpath(genpath('./Tracks'));

%% README
% RENAME track_RDF with the selected track 
% RENAME IC_pose with the initial pose desired
% change the value of x,y,psi,u,delta

%-------------------------------- START User edit
track_RDF             = 'noTrack';             % 'noTrack' for 2D Simulation
IC_pose               = '_pistaAz';            % Pose location (_7charactersname)
IC_x                  = 0;
IC_y                  = 0;
IC_psi                = 0;
IC_u                  = 0;
IC_delta              = 0;
%-------------------------------- END User edit


%% Compute initial conditions

% Define initial pose
IC.pose               = strcat(track_RDF, IC_pose);
IC.x0                 = IC_x;                   % [m] initial vehicle x position
IC.y0                 = IC_y;                   % [m] initial vehicle y position
IC.psi0               = IC_psi;                 % [m] initial vehicle yaw angle
IC.u0                 = IC_u;                   % [m/s] initial long velocity
IC.delta0             = IC_delta;               % [rad] initial steering angle

% Derived ICs
if ~ strcmp(track_RDF, 'noTrack')
    Delta_X           = 1;                      % [m] Virtual wheelbase for the first guess of pitch/roll angle         
    Delta_Y           = 1;                      % [m] Virtual track for the first guess of pitch/roll angle
    [N, E, MU] = RDF_read(track_RDF);
    E(:,4) = 1:length(E);
    TR = triangulation(E(:,1:3),N);
    Face_normals = faceNormal(TR);
    Face_areas = faceArea(E,N);    
    [IC.z0, IC.phi0, IC.mu0, ~] =  Road_param([IC.x0 IC.y0 IC.psi0], Delta_X, Delta_Y, N, E, Face_normals, Face_areas);
else
    IC.z0 = 0;                                  % [m] initial condition for the internal dof z
    IC.phi0 = 0;                                % [rad] initial roll angle
    IC.mu0 = 0;                                 % [rad] initial pitch angle
end

%% Write configuration file

filename = strcat('./Tracks/Map_MESH/', track_RDF, '/IC/', IC.pose, '.txt');

if ~ isfile(filename)
    writetable(struct2table(IC), filename);
else
    answer = questdlg('File already exists! Wanna replace it?', 'Warning IC file', 'Yes', 'No', 'No');
    if strcmp(answer, 'Yes')
        writetable(struct2table(IC), filename, 'Delimiter', ' ');
    end
end
    