gridSize = 0.05

mechatronix do |data|
  # User defined classes initialization
  data.Spline = 
  {
    :x => [ 0, 20, 20+80, 20+80+157.08, 20+80+157.08+80, 20+80+157.08+80+20 ],
    :y => [ 0, 0, 0.02, 0, 0 ],
  }
end