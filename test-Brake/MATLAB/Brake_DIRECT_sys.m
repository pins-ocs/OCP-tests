global N epsilon epsilon2;

close all;

N        = 400;
epsilon  = 0.1;
epsilon2 = 0.0;

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

opts1 = optimoptions(...
  'fsolve', ...
  'FunctionTolerance',1e-12, ...
  'StepTolerance', 1e-12, ...
  'MaxIterations', 1000, ...
  'MaxFunctionEvaluations', 500000, ...
  'CheckGradients',false, ...
  'Display','iter', ...
  'SpecifyObjectiveGradient',false ...
);

fprintf('epsilon = %g\n',epsilon);

x0_sys = guess();
F0_sys = sys( x0_sys );
[ X, V, L1, L2, OM, T ] = unpack( x0_sys );
ACC0_sys = get_ACC( (L2(1:end-1)+L2(2:end))./2, T );

%[ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, lb, ub, opts );
[ Z_sys, fval, exitflag, output ] = fsolve( @sys, x0_sys, opts1 );

fprintf('exitflag = %d\n',exitflag);
fprintf('iterations = %d\n',output.iterations);
fprintf('%s\n',output.message);

[ X, V, L1, L2, OM, T ] = unpack( Z_sys );

T

ACC = get_ACC( (L2(1:end-1)+L2(2:end))./2, T );

AA   = reshape( [ACC;ACC], 1, 2*N );
XX   = reshape( [X(1:end-1).';X(2:end).'], 1, 2*N );
ZETA = [0:1/(length(L1)-1):1].';
ZZ   = reshape( [ZETA(1:end-1).';ZETA(2:end).'], 1, 2*N );

subplot(3,1,1);
plot( ZZ, AA, 'LineWidth', 3 );
%xlim([X(1),X(end)]);
ylim([-1.1,1.1]);
grid on
title('acceleration');

subplot(3,1,2);
hold on
plot( ZETA, V, 'LineWidth', 3 );
hold on
plot( ZETA, X, 'LineWidth', 3 );
%xlim([X(1),X(end)]);
%ylim([0,1.1]);
grid on
legend('V','X');
title('velocity');

subplot(3,1,3);
hold off;
plot( ZETA, L1, 'LineWidth', 3 );
hold on;
plot( ZETA, L2, 'LineWidth', 3 );
%xlim([X(1),X(end)]);
grid on
title('lambda 2');

%
% ========================================================================
%
function Z = guess()
  global N;
  m  = N+1;
  X  = ((0:N)./N);
  V  = ones(1,m);
  L1 = ones(1,m);
  L2 = 1-X;
  T  = 1;
  OM = [0 0 0];
  Z  = [reshape( [X; V; L1; L2], 1, 4*m), OM, T];
end
%
% ========================================================================
%
function [L,U] = bounds()
  global N;
  m     = N+1;
  Xmin  = zeros(1,m);        Xmax  = 10*ones(1,m);
  Vmin  = zeros(1,m);        Vmax  = 10*ones(1,m);
  L1min = -Inf*ones(1,m);    L1max = Inf*ones(1,m);
  L2min = -Inf*ones(1,m);    L2max = Inf*ones(1,m);
  Amin  = -0.9999*ones(1,N); Amax  = 0.9999*ones(1,N);
  Omin  = -Inf*ones(1,N);    Omax  = Inf*ones(1,N);
  Tmin  = 0.001;             Tmax  = 10;
  L = [ reshape( [Xmin; Vmin; L1min; L2min], 1, 4*m), Omin, Tmin ].'-0.0001;
  U = [ reshape( [Xmax; Vmax; L1max; L2max], 1, 4*m), Omax, Tmax ].';
end
%
% ========================================================================
%
function ACC = get_ACC( L2, T )
  global N epsilon;
  ACC = -(2/pi)*atan((2/(pi*epsilon))*L2);
end

%
% ========================================================================
%
function F = fd_sys( X, V, L1, L2, OM, T )
  global N epsilon epsilon2;
  h = 1/N;

  V_D  = (V(2:end)-V(1:end-1))./h;
  X_D  = (X(2:end)-X(1:end-1))./h;
  L1_D = (L1(2:end)-L1(1:end-1))./h;
  L2_D = (L2(2:end)-L2(1:end-1))./h;

  VM   = (V(2:end)+V(1:end-1))./2;
  L1M  = (L1(2:end)+L1(1:end-1))./2;
  L2M  = (L2(2:end)+L2(1:end-1))./2;

  ACC = get_ACC( L2M, T );

  FD1 = X_D - T*VM;
  FD2 = V_D - T*ACC;
  FD3 = L1_D;
  FD4 = L2_D+T*L1M;
  %  VA SCALATA!
  FD5 = -epsilon2/T + sum(h*(L1M.*VM + L2M.*ACC -epsilon*log( cos(pi/2*ACC) ) ));
  BC  = [ X(1), V(1)-1, V(end), OM(1)+L1(1), OM(2)+L2(1), 1-L1(end), OM(3)-L2(end)];
  F   = [ reshape( [FD1; FD2; FD3; FD4], 1, 4*N), BC, FD5 ];
end
%
% ========================================================================
%
function [ X, V, L1, L2, OM, T ] = unpack( Z )
  global N;
  m  = N+1;
  X  = Z(1:4:4*m-2);
  V  = Z(2:4:4*m-1);
  L1 = Z(3:4:4*m-0);
  L2 = Z(4:4:4*m  );
  OM = Z(4*m+1:4*m+3);
  T  = Z(4*m+4);
end
%
% ========================================================================
%
function F = sys( Z )
  global epsilon;
  [ X, V, L1, L2, OM, T ] = unpack( Z );
  F = fd_sys( X, V, L1, L2, OM, T );
end
