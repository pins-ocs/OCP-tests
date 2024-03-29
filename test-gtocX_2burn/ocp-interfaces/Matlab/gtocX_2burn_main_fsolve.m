%-----------------------------------------------------------------------%
%  file: gtocX_2burn_fsolve_main.m                                      %
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


addpath('../../../nlsys_solver');
addpath('../../../../nlsys_solver');

% -------------------------------------------------------------------------
% INITIALIZATION
% -------------------------------------------------------------------------
clc;
clear all;
close all
figsize=[0,0,400,800];

% create object
infolevel  = 4;
ocp = gtocX_2burn( 'gtocX_2burn', infolevel );

nlsys = @(x) deal(ocp.eval_F(x),ocp.eval_JF(x));

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(gtocX_2burn_data);
%ocp.setup('../../data/gtocX_2burn_Data.lua');
ocp.setup('../../data/gtocX_2burn_Data.rb');
ocp.set_guess(); % use default guess


algo = {'trust-region-dogleg', 'trust-region','levenberg-marquardt'};

options = optimoptions(@fsolve,...
                       'Display','iter',...
                       'Algorithm',algo{1}, ...
                       'SpecifyObjectiveGradient',true, ...
                       'FunctionTolerance',1e-10, ...
                       'MaxIterations',1000,...
                       'OptimalityTolerance',1e-10, ...
                       'CheckGradients',false,...
                       'JacobPattern',ocp.eval_JF_pattern(), ...
                       'FiniteDifferenceType','central', ...
                       'FiniteDifferenceStepSize',eps^(1/3.5));

x0 = ocp.get_raw_solution();
x  = fsolve( nlsys, x0, options );
ocp.set_raw_solution(x);

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
%x = gtocX_2burn_Mex('get_raw_solution',obj);
%J = gtocX_2burn_Mex('eval_JF',obj,x);
%f = gtocX_2burn_Mex('eval_F',obj,x);
