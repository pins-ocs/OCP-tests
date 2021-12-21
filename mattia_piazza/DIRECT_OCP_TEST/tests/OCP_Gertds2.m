%--------------------------------------------------------------------------%
%                                                                          %
%  Copyright (C) 2018                                                      %
%                                                                          %
%         , __                 , __                                        %
%        /|/  \               /|/  \                                       %
%         | __/ _   ,_         | __/ _   ,_                                %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                        %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       %
%                           /|                   /|                        %
%                           \|                   \|                        %
%                                                                          %
%      Enrico Bertolazzi                                                   %
%      Dipartimento di Ingegneria Industriale                              %
%      Universita` degli Studi di Trento                                   %
%      email: enrico.bertolazzi@unitn.it                                   %
%                                                                          %
%--------------------------------------------------------------------------%

classdef OCP_Gertds2 < OCP_NLP

  properties (SetAccess = private, Hidden = true)
    x1_i
    x2_i
    x3_i
    x1_f
    x2_f
    sol
  end

  methods

    function self = OCP_Gertds2( )
      nx  = 3 ; % number of states
      nu  = 1 ; % number of controls
      np  = 0 ; % number of free parameters
      npc = 0 ; % number of path constraints
      nbc = 5 ; % number of boundary conditions
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;
    end
    
    function setup( self, nodes )
      setup@OCP_NLP( self, nodes ) ;
      self.x1_i = 0;
      self.x2_i = 1;
      self.x3_i = 0;
      self.x1_f = 0;
      self.x2_f = -1;
    end 

    function info = solve( self )
      
      N   = self.N;
      nx  = self.nx;
      nu  = self.nu;
      nbc = self.nbc;

      options.lb = -ones(1,N*nx+N-1)*Inf ;  % Lower bound on the variables.
      options.ub = [ reshape( [1/9;Inf;Inf] * ones(1,N), 1, 3*N ), ones(1,N-1)*Inf ] ;  % Upper bound on the variables.

      % The constraint functions are bounded to zero
      options.cl = zeros(1,(N-1)*nx+nbc); %  constraints
      options.cu = zeros(1,(N-1)*nx+nbc);

      % Set the IPOPT options.
      options.ipopt.jac_d_constant   = 'no';
      options.ipopt.hessian_constant = 'no';
      options.ipopt.mu_strategy      = 'adaptive';
      options.ipopt.max_iter         = 400;
      options.ipopt.tol              = 1e-10;%
      %options.ipopt.linear_solver    = 'ma57';
      options.ipopt.linear_solver    = 'mumps';
      %options.ipopt.linear_solver    = 'pardiso';

      % The callback functions.
      funcs.objective         = @(Z) self.NLP_target(Z);
      funcs.gradient          = @(Z) self.NLP_target_gradient(Z);

      funcs.constraints       = @(Z) self.NLP_constraints(Z);
      funcs.jacobian          = @(Z) self.NLP_constraints_jacobian(Z);
      funcs.jacobianstructure = @() self.NLP_constraints_jacobian_pattern();

      if true
        %options.ipopt.derivative_test = 'second-order';
        funcs.hessian           = @( Z, sigma, lambda ) self.NLP_hessian( Z, sigma, lambda ) ;
        funcs.hessianstructure  = @() self.NLP_hessian_pattern();
      else
        %options.ipopt.derivative_test            = 'first-order';
        options.ipopt.hessian_approximation      = 'limited-memory';
        options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}
      end

      % Run IPOPT.
      x0 = zeros(3*N+N-1,1) ;

      tic
      [self.sol, info] = ipopt(x0,funcs,options);
      elapsed = toc ;

    end
    
    function plot( self )
      N   = self.N ;
      x1  = self.sol(1:3:3*N) ;
      x2  = self.sol(2:3:3*N) ;
      x3  = self.sol(3:3:3*N) ;
      u   = self.sol(3*N+1:end) ;
      nodes = self.nodes ;

      subplot( 2, 1, 1 );  
      plot( nodes, x1, nodes, x2, nodes, x3, 'Linewidth', 2 ) ;
      title('x') ;

      subplot( 2, 1, 2 );
      uu = reshape( [1;1] * u.', 1, 2*(N-1) ) ; 
      nn = reshape( [ nodes(1:end-1) ; nodes(2:end)], 1, 2*(N-1) ) ;
      plot( nn, uu, 'Linewidth', 2 ) ;
      title('u') ;

    end

    %                      __              _   _
    %  _  _ ___ ___ _ _   / _|_  _ _ _  __| |_(_)___ _ _  ___
    % | || (_-</ -_) '_| |  _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \_,_/__/\___|_|   |_|  \_,_|_||_\__|\__|_\___/_||_/__/
    %

    %  _
    % | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
    % | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
    % |____\__,_\__, |_| \__,_|_||_\__, \___|
    %           |___/              |___/
    %
    function L = lagrange( ~, ~, tL, tR, XL, XR, UC, ~ )
      L = 0 ;
    end

    %
    function gradL = lagrange_gradient( self, ~, tL, tR, XL, XR, UC, ~ )
      gradL = zeros(1,2*self.nx+self.nu) ;
    end
    
    %
    function hessL = lagrange_hessian( self, ~, tL, tR, XL, XR, UC, ~ )
      dim = 2*self.nx+self.nu ;
      hessL = zeros( dim, dim ) ;
    end

    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( ~, tL, tR, XL, XR, ~ )
      M = XR(3) ;
    end
    
    %
    function gradM = mayer_gradient( ~, tL, tR, XL, XR, ~ )
      gradM = [0,0,0,0,0,1] ;
    end
    
    % [ M, gradM, hessianM ]
    function hessM = mayer_hessian( ~, tL, tR, XL, XR, ~ )
      hessM = zeros(6,6) ;
    end

    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    function C = ds( self, ~, tL, tR, XL, XR, UC, ~ )
      % ----------
      DT  = tR-tL ;
      % ----------
      C    = zeros(3,1) ;
      C(1) = (XR(1) - XL(1))/DT - (XL(2)+XR(2))/2;
      C(2) = (XR(2) - XL(2))/DT - UC(1);
      C(3) = (XR(3) - XL(3))/DT - 0.5*UC(1)^2;
    end

    %
    function JAC = ds_jacobian( self, ~, tL, tR, XL, XR, UC, ~ )
      % ----------
      DT  = tR-tL ;
      % ----------
      JAC = [ -1/DT, -0.5,      0, 1/DT, -0.5,    0,  0     ; ...
                  0, -1/DT,     0,    0, 1/DT,    0, -1     ; ...
                  0,     0, -1/DT,    0,    0, 1/DT, -UC(1) ] ;
    end

    %
    function H = ds_hessian( self, nseg, tL, tR, XL, XR, UC, P, L )
      if false
        H = self.FD_ds_hessian( nseg, tL, tR, XL, XR, UC, P, L ) ;
      else
        H      = zeros(7,7) ;
        H(7,7) = -L(3) ;
      end
    end

    %              _   _                           _             _           _   
    %  _ __   __ _| |_| |__     ___ ___  _ __  ___| |_ _ __ __ _(_)_ __  ___| |_ 
    % | '_ \ / _` | __| '_ \   / __/ _ \| '_ \/ __| __| '__/ _` | | '_ \/ __| __|
    % | |_) | (_| | |_| | | | | (_| (_) | | | \__ \ |_| | | (_| | | | | \__ \ |_ 
    % | .__/ \__,_|\__|_| |_|  \___\___/|_| |_|___/\__|_|  \__,_|_|_| |_|___/\__|
    % |_|                                                                        
    % 

    % Path constraints
    function C = pc( self, t, X, PARS )
      C = zeros(0,1) ;
    end

    function CJ = pc_jacobian( self, t, X, PARS )
      CJ = zeros(0,self.nx) ;
    end

    function CH = pc_hessian( self, t, X, PARS, L )
      CH = zeros(self.nx,self.nx) ;
    end

    %     _
    %  _ | |_  _ _ __  _ __
    % | || | || | '  \| '_ \
    %  \__/ \_,_|_|_|_| .__/
    %                 |_|
    %
    function ODE = jump( ~, tL, tR, XL, XR, ~ )
      ODE = XR - XL ;
    end

    %
    function JAC = jump_jacobian( ~, tL, tR, XL, XR, ~ )
      JAC = [ -eye(2,2), eye(2,2) ] ;
    end

    %
    function H = jump_hessian( ~, tL, tR, XL, XR, ~, L )
      H  = zeros(4,4) ;
    end

    %  ___  ___
    % | _ )/ __|
    % | _ \ (__
    % |___/\___|
    %
    function bc = bc( self, tL, tR, XL, XR, ~ )
      bc = [ XL(1) - self.x1_i ; ...
             XL(2) - self.x2_i ; ...
             XL(3) - self.x3_i ; ...
             XR(1) - self.x1_f ; ...
             XR(2) - self.x2_f ] ;
    end

    %
    function Jac = bc_jacobian( ~, tL, tR, XL, XR, ~ )
      Jac = [ 1, 0, 0, 0, 0, 0 ; ...
              0, 1, 0, 0, 0, 0 ; ...
              0, 0, 1, 0, 0, 0 ; ...
              0, 0, 0, 1, 0, 0 ; ...
              0, 0, 0, 0, 1, 0 ] ;
    end

    %
    function Hess = bc_hessian( ~, tL, tR, XL, XR, ~, L )
      Hess = zeros(6,6) ;
    end

    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    %
    function tvU = TVU( self, tL, tC, tR, UCL, UCR )
      tvU = 0;
    end

    function tvG = TVU_gradient( self, tL, tC, tR, UCL, UCR )
      tvG = zeros(1,2) ;
    end
 
    function tvH = TVU_hessian( self, tL, tC, tR, UCL, UCR )
      tvH = zeros(2,2);
    end
  end
end
