%
%
%  target: x(end) + int_0^1 P(a) + (epsilon/2)*(a-A)^2 dt
%
%  P(a) = -mu*log(cos((pi/2)*a))
%  P'(a) = -(mu*pi/2)*tan((pi/2)*a)
%
%  ODE:  x' = T v
%        v' = T a
%        T' = 0
%
%  Hamiltonian
%
%  H = lambda1 T v + lambda2 T a + (epsilon/2)*(a-A)^2 + P(a)
%
%  co-equation
%
%  H_x = 0
%  H_v = lambda1 T
%  H_T = lambda1 v + lambda2 a
%
%  control (indirect)
%
%  H_a   = lambda2 T + epsilon*(a-A) + P'(a) --> a = A - T*lambda2/epsilon (se P(a) == 0)
%
%  control (Borzi)
%
%  K   = P(a) + lambda2 T + lambda2 T a + (epsilon/2)*(a-A)^2
%  K_a = P'(a) + lambda2 T + epsilon*(a - A)
%
%  List of unknown for BVP
%  Z = [ X V T L1 L2 L3]
%

global N mu epsilon ABAR;

close all;

N  = 10;
mu = 1e-4;
epsilon = 10000;

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

opts = optimoptions(...
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

ABAR = -0.99*ones(N,1);

x0 = guess();
[ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, [], [], opts );
%[ Z, fval, exitflag, output ] = fsolve( @sys, x0, opts );

fprintf('exitflag = %d\n',exitflag);
fprintf('iterations = %d\n',output.iterations);
fprintf('%s\n',output.message);

[ X, V, T, L1, L2, L3, ACC ] = unpack( Z );

%L2M = (L2(1:end-1)+L2(2:end))./2;
%TM  = (T(1:end-1)+T(2:end))./2;
%ACC = get_ACC( L2M, TM );

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
plot( 1:length(L1), L3, 'LineWidth', 3 );
title('lambda 1/2/3');

%
% ========================================================================
%
function Z = guess()
  global N;
  m  = N+1;
  X  = ((0:N)./N).';
  V  = ones(m,1);
  T  = ones(m,1);
  L1 = zeros(m,1);
  L2 = zeros(m,1);
  L3 = zeros(m,1);
  ACC = zeros(N,1);
  Z  = [X;V;T;L1;L2;L3;ACC];
end
%
% ========================================================================
%
function [L,U] = bounds()
  global N;
  m    = N+1;
  epsi = 1e-6;
  Xmin = zeros(m,1)-epsi; Xmax = 10*ones(m,1);
  Vmin = zeros(m,1)-epsi; Vmax = 10*ones(m,1);
  Tmin = zeros(m,1)+epsi; Tmax = 10*ones(m,1);
  Amin = -ones(N,1)+epsi; Amax = ones(N,1)-epsi;
  L = [ Xmin; Vmin; Tmin; -Inf*ones(3*m,1); Amin ];
  U = [ Xmax; Vmax; Tmax;  Inf*ones(3*m,1); Amax ];
end
%
% ========================================================================
function PA = penalty( ACC )
  global mu;
  PA  = Inf*ones(size(ACC));
  IDX = find( ACC < 1 & ACC > -1 );
  PA(IDX) = -mu*log(cos((pi/2)*ACC(IDX)));
end
% ========================================================================
function DPA = penalty_D( ACC )
  global mu;
  DPA = Inf*ones(size(ACC));
  IDX = find( ACC <= -1+eps );
  DPA(IDX) = -Inf;
  IDX = find( ACC < 1-eps & ACC > -1+eps );
  DPA(IDX) = -(mu*pi/2)*tan((pi/2)*ACC(IDX));
end
%
% ========================================================================
%
function F = fd_sys( X, V, T, L1, L2, L3, ACC )
  global N mu epsilon ABAR;
  h    = 1/N;
  X_D  = (X(2:end)-X(1:end-1))./h;
  V_D  = (V(2:end)-V(1:end-1))./h;
  T_D  = (T(2:end)-T(1:end-1))./h;
  L1_D = (L1(2:end)-L1(1:end-1))./h;
  L2_D = (L2(2:end)-L2(1:end-1))./h;
  L3_D = (L3(2:end)-L3(1:end-1))./h;

  VM   = (V(2:end)+V(1:end-1))./2;
  TM   = (T(2:end)+T(1:end-1))./2;
  L1M  = (L1(2:end)+L1(1:end-1))./2;
  L2M  = (L2(2:end)+L2(1:end-1))./2;
%  H_T = -mu*log(cos(pi/2*a)) + lambda1 v + lambda2 a +  [ + (epsilon/2)*(a-A)^2 ]
%  ACC = get_ACC( L2M, TM );

  FD1 = X_D - TM.*VM;
  FD2 = V_D - TM.*ACC;
  FD3 = T_D;
  FD4 = L1_D;
  FD5 = L2_D+TM.*L1M;
  FD6 = L3_D + L1M.*VM + L2M.*ACC;
  FD7 = L2M.*TM + epsilon*(ACC - ABAR) + penalty_D(ACC);
  BC  = [ X(1); V(1)-1; V(end); 1-L1(end); L3(1); L3(end) ];
  F   = [ FD1; FD2; FD3; FD4; FD5; FD6; FD7; BC ];
end
%
% ========================================================================
%
function [ X, V, T, L1, L2, L3, ACC ] = unpack( Z )
  global N;
  m  = N+1;
  X  = Z(0*m+1:1*m);
  V  = Z(1*m+1:2*m);
  T  = Z(2*m+1:3*m);
  L1 = Z(3*m+1:4*m);
  L2 = Z(4*m+1:5*m);
  L3 = Z(5*m+1:6*m);
  ACC = Z(6*m+1:7*m-1);
end
%
% ========================================================================
%
function F = sys( Z )
  [ X, V, T, L1, L2, L3, ACC ] = unpack( Z );
  F = fd_sys( X, V, T, L1, L2, L3, ACC );
end
