#--------------------------------------------------------------------------#
#  file: pointcar_Data.rb                                                  #
#                                                                          #
#  version: 1.0   date 13/7/2018                                           #
#                                                                          #
#  Copyright (C) 2018                                                      #
#                                                                          #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti                #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      Via Sommarive 9, I-38123, Trento, Italy                             #
#      email: enrico.bertolazzi@unitn.it                                   #
#             francesco.biral@unitn.it                                     #
#             paolo.bosetti@unitn.it                                       #
#--------------------------------------------------------------------------#

# User defined classes initialization
# User defined classes: R O A D

mechatronix do |data|

  # User defined classes initialization
  # User defined classes: R O A D
  data.Road = 
  {
    :roadWidth => 3.7,
    :gridSize  => 0.1,
    :theta0    => 0,
    :s0        => 0,
    :x0        => 0,
    :y0        => 0,
    :is_SAE    => true,
    :segments  => [
      
      {
        :length   => 10,
        :gridSize => 0.15,
      },
      
      {
        :length   => 50*Math::PI,
        :gridSize => 1,
        :radius   => 50,
      },
      
      {
        :length   => 60,
        :gridSize => 0.5,
      },
      
      {
        :length   => 10,
        :gridSize => 0.15,
      },
    ]
  }
end

# EOF
