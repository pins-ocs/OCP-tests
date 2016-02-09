gridSize = 0.05

mechatronix do |data|
  # User defined classes initialization
  data.Road = 
  {
    :theta0   => 0,
    :s0       => 0,
    :x0       => 0,
    :y0       => 0,
    :is_SAE   => false,
    :segments => [
      
      {
        :leftWidth  => 5/2,
        :curvature  => 0,
        :rightWidth => 5/2,
        :gridSize   => gridSize,
        :length     => 20,
      },
      
      {
        :leftWidth  => 5/2,
        :curvature  => 0,
        :rightWidth => 5/2,
        :gridSize   => gridSize,
        :length     => 80,
      },
      
      {
        :initialCurvature => 0.02,
        :leftWidth        => 5/2,
        :rightWidth       => 5/2,
        :finalCurvature   => 0.02,
        :gridSize         => gridSize,
        :length           => 157.08,
      },
      
      {
        :leftWidth  => 5/2,
        :curvature  => 0,
        :rightWidth => 5/2,
        :gridSize   => gridSize,
        :length     => 80,
      },
      
      {
        :leftWidth  => 5/2,
        :curvature  => 0,
        :rightWidth => 5/2,
        :gridSize   => gridSize,
        :length     => 20,
      },
    ]
    }

end