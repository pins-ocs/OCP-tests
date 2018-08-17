#!/usr/bin/env pins
 #--------------------------------------------------------------------------#
 #  file: Train_run.rb                                                      #
 #                                                                          #
 #  version: 1.0   date 31/3/2014                                           #
 #                                                                          #
 #  Copyright (C) 2014                                                      #
 #                                                                          #
 #      Enrico Bertolazzi and Francesco Biral and Paolo Bosetti             #
 #      Dipartimento di Ingegneria Industriale                              #
 #      Universita` degli Studi di Trento                                   #
 #      Via Mesiano 77, I-38050 Trento, Italy                               #
 #      email: enrico.bertolazzi@unitn.it                                   #
 #             francesco.biral@unitn.it                                     #
 #             paolo.bosetti@unitn.it                                       #
 #--------------------------------------------------------------------------#

require 'mechatronix'
require './data/Train_Data.rb'


# Set the model name
problem_name = "Train"

# Compile the scripts, unless the library already exists
# the command line flag '-f' forces recompilation
if ! File.exist?("lib/lib#{problem_name}.dylib") || ARGV[0] == '-f' then
  require "build"
  MXBuilder.new(problem_name).build
end

# Link the library
ocp = Mechatronix::OCPSolver.new "lib/lib#{problem_name}.dylib"

ocp.data.InfoLevel = 0
pa = Mechatronix::ParametricAnalysis.new
pa.solver = ocp
pa.parameters = {:alpha => [0.2, 0.3, 0.4], :beta => [0.13, 0.14, 0.15]}

i = 0
pa.each do |solver, combination|
  desc =  "alpha = #{solver.data.Parameters[:alpha]}, beta = #{solver.data.Parameters[:beta]}"
  solver.solve
  solver.write_ocp_solution("data/#{problem_name}_OCP_result_#{i}.txt", desc)
  i += 1
end

p pa.combinations


# # Setup the solver
# ocp.setup
# 
# # Calculate the OCP solution. Result is into ocp.ocp_solution
# ocp.solve
# 
# # Write results
# unless ocp.ocp_solution[:Error] then
#   ocp.write_ocp_solution("data/#{problem_name}_OCP_result.txt")
#   figlet "All Done Folks!"
# else
#   figlet "Solver crash"
# end
# 
# 
# # EOF
