data = importdata('data/Brachiostocrona_out.txt');

zeta   = data.data(:,2) ;
x      = data.data(:,4) ;
y      = data.data(:,5) ;
vtheta = data.data(:,3) ;
theta  = data.data(:,8) ;

subplot(2,2,1) ;
plot(x,y) ;
title('x,y') ;
axis equal ;

subplot(2,2,2) ;
plot(zeta,theta) ;
title('theta') ;

subplot(2,2,3) ;
plot(zeta,vtheta) ;
title('v-theta') ;
