mesh_step = 0.1 
mechatronix do |data|
    # User defined classes initialization
    # Read tabulated file data
    # p "Start reading data from file"
    table = Utils::read_from_table(File.expand_path('../trajectory_data.txt', __FILE__))
    puts table["abscissa"].size 
    
    # p "Data read correctly and trajectory built"
    len = table["abscissa"][-1]-table["abscissa"][0]
    puts "s0 = #{table["abscissa"][0]}, s1 = #{table["abscissa"][-1]}, len = #{len}"
    npts = (len/mesh_step).round(0)
    puts " mesh: number of points = #{npts}, mesh step = #{mesh_step} " 
    
    data.Trajectory = 
    { :x0            => 0.0,
      :y0            => 0.0,
      :theta0        => 0.0,
      :abscissa_step => mesh_step,
      :mesh          => {:segments=>[{:length=>1,:n=>npts},]}, #[[length=len,n=1000]],
      #:absolute_length => len,
      :abscissa  => table["abscissa"],
      :curvature => table["curvature"],
    }
end
