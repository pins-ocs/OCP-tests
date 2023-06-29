%-------------------------------------------------------------------------------
%% Fit ggv vs ax and ay using cubic splines
%-------------------------------------------------------------------------------

% Load the data
ax_data = load('ax_points_polyt_full_list.mat').ax_points_polyt_full_list;
ay_data = load('ay_points_polyt_full_list.mat').ay_points_polyt_full_list;
vx_data = load('speed_list.mat').speed_vector;

% Unpack and tailor the data
ax = [fliplr(ax_data), ax_data];
ay = [-fliplr(ay_data), ay_data];
vx = repmat(vx_data, 1, size(ay, 2));

% Reorder the data using atan2
% [th, idxs] = sort(atan2(ax, ay), 2);
% for i = 1:size(ay, 1)
%     ay(i, :) = ay(i, idxs(i, :));
%     ax(i, :) = ax(i, idxs(i, :));
%     vx(i, :) = vx(i, idxs(i, :));
% end

% Resample linearly the data
xdata_or       = linspace(min(ay, [], 'all'), max(ay, [], 'all'), 8);
ydata_or       = linspace(min(vx, [], 'all'), max(vx, [], 'all'), 31);
[xdata, ydata] = meshgrid(xdata_or, ydata_or);
fit_ax         = scatteredInterpolant(ay(:), vx(:), ax(:), 'linear');
ax_fit         = fit_ax(xdata, ydata);

% Interpolate using a bicubic spline
spline_ax = Spline2D('bicubic', ydata_or, xdata_or, ax_fit);

% Close in the y directions
% spline_ay.make_y_closed();
% spline_ax.make_y_closed();

% Evaluate the fit
x_eval           = linspace(min(xdata_or), max(xdata_or), 100);
y_eval           = linspace(min(ydata_or), max(ydata_or), 100);
[x_eval, y_eval] = meshgrid(x_eval, y_eval);

[ax_eval, ax_Dx_eval, ax_Dy_eval] = spline_ax.eval(y_eval, x_eval);

% Plot the original data, the fitted data, and its derivatives
figure();

% Plot the original data and the fitted data
hold on;
surf(xdata, ax_fit, ydata);
surf(x_eval, ax_eval, y_eval);

% Plot the derivatives
figure();
subplot(1,2,1);
surf(x_eval, ax_Dx_eval, y_eval);

subplot(1,2,2);
surf(x_eval, ax_Dy_eval, y_eval);

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('polytope_spline_ay.txt','w');
fprintf(fileID, 'ay\n');
for i = 1:length(xdata_or)
    fprintf(fileID, '%.12e\n', xdata_or(i));
end
fclose(fileID);

fileID = fopen('polytope_spline_vx.txt','w');
fprintf(fileID, 'vx\n');
for i = 1:length(ydata_or)
    fprintf(fileID, '%.12e\n', ydata_or(i));
end
fclose(fileID);

fileID = fopen('polytope_spline_ax.txt','w');
for i = 1:size(ax_fit, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(ax_fit, 1)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(ax_fit, 'polytope_spline_ax.txt', 'Delimiter', 'tab', 'WriteMode', 'append');
