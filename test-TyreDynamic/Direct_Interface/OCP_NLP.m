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
    segments
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
    L     = lagrange( this, isegL, isegR, tL, tR, XL, XR, UC, PARS )
    gradL = lagrange_gradient( this, isegL, isegR, tL, tR, XL, XR, UC, PARS )
    hessL = lagrange_hessian( this, isegL, isegR, tL, tR, XL, XR, UC, PARS )

    % Mayer target
    M     = mayer( this, tL, tR, XL, XR, PARS )
    gradM = mayer_gradient( this, tL, tR, XL, XR, PARS )
    hessM = mayer_hessian( this, tL, tR, XL, XR, PARS )

    % Dynamical system part
%     C   = ds( this, nseg, tL, tR, XL, XR, UC, PARS )
%     CJ  = ds_jacobian( this, nseg, tL, tR, XL, XR, UC, PARS )
%     CH  = ds_hessian( this, nseg, tL, tR, XL, XR, UC, PARS, L )
    C   = ds( this, isegL, isegR, tL, tR, XL, XR, UC, PARS )
    CJ  = ds_jacobian( this, isegL, isegR, tL, tR, XL, XR, UC, PARS )
    CH  = ds_hessian( this, isegL, isegR, tL, tR, XL, XR, UC, PARS, L )

    % Path constraints
    C  = pc( this, t, X, PARS )
    CJ = pc_jacobian( this, t, X, PARS )
    CH = pc_hessian( this, t, X, PARS, L )

    % Boundary conditions
    bcf = bc( this, tL, tR, XL, XR, PARS )
    bcJ = bc_jacobian( this, tL, tR, XL, XR, PARS )
    bcH = bc_hessian( this, tL, tR, XL, XR, PARS, L )

    % tvU
    tvU = TVU( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
    tvG = TVU_gradient( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
    tvH = TVU_hessian( this, isegL, isegC, isegR, tL, tC, tR, UCL, UCR )
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

    function setup( this, nodes, segments )
      this.segments = segments;
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
        res  = res + this.lagrange( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ; % * (nk1 - nk)
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
        res  = res + this.TVU(this.segments(k-1),this.segments(k),this.segments(k+1), nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
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
        g(id) = g(id) + this.lagrange_gradient( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
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
        g(id) = g(id) + this.TVU_gradient( this.segments(k-1),this.segments(k),this.segments(k+1), nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
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
      fprintf("\n")
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
                       sigma * this.lagrange_hessian( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) + ...
                       this.ds_hessian( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp), lambda(idl) ) ;
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
        H(id,id) = H(id,id) + sigma * this.TVU_hessian( this.segments(k-1),this.segments(k),this.segments(k+1), nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
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
        C(idxc) = this.ds( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
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
        J     = this.ds_jacobian( this.segments(k), this.segments(k+1), nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
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

    

    
  end
end
