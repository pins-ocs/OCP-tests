
clear all
clc

NPT                           = 1000;
% Phase 1 Information
iphase = 1;
bounds.phase(iphase).initialtime.lower  = 0;
bounds.phase(iphase).initialtime.upper  = 0;
bounds.phase(iphase).finaltime.lower    = 1;
bounds.phase(iphase).finaltime.upper    = 1;
bounds.phase(iphase).initialstate.lower = [0 1 0 0 0 0 0 ];
bounds.phase(iphase).initialstate.upper = [0 1 0 0 0 0 12];
bounds.phase(iphase).state.lower        = [-inf -inf -inf -inf -inf -inf -inf];
bounds.phase(iphase).state.upper        = [inf inf inf inf inf inf inf];
bounds.phase(iphase).finalstate.lower   = [2 1 0 0 0 0 0];
bounds.phase(iphase).finalstate.upper   = [2 1 0 0 0 0 12];
bounds.phase(iphase).control.lower      = [-1 -1 -1];
bounds.phase(iphase).control.upper      = [1 1 1];
bounds.phase(iphase).integral.lower = [];
bounds.phase(iphase).integral.upper = [];
%bounds.phase(iphase).path.lower         = auxdata.lmin;
%bounds.phase(iphase).path.upper         = auxdata.lmax;
%bounds.eventgroup(1).lower              = zeros(1,3);
%bounds.eventgroup(1).upper              = zeros(1,3);
%bounds.parameter.lower                  = betamin;
%bounds.parameter.upper                  = betamax;


% CL0                         = CLmax;
guess.phase(iphase).time       = [0; 1] ;
guess.phase(iphase).state(:,1) = [0; 2] ;
guess.phase(iphase).state(:,2) = [1; 1] ;
guess.phase(iphase).state(:,3) = [0; 0] ;
guess.phase(iphase).state(:,4) = [2/10; 2/10] ;
guess.phase(iphase).state(:,5) = [0.1; -0.1] ;
guess.phase(iphase).state(:,6) = [0; 0] ;
guess.phase(iphase).state(:,7) = [10; 10] ;
guess.phase(iphase).control    = [0 0 0;0 0 0] ;
guess.phase.integral           = [] ;

setup.name                             = 'Underwater' ;
setup.functions.continuous             = 'UnderwaterContinuous' ;
setup.functions.endpoint               = 'UnderwaterEndpoint' ;
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
    
   
subplot(2,1,2);
plot( solution.phase.time,  ...
      solution.phase.control(:,1), ...
      '-ok');
hold on
plot( solution.phase.time,  ...
      solution.phase.control(:,2), ...
      '--or');
  plot( solution.phase.time,  ...
      solution.phase.control(:,3), ...
      '--og');
  plot( solution.phase.time,  ...
      solution.phase.costate(:,3), ...
      '--ob');
hold off

