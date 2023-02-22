close all;

% Intance of PINS object for OCP
global OCP;

addpath('../generated_code/ocp-interfaces/Matlab')

% create object
OCP = stirred_tank( 'stirred_tank' );

% read data file
OCP.setup('../generated_code/data/stirred_tank_Data');

OCP.set_info_level(4);

% use default guess generated in MAPLE
% get last computed solution, no computation = GUESS
OCP.set_guess();
[Z0,U0] = OCP.get_raw_solution();

%data = OCP.get_ocp_data();
%data.Parameters
%fprintf( 'nodes    = %d\n', OCP.get_num_nodes() );
%fprintf( 'epsilon  = %g\n', data.Parameters.epsilon );
%fprintf( 'epsilon2 = %g\n', data.Parameters.epsilon2 );
%fprintf( 'mu       = %g\n', data.Parameters.mu );

opts = optimoptions(...
  'fsolve', ...
  'FunctionTolerance',1e-12, ...
  'StepTolerance', 1e-12, ...
  'MaxIterations', 1000, ...
  'MaxFunctionEvaluations', 500000, ...
  'CheckGradients',false, ...
  'Display','iter', ...
  'SpecifyObjectiveGradient',true ...
);

[ Z, fval, exitflag, output ] = fsolve( @sys, Z0, opts );

fprintf('exitflag = %d\n',exitflag);
fprintf('iterations = %d\n',output.iterations);
fprintf('%s\n',output.message);

% compute controls
Uguess = OCP.guess_U( Z );
U      = OCP.eval_U( Z, Uguess );
OCP.set_raw_solution( Z, U );

%ZETA = OCP.zeta;
%X    = OCP.x;
%V    = OCP.v;
%L1   = OCP.lambda1;
%L2   = OCP.lambda2;
%ACC  = OCP.a;

subplot(3,1,1);
OCP.plot_states();
grid on

subplot(3,1,2);
OCP.plot_multipliers();
grid on

subplot(3,1,3);
OCP.plot_controls();
grid on

%
% ========================================================================
%
function [F,JF] = sys( Z )
  global OCP;
  UG  = OCP.guess_U( Z );
  ACC = OCP.eval_U( Z, UG );
  F   = OCP.eval_F( Z, ACC );
  JF  = OCP.eval_JF( Z, ACC );
end
