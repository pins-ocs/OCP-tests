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

CXXFLAGS   = `pins --cppflags`
CFLAGS     = `pins --cflags`
LFLAGS     = `pins --lflags`
LIBS       = `pins --libs`
INCLUDES   = `pins --includes`
FRAMEWORKS = `pins --frameworks`
PATHLIB    = `pins --path`

case RUBY_PLATFORM

when /darwin/

  OS         = :mac
  WHICH_CMD  = 'which'
  DYL_EXT    = 'dylib'
  PREFIX     = ''
  VS_VERSION = ''
  VS_ARCH    = ''
  MAPLECMD   = `ls -1 /Applications/Maple*/maple | tail -1`.gsub(' ','\ ').chomp

when /linux/

  OS         = :linux
  WHICH_CMD  = 'which'
  DYL_EXT    = 'so'
  PREFIX     = '/usr/local'
  VS_VERSION = ''
  VS_ARCH    = ''
  MAPLECMD   = "maple" # da sistenare

when /mingw|mswin/

  OS        = :win
  WHICH_CMD = 'where'
  DYL_EXT   = 'dll'
  PREFIX    = '/usr/local'

  # in windows use visual studio compiler, check version
  tmp = `#{WHICH_CMD} cl.exe`.lines.first
  case tmp
  when /2017/
    VS_VERSION = '2017'
  when /16\.0/
    VS_VERSION = '2017'
  when /14\.0/
    VS_VERSION = '2015'
  when /12\.0/
    VS_VERSION = '2013'
  when /10\.0/
    VS_VERSION = '2010'
  else
    raise RuntimeError, "Unsupported VisualStudio version"
  end
  # check architecture
  case tmp
  when /x64\\cl\.exe/
    VS_ARCH = 'x64'
  when /amd64\\cl\.exe/
    VS_ARCH = 'x64'
  when /bin\\cl\.exe/
    VS_ARCH = 'x86'
  else
    raise RuntimeError, "Cannot determine architecture for Visual Studio #{VS_VERSION}".red
  end

  MAPLECMD = "cmaple.exe" # da sistenare

else
  raise RuntimeError, "Unsupported OS: #{RUBY_PLATFORM}"
end


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
  SOURCES  = FileList["#{SRC_DIR}/*.{c,cc}"]
  HEADERS  = FileList["#{SRC_DIR}/*.{h,hh}"]

  case OS
  when :mac
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}.#{DYL_EXT}"
    COMPILE_FLAGS = "#{CXXFLAGS}"
    LINKER_FLAGS  = "#{FRAMEWORKS} #{LFLAGS} #{LIBS}"
    HEADERS_FLAGS = "#{INCLUDES} -I#{SRC_DIR}"
    CC            = {'.c' => 'clang', '.cc' => 'clang++'}
    OBJS          = SOURCES.ext('o')
    CLEAN.include ["#{SRC_DIR}/**/*.o","#{SRC_DIR}/*.o","#{LIB_DIR}/*.dylib","#{BIN_DIR}/main"]
    RUN           = "cd #{ROOT}\n./bin/main"
  when :linux
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}.#{DYL_EXT}"
    COMPILE_FLAGS = "#{CXXFLAGS}"
    LINKER_FLAGS  = "#{FRAMEWORKS} #{LFLAGS} #{LIBS}"
    HEADERS_FLAGS = "#{INCLUDES} -I#{SRC_DIR}"
    CC            = {'.c' => 'gcc', '.cc' => 'g++'}
    OBJS          = SOURCES.ext('o')
    CLEAN.include ["#{SRC_DIR}/**/*.o","#{SRC_DIR}/*.o","#{LIB_DIR}/*.so","#{BIN_DIR}/main"]
    RUN           = "cd #{ROOT}\n./bin/main"
  when :win
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}"
    COMPILE_FLAGS = "#{CXXFLAGS}"
    LINKER_FLAGS  = "/link /DLL"
    HEADERS_FLAGS = "#{INCLUDES} /I#{SRC_DIR}"
    LIB_WIN_DIR   = "#{LFLAGS} #{FRAMEWORKS}"
    CC            = {'.c' => 'cl.exe', '.cc' => 'cl.exe', '.lib' => 'lib.exe', '.dll' => 'link.exe'}
    OBJS          = SOURCES.ext('obj')
    CLEAN.include ["#{SRC_DIR}/**/*.obj","#{SRC_DIR}/*.obj","#{LIB_DIR}/*.{dll,lib,exp}","#{BIN_DIR}/main.{obj,exe}"]
    $RUN           = "(set path=%path%;#{PATHLIB} & bin\\main)"
    RUN           = "bin\\main"
  end
  MAIN = "#{MAIN_DIR}/#{MODEL_NAME}_Main.cc"

  CLOBBER.include [
    "#{ROOT}/{data,lib,bin}/*",
    "#{ROOT}/ocp-*",
    "#{ROOT}/*_run*.rb",
    "#{ROOT}/#{MODEL_DIR}/bvpOut",
    "#{LIBRARY}",
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
      case OS
      when :mac, :linux
        sh "#{MAPLECMD} #{mpl}"
      when :win
        sh "cd model & #{MAPLECMD} #{mpl}"
      end
    end
    puts ">> source code generated".green
  else
    warn ">> #{MAPLET} does not exist!".red
  end
end

%w|.c .cc|.each do |ext|
  lang = {'.c'=>'c', '.cc'=>'c++'}[ext]
  case OS
  when :mac
    rule ".o" => ext do |t|
      puts ">> Compiling #{t.source}".yellow
      sh "#{CC[ext]} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -o #{t} -c #{t.source}"
    end
  when :linux
    rule ".o" => ext do |t|
      puts ">> Compiling #{t.source}".yellow
      sh "#{CC[ext]} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -o #{t} -c #{t.source}"
    end
  when :win
    rule ".obj" => ext do |t|
      puts ">> Compiling #{t.source}".yellow
      sh "#{CC[ext]} #{COMPILE_FLAGS} /D _USRDLL /D _WINDLL /D\"#{MODEL_NAME.upcase}_EXPORT\" #{HEADERS_FLAGS} /c /Fo#{t} #{t.source}"
    end
  end
end

file LIBRARY => OBJS do
  puts ">> Building lib#{MODEL_NAME}".green
  lib_name = "lib#{MODEL_NAME}.#{DYL_EXT}"
  case OS
  when :mac
    sh "#{CC['.cc']} -dynamiclib -current_version 1.0 #{LINKER_FLAGS} -o #{LIBRARY} -install_name @rpath/../lib/#{lib_name} #{OBJS}"
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run.rb"     if File.exist?("#{ROOT}/#{MODEL_NAME}_run.rb")
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run_ffi.rb" if File.exist?("#{ROOT}/#{MODEL_NAME}_run_ffi.rb")
  when :linux
    sh "#{CC['.cc']} -shared #{OBJS} #{LINKER_FLAGS} -o #{LIBRARY} "
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run.rb"     if File.exist?("#{ROOT}/#{MODEL_NAME}_run.rb")
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run_ffi.rb" if File.exist?("#{ROOT}/#{MODEL_NAME}_run_ffi.rb")
  when :win
    sh "#{CC['.dll']} #{LINKER_FLAGS} #{LIB_WIN_DIR} #{LIBS} /OUT:#{LIBRARY}.dll #{OBJS}"
    #sh "#{CC['.cc']} /D _USRDLL /D _WINDLL #{OBJS} #{LIB_WIN_DIR} #{LIBS} #{LINKER_FLAGS} /OUT:#{LIBRARY}.dll"
    sh "#{CC['.lib']} /OUT:#{LIBRARY}_static.lib #{OBJS}"
  end
  puts "   built library #{LIBRARY}".green
end

desc "Build the dynamic library #{MODEL_NAME}".green
task MODEL_NAME do
  #sleep 1 (non serve ?)
  puts "working in "
  Rake::Task[LIBRARY].invoke
end

desc "Test autocompile feature".green
task :auto do
  puts ">> Building lib#{MODEL_NAME}".green
  cd ROOT do
    sh "pins ./#{MODEL_NAME}_run.rb"
  end
end

desc "Build the #{MODEL_NAME}_Main executable".yellow
case OS
when :mac, :linux
  task :main => [LIBRARY] do |t|
    puts ">> Building #{MODEL_NAME}_Main".green
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} #{MAIN} -L#{LIB_DIR} -l#{MODEL_NAME} #{LINKER_FLAGS} -Wl,-rpath,./lib -o #{BIN_DIR}/#{t}"
    puts "   built executable #{BIN_DIR}/#{t}".green
  end
when :win
  task :main => [LIBRARY] do |t|
    puts ">> Building #{MODEL_NAME}_Main".green
    #sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} /D \"#{MODEL_NAME.upcase}_IMPORT\" #{MAIN} /Fe\"#{BIN_DIR}/#{t}\" /link #{LIB_WIN_DIR} #{ROOT}/lib/lib#{MODEL_NAME}_static.lib #{LIBS}"
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} #{MAIN} /Fe\"#{BIN_DIR}/#{t}\" /link #{LIB_WIN_DIR} #{ROOT}/lib/lib#{MODEL_NAME}_static.lib #{LIBS}"
    puts "   built executable #{BIN_DIR}/#{t}".green
  end
end

desc "Run executable".green
task :run => [:main] do
  puts "Run executable #{RUN}".yellow
  ENV['PATH'] = ENV['PATH']+PATHLIB
  cd ROOT
  sh RUN
end

task :default => LIBRARY

task :pry do
  require 'pry'
  binding.pry
end
