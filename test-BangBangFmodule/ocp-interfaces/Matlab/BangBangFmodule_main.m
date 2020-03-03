%-----------------------------------------------------------------------%
%  file: BangBangFmodule_main.m                                         %
%                                                                       %
%  version: 1.0   date 28/3/2020                                        %
%                                                                       %
%  Copyright (C) 2020                                                   %
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
ocp = BangBangFmodule( 'BangBangFmodule' );

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(BangBangFmodule_data);
%ocp.setup('../../data/BangBangFmodule_Data.lua');
ocp.setup('../../data/BangBangFmodule_Data.rb');
ocp.infoLevel(4);

ocp.set_guess(); % use default guess generated in MAPLE
%
% in alternative
% ocp.set_guess( struct );
%
% initialize the guess using the following criteria
% struct.initialize = 'zero'           % fill the guess with all zero
% struct.initialize = 'none' or 'warm' % do not fill the guess
%
% after initialization fill the guess
%
% struct.guess_type = 'none'
% in this case none is done
%
% fill the guess with the guess generated in MAPLE
% struct.guess_type = 'default'
%
% struct.guess_type             = 'spline' % use spline to initialize states/multiplers
% struct.spline_set             = structure with the spline table to initialize states/multiplers/controls
% struct.spline_set.headers     = cell array of strings with name of the splines (name of states/multiplers/controls)
% struct.spline_set.spline_type = cell array of strings with the type of splines ('pchip','cubic','quintic')
% struct.spline_set.xdata:      = vector of 'x' samples of the splines
% struct.spline_set.ydata:      = matrix npts x data of 'y' of the splines
%
% the data of the guess are updated ONLY in the 'x' range of the spline
%
% struct.guess_type  = 'table' % use spline to initialize states/multiplers
% struct.states      =  structure of vectors, each field is the name of the state
% struct.multipliers =  structure of vectors, each field is the name of the multiplier
% struct.controls    =  structure of vectors, each field is the name of the control
%
% the length of the vector must be compatible with the mesh
%

epsi = 1e-5;
ocp.check_jacobian( ocp.get_raw_solution(), epsi );

names = ocp.names();

% SET TRACKED VARIABLE ---------------------------------------------------------
% Specify the problem variable that you want to track during solver iteration
% by filling in the following cell array:
%tracked = {<'xx1'>,<'xx2'>,...}
%tracked = {};
%BangBangFmodule_Mex('set_tracked',obj,tracked);

% -------------------------------------------------------------------------
% COMPUTE SOLUTION
% -------------------------------------------------------------------------
ok = ocp.solve();
% ok = false if computation failed
% ok = true if computation is succesfull
%epsi = 1e-5;
%ocp.check_jacobian(ocp.get_raw_solution(),epsi);

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

%%clear mex
%x = BangBangFmodule_Mex('get_raw_solution',obj);
%J = BangBangFmodule_Mex('eval_JF',obj,x);
%f = BangBangFmodule_Mex('eval_F',obj,x);
