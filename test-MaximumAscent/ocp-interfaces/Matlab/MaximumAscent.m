%-----------------------------------------------------------------------%
%  file: MaximumAscent.m                                                %
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


classdef MaximumAscent < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = MaximumAscent( name )
      self.objectHandle = MaximumAscent_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      MaximumAscent_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      MaximumAscent_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = MaximumAscent_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      MaximumAscent_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = MaximumAscent_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = MaximumAscent_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = MaximumAscent_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      MaximumAscent_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      MaximumAscent_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = MaximumAscent_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = MaximumAscent_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = MaximumAscent_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      MaximumAscent_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = MaximumAscent_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = MaximumAscent_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = MaximumAscent_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = r( self, varargin  )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'r', varargin{:} );
    end
    function res = u( self, varargin  )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'u', varargin{:} );
    end
    function res = v( self, varargin  )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = theta( self, varargin  )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'theta', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = alpha( self, varargin )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'alpha', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = sqrtl12( self )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'sqrtl12' );
    end
    function res = R( self )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'R' );
    end
    function res = U( self )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'U' );
    end
    function res = V( self )
      res = MaximumAscent_Mex( 'get_solution', self.objectHandle, 'V' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = MaximumAscent_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = MaximumAscent_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = MaximumAscent_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = MaximumAscent_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      MaximumAscent_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = MaximumAscent_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      MaximumAscent_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.r(), ...
        self.zeta(), self.u(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.theta(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'r', 'u', 'v', 'th\eta' );
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
        self.zeta(), self.alpha(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( '\alpha' );
    end

  end

end

% EOF: MaximumAscent.m
