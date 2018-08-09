function phaseout=SingularControl04Continuous(input)
  t    = input.phase(1).time ;
  x1    = input.phase(1).state(:,1) ;
  x2    = input.phase(1).state(:,2) ;
  x3    = input.phase(1).state(:,3) ;
  x4    = input.phase(1).state(:,4) ;
  u    = input.phase(1).control(:,1) ;
  
  
  
  x1dot = x2 ;
  x2dot = x3;
  x3dot = u;
  x4dot = x1.^2;
  
   
  phaseout.dynamics  = [x1dot x2dot x3dot x4dot] ;
  phaseout.path      = [] ; % no path constraint
  phaseout.integrand = zeros(size(t)) ;
end
