global BangBangF_data ;

addpath('matlab_scripts') ;
addpath('matlab_user_scripts') ;

numNodes      = 101 ;
nodes         = 0:1/(numNodes-1):1 ;
nodeToSegment = ones(numNodes,1) ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_x = true ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.final_v   = true ;

BangBangF_Setup( data ) ;

z  = BangBangF_Guess() ;
UM = BangBangF_UM_eval( z ) ;
n  = length(z) ;

ZUM = [ z ; UM ] ;
for k=1:4
  F  = BangBangF_big_system( ZUM ) ;
  J  = BangBangF_big_jacobian( ZUM ) ;
  d  = J\F ;
  fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );
  ZUM = ZUM - d ;
  alpha = 1 ;
end

F  = BangBangF_big_system( ZUM ) ;
J  = BangBangF_big_jacobian( ZUM ) ;
fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

%z-ZZ
%norm(F-FF,Inf)

[Z,pars,omega,UM] = BangBangF_unpack( ZUM ) ;

% Z
% pars
% omega
% UM
x  = Z(1,:) ;
v  = Z(2,:) ;
l1 = Z(3,:) ;
l2 = Z(4,:) ;

x_  = Z(1,:) ;
v_  = Z(2,:) ;
l1_ = Z(3,:) ;
l2_ = Z(4,:) ;
UM_ = UM ;
subplot(2,2,1) ;
plot( nodes, v, '-o', nodes, v_ ) ;
title('v') ;

subplot(2,2,2) ;
nn = (nodes(2:end)+nodes(1:end-1))/2 ;
plot( nn, UM, '-o', nn, UM_ ) ;
title('u') ;

subplot(2,2,3) ;
plot( nodes, l1, '-o', nodes, l1_ ) ;

subplot(2,2,4) ;
plot( nodes, l2, '-o', nodes, l2_ ) ;

if false
  subplot(1,3,1);
  spy(J) ;
  title('J') ;
  
  subplot(1,3,2);
  spy(JJ) ;
  title('JJ') ;
  
  subplot(1,3,3);
  spy(J-JJ) ;
end
