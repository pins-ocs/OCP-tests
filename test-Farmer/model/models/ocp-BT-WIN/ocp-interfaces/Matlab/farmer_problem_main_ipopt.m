%-----------------------------------------------------------------------%
%  file: farmer_problem_fsolve_main.m                                   %
%                                                                       %
%  version: 1.0   date 16/6/2019                                        %
%                                                                       %
%  Copyright (C) 2019                                                   %
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
close all;
figsize=[0,0,400,800];

% create object
infolevel  = 4;
ocp = farmer_problem( 'farmer_problem', infolevel );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/farmer_problem_Data.rb');
ocp.set_guess(); % use default guess
%ocp.updateContinuation(0,1);

solver = nlsys_solver_ipopt(ocp);
x = solver.solve();
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
