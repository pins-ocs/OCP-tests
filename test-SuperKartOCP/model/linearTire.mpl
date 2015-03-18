tire_N := (name, N0, xi, xi_rate) -> posReg(N0+cat(k_,name)*xi+cat(c_,name)*
xi_rate);
tire_S := (tire, N, lambda, phi, kappa) -> cat(KS_,tire)*N*kappa;
tire_F := (tire, N, lambda, phi, kappa) -> cat(KL_,tire)*N*lambda;
