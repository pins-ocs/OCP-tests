function [problem,guess] = HangGlider
  % Initial time. t0<tf
  problem.time.t0=0;

  % Final time. Let tf_min=tf_max if tf is fixed.
  problem.time.tf_min = 1 ;     
  problem.time.tf_max = 1 ; 
  guess.tf            = 1 ;

  % Parameters bounds. pl=< p <=pu
  problem.parameters.pl=[];
  problem.parameters.pu=[];
  guess.parameters=[];

  % Initial conditions for system.
  %problem.states.x0=[0 1000 13.23 -1.288  0 ];
  x0 = [0 1000 13.23 -1.288] ;
  problem.states.x0  = [ x0 1100 ] ;
  % Initial conditions for system. Bounds if x0 is free s.t. x0l=< x0 <=x0u
  problem.states.x0l = [ x0 1000 ] ; % 
  problem.states.x0u = [ x0 1500 ] ; 

  % State bounds. xl=< x <=xu
  % t,y,vx,vy,X
  problem.states.xl=[0   0    0 -10 1000] ;
  problem.states.xu=[200 1500 20 10 1500] ;

  % Terminal state bounds. xfl=< xf <=xfu
  xf = [900 13.23 -1.288] ;
  problem.states.xfl=[0   xf 1000]; 
  problem.states.xfu=[200 xf 1500];

  % Guess the state trajectories with [x0 xf]
  guess.states(:,1)=[0       100]; % t
  guess.states(:,2)=[1000    900]; % y
  guess.states(:,3)=[13.23   13.23]; % vx
  guess.states(:,4)=[-1.288 -1.288 ]; % vy
  guess.states(:,5)=[1250     1250 ];  % X

  % Number of control actions N 
  % Set problem.inputs.N=0 if N is equal to the number of integration steps.  
  % Note that the number of integration steps defined in settings.m has to be divisible 
  % by the  number of control actions N whenever it is not zero.
  problem.inputs.N=0;

  % Input bounds
  problem.inputs.ul=[0];
  problem.inputs.uu=[1.4];

  % Guess the input sequences with [u0 uf]
  guess.inputs(:,1)=[1 1];

  % Choose the set-points if required
  problem.setpoints.states=[];
  problem.setpoints.inputs=[];

  % Bounds for path constraint function gl =< g(x,u,p,t) =< gu
  problem.constraints.gl=[];
  problem.constraints.gu=[];

  % Bounds for boundary constraints bl =< b(x0,xf,u0,uf,p,t0,tf) =< bu
  problem.constraints.bl=[];
  problem.constraints.bu=[];

  % Problem data
  problem.data=[];

  % Get function handles and return to Main.m
  problem.functions={@L,@E,@f,@g,@b};

end

% L - Returns the stage cost.
% The function must be vectorized and
% xi, ui are column vectors taken as x(:,i) and u(:,i) (i denotes the i-th
% variable)
% 
% Syntax:  stageCost = L(x,xr,u,ur,p,t,data)
%
% Inputs:
%    x  - state vector
%    xr - state reference
%    u  - input
%    ur - input reference
%    p  - parameter
%    t  - time
%    data- structured variable containing the values of additional data used inside
%          the function
%
% Output:
%    stageCost - Scalar or vectorized stage cost
%
%  Remark: If the stagecost does not depend on variables it is necessary to multiply
%          the assigned value by t in order to have right vector dimesion when called for the optimization. 
%          Example: stageCost = 0*t;
function stageCost=L(x,xr,u,ur,p,t,data)
  stageCost = 0 ;
end

% E - Returns the boundary value cost
%
% Syntax:  boundaryCost=E(x0,xf,u0,uf,p,tf,data)
%
% Inputs:
%    x0  - state at t=0
%    xf  - state at t=tf
%    u0  - input at t=0
%    uf  - input at t=tf
%    p   - parameter
%    tf  - final time
%    data- structured variable containing the values of additional data used inside
%          the function
%
% Output:
%    boundaryCost - Scalar boundary cost
%
function boundaryCost=E(x0,xf,u0,uf,p,tf,data) 
  boundaryCost=-xf(5)/1000;
end

% f - Returns the ODE right hand side where x'= f(x,u,p,t)
% The function must be vectorized and
% xi, ui, pi are column vectors taken as x(:,i), u(:,i) and p(:,i). Each
% state corresponds to one column of dx.
% 
% 
% Syntax:  dx = f(x,u,p,t,data)
%
% Inputs:
%    x  - state vector
%    u  - input
%    p  - parameter
%    t  - time
%    data-structured variable containing the values of additional data used inside
%          the function 
%
% Output:
%    dx - time derivative of x
%
%  Remark: If the i-th ODE right hand side does not depend on variables it is necessary to multiply
%          the assigned value by a vector of ones with the same length  of t  in order 
%          to have  a vector with the right dimesion  when called for the optimization. 
%          Example: dx(:,i)= 0*ones(size(t,1)); 
%
function dx = f(x,u,p,t,data)
  tempo = x(:,1);
  yy    = x(:,2);
  vx    = x(:,3);
  vy    = x(:,4);
  L     = x(:,5);
  CL    = u(:,1);

  g   = 9.80665 ;
  rho = 1.13 ;
  S   = 14 ;
  k   = 0.069662 ;
  c0  = 0.034 ;
  m   = 100 ;
  R   = 100 ;
  um  = 2.5 ;
  
  xt = t.*L ;
  X  = (xt/R-2.5).^2 ;
  ua = um*(1-X).*exp(-X) ;
  Vy = vy-ua;
  vr = sqrt(vx.^2+Vy.^2) ;
  CD = c0+k*CL.^2;
  W  = m*g;

  dx(:,1) = (L./vx) ;
  dx(:,2) = (L./vx).*vy ;
  dx(:,3) = ((L*rho*S/(2*m))./vx).*vr.*(-CD.*vx-CL.*Vy) ;
  dx(:,4) = ((L*rho*S/(2*m))./vx).*vr.*(-CD.*Vy+CL.*vx)-(L*g./vx) ;
  dx(:,5) = 0;
end

% g - Returns the path constraint function where gl =< g(x,u,p,t) =< gu
% The function must be vectorized and
% xi, ui, pi are column vectors taken as x(:,i), u(:,i) and p(:,i). Each
% constraint corresponds to one column of c
% 
% Syntax:  c=g(x,u,p,t,data)
%
% Inputs:
%    x  - state vector
%    u  - input
%    p  - parameter
%    t  - time
%   data- structured variable containing the values of additional data used inside
%          the function
%
% Output:
%    c - constraint function
%
function c=g(x,u,p,t,data)
  c=[];
end

% b - Returns a column vector containing the evaluation of the boundary constraints: bl =< bf(x0,xf,u0,uf,p,t0,tf) =< bu
%
% Syntax:  bc=b(x0,xf,u0,uf,p,tf,data)
%
% Inputs:
%    x0  - state at t=0
%    xf  - state at t=tf
%    u0  - input at t=0
%    uf  - input at t=tf
%    p   - parameter
%    tf  - final time
%    data- structured variable containing the values of additional data used inside
%          the function
%
%          
% Output:
%    bc - column vector containing the evaluation of the boundary function 
%
function bc=b(x0,xf,u0,uf,p,tf,data)
  bc=[];
end
