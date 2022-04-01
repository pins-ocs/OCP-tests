%--------------------------------------------------------------------------%
%                                                                          %
%  Copyright (C) 2018                                                      %
%                                                                          %
%         , __                 , __                                        %
%        /|/  \               /|/  \                                       %
%         | __/ _   ,_         | __/ _   ,_                                %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                        %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       %
%                           /|                   /|                        %
%                           \|                   \|                        %
%                                                                          %
%      Enrico Bertolazzi                                                   %
%      Dipartimento di Ingegneria Industriale                              %
%      Universita` degli Studi di Trento                                   %
%      email: enrico.bertolazzi@unitn.it                                   %
%                                                                          %
%--------------------------------------------------------------------------%
clc;
clear all;
close all

figsize=[0,0,400,800];
addpath('../lib') ;
%%% addpath('C:/Users/T75/AppData/Roaming/MathWorks/MATLAB Add-Ons/Toolboxes/IPOPT-toolbox/lib') ;

N     = 99 ;
nodes = (0:N)/N * 1;

bb = OCP_BangBang() ;

bb.setup( nodes ) ;

info = bb.solve() ;
bb.plot() ;
info 