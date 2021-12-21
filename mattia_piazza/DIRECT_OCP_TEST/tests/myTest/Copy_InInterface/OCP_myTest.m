%--------------------------------------------------------------------------%
%                                                                          %
%         , __                 , __                                        %
%        /|/  \               /|/  \                                       %
%         | __/ _   ,_         | __/ _   ,_                                %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                        %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       %
%                           /|                   /|                        %
%                           \|                   \|                        %
%                                                                          %
%      Mattia Piazza                                                       %
%      Dipartimento di Ingegneria Industriale                              %
%      Universita` degli Studi di Trento                                   %
%      email: mattia.piazza@unitn.it                                       %
%                                                                          %
%--------------------------------------------------------------------------%

classdef OCP_myTest < OCP_NLP 

  properties %(SetAccess = private, Hidden = true)
    pins_dims
    pins
    pins_data
    
    v_i
    
    v_f
    sol
  end

  methods %(Hidden = true)
    %   ___  ___  ___
    %  / _ \|   \| __|
    % | (_) | |) | _|
    %  \___/|___/|___|
    %
    function RES = A(self, nseg, t, X, ~  )
      RES = full(self.pins.eval_A( nseg, t, X, [] ));
%       RES = [1];
    end
    
    function RES = J__A__x(self,nseg,t,X, ~ ) % unused
      RES = [1]; %%% TO BE IMPLEMENTED
    end
    
    
    function RES = DnuDx(self, nseg, t, X,V, ~  )
      RES = self.pins.eval_DnuDx(nseg, t, X, V, [] );
    end
    
    function RES = RHS( self, nseg, t, X, U, ~  )
      RES = self.pins.eval_rhs_ode(nseg, t, X, U, [] );
%       RES = [ U/X(1)] ;
    end
    %
%     function RES = JAC( self, nseg, t, X, U, ~ )
%       RES = [ -U/X(1)^2, 1/X(1)] ;
%     end
    %
    function RES = J__RHS__x( self, nseg, t, X, U, ~ )
      RES = full(self.pins.eval_Drhs_odeDx(nseg, t, X, U, [] ));
    end
    %
    function RES = J__RHS__U( self, nseg, t, X, U, ~ )
      RES = full(self.pins.eval_Drhs_odeDu(nseg, t, X, U, [] ));
    end
    %
    function RES = HESS( self, nseg, t, X, U, ~ ) % unused
      RES = [ 2*U/X(1)^3, -1/X(1)^2 ; ...
               -1/X(1)^2,         0 ] ;
    end
  end

  methods

    function self = OCP_myTest( )
      tmp_pins = Test_1D_singulararc( 'Test_1D_singulararc' );
      tmp_pins.setup('../../data/Test_1D_singulararc_Data.rb');
      dims = tmp_pins.dims();
      

      nx  = double(dims.dim_x) ;    % number of states
      nu  = double(dims.dim_u) ;    % number of controls
      np  = double(dims.dim_pars) ; % number of free parameters
      npc = 0 ;                     % number of path constraints
      nbc = 2; % dims.dim_bc;    % number of boundary conditions
      % number bc errato
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;

      self.pins = tmp_pins;
      self.pins_data = tmp_pins.get_ocp_data();
      
      self.pins.set_guess();
      
      self.pins_dims = dims;
    end
    
    function setup( self, nodes )
      setup@OCP_NLP( self, nodes ) ;

      self.v_i = 1;
      self.v_f = 1;
    end 

    function info = solve( self )
      
      xones = ones(1,self.N*self.nx) ;
      uones = ones(1,(self.N-1)*self.nu) ;
      
      options.lb = [ -xones*0, -uones] ;  % Lower bound on the variables.
      options.ub = [  xones*500,  uones] ;  % Upper bound on the variables.

      % The constraint functions are bounded to zero
      options.cl = zeros(1,(self.N-1)*self.nx+self.nbc); %  constraints
      options.cu = zeros(1,(self.N-1)*self.nx+self.nbc);

      % Set the IPOPT options.
      options.ipopt.jac_d_constant   = 'no';
      options.ipopt.hessian_constant = 'no';
      options.ipopt.mu_strategy      = 'adaptive';
      options.ipopt.max_iter         = 1000;
      options.ipopt.tol              = 1e-4;%
      %options.ipopt.linear_solver    = 'ma57';
      options.ipopt.linear_solver    = 'mumps';
      %options.ipopt.linear_solver    = 'pardiso';

      % The callback functions.
      funcs.objective         = @(Z) self.NLP_target(Z);
      funcs.gradient          = @(Z) self.NLP_target_gradient(Z);

      funcs.constraints       = @(Z) self.NLP_constraints(Z);
      funcs.jacobian          = @(Z) self.NLP_constraints_jacobian(Z);
      funcs.jacobianstructure = @() self.NLP_constraints_jacobian_pattern();

      if false %%%
        %options.ipopt.derivative_test = 'second-order';
        funcs.hessian           = @( Z, sigma, lambda ) self.NLP_hessian( Z, sigma, lambda ) ;
        funcs.hessianstructure  = @() self.NLP_hessian_pattern();
      else
        %options.ipopt.derivative_test            = 'first-order';
        options.ipopt.hessian_approximation      = 'limited-memory';
        options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}
      end

      % Run IPOPT.
      % xguess = (self.x_i+(self.x_f-self.x_i)*self.nodes).' ;
      vguess = (self.v_i+(self.v_f-self.v_i)*self.nodes).' ;
      uguess = zeros(self.N-1,1);

%       x0 = [ reshape( [ xguess, vguess], 2*self.N ,1 ) ; uguess ; 0 ] ;
      x0 = [  vguess ; uguess ] ;

      tic
      [self.sol, info] = ipopt_auxdata(x0,funcs,options); %%% ipopt(x0,funcs,options);
      elapsed = toc ;

    end
    
    function plot( self )
      N     = self.N;
      v     = self.sol(1:1:N);
      u     = self.sol(N+1:end);
      % T     = self.sol(end) ;
      nodes = self.nodes;

      subplot( 2, 1, 1 );   
      plot( nodes, v, 'Linewidth', 2 );
      title('v') ;

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
    function L = lagrange( self, nseg, tL, tR, XL, XR, UC, ~ )
%       dt = (tR-tL);
%       VM = ( XR(1) + XL(1) )/dt / 2;
%       L = 1/(VM) ;
      XM = (XR+XL)/2;
      tM = (tR+tL)/2;
      L = self.pins.eval_lagrange_target(nseg,tM,XM,UC,[]);
    end

    %
    function gradL = lagrange_gradient( self, nseg, tL, tR, XL, XR, UC, ~ )
%       dt = (tR-tL);
%       XM = ( XR(1) + XL(1) ) / 2;
%       dXMdXR = 1/2;
%       dXMdXL = 1/2;
%       dLdXM  = -1/XM^2;
% %       dLdUC  = 0;
% %       dLdP   = 0;
%       gradL = dt * [dLdXM*dXMdXL, dLdXM*dXMdXR, 0];
% %       dt = (tR-tL);
% %       XM = ( XR + XL ) / 2;
% %       tM = (tR+tL)/2;
% %       dXMdXR = 1/2;
% %       dXMdXL = 1/2;
% %       dLdXM = self.pins.eval_Hx(nseg,tM,XM,XM*0,XM/dt,UC,[]);
% %       dLdUC = self.pins.eval_Hu(nseg,tM,XM,XM*0,UC,[]);
% %       dLdP  = self.pins.eval_Hp(nseg,tM,XM,XM*0,XM/dt,UC,[]);
% %       gradL = [dLdXM*dXMdXL, dLdXM*dXMdXR, dLdUC, dLdP];
      dt = (tR-tL);
      XM = ( XR + XL ) / 2;
      tM = (tR+tL)/2;
      dXMdXR = 1/2;
      dXMdXL = 1/2;
      dL    = self.pins.eval_DlagrangeDxup(nseg,tM,XM,UC,[]);
      
      dXMUCPdXLXRUCP = [dXMdXL,dXMdXR,0;...
                        0     ,0     ,1];
      gradL = dL' * dXMUCPdXLXRUCP;
    end

    % WRONG
    function hessL = lagrange_hessian( self, ~, tL, tR, XL, XR, UC, ~ )% unused
      dt = (tR-tL);
      VM = ( XR(1) + XL(1) ) / 2;
      dXMdXR = 1/2;
      dXMdXL = 1/2;
      % dLdXM  = -1/VM^2;
      d2LdXM2 = +2*1/VM^3;
      hessL = dt * [d2LdXM2*dXMdXL^2     , d2LdXM2*dXMdXR*dXMdXL, 0 ; ...
                    d2LdXM2*dXMdXL*dXMdXR, d2LdXM2*dXMdXR^2     , 0 ; ...
                    0                    , 0                    , 0 ];
    end

    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( self, tL, tR, XL, XR, ~  )
      % NOT SURE
      % self.pins.eval_mayer_target(1,tL,XL,2,tR,XR,U,[])
      M = 0 ; 
    end
    
    %
    function gradM = mayer_gradient( self, tL, tR, XL, XR, ~ )
      dim   = 2*self.nx + self.np ;
      gradM = zeros(1,dim) ;
    end
    
    % [ M, gradM, hessianM ]
    function hessM = mayer_hessian( self, tL, tR, XL, XR, ~ )
      dim   = 2*self.nx + self.np ;
      hessM = zeros(dim,dim) ;
    end

    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
% %     function C = ds( self, nseg, tL, tR, XL, XR, UC, ~ )
% % %       C = self.midpoint_ds( nseg, tL, tR, XL, XR, UC, T, @self.RHS ) ;
% %       tM = (tR+tL)/2 ;
% %       XM = (XR+XL)./2 ;
% % %       C  = (XR-XL)/(tR-tL) - feval( RHS, nseg, tM, XM, UC ) ;
% %       C  = (XR-XL)/(tR-tL) - self.RHS(nseg, tM, XM, UC ) ;
% %     end
% % 
% %     %
% %     function CJ = ds_jacobian( self, nseg, tL, tR, XL, XR, UC, ~ )
% % %       CJ = self.midpoint_ds_jacobian( nseg, tL, tR, XL, XR, UC, T, @self.JAC ) ;
% %       tM = (tR+tL)/2 ;
% %       XM = (XR+XL)./2 ;
% % %       JJ = feval( JAC, nseg, tM, XM, UC) ;
% %       JJ = self.JAC( nseg, tM, XM, UC) ;
% %       B1 = (-0.5)*JJ(1:self.nx,1:self.nx) ;
% %       B2 = JJ(1:self.nx,self.nx+1:end) ;
% %       bf = 1/(tR - tL) ;
% %       CJ = [ B1-bf*eye(self.nx), B1+bf*eye(self.nx), -B2 ] ;
% %     end
% % 
% %     %
% %     function CH = ds_hessian( self, nseg, tL, tR, XL, XR, UC, ~, L )
% % %       CH = self.midpoint_ds_hessian( nseg, tL, tR, XL, XR, UC, T, L, @self.HESS ) ;
% %       tM = (tR+tL)/2 ;
% %       XM = (XR+XL)./2 ;
% % %       HH = feval( HESS, nseg, tM, XM, UC, L ) ;
% %       HH = self.HESS( nseg, tM, XM, UC, L ) ;
% %       D1 = (-0.25)*HH(1:self.nx,1:self.nx) ;
% %       R1 = (-0.5)*HH(1:self.nx,self.nx+1:end) ;
% %       D2 = -HH(self.nx+1:end,self.nx+1:end) ;
% %       CH = [ D1,   D1,   R1 ; ...
% %              D1,   D1,   R1 ; ...
% %              R1.', R1.', D2 ] ;
% %     end

    function C = ds( self, nseg, tL, tR, XL, XR, UC, ~ )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      %%% C = 0
      %%% C = A(tM,XM)*X'-RHS(tM,XM,UC) = 0
      %%% A(tM,XM)*dX/dt-RHS(tM,XM,UC) = 0
      %%% A(tM,XM)*(XR-XL)/tR-tL)-RHS(tM,XM,UC) = 0
      VM = (XR-XL)/(tR-tL);
      %%% nu = A*V
      % nu = self.nu( nseg, tM, XM, VM);
      nu = self.pins.eval_nu(nseg, tM, XM, VM, [] );
      rhs = self.pins.eval_rhs_ode(nseg, tM, XM, UC, [] );
      C  = nu - rhs;
    end

    %
    function CJ = ds_jacobian( self, nseg, tL, tR, XL, XR, UC, ~ )
%       tM = (tR+tL)/2 ;
%       XM = (XR+XL)./2 ;
%       JJ = self.JAC( nseg, tM, XM, UC) ;
%       B1 = (-0.5)*JJ(1:self.nx,1:self.nx) ;
%       B2 = JJ(1:self.nx,self.nx+1:end) ;
%       bf = 1/(tR - tL) ;
%       CJ = [ B1-bf*eye(self.nx), B1+bf*eye(self.nx), -B2 ] ;
      
%       tM = (tR+tL)/2 ;
%       XM = (XR+XL)./2 ;
% 
%       bf = 1/(tR - tL) ;
%       
%       J_A = self.J__A__x( nseg, tM, XM);
%       
%       A = self.A( nseg, tM, XM);
%       J_RHS_X = self.J__RHS__x( nseg, tM, XM, UC) ;
% 
%       
%       DCDXL = bf * (XR - XL) * J_A / 2 - bf * A - J_RHS_X / 2;
%       DCDXR = bf * (XR - XL) * J_A / 2 + bf * A - J_RHS_X / 2;
%       DCDUC = - self.J__RHS__U( nseg,tM,XM,UC);
% 
%       
%       CJ = [ DCDXL, DCDXR, DCDUC ];
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      dt = (tR - tL) ;
      dX = (XR - XL) ;
      VM = dX/dt;
      DXMDXL = 1/2;
      DXMDXR = 1/2;
      DVMDXL = -1/dt;
      DVMDXR =  1/dt;
      
      % C  = nu - RHS
      % C  = A*V - RHS
      % C' = A'*V + A*V' - RHS' = D
      % V' = V1

%       nu = self.pins.eval_nu(nseg, tM, XM, VM, [] );
      A = full(self.pins.eval_A( nseg, tM, XM, [] ));
      DnuDXM  = full(self.pins.eval_DnuDx(nseg, tM, XM, VM, [] ));
      DnuDVM  = A; 
      DRHSDXM = full(self.pins.eval_Drhs_odeDx(nseg, tM, XM, UC, [] ));
      DRHSDUC = full(self.pins.eval_Drhs_odeDu(nseg, tM, XM, UC, [] ));
      

      DCDXL = DnuDXM * DXMDXL + DnuDVM * DVMDXL - DRHSDXM * DXMDXL;
      DCDXR = DnuDXM * DXMDXR + DnuDVM * DVMDXR - DRHSDXM * DXMDXR;
      
      DCDUC = - DRHSDUC;

      
      CJ = [ DCDXL, DCDXR, DCDUC ];
    end

    % NON VIENE USATO PER ORA DA MODIFICARE
    function CH = ds_hessian( self, nseg, tL, tR, XL, XR, UC, ~, L )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      HH = self.HESS( nseg, tM, XM, UC, L ) ;
      D1 = (-0.25)*HH(1:self.nx,1:self.nx) ;
      R1 = (-0.5)*HH(1:self.nx,self.nx+1:end) ;
      D2 = -HH(self.nx+1:end,self.nx+1:end) ;
      CH = [ D1,   D1,   R1 ; ...
             D1,   D1,   R1 ; ...
             R1.', R1.', D2 ] ;
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
    function bc = bc( self, tL, tR, XL, XR, ~  )
%       vL = XL(1) ;
%       vR = XR(1) ;
      bc = self.pins.eval_bc(1,tL,XL,2,tR,XR,[]);
%       bc = [ vL - self.v_i ; ...
%              vR - self.v_f ] ;
    end

    %
    function Jac = bc_jacobian( self, tL, tR, XL, XR, ~ )
      Jac = full(self.pins.eval_DbcDxxp(1,tL,XL,2,tR,XR,[]));
%       Jac = [ 1, 0; ...
%               0, 1] ;
    end
    
    %
    function Hess = bc_hessian( ~, tL, tR, XL, XR, ~, L )
      Hess = zeros(2,2) ; %%% NOT USED
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
