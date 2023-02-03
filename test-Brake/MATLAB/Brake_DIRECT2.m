global N epsilon;

N = 20;
epsilon = 0.1;

x0      = guess();
[lb,ub] = bounds();

opts = optimoptions(...
  'fmincon', ...
  'CheckGradients',false, ...
  'Display','iter', ...
  'MaxFunctionEvaluations', 100000, ...
  'ConstraintTolerance', 1e-12, ...
  'SpecifyConstraintGradient',false, ...
  'SpecifyObjectiveGradient',false ...
);

Z = fmincon( @fun, x0, [], [], [], [], lb, ub, @nonlcons, opts );

[ X, V, ACC, T ] = unpack( Z );

FUN = fd_ode( X, V, ACC, T );

R = constraints( Z );
Time = (T*(0:N)/N).';

AA = reshape( [ACC.';ACC.'], 1, 2*N );
XX = reshape( [X(1:end-1).';X(2:end).'], 1, 2*N );
TT = reshape( [Time(1:end-1).';Time(2:end).'], 1, 2*N );


subplot(3,1,1);
plot( TT, AA, 'LineWidth', 3 );
ylim([-1.1,1.1]);
title('acceleration');

subplot(3,1,2);
plot( Time, V, 'LineWidth', 3 );
ylim([0,1.1]);
title('velocity');

subplot(3,1,3);
plot( Time, X, 'LineWidth', 3 );


%
% ========================================================================
%
function Z = guess()
  global N;
  m = N+1;
  X = ((0:N)./N).';
  V = ones(m,1);
  A = -ones(N,1);
  T = 1;
  Z = [X;V;A;T];
end
%
% ========================================================================
%
function [L,U] = bounds()
  global N;
  m    = N+1;
  Xmin = zeros(m,1); Xmax = 10*ones(m,1);
  Vmin = zeros(m,1); Vmax = 10*ones(m,1);
  Amin = -ones(N,1); Amax = ones(N,1);
  Tmin = 0.001;      Tmax = 10;
  L = [ Xmin; Vmin; Amin; Tmin ]-0.0001;
  U = [ Xmax; Vmax; Amax; Tmax ];
end
%
% ========================================================================
%
function FUN = fd_ode( X, V, ACC, T )
  global N;
  h   = 1/N;
  VM  = (V(2:end)+V(1:end-1))./2;
  DX  = (X(2:end) - X(1:end-1))/h;
  DV  = (V(2:end) - V(1:end-1))/h; 
  FD1 = DX - T*VM;
  FD2 = DV - T*ACC;
  BC  = [ X(1); V(1)-1; V(end) ];
  FUN = [ FD1; FD2; BC ];
end
%
% ========================================================================
%
function RES = target( X, V, ACC, T )
  global N epsilon;
  RES = X(end)-T*epsilon*sum(log(cos((pi/2)*ACC)))/N;
end
%
% ========================================================================
%
function [ X, V, ACC,T ] = unpack( Z )
  global N;
  m   = N+1;
  X   = Z(1:m);
  V   = Z(m+1:2*m);
  ACC = Z(2*m+1:3*m-1);
  T   = Z(3*m);
end
%
% ========================================================================
%
function varargout = fun( Z )
  [ X, V, ACC, T ] = unpack( Z );
  [varargout{1:nargout}] = target( X, V, ACC, T );
end
%
% ========================================================================
%
function C = constraints( Z )
  [ X, V, ACC, T ] = unpack( Z );
  C = fd_ode( X, V, ACC, T );
end
%
% ========================================================================
%
function [c,ceq,Dc,Dceq] = nonlcons( Z )
  c    = [];
  Dc   = [];
  ceq  = constraints( Z );
  Dceq = []; % vuole jacobiano trasposto!
end
