%-------------------------------------------------------------------------%
%                                                                         %
%         , __                 , __                                       %
%        /|/  \               /|/  \                                      %
%         | __/ _   ,_         | __/ _   ,_                               %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                       %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                      %
%                           /|                   /|                       %
%                           \|                   \|                       %
%                                                                         %
%      Enrico Berolazzi                                                   %
%      Mattia Piazza                                                      %
%      Dipartimento di Ingegneria Industriale                             %
%      Universita` degli Studi di Trento                                  %
%      email: enrico.bertolazzi@unitn.it                                  %
%             mattia.piazza@unitn.it                                      %
%                                                                         %
%-------------------------------------------------------------------------%
clc;
clear all;
close all

figsize=[0,0,400,800];

bb = OCP_Direct_BangBangF() ;

bb.setup() ;

info = bb.solve() ;
bb.plot() ;
