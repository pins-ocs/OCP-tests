include Mechatronix

gridSize = 0.05 # default: every 5cm

mechatronix do |data|

  # Road per il circuito di SPA-FRANCORCHAMPS  
  Road_half_width = 6

  GridSizeMultipler = 1
    # R O A D
    data.Road = {
      #:meshGridSize => 1,
      :gridSize => 1,
      :roadWidth    => 2*Road_half_width, 
      :theta0       => 0,
      :s0           => 0,
      :x0           => 0,
      :y0           => 0,
      :isSAE        => true,
      :segments     => []
  }

  data.Road[:segments] << {:Length => 268.41596493, :initialCurvature =>  -0.00013852,  :finalCurvature   =>  -0.00111413 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  31.16644924, :initialCurvature =>  -0.14835903,  :finalCurvature   =>  -0.00905621 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 354.65575897, :initialCurvature =>   0.00083487,  :finalCurvature   =>  -0.00313990 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 207.95039965, :initialCurvature =>   0.00044729,  :finalCurvature   =>  -0.00004305 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  83.11870679, :initialCurvature =>  -0.00499887,  :finalCurvature   =>   0.01208489 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  95.55365343, :initialCurvature =>   0.00134067,  :finalCurvature   =>  -0.01052564 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 116.78112466, :initialCurvature =>  -0.00962787,  :finalCurvature   =>   0.00411102 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 100.90536102, :initialCurvature =>   0.01105484,  :finalCurvature   =>  -0.00565341 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 244.17564307, :initialCurvature =>   0.00150893,  :finalCurvature   =>  -0.00253593 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  88.89102995, :initialCurvature =>  -0.00485968,  :finalCurvature   =>   0.00254170 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 680.11925941, :initialCurvature =>  -0.00006341,  :finalCurvature   =>   0.00002659 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  78.57394239, :initialCurvature =>  -0.01649083,  :finalCurvature   =>  -0.02122158 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  79.07273174, :initialCurvature =>   0.02522984,  :finalCurvature   =>   0.01144217 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  95.92187019, :initialCurvature =>   0.00851979,  :finalCurvature   =>  -0.01744093 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 188.04481029, :initialCurvature =>  -0.01269045,  :finalCurvature   =>   0.00424639 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 167.95026167, :initialCurvature =>   0.00168104,  :finalCurvature   =>  -0.00379117 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  93.13450504, :initialCurvature =>  -0.02225371,  :finalCurvature   =>  -0.01948272 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  62.91880703, :initialCurvature =>  -0.02403964,  :finalCurvature   =>  -0.01088918 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 130.10616794, :initialCurvature =>  -0.00006949,  :finalCurvature   =>   0.00346007 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  52.06009800, :initialCurvature =>   0.02621089,  :finalCurvature   =>   0.01920416 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 220.74231575, :initialCurvature =>  -0.00010272,  :finalCurvature   =>  -0.00144167 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 235.19138393, :initialCurvature =>  -0.00026125,  :finalCurvature   =>   0.00070307 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 136.14786035, :initialCurvature =>   0.01475287,  :finalCurvature   =>   0.00385269 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 191.52279546, :initialCurvature =>   0.00310431,  :finalCurvature   =>   0.00902704 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 272.17221893, :initialCurvature =>   0.00146630,  :finalCurvature   =>  -0.00088744 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 126.16789847, :initialCurvature =>   0.00334631,  :finalCurvature   =>  -0.01677585 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  80.83492003, :initialCurvature =>  -0.01457234,  :finalCurvature   =>  -0.00889941 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 103.44483379, :initialCurvature =>   0.01084106,  :finalCurvature   =>   0.01592214 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 207.70524107, :initialCurvature =>   0.00494010,  :finalCurvature   =>  -0.00350124 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  84.38887630, :initialCurvature =>  -0.01196972,  :finalCurvature   =>  -0.02586791 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 148.20073114, :initialCurvature =>   0.00555922,  :finalCurvature   =>  -0.01020357 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  85.12269980, :initialCurvature =>  -0.00816289,  :finalCurvature   =>  -0.01218014 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 118.11789492, :initialCurvature =>   0.00080205,  :finalCurvature   =>  -0.00442719 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 184.93552473, :initialCurvature =>  -0.00260881,  :finalCurvature   =>  -0.00038858 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 267.23389782, :initialCurvature =>  -0.00338904,  :finalCurvature   =>   0.00178021 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 214.66190111, :initialCurvature =>   0.00241122,  :finalCurvature   =>   0.00411986 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 180.50060988, :initialCurvature =>  -0.00421951,  :finalCurvature   =>   0.00774823 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  73.10986179, :initialCurvature =>   0.01129778,  :finalCurvature   =>  -0.00106990 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 184.20716325, :initialCurvature =>   0.00053508,  :finalCurvature   =>  -0.00069143 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 144.45884371, :initialCurvature =>  -0.00353334,  :finalCurvature   =>  -0.00007505 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 136.23643684, :initialCurvature =>  -0.00067520,  :finalCurvature   =>   0.00097963 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  28.80513435, :initialCurvature =>  -0.08890172,  :finalCurvature   =>  -0.05712332 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  45.61022550, :initialCurvature =>   0.00885904,  :finalCurvature   =>   0.06595860 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length =>  44.86161912, :initialCurvature =>   0.05021172,  :finalCurvature   =>  -0.01200622 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width } 
  data.Road[:segments] << {:Length => 257.77168829, :initialCurvature =>  -0.00088992,  :finalCurvature   =>   0.00086831 , :GridSize   => 1.0, :LeftWidth  => Road_half_width, :RightWidth  => Road_half_width }
end