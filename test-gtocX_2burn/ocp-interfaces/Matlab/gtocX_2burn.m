%-----------------------------------------------------------------------%
%  file: gtocX_2burn.m                                                  %
%                                                                       %
%  version: 1.0   date 9/3/2021                                         %
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


classdef gtocX_2burn < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = gtocX_2burn( name )
      %% Allocate the C++ class instance
      self.objectHandle = gtocX_2burn_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      gtocX_2burn_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      gtocX_2burn_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      % read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      data = gtocX_2burn_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      gtocX_2burn_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = gtocX_2burn_Mex( 'names', self.objectHandle );
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
      res = gtocX_2burn_Mex( 'dims', self.objectHandle );
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
      res = gtocX_2burn_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO LEVEL
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      % set information level
      gtocX_2burn_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NUM THREAD
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function N_thread( self, nt )
      % set information level
      gtocX_2burn_Mex( 'N_thread', self.objectHandle, nt );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % REMESH
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function remesh( self, new_mesh )
      % use structure to initialize mesh
      gtocX_2burn_Mex( 'remesh', self.objectHandle, new_mesh );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GUESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_guess( self, varargin )
      % with no argument use predefined guess, otherwise
      % use structure to initialize guess
      gtocX_2burn_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      % return a structure with the stored guess
      guess = gtocX_2burn_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      % return a structure with the solution formatted as a guess
      guess = gtocX_2burn_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = gtocX_2burn_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function updateContinuation( self, n, old_s, s )
      % set parameter of the problem for continuation step `n` at fraction `s`
      gtocX_2burn_Mex( ...
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
      sol = gtocX_2burn_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution2( self )
      % return the whole solution
      sol = gtocX_2burn_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution3( self )
      % return the whole solution
      sol = gtocX_2burn_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      % combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS
      sol = gtocX_2burn_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      % unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS
      [X, Lambda, Pars, Omega] = gtocX_2burn_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = p( self )
      % return the solution for the state: p
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'p' );
    end
    function res = f( self )
      % return the solution for the state: f
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'f' );
    end
    function res = g( self )
      % return the solution for the state: g
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'g' );
    end
    function res = h( self )
      % return the solution for the state: h
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'h' );
    end
    function res = k( self )
      % return the solution for the state: k
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'k' );
    end
    function res = L( self )
      % return the solution for the state: L
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'L' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % MULTIPLIER
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = lambda1( self )
      % return the solution for the multiplier: lambda1
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      % return the solution for the multiplier: lambda2
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end
    function res = lambda3( self )
      % return the solution for the multiplier: lambda3
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda3__xo' );
    end
    function res = lambda4( self )
      % return the solution for the multiplier: lambda4
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda4__xo' );
    end
    function res = lambda5( self )
      % return the solution for the multiplier: lambda5
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda5__xo' );
    end
    function res = lambda6( self )
      % return the solution for the multiplier: lambda6
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'lambda6__xo' );
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
      % return the solution for the post processing variable: time
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'time' );
    end
    function res = post_processing_ray( self )
      % return the solution for the post processing variable: ray
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'ray' );
    end
    function res = post_processing_X( self )
      % return the solution for the post processing variable: X
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'X' );
    end
    function res = post_processing_Y( self )
      % return the solution for the post processing variable: Y
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Y' );
    end
    function res = post_processing_Z( self )
      % return the solution for the post processing variable: Z
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Z' );
    end
    function res = post_processing_VX( self )
      % return the solution for the post processing variable: VX
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VX' );
    end
    function res = post_processing_VY( self )
      % return the solution for the post processing variable: VY
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VY' );
    end
    function res = post_processing_VZ( self )
      % return the solution for the post processing variable: VZ
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VZ' );
    end
    function res = post_processing_X_begin( self )
      % return the solution for the post processing variable: X_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'X_begin' );
    end
    function res = post_processing_Y_begin( self )
      % return the solution for the post processing variable: Y_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Y_begin' );
    end
    function res = post_processing_Z_begin( self )
      % return the solution for the post processing variable: Z_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Z_begin' );
    end
    function res = post_processing_VX_begin( self )
      % return the solution for the post processing variable: VX_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VX_begin' );
    end
    function res = post_processing_VY_begin( self )
      % return the solution for the post processing variable: VY_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VY_begin' );
    end
    function res = post_processing_VZ_begin( self )
      % return the solution for the post processing variable: VZ_begin
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VZ_begin' );
    end
    function res = post_processing_X_end( self )
      % return the solution for the post processing variable: X_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'X_end' );
    end
    function res = post_processing_Y_end( self )
      % return the solution for the post processing variable: Y_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Y_end' );
    end
    function res = post_processing_Z_end( self )
      % return the solution for the post processing variable: Z_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'Z_end' );
    end
    function res = post_processing_VX_end( self )
      % return the solution for the post processing variable: VX_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VX_end' );
    end
    function res = post_processing_VY_end( self )
      % return the solution for the post processing variable: VY_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VY_end' );
    end
    function res = post_processing_VZ_end( self )
      % return the solution for the post processing variable: VZ_end
      res = gtocX_2burn_Mex( 'get_solution', self.objectHandle, 'VZ_end' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function F = eval_F( self, x )
      % return the nonlinear system of the indirect methods
      F = gtocX_2burn_Mex( 'eval_F', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF( self, x )
      % return the jacobian of the nonlinear system of the indirect methods
      JF = gtocX_2burn_Mex( 'eval_JF', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      % return the pattern of the jacobian of the nonlinear system of the indirect methods
      JF = gtocX_2burn_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function x = get_raw_solution( self )
      % return the solution in a vector as stored in PINS
      x = gtocX_2burn_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, x )
      % return set the solution in a vector as stored in PINS
      gtocX_2burn_Mex( 'set_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, x )
      % check the solution in a vector as stored in PINS
      ok = gtocX_2burn_Mex( 'check_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, x, epsi )
      % check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance
      gtocX_2burn_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,c] = eval_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [a,c] = gtocX_2burn_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [Ja,Jc] = eval_DacDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [Ja,Jc] = gtocX_2burn_Mex( 'DacDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [h,c] = gtocX_2burn_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlop( self, iseg_L, q_L, x_L, lambda_L, ...
                                            iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [Jh,Jc] = gtocX_2burn_Mex( 'DhcDxlop', self.objectHandle, ...
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
      u = gtocX_2burn_Mex( 'u', self.objectHandle, varargin{:} );
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
      u = gtocX_2burn_Mex( 'DuDxlp', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      % compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      rhs = gtocX_2burn_Mex(...
        'rhs_ode', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`
      J = gtocX_2burn_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = gtocX_2burn_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      A = gtocX_2burn_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      % compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      eta = gtocX_2burn_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      % compute `nu(q,x,V,pars) = A(q,x,pars) V`
      nu = gtocX_2burn_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = gtocX_2burn_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = gtocX_2burn_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      Hx = gtocX_2burn_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hu( self, iseg, q, x, lambda, V, u, pars )
      Hx = gtocX_2burn_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = gtocX_2burn_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = gtocX_2burn_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = gtocX_2burn_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDx( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = gtocX_2burn_Mex( ...
        'DboundaryConditionsDx', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = gtocX_2burn_Mex( ...
        'DboundaryConditionsDp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = gtocX_2burn_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = gtocX_2burn_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = gtocX_2burn_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = gtocX_2burn_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                       iseg_R, q_R, x_R, lambda_R, pars )
      J = gtocX_2burn_Mex( ...
        'DjumpDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, lambda, u, pars )
      J = gtocX_2burn_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, lambda, u, pars )
      J = gtocX_2burn_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = gtocX_2burn_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               u, pars )
      target = gtocX_2burn_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = gtocX_2burn_Mex( 'q', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = gtocX_2burn_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = gtocX_2burn_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    %  _   _               ___             _   _
    % | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
    % | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
    % ---------------------------------------------------------------------
    function res = cont( self, xo__s, xo__eps0, xo__eps1 )
      res = gtocX_2burn_Mex('cont', self.objectHandle, xo__s, xo__eps0, xo__eps1 );
    end
    % ---------------------------------------------------------------------
    function res = xPosition( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xPosition_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xPosition_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yPosition_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yPosition_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zPosition_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zPosition_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = xVelocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('xVelocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = yVelocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('yVelocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_1( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_1_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_1_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_2( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_2_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_2_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3_3( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_3_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_3_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_4_4( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_4_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_4_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_4_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_4_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_4_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_5_5( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_5_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_5_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_5_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_5_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_6_6( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_6_6', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_6_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_6_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = zVelocity_D_7_7( self, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde )
      res = gtocX_2burn_Mex('zVelocity_D_7_7', self.objectHandle, xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_1', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_1( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_1_1', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_1_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_1_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_1_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2_2( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_2_2', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_2_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_2_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = norm_reg_D_3_3( self, xo__x, xo__y, xo__z )
      res = gtocX_2burn_Mex('norm_reg_D_3_3', self.objectHandle, xo__x, xo__y, xo__z );
    end
    % ---------------------------------------------------------------------
    function res = ray( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_1( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_1_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_2( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_2_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3_3( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_3_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = ray_D_4_4( self, xo__p, xo__f, xo__g, xo__L )
      res = gtocX_2burn_Mex('ray_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L );
    end
    % ---------------------------------------------------------------------
    function res = vel( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_1( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1_1', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_1_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_1_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_2( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_2_2', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_2_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_2_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_2_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_2_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_3( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_3_3', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_3_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_3_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_3_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4_4( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_4_4', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_4_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_4_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vel_D_5_5( self, xo__p, xo__f, xo__g, xo__L, xo__muS )
      res = gtocX_2burn_Mex('vel_D_5_5', self.objectHandle, xo__p, xo__f, xo__g, xo__L, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = vc( self, xo__r )
      res = gtocX_2burn_Mex('vc', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = vc_D( self, xo__r )
      res = gtocX_2burn_Mex('vc_D', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = vc_DD( self, xo__r )
      res = gtocX_2burn_Mex('vc_DD', self.objectHandle, xo__r );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r_D_1', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_2( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r_D_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1_1( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r_D_1_1', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_1_2( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r_D_1_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = acceleration_r_D_2_2( self, xo__r, xo__muS )
      res = gtocX_2burn_Mex('acceleration_r_D_2_2', self.objectHandle, xo__r, xo__muS );
    end
    % ---------------------------------------------------------------------
    function res = X_begin( self, xo__t )
      res = gtocX_2burn_Mex('X_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('X_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('X_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin( self, xo__t )
      res = gtocX_2burn_Mex('Y_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('Y_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('Y_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin( self, xo__t )
      res = gtocX_2burn_Mex('Z_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('Z_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('Z_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin( self, xo__t )
      res = gtocX_2burn_Mex('VX_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('VX_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('VX_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin( self, xo__t )
      res = gtocX_2burn_Mex('VY_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('VY_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('VY_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin( self, xo__t )
      res = gtocX_2burn_Mex('VZ_begin', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin_D( self, xo__t )
      res = gtocX_2burn_Mex('VZ_begin_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_begin_DD( self, xo__t )
      res = gtocX_2burn_Mex('VZ_begin_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end( self, xo__t )
      res = gtocX_2burn_Mex('X_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end_D( self, xo__t )
      res = gtocX_2burn_Mex('X_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = X_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('X_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end( self, xo__t )
      res = gtocX_2burn_Mex('Y_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end_D( self, xo__t )
      res = gtocX_2burn_Mex('Y_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Y_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('Y_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end( self, xo__t )
      res = gtocX_2burn_Mex('Z_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end_D( self, xo__t )
      res = gtocX_2burn_Mex('Z_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = Z_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('Z_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end( self, xo__t )
      res = gtocX_2burn_Mex('VX_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end_D( self, xo__t )
      res = gtocX_2burn_Mex('VX_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VX_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('VX_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end( self, xo__t )
      res = gtocX_2burn_Mex('VY_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end_D( self, xo__t )
      res = gtocX_2burn_Mex('VY_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VY_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('VY_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end( self, xo__t )
      res = gtocX_2burn_Mex('VZ_end', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end_D( self, xo__t )
      res = gtocX_2burn_Mex('VZ_end_D', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = VZ_end_DD( self, xo__t )
      res = gtocX_2burn_Mex('VZ_end_DD', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = p_guess( self, xo__t )
      res = gtocX_2burn_Mex('p_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = f_guess( self, xo__t )
      res = gtocX_2burn_Mex('f_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = g_guess( self, xo__t )
      res = gtocX_2burn_Mex('g_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = h_guess( self, xo__t )
      res = gtocX_2burn_Mex('h_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = k_guess( self, xo__t )
      res = gtocX_2burn_Mex('k_guess', self.objectHandle, xo__t );
    end
    % ---------------------------------------------------------------------
    function res = L_guess( self, xo__t, xo__t0 )
      res = gtocX_2burn_Mex('L_guess', self.objectHandle, xo__t, xo__t0 );
    end
    % ---------------------------------------------------------------------
    function res = guess_setup( self )
      res = gtocX_2burn_Mex('guess_setup', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.p(), ...
        self.zeta(), self.f(), ...
        self.zeta(), self.g(), ...
        self.zeta(), self.h(), ...
        self.zeta(), self.k(), ...
        self.zeta(), self.L(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'p', 'f', 'g', 'h', 'k', 'L' );
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
      % no control to plot
    end
  end
end

% EOF: gtocX_2burn.m
