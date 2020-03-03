%-----------------------------------------------------------------------%
%  file: Underwater.m                                                   %
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


classdef Underwater < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = Underwater( name )
      self.objectHandle = Underwater_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Underwater_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      Underwater_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = Underwater_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      Underwater_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = Underwater_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = Underwater_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = Underwater_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      Underwater_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      Underwater_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = Underwater_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = Underwater_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = Underwater_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      Underwater_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = Underwater_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = Underwater_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = Underwater_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'x', varargin{:} );
    end
    function res = z( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'z', varargin{:} );
    end
    function res = theta( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'theta', varargin{:} );
    end
    function res = vx( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'vx', varargin{:} );
    end
    function res = vz( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'vz', varargin{:} );
    end
    function res = Omega( self, varargin  )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'Omega', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end
    function res = lambda6( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'lambda6__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = u1( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'u1', varargin{:} );
    end
    function res = u2( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'u2', varargin{:} );
    end
    function res = u3( self, varargin )
      res = Underwater_Mex( 'get_solution', self.objectHandle, 'u3', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = Underwater_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = Underwater_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = Underwater_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = Underwater_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      Underwater_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = Underwater_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      Underwater_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.z(), ...
        self.zeta(), self.theta(), ...
        self.zeta(), self.vx(), ...
        self.zeta(), self.vz(), ...
        self.zeta(), self.Omega(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'z', 'th\eta', 'vx', 'vz', '\Omega' );
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
        self.zeta(), self.u1(), ...
        self.zeta(), self.u2(), ...
        self.zeta(), self.u3(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'u1', 'u2', 'u3' );
    end

  end

end

% EOF: Underwater.m
