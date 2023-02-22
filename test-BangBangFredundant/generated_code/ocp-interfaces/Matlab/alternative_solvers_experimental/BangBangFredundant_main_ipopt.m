%-----------------------------------------------------------------------%
%  file: BangBangFredundant_fsolve_main.m                               %
%                                                                       %
%  version: 1.0   date 22/2/2023                                        %
%                                                                       %
%  Copyright (C) 2023                                                   %
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
infolevel = 4;
ocp = BangBangFredundant( 'BangBangFredundant' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/BangBangFredundant_Data'); % automatically try extension .rb and .lua
ocp.set_info_level(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

solver = nlsys_solver_ipopt(ocp);
x = solver.solve();

u = ocp.eval_U(x,ocp.guess_U(x));
ocp.set_raw_solution(x,u);

% -------------------------------------------------------------------------
% PLOT SOLUTION
% -------------------------------------------------------------------------

subplot(3,1,1);
ocp.plot_states();

subplot(3,1,2);
ocp.plot_multipliers();

subplot(3,1,3);
ocp.plot_controls();
