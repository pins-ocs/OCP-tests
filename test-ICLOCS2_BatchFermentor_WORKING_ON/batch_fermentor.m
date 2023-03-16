%Batch fermentor problem ( see ICLOCS website)
%
close all; clear all;

global T N mu mu1 epsilon dt
global ubar utilde umin umax

% Parametri moddello
global W rho_max mu_max mu_s kappa_x kappa_p kappa_in kappa_m S_f K_degr Yxs Yes;

W        = 1e-5;
rho_max  = 0.0055;
mu_max   = 0.11;
mu_s     = 0.029;
kappa_x  = 0.006;
kappa_p  = 0.0001;
kappa_in = 0.1;
kappa_m  = 0.0001;
S_f      = 500;
K_degr   = 0.01;
Yxs      = 0.47;
Yes      = 1.2;

T   = 126;
N   = 20;
mu  = 1e8; %penalty to add the state-constraints in J
mu1 = 0*1e0;
% epsilon = 100;
dt = T/N;

%----------------------




%-----------------------
%SQH parameters
kappa=10^-10;  %Tolerance for convergence
eta=10^-9;
zeta=0.8;
sigma=2;
kmax=100;        %Maximum iteration number
epsilon=10;      %Initial guess for epsilon
%-----------------------



% opts = optimoptions(...
%   'lsqnonlin', ...
%   'FunctionTolerance',1e-12, ...
%   'StepTolerance', 1e-12, ...
%   'MaxIterations', 1000, ...
%   'MaxFunctionEvaluations', 500000, ...
%   'CheckGradients',false, ...
%   'Display','iter', ...
%   'SpecifyObjectiveGradient',false ...
% );

opts = optimoptions(...
  'fsolve', ...
  'FunctionTolerance',1e-12, ...
  'StepTolerance', 1e-12, ...
  'MaxIterations', 1000, ...
  'MaxFunctionEvaluations', 500000, ...
  'CheckGradients',false, ...
  'Display','off', ...
  'SpecifyObjectiveGradient',false ...
);


u = 2*ones(N,1);
ubar=u;
utilde=u;

umin = zeros(N,1); umax = 50.*ones(N,1);


x0 = guess();

% [ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, [], [], opts );
[ Z, fval, exitflag, output ] = fsolve( @sys, x0, opts );

Zbar= Z;

% fprintf('exitflag = %d\n',exitflag);
% fprintf('iterations = %d\n',output.iterations);
% fprintf('%s\n',output.message);

[ X, P, S, V, L1, L2, L3, L4 ] = unpack( Z );

XM = (X(2:end)+X(1:end-1))./2;
PM = (P(2:end)+P(1:end-1))./2;
SM = (S(2:end)+S(1:end-1))./2;
VM = (V(2:end)+V(1:end-1))./2;

J_plot(1,1)=get_J(XM, PM,SM,VM,u);
J_plot(1,1);
Jk(1)=J_plot(1,1);

count_updates=1;
%-------------------------------------------
% SQH loop
%-------------------------------------------
tic
for k = 1: kmax

  [ X, P, S, V, L1, L2, L3, L4 ] = unpack( Z );

  XM   = (X(2:end)+X(1:end-1))./2;
  PM   = (P(2:end)+P(1:end-1))./2;
  SM   = (S(2:end)+S(1:end-1))./2;
  VM   = (V(2:end)+V(1:end-1))./2;

  L1M  = (L1(2:end)+L1(1:end-1))./2;
  L2M  = (L2(2:end)+L2(1:end-1))./2;
  L3M  = (L3(2:end)+L3(1:end-1))./2;
  L4M  = (L4(2:end)+L4(1:end-1))./2;

  for i = 1:N
    u(i,1) = argminH(XM(i), PM(i), SM(i),VM(i),L1M(i),L2M(i),L3M(i),L4M(i), u(i));
  end

  utilde=u;

  du = sum((u-ubar).^2)*dt ;

  %[ Z, resnorm, residual, exitflag, output ] = lsqnonlin( @sys, x0, [], [], opts );
  [ Z, fval, exitflag, output ]  = fsolve( @sys, x0, opts );
  [ X, P, S, V, L1, L2, L3, L4 ] = unpack( Z );

  XM = (X(2:end)+X(1:end-1))./2;
  PM = (P(2:end)+P(1:end-1))./2;
  SM = (S(2:end)+S(1:end-1))./2;
  VM = (V(2:end)+V(1:end-1))./2;

  J_int=get_J(XM, PM,SM,VM,u);   %(XM, PM,SM,VM,u)


  if(J_int-Jk(count_updates)>-eta*du)
    u = ubar;
    Z = Zbar;
    epsilon = epsilon*sigma;
  else
    count_updates=count_updates+1;
    epsilon=epsilon*zeta;
    mu1 = mu1*0.5;
    Jk(count_updates)=J_int;
    ubar=u;
    Zbar=Z;
    fprintf('| iter=%4i | J= %10.8f | du=%10.4e | eps=%10.4e |\n',k, J_int, du,epsilon);
  end

  if(du<kappa)
    u = ubar;
%   fprintf('converged\n')
    break;
  end
end
toc

%-------------------------------------------
% end SQH loop
%-------------------------------------------

figure
plot( u, 'LineWidth', 3 ); title('u');

figure
plot(0:dt:T, X, 'Linewidth',3); hold on;
plot(0:dt:T, P, 'Linewidth',3);
plot(0:dt:T, S, 'Linewidth',3);
plot(0:dt:T, V, 'Linewidth',3);
title('X 1...4')
hold off;



figure
plot(Jk,'-*','Linewidth',2)
xlabel('SQH iterations')
ylabel('J')





%
% ========================================================================
%
% H1
function res = mu_fun( s, x )
  global mu_max kappa_x;
  res = mu_max.*s./(kappa_x.*x+s);
end
% H2
function res = rho_fun( s )
  global rho_max kappa_p kappa_in;
  res = rho_max.*s./(kappa_p+s.*(1+s./kappa_in));
end

function res = Hamiltonian( X, P, S, V, L1, L2, L3, L4, u )
  global W rho_max mu_max mu_s kappa_x kappa_p kappa_in kappa_m S_f K_degr Yxs Yes;
  h1  = mu_fun(S,X);
  h2  = rho_fun(S);
  res = W*u.^2 + ...
        L1.*(h1.*X - X.*u./(S_f*V)) + ...
        L2.*(h2.*X - K_degr*P - P.*u./(S_f*V)) + ...
        L3.*( -h1.*X./Yxs - h2.*X./Yes - mu_s*S.*X./(kappa_m + S) + (u./V).*(1 - S./S_f) ) + ...
        L4.*u/S_f;
end

function Z = guess()
  global N;
  m  = N+1;
  X  = 30*ones(m,1);
  P  = 8.5*ones(m,1);
  S  = 0*ones(m,1);
  V  = 10*ones(m,1);

  L1 = zeros(m,1);
  L2 = zeros(m,1);
  L3 = zeros(m,1);
  L4 = zeros(m,1);

  Z  = [X;P;S;V;L1;L2;L3;L4];
end

function res = penalty( VAR )
  global mu;
  res = mu*(max(0,VAR).^3);
end

function res = int_penalty( VAR )
  global dt;
  res = sum(penalty(VAR))*dt;
end

function P = all_penalty( X, P, S, V, u )
  global N T mu dt;
  P = penalty(-X)   + penalty(-P)   + penalty(-S)   + penalty(-V) + ...
      penalty(X-40) + penalty(P-50) + penalty(S-25) + penalty( V-10 );
end

function J = get_J(X, P, S, V,u)  %(XM, PM,SM,VM,u)
  global W N T mu dt;
  % dt= T/N;
  J = -P(end)*V(end) + W*sum(u.^2)*dt + sum(all_penalty( X, P, S, V, u ))*dt;
end
%
% ========================================================================
%
function v = argminH( X, P, S, V, L1, L2, L3, L4, u )
  global epsilon umin umax mu mu1
  %----------------ANALYTICAL COMPUTATION-------------------------
  % dH/du = 0 =>....=>
  %u = max(umin, min(umax, u))
  %---------------------------------------------------------------

  %-----------------ALTERNATIVE METHOD----------------------------

  num_Int=100;
  Disc_KU=linspace(umin(1),umax(1),num_Int);
    dist=inf;
    while ( dist > 10^-12 )
      Ham = Hamiltonian( X, P, S, V, L1, L2, L3, L4, Disc_KU );

      %Find the position of a minimum on the disretised Disc_KU
      h1 = 0.11*S./(0.006*X +S);
      h2 = 0.0055*S./(0.0001 + S.*(1 +10*S));

      ad1 = L1.*(h1.*X - X./(500*V).*Disc_KU);
      ad2 = L2.*(h2.*X -0.01*P -P./(500*V).*Disc_KU);
      ad3 = L3.*(-X/0.47 .*h1 - X./1.2 .*h2 - 0.029*S./(0.0001 + S).*X + Disc_KU./V.*(1-S/500));
      ad4 = L4.*(Disc_KU./500) + 1e-5*Disc_KU.^2;

      if max(abs(Ham-ad1-ad2-ad3-ad4)) > 1e-6
        Ham-ad1-ad2-ad3-ad4
        stop;
      end

      ad5 =  mu*((max(0,-X).^3)) + mu*((max(0,-P).^3))+mu*((max(0,-S).^3))+mu*((max(0,-V).^3));
      ad6 =  mu*((max(0,X-40).^3)) + mu*((max(0,P-50).^3))+mu*((max(0,S-25).^3))+mu*((max(0,V-10).^3));

      %[~,pos]= min( Ham + all_penalty(X, P, S, V, u) + epsilon*((Disc_KU-u).^2) );
      [~,pos]= min(Ham+ ad5+ad6+ epsilon*((Disc_KU-u).^2) + mu1*(Disc_KU.^2));
      %Set the argument that minimised the augmented Hamiltonian as the current value for the control in
      %the corresponding grid point
      v = Disc_KU(pos);

      if (pos==1)                                              % If the interval is on the lower boundary of Disc_KU
        Disc_KU = linspace(Disc_KU(pos),Disc_KU(pos+1),num_Int); % Discretise the interval around the minimum
        dist    = (Disc_KU(pos+1)-Disc_KU(pos));                    % New distance of an interval
      elseif (pos==max(size(Disc_KU)))                        % Case if minimum is on the upper bound
        Disc_KU = linspace(Disc_KU(pos-1),Disc_KU(pos),num_Int);
        dist    = (Disc_KU(pos)-Disc_KU(pos-1));
      else
        %If the minimum is in the inner of Disc_KU, discretise around the minimum
        Disc_KU = linspace(Disc_KU(pos-1),Disc_KU(pos+1),num_Int);
        dist    = (Disc_KU(pos+1)-Disc_KU(pos-1));
      end
    end
  end
%
% ========================================================================
%
function F = fd_sys( X, P, S, V, L1, L2, L3, L4 , u )
  global N T mu dt
  h=dt;
%   h    = T/N;

X_D  = (X(2:end)-X(1:end-1))./h;
  P_D  = (P(2:end)-P(1:end-1))./h;
  S_D  = (S(2:end)-S(1:end-1))./h;
  V_D  = (V(2:end)-V(1:end-1))./h;

  L1_D = (L1(2:end)-L1(1:end-1))./h;
  L2_D = (L2(2:end)-L2(1:end-1))./h;
  L3_D = (L3(2:end)-L3(1:end-1))./h;
  L4_D = (L4(2:end)-L4(1:end-1))./h;

  XM   = (X(2:end)+X(1:end-1))./2;
  PM   = (P(2:end)+P(1:end-1))./2;
  SM   = (S(2:end)+S(1:end-1))./2;
  VM   = (V(2:end)+V(1:end-1))./2;

  L1M  = (L1(2:end)+L1(1:end-1))./2;
  L2M  = (L2(2:end)+L2(1:end-1))./2;
  L3M  = (L3(2:end)+L3(1:end-1))./2;
  L4M  = (L4(2:end)+L4(1:end-1))./2;

  h1 = 0.11*SM./(0.006*XM +SM);
  h2 = 0.0055*SM./(0.0001 + SM.*(1 +10*SM));

  h1_DX= - 0.006*(0.11*SM)./(0.006*XM+SM).^2;
  h1_DS= 0.11./(0.006*XM +SM) - (0.11*SM)./(0.006*XM+SM).^2;
  h2_DS= 0.0055./(0.0001+SM.*(1+10*SM)) -0.0055*SM./(0.0001+SM.*(1+10*SM)).^2.*(1+20*SM);

  FD1 = X_D - (h1.*XM - XM./(500*VM).*u);
  FD2 = P_D - (h2.*XM - 0.01*PM - PM./(500*VM).*u);
  FD3 = S_D - (-XM/0.47.*h1 - XM/1.2.*h2 - 0.029*SM./(0.0001 +SM).*XM + u./VM.*(1-SM/500));
  FD4 = V_D - (u/500);

%   FD5 = L1_D - (-L1M.*(-u./(500*VM) +h1 - 0.006*XM.*(0.11*SM)./(0.006*XM+SM).^2) -L2M.*h2 -L3M.*(-h1/0.47 - h2/1.2 + 0.006/0.47*XM.*(0.11*SM)./(0.006*XM+SM).^2 - 0.029*SM./(0.0001+SM)) - 3*mu.*max(0,-XM).^2 - 3*mu.*max(0,XM-40).^2);
%   FD6 = L2_D - (L2M.*(0.01 +u./(500*VM)) - 3*mu.*max(0,-PM).^2 - 3*mu.*max(0, PM-50).^2);
%   FD7 = L3_D - (-L1M.*(0.11./(0.006*XM +SM) - (0.11*SM)./(0.006*XM+SM).^2).*XM -L2M.*XM.*(0.0055./(0.0001+SM.*(1+10*SM)) -0.0055*SM./(0.0001+SM.*(1+10*SM)).^2.*(1+20*SM)) - L3M.*((-0.029./(0.0001+SM) + 0.029*SM./(0.0001+SM).^2).*XM - u./VM.*(1/500) -XM./0.47 .*(0.11./(0.006*XM+SM) -0.11*SM./(0.006*XM + SM).^2) - XM/1.2.*(0.0055./(0.0001+SM.*(1+10*SM)) - 0.0055*SM./(0.0001+SM.*(1+10*SM)).^2 .*(1+20*SM))) - 3*mu.*max(0,-SM).^2 - 3*mu.*max(0, SM-25).^2);
%   FD8 = L4_D - (u./(VM.^2).*((-L1M.*XM -L2M.*PM)/500 + L3M.*(1-SM/500)) -3*mu.*max(0,-VM).^2 - 3*mu.*max(0, VM-10).^2);

  FD5 = L1_D - (-L1M.*(-u./(500*VM) +h1 + XM.*h1_DX) -L2M.*h2 -L3M.*(-h1/0.47 - h2/1.2 - XM./0.47.*h1_DX - 0.029*SM./(0.0001+SM)) - 3*mu/h*max(0,-XM).^2 - 3*mu/h*max(0,XM-40).^2);
  FD6 = L2_D - (L2M.*(0.01 +u./(500*VM)) - 3*mu/h*max(0,-PM).^2 - 3*mu/h*max(0, PM-50).^2);
  FD7 = L3_D - (-L1M.*h1_DS.*XM -L2M.*XM.*h2_DS - L3M.*((-0.029./(0.0001+SM) + 0.029*SM./(0.0001+SM).^2).*XM - u./VM.*(1/500) -XM./0.47 .*h1_DS - XM/1.2.*h2_DS) - 3*mu/h*max(0,-SM).^2 - 3*mu/h*max(0, SM-25).^2);
  FD8 = L4_D - (u./(VM.^2).*((-L1M.*XM -L2M.*PM)/500 + L3M.*(1-SM/500)) -3*mu/h*max(0,-VM).^2 - 3*mu/h*max(0, VM-10).^2);



  BC  = [ X(1) - 1.5; P(1); S(1); V(1)-7; L1(end); L2(end) + V(end); L3(end); L4(end) + P(end)];
  F   = [ FD1; FD2; FD3; FD4; FD5; FD6; FD7; FD8; BC ];
end
%
% ========================================================================
%
function [ X, P, S, V, L1, L2, L3, L4 ] = unpack( Z )
  global N;
  m   = N+1;
  X  = Z(0*m+1:1*m);
  P  = Z(1*m+1:2*m);
  S  = Z(2*m+1:3*m);
  V  = Z(3*m+1:4*m);
  L1  = Z(4*m+1:5*m);
  L2  = Z(5*m+1:6*m);
  L3  = Z(6*m+1:7*m);
  L4  = Z(7*m+1:8*m);




end
%
% ========================================================================
%
function F = sys( Z )
global utilde
  [ X, P, S, V, L1, L2, L3, L4 ] = unpack( Z );
  F = fd_sys(  X, P, S, V, L1, L2, L3, L4 ,utilde );
end
