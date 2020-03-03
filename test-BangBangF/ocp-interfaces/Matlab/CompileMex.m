%-----------------------------------------------------------------------%
%  file: BangBangF_Data.rb                                              %
%                                                                       %
%  version: 1.0   date 28/3/2020                                        %
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


function [mex_name,lib_name] = CompileMex()
  MODEL     = 'BangBangF';
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

  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',MODEL);

  CMD = [ 'mex -largeArrayDims -output ' MODEL '_Mex ' ];
  if isunix || ismac
    [status,CMD_MEX] = system("/usr/local/bin/pins --mex");
    CMD = [ CMD ' ' CMD_MEX ' ' INC ' ' SRCS ];
    if ismac
      mex_name = [ MODEL,'_Mex.mexmaci64' ];
    else
      mex_name = [ MODEL,'_Mex.mexa64' ];
    end
    %CMD  = [ CMD ' ' LIBS ];
  elseif ispc
    [status,CMD_MEX]  = system("pins.exe --mex");
    CMD = [ CMD ' ' CMD_MEX ' ' INC ' ' SRCS ];
    mex_name = [ MODEL,'_Mex.mexw64' ];
  else
    error('unsupported OS!')
  end
  disp(CMD);
  eval(CMD);
  disp('----------------------- DONE ----------------------------');
end
