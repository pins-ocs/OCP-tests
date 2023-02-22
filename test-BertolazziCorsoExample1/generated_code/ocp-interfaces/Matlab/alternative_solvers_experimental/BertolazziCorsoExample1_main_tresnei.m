%-----------------------------------------------------------------------%
%  file: BertolazziCorsoExample1_fsolve_main.m                          %
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
infolevel       = 4;
do_minimization = false;
ocp = BertolazziCorsoExample1( 'BertolazziCorsoExample1' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/BertolazziCorsoExample1_Data'); % automatically try extension .rb and .lua
ocp.set_info_level(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

[xinit,uimit] = ocp.get_raw_solution();

LU = 1.e20*ones(size(xinit));

options          = TRESNEI();
options.output   = 1;
options.jacobian = 'on';
[x,ierr,output]  = TRESNEI(xinit,[length(xinit),0],@nlsys_local,-LU,LU,options,ocp);

ierr

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

% -------------------------------------------------------------------------
% LOCAL SYSTEM
% -------------------------------------------------------------------------

function [F,JF] = nlsys_local( x, ocp )
  do_minimization = false;
  u_guess  = ocp.guess_U(x);
  u        = ocp.eval_U(x,u_guess);
  [F,ok1]  = ocp.eval_F(x,u);
  [JF,ok2] = ocp.eval_JF(x,u);
  if ~(ok1&&ok2)
    F = NaN*ones(size(F));
  end
end
