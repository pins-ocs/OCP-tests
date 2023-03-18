%-----------------------------------------------------------------------%
%  file: ICLOCS_TwoLinkRobotArm_fsolve_main.m                           %
%                                                                       %
%  version: 1.0   date 20/3/2023                                        %
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

% -------------------------------------------------------------------------
% INITIALIZATION
% -------------------------------------------------------------------------
clc;
clear all;
close all;

DATA_PATH = '../../../data/';
LIB_PATH  = '../../../../../nlsys_solver';

addpath('..');
addpath(LIB_PATH);

figsize=[0,0,400,800];

% create object
infolevel = 4;
ocp = ICLOCS_TwoLinkRobotArm( 'ICLOCS_TwoLinkRobotArm' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup( [DATA_PATH 'ICLOCS_TwoLinkRobotArm_Data'] ); % automatically try extension .rb and .lua
ocp.set_info_level(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

solver = nlsys_solver_ipopt(ocp);
x = solver.solve();

MU_U = ocp.eval_MU_U( x, ocp.guess_U( x ) );
ocp.set_raw_solution( x, MU_U );

% -------------------------------------------------------------------------
% PLOT SOLUTION
% -------------------------------------------------------------------------

subplot(3,1,1);
ocp.plot_states();

subplot(3,1,2);
ocp.plot_multipliers();

subplot(3,1,3);
ocp.plot_controls();
