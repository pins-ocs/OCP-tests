#  _____            _                  _   _       _
# | ____|__ _ _   _(_)_ __   ___   ___| |_(_) __ _| |
# |  _| / _` | | | | | '_ \ / _ \ / __| __| |/ _` | |
# | |__| (_| | |_| | | | | | (_) | (__| |_| | (_| | |
# |_____\__, |\__,_|_|_| |_|\___/ \___|\__|_|\__,_|_|
#          |_|
# spacecracft equations
bf1      := sqrt(p)/sqrt(muS):
TimeSize := time_f-time_i:

eq1 := dp - TimeSize*bf1*((2*p/w)*DELTA_T):
eq2 := df - TimeSize*bf1*(DELTA_R*sin(L)+
                         ((w+1)*cos(L)+f)*DELTA_T/w -
                         (h*sin(L)-k*cos(L))*g*DELTA_N/w ):
eq3 := dg - TimeSize*bf1*(-DELTA_R*cos(L)+
                            ((w+1)*sin(L)+g)*DELTA_T/w+
                            (h*sin(L)-k*cos(L))*f*DELTA_N/w):
eq4 := dh - TimeSize*bf1*(s2*DELTA_N*cos(L)/(2*w)):
eq5 := dk - TimeSize*bf1*(s2*DELTA_N*sin(L)/(2*w)):
eq6 := dL - TimeSize*(w^2/(p*bf1)+bf1*(h*sin(L)-k*cos(L))*DELTA_N/w):

EQSUBS1 := [
  w       = 1+f*cos(L)+g*sin(L),
  s2      = 1+h^2+k^2,
  r       = p/(1+f*cos(L)+g*sin(L)),
  a2      = h^2-k^2,
  DELTA_R = w_nonlin*acceleration_r(ray(p,f,g,L),muS),
  DELTA_T = w_nonlin*0,
  DELTA_N = w_nonlin*0
]:

EQSUBS2 := [
  p  = p(zeta),
  f  = f(zeta),
  g  = g(zeta),
  h  = h(zeta),
  k  = k(zeta),
  L  = L(zeta),
  dp = diff(p(zeta),zeta),
  df = diff(f(zeta),zeta),
  dg = diff(g(zeta),zeta),
  dh = diff(h(zeta),zeta),
  dk = diff(k(zeta),zeta),
  dL = diff(L(zeta),zeta)
]:

ode := subs(EQSUBS2,subs(EQSUBS1,<eq||(1..6)>)):

# equinoziale -> posizione
bf := p/((1+f*cos(L)+g*sin(L))*(1+h^2+k^2)):
X  := bf*cos(L):
Y  := bf*sin(L):
xP := simplify((1+h^2-k^2)*X+2*retrograde*h*k*Y):
yP := simplify(retrograde*(1-h^2+k^2)*Y+2*h*k*X):
zP := simplify(2*(h*Y-retrograde*k*X)):

# equinoziale -> velocità
bf2   := sqrt(muS)/(sqrt(p)*(1+h^2+k^2)):
cosLf := bf2 * (cos(L)+f):
sinLg := bf2 * (sin(L)+g):
xV    := simplify( retrograde*2*h*k*cosLf - (1+h^2-k^2)*sinLg ):
yV    := simplify( retrograde*(1-h^2+k^2)*cosLf - 2*h*k*sinLg ):
zV    := simplify( 2 * ( h*cosLf + retrograde*k*sinLg) ):

# distanza dal fuoco
raggio := p/(1+f*cos(L)+g*sin(L)):

# velocità
velocita2 := muS*(f*(2*cos(L)+f)+g*(2*sin(L)+g)+1)/p:

#
# terna equinoziale
#
Dr := <(h^2-k^2+1)*cos(L)+2*retrograde*h*k*sin(L),
        -(retrograde*(h^2-k^2-1)*sin(L)-2*h*k*cos(L)),
         2*(-cos(L)*k*retrograde+h*sin(L))>/(h^2+k^2+1):

Dn := <2*k, -2*h, -retrograde*(h^2+k^2-1)>/(h^2+k^2+1):

Dt := <(-h^2+k^2-1)*sin(L)+2*h*k*retrograde*cos(L),
        -retrograde*(h^2-k^2-1)*cos(L)-2*h*k*sin(L),
         2*k*retrograde*sin(L)+2*h*cos(L)>/(h^2+k^2+1):

# continuazione
addUserFunction(cont(s,eps0,eps1)=exp((1-s)*log(eps0)+s*log(eps1)),derivatives=0);

# proiezione r/|r|^3 lungo Dr= 1/|r|^2

#addUserFunction(x_position(p,f,g,h,k,L,retrograde)=xP,derivatives=2,simplify_assume=[p>0]);
#addUserFunction(y_position(p,f,g,h,k,L,retrograde)=yP,derivatives=2,simplify_assume=[p>0]);
#addUserFunction(z_position(p,f,g,h,k,L,retrograde)=zP,derivatives=2,simplify_assume=[p>0]);

#addUserFunction(x_velocity(p,f,g,h,k,L,retrograde)=xV,derivatives=2,simplify_assume=[p>0]);
#addUserFunction(y_velocity(p,f,g,h,k,L,retrograde)=yV,derivatives=2,simplify_assume=[p>0]);
#addUserFunction(z_velocity(p,f,g,h,k,L,retrograde)=zV,derivatives=2,simplify_assume=[p>0]);

addUserFunction(norm_reg(x,y,z)=sqrt(x^2+y^2+z^2+epsi_norm^2),derivatives=2);
addUserFunction(ray(p,f,g,L)=raggio,derivatives=2,simplify_assume=[p>0]);
addUserFunction(vel(p,f,g,L,muS)=sqrt(velocita2),derivatives=2,simplify_assume=[p>0,muS>0]);

addUserFunction(vc(r),derivatives=2);
addUserFunction(acceleration_r(r,muS)=(muS/r-vc(r)^2)/r,derivatives=2,simplify_assume=[r>0,muS>0]);

addUserFunction(X_begin(t),derivatives=2);
addUserFunction(Y_begin(t),derivatives=2);
addUserFunction(Z_begin(t),derivatives=2);
addUserFunction(VX_begin(t),derivatives=2);
addUserFunction(VY_begin(t),derivatives=2);
addUserFunction(VZ_begin(t),derivatives=2);

addUserFunction(X_end(t),derivatives=2);
addUserFunction(Y_end(t),derivatives=2);
addUserFunction(Z_end(t),derivatives=2);
addUserFunction(VX_end(t),derivatives=2);
addUserFunction(VY_end(t),derivatives=2);
addUserFunction(VZ_end(t),derivatives=2);

#Describe(addBoundaryConditions) ;
XPOS := astro_x_position__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),retrograde):
YPOS := astro_y_position__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),retrograde):
ZPOS := astro_z_position__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),retrograde):
XVEL := astro_x_velocity__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),muS,retrograde):
YVEL := astro_y_velocity__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),muS,retrograde):
ZVEL := astro_z_velocity__xo(p(zeta),f(zeta),g(zeta),h(zeta),k(zeta),L(zeta),muS,retrograde):

X0  := X_begin(time_i):
Y0  := Y_begin(time_i):
Z0  := Z_begin(time_i):

X1  := X_end(time_f):
Y1  := Y_end(time_f):
Z1  := Z_end(time_f):

VX0 := VX_begin(time_i):
VY0 := VY_begin(time_i):
VZ0 := VZ_begin(time_i):

VX1 := VX_end(time_f):
VY1 := VY_end(time_f):
VZ1 := VZ_end(time_f):

COMMON_PARS := [
  w_guess  = 0,
  w_nonlin = 0,
  # --------
  maxDV   = 0.1789746289,
  totalDV = 0.4090848660,
  # --------
  ray_min        = 2.01,
  ray_max        = 31.99,
  ray_tol        = 0.001,
  ray_epsi       = 0.001,
  min_delta_T    = 2,
  time_epsilon   = 0.0001,
  time_tolerance = 0.01,
  # --------
  epsi_norm      = 0.01,
  epsi_norm_max  = 0.01,
  epsi_norm_min  = 0.0001
]:

COMMON_POST := [
  [X_begin(TIME),"X_begin"],
  [Y_begin(TIME),"Y_begin"],
  [Z_begin(TIME),"Z_begin"],

  [VX_begin(TIME),"VX_begin"],
  [VY_begin(TIME),"VY_begin"],
  [VZ_begin(TIME),"VZ_begin"],

  [X_end(TIME),"X_end"],
  [Y_end(TIME),"Y_end"],
  [Z_end(TIME),"Z_end"],

  [VX_end(TIME),"VX_end"],
  [VY_end(TIME),"VY_end"],
  [VZ_end(TIME),"VZ_end"]
]:
