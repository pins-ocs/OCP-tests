require "rake/clean"
%w(etc pry pp colorize fileutils nokogiri).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n$ (sudo) gem install #{gem}"
    exit 1
  end
end

class WrongTestDirError < Exception; end
class ModelDirNotFoundError < Exception; end

PATHLIB = `pins --path`

case RUBY_PLATFORM
when /darwin/
  OS       = :mac
  MAPLECMD = "/Library/Frameworks/Maple.framework/Versions/Current/bin/maple"
when /linux/
  OS       = :linux
  PREFIX   = '/usr/local'
  V1       = Dir.glob("/usr/local/maple*/bin/maple").map { |d| d }
  V2       = Dir.glob("/opt/maple*/bin/maple").map { |d| d }
  MAPLECMD = V1.push(V2).flatten.sort.last # da sistenare
when /mingw|mswin/
  OS       = :win
  PREFIX   = '/usr/local'
  MAPLECMD = '"' + Dir.glob("C:/Program Files*/Maple*/bin*/cmaple.exe").map { |d| d }.sort.last + '"'
else
  raise RuntimeError, "Unsupported OS: #{RUBY_PLATFORM}"
end

puts "MAPLE = #{MAPLECMD}".green

begin # definitions

  ROOT      = Rake.original_dir
  MODEL_DIR = "model"

  raise ModelDirNotFoundError unless (Dir.exist? "#{ROOT}/#{MODEL_DIR}")

  tmp_name = ROOT.split('/')[-1].match(/^\d*test\d*-(\w+)$/)

  raise WrongTestDirError unless tmp_name

  MODEL_NAME = tmp_name[1] # meglio non capitalizzare    ------ .capitalize # non usare ! se viene assegnato

  puts "Compiling model: #{MODEL_NAME}\n"

  MAPLE_SRC  = "#{ROOT}/#{MODEL_DIR}/#{MODEL_NAME}.mw"
  MATLAB_SRC = "#{ROOT}/generated_code/ocp-interfaces/Matlab"

  CLOBBER.include [
    "#{ROOT}/#{MODEL_DIR}/bvpOut",
    "#{ROOT}/generated_code"
  ]

rescue ModelDirNotFoundError
  warn "Cannot find ``model`` directory!\n".red
  #exit
rescue WrongTestDirError
  warn "Wrong directory!\nyou must start within a test-MODELNAME with MODELNAME only letters\nfound: #{ROOT.split('/')[-1]}".red
  #exit
rescue => e
  p e
  binding.pry
end

def check_maple_input( node )
  return true if node['style'] == "Maple Input"
  node.xpath('.//*').each do |link|
    return true if link['style'] == "Maple Input"
    return true if check_maple_input(link)
  end
  return false;
end

desc "Run the maple file and generate source".green
task :maple do
  mpl = File.basename MAPLE_SRC
  dir = File.dirname MAPLE_SRC
  cd dir do
    if File.exist?(MODEL_NAME+".mw")
      #
      # extract Maplet
      #
      File.open("#{MODEL_NAME}.mpl", "w") do |f|
        doc = Nokogiri::XML(File.read(MODEL_NAME+".mw"))
        doc.xpath('//Worksheet//Input//Text-field').each do |link|
          next unless check_maple_input( link )
          line = link.content.strip
          line += ';' if line[-1] != ';' # add missing ;
          break if line =~ /\#\s*quit\s*;?$/
          f.puts line
        end
      end
      #
      # execute maple
      #
      cmd = "#{MAPLECMD} -q -w 0 #{MODEL_NAME}.mpl"
      puts ">> #{cmd}".green
      sh cmd
      puts ">> source code generated".green
    else
      warn ">> #{MODEL_NAME}.mw does not exist!".red
    end
  end
end

desc "Build executable".green
task :main do
  ENV['PATH'] = ENV['PATH']+":"+PATHLIB
  dir = ROOT+'/generated_code'
  if File.exist?(dir) then
    cd dir do
      FileUtils.rm_rf "build"
      FileUtils.mkdir "build"
      cmd = "cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -Bbuild -S .";
      puts "Run: #{cmd}".yellow
      system(cmd);
      cmd = "ninja -C build install";
      puts "Run: #{cmd}".yellow
      system(cmd);
    end
  else
    puts "Missing: #{dir}".red
  end
end

desc "Run executable".green
task :run do
  ENV['PATH'] = ENV['PATH']+":"+PATHLIB
  dir = ROOT+'/generated_code'
  if File.exist?(dir) then
    cd dir do
      if OS != :win then
        cmd = "./bin/main";
      else
        cmd = ".\\bin\\main.exe";
      end
      puts "Run: #{cmd}".yellow
      system(cmd);
    end
  else
    puts "Missing: #{dir}".red
  end
end

task :all do
  Rake::Task[:clobber].invoke
  Rake::Task[:maple].invoke
  Rake::Task[:clean].invoke
  Rake::Task[:main].invoke
  Rake::Task[:run].invoke
end

task :matlab do
  cd ROOT+'/generated_code/ocp-interfaces/Matlab'
  FileUtils.rm_rf "build"
  FileUtils.mkdir_p "build"
  cd "build"
  sh "cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .."
  sh "cmake --build ."
  cd ".."
  cd ROOT
end

desc "Execute in MATLAB starting from shell".green
task :run_matlab do
  cd ROOT+'/generated_code/ocp-interfaces/Matlab' do
    case OS
    when :win
      cmd = "matlab";
    when :linux
      M   = Dir.glob("/usr/local/MATLAB/R*/bin/matlab").map { |d| d }
      cmd = M.sort.last;
    else
      M   = Dir.glob("/Applications/MATLAB_R*.app/bin/matlab").map { |d| d }
      cmd = M.sort.last;
    end
    cmd = "#{cmd} -nodesktop -nojvm -nodisplay -nosplash"
    puts "run: #{cmd}".yellow
    sh cmd
  end
end

desc "Remove all the ingnored files and reset the commit"
task :cleanup do
  #sh "git clean -d -x -f"
  sh "git reset --hard"
  sh "git submodule foreach --recursive git reset --hard"
  sh "git submodule foreach --recursive git clean -d -x -f"
  # estrae i sottomoduli alla corretta versione!
  sh "git submodule update --checkout --recursive"
end

desc "Clean generated tests".green
task :clean_test do
  puts "do clean_test".green
  Dir.glob("test-*/generated_code").each do |f|
    puts "remove #{f}".yellow
    FileUtils.rm_rf f
  end
end
