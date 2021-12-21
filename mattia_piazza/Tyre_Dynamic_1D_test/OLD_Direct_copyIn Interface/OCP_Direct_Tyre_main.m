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
%      Universita` degli Studi di Trento                                   %
%      email: mattia.piazza@unitn.it                                       %
%                                                                          %
%--------------------------------------------------------------------------%
clc;
clear all;
close all

figsize=[0,0,400,800];



% N     = 50;
% S_fin = 5;
% nodes = (0:N)/N * S_fin ;

% nodes = [linspace(0,10,50),linspace(11,94,100),linspace(95,100,50)] ;

bb = OCP_Direct_Tyre() ;

% bb.setup( nodes ) ;
bb.setup() ;

info = bb.solve() ;
bb.plot() ;

%%

info2 = bb.solve(info.x);



bb.plot() ;
info 

