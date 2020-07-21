%-----------------------------------------------------------------------%
%  file: SingularLuus03_Data.rb                                         %
%                                                                       %
%  version: 1.0   date 21/7/2020                                        %
%                                                                       %
%  Copyright (C) 2020                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


function [mex_name,lib_name] = CompileOctave()
  MODEL     = 'SingularLuus03';
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

  [flg,HDR] = system('pins --includes');

  LIBS = [];
  INC  = [ '-I' SRCS_BASE ];

  % user defined libraries
  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',MODEL);

  CMD  = [ 'mkoctfile --mex -output ' MODEL '_Mex ' ];

  % compiler options

  LIBS = [ ...
    ' -lMechatronixCore ', ...
    '-lMechatronixSolver ', ...
    '-lMechatronixManufacturing ', ...
    '-lMechatronixRoad ', ...
    '-lMechatronixODE ', ...
    '-lMechatronixVehicle ', ...
    '-lMechatroniAstro ' ...
    '-lMechatronixInterfaceMruby ' ...
  ];

  if ispc
    MKL_BASE_PATH = 'C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/mkl';
    MKL_HDR_PATH  = [ MKL_BASE_PATH '/include' ];
    MKL_LIB_PATH  = [ MKL_BASE_PATH '/lib/intel64' ];
    PINS_PATH     = 'C:/PINS/';
    PINS_PATH_LIB = [ PINS_PATH 'lib'];
    PINS_PATH_INC = [ PINS_PATH 'include'];

    LIBS     = [ LIBS ' -L"' PINS_PATH_LIB '" -L"' MKL_LIB_PATH '" '];
    INC      = [ INC  ' -I"' PINS_PATH_INC '" -I"' MKL_HDR_PATH '" '];
    CXXFLAGS = '' ;
  else
    [flg,CXXFLAGS] = system('pins --cppflags');
    [flg,LIBS2]    = system('pins --libs');
    [flg,HDR]      = system('pins --includes');
    INC  = [ INC ' ' HDR ];
    LIBS = [ LIBS, ' ', LIBS2 ];
  end

  mex_name = [ MODEL,'_Mex.mex' ];
  CMD      = [ CMD, INC, ' ', CXXFLAGS, ' ', SRCS, ' ', LIBS ];

  disp(CMD);
  eval(CMD);
  disp('----------------------- DONE ----------------------------');
end
