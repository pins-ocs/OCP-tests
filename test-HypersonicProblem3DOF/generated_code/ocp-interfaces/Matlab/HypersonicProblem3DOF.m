%-----------------------------------------------------------------------%
%  file: HypersonicProblem3DOF.m                                        %
%                                                                       %
%  version: 1.0   date 19/6/2022                                        %
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


classdef HypersonicProblem3DOF < handle
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
    function self = HypersonicProblem3DOF( name )
      %% Allocate the C++ class instance
      self.objectHandle = HypersonicProblem3DOF_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      HypersonicProblem3DOF_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( ~ )
      %% print help for the class usage
      HypersonicProblem3DOF_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = HypersonicProblem3DOF_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      HypersonicProblem3DOF_Mex( 'setup', self.objectHandle, fname_or_struct );
      res = HypersonicProblem3DOF_Mex( 'dims', self.objectHandle );
      self.dim_q         = res.dim_q;
      self.dim_x         = res.dim_x;
      self.dim_u         = res.dim_u;
      self.dim_pars      = res.dim_pars;
      self.num_active_BC = res.num_active_BC;
      self.dim_ineq      = res.dim_ineq;
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Q( self )
      HypersonicProblem3DOF_Mex( 'dim_Q', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_Q', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_X( self )
      HypersonicProblem3DOF_Mex( 'dim_X', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_X', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Pars( self )
      HypersonicProblem3DOF_Mex( 'dim_Pars', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_Pars', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_BC( self )
      HypersonicProblem3DOF_Mex( 'dim_BC', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Post( self )
      HypersonicProblem3DOF_Mex( 'dim_Post', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_Post', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Ipost( self )
      HypersonicProblem3DOF_Mex( 'dim_Ipost', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_Ipost', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_active_BC( self )
      HypersonicProblem3DOF_Mex( 'num_active_BC', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'num_active_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_nodes( self )
      HypersonicProblem3DOF_Mex( 'num_nodes', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'num_nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_equations( self )
      HypersonicProblem3DOF_Mex( 'num_equations', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'num_equations', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_segments( self )
      HypersonicProblem3DOF_Mex( 'num_segments', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'num_segments', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_full_bc( self )
      HypersonicProblem3DOF_Mex( 'dim_full_bc', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_full_bc', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_ineq( self )
      HypersonicProblem3DOF_Mex( 'dim_ineq', self.objectHandle );
      res = HypersonicProblem3DOF_Mex( 'dim_ineq', self.objectHandle );
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
      n = HypersonicProblem3DOF_Mex( 'names', self.objectHandle );
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
      res = HypersonicProblem3DOF_Mex( 'dims', self.objectHandle );
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
      res = HypersonicProblem3DOF_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function info( self )
      HypersonicProblem3DOF_Mex( 'info', self.objectHandle );
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
      HypersonicProblem3DOF_Mex( 'set_info_level', self.objectHandle, infoLvl );
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
      HypersonicProblem3DOF_Mex( 'set_max_threads', self.objectHandle, nt );
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
      HypersonicProblem3DOF_Mex( 'remesh', self.objectHandle, new_mesh );
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
      HypersonicProblem3DOF_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    %
    % ---------------------------------------------------------------------
    %
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = HypersonicProblem3DOF_Mex( 'get_guess', self.objectHandle );
    end
    %
    % ---------------------------------------------------------------------
    %
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = HypersonicProblem3DOF_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = HypersonicProblem3DOF_Mex( 'solve', self.objectHandle, varargin{:} );
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
      HypersonicProblem3DOF_Mex( 'update_continuation', self.objectHandle, n, old_s, s );
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
      sol = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, varargin{:} );
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
      sol = HypersonicProblem3DOF_Mex( 'get_solution2', self.objectHandle );
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
      sol = HypersonicProblem3DOF_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution from the matrices `X`, `Lambda`, `Pars` and `Omega`
      % into a single vector as stored in the solver PINS.
      %
      sol = HypersonicProblem3DOF_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % from the vector `sol` which contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = HypersonicProblem3DOF_Mex( 'unpack', self.objectHandle, sol );
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
      sol = HypersonicProblem3DOF_Mex( 'pack_for_direct', self.objectHandle, X, U, Pars );
    end
    % ---------------------------------------------------------------------
    function [X, U, Pars] = unpack_for_direct( self, sol )
      %
      % Unpack from a vector to the matrices `X`, `U` and `Pars`.
      % The vector must contains the data as stored in a direct solver.
      %
      [X, U, Pars] = HypersonicProblem3DOF_Mex( 'unpack_for_direct', self.objectHandle, sol );
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
      [Lambda,Omega] = HypersonicProblem3DOF_Mex( 'estimate_multipliers', self.objectHandle, X, U, Pars, method );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = h( self )
      %
      % Return the solution for the state: h
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'h' );
    end
    function res = theta( self )
      %
      % Return the solution for the state: theta
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'theta' );
    end
    function res = phi( self )
      %
      % Return the solution for the state: phi
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'phi' );
    end
    function res = V( self )
      %
      % Return the solution for the state: V
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'V' );
    end
    function res = G( self )
      %
      % Return the solution for the state: G
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'G' );
    end
    function res = psi( self )
      %
      % Return the solution for the state: psi
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'psi' );
    end
    function res = sigma( self )
      %
      % Return the solution for the state: sigma
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'sigma' );
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
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      %
      % Return the solution for the multiplier: lambda6
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
    end
    function res = lambda7( self )
      %
      % Return the solution for the multiplier: lambda7
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'lambda7__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = alpha( self )
      %
      % Return the solution for the control: alpha
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'alpha' );
    end
    function res = u2( self )
      %
      % Return the solution for the control: u2
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'u2' );
    end
    function res = c_h( self )
      %
      % Return the solution for the control: c_h
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_h' );
    end
    function res = c_theta( self )
      %
      % Return the solution for the control: c_theta
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_theta' );
    end
    function res = c_phi( self )
      %
      % Return the solution for the control: c_phi
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_phi' );
    end
    function res = c_V( self )
      %
      % Return the solution for the control: c_V
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_V' );
    end
    function res = c_G( self )
      %
      % Return the solution for the control: c_G
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_G' );
    end
    function res = c_psi( self )
      %
      % Return the solution for the control: c_psi
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_psi' );
    end
    function res = c_sigma( self )
      %
      % Return the solution for the control: c_sigma
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'c_sigma' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_u2Control( self )
      %
      % Return the solution for the post processing variable: u2Control
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'u2Control' );
    end
    function res = post_processing_G_bound_min( self )
      %
      % Return the solution for the post processing variable: G_bound_min
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'G_bound_min' );
    end
    function res = post_processing_G_bound_max( self )
      %
      % Return the solution for the post processing variable: G_bound_max
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'G_bound_max' );
    end
    function res = post_processing_altitude( self )
      %
      % Return the solution for the post processing variable: altitude
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'altitude' );
    end
    function res = post_processing_velocity_magnitude( self )
      %
      % Return the solution for the post processing variable: velocity_magnitude
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'velocity magnitude' );
    end
    function res = post_processing_angle_deg( self )
      %
      % Return the solution for the post processing variable: angle_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'angle [deg]' );
    end
    function res = post_processing_longitude_deg( self )
      %
      % Return the solution for the post processing variable: longitude_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'longitude [deg]' );
    end
    function res = post_processing_latitude_deg( self )
      %
      % Return the solution for the post processing variable: latitude_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'latitude [deg]' );
    end
    function res = post_processing_velocity_flight_minus_path_angle_deg( self )
      %
      % Return the solution for the post processing variable: velocity_flight_minus_path_angle_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'velocity flight-path angle [deg]' );
    end
    function res = post_processing_velocity_heading_angle_deg( self )
      %
      % Return the solution for the post processing variable: velocity_heading_angle_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'velocity heading angle [deg]' );
    end
    function res = post_processing_bank_angle_deg( self )
      %
      % Return the solution for the post processing variable: bank_angle_deg
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'bank angle [deg]' );
    end
    function res = post_processing_CL( self )
      %
      % Return the solution for the post processing variable: CL
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'CL' );
    end
    function res = post_processing_CD( self )
      %
      % Return the solution for the post processing variable: CD
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'CD' );
    end
    function res = post_processing_G_PI( self )
      %
      % Return the solution for the post processing variable: G_PI
      %
      res = HypersonicProblem3DOF_Mex( 'get_solution', self.objectHandle, 'G_PI' );
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
      U = HypersonicProblem3DOF_Mex( 'init_U', self.objectHandle, Z, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, Z, u_guess )
      %
      % Compute controls `U` given a guess and X, L states.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      U = HypersonicProblem3DOF_Mex( 'eval_U', self.objectHandle, Z, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, Z, U )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `Z` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      [F,ok] = HypersonicProblem3DOF_Mex( 'eval_F', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, Z, U )
      %
      % Return the jacobian of the nonlinear system
      % of the indirect methods evaluated ad `Z` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      [JF,ok] = HypersonicProblem3DOF_Mex( 'eval_JF', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = HypersonicProblem3DOF_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [Z,U] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [Z,U] = HypersonicProblem3DOF_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, Z, U )
      %
      % Set the solution in a vector as stored in PINS.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      HypersonicProblem3DOF_Mex( 'set_raw_solution', self.objectHandle, Z, U );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, Z )
      %
      % Return true if the solution does not violate
      % admissible regions.
      %
      ok = HypersonicProblem3DOF_Mex( 'check_raw_solution', self.objectHandle, Z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, Z, U, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      HypersonicProblem3DOF_Mex( 'check_jacobian', self.objectHandle, Z, U, epsi );
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
      ac = HypersonicProblem3DOF_Mex( 'ac', self.objectHandle, ...
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
      [DacDxlxlp, DacDu] = HypersonicProblem3DOF_Mex( ...
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
      [h,c] = HypersonicProblem3DOF_Mex( 'hc', self.objectHandle, ...
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
      [Jh,Jc] = HypersonicProblem3DOF_Mex( 'DhcDxlxlop', self.objectHandle, ...
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
        u = HypersonicProblem3DOF_Mex( 'u', self.objectHandle, ...
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
        DuDxlxlp = HypersonicProblem3DOF_Mex( 'DuDxlxlp', self.objectHandle, ...
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
      rhs = HypersonicProblem3DOF_Mex( 'rhs_ode', self.objectHandle, ...
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
      J = HypersonicProblem3DOF_Mex(...
        'Drhs_odeDxpu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = HypersonicProblem3DOF_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = HypersonicProblem3DOF_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDxp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x` and `pars`.
      %
      J = HypersonicProblem3DOF_Mex(...
        'DetaDxp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = HypersonicProblem3DOF_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDxp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x` and `pars`.
      %
      J = HypersonicProblem3DOF_Mex( 'DnuDxp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      bc = HypersonicProblem3DOF_Mex( ...
        'bc', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      J = HypersonicProblem3DOF_Mex( ...
        'DbcDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_D2bcD2xxp( self, iseg_L, t_L, x_L, iseg_R, t_R, x_R, pars, omega_full )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      J = HypersonicProblem3DOF_Mex( ...
        'D2bcD2xxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars, omega_full ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = HypersonicProblem3DOF_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxpu = eval_DlagrangeDxpu( self, iseg, q, x, u, pars )
      DlagrangeDxpu = HypersonicProblem3DOF_Mex( ...
        'DlagrangeDxpu', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function D2lagrangeD2xpu = eval_D2lagrangeD2xpu( self, iseg, q, x, u, pars )
      D2lagrangeD2xpu = HypersonicProblem3DOF_Mex( ...
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
        fd_ode = HypersonicProblem3DOF_Mex( ...
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
        Dfd_odeDxxpu = HypersonicProblem3DOF_Mex( ...
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
        D2fd_odeD2xxpu = HypersonicProblem3DOF_Mex( ...
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
      target = HypersonicProblem3DOF_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, t_L, x_L, ...
                                                 iseg_R, t_R, x_R, ...
                                                 pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      DmayerDxxp = HypersonicProblem3DOF_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function D2mayerD2xxp = eval_D2mayerD2xxp( self, iseg_L, t_L, x_L, ...
                                                     iseg_R, t_R, x_R, ...
                                                     pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      D2mayerD2xxp = HypersonicProblem3DOF_Mex( ...
        'D2mayerD2xxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function c = eval_c( self, iseg, q, x, u, pars )
      %
      % Evaluate contraints c(x,u,p) <= 0
      %
      c = HypersonicProblem3DOF_Mex(...
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
      Jc = HypersonicProblem3DOF_Mex(...
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
      Hc = HypersonicProblem3DOF_Mex(...
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
      Hxp = HypersonicProblem3DOF_Mex(...
        'Hxp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxpDxpu( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hxp(q,x,lambda,V,pars)`
      % respect to `x` and `pars`.
      %
      J = HypersonicProblem3DOF_Mex(...
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
      Hu = HypersonicProblem3DOF_Mex(...
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
      J = HypersonicProblem3DOF_Mex( 'JP', self.objectHandle, iseg, q, x, u, pars );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      %
      % Compute Ju(x,u,pars,zeta)
      %
      J = HypersonicProblem3DOF_Mex( 'JU', self.objectHandle, iseg, q, x, u, pars );
    end
    % ---------------------------------------------------------------------
    function LT = eval_LT( self, iseg, q, x, u, pars )
      LT = HypersonicProblem3DOF_Mex(...
        'LT', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function JP = eval_JP( self, iseg, q, x, u, pars )
      JP = HypersonicProblem3DOF_Mex(...
        'JP', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function JU = eval_JU( self, iseg, q, x, u, pars )
      JU = HypersonicProblem3DOF_Mex(...
        'JU', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function LTargs = eval_LTargs( self, iseg, q, x, u, pars )
      LTargs = HypersonicProblem3DOF_Mex(...
        'LTargs', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function jmp = eval_jump( self, iseg_L, t_L, x_L, lambda_L, ...
                                    iseg_R, t_R, x_R, lambda_R, pars )
      [q_L,q_R] = self.eval_q_LR( iseg_L, t_L, iseg_R, t_R );
      jmp = HypersonicProblem3DOF_Mex( ...
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
      J = HypersonicProblem3DOF_Mex( ...
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
      H = HypersonicProblem3DOF_Mex( ...
        'Hessian_jump_xlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, ...
        iseg_R, q_R, x_R, lambda_R, ...
        pars, omega ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = HypersonicProblem3DOF_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = HypersonicProblem3DOF_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = HypersonicProblem3DOF_Mex( 'node_to_segment', self.objectHandle );
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
      res = HypersonicProblem3DOF_Mex('A_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DbcDxxp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DbcDxxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2bcD2xxp_pattern( self )
      res = HypersonicProblem3DOF_Mex('D2bcD2xxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = Drhs_odeDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('Drhs_odeDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DsegmentLinkDxp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DsegmentLinkDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DjumpDxlxlp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DjumpDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DHxpDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DHxpDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DJPDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DJPDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DLTDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DLTDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DJUDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DJUDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2JPD2xpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('D2JPD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTD2xpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('D2LTD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2JUD2xpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('D2JUD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DLTargsDxpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DLTargsDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTargsD2xpu_pattern( self )
      res = HypersonicProblem3DOF_Mex('D2LTargsD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DnuDxp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DnuDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DetaDxp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DetaDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDxlxlp_pattern( self )
      res = HypersonicProblem3DOF_Mex('DgDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DgDu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DmDuu_pattern( self )
      res = HypersonicProblem3DOF_Mex('DmDuu_pattern', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = h_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('h_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = h_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('h_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = h_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('h_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = theta_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('theta_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = theta_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('theta_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = theta_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('theta_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = phi_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('phi_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = phi_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('phi_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = phi_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('phi_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = V_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('V_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = V_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('V_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = V_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('V_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = G_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('G_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = G_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('G_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = G_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('G_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = psi_guess( self, xo__s )
      res = HypersonicProblem3DOF_Mex('psi_guess', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = psi_guess_D( self, xo__s )
      res = HypersonicProblem3DOF_Mex('psi_guess_D', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = psi_guess_DD( self, xo__s )
      res = HypersonicProblem3DOF_Mex('psi_guess_DD', self.objectHandle, xo__s );
    end
    % ---------------------------------------------------------------------
    function res = G_bound( self, xo___V )
      res = HypersonicProblem3DOF_Mex('G_bound', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    function res = G_bound_D( self, xo___V )
      res = HypersonicProblem3DOF_Mex('G_bound_D', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    function res = G_bound_DD( self, xo___V )
      res = HypersonicProblem3DOF_Mex('G_bound_DD', self.objectHandle, xo___V );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.h(), ...
        self.zeta(), self.theta(), ...
        self.zeta(), self.phi(), ...
        self.zeta(), self.V(), ...
        self.zeta(), self.G(), ...
        self.zeta(), self.psi(), ...
        self.zeta(), self.sigma(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'h', 'th\eta', '\phi', 'V', 'G', '\psi', '\sigma' );
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
        self.zeta(), self.alpha(), ...
        self.zeta(), self.u2(), ...
        self.zeta(), self.c_h(), ...
        self.zeta(), self.c_theta(), ...
        self.zeta(), self.c_phi(), ...
        self.zeta(), self.c_V(), ...
        self.zeta(), self.c_G(), ...
        self.zeta(), self.c_psi(), ...
        self.zeta(), self.c_sigma(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( '\alpha', 'u2', 'c\_h', 'c\_th\eta', 'c\_\phi', 'c\_V', 'c\_G', 'c\_\psi', 'c\_\sigma' );
    end
  end
end

% EOF: HypersonicProblem3DOF.m
