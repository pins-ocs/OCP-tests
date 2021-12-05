%-----------------------------------------------------------------------%
%  file: ICLOCS_ParallelParking.m                                       %
%                                                                       %
%  version: 1.0   date 5/12/2021                                        %
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


classdef ICLOCS_ParallelParking < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = ICLOCS_ParallelParking( name )
      %% Allocate the C++ class instance
      self.objectHandle = ICLOCS_ParallelParking_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      ICLOCS_ParallelParking_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      ICLOCS_ParallelParking_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = ICLOCS_ParallelParking_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      ICLOCS_ParallelParking_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = ICLOCS_ParallelParking_Mex( 'names', self.objectHandle );
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
      res = ICLOCS_ParallelParking_Mex( 'dims', self.objectHandle );
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
      res = ICLOCS_ParallelParking_Mex( 'get_ocp_data', self.objectHandle );
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
      ICLOCS_ParallelParking_Mex( 'infoLevel', self.objectHandle, infoLvl );
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
      ICLOCS_ParallelParking_Mex( 'set_max_threads', self.objectHandle, nt );
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
      ICLOCS_ParallelParking_Mex( 'remesh', self.objectHandle, new_mesh );
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
      ICLOCS_ParallelParking_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = ICLOCS_ParallelParking_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = ICLOCS_ParallelParking_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = ICLOCS_ParallelParking_Mex( 'solve', self.objectHandle, varargin{:} );
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
      ICLOCS_ParallelParking_Mex( ...
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
      sol = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, varargin{:} );
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
      sol = ICLOCS_ParallelParking_Mex( 'get_solution2', self.objectHandle );
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
      sol = ICLOCS_ParallelParking_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = ICLOCS_ParallelParking_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = ICLOCS_ParallelParking_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = x( self )
      %
      % Return the solution for the state: x
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'x' );
    end
    function res = y( self )
      %
      % Return the solution for the state: y
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'y' );
    end
    function res = v( self )
      %
      % Return the solution for the state: v
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'v' );
    end
    function res = a( self )
      %
      % Return the solution for the state: a
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'a' );
    end
    function res = theta( self )
      %
      % Return the solution for the state: theta
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'theta' );
    end
    function res = phi( self )
      %
      % Return the solution for the state: phi
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'phi' );
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
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      %
      % Return the solution for the multiplier: lambda6
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = u1( self )
      %
      % Return the solution for the control: u1
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'u1' );
    end
    function res = u2( self )
      %
      % Return the solution for the control: u2
      %
      res = ICLOCS_ParallelParking_Mex( 'get_solution', self.objectHandle, 'u2' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function U = init_U( self, x, do_minimization )
      %
      % Initialize `u`
      %
      U = ICLOCS_ParallelParking_Mex( 'init_U', self.objectHandle, x, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, x, u_guess )
      %
      % Compute `u`
      %
      U = ICLOCS_ParallelParking_Mex( 'eval_U', self.objectHandle, x, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, x, u )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `x` and `u`.
      %
      [F,ok] = ICLOCS_ParallelParking_Mex( 'eval_F', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, x, u )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x` and `u`.
      %
      [JF,ok] = ICLOCS_ParallelParking_Mex( 'eval_JF', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = ICLOCS_ParallelParking_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [z,u] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [z,u] = ICLOCS_ParallelParking_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, z, u )
      %
      % Set the solution in a vector as stored in PINS.
      %
      ICLOCS_ParallelParking_Mex( 'set_raw_solution', self.objectHandle, z, u );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, z )
      %
      % Return true if the solution does not violate 
      % admissible regions.
      %
      ok = ICLOCS_ParallelParking_Mex( 'check_raw_solution', self.objectHandle, z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, z, u, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      ICLOCS_ParallelParking_Mex( 'check_jacobian', self.objectHandle, z, u, epsi );
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
      [a,c] = ICLOCS_ParallelParking_Mex( 'ac', self.objectHandle, ...
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
      [Ja,Jc] = ICLOCS_ParallelParking_Mex( 'DacDxlxlp', self.objectHandle, ...
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
      [h,c] = ICLOCS_ParallelParking_Mex( 'hc', self.objectHandle, ...
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
      [Jh,Jc] = ICLOCS_ParallelParking_Mex( 'DhcDxlxlop', self.objectHandle, ...
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
      u = ICLOCS_ParallelParking_Mex( 'u', self.objectHandle, ...
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
      DuDxlxlp = ICLOCS_ParallelParking_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = ICLOCS_ParallelParking_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = ICLOCS_ParallelParking_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = ICLOCS_ParallelParking_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = ICLOCS_ParallelParking_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = ICLOCS_ParallelParking_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) = 
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V) 
      %
      % Hx(x,V,lambda,u,p,zeta) = partial_x H(...)
      %
      Hx = ICLOCS_ParallelParking_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `pars`.
      %
      J = ICLOCS_ParallelParking_Mex(...
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
      Hu = ICLOCS_ParallelParking_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = ICLOCS_ParallelParking_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ParallelParking_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = ICLOCS_ParallelParking_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = ICLOCS_ParallelParking_Mex( ...
        'DboundaryConditionsDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = ICLOCS_ParallelParking_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = ICLOCS_ParallelParking_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = ICLOCS_ParallelParking_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = ICLOCS_ParallelParking_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = ICLOCS_ParallelParking_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, u, pars )
      J = ICLOCS_ParallelParking_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      J = ICLOCS_ParallelParking_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = ICLOCS_ParallelParking_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxup = eval_DlagrangeDxup( self, iseg, q, x, u, pars )
      DlagrangeDxup = ICLOCS_ParallelParking_Mex( ...
        'DlagrangeDxup', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               pars )
      target = ICLOCS_ParallelParking_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, q_L, x_L, ...
                                                 iseg_R, q_R, x_R, ...
                                                 pars )
      DmayerDxxp = ICLOCS_ParallelParking_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = ICLOCS_ParallelParking_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = ICLOCS_ParallelParking_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = ICLOCS_ParallelParking_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = Ax( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ax_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ax_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ay_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ay_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Bx_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Bx_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = By_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('By_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cx_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cx_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Cy_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Cy_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dx_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dx_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Dy_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Dy_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ox_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ox_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Oy_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Oy_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ex_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ex_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = Ey_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('Ey_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = area( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_1( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_1', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_2( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_2', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_3( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_3', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_1_1( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_1_1', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_1_2( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_1_2', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_1_3( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_1_3', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_2_2( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_2_2', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_2_3( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_2_3', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area_D_3_3( self, xo__a, xo__b, xo__c )
      res = ICLOCS_ParallelParking_Mex('area_D_3_3', self.objectHandle, xo__a, xo__b, xo__c );
    end
    % ---------------------------------------------------------------------
    function res = area2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_1( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_1', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_1_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_1_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_2_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_2_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_3_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_3_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_3_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_3_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_3_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_3_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_3_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_3_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_4_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_4_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_4_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_4_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_4_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_4_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_5_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_5_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_5_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_5_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = area2_D_6_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y )
      res = ICLOCS_ParallelParking_Mex('area2_D_6_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_1( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_1', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_2( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_2', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_3( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_3', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_4( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_4', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_1_1( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_1_1', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_1_2( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_1_2', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_1_3( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_1_3', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_1_4( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_1_4', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_2_2( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_2_2', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_2_3( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_2_3', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_2_4( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_2_4', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_3_3( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_3_3', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_3_4( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_3_4', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ_D_4_4( self, xo__a, xo__b, xo__c, xo__d )
      res = ICLOCS_ParallelParking_Mex('areaQ_D_4_4', self.objectHandle, xo__a, xo__b, xo__c, xo__d );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_1( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_1', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_1_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_1_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_2( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_2', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_2_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_2_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_3( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_3', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_3_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_3_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4_4( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4_4', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_4_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_4_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_5_5( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_5_5', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_5_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_5_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_5_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_5_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_5_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_5_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_6_6( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_6_6', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_6_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_6_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_6_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_6_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_7_7( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_7_7', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_7_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_7_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = areaQ2_D_8_8( self, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y )
      res = ICLOCS_ParallelParking_Mex('areaQ2_D_8_8', self.objectHandle, xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y );
    end
    % ---------------------------------------------------------------------
    function res = AEB( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AEB_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AEB_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BEC_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BEC_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = CED_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('CED_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DEA_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DEA_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = AOB_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('AOB_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = BOC_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('BOC_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = COD_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('COD_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = DOA_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('DOA_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_1_1( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_1_1', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_1_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_1_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_1_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_1_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_2_2( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_2_2', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_2_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_2_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = ABCD_D_3_3( self, xo__x, xo__y, xo__theta )
      res = ICLOCS_ParallelParking_Mex('ABCD_D_3_3', self.objectHandle, xo__x, xo__y, xo__theta );
    end
    % ---------------------------------------------------------------------
    function res = f_slot( self, xo__x )
      res = ICLOCS_ParallelParking_Mex('f_slot', self.objectHandle, xo__x );
    end
    % ---------------------------------------------------------------------
    function res = f_slot_D( self, xo__x )
      res = ICLOCS_ParallelParking_Mex('f_slot_D', self.objectHandle, xo__x );
    end
    % ---------------------------------------------------------------------
    function res = f_slot_DD( self, xo__x )
      res = ICLOCS_ParallelParking_Mex('f_slot_DD', self.objectHandle, xo__x );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.y(), ...
        self.zeta(), self.v(), ...
        self.zeta(), self.a(), ...
        self.zeta(), self.theta(), ...
        self.zeta(), self.phi(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'y', 'v', 'a', 'th\eta', '\phi' );
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
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5', '\lambda6' );
    end
    % ---------------------------------------------------------------------
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

% EOF: ICLOCS_ParallelParking.m
