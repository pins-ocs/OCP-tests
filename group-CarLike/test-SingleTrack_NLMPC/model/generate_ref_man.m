clc
clear variables
close all

data_in = importdata('SingleTrack_Road_OCP_result.txt','\t');

% for i = 1:length(data_in.colheaders)
%   disp(data_in.colheaders{i})
% end

zeta0 = getData(data_in,'zeta');

%find non repeated values
id_nr = find(diff(zeta0) ~= 0);

% extract relevant reference data
zeta = zeta0(id_nr);
u     = (getData(data_in,'u'));       u     = u(id_nr);
VG    = (getData(data_in,'VG'));      VG    = VG(id_nr);
omega = (getData(data_in,'Omega'));   omega = omega(id_nr);
delta = (getData(data_in,'delta'));   delta = delta(id_nr);
S     = (getData(data_in,'S'));       S     = S(id_nr);

curv  = omega./VG;
x     = (getData(data_in,'xCoMCar')); x = x(id_nr);
y     = (getData(data_in,'yCoMCar')); y = y(id_nr);

% build table
tab_ref = table(zeta,u,VG,omega,delta,S,curv,x,y,...
                'VariableNames',{'zeta','ref_u','ref_VG','ref_yawrate',...
                                 'ref_steer','ref_longforce',...
                                 'ref_curv','ref_x','ref_y'});

% write table to file
writetable(tab_ref,'reference_manoeuvre.txt','Delimiter','\t','WriteVariableNames',true);



