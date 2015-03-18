function phaseout=UnderwaterContinuous(input)
  m1 = 13.2;
  m3 = 25.6;
  inertia = 0.12;
  t     = input.phase(1).time ;
  x     = input.phase(1).state(:,1) ;
  z     = input.phase(1).state(:,2) ;
  vx    = input.phase(1).state(:,3) ;
  vz    = input.phase(1).state(:,4) ;
  theta = input.phase(1).state(:,5) ;
  omega = input.phase(1).state(:,6) ;
  T     = input.phase(1).state(:,7) ;
  u1    = input.phase(1).control(:,1) ;
  u2    = input.phase(1).control(:,2) ;
  u3    = input.phase(1).control(:,3) ;
  
  
  
  x1dot = T.*(vx.*cos(theta)+vz.*sin(theta)) ;
  x2dot = T.*(vz.*cos(theta)-vx.*sin(theta));
  x3dot = T.*omega ;
  x4dot = T.*(u1./m1-vz.*omega.*(m3/m1));
  x5dot = T.*(u2./m3+vx.*omega.*(m1/m3));
  x6dot = T.*(u3./inertia+vx.*vz.*(m3-m1)/inertia);
  x7dot = zeros(size(t));
   
  phaseout.dynamics  = [x1dot x2dot x3dot x4dot x5dot x6dot x7dot ] ;
  phaseout.path      = [] ; % no path constraint
  phaseout.integrand = zeros(size(t)) ;
end
