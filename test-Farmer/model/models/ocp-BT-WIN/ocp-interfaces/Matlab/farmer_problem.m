%-----------------------------------------------------------------------%
%  file: farmer_problem.m                                               %
%                                                                       %
%  version: 1.0   date 16/6/2019                                        %
%                                                                       %
%  Copyright (C) 2019                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


classdef farmer_problem < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = farmer_problem( name )
      self.objectHandle = farmer_problem_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      farmer_problem_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      farmer_problem_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = farmer_problem_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      farmer_problem_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = farmer_problem_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = farmer_problem_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = farmer_problem_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      farmer_problem_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      farmer_problem_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = farmer_problem_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = farmer_problem_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = farmer_problem_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      farmer_problem_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = farmer_problem_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = farmer_problem_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = farmer_problem_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x1( self, varargin  )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x1', varargin{:} );
    end
    function res = x2( self, varargin  )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x2', varargin{:} );
    end
    function res = x3( self, varargin  )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x3', varargin{:} );
    end
    function res = res( self, varargin  )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'res', varargin{:} );
    end
    function res = x4( self, varargin  )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x4', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = x1__o( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x1__o', varargin{:} );
    end
    function res = x2__o( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x2__o', varargin{:} );
    end
    function res = x3__o( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x3__o', varargin{:} );
    end
    function res = x4__o( self, varargin )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'x4__o', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = power_delivered( self )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'power_delivered' );
    end
    function res = power_required( self )
      res = farmer_problem_Mex( 'get_solution', self.objectHandle, 'power_required' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = farmer_problem_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = farmer_problem_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = farmer_problem_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = farmer_problem_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      farmer_problem_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = farmer_problem_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      farmer_problem_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x1(), ...
        self.zeta(), self.x2(), ...
        self.zeta(), self.x3(), ...
        self.zeta(), self.res(), ...
        self.zeta(), self.x4(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x1', 'x2', 'x3', 'res', 'x4' );
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
        self.zeta(), self.x1__o(), ...
        self.zeta(), self.x2__o(), ...
        self.zeta(), self.x3__o(), ...
        self.zeta(), self.x4__o(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'x1\_o', 'x2\_o', 'x3\_o', 'x4\_o' );
    end

  end

end

% EOF: farmer_problem.m
