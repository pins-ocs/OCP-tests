%-----------------------------------------------------------------------%
%  file: BrysonDenham_main.m                                            %
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


clc;
clear all;
close all

% create object
ocp = BrysonDenham( 'BrysonDenham' );

ocp.setup('../../../data/BrysonDenham_Data'); % automatically try extension .rb and .lua
ocp.set_info_level(4);
ocp.set_guess(); % use default guess generated in MAPLE
[Z,MU,U] = ocp.get_raw_solution();
[F,OK] = ocp.eval_F( Z, MU, U );
[JF,OK] = ocp.eval_JF( Z, MU, U );

[X,Lambda,Pars,Omega] = ocp.unpack( Z );

spy(JF);

save( 'FJF.mat', 'F', 'JF', 'U', 'X', 'Lambda', 'Pars', 'Omega' );

