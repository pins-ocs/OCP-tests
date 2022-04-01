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

classdef OCP_train < OCP_NLP

  properties (SetAccess = private, Hidden = true)
    x_i
    x_f
    v_i
    v_f
    alpha
    beta
    gm
    uepsi
    epsilon
    ss
    zz
    uaMax
    ubMax
    sol
    epsia % TV epsi ctrl a
    epsib % TV epsi ctrl b
  end

  methods

    function self = OCP_train( )
      nx  = 2 ; % number of states
      nu  = 2 ; % number of controls
      np  = 0 ; % number of free parameters
      npc = 0 ; % number of path constraints
      nbc = 4 ; % number of boundary conditions
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;
    end
    
    function setup( self, nodes )
      setup@OCP_NLP( self, nodes ) ;
      self.x_i     = 0;
      self.x_f     = 6;
      self.v_i     = 0;
      self.v_f     = 0;
      self.alpha   = 0.3;
      self.beta    = 0.14;
      self.gm      = 0.16;
      self.uepsi   = 1e-7 ;
      self.epsilon = 0.05 ;
      self.ss      = [ -2, 0, 2 ];
      self.zz      = [ 2, 4 ];
      self.uaMax   = 10 ;
      self.ubMax   = 2 ;    
      self.epsia   = 1e-8;
      self.epsib   = 0 ;    
    end 

    function info = solve( self )
      
      N     = self.N;
      nx    = self.nx;
      nu    = self.nu;
      nbc   = self.nbc;
      uaMax = self.uaMax;
      ubMax = self.ubMax;
      
      options.lb = [-ones(1,N*nx)*Inf, zeros( 1, (N-1)*nu ) ] ;  % Lower bound on the variables.
      options.ub = [ ones(1,N*nx)*Inf, reshape( [uaMax;ubMax]*ones(1,N-1), 1, nu*(N-1)) ] ;  % Upper bound on the variables.

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
      xguess  = self.x_i+(self.x_f-self.x_i)*self.nodes./4.8 ;
      vguess  = ones(1,N) ;
      uaguess = zeros(1,N-1) ;
      ubguess = zeros(1,N-1) ;

      x0 = [ reshape( [ xguess,   vguess], 2*N ,1 ) ; ...
             reshape( [ uaguess, ubguess], 2*(N-1) ,1 ) ] ;

      tic
      [self.sol, info] = ipopt(x0,funcs,options);
      elapsed = toc ;

    end
    
    function plot( self )
      N     = self.N ;
      x     = self.sol(1:2:2*N) ;
      v     = self.sol(2:2:2*N) ;
      ua    = self.sol(2*N+(1:2:2*N-2)) ;
      ub    = self.sol(2*N+(2:2:2*N-2)) ;
      nodes = self.nodes ;

      subplot( 3, 1, 1 );  
      plot( nodes, x, 'Linewidth', 2 ) ;
      title('x') ;

      subplot( 3, 1, 2 );  
      plot( nodes, v, 'Linewidth', 2 ) ;
      title('v') ;

      subplot( 3, 1, 3 );
      uua = reshape( [1;1] * ua.', 1, 2*(N-1) ) ; 
      uub = reshape( [1;1] * ub.', 1, 2*(N-1) ) ;
      nnn = reshape( [ nodes(1:end-1) ; nodes(2:end)], 1, 2*(N-1) ) ;
      plot( nnn, uua, nnn, uub, 'Linewidth', 2 ) ;
      title('ua,ub') ;

    end

    %                      __              _   _
    %  _  _ ___ ___ _ _   / _|_  _ _ _  __| |_(_)___ _ _  ___
    % | || (_-</ -_) '_| |  _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \_,_/__/\___|_|   |_|  \_,_|_||_\__|\__|_\___/_||_/__/
    %
    function res = hfun( self, x )
      res = 0 ;
      for j=1:2
        res = res + (self.ss(j+1)-self.ss(j))*atan((x-self.zz(j))/self.epsilon) ;
      end
      res = res / pi ;
    end

    %
    function res = hfun_D( self, x )
      res = 0 ;
      for j=1:2
        res = res + (self.ss(j+1)-self.ss(j))/(1+((x-self.zz(j))/self.epsilon)^2) ;
      end
      res = res / pi / self.epsilon ;
    end

    %
    function res = hfun_DD( self, x )
      res = 0 ;
      for j=1:2
        dz  = x-self.zz(j) ;
        dz2 = (dz/self.epsilon)^2 ;
        res = res + (self.ss(j+1)-self.ss(j))*dz/(1+dz2)^2 ;
      end
      res = -2*res / pi / self.epsilon^3 ;
    end

    %  _
    % | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
    % | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
    % |____\__,_\__, |_| \__,_|_||_\__, \___|
    %           |___/              |___/
    %
    function L = lagrange( ~, ~, tL, tR, XL, XR, UC, ~ )
      ua = UC(1) ; ub = UC(2) ;
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      v  = (vL+vR)/2 ;
      L  = (tR-tL) * ua * v ;
    end

    %
    function gradL = lagrange_gradient( ~, ~, tL, tR, XL, XR, UC, ~ )
      ua = UC(1) ; ub = UC(2) ;
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      v  = (vL+vR)/2 ;
      gradL = (tR-tL) * [ 0, ua/2, 0, ua/2,  v, 0] ;
    end
    
    %
    function hessL = lagrange_hessian( ~, ~, tL, tR, XL, XR, UC, ~ )
      ua = UC(1) ; ub = UC(2) ;
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      v  = (vL+vR)/2 ;
      hessL = (tR-tL) * [ 0,   0,   0,   0, 0,   0 ; ...
                          0,   0,   0,   0, 0.5, 0 ; ...
                          0,   0,   0,   0, 0,   0 ; ...
                          0,   0,   0,   0, 0.5, 0 ; ...
                          0, 0.5,   0, 0.5, 0,   0 ; ...
                          0,   0,   0,   0, 0,   0 ] ;
    end

    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( ~, tL, tR, XL, XR, ~ )
      M = 0 ;
    end
    
    %
    function gradM = mayer_gradient( ~, tL, tR, XL, XR, ~ )
      gradM = zeros(1,4) ;
    end
    
    % [ M, gradM, hessianM ]
    function hessM = mayer_hessian( ~, tL, tR, XL, XR, ~ )
      hessM = zeros(4,4) ;
    end

    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    function C = ds( self, ~, tL, tR, XL, XR, UC, ~ )
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      ua = UC(1) ; ub = UC(2) ;
      % ----------
      DT = tR - tL ;
      xM = (xR+xL)/2 ;
      vM = (vR+vL)/2 ;
      % ----------
      C    = zeros(2,1) ;
      acc  = self.hfun(xM) - ( self.alpha + self.beta * vM + self.gm * vM^2 ) ; 
      C(1) = (xR - xL)/DT - vM ;
      C(2) = (vR - vL)/DT - acc - ua + ub ;
    end

    %
    function JAC = ds_jacobian( self, ~, tL, tR, XL, XR, UC, ~ )
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      ua = UC(1) ; ub = UC(2) ;
      % ----------
      DT = tR - tL ;
      xM = (xR+xL)/2 ;
      vM = (vR+vL)/2 ;
      % ----------
      tmp_x = -0.5 * self.hfun_D(xM) ; 
      tmp_v =  0.5 * self.beta + self.gm * vM ; 
      JAC = [ -1/DT,        -0.5,  1/DT,       -0.5,  0, 0 ; ... 
               tmp_x, tmp_v-1/DT, tmp_x, tmp_v+1/DT, -1, 1 ] ;
    end

    %
    function H = ds_hessian( self, nseg, tL, tR, XL, XR, UC, P, L )
      if false
        H = self.FD_ds_hessian( nseg, tL, tR, XL, XR, UC, P, L ) ;
      else
        xL = XL(1) ; vL = XL(2) ;
        xR = XR(1) ; vR = XR(2) ;
        ua = UC(1) ; ub = UC(2) ;
        % ----------
        DT = tR - tL ;
        xM = (xR+xL)/2 ;
        vM = (vR+vL)/2 ;
        % ----------
        nx = 2 ;
        nu = 2 ;
        tmp_xx = -0.25 * self.hfun_DD(xM)  ; 
        tmp_vv =  0.5 * self.gm ; 
        Ahess  = [ tmp_xx, 0 ; 0, tmp_vv ] ;
        H      = L(2) * [ Ahess, Ahess, zeros(nx,nu) ; ...
                          Ahess, Ahess, zeros(nx,nu) ; ...
                          zeros(nu,2*nx+nu) ] ;
      end
    end

    %     _
    %  _ | |_  _ _ __  _ __
    % | || | || | '  \| '_ \
    %  \__/ \_,_|_|_|_| .__/
    %                 |_|
    %
    function ODE = jump( ~, nseg, t, XL, XR, ~ )
      ODE = XR - XL ;
    end

    %
    function JAC = jump_jacobian( ~, nseg, t, XL, XR, ~ )
      JAC = [ -eye(2,2), eye(2,2) ] ;
    end

    %
    function H = jump_hessian( ~, nseg, t, XL, XR, ~, L )
      H  = zeros(4,4) ;
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

    %  ___  ___
    % | _ )/ __|
    % | _ \ (__
    % |___/\___|
    %
    function bc = bc( self, tL, tR, XL, XR, ~ )
      xL = XL(1) ; vL = XL(2) ;
      xR = XR(1) ; vR = XR(2) ;
      bc = [ xL - self.x_i ; ...
             xR - self.x_f ; ...
             vL - self.v_i ; ...
             vR - self.v_f ] ;
    end

    %
    function Jac = bc_jacobian( ~, tL, tR, XL, XR, ~ )
      Jac = [ 1, 0, 0, 0 ; ...
              0, 0, 1, 0 ; ...
              0, 1, 0, 0 ; ...
              0, 0, 0, 1 ] ;
    end
    
    %
    function Hess = bc_hessian( ~, tL, tR, XL, XR, ~, L )
      Hess = zeros(4,4) ;
    end


    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    %
    function tvU = TVU( self, tL, tC, tR, UCL, UCR )
      epsi1 = self.epsia/(tR-tL) ;
      epsi2 = self.epsib/(tR-tL) ;
      tvU   = epsi1 * (UCR(1)-UCL(1))^2 + epsi2 * (UCR(2)-UCL(2))^2 ;
    end

    function tvG = TVU_gradient( self, tL, tC, tR, UCL, UCR )
      epsi1 = self.epsia*(UCR(1)-UCL(1))/(tR-tL) ;
      epsi2 = self.epsib*(UCR(2)-UCL(2))/(tR-tL) ;
      tvG   = epsi1 * [ -2, 0, 2, 0 ] + epsi2 * [ 0, -2, 0, 2 ] ;
    end
 
    function tvH = TVU_hessian( self, tL, tC, tR, UCL, UCR )
      epsi1 = self.epsia/(tR-tL) ;
      epsi2 = self.epsib/(tR-tL) ;
      tvH   = epsi1 * [  2, 0, -2, 0 ; ...
                         0, 0,  0, 0 ; ...
                        -2, 0,  2, 0 ; ...
                         0, 0,  0, 0 ] + ...
              epsi2 * [ 0,  0, 0,  0 ; ...
                        0,  2, 0, -2 ; ...
                        0,  0, 0,  0 ; ...
                        0, -2, 0,  2 ];
    end
  end
end
