%-----------------------------------------------------------------------%
%  file: Dadebo1.m                                                      %
%                                                                       %
%  version: 1.0   date 3/6/2021                                         %
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


classdef Dadebo1 < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = Dadebo1( name )
      %% Allocate the C++ class instance
      self.objectHandle = Dadebo1_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      Dadebo1_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      Dadebo1_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      %
      data = Dadebo1_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      Dadebo1_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = Dadebo1_Mex( 'names', self.objectHandle );
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
      res = Dadebo1_Mex( 'dims', self.objectHandle );
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
      res = Dadebo1_Mex( 'get_ocp_data', self.objectHandle );
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
      Dadebo1_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NUM THREAD
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function N_thread( self, nt )
      %
      % Set information level.
      %
      Dadebo1_Mex( 'N_thread', self.objectHandle, nt );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % REMESH
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function remesh( self, new_mesh )
      %
      % Use structure to initialize mesh.
      %
      Dadebo1_Mex( 'remesh', self.objectHandle, new_mesh );
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
      Dadebo1_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = Dadebo1_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = Dadebo1_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = Dadebo1_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function updateContinuation( self, n, old_s, s )
      %
      % Set parameter of the problem for continuation
      % step `n` at fraction `s`
      %
      Dadebo1_Mex( ...
        'updateContinuation', self.objectHandle, n, old_s, s ...
      );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GET SOLUTION
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function sol = solution( self, varargin )
      %
      % Return the whole solution or the column of name varargin{1}.
      %
      sol = Dadebo1_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution2( self )
      %
      % Return the whole solution.
      %
      sol = Dadebo1_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution3( self )
      %
      % Return the whole solution.
      %
      sol = Dadebo1_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = Dadebo1_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = Dadebo1_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'zeta' );
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
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'x' );
    end
    function res = y( self )
      %
      % Return the solution for the state: y
      %
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'y' );
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
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = u( self )
      %
      % Return the solution for the control: u
      %
      res = Dadebo1_Mex( 'get_solution', self.objectHandle, 'u' );
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
    function F = eval_F( self, x )
      %
      % Return the nonlinear system of the indirect
      % methods evaluated at `x`.
      %
      F = Dadebo1_Mex( 'eval_F', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF( self, x )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x`.
      %
      JF = Dadebo1_Mex( 'eval_JF', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = Dadebo1_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function x = get_raw_solution( self )
      %
      % Return the solution in a vector as stored in PINS.
      %
      x = Dadebo1_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, x )
      %
      % Return set the solution in a vector as stored in PINS.
      %
      Dadebo1_Mex( 'set_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, x )
      %
      % Check the solution in a vector as stored in PINS.
      %
      ok = Dadebo1_Mex( 'check_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, x, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      Dadebo1_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,c] = eval_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      [a,c] = Dadebo1_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [Ja,Jc] = eval_DacDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, pars, U )
      %
      % Compute the block of the nonlinear system
      % given left and right states.
      %
      [Ja,Jc] = Dadebo1_Mex( 'DacDxlp', self.objectHandle, ...
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
      [h,c] = Dadebo1_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlop( self, iseg_L, q_L, x_L, lambda_L, ...
                                            iseg_R, q_R, x_R, lambda_R, pars )
      %
      % Compute the block of the BC of the nonlinear system
      % given left and right states.
      %
      [Jh,Jc] = Dadebo1_Mex( 'DhcDxlop', self.objectHandle, ...
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
      u = Dadebo1_Mex( 'u', self.objectHandle, ...
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
      DuDxlxlp = Dadebo1_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = Dadebo1_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = Dadebo1_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = Dadebo1_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = Dadebo1_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = Dadebo1_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = Dadebo1_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = Dadebo1_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = Dadebo1_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      Hx = Dadebo1_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hu( self, iseg, q, x, lambda, V, u, pars )
      Hx = Dadebo1_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = Dadebo1_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = Dadebo1_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = Dadebo1_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDx( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = Dadebo1_Mex( ...
        'DboundaryConditionsDx', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = Dadebo1_Mex( ...
        'DboundaryConditionsDp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = Dadebo1_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = Dadebo1_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = Dadebo1_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = Dadebo1_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = Dadebo1_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, lambda, u, pars )
      J = Dadebo1_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, lambda, u, pars )
      J = Dadebo1_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = Dadebo1_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               u, pars )
      target = Dadebo1_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = Dadebo1_Mex( 'q', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = Dadebo1_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = Dadebo1_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.y(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'y' );
    end
    % ---------------------------------------------------------------------
    function plot_multipliers( self )
      plot(...
        self.zeta(), self.lambda1(), ...
        self.zeta(), self.lambda2(), ...
        'Linewidth', 2 ...
      );
      title('multipliers');
      legend( '\lambda1', '\lambda2' );
    end
    % ---------------------------------------------------------------------
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

% EOF: Dadebo1.m
