%-----------------------------------------------------------------------%
%  file: TyreDynamic.m                                                  %
%                                                                       %
%  version: 1.0   date 9/5/2023                                         %
%                                                                       %
%  Copyright (C) 2023                                                   %
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
    function res = get_dim_BC( self )
      res = TyreDynamic_Mex( 'dim_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_full_bc( self )
      res = TyreDynamic_Mex( 'dim_full_bc', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_ineq( self )
      res = TyreDynamic_Mex( 'dim_ineq', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Ipost( self )
      res = TyreDynamic_Mex( 'dim_Ipost', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Pars( self )
      res = TyreDynamic_Mex( 'dim_Pars', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Post( self )
      res = TyreDynamic_Mex( 'dim_Post', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_Q( self )
      res = TyreDynamic_Mex( 'dim_Q', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_dim_X( self )
      res = TyreDynamic_Mex( 'dim_X', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_active_BC( self )
      res = TyreDynamic_Mex( 'num_active_BC', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_equations( self )
      res = TyreDynamic_Mex( 'num_equations', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_nodes( self )
      res = TyreDynamic_Mex( 'num_nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = get_num_segments( self )
      res = TyreDynamic_Mex( 'num_segments', self.objectHandle );
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
      % res.JU_threaded = number of thread for JU(X) computation
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
    function res = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      res = TyreDynamic_Mex( 'get_guess', self.objectHandle );
    end
    %
    % ---------------------------------------------------------------------
    %
    function res = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      res = TyreDynamic_Mex( 'get_solution_as_guess', self.objectHandle );
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
    % ---------------------------------------------------------------------
    function [ MU, U ] = MU_U_split( self, MU_U )
      dd    = self.dims();
      nx    = dd.dim_x;
      nu    = dd.dim_u;
      ncell = dd.num_nodes-1;
      MU    = reshape( MU_U(ncell*nu+1:ncell*(nx+nu)), nx, ncell );
      U     = reshape( MU_U(1:ncell*nu), nu, ncell );
    end
    % ---------------------------------------------------------------------
    function MU_U = MU_U_join( self, MU, U )
      MU_U = [U(:);MU(:)];
    end
    % ---------------------------------------------------------------------
    function MU_U = guess_MU_U( self, Z )
      MU_U = TyreDynamic_Mex( 'guess_MU_U', self.objectHandle, Z );
    end
    % ---------------------------------------------------------------------
    function U = guess_U( self, Z )
      MU_U    = self.guess_MU_U( Z );
      [~, U ] = self.MU_U_split(MU_U);
    end
    % ---------------------------------------------------------------------
    function MU_U = eval_MU_U( self, Z, u_guess )
      MU_U = TyreDynamic_Mex( 'eval_MU_U', self.objectHandle, Z, u_guess );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, Z, u_guess )
      MU_U = self.eval_MU_U( Z, u_guess );
      [~, U ] = self.MU_U_split(MU_U);
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, Z, varargin )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `Z`, `MU` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      if nargin == 3
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      [F,ok] = TyreDynamic_Mex( 'eval_F', self.objectHandle, Z, MU_U );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, Z, varargin )
      %
      % Return the jacobian of the nonlinear system
      % of the indirect methods evaluated ad `Z`, `MU` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      if nargin == 3
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      [JF,ok] = TyreDynamic_Mex( 'eval_JF', self.objectHandle, Z, MU_U );
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
    function [JF,ok] = eval_JF2( self, Z, varargin )
      %
      % Return the jacobian of the nonlinear system
      % of the indirect methods evaluated ad `Z`, `MU` and `U`.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      if nargin == 3
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      [JF,ok] = TyreDynamic_Mex( 'eval_JF2', self.objectHandle, Z, MU_U );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF2_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = TyreDynamic_Mex( 'eval_JF2_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [ Z, MU, U ] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [ Z, MU_U ] = TyreDynamic_Mex( 'get_raw_solution', self.objectHandle );
      [ MU, U ]   = self.MU_U_split(MU_U);
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, Z, varargin )
      %
      % Set the solution in a vector as stored in PINS.
      % Vector Z can be built as Z = pack( X, Lambda, Pars, Omega );
      %
      if nargin == 3
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      TyreDynamic_Mex( 'set_raw_solution', self.objectHandle, Z, MU_U );
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
    function check_jacobian( self, Z, varargin )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      if nargin == 4
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      TyreDynamic_Mex( 'check_jacobian', self.objectHandle, Z, MU_U, varargin{end} );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [ q_L, q_R ] = eval_q_LR( self, L, R )
      q_L = self.eval_q( L );
      q_R = self.eval_q( R );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,b,c] = eval_abc( self, L, R, pars, varargin )
      %
      % Compute the block of the nonlinear system given left and right states.
      %
      % L.iseg     R.iseg
      % L.q        R.q
      % L.x        R.x
      % L.lambda   R.lambda
      %
      % <<FD1.jpg>>
      %
      if nargin == 5
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      [a,b,c] = TyreDynamic_Mex( 'abc', self.objectHandle, L, R, pars, MU_U );
    end
    % ---------------------------------------------------------------------
    function DabcDxlxlpu = eval_DabcDxlxlpu( self, L, R, pars, varargin )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      % <<FD2.jpg>>
      %
      if nargin == 5
        MU_U = varargin{1};
      else
        MU_U = self.MU_U_join( varargin{1}, varargin{2} ); % MU, U
      end
      DabcDxlxlpu = TyreDynamic_Mex( 'DabcDxlxlpu', self.objectHandle, L, R, pars, MU_U );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, L, R, pars )
      %
      % Compute the block of the BC of the nonlinear
      % system given left and right states.
      %
      % <<FD3.jpg>>
      %
      [h,c] = TyreDynamic_Mex( 'hc', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlxlop( self, L, R, pars )
      %
      % Compute the block of the BC of the nonlinear system
      % given left and right states.
      %
      % <<FD4.jpg>>
      %
      [Jh,Jc] = TyreDynamic_Mex( 'DhcDxlxlop', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTINUOUS PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function u = eval_u( self, L, R, pars )
      %
      % Compute the control given states and multiplyers.
      %
      if L.iseg == L.iseg
        u = TyreDynamic_Mex( 'u', self.objectHandle, L, R, pars );
      else
        u = zeros(self.dim_u,1);
      end
    end
    % ---------------------------------------------------------------------
    function [DmuDxlxlp, DuDxlxlp] = MU_U_eval_Dxlxlp( self, NODE, pars, MU, U )
      %
      % Compute the jacobian of controls given states and multiplyers.
      %
      [DmuDxlxlp, DuDxlxlp] = TyreDynamic_Mex( 'MU_U_eval_Dxlxlp', self.objectHandle, NODE, pars, MU, U );
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
    %  subject to ODE: rhs( q, x, pars, u ) - A( q, x, pars ) x'
    % ---------------------------------------------------------------------
    function rhs = eval_ode( self, S, pars, U, V )
      %
      % Compute rhs of the ODE `rhs( q, x, pars, u ) - A( q, x, pars ) x'`.
      %
      % S.iseg
      % S.q
      % S.x
      %
      rhs = TyreDynamic_Mex( 'ode', self.objectHandle, S, pars, U, V );
    end
    % ---------------------------------------------------------------------
    %
    function J = eval_DodeDxpuv( self, S, pars, U, V )
      %
      % Compute Jacobian of rhs of the ODE `A( q, x, pars ) x' = rhs( q, x, pars, u )`
      % respect to `x`.
      %
      J = TyreDynamic_Mex( 'DodeDxpuv', self.objectHandle, S, pars, U, V );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, S, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, pars, u )`
      % respect to `pars`.
      %
      A = TyreDynamic_Mex( 'A', self.objectHandle, S, pars );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, L, R, pars )
      bc = TyreDynamic_Mex( 'bc', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, L, R, pars )
      J = TyreDynamic_Mex( 'DbcDxxp', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, S, pars, U )
      target = TyreDynamic_Mex( 'lagrange_target', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxpu = eval_DlagrangeDxpu( self, S, pars, U )
      DlagrangeDxpu = TyreDynamic_Mex( 'DlagrangeDxpu', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function D2lagrangeD2xpu = eval_D2lagrangeD2xpu( self, S, pars, U )
      D2lagrangeD2xpu = TyreDynamic_Mex( 'D2lagrangeD2xpu', self.objectHandle, S, pars, U );
    end
    %
    %   ____  _               _
    %  |  _ \(_)_ __ ___  ___| |_
    %  | | | | | '__/ _ \/ __| __|
    %  | |_| | | | |  __/ (__| |_
    %  |____/|_|_|  \___|\___|\__|
    %
    % ---------------------------------------------------------------------
    function J = eval_Dfd_BCDxlxlp( self, L, R, pars, omega )
      J = TyreDynamic_Mex( 'Dfd_BCDxlxlp', self.objectHandle, L, R, pars, omega );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, L, R, pars )
      target = TyreDynamic_Mex( 'mayer_target', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, L, R, pars )
      DmayerDxxp = TyreDynamic_Mex( 'DmayerDxxp', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function D2mayerD2xxp = eval_D2mayerD2xxp( self, L, R, pars )
      D2mayerD2xxp = TyreDynamic_Mex( 'D2mayerD2xxp', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function c = eval_c( self, S, pars, U )
      %
      % Evaluate contraints c(x,u,p) <= 0
      %
      c = TyreDynamic_Mex( 'LTargs', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function Jc = eval_DcDxpu( self, S, pars, U )
      %
      % Evaluate jacobian of constraints c(x,u,p) <= 0
      %
      Jc = TyreDynamic_Mex( 'DLTargsDxpu', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function Hc = eval_D2cD2xpu( self, S, pars, U, omega )
      %
      % Evaluate hessian of constraints omega . c(x,u,p) <= 0
      %
      Hc = TyreDynamic_Mex( 'D2LTargsD2xpu', self.objectHandle, S, pars, U, omega );
    end
    %
    %
    %   ___ _   _ ____ ___ ____  _____ ____ _____
    %  |_ _| \ | |  _ \_ _|  _ \| ____/ ___|_   _|
    %   | ||  \| | | | | || |_) |  _|| |     | |
    %   | || |\  | |_| | ||  _ <| |__| |___  | |
    %  |___|_| \_|____/___|_| \_\_____\____| |_|
    % ---------------------------------------------------------------------
    function Hxp = eval_Hxp( self, S, pars, MU, U, V )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) =
      %   J(x,u,pars,zeta) + lambda.f(x,u,pars,zeta)
      %
      % Hxp(x,u,p,mu,zeta) = partial_{xp} H(...)
      %
      Hxp = TyreDynamic_Mex( 'Hxp', self.objectHandle, S, pars, MU, U, V );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxpDxpuv( self, S, pars, MU, U, V )
      %
      % Compute the jacobian of `Hxp( q, x, pars, mu, U, V )`
      % respect to `x`, `lambda`, `u` and `pars`.
      %
      J = TyreDynamic_Mex( 'DHxpDxpuv', self.objectHandle, S, pars, MU, U, V );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, S, pars, U )
      %
      % Compute Jp(x,u,pars,zeta)
      %
      J = TyreDynamic_Mex( 'JP', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, S, pars, U )
      %
      % Compute Ju(x,u,pars,zeta)
      %
      J = TyreDynamic_Mex( 'JU', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function JP = eval_JP( self, S, pars, U )
      JP = TyreDynamic_Mex( 'JP', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function JU = eval_JU( self, S, pars, U )
      JU = TyreDynamic_Mex( 'JU', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function LT = eval_LT( self, S, pars, U )
      LT = TyreDynamic_Mex( 'LT', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    function LTargs = eval_LTargs( self, S, pars, U )
      LTargs = TyreDynamic_Mex( 'LTargs', self.objectHandle, S, pars, U );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function jmp = eval_jump( self, L, R, pars )
      jmp = TyreDynamic_Mex( 'jump', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, L, R, pars )
      J = TyreDynamic_Mex( 'DjumpDxlxlp', self.objectHandle, L, R, pars );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, S )
      %
      % S.i_segment
      % S.s
      %
      target = TyreDynamic_Mex( 'mesh_functions', self.objectHandle, S );
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
    function res = D2JPD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2JPD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2JUD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2JUD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2lagrangeD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2lagrangeD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTargsD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2LTargsD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2LTD2xpu_pattern( self )
      res = TyreDynamic_Mex('D2LTD2xpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = D2mayerD2xxp_pattern( self )
      res = TyreDynamic_Mex('D2mayerD2xxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DbcDxxp_pattern( self )
      res = TyreDynamic_Mex('DbcDxxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DetaDxp_pattern( self )
      res = TyreDynamic_Mex('DetaDxp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = Dfd_BCDxlxlp_pattern( self )
      res = TyreDynamic_Mex('Dfd_BCDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDu_pattern( self )
      res = TyreDynamic_Mex('DgDu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DgDxpm_pattern( self )
      res = TyreDynamic_Mex('DgDxpm_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DHxpDxpuv_pattern( self )
      res = TyreDynamic_Mex('DHxpDxpuv_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DjumpDxlxlp_pattern( self )
      res = TyreDynamic_Mex('DjumpDxlxlp_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DLTargsDxpu_pattern( self )
      res = TyreDynamic_Mex('DLTargsDxpu_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function res = DodeDxpuv_pattern( self )
      res = TyreDynamic_Mex('DodeDxpuv_pattern', self.objectHandle );
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
