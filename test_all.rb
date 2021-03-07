require 'fileutils'

FileUtils.rm_rf "./collected_results/"
FileUtils.mkdir "./collected_results/"

def do_test(dir)
  name = dir.split("test-")[1];
  puts "\n\n"
  FileUtils.cd dir
  system("rake clobber maple" );
  puts "\n\n"
  system("pins #{name}_pins_run.rb -f -b -main" );
  puts "\n\n"
  case RUBY_PLATFORM
  when /(mingw|win)/
    cmd = "bin\\main"
  else
    cmd = "./bin/main"
  end
  system("#{cmd} | perl -ne \"print \$_; print STDERR \$_;\" 2>  iterations.txt" );
  puts "\n\n"
  FileUtils.cd ".."
  ff   = "#{dir}/iterations.txt";
  if File.exist? "#{dir}/data/#{name}_OCP_result.txt" then
    gg = "./collected_results/#{name}_iterations.txt";
  else
    gg = "./collected_results/#{name}_iterations_NO_OK.txt";    
  end
  FileUtils.cp ff, gg if File.exist? ff
end

#List of test that are excluded from
##
#figlet "OCP Tests"
#figlet "Checker"
banner =
"==============================================================================\n" +
"                 TEST OPTIMAL BENCHMARK CONTROL PROBLEMS                      \n"+
"==============================================================================\n" 

puts "#{banner}"

## Get all test directries in folder
ocps_path = '.'
tests_dirs = []
excluded_tests = []
Dir.entries(ocps_path).select {|f|
  if File.directory?(f) && 
     f != '.' &&  f != '..' && 
     (f.include? "test-") && 
     !(f.include? "-no-test") then
    tests_dirs << f
  end
  if f.include? "-no-test" then
    excluded_tests << f
  end
}

#ordina directory
tests_dirs.sort!

tests_dirs.each_with_index { |f,i|
  puts "#{i}: #{f}"
}
excluded_tests.each_with_index { |f,i|
  puts "#{i}: #{f}"
}

puts "Start loop on tests"
tests_dirs.each do |d|
  puts "\n"
  puts "-------------------------------------------------------------------------------"
  puts "Testing: #{d}"
  do_test(d) ;
  puts "\n\n#{d}\n\n\n"
end
