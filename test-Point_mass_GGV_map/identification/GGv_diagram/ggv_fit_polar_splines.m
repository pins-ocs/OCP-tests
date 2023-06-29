%%

set(0,'DefaultFigureWindowStyle','docked')

%-------------------------------------------------------------------------------
%% Fit ggv vs ax and ay using cubic splines
%-------------------------------------------------------------------------------

% Load the data
ggv_data = load('GGv_diagram_data/GGv_simData.mat').GGv_data_save;

% Unpack the data
ay = ggv_data.Ay_GGv_sameSpeed;
ax = ggv_data.Ax_GGv_sameSpeed;
vx = repmat(ggv_data.speed_vector, 1, size(ay, 2));

% Test shift ax
ax_shift = 0; %(max(ax(end, :)) - min(ax(end, :))) / 2;
ax = ax + ax_shift;

% Reorder the data using atan2
[th, idxs] = sort(atan2(ax, ay), 2);
for i = 1:size(ay, 1)
    ay(i, :) = ay(i, idxs(i, :));
    ax(i, :) = ax(i, idxs(i, :));
    vx(i, :) = vx(i, idxs(i, :));
end

% Resample linearly the data using only half of the ggv (the one well-behaved)
xdata_or       = linspace(-pi / 2, pi / 2, 15); % linspace(min(th, [], 'all'), max(th, [], 'all'), 30);
ydata_or       = linspace(min(vx, [], 'all'), max(vx, [], 'all'), 31);
ydata_or = ydata_or(1:end-1);
[xdata, ydata] = meshgrid(xdata_or, ydata_or);
fit_ay         = scatteredInterpolant(th(:), vx(:), ay(:), 'natural');
fit_ax         = scatteredInterpolant(th(:), vx(:), ax(:), 'natural');
ay_fit         = fit_ay(xdata, ydata);
ax_fit         = fit_ax(xdata, ydata);

% Make sure the values at -pi/2, 0, and pi/2 are zero for ay and ax
ay_fit(:, [1, end]) = 0;
ax_fit(:, find(xdata_or == 0)) = 0;

% Construct the full GGv
xdata_or       = [xdata_or, xdata_or(2:end-1) + pi];
[xdata, ydata] = meshgrid(xdata_or, ydata_or);
ay_fit         = [ay_fit, -fliplr(ay_fit(:, 2:end-1))];
ax_fit         = [ax_fit(:, 1:end-1), ax_fit(:, end-1), fliplr(ax_fit(:, 2:end-1))]; % avoid those horrific points at ay = 0

% Shift to be in the range [-pi, pi]
shift_num = size(xdata, 2) - find(xdata(1, :) == pi);
xdata     = circshift(xdata, shift_num, 2);
xdata(:, 1:shift_num) = -fliplr(xdata(:, 1:shift_num)) + pi / 2;
ydata     = circshift(ydata, shift_num, 2);
xdata_or  = xdata(1, :);
ydata_or  = ydata(:, 1)';
ay_fit    = circshift(ay_fit, shift_num, 2);
ax_fit    = circshift(ax_fit, shift_num, 2);

% Close the GGv
xdata_or = [-xdata_or(end), xdata_or];
xdata    = [-xdata(:, end), xdata];
ydata    = [ydata(:, end), ydata];
ay_fit   = [ay_fit(:, end), ay_fit];
ax_fit   = [ax_fit(:, end), ax_fit];

% Compute the radius
radius = sqrt(ay_fit.^2 + (ax_fit).^2); %  + abs(min(ax_fit, [], 'all'))

% tmp = fit([xdata(:), ydata(:)], radius(:), 'poly33');

% Interpolate using a bicubic spline
spline = Spline2D('biquintic', ydata_or, xdata_or, radius); % tmp(xdata, ydata)

% Close in the y directions
% spline.make_x_closed();
spline.make_y_closed();

% Evaluate the fit
x_eval           = linspace(min(xdata_or), max(xdata_or), 100);
y_eval           = linspace(min(ydata_or), max(ydata_or), 100);
[x_eval, y_eval] = meshgrid(x_eval, y_eval);

[rad_eval, rad_Dx_eval, rad_Dy_eval, rad_DDx_eval, rad_DxDy_eval, rad_DDy_eval] = spline.eval(y_eval, x_eval);

% Plot the original data and the fitted data
figure();
grid on;
surf(ay_fit, ax_fit, ydata);

figure();
grid on;
hold on;
surf(x_eval, y_eval, rad_eval);
% surf(xdata_or, ydata_or, radius);

% Plot the derivatives
figure();
grid on;
subplot(1,2,1);
surf(x_eval, y_eval, rad_Dx_eval);

subplot(1,2,2);
surf(x_eval, y_eval, rad_Dy_eval);

figure();
grid on;
subplot(1,2,1);
surf(x_eval, y_eval, rad_DDx_eval);

subplot(1,2,2);
surf(x_eval, y_eval, rad_DDy_eval);

figure();
grid on;
surf(x_eval, y_eval, rad_DxDy_eval);

figure();
grid on;
surf(rad_eval .* cos(x_eval), rad_eval .* sin(x_eval), y_eval);

% figure();
% grid on;
% hold on;
% plot(y_eval(:, 1), rad_eval(:, 1));
% plot(y_eval(:, 1), rad_eval(:, end));
% plot(y_eval(:, 1), rad_Dy_eval(:, 1));
% plot(y_eval(:, 1), rad_Dy_eval(:, end));
% plot(y_eval(:, 1), rad_Dx_eval(:, 1));
% plot(y_eval(:, 1), rad_Dx_eval(:, end));

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Flatten the data
ay_flat = ay(:);
ax_flat = ax(:);

% Save the data as a txt file delimited by tabs
fileID = fopen('ggv_polar_spline_th.txt','w');
fprintf(fileID, 'th\n');
for i = 1:length(xdata_or)
    fprintf(fileID, '%.12e\n', xdata_or(i));
end
fclose(fileID);

fileID = fopen('ggv_polar_spline_vx.txt','w');
fprintf(fileID, 'vx\n');
for i = 1:length(ydata_or)
    fprintf(fileID, '%.12e\n', ydata_or(i));
end
fclose(fileID);

fileID = fopen('ggv_polar_spline_radius.txt','w');
for i = 1:size(radius, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(radius, 2)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(radius, 'ggv_polar_spline_radius.txt', 'Delimiter', 'tab', 'WriteMode', 'append');
