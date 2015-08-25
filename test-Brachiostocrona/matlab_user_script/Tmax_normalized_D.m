function res = Tmax_normalized_D( v__ )
  global Bike1D_data ;
  ModelPars = Bike1D_data.ModelPars ;
  Pmax = ModelPars(1) ;
  g    = ModelPars(2) ;
  m    = ModelPars(3) ;
  vmax = ModelPars(9) ;
  res  = -Pmax / m / g / vmax ;
end
