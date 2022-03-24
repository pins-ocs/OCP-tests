%-------------------------------------------------------------------------%
%                                                                         %
%         , __                 , __                                       %
%        /|/  \               /|/  \                                      %
%         | __/ _   ,_         | __/ _   ,_                               %
%         |   \|/  /  |  |   | |   \|/  /  |  |   |                       %
%         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                      %
%                           /|                   /|                       %
%                           \|                   \|                       %
%                                                                         %
%      Enrico Berolazzi                                                   %
%      Mattia Piazza                                                      %
%      Dipartimento di Ingegneria Industriale                             %
%      Universita` degli Studi di Trento                                  %
%      email: enrico.bertolazzi@unitn.it                                  %
%             mattia.piazza@unitn.it                                      %
%                                                                         %
%-------------------------------------------------------------------------%
%
classdef OCP_Direct_BangBangF < OCP_NLP
%
  properties 
    pins_dims
    pins
    pins_data
    guess
    sol
    w__tv = 0.0001; % total variation weigth
  end
  %
  methods
    %
    function this = OCP_Direct_BangBangF( )
      % Constructor
      addpath('../generated_code/ocp-interfaces/Matlab');         % add path to the interface folder
      tmp_pins = BangBangF( 'BangBangF' );                        % initialise the object from PINS
      tmp_pins.setup('../generated_code/data/BangBangF_Data.rb'); % setup the object with the ruby data file
      dims = tmp_pins.dims();                                     % get dimension structure
      nx  = double(dims.dim_x) ;                                  % number of states
      nu  = double(dims.dim_u) ;                                  % number of controls
      np  = double(dims.dim_pars) ;                               % number of free parameters
      npc = 1 ;                                                   % number of path constraints
      nbc = dims.dim_bc;                                          % number of boundary conditions
      this@OCP_NLP( nx, nu, np, npc, nbc ) ;                      % initialise the NLP object
      this.pins = tmp_pins;                                       % copy of the PINS object
      this.pins_data = tmp_pins.get_ocp_data();                   % copy of the DATA
      this.pins.set_guess();                                      % use default guess generated in MAPLE
      this.pins_dims = dims;                                      % copy the dimension
    end
    % 
    function setup( this, varargin )
      % Setup function.
      % Default case: use mesh from PINS
      % Otherwise specify the mesh
      if nargin == 1
         nodes = unique(this.pins.get_nodes(),'rows')';
      elseif nargin == 2
        nodes = varargin{1};
      else
        fprintf("Wrong Mesh\nUsing DEFAULT MESH ");
        nodes = unique(this.pins.get_nodes(),'rows')';
      end
      setup@OCP_NLP( this, nodes ) ;
    end
    %
    function q = eval_q(this,s) %%% Can be avoided
      q = this.pins.eval_q(0,s);
    end
    %

    %  _
    % | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
    % | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
    % |____\__,_\__, |_| \__,_|_||_\__, \___|
    %           |___/              |___/
    %
    function L = lagrange( this, nseg, tL, tR, XL, XR, UC, P )
      % lagrange target at midpoint
      XM = (XR+XL)/2;
      tM = (tR+tL)/2;
      qM = this.pins.eval_q(nseg,tM);
      L  = this.pins.eval_lagrange_target(nseg,qM,XM,UC,P);
    end
    %
    function gradL = lagrange_gradient( this, nseg, tL, tR, XL, XR, UC, P )
      % lagrange gradient at midpoint
      XM     = ( XR + XL ) / 2;
      tM     = (tR+tL)/2;
      dXMdXR = 1/2;
      dXMdXL = 1/2;
      qM     = this.pins.eval_q(nseg,tM);
      dL     = this.pins.eval_DlagrangeDxup(nseg,qM,XM,UC,P);
      dLdx   = dL(1:this.nx);
      dLdu   = dL(this.nx + (1:this.nu) );
      dLdp   = dL(this.nx + this.nu + 1:end );
      gradL  = [dLdx*dXMdXR, dLdx*dXMdXL, dLdu, dLdp];
    end
    %
    %%% WRONG
    function hessL = lagrange_hessian( this, ~, tL, tR, XL, XR, UC, ~ )% unused
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
    %
    %  __  __
    % |  \/  |__ _ _  _ ___ _ _
    % | |\/| / _` | || / -_) '_|
    % |_|  |_\__,_|\_, \___|_|
    %              |__/
    %
    function M = mayer( this, tL, tR, XL, XR, P  ) %% iseg_L
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      M     = this.pins.eval_mayer_target(isegL,qL,XL,isegR,qR,XR,P) ;
    end
    %
    function gradM = mayer_gradient( this, tL, tR, XL, XR, P )
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      gradM = this.pins.eval_DmayerDxxp(isegL,qL,XL,isegR,qR,XR,P) ;
    end
    %
    %%% WRONG
    function hessM = mayer_hessian( this, tL, tR, XL, XR, ~ )
      dim   = 2*this.nx + this.np ;
      hessM = zeros(dim,dim) ;
    end
    %
    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    %
    function C = ds( this, nseg, tL, tR, XL, XR, UC, P )
      qL     = this.pins.eval_q(nseg,tL);
      qR     = this.pins.eval_q(nseg,tR);
      C_coll = this.pins.eval_fd_ode(nseg, qL, XL, nseg, qR, XR, UC, P);
      C_InC  = this.pins.eval_fd_c(  nseg, tL, XL, nseg, tR, XR, UC, P);
      C      = [C_coll; C_InC];
    end
    %
    function CJ = ds_jacobian( this, nseg, tL, tR, XL, XR, UC, P )
      qL      = this.pins.eval_q(nseg,tL);
      qR      = this.pins.eval_q(nseg,tR);
      CJ_coll = this.pins.eval_Dfd_odeDxxup(nseg, qL, XL, nseg, qR, XR, UC, P);
      CJ_InC  = this.pins.eval_Dfd_cDxxup(  nseg, tL, XL, nseg, tR, XR, UC, P);
      CJ = [CJ_coll;CJ_InC];
    end

    % NON VIENE USATO PER ORA DA MODIFICARE
    function CH = ds_hessian( this, nseg, tL, tR, XL, XR, UC, ~, L )
      CH_coll = this.ds_midpont_hessian( nseg, tL, tR, XL, XR, UC, [], L );
      CH = CH_coll;
    end

    % NON VIENE USATO PER ORA DA MODIFICARE
    function CH = ds_midpont_hessian( this, nseg, tL, tR, XL, XR, UC, ~, L )

      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      qM = this.eval_q(tM);
      dt = (tR - tL) ;
      dX = (XR - XL) ;
      VM = dX/dt;
      DXMDXL = 1/2;
      DXMDXR = 1/2;
      DVMDXL = -1/dt;
      DVMDXR =  1/dt;

      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      HH = this.HESS( nseg, tM, XM, UC, L ) ;
      D1 = (-0.25)*HH(1:this.nx,1:this.nx) ;
      R1 = (-0.5)*HH(1:this.nx,this.nx+1:end) ;
      D2 = -HH(this.nx+1:end,this.nx+1:end) ;
      CH = [ D1,   D1,   R1 ; ...
             D1,   D1,   R1 ; ...
             R1.', R1.', D2 ] ;
    end
    %
    %  ___  ___
    % | _ )/ __|
    % | _ \ (__
    % |___/\___|
    %
    function bc = bc( this, tL, tR, XL, XR, P  )
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      bc    = this.pins.eval_bc(isegL,qL,XL,isegL,qR,XR,P);
    end
    %
    function Jac = bc_jacobian( this, tL, tR, XL, XR, P )
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      Jac = full(this.pins.eval_DbcDxxp(isegL,qL,XL,isegR,qR,XR,P));
    end
    %
    % NON VIENE USATO PER ORA DA MODIFICARE
    function Hess = bc_hessian( ~, tL, tR, XL, XR, ~, L )
      Hess = zeros(2,2) ; %%% NOT USED
    end
    %

    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    % 
    function tvU = TVU( this, tL, tC, tR, UCL, UCR )
      % tvU = this.TVU_standard( tL, tC, tR, UCL, UCR );
      delta = (UCL - UCR);
      tvU = this.w__tv * (delta * delta');
    end
    %
    function tvG = TVU_gradient( this, tL, tC, tR, UCL, UCR )
      % tvG = this.TVU_standard_gradient( tL, tC, tR, UCL, UCR );
      delta  = (UCL - UCR);
      Ddelta = [eye(length(delta)), -eye(length(delta))];
      tvG = this.w__tv * 2 * delta * Ddelta;
    end
    %
    % NON VIENE USATO PER ORA DA MODIFICARE
    function tvH = TVU_hessian( this, tL, tC, tR, UCL, UCR )
      tvH = this.TVU_standard_hessian( tL, tC, tR, UCL, UCR );
    end
    %
    %  ____                        _
    % | __ )  ___  _   _ _ __   __| |___
    % |  _ \ / _ \| | | | '_ \ / _` / __|
    % | |_) | (_) | |_| | | | | (_| \__ \
    % |____/ \___/ \__,_|_| |_|\__,_|___/
    %
    function [x_lb,x_ub,u_lb,u_ub] = bounds(this, varargin)
      % bounds() define bounds for all states and controls
      % Vector of ones
      oneN      = ones(1,this.N);
      oneN_1    = ones(1,(this.N-1));
      % states bounds
      x_ub     = +inf * oneN;
      x_lb     =    0 * oneN; %%% -inf * oneN;
      v_ub     = +inf * oneN;
      v_lb     =    0 * oneN; %%% -inf * oneN;
      % control bounds
      F_lb     = -1 * oneN_1;
      F_ub     = +1 * oneN_1;
      % reshape vectors
      x_lb = reshape([x_lb; v_lb], 1, this.N*this.nx );
      x_ub = reshape([x_ub; v_ub], 1, this.N*this.nx );
      u_lb = F_lb;
      u_ub = F_ub;
    end
    %
    function [c_lb,c_ub] = Constraint_bounds(this, varargin)
      % Constraint_bounds() define bounds for all constrained.
      % The problem is built the assumption that we are using direct collocation and
      % all the constarains are of the kind C1(x) <= 0
      % C0 are equatity constraint C1 are inequality constraint
      % Bounds for constraints C0
      C0_lb     = zeros(this.nx, this.N-1);
      C0_ub     = zeros(this.nx, this.N-1);
      % Bounds for constraints C1
      C1_lb     = -inf * ones(this.npc, this.N-1); 
      C1_ub     = zeros(this.npc, this.N-1); 
      % Bounds for constraints Boundary Conditions
      Cbc_lb    = zeros(1,this.nbc);
      Cbc_ub    = zeros(1,this.nbc);
      % Build output vectors
      c_lb      = [ reshape([C0_lb; C1_lb], 1, (this.N-1)*(this.nx+this.npc) ) , Cbc_lb ];
      c_ub      = [ reshape([C0_ub; C1_ub], 1, (this.N-1)*(this.nx+this.npc) ) , Cbc_ub ];
    end
    %
    %  ____
    % / ___|_   _  ___  ___ ___
    %| |  _| | | |/ _ \/ __/ __|
    %| |_| | |_| |  __/\__ \__ \
    % \____|\__,_|\___||___/___/
    %
    function x0 = standard_Guess(this)
      % Define the guess
      % zeta
      zeta = this.nodes / this.nodes(end);
      % define states guesses
      x_g = zeta*0;
      v_g = zeta.*(1-zeta);
      % Vector of ones
      oneN      = ones(1,this.N);
      oneN_1    = ones(1,(this.N-1));
      % define control guess
      F_g      = 0 * oneN_1;
      % reshape vector
      XGUESS = reshape([x_g; v_g], 1, this.N*this.nx );
      UGUESS = reshape([F_g], 1,(this.N-1)*this.nu);
      % build output guess
      x0 = [  XGUESS , UGUESS ] ;
    end
    %
    %  ____        _
    % / ___|  ___ | |_   _____
    % \___ \ / _ \| \ \ / / _ \
    %  ___) | (_) | |\ V /  __/
    % |____/ \___/|_| \_/ \___|
    %
    function info = solve( this, varargin )
      % Solve function
      % Set upper and lower bound for states and controls
      [x_lb,x_ub,u_lb,u_ub] = this.bounds();
      % The constraint functions are bounded to [0,0] for equality and
      % [-inf,0] for inequality
      [c_lb,c_ub] = this.Constraint_bounds();
      % Store in option structure
      options.lb = [ x_lb, u_lb ] ;  % Lower bound on the variables.
      options.ub = [ x_ub, u_ub ] ;  % Upper bound on the variables.
      options.cl = c_lb;             % Lower bound constraints.
      options.cu = c_ub;             % Upper bound constraints.
      % Set the IPOPT options.
      options.ipopt.jac_d_constant   = 'no';
      options.ipopt.hessian_constant = 'no';
      options.ipopt.mu_strategy      = 'adaptive'; 
      options.ipopt.max_iter         = 500; 
      options.ipopt.tol              = 1e-8;
      options.ipopt.linear_solver    = 'mumps'; % 'ma57' % 'pardiso'
      options.ipopt.derivative_test  = 'none'; 
        % - none              : no derivative test
        % - first-order       : perform test of first derivatives 
        % - second-order      : perform test of first and second derivatives 
        % - only-second-order : perform test of only second derivatives
      % The callback functions. AKA function mapping
      funcs.objective         = @(Z) this.NLP_target(Z);
      funcs.gradient          = @(Z) this.NLP_target_gradient(Z);
      funcs.constraints       = @(Z) this.NLP_constraints(Z);
      funcs.jacobian          = @(Z) this.NLP_constraints_jacobian(Z);
      funcs.jacobianstructure = @() this.NLP_constraints_jacobian_pattern();
      % choose between "analytic" Hessian  and numeric
      %%%
      HessianType = 'bfgs'; %'analityc';
      if strcmp(HessianType, 'analityc')
        funcs.hessian           = @( Z, sigma, lambda ) this.NLP_hessian( Z, sigma, lambda ) ;
        funcs.hessianstructure  = @() this.NLP_hessian_pattern();
      elseif strcmp(HessianType, 'bfgs')
        options.ipopt.hessian_approximation      = 'limited-memory';
        options.ipopt.limited_memory_update_type = 'bfgs' ; % {bfgs}, sr1 = 6; % {6}
      else
        error("Error in solve() unexpected hessian type: %s",HessianType);
      end
      % Set Guess from method
      x0 = this.standard_Guess();
      % If there is an argument to the function try to set the argument as guess
      % Only for warm start of states
      % Full warm start to be implemented
      if nargin == 2
        new_guess = varargin{1};
        size_new  = size(new_guess,2);
        supposed_size = this.N*this.nx +(this.N-1)*this.nu;
        if size_new == supposed_size
          x0 = new_guess;
        else
          error("Bad guess dimension. Expected %d but got %d \n",supposed_size,size_new);
        end
      end
      % SOLVE
      tic
      [this.sol, info] = ipopt_auxdata(x0,funcs,options);
      elapsed = toc ;
    end
    %
    %  ____  _       _
    % |  _ \| | ___ | |_
    % | |_) | |/ _ \| __|
    % |  __/| | (_) | |_
    % |_|   |_|\___/ \__|    
    %
    function plot( this )
      % set Latex Interpreter
      set(0,'defaultTextInterpreter','latex');
      % Unpack the solution
      Nx_sol   = this.N*this.nx;
      % Number of each state and control
      n_x  = 1;
      n_v  = 2;
      n_F  = 1;
      % build solution vectors
      x    = this.sol( n_x:this.nx:Nx_sol);
      v    = this.sol( n_v:this.nx:Nx_sol);
      F    = this.sol( Nx_sol+n_F:this.nu:end);
      % get nodes
      nodes = this.nodes;
      % initialize figures
      figure('WindowStyle', 'Docked','Name','SOLUTION')
      %
      subplot( 4, 1, 1 );
      hold on
      plot( nodes, x, 'Linewidth', 2 );
      plot( nodes, v, 'Linewidth', 2 );
      title('x v') ;
      %
      subplot( 4, 1, 2 );
      hold on
      plot( nodes, v, 'Linewidth', 2 );
      legend('v') ;
      %
      subplot( 4, 1, 3 );
      %
      subplot( 4, 1, 4 );
      % trick to plot constant control in a cell
      hold on
      F_ = reshape( [1;1] * F, 1, 2*(this.N-1) ) ;
      nn = reshape( [ nodes(1:end-1) ; nodes(2:end)], 1, 2*(this.N-1) ) ;
      plot( nn, F_, 'Linewidth', 2 ) ;
      title('Controls') ;
      legend(["F"]);
      hold off
    end
    %
    %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% NOT IMPLEMENTED WITH PINS YET %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %              _   _                           _             _           _
    %  _ __   __ _| |_| |__     ___ ___  _ __  ___| |_ _ __ __ _(_)_ __  ___| |_
    % | '_ \ / _` | __| '_ \   / __/ _ \| '_ \/ __| __| '__/ _` | | '_ \/ __| __|
    % | |_) | (_| | |_| | | | | (_| (_) | | | \__ \ |_| | | (_| | | | | \__ \ |_
    % | .__/ \__,_|\__|_| |_|  \___\___/|_| |_|___/\__|_|  \__,_|_|_| |_|___/\__|
    % |_|
    %
    function C = pc( this, t, X, PARS )
      C = zeros(0,1) ;
    end
    %
    function CJ = pc_jacobian( this, t, X, PARS )
      CJ = zeros(0,this.nx) ;
    end
    %
    function CH = pc_hessian( this, t, X, PARS, L )
      CH = zeros(this.nx,this.nx) ;
    end
    %
    %     _
    %  _ | |_  _ _ __  _ __
    % | || | || | '  \| '_ \
    %  \__/ \_,_|_|_|_| .__/
    %                 |_|
    %
    function ODE = jump( this, nsegL, t, XL, XR )
      ODE = this.jump_standard(tL, tR, XL, XR );
    end
    %
    function JAC = jump_jacobian( ~, nsegL, t, XL, XR )
      JAC = this.jump_jacobian_standard( tL, tR, XL, XR );
    end
    %
    function H = jump_hessian( ~, nsegL, t, XL, XR, L )
      H = this.jump_hessian_standard( tL, tR, XL, XR, L );
    end
    %
  end
end
