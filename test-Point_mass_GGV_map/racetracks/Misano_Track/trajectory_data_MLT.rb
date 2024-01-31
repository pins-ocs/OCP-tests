mesh_step = 1
mechatronix do |data|
    # User defined classes initialization
    # Read tabulated file data
    # p "Start reading data from file"
    vars, table = Utils::read_from_table(File.expand_path('../road_Misano_MLT.txt', __FILE__))
    
    puts table["abscissa"].size
    
    # p "Data read correctly and trajectory built"
    len = table["abscissa"][-1]-table["abscissa"][0]
    puts "s0 = #{table["abscissa"][0]}, s1 = #{table["abscissa"][-1]}, len = #{len}"
    #npts = (len/mesh_step).round(0)
    #puts " mesh: number of points = #{npts}, mesh step = #{mesh_step} "
    
    #nodes = (0..npts-1).to_a
    mesh_step_fine_top    = 0.025  # [m] fine mesh step
    mesh_step_fine_interm = 0.1   # [m] intermediate mesh step
    road_fine_top_end     = 5     # [m] distance from the origin at which the road portion discretized with the fine mesh ends
    road_fine_interm_end  = 7     # [m] distance from the origin at which the road portion discretized with the interm mesh ends
    
    nodes_fine_top    = 0.step(road_fine_top_end-mesh_step_fine_top,mesh_step_fine_top).to_a
    nodes_fine_interm = road_fine_top_end.step(road_fine_interm_end-mesh_step_fine_interm,mesh_step_fine_interm).to_a
    nodes             = nodes_fine_top.concat(nodes_fine_interm).concat((road_fine_interm_end..len).to_a)
            
    data.Trajectory = 
    { :x0            =>  table["X"][0],
      :y0            =>  table["Y"][0],
      :theta0        =>  table["theta"][0],
      :abscissa_step =>  mesh_step,
      #:mesh          => {:segments=>[{:length=>1,:n=>npts},]},
      :mesh          => {:nodes=>nodes},
      :abscissa      => table["abscissa"],
      :curvature     => table["curvature"],
    }
end