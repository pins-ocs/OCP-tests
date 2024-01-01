tvars := [s(t), n(t), alpha(t), V(t), Omega(t), fx(t)];
uvars := [v__fx(t), v__Omega(t)];
eqns_t := [diff(s(t),t) = V(t)*cos(alpha(t))/(1-Kappa(s(t))*n(t)), diff(n(t),t
) = V(t)*sin(alpha(t)), diff(alpha(t),t) = Omega(t)-Kappa(s(t))*diff(s(t),t),
diff(V(t),t) = fx(t)-kD*V(t)^2, diff(fx(t),t) = v__fx(t)*v__fx__max, diff(
Omega(t),t) = v__Omega(t)*v__Omega__max];
fy := Omega(t)*V(t);
point_mass_data := [g = 9.806, m = 700, kD = .2500000000/m, mu__x__max = 1, 
mu__y__max = 1.5, Pmax = .200e6, v__fx__max = 30, v__Omega__max = 5];
