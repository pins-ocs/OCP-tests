%-----------------------------------------------------------------------%
%  file: Bike1D.m                                                       %
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


classdef Bike1D < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = Bike1D( name )
      self.objectHandle = Bike1D_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Bike1D_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      Bike1D_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = Bike1D_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      Bike1D_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = Bike1D_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = Bike1D_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = Bike1D_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      Bike1D_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      Bike1D_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = Bike1D_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = Bike1D_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = Bike1D_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      Bike1D_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = Bike1D_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = Bike1D_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = Bike1D_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = v( self, varargin  )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = mur( self, varargin )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'mur', varargin{:} );
    end
    function res = muf( self, varargin )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'muf', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = Tmax_norma( self )
      res = Bike1D_Mex( 'get_solution', self.objectHandle, 'Tmax_norma' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = Bike1D_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = Bike1D_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = Bike1D_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = Bike1D_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      Bike1D_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = Bike1D_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      Bike1D_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.v(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'v' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.mur(), ...
        self.zeta(), self.muf(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( '\mur', '\muf' );
    end

  end

end

% EOF: Bike1D.m
