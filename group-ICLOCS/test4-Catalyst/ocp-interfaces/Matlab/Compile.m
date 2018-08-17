%-----------------------------------------------------------------------%
%  file: Catalyst_Data.rb                                               %
%                                                                       %
%  version: 1.0   date 17/8/2018                                        %
%                                                                       %
%  Copyright (C) 2018                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


clear all;
clear functions;
clear mex;
clc;

MODEL     = 'Catalyst';
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

if isunix || ismac
  CMD  = [ 'mex -largeArrayDims ' INC ' -output ' MODEL '_Mex ' SRCS ];
  if ismac
    LIBS_MAC = [ ...
      '-framework MechatronixCore ', ...
      '-framework MechatronixSolver ', ...
      '-framework MechatronixManufacturing ', ...
      '-framework MechatronixRoad ', ...
      '-framework MechatronixODE ', ...
      '-framework MechatronixVehicle ' ...
      '-framework MechatronixInterfaceMruby ' ...
      '-framework Accelerate ' ...
    ];
    CMD = [ CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0 -F/Library/Frameworks/" LDFLAGS="\$LDFLAGS ', LIBS_MAC, '"'];
  else
    LIBS = [ LIBS '-L/usr/local/lib -lbz2 -lpcre '];
    INC  = [ INC '-I/usr/local/include -I/usr/local/include/eigen3 ' ];
    CMD  = [ CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'];
  end
  CMD  = [ CMD ' ' LIBS ];
elseif ispc
  % -llegacy_stdio_definitions
  LIBS = [ LIBS '-L"C:/PINS/pins-libs/lib" '];
  INC  = [ INC '-I"C:/PINS/pins-libs/include" ' ];
  CMD  = [ 'mex -largeArrayDims ' INC ' -output ' MODEL ' ' SRCS ' ' LIBS ];
else
  error('unsupported OS!')
end
disp(CMD);
eval(CMD);

disp('----------------------- DONE ----------------------------');
