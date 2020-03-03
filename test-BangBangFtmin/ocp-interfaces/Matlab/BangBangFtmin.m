%-----------------------------------------------------------------------%
%  file: BangBangFtmin.m                                                %
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


classdef BangBangFtmin < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = BangBangFtmin( name )
      self.objectHandle = BangBangFtmin_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      BangBangFtmin_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      BangBangFtmin_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = BangBangFtmin_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      BangBangFtmin_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = BangBangFtmin_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = BangBangFtmin_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = BangBangFtmin_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      BangBangFtmin_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      BangBangFtmin_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = BangBangFtmin_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = BangBangFtmin_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = BangBangFtmin_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      BangBangFtmin_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = BangBangFtmin_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = BangBangFtmin_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = BangBangFtmin_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = v( self, varargin  )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = T( self, varargin  )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'T', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = F( self, varargin )
      res = BangBangFtmin_Mex( 'get_solution', self.objectHandle, 'F', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = BangBangFtmin_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = BangBangFtmin_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = BangBangFtmin_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = BangBangFtmin_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      BangBangFtmin_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = BangBangFtmin_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      BangBangFtmin_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.T(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'v', 'T' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.F(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'F' );
    end

  end

end

% EOF: BangBangFtmin.m
