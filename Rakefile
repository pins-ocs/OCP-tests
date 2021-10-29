require "rake/clean"
%w(pry colorize).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n $ (sudo) gem install #{gem}"
    exit 1
  end
end

class WrongTestDirError < Exception; end
class ModelDirNotFoundError < Exception; end

PATHLIB = `pins --path`

case RUBY_PLATFORM

when /darwin/

  OS         = :mac
  WHICH_CMD  = 'which'
  DYL_EXT    = 'dylib'
  #MAPLECMD   = `ls -1 /Applications/Maple*/maple | tail -1`.gsub(' ','\ ').chomp
  MAPLECMD   = "/Library/Frameworks/Maple.framework/Versions/Current/bin/maple"

when /linux/

  OS         = :linux
  WHICH_CMD  = 'which'
  DYL_EXT    = 'so'
  PREFIX     = '/usr/local'
  V1         = Dir.glob("/usr/local/maple*/bin/maple").map { |d| d }
  V2         = Dir.glob("/opt/maple*/bin/maple").map { |d| d }
  MAPLECMD   = V1.push(V2).flatten.sort.last # da sistenare

when /mingw|mswin/

  OS        = :win
  WHICH_CMD = 'where'
  DYL_EXT   = 'dll'
  PREFIX    = '/usr/local'
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

  MAPLET   = "#{ROOT}/#{MODEL_DIR}/#{MODEL_NAME}.mpl"
  SRC_DIR  = "#{ROOT}/ocp-src"
  MAIN_DIR = "#{ROOT}/ocp-interfaces/cpp"
  LIB_DIR  = "#{ROOT}/lib"
  BIN_DIR  = "#{ROOT}/bin"

  CLOBBER.include [
    "#{ROOT}/{data,lib,bin}/*",
    "#{ROOT}/ocp-*",
    "#{ROOT}/*_run*.rb",
    "#{ROOT}/#{MODEL_DIR}/bvpOut"
  ]

  include FileUtils
  # verbose(true)
  mkdir_p LIB_DIR
  mkdir_p BIN_DIR
rescue ModelDirNotFoundError
  warn "Cannot find ``model`` directory!\n".red
  exit
rescue WrongTestDirError
  warn "Wrong directory!\nyou must start within a test-MODELNAME with MODELNAME only letters\nfound: #{ROOT.split('/')[-1]}".red
  exit
rescue => e
  p e
  require 'pry'
  binding.pry
end

desc "Run the mpl file and generate source".green
task :maple do
  mpl = File.basename MAPLET
  dir = File.dirname MAPLET
  if File.exist?(MAPLET)
    cd dir do
      sh "#{MAPLECMD} #{mpl}"
    end
    puts ">> source code generated".green
  else
    warn ">> #{MAPLET} does not exist!".red
  end
end

desc "Build executable".green
task :main do
  ENV['PATH'] = ENV['PATH']+PATHLIB
  cd ROOT
  cmd = "pins #{MODEL_NAME}_pins_run.rb -f -b -main";
  puts "Run: #{cmd}".yellow
  system(cmd);
end

desc "Run executable".green
task :run do
  ENV['PATH'] = ENV['PATH']+PATHLIB
  cd ROOT
  cmd = "pins #{MODEL_NAME}_pins_run.rb";
  puts "Run: #{cmd}".yellow
  system(cmd);
end

task :all do
  puts "\n\n\nCLOBBER\n\n".green
  Rake::Task[:clobber].invoke
  puts "\n\nMAPLE\n\n".green
  Rake::Task[:maple].invoke
  puts "\n\nCLEAN\n\n".green
  Rake::Task[:clean].invoke
  puts "\n\nMAIN\n\n".green
  Rake::Task[:main].invoke
  puts "\n\nRUN\n\n".green
  Rake::Task[:run].invoke
end
