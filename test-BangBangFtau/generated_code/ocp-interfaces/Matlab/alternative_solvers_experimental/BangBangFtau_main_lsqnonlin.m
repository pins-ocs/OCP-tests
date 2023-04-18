%-----------------------------------------------------------------------%
%  file: BangBangFtau_fsolve_main.m                                     %
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
close all

DATA_PATH = '../../../data/';
LIB_PATH  = '../../../../../nlsys_solver';

addpath('..');
addpath(LIB_PATH);

figsize=[0,0,400,800];

% create object
infolevel = 4;
ocp = BangBangFtau( 'BangBangFtau' );

nlsys = @(x) nlsys_local(ocp,x);

%ocp.help(); % print usage

% -----------------------------------------------------------------------------
% SET UP OF OPTIMAL CONTROL PROBLEM
% -----------------------------------------------------------------------------
% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file
%ocp.setup(BangBangFtau_data);
ocp.setup( [DATA_PATH 'BangBangFtau_Data'] ); % automatically try extension .rb and .lua
ocp.set_info_level(infolevel);
ocp.set_guess(); % use default guess


algo = {'trust-region-reflective', 'levenberg-marquardt'};

options = optimoptions(...
  @lsqnonlin,...
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

[x0,mu0,u0] = ocp.get_raw_solution();
LB = -Inf*ones(size(x0));
UB = Inf*ones(size(x0));

x = lsqnonlin( nlsys, x0, LB, UB, options );

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

[F,JF] = nlsys_local( ocp, x );

fprintf('||F|| = %g, || grad F^2 || = %g\n', norm(F,inf), norm( JF.'*F, inf ));

%%clear mex
%[Z,MU,U] = BangBangFtau_Mex('get_raw_solution',obj);
%J        = BangBangFtau_Mex('eval_JF',obj,Z,MU,U);
%f        = BangBangFtau_Mex('eval_F',obj,Z,MU,U);

function [F,JF] = nlsys_local( ocp, x )
  do_minimization = false;
  MU_U     = ocp.eval_MU_U(x,ocp.guess_U(x));
  [F,ok1]  = ocp.eval_F(x,MU_U);
  [JF,ok2] = ocp.eval_JF(x,MU_U);
  if ~(ok1&&ok2)
    F = NaN*ones(size(F));
  end
end
