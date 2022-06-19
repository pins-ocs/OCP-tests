file1 = "circuit-fiorano_map_ADMA_ref_traguardo_v2_rebuilt.txt"
file2 = "circuit-Mugello_kerbs_tuned_rebuilt.txt"
puts "Read circuit: #{file1}"
Circuit_Vars, Circuit_Table = Utils::read_from_table(File.expand_path(file1, File.dirname(__FILE__)))
len       = Circuit_Table["abscissa"][-1]-Circuit_Table["abscissa"][0]
mesh_step = 0.5;
npts      = (len/mesh_step).round(0)
mechatronix do |data|
  data.Trajectory = {
    :x0            => Circuit_Vars[:x0],
    :y0            => Circuit_Vars[:y0],
    :theta0        => Circuit_Vars[:theta0],
    :abscissa_step => mesh_step,
    :closed        => true,
    :x             => Circuit_Table["x_mid_line"],
    :y             => Circuit_Table["y_mid_line"],
    :theta         => Circuit_Table["dir_mid_line"],

    :abscissa      => Circuit_Table["abscissa"],
    #:curvature     => Circuit_Table["curvature"],

    :mesh          => {:segments=>[{:length=>len,:n=>npts}]}
  }
end

# res = ""
# Circuit_Table["abscissa"].each_with_index do |a,idx|
#   res += "#{a}, "
#   res += "...\n" if (idx%10) == 0
# end
# puts "abscissa = [ #{res} ];"
# res = ""
# Circuit_Table["curvature"].each_with_index do |a,idx|
#   res += "#{a}, "
#   res += "...\n" if (idx%10) == 0
# end
# puts "curvature = [ #{res} ];"
