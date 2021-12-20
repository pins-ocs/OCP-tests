%-----------------------------------------------------------------------%
%  file: gtocX_2burn_pars.m                                             %
%                                                                       %
%  version: 1.0   date 20/12/2021                                       %
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


classdef gtocX_2burn_pars < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = gtocX_2burn_pars( name )
      %% Allocate the C++ class instance
      self.objectHandle = gtocX_2burn_pars_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      gtocX_2burn_pars_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      gtocX_2burn_pars_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = gtocX_2burn_pars_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      gtocX_2burn_pars_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = gtocX_2burn_pars_Mex( 'names', self.objectHandle );
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
      res = gtocX_2burn_pars_Mex( 'dims', self.objectHandle );
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
      res = gtocX_2burn_pars_Mex( 'get_ocp_data', self.objectHandle );
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
      gtocX_2burn_pars_Mex( 'infoLevel', self.objectHandle, infoLvl );
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
      gtocX_2burn_pars_Mex( 'set_max_threads', self.objectHandle, nt );
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
      gtocX_2burn_pars_Mex( 'remesh', self.objectHandle, new_mesh );
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
      gtocX_2burn_pars_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = gtocX_2burn_pars_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = gtocX_2burn_pars_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = gtocX_2burn_pars_Mex( 'solve', self.objectHandle, varargin{:} );
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
      gtocX_2burn_pars_Mex( ...
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
      sol = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, varargin{:} );
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
      sol = gtocX_2burn_pars_Mex( 'get_solution2', self.objectHandle );
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
      sol = gtocX_2burn_pars_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = gtocX_2burn_pars_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = gtocX_2burn_pars_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = f( self )
      %
      % Return the solution for the state: f
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'f' );
    end
    function res = g( self )
      %
      % Return the solution for the state: g
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'g' );
    end
    function res = L( self )
      %
      % Return the solution for the state: L
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'L' );
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
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_time( self )
      %
      % Return the solution for the post processing variable: time
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'time' );
    end
    function res = post_processing_ray( self )
      %
      % Return the solution for the post processing variable: ray
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'ray' );
    end
    function res = post_processing_X( self )
      %
      % Return the solution for the post processing variable: X
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X' );
    end
    function res = post_processing_Y( self )
      %
      % Return the solution for the post processing variable: Y
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y' );
    end
    function res = post_processing_Z( self )
      %
      % Return the solution for the post processing variable: Z
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z' );
    end
    function res = post_processing_VX( self )
      %
      % Return the solution for the post processing variable: VX
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX' );
    end
    function res = post_processing_VY( self )
      %
      % Return the solution for the post processing variable: VY
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY' );
    end
    function res = post_processing_VZ( self )
      %
      % Return the solution for the post processing variable: VZ
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ' );
    end
    function res = post_processing_X_begin( self )
      %
      % Return the solution for the post processing variable: X_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X_begin' );
    end
    function res = post_processing_Y_begin( self )
      %
      % Return the solution for the post processing variable: Y_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y_begin' );
    end
    function res = post_processing_Z_begin( self )
      %
      % Return the solution for the post processing variable: Z_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z_begin' );
    end
    function res = post_processing_VX_begin( self )
      %
      % Return the solution for the post processing variable: VX_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX_begin' );
    end
    function res = post_processing_VY_begin( self )
      %
      % Return the solution for the post processing variable: VY_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY_begin' );
    end
    function res = post_processing_VZ_begin( self )
      %
      % Return the solution for the post processing variable: VZ_begin
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ_begin' );
    end
    function res = post_processing_X_end( self )
      %
      % Return the solution for the post processing variable: X_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'X_end' );
    end
    function res = post_processing_Y_end( self )
      %
      % Return the solution for the post processing variable: Y_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Y_end' );
    end
    function res = post_processing_Z_end( self )
      %
      % Return the solution for the post processing variable: Z_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'Z_end' );
    end
    function res = post_processing_VX_end( self )
      %
      % Return the solution for the post processing variable: VX_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VX_end' );
    end
    function res = post_processing_VY_end( self )
      %
      % Return the solution for the post processing variable: VY_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VY_end' );
    end
    function res = post_processing_VZ_end( self )
      %
      % Return the solution for the post processing variable: VZ_end
      %
      res = gtocX_2burn_pars_Mex( 'get_solution', self.objectHandle, 'VZ_end' );
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
      U = gtocX_2burn_pars_Mex( 'init_U', self.objectHandle, x, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, x, u_guess )
      %
      % Compute `u`
      %
      U = gtocX_2burn_pars_Mex( 'eval_U', self.objectHandle, x, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, x, u )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `x` and `u`.
      %
      [F,ok] = gtocX_2burn_pars_Mex( 'eval_F', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, x, u )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x` and `u`.
      %
      [JF,ok] = gtocX_2burn_pars_Mex( 'eval_JF', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = gtocX_2burn_pars_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [z,u] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [z,u] = gtocX_2burn_pars_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, z, u )
      %
      % Set the solution in a vector as stored in PINS.
      %
      gtocX_2burn_pars_Mex( 'set_raw_solution', self.objectHandle, z, u );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, z )
      %
      % Return true if the solution does not violate 
      % admissible regions.
      %
      ok = gtocX_2burn_pars_Mex( 'check_raw_solution', self.objectHandle, z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, z, u, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      gtocX_2burn_pars_Mex( 'check_jacobian', self.objectHandle, z, u, epsi );
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
      [a,c] = gtocX_2burn_pars_Mex( 'ac', self.objectHandle, ...
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
      [Ja,Jc] = gtocX_2burn_pars_Mex( 'DacDxlxlp', self.objectHandle, ...
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
      [h,c] = gtocX_2burn_pars_Mex( 'hc', self.objectHandle, ...
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
      [Jh,Jc] = gtocX_2burn_pars_Mex( 'DhcDxlxlop', self.objectHandle, ...
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
      u = gtocX_2burn_pars_Mex( 'u', self.objectHandle, ...
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
      DuDxlxlp = gtocX_2burn_pars_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = gtocX_2burn_pars_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = gtocX_2burn_pars_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = gtocX_2burn_pars_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = gtocX_2burn_pars_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = gtocX_2burn_pars_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = gtocX_2burn_pars_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) = 
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V) 
      %
      % Hx(x,V,lambda,u,p,zeta) = partial_x H(...)
      %
      Hx = gtocX_2burn_pars_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `pars`.
      %
      J = gtocX_2burn_pars_Mex(...
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
      Hu = gtocX_2burn_pars_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = gtocX_2burn_pars_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = gtocX_2burn_pars_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = gtocX_2burn_pars_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = gtocX_2burn_pars_Mex( ...
        'DboundaryConditionsDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = gtocX_2burn_pars_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = gtocX_2burn_pars_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = gtocX_2burn_pars_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = gtocX_2burn_pars_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = gtocX_2burn_pars_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, u, pars )
      J = gtocX_2burn_pars_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      J = gtocX_2burn_pars_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = gtocX_2burn_pars_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxup = eval_DlagrangeDxup( self, iseg, q, x, u, pars )
      DlagrangeDxup = gtocX_2burn_pars_Mex( ...
        'DlagrangeDxup', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               pars )
      target = gtocX_2burn_pars_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, q_L, x_L, ...
                                                 iseg_R, q_R, x_R, ...
                                                 pars )
      DmayerDxxp = gtocX_2burn_pars_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = gtocX_2burn_pars_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = gtocX_2burn_pars_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = gtocX_2burn_pars_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = cont( self, xo__s, xo__eps0, xo__eps1 )
      res = gtocX_2burn_pars_Mex('cont', self.objectHandle, xo__s, xo__eps0, xo__eps1 );
    end
    % ---------------------------------------------------------------------
    function res = x_position( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_position_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_position_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_position_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_position_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_position_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_position_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = x_velocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('x_velocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = y_velocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('y_velocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = z_velocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_pars_Mex('z_velocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_1', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_1( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_1_1', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_1_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_1_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_2_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_2_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_3_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_pars_Mex('norm_reg_D_3_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = ray( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_1( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_4_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_pars_Mex('ray_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = vel( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_1( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_5_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_pars_Mex('vel_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vc( self, xo__r )
      res = gtocX_2burn_pars_Mex('vc', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = vc_D( self, xo__r )
      res = gtocX_2burn_pars_Mex('vc_D', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = vc_DD( self, xo__r )
      res = gtocX_2burn_pars_Mex('vc_DD', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r_D_1', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_2( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r_D_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1_1( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r_D_1_1', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1_2( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r_D_1_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_2_2( self, xo__r, xo__muS )
      res = gtocX_2burn_pars_Mex('acceleration_r_D_2_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = X_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('X_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('Y_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('Z_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VX_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VY_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end_D( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end_DD( self, xo__t )
      res = gtocX_2burn_pars_Mex('VZ_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = p_guess( self, xo__t )
      res = gtocX_2burn_pars_Mex('p_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = f_guess( self, xo__t )
      res = gtocX_2burn_pars_Mex('f_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = g_guess( self, xo__t )
      res = gtocX_2burn_pars_Mex('g_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = h_guess( self, xo__t )
      res = gtocX_2burn_pars_Mex('h_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = k_guess( self, xo__t )
      res = gtocX_2burn_pars_Mex('k_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = L_guess( self, xo__t, xo__t0 )
      res = gtocX_2burn_pars_Mex('L_guess', self.objectHandle, xo__t, xo__t0 );
    end
    % ---------------------------------------------------------------------
    function res = guess_setup( self,  )
      res = gtocX_2burn_pars_Mex('guess_setup', self.objectHandle,  );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.f(), ...
        self.zeta(), self.g(), ...
        self.zeta(), self.L(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'f', 'g', 'L' );
    end
    % ---------------------------------------------------------------------
    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        self.zeta(), self.lambda3(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3' );
    end
    % ---------------------------------------------------------------------
    function plot_controls( self )
      % no control to plot
    end
  end
end

% EOF: gtocX_2burn_pars.m
