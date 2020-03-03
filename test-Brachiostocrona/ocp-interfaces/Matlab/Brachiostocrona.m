%-----------------------------------------------------------------------%
%  file: Brachiostocrona.m                                              %
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


classdef Brachiostocrona < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = Brachiostocrona( name )
      self.objectHandle = Brachiostocrona_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Brachiostocrona_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      Brachiostocrona_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = Brachiostocrona_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      Brachiostocrona_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = Brachiostocrona_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = Brachiostocrona_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = Brachiostocrona_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      Brachiostocrona_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      Brachiostocrona_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = Brachiostocrona_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = Brachiostocrona_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = Brachiostocrona_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      Brachiostocrona_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = Brachiostocrona_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = Brachiostocrona_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = Brachiostocrona_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = y( self, varargin  )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'y', varargin{:} );
    end
    function res = v( self, varargin  )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = theta( self, varargin  )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'theta', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = vtheta( self, varargin )
      res = Brachiostocrona_Mex( 'get_solution', self.objectHandle, 'vtheta', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = Brachiostocrona_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = Brachiostocrona_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = Brachiostocrona_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = Brachiostocrona_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      Brachiostocrona_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = Brachiostocrona_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      Brachiostocrona_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.y(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.theta(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'y', 'v', 'th\eta' );
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
        self.zeta(), self.vtheta(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'vth\eta' );
    end

  end

end

% EOF: Brachiostocrona.m
