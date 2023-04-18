%-----------------------------------------------------------------------%
%  file: LUUS_Singular03_Data.rb                                        %
%                                                                       %
%  version: 1.0   date 9/5/2023                                         %
%                                                                       %
%  Copyright (C) 2023                                                   %
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

old_dir = cd(fileparts(which(mfilename)));

MODEL     = 'LUUS_Singular03';
lib_name  = [MODEL, '.m'];
SRCS_BASE = '../../ocp-src/';
SRCS      = [ ...
  MODEL '_Mex.cc ' ...
  MODEL '_Mex_class.cc '  ...
  MODEL '_Mex_methods.cc '  ...
  MODEL '_Mex_user.cc GenericContainerMatlabInterface.cc ' ...
];
OBJS      = '';
LIBS      = [];
INC       = ['-I' SRCS_BASE ' '];

if ismac
  [status,CMD_MEX] = system('/usr/local/bin/pins --mex');
  mex_name = [ MODEL,'_Mex.mexmaci64' ];
elseif isunix
  [status,CMD_MEX] = system('(export LD_LIBRARY_PATH="";/usr/local/bin/pins --mex)');
  mex_name = [ MODEL,'_Mex.mexa64' ];
elseif ispc
  [status,CMD_MEX] = system("pins.exe --mex");
  mex_name = [ MODEL,'_Mex.mexw64' ];
else
  error('unsupported OS!');
end

% get library sources (NOW SKIPPED)
fdir = dir([SRCS_BASE '*.cc']);
for n=1:length(fdir)
  if strfind(fdir(n).name, '_dll.cc') > 0
    % skip dll interface with ruby and pins
  else
    if ispc
      SRCS = [ SRCS, SRCS_BASE, fdir(n).name, ' ' ];
    else
      OBJS = [ OBJS extractBefore(fdir(n).name,'.cc'), '.o ' ];
      CMD  = [ 'mex -largeArrayDims -c ' CMD_MEX ' ' INC ' ' SRCS_BASE fdir(n).name ];
      disp('---------------------------------------------------------');
      disp(CMD);
      eval(CMD);
    end
  end
end

disp('---------------------------------------------------------');
fprintf(1,'Compiling: %s\n',MODEL);

CMD = [ 'mex -largeArrayDims -output ' MODEL '_Mex ' CMD_MEX ' ' INC ' ' SRCS ' ' OBJS ];
disp(CMD);
eval(CMD);
disp('----------------------- DONE ----------------------------');

cd(old_dir);
