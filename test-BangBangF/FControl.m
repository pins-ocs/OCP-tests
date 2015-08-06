function res = FControl( what, y, a, b )
  global BangBangF_data ;
  ModelPars = BangBangF_data.ModelPars ;

  epsilon = BangBangF_data.Fcontrol.epsilon ;
  h       = BangBangF_data.Fcontrol.h ;

  CF1 = epsilon/log(cos((pi/2)*(1-h)));
  CF2 = (b-a)/(pi*CF1) ;

  x = (2*y-(b+a))/(b-a) ;

  switch ( what )
  case 'eval'
    res = CF1*log(cos((pi/2)*x));
  case 'solve'
    res = (a+b)/2-((b-a)/pi)*atan(CF2*y) ;
  case 'D_1'
    res = -CF1*(pi/(b-a))*tan((pi/2)*x) ;
  case 'D_1_1'
    res = -CF1*(pi/(b-a))^2/(cos((pi/2)*x))^2 ;
  end
end
