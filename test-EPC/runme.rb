#!/usr/bin/env ruby 
# state_offline_optimization.rb

# Created by Carlos Maximiliano Giorgio Bort on 2012-11-16.
# Copyright (c) 2012 University of Trento. All rights reserved.

require "pry"
require File.expand_path('../support/units', __FILE__)
require File.expand_path('../lib/EPC_ffi', __FILE__)

CONVERGENCE = { :NOT_CONVERGED => 0, :OK => 1}




# ________________________________________________                                               
#  _____             __ _                      
# / ____|           / _(_)                     
#| |     ___  _ __ | |_ _  __ _ _   _ _ __ ___ 
#| |    / _ \| '_ \|  _| |/ _` | | | | '__/ _ \
#| |___| (_) | | | | | | | (_| | |_| | | |  __/
# \_____\___/|_| |_|_| |_|\__, |\__,_|_|  \___|
#                          __/ |               
#                         |___/                
# ________________________________________________                                              
params = { S: 1500, F: 1000}
params[:machine_data] = {
  :s_max  => 1500, # (RPM)     Maximum spindle speed
  :s_min  => 100,  # (RPM)     Minimum spindle speed
  :s_a    => 1000, # (RPM/s^2) Acceleration of the spindle
  :f_max  => 10000,# (mm/min)  Maximum feed rate
  :f_min  => 0,    # (mm/min)  Minimum feed rate
  :f_a    => 0.4,  # (m/s^2)   Acceleration of the linear axes
  :f_d    => 0.4,  # (m/s^2)   Decceleration of the linear axes
  :pc_max => 11000, # (watt)  Maximum power at spindle
  :tc_max => 57.3   # (N m)   Maximum torque at spindle
}

params[:tool_data] = {
  :type          => :cylinder,
  :length        => 69.8,     # (mm) tool length
  :radius        => 31.5,     # (mm) tool radius
  :helix_angle   => 0.00001,  # (rad) helix angle   
  :fillet_radius => 1.2,      # (mm)
  :teeth         => 5,        # (/)
  :inertia       => 636172.5, # (mm^4) moment of inertia
  :young_mod     => 500.0,    # (MPa) Young's modulus     
  :wear_data     => { :n => 0.17,
                      :a => 0.17,
                      :b => 0.37 }
}
params[:workpiece_data] = { us: 0.75 }

max_feed_acc  = params[:machine_data][:f_a]*UNITS::M/(UNITS::S**2)
min_feed      = (params[:machine_data][:f_min]+10)*UNITS::MM/UNITS::MIN
max_feed      = params[:machine_data][:f_max]*UNITS::MM/UNITS::MIN
max_omega_acc = params[:machine_data][:s_a]*UNITS::RPM/UNITS::S
min_omega     = params[:machine_data][:s_min]*UNITS::RPM
max_omega     = params[:machine_data][:s_max]*UNITS::RPM
zero_feed     = min_feed*10.0
maxFeedRate   = params[:machine_data][:f_max]*UNITS::MM/UNITS::MIN



# ________________________________________________
#  _____ _                 _       _             
# / ____(_)               | |     | |            
#| (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __ 
# \___ \| | '_ ` _ \| | | | |/ _` | __/ _ \| '__|
# ____) | | | | | | | |_| | | (_| | || (_) | |   
#|_____/|_|_| |_| |_|\__,_|_|\__,_|\__\___/|_|   
# ________________________________________________                                               

# Look for dumped block in dumps folder
parsed_data = {
  :nblk        => [],
  :blocks      => [],
  :zeta_blocks => {
    :zeta          => [],
    :cross_section => [],
    :iblk          => [],
    :init_blk      => {}
  }
}
cumul_aux = 0

Dir["./dumps/*"].each do |dump|
  dump =~ /([0-9]+)/
  nblk = $1
  next if nblk.nil?
  
  dump      =~ /([^0-9]+)/
  dump_file = $1
  dump_file.insert(-1, "#{nblk}.dump")
  
  block = {}
  index = 0
  unless parsed_data[:nblk].include? nblk
    dump_file_zeta= dump_file.dup
    dump_file_tq  = dump_file.dup
    dump_file_fx  = dump_file.dup
    dump_file_fy  = dump_file.dup
    dump_file_fz  = dump_file.dup
    dump_file_sld = dump_file.dup
    dump_file_zeta.insert(-6, ".zeta")
    dump_file_tq.insert(  -6, ".Tq")
    dump_file_fx.insert(  -6, ".Fx")
    dump_file_fy.insert(  -6, ".Fy")
    dump_file_fz.insert(  -6, ".Fz")
    dump_file_sld.insert( -6, ".sld")
    
    block[:zeta] = File.open(dump_file_zeta, "rb") { |file| Marshal.load(file) }
    block[:mrr]  = File.open(     dump_file, "rb") { |file| Marshal.load(file) }
    block[:Tq]   = File.open(  dump_file_tq, "rb") { |file| Marshal.load(file) } 
    block[:Fx]   = File.open(  dump_file_fx, "rb") { |file| Marshal.load(file) } 
    block[:Fy]   = File.open(  dump_file_fy, "rb") { |file| Marshal.load(file) }
    block[:Fz]   = File.open(  dump_file_fz, "rb") { |file| Marshal.load(file) }
    block[:sld]  = File.open( dump_file_sld, "rb") { |file| Marshal.load(file) }
    
    block[:zeta].collect!{ |s| (cumul_aux+s).to_f }
    
    parsed_data[:blocks] << block
    parsed_data[:nblk]   << nblk
    
    parsed_data[:zeta_blocks][:zeta].push(*block[:zeta])
    parsed_data[:zeta_blocks][:cross_section].push(*block[:mrr])
    parsed_data[:zeta_blocks][:iblk].push(*[index]*block[:zeta].size)
    parsed_data[:zeta_blocks][:init_blk][block[:N]] = cumul_aux
    
    cumul_aux = block[:zeta].last
    last_mrr  = block[:mrr].last
    
    index += 1
  end # unless parsed_data...
end # Dir[].each...

# interpolate the cross_section
spline_cross_section = EPC::Spline.new 'pchip'
parsed_data[:zeta_blocks][:zeta].each_with_index do |z, i|
  spline_cross_section.push_back( z, parsed_data[:zeta_blocks][:cross_section][i] )
end
spline_cross_section.build





def create_segment_from(block)
  return segment = {
    :MinFeedRate                 => [min_feed, params[:machine_data][:f_min]*UNITS::MM/UNITS::MIN].max,
    :MaxFeedRate                 => maxFeedRate,

    :MinSpindleRate              => params[:machine_data][:s_min]*UNITS::RPM,
    :MaxSpindleRate              => params[:machine_data][:s_max]*UNITS::RPM,

    :InitialEstimatedSpindleRate => params[:machine_data][:s_min]*UNITS::RPM,
    :FinalEstimatedSpindleRate   => params[:machine_data][:s_max]*UNITS::RPM,
    :NominalEstimatedSpindleRate => (params[:S] || params[:machine_data][:s_min])*UNITS::RPM,

    :InitialEstimatedFeedRate    => zero_feed,
    :FinalEstimatedFeedRate      => zero_feed,
    :NominalEstimatedFeedRate    => (block[:type] == :rapid ? maxFeedRate : params[:F]*UNITS::MM/UNITS::MIN),
  
    :ssStep                      => (block[:zeta][1] - block[:zeta][0])/10.0,
  
    :PathPosition                => block[:zeta].dup,
    :CrossSection                => block[:mrr].dup, 
  }
end



# ________________________________________________
#  ____        _   _           _              
# / __ \      | | (_)         (_)             
#| |  | |_ __ | |_ _ _ __ ___  _ _______ _ __ 
#| |  | | '_ \| __| | '_ ` _ \| |_  / _ \ '__|
#| |__| | |_) | |_| | | | | | | |/ /  __/ |   
# \____/| .__/ \__|_|_| |_| |_|_/___\___|_|   
#       | |                                   
#       |_|                                   
# ________________________________________________

# Initialize the offline optimizator
opt = EPC::OCPSolver.new

nominal_omega = 0
parsed_data[:blocks].each do |block|
  nominal_omega = params[:S] || params[:machine_data][:s_max]-100
  break if params[:S]
end
nominal_omega *=UNITS::RPM
nominal_omega =1000*UNITS::RPM

opt.data = {
  # Level of message
  :InfoLevel => 4,
  
  # manages solver
  :Solver => {
    :max_iter  => 500,
    :tolerance => 1e-6,
  },

  # Boundary Conditions
  :BoundaryConditions => {
    :initial_f     => true,
    :initial_omega => true,
    :final_f       => false,
    :final_omega   => false,
  },

  # Model Parameters
  :Parameters => {
    :Pc_max                => params[:machine_data][:pc_max]*UNITS::WATT,
    :Tc_max                => params[:machine_data][:tc_max]*UNITS::NM,
    :a                     => params[:tool_data][:wear_data][:a],
    :b                     => params[:tool_data][:wear_data][:b],
    
    :eta                   => 0.9, # rendimento, numero puro
    :f_f                   => min_feed,
    :f_i                   => zero_feed,
    :max_feed              => max_feed,
    :max_feed_acc          => max_feed_acc,
    :max_omega             => max_omega,
    :max_omega_acc         => max_omega_acc,
    :min_feed              => min_feed,
    :min_omega             => min_omega,
    :n                     => params[:tool_data][:wear_data][:n],
    :nt                    => params[:tool_data][:teeth], # number of teeth
    :omega_f               => nominal_omega,
    :omega_i               => nominal_omega,
    :r                     => params[:tool_data][:radius]*UNITS::MM,
    :rf                    => params[:tool_data][:fillet_radius]*UNITS::MM,
    :us                    => params[:workpiece_data][:us] * UNITS::WATT * UNITS::S / UNITS::MM**3, # specific energy
    :vOmegaControlMaxValue =>  max_omega_acc,
    :vOmegaControlMinValue => -max_omega_acc,
    :vfControlMaxValue     =>  max_feed_acc,
    :vfControlMinValue     => -max_feed_acc,
    :wT_min                => 1, # minimum time target
    :wT_Ra                 => 1, # minimum roughness target
    :wT_tw                 => 1, # minimum tool wear
    :wT_en                 => 1, # minimum energy consumption
    :wi                    => 0, # activate least square initial conditions
    
    :omegaRange_weight     => 1e-4,
    :CuttingTorque_weight  => 1e-4,
  },

  # Controls
  :Controls => {
    :vfControl => {
      :type      => Mechatronix::U_COS_LOGARITHMIC,
      :epsilon   => 0.01,
      :tolerance => 0.01,
    },
    :vOmegaControl => {
      :type      => Mechatronix::U_COS_LOGARITHMIC,
      :epsilon   => 0.01,
      :tolerance => 0.01,
    },
  }
}

opt.data[:MappedObjects] = {
  # SignRegularizedWithErf
  :on_off => { :epsilon => 1E-9, :h => 1E2 },
}

opt.data[:Constraints] = {
  # Constraint1D

  # Barrier1DGreaterThan
  :CuttingTorqueLimit => {
    :subType   => Barrier1D::LOG_EXP,
    :epsilon   => 0.01,
    :tolerance => opt.data[:Parameters][:Tc_max]*0.1,
  },
  # Barrier1DGreaterThan
  :CuttingPowerLimit => {
    :subType   => Barrier1D::LOG_EXP,
    :weight    => 1,
    :epsilon   => 0.01,
    :tolerance => opt.data[:Parameters][:Pc_max]*0.01,
  },
  # Barrier1DInterval
  :fRange => {
    :subType   => Barrier1D::LOG_EXP,
    :epsilon   => 0.001,
    :tolerance => (max_feed - min_feed) * 0.01,
    :min       => min_feed,
    :max       => max_feed,
  },
  # Barrier1DInterval
  :omegaRange => {
    :subType   => Barrier1D::LOG_EXP,
    :epsilon   => 0.01,
    :tolerance => (max_omega - min_omega) * 0.01,
    :min       => min_omega,
    :max       => max_omega,
  },
  # Penalty1DGreaterThan
  :FeedRateLimit => {
    :subType   => Penalty1D::SMOOTH,
    :epsilon   => 0.1,
    :tolerance => 0.01,
  }
  
  # Constraint2D
  # NONE
}



# Performs the offline optimization
# Preare the segments for the OCP
segs = []

parsed_data[:blocks].each_with_index do |block, indx|
  segment = {
    :MinFeedRate                 => [min_feed, params[:machine_data][:f_min]*UNITS::MM/UNITS::MIN].max,
    :MaxFeedRate                 => maxFeedRate,

    :MinSpindleRate              => params[:machine_data][:s_min]*UNITS::RPM,
    :MaxSpindleRate              => params[:machine_data][:s_max]*UNITS::RPM,

    :InitialEstimatedSpindleRate => params[:machine_data][:s_min]*UNITS::RPM,
    :FinalEstimatedSpindleRate   => params[:machine_data][:s_max]*UNITS::RPM,
    :NominalEstimatedSpindleRate => (params[:S] || params[:machine_data][:s_min])*UNITS::RPM,

    :InitialEstimatedFeedRate    => zero_feed,
    :FinalEstimatedFeedRate      => zero_feed,
    :NominalEstimatedFeedRate    => (block[:type] == :rapid ? maxFeedRate : params[:F]*UNITS::MM/UNITS::MIN),

    :ssStep                      => (block[:zeta][1] - block[:zeta][0])/10.0,

    :PathPosition                => block[:zeta].dup,
    :CrossSection                => block[:mrr].dup, 
  }
  segs << segment
end # @params.parsed.blocks.each_with_index ...

# Load segments into the OCP and solve the problem
opt.data[:ToolPath1D] = { :segments => segs }

opt_result = opt.solve
#p opt_result.keys

# Post processing
raise OptimizationError, opt_result[:error] if opt_result.has_key? :error

opt.write_ocp_solution("data/xoptima_solution.txt")

puts "-- Optimised cut lasting #{opt_result[:data][:t].last.round(2)} s"

