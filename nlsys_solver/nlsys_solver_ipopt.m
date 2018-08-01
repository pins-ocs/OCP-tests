classdef nlsys_solver_ipopt < handle
  %% MATLAB class wrapper for the underlying C++ class
  properties (SetAccess = private, Hidden = true)
    OBJ;
    check_gradient;
    dims;
    solution;
  end

  methods (Hidden = true)
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function [o,g] = obj( self, theta )
      o = 1;
      g = zeros(self.dims.neq,1);
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function [ceq,jaceq] = nlsys( self, x )
      ceq   = self.OBJ.evalf_F( x );
      jaceq = self.OBJ.evalf_JF( x ); ;
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function [c,ceq,jac,jaceq] = con( self, theta )
      c     = zeros(0,0) ;
      ceq   = self.OBJ.evalf_F( x );
      jac   = sparse(0,0);
      jaceq = self.OBJ.evalf_JF( x ); ;
    end
  end

  methods
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function self = nlsys_solver_ipopt( OBJname )
      self.OBJ            = OBJname;
      self.check_gradient = false ;
      self.dims           = OBJname.dims();
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

      options.ub = Inf*ones(self.dims.neq,1);
      options.lb = -Inf*ones(self.dims.neq,1) ;

      % The constraint functions are bounded to zero
      options.cl = zeros(self.dims.neq,1) ; %  constraints
      options.cu = zeros(self.dims.neq,1) ;

      % Set the IPOPT options.
      options.ipopt.jac_d_constant      = 'no' ;
      options.ipopt.hessian_constant    = 'no' ;
      options.ipopt.mu_strategy         = 'adaptive';
      options.ipopt.max_iter            = 400 ;
      options.ipopt.tol                 = 1e-10 ;
      options.ipopt.derivative_test_tol = 1e-5 ;
      options.ipopt.print_level         = 5;
      if self.check_gradient
        options.ipopt.derivative_test = 'first-order' ;
      else
        options.ipopt.derivative_test = 'none' ;
      end
      %options.ipopt.derivative_test_perturbation = 1e-8 ;

      % The callback functions.
      funcs.objective         = @(x) 1;
      funcs.gradient          = @(x) zeros(self.dims.neq,1);
      funcs.constraints       = @(x) self.OBJ.eval_F(x);
      funcs.jacobian          = @(x) self.OBJ.eval_JF(x);
      funcs.jacobianstructure = @()  self.OBJ.eval_JF_pattern();

      %options.ipopt.jacobian_approximation = 'finite-difference-values';
      options.ipopt.hessian_approximation  = 'limited-memory';
      %options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}
      %options.ipopt.limited_memory_update_type = 'sr1' ;
      options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}

      tic
      x_guess = self.OBJ.get_raw_solution();
      [sol, info] = ipopt(x_guess,funcs,options);
      stats.elapsed = toc ;
      info;

      self.solution = sol;
    end

    function sol = get_solution( self )
       sol = self.solution;
    end
  end
end
