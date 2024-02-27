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
  vars,table = Utils::read_from_table(File.expand_path('reference_manoeuvre.txt', File.dirname(__FILE__)))
  p table 
    
  # p "Data read correctly and trajectory built"

  data.SplineMeasurement = 
    {
      :spline_type  => [ "linear" ],
      :headers      => [ "eta" ],
      :xdata         => table["time"],
      :ydata         => [table["measurements"]
                        ],
      :boundary => [
                    { :closed => false }
                  ],
    }

  #p data.SplineSet[:data]

end

#EOF