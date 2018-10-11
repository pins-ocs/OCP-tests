%-----------------------------------------------------------------------%
%  file: PathConstrained.m                                              %
%                                                                       %
%  version: 1.0   date 17/8/2018                                        %
%                                                                       %
%  Copyright (C) 2018                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


classdef PathConstrained < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = PathConstrained( name, infoLevel )
      self.objectHandle = PathConstrained_Mex( 'new', name, infoLevel );
    end

    function delete( self )
      %% Destroy the C++ class instance
      PathConstrained_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      PathConstrained_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function setup( self, fname_or_struct )
      PathConstrained_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      n = PathConstrained_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      res = PathConstrained_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      res = PathConstrained_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function guess( self, varargin )
      PathConstrained_Mex( 'guess', self.objectHandle, varargin{:} );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      ok = PathConstrained_Mex( 'solve', self.objectHandle );
    end

    function updateContinuation( self, n, s )
      PathConstrained_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = PathConstrained_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Ommega )
      sol = PathConstrained_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Ommega );
    end

    function [X, Lambda, Pars, Ommega] = unpack( self, sol )
      [X, Lambda, Pars, Ommega] = PathConstrained_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = x1( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'x1' );
    end
    function res = x2( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'x2' );
    end
    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = u( self )
      res = PathConstrained_Mex( 'get_solution', self.objectHandle, 'u' );
    end
    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = PathConstrained_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = PathConstrained_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = PathConstrained_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = PathConstrained_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      PathConstrained_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = PathConstrained_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      PathConstrained_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x1(), ...
        self.zeta(), self.x2(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x1', 'x2' );
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
        self.zeta(), self.u(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'u' );
    end

  end

end

% EOF: PathConstrained.m