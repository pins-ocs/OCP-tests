%% clear command window, plots and workspace
clc
close all
clear variables

addpath('./');

% import result file
sol = importdata('../data/SingleTrackOL_fwd.txt','\t',8);

% extract data from solution
s        = getData(sol,'s');
n        = getData(sol,'n');
u        = getData(sol,'u');
delta    = getData(sol,'delta');
delta_o  = getData(sol,'delta__o');
ref_curv = getData(sol,'ref_curv');
trj_curv = getData(sol,'trj_curv');
omega    = getData(sol,'Omega');
u        = getData(sol,'u');


%% plot results

% figure()
% plot(getData(sol,'x'),getData(sol,'y'))
% axis equal


figure()
subplot(5,1,1)
plot(s,u*3.6)
ylim([0 100])
ylabel('speed (km/h)')

subplot(5,1,2)
plot(s,n)
ylim([-3 3])
ylabel('n (m)')

subplot(5,1,3)
plot(s,delta*180/pi)
hold on
plot(s,delta_o*180/pi)
legend('\delta','\delta_{o}')
ylim([-60 60])
ylabel('steer (deg)')

subplot(5,1,4)
plot(s,omega*180/pi)
ylim([-60 60])
ylabel('yaw rate (deg/s)')

subplot(5,1,5)
plot(s,ref_curv)
hold on
plot(s,trj_curv)
legend('\kappa_{ref}','\kappa')
%ylim([-10 10])
ylabel('curv (1/m)')


figure()

subplot(4,1,1)
plot(s,  getData(sol,'alpha__r')*180/pi)
hold on
plot(s,  getData(sol,'alpha__f')*180/pi)
legend('r','f')
%ylim([-10 10])
ylabel('(deg)')
title('side slip angles')

subplot(4,1,2)
plot(s,  getData(sol,'fxr'))
hold on
plot(s,  getData(sol,'fxf'))
legend('r','f')
%ylim([-10 10])
ylabel('(N)')
title('longitudinal forces')

subplot(4,1,3)
plot(s,  getData(sol,'fyr'))
hold on
plot(s,  getData(sol,'fyf'))
legend('r','f')
%ylim([-10 10])
ylabel('(N)')
title('lateral forces')

subplot(4,1,4)
plot(s,  getData(sol,'fzr'))
hold on
plot(s,  getData(sol,'fzf'))
legend('r','f')
%ylim([-10 10])
ylabel('(N)')
title('vertical forces')







