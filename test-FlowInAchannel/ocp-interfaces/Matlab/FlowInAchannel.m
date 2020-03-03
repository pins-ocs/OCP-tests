%-----------------------------------------------------------------------%
%  file: FlowInAchannel.m                                               %
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


classdef FlowInAchannel < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = FlowInAchannel( name )
      self.objectHandle = FlowInAchannel_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      FlowInAchannel_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      FlowInAchannel_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      data = FlowInAchannel_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      FlowInAchannel_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = FlowInAchannel_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = FlowInAchannel_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = FlowInAchannel_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      FlowInAchannel_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      FlowInAchannel_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      guess = FlowInAchannel_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      guess = FlowInAchannel_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = FlowInAchannel_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      FlowInAchannel_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = FlowInAchannel_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = FlowInAchannel_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = FlowInAchannel_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = u( self, varargin  )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'u', varargin{:} );
    end
    function res = u1( self, varargin  )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'u1', varargin{:} );
    end
    function res = u2( self, varargin  )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'u2', varargin{:} );
    end
    function res = u3( self, varargin  )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'u3', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = FlowInAchannel_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = FlowInAchannel_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = FlowInAchannel_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = FlowInAchannel_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = FlowInAchannel_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      FlowInAchannel_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = FlowInAchannel_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      FlowInAchannel_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.u(), ...
        self.zeta(), self.u1(), ...
        self.zeta(), self.u2(), ...
        self.zeta(), self.u3(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'u', 'u1', 'u2', 'u3' );
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
        'Linewidth', 2 ...
      );
      title('controls');
      legend(  );
    end

  end

end

% EOF: FlowInAchannel.m
