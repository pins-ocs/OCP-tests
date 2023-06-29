#--------------------------------------------------------------------------#
#   ____        _ _               ____ _               
#  / ___| _ __ | (_)_ __   ___   / ___| | __ _ ___ ___ 
#  \___ \| '_ \| | | '_ \ / _ \ | |   | |/ _` / __/ __|
#   ___) | |_) | | | | | |  __/ | |___| | (_| \__ \__ \
#  |____/| .__/|_|_|_| |_|\___|  \____|_|\__,_|___/___/
#        |_|                                           
#   ____       _               
#  / ___|  ___| |_ _   _ _ __  
#  \___ \ / _ \ __| | | | '_ \ 
#   ___) |  __/ |_| |_| | |_) |
#  |____/ \___|\__|\__,_| .__/ 
#                       |_|    
#--------------------------------------------------------------------------#
# possible choices

include Mechatronix

# user defined values

mechatronix do |data|
  
  # Read tabulated file data
  # p "Start reading data from file"
  pars, table = Utils::read_from_table(File.expand_path('../road_Valencia.txt', __FILE__))
  #p table 
    
  # p "Data read correctly and trajectory built"
  #abscissa	curvature	width_L	width_R
  data.SplineSetRoad2D =
    {
      #:spline_type  => [ "cubic", "cubic" , "cubic" , "cubic" , "cubic" , "cubic" , "cubic"   ], 
      :spline_type  => [ "linear", "linear"  ],
      :headers      => [ "width_L", "width_R"  ],
      :xdata         => table["abscissa"], #.map {|x|x*Math::PI/180.0},
      :ydata         => [table["width_L"],
                         table["width_R"], ],
    }

  #p data.SplineSet[:data]

end

#EOF
