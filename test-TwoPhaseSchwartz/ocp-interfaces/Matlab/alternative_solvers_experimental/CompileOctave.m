%-----------------------------------------------------------------------%
%  file: TwoPhaseSchwartz_Data.rb                                       %
%                                                                       %
%  version: 1.0   date 5/7/2021                                         %
%                                                                       %
%  Copyright (C) 2021                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


function [lib_name] = CompileOctave()
  MODEL     = 'TwoPhaseSchwartz';
  lib_name  = [MODEL, '.m'];
  SRCS_BASE = '../../ocp-src/';
  SRCS      = [ MODEL '_Mex.cc GenericContainerMatlabInterface.cc ' ];
  LIBS      = [];
  INC       = ['-I' SRCS_BASE ' '];

  % get library sources (NOW SKIPPED)
  fdir = dir([SRCS_BASE '*.cc']);
  for n=1:length(fdir)
    nn = fdir(n).name;
    if strfind(nn, '_dll.cc') > 0
      % skip dll interface with ruby and pins
    else
      SRCS = [ SRCS, SRCS_BASE, nn, ' ' ];
    end
  end

  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',MODEL);
  [status,CMD1] = system('/usr/local/bin/pins --includes');
  [status,CMD2] = system('/usr/local/bin/pins --lflags');
  [status,CMD3] = system('/usr/local/bin/pins --frameworks');
  [status,CMD4] = system('/usr/local/bin/pins --libs');
  CMD_MEX = [ CMD1, CMD3, CMD4, ' -L/usr/local/PINS/lib -L/usr/lib/llvm-10/lib ' ];
  CMD     = [ 'mkoctfile --mex -output ' MODEL '_Mex ' CMD_MEX ' ' INC ' ' SRCS ];
  disp(CMD);
  eval(CMD);
  disp('----------------------- DONE ----------------------------');
end
