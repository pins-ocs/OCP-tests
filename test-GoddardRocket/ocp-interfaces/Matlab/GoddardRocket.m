%-----------------------------------------------------------------------%
%  file: GoddardRocket.m                                                %
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


classdef GoddardRocket < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = GoddardRocket( name )
      self.objectHandle = GoddardRocket_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      GoddardRocket_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      GoddardRocket_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = GoddardRocket_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      GoddardRocket_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = GoddardRocket_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = GoddardRocket_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = GoddardRocket_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      GoddardRocket_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      GoddardRocket_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = GoddardRocket_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = GoddardRocket_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = GoddardRocket_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      GoddardRocket_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = GoddardRocket_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = GoddardRocket_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = GoddardRocket_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = h( self, varargin  )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'h', varargin{:} );
    end
    function res = v( self, varargin  )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = m( self, varargin  )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'm', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = T( self, varargin )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'T', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = Time( self )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'Time' );
    end
    function res = target( self )
      res = GoddardRocket_Mex( 'get_solution', self.objectHandle, 'target' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = GoddardRocket_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = GoddardRocket_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = GoddardRocket_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = GoddardRocket_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      GoddardRocket_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = GoddardRocket_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      GoddardRocket_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.h(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.m(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'h', 'v', 'm' );
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
        self.zeta(), self.T(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'T' );
    end

  end

end

% EOF: GoddardRocket.m
