%-----------------------------------------------------------------------%
%  file: FlowInAchannel_main.m                                          %
%                                                                       %
%  version: 1.0   date 1/6/2022                                         %
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


clc;
clear all;
close all

% create object
ocp = FlowInAchannel( 'FlowInAchannel' );

ocp.setup('../../data/FlowInAchannel_Data'); % automatically try extension .rb and .lua
ocp.infoLevel(4);
ocp.set_guess(); % use default guess generated in MAPLE
[Z,U] = ocp.get_raw_solution();
[F,OK] = ocp.eval_F( Z, U );
[JF,OK] = ocp.eval_JF( Z, U );

[X,Lambda,Pars,Omega] = ocp.unpack( Z );

spy(JF);

save( 'FJF.mat', 'F', 'JF', 'U', 'X', 'Lambda', 'Pars', 'Omega' );

