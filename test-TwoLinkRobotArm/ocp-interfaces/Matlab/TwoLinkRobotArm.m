%-----------------------------------------------------------------------%
%  file: TwoLinkRobotArm.m                                              %
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


classdef TwoLinkRobotArm < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = TwoLinkRobotArm( name )
      self.objectHandle = TwoLinkRobotArm_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      TwoLinkRobotArm_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      TwoLinkRobotArm_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = TwoLinkRobotArm_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      TwoLinkRobotArm_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = TwoLinkRobotArm_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = TwoLinkRobotArm_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = TwoLinkRobotArm_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      TwoLinkRobotArm_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      TwoLinkRobotArm_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = TwoLinkRobotArm_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = TwoLinkRobotArm_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = TwoLinkRobotArm_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      TwoLinkRobotArm_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = TwoLinkRobotArm_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = TwoLinkRobotArm_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x1( self, varargin  )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'x1', varargin{:} );
    end
    function res = x2( self, varargin  )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'x2', varargin{:} );
    end
    function res = x3( self, varargin  )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'x3', varargin{:} );
    end
    function res = x4( self, varargin  )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'x4', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = u1( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'u1', varargin{:} );
    end
    function res = u2( self, varargin )
      res = TwoLinkRobotArm_Mex( 'get_solution', self.objectHandle, 'u2', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = TwoLinkRobotArm_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = TwoLinkRobotArm_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = TwoLinkRobotArm_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = TwoLinkRobotArm_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      TwoLinkRobotArm_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = TwoLinkRobotArm_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      TwoLinkRobotArm_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x1(), ...
        self.zeta(), self.x2(), ...
        self.zeta(), self.x3(), ...
        self.zeta(), self.x4(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x1', 'x2', 'x3', 'x4' );
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
        self.zeta(), self.u1(), ...
        self.zeta(), self.u2(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'u1', 'u2' );
    end

  end

end

% EOF: TwoLinkRobotArm.m
