%-----------------------------------------------------------------------%
%  file: LUUS_DrugDisplacement_main.m                                   %
%                                                                       %
%  version: 1.0   date 13/12/2021                                       %
%                                                                       %
%  Copyright (C) 2021                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


% -------------------------------------------------------------------------
% INITIALIZATION
% -------------------------------------------------------------------------
clc;
clear all;
close all

figsize=[0,0,400,800];

% create object
ocp = LUUS_DrugDisplacement( 'LUUS_DrugDisplacement' );

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(LUUS_DrugDisplacement_data);
%ocp.setup('../../data/LUUS_DrugDisplacement_Data.lua');
ocp.setup('../../data/LUUS_DrugDisplacement_Data.rb');
ocp.infoLevel(4);

ocp.set_guess(); % use default guess generated in MAPLE
%
% in alternative
% ocp.set_guess( struct );
%
% initialize the guess using the following criteria
%
% struct.initialize
% 'zero'           % fill the guess with all zero
% 'none' or 'warm' % do not fill the guess, use existing guess in memory
%
% after initialization fill the guess
% struct.guess_type
% 'none'      % in this case none is done
% 'default'   % fill the guess with the guess generated in MAPLE
% 'spline'    % use spline to initialize states/multiplers
%             expected extra fields
%             struct.spline_set             = structure with the spline table to
%                                             initialize states/multipliers/controls
%             struct.spline_set.spline_type = cell array of strings with the type of
%                                             splines ('pchip','cubic','quintic')
%             struct.spline_set.xdata       = vector of 'x' samples of the splines
%             struct.spline_set.ydata       = matrix npts x data of 'y' of the splines
%             struct.spline_set.headers     = cell array of strings with name of
%                                             the splines (name of states/multipliers/controls)
%
%             the data of the guess are updated ONLY in the 'x' range of the spline
%
% 'table'     % use sampled values to initialize states/multiplers
%             struct.states      =  structure of vectors, each field is the name of the state
%             struct.multipliers =  structure of vectors, each field is the name of the multiplier
%             struct.controls    =  structure of vectors, each field is the name of the control
%
%             the length of the vector must be compatible with the mesh
%

check_jacobian = false; % set true if you want to check jacobian matrix
if check_jacobian
  % check the jacobian of initial guess
  epsi = 1e-5;
  [Z,U] = ocp.get_raw_solution();
  ocp.check_jacobian( Z, U, epsi );
end

names = ocp.names();

% SET TRACKED VARIABLE ---------------------------------------------------------
% Specify the problem variable that you want to track during solver iteration
% by filling in the following cell array:
%tracked = {<'xx1'>,<'xx2'>,...}
%tracked = {};
%LUUS_DrugDisplacement_Mex('set_tracked',obj,tracked);

% -------------------------------------------------------------------------
% COMPUTE SOLUTION
% -------------------------------------------------------------------------
timeout_ms = 0; % if > 0 set a timeout in ms
ok = ocp.solve( timeout_ms );
% ok = false if computation failed
% ok = true if computation is succesfull
if check_jacobian
  % check the jacobian of the computed solution
  epsi = 1e-5;
  [Z, U] = ocp.get_raw_solution();
  ocp.check_jacobian( Z, U, epsi );
end

% -------------------------------------------------------------------------
% GET SOLUTION
% -------------------------------------------------------------------------
solution = ocp.solution(); % whole solution in a structure
zeta = ocp.solution('zeta');

% -------------------------------------------------------------------------
% PLOT SOLUTION
% -------------------------------------------------------------------------

subplot(3,1,1);
ocp.plot_states();

subplot(3,1,2);
ocp.plot_multipliers();

subplot(3,1,3);
ocp.plot_controls();

%[Z,U] = LUUS_DrugDisplacement_Mex('get_raw_solution',obj);
%J     = LUUS_DrugDisplacement_Mex('eval_JF',obj,Z,U);
%f     = LUUS_DrugDisplacement_Mex('eval_F',obj,Z,U);