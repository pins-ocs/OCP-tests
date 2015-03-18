def do_test(dir)
  system("cd #{dir} ; rake clobber maple clean main >& tmp.txt ; ./bin/main ; cd .." ) ;
end

dirs = [ 
  "test-BangBangF",
  "test-BangBangFclip",
  "test-BangBangFmodule",
  "test-BangBangFtau",
  "test-BangBangFtmin",
  "test-BangBangFwork",
  "test-Bike1D",
  "test-BikeSteering",
  ##"test-BoundaryConditions",
  "test-Brachiostocrona",
  "test-CNOC",
  "test-DaLio1Dcar",
  "test-Dadebo1",
  "test-DubinsCar",
  "test-EPC",
  "test-EconomicGrowthModel",
  "test-EconomicGrowthModel2",
  "test-Fermentor",
  "test-GerdtsKunkel",
  "test-GoddardRocket",
  "test-GunnAndThomas",
  "test-HangGlider",
  "test-Monobike",
  "test-Monocar",
  "test-MonocarLot",
  "test-PARAMETER-ESTIMATION2-FROM-ACADO",
  "test-RaoAndMease",
  "test-SingularCalogero",
  "test-SingularCalogeroModified",
  "test-SingularConstrainedCalogero",
  "test-SingularLuus02",
  "test-SingularLuus03",
  "test-SingularLuus04",
  "test-SingularLuus04_FreeTime",
  "test-SingularMarchal",
  "test-SlidingMode",
  "test-SuperBike",
  "test-SuperCarOCP",
  "test-SuperKartOCP",
  "test-SuperKart_complete",
  "test-Train",
  "test-Underwater",
  "test-Zermelo",
  "test-ZermeloSimple",
  "test-moto_dalio",
  "test-pointcar"
] ;

dirs.each do |d|
  puts "\n\n\n\n\n"
  puts "=================================================================="
  puts "=================================================================="
  puts "=================================================================="
  puts "=================================================================="
  puts "=================================================================="
  puts "=================================================================="
  puts "#{d}"
  do_test(d) ;
  puts "\n\n#{d}\n\n\n"
end
