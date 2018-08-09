%--------------------------------------------------------------------------#
%   ____        _ _               ____ _               
%  / ___| _ __ | (_)_ __   ___   / ___| | __ _ ___ ___ 
%  \___ \| '_ \| | | '_ \ / _ \ | |   | |/ _` / __/ __|
%   ___) | |_) | | | | | |  __/ | |___| | (_| \__ \__ \
%  |____/| .__/|_|_|_| |_|\___|  \____|_|\__,_|___/___/
%        |_|                                           
%   ____       _               
%  / ___|  ___| |_ _   _ _ __  
%  \___ \ / _ \ __| | | | '_ \ 
%   ___) |  __/ |_| |_| | |_) |
%  |____/ \___|\__|\__,_| .__/ 
%                       |_|    
%--------------------------------------------------------------------------#
% Read tabulated file data
table = importdata('reference_manoeuvre.txt','\t');

% build tabulated data for spline
data = [getData(table,'ref_u'),getData(table,'ref_yawrate'),...
        getData(table,'ref_steer'),getData(table,'ref_longforce'),...
        getData(table,'ref_curv'),getData(table,'ref_x'),getData(table,'ref_y')];

% build structure to setup spline object
SplineRefMan.spline_type = { 'cubic', 'cubic' , 'cubic', 'cubic', 'cubic', 'cubic', 'cubic'  };
SplineRefMan.headers     = { 'ref_u', 'ref_yawrate' , 'ref_steer', 'ref_longforce', 'ref_curv', 'ref_x','ref_y' };
SplineRefMan.xdata       = getData(table,'zeta');
SplineRefMan.ydata       = data;

% Store spline structure data in object structure "SingleTrackOL_data".
% Please check that the object name is correct.
SingleTrackOL_data.SplineRefMan  = SplineRefMan; % for OL
SingleTrackMPC_data.SplineRefMan = SplineRefMan; % for OCP


  
