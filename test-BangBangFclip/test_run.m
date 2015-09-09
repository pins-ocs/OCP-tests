global BangBangFclip_data ;

addpath('matlab_scripts') ;
addpath('matlab_user_scripts') ;

seg1  = 0:0.1/10:0.1 ;      
seg2  = 0:0.4/40:0.4 ;      
nodes = [ seg1 seg2+0.1 seg2+0.5 seg1+0.9 ] ;
numNodes = length(nodes) ;

nodeToSegment = [ ones(1,11) 2*ones(1,41) 3*ones(1,41) 4*ones(1,11) ] ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_x = true ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.initial_F = true ;
data.BoundaryConditions.final_v   = true ;
data.BoundaryConditions.final_F   = true ;

data.Parameters.maxClip = 1 ;
data.Parameters.minClip = -1 ;
data.Parameters.vFmax   = 10 ;

BangBangFclip_Setup( data ) ;

if false

fname = 'BangBangFclip_dump_' ;

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

[Z_,pars_,omega_,UM_] = BangBangFclip_unpack( ZZ ) ;
JJ = sparse( I, J, R ) ;
end

z = BangBangFclip_Guess() ;
UM = BangBangFclip_UM_eval( z ) ;
%UM = BangBangFclip_NLS_Controls( z, ones(size(UM)), -10*ones(size(UM)), 10*ones(size(UM)) ) ;

z  = BangBangFclip_LS_Multiplier( z, UM ) ;

alpha = ones(1,100) ;
alpha(1:6) = [ 0.30678 3.05E-08 6.37E-08 2.76E-08 0.12028 0.69362 ] ;

for k=1:10
  lambda = 1e-6/k^2 ;
  UM = BangBangFclip_UM_eval( z ) ;
  F  = BangBangFclip_system( z, UM ) ;
  J  = BangBangFclip_jacobian( z, UM ) ;
  %d  = (J.'*J+lambda*eye(size(J)))\(J.'*F) ;
  d  = J\F;
  fprintf( 'iter %d, norm1 = %g dnorm = %g\n', k, norm(F,1)/n, norm(d,1)/n );
  z = z - alpha(k)*d ;
  %z = z -d ;
end

%UM = BangBangFclip_UM_eval( z ) ;
F  = BangBangFclip_system( z, UM ) ;
J  = BangBangFclip_jacobian( z, UM ) ;
fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

[Z,pars,omega,UM,UC] = BangBangFclip_unpack( z ) ;

x  = Z(1,:) ;
v  = Z(2,:) ;
F  = Z(3,:) ;
l1 = Z(4,:) ;
l2 = Z(5,:) ;
l3 = Z(6,:) ;

subplot(2,2,1) ;
plot( nodes, v, '-o' ) ;
title('v') ;

subplot(2,2,2) ;
plot( UC(end,:), UC(1,:), '-o' ) ;

subplot(2,2,3) ;
plot( nodes, l1, '-o' , nodes, l2, '-o' , nodes, l3, '-o' ) ;
legend('l1','l2','l3') ;

subplot(2,2,4) ;
plot( nodes, l2, '-o' ) ;

