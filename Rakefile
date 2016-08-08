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

# constanti legate al sistema operativo e al compilatore
case RUBY_PLATFORM

when /darwin/

  OS         = :mac
  WHICH_CMD  = 'which'
  DYL_EXT    = 'dylib'
  PREFIX     = ''
  VS_VERSION = ''
  VS_ARCH    = ''
  LIBCC      = '-stdlib=libc++ -lc++'
  MAPLECMD   = `ls -1 /Applications/Maple*/maple | tail -1`.gsub(' ','\ ').chomp

when /linux/

  OS         = :linux
  WHICH_CMD  = 'which'
  DYL_EXT    = 'so'
  PREFIX     = '/usr/local'
  VS_VERSION = ''
  VS_ARCH    = ''
  LIBCC      = '-stdlib=libc++ -lc++'
  MAPLECMD   = "maple" # da sistenare

when /mingw|mswin/

  OS        = :win
  WHICH_CMD = 'where'
  DYL_EXT   = 'dll'
  PREFIX    = '/usr/local'

  # in windows use visual studio compiler, check version
  tmp = `#{WHICH_CMD} cl.exe`.chop
  case tmp
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
  when /amd64\\cl\.exe/
    VS_ARCH = 'x64'
  when /bin\\cl\.exe/
    VS_ARCH = 'x86'
  else
    raise RuntimeError, "Cannot determine architecture for Visual Studio #{VS_VERSION}"
  end

  WSFLAGS_COMMON  = %w(/nologo /GS /W3 /WX- /Gm- /Gd /fp:precise /EHsc /FS /D_CRT_SECURE_NO_DEPRECATE /D_CRT_SECURE_NO_WARNINGS)
  WSFLAGS_RELEASE = WSFLAGS_COMMON + %w(/Ox /favor:blend /MD)
  WSFLAGS_DEBUG   = WSFLAGS_COMMON + %w(/Od /Ob0 /MDd /Zi /RTC1 /D_DEBUG)

  MAPLECMD   = "cmaple.exe" # da sistenare

else
  raise RuntimeError, "Unsupported OS: #{RUBY_PLATFORM}"
end

begin # definitions
  ROOT          = Rake.original_dir
  MODEL_DIR     = "model"

  raise ModelDirNotFoundError unless (Dir.exist? "#{ROOT}/#{MODEL_DIR}")

  tmp_name      = ROOT.split('/')[-1].match(/^test-(\w+)$/)

  raise WrongTestDirError unless tmp_name

  MODEL_NAME    = tmp_name[1] # meglio non capitalizzare    ------ .capitalize # non usare ! se viene assegnato

  puts "Compiling model: #{MODEL_NAME}\n"
  
  MAPLET  = "#{ROOT}/#{MODEL_DIR}/#{MODEL_NAME}.maplet"
  SRC_DIR = "#{ROOT}/ocp-cpp"
  LIB_DIR = "#{ROOT}/lib"
  BIN_DIR = "#{ROOT}/bin"
  SOURCES = FileList["#{SRC_DIR}/src/*.{c,cc}"]
  HEADERS = FileList["#{SRC_DIR}/src/*.{h,hh}"]
  
  PINS_LIBS = `pins --libs`
  PINS_HDR  = `pins --headers`

  case OS
  when :mac
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}.dylib"
    COMPILE_FLAGS = "-msse4.2 -msse4.1 -mssse3 -msse3 -msse2 -msse -mmmx -m64 -O3 -funroll-loops -fPIC -std=c++11 -stdlib=libc++ -arch x86_64"
    FRAMEWORKS    = %w(MechatronixCore MechatronixInterfaceLua MechatronixInterfaceMruby MechatronixODE MechatronixRoad MechatronixSolver MechatronixVehicle MechatronixManufacturing).inject("-F/Library/Frameworks") {|s,f| s + " -framework #{f}"}
    LINKER_FLAGS  = "-std=c++11 -stdlib=libc++ #{FRAMEWORKS} #{PINS_LIBS}"
    HEADERS_FLAGS = "#{PINS_HDR} -I/usr/local/include -I#{SRC_DIR}/src -I/Library/Frameworks/MechatronixInterfaceMruby.framework/Headers/mruby/"    
    CC = {'.c' => 'clang', '.cc' => 'clang++'}
    OBJS          = SOURCES.ext('o')
    CLEAN.include   ["#{SRC_DIR}/**/*.o"]
  when :linux
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}.so"
    COMPILE_FLAGS = "-msse4.2 -msse4.1 -mssse3 -msse3 -msse2 -msse -mmmx -m64 -O3 -funroll-loops -fPIC "
    LINKER_FLAGS  = "-module -fPIC -stdlib=libstdc++ -lstdc++ -lpthread -lreadline -ldl -lpcre -L/usr/lib/atlas-base -llapack_atlas -llapack -lcblas -Wl,-rpath=. -Wl,-rpath=./lib -Wl,-rpath=/usr/lib/openblas-base -Wl,-rpath=/usr/lib/atlas-base"
    HEADERS_FLAGS = "-I/usr/local/include -I/usr/include/atlas /usr/local/include/MechatronixInterfaceMruby/mruby -I#{SRC_DIR}/src"
    LIBS          = %w(MechatronixCore MechatronixSolver MechatronixInterfaceLua MechatronixInterfaceMruby MechatronixODE MechatronixRoad MechatronixVehicle MechatronixManufacturing).inject("-L/usr/local/lib -Wl,--whole-archive ") {|s,l| s + " -l#{l}"} + " -Wl,--no-whole-archive"
    CC = {'.c' => 'clang', '.cc' => 'clang++'}
    OBJS          = SOURCES.ext('o')
    CLEAN.include   ["#{SRC_DIR}/**/*.o"]
  when :win
    LIBRARY       = "#{LIB_DIR}/lib#{MODEL_NAME}"
    COMPILE_FLAGS = WSFLAGS_RELEASE.join(' ') ;
    LINKER_FLAGS  = "/link /DLL"
    HEADERS_FLAGS = "/IC:/Mechatronix/include /I#{SRC_DIR}/src /IC:/Mechatronix/include/MechatronixInterfaceMruby/mruby"
    LIB_WIN_DIR   = "/LIBPATH:C:/Mechatronix/lib /LIBPATH:C:/Mechatronix/dll"
    LIBS          = " msvcrt.lib"
    CC = {'.c' => 'cl.exe', '.cc' => 'cl.exe', '.lib' => 'lib.exe', '.dll' => 'link.exe'}
    OBJS          = SOURCES.ext('obj')
    CLEAN.include   ["#{SRC_DIR}/**/*.obj"]
  end
  MAIN       = "#{SRC_DIR}/#{MODEL_NAME}_Main.cc"
  STANDALONE = "#{SRC_DIR}/#{MODEL_NAME}_MainStandalone.cc"

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
  
desc "Run the maplet file and generate source".green
task :maple do
  maplet = File.basename MAPLET
  dir = File.dirname MAPLET
  if File.exist?(MAPLET)
    cd dir do
      case OS
      when :mac, :linux
        sh "#{MAPLECMD} #{maplet}"
      when :win
        sh "cd model & #{MAPLECMD} #{maplet}"
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
      sh "#{CC[ext]} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -F/Library/Frameworks -o #{t} -c #{t.source}"
    end
  when :linux
    rule ".o" => ext do |t|
      puts ">> Compiling #{t.source}".yellow
      sh "#{CC[ext]} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -o #{t} -c #{t.source}"
    end
  when :win
    rule ".obj" => ext do |t|
      puts ">> Compiling #{t.source}".yellow
      sh "#{CC[ext]} #{COMPILE_FLAGS} /D \"#{MODEL_NAME.upcase}_EXPORT\" #{HEADERS_FLAGS} /c /Fo#{t} #{t.source}"
    end
  end
end

file LIBRARY => OBJS do
  puts ">> Building lib#{MODEL_NAME}".green
  case OS
  when :mac
    lib_name = "lib#{MODEL_NAME}.dylib"
    sh "#{CC['.cc']} -arch x86_64 -dynamiclib -current_version 1.0 #{LINKER_FLAGS} -o #{LIBRARY} -install_name @rpath/../lib/#{lib_name} #{OBJS}"
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run.rb"      if File.exist?("#{ROOT}/#{MODEL_NAME}_run.rb")
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run_ffi.rb"  if File.exist?("#{ROOT}/#{MODEL_NAME}_run_ffi.rb")
  when :linux
    lib_name = "lib#{MODEL_NAME}.so"
    sh "#{CC['.cc']} -shared #{LINKER_FLAGS} #{LIBS} -o #{LIBRARY} #{OBJS}"
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run.rb"      if File.exist?("#{ROOT}/#{MODEL_NAME}_run.rb")
    sh "chmod u+x #{ROOT}/#{MODEL_NAME}_run_ffi.rb"  if File.exist?("#{ROOT}/#{MODEL_NAME}_run_ffi.rb")
  when :win
    lib_name = "#{MODEL_NAME}.dll"
    sh "#{CC['.dll']} #{LINKER_FLAGS} #{LIB_WIN_DIR} #{LIBS} /OUT:#{LIBRARY}.dll #{OBJS}"
    sh "#{CC['.lib']} /OUT:#{LIBRARY}.lib #{OBJS}"
  end
  puts "   built library #{LIBRARY}".green
end

desc "Build the dynamic library #{MODEL_NAME}".green
task MODEL_NAME do
  sleep 1
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
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -L#{LIB_DIR} -l#{MODEL_NAME} #{LINKER_FLAGS} -Wl,-rpath,@loader_path/. #{MAIN} -o #{BIN_DIR}/#{t}"
    puts "   built executable #{BIN_DIR}/#{t}".green
  end
when :win
  task :main => [LIBRARY] do |t|
    puts ">> Building #{MODEL_NAME}_Main".green
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} #{MAIN.ext('obj')} /Fe\"#{BIN_DIR}/#{t}\" /link #{LIB_WIN_DIR} #{ROOT}/lib/lib#{MODEL_NAME}.lib #{LIBS}"
    puts "   built executable #{BIN_DIR}/#{t}".green  
  end
end

desc "Build the #{MODEL_NAME}_MainStandalone executable".yellow
case OS
when :mac, :linux
  task :standalone => [LIBRARY, STANDALONE.ext('o')] do |t|
    puts ">> Building #{MODEL_NAME}_MainStandalone".green
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} -L#{LIB_DIR} -l#{MODEL_NAME} #{LINKER_FLAGS} -Wl,-rpath,@loader_path/. #{STANDALONE} -o  #{BIN_DIR}/#{t}"
    puts "   built executable #{BIN_DIR}/#{t}".green
  end
when :win
  task :standalone => [LIBRARY, STANDALONE.ext('obj')] do |t|
    puts ">> Building #{MODEL_NAME}_MainStandalone".green
    sh "#{CC['.cc']} #{COMPILE_FLAGS} #{HEADERS_FLAGS} #{STANDALONE.ext('obj')} /Fe#{BIN_DIR}/#{t} /link #{LIB_WIN_DIR} #{ROOT}/lib/lib#{MODEL_NAME}.lib #{LIBS}"
    puts "   built executable #{BIN_DIR}/#{t}".green
  end
end

task :default => LIBRARY

task :pry do
  require 'pry'
  binding.pry
end
