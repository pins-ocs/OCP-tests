%-----------------------------------------------------------------------%
%  file: BangBangFmodule.m                                              %
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


classdef BangBangFmodule < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = BangBangFmodule( name )
      self.objectHandle = BangBangFmodule_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      BangBangFmodule_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      BangBangFmodule_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = BangBangFmodule_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      BangBangFmodule_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = BangBangFmodule_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = BangBangFmodule_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = BangBangFmodule_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      BangBangFmodule_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      BangBangFmodule_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = BangBangFmodule_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = BangBangFmodule_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = BangBangFmodule_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      BangBangFmodule_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = BangBangFmodule_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = BangBangFmodule_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = BangBangFmodule_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = v( self, varargin  )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = Fp( self, varargin )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'Fp', varargin{:} );
    end
    function res = Fm( self, varargin )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'Fm', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = ForceP( self )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'ForceP' );
    end
    function res = ForceM( self )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'ForceM' );
    end
    function res = F( self )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'F' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = BangBangFmodule_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = BangBangFmodule_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = BangBangFmodule_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = BangBangFmodule_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      BangBangFmodule_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = BangBangFmodule_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      BangBangFmodule_Mex( 'check_jacobian', self.objectHandle, x, epsi );
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
        self.zeta(), self.Fp(), ...
        self.zeta(), self.Fm(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'Fp', 'Fm' );
    end

  end

end

% EOF: BangBangFmodule.m
