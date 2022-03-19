%-----------------------------------------------------------------------%
%  file: Farmer_fsolve_main.m                                           %
%                                                                       %
%  version: 1.0   date 19/3/2022                                        %
%                                                                       %
%  Copyright (C) 2022                                                   %
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
ocp = Farmer( 'Farmer' );
%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
ocp.setup('../../data/Farmer_Data.rb');
ocp.infoLevel(infolevel);
ocp.set_guess(); % use default guess
%ocp.update_continuation(0,0,1);

[xinit,uimit] = ocp.get_raw_solution();

LU = 1.e20*ones(size(xinit));

options          = TRESNEI();
options.output   = 1;
options.jacobian = 'on';
[x,ierr,output]  = TRESNEI(xinit,[length(xinit),0],@nlsys_local,-LU,LU,options,ocp);

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

% -------------------------------------------------------------------------
% LOCAL SYSTEM
% -------------------------------------------------------------------------

function [F,JF] = nlsys_local( x, ocp )
  do_minimization = false;
  u_guess  = ocp.init_U(x,do_minimization);
  u        = ocp.eval_U(x,u_guess);
  [F,ok1]  = ocp.eval_F(x,u);
  [JF,ok2] = ocp.eval_JF(x,u);
  if ~(ok1&&ok2)
    F = NaN*ones(size(F));
  end
end