%--------------------------------------
% BEGIN: function SingularCost.m
%--------------------------------------
% function [Mayer,Lagrange]=brachistochroneCost(sol);
function [Mayer, Lagrange]=SingularCost(sol);

tf = sol.terminal.time;
t  = sol.time;
x  = sol.state(:,1);
u  = sol.control;
Mayer = 0; %zeros(size(t));
% (x-1+t^2)^2
Lagrange = (x-ones(size(t))+t.*t).^2;

