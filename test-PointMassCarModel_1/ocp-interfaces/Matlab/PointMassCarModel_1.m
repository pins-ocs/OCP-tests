%-----------------------------------------------------------------------%
%  file: PointMassCarModel_1.m                                          %
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


classdef PointMassCarModel_1 < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = PointMassCarModel_1( name )
      %% Allocate the C++ class instance
      self.objectHandle = PointMassCarModel_1_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      PointMassCarModel_1_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      PointMassCarModel_1_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      %
      % Read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      %
      data = PointMassCarModel_1_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      PointMassCarModel_1_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = PointMassCarModel_1_Mex( 'names', self.objectHandle );
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
      res = PointMassCarModel_1_Mex( 'dims', self.objectHandle );
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
      res = PointMassCarModel_1_Mex( 'get_ocp_data', self.objectHandle );
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
      PointMassCarModel_1_Mex( 'infoLevel', self.objectHandle, infoLvl );
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
      PointMassCarModel_1_Mex( 'N_thread', self.objectHandle, nt );
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
      PointMassCarModel_1_Mex( 'remesh', self.objectHandle, new_mesh );
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
      PointMassCarModel_1_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      %
      % Return a structure with the stored guess.
      %
      guess = PointMassCarModel_1_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      %
      % Return a structure with the solution formatted as a guess.
      %
      guess = PointMassCarModel_1_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = PointMassCarModel_1_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function updateContinuation( self, n, old_s, s )
      %
      % Set parameter of the problem for continuation
      % step `n` at fraction `s`
      %
      PointMassCarModel_1_Mex( ...
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
      sol = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution2( self )
      %
      % Return the whole solution.
      %
      sol = PointMassCarModel_1_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution3( self )
      %
      % Return the whole solution.
      %
      sol = PointMassCarModel_1_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      %
      % Combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS.
      %
      sol = PointMassCarModel_1_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      %
      % Unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS.
      %
      [X, Lambda, Pars, Omega] = PointMassCarModel_1_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = n( self )
      %
      % Return the solution for the state: n
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'n' );
    end
    function res = alpha( self )
      %
      % Return the solution for the state: alpha
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'alpha' );
    end
    function res = V( self )
      %
      % Return the solution for the state: V
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'V' );
    end
    function res = Omega( self )
      %
      % Return the solution for the state: Omega
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'Omega' );
    end
    function res = fx( self )
      %
      % Return the solution for the state: fx
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'fx' );
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
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      %
      % Return the solution for the multiplier: lambda2
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      %
      % Return the solution for the multiplier: lambda3
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      %
      % Return the solution for the multiplier: lambda4
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      %
      % Return the solution for the multiplier: lambda5
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = v__fx( self )
      %
      % Return the solution for the control: v__fx
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'v__fx' );
    end
    function res = v__Omega( self )
      %
      % Return the solution for the control: v__Omega
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'v__Omega' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_v__fxControl( self )
      %
      % Return the solution for the post processing variable: v__fxControl
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'v__fxControl' );
    end
    function res = post_processing_v__OmegaControl( self )
      %
      % Return the solution for the post processing variable: v__OmegaControl
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'v__OmegaControl' );
    end
    function res = post_processing_AdherenceEllipse( self )
      %
      % Return the solution for the post processing variable: AdherenceEllipse
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'AdherenceEllipse' );
    end
    function res = post_processing_RoadLeftBorder( self )
      %
      % Return the solution for the post processing variable: RoadLeftBorder
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'RoadLeftBorder' );
    end
    function res = post_processing_RoadRightBorder( self )
      %
      % Return the solution for the post processing variable: RoadRightBorder
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'RoadRightBorder' );
    end
    function res = post_processing_PowerLimit( self )
      %
      % Return the solution for the post processing variable: PowerLimit
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'PowerLimit' );
    end
    function res = post_processing_LimitMinSpeed( self )
      %
      % Return the solution for the post processing variable: LimitMinSpeed
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'LimitMinSpeed' );
    end
    function res = post_processing_xV( self )
      %
      % Return the solution for the post processing variable: xV
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'xV' );
    end
    function res = post_processing_yV( self )
      %
      % Return the solution for the post processing variable: yV
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'yV' );
    end
    function res = post_processing_fy( self )
      %
      % Return the solution for the post processing variable: fy
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'fy' );
    end
    function res = post_processing_mu_x( self )
      %
      % Return the solution for the post processing variable: mu_x
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'mu_x' );
    end
    function res = post_processing_mu_y( self )
      %
      % Return the solution for the post processing variable: mu_y
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'mu_y' );
    end
    function res = post_processing_inv_zeta_dot( self )
      %
      % Return the solution for the post processing variable: inv_zeta_dot
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'inv_zeta_dot' );
    end
    function res = post_processing_zeta_dot_eq( self )
      %
      % Return the solution for the post processing variable: zeta_dot_eq
      %
      res = PointMassCarModel_1_Mex( 'get_solution', self.objectHandle, 'zeta_dot_eq' );
    end

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
      F = PointMassCarModel_1_Mex( 'eval_F', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF( self, x )
      %
      % Return the jacobian of the nonlinear system 
      % of the indirect methods evaluated ad `x`.
      %
      JF = PointMassCarModel_1_Mex( 'eval_JF', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      %
      % Return the pattern of the jacobian of the nonlinear
      % system of the indirect methods.
      %
      JF = PointMassCarModel_1_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function x = get_raw_solution( self )
      %
      % Return the solution in a vector as stored in PINS.
      %
      x = PointMassCarModel_1_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, x )
      %
      % Return set the solution in a vector as stored in PINS.
      %
      PointMassCarModel_1_Mex( 'set_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, x )
      %
      % Check the solution in a vector as stored in PINS.
      %
      ok = PointMassCarModel_1_Mex( 'check_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, x, epsi )
      %
      % Check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance.
      %
      PointMassCarModel_1_Mex( 'check_jacobian', self.objectHandle, x, epsi );
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
      [a,c] = PointMassCarModel_1_Mex( 'ac', self.objectHandle, ...
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
      [Ja,Jc] = PointMassCarModel_1_Mex( 'DacDxlp', self.objectHandle, ...
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
      [h,c] = PointMassCarModel_1_Mex( 'hc', self.objectHandle, ...
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
      [Jh,Jc] = PointMassCarModel_1_Mex( 'DhcDxlop', self.objectHandle, ...
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
      u = PointMassCarModel_1_Mex( 'u', self.objectHandle, ...
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
      DuDxlxlp = PointMassCarModel_1_Mex( 'DuDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      %
      % Compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`.
      %
      rhs = PointMassCarModel_1_Mex( 'rhs_ode', self.objectHandle, ...
        iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      %
      % Compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`.
      %
      J = PointMassCarModel_1_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = PointMassCarModel_1_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      %
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`.
      %
      A = PointMassCarModel_1_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      %
      % Compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`.
      %
      eta = PointMassCarModel_1_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      %
      % Compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      %
      % Compute `nu(q,x,V,pars) = A(q,x,pars) V`.
      %
      nu = PointMassCarModel_1_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      %
      % Compute the Jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      Hx = PointMassCarModel_1_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hu( self, iseg, q, x, lambda, V, u, pars )
      Hx = PointMassCarModel_1_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = PointMassCarModel_1_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      %
      % Compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`.
      %
      J = PointMassCarModel_1_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = PointMassCarModel_1_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDx( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = PointMassCarModel_1_Mex( ...
        'DboundaryConditionsDx', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = PointMassCarModel_1_Mex( ...
        'DboundaryConditionsDp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = PointMassCarModel_1_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = PointMassCarModel_1_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = PointMassCarModel_1_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = PointMassCarModel_1_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, pars )
      J = PointMassCarModel_1_Mex( ...
        'DjumpDxlxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, lambda, u, pars )
      J = PointMassCarModel_1_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, lambda, u, pars )
      J = PointMassCarModel_1_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = PointMassCarModel_1_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               u, pars )
      target = PointMassCarModel_1_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = PointMassCarModel_1_Mex( 'q', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = PointMassCarModel_1_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = PointMassCarModel_1_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_1( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_1', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_2( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_2', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_3( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_3', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_4( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_4', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_1_1( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_1_1', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_1_2( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_1_2', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_1_3( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_1_3', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_1_4( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_1_4', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_2_2( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_2_2', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_2_3( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_2_3', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_2_4( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_2_4', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_3_3( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_3_3', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_3_4( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_3_4', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    function res = inv_zeta__dot_D_4_4( self, xo__V, xo__alpha, xo__n, xo__Kappa )
      res = PointMassCarModel_1_Mex('inv_zeta__dot_D_4_4', self.objectHandle, xo__V, xo__alpha, xo__n, xo__Kappa );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.n(), ...
        self.zeta(), self.alpha(), ...
        self.zeta(), self.V(), ...
        self.zeta(), self.Omega(), ...
        self.zeta(), self.fx(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'n', '\alpha', 'V', '\Omega', 'fx' );
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
        self.zeta(), self.v__fx(), ...
        self.zeta(), self.v__Omega(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'v\_fx', 'v\_\Omega' );
    end
  end
end

% EOF: PointMassCarModel_1.m
