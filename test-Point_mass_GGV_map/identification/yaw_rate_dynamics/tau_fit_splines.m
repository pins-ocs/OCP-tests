%-------------------------------------------------------------------------------
%% Fit tau_omega vs u using cubic splines
%-------------------------------------------------------------------------------

% Load the data
u_data   = load('u_fit.mat').speed_vect_interp';
tau_data = load('tau_fit.mat').tau_Omega_opt_interp';

% Filter the data by fitting with a smoothing spline
f = fit(u_data, tau_data, 'smoothingspline', 'SmoothingParam', 0.8);

% Resample the target data
tau_smooth= f(u_data);

% Repeat the first and last data points n-times to avoid extrapolation
% u_step_lb  = u_data(2) - u_data(1);
% u_step_ub  = u_data(end) - u_data(end-1);
% n          = 10;
% u_data     = [u_data(1) - u_step_lb * (n:-1:1)'; u_data; u_data(end) + u_step_ub * (1:n)'];
% tau_data   = [tau_data(1) * ones(n,1); tau_data; tau_data(end) * ones(n,1)];
% tau_smooth = [tau_smooth(1) * ones(n,1); tau_smooth; tau_smooth(end) * ones(n,1)];

% Fit the data
spline = Spline1D('cubic', u_data, tau_smooth);

% Evaluate the fit
u_eval = linspace(min(u_data) - 30, max(u_data) + 30, 10000);
[tau_eval, tau_D_eval, tau_DD_eval] = spline.eval(u_eval);

% Plot the original data, the fitted data, and its derivatives
figure();

% Plot the original data and the fitted data
subplot(3,1,1);
plot(u_data, tau_data, 'o', 'MarkerSize', 3);
hold on;
plot(u_data, tau_smooth, 'o', 'MarkerSize', 3);
plot(u_eval, tau_eval, 'LineWidth', 1);
hold off;
xlabel('u');
ylabel('tau');
legend('original data', 'smooth data', 'fit');
title('tau vs u - cubic spline');

% Plot the first derivative
subplot(3,1,2);
plot(u_eval, tau_D_eval, 'LineWidth', 1);
xlabel('u');
ylabel('tau D');
title('tau D vs u - cubic spline');

% Plot the second derivative
subplot(3,1,3);
plot(u_eval, tau_DD_eval, 'LineWidth', 1);
xlabel('u');
ylabel('tau DD');
title('tau DD vs u - cubic spline');

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('tau_omega_vs_u_spline.txt','w');
fprintf(fileID, 'u\ttau\n');
for i = 1:length(u_data)
    fprintf(fileID, '%.12e\t%.12e\n', u_data(i), tau_smooth(i));
end
fclose(fileID);
