%-------------------------------------
% BEGIN: function SingularDae.m
%-------------------------------------
function dae = SingularDae(sol);

global CONSTANTS

t = sol.time;
x = sol.state(:,1);
% y = sol.state(:,2);
% v = sol.state(:,3);
u = sol.control;
xdot = u;
% ydot = -v.*cos(u);
% vdot = CONSTANTS.g*cos(u);
% dae = [xdot ydot vdot];
dae = [xdot ];
%-----------------------------------
% END: function SingularDae.m
%-----------------------------------

