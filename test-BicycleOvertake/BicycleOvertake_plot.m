data = importdata('data/BicycleOvertake_out.txt') ;
%data = importdata('data/BicycleOvertake_not_converged.txt') ;


zeta = data.data(:,find( strcmp(data.textdata,'zeta') )) ;
TimeSize = data.data(:,find( strcmp(data.textdata,'TimeSize') )) ;
t    = zeta.*TimeSize ;
s1   = data.data(:,find( strcmp(data.textdata,'s1') )) ;
v1   = data.data(:,find( strcmp(data.textdata,'v1') )) ;
s2   = data.data(:,find( strcmp(data.textdata,'s2') )) ;
v2   = data.data(:,find( strcmp(data.textdata,'v2') )) ;
u    = data.data(:,find( strcmp(data.textdata,'u') )) ;
ds   = data.data(:,find( strcmp(data.textdata,'ds') )) ;
scia = data.data(:,find( strcmp(data.textdata,'scia') )) ;

subplot(4,1,1) ;
plot( t, s1-s2 ) ; %, t, ds ) ;
title('s1-s2') ;

subplot(4,1,2) ;
plot( t, u ) ;
title('u') ;

subplot(4,1,3) ;
plot( t, v1, t, v2 ) ;
title('v1, v2') ;

subplot(4,1,4) ;
plot( t, scia ) ;
title('step') ;
