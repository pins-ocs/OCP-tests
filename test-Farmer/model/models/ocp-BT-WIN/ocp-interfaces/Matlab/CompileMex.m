%-----------------------------------------------------------------------%
%  file: farmer_problem_Data.rb                                         %
%                                                                       %
%  version: 1.0   date 6/5/2019                                         %
%                                                                       %
%  Copyright (C) 2019                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


function [mex_name,lib_name] = CompileMex()
  MODEL     = 'farmer_problem';
  lib_name  = [MODEL, '.m'];
  SRCS_BASE = '../../ocp-src/';
  SRCS      = [ MODEL '_Mex.cc GenericContainerMatlabInterface.cc ' ];

  % get library sources
  fdir = dir([SRCS_BASE '*.cc']);
  for n=1:length(fdir)
    if strfind(fdir(n).name, '_dll.cc') > 0
      % skip dll interface with ruby and pins
    else
      SRCS = [ SRCS, SRCS_BASE, fdir(n).name, ' ' ];
    end
  end

  LIBS = [];
  INC  = ['-I' SRCS_BASE ' '];

  % user defined libraries

  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',MODEL);

  CMD  = [ 'mex -largeArrayDims -output ' MODEL '_Mex ' ];

  if isunix || ismac
    CMD = [ CMD ' ' INC ' ' SRCS ];
    if ismac
      LIBS_MAC = [ ...
        '-framework MechatronixCore ', ...
        '-framework MechatronixSolver ', ...
        '-framework MechatronixManufacturing ', ...
        '-framework MechatronixRoad ', ...
        '-framework MechatronixODE ', ...
        '-framework MechatronixVehicle ', ...
        '-framework MechatronixInterfaceMruby ', ...
        '-framework Accelerate ' ...
      ];
      mex_name = [ MODEL,'_Mex.mexmaci64' ];
      CMD      = [ CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0 -F/Library/Frameworks/" LDFLAGS="\$LDFLAGS ', LIBS_MAC, '"'];
    else
      LIBS     = [ LIBS '-L/usr/local/lib -lbz2 -lpcre '];
      %%INC      = [ INC '-I/usr/local/include -I/usr/local/include/eigen3 ' ];
      CMD      = [ CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'];
      mex_name = [ MODEL,'_Mex.mexa64' ];
    end
    CMD  = [ CMD ' ' LIBS ];
  elseif ispc
    MKL_BASE_PATH = 'C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/mkl';
    MKL_HDR_PATH  = [ MKL_BASE_PATH '/include' ];
    MKL_LIB_PATH  = [ MKL_BASE_PATH '/lib/intel64' ];
    %MKL_LIB_PATH  = [ MKL_BASE_PATH '/lib/ia32' ];
    PINS_PATH     = 'C:/PINS/';
    PINS_PATH_LIB = [ PINS_PATH 'lib'];
    PINS_PATH_INC = [ PINS_PATH 'include'];
    LIBS     = [ LIBS '-L"' PINS_PATH_LIB '" -L"' MKL_LIB_PATH '" '];
    INC      = [ INC '-I"' PINS_PATH_INC '" -I"' MKL_HDR_PATH '" '];
    CMD      = [ CMD, ' COMPFLAGS="$COMPFLAGS /nologo /GS /W3 /WX- /Gm- /fp:precise /EHsc /D_WINDOWS /D_SCL_SECURE_NO_WARNINGS /DHAVE_STRING_H /DNO_GETTIMEOFDAY /DYAML_DECLARE_STATIC /DPCRE_STATIC /O2 /MD" ' INC ' ' SRCS ' ' LIBS ];
    mex_name = [ MODEL,'_Mex.mexw64' ];
  else
    error('unsupported OS!')
  end
  disp(CMD);
  eval(CMD);
  disp('----------------------- DONE ----------------------------');
end
