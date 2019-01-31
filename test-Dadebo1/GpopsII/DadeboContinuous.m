function phaseout=DadeboContinuous(input)
  t    = input.phase(1).time ;
  x1    = input.phase(1).state(:,1) ;
  x2    = input.phase(1).state(:,2) ;
  u    = input.phase(1).control(:,1) ;
  
  
  
  x1dot = u ;
  x2dot = x1.^2+u.^2;
  
  
   
  phaseout.dynamics  = [x1dot x2dot ] ;
  phaseout.path      = [] ; % no path constraint
  phaseout.integrand = zeros(size(t)) ;
end
