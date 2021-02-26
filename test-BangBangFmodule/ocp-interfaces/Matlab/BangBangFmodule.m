%-----------------------------------------------------------------------%
%  file: BangBangFmodule.m                                              %
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


classdef BangBangFmodule < handle
  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods
    % ---------------------------------------------------------------------
    function self = BangBangFmodule( name )
      %% Allocate the C++ class instance
      self.objectHandle = BangBangFmodule_Mex( 'new', name );
    end
    % ---------------------------------------------------------------------
    function delete( self )
      %% Destroy the C++ class instance
      BangBangFmodule_Mex( 'delete', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function help( self )
      %% print help for the class usage
      BangBangFmodule_Mex('help');
    end

    % ---------------------------------------------------------------------
    % INITIALIZATION
    % ---------------------------------------------------------------------
    function data = read( self, fname )
      % read a file with problem description in Ruby o LUA
      % and return a MATLAB structure with the readed data
      data = BangBangFmodule_Mex( 'read', self.objectHandle, fname );
    end
    % ---------------------------------------------------------------------
    function setup( self, fname_or_struct )
      % Initialize an OCP problem reading data from a file or a MATLAT stucture
      BangBangFmodule_Mex( 'setup', self.objectHandle, fname_or_struct );
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
      n = BangBangFmodule_Mex( 'names', self.objectHandle );
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
      res = BangBangFmodule_Mex( 'dims', self.objectHandle );
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
      res = BangBangFmodule_Mex( 'get_ocp_data', self.objectHandle );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % INFO LEVEL
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function infoLevel( self, infoLvl )
      % set information level
      BangBangFmodule_Mex( 'infoLevel', self.objectHandle, infoLvl );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NUM THREAD
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function N_thread( self, nt )
      % set information level
      BangBangFmodule_Mex( 'N_thread', self.objectHandle, nt );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % GUESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function set_guess( self, varargin )
      % with no argument use predefined guess, otherwise
      % use structure to initialize guess
      BangBangFmodule_Mex( 'set_guess', self.objectHandle, varargin{:} );
    end
    function guess = get_guess( self )
      % return a structure with the stored guess
      guess = BangBangFmodule_Mex( 'get_guess', self.objectHandle );
    end
    function guess = get_solution_as_guess( self )
      % return a structure with the solution formatted as a guess
      guess = BangBangFmodule_Mex( 'get_solution_as_guess', self.objectHandle );
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
      ok = BangBangFmodule_Mex( 'solve', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function updateContinuation( self, n, old_s, s )
      % set parameter of the problem for continuation step `n` at fraction `s`
      BangBangFmodule_Mex( ...
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
      sol = BangBangFmodule_Mex( 'get_solution', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function sol = solution2( self )
      % return the whole solution
      sol = BangBangFmodule_Mex( 'get_solution2', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = solution3( self )
      % return the whole solution
      sol = BangBangFmodule_Mex( 'get_solution3', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function sol = pack( self, X, Lambda, Pars, Omega )
      % combine the solution in the matrices `X`, `Lambda`, `Pars` and `Omega`
      % in a single vector as stored in the solver PINS
      sol = BangBangFmodule_Mex( 'pack', self.objectHandle, X, Lambda, Pars, Omega );
    end
    % ---------------------------------------------------------------------
    function [X, Lambda, Pars, Omega] = unpack( self, sol )
      % unpack a vector to the matrices `X`, `Lambda`, `Pars` and `Omega`
      % the vector must contains the data as stored in the solver PINS
      [X, Lambda, Pars, Omega] = BangBangFmodule_Mex( 'unpack', self.objectHandle, sol );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % ZETA
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = zeta( self )
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'zeta' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % STATES
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = x( self )
      % return the solution for the state: x
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'x' );
    end
    function res = v( self )
      % return the solution for the state: v
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'v' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % MULTIPLIER
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = lambda1( self )
      % return the solution for the multiplier: lambda1
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'lambda1__xo' );
    end
    function res = lambda2( self )
      % return the solution for the multiplier: lambda2
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'lambda2__xo' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % CONTROLS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = Fp( self )
      % return the solution for the control: Fp
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'Fp' );
    end
    function res = Fm( self )
      % return the solution for the control: Fm
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'Fm' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % POSTPROCESSING
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function res = post_processing_ForceP( self )
      % return the solution for the post processing variable: ForceP
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'ForceP' );
    end
    function res = post_processing_ForceM( self )
      % return the solution for the post processing variable: ForceM
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'ForceM' );
    end
    function res = post_processing_F( self )
      % return the solution for the post processing variable: F
      res = BangBangFmodule_Mex( 'get_solution', self.objectHandle, 'F' );
    end

    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % NONLINEAR SYSTEM
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function F = eval_F( self, x )
      % return the nonlinear system of the indirect methods
      F = BangBangFmodule_Mex( 'eval_F', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF( self, x )
      % return the jacobian of the nonlinear system of the indirect methods
      JF = BangBangFmodule_Mex( 'eval_JF', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function JF = eval_JF_pattern( self )
      % return the pattern of the jacobian of the nonlinear system of the indirect methods
      JF = BangBangFmodule_Mex( 'eval_JF_pattern', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function x = get_raw_solution( self )
      % return the solution in a vector as stored in PINS
      x = BangBangFmodule_Mex( 'get_raw_solution', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function set_raw_solution( self, x )
      % return set the solution in a vector as stored in PINS
      BangBangFmodule_Mex( 'set_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function ok = check_raw_solution( self, x )
      % check the solution in a vector as stored in PINS
      ok = BangBangFmodule_Mex( 'check_raw_solution', self.objectHandle, x );
    end
    % ---------------------------------------------------------------------
    function check_jacobian( self, x, epsi )
      % check the analytic jacobian comparing with finite difference one.
      % `epsi` is the admitted tolerance
      BangBangFmodule_Mex( 'check_jacobian', self.objectHandle, x, epsi );
    end
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    % DISCRETIZED PROBLEM ACCESS
    % ---------------------------------------------------------------------
    % ---------------------------------------------------------------------
    function [a,c] = eval_ac( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [a,c] = BangBangFmodule_Mex( 'ac', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [Ja,Jc] = eval_DacDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, pars, U )
      % compute the block of the nonlinear system given left and right stated
      [Ja,Jc] = BangBangFmodule_Mex( 'DacDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, U ...
      );
    end
    % ---------------------------------------------------------------------
    function [h,c] = eval_hc( self, iseg_L, q_L, x_L, lambda_L, ...
                                    iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [h,c] = BangBangFmodule_Mex( 'hc', self.objectHandle, ...
        iseg_L,  q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function [Jh,Jc] = eval_DhcDxlop( self, iseg_L, q_L, x_L, lambda_L, ...
                                            iseg_R, q_R, x_R, lambda_R, pars )
      % compute the block of the BC of the nonlinear system given left and right stated
      [Jh,Jc] = BangBangFmodule_Mex( 'DhcDxlop', self.objectHandle, ...
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
      u = BangBangFmodule_Mex( 'u', self.objectHandle, varargin{:} );
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
      u = BangBangFmodule_Mex( 'DuDxlp', self.objectHandle, varargin{:} );
    end
    % ---------------------------------------------------------------------
    function rhs = eval_rhs_ode( self, iseg, q, x, u, pars )
      % compute rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      rhs = BangBangFmodule_Mex(...
        'rhs_ode', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDx( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'Drhs_odeDx', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDu( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `u`
      J = BangBangFmodule_Mex(...
        'Drhs_odeDu', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_Drhs_odeDp( self, iseg, q, x, u, pars )
      % compute Jacobian of rhs of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      J = BangBangFmodule_Mex(...
        'Drhs_odeDp', self.objectHandle, iseg, q, x, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function A = eval_A( self, iseg, q, x, pars )
      % compute `A(q,x)` of the ODE `A(q,x,pars) x' = rhs( q, x, u, pars )`
      % respect to `pars`
      A = BangBangFmodule_Mex( 'A', self.objectHandle, iseg, q, x, pars );
    end
    % ---------------------------------------------------------------------
    function eta = eval_eta( self, iseg, q, x, lambda, pars )
      % compute `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      eta = BangBangFmodule_Mex(...
        'eta', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDx( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DetaDx', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DetaDp( self, iseg, q, x, lambda, pars )
      % compute the jacobian of `eta(q,x,lambda,pars) = A(q,x,pars)^T lambda`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DetaDp', self.objectHandle, iseg, q, x, lambda, pars...
      );
    end
    % ---------------------------------------------------------------------
    function nu = eval_nu( self, iseg, q, x, V, pars )
      % compute `nu(q,x,V,pars) = A(q,x,pars) V`
      nu = BangBangFmodule_Mex( 'nu', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDx( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = BangBangFmodule_Mex( 'DnuDx', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function J = eval_DnuDp( self, iseg, q, x, V, pars )
      % compute the jacobian of `nu(q,x,V,pars) = A(q,x,pars) V`
      % respect to `x`
      J = BangBangFmodule_Mex( 'DnuDp', self.objectHandle, iseg, q, x, V, pars );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hx( self, iseg, q, x, lambda, V, u, pars )
      Hx = BangBangFmodule_Mex(...
        'Hx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,pars)`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DHxDx', self.objectHandle, iseg, q, x, lambda, V, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHxDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hx(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DHxDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hx = eval_Hu( self, iseg, q, x, lambda, V, u, pars )
      Hx = BangBangFmodule_Mex(...
        'Hu', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDx( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DHuDx', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHuDp( self, iseg, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hu(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DHuDp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function Hp = eval_Hp( self, iseg, q, x, lambda, V, u, pars )
      Hp = BangBangFmodule_Mex(...
        'Hp', self.objectHandle, iseg, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DHpDp( self, q, x, lambda, V, u, pars )
      % compute the jacobian of `Hp(q,x,lambda,V,u,pars)`
      % respect to `x`
      J = BangBangFmodule_Mex(...
        'DHpDp', self.objectHandle, q, x, lambda, V, u, pars...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_bc( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      bc = BangBangFmodule_Mex( ...
        'boundaryConditions', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDx( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = BangBangFmodule_Mex( ...
        'DboundaryConditionsDx', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DbcDp( self, iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars )
      J = BangBangFmodule_Mex( ...
        'DboundaryConditionsDp', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_adjoiontBC( self, iseg_L, q_L, x_L, lambda_L, ...
                                         iseg_R, q_R, x_R, lambda_R, ...
                                         pars, Omega )
      bc = BangBangFmodule_Mex( ...
        'adjoiontBC', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDx( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = BangBangFmodule_Mex( ...
        'DadjoiontBCDx', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DadjoiontBCDp( self, iseg_L, q_L, x_L, lambda_L, ...
                                           iseg_R, q_R, x_R, lambda_R, ...
                                           pars, Omega )
      J = BangBangFmodule_Mex( ...
        'DadjoiontBCDp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars, Omega ...
      );
    end
    % ---------------------------------------------------------------------
    function bc = eval_jump( self, iseg_L, q_L, x_L, lambda_L, ...
                                   iseg_R, q_R, x_R, lambda_R, pars )
      bc = BangBangFmodule_Mex( ...
        'jump', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_DjumpDxlp( self, iseg_L, q_L, x_L, lambda_L, ...
                                       iseg_R, q_R, x_R, lambda_R, pars )
      J = BangBangFmodule_Mex( ...
        'DjumpDxlp', self.objectHandle, ...
        iseg_L, q_L, x_L, lambda_L, iseg_R, q_R, x_R, lambda_R, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_penalties( self, iseg, q, x, lambda, u, pars )
      J = BangBangFmodule_Mex( ...
        'penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function J = eval_control_penalties( self, iseg, q, x, lambda, u, pars )
      J = BangBangFmodule_Mex( ...
        'control_penalties', self.objectHandle, iseg, q, x, lambda, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_lagrange_target( self, iseg, q, x, u, pars )
      target = BangBangFmodule_Mex( ...
        'lagrange_target', self.objectHandle, iseg, q, x, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_mayer_target( self, iseg_L, q_L, x_L, ...
                                               iseg_R, q_R, x_R, ...
                                               u, pars )
      target = BangBangFmodule_Mex( ...
        'mayer_target', self.objectHandle, ...
        iseg_L, q_L, x_L, iseg_R, q_R, x_R, u, pars ...
      );
    end
    % ---------------------------------------------------------------------
    function target = eval_q( self, i_segment, s )
      target = BangBangFmodule_Mex( 'q', self.objectHandle, i_segment, s );
    end
    % ---------------------------------------------------------------------
    function nodes = get_nodes( self )
      nodes = BangBangFmodule_Mex( 'nodes', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    function node_to_segment = get_node_to_segment( self )
      node_to_segment = BangBangFmodule_Mex( 'node_to_segment', self.objectHandle );
    end
    % ---------------------------------------------------------------------
    % PLOT SOLUTION
    % ---------------------------------------------------------------------
    function plot_states( self )
      plot(...
        self.zeta(), self.x(), ...
        self.zeta(), self.v(), ...
        'Linewidth', 2 ...
      );
      title('states');
      legend( 'x', 'v' );
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
        self.zeta(), self.Fp(), ...
        self.zeta(), self.Fm(), ...
        'Linewidth', 2 ...
      );
      title('controls');
      legend( 'Fp', 'Fm' );
    end
  end
end

% EOF: BangBangFmodule.m
