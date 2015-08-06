global BangBangF_data ;

addpath('matlab_scripts') ;

numNodes      = 100 ;
nodes         = 0:1/(numNodes-1):1 ;
nodeToSegment = ones(numNodes,1) ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_x = true ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.final_v   = true ;
data.Fcontrol.epsilon             = 0.001 ;
data.Fcontrol.h                   = 0.001 ;

BangBangF_Setup( data ) ;

z_guess = BangBangF_Guess() ;

UM = BangBangF_u_system( z_guess ) ;
F  = BangBangF_system( z_guess, UM ) ;
J  = BangBangF_jacobian( z_guess, UM ) ;
norm(F,inf)

z = z_guess - J\F ;
for k=1:3
  UM = BangBangF_u_system( z ) ;
  F  = BangBangF_system( z, UM ) ;
  J  = BangBangF_jacobian( z, UM ) ;
  norm(F,inf)
  z = z - J\F ;
end

[Z,pars,omega,UM] = BangBangF_unpack( z ) ;

% Z
% pars
% omega
% UM
x  = Z(1,:) ;
v  = Z(2,:) ;
l1 = Z(3,:) ;
l2 = Z(4,:) ;

subplot(2,2,1) ;
plot( nodes, v, '-o' ) ;
title('v') ;

subplot(2,2,2) ;
plot( (nodes(2:end)+nodes(1:end-1))/2, UM, '-o' ) ;

subplot(2,2,3) ;
plot( nodes, l1, '-o' ) ;

subplot(2,2,4) ;
plot( nodes, l2, '-o' ) ;

