eqns_dyn_xy_no_slip := [diff(x(t),t)-cos(psi(t))*u(t), diff(y(t),t)-sin(psi(t)
)*u(t), diff(psi(t),t)-Omega(t), diff(u(t),t) = a(t)-c0*u(t)-c1*u(t)^2];
eqns_dyn_sn_no_slip := [(-kappa(s(t))*n(t)+1)*diff(s(t),t) = cos(alpha(t))*u(t
), diff(n(t),t) = sin(alpha(t))*u(t), tan(delta(t))*u(t)/L-diff(alpha(t),t) =
diff(s(t),t)*kappa(s(t)), diff(u(t),t) = a(t)-c0*u(t)-c1*u(t)^2];
eq_clothoid := [kappa(t) = kappa0+kappa1*s(t), theta(t) = 1/2*s^2*kappa1+
kappa0*s+theta0];
eq_psi_dot := diff(psi(t),t) = tan(delta(t))*u(t)/L;
