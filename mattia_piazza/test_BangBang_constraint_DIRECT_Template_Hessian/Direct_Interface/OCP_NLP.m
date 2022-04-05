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

classdef (Abstract) OCP_NLP < handle

  properties (SetAccess = protected, Hidden = true)
    nodes
    N    % total number of nodes
    nx   % number of states
    nu   % number of controls
    np   % number of parameters
    nbc  % number of boundary conditions
    nseg % number of segments
    npc  % number of path constraints
  end

  methods (Abstract)
    % Lagrange target
    % nseg = number of the segment
    % tL   = left node
    % tR   = right node
    % XL   = left state
    % XR   = right state
    % UC   = control like state 
    % PARS = free parameters 
    L     = lagrange( this, nseg, tL, tR, XL, XR, UC, PARS )
    gradL = lagrange_gradient( this, nseg, tL, tR, XL, XR, UC, PARS )
    hessL = lagrange_hessian( this, nseg, tL, tR, XL, XR, UC, PARS )

    % Mayer target
    M     = mayer( this, tL, tR, XL, XR, PARS )
    gradM = mayer_gradient( this, tL, tR, XL, XR, PARS )
    hessM = mayer_hessian( this, tL, tR, XL, XR, PARS )

    % Dynamical system part
    C   = ds( this, nseg, tL, tR, XL, XR, UC, PARS )
    CJ  = ds_jacobian( this, nseg, tL, tR, XL, XR, UC, PARS )
    CH  = ds_hessian( this, nseg, tL, tR, XL, XR, UC, PARS, L )

    % Path constraints
    C  = pc( this, t, X, PARS )
    CJ = pc_jacobian( this, t, X, PARS )
    CH = pc_hessian( this, t, X, PARS, L )

    % Jump condition
    % nsegL = number of the left segment, the right segment is nsegL+1
    jmp  = jump( this, nsegL, t, XL, XR, PARS )
    jmpJ = jump_jacobian( this, nsegL, t, XL, XR, PARS )
    jmpH = jump_hessian( this, nsegL, t, XL, XR, PARS, L )

    % Boundary conditions
    bcf = bc( this, tL, tR, XL, XR, PARS )
    bcJ = bc_jacobian( this, tL, tR, XL, XR, PARS )
    bcH = bc_hessian( this, tL, tR, XL, XR, PARS, L )

    % tvU
    tvU = TVU( this, tL, tC, tR, UCL, UCR )
    tvG = TVU_gradient( this, tL, tC, tR, UCL, UCR )
    tvH = TVU_hessian( this, tL, tC, tR, UCL, UCR )
  end

  methods
    %
    % nx  = number of states
    % nu  = number of controls
    % np  = number of free parameters
    % npc = number of path constraints
    % nbc = number of boundary conditions
    %
    function this = OCP_NLP( nx, nu, np, npc, nbc )
      this.nx   = nx ;
      this.nu   = nu ;
      this.np   = np ;
      this.npc  = npc ;
      this.nbc  = nbc ;
      this.nseg = 1 ;
    end

    function setup( this, nodes )
      this.nodes = nodes;
      this.N     = length(nodes) ;
    end
    
    %  _                     _
    % | |_ __ _ _ _ __ _ ___| |_
    % |  _/ _` | '_/ _` / -_)  _|
    %  \__\__,_|_| \__, \___|\__|
    %              |___/
    %
    function res = NLP_target( this, Z )
      %
      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      idx  = 1:this.nx ;
      idx1 = (totx-this.nx)+(1:this.nx) ;
      idp  = (totx+totu)+(1:this.np) ;
      res  = this.mayer( this.nodes(1), this.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      idu  = totx+(1:this.nu) ;
      nsg  = 0 ; % segment number
      for k=1:this.N-1
        nk   = this.nodes(k) ;
        nk1  = this.nodes(k+1) ;
        idx1 = idx + this.nx ; 
        res  = res + this.lagrange( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ; % * (nk1 - nk)
        idu  = idu + this.nu ;
        idx  = idx1 ;
      end
      % variation for controls
      idu = totx+(1:this.nu) ;
      for k=2:this.N-1
        nk0  = this.nodes(k-1) ;
        nk1  = this.nodes(k)   ;
        nk2  = this.nodes(k+1) ;
        idu1 = idu+this.nu ;
        res  = res + this.TVU( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu  = idu1 ;
      end
    end
    %
    function g = NLP_target_gradient( this, Z )
      %
      totx  = this.N*this.nx ;
      totu  = (this.N-1)*this.nu ;
      idx   = 1:this.nx ;
      idx1  = (totx-this.nx)+(1:this.nx) ;
      idp   = (totx+totu)+(1:this.np) ;
      %
      g     = zeros( 1, totx + totu + this.np ) ;
      id    = [idx,idx1,idp] ;
      g(id) = this.mayer_gradient( this.nodes(1), this.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      idu   = totx+(1:this.nu) ;
      nsg   = 0 ; % segment number
      for k=1:this.N-1
        nk    = this.nodes(k) ;
        nk1   = this.nodes(k+1) ;
        idx1  = idx + this.nx ;
        id    = [ idx, idx1, idu, idp ] ;
        g(id) = g(id) + this.lagrange_gradient( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        idx   = idx1 ;
        idu   = idu + this.nu ;
      end
      % variation for controls
      idu = totx+(1:this.nu) ;
      for k=2:this.N-1
        nk0   = this.nodes(k-1) ;
        nk1   = this.nodes(k)   ;
        nk2   = this.nodes(k+1) ;
        idu1  = idu+this.nu ;
        id    = [ idu, idu1 ] ;
        g(id) = g(id) + this.TVU_gradient( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu   = idu1 ;
      end
    end
    %
    %  _  _           _
    % | || |___ _____(_)__ _ _ _
    % | __ / -_|_-<_-< / _` | ' \
    % |_||_\___/__/__/_\__,_|_||_|
    %
    function H = NLP_hessian( this, Z, sigma, lambda )
      %
      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      H    = sparse( totx+totu, totx+totu ) ;
      %
      idx  = 1:this.nx ;
      idx1 = (totx-this.nx)+(1:this.nx) ;
      idp  = (totx+totu)+(1:this.np) ;
      idl  = (this.nx*(this.N-1))+(1:this.nbc);
      %
      imap = [ idx, idx1, idp ] ;
      n1   = this.nodes(1) ;
      ne   = this.nodes(end) ;
      H(imap,imap) = sigma * this.mayer_hessian( n1, ne, Z(idx), Z(idx1), Z(idp) ) + ...
                     this.bc_hessian( n1, ne, Z(idx), Z(idx1), Z(idp), lambda(idl) ) ;
      idu = totx+(1:this.nu) ;

      idl = 1:(this.nx+this.npc) ;
      nsg = 0 ; % segment number
      for k=1:this.N-1
        nk   = this.nodes(k) ;
        nk1  = this.nodes(k+1) ;
        idx1 = idx + this.nx ;
        idl1  = idl + this.nx+this.npc;
        imap = [ idx, idx1, idu, idp ] ;
        H(imap,imap) = H(imap,imap) + ...
                       sigma * this.lagrange_hessian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) + ...
                       this.ds_hessian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp), lambda(idl) ) ;
        idx = idx1 ;
        idu = idu + this.nu ;
        idl   = idl1;
      end
      % variation for controls
      idu = totx+(1:this.nu) ;
      for k=2:this.N-1
        nk0   = this.nodes(k-1) ;
        nk1   = this.nodes(k)   ;
        nk2   = this.nodes(k+1) ;
        idu1  = idu+this.nu ;
        id    = [ idu, idu1 ] ;
        H(id,id) = H(id,id) + sigma * this.TVU_hessian( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu   = idu1 ;
      end
      H = tril(H) ;
    end

    function H = NLP_hessian_pattern( this )
      %
      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      H    = sparse( totx + totu, totx + totu ) ;
      imap = [1:this.nx, (totx-this.nx)+(1:this.nx) ] ;
      H(imap,imap) = ones(2*this.nx,2*this.nx);
      %
      idp = (totx+totu)+(1:this.np) ;
      dim = 2*this.nx+this.nu+this.np ;
      nsg = 0 ; % segment number
      for k=1:this.N-1
        idx  = (k-1)*this.nx ;
        idu  = (k-1)*this.nu + totx ;
        imap = [ idx+(1:2*this.nx), idu+(1:this.nu), idp ] ;
        H(imap,imap) = ones( dim, dim ) ;
      end
      % variation for controls
      idu = totx+(1:this.nu) ;
      for k=2:this.N-1
        idu1  = idu+this.nu ;
        id    = [ idu, idu1 ] ;
        H(id,id) = 1 ;
        idu   = idu1 ;
      end
      H = tril(H) ;
    end
    %

    %   ___             _            _     _
    %  / __|___ _ _  __| |_ _ _ __ _(_)_ _| |_ ___
    % | (__/ _ \ ' \(_-<  _| '_/ _` | | ' \  _(_-<
    %  \___\___/_||_/__/\__|_| \__,_|_|_||_\__/__/
    %
    function C = NLP_constraints( this, Z )
      %
      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      idx  = 1:this.nx ;
      idu  = totx+(1:this.nu) ;
      idp  = (totx+totu)+(1:this.np) ;

      idxc = 1:(this.nx+this.npc) ;

      C = zeros( (this.N-1)*this.nx + (this.N-1)*this.npc + this.nbc, 1 ) ;

      nsg = 0 ; % segment number
      for k=1:this.N-1
        nk     = this.nodes(k) ;
        nk1    = this.nodes(k+1) ;
        idxc1  = idxc + this.nx+this.npc;
        idx1   = idx + this.nx ;
        C(idxc) = this.ds( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        idx    = idx1 ;
        idxc   = idxc1;

        idu    = idu + this.nu ;
      end
      idx   = 1:this.nx ;
      id    = ((this.N-1)*this.nx + (this.N-1)*this.npc)+(1:this.nbc) ;
      C(id) = this.bc( this.nodes(1), this.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
    end

    % -------
    function Jac = NLP_constraints_jacobian( this, Z )

      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      totc = (this.N-1)*this.npc ;
      idx  = 1:this.nx ;
      idu  = totx+(1:this.nu) ;
      idp  = (totx+totu)+(1:this.np) ;

      idxc = 1:(this.nx+this.npc) ;

      dim  = (this.N-1)*this.nx+(this.N-1)*this.npc+this.nbc ;
      Jac  = sparse( dim, totx+totu+this.np ) ;

      nsg = 0 ; % segment number
      for k=1:this.N-1
        nk    = this.nodes(k) ;
        nk1   = this.nodes(k+1) ;
        idxc1 = idxc + this.nx+this.npc;
        idx1  = idx + this.nx ;
        J     = this.ds_jacobian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        Jac( idxc, [ idx, idx1, idu, idp ] ) = J ;
        idu   = idu + this.nu ;
        idx   = idx1 ;
        idxc  = idxc1;
      end
      idx = 1:this.nx ;
      J = this.bc_jacobian( this.nodes(1), this.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      imap = [ (this.N-1)*this.nx+(this.N-1)*this.npc + (1:this.nbc) ] ;
      jmap = [ idx, idx1, idp ] ;
      Jac(imap,jmap) = Jac(imap,jmap) + J ;
    end

    % -------
    function Jac = NLP_constraints_jacobian_pattern( this )
      totx = this.N*this.nx ;
      totu = (this.N-1)*this.nu ;
      totc = (this.N-1)*this.npc ;

      idx  = 1:this.nx ;
      idu  = totx+(1:this.nu) ;
      idp  = (totx+totu)+(1:this.np) ;
      idxc = 1:(this.nx+this.npc) ;

      dimC = (this.N-1)*this.nx+(this.N-1)*this.npc+this.nbc ;
      dimZ = totx+totu+this.np ;
      Jac  = sparse( dimC, dimZ ) ;
      J    = ones(this.nx+this.npc,2*this.nx+this.nu+this.np) ;
      idp  = totx + totu + (1:this.np) ;
      nsg  = 1 ; % segment number
      for k=1:this.N-1
        nk    = this.nodes(k) ;
        nk1   = this.nodes(k+1) ;
        idxc1 = idxc + this.nx+this.npc;
        idx1  = idx + this.nx ;
        % imap = idxc;
        % jmap = [ idx + (1:2*this.nx), idu + (1:this.nu), idp  ] ;
        Jac(idxc, [ idx, idx1, idu, idp ]) = J ;
        idu   = idu + this.nu ;
        idx   = idx1 ;
        idxc  = idxc1;
      end
      imap = [(this.N-1)*this.nx+(this.N-1)*this.npc + (1:this.nbc) ] ;
      jmap = [ 1:this.nx, totx-this.nx+(1:this.nx), idp ] ;
      Jac(imap,jmap) = ones(this.nbc,2*this.nx+this.np)  ;
    end

    %  _   _ _   _ _
    % | | | | |_(_) |___
    % | |_| |  _| | (_-<
    %  \___/ \__|_|_/__/
    %
    function H = FD_ds_hessian( this, nseg, tL, tR, XL, XR, UC, PARS, L )
      N = 2*this.nx+this.nu+this.np ;

      id1 = 1:this.nx ;
      id2 = this.nx+id1 ;
      id3 = 2*this.nx+(1:this.nu) ;
      id4 = 2*this.nx+this.nu+(1:this.np) ;

      GRAD = @(W) this.ds_jacobian( nseg, tL, tR, XL+W(id1), XR+W(id2), UC+W(id3), PARS+W(id4)).' * L ;

      % finite difference approximation of the hessian
      % Baseed on a code by Brendan C. Wood
      % Copyright (c) 2011, Brendan C. Wood <b.wood@unb.ca>
      H = zeros(N,N);
      h = max(1,abs([XL;XR;UC;PARS]))*eps^(1/3); % ricetta di cucina
      for i=1:N
        % derivative at first point (left)
        x1    = zeros(N,1);
        x1(i) = - h(i) ;
        df1   = GRAD(x1);
        
        % derivative at second point (right)
        x2    = zeros(N,1);
        x2(i) = h(i);
        df2   = GRAD(x2);
        
        % differentiate between the two derivatives
        d2f = (df2-df1) ./ (2*h(i));
        
        % assign as column i of Hessian
        H(:,i) = d2f;
      end
      H = 0.5*(H+H.');      
    end

    %     _
    %  _ | |_  _ _ __  _ __
    % | || | || | '  \| '_ \
    %  \__/ \_,_|_|_|_| .__/
    %                 |_|
    %
    function ODE = jump_standard( ~, nsegL, t, XL, XR, UC )
      ODE = XR - XL ;
    end

    %
    function JAC = jump_standard_jacobian( ~, nsegL, t, XL, XR, UC )
      JAC = [ -eye(this.nx,this.nx), ...
               eye(this.nx,this.nx), ...
               zeros(this.nx, this.nu+this.np) ] ;
    end

    %
    function H = jump_standard_hessian( ~, nsegL, t, XL, XR, UC, L )
      dim = 2*this.nx+this.nu+this.np ;
      H   = zeros(dim,dim) ;
    end

    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    % tvU
    function tvU = TVU_standard( this, tL, tC, tR, UCL, UCR )
      tvU = 0 ;
    end

    function tvG = TVU_standard_gradient( this, tL, tC, tR, UCL, UCR )
      tvG = zeros(1,2*this.nu) ;
    end

    function tvH = TVU_standard_hessian( this, tL, tC, tR, UCL, UCR )
      tvH = zeros(2*this.nu,2*this.nu) ;      
    end

    %        _    _           _     _
    %  _ __ (_)__| |_ __  ___(_)_ _| |_
    % | '  \| / _` | '_ \/ _ \ | ' \  _|
    % |_|_|_|_\__,_| .__/\___/_|_||_\__|
    %              |_|
    %     
    function C = midpoint_ds( this, nseg, tL, tR, XL, XR, UC, PARS, RHS )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      C  = (XR-XL)/(tR-tL) - feval( RHS, nseg, tM, XM, UC, PARS ) ;
    end
 
    function CJ = midpoint_ds_jacobian( this, nseg, tL, tR, XL, XR, UC, PARS, JAC )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      JJ = feval( JAC, nseg, tM, XM, UC, PARS ) ;
      B1 = (-0.5)*JJ(1:this.nx,1:this.nx) ;
      B2 = JJ(1:this.nx,this.nx+1:end) ;
      bf = 1/(tR - tL) ;
      CJ = [ B1-bf*eye(this.nx), B1+bf*eye(this.nx), -B2 ] ;
    end

    function CH = midpoint_ds_hessian( this, nseg, tL, tR, XL, XR, UC, PARS, L, HESS )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      HH = feval( HESS, nseg, tM, XM, UC, PARS, L ) ;
      D1 = (-0.25)*HH(1:this.nx,1:this.nx) ;
      R1 = (-0.5)*HH(1:this.nx,this.nx+1:end) ;
      D2 = -HH(this.nx+1:end,this.nx+1:end) ;
      CH = [ D1,   D1,   R1 ; ...
             D1,   D1,   R1 ; ...
             R1.', R1.', D2 ] ;
    end
  end
end
