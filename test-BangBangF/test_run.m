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

if false

fname = 'BangBangF_dump_' ;

fid = fopen([fname 'JAC.mm'], 'r');
line = fgetl(fid);
line = fgetl(fid);
r    = sscanf(line, '%d%d%d');
n    = r(1) ;
n    = r(2) ;
nnz  = r(3) ;
I = zeros(nnz,1) ;
J = zeros(nnz,1) ;
R = zeros(nnz,1) ;
for k=1:nnz
  line = fgetl(fid) ;
  r = sscanf(line,'%d%d%f') ;
  I(k) = r(1) ;
  J(k) = r(2) ;
  R(k) = r(3) ;
end
fclose(fid) ;

fid = fopen([fname 'F.mm'], 'r');
line = fgetl(fid);
line = fgetl(fid);
r    = sscanf(line, '%d');
n    = r(1) ;
FF   = zeros(n,1) ;
for k=1:n
  line = fgetl(fid) ;
  r = sscanf(line,'%f') ;
  FF(k) = r(1) ;
end
fclose(fid) ;

fid = fopen([fname 'Z.mm'], 'r');
line = fgetl(fid);
line = fgetl(fid);
r    = sscanf(line, '%d');
n    = r(1) ;
ZZ   = zeros(n,1) ;
for k=1:n
  line = fgetl(fid) ;
  r = sscanf(line,'%f') ;
  ZZ(k) = r(1) ;
end
fclose(fid) ;

[Z_,pars_,omega_,UM_] = BangBangF_unpack( ZZ ) ;
JJ = sparse( I, J, R ) ;
end

%BangBangF_data.parsOmegaMapping = [ 3 1 2 ] ;
%BangBangF_data.omegaMapping     = [ 3 1 2 ] ;
%BangBangF_data.bcMapping        = [ 3 6 7 1 2 4 5 ] ;

z = BangBangF_Guess() ;
n = length(z) ;

alpha = 0.47414 ; % 0.44911 ;
for k=1:4
  UM = BangBangF_UM_eval( z ) ;
  F  = BangBangF_system( z, UM ) ;
  J  = BangBangF_jacobian( z, UM ) ;
  d  = J\F ;
  fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );
  z = z - alpha*d ;
  alpha = 1 ;
  %UM = BangBangF_UM_eval( z ) ;
  %F  = BangBangF_system( z, UM ) ;
  %fprintf( 'norm1 = %g\n', norm(F,1)/n );
end

UM = BangBangF_UM_eval( z ) ;
F  = BangBangF_system( z, UM ) ;
J  = BangBangF_jacobian( z, UM ) ;
fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

%z-ZZ
%norm(F-FF,Inf)

[Z,pars,omega,UM] = BangBangF_unpack( z ) ;

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
