%-----------------------------------------------------------------------%
%  file: Brake.m                                                        %
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


classdef Brake < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = Brake( name )
      self.objectHandle = Brake_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Brake_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      Brake_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = Brake_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      Brake_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = Brake_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = Brake_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = Brake_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      Brake_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      Brake_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = Brake_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = Brake_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = Brake_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      Brake_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = Brake_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = Brake_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = Brake_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = v( self, varargin  )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = a( self, varargin )
      res = Brake_Mex( 'get_solution', self.objectHandle, 'a', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = Brake_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = Brake_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = Brake_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = Brake_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      Brake_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = Brake_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      Brake_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.v(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'v' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.a(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'a' );
    end

  end

end

% EOF: Brake.m
