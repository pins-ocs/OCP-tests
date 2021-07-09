classdef nlsys_solver_ipopt < handle
  %% MATLAB class wrapper for the underlying C++ class
  properties (SetAccess = private, Hidden = true)
    OBJ;
    check_gradient;
    dims;
    solution;
    do_minimization;
  end

  methods (Hidden = true)
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function F = evaluate_F( self, x )
      neq     = self.dims.neq;
      u_guess = self.OBJ.init_U(x,self.do_minimization);
      u       = self.OBJ.eval_U(x,u_guess);
      [F,ok]  = self.OBJ.eval_F( x, u );
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function JF = evaluate_JF( self, x )
      neq     = self.dims.neq;
      u_guess = self.OBJ.init_U(x,self.do_minimization);
      u       = self.OBJ.eval_U(x,u_guess);
      [JF,ok] = self.OBJ.eval_JF( x, u );
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function JF = evaluate_pattern( self )
      JF = self.OBJ.eval_JF_pattern();
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function res = evaluate_target( self, x )
      F = self.evaluate_F( x );
      res = 0.5*dot(F,F);
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function g = evaluate_gradient( self, x )
      JF = self.evaluate_JF( x );
      F  = self.evaluate_F( x );
      g  = JF.' * F;
    end
  end

  methods
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function self = nlsys_solver_ipopt( OBJname )
      self.OBJ             = OBJname;
      self.check_gradient  = false;
      self.dims            = OBJname.dims();
      self.do_minimization = false;
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function delete( self )
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function ipopt_check( self, yesno )
      self.check_gradient = yesno ;
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function sol = solve( self )
      options = {} ;

      neq = self.dims.neq;

      options.ub =  Inf*ones(neq,1);
      options.lb = -Inf*ones(neq,1) ;

      % The constraint functions are bounded to zero
      options.cl = []; %  constraints
      options.cu = [];

      % Set the IPOPT options.
      options.ipopt.jac_d_constant      = 'no';
      options.ipopt.hessian_constant    = 'no';
      options.ipopt.mu_strategy         = 'adaptive';
      options.ipopt.max_iter            = 400;
      options.ipopt.tol                 = 1e-10;
      options.ipopt.constr_viol_tol     = 1e-8;
      options.ipopt.derivative_test_tol = 1e-5;
      options.ipopt.print_level         = 5;
      if self.check_gradient
        options.ipopt.derivative_test = 'first-order' ;
      else
        options.ipopt.derivative_test = 'none' ;
      end
      %options.ipopt.derivative_test_perturbation = 1e-8 ;

      % The callback functions.
      funcs.objective         = @(z) self.evaluate_target(z);
      funcs.gradient          = @(z) self.evaluate_gradient(z);
      funcs.constraints       = @(z) [];
      funcs.jacobian          = @(z) [];
      funcs.jacobianstructure = @()  [];

      %options.ipopt.jacobian_approximation    = 'finite-difference-values';
      options.ipopt.hessian_approximation      = 'limited-memory';
      options.ipopt.limited_memory_update_type = 'bfgs'; % {bfgs}, sr1 = 6; % {6}

      tic
      x_guess     = self.OBJ.get_raw_solution();
      [sol, info] = ipopt( x_guess, funcs, options );
      stats.elapsed = toc ;
      info;

      self.solution = sol(1:neq);
    end

    function sol = get_solution( self )
       sol = self.solution;
    end
  end
end
