%-----------------------------------------------------------------------%
%  file: CNOC.m                                                         %
%                                                                       %
%  version: 1.0   date 12/11/2020                                       %
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


classdef CNOC < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = CNOC( name )
      %% Allocate the C++ class instance
      self.objectHandle = CNOC_Mex( 'new', name );
    end

    function delete( self )
      %% Destroy the C++ class instance
      CNOC_Mex( 'delete', self.objectHandle );
    end

    function help( self )
      %% print help for the class usage
      CNOC_Mex('help');
    end

    % -------------------------------------------------------------------------
    % INITIALIZATION
    % -------------------------------------------------------------------------
    function data = read( self, fname )
      % read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      data = CNOC_Mex( 'read', self.objectHandle, fname );
    end

    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      CNOC_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = CNOC_Mex( 'names', self.objectHandle );
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
      res = CNOC_Mex( 'dims', self.objectHandle );
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
      res = CNOC_Mex( 'get_ocp_data', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % INFO LEVEL
    % -------------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      % set information level
      CNOC_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % -------------------------------------------------------------------------
    % NUM THREAD
    % -------------------------------------------------------------------------
    function N_thread( self, nt )
      % set information level
      CNOC_Mex( 'N_thread', self.objectHandle, nt );
    end

    % -------------------------------------------------------------------------
    % GUESS
    % -------------------------------------------------------------------------
    function set_guess( self, varargin )
      % with no argument use predefined guess, otherwise
      % use structure to initialize guess
      CNOC_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      % return a structure with the stored guess
      guess = CNOC_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      % return a structure with the solution formatted as a guess
      guess = CNOC_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % -------------------------------------------------------------------------
    % SOLVE
    % -------------------------------------------------------------------------
    function ok = solve( self, varargin )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      % varargin{1} = timeout
      ok = CNOC_Mex( 'solve', self.objectHandle, varargin{:} );
    end

    function updateContinuation( self, n, s )
      % set parameter of the problem for continuation step `n` at fraction `s`
      %
      CNOC_Mex( 'updateContinuation', self.objectHandle, n, s );
    end

    % -------------------------------------------------------------------------
    % GET SOLUTION
    % -------------------------------------------------------------------------
    function sol = solution( self, varargin )
      sol = CNOC_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end

    function sol = pack( self, X, Lambda, Pars, Omega )
      sol = CNOC_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end

    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      [X, Lambda, Pars, Omega] = CNOC_Mex( 'unpack', self.objectHandle, sol );
    end

    % -------------------------------------------------------------------------
    % ZETA
    % -------------------------------------------------------------------------
    function res = zeta( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % -------------------------------------------------------------------------
    % STATES
    % -------------------------------------------------------------------------
    function res = s( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 's', varargin{:} );
    end
    function res = n( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'n', varargin{:} );
    end
    function res = vs( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vs', varargin{:} );
    end
    function res = vn( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vn', varargin{:} );
    end
    function res = as( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'as', varargin{:} );
    end
    function res = an( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'an', varargin{:} );
    end
    function res = coV( self, varargin  )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'coV', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % MULTIPLIER
    % -------------------------------------------------------------------------
    function res = lambda1( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda1__xo', varargin{:} );
    end
    function res = lambda2( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda2__xo', varargin{:} );
    end
    function res = lambda3( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda3__xo', varargin{:} );
    end
    function res = lambda4( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda4__xo', varargin{:} );
    end
    function res = lambda5( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda5__xo', varargin{:} );
    end
    function res = lambda6( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda6__xo', varargin{:} );
    end
    function res = lambda7( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda7__xo', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % CONTROLS
    % -------------------------------------------------------------------------
    function res = js( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'js', varargin{:} );
    end
    function res = jn( self, varargin )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jn', varargin{:} );
    end

    % -------------------------------------------------------------------------
    % POSTPROCESSING
    % -------------------------------------------------------------------------
    function res = feed( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'feed' );
    end
    function res = acc( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'acc' );
    end
    function res = jerk( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jerk' );
    end
    function res = vx( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vx' );
    end
    function res = vy( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vy' );
    end
    function res = ax( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ax' );
    end
    function res = ay( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ay' );
    end
    function res = jx( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jx' );
    end
    function res = jy( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jy' );
    end
    function res = X_minus_path( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-path' );
    end
    function res = Y_minus_path( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-path' );
    end
    function res = X_minus_traj( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-traj' );
    end
    function res = Y_minus_traj( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-traj' );
    end
    function res = X_minus_left( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-left' );
    end
    function res = Y_minus_left( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-left' );
    end
    function res = X_minus_right( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-right' );
    end
    function res = Y_minus_right( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-right' );
    end

    % -------------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % -------------------------------------------------------------------------
    function F = eval_F( self, x )
      F = CNOC_Mex( 'eval_F', self.objectHandle, x );
    end

    function JF = eval_JF( self, x )
      JF = CNOC_Mex( 'eval_JF', self.objectHandle, x );
    end

    function JF = eval_JF_pattern( self )
      JF = CNOC_Mex( 'eval_JF_pattern', self.objectHandle );
    end

    function x = get_raw_solution( self )
      x = CNOC_Mex( 'get_raw_solution', self.objectHandle );
    end

    function set_raw_solution( self, x )
      CNOC_Mex( 'set_raw_solution', self.objectHandle, x );
    end

    function ok = check_raw_solution( self, x )
      ok = CNOC_Mex( 'check_raw_solution', self.objectHandle, x );
    end

    function check_jacobian( self, x, epsi )
      CNOC_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end

    function [a,c] = get_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars, U )
      [a,c] = CNOC_Mex( 'a', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end

    function [h,c] = get_hc( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      [h,c] = CNOC_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end

    % -------------------------------------------------------------------------
    % PLOT SOLUTION
    % -------------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.s(), ...
        self.zeta(), self.n(), ...
        self.zeta(), self.vs(), ...
        self.zeta(), self.vn(), ...
        self.zeta(), self.as(), ...
        self.zeta(), self.an(), ...
        self.zeta(), self.coV(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 's', 'n', 'vs', 'vn', 'as', 'an', 'coV' );
    end

    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        self.zeta(), self.lambda4(), ...
        self.zeta(), self.lambda5(), ...
        self.zeta(), self.lambda6(), ...
        self.zeta(), self.lambda7(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5', '\lambda6', '\lambda7' );
    end

    function plot_controls( self )
      plot(...
        self.zeta(), self.js(), ...
        self.zeta(), self.jn(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'js', 'jn' );
    end

  end

end

% EOF: CNOC.m
