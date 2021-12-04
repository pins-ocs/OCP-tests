%-----------------------------------------------------------------------%
%  file: gtocX_2burn_pars_fsolve_main.m                                 %
%                                                                       %
%  version: 1.0   date 4/12/2021                                        %
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
infolevel       = 4;
do_minimization = false;
ocp = gtocX_2burn_pars( 'gtocX_2burn_pars' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/gtocX_2burn_pars_Data.rb');
ocp.infoLevel(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

[xinit,uimit] = ocp.get_raw_solution();
solver = NL_CG_Solver();
fun    = @(x) ocp.eval_F(x,ocp.eval_U(x,ocp.init_U(x,do_minimization)));
jac    = @(x) ocp.eval_JF(x,ocp.eval_U(x,ocp.init_U(x,do_minimization)));
check  = @(x) ocp.check_raw_solution(x);

[x,ierr] = solver.solve( xinit, fun, jac, check, false );

ierr

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
