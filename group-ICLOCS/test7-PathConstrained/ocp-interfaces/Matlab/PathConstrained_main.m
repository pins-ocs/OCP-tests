%-----------------------------------------------------------------------%
%  file: PathConstrained_main.m                                         %
%                                                                       %
%  version: 1.0   date 17/8/2018                                        %
%                                                                       %
%  Copyright (C) 2018                                                   %
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
infolevel = 4;
ocp = PathConstrained( 'PathConstrained', infolevel );

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(PathConstrained_data);
%ocp.setup('../../data/PathConstrained_Data.lua');
ocp.setup('../../data/PathConstrained_Data.rb');

ocp.guess(); % use default guess

epsi = 1e-5;
ocp.check_jacobian(ocp.get_raw_solution(),epsi);

names = ocp.names();

% SET TRACKED VARIABLE ---------------------------------------------------------
% Specify the problem variable that you want to track during solver iteration
% by filling in the following cell array:
%tracked = {<'xx1'>,<'xx2'>,...}
%tracked = {};
%PathConstrained_Mex('set_tracked',obj,tracked);

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
%x = PathConstrained_Mex('get_raw_solution',obj);
%J = PathConstrained_Mex('eval_JF',obj,x);
%f = PathConstrained_Mex('eval_F',obj,x);
