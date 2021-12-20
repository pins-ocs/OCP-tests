%-----------------------------------------------------------------------%
%  file: ICLOCS_ContinuousMP.m                                          %
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


classdef ICLOCS_ContinuousMP < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = ICLOCS_ContinuousMP( name )
      %% Allocate the C++ class instance
      self.objectHandle = ICLOCS_ContinuousMP_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      ICLOCS_ContinuousMP_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      ICLOCS_ContinuousMP_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the read data
      %
      data = ICLOCS_ContinuousMP_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      %
      % Initialize an OCP problem reading data from a file or a MATLAB stucture
      %
      ICLOCS_ContinuousMP_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = ICLOCS_ContinuousMP_Mex( 'names', self.objectHandle );
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
      res = ICLOCS_ContinuousMP_Mex( 'dims', self.objectHandle );
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
      res = ICLOCS_ContinuousMP_Mex( 'get_ocp_data', self.objectHandle );
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
      ICLOCS_ContinuousMP_Mex( 'infoLevel', self.objectHandle, infoLvl );
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
      ICLOCS_ContinuousMP_Mex( 'set_max_threads', self.objectHandle, nt );
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
      ICLOCS_ContinuousMP_Mex( 'remesh', self.objectHandle, new_mesh );
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
      ICLOCS_ContinuousMP_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = ICLOCS_ContinuousMP_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = ICLOCS_ContinuousMP_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = ICLOCS_ContinuousMP_Mex( 'solve', self.objectHandle, varargin{:} );
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
      ICLOCS_ContinuousMP_Mex( ...
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
      sol = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, varargin{:} );
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
      sol = ICLOCS_ContinuousMP_Mex( 'get_solution2', self.objectHandle );
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
      sol = ICLOCS_ContinuousMP_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = ICLOCS_ContinuousMP_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega ] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = ICLOCS_ContinuousMP_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = x1( self )
      %
      % Return the solution for the state: x1
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x1' );
    end
    function res = x2( self )
      %
      % Return the solution for the state: x2
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x2' );
    end
    function res = x3( self )
      %
      % Return the solution for the state: x3
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x3' );
    end
    function res = x4( self )
      %
      % Return the solution for the state: x4
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x4' );
    end
    function res = x5( self )
      %
      % Return the solution for the state: x5
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x5' );
    end
    function res = x6( self )
      %
      % Return the solution for the state: x6
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x6' );
    end
    function res = x7( self )
      %
      % Return the solution for the state: x7
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x7' );
    end
    function res = x8( self )
      %
      % Return the solution for the state: x8
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x8' );
    end
    function res = x9( self )
      %
      % Return the solution for the state: x9
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x9' );
    end
    function res = x10( self )
      %
      % Return the solution for the state: x10
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x10' );
    end
    function res = x11( self )
      %
      % Return the solution for the state: x11
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x11' );
    end
    function res = x12( self )
      %
      % Return the solution for the state: x12
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x12' );
    end
    function res = x13( self )
      %
      % Return the solution for the state: x13
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x13' );
    end
    function res = x14( self )
      %
      % Return the solution for the state: x14
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x14' );
    end
    function res = x15( self )
      %
      % Return the solution for the state: x15
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x15' );
    end
    function res = x16( self )
      %
      % Return the solution for the state: x16
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x16' );
    end
    function res = x17( self )
      %
      % Return the solution for the state: x17
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x17' );
    end
    function res = x18( self )
      %
      % Return the solution for the state: x18
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x18' );
    end
    function res = x19( self )
      %
      % Return the solution for the state: x19
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x19' );
    end
    function res = x20( self )
      %
      % Return the solution for the state: x20
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'x20' );
    end
    function res = y1( self )
      %
      % Return the solution for the state: y1
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y1' );
    end
    function res = y2( self )
      %
      % Return the solution for the state: y2
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y2' );
    end
    function res = y3( self )
      %
      % Return the solution for the state: y3
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y3' );
    end
    function res = y4( self )
      %
      % Return the solution for the state: y4
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y4' );
    end
    function res = y5( self )
      %
      % Return the solution for the state: y5
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y5' );
    end
    function res = y6( self )
      %
      % Return the solution for the state: y6
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y6' );
    end
    function res = y7( self )
      %
      % Return the solution for the state: y7
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y7' );
    end
    function res = y8( self )
      %
      % Return the solution for the state: y8
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y8' );
    end
    function res = y9( self )
      %
      % Return the solution for the state: y9
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y9' );
    end
    function res = y10( self )
      %
      % Return the solution for the state: y10
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y10' );
    end
    function res = y11( self )
      %
      % Return the solution for the state: y11
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y11' );
    end
    function res = y12( self )
      %
      % Return the solution for the state: y12
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y12' );
    end
    function res = y13( self )
      %
      % Return the solution for the state: y13
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y13' );
    end
    function res = y14( self )
      %
      % Return the solution for the state: y14
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y14' );
    end
    function res = y15( self )
      %
      % Return the solution for the state: y15
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y15' );
    end
    function res = y16( self )
      %
      % Return the solution for the state: y16
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y16' );
    end
    function res = y17( self )
      %
      % Return the solution for the state: y17
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y17' );
    end
    function res = y18( self )
      %
      % Return the solution for the state: y18
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y18' );
    end
    function res = y19( self )
      %
      % Return the solution for the state: y19
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y19' );
    end
    function res = y20( self )
      %
      % Return the solution for the state: y20
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'y20' );
    end
    function res = xx1( self )
      %
      % Return the solution for the state: xx1
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx1' );
    end
    function res = xx2( self )
      %
      % Return the solution for the state: xx2
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx2' );
    end
    function res = xx3( self )
      %
      % Return the solution for the state: xx3
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx3' );
    end
    function res = xx4( self )
      %
      % Return the solution for the state: xx4
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx4' );
    end
    function res = xx5( self )
      %
      % Return the solution for the state: xx5
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx5' );
    end
    function res = xx6( self )
      %
      % Return the solution for the state: xx6
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx6' );
    end
    function res = xx7( self )
      %
      % Return the solution for the state: xx7
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx7' );
    end
    function res = xx8( self )
      %
      % Return the solution for the state: xx8
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx8' );
    end
    function res = xx9( self )
      %
      % Return the solution for the state: xx9
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx9' );
    end
    function res = xx10( self )
      %
      % Return the solution for the state: xx10
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx10' );
    end
    function res = xx11( self )
      %
      % Return the solution for the state: xx11
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx11' );
    end
    function res = xx12( self )
      %
      % Return the solution for the state: xx12
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx12' );
    end
    function res = xx13( self )
      %
      % Return the solution for the state: xx13
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx13' );
    end
    function res = xx14( self )
      %
      % Return the solution for the state: xx14
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx14' );
    end
    function res = xx15( self )
      %
      % Return the solution for the state: xx15
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx15' );
    end
    function res = xx16( self )
      %
      % Return the solution for the state: xx16
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx16' );
    end
    function res = xx17( self )
      %
      % Return the solution for the state: xx17
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx17' );
    end
    function res = xx18( self )
      %
      % Return the solution for the state: xx18
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx18' );
    end
    function res = xx19( self )
      %
      % Return the solution for the state: xx19
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx19' );
    end
    function res = xx20( self )
      %
      % Return the solution for the state: xx20
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'xx20' );
    end
    function res = yy1( self )
      %
      % Return the solution for the state: yy1
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy1' );
    end
    function res = yy2( self )
      %
      % Return the solution for the state: yy2
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy2' );
    end
    function res = yy3( self )
      %
      % Return the solution for the state: yy3
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy3' );
    end
    function res = yy4( self )
      %
      % Return the solution for the state: yy4
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy4' );
    end
    function res = yy5( self )
      %
      % Return the solution for the state: yy5
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy5' );
    end
    function res = yy6( self )
      %
      % Return the solution for the state: yy6
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy6' );
    end
    function res = yy7( self )
      %
      % Return the solution for the state: yy7
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy7' );
    end
    function res = yy8( self )
      %
      % Return the solution for the state: yy8
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy8' );
    end
    function res = yy9( self )
      %
      % Return the solution for the state: yy9
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy9' );
    end
    function res = yy10( self )
      %
      % Return the solution for the state: yy10
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy10' );
    end
    function res = yy11( self )
      %
      % Return the solution for the state: yy11
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy11' );
    end
    function res = yy12( self )
      %
      % Return the solution for the state: yy12
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy12' );
    end
    function res = yy13( self )
      %
      % Return the solution for the state: yy13
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy13' );
    end
    function res = yy14( self )
      %
      % Return the solution for the state: yy14
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy14' );
    end
    function res = yy15( self )
      %
      % Return the solution for the state: yy15
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy15' );
    end
    function res = yy16( self )
      %
      % Return the solution for the state: yy16
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy16' );
    end
    function res = yy17( self )
      %
      % Return the solution for the state: yy17
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy17' );
    end
    function res = yy18( self )
      %
      % Return the solution for the state: yy18
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy18' );
    end
    function res = yy19( self )
      %
      % Return the solution for the state: yy19
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy19' );
    end
    function res = yy20( self )
      %
      % Return the solution for the state: yy20
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'yy20' );
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
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      %
      % Return the solution for the multiplier: lambda6
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
    end
    function res = lambda7( self )
      %
      % Return the solution for the multiplier: lambda7
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda7__xo' );
    end
    function res = lambda8( self )
      %
      % Return the solution for the multiplier: lambda8
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda8__xo' );
    end
    function res = lambda9( self )
      %
      % Return the solution for the multiplier: lambda9
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda9__xo' );
    end
    function res = lambda10( self )
      %
      % Return the solution for the multiplier: lambda10
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda10__xo' );
    end
    function res = lambda11( self )
      %
      % Return the solution for the multiplier: lambda11
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda11__xo' );
    end
    function res = lambda12( self )
      %
      % Return the solution for the multiplier: lambda12
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda12__xo' );
    end
    function res = lambda13( self )
      %
      % Return the solution for the multiplier: lambda13
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda13__xo' );
    end
    function res = lambda14( self )
      %
      % Return the solution for the multiplier: lambda14
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda14__xo' );
    end
    function res = lambda15( self )
      %
      % Return the solution for the multiplier: lambda15
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda15__xo' );
    end
    function res = lambda16( self )
      %
      % Return the solution for the multiplier: lambda16
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda16__xo' );
    end
    function res = lambda17( self )
      %
      % Return the solution for the multiplier: lambda17
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda17__xo' );
    end
    function res = lambda18( self )
      %
      % Return the solution for the multiplier: lambda18
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda18__xo' );
    end
    function res = lambda19( self )
      %
      % Return the solution for the multiplier: lambda19
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda19__xo' );
    end
    function res = lambda20( self )
      %
      % Return the solution for the multiplier: lambda20
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda20__xo' );
    end
    function res = lambda21( self )
      %
      % Return the solution for the multiplier: lambda21
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda21__xo' );
    end
    function res = lambda22( self )
      %
      % Return the solution for the multiplier: lambda22
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda22__xo' );
    end
    function res = lambda23( self )
      %
      % Return the solution for the multiplier: lambda23
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda23__xo' );
    end
    function res = lambda24( self )
      %
      % Return the solution for the multiplier: lambda24
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda24__xo' );
    end
    function res = lambda25( self )
      %
      % Return the solution for the multiplier: lambda25
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda25__xo' );
    end
    function res = lambda26( self )
      %
      % Return the solution for the multiplier: lambda26
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda26__xo' );
    end
    function res = lambda27( self )
      %
      % Return the solution for the multiplier: lambda27
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda27__xo' );
    end
    function res = lambda28( self )
      %
      % Return the solution for the multiplier: lambda28
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda28__xo' );
    end
    function res = lambda29( self )
      %
      % Return the solution for the multiplier: lambda29
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda29__xo' );
    end
    function res = lambda30( self )
      %
      % Return the solution for the multiplier: lambda30
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda30__xo' );
    end
    function res = lambda31( self )
      %
      % Return the solution for the multiplier: lambda31
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda31__xo' );
    end
    function res = lambda32( self )
      %
      % Return the solution for the multiplier: lambda32
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda32__xo' );
    end
    function res = lambda33( self )
      %
      % Return the solution for the multiplier: lambda33
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda33__xo' );
    end
    function res = lambda34( self )
      %
      % Return the solution for the multiplier: lambda34
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda34__xo' );
    end
    function res = lambda35( self )
      %
      % Return the solution for the multiplier: lambda35
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda35__xo' );
    end
    function res = lambda36( self )
      %
      % Return the solution for the multiplier: lambda36
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda36__xo' );
    end
    function res = lambda37( self )
      %
      % Return the solution for the multiplier: lambda37
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda37__xo' );
    end
    function res = lambda38( self )
      %
      % Return the solution for the multiplier: lambda38
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda38__xo' );
    end
    function res = lambda39( self )
      %
      % Return the solution for the multiplier: lambda39
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda39__xo' );
    end
    function res = lambda40( self )
      %
      % Return the solution for the multiplier: lambda40
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda40__xo' );
    end
    function res = lambda41( self )
      %
      % Return the solution for the multiplier: lambda41
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda41__xo' );
    end
    function res = lambda42( self )
      %
      % Return the solution for the multiplier: lambda42
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda42__xo' );
    end
    function res = lambda43( self )
      %
      % Return the solution for the multiplier: lambda43
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda43__xo' );
    end
    function res = lambda44( self )
      %
      % Return the solution for the multiplier: lambda44
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda44__xo' );
    end
    function res = lambda45( self )
      %
      % Return the solution for the multiplier: lambda45
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda45__xo' );
    end
    function res = lambda46( self )
      %
      % Return the solution for the multiplier: lambda46
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda46__xo' );
    end
    function res = lambda47( self )
      %
      % Return the solution for the multiplier: lambda47
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda47__xo' );
    end
    function res = lambda48( self )
      %
      % Return the solution for the multiplier: lambda48
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda48__xo' );
    end
    function res = lambda49( self )
      %
      % Return the solution for the multiplier: lambda49
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda49__xo' );
    end
    function res = lambda50( self )
      %
      % Return the solution for the multiplier: lambda50
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda50__xo' );
    end
    function res = lambda51( self )
      %
      % Return the solution for the multiplier: lambda51
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda51__xo' );
    end
    function res = lambda52( self )
      %
      % Return the solution for the multiplier: lambda52
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda52__xo' );
    end
    function res = lambda53( self )
      %
      % Return the solution for the multiplier: lambda53
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda53__xo' );
    end
    function res = lambda54( self )
      %
      % Return the solution for the multiplier: lambda54
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda54__xo' );
    end
    function res = lambda55( self )
      %
      % Return the solution for the multiplier: lambda55
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda55__xo' );
    end
    function res = lambda56( self )
      %
      % Return the solution for the multiplier: lambda56
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda56__xo' );
    end
    function res = lambda57( self )
      %
      % Return the solution for the multiplier: lambda57
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda57__xo' );
    end
    function res = lambda58( self )
      %
      % Return the solution for the multiplier: lambda58
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda58__xo' );
    end
    function res = lambda59( self )
      %
      % Return the solution for the multiplier: lambda59
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda59__xo' );
    end
    function res = lambda60( self )
      %
      % Return the solution for the multiplier: lambda60
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda60__xo' );
    end
    function res = lambda61( self )
      %
      % Return the solution for the multiplier: lambda61
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda61__xo' );
    end
    function res = lambda62( self )
      %
      % Return the solution for the multiplier: lambda62
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda62__xo' );
    end
    function res = lambda63( self )
      %
      % Return the solution for the multiplier: lambda63
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda63__xo' );
    end
    function res = lambda64( self )
      %
      % Return the solution for the multiplier: lambda64
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda64__xo' );
    end
    function res = lambda65( self )
      %
      % Return the solution for the multiplier: lambda65
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda65__xo' );
    end
    function res = lambda66( self )
      %
      % Return the solution for the multiplier: lambda66
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda66__xo' );
    end
    function res = lambda67( self )
      %
      % Return the solution for the multiplier: lambda67
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda67__xo' );
    end
    function res = lambda68( self )
      %
      % Return the solution for the multiplier: lambda68
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda68__xo' );
    end
    function res = lambda69( self )
      %
      % Return the solution for the multiplier: lambda69
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda69__xo' );
    end
    function res = lambda70( self )
      %
      % Return the solution for the multiplier: lambda70
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda70__xo' );
    end
    function res = lambda71( self )
      %
      % Return the solution for the multiplier: lambda71
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda71__xo' );
    end
    function res = lambda72( self )
      %
      % Return the solution for the multiplier: lambda72
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda72__xo' );
    end
    function res = lambda73( self )
      %
      % Return the solution for the multiplier: lambda73
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda73__xo' );
    end
    function res = lambda74( self )
      %
      % Return the solution for the multiplier: lambda74
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda74__xo' );
    end
    function res = lambda75( self )
      %
      % Return the solution for the multiplier: lambda75
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda75__xo' );
    end
    function res = lambda76( self )
      %
      % Return the solution for the multiplier: lambda76
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda76__xo' );
    end
    function res = lambda77( self )
      %
      % Return the solution for the multiplier: lambda77
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda77__xo' );
    end
    function res = lambda78( self )
      %
      % Return the solution for the multiplier: lambda78
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda78__xo' );
    end
    function res = lambda79( self )
      %
      % Return the solution for the multiplier: lambda79
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda79__xo' );
    end
    function res = lambda80( self )
      %
      % Return the solution for the multiplier: lambda80
      %
      res = ICLOCS_ContinuousMP_Mex( 'get_solution', self.objectHandle, 'lambda80__xo' );
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

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function U = init_U( self, x, do_minimization )
      %
      % Initialize `u`
      %
      U = ICLOCS_ContinuousMP_Mex( 'init_U', self.objectHandle, x, do_minimization );
    end
    % ---------------------------------------------------------------------
    function U = eval_U( self, x, u_guess )
      %
      % Compute `u`
      %
      U = ICLOCS_ContinuousMP_Mex( 'eval_U', self.objectHandle, x, u_guess );
    end
    % ---------------------------------------------------------------------
    function [F,ok] = eval_F( self, x, u )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `x` and `u`.
      %
      [F,ok] = ICLOCS_ContinuousMP_Mex( 'eval_F', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function [JF,ok] = eval_JF( self, x, u )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x` and `u`.
      %
      [JF,ok] = ICLOCS_ContinuousMP_Mex( 'eval_JF', self.objectHandle, x, u );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = ICLOCS_ContinuousMP_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function [z,u] = get_raw_solution( self )
      %
      % Return the solution states and multipliers and controls as stored in PINS.
      %
      [z,u] = ICLOCS_ContinuousMP_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, z, u )
      %
      % Set the solution in a vector as stored in PINS.
      %
      ICLOCS_ContinuousMP_Mex( 'set_raw_solution', self.objectHandle, z, u );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, z )
      %
      % Return true if the solution does not violate 
      % admissible regions.
      %
      ok = ICLOCS_ContinuousMP_Mex( 'check_raw_solution', self.objectHandle, z );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, z, u, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      ICLOCS_ContinuousMP_Mex( 'check_jacobian', self.objectHandle, z, u, epsi );
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
      [a,c] = ICLOCS_ContinuousMP_Mex( 'ac', self.objectHandle, ...
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
      [Ja,Jc] = ICLOCS_ContinuousMP_Mex( 'DacDxlxlp', self.objectHandle, ...
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
      [h,c] = ICLOCS_ContinuousMP_Mex( 'hc', self.objectHandle, ...
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
      [Jh,Jc] = ICLOCS_ContinuousMP_Mex( 'DhcDxlxlop', self.objectHandle, ...
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
      u = ICLOCS_ContinuousMP_Mex( 'u', self.objectHandle, ...
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
      DuDxlxlp = ICLOCS_ContinuousMP_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = ICLOCS_ContinuousMP_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = ICLOCS_ContinuousMP_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = ICLOCS_ContinuousMP_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = ICLOCS_ContinuousMP_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = ICLOCS_ContinuousMP_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Derivative of H(x,V,lambda,u,pars,zeta) = 
      %   J(x,u,pars,zeta) + lambda.(f(x,u,pars,zeta)-A(x,pars,zeta)*V) 
      %
      % Hx(x,V,lambda,u,p,zeta) = partial_x H(...)
      %
      Hx = ICLOCS_ContinuousMP_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `pars`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
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
      Hu = ICLOCS_ContinuousMP_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = ICLOCS_ContinuousMP_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = ICLOCS_ContinuousMP_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = ICLOCS_ContinuousMP_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDxxp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = ICLOCS_ContinuousMP_Mex( ...
        'DboundaryConditionsDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = ICLOCS_ContinuousMP_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = ICLOCS_ContinuousMP_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = ICLOCS_ContinuousMP_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = ICLOCS_ContinuousMP_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = ICLOCS_ContinuousMP_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, u, pars )
      J = ICLOCS_ContinuousMP_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, u, pars )
      J = ICLOCS_ContinuousMP_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = ICLOCS_ContinuousMP_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DlagrangeDxup = eval_DlagrangeDxup( self, iseg, q, x, u, pars )
      DlagrangeDxup = ICLOCS_ContinuousMP_Mex( ...
        'DlagrangeDxup', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               pars )
      target = ICLOCS_ContinuousMP_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function DmayerDxxp = eval_DmayerDxxp( self, iseg_L, q_L, x_L, ...
                                                 iseg_R, q_R, x_R, ...
                                                 pars )
      DmayerDxxp = ICLOCS_ContinuousMP_Mex( ...
        'DmayerDxxp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = ICLOCS_ContinuousMP_Mex( 'mesh_functions', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = ICLOCS_ContinuousMP_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = ICLOCS_ContinuousMP_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x1(), ...
        self.zeta(), self.x2(), ...
        self.zeta(), self.x3(), ...
        self.zeta(), self.x4(), ...
        self.zeta(), self.x5(), ...
        self.zeta(), self.x6(), ...
        self.zeta(), self.x7(), ...
        self.zeta(), self.x8(), ...
        self.zeta(), self.x9(), ...
        self.zeta(), self.x10(), ...
        self.zeta(), self.x11(), ...
        self.zeta(), self.x12(), ...
        self.zeta(), self.x13(), ...
        self.zeta(), self.x14(), ...
        self.zeta(), self.x15(), ...
        self.zeta(), self.x16(), ...
        self.zeta(), self.x17(), ...
        self.zeta(), self.x18(), ...
        self.zeta(), self.x19(), ...
        self.zeta(), self.x20(), ...
        self.zeta(), self.y1(), ...
        self.zeta(), self.y2(), ...
        self.zeta(), self.y3(), ...
        self.zeta(), self.y4(), ...
        self.zeta(), self.y5(), ...
        self.zeta(), self.y6(), ...
        self.zeta(), self.y7(), ...
        self.zeta(), self.y8(), ...
        self.zeta(), self.y9(), ...
        self.zeta(), self.y10(), ...
        self.zeta(), self.y11(), ...
        self.zeta(), self.y12(), ...
        self.zeta(), self.y13(), ...
        self.zeta(), self.y14(), ...
        self.zeta(), self.y15(), ...
        self.zeta(), self.y16(), ...
        self.zeta(), self.y17(), ...
        self.zeta(), self.y18(), ...
        self.zeta(), self.y19(), ...
        self.zeta(), self.y20(), ...
        self.zeta(), self.xx1(), ...
        self.zeta(), self.xx2(), ...
        self.zeta(), self.xx3(), ...
        self.zeta(), self.xx4(), ...
        self.zeta(), self.xx5(), ...
        self.zeta(), self.xx6(), ...
        self.zeta(), self.xx7(), ...
        self.zeta(), self.xx8(), ...
        self.zeta(), self.xx9(), ...
        self.zeta(), self.xx10(), ...
        self.zeta(), self.xx11(), ...
        self.zeta(), self.xx12(), ...
        self.zeta(), self.xx13(), ...
        self.zeta(), self.xx14(), ...
        self.zeta(), self.xx15(), ...
        self.zeta(), self.xx16(), ...
        self.zeta(), self.xx17(), ...
        self.zeta(), self.xx18(), ...
        self.zeta(), self.xx19(), ...
        self.zeta(), self.xx20(), ...
        self.zeta(), self.yy1(), ...
        self.zeta(), self.yy2(), ...
        self.zeta(), self.yy3(), ...
        self.zeta(), self.yy4(), ...
        self.zeta(), self.yy5(), ...
        self.zeta(), self.yy6(), ...
        self.zeta(), self.yy7(), ...
        self.zeta(), self.yy8(), ...
        self.zeta(), self.yy9(), ...
        self.zeta(), self.yy10(), ...
        self.zeta(), self.yy11(), ...
        self.zeta(), self.yy12(), ...
        self.zeta(), self.yy13(), ...
        self.zeta(), self.yy14(), ...
        self.zeta(), self.yy15(), ...
        self.zeta(), self.yy16(), ...
        self.zeta(), self.yy17(), ...
        self.zeta(), self.yy18(), ...
        self.zeta(), self.yy19(), ...
        self.zeta(), self.yy20(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x1', 'x2', 'x3', 'x4', 'x5', 'x6', 'x7', 'x8', 'x9', 'x10', 'x11', 'x12', 'x13', 'x14', 'x15', 'x16', 'x17', 'x18', 'x19', 'x20', 'y1', 'y2', 'y3', 'y4', 'y5', 'y6', 'y7', 'y8', 'y9', 'y10', 'y11', 'y12', 'y13', 'y14', 'y15', 'y16', 'y17', 'y18', 'y19', 'y20', 'xx1', 'xx2', 'xx3', 'xx4', 'xx5', 'xx6', 'xx7', 'xx8', 'xx9', 'xx10', 'xx11', 'xx12', 'xx13', 'xx14', 'xx15', 'xx16', 'xx17', 'xx18', 'xx19', 'xx20', 'yy1', 'yy2', 'yy3', 'yy4', 'yy5', 'yy6', 'yy7', 'yy8', 'yy9', 'yy10', 'yy11', 'yy12', 'yy13', 'yy14', 'yy15', 'yy16', 'yy17', 'yy18', 'yy19', 'yy20' );
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
        self.zeta(), self.lambda8(), ...
        self.zeta(), self.lambda9(), ...
        self.zeta(), self.lambda10(), ...
        self.zeta(), self.lambda11(), ...
        self.zeta(), self.lambda12(), ...
        self.zeta(), self.lambda13(), ...
        self.zeta(), self.lambda14(), ...
        self.zeta(), self.lambda15(), ...
        self.zeta(), self.lambda16(), ...
        self.zeta(), self.lambda17(), ...
        self.zeta(), self.lambda18(), ...
        self.zeta(), self.lambda19(), ...
        self.zeta(), self.lambda20(), ...
        self.zeta(), self.lambda21(), ...
        self.zeta(), self.lambda22(), ...
        self.zeta(), self.lambda23(), ...
        self.zeta(), self.lambda24(), ...
        self.zeta(), self.lambda25(), ...
        self.zeta(), self.lambda26(), ...
        self.zeta(), self.lambda27(), ...
        self.zeta(), self.lambda28(), ...
        self.zeta(), self.lambda29(), ...
        self.zeta(), self.lambda30(), ...
        self.zeta(), self.lambda31(), ...
        self.zeta(), self.lambda32(), ...
        self.zeta(), self.lambda33(), ...
        self.zeta(), self.lambda34(), ...
        self.zeta(), self.lambda35(), ...
        self.zeta(), self.lambda36(), ...
        self.zeta(), self.lambda37(), ...
        self.zeta(), self.lambda38(), ...
        self.zeta(), self.lambda39(), ...
        self.zeta(), self.lambda40(), ...
        self.zeta(), self.lambda41(), ...
        self.zeta(), self.lambda42(), ...
        self.zeta(), self.lambda43(), ...
        self.zeta(), self.lambda44(), ...
        self.zeta(), self.lambda45(), ...
        self.zeta(), self.lambda46(), ...
        self.zeta(), self.lambda47(), ...
        self.zeta(), self.lambda48(), ...
        self.zeta(), self.lambda49(), ...
        self.zeta(), self.lambda50(), ...
        self.zeta(), self.lambda51(), ...
        self.zeta(), self.lambda52(), ...
        self.zeta(), self.lambda53(), ...
        self.zeta(), self.lambda54(), ...
        self.zeta(), self.lambda55(), ...
        self.zeta(), self.lambda56(), ...
        self.zeta(), self.lambda57(), ...
        self.zeta(), self.lambda58(), ...
        self.zeta(), self.lambda59(), ...
        self.zeta(), self.lambda60(), ...
        self.zeta(), self.lambda61(), ...
        self.zeta(), self.lambda62(), ...
        self.zeta(), self.lambda63(), ...
        self.zeta(), self.lambda64(), ...
        self.zeta(), self.lambda65(), ...
        self.zeta(), self.lambda66(), ...
        self.zeta(), self.lambda67(), ...
        self.zeta(), self.lambda68(), ...
        self.zeta(), self.lambda69(), ...
        self.zeta(), self.lambda70(), ...
        self.zeta(), self.lambda71(), ...
        self.zeta(), self.lambda72(), ...
        self.zeta(), self.lambda73(), ...
        self.zeta(), self.lambda74(), ...
        self.zeta(), self.lambda75(), ...
        self.zeta(), self.lambda76(), ...
        self.zeta(), self.lambda77(), ...
        self.zeta(), self.lambda78(), ...
        self.zeta(), self.lambda79(), ...
        self.zeta(), self.lambda80(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2', '\lambda3', '\lambda4', '\lambda5', '\lambda6', '\lambda7', '\lambda8', '\lambda9', '\lambda10', '\lambda11', '\lambda12', '\lambda13', '\lambda14', '\lambda15', '\lambda16', '\lambda17', '\lambda18', '\lambda19', '\lambda20', '\lambda21', '\lambda22', '\lambda23', '\lambda24', '\lambda25', '\lambda26', '\lambda27', '\lambda28', '\lambda29', '\lambda30', '\lambda31', '\lambda32', '\lambda33', '\lambda34', '\lambda35', '\lambda36', '\lambda37', '\lambda38', '\lambda39', '\lambda40', '\lambda41', '\lambda42', '\lambda43', '\lambda44', '\lambda45', '\lambda46', '\lambda47', '\lambda48', '\lambda49', '\lambda50', '\lambda51', '\lambda52', '\lambda53', '\lambda54', '\lambda55', '\lambda56', '\lambda57', '\lambda58', '\lambda59', '\lambda60', '\lambda61', '\lambda62', '\lambda63', '\lambda64', '\lambda65', '\lambda66', '\lambda67', '\lambda68', '\lambda69', '\lambda70', '\lambda71', '\lambda72', '\lambda73', '\lambda74', '\lambda75', '\lambda76', '\lambda77', '\lambda78', '\lambda79', '\lambda80' );
    end
    % ---------------------------------------------------------------------
    function plot_controls( self )
      % no control to plot
    end
  end
end

% EOF: ICLOCS_ContinuousMP.m
