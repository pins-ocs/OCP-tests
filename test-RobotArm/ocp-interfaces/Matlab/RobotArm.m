%-----------------------------------------------------------------------%
%  file: RobotArm.m                                                     %
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


classdef RobotArm < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = RobotArm( name )
      self.objectHandle = RobotArm_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      RobotArm_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      RobotArm_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = RobotArm_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      RobotArm_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = RobotArm_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = RobotArm_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = RobotArm_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      RobotArm_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      RobotArm_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = RobotArm_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = RobotArm_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = RobotArm_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      RobotArm_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = RobotArm_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = RobotArm_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = RobotArm_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = rho( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'rho', varargin{:} );
    end
    function res = theta( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'theta', varargin{:} );
    end
    function res = phi( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'phi', varargin{:} );
    end
    function res = rho1( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'rho1', varargin{:} );
    end
    function res = theta1( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'theta1', varargin{:} );
    end
    function res = phi1( self, varargin  )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'phi1', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end
    function res = lambda6( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'lambda6__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = u_rho( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'u_rho', varargin{:} );
    end
    function res = u_theta( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'u_theta', varargin{:} );
    end
    function res = u_phi( self, varargin )
      res = RobotArm_Mex( 'get_solution', self.objectHandle, 'u_phi', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = RobotArm_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = RobotArm_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = RobotArm_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = RobotArm_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      RobotArm_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = RobotArm_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      RobotArm_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.rho(), ...
        self.zeta(), self.theta(), ...
        self.zeta(), self.phi(), ...
        self.zeta(), self.rho1(), ...
        self.zeta(), self.theta1(), ...
        self.zeta(), self.phi1(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( '\rho', 'th\eta', '\phi', '\rho1', 'th\eta1', '\phi1' );
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
        self.zeta(), self.u_rho(), ...
        self.zeta(), self.u_theta(), ...
        self.zeta(), self.u_phi(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'u\_\rho', 'u\_th\eta', 'u\_\phi' );
    end

  end

end

% EOF: RobotArm.m
