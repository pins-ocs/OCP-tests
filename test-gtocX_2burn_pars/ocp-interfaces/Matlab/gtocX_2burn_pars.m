%-----------------------------------------------------------------------%
%  file: gtocX_2burn_pars.m                                             %
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


classdef gtocX_2burn_pars < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = gtocX_2burn_pars( name )
      self.objectHandle = gtocX_2burn_pars_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      gtocX_2burn_pars_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      gtocX_2burn_pars_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = gtocX_2burn_pars_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      gtocX_2burn_pars_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = gtocX_2burn_pars_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = gtocX_2burn_pars_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = gtocX_2burn_pars_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      gtocX_2burn_pars_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      gtocX_2burn_pars_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = gtocX_2burn_pars_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = gtocX_2burn_pars_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = gtocX_2burn_pars_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      gtocX_2burn_pars_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = gtocX_2burn_pars_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = gtocX_2burn_pars_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = f( self, varargin  )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'f', varargin{:} );
    end
    function res = g( self, varargin  )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'g', varargin{:} );
    end
    function res = L( self, varargin  )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'L', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = time( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'time' );
    end
    function res = ray( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'ray' );
    end
    function res = X( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X' );
    end
    function res = Y( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y' );
    end
    function res = Z( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z' );
    end
    function res = VX( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX' );
    end
    function res = VY( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY' );
    end
    function res = VZ( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ' );
    end
    function res = X_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X_begin' );
    end
    function res = Y_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y_begin' );
    end
    function res = Z_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z_begin' );
    end
    function res = VX_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX_begin' );
    end
    function res = VY_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY_begin' );
    end
    function res = VZ_begin( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ_begin' );
    end
    function res = X_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X_end' );
    end
    function res = Y_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y_end' );
    end
    function res = Z_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z_end' );
    end
    function res = VX_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX_end' );
    end
    function res = VY_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY_end' );
    end
    function res = VZ_end( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ_end' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = gtocX_2burn_pars_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = gtocX_2burn_pars_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = gtocX_2burn_pars_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = gtocX_2burn_pars_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      gtocX_2burn_pars_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = gtocX_2burn_pars_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      gtocX_2burn_pars_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.f(), ...
        self.zeta(), self.g(), ...
        self.zeta(), self.L(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'f', 'g', 'L' );
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
        'Linewidth', 2 ...
      );
      title('controls');
      legend(  );
    end

  end

end

% EOF: gtocX_2burn_pars.m
