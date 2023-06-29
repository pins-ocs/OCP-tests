%-------------------------------------------------------------------------------
%% Fit aymax vs u using cubic splines
%-------------------------------------------------------------------------------

% Load the data
u_data     = load('speed_vect_interp.mat').speed_vect_interp';
aymax_data = load('ay_max_interp.mat').ay_max_interp';

% Filter the data by fitting with a smoothing spline
f = fit(u_data, aymax_data, 'smoothingspline', 'SmoothingParam', 2e-2);

% Resample the target data
aymax_smooth= f(u_data);

% Repeat the first and last data points n-times to avoid extrapolation
u_step_lb  = u_data(2) - u_data(1);
u_step_ub  = u_data(end) - u_data(end-1);
n          = 10;
u_data     = [u_data(1) - u_step_lb * (n:-1:1)'; u_data; u_data(end) + u_step_ub * (1:n)'];
aymax_data   = [aymax_data(1) * ones(n,1); aymax_data; aymax_data(end) * ones(n,1)];
aymax_smooth = [aymax_smooth(1) * ones(n,1); aymax_smooth; aymax_smooth(end) * ones(n,1)];

% Fit the data
spline = Spline1D('cubic', u_data, aymax_smooth);

% Evaluate the fit
u_eval = linspace(min(u_data) - 30, max(u_data) + 30, 10000);
[aymax_eval, aymax_D_eval, aymax_DD_eval] = spline.eval(u_eval);

% Plot the original data, the fitted data, and its derivatives
figure();

% Plot the original data and the fitted data
subplot(3,1,1);
plot(u_data, aymax_data, 'o', 'MarkerSize', 3);
hold on;
plot(u_data, aymax_smooth, 'o', 'MarkerSize', 3);
plot(u_eval, aymax_eval, 'LineWidth', 1);
hold off;
xlabel('u');
ylabel('aymax');
legend('original data', 'smooth data', 'fit');
title('aymax vs u - cubic spline');

% Plot the first derivative
subplot(3,1,2);
plot(u_eval, aymax_D_eval, 'LineWidth', 1);
xlabel('u');
ylabel('aymax D');
title('aymax D vs u - cubic spline');

% Plot the second derivative
subplot(3,1,3);
plot(u_eval, aymax_DD_eval, 'LineWidth', 1);
xlabel('u');
ylabel('aymax DD');
title('aymax DD vs u - cubic spline');

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('aymax_vs_u_spline.txt','w');
fprintf(fileID, 'u\taymax\n');
for i = 1:length(u_data)
    fprintf(fileID, '%.12e\t%.12e\n', u_data(i), aymax_smooth(i));
end
fclose(fileID);
