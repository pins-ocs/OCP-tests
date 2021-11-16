%-----------------------------------------------------------------------%
%  file: SingularLuus04_FreeTime_fsolve_main.m                          %
%                                                                       %
%  version: 1.0   date 17/11/2021                                       %
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
ocp = SingularLuus04_FreeTime( 'SingularLuus04_FreeTime' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/SingularLuus04_FreeTime_Data.rb');
ocp.infoLevel(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

solver = nlsys_solver_ipopt(ocp);
x = solver.solve();

do_minimization = false;
u = ocp.eval_U(x,ocp.init_U(x,do_minimization));
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
