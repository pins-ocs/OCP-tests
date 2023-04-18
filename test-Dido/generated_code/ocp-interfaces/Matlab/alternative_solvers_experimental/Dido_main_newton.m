%-----------------------------------------------------------------------%
%  file: Dido_fsolve_main.m                                             %
%                                                                       %
%  version: 1.0   date 9/5/2023                                         %
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
infolevel       = 4;
do_minimization = false;
ocp = Dido( 'Dido' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup( [DATA_PATH 'Dido_Data'] ); % automatically try extension .rb and .lua
ocp.set_info_level(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

[xinit,muinit,uinit] = ocp.get_raw_solution();
nwt   = PINS_NewtonSolver( 2 );
fun   = @(x) ocp.eval_F(x,ocp.eval_MU_U(x,ocp.guess_U(x)));
jac   = @(x) ocp.eval_JF(x,ocp.eval_MU_U(x,ocp.guess_U(x)));
check = @(x) ocp.check_raw_solution(x);

[x,ierr] = nwt.solve( xinit, fun, jac, check );

ierr

MU_U = ocp.eval_MU_U(x,ocp.guess_U(x));
ocp.set_raw_solution(x,MU_U);

% -------------------------------------------------------------------------
% PLOT SOLUTION
% -------------------------------------------------------------------------

subplot(3,1,1);
ocp.plot_states();

subplot(3,1,2);
ocp.plot_multipliers();

subplot(3,1,3);
ocp.plot_controls();
