global N;

N = 100;

x0      = guess();
[lb,ub] = bounds();

opts = optimoptions(...
  'fmincon', ...
  'CheckGradients',true, ...
  'Display','iter', ...
  'SpecifyConstraintGradient',true, ...
  'SpecifyObjectiveGradient',true ...
);

Z = fmincon( @fun, x0, [], [], [], [], lb, ub, @nonlcons, opts );

[ X, V, ACC, T ] = unpack( Z );

R = constraints( Z );

AA = reshape( [ACC.';ACC.'], 1, 2*N );
XX = reshape( [X(1:end-1).';X(2:end).'], 1, 2*N );

subplot(3,1,1);
plot( XX, AA, 'LineWidth', 3 );
xlim([X(1),X(end)]);
ylim([-1.1,1.1]);
title('acceleration');

subplot(3,1,2);
plot( X, V, 'LineWidth', 3 );
xlim([X(1),X(end)]);
ylim([0,1.1]);
title('velocity');

subplot(3,1,3);
plot( X, 'LineWidth', 3 );
xlim([0,length(X)]);

%
% ========================================================================
%
function Z = guess()
  global N;
  m = N+1;
  X = ((0:N)./N).';
  V = ones(m,1);
  A = zeros(N,1);
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
function varargout = fd_ode( X, V, ACC, T )
  global N;
  h   = 1/N;
  tmp = h*T;
  VM  = (V(2:end)+V(1:end-1))./2;
  FD1 = X(2:end) - X(1:end-1) - tmp*VM;
  FD2 = V(2:end) - V(1:end-1) - tmp*ACC;
  BC  = [ X(1); V(1)-1; V(end) ];
  varargout{1} = [ FD1; FD2; BC ];
  if nargout > 1
    m   = N+1;
    J1x = zeros(N,m); J1v = zeros(N,m); J1a = zeros(N,N); J1T = zeros(N,1);
    J2x = zeros(N,m); J2v = zeros(N,m); J2a = zeros(N,N); J2T = zeros(N,1);
    JBx = zeros(3,m);
    JBv = zeros(3,m);
    JBa = zeros(3,N);
    JBT = zeros(3,1);
    for k=1:N
      J1x(k,k:k+1) = [-1,1];
      J1v(k,k:k+1) = tmp*[-0.5,-0.5];
      J2v(k,k:k+1) = [-1,1];
      J2a(k,k)     = -tmp;
    end
    J1T(:,1)  = -h*VM;
    J2T(:,1)  = -h*ACC;
    JBx(1,1) = 1;
    JBv(2,1) = 1;
    JBv(3,m) = 1;
    varargout{2} = sparse([J1x,J1v,J1a,J1T; ...
                           J2x,J2v,J2a,J2T; ...
                           JBx,JBv,JBa,JBT]);
  end
end
%
% ========================================================================
%
function varargout = target( X, V, ACC, T )
  global N;
  varargout{1} = X(end);
  if nargout > 1
    m            = N+1;
    res          = zeros(3*m,1);
    res(m)       = 1;
    varargout{2} = res;
  end
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
function varargout = constraints( Z )
  [ X, V, ACC, T ] = unpack( Z );
  [varargout{1:nargout}] = fd_ode( X, V, ACC, T );
end
%
% ========================================================================
%
function [c,ceq,Dc,Dceq] = nonlcons( Z )
  c          = [];
  Dc         = [];
  [ceq,Dceq] = constraints( Z );
  Dceq       = Dceq.'; % vuole jacobiano trasposto!
end
