function output = SingularControlEndpoint(input)
% 
% t0    = input.phase(1).initialtime;
% tf    = input.phase(1).finaltime;
% x0    = input.phase(1).initialstate;
% xf    = input.phase(1).finalstate;
%t             = input.phase(1).time;
%x             = input.phase(1).state;
%beta  = input.parameter;
%output.eventgroup(1).event = [xf(4)-x0(4), (xf(5)-x0(5)), xf(6)+2*pi-x0(6)];
q = input.phase(1).integral;
output.objective = q;
