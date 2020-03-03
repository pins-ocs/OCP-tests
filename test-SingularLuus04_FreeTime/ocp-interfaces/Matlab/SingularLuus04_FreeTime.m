%-----------------------------------------------------------------------%
%  file: SingularLuus04_FreeTime.m                                      %
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


classdef SingularLuus04_FreeTime < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = SingularLuus04_FreeTime( name )
      self.objectHandle = SingularLuus04_FreeTime_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      SingularLuus04_FreeTime_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      SingularLuus04_FreeTime_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = SingularLuus04_FreeTime_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      SingularLuus04_FreeTime_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = SingularLuus04_FreeTime_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = SingularLuus04_FreeTime_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = SingularLuus04_FreeTime_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      SingularLuus04_FreeTime_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      SingularLuus04_FreeTime_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = SingularLuus04_FreeTime_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = SingularLuus04_FreeTime_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = SingularLuus04_FreeTime_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      SingularLuus04_FreeTime_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = SingularLuus04_FreeTime_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = SingularLuus04_FreeTime_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = y( self, varargin  )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'y', varargin{:} );
    end
    function res = z( self, varargin  )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'z', varargin{:} );
    end
    function res = T( self, varargin  )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'T', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = u( self, varargin )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'u', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = Time( self )
      res = SingularLuus04_FreeTime_Mex( 'get_solution', self.objectHandle, 'Time' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = SingularLuus04_FreeTime_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = SingularLuus04_FreeTime_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = SingularLuus04_FreeTime_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = SingularLuus04_FreeTime_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      SingularLuus04_FreeTime_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = SingularLuus04_FreeTime_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      SingularLuus04_FreeTime_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.y(), ...
        self.zeta(), self.z(), ...
        self.zeta(), self.T(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'y', 'z', 'T' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        self.zeta(), self.lambda4(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.u(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'u' );
    end

  end

end

% EOF: SingularLuus04_FreeTime.m
