%-----------------------------------------------------------------------%
%  file: BangBangFwork_fsolve_main.m                                    %
%                                                                       %
%  version: 1.0   date 10/11/2022                                       %
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
close all
figsize=[0,0,400,800];

% create object
infolevel  = 4;
ocp = BangBangFwork( 'BangBangFwork' );

nlsys = @(x) nlsys_local(ocp,x);

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(BangBangFwork_data);
ocp.setup('../../data/BangBangFwork_Data'); % automatically try extension .rb and .lua
ocp.infoLevel(infolevel);
ocp.set_guess(); % use default guess

algo = { 'trust-region-dogleg', 'trust-region', 'levenberg-marquardt' };

options = optimoptions(...
  @fsolve,...
  'Display','iter',...
  'Algorithm',algo{1}, ...
  'SpecifyObjectiveGradient',true, ...
  'FunctionTolerance',1e-10, ...
  'MaxIterations',1000,...
  'OptimalityTolerance',1e-10, ...
  'CheckGradients',false,...
  'JacobPattern',ocp.eval_JF_pattern(), ...
  'FiniteDifferenceType','central', ...
  'FiniteDifferenceStepSize',eps^(1/3.5) ...
);

[x0,u0] = ocp.get_raw_solution();
x       = fsolve( nlsys, x0, options );

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

%%clear mex
%[Z,U] = BangBangFwork_Mex('get_raw_solution',obj);
%J     = BangBangFwork_Mex('eval_JF',obj,Z,U);
%f     = BangBangFwork_Mex('eval_F',obj,Z,U);

function [F,JF] = nlsys_local( ocp, x )
  do_minimization = false;
  u_guess  = ocp.init_U(x,do_minimization);
  u        = ocp.eval_U(x,u_guess);
  [F,ok1]  = ocp.eval_F(x,u);
  [JF,ok2] = ocp.eval_JF(x,u);
  if ~(ok1&&ok2)
    F = NaN*ones(size(F));
  end
end
