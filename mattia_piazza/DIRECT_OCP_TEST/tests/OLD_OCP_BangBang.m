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

classdef OCP_BangBang < OCP_NLP

  properties (SetAccess = private, Hidden = true)
    x_i
    v_i
    x_f
    v_f
    sol
  end

  methods (Hidden = true)
    %   ___  ___  ___
    %  / _ \|   \| __|
    % | (_) | |) | _|
    %  \___/|___/|___|
    %
    function RES = RHS( self, nseg, t, X, U, T )
      RES = [ T*X(2) ; T*U ] ;
    end
    %
    function RES = JAC( self, nseg, t, X, U, T )
      RES = [ 0, T, 0, X(2) ; ...
              0, 0, T, U  ] ;
    end
    %
    function RES = HESS( self, nseg, t, X, U, T, L )
      RES = [ 0, 0,    0,    0    ; ...
              0, 0,    0,    L(1) ; ...
              0, 0,    0,    L(2) ; ...
              0, L(1), L(2), 0 ] ;
    end
  end

  methods

    function self = OCP_BangBang( )
      nx  = 2 ; % number of states
      nu  = 1 ; % number of controls
      np  = 1 ; % number of free parameters
      npc = 0 ; % number of path constraints
      nbc = 4 ; % number of boundary conditions
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;
    end
    
    function setup( self, nodes )
      setup@OCP_NLP( self, nodes ) ;
      self.x_i = 0;
      self.x_f = 1;
      self.v_i = 0;
      self.v_f = 0;
    end 

    function info = solve( self )
      
      xones = ones(1,self.N*self.nx) ;
      uones = ones(1,(self.N-1)*self.nu) ;
      
      options.lb = [ -xones*Inf, -uones, 0   ] ;  % Lower bound on the variables.
      options.ub = [  xones*Inf,  uones, Inf ] ;  % Upper bound on the variables.

      % The constraint functions are bounded to zero
      options.cl = zeros(1,(self.N-1)*self.nx+self.nbc); %  constraints
      options.cu = zeros(1,(self.N-1)*self.nx+self.nbc);

      % Set the IPOPT options.
      options.ipopt.jac_d_constant   = 'no';
      options.ipopt.hessian_constant = 'no';
      options.ipopt.mu_strategy      = 'adaptive';
      options.ipopt.max_iter         = 400;
      options.ipopt.tol              = 1e-10;%
      options.ipopt.linear_solver    = 'ma57';
      %options.ipopt.linear_solver    = 'mumps';
      %options.ipopt.linear_solver    = 'pardiso';

      % The callback functions.
      funcs.objective         = @(Z) self.NLP_target(Z);
      funcs.gradient          = @(Z) self.NLP_target_gradient(Z);

      funcs.constraints       = @(Z) self.NLP_constraints(Z);
      funcs.jacobian          = @(Z) self.NLP_constraints_jacobian(Z);
      funcs.jacobianstructure = @() self.NLP_constraints_jacobian_pattern();

      if false
        %options.ipopt.derivative_test = 'second-order';
        funcs.hessian           = @( Z, sigma, lambda ) self.NLP_hessian( Z, sigma, lambda ) ;
        funcs.hessianstructure  = @() self.NLP_hessian_pattern();
      else
        %options.ipopt.derivative_test            = 'first-order';
        options.ipopt.hessian_approximation      = 'limited-memory';
        options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}
      end

      % Run IPOPT.
      xguess = (self.x_i+(self.x_f-self.x_i)*self.nodes).' ;
      vguess = zeros(self.N,1);
      uguess = zeros(self.N-1,1);

      x0 = [ reshape( [ xguess, vguess], 2*self.N ,1 ) ; uguess ; 0 ] ;

      tic
      [self.sol, info] = ipopt(x0,funcs,options);
      elapsed = toc ;

    end
    
    function plot( self )
      N     = self.N;
      x     = self.sol(1:2:2*N);
      v     = self.sol(2:2:2*N);
      u     = self.sol(2*N+1:end-1);
      T     = self.sol(end) ;
      nodes = self.nodes;

      subplot( 3, 1, 1 );  
      plot( nodes, x, 'Linewidth', 2 );
      title('x') ;

      subplot( 3, 1, 2 );  
      plot( nodes, v, 'Linewidth', 2 );
      title('v') ;

      subplot( 3, 1, 3 );
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
    function L = lagrange( ~, ~, tL, tR, XL, XR, UC, P )
      L = 0 ;
    end

    %
    function gradL = lagrange_gradient( self, ~, tL, tR, XL, XR, UC, P )
      dim   = 2*self.nx + self.nu + self.np ;
      gradL = zeros( 1, dim ) ;
    end

    %
    function hessL = lagrange_hessian( self, ~, tL, tR, XL, XR, UC, P )
      dim   = 2*self.nx + self.nu + self.np ;
      hessL = zeros(dim,dim) ;
    end

    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( ~, tL, tR, XL, XR, T )
      M = T ; % only one parameter
    end
    
    %
    function gradM = mayer_gradient( self, tL, tR, XL, XR, T )
      dim   = 2*self.nx + self.np ;
      gradM = zeros(1,dim) ;
      gradM(2*self.nx+1) = 1 ;
    end
    
    % [ M, gradM, hessianM ]
    function hessM = mayer_hessian( self, tL, tR, XL, XR, T )
      dim   = 2*self.nx + self.np ;
      hessM = zeros(dim,dim) ;
    end

    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    function C = ds( self, nseg, tL, tR, XL, XR, UC, T )
      C = self.midpoint_ds( nseg, tL, tR, XL, XR, UC, T, @self.RHS ) ;
    end

    %
    function CJ = ds_jacobian( self, nseg, tL, tR, XL, XR, UC, T )
      CJ = self.midpoint_ds_jacobian( nseg, tL, tR, XL, XR, UC, T, @self.JAC ) ;
    end

    %
    function H = ds_hessian( self, nseg, tL, tR, XL, XR, UC, T, L )
      H = self.midpoint_ds_hessian( nseg, tL, tR, XL, XR, UC, T, L, @self.HESS ) ;
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
    function ODE = jump( self, nsegL, t, XL, XR )
      ODE = self.jump_standard(tL, tR, XL, XR );
    end

    %
    function JAC = jump_jacobian( ~, nsegL, t, XL, XR )
      JAC = self.jump_jacobian_standard( tL, tR, XL, XR );
    end

    %
    function H = jump_hessian( ~, nsegL, t, XL, XR, L )
      H = self.jump_hessian_standard( tL, tR, XL, XR, L );
    end

    %  ___  ___
    % | _ )/ __|
    % | _ \ (__
    % |___/\___|
    %
    function bc = bc( self, tL, tR, XL, XR, P )
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      bc = [ xL - self.x_i ; ...
             xR - self.x_f ; ...
             vL - self.v_i ; ...
             vR - self.v_f ] ;
    end

    %
    function Jac = bc_jacobian( ~, tL, tR, XL, XR, P )
      Jac = [ 1, 0, 0, 0, 0 ; ...
              0, 0, 1, 0, 0 ; ...
              0, 1, 0, 0, 0 ; ...
              0, 0, 0, 1, 0 ] ;
    end
    
    %
    function Hess = bc_hessian( ~, tL, tR, XL, XR, P, L )
      Hess = zeros(5,5) ;
    end


    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    % tvU
    function tvU = TVU( self, tL, tC, tR, UCL, UCR )
      tvU = self.TVU_standard( tL, tC, tR, UCL, UCR );
    end

    function tvG = TVU_gradient( self, tL, tC, tR, UCL, UCR )
      tvG = self.TVU_standard_gradient( tL, tC, tR, UCL, UCR );
    end

    function tvH = TVU_hessian( self, tL, tC, tR, UCL, UCR )
      tvH = self.TVU_standard_hessian( tL, tC, tR, UCL, UCR );
    end

  end
end
