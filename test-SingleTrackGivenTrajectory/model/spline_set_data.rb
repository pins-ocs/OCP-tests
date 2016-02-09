gridSize = 0.05

mechatronix do |data|
  # User defined classes initialization
  data.SplineSet = 
  {
    :spline_type => [ "linear" ],
    :headers     => [ "curvature" ],
    :xdata => [ 0, 20, 20+80, 20+80+157.08, 20+80+157.08+80, 20+80+157.08+80+20  ],
    :ydata => [ [ 0, 0, 0.02, 0, 0 ] ],
  }
end
