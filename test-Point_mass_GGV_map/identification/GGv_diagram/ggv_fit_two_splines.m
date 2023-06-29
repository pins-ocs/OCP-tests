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
xdata_or       = linspace(-pi, pi, 100);
ydata_or       = linspace(min(vx, [], 'all'), max(vx, [], 'all'), 31);
[xdata, ydata] = meshgrid(xdata_or, ydata_or);
fit_ay         = scatteredInterpolant(th(:), vx(:), ay(:), 'linear');
fit_ax         = scatteredInterpolant(th(:), vx(:), ax(:), 'linear');
ay_fit         = fit_ay(xdata, ydata);
ax_fit         = fit_ax(xdata, ydata);

% Divide the data between [-pi, 0[ and [0, pi]
up_idxs   = find(xdata_or > 0);
down_idxs = find(xdata_or < 0);
ay_up     = ay_fit(:, up_idxs(1:end-1));
ax_up     = ax_fit(:, up_idxs(1:end-1));
vx_up     = ydata(:, up_idxs(1:end-1));
ay_down   = ay_fit(:, down_idxs(2:end));
ax_down   = ax_fit(:, down_idxs(2:end));
vx_down   = ydata(:, down_idxs(2:end));

% Fit a linear surface to obtain the surface with ax as the z-axis
up_surf   = fit([ay_up(:), vx_up(:)], ax_up(:), 'linearinterp', ExtrapolationMethod='nearest');
down_surf = fit([ay_down(:), vx_down(:)], ax_down(:), 'linearinterp', ExtrapolationMethod='nearest'); % 'linearinterp', ExtrapolationMethod='nearest'

% Downsample to get back to the original point amount
xspline        = linspace(min(ay, [], 'all'), max(ay, [], 'all'), 300);
yspline        = linspace(min(vx, [], 'all'), max(vx, [], 'all'), 31);
[xspline_grid, yspline_grid] = meshgrid(xspline, yspline);
zspline_up     = up_surf(xspline_grid, yspline_grid);
zspline_down   = down_surf(xspline_grid, yspline_grid);

% Create the splines
spline_up   = Spline2D('bicubic', yspline, xspline, zspline_up);
spline_down = Spline2D('bicubic', yspline, xspline, zspline_down);

% Plot

figure();
grid on;
surf(ay_fit, ax_fit, ydata);

figure();
grid on;
hold on;
surf(ay_up, ax_up, vx_up);
surf(ay_up, up_surf(ay_up, vx_up), vx_up);

figure();
grid on;
hold on;
surf(ay_up, up_surf(ay_up, vx_up), vx_up);
surf(ay_up, spline_up.eval(vx_up, ay_up), vx_up);

figure();
grid on;
hold on;
surf(ay_down, ax_down, vx_down);
surf(ay_down, down_surf(ay_down, vx_down), vx_down);

figure();
grid on;
hold on;
surf(ay_down, down_surf(ay_down, vx_down), vx_down);
surf(ay_down, spline_down.eval(vx_down, ay_down), vx_down);

figure();
grid on;
hold on;
surf(ay_up, up_surf(ay_up, vx_up), vx_up);
surf(ay_down, down_surf(ay_down, vx_down), vx_down);
surf(ay_up, spline_up.eval(vx_up, ay_up), vx_up);
surf(ay_down, spline_down.eval(vx_down, ay_down), vx_down);

figure();
grid on;
hold on;
surf(ay_up, spline_up.eval(vx_up, ay_up), vx_up);
surf(ay_down, spline_down.eval(vx_down, ay_down), vx_down);

%-------------------------------------------------------------------------------
%% Save the data
%-------------------------------------------------------------------------------

% Save the data as a txt file delimited by tabs
fileID = fopen('ggv_spline_updown_ay.txt','w');
fprintf(fileID, 'ay\n');
for i = 1:length(xspline)
    fprintf(fileID, '%.12e\n', xspline(i));
end
fclose(fileID);

fileID = fopen('ggv_spline_updown_vx.txt','w');
fprintf(fileID, 'vx\n');
for i = 1:length(yspline)
    fprintf(fileID, '%.12e\n', yspline(i));
end
fclose(fileID);

fileID = fopen('ggv_spline_up_ax.txt','w');
for i = 1:size(zspline_up, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(zspline_up, 2)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(zspline_up, 'ggv_spline_up_ax.txt', 'Delimiter', 'tab', 'WriteMode', 'append');

fileID = fopen('ggv_spline_down_ax.txt','w');
for i = 1:size(zspline_down, 2)
    fprintf(fileID, 'col_%d', i);
    if i < size(zspline_down, 2)
        fprintf(fileID, '\t');
    else
        fprintf(fileID, '\n');
    end
end
fclose(fileID);
writematrix(zspline_down, 'ggv_spline_down_ax.txt', 'Delimiter', 'tab', 'WriteMode', 'append');
