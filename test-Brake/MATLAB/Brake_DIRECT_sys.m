global N epsilon;

close all;

N       = 200;
epsilon = 0.000000001;

[lb,ub] = bounds();

opts = optimoptions(...
  'lsqnonlin', ...
  'FunctionTolerance',1e-12, ...
  'StepTolerance', 1e-12, ...
  'MaxIterations', 1000, ...
  'MaxFunctionEvaluations', 500000, ...
  'CheckGradients',false, ...
  'Display','iter', ...
  'SpecifyObjectiveGradient',false ...
);

fprintf('epsilon = %g\n',epsilon);

x0 = guess();
[ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, [], [], opts );

fprintf('exitflag = %d\n',exitflag);
fprintf('iterations = %d\n',output.iterations);
fprintf('%s\n',output.message);

[ X, V, L1, L2, T ] = unpack( Z );

ACC = get_ACC( (L2(1:end-1)+L2(2:end))./2, T );

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
hold off;
plot( 1:length(L1), L1, 'LineWidth', 3 );
hold on;
plot( 1:length(L1), L2, 'LineWidth', 3 );
%xlim([X(1),X(end)]);
title('lambda 2');

%
% ========================================================================
%
function Z = guess()
  global N;
  m  = N+1;
  X  = ((0:N)./N).';
  V  = ones(m,1);
  L1 = ones(m,1);
  L2 = 1-X;
  T  = 1;
  Z  = [X;V;L1;L2;T];
end
%
% ========================================================================
%
function [L,U] = bounds()
  global N;
  m    = N+1;
  Xmin = zeros(m,1); Xmax = 10*ones(m,1);
  Vmin = zeros(m,1); Vmax = 10*ones(m,1);
  Amin = -0.9999*ones(N,1); Amax = 0.9999*ones(N,1);
  Tmin = 0.001;      Tmax = 10;
  L = [ Xmin; Vmin; -Inf*ones(2*m,1); Tmin ]-0.0001;
  U = [ Xmax; Vmax;  Inf*ones(2*m,1); Tmax ];
end
%
% ========================================================================
%
function ACC = get_ACC( L2, T )
  global N epsilon;
  ACC = -(2/pi)*atan((2*T/(pi*epsilon))*L2);
end

%
% ========================================================================
%
function F = fd_sys( X, V, L1, L2, T )
  global N epsilon;
  h    = 1/N;
  VM   = (V(2:end)+V(1:end-1))./2;
  V_D  = (V(2:end)-V(1:end-1))./h;
  X_D  = (X(2:end)-X(1:end-1))./h;
  L1_D = (L1(2:end)-L1(1:end-1))./h;
  L2_D = (L2(2:end)-L2(1:end-1))./h;
  L1M  = (L1(2:end)+L1(1:end-1))./2;
  L2M  = (L2(2:end)+L2(1:end-1))./2;

  ACC = get_ACC( L2M, T );

  FD1 = X_D - T*VM;
  FD2 = V_D - T*ACC;
  FD3 = L1_D;
  FD4 = L2_D+T*L1M;
  %  VA SCALATA!
  FD5 = sum(h*(L1M.*VM + L2M.*ACC -epsilon*log( cos(pi/2*ACC) ) ));
  BC  = [ X(1); V(1)-1; V(end); 1-L1(end) ];
  W   = 1;
  F   = [ W*FD1; W*FD2; FD3; FD4; FD5; BC ];
end
%
% ========================================================================
%
function [ X, V, L1, L2, T ] = unpack( Z )
  global N;
  m   = N+1;
  X   = Z(0*m+1:1*m);
  V   = Z(1*m+1:2*m);
  L1  = Z(2*m+1:3*m);
  L2  = Z(3*m+1:4*m);
  T   = Z(4*m+1);
end
%
% ========================================================================
%
function F = sys( Z )
  global epsilon;
  [ X, V, L1, L2, T ] = unpack( Z );
  F = fd_sys( X, V, L1, L2, T );
end
