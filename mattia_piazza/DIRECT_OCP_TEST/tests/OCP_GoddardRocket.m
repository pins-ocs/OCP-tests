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

classdef OCP_GoddardRocket < OCP_NLP

  properties (SetAccess = private, Hidden = true)

    h_i
    v_i
    m_i
    m_f

    Dc
    Tmax
    c
    g0

    hc
    mc
    vc

    sol
  end

  methods

    function self = OCP_GoddardRocket( )
      nx  = 3 ; % number of states
      nu  = 1 ; % number of controls
      np  = 1 ; % number of free parameters
      npc = 0 ; % number of path constraints
      nbc = 4 ; % number of boundary conditions
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;
    end

    function setup( self, nodes )
      setup@OCP_NLP( self, nodes ) ;

      self.hc   = 500;
      self.mc   = 0.6;
      self.vc   = 620;
      self.g0   = 9.81;

      self.h_i  = 1;
      self.v_i  = 0;
      self.m_i  = 1;
      self.m_f  = self.m_i * self.mc ;
      
      self.Dc   = 0.5*self.vc*self.m_i/self.g0;
      self.Tmax = 3.5*self.g0*self.m_i;
      self.c    = 0.5*sqrt(self.g0*self.h_i);

    end 

    function info = solve( self )
      
      N   = self.N;
      nx  = self.nx;
      nu  = self.nu;
      nbc = self.nbc;
 
      LZ = reshape([ self.h_i; 0; self.m_f ] * ones(1,N), 1, 3*N ) ;
      UZ = reshape([ Inf;      10; self.m_i ] * ones(1,N), 1, 3*N ) ;

      options.lb = [ LZ, zeros(1,N-1), 0.0001 ] ;  % Lower bound on the variables.
      options.ub = [ UZ, self.Tmax*ones(1,N-1), Inf ] ;  % Upper bound on the variables.

      % The constraint functions are bounded to zero
      options.cl = zeros(1,(N-1)*nx+nbc); % constraints
      options.cu = zeros(1,(N-1)*nx+nbc);

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
      TS     = 1 ;
      hguess = ones(N,1) * self.h_i ;
      vguess = (self.nodes.*(1-self.nodes)).' ;
      mguess = (self.m_f*self.nodes+self.m_i*(1-self.nodes)).';
      Tguess = ones(N-1,1)*self.Tmax/2 ;
      GZ     = reshape( [ hguess vguess mguess ], 3*N, 1 ) ;
      x0     = [ GZ ; Tguess ; TS ] ;

      tic
      [self.sol, info] = ipopt(x0,funcs,options);
      elapsed = toc ;

    end

    function plot( self )
      N     = self.N ;
      h     = self.sol(1:3:3*N) ;
      v     = self.sol(2:3:3*N) ;
      m     = self.sol(3:3:3*N) ;
      T     = self.sol(3*N+(1:N-1)) ;
      nodes = self.nodes ;

      subplot( 4, 1, 1 );  
      plot( nodes, h, 'Linewidth', 2 ) ;
      title('h') ;

      subplot( 4, 1, 2 );
      plot( nodes, v, 'Linewidth', 2 ) ;
      title('v') ;

      subplot( 4, 1, 3 );
      plot( nodes, m, 'Linewidth', 2 ) ;
      title('mass') ;

      subplot( 4, 1, 4 );
      TT = reshape( [1;1] * T.', 1, 2*(N-1) ) ; 
      nn = reshape( [ nodes(1:end-1) ; nodes(2:end)], 1, 2*(N-1) ) ;
      plot( nn, TT, 'Linewidth', 2 ) ;
      title('thrust') ;
    end

    %                      __              _   _
    %  _  _ ___ ___ _ _   / _|_  _ _ _  __| |_(_)___ _ _  ___
    % | || (_-</ -_) '_| |  _| || | ' \/ _|  _| / _ \ ' \(_-<
    %  \_,_/__/\___|_|   |_|  \_,_|_||_\__|\__|_\___/_||_/__/
    %
    function res = D( self, h, v )
      e   = exp( self.hc * (1 - h/self.h_i)) ;
      res = self.Dc * v^2 * e ;
    end

    %
    function res = Dh( self, h, v )
      eh  = -exp( self.hc * (1 - h/self.h_i))*self.hc/self.h_i ;
      res = self.Dc * v^2 * eh ;
    end

    %
    function res = Dv( self, h, v )
      e   = exp( self.hc * (1 - h/self.h_i)) ;
      res = 2 * v * self.Dc * e ;
    end

    %
    function res = Dhh( self, h, v )
      ehh = exp( self.hc * (1 - h/self.h_i))*(self.hc/self.h_i)^2 ;
      res = ehh * self.Dc * v^2 ;
    end

    %
    function res = Dhv( self, h, v )
      eh  = -exp( self.hc * (1 - h/self.h_i))*self.hc/self.h_i ;
      res = 2 * v * self.Dc * eh ;
    end

    %
    function res = Dvv( self, h, v )
      e   = exp( self.hc * (1 - self.h_i / h )) ;
      res = 2 * self.Dc * e ;
    end

    %
    function res = g( self, h )
      res = self.g0 * (self.h_i/h)^2 ;
    end

    %
    function res = g_D( self, h )
      res = -2 * self.g0 * self.h_i^2 / h^3 ;
    end

    %
    function res = g_DD( self, h )
      res = 6 * self.g0 * self.h_i^2 / h^4 ;
    end

    %  _
    % | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
    % | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
    % |____\__,_\__, |_| \__,_|_||_\__, \___|
    %           |___/              |___/
    %
    function L = lagrange( ~, ~, tL, tR, XL, XR, UC, TS )
      L = 0 ;
    end

    %
    function gradL = lagrange_gradient( self, ~, tL, tR, XL, XR, UC, TS )
      gradL = zeros( 1, 2*self.nx + self.nu + self.np ) ;
    end

    %
    function hessL = lagrange_hessian( self, ~, tL, tR, XL, XR, UC, TS )
      dim = 2*self.nx + self.nu + self.np ;
      hessL = zeros(dim,dim) ;
    end

    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( ~, tL, tR, XL, XR, TS )
      hL = XL(1) ; vL = XL(2) ; mL = XL(3) ;
      hR = XR(1) ; vR = XR(2) ; mR = XR(3) ;
      M  = -hR ;
    end

    %
    function gradM = mayer_gradient( self, tL, tR, XL, XR, TS )
      dim   = 2*self.nx + self.np ;
      gradM = zeros(1,dim) ;
      gradM(self.nx+1) = -1 ;
    end

    % [ M, gradM, hessianM ]
    function hessM = mayer_hessian( self, tL, tR, XL, XR, TS )
      dim   = 2*self.nx + self.np ;
      hessM = zeros(dim,dim) ;
    end

    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    function C = ds( self, ~, tL, tR, XL, XR, UC, TS )
      hL = XL(1) ; vL = XL(2) ; mL = XL(3) ;
      hR = XR(1) ; vR = XR(2) ; mR = XR(3) ;
      T  = UC(1) ;
      % ----------
      DT = tR - tL ;
      hM = (hR+hL)/2 ;
      vM = (vR+vL)/2 ;
      mM = (mR+mL)/2 ;
      % ----------
      C    = zeros(3,1) ;
      d    = self.D(hM,vM);
      C(1) = (hR - hL)/DT - TS*vM ;
      C(2) = (vR - vL)/DT + TS*( (d-T)/mM + self.g(hM) ) ;
      C(3) = (mR - mL)/DT + TS*T/self.c ;
    end

    %
    function JAC = ds_jacobian( self, ~, tL, tR, XL, XR, UC, TS )
      hL = XL(1) ; vL = XL(2) ; mL = XL(3) ;
      hR = XR(1) ; vR = XR(2) ; mR = XR(3) ;
      T  = UC(1) ;
      % ----------
      DT = tR - tL ;
      hM = (hR+hL)/2 ;
      vM = (vR+vL)/2 ;
      mM = (mR+mL)/2 ;
      
      JAC = zeros( 3, 2*self.nx + self.nu + self.np ) ;

      % C(1) = (hR - hL)/DT - TS*vM ;
      JAC(1,1) = -1/DT;
      JAC(1,2) = -0.5*TS;

      JAC(1,4) =  1/DT;
      JAC(1,5) = JAC(1,2);

      JAC(1,8) = -vM ;

      % C(2) = (vR - vL)/DT + TS*( (d-T)/mM + self.g(hM) ) ;

      d  = self.D(hM,vM);
      dh = self.Dh(hM,vM);
      dv = self.Dv(hM,vM);
      bf = 0.5*TS*dv/mM;

      JAC(2,1) = 0.5*TS*( dh/mM + self.g_D(hM) ) ;
      JAC(2,2) = -1/DT + bf ;
      JAC(2,3) = -0.5*TS*(d-T)/mM^2 ;

      JAC(2,4) = JAC(2,1) ;
      JAC(2,5) = 1/DT + bf ;
      JAC(2,6) = JAC(2,3) ;

      JAC(2,7) = -TS/mM ;
      JAC(2,8) = (d-T)/mM + self.g(hM) ;

      % C(3) = (mR - mL)/DT + TS*T/self.c ;
      JAC(3,3) = -1/DT ;
      JAC(3,6) =  1/DT ;
      JAC(3,7) =  TS/self.c ;
      JAC(3,8) =  T/self.c ;

    end

    %
    function H = ds_hessian( self, nseg, tL, tR, XL, XR, UC, P, L )
      H = self.FD_ds_hessian( nseg, tL, tR, XL, XR, UC, P, L ) ;
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
    function ODE = jump( ~, ~, t, XL, XR, P )
      ODE = XR - XL ;
    end

    %
    function JAC = jump_jacobian( ~, ~, t, XL, XR, P )
      JAC = [ -eye(3,3), eye(3,3) ] ;
    end

    %
    function H = jump_hessian( ~, ~, t, XL, XR, P, L )
      H = zeros(6,6) ;
    end

    %  ___  ___
    % | _ )/ __|
    % | _ \ (__
    % |___/\___|
    %
    function bc = bc( self, tL, tR, XL, XR, P )
      hL = XL(1) ; vL = XL(2) ; mL = XL(3) ;
      hR = XR(1) ; vR = XR(2) ; mR = XR(3) ;
      bc = [ hL - self.h_i ; ...
             vL - self.v_i ; ...
             mL - self.m_i ; ...
             mR - self.m_f ] ;
    end

    %
    function Jac = bc_jacobian( ~, tL, tR, XL, XR, P )
      Jac = [ 1, 0, 0, 0, 0, 0, 0 ; ...
              0, 1, 0, 0, 0, 0, 0 ; ...
              0, 0, 1, 0, 0, 0, 0 ; ...
              0, 0, 0, 0, 0, 1, 0 ] ;
    end

    %
    function Hess = bc_hessian( ~, tL, tR, XL, XR, P, L )
      Hess = zeros(7,7) ;
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
