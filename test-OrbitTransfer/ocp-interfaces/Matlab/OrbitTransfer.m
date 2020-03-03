%-----------------------------------------------------------------------%
%  file: OrbitTransfer.m                                                %
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


classdef OrbitTransfer < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = OrbitTransfer( name )
      self.objectHandle = OrbitTransfer_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      OrbitTransfer_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      OrbitTransfer_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = OrbitTransfer_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      OrbitTransfer_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = OrbitTransfer_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = OrbitTransfer_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = OrbitTransfer_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      OrbitTransfer_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      OrbitTransfer_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = OrbitTransfer_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = OrbitTransfer_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = OrbitTransfer_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      OrbitTransfer_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = OrbitTransfer_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = OrbitTransfer_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = OrbitTransfer_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = m( self, varargin  )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'm', varargin{:} );
    end
    function res = alpha( self, varargin  )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'alpha', varargin{:} );
    end
    function res = r( self, varargin  )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'r', varargin{:} );
    end
    function res = u( self, varargin  )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'u', varargin{:} );
    end
    function res = v( self, varargin  )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'v', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = theta( self, varargin )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'theta', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = X_minus_pos( self )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'X-pos' );
    end
    function res = Y_minus_pos( self )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'Y-pos' );
    end
    function res = X_minus_pos0( self )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'X-pos0' );
    end
    function res = Y_minus_pos0( self )
      res = OrbitTransfer_Mex( 'get_solution', self.objectHandle, 'Y-pos0' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = OrbitTransfer_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = OrbitTransfer_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = OrbitTransfer_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = OrbitTransfer_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      OrbitTransfer_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = OrbitTransfer_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      OrbitTransfer_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.m(), ...
        self.zeta(), self.alpha(), ...
        self.zeta(), self.r(), ...
        self.zeta(), self.u(), ...
        self.zeta(), self.v(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'm', '\alpha', 'r', 'u', 'v' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        self.zeta(), self.lambda4(), ...
        self.zeta(), self.lambda5(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.theta(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'th\eta' );
    end

  end

end

% EOF: OrbitTransfer.m
