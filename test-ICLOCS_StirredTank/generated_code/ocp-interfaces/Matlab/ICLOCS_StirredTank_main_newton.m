%-----------------------------------------------------------------------%
%  file: ICLOCS_StirredTank_fsolve_main.m                               %
%                                                                       %
%  version: 1.0   date 16/11/2021                                       %
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
infolevel  = 4;
ocp = ICLOCS_StirredTank( 'ICLOCS_StirredTank', infolevel );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/ICLOCS_StirredTank_Data.rb');
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

xinit = ocp.get_raw_solution();
nwt = NewtonSolver( 2 );
fun   = @(x) ocp.eval_F(x);
jac   = @(x) ocp.eval_JF(x);
check = @(x) ocp.check_raw_solution(x);

[x,ierr] = nwt.solve( xinit, fun, jac, check );

ierr

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
