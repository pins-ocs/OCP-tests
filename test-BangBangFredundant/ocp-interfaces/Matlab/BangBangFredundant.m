%-----------------------------------------------------------------------%
%  file: BangBangFredundant.m                                           %
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


classdef BangBangFredundant < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = BangBangFredundant( name )
      self.objectHandle = BangBangFredundant_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      BangBangFredundant_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      BangBangFredundant_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = BangBangFredundant_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      BangBangFredundant_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = BangBangFredundant_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = BangBangFredundant_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = BangBangFredundant_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      BangBangFredundant_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      BangBangFredundant_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = BangBangFredundant_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = BangBangFredundant_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = BangBangFredundant_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      BangBangFredundant_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = BangBangFredundant_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = BangBangFredundant_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = BangBangFredundant_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = v( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end
    function res = F1( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'F1', varargin{:} );
    end
    function res = F2( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'F2', varargin{:} );
    end
    function res = vF1( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'vF1', varargin{:} );
    end
    function res = vF2( self, varargin  )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'vF2', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end
    function res = lambda6( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'lambda6__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = aF1( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'aF1', varargin{:} );
    end
    function res = aF2( self, varargin )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'aF2', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = aF1Control( self )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'aF1Control' );
    end
    function res = aF2Control( self )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'aF2Control' );
    end
    function res = Flim( self )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'Flim' );
    end
    function res = F1_plus_F2( self )
      res = BangBangFredundant_Mex( 'get_solution', self.objectHandle, 'F1+F2' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = BangBangFredundant_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = BangBangFredundant_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = BangBangFredundant_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = BangBangFredundant_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      BangBangFredundant_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = BangBangFredundant_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      BangBangFredundant_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.F1(), ...
        self.zeta(), self.F2(), ...
        self.zeta(), self.vF1(), ...
        self.zeta(), self.vF2(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'v', 'F1', 'F2', 'vF1', 'vF2' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        self.zeta(), self.lambda4(), ...
        self.zeta(), self.lambda5(), ...
        self.zeta(), self.lambda6(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5', '\lambda6' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.aF1(), ...
        self.zeta(), self.aF2(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'aF1', 'aF2' );
    end

  end

end

% EOF: BangBangFredundant.m
