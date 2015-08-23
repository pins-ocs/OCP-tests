global BangBangF_data ;

addpath('matlab_scripts') ;

if false

fid = fopen('BangBangF_dump_JAC.mm', 'r');
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

fid = fopen('BangBangF_dump_F.mm', 'r');
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

fid = fopen('BangBangF_dump_Z.mm', 'r');
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

JJ = sparse( I, J, R ) ;
d = JJ\FF ;
fprintf( 'READ norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

end

numNodes      = 101 ;
nodes         = 0:1/(numNodes-1):1 ;
nodeToSegment = ones(numNodes,1) ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_x = true ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.final_v   = true ;

BangBangF_Setup( data ) ;

z = BangBangF_Guess() ;
n = length(z)

UM = BangBangF_u_system( z ) ;
F  = BangBangF_system( z, UM ) ;
J  = BangBangF_jacobian( z, UM ) ;
%d  = J\F ;
%fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );
for k=1:3
  UM = BangBangF_u_system( z ) ;
  F  = BangBangF_system( z, UM ) ;
  J  = BangBangF_jacobian( z, UM ) ;
  d  = J\F ;
  fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );
  z = z - d ;
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
title('u') ;

subplot(2,2,3) ;
plot( nodes, l1, '-o' ) ;

subplot(2,2,4) ;
plot( nodes, l2, '-o' ) ;

