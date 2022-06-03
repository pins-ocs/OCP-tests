%-----------------------------------------------------------------------%
%  file: TyreDynamic.m                                                  %
%                                                                       %
%  version: 1.0   date 4/6/2022                                         %
%                                                                       %
%  Copyright (C) 2022                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


classdef TyreDynamic < handle
  properties (SetAccess = private, Hidden = true)
    dim_q;
    dim_x;
    dim_u;
    dim_pars;
    num_active_BC;
    dim_ineq;
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = TyreDynamic( name )
      %% Allocate the C++ class instance
      self.objectHandle = TyreDynamic_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      TyreDynamic_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( ~ )
      %% print help for the class usage
      TyreDynamic_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = TyreDynamic_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      TyreDynamic_Mex( 'setup', self.objectHandle, fname_or_struct );
      res = TyreDynamic_Mex( 'dims', self.objectHandle );
      self.dim_q         = res.dim_q;
      self.dim_x         = res.dim_x;
      self.dim_u         = res.dim_u;
      self.dim_pars      = res.dim_pars;
      self.num_active_BC = res.num_active_BC;
      self.dim_ineq      = res.dim_ineq;
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Q( self )
      TyreDynamic_Mex( 'dim_Q', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_Q', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_X( self )
      TyreDynamic_Mex( 'dim_X', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_X', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Pars( self )
      TyreDynamic_Mex( 'dim_Pars', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_Pars', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_BC( self )
      TyreDynamic_Mex( 'dim_BC', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Post( self )
      TyreDynamic_Mex( 'dim_Post', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_Post', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Ipost( self )
      TyreDynamic_Mex( 'dim_Ipost', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_Ipost', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_active_BC( self )
      TyreDynamic_Mex( 'num_active_BC', self.objectHandle );
      res = TyreDynamic_Mex( 'num_active_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_nodes( self )
      TyreDynamic_Mex( 'num_nodes', self.objectHandle );
      res = TyreDynamic_Mex( 'num_nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_equations( self )
      TyreDynamic_Mex( 'num_equations', self.objectHandle );
      res = TyreDynamic_Mex( 'num_equations', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_segments( self )
      TyreDynamic_Mex( 'num_segments', self.objectHandle );
      res = TyreDynamic_Mex( 'num_segments', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_full_bc( self )
      TyreDynamic_Mex( 'dim_full_bc', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_full_bc', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_ineq( self )
      TyreDynamic_Mex( 'dim_ineq', self.objectHandle );
      res = TyreDynamic_Mex( 'dim_ineq', self.objectHandle );
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
      n = TyreDynamic_Mex( 'names', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = dims( self )
      %
      % Return a MATLAB structures collecting the dimension of the OCP problem:
      % res.dim_q         = number of mesh variables (variables computed ad mesh nodes)
      % res.dim_x         = number of states
      % res.dim_u         = number of controls
      % res.dim_pars      = number of parameters
      % res.num_active_BC = number of mutipliers associated to BC
      % res.dim_bc        = number of BC
      % res.num_nodes     = number of nodes of the discretization grid
      % res.neq           = number of equations
      %
      res = TyreDynamic_Mex( 'dims', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_ocp_data( self )
      %
      % Return a structure with data for the OCP problem.
      % Information level for message during computation takes
      % the following possible values: -1,0,1,2,3,4
      % res.InfoLevel
      %
      % number of thread for computation
      % res.N_threads   = maximum number of available thread
      % res.LU_threaded = number of thread for LU factorization
      % res.F_threaded  = number of thread for F(X) computation
      % res.JF_threaded = number of thread for JF(X) computation
      % res.U_threaded  = number of thread for controls computation
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
      res = TyreDynamic_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function info( self )
      TyreDynamic_Mex( 'info', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO LEVEL
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_info_level( self, infoLvl )
      %
      % Set information level
      %
      TyreDynamic_Mex( 'set_info_level', self.objectHandle, infoLvl );
    end
    %
    % DEPRECATED
    %
    function infoLevel( self, infoLvl )
      self.set_info_level( infoLvl );
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
      TyreDynamic_Mex( 'set_max_threads', self.objectHandle, nt );
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
      TyreDynamic_Mex( 'remesh', self.objectHandle, new_mesh );
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
      TyreDynamic_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    %
    % ---------------------------------------------------------------------
    %
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = TyreDynamic_Mex( 'get_guess', self.objectHandle );
    end
    %
    % ---------------------------------------------------------------------
    %
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = TyreDynamic_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = TyreDynamic_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    %
    % ---------------------------------------------------------------------
    %
    function update_continuation( self, n, old_s, s )
      %
      % Set parameter of the problem for continuation.
      %
      % The nonlinear system is of the form
      % F(x) = F_{n-1}(x)*(1-s)+F_{n}(x)*s
      % depends on the stage `n` and parameter `s` of
      % the continuation.
      %
      TyreDynamic_Mex( 'update_continuation', self.objectHandle, n, old_s, s );
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
      sol = TyreDynamic_Mex( 'get_solution', self.objectHandle, varargin{:} );
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
      sol = TyreDynamic_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution_by_group_and_names( self )
      %
      % Return the whole solution in a different format
      %
      % struct of vectors with OCP solutions
      %
      % res.data.q -> struct whose fields are the name of the columns of the data
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
      sol = TyreDynamic_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution from the matrices `X`, `Lambda`, `Pars` and `Omega`
      % into a single vector as stored in the solver PINS.
      %
      sol = TyreDynamic_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % from the vector `sol` which contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = TyreDynamic_Mex( 'unpack', self.objectHandle, sol );
    end
    % ---------------------------------------------------------------------
    function sol = pack_for_direct( self, X, U, Pars )
      %
      % Combine the solution from the matrices `X`, `U` and `Pars`
      % in a single vector ato be used with a direct solver.
      %
      %  X    = [ x0, x1, ..., xn     ] % The states at nodal point
      %  U    = [ u0, u1, ..., u(n-1) ] % The controls at cell point
      %  Pars = are the optimization parameter of the OCP
      %
      sol = TyreDynamic_Mex( 'pack_for_direct', self.objectHandle, X, U, Pars );
    end
    % ---------------------------------------------------------------------
    function [X, U, Pars] = unpack_for_direct( self, sol )
      %
      % Unpack from a vector to the matrices `X`, `U` and `Pars`.
      % The vector must contains the data as stored in a direct solver.
      %
      [X, U, Pars] = TyreDynamic_Mex( 'unpack_for_direct', self.objectHandle, sol );
    end
    % ---------------------------------------------------------------------
    function [Lambda,Omega] = estimate_multipliers( self, X, U, Pars, method )
      %
      % From the matrices `X`, `U` and `Pars` estimate
      % the multiplein a single vector ato be used with a direct solver.
      %
      %  X    = [ x0, x1, ..., xn     ] % The states at nodal point
      %  U    = [ u0, u1, ..., u(n-1) ] % The controls at cell point
      %  Pars = are the optimization parameter of the OCP
      %
      %  method = 'least_squares' ...
      %
      [Lambda,Omega] = TyreDynamic_Mex( 'estimate_multipliers', self.objectHandle, X, U, Pars, method );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = v( self )
      %
      % Return the solution for the state: v
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'v' );
    end
    function res = omega( self )
      %
      % Return the solution for the state: omega
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'omega' );
    end
    function res = lambda( self )
      %
      % Return the solution for the state: lambda
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda' );
    end
    function res = p( self )
      %
      % Return the solution for the state: p
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'p' );
    end
    function res = b( self )
      %
      % Return the solution for the state: b
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'b' );
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
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = p__o( self )
      %
      % Return the solution for the control: p__o
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'p__o' );
    end
    function res = b__o( self )
      %
      % Return the solution for the control: b__o
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'b__o' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_b__oControl( self )
      %
      % Return the solution for the post processing variable: b__oControl
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'b__oControl' );
    end
    function res = post_processing_p__oControl( self )
      %
      % Return the solution for the post processing variable: p__oControl
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'p__oControl' );
    end
    function res = post_processing_OnlyBrakingRear( self )
      %
      % Return the solution for the post processing variable: OnlyBrakingRear
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'OnlyBrakingRear' );
    end
    function res = post_processing_OnlyTractionRear( self )
      %
      % Return the solution for the post processing variable: OnlyTractionRear
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'OnlyTractionRear' );
    end
    function res = post_processing_LongSlipRear_min( self )
      %
      % Return the solution for the post processing variable: LongSlipRear_min
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'LongSlipRear_min' );
    end
    function res = post_processing_LongSlipRear_max( self )
      %
      % Return the solution for the post processing variable: LongSlipRear_max
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'LongSlipRear_max' );
    end
    function res = post_processing_v_min( self )
      %
      % Return the solution for the post processing variable: v_min
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'v_min' );
    end
    function res = post_processing_Fx_norm( self )
      %
      % Return the solution for the post processing variable: Fx_norm
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'Fx_norm' );
    end
    function res = post_processing_kappa__w( self )
      %
      % Return the solution for the post processing variable: kappa__w
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'kappa__w' );
    end
    function res = post_processing_F__x( self )
      %
      % Return the solution for the post processing variable: F__x
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'F__x' );
    end
    function res = post_processing_p__pos( self )
      %
      % Return the solution for the post processing variable: p__pos
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'p__pos' );
    end
    function res = post_processing_p__neg( self )
      %
      % Return the solution for the post processing variable: p__neg
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'p__neg' );
    end
    function res = post_processing_b__pos( self )
      %
      % Return the solution for the post processing variable: b__pos
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'b__pos' );
    end
    function res = post_processing_b__neg( self )
      %
      % Return the solution for the post processing variable: b__neg
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'b__neg' );
    end
    function res = post_processing_TT__env( self )
      %
      % Return the solution for the post processing variable: TT__env
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'TT__env' );
    end
    function res = post_processing_BT__env( self )
      %
      % Return the solution for the post processing variable: BT__env
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'BT__env' );
    end
    function res = post_processing_TT( self )
      %
      % Return the solution for the post processing variable: TT
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'TT' );
    end
    function res = post_processing_TB( self )
      %
      % Return the solution for the post processing variable: TB
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'TB' );
    end
    function res = post_processing_Fa( self )
      %
      % Return the solution for the post processing variable: Fa
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'Fa' );
    end
    function res = post_processing_Ma( self )
      %
      % Return the solution for the post processing variable: Ma
      %
      res = TyreDynamic_Mex( 'get_solution', self.objectHandle, 'Ma' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM (ASSEMBLED)
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function U = init_U( self, Z, do_minimization )
      %
      % Initialize `u`
      %
      U = TyreDynamic_Mex( 'init_U', self.objectHandle, Z, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, Z, u_guess )
      %
      % Compute controls `U` given a guess and X, L states.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      U = TyreDynamic_Mex( 'eval_U', self.objectHandle, Z, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, Z, U )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `Z` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      [F,ok] = TyreDynamic_Mex( 'eval_F', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, Z, U )
      %
      % Return the jacobian of the nonlinear system
      % of the indirect methods evaluated ad `Z` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      [JF,ok] = TyreDynamic_Mex( 'eval_JF', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = TyreDynamic_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [Z,U] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [Z,U] = TyreDynamic_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, Z, U )
      %
      % Set the solution in a vector as stored in PINS.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      TyreDynamic_Mex( 'set_raw_solution', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, Z )
      %
      % Return true if the solution does not violate
      % admissible regions.
      %
      ok = TyreDynamic_Mex( 'check_raw_solution', self.objectHandle, Z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, Z, U, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      TyreDynamic_Mex( 'check_jacobian', self.objectHandle, Z, U, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [q_L,q_R] = eval_q_LR( self, iseg_L, t_L, iseg_R, t_R )
      if length( t_L ) == 1
        q_L = self.eval_q( iseg_L, t_L(1) );
      else
        q_L = t_L;
      end
      if length( t_R ) == 1
        q_R = self.eval_q( iseg_R, t_R(1) );
      else
        q_R = t_R;
      end
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [ac] = eval_ac( self, iseg_L, t_L, x_L, lambda_L, ...
                                    iseg_R, t_R, x_R, lambda_R, ...
                                    pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      % <<FD1.jpg>>
      %
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      ac = TyreDynamic_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [ DacDxlxlp, DacDu ] = ...
      eval_DacDxlxlpu( self, iseg_L, t_L, x_L, lambda_L, ...
                             iseg_R, t_R, x_R, lambda_R, ...
                             pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      % <<FD2.jpg>>
      %
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      [DacDxlxlp, DacDu] = TyreDynamic_Mex( ...
        'DacDxlxlpu', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, iseg_L, t_L, x_L, lambda_L, ...
                                    iseg_R, t_R, x_R, lambda_R, pars )
      %
      % Compute the block of the BC of the nonlinear
      % system given left and right states.
      %
      % <<FD3.jpg>>
      %
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      [h,c] = TyreDynamic_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlxlop( self, iseg_L, t_L, x_L, lambda_L, ...
                                              iseg_R, t_R, x_R, lambda_R, pars )
      %
      % Compute the block of the BC of the nonlinear system
      % given left and right states.
      %
      % <<FD4.jpg>>
      %
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      [Jh,Jc] = TyreDynamic_Mex( 'DhcDxlxlop', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTINUOUS PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function u = eval_u( self, iseg_L, t_L, x_L, lambda_L, ...
                               iseg_R, t_R, x_R, lambda_R, ...
                               pars )
      %
      % Compute the control given states and multiplyers.
      %
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        u = TyreDynamic_Mex( 'u', self.objectHandle, ...
          iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
        );
      else
        u = zeros(self.dim_u,1);
      end
    end
    % ---------------------------------------------------------------------
    function DuDxlxlp = eval_DuDxlxlp( self, iseg_L, t_L, x_L, lambda_L, ...
                                             iseg_R, t_R, x_R, lambda_R, ...
                                             pars )
      %
      % Compute the jacobian of controls given states and multiplyers.
      %
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        DuDxlxlp = TyreDynamic_Mex( 'DuDxlxlp', self.objectHandle, ...
          iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
        );
      else
        DuDxlxlp = zeros( self.dim_u, 4*self.dim_x+self.dim_pars );
      end
    end
    % ---------------------------------------------------------------------
    %   ____ ___ ____  _____ ____ _____
    %  |  _ \_ _|  _ \| ____/ ___|_   _|
    %  | | | | || |_) |  _|| |     | |
    %  | |_| | ||  _ <| |__| |___  | |
    %  |____/___|_| \_\_____\____| |_|
    %
    %  minimize Target
    %
    %  subject to ODE: A(q,x,pars) x' = rhs( q, x, u, pars )
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = TyreDynamic_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    %
    function J = eval_Drhs_odeDxpu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = TyreDynamic_Mex(...
        'Drhs_odeDxpu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = TyreDynamic_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = TyreDynamic_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDxp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x` and `pars`.
      %
      J = TyreDynamic_Mex(...
        'DetaDxp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = TyreDynamic_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDxp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x` and `pars`.
      %
      J = TyreDynamic_Mex( 'DnuDxp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      bc = TyreDynamic_Mex( ...
        'bc', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      J = TyreDynamic_Mex( ...
        'DbcDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_D2bcD2xxp( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars, omega_full )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      J = TyreDynamic_Mex( ...
        'D2bcD2xxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, omega_full ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = TyreDynamic_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxpu = eval_DlagrangeDxpu( self, iseg, q, x, u, pars )
      DlagrangeDxpu = TyreDynamic_Mex( ...
        'DlagrangeDxpu', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function D2lagrangeD2xpu = eval_D2lagrangeD2xpu( self, iseg, q, x, u, pars )
      D2lagrangeD2xpu = TyreDynamic_Mex( ...
        'D2lagrangeD2xpu', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    %
    %   ____  _               _
    %  |  _ \(_)_ __ ___  ___| |_
    %  | | | | | '__/ _ \/ __| __|
    %  | |_| | | | |  __/ (__| |_
    %  |____/|_|_|  \___|\___|\__|
    %
    % ---------------------------------------------------------------------
    function fd_ode = eval_fd_ode( self, iseg_L, t_L, x_L, ...
                                         iseg_R, t_R, x_R, ...
                                         U, pars )
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        fd_ode = TyreDynamic_Mex( ...
          'fd_ode', self.objectHandle, ...
          iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars ...
        );
      else
        % per ora solo condizione di continuità
        fd_ode = x_R - x_L;
      end
    end
    % ---------------------------------------------------------------------
    function Dfd_odeDxxpu = eval_Dfd_odeDxxpu( self, iseg_L, t_L, x_L, ...
                                                     iseg_R, t_R, x_R, ...
                                                     U, pars )
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        Dfd_odeDxxpu = TyreDynamic_Mex( ...
          'Dfd_odeDxxpu', self.objectHandle, ...
          iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars ...
        );
      else
        % per ora codizione di continuità
        nx = self.dim_x;
        np = self.dim_pars;
        nu = self.dim_u;
        Dfd_odeDxxpu = [ -eye(nx,nx), eye(nx,nx), zeros(nx,nu+np) ];
      end
    end
    % ---------------------------------------------------------------------
    function D2fd_odeD2xxpu = eval_D2fd_odeD2xxpu( self, iseg_L, t_L, x_L, ...
                                                         iseg_R, t_R, x_R, ...
                                                         U, pars, lambda )
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        D2fd_odeD2xxpu = TyreDynamic_Mex( ...
          'D2fd_odeD2xxpu', self.objectHandle, ...
          iseg_L, q_L, x_L, iseg_R, q_R, x_R, U, pars, lambda ...
        );
      else
        nx = self.dim_x;
        np = self.dim_pars;
        nu = self.dim_u;
        D2fd_odeD2xxpu = zeros( 2*nx+nu+np );
      end
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, t_L, x_L, ...
                                               iseg_R, t_R, x_R, ...
                                               pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      target = TyreDynamic_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, t_L, x_L, ...
                                                 iseg_R, t_R, x_R, ...
                                                 pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      DmayerDxxp = TyreDynamic_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function D2mayerD2xxp = eval_D2mayerD2xxp( self, iseg_L, t_L, x_L, ...
                                                     iseg_R, t_R, x_R, ...
                                                     pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      D2mayerD2xxp = TyreDynamic_Mex( ...
        'D2mayerD2xxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function c = eval_c( self, iseg, q, x, u, pars )
      %
      % Evaluate contraints c(x,u,p) <= 0
      %
      c = TyreDynamic_Mex(...
        'LTargs', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function c = eval_fd_c( self, iseg_L, t_L, x_L, ...
                                  iseg_R, t_R, x_R, ...
                                  u, pars )
      %
      % Evaluate contraints c(x_M,u,p) <= 0
      %
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        q = (q_L+q_R)./2;
        x = (x_L+x_R)./2;
        c = self.eval_c(iseg_L,q,x,u,pars);
      else
        c = zeros( self.dim_ineq, 1 );
      end
    end
    % ---------------------------------------------------------------------
    function Jc = eval_DcDxpu( self, iseg, q, x, u, pars )
      %
      % Evaluate jacobian of constraints c(x,u,p) <= 0
      %
      Jc = TyreDynamic_Mex(...
        'DLTargsDxpu', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function Jc = eval_Dfd_cDxxpu( self, iseg_L, t_L, x_L, ...
                                         iseg_R, t_R, x_R, ...
                                         u, pars )
      %
      % Evaluate jacobian of constraints c(x,u,p) <= 0
      %
      nx = self.dim_x;
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        q      = (q_L+q_R)./2;
        x      = (x_L+x_R)./2;
        Jc_pre = self.eval_DcDxpu( iseg_L, q, x, u, pars );
        Jx     = 0.5*Jc_pre(:,1:nx);
        Jc     = [Jx,Jx,Jc_pre(:,nx+1:end)];
      else
        nn = 2*nx + self.dim_u + self.dim_pars;
        Jc = zeros( self.dim_ineq, nn );
      end
    end
    % ---------------------------------------------------------------------
    function Hc = eval_D2cD2xpu( self, iseg, q, x, u, pars, omega )
      %
      % Evaluate hessian of constraints omega . c(x,u,p) <= 0
      %
      Hc = TyreDynamic_Mex(...
        'D2LTargsD2xpu', self.objectHandle, iseg, q, x, u, pars, omega ...
      );
    end
    % ---------------------------------------------------------------------
    function HcBIG = eval_D2fd_cD2xxpu( self, iseg_L, t_L, x_L, ...
                                              iseg_R, t_R, x_R, ...
                                              u, pars, omega )
      %
      % Evaluate hessian of constraints omega . c(x,u,p) <= 0
      %
      if iseg_L == iseg_R
        [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
        q_M = (q_R+q_L)/2;
        x_M = (x_R+x_L)/2;
        Hc = self.eval_D2cD2xpu( iseg_L, q_M, x_M, u, pars, omega );
        nx = self.dim_x;
        A  = Hc(1:nx,1:nx)./4;
        B  = Hc(1:nx,nx+1:end)./2;
        C  = Hc(nx+1:end,nx+1:end);
        HcBIG = [ A,   A,   B; ...
                  A,   A,   B; ...
                  B.', B.', C ];
      else
        nn    = 2*self.dim_x + self.dim_u + self.dim_pars;
        HcBIG = zeros( nn, nn );
      end
    end
    %
    %
    %   ___ _   _ ____ ___ ____  _____ ____ _____
    %  |_ _| \ | |  _ \_ _|  _ \| ____/ ___|_   _|
    %   | ||  \| | | | | || |_) |  _|| |     | |
    %   | || |\  | |_| | ||  _ <| |__| |___  | |
    %  |___|_| \_|____/___|_| \_\_____\____| |_|
    % ---------------------------------------------------------------------
    function Hxp = eval_Hxp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) =
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V)
      %
      % Hxp(x,V,lambda,u,p,zeta) = partial_{xp} H(...)
      %
      Hxp = TyreDynamic_Mex(...
        'Hxp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxpDxpu( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hxp(q,x,lambda,V,pars)`
      % respect to `x` and `pars`.
      %
      J = TyreDynamic_Mex(...
        'DHxpDxpu', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
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
      Hu = TyreDynamic_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, u, pars )
      %
      % Compute Jp(x,u,pars,zeta)
      %
      J = TyreDynamic_Mex( 'JP', self.objectHandle, iseg, q, x, u, pars );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      %
      % Compute Ju(x,u,pars,zeta)
      %
      J = TyreDynamic_Mex( 'JU', self.objectHandle, iseg, q, x, u, pars );
    end
    % ---------------------------------------------------------------------
    function LT = eval_LT( self, iseg, q, x, u, pars )
      LT = TyreDynamic_Mex(...
        'LT', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function JP = eval_JP( self, iseg, q, x, u, pars )
      JP = TyreDynamic_Mex(...
        'JP', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function JU = eval_JU( self, iseg, q, x, u, pars )
      JU = TyreDynamic_Mex(...
        'JU', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function LTargs = eval_LTargs( self, iseg, q, x, u, pars )
      LTargs = TyreDynamic_Mex(...
        'LTargs', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function jmp = eval_jump( self, iseg_L, t_L, x_L, lambda_L, ...
                                    iseg_R, t_R, x_R, lambda_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      jmp = TyreDynamic_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, ...
        iseg_R, q_R, x_R, lambda_R, ...
        pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, t_L, x_L, lambda_L, ...
                                         iseg_R, t_R, x_R, lambda_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      J = TyreDynamic_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, ...
        iseg_R, q_R, x_R, lambda_R, ...
        pars ...
      );
    end
    % ---------------------------------------------------------------------
    % DA FARE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    % omega*Jump(x_l,lambda_L,x_R,lambda_R,pars)
    %
    function H = eval_Hessian_jump_xlxlp( self, ...
      iseg_L, t_L, x_L, lambda_L, ...
      iseg_R, t_R, x_R, lambda_R, ...
      pars, omega                 ...
    )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      H = TyreDynamic_Mex( ...
        'Hessian_jump_xlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, ...
        iseg_R, q_R, x_R, lambda_R, ...
        pars, omega ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = TyreDynamic_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = TyreDynamic_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = TyreDynamic_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % ARGOMENTI DEI VINCOLI
    % INTERVALLI VINCOLI
    % CHIAMATA A GUESS SENZA SOLVER


    %
    %  ____       _   _
    % |  _ \ __ _| |_| |_ ___ _ __ _ __
    % | |_) / _` | __| __/ _ \ '__| '_ \
    % |  __/ (_| | |_| ||  __/ |  | | | |
    % |_|   \__,_|\__|\__\___|_|  |_| |_|
    %
    % ---------------------------------------------------------------------
    function res = A_pattern( self )
      res = TyreDynamic_Mex('A_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DbcDxxp_pattern( self )
      res = TyreDynamic_Mex('DbcDxxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2bcD2xxp_pattern( self )
      res = TyreDynamic_Mex('D2bcD2xxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = Drhs_odeDxpu_pattern( self )
      res = TyreDynamic_Mex('Drhs_odeDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DsegmentLinkDxp_pattern( self )
      res = TyreDynamic_Mex('DsegmentLinkDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DjumpDxlxlp_pattern( self )
      res = TyreDynamic_Mex('DjumpDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DHxpDxpu_pattern( self )
      res = TyreDynamic_Mex('DHxpDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DJPDxpu_pattern( self )
      res = TyreDynamic_Mex('DJPDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DLTDxpu_pattern( self )
      res = TyreDynamic_Mex('DLTDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DJUDxpu_pattern( self )
      res = TyreDynamic_Mex('DJUDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2JPD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2JPD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2LTD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2JUD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2JUD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DLTargsDxpu_pattern( self )
      res = TyreDynamic_Mex('DLTargsDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTargsD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2LTargsD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DnuDxp_pattern( self )
      res = TyreDynamic_Mex('DnuDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DetaDxp_pattern( self )
      res = TyreDynamic_Mex('DetaDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDxlxlp_pattern( self )
      res = TyreDynamic_Mex('DgDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDu_pattern( self )
      res = TyreDynamic_Mex('DgDu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DmDuu_pattern( self )
      res = TyreDynamic_Mex('DmDuu_pattern', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = LongSlipRear( self, xo___V )
      res = TyreDynamic_Mex('LongSlipRear', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    function res = LongSlipRear_D( self, xo___V )
      res = TyreDynamic_Mex('LongSlipRear_D', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    function res = LongSlipRear_DD( self, xo___V )
      res = TyreDynamic_Mex('LongSlipRear_DD', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w_D_1( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w_D_1', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w_D_2( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w_D_2', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w_D_1_1( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w_D_1_1', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w_D_1_2( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w_D_1_2', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = kappa__w_D_2_2( self, xo__v, xo__omega )
      res = TyreDynamic_Mex('kappa__w_D_2_2', self.objectHandle, xo__v, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = F__x( self, xo__lambda )
      res = TyreDynamic_Mex('F__x', self.objectHandle, xo__lambda );
    end
    % ---------------------------------------------------------------------
    function res = F__x_D( self, xo__lambda )
      res = TyreDynamic_Mex('F__x_D', self.objectHandle, xo__lambda );
    end
    % ---------------------------------------------------------------------
    function res = F__x_DD( self, xo__lambda )
      res = TyreDynamic_Mex('F__x_DD', self.objectHandle, xo__lambda );
    end
    % ---------------------------------------------------------------------
    function res = p__pos( self, xo__p )
      res = TyreDynamic_Mex('p__pos', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = p__pos_D( self, xo__p )
      res = TyreDynamic_Mex('p__pos_D', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = p__pos_DD( self, xo__p )
      res = TyreDynamic_Mex('p__pos_DD', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = p__neg( self, xo__p )
      res = TyreDynamic_Mex('p__neg', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = p__neg_D( self, xo__p )
      res = TyreDynamic_Mex('p__neg_D', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = p__neg_DD( self, xo__p )
      res = TyreDynamic_Mex('p__neg_DD', self.objectHandle, xo__p );
    end
    % ---------------------------------------------------------------------
    function res = b__pos( self, xo__b )
      res = TyreDynamic_Mex('b__pos', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = b__pos_D( self, xo__b )
      res = TyreDynamic_Mex('b__pos_D', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = b__pos_DD( self, xo__b )
      res = TyreDynamic_Mex('b__pos_DD', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = b__neg( self, xo__b )
      res = TyreDynamic_Mex('b__neg', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = b__neg_D( self, xo__b )
      res = TyreDynamic_Mex('b__neg_D', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = b__neg_DD( self, xo__b )
      res = TyreDynamic_Mex('b__neg_DD', self.objectHandle, xo__b );
    end
    % ---------------------------------------------------------------------
    function res = TT__env( self, xo__omega )
      res = TyreDynamic_Mex('TT__env', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT__env_D( self, xo__omega )
      res = TyreDynamic_Mex('TT__env_D', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT__env_DD( self, xo__omega )
      res = TyreDynamic_Mex('TT__env_DD', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = BT__env( self, xo__omega )
      res = TyreDynamic_Mex('BT__env', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = BT__env_D( self, xo__omega )
      res = TyreDynamic_Mex('BT__env_D', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = BT__env_DD( self, xo__omega )
      res = TyreDynamic_Mex('BT__env_DD', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT_D_1( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT_D_1', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT_D_2( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT_D_2', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT_D_1_1( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT_D_1_1', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT_D_1_2( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT_D_1_2', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TT_D_2_2( self, xo__p__pos, xo__omega )
      res = TyreDynamic_Mex('TT_D_2_2', self.objectHandle, xo__p__pos, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB_D_1( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB_D_1', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB_D_2( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB_D_2', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB_D_1_1( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB_D_1_1', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB_D_1_2( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB_D_1_2', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = TB_D_2_2( self, xo__b__neg, xo__omega )
      res = TyreDynamic_Mex('TB_D_2_2', self.objectHandle, xo__b__neg, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = Fa( self, xo__v )
      res = TyreDynamic_Mex('Fa', self.objectHandle, xo__v );
    end
    % ---------------------------------------------------------------------
    function res = Fa_D( self, xo__v )
      res = TyreDynamic_Mex('Fa_D', self.objectHandle, xo__v );
    end
    % ---------------------------------------------------------------------
    function res = Fa_DD( self, xo__v )
      res = TyreDynamic_Mex('Fa_DD', self.objectHandle, xo__v );
    end
    % ---------------------------------------------------------------------
    function res = Ma( self, xo__omega )
      res = TyreDynamic_Mex('Ma', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = Ma_D( self, xo__omega )
      res = TyreDynamic_Mex('Ma_D', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    function res = Ma_DD( self, xo__omega )
      res = TyreDynamic_Mex('Ma_DD', self.objectHandle, xo__omega );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.v(), ...
        self.zeta(), self.omega(), ...
        self.zeta(), self.lambda(), ...
        self.zeta(), self.p(), ...
        self.zeta(), self.b(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'v', '\omega', '\lambda', 'p', 'b' );
    end
    % ---------------------------------------------------------------------
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
    % ---------------------------------------------------------------------
    function plot_controls( self )
      plot(...
        self.zeta(), self.p__o(), ...
        self.zeta(), self.b__o(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'p\_o', 'b\_o' );
    end
  end
end

% EOF: TyreDynamic.m
