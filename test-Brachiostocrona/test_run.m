global Brachiostocrona_data ;

addpath('matlab_scripts') ;
addpath('matlab_user_script') ;

numNodes      = 501 ;
nodes         = 0:1/(numNodes-1):1 ;
nodeToSegment = ones(1,numNodes) ;

data.nodes         = nodes ;
data.nodeToSegment = nodeToSegment ;
data.BoundaryConditions.initial_x = true ;
data.BoundaryConditions.initial_y = true ;
data.BoundaryConditions.initial_v = true ;
data.BoundaryConditions.final_x   = true ;
data.BoundaryConditions.final_y   = true ;

g  = 9.81 ;
yf = -3 ;
Tf = (-2.0*yf/g)^(1/2) ;
xf = 10 ;
Vf = sqrt(xf^2+yf^2)/sqrt(-2.0*yf/g) ;
% Model Parameters
data.Parameters.g = g ;
data.Parameters.mass = 1 ;
% Guess Parameters
data.Parameters.Tf = Tf ;
data.Parameters.Vf = Vf ;
% Boundary Conditions
data.Parameters.xf = xf ;
data.Parameters.yf = yf ;

Brachiostocrona_Setup( data ) ;

if true

fname = 'Brachiostocrona_dump_' ;

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
n    = r(1)
ZZ   = zeros(n,1) ;
for k=1:n
  line = fgetl(fid) ;
  r = sscanf(line,'%f') ;
  ZZ(k) = r(1) ;
end
fclose(fid) ;

[Z_,pars_,omega_,UM_,UC_] = Brachiostocrona_unpack( ZZ ) ;
JJ = sparse( I, J, R ) ;
end


z = Brachiostocrona_Guess() ;
n = length(z) ;

size(z)
size(ZZ)

norm(z-ZZ,Inf)

alpha = ones(1,100) ;
alpha(1:7) = [1,0.30377,0.46879,1.00000,1.00000,1.00000,1.00000] ;

for k=1:10
  UM = Brachiostocrona_UM_eval( z ) ;
  F  = Brachiostocrona_system( z, UM ) ;
  J  = Brachiostocrona_jacobian( z, UM ) ;
  d  = J\F ;
  fprintf( 'iter %d norm1 = %g dnorm = %g\n', k, norm(F,1)/n, norm(d,1)/n );
  z = z - alpha(k)*d ;
end

UM = Brachiostocrona_UM_eval( z ) ;
F  = Brachiostocrona_system( z, UM ) ;
J  = Brachiostocrona_jacobian( z, UM ) ;
fprintf( 'norm1 = %g dnorm = %g\n', norm(F,1)/n, norm(d,1)/n );

%norm(F-FF,Inf)

[Z,pars,omega,UM,UC] = Brachiostocrona_unpack( z ) ;

% Z
% pars
% omega
% UM
x      = Z(1,:) ;
y      = Z(2,:) ;
v      = Z(3,:) ;
T      = Z(4,:) ;
theta  = Z(5,:) ;
l1     = Z(6,:) ;
l2     = Z(7,:) ;
l3     = Z(8,:) ;
l4     = Z(9,:) ;
l5     = Z(10,:) ;

subplot(2,2,1) ;
plot( x, y, '-o' ) ;
title('x,y') ;

subplot(2,2,2) ;
nn = (nodes(2:end)+nodes(1:end-1))/2 ;
plot( UC(end,:), UC(1,:), '-o'  ) ;
title('vtheta') ;

subplot(2,2,3) ;
plot( nodes, theta, '-o' ) ;
title('theta') ;
