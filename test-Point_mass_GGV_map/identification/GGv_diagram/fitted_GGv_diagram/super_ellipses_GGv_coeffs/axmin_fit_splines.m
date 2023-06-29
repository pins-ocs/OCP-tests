%-------------------------------------------------------------------------------
%% Fit axmin vs u using cubic splines
%-------------------------------------------------------------------------------

% Load the data
u_data     = load('speed_vect_interp.mat').speed_vect_interp';
axmin_data = load('ax_min_interp.mat').ax_min_interp';

% Filter the data by fitting with a smoothing spline
f = fit(u_data, axmin_data, 'smoothingspline', 'SmoothingParam', 2e-2);

% Resample the target data
axmin_smooth= f(u_data);

% Repeat the first and last data points n-times to avoid extrapolation
u_step_lb  = u_data(2) - u_data(1);
u_step_ub  = u_data(end) - u_data(end-1);
n          = 10;
u_data     = [u_data(1) - u_step_lb * (n:-1:1)'; u_data; u_data(end) + u_step_ub * (1:n)'];
axmin_data   = [axmin_data(1) * ones(n,1); axmin_data; axmin_data(end) * ones(n,1)];
axmin_smooth = [axmin_smooth(1) * ones(n,1); axmin_smooth; axmin_smooth(end) * ones(n,1)];

% Fit the data
spline = Spline1D('cubic', u_data, axmin_smooth);

% Evaluate the fit
u_eval = linspace(min(u_data) - 30, max(u_data) + 30, 10000);
[axmin_eval, axmin_D_eval, axmin_DD_eval] = spline.eval(u_eval);

% Plot the original data, the fitted data, and its derivatives
figure();

% Plot the original data and the fitted data
subplot(3,1,1);
plot(u_data, axmin_data, 'o', 'MarkerSize', 3);
hold on;
plot(u_data, axmin_smooth, 'o', 'MarkerSize', 3);
plot(u_eval, axmin_eval, 'LineWidth', 1);
hold off;
xlabel('u');
ylabel('axmin');
legend('original data', 'smooth data', 'fit');
title('axmin vs u - cubic spline');

% Plot the first derivative
subplot(3,1,2);
plot(u_eval, axmin_D_eval, 'LineWidth', 1);
xlabel('u');
ylabel('axmin D');
title('axmin D vs u - cubic spline');

% Plot the second derivative
subplot(3,1,3);
plot(u_eval, axmin_DD_eval, 'LineWidth', 1);
xlabel('u');
ylabel('axmin DD');
title('axmin DD vs u - cubic spline');

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('axmin_vs_u_spline.txt','w');
fprintf(fileID, 'u\taxmin\n');
for i = 1:length(u_data)
    fprintf(fileID, '%.12e\t%.12e\n', u_data(i), axmin_smooth(i));
end
fclose(fileID);
