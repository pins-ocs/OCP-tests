%% Description
%
% This file implement the MPC controler. The vehicle dynamic is modelled
% with a mex file that embed a Single track model. The MPC is a mex file
% that track a reference speed and trajectory.
% the first value of the optimal control input are used as control for the
% vehicle model. The control input are considered as constant for the
% interval of integration dt = 0.01s. after that period controls are
% recomputed by solving another mpc problem.
%
%% initialization
% 
% first of all compile the DS Mex and the OCP Mex and check they are
% working
%
close all
clc
clear variables

addpath('../ds-interfaces/Matlab/');
addpath('../ocp-interfaces/Matlab/');


dt = 0.1; %sampling time for MPC

% -------------------------------------------------------------------------
% INITIALISE OCP
% -------------------------------------------------------------------------

% List of OCP problem's variables
ocp_xvars = { 'n','xi','u','v','Omega','alpha__r','alpha__f','delta','S' } ;

% List of OCP problem's lagrange multipliers
ocp_lvars = { 'lambda1__xo','lambda2__xo','lambda3__xo','lambda4__xo',...
             'lambda5__xo','lambda6__xo','lambda7__xo','lambda8__xo','lambda9__xo' } ;

% List of OCP problem's controls
ocp_uvars = { 'v__delta','vS' } ;

% List of OCP problem's post process variables
ocp_postvars = { 'lagrange_target','penalties','v__deltaControl','vSControl',...
             'roadRightLateralBoundaries','roadLeftLateralBoundaries',....
             'rearEllipse','frontEllipse','MaxPowerLimit','SteeringLimit',...
             'ay','beta','VG','fzr','fzf','fxr','fyr','fxf','fyf','mu_xr',...
             'mu_yr','mu_xf','mu_yf','vehicle_power','trj_curv',...
             'ref_curv','ref_speed','ref_yaw_rate','ref_delta','ref_thrust' } ;
             
ocp_zvars = {ocp_xvars{:},ocp_lvars{:},ocp_uvars{:}};

% List of OCP problem's mesh variables
qvars = { 'zeta' } ;

% load default data
SingleTrackMPC_Data ;

%change warning level
SingleTrackMPC_data.InfoLevel = int32(1) ;

% setup ocp object
fprintf(1,'> OCP setup\n');
SingleTrackMPC_Mex('setup', SingleTrackMPC_data) ;

% solve first time
fprintf(1,'> OCP compute solution\n');
SingleTrackMPC_Mex('solve') ;
% get solution
mpc_sol = SingleTrackMPC_Mex('get_solution') ;
if mpc_sol.converged
  fprintf(1,'> Solution found\n');
else
  fprintf(1,'> Not converged\n');
end

% get controls
tmp = getData(mpc_sol,'zeta');  s0     = tmp(1);
tmp = getData(mpc_sol,'u');     u0     = tmp(1);
tmp = getData(mpc_sol,'delta'); delta0 = tmp(1);
tmp = getData(mpc_sol,'S');     S0     = tmp(1);

% -------------------------------------------------------------------------
% INITIALISE DYNAMICAL SYSTEM
% -------------------------------------------------------------------------

% List of DS problem's variables
ds_xvars = { 's','n','xi','u','v','Omega','alpha__r','alpha__f','fzr','fzf','delta','S' } ;
ics_vars = {'zeta','n','xi','u','v','Omega','alpha__r','alpha__f','fzr','fzf','delta','S'};

% List of DS problem's controls
ds_uvars = { 'delta__o','S__o' } ;

% List of DS problem's post process variables
ds_postvars = { 'fyr','fyf','fxr','fxf','VG','trj_curv','ref_curv',...
                'ref_speed','ref_yaw_rate','ref_delta','ref_thrust','ref_x','ref_y' } ;


% load default data
SingleTrackOL_Data ; %matlab file

%change warning level
SingleTrackOL_data.InfoLevel = int32(0) ;

%set initial condition and controls.
% Overriding default integration setting
SingleTrackOL_data.Parameters.V0       = u0 ;
SingleTrackOL_data.Parameters.u__S     = S0 ;
SingleTrackOL_data.Parameters.u__delta = delta0 ;

% setup ocp object
fprintf(1,'> DS setup\n');
SingleTrackOL_Mex('setup', SingleTrackOL_data) ;

% solve first time
fprintf(1,'\n> DS Integrating equations of motion\n');

t0 = 0;
t1 = t0+dt;
tsample  = t0:dt/10.0:t1;           % define integration range
ns = length(tsample);

ics = get_vec_data(mpc_sol,ics_vars,1)';

% Closed-loop  parameters to be used in case they need to be updated
SingleTrackOL_data.Parameters.u__S     = S0 ;
SingleTrackOL_data.Parameters.u__delta = u0 ;
ode_sol = SingleTrackOL_Mex('do_integration_step',tsample, ics, SingleTrackOL_data) ;

% plotting ---------------------------------------------------------------
tmp_s = getData(ode_sol,'s');
tmp_ocp = SingleTrackMPC_Mex('get_solution',tmp_s',{'u','delta','S'});

id_fig1 = figure();
fn = 4;
subplot(fn,1,1)
plot(tsample,getData(ode_sol,'u'))
ylabel('u')
hold on

subplot(fn,1,2)
plot(tmp_s,getData(ode_sol,'u'))
hold on
plot(tmp_s,tmp_ocp.u)
ylabel('u')

subplot(fn,1,3)
plot(tmp_s,getData(ode_sol,'delta'))
hold on
plot(tmp_s,tmp_ocp.delta)
ylabel('delta')

subplot(fn,1,4)
plot(tmp_s,getData(ode_sol,'S'))
hold on
plot(tmp_s,tmp_ocp.S)
ylabel('S')


% -------------------------------------------------------------------------
% MPC LOOP
% -------------------------------------------------------------------------

tmp = getData(ode_sol,'s');
s0  = tmp(end);
%get_vec_data(ode_sol, ds_xvars,ns);

% change horizon
SingleTrackMPC_data.Mesh.s0 = s0; %int32(0);
SingleTrackMPC_data.Mesh.segments{1}.n = int32(500);
SingleTrackMPC_data.Mesh.segments{1}.length = L_horizon;

% change initial conditions
SingleTrackMPC_data.Parameters.Omega0    =  get_vec_data(ode_sol,{'Omega'},ns);
SingleTrackMPC_data.Parameters.S0        =  get_vec_data(ode_sol,{'S'},ns);
SingleTrackMPC_data.Parameters.delta0    =  get_vec_data(ode_sol,{'delta'},ns); 
SingleTrackMPC_data.Parameters.n0        =  get_vec_data(ode_sol,{'n'},ns); 
SingleTrackMPC_data.Parameters.u0        =  get_vec_data(ode_sol,{'u'},ns); 
SingleTrackMPC_data.Parameters.v0        =  get_vec_data(ode_sol,{'v'},ns); 
SingleTrackMPC_data.Parameters.xi0       =  get_vec_data(ode_sol,{'xi'},ns); 
SingleTrackMPC_data.Parameters.alpha__f0 =  get_vec_data(ode_sol,{'alpha__f'},ns); 
SingleTrackMPC_data.Parameters.alpha__r0 =  get_vec_data(ode_sol,{'alpha__r'},ns); 


% use previous solution as guess
SingleTrackMPC_data.ResetGuess = false ; % set guess to zero 
xx = getData(mpc_sol,'zeta'); 
SingleTrackMPC_data.Guess.idx  = mpc_sol.idx;
SingleTrackMPC_data.Guess.data = mpc_sol.data; 

% setup ocp object
fprintf(1,'> OCP setup\n');
SingleTrackMPC_Mex('setup', SingleTrackMPC_data) ;

% solve first time
fprintf(1,'> OCP compute solution\n');
SingleTrackMPC_Mex('solve') ;
% get solution
mpc_sol = SingleTrackMPC_Mex('get_solution') ;
%sol = SingleTrackMPC__Mex('get_solution',0.0,{'u','v'})
if mpc_sol.converged
  fprintf(1,'> Solution found\n');
else
  fprintf(1,'> Not converged\n');
end

% get controls
tmp = getData(mpc_sol,'zeta');  s0     = tmp(1);
tmp = getData(mpc_sol,'u');     u0     = tmp(1);
tmp = getData(mpc_sol,'delta'); delta0 = tmp(1);
tmp = getData(mpc_sol,'S');     S0     = tmp(1);

%set initial condition and controls.
% Overriding default integration setting
SingleTrackOL_data.Parameters.V0       = u0 ;
SingleTrackOL_data.Parameters.u__S     = S0 ;
SingleTrackOL_data.Parameters.u__delta = delta0 ;


% setup ocp object
fprintf(1,'> DS setup\n');
SingleTrackOL_Mex('setup', SingleTrackOL_data) ;

% solve first time
fprintf(1,'\n> DS Integrating equations of motion\n');

t0 = t1;
t1 = t0+dt;
tsample  = t0:dt/10.0:t1;           % define integration range
ns = length(tsample);

ics = get_vec_data(mpc_sol,ics_vars,1)';
fprintf(1,'ics: \n');
for i=1:length(ics_vars)
fprintf(1,'%10s = %12.6f\n',ics_vars{i},ics(i));
end 


% Closed-loop  parameters to be used in case they need to be updated
SingleTrackOL_data.Parameters.u__S     = S0 ;
SingleTrackOL_data.Parameters.u__delta = u0 ;
ode_sol = SingleTrackOL_Mex('do_integration_step',tsample, ics, SingleTrackOL_data) ;

% plotting ---------------------------------------------------------------
tmp_s = getData(ode_sol,'s');
tmp_ocp = SingleTrackMPC_Mex('get_solution',tmp_s',{'u','delta','S'});

figure(id_fig1);
clf
subplot(fn,1,1)
plot(tsample,getData(ode_sol,'u'))
ylabel('u')
hold on

subplot(fn,1,2)
plot(tmp_s,getData(ode_sol,'u'))
hold on
plot(tmp_s,tmp_ocp.u)
ylabel('u')

subplot(fn,1,3)
plot(tmp_s,getData(ode_sol,'delta'))
hold on
plot(tmp_s,tmp_ocp.delta)
ylabel('delta')

subplot(fn,1,4)
plot(tmp_s,getData(ode_sol,'S'))
hold on
plot(tmp_s,tmp_ocp.S)
ylabel('S')



              