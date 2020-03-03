%-----------------------------------------------------------------------%
%  file: Crossroad.m                                                    %
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


classdef Crossroad < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = Crossroad( name )
      self.objectHandle = Crossroad_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Crossroad_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      Crossroad_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = Crossroad_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      Crossroad_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = Crossroad_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = Crossroad_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = Crossroad_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      Crossroad_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      Crossroad_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = Crossroad_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = Crossroad_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = Crossroad_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      Crossroad_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = Crossroad_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = Crossroad_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = Crossroad_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = s( self, varargin  )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 's', varargin{:} );
    end
    function res = v( self, varargin  )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = a( self, varargin  )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'a', varargin{:} );
    end
    function res = Ts( self, varargin  )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'Ts', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = jerk( self, varargin )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'jerk', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = kappa( self )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'kappa' );
    end
    function res = a_su_along( self )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'a_su_along' );
    end
    function res = a_su_alat( self )
      res = Crossroad_Mex( 'get_solution', self.objectHandle, 'a_su_alat' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = Crossroad_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = Crossroad_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = Crossroad_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = Crossroad_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      Crossroad_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = Crossroad_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      Crossroad_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.s(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.a(), ...
        self.zeta(), self.Ts(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 's', 'v', 'a', 'Ts' );
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
        self.zeta(), self.jerk(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'jerk' );
    end

  end

end

% EOF: Crossroad.m
