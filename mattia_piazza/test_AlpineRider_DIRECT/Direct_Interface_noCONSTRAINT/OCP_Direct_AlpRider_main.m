%--------------------------------------------------------------------------%
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
%      Universita` di Trento                                               %
%      email: mattia.piazza@unitn.it                                       %
%                                                                          %
%--------------------------------------------------------------------------%
clc;
clear all;
close all

figsize=[0,0,400,800];

bb = OCP_Direct_AlpRider() ;

bb.setup() ;

info = bb.solve() ;
bb.plot() ;
