require "rake/clean"

%w(pry rbconfig colorize fileutils).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n$ (sudo) gem install #{gem}"
    exit 1
  end
end

host_os = RbConfig::CONFIG['host_os']
case host_os
when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
  OS = :windows
when /darwin|mac os/
  OS = :macosx
when /linux/
  OS = :linux
when /solaris|bsd/
  OS = :unix
else
  raise Error::WebDriverError, "unknown os: #{host_os.inspect}"
end

FileUtils.rm_rf "./collected_results/"
FileUtils.mkdir "./collected_results/"

def do_test(dir,idx,ffile,ffile2)
  name = dir.split("test-")[1];
  FileUtils.cd dir do
    puts "\n\n"
    system("rake clobber maple" );
    system("rake main" );
    puts "\n\n"
    begin
      FileUtils.cd "generated_code" do
        puts "\n\n"
        if OS == :windows then
          cmd = 'bin\main | ' + "perl -ne \"print \$_; print STDERR \$_;\" 2> iterations.txt" ;
        else
          cmd = "./bin/main | tee iterations.txt";
        end
        puts "EXECUTE: #{cmd}\n"
        system( cmd );
        puts "\n\n"
      end
    rescue => e
      p e
      ffile.puts name
      #binding.pry
    end
  end
  begin
    ff   = "#{dir}/generated_code/iterations.txt";
    iter = -1;
    if File.exist? "#{dir}/generated_code/data/#{name}_OCP_result.txt" then
      gg = "./collected_results/#{'%03d' % idx}_#{name}_iterations.txt";
      File.open(ff).grep(/iteration\s+=\s+(\d+)/){ |n| iter = $1; }
    else
      gg = "./collected_results/#{'%03d' % idx}_#{name}_iterations_NO_OK.txt";
    end
    FileUtils.cp ff, gg if File.exist? ff
    ffile2.puts " iteration = " + ("%-5s" % iter) + " " + name
    ffile2.flush
  rescue => e
    p e
    ffile.puts name
    #binding.pry
  end
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
ocps_path  = '.'
tests_dirs = %W(
  test-AlpRider
  test-BertolazziCorsoExample1
  test-Brake
  test-CNOC
  test-Chachuat3_44
  test-CristianiMartinon
  test-GoddardRocket
  test-HangGlider
  test-HangingChain
  test-ICLOCS_Catalyst
  test-ICLOCS_MinimumFuelOrbitRaising
  test-ICLOCS_StirredTank
  test-ICLOCS_TwoLinkRobotArm
  test-MinimumEnergyProblem
  test-ROSS_Fuller
  test-SoundingRocket
  test-TwoPhaseSchwartz
  test-TwoStageCSTR
  test-Underwater
)

# test-StirredTank non funziona

File.open("./collected_results/000_list2.txt","w") do |file|
  file.puts banner
  tests_dirs.each_with_index do |f,i|
    puts "#{i}: #{f}";
    file.puts "#{i}: #{f}";
  end
end

puts "Start loop on tests"
ffile  = File.open("./collected_results/000_list_failed2.txt","w")
ffile2 = File.open("./collected_results/000_iterations2.txt","w")
tests_dirs.each_with_index do |d,idx|
  puts "\n"
  puts "-------------------------------------------------------------------------------"
  puts "Testing: #{d}"
  do_test(d,idx+1,ffile,ffile2) ;
  puts "\n\n#{d}\n\n\n"
end
ffile.close()
ffile2.close()
