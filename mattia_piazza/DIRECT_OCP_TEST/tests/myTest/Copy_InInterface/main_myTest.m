%-------99-------------------------------------------------------------------%
%                                                                          %
%         , __                 , __                                        %
%        /|/  \               /|/  \                                       %
%         | __/ _   ,_         | __/ _   ,_                                %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                        %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       %
%                           /|                   /|                        %
%                           \|                   \|                        %
%                                                                          %
%      Mattia Piazza                                                       %
%      Dipartimento di Ingegneria Industriale                              %
%      Universita` degli Studi di Trento                                   %
%      email: mattia.piazza@unitn.it                                       %
%                                                                          %
%--------------------------------------------------------------------------%
clc;
clear all;
close all

figsize=[0,0,400,800];



N     =  100;
% nodes = (0:N)/N ;
S_fin = 1000;
nodes = (0:N)/N * S_fin ;

bb = OCP_myTest() ;

bb.setup( nodes ) ;

info = bb.solve() ;
bb.plot() ;
info 

