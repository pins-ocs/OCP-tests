%-----------------------------------------------------------------------%
%  file: PointMassCarModel_4.m                                          %
%                                                                       %
%  version: 1.0   date 26/2/2021                                        %
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


classdef PointMassCarModel_4 < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = PointMassCarModel_4( name )
      %% Allocate the C++ class instance
      self.objectHandle = PointMassCarModel_4_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      PointMassCarModel_4_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      PointMassCarModel_4_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      % read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      data = PointMassCarModel_4_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      PointMassCarModel_4_Mex( 'setup', self.objectHandle, fname_or_struct );
    end
    % ---------------------------------------------------------------------
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
      n = PointMassCarModel_4_Mex( 'names', self.objectHandle );
    end
    % ---------------------------------------------------------------------
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
      res = PointMassCarModel_4_Mex( 'dims', self.objectHandle );
    end
    % ---------------------------------------------------------------------
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
      res = PointMassCarModel_4_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO LEVEL
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      % set information level
      PointMassCarModel_4_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NUM THREAD
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function N_thread( self, nt )
      % set information level
      PointMassCarModel_4_Mex( 'N_thread', self.objectHandle, nt );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GUESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_guess( self, varargin )
      % with no argument use predefined guess, otherwise
      % use structure to initialize guess
      PointMassCarModel_4_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      % return a structure with the stored guess
      guess = PointMassCarModel_4_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      % return a structure with the solution formatted as a guess
      guess = PointMassCarModel_4_Mex( 'get_solution_as_guess', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % SOLVE
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function ok = solve( self, varargin )
      % ok = false if computation failed
      % ok = true if computation is succesfull
      % varargin{1} = timeout
      ok = PointMassCarModel_4_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function updateContinuation( self, n, old_s, s )
      % set parameter of the problem for continuation step `n` at fraction `s`
      PointMassCarModel_4_Mex( ...
        'updateContinuation', self.objectHandle, n, old_s, s ...
      );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GET SOLUTION
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function sol = solution( self, varargin )
      % return the whole solution or the column of name varargin{1}
      sol = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution2( self )
      % return the whole solution
      sol = PointMassCarModel_4_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution3( self )
      % return the whole solution
      sol = PointMassCarModel_4_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      % combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS
      sol = PointMassCarModel_4_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      % unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS
      [X, Lambda, Pars, Omega] = PointMassCarModel_4_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = s( self )
      % return the solution for the state: s
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 's' );
    end
    function res = n( self )
      % return the solution for the state: n
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'n' );
    end
    function res = alpha( self )
      % return the solution for the state: alpha
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'alpha' );
    end
    function res = V( self )
      % return the solution for the state: V
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'V' );
    end
    function res = Omega( self )
      % return the solution for the state: Omega
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'Omega' );
    end
    function res = fx( self )
      % return the solution for the state: fx
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'fx' );
    end
    function res = log_inv_Vseg( self )
      % return the solution for the state: log_inv_Vseg
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'log_inv_Vseg' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % MULTIPLIER
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = lambda1( self )
      % return the solution for the multiplier: lambda1
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      % return the solution for the multiplier: lambda2
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      % return the solution for the multiplier: lambda3
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      % return the solution for the multiplier: lambda4
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      % return the solution for the multiplier: lambda5
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      % return the solution for the multiplier: lambda6
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
    end
    function res = lambda7( self )
      % return the solution for the multiplier: lambda7
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'lambda7__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = v__fx( self )
      % return the solution for the control: v__fx
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'v__fx' );
    end
    function res = v__Omega( self )
      % return the solution for the control: v__Omega
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'v__Omega' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_v__fxControl( self )
      % return the solution for the post processing variable: v__fxControl
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'v__fxControl' );
    end
    function res = post_processing_v__OmegaControl( self )
      % return the solution for the post processing variable: v__OmegaControl
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'v__OmegaControl' );
    end
    function res = post_processing_AdherenceEllipse( self )
      % return the solution for the post processing variable: AdherenceEllipse
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'AdherenceEllipse' );
    end
    function res = post_processing_RoadLeftBorder( self )
      % return the solution for the post processing variable: RoadLeftBorder
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'RoadLeftBorder' );
    end
    function res = post_processing_RoadRightBorder( self )
      % return the solution for the post processing variable: RoadRightBorder
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'RoadRightBorder' );
    end
    function res = post_processing_PowerLimit( self )
      % return the solution for the post processing variable: PowerLimit
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'PowerLimit' );
    end
    function res = post_processing_Kappa( self )
      % return the solution for the post processing variable: Kappa
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'Kappa' );
    end
    function res = post_processing_leftWidth( self )
      % return the solution for the post processing variable: leftWidth
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'leftWidth' );
    end
    function res = post_processing_rightWidth( self )
      % return the solution for the post processing variable: rightWidth
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'rightWidth' );
    end
    function res = post_processing_xLane( self )
      % return the solution for the post processing variable: xLane
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'xLane' );
    end
    function res = post_processing_yLane( self )
      % return the solution for the post processing variable: yLane
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'yLane' );
    end
    function res = post_processing_theta( self )
      % return the solution for the post processing variable: theta
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'theta' );
    end
    function res = post_processing_xV( self )
      % return the solution for the post processing variable: xV
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'xV' );
    end
    function res = post_processing_yV( self )
      % return the solution for the post processing variable: yV
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'yV' );
    end
    function res = post_processing_xL( self )
      % return the solution for the post processing variable: xL
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'xL' );
    end
    function res = post_processing_yL( self )
      % return the solution for the post processing variable: yL
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'yL' );
    end
    function res = post_processing_xR( self )
      % return the solution for the post processing variable: xR
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'xR' );
    end
    function res = post_processing_yR( self )
      % return the solution for the post processing variable: yR
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'yR' );
    end
    function res = post_processing_fy( self )
      % return the solution for the post processing variable: fy
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'fy' );
    end
    function res = post_processing_mu_x( self )
      % return the solution for the post processing variable: mu_x
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'mu_x' );
    end
    function res = post_processing_mu_y( self )
      % return the solution for the post processing variable: mu_y
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'mu_y' );
    end
    function res = post_processing_Vseg( self )
      % return the solution for the post processing variable: Vseg
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'Vseg' );
    end
    function res = post_processing_Tseg( self )
      % return the solution for the post processing variable: Tseg
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'Tseg' );
    end
    function res = post_processing_zeta_dot_eq( self )
      % return the solution for the post processing variable: zeta_dot_eq
      res = PointMassCarModel_4_Mex( 'get_solution', self.objectHandle, 'zeta_dot_eq' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function F = eval_F( self, x )
      % return the nonlinear system of the indirect methods
      F = PointMassCarModel_4_Mex( 'eval_F', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF( self, x )
      % return the jacobian of the nonlinear system of the indirect methods
      JF = PointMassCarModel_4_Mex( 'eval_JF', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      % return the pattern of the jacobian of the nonlinear system of the indirect methods
      JF = PointMassCarModel_4_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function x = get_raw_solution( self )
      % return the solution in a vector as stored in PINS
      x = PointMassCarModel_4_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, x )
      % return set the solution in a vector as stored in PINS
      PointMassCarModel_4_Mex( 'set_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, x )
      % check the solution in a vector as stored in PINS
      ok = PointMassCarModel_4_Mex( 'check_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, x, epsi )
      % check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance
      PointMassCarModel_4_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,c] = eval_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [a,c] = PointMassCarModel_4_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [Ja,Jc] = eval_DacDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [Ja,Jc] = PointMassCarModel_4_Mex( 'DacDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [h,c] = PointMassCarModel_4_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlop( self, iseg_L, q_L, x_L, lambda_L, ...
                                            iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [Jh,Jc] = PointMassCarModel_4_Mex( 'DhcDxlop', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTINUOUS PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function u = eval_u( self, varargin )
      % compute the control give states and multiplyer
      % res = self.eval_u( iseg, q, x, lambda, pars )
      % the call
      % res = self.eval_u( iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars )
      % is the same as
      % res = self.eval_u( iseg_L, (q_L+q_R)./2, (x_L+x_R)./2, (lambda_L+lambda_R)./2, pars )
      u = PointMassCarModel_4_Mex( 'u', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function u = eval_DuDxlp( self, varargin )
      % compute the control give states and multiplyer
      % res = self.eval_DuDxlp( iseg, q, x, lambda, pars )
      % the call
      % res = self.eval_DuDxlp( iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars )
      % is the same as
      % res = self.eval_DuDxlp( iseg_L, (q_L+q_R)./2, (x_L+x_R)./2, (lambda_L+lambda_R)./2, pars )
      %
      u = PointMassCarModel_4_Mex( 'DuDxlp', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      % compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      rhs = PointMassCarModel_4_Mex(...
        'rhs_ode', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`
      J = PointMassCarModel_4_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = PointMassCarModel_4_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      A = PointMassCarModel_4_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      % compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      eta = PointMassCarModel_4_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      % compute `nu(q,x,V,pars) = A(q,x,pars) V`
      nu = PointMassCarModel_4_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = PointMassCarModel_4_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = PointMassCarModel_4_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      Hx = PointMassCarModel_4_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hu( self, iseg, q, x, lambda, V, u, pars )
      Hx = PointMassCarModel_4_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = PointMassCarModel_4_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = PointMassCarModel_4_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = PointMassCarModel_4_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDx( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = PointMassCarModel_4_Mex( ...
        'DboundaryConditionsDx', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = PointMassCarModel_4_Mex( ...
        'DboundaryConditionsDp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = PointMassCarModel_4_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = PointMassCarModel_4_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = PointMassCarModel_4_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = PointMassCarModel_4_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                       iseg_R, q_R, x_R, lambda_R, pars )
      J = PointMassCarModel_4_Mex( ...
        'DjumpDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, lambda, u, pars )
      J = PointMassCarModel_4_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, lambda, u, pars )
      J = PointMassCarModel_4_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = PointMassCarModel_4_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               u, pars )
      target = PointMassCarModel_4_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = PointMassCarModel_4_Mex( 'q', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = PointMassCarModel_4_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = PointMassCarModel_4_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = zeta__dot( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_1( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_1', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_2( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_2', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_3( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_3', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_4( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_4', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_1_1( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_1_1', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_1_2( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_1_2', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_1_3( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_1_3', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_1_4( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_1_4', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_2_2( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_2_2', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_2_3( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_2_3', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_2_4( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_2_4', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_3_3( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_3_3', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_3_4( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_3_4', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    function res = zeta__dot_D_4_4( self, V__XO, alpha__XO, n__XO, Kappa__XO )
      res = PointMassCarModel_4_Mex('zeta__dot_D_4_4', self.objectHandle, V__XO, alpha__XO, n__XO, Kappa__XO );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.s(), ...
        self.zeta(), self.n(), ...
        self.zeta(), self.alpha(), ...
        self.zeta(), self.V(), ...
        self.zeta(), self.Omega(), ...
        self.zeta(), self.fx(), ...
        self.zeta(), self.log_inv_Vseg(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 's', 'n', '\alpha', 'V', '\Omega', 'fx', 'log\_inv\_Vseg' );
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
        self.zeta(), self.v__fx(), ...
        self.zeta(), self.v__Omega(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'v\_fx', 'v\_\Omega' );
    end
  end
end

% EOF: PointMassCarModel_4.m
