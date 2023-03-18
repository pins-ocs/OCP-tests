#!/usr/bin/env pins
#-----------------------------------------------------------------------#
#  file: BangBangFclip_pins_run.rb                                      #
#                                                                       #
#  version: 1.0   date 20/3/2023                                        #
#                                                                       #
#  Copyright (C) 2023                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#

require 'mechatronix'

# Set the model name
problem_name = "BangBangFclip"
problem_lib  = "lib/lib#{problem_name}.#{Mechatronix::DYLIB_EXT}"

# Compile the scripts, unless the library already exists
# the command line flag '-f' forces recompilation
# the command line flag '-b' only performs compilation and skips solution
if ! File.exist?(problem_lib) ||
     ARGV.include?('-f')      ||
     ARGV.include?('-b')      ||
     ARGV.include?('-main')  then
  require "build"
  compiler = MXBuilder.new(problem_name)
  compiler.build
  compiler.standalone if ARGV.include?('-main')
  exit if ARGV.include?('-b')
end

require './data/BangBangFclip_Data.rb'

# If requested, enable the Doctor
Mechatronix.content.Doctor = ARGV.include?('-d')

# Link the library
ocp = Mechatronix::OCPSolver.new problem_lib

# Setup the solver
ocp.setup

# Guess
ocp.guess

# Calculate the OCP solution. Result is into ocp.ocp_solution
ocp.solve

# Write results
unless ocp.ocp_solution[:error] then
  if ocp.ocp_solution[:converged] then
    puts "Lagrange          = #{ocp.ocp_solution[:target][:lagrange]}"
    puts "Mayer             = #{ocp.ocp_solution[:target][:mayer]}"
    puts "Penalties         = #{ocp.ocp_solution[:target][:penalties]}"
    puts "Control penalties = #{ocp.ocp_solution[:target][:control_penalties]}"
    if ocp.ocp_solution[:parameters] then
      puts "Optimization parameters: #{ocp.ocp_solution[:parameters]}"
    end
    puts "\nSaving solution file: data/#{problem_name}_OCP_result.txt"
    ocp.write_ocp_solution("data/#{problem_name}_OCP_result.txt")
  else
    puts "\nSaving solution file: data/#{problem_name}_OCP_result_NOT_CONVERGED.txt"
    ocp.write_ocp_solution("data/#{problem_name}_OCP_result_NOT_CONVERGED.txt")
    puts "Solver Message:"
    puts ocp.ocp_solution[:solver_message]
  end
else
  p "ERROR: output file not generated"
  puts ocp.ocp_solution[:error]
end

# If requested, print out Doctor's diagnosis
if ARGV.include?('-d') or Mechatronix.content.Doctor then
  d = ocp.ocp_solution[:diagnosis]
  puts "\nDOCTOR'S DIAGNOSIS\n#{'=' * 79}"
  puts "- INVERSE OF CONDITION NUMBER (the smaller, the more ill-conditioned):"
  puts "  Norm 1        = #{d[:inverse_of_conditon_number][:norm_1]}"
  puts "  Norm Infinity = #{d[:inverse_of_conditon_number][:norm_inf]}"
  #ctrls = d[:controls]
  #if ctrls && ctrls.length > 0 then
  #  ncrtl = ctrls.length
  #  ncell = ctrls[0].length
  #  (0..ncell-1).each { |nc|
  #    puts "  cell[#{nc}] (rcond) = #{ctrls[ncrtl-1][nc]/ctrls[0][nc]}"
  #  }
  #end
  #cells  = d[:cells]
  #ncells = cells.length
  #cells.each_with_index do |c,idx|
  #  puts "  cell[#{idx}] (X-rcond) = #{c[:X_singular_values][-1]/c[:X_singular_values][0]}"
  #  puts "  cell[#{idx}] (L-rcond) = #{c[:LAMBDA_singular_values][-1]/c[:LAMBDA_singular_values][0]}"
  #  puts "  cell[#{idx}] (rcond)   = #{c[:ratio_singular_value]}"
  #end
  puts "  bc = #{d[:bc]}"
  puts "#{'=' * 79}"
end

figlet "All Done Folks!"

# EOF
