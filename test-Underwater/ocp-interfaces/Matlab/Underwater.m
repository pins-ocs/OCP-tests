%-----------------------------------------------------------------------%
%  file: Underwater.m                                                   %
%                                                                       %
%  version: 1.0   date 21/7/2020                                        %
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
      %% Allocate the C++ class instance
      self.objectHandle = Underwater_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      Underwater_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      %% print help for the class usage
      Underwater_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      % read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      data = Underwater_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      Underwater_Mex( 'setup', self.objectHandle, fname_or_struct );
    end

    function n = names( self )
      % return a MATLAB structures collecting the names of the variable, states etc
      % of the OCP problem:
      %
      % n.state_names                  = cell array of strings
      % n.lagrange_multiplier_names    = cell array of strings
      % n.control_names                = cell array of strings
      % n.mesh_variable_names          = cell array of strings
      % n.parameter_names              = cell array of strings
      % n.bc_lagrange_multiplier_names = cell array of strings
      % n.post_processing_names        = cell array of strings, post processing variables name
      % n.model_names                  = cell array of strings, names of model parameters
      n = Underwater_Mex( 'names', self.objectHandle );
    end

    function res = dims( self )
      % return a MATLAB structures collecting the dimension of the OCP problem:
      % res.dim_q     = number of mesh variables (variables computed ad mesh nodes)
      % res.dim_x     = number of states
      % res.dim_u     = number of controls
      % res.dim_pars  = number of parameters
      % res.dim_omega = number of mutipliers associated to BC
      % res.dim_bc    = number of BC
      % res.num_nodes = number of nodes of the discretization grid
      % res.neq       = number of equations
      res = Underwater_Mex( 'dims', self.objectHandle );
    end

    function res = get_ocp_data( self )
      % return a structure with data and solution (if computed) of the OCP problem
      % information level possible values: -1,0,1,2,3,4
      % res.InfoLevel
      %
      % number of thread for computation
      % res.N_threads    = maximum number of available thread
      % res.LU_threaded  = number of thread for LU factorization
      % res.F_threaded   = number of thread for F(X) computation
      % res.JF_threaded  = number of thread for JF(X) computation
      % res.U_threaded   = number of thread for controls computation
      %
      % res.ControlSolver = structure with the fields
      %   res.ControlSolver.InfoLevel
      %   Iterative                        true/false (use iterative method for control computation)
      %   res.ControlSolver.MaxIter        maximum number of iteration
      %   res.ControlSolver.Tolerance      tolerance for stopping iteration
      %   res.ControlSolver.factorization: factorization used (e.g. 'LU')
      %
      % res.Solver = structure with the fields
      %   res.Solver.solver               = used solver, 'Hyness', 'DumpedNewton'
      %   res.Solver.tolerance            = used tolerance,  e.g. 1e-9
      %   res.Solver.factorization        = used factorization e.g. 'LU', 'QR'
      %   res.Solver.last_factorization   = used last factorization for cyclic reduction, e.g 'LU', 'QR'
      %   res.Solver.max_accumulated_iter = maximum number of total iterations, e.g. 800
      %   res.Solver.max_iter             = maximum number of iterations, e.g. 300 (for the forst stage)
      %   res.Solver.max_step_iter        = maximum number of iterations for a sub-step of continuation
      %   res.Solver.continuation         = structure with parameter driwing continuation
      %     res.Solver.continuation.augment_factor = 1.5
      %     res.Solver.continuation.few_iterations = 8
      %     res.Solver.continuation.initial_step   = 0.2
      %     res.Solver.continuation.min_step       = 1e-03
      %     res.Solver.continuation.reduce_factor  = 0.5
      %   res.Solver.ns_continuation_begin = initial stage of continuation
      %   res.Solver.ns_continuation_end   = final+1 stage of continuation
      %
      % res.Guess                  = structure with the used guess
      % res.Parameters             = cell array with the model parameters
      % res.RedirectStreamToString = true/false
      %
      % FiniteDifferenceJacobian: true/false (use finite difference jacobian)
      % res.JacobianCheck: true/false
      % res.JacobianCheckFull: true/false
      % res.JacobianCheck_epsilon: 1e-04 (tolerance for finite difference check)
      %
      % res.BoundaryConditions = structure with the activation status of the BC
      % res.Constraints: [1×1 struct]
      % res.Controls: [1×1 struct]
      % res.Doctor: 0
      % res.MappedObjects
      % res.Mesh
      % res.OutputSplines
      % res.Pointers
      res = Underwater_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      % set information level
      Underwater_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      % with no argument use predefined guess, otherwise
      % use structure to initialize guess
      Underwater_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      % return a structure with the stored guess
      guess = Underwater_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      % return a structure with the solution formatted as a guess
      guess = Underwater_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self, varargin )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      % varargin{1} = timeout
      ok = Underwater_Mex( 'solve', self.objectHandle, varargin{:} );
    end

    function updateContinuation( self, n, s )
      % set parameter of the problem for continuation step `n` at fraction `s`
      %
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
