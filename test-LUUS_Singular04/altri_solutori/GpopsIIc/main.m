%------------------- Dynamic Soaring Problem -----------------------------%
% This example is taken from the following reference:                     %
% Zhao, Y. J., "Optimal Pattern of Glider Dynamic Soaring," Optimal       %
% Control Applications and Methods, Vol. 25, 2004, pp. 67-89.             %
%-------------------------------------------------------------------------%
clear all
clc

NPT                           = 1000;
% Phase 1 Information
iphase = 1;
bounds.phase(iphase).initialtime.lower  = 0;
bounds.phase(iphase).initialtime.upper  = 0;
bounds.phase(iphase).finaltime.lower    = 0;
bounds.phase(iphase).finaltime.upper    = 7;
bounds.phase(iphase).initialstate.lower = [1 0 0 0];
bounds.phase(iphase).initialstate.upper = [1 0 0 0];
bounds.phase(iphase).state.lower        = [-inf -inf -inf -inf];
bounds.phase(iphase).state.upper        = [inf inf inf inf];
bounds.phase(iphase).finalstate.lower   = [0 0 0 -inf];
bounds.phase(iphase).finalstate.upper   = [0 0 0 inf];
bounds.phase(iphase).control.lower      = -1;
bounds.phase(iphase).control.upper      = 1;
bounds.phase(iphase).integral.lower = [];
bounds.phase(iphase).integral.upper = [];
%bounds.phase(iphase).path.lower         = auxdata.lmin;
%bounds.phase(iphase).path.upper         = auxdata.lmax;
%bounds.eventgroup(1).lower              = zeros(1,3);
%bounds.eventgroup(1).upper              = zeros(1,3);
%bounds.parameter.lower                  = betamin;
%bounds.parameter.upper                  = betamax;


% CL0                         = CLmax;
guess.phase(iphase).time       = [0; 5] ;
guess.phase(iphase).state(:,1) = [1; 1] ;
guess.phase(iphase).state(:,2) = [0; 0] ;
guess.phase(iphase).state(:,3) = [0; 0] ;
guess.phase(iphase).state(:,4) = [0; 0] ;
guess.phase(iphase).control    = [0; 0] ;
guess.phase.integral           = [] ;

setup.name                             = 'SingularControl04' ;
setup.functions.continuous             = 'SingularControl04Continuous' ;
setup.functions.endpoint               = 'SingularControl04Endpoint' ;
%setup.nlp.solver                       = 'snopt';
setup.nlp.solver                       = 'ipopt';
setup.bounds                           = bounds;
setup.guess                            = guess;

setup.derivatives.supplier             = 'sparseCD';
setup.derivatives.derivativelevel      = 'second';
setup.derivatives.dependencies         = 'sparseNaN';
setup.scales                           = 'none';

setup.mesh.method                      = 'hp1';
setup.mesh.tolerance                   = 1e-6;
setup.mesh.maxiteration                = 45;
setup.mesh.phase(iphase).colpoints     = 2*ones(1,NPT); % 4 punti collocazione per intervallo 
setup.mesh.phase(iphase).fraction      = ones(1,NPT)/NPT ;

setup.scales.method                    = 'none' ; %'automatic-bounds';
setup.method                           = 'RPMintegration';

output   = gpops2(setup);
solution = output.result.solution;

subplot(2,1,1);
plot( solution.phase.time,  ...
      solution.phase.state(:,1), ...
      '-or');
hold on
plot( solution.phase.time,  ...
      solution.phase.state(:,2), ...
      '-og');
plot( solution.phase.time,  ...
      solution.phase.state(:,3), ...
      '-ob');
  plot( solution.phase.time,  ...
      solution.phase.state(:,4), ...
      '-ob');
    
   
subplot(2,1,2);
plot( solution.phase.time,  ...
      solution.phase.control(:,1), ...
      '-ok');
hold on
plot( solution.phase.time,  ...
      solution.phase.costate(:,1), ...
      '--or');
  plot( solution.phase.time,  ...
      solution.phase.costate(:,2), ...
      '--og');
  plot( solution.phase.time,  ...
      solution.phase.costate(:,3), ...
      '--ob');
  plot( solution.phase.time,  ...
      solution.phase.costate(:,4), ...
      '--ob');
hold off
A = [solution.phase.time,solution.phase.control, ...
solution.phase.state(:,1),   solution.phase.state(:,2)  ,solution.phase.state(:,3),  solution.phase.state(:,4),...
solution.phase.costate(:,1), solution.phase.costate(:,2),solution.phase.costate(:,3),solution.phase.costate(:,4)];

fileID = fopen('gpops_sing04c.txt','w');
fprintf(fileID,'%6s %12s\n','time','u states costates');
fprintf(fileID,'%6.5f %12.18f %12.18f %12.18f %12.18f %12.18f %12.18f %12.18f %12.18f %12.18f\n',A');
fclose(fileID);
