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
  table = Utils::read_from_table(File.expand_path('../reference_manoeuvre.txt', __FILE__))
  #p table 
    
  # p "Data read correctly and trajectory built"

  data.SplineRefMan = 
    {
      :spline_type  => [ "cubic", "cubic" , "cubic", "cubic", "cubic"  ],
      :headers      => [ "u", "Omega" , "delta", "S", "curv_trj" ],
      :xdata         => table["zeta"],
      :ydata         => [table["u"],
                         table["Omega"],
                         table["delta"],
                         table["S"],
                         table["curv_trj"]
                        ],
    }

  #p data.SplineSet[:data]

end

#EOF