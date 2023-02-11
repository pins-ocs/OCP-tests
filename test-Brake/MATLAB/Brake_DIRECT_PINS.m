global OCP;

% nodes    = 151
% epsilon  = 0.1
% epsilon2 = 0
% mu       = 0
%
%                                          Norm of      First-order   Trust-region
%  Iteration  Func-count     f(x)          step         optimality    radius
%      0        609         87.1358                           135               1
%      1       1218         72.1477              1            173               1
%      2       1827         33.6804            2.5           57.8             2.5
%      3       2436         1.62619        5.53848           23.5            6.25
%      4       3045     0.000348359       0.535498          0.589            13.8
%      5       3654     2.07145e-05      0.0822983          0.127            13.8
%      6       4263     1.00344e-06      0.0400459          0.033            13.8
%      7       4872     2.91822e-08      0.0161049        0.00399            13.8
%      8       5481     1.71158e-10     0.00424277       0.000882            13.8
%      9       6090      3.0136e-12    0.000333739       0.000248            13.8
%     10       6699     1.44453e-15    8.26106e-06       6.47e-06            13.8
%     11       7308     4.84404e-19    1.29247e-07       9.23e-08            13.8


close all;

addpath('../generated_code/ocp-interfaces/Matlab')

% create object
OCP = Brake( 'Brake' );
OCP.setup('../generated_code/data/Brake_Data');  % automatically try extension .rb and .lua
OCP.set_info_level(4);
OCP.set_guess(); % use default guess generated in MAPLE
data = OCP.get_ocp_data();
%data.Parameters

fprintf( 'nodes    = %d\n', OCP.get_num_nodes() );
fprintf( 'epsilon  = %g\n', data.Parameters.epsilon );
fprintf( 'epsilon2 = %g\n', data.Parameters.epsilon2 );
%fprintf( 'mu       = %g\n', data.Parameters.mu );

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

x0_pins = guess();
F0_pins = sys( x0_pins );
ACC0_pins = get_ACC( x0_pins );

%[ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, lb, ub, opts );
[ Z_pins, fval, exitflag, output ] = fsolve( @sys, x0_pins, opts1 );

fprintf('exitflag = %d\n',exitflag);
fprintf('iterations = %d\n',output.iterations);
fprintf('%s\n',output.message);

[ X, V, L1, L2, T ] = unpack( Z_pins );

T

ACC = get_ACC( Z_pins );

N    = OCP.get_num_nodes()-1;
AA   = reshape( [ACC.';ACC.'], 1, 2*N );
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
  global OCP;
  m  = OCP.get_num_nodes();
  s  = ((0:m-1)./(m-1)).';
  X  = OCP.guess_x(s);
  V  = OCP.guess_v(s);
  L1 = OCP.guess_lambda1(s);
  L2 = OCP.guess_lambda2(s);
  T  = 1;
  Z = OCP.pack( [X.';V.'], [L1.';L2.'], T, [0,0,0] );
end
%
% ========================================================================
%
function [L,U] = bounds()
  global OCP;
  m    = OCP.get_num_nodes();
  Xmin = zeros(m,1);          Xmax = 10*ones(m,1);
  Vmin = zeros(m,1);          Vmax = 10*ones(m,1);
  Amin = -0.9999*ones(m-1,1); Amax = 0.9999*ones(m-1,1);
  Tmin = 0.001;               Tmax = 10;
  L = [ Xmin; Vmin; -Inf*ones(2*m,1); Tmin ]-0.0001;
  U = [ Xmax; Vmax;  Inf*ones(2*m,1); Tmax ];
end
%
function ACC = get_ACC( Z )
  global OCP;
  UG  = OCP.guess_U( Z );
  ACC = OCP.eval_U( Z, UG );
end
%
% ========================================================================
%
function [ X, V, L1, L2, T, OMEGA ] = unpack( Z )
  global OCP;
  m  = OCP.get_num_nodes();
  [XX,LL,PARS,OMEGA] = OCP.unpack( Z );
  X  = XX(1:2:end);
  V  = XX(2:2:end);
  L1 = LL(1:2:end);
  L2 = LL(2:2:end);
  T  = PARS(1);
end
%
% ========================================================================
%
function F = sys( Z )
  global OCP;
  UG  = OCP.guess_U( Z );
  ACC = OCP.eval_U( Z, UG );
  F   = OCP.eval_F( Z, ACC );
  %JF  = OCP.eval_JF( Z, ACC );
end
