#-----------------------------------------------------------------------#
#  file: Monocar_Data.rb                                                #
#                                                                       #
#  version: 1.0   date 1/8/2018                                         #
#                                                                       #
#  Copyright (C) 2018                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#

mechatronix do |data|

  # User defined classes initialization
  # User defined classes: R O A D
  data.Road =
  {
    :roadWidth => 3.7,
    :gridSize  => 5,
    :theta0    => 0,
    :s0        => 0,
    :x0        => 0,
    :y0        => 0,
    :is_SAE    => false,
    :segments  => [

      {
        :rightWidth => 1.85,
        :leftWidth  => 1.85,
        :gridSize   => 1,
        :curvature  => 0,
        :length     => 50,
      },

      {
        :rightWidth => 1.85,
        :leftWidth  => 1.85,
        :gridSize   => 1,
        :curvature  => 0.02,
        :length     => 157.0796327,
      },

      {
        :rightWidth => 1.85,
        :leftWidth  => 1.85,
        :gridSize   => 1,
        :curvature  => 0,
        :length     => 50,
      },
    ],
  } ;

end

# EOF
