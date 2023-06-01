p = bb.sol( 4:bb.nx:(bb.N*bb.nx));

p__o = bb.sol( (bb.N*bb.nx)+1:bb.nu:end);

zeta = bb.nodes;

zeta_1 = bb.nodes(1:end-1);
figure()

plot(zeta,p  ,'Linewidth', 2);
hold on
plot(zeta_1,p__o, 'Linewidth', 2);
legend('p','p__o')
grid on