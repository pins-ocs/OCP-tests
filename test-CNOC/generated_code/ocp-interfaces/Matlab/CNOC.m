%-----------------------------------------------------------------------%
%  file: CNOC.m                                                         %
%                                                                       %
%  version: 1.0   date 13/12/2021                                       %
%                                                                       %
%  Copyright (C) 2021                                                   %
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
    % ---------------------------------------------------------------------
    function self = CNOC( name )
      %% Allocate the C++ class instance
      self.objectHandle = CNOC_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      CNOC_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      CNOC_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = CNOC_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      CNOC_Mex( 'setup', self.objectHandle, fname_or_struct );
    end
    % ---------------------------------------------------------------------
    function n = names( self )
      %
      % Return a MATLAB structures collecting the names of the variable, states etc
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
      %
      n = CNOC_Mex( 'names', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = dims( self )
      %
      % Return a MATLAB structures collecting the dimension of the OCP problem:
      % res.dim_q     = number of mesh variables (variables computed ad mesh nodes)
      % res.dim_x     = number of states
      % res.dim_u     = number of controls
      % res.dim_pars  = number of parameters
      % res.dim_omega = number of mutipliers associated to BC
      % res.dim_bc    = number of BC
      % res.num_nodes = number of nodes of the discretization grid
      % res.neq       = number of equations
      %
      res = CNOC_Mex( 'dims', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_ocp_data( self )
      %
      % Return a structure with data and solution (if computed) of the OCP problem
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
      %
      res = CNOC_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO LEVEL
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      %
      % Set information level
      %
      CNOC_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NUM THREAD
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_max_threads( self, nt )
      %
      % Set the maximum number of threads used.
      %
      CNOC_Mex( 'set_max_threads', self.objectHandle, nt );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % REMESH
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function remesh( self, new_mesh )
      %
      % Use structure to replace the old mesh
      % readed and defined with a setup('file') method 
      % with the mesh contained in new_mesh.
      % The old mesh and the new mesh do not need to be
      % of the same type. After mesh replacement a new
      % setup command is executed.
      % For mesh refinement provide splines or node/values list.
      %
      CNOC_Mex( 'remesh', self.objectHandle, new_mesh );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GUESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_guess( self, varargin )
      %
      % With no argument use predefined guess, otherwise
      % use structure to initialize guess.
      %
      CNOC_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = CNOC_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = CNOC_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % SOLVE
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function ok = solve( self, varargin )
      %
      % ok = false if computation failed
      % ok = true if computation is succesfull
      % varargin{1} = timeout (if present)
      %
      ok = CNOC_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function update_continuation( self, n, old_s, s )
      %
      % Set parameter of the problem for continuation.
      %
      % The nonlinear system is of the form 
      % F(x) = F_{n-1}(x)*(1-s)+F_{n}(x)*s
      % depends on the stage `n` and parameter `s` of 
      % the continuation.
      %
      CNOC_Mex( ...
        'update_continuation', self.objectHandle, n, old_s, s ...
      );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GET SOLUTION
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    %
    % common solution fields
    % res.model_name;
    % res.cpu_time;
    % res.converged;
    % res.lapack;         % used LA package name
    % res.num_equations;
    % res.num_parameters;
    % res.solution_saved; % true if solution will be saved into the structure
    % res.solver_type;    % string: name of the solver used
    % res.nonlinear_system_solver.iterations;
    % res.nonlinear_system_solver.tolerance;
    % res.nonlinear_system_solver.message;       % string of last error
    % res.nonlinear_system_solver.max_iter;      % maximium iteration first stage 
    % res.nonlinear_system_solver.max_step_iter; % maximium iteration continuation step 
    % res.nonlinear_system_solver.max_accumulated_iter;
    % res.nonlinear_system_solver.continuation.initial_step;
    % res.nonlinear_system_solver.continuation.min_step;
    % res.nonlinear_system_solver.continuation.reduce_factor;
    % res.nonlinear_system_solver.continuation.augment_factor;
    % res.nonlinear_system_solver.continuation.few_iterations;
    % res.nonlinear_system_solver.target.lagrange;          % integral value
    % res.nonlinear_system_solver.target.mayer;
    % res.nonlinear_system_solver.target.penalties;         % integral value
    % res.nonlinear_system_solver.target.control_penalties; % integral value
    % res.nonlinear_system_solver.parameters; % optimization parameters
    %
    function sol = solution( self, varargin )
      %
      % Return the whole solution or the column of name varargin{1}.
      %
      % the whole solution adds
      % res.headers % name of the columns
      % res.idx     % struct with field name of the column and value index of the column
      %             % C-indexing starting from 0.
      % res.data    % matrix with columns the computed solution 
      %
      %
      sol = CNOC_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution_by_group( self )
      %
      % Return the whole solution in a different format
      %
      % cell arrays of strings with OCP names
      % res.q_names; 
      % res.names.u_names;
      % res.names.x_names;
      % res.names.lambda_names;
      % res.names.mu_names;
      % res.names.x_D_names;
      % res.names.mu_D_names;
      %
      % arrays with data
      % res.data.q
      % res.data.u
      % res.data.x
      % res.data.lambda
      % res.data.mu
      % res.data.u_cell
      % res.data.x_D
      % res.data.mu_D
      % res.data.i_segment
      % res.data.lagrange_target
      % res.data.penalties
      % res.data.control_penalties
      sol = CNOC_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution_by_group_and_names( self )
      %
      % Return the whole solution in a different format
      %
      % struct of vectors with OCP solutions
      %
      % res.data.q  -> struct whose fields are the name of the columns of the data
      % res.data.u
      % res.data.x
      % res.data.lambda
      % res.data.mu
      % res.data.u_cell
      % res.data.x_D
      % res.data.mu_D
      % res.data.i_segment
      % res.data.lagrange_target
      % res.data.penalties
      % res.data.control_penalties
      %
      sol = CNOC_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = CNOC_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = CNOC_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = s( self )
      %
      % Return the solution for the state: s
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 's' );
    end
    function res = n( self )
      %
      % Return the solution for the state: n
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'n' );
    end
    function res = vs( self )
      %
      % Return the solution for the state: vs
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vs' );
    end
    function res = vn( self )
      %
      % Return the solution for the state: vn
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vn' );
    end
    function res = as( self )
      %
      % Return the solution for the state: as
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'as' );
    end
    function res = an( self )
      %
      % Return the solution for the state: an
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'an' );
    end
    function res = coV( self )
      %
      % Return the solution for the state: coV
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'coV' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % MULTIPLIER
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = lambda1( self )
      %
      % Return the solution for the multiplier: lambda1
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      %
      % Return the solution for the multiplier: lambda6
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
    end
    function res = lambda7( self )
      %
      % Return the solution for the multiplier: lambda7
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'lambda7__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = js( self )
      %
      % Return the solution for the control: js
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'js' );
    end
    function res = jn( self )
      %
      % Return the solution for the control: jn
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jn' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_feed( self )
      %
      % Return the solution for the post processing variable: feed
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'feed' );
    end
    function res = post_processing_acc( self )
      %
      % Return the solution for the post processing variable: acc
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'acc' );
    end
    function res = post_processing_jerk( self )
      %
      % Return the solution for the post processing variable: jerk
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jerk' );
    end
    function res = post_processing_vx( self )
      %
      % Return the solution for the post processing variable: vx
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vx' );
    end
    function res = post_processing_vy( self )
      %
      % Return the solution for the post processing variable: vy
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'vy' );
    end
    function res = post_processing_ax( self )
      %
      % Return the solution for the post processing variable: ax
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ax' );
    end
    function res = post_processing_ay( self )
      %
      % Return the solution for the post processing variable: ay
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'ay' );
    end
    function res = post_processing_jx( self )
      %
      % Return the solution for the post processing variable: jx
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jx' );
    end
    function res = post_processing_jy( self )
      %
      % Return the solution for the post processing variable: jy
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'jy' );
    end
    function res = post_processing_X_minus_path( self )
      %
      % Return the solution for the post processing variable: X_minus_path
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-path' );
    end
    function res = post_processing_Y_minus_path( self )
      %
      % Return the solution for the post processing variable: Y_minus_path
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-path' );
    end
    function res = post_processing_X_minus_traj( self )
      %
      % Return the solution for the post processing variable: X_minus_traj
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-traj' );
    end
    function res = post_processing_Y_minus_traj( self )
      %
      % Return the solution for the post processing variable: Y_minus_traj
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-traj' );
    end
    function res = post_processing_X_minus_left( self )
      %
      % Return the solution for the post processing variable: X_minus_left
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-left' );
    end
    function res = post_processing_Y_minus_left( self )
      %
      % Return the solution for the post processing variable: Y_minus_left
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-left' );
    end
    function res = post_processing_X_minus_right( self )
      %
      % Return the solution for the post processing variable: X_minus_right
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'X-right' );
    end
    function res = post_processing_Y_minus_right( self )
      %
      % Return the solution for the post processing variable: Y_minus_right
      %
      res = CNOC_Mex( 'get_solution', self.objectHandle, 'Y-right' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function U = init_U( self, x, do_minimization )
      %
      % Initialize `u`
      %
      U = CNOC_Mex( 'init_U', self.objectHandle, x, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, x, u_guess )
      %
      % Compute `u`
      %
      U = CNOC_Mex( 'eval_U', self.objectHandle, x, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, x, u )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `x` and `u`.
      %
      [F,ok] = CNOC_Mex( 'eval_F', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, x, u )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x` and `u`.
      %
      [JF,ok] = CNOC_Mex( 'eval_JF', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = CNOC_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [z,u] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [z,u] = CNOC_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, z, u )
      %
      % Set the solution in a vector as stored in PINS.
      %
      CNOC_Mex( 'set_raw_solution', self.objectHandle, z, u );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, z )
      %
      % Return true if the solution does not violate 
      % admissible regions.
      %
      ok = CNOC_Mex( 'check_raw_solution', self.objectHandle, z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, z, u, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      CNOC_Mex( 'check_jacobian', self.objectHandle, z, u, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,c] = eval_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, ...
                                    pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      % <<FD1.jpg>>
      %
      [a,c] = CNOC_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [Ja,Jc] = eval_DacDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                             iseg_R, q_R, x_R, lambda_R, ...
                                             pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      % <<FD2.jpg>>
      %
      [Ja,Jc] = CNOC_Mex( 'DacDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars )
      %
      % Compute the block of the BC of the nonlinear
      % system given left and right states.
      %
      % <<FD3.jpg>>
      %
      [h,c] = CNOC_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlxlop( self, iseg_L, q_L, x_L, lambda_L, ...
                                              iseg_R, q_R, x_R, lambda_R, pars )
      %
      % Compute the block of the BC of the nonlinear system
      % given left and right states.
      %
      % <<FD4.jpg>>
      %
      [Jh,Jc] = CNOC_Mex( 'DhcDxlxlop', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTINUOUS PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function u = eval_u( self, iseg_L, q_L, x_L, lambda_L, ...
                               iseg_R, q_R, x_R, lambda_R, ...
                               pars )
      %
      % Compute the control given states and multiplyers.
      %
      u = CNOC_Mex( 'u', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DuDxlxlp = eval_DuDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                             iseg_R, q_R, x_R, lambda_R, ...
                                             pars )
      %
      % Compute the jacobian of controls given states and multiplyers.
      %
      DuDxlxlp = CNOC_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = CNOC_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = CNOC_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = CNOC_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = CNOC_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = CNOC_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = CNOC_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = CNOC_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = CNOC_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) = 
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V) 
      %
      % Hx(x,V,lambda,u,p,zeta) = partial_x H(...)
      %
      Hx = CNOC_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `pars`.
      %
      J = CNOC_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hu = eval_Hu( self, iseg, q, x, lambda, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) = 
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V) 
      %
      % Hu(x,lambda,u,p,zeta) = partial_u H(...)
      %
      Hu = CNOC_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = CNOC_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = CNOC_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = CNOC_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = CNOC_Mex( ...
        'DboundaryConditionsDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = CNOC_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = CNOC_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = CNOC_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = CNOC_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = CNOC_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, u, pars )
      J = CNOC_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      J = CNOC_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = CNOC_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxup = eval_DlagrangeDxup( self, iseg, q, x, u, pars )
      DlagrangeDxup = CNOC_Mex( ...
        'DlagrangeDxup', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               pars )
      target = CNOC_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, q_L, x_L, ...
                                                 iseg_R, q_R, x_R, ...
                                                 pars )
      DmayerDxxp = CNOC_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = CNOC_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = CNOC_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = CNOC_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
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
    % ---------------------------------------------------------------------
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
    % ---------------------------------------------------------------------
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