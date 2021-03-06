
def do_test(dir)
  system("cd #{dir}; rake clobber maple; rake clean main; ./bin/main | tee iterations.txt; cd .." ) ;
end

#List of test that are excluded from


##
#figlet "OCP Tests"
#figlet "Checker"
banner =
"==============================================================================\n" +
"     TEST OPTIMAL BENCHMARK CONTROL PROBLEMS                                  \n"+
"==============================================================================\n" 

puts "#{banner}"

## Get all test directries in folder
ocps_path = '.'
tests_dirs = []
excluded_tests = []
Dir.entries(ocps_path).select {|f|
  if File.directory?(f) && f != '.' &&  f != '..' && !(f.include? "-no-test") then
    tests_dirs << f
  end
  if f.include? "-no-test" then
    excluded_tests << f
  end
}

#files = Dir.entries(ocps_path)

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
