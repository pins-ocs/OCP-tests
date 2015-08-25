function res = Tmax_normalized( v__ )
  global Bike1D_data ;
  ModelPars = Bike1D_data.ModelPars ;
  Pmax = ModelPars(1) ;
  g    = ModelPars(2) ;
  m    = ModelPars(3) ;
  vmax = ModelPars(9) ;
  res  = Pmax / m / g * (1 - v__ / vmax);
end
