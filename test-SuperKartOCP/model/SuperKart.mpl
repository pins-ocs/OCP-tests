fo_vars := [s(t), n(t), alpha(t), u(t), v(t), z(t), phi(t), mu(t), Omega(t), 
omega_r(t), z_dot(t), phi_dot(t), mu_dot(t)];
u_vars := [delta(t), T_r(t)];
fo_eqns := [n(t)*diff(s(t),t)*Theta(s(t))-v(t)*sin(alpha(t))+u(t)*cos(alpha(t)
)-diff(s(t),t), -v(t)*cos(alpha(t))-u(t)*sin(alpha(t))+diff(n(t),t), -Omega(t)
*n(t)*Theta(s(t))+n(t)*diff(alpha(t),t)*Theta(s(t))+v(t)*sin(alpha(t))*Theta(s
(t))-u(t)*cos(alpha(t))*Theta(s(t))+Omega(t)-diff(alpha(t),t), -Omega(t)*m*v(t
)+m*diff(u(t),t)+1/2*rho*C_dA*u(t)^2-tire_S(r,tire_N(r,1/2*a*g*m/(a+b),mu(t)*b
-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-1/2*phi_dot(t)*t_r+z_dot(t)),arctan(Omega(t)*
b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(1/2*Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*
Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(1/2*Omega(t)*t_r+u(t))-1)-tire_S(r,
tire_N(r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t
)*t_r+z_dot(t)),arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*Omega(t
)*t_r+u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(-1
/2*Omega(t)*t_r+u(t))-1)+(tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a-1/2*phi(t
)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(Omega(t)*a/(1/2*
Omega(t)*t_f+u(t)))-1/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*
t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)*t_f-u(t)-2*Omega(t)^2*a^2/(Omega(t)*t_f+2*u
(t)))/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*t_f+u(t))^2+1)*
delta(t),0,0)+tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a+1/2*phi(t)*t_f+z(t),-
mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(Omega(t)*a/(-1/2*Omega(t)*t_f
+u(t)))-1/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+
1)*v(t)-(1/2*Omega(t)*t_f-u(t)+2*Omega(t)^2*a^2/(Omega(t)*t_f-2*u(t)))/(-1/2*
Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*delta(t),0,0)
)*delta(t), Omega(t)*m*u(t)+m*diff(v(t),t)-tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-
mu(t)*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(
Omega(t)*a/(1/2*Omega(t)*t_f+u(t)))-1/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/
(1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)*t_f-u(t)-2*Omega(t)^2*a^2/(
Omega(t)*t_f+2*u(t)))/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*
t_f+u(t))^2+1)*delta(t),0,0)-tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a+1/2*
phi(t)*t_f+z(t),-mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(Omega(t)*a/(
-1/2*Omega(t)*t_f+u(t)))-1/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*
Omega(t)*t_f+u(t))^2+1)*v(t)-(1/2*Omega(t)*t_f-u(t)+2*Omega(t)^2*a^2/(Omega(t)
*t_f-2*u(t)))/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t)
)^2+1)*delta(t),0,0)-tire_F(r,tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+
z(t),mu_dot(t)*b-1/2*phi_dot(t)*t_r+z_dot(t)),arctan(Omega(t)*b/(1/2*Omega(t)*
t_r+u(t)))-v(t)/(1/2*Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t)
)^2+1),0,omega_r(t)*r_r/(1/2*Omega(t)*t_r+u(t))-1)-tire_F(r,tire_N(r,1/2*a*g*m
/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t)*t_r+z_dot(t)),
arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*Omega(t)*t_r+u(t))/(
Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(-1/2*Omega(t)*
t_r+u(t))-1), m*diff(z_dot(t),t)-m*g+tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a-1/2*phi
(t)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+z_dot(t))+tire_N(f,1/2*m*g*b/(a+b
),-mu(t)*a+1/2*phi(t)*t_f+z(t),-mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t))+
tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-1/2*phi_dot(t
)*t_r+z_dot(t))+tire_N(r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)
*b+1/2*phi_dot(t)*t_r+z_dot(t)), Omega(t)*h*m*u(t)+(-diff(Omega(t),t)*I_xx+
I_zz*diff(Omega(t),t))*mu(t)-Omega(t)*(Omega(t)*I_yy-I_zz*Omega(t))*phi(t)-
Omega(t)*m*u(t)*z(t)+(-Omega(t)*I_xx-Omega(t)*I_yy+I_zz*Omega(t))*mu_dot(t)+h*
m*diff(v(t),t)+I_xx*diff(phi_dot(t),t)-1/2*t_f*tire_N(f,1/2*m*g*b/(a+b),-mu(t)
*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+z_dot(t))+1/2*t_f*
tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a+1/2*phi(t)*t_f+z(t),-mu_dot(t)*a+1/2*phi_dot
(t)*t_f+z_dot(t))-1/2*t_r*tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+z(t)
,mu_dot(t)*b-1/2*phi_dot(t)*t_r+z_dot(t))+1/2*t_r*tire_N(r,1/2*a*g*m/(a+b),mu(
t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t)*t_r+z_dot(t)), -h*m*diff(u
(t),t)-a*tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/
2*phi_dot(t)*t_f+z_dot(t))-a*tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a+1/2*phi(t)*t_f+
z(t),-mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t))-1/2*h*rho*C_dA*u(t)^2+b*tire_N(
r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t)*t_r+
z_dot(t))+b*tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-1
/2*phi_dot(t)*t_r+z_dot(t))+Omega(t)*(-Omega(t)*I_xx+I_zz*Omega(t))*mu(t)+(
diff(Omega(t),t)*I_yy-I_zz*diff(Omega(t),t))*phi(t)+Omega(t)*h*m*v(t)+(m*diff(
u(t),t)+1/2*rho*C_dA*u(t)^2)*z(t)+(Omega(t)*I_xx+Omega(t)*I_yy-I_zz*Omega(t))*
phi_dot(t)+I_yy*diff(mu_dot(t),t), I_zz*diff(Omega(t),t)-a*tire_F(f,tire_N(f,1
/2*m*g*b/(a+b),-mu(t)*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+
z_dot(t)),-arctan(Omega(t)*a/(1/2*Omega(t)*t_f+u(t)))-1/(1/2*Omega(t)*t_f+u(t)
)/(Omega(t)^2*a^2/(1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)*t_f-u(t)-2*
Omega(t)^2*a^2/(Omega(t)*t_f+2*u(t)))/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/
(1/2*Omega(t)*t_f+u(t))^2+1)*delta(t),0,0)-a*tire_F(f,tire_N(f,1/2*m*g*b/(a+b)
,-mu(t)*a+1/2*phi(t)*t_f+z(t),-mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t)),-
arctan(Omega(t)*a/(-1/2*Omega(t)*t_f+u(t)))-1/(-1/2*Omega(t)*t_f+u(t))/(Omega(
t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(1/2*Omega(t)*t_f-u(t)+2*Omega(t)^
2*a^2/(Omega(t)*t_f-2*u(t)))/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*
Omega(t)*t_f+u(t))^2+1)*delta(t),0,0)+1/2*t_r*tire_S(r,tire_N(r,1/2*a*g*m/(a+b
),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t)*t_r+z_dot(t)),arctan(
Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*Omega(t)*t_r+u(t))/(Omega(t)^2
*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(-1/2*Omega(t)*t_r+u(t))-1
)+b*tire_F(r,tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-\
1/2*phi_dot(t)*t_r+z_dot(t)),arctan(Omega(t)*b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(
1/2*Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(
t)*r_r/(1/2*Omega(t)*t_r+u(t))-1)-1/2*t_r*tire_S(r,tire_N(r,1/2*a*g*m/(a+b),mu
(t)*b-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-1/2*phi_dot(t)*t_r+z_dot(t)),arctan(
Omega(t)*b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(1/2*Omega(t)*t_r+u(t))/(Omega(t)^2*b
^2/(1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(1/2*Omega(t)*t_r+u(t))-1)+b*
tire_F(r,tire_N(r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*
phi_dot(t)*t_r+z_dot(t)),arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/
2*Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t
)*r_r/(-1/2*Omega(t)*t_r+u(t))-1)+(1/2*t_f*tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-
mu(t)*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(
Omega(t)*a/(1/2*Omega(t)*t_f+u(t)))-1/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/
(1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)*t_f-u(t)-2*Omega(t)^2*a^2/(
Omega(t)*t_f+2*u(t)))/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*
t_f+u(t))^2+1)*delta(t),0,0)-1/2*t_f*tire_F(f,tire_N(f,1/2*m*g*b/(a+b),-mu(t)*
a+1/2*phi(t)*t_f+z(t),-mu_dot(t)*a+1/2*phi_dot(t)*t_f+z_dot(t)),-arctan(Omega(
t)*a/(-1/2*Omega(t)*t_f+u(t)))-1/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/
2*Omega(t)*t_f+u(t))^2+1)*v(t)-(1/2*Omega(t)*t_f-u(t)+2*Omega(t)^2*a^2/(Omega(
t)*t_f-2*u(t)))/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(
t))^2+1)*delta(t),0,0))*delta(t), I_r*diff(omega_r(t),t)+r_r*(tire_S(r,tire_N(
r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*phi_dot(t)*t_r+
z_dot(t)),arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*Omega(t)*t_r+
u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*r_r/(-1/2*
Omega(t)*t_r+u(t))-1)+tire_S(r,tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r
+z(t),mu_dot(t)*b-1/2*phi_dot(t)*t_r+z_dot(t)),arctan(Omega(t)*b/(1/2*Omega(t)
*t_r+u(t)))-v(t)/(1/2*Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t
))^2+1),0,omega_r(t)*r_r/(1/2*Omega(t)*t_r+u(t))-1))-T_r(t), z_dot(t)-diff(z(t
),t), phi_dot(t)-diff(phi(t),t), mu_dot(t)-diff(mu(t),t)];
unprotect('small_vars'); small_vars := {mu(t), phi(t), v(t), z(t), delta(t), 
diff(mu(t),t), diff(phi(t),t), diff(v(t),t), diff(z(t),t), diff(delta(t),t), 
diff(diff(mu(t),t),t), diff(diff(phi(t),t),t), diff(diff(z(t),t),t), diff(diff
(delta(t),t),t)}; protect('small_vars');
vehicle_data := [g = 9.81, m = 165., I_zz = 26.40, I_xx = 23.82, I_yy = 20.21,
h = .26, a = .4, b = .4, t_f = 1.055, t_r = 1.2, k_r = .10e5, c_r = .5e3, k_f
= .10e5, c_f = .5e3, KS_r = 20., KL_r = 28., KL_f = 16., r_r = .16, rho = 1.2,
C_dA = .50, I_r = 1];
F_rr := tire_F(r,N_rr,arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*
Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*
r_r/(-1/2*Omega(t)*t_r+u(t))-1);
S_rr := tire_S(r,N_rr,arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*
Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*
r_r/(-1/2*Omega(t)*t_r+u(t))-1);
N_rr := tire_N(r,1/2*a*g*m/(a+b),mu(t)*b+1/2*phi(t)*t_r+z(t),mu_dot(t)*b+1/2*
phi_dot(t)*t_r+z_dot(t));
F_rl := tire_F(r,N_rl,arctan(Omega(t)*b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(1/2*
Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*
r_r/(1/2*Omega(t)*t_r+u(t))-1);
S_rl := tire_S(r,N_rl,arctan(Omega(t)*b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(1/2*
Omega(t)*t_r+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t))^2+1),0,omega_r(t)*
r_r/(1/2*Omega(t)*t_r+u(t))-1);
N_rl := tire_N(r,1/2*a*g*m/(a+b),mu(t)*b-1/2*phi(t)*t_r+z(t),mu_dot(t)*b-1/2*
phi_dot(t)*t_r+z_dot(t));
F_fr := tire_F(f,N_fr,-arctan(Omega(t)*a/(-1/2*Omega(t)*t_f+u(t)))-1/(-1/2*
Omega(t)*t_f+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(1/2*
Omega(t)*t_f-u(t)+2*Omega(t)^2*a^2/(Omega(t)*t_f-2*u(t)))/(-1/2*Omega(t)*t_f+u
(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*delta(t),0,0);
N_fr := tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a+1/2*phi(t)*t_f+z(t),-mu_dot(t)*a+1/2
*phi_dot(t)*t_f+z_dot(t));
F_fl := tire_F(f,N_fl,-arctan(Omega(t)*a/(1/2*Omega(t)*t_f+u(t)))-1/(1/2*Omega
(t)*t_f+u(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)
*t_f-u(t)-2*Omega(t)^2*a^2/(Omega(t)*t_f+2*u(t)))/(1/2*Omega(t)*t_f+u(t))/(
Omega(t)^2*a^2/(1/2*Omega(t)*t_f+u(t))^2+1)*delta(t),0,0);
N_fl := tire_N(f,1/2*m*g*b/(a+b),-mu(t)*a-1/2*phi(t)*t_f+z(t),-mu_dot(t)*a-1/2
*phi_dot(t)*t_f+z_dot(t));
lambda_rr := arctan(Omega(t)*b/(-1/2*Omega(t)*t_r+u(t)))-v(t)/(-1/2*Omega(t)*
t_r+u(t))/(Omega(t)^2*b^2/(-1/2*Omega(t)*t_r+u(t))^2+1);
lambda_rl := arctan(Omega(t)*b/(1/2*Omega(t)*t_r+u(t)))-v(t)/(1/2*Omega(t)*t_r
+u(t))/(Omega(t)^2*b^2/(1/2*Omega(t)*t_r+u(t))^2+1);
lambda_fr := -arctan(Omega(t)*a/(-1/2*Omega(t)*t_f+u(t)))-1/(-1/2*Omega(t)*t_f
+u(t))/(Omega(t)^2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(1/2*Omega(t)*t_f-u(
t)+2*Omega(t)^2*a^2/(Omega(t)*t_f-2*u(t)))/(-1/2*Omega(t)*t_f+u(t))/(Omega(t)^
2*a^2/(-1/2*Omega(t)*t_f+u(t))^2+1)*delta(t);
lambda_fl := -arctan(Omega(t)*a/(1/2*Omega(t)*t_f+u(t)))-1/(1/2*Omega(t)*t_f+u
(t))/(Omega(t)^2*a^2/(1/2*Omega(t)*t_f+u(t))^2+1)*v(t)-(-1/2*Omega(t)*t_f-u(t)
-2*Omega(t)^2*a^2/(Omega(t)*t_f+2*u(t)))/(1/2*Omega(t)*t_f+u(t))/(Omega(t)^2*a
^2/(1/2*Omega(t)*t_f+u(t))^2+1)*delta(t);
kappa_rr := omega_r(t)*r_r/(-1/2*Omega(t)*t_r+u(t))-1;
kappa_rl := omega_r(t)*r_r/(1/2*Omega(t)*t_r+u(t))-1;
