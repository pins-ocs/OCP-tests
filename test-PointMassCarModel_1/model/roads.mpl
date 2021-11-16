# Road definition
grid_size_base := 1.0:
W0             := 5*12:
RoadWidth      := W0;
road_data_init := [
  "theta0"   = 0,
  "s0"       = 0,
  "x0"       = 0,
  "y0"       = 0,
  "is_SAE"   = false,
  "segments" = Array([
    #table([
    #  "length"     = 10,
    #  "gridSize"   = 0.1,
    #  "curvature"  = 0,
    #  "rightWidth" = 0*W0/2,
    #  "leftWidth"  = W0
    #]),
    table([
      "length"     = 190,
      "gridSize"   = grid_size_base,
      "curvature"  = 0,
      "rightWidth" = W0,
      "leftWidth"  = W0/8
    ]),
    table([
      "length"     = evalf(Pi*310),
      "gridSize"   = grid_size_base,
      "curvature"  = 1/310.,
      "rightWidth" = W0/2,
      "leftWidth"  = W0
    ]),
    table([
      "length"     = 180,
      "gridSize"   = grid_size_base,
      "curvature"  = 0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = evalf(Pi/2*150),
      "gridSize"   = grid_size_base,
      "curvature"  = 1/150.,
      "rightWidth" = W0/4,
      "leftWidth"  = W0/3
    ]),
    table([
      "length"     = 240,
      "gridSize"   = grid_size_base,
      "curvature"  = 0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = evalf(Pi/2*150),
      "gridSize"   = grid_size_base,
      "curvature"  = -1/150,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = 200,
      "gridSize"   = grid_size_base,
      "curvature"  = 0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = evalf(Pi*40),
      "gridSize"   = grid_size_base,
      "curvature"  = 1/40.,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = 480,
      "gridSize"   = grid_size_base,
      "curvature"  = 0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ]),
    table([
      "length"     = 10,
      "gridSize"   = 0.1,
      "curvature"  = 0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ])
  ])
]:

R0 := 100.:
road_data_init2 := [
  "theta0"   = 0,
  "s0"       = 0,
  "x0"       = 0,
  "y0"       = 0,
  "is_SAE"   = false,
  "segments" = Array([
    table([
      "length"     = evalf(2*Pi*R0),
      "gridSize"   = 0.1,
      "curvature"  = 1/R0,
      "rightWidth" = W0/2,
      "leftWidth"  = W0/2
    ])
  ])
]:
