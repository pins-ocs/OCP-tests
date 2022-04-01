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

classdef OCP_tyre_Dynamic_1D_Direct < OCP_NLP 

  properties %(SetAccess = private, Hidden = true)
    pins_dims
    pins
    pins_data
    guess
    sol
  end

  methods %(Hidden = true)
    %   ___  ___  ___
    %  / _ \|   \| __|
    % | (_) | |) | _|
    %  \___/|___/|___|
    %
    
    function q = eval_q(self,s)
      q = self.pins.eval_q(0,s);
    end
    
    function RES = A(self, nseg, t, X, ~  )
      RES = full(self.pins.eval_A( nseg, t, X, [] ));
    end
   
    function RES = DnuDx(self, nseg, t, X,V, ~  )
      RES = self.pins.eval_DnuDx(nseg, t, X, V, [] );
    end
    
    function RES = RHS( self, nseg, t, X, U, ~  )
      RES = self.pins.eval_rhs_ode(nseg, t, X, U, [] );
    end
    
    function RES = J__RHS__x( self, nseg, t, X, U, ~ )
      RES = full(self.pins.eval_Drhs_odeDx(nseg, t, X, U, [] ));
    end
    
    function RES = J__RHS__U( self, nseg, t, X, U, ~ )
      RES = full(self.pins.eval_Drhs_odeDu(nseg, t, X, U, [] ));
    end

  end

  methods

    function self = OCP_tyre_Dynamic_1D_Direct( )
      % Constructor

      addpath('../generated_code/ocp-interfaces/Matlab');                   % add path to the interface folder
      tmp_pins = OCP_tyre_Dynamic_1D( 'OCP_tyre_Dynamic_1D' );              % initialise the object from PINS 
      tmp_pins.setup('../generated_code/data/OCP_tyre_Dynamic_1D_Data.rb'); % setup the object with the ruby data file  
      dims = tmp_pins.dims();                                               % get dimension structure
      nx  = double(dims.dim_x) ;                                            % number of states
      nu  = double(dims.dim_u) ;                                            % number of controls
      np  = double(dims.dim_pars) ;                                         % number of free parameters
      npc = 0 ;                                                             % number of path constraints
      nbc = dims.dim_bc;                                                    % number of boundary conditions
      self@OCP_NLP( nx, nu, np, npc, nbc ) ;                                % initialise the NLP object 
      self.pins = tmp_pins;                                                 % copy of the PINS object
      self.pins_data = tmp_pins.get_ocp_data();                             % copy of the DATA
      self.pins.set_guess();                                                % use default guess generated in MAPLE
      self.pins_dims = dims;                                                % copy the dimension
    end
    
    function setup( self, varargin )
      % Setup function. 
      % Default case: use mesh from PINS
      % Otherwise specify the mesh

      if nargin == 1
         nodes = unique(self.pins.get_nodes(),'rows')';
      elseif nargin == 2
        nodes = varargin{1};
      else
        fprintf("Wrong Mesh\nUsing DEFAULT MESH ");
        nodes = unique(self.pins.get_nodes(),'rows')';
      end
      setup@OCP_NLP( self, nodes ) ;
    end 
    
    function [x_lb,x_ub,u_lb,u_ub] = bounds(self, varargin) 
	    % bounds()
	    % define bounds for all states and controls
    
	    oneN      = ones(1,self.N);
	    oneN_1    = ones(1,(self.N-1));
	    v__ub      = oneN * double( self.pins_data.Parameters.v__ub ) ;
	    v__lb      = oneN * double( self.pins_data.Parameters.v__lb ) ;
	    omega__ub  = oneN * double( self.pins_data.Parameters.omega__ub );
	    omega__lb  = oneN * double( self.pins_data.Parameters.omega__lb );
	    lambda__ub = oneN * double( self.pins_data.Parameters.lambda__ub );
	    lambda__lb = oneN * double( self.pins_data.Parameters.lambda__lb );
	    p__ub      = oneN * double( self.pins_data.Parameters.p__ub );
	    p__lb      = oneN * double( self.pins_data.Parameters.p__lb );
	    b__ub      = oneN * double( self.pins_data.Parameters.b__ub );
	    b__lb      = oneN * double( self.pins_data.Parameters.b__lb );
	    p__o__ub   = oneN_1 * double( self.pins_data.Parameters.p__o__ub );
	    p__o__lb   = oneN_1 * double( self.pins_data.Parameters.p__o__lb );
	    b__o__ub   = oneN_1 * double( self.pins_data.Parameters.b__o__ub );
	    b__o__lb   = oneN_1 * double( self.pins_data.Parameters.b__o__lb );
    
	    x_ub = reshape([ v__ub; omega__ub; lambda__ub; p__ub; b__ub;  ], 1, self.N*self.nx );
	    x_lb = reshape([ v__lb; omega__lb; lambda__lb; p__lb; b__lb;  ], 1, self.N*self.nx );
	    u_ub = reshape([ p__o__ub; b__o__ub;  ], 1, (self.N-1)*self.nu );
	    u_lb = reshape([ p__o__lb; b__o__lb;  ], 1, (self.N-1)*self.nu );
    end 

    function x0 = standard_Guess(self) 
	    % bounds()
	    % Define guess for all states and controls
    
	    oneN      = ones(1,self.N);
	    oneN_1    = ones(1,(self.N-1));
	    v__g       = oneN * double( self.pins_data.Parameters.v__ss );
	    omega__g   = oneN * double( self.pins_data.Parameters.omega__ss );
	    lambda__g  = oneN * double( self.pins_data.Parameters.lambda__ss );
	    p__g       = oneN * double( self.pins_data.Parameters.p__ss );
	    b__g       = oneN * double( self.pins_data.Parameters.b__ss );
	    p__o__g    = oneN_1 * 0 ;
	    b__o__g    = oneN_1 * 0 ;
    
	    x_g = reshape([ v__g; omega__g; lambda__g; p__g; b__g;  ], 1, self.N*self.nx );
	    u_g = reshape([ p__o__g; b__o__g;  ], 1, (self.N-1)*self.nu );
	    x0 = [ x_g , u_g ] ;
    end 

    function [c_lb,c_ub] = Constraint_bounds(self, varargin)
      % Constraint_bounds()
      % define bounds for all constrained. 
      % The problem is built the assumption that we are using direct collocation and 
      % all the constarains are of the kind C(x) >= 0

      C0_lb     = zeros(self.nx, self.N-1);
      C1_lb     = zeros(self.npc, self.N-1);
      C0_ub     = zeros(self.nx, self.N-1);
      C1_ub     = inf * ones(self.npc, self.N-1);

      Cbc_lb    = zeros(1,self.nbc);
      Cbc_ub    = zeros(1,self.nbc);

      c_lb      = [ reshape([C0_lb; C1_lb], 1, (self.N-1)*(self.nx+self.npc) ) , Cbc_lb ];
      c_ub      = [ reshape([C0_ub; C1_ub], 1, (self.N-1)*(self.nx+self.npc) ) , Cbc_ub ];
    end
    
    function info = solve( self, varargin )
      
      % Set upper and lower bound for states and controls
      
      [x_lb,x_ub,u_lb,u_ub] = self.bounds();
      options.lb = [ x_lb, u_lb ] ;  % Lower bound on the variables.
      options.ub = [ x_ub, u_ub ] ;  % Upper bound on the variables.
      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      % The constraint functions are bounded to zero

      [c_lb,c_ub] = self.Constraint_bounds();
      options.cl = c_lb; %  constraints
      options.cu = c_ub;

      % options.cl = zeros(1,(self.N-1)*(self.nx+self.npc)+self.nbc); %  constraints
      % options.cu = zeros(1,(self.N-1)*(self.nx+self.npc)+self.nbc);

      % Set the IPOPT options.
      options.ipopt.jac_d_constant   = 'no';
      options.ipopt.hessian_constant = 'no';
      options.ipopt.mu_strategy      = 'adaptive';
      options.ipopt.max_iter         = 2000; %%% 2000
      options.ipopt.tol              = 1e-8;%
      %options.ipopt.linear_solver    = 'ma57';
      options.ipopt.linear_solver    = 'mumps';
      %options.ipopt.linear_solver    = 'pardiso';
      
      options.ipopt.derivative_test  = 'none'; %% 
        %%% none: do not perform derivative test
        %%% first-order: perform test of first derivatives at starting point
        %%% second-order: perform test of first and second derivatives at starting point
        %%% only-second-order: perform test of second derivatives at starting point

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
      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      % Set Guess      
      x0 = self.standard_Guess();
      
      % If there is an argument to the function try to set the argument as guess
      if nargin == 2
        new_guess = varargin{1};
        size_new  = size(new_guess,2);
        supposed_size = self.N*self.nx + (self.N-1)*self.nu;
        if size_new == supposed_size
          x0 = new_guess;
        else
          fprintf("Bad guess dimension. Expected %d but got %d \n",supposed_size,size_new);
        end
      end
      
      % SOLVE

      tic
      [self.sol, info] = ipopt_auxdata(x0,funcs,options); %%% ipopt(x0,funcs,options);
      elapsed = toc ;

    end
    
    function plot( self )
      set(0,'defaultTextInterpreter','latex');
      
      Nx_sol   = self.N*self.nx;
      
      n_x  = 1;
      n_v  = 2;
      n_F  = 1;


      x    = self.sol( n_x:self.nx:Nx_sol);
      v    = self.sol( n_v:self.nx:Nx_sol);

      
      F    = self.sol( Nx_sol+n_F:self.nu:end);


      nodes = self.nodes;
      
      figure('WindowStyle', 'Docked','Name','SOLUTION')

      subplot( 4, 1, 1 );   
      hold on
      plot( nodes, x, 'Linewidth', 2 );
      plot( nodes, v, 'Linewidth', 2 );

      title('x v') ;
      
      subplot( 4, 1, 2 );   
      hold on
      plot( nodes, v, 'Linewidth', 2 );
      legend('v') ;
      
      subplot( 4, 1, 3 );   
      

      subplot( 4, 1, 4 );
      hold on
      F_ = reshape( [1;1] * F, 1, 2*(self.N-1) ) ;
      
      nn = reshape( [ nodes(1:end-1) ; nodes(2:end)], 1, 2*(self.N-1) ) ;
      plot( nn, F_, 'Linewidth', 2 ) ;
      title('Controls') ;
      legend(["F"]);
      
      hold off 
      

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
      qM = self.eval_q(tM);
      L = self.pins.eval_lagrange_target(nseg,qM,XM,UC,[]);
    end

    %
    function gradL = lagrange_gradient( self, nseg, tL, tR, XL, XR, UC, ~ )
      dt = (tR-tL);
      XM = ( XR + XL ) / 2;
      tM = (tR+tL)/2;
      dXMdXR = 1/2;
      dXMdXL = 1/2;
      
      qM = self.eval_q(tM);
      dL    = self.pins.eval_DlagrangeDxup(nseg,qM,XM,UC,[]);
      
      dXMUCPdXLXRUCP = [dXMdXL*eye(self.nx)      , dXMdXR*eye(self.nx)      , 0*zeros(self.nx,self.nu);...
                        0*zeros(self.nu,self.nx) , 0*zeros(self.nu,self.nx) , 1*eye(self.nu)];
      gradL = dL * dXMUCPdXLXRUCP;
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
      qL = self.eval_q(tL);
      qR = self.eval_q(tR);
      M = self.pins.eval_mayer_target(0,qL,XL,0,qR,XR,[]) ; 
    end
    
    %
    function gradM = mayer_gradient( self, tL, tR, XL, XR, ~ )
      qL = self.eval_q(tL);
      qR = self.eval_q(tR);
      gradM = self.pins.eval_DmayerDxxp(0,qL,XL,0,qR,XR,[]) ;
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

    function C = ds( self, nseg, tL, tR, XL, XR, UC, ~ )
      C_coll = self.ds_midpoint(nseg, tL, tR, XL, XR, UC);
      %%% C_InC  = self.ds_inequality_Constraint(nseg, tL, tR, XL, XR, UC);
      %%% C  = [C_coll; C_InC];
      C  = C_coll;
    end

    function CJ = ds_jacobian( self, nseg, tL, tR, XL, XR, UC, ~ )  
      CJ_coll = self.ds_midpoint_jacobian(nseg, tL, tR, XL, XR, UC);
      %%% CJ_InC  = self.ds_inequality_Constraint_jacobian(nseg, tL, tR, XL, XR, UC);  
      %%% CJ = [CJ_coll;CJ_InC];
      CJ = CJ_coll;
    end

    % NON VIENE USATO PER ORA DA MODIFICARE
    function CH = ds_hessian( self, nseg, tL, tR, XL, XR, UC, ~, L )
      CH = [] ;
    end

    function C = ds_midpoint( self, nseg, tL, tR, XL, XR, UC, ~ )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      qM = self.eval_q(tM);
      %%% C = 0
      %%% C = A(tM,XM)*X'-RHS(tM,XM,UC) = 0
      %%% A(tM,XM)*dX/dt-RHS(tM,XM,UC) = 0
      %%% A(tM,XM)*(XR-XL)/tR-tL)-RHS(tM,XM,UC) = 0
      VM = (XR-XL)/(tR-tL);
      %%% nu = A*V
      % nu = self.nu( nseg, tM, XM, VM);
      nu = self.pins.eval_nu(nseg, qM, XM, VM, [] );
      rhs = self.pins.eval_rhs_ode(nseg, qM, XM, UC, [] );
      C  = nu - rhs;
    end

    function C = ds_inequality_Constraint( self, nseg, tL, tR, XL, XR, UC, ~ )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      qM = self.eval_q(tM);
      C = self.pins.C1(XM(2));
    end

    %
    function CJ = ds_midpoint_jacobian( self, nseg, tL, tR, XL, XR, UC, ~ )
      tM = (tR+tL)/2 ;
      qM = self.eval_q(tM);
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
      A = full(self.pins.eval_A( nseg, qM, XM, [] ));
      DnuDXM  = full(self.pins.eval_DnuDx(nseg, qM, XM, VM, [] ));
      DnuDVM  = A; 
      DRHSDXM = full(self.pins.eval_Drhs_odeDx(nseg, qM, XM, UC, [] ));
      DRHSDUC = full(self.pins.eval_Drhs_odeDu(nseg, qM, XM, UC, [] ));

      DCDXL = DnuDXM * DXMDXL + DnuDVM * DVMDXL - DRHSDXM * DXMDXL;
      DCDXR = DnuDXM * DXMDXR + DnuDVM * DVMDXR - DRHSDXM * DXMDXR;
      
      DCDUC = - DRHSDUC;
      
      CJ = [ DCDXL, DCDXR, DCDUC ];
    end

    function C = ds_inequality_Constraint_jacobian(self, nseg, tL, tR, XL, XR, UC)
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      qM = self.eval_q(tM);
      dt = (tR - tL) ;
      dX = (XR - XL) ;
      VM = dX/dt;
      DXMDXL = 1/2;
      DXMDXR = 1/2;
      DVMDXL = -1/dt;
      DVMDXR =  1/dt; 


      CJXM = zeros(1,self.nx);
      CJUC = zeros(1,self.nu);
      CJXM(1) = 0;
      CJXM(2) = self.pins.C1_D(XM(2));


      DCDXL = CJXM * DXMDXL;
      DCDXR = CJXM * DXMDXR;
      DCDUC = CJUC;

      C = [DCDXL,DCDXR,DCDUC];
    end

    % NON VIENE USATO PER ORA DA MODIFICARE
    function CH = ds_midpont_hessian( self, nseg, tL, tR, XL, XR, UC, ~, L )
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
      qL = self.eval_q(tL);
      qR = self.eval_q(tR);
      tmp = self.pins.eval_bc(0,qL,XL,0,qR,XR,[]);
      bc  = tmp(1:self.nbc);
%       bc = [ vL - self.v_i ; ...
%              vR - self.v_f ] ;
    end

    %
    function Jac = bc_jacobian( self, tL, tR, XL, XR, ~ )
      qL = self.eval_q(tL);
      qR = self.eval_q(tR);
      Jac = full(self.pins.eval_DbcDxxp(0,qL,XL,0,qR,XR,[]));
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
%       tvU = self.TVU_standard( tL, tC, tR, UCL, UCR );
      tvU = self.TVU_custom( tL, tC, tR, UCL, UCR );
    end

    function tvG = TVU_gradient( self, tL, tC, tR, UCL, UCR )
%       tvG = self.TVU_standard_gradient( tL, tC, tR, UCL, UCR );
      tvG = self.TVU_custom_gradient( tL, tC, tR, UCL, UCR );
    end

    function tvH = TVU_hessian( self, tL, tC, tR, UCL, UCR )
      tvH = self.TVU_standard_hessian( tL, tC, tR, UCL, UCR );
    end
    
    function p = dotprod(self,x1,x2)
      p = x1 * x2';
    end
    
    function p2 = vec_square(self,x1)
      p2 = self.dotprod(x1,x1);
    end
    
    function dp2 = Dvec_square(self,x1)
      dp2 = 2 * x1;
    end
    
    function tvU = TVU_custom( self, tL, tC, tR, UCL, UCR )
      w__tv = 0;
      delta = (UCL - UCR);
      tvU = w__tv * self.vec_square(delta);
    end
    
    function tvG = TVU_custom_gradient( self, tL, tC, tR, UCL, UCR )
      w__tv = 0;
      delta  = (UCL - UCR);
      Ddelta = [eye(self.nu), -eye(self.nu)];
      tvG = w__tv * self.Dvec_square(delta) * Ddelta;
    end

  end
end
