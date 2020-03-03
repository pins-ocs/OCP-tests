%-----------------------------------------------------------------------%
%  file: BikeSteering.m                                                 %
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


classdef BikeSteering < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = BikeSteering( name )
      self.objectHandle = BikeSteering_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      BikeSteering_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      BikeSteering_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = BikeSteering_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      BikeSteering_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = BikeSteering_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = BikeSteering_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = BikeSteering_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      BikeSteering_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      BikeSteering_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = BikeSteering_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = BikeSteering_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = BikeSteering_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      BikeSteering_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = BikeSteering_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = BikeSteering_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = BikeSteering_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = omega( self, varargin  )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'omega', varargin{:} );
    end
    function res = phi( self, varargin  )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'phi', varargin{:} );
    end
    function res = TimeSize( self, varargin  )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'TimeSize', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = Fy( self, varargin )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'Fy', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = minTime( self )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'minTime' );
    end
    function res = Talpha( self )
      res = BikeSteering_Mex( 'get_solution', self.objectHandle, 'Talpha' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = BikeSteering_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = BikeSteering_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = BikeSteering_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = BikeSteering_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      BikeSteering_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = BikeSteering_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      BikeSteering_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.omega(), ...
        self.zeta(), self.phi(), ...
        self.zeta(), self.TimeSize(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( '\omega', '\phi', 'TimeSize' );
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
        self.zeta(), self.Fy(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'Fy' );
    end

  end

end

% EOF: BikeSteering.m
