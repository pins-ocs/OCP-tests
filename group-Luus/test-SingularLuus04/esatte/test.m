% x1,y1,z1,t1,x2,y2,z2,t2, k C a ,b , x3,y3,z3,t3,c
%  1  2  3  4  5  6  7  8  9 10
% x(1), ... , x(9)
%valori di xoptima
x0 = [ 0.906, -0.33, -0.82, 0.82, -0.05, -0.26, 0.91, 2.56,.53,1,0,0];

x0 = [ 0.8537   -0.3491   -0.8599    0.82   -0.1724   -0.2748    0.6571    2.4894 0.5769    2.31    0.7883         0];
%x0 = ones(1,17);
options = optimoptions('fsolve','Display','iter','MaxIter',50000, ...
'MaxFunEvals',400000 ); % Option to display output
%'algorithm','levenberg-marquardt'
[x,fval] = fsolve(@myfun,x0,options); % Call solver
x
%fval
norm(fval)