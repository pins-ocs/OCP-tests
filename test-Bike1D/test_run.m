global Bike1D_data ;

addpath('matlab_scripts') ;
addpath('matlab_user_scripts') ;

numNodes      = 1001 ;
nodes         = 0:1000/(numNodes-1):1000 ;
nodeToSegment = ones(numNodes,1) ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.final_v = true ;
% Model Parameters
data.Parameters.g       = 9.81 ;
data.Parameters.muf_min = -1 ;
data.Parameters.mur_max = 1  ;
data.Parameters.mur_min = -1 ;
% Guess Parameters
% Boundary Conditions
data.Parameters.v_f = 10 ;
data.Parameters.v_i = 10 ;
% Post Processing Parameters
% User Function Parameters
data.Parameters.Pmax = 50000 ;
data.Parameters.m    = 275 ;
data.Parameters.vmax = 100 ;

Bike1D_Setup( data ) ;

z = Bike1D_Guess() ;
n = length(z) ;

for k=1:20
  UM = Bike1D_UM_eval( z ) ;
  F  = Bike1D_system( z, UM ) ;
  J  = Bike1D_jacobian( z, UM ) ;
  d  = J\F ;
  fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );
  z = z - d ;
end

UM = Bike1D_UM_eval( z ) ;
F  = Bike1D_system( z, UM ) ;
J  = Bike1D_jacobian( z, UM ) ;
fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

%norm(F-FF,Inf)

[Z,pars,omega,UM] = Bike1D_unpack( z ) ;

% Z
% pars
% omega
% UM
v  = Z(1,:) ;
l1 = Z(1,:) ;

subplot(2,2,1) ;
plot( nodes, v, '-o' ) ;
title('v') ;

subplot(2,2,2) ;
nn = (nodes(2:end)+nodes(1:end-1))/2 ;
plot( nn, UM(1:1000), '-o', nn, UM(1001:2000)  ) ;
title('u') ;

subplot(2,2,3) ;
plot( nodes, l1, '-o' ) ;
