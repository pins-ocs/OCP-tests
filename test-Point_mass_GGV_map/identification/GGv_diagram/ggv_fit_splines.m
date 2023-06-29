%-------------------------------------------------------------------------------
%% Fit ggv vs ax and ay using cubic splines
%-------------------------------------------------------------------------------

% Load the data
ggv_data = load('GGv_diagram_data/GGv_simData.mat').GGv_data_save;

% Unpack the data
ay = ggv_data.Ay_GGv_sameSpeed;
ax = ggv_data.Ax_GGv_sameSpeed;
vx = repmat(ggv_data.speed_vector, 1, size(ay, 2));

% Reorder the data using atan2
[th, idxs] = sort(atan2(ax, ay), 2);
for i = 1:size(ay, 1)
    ay(i, :) = ay(i, idxs(i, :));
    ax(i, :) = ax(i, idxs(i, :));
    vx(i, :) = vx(i, idxs(i, :));
end

% Resample linearly the data
xdata_or       = linspace(min(th, [], 'all'), max(th, [], 'all'), 30);
ydata_or       = linspace(min(vx, [], 'all'), max(vx, [], 'all'), 31);
[xdata, ydata] = meshgrid(xdata_or, ydata_or);
fit_ay         = scatteredInterpolant(th(:), vx(:), ay(:), 'linear');
fit_ax         = scatteredInterpolant(th(:), vx(:), ax(:), 'linear');
ay_fit         = fit_ay(xdata, ydata);
ax_fit         = fit_ax(xdata, ydata);

% Interpolate using a bicubic spline
spline_ay = Spline2D('bicubic', ydata_or, xdata_or, ay_fit);
spline_ax = Spline2D('bicubic', ydata_or, xdata_or, ax_fit);

% Close in the y directions
spline_ay.make_y_closed();
spline_ax.make_y_closed();

% Evaluate the fit
x_eval           = linspace(min(xdata_or), max(xdata_or), 100);
y_eval           = linspace(min(ydata_or), max(ydata_or), 100);
[x_eval, y_eval] = meshgrid(x_eval, y_eval);

[ay_eval, ay_Dx_eval, ay_Dy_eval] = spline_ay.eval(y_eval, x_eval);
[ax_eval, ax_Dx_eval, ax_Dy_eval] = spline_ax.eval(y_eval, x_eval);

% Plot the original data, the fitted data, and its derivatives
figure();

% Plot the original data and the fitted data
subplot(1,2,1);
hold on;
surf(xdata, ydata, ay_fit);
surf(x_eval, y_eval, ay_eval);

subplot(1,2,2);
hold on;
surf(xdata, ydata, ax_fit);
surf(x_eval, y_eval, ax_eval);

% Plot the GGv
figure();
surf(ay_eval, ax_eval, y_eval);

% Plot the derivatives
figure();
subplot(1,2,1);
surf(x_eval, y_eval, ay_Dx_eval);

subplot(1,2,2);
surf(x_eval, y_eval, ay_Dy_eval);

figure();
subplot(1,2,1);
surf(x_eval, y_eval, ax_Dx_eval);

subplot(1,2,2);
surf(x_eval, y_eval, ax_Dy_eval);

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('ggv_spline_th.txt','w');
fprintf(fileID, 'th\n');
for i = 1:length(xdata_or)
    fprintf(fileID, '%.12e\n', xdata_or(i));
end
fclose(fileID);

fileID = fopen('ggv_spline_vx.txt','w');
fprintf(fileID, 'vx\n');
for i = 1:length(ydata_or)
    fprintf(fileID, '%.12e\n', ydata_or(i));
end
fclose(fileID);

fileID = fopen('ggv_spline_ay.txt','w');
for i = 1:size(ay_fit, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(ay_fit, 2)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(ay_fit, 'ggv_spline_ay.txt', 'Delimiter', 'tab', 'WriteMode', 'append');

fileID = fopen('ggv_spline_ax.txt','w');
for i = 1:size(ax_fit, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(ax_fit, 2)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(ax_fit, 'ggv_spline_ax.txt', 'Delimiter', 'tab', 'WriteMode', 'append');
