%-------------------------------------------------------------------------------
%% Model a spline to mimic a ReLU
%-------------------------------------------------------------------------------

% Define the points to interpolate
x = [0, 1];
y = [0, 1];

% Add n collinear points at the extremes to get good-behaving derivatives
n = 0;
x = [x(1) - n:1:x(1) - 1, x, x(end) + 1:1:x(end) + n];
y = [zeros(1, n), y, ones(1, n)];

% Define the spline
spline = Spline1D('akima', x, y);

% Sample the spline
xdata = linspace(min(x), max(x), 1000);
ydata = spline.eval(xdata);

% Plot the spline
figure;
plot(xdata, ydata, 'LineWidth', 2);
xlabel('x');
ylabel('y');
title('Spline ReLU');
grid on;


%%
xdata = linspace(-1, 1, 1000);
test  = 1 ./ (1 + exp(20 .* (xdata + 0.5)));
dtest = test .* (1 - test);
ddtest = dtest - 2 .* test .* dtest;

figure;
hold on
grid on
plot(xdata, test)
plot(xdata, dtest)
plot(xdata, ddtest)