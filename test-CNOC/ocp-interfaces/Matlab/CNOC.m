%-----------------------------------------------------------------------%
%  file: CNOC.m                                                         %
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


classdef CNOC < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = CNOC( name )
      self.objectHandle = CNOC_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      CNOC_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      CNOC_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = CNOC_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      CNOC_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = CNOC_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = CNOC_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = CNOC_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      CNOC_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      CNOC_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = CNOC_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = CNOC_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = CNOC_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      CNOC_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = CNOC_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = CNOC_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = CNOC_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = s( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 's', varargin{:} );
    end
    function res = n( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'n', varargin{:} );
    end
    function res = vs( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vs', varargin{:} );
    end
    function res = vn( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vn', varargin{:} );
    end
    function res = as( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'as', varargin{:} );
    end
    function res = an( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'an', varargin{:} );
    end
    function res = coV( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'coV', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end
    function res = lambda6( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda6__xo', varargin{:} );
    end
    function res = lambda7( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda7__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = js( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'js', varargin{:} );
    end
    function res = jn( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jn', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = feed( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'feed' );
    end
    function res = acc( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'acc' );
    end
    function res = jerk( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jerk' );
    end
    function res = vx( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vx' );
    end
    function res = vy( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vy' );
    end
    function res = ax( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ax' );
    end
    function res = ay( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ay' );
    end
    function res = jx( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jx' );
    end
    function res = jy( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jy' );
    end
    function res = X_minus_path( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-path' );
    end
    function res = Y_minus_path( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-path' );
    end
    function res = X_minus_traj( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-traj' );
    end
    function res = Y_minus_traj( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-traj' );
    end
    function res = X_minus_left( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-left' );
    end
    function res = Y_minus_left( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-left' );
    end
    function res = X_minus_right( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-right' );
    end
    function res = Y_minus_right( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-right' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = CNOC_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = CNOC_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = CNOC_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = CNOC_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      CNOC_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = CNOC_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      CNOC_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.s(), ...
        self.zeta(), self.n(), ...
        self.zeta(), self.vs(), ...
        self.zeta(), self.vn(), ...
        self.zeta(), self.as(), ...
        self.zeta(), self.an(), ...
        self.zeta(), self.coV(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 's', 'n', 'vs', 'vn', 'as', 'an', 'coV' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        self.zeta(), self.lambda4(), ...
        self.zeta(), self.lambda5(), ...
        self.zeta(), self.lambda6(), ...
        self.zeta(), self.lambda7(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5', '\lambda6', '\lambda7' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.js(), ...
        self.zeta(), self.jn(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'js', 'jn' );
    end

  end

end

% EOF: CNOC.m
