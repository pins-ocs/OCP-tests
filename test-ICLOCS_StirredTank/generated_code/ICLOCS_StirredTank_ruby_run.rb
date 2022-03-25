#!/usr/bin/env ruby
#-----------------------------------------------------------------------#
#  file: ICLOCS_StirredTank_ruby_run.rb                                 #
#                                                                       #
#  version: 1.0   date 25/3/2022                                        #
#                                                                       #
#  Copyright (C) 2022                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#


require './ocp-interfaces/Ruby/ICLOCS_StirredTank_ffi.rb'
require './data/ICLOCS_StirredTank_Data.rb'

ocp = ICLOCS_StirredTank::OCPSolver.new

begin
  res = ocp.solve
  if res[:converged] then
    ocp.write_ocp_solution("data/ICLOCS_StirredTank_OCP_result.txt")
  else
    ocp.write_ocp_solution("data/ICLOCS_StirredTank_OCP_result_NOT_CONVERGED.txt")
  end
rescue RuntimeError => e
  puts e
  ocp.write_ocp_solution("data/ICLOCS_StirredTank_OCP_result_NOT_CONVERGED.txt")
rescue => e
  puts e.message
  puts "Trace"
  e.backtrace.each do |t|
    puts t
  end
rescue
  puts "Unknown error!"
end

if ARGV.include? "-g" then
  dg = Dgraph.new
  dg.set_fields %w(z x v)
  dg.plot "z", "x"
  dg.plot "z", "v"
  res[:data][0].each_with_index do |z,i|
    dg << {z:z, x:res[:data][1][i], v:res[:data][2][i]}
  end
  dg.close
end

puts "All Done Folks!"

# EOF
