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
classdef OCP_tyre_Dynamic_1D_Direct < OCP_NLP
%
  properties 
    pins_dims
    pins
    pins_data
    guess
    sol
    pins_sol
    w__tv = 1E-4; % total variation weigth
    tolh  = 0.001;
  end
  %
  methods
    %
    function this = OCP_tyre_Dynamic_1D_Direct( )
      % Constructor
      addpath('../generated_code/ocp-interfaces/Matlab');             % add path to the interface folder
      tmp_pins = TyreDynamic( 'TyreDynamic' );                      % initialise the object from PINS 
      tmp_pins.setup('../generated_code/data/TyreDynamic_Data.rb'); % setup the object with the ruby data file  
      dims = tmp_pins.dims();                                         % get dimension structure
      nx   = double(dims.dim_x) ;                                     % number of states
      nu   = double(dims.dim_u) ;                                     % number of controls
      np   = double(dims.dim_pars) ;                                  % number of free parameters
      npc  = double(dims.dim_ineq) ;                                  % number of path constraints
      nbc  = double(dims.num_active_BC);                              % number of boundary conditions
      this@OCP_NLP( nx, nu, np, npc, nbc ) ;                          % initialise the NLP object
      this.pins = tmp_pins;                                           % copy of the PINS object
      this.pins_data = tmp_pins.get_ocp_data();                       % copy of the DATA
      this.pins.set_guess();                                          % use default guess generated in MAPLE
      this.pins_dims = dims;                                          % copy the dimension
    end
    % 
    function setup( this, varargin )
      % Setup function.
      % Default case: use mesh from PINS
      % Otherwise specify the mesh
      if nargin == 1
        nodes = this.pins.get_nodes()';
        segments = this.pins.get_node_to_segment();
      elseif nargin == 2
        nodes = varargin{1};
        segments = 0 * nodes;
      else
        fprintf("Wrong Mesh\nUsing DEFAULT MESH ");
        nodes = this.pins.get_nodes()';
      end
      setup@OCP_NLP( this, nodes , segments) ;
    end
    %
    %  _
    % | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
    % | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
    % |____\__,_\__, |_| \__,_|_||_\__, \___|
    %           |___/              |___/
    %
    function L = lagrange( this, isegL, isegR, tL, tR, XL, XR, UC, P )
      % lagrange target at midpoint
      XM = (XR+XL)/2;
      tM = (tR+tL)/2;
      dt = (tR-tL);
      qM = this.pins.eval_q(isegL,tM);
      L  = this.pins.eval_lagrange_target(isegL,qM,XM,UC,P) * dt;
    end
    %
    function gradL = lagrange_gradient( this, isegL, isegR, tL, tR, XL, XR, UC, P )
      % lagrange gradient at midpoint
      XM     = ( XR + XL ) / 2;
      tM     = (tR+tL)/2;
      dXMdXR = 1/2;
      dXMdXL = 1/2;
      qM     = this.pins.eval_q(isegL,tM);
      dt = (tR-tL);
      dL     = this.pins.eval_DlagrangeDxup(isegL,qM,XM,UC,P) * dt;
      dLdx   = dL(1:this.nx);
      dLdu   = dL(this.nx + (1:this.nu) );
      dLdp   = dL(this.nx + this.nu + 1:end );
      gradL  = [dLdx*dXMdXR, dLdx*dXMdXL, dLdu, dLdp];
    end
    %
    function hessL = lagrange_hessian( this, isegL, isegR, tL, tR, XL, XR, UC, P )
    % function hessL = lagrange_hessian( this, nseg, tL, tR, XL, XR, UC, P )
      XM     = ( XR + XL ) / 2;
      tM     = (tR+tL)/2;
      DXMDXR = 1/2;
      DXMDXL = 1/2;
      qM     = this.pins.eval_q(isegL,tM);
      %
      dt = (tR-tL);
      hess_XMUXP = full(this.pins.eval_D2lagrangeD2xup(isegL,qM,XM,UC,P)) * dt;
      % Matrix can be decomposed in 
      % [ A | B ]
      % [ --|-- ]
      % [ B'| C ]
      % Where A is the hessian with respect to XM, 
      % B is the hessian of the mixed term XM-UC, XM-P and
      % C is the hessian with respect to UC, P and the mixed terms
      % The resulting hessian matrix should be
      % [ 1/4*A | 1/4*A | 1/2*B ]
      % [ ------|-------|-------]
      % [ 1/4*A | 1/4*A | 1/2*B ]
      % [ ------|-------|-------]
      % [ 1/2*B'| 1/2*B'|     C ]
      %
      A  = hess_XMUXP(1:this.nx,1:this.nx);
      B  = hess_XMUXP(1:this.nx,(this.nx+1):end);
      BT = hess_XMUXP((this.nx+1):end,1:this.nx);
      
      C  = hess_XMUXP((this.nx+1):end,(this.nx+1):end);
      %
      hessL =  [ 1/4*A , 1/4*A , 1/2*B ; ...
                 1/4*A , 1/4*A , 1/2*B ; ...
                 1/2*B', 1/2*B',     C ];
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
    function hessM = mayer_hessian( this, tL, tR, XL, XR, P )
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      %
      hessM = full(this.pins.eval_D2mayerD2xxp( isegL, qL, XL, isegR, qR, XR, P ));
    end
    %
    %   ___  ___  ___   _____   _   ___
    %  / _ \|   \| __| / /   \ /_\ | __|
    % | (_) | |) | _| / /| |) / _ \| _|
    %  \___/|___/|___/_/ |___/_/ \_\___|
    %
    %
    function C = ds( this, isegL, isegR, tL, tR, XL, XR, UC, P )
      qL     = this.pins.eval_q(isegL,tL);
      qR     = this.pins.eval_q(isegR,tR);
      if isegL == isegR
        % if same segment
        C_coll = this.pins.eval_fd_ode(isegL, qL, XL, isegR, qR, XR, UC, P);
        C_InC  = this.pins.eval_fd_c(  isegL, tL, XL, isegR, tR, XR, UC, P);
      else
        C_coll = this.Jump(isegL, qL, XL, isegR, qR, XR, UC, P);
        C_InC  = this.JumpInC(  isegL, tL, XL, isegR, tR, XR, UC, P);
      end
      C      = [C_coll; C_InC];
    end
    %
    function CJ = ds_jacobian( this, isegL, isegR, tL, tR, XL, XR, UC, P )
      qL     = this.pins.eval_q(isegL,tL);
      qR     = this.pins.eval_q(isegR,tR);
      if isegL == isegR
        % if same segment
        CJ_coll = this.pins.eval_Dfd_odeDxxup(isegL, qL, XL, isegR, qR, XR, UC, P);
        CJ_InC  = this.pins.eval_Dfd_cDxxup(  isegL, tL, XL, isegR, tR, XR, UC, P);
      else
        CJ_coll = this.JumpJacobian(isegL, qL, XL, isegR, qR, XR, UC, P);
        CJ_InC  = this.JumpJacobianInC(  isegL, tL, XL, isegR, tR, XR, UC, P);
      end
      CJ = [CJ_coll;CJ_InC];
    end

    function CH = ds_hessian( this, isegL, isegR, tL, tR, XL, XR, UC, P, L )
      qL     = this.pins.eval_q(isegL,tL);
      qR     = this.pins.eval_q(isegR,tR);
      L_coll = L(1:this.nx);
      L_InC  = L((this.nx+1):end);
      if isegL == isegR
        % if same segment
        CH_coll = full(this.pins.eval_D2fd_odeD2xxup( isegL, qL, XL, isegR, qR, XR, UC, P, L_coll ));
        CH_InC  = full(this.pins.eval_D2fd_cD2xxup(    isegL, qL, XL, isegR, qR, XR, UC, P, L_InC ));
      else
        CH_coll = this.JumpHessian(    isegL, qL, XL, isegR, qR, XR, UC, P, L_coll );
        CH_InC  = this.JumpHessianInC( isegL, qL, XL, isegR, qR, XR, UC, P, L_InC );
      end
      CH = CH_coll + CH_InC;
    end
    %
    %
    %     _
    %  _ | |_  _ _ __  _ __
    % | || | || | '  \| '_ \
    %  \__/ \_,_|_|_|_| .__/
    %                 |_|
    %
    %
    function J = Jump(this, isegL, qL, XL, isegR, qR, XR, UC, P)
      J = ( XR - XL )' ;
    end
    %
    function J = JumpInC(this, isegL, qL, XL, isegR, qR, XR, UC, P)
      J = zeros(this.npc,1) ;
    end
    %
    function JJ = JumpJacobian(this, isegL, qL, XL, isegR, qR, XR, UC, P)
      JJ = [ -eye(this.nx,this.nx), ...
              eye(this.nx,this.nx), ...
              zeros(this.nx, this.nu+this.np) ] ;
    end
    %
    function JJ = JumpJacobianInC(this, isegL, qL, XL, isegR, qR, XR, UC, P)
      JJ = zeros(this.npc,2*this.nx+this.nu+this.np) ;
    end
    %
    %
    function JH = JumpHessian(this, isegL, qL, XL, isegR, qR, XR, UC, P, L_coll)
      dim = 2*this.nx+this.nu+this.np ;
      JH  = zeros(dim,dim) ;
    end
    %
    function JH = JumpHessianInC(this, isegL, qL, XL, isegR, qR, XR, UC, P, L_InC)
      dim = 2*this.nx+this.nu+this.np ;
      JH  = zeros(dim,dim) ;
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
      Jac   = full(this.pins.eval_DbcDxxp(isegL,qL,XL,isegR,qR,XR,P));
    end
    %
    % 
    function Hess = bc_hessian( this, tL, tR, XL, XR, P, L )
      isegL = 0;
      isegR = 0;
      qL    = this.pins.eval_q(isegL,tL);
      qR    = this.pins.eval_q(isegR,tR);
      Hess  = full(this.pins.eval_D2bcD2xxp( isegL, qL, XL, isegR, qR, XR, P, L ) ); 
    end
    %

    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    % 
    function tvU = TVU( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
      % tvU = this.TVU_standard( tL, tC, tR, UCL, UCR );
      delta = (UCL - UCR);
      if isegL == isegC && isegC == isegR
        dt = (tR-tL);
        tvU = this.w__tv * (delta * delta') * dt ;
      else
        tvU = (delta * delta') * 0;
      end
    end
    %
    function tvG = TVU_gradient( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
      % tvG = this.TVU_standard_gradient( tL, tC, tR, UCL, UCR );
      delta = (UCL - UCR);
      Ddelta = [eye(length(delta)), -eye(length(delta))];
      if isegL == isegC && isegC == isegR
        dt = (tR-tL);
        tvG = this.w__tv * 2 * delta * Ddelta * dt ;
      else
        tvG = 2 * delta * Ddelta * 0;
      end
    end
    %
    function tvH = TVU_hessian( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
      % tvH = this.TVU_standard_hessian( tL, tC, tR, UCL, UCR );
      dt = (tR-tL);
      delta  = (UCL - UCR);
      Ddelta = [eye(length(delta)), -eye(length(delta))];
      if isegL == isegC && isegC == isegR
        tvH = this.w__tv * 2 * (Ddelta' * Ddelta) * dt ;
      else
        tvH = 2 * (Ddelta' * Ddelta) * 0;
      end
    end
    %
    %  ____                        _
    % | __ )  ___  _   _ _ __   __| |___
    % |  _ \ / _ \| | | | '_ \ / _` / __|
    % | |_) | (_) | |_| | | | | (_| \__ \
    % |____/ \___/ \__,_|_| |_|\__,_|___/
    %
    function [x_lb,x_ub,u_lb,u_ub,p_lb,p_ub] = bounds(this, varargin)
      % bounds() define bounds for all states and controls
      % Vector of ones
      oneNx      = ones(1,this.N*this.nx);
      oneNu      = ones(1,(this.N-1)*this.nu);
      oneNp      = ones(1,this.np);
      % states and control bounds
      x_lb = -inf * oneNx; 
      x_ub = +inf * oneNx;
      u_lb =   -1 * oneNu; 
      u_ub =   +1 * oneNu;
      p_lb = -inf * oneNp; 
      p_ub = +inf * oneNp;      
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
      %  % Define the guess
      %  % zeta
      %  zeta = this.nodes / this.nodes(end);
      %  % define states guesses
      %  x_g = zeta*0;
      %  v_g = zeta.*(1-zeta);
      %  % Vector of ones
      %  oneN      = ones(1,this.N);
      %  oneN_1    = ones(1,(this.N-1));
      %  % define control guess
      %  F_g      = 0 * oneN_1;
      %  % reshape vector
      %  XGUESS = reshape([x_g; v_g], 1, this.N*this.nx );
      %  UGUESS = reshape([F_g], 1,(this.N-1)*this.nu);
      %  % build output guess
      %  x0 = [  XGUESS , UGUESS ] ;
      %
      raw = this.pins.get_raw_solution();
      [XGUESS, ~, PGUESS, ~] = this.pins.unpack(raw);
      XGUESS = reshape(XGUESS,1,[]);
      UGUESS = zeros(1,(this.N-1)*this.nu);
      x0     = [  XGUESS , UGUESS, PGUESS ] ;
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
      [x_lb,x_ub,u_lb,u_ub,p_lb,p_ub] = this.bounds();
      % The constraint functions are bounded to [0,0] for equality and
      % [-inf,0] for inequality
      [c_lb,c_ub] = this.Constraint_bounds();
      % Store in option structure
      options.lb = [ x_lb, u_lb, p_lb ] ;  % Lower bound on the variables.
      options.ub = [ x_ub, u_ub, p_ub ] ;  % Upper bound on the variables.
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
      HessianType = 'analityc';
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
%       if nargin == 2
%         new_guess = varargin{1};
%         size_new  = size(new_guess,2);
%         supposed_size = this.N*this.nx +(this.N-1)*this.nu;
%         if size_new == supposed_size
%           x0 = new_guess;
%         else
%           error("Bad guess dimension. Expected %d but got %d \n",supposed_size,size_new);
%         end
%       end
      if nargin == 2
        if isstruct(varargin{1})
          new_guess      = varargin{1}.x;
          options.zl     = varargin{1}.zl;
          options.zu     = varargin{1}.zu;
          options.lambda = varargin{1}.lambda;
        else
          new_guess = varargin{1};
        end
        size_new  = size(new_guess,2);
        supposed_size = this.N*this.nx + (this.N-1)*this.nu;
        if size_new == supposed_size
          x0 = new_guess;
        else
          fprintf("Bad guess dimension. Expected %d but got %d \n",supposed_size,size_new);
        end
      end
      % SOLVE
      tic
      [this.sol, info] = ipopt_auxdata(x0,funcs,options);
      elapsed = toc ;
    end
    %
    %  ____        _                             _   _                   _   _
    % / ___|  ___ | |_   _____    ___ ___  _ __ | |_(_)_ __  _   _  __ _| |_(_) ___  _ __
    % \___ \ / _ \| \ \ / / _ \  / __/ _ \| '_ \| __| | '_ \| | | |/ _` | __| |/ _ \| '_ \
    %  ___) | (_) | |\ V /  __/ | (_| (_) | | | | |_| | | | | |_| | (_| | |_| | (_) | | | |
    % |____/ \___/|_| \_/ \___|  \___\___/|_| |_|\__|_|_| |_|\__,_|\__,_|\__|_|\___/|_| |_|

    %%%%%%%%%%%%%%%%%%%%%
    function info = solve_continuation( this, varargin )
      % tmp store first solution
      info_tmp = this.solve();
      % store it into last saved solution
      last_saved_sol = info_tmp;
      % plot for debug
      this.plot();
      % flag to end continuation
      cont_end_flag = 1;
      % number of continuation
      num_cont = 0;
      % initial step continuation
      ds     = 0.2;
      % initial value ogf continuation
      s_old  = 0;
      % next value ogf continuation
      s_new  = 0;
      % lower limit for step
      ds_lim = 0.01;
      % check if the first problem is converged
      if info_tmp.status == 0
        % Start  continuation
        fprintf("\n+++++++++++++++++++++++++START CONTINUATION+++++++++++++++++++++++++\n")
        while (cont_end_flag && ds > ds_lim)
          % saturate s
          s_new = min( s_old + ds , 1);
          % update the continuation
          this.pins.update_continuation(num_cont,s_old,s_new)
          % solve
          info_tmp = this.solve(last_saved_sol);
          if info_tmp.status == 0
            % if converged -> update and increment step
            last_saved_sol = info_tmp;
            s_old = s_new;
            ds = ds * 1.5;
          else
            % if not converged -> decrease step
            ds = ds * 0.5;
          end
          % plot for debug
          this.plot();
          % end condition if all continuation converged
          if (s_new >= 1 && info_tmp.status == 0)
            cont_end_flag = 0;
          end
        end
      else
        % Not convergence of first solution
        fprintf("\n++++++++++++++++++++++++++NOT CONVERGED!!!++++++++++++++++++++++++++\n");
      end
      % return solution
      info = last_saved_sol; 
    end
    %%%%%%%%%%%%%%%%%%%%%%%
    %                   _                _       _   _
    %  _ __   __ _  ___| | __  ___  ___ | |_   _| |_(_) ___  _ __
    % | '_ \ / _` |/ __| |/ / / __|/ _ \| | | | | __| |/ _ \| '_ \
    % | |_) | (_| | (__|   <  \__ \ (_) | | |_| | |_| | (_) | | | |
    % | .__/ \__,_|\___|_|\_\ |___/\___/|_|\__,_|\__|_|\___/|_| |_|
    % |_|
    function pack_sol(this)
      Nx = this.N*this.nx;
      Nu = (this.N-1)*this.nu;
      X = this.sol(1:Nx);
      U = this.sol(Nx+(1:Nu));
      P = this.sol(Nx+Nu+(1:this.np));
      X = reshape(X,this.nx,[]);
      this.pins_sol = this.pins.pack(X,0*X,P,zeros(1,this.nbc));
      this.pins.set_raw_solution(this.pins_sol,U);
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
      this.pack_sol();
      %this.pins.plot_states();

      % initialize figures
      figure('WindowStyle', 'Docked','Name','SOLUTION')
      %
      zeta = this.pins.solution('zeta');
      % xvars_t := [v(t),omega(t),lambda(t),p(t),b(t)]: 
      % uvars_t := [p__o(t), b__o(t)]:

      v    = this.pins.solution('v');
      omega    = this.pins.solution('omega');
      lambda    = this.pins.solution('lambda');
      p    = this.pins.solution('p');
      b    = this.pins.solution('b');
      %
      subplot( 4, 1, 1 );
      plot( zeta, v, 'Linewidth', 2 );
      legend('v') ;
      %
      subplot( 4, 1, 2 );
      plot( zeta, lambda, 'Linewidth', 2 );
      legend('lambda') ;
      %
      subplot( 4, 1, 3 );
      hold on
      plot( zeta, p, 'Linewidth', 2 );
      plot( zeta, b, 'Linewidth', 2 );
      hold off
      legend('p','b') ;
      %
      subplot( 4, 1, 4 );
      hold on
      title('Controls') ;
      this.pins.plot_controls();
      % legend('');
      hold off

      % initialize figures
      figure('WindowStyle', 'Docked','Name','Slip-Force')
      subplot( 1, 2, 1 );
      hold on
      plot(-0.3:0.01:0.3, this.pins.F__x(-0.3:0.01:0.3) , 'r', 'Linewidth', 2 )
      this.plot2('lambda','F__x', 'b*', 'Linewidth', 2 )
      hold off
      subplot( 1, 2, 2 );
      hold on
      this.plot2('omega','TT__env', 'r', 'Linewidth', 2 )
      this.plot2('omega','BT__env', 'g', 'Linewidth', 2 )
      this.plot2('omega','TT', 'b', 'Linewidth', 2 )
      this.plot2('omega','TB', 'c', 'Linewidth', 2 )
      plot(this.pins.solution('omega'), this.pins.solution('TT')+this.pins.solution('TB'), 'b-.' ,'Linewidth', 2)
      legend('Traction Envelope','Braking Envelope', 'Traction Torque', 'Braking Torque', 'DIFF') ;
      hold off
    end
    %
    function plot2(this,x_str,y_str,varargin)
      plot(this.pins.solution(x_str),this.pins.solution(y_str),varargin{:})
    end
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
%     %
%     %     _
%     %  _ | |_  _ _ __  _ __
%     % | || | || | '  \| '_ \
%     %  \__/ \_,_|_|_|_| .__/
%     %                 |_|
%     %
%     function ODE = jump( this, nsegL, t, XL, XR )
%       ODE = this.jump_standard(tL, tR, XL, XR );
%     end
%     %
%     function JAC = jump_jacobian( ~, nsegL, t, XL, XR )
%       JAC = this.jump_jacobian_standard( tL, tR, XL, XR );
%     end
%     %
%     function H = jump_hessian( ~, nsegL, t, XL, XR, L )
%       H = this.jump_hessian_standard( tL, tR, XL, XR, L );
%     end
    %
  end
end

