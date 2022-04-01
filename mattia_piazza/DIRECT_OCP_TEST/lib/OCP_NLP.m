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
    L     = lagrange( self, nseg, tL, tR, XL, XR, UC, PARS )
    gradL = lagrange_gradient( self, nseg, tL, tR, XL, XR, UC, PARS )
    hessL = lagrange_hessian( self, nseg, tL, tR, XL, XR, UC, PARS )

    % Mayer target
    M     = mayer( self, tL, tR, XL, XR, PARS )
    gradM = mayer_gradient( self, tL, tR, XL, XR, PARS )
    hessM = mayer_hessian( self, tL, tR, XL, XR, PARS )

    % Dynamical system part
    C   = ds( self, nseg, tL, tR, XL, XR, UC, PARS )
    CJ  = ds_jacobian( self, nseg, tL, tR, XL, XR, UC, PARS )
    CH  = ds_hessian( self, nseg, tL, tR, XL, XR, UC, PARS, L )

    % Path constraints
    C  = pc( self, t, X, PARS )
    CJ = pc_jacobian( self, t, X, PARS )
    CH = pc_hessian( self, t, X, PARS, L )

    % Jump condition
    % nsegL = number of the left segment, the right segment is nsegL+1
    jmp  = jump( self, nsegL, t, XL, XR, PARS )
    jmpJ = jump_jacobian( self, nsegL, t, XL, XR, PARS )
    jmpH = jump_hessian( self, nsegL, t, XL, XR, PARS, L )

    % Boundary conditions
    bcf = bc( self, tL, tR, XL, XR, PARS )
    bcJ = bc_jacobian( self, tL, tR, XL, XR, PARS )
    bcH = bc_hessian( self, tL, tR, XL, XR, PARS, L )

    % tvU
    tvU = TVU( self, tL, tC, tR, UCL, UCR )
    tvG = TVU_gradient( self, tL, tC, tR, UCL, UCR )
    tvH = TVU_hessian( self, tL, tC, tR, UCL, UCR )
  end

  methods
    %
    % nx  = number of states
    % nu  = number of controls
    % np  = number of free parameters
    % npc = number of path constraints
    % nbc = number of boundary conditions
    %
    function self = OCP_NLP( nx, nu, np, npc, nbc )
      self.nx   = nx ;
      self.nu   = nu ;
      self.np   = np ;
      self.npc  = npc ;
      self.nbc  = nbc ;
      self.nseg = 1 ;
    end

    function setup( self, nodes )
      self.nodes = nodes;
      self.N     = length(nodes) ;
    end
    
    %  _                     _
    % | |_ __ _ _ _ __ _ ___| |_
    % |  _/ _` | '_/ _` / -_)  _|
    %  \__\__,_|_| \__, \___|\__|
    %              |___/
    %
    function res = NLP_target( self, Z )

      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;

      idx  = 1:self.nx ;
      idx1 = (totx-self.nx)+(1:self.nx) ;
      idp  = (totx+totu)+(1:self.np) ;

      res = self.mayer( self.nodes(1), self.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      idu = totx+(1:self.nu) ;
      nsg = 1 ; % segment number
      for k=1:self.N-1
        nk   = self.nodes(k) ;
        nk1  = self.nodes(k+1) ;
        idx1 = idx + self.nx ; 
        res  = res + self.lagrange( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        idu  = idu + self.nu ;
        idx  = idx1 ;
      end
      % variation for controls
      idu = totx+(1:self.nu) ;
      for k=2:self.N-1
        nk0  = self.nodes(k-1) ;
        nk1  = self.nodes(k)   ;
        nk2  = self.nodes(k+1) ;
        idu1 = idu+self.nu ;
        res  = res + self.TVU( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu  = idu1 ;
      end
    end

    %
    function g = NLP_target_gradient( self, Z )

      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      
      idx  = 1:self.nx ;
      idx1 = (totx-self.nx)+(1:self.nx) ;
      idp  = (totx+totu)+(1:self.np) ;
      
      g = zeros( 1, totx + totu + self.np ) ;
      g([idx,idx1,idp]) = self.mayer_gradient( self.nodes(1), self.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      idu = totx+(1:self.nu) ;
      nsg = 1 ; % segment number
      for k=1:self.N-1
        nk    = self.nodes(k) ;
        nk1   = self.nodes(k+1) ;
        idx1  = idx + self.nx ;
        id    = [ idx, idx1, idu, idp ] ;
        g(id) = g(id) + self.lagrange_gradient( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        idx   = idx1 ;
        idu   = idu + self.nu ;
      end
      % variation for controls
      idu = totx+(1:self.nu) ;
      for k=2:self.N-1
        nk0   = self.nodes(k-1) ;
        nk1   = self.nodes(k)   ;
        nk2   = self.nodes(k+1) ;
        idu1  = idu+self.nu ;
        id    = [ idu, idu1 ] ;
        g(id) = g(id) + self.TVU_gradient( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu   = idu1 ;
      end
      %g = [ cell2mat(gx), cell2mat(gu), gp ] ;
    end

    %  _  _           _
    % | || |___ _____(_)__ _ _ _
    % | __ / -_|_-<_-< / _` | ' \
    % |_||_\___/__/__/_\__,_|_||_|
    %
    function H = NLP_hessian( self, Z, sigma, lambda )

      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      H    = sparse( totx+totu, totx+totu ) ;

      idx  = 1:self.nx ;
      idx1 = (totx-self.nx)+(1:self.nx) ;
      idp  = (totx+totu)+(1:self.np) ;
      idl  = (self.nx*(self.N-1))+(1:self.nbc);

      imap = [ idx, idx1, idp ] ;
      n1   = self.nodes(1) ;
      ne   = self.nodes(end) ;
      H(imap,imap) = sigma * self.mayer_hessian( n1, ne, Z(idx), Z(idx1), Z(idp) ) + ...
                     self.bc_hessian( n1, ne, Z(idx), Z(idx1), Z(idp), lambda(idl) ) ;
      idu = totx+(1:self.nu) ;
      nsg = 1 ; % segment number
      for k=1:self.N-1
        nk   = self.nodes(k) ;
        nk1  = self.nodes(k+1) ;
        idx1 = idx + self.nx ;
        imap = [ idx, idx1, idu, idp ] ;
        H(imap,imap) = H(imap,imap) + ...
                       sigma * self.lagrange_hessian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) + ...
                       self.ds_hessian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp), lambda(idx) ) ;
        idx = idx1 ;
        idu = idu + self.nu ;
      end
      % variation for controls
      idu = totx+(1:self.nu) ;
      for k=2:self.N-1
        nk0   = self.nodes(k-1) ;
        nk1   = self.nodes(k)   ;
        nk2   = self.nodes(k+1) ;
        idu1  = idu+self.nu ;
        id    = [ idu, idu1 ] ;
        H(id,id) = H(id,id) + sigma * self.TVU_hessian( nk0, nk1, nk2, Z(idu), Z(idu1) ) ;
        idu   = idu1 ;
      end
      H = tril(H) ;
    end

    function H = NLP_hessian_pattern( self )
      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      H    = sparse( totx + totu, totx + totu ) ;
      imap = [1:self.nx, (totx-self.nx)+(1:self.nx) ] ;
      H(imap,imap) = ones(2*self.nx,2*self.nx);

      idp = (totx+totu)+(1:self.np) ;
      dim = 2*self.nx+self.nu+self.np ;
      nsg = 1 ; % segment number
      for k=1:self.N-1
        idx  = (k-1)*self.nx ;
        idu  = (k-1)*self.nu + totx ;
        imap = [ idx+(1:2*self.nx), idu+(1:self.nu), idp ] ;
        H(imap,imap) = ones( dim, dim ) ;
      end
      % variation for controls
      idu = totx+(1:self.nu) ;
      for k=2:self.N-1
        idu1  = idu+self.nu ;
        id    = [ idu, idu1 ] ;
        H(id,id) = 1 ;
        idu   = idu1 ;
      end
      H = tril(H) ;
    end

    %   ___             _            _     _
    %  / __|___ _ _  __| |_ _ _ __ _(_)_ _| |_ ___
    % | (__/ _ \ ' \(_-<  _| '_/ _` | | ' \  _(_-<
    %  \___\___/_||_/__/\__|_| \__,_|_|_||_\__/__/
    %
    function C = NLP_constraints( self, Z )

      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      idx  = 1:self.nx ;
      idu  = totx+(1:self.nu) ;
      idp  = (totx+totu)+(1:self.np) ;

      C = zeros( (self.N-1)*self.nx + self.nbc, 1 ) ;

      nsg = 1 ; % segment number
      for k=1:self.N-1
        nk     = self.nodes(k) ;
        nk1    = self.nodes(k+1) ;
        idx1   = idx + self.nx ;
        C(idx) = self.ds( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        idx    = idx1 ;
        idu    = idu + self.nu ;
      end
      idx   = 1:self.nx ;
      id    = ((self.N-1)*self.nx)+(1:self.nbc) ;
      C(id) = self.bc( self.nodes(1), self.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
    end

    % -------
    function Jac = NLP_constraints_jacobian( self, Z )

      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      idx  = 1:self.nx ;
      idu  = totx+(1:self.nu) ;
      idp  = (totx+totu)+(1:self.np) ;

      dim  = (self.N-1)*self.nx+self.nbc ;
      Jac  = sparse( dim, totx+totu+self.np ) ;

      nsg = 1 ; % segment number
      for k=1:self.N-1
        nk   = self.nodes(k) ;
        nk1  = self.nodes(k+1) ;
        idx1 = idx + self.nx ;
        J    = self.ds_jacobian( nsg, nk, nk1, Z(idx), Z(idx1), Z(idu), Z(idp) ) ;
        Jac( idx, [ idx, idx1, idu, idp ] ) = J ;
        idu = idu + self.nu ;
        idx = idx1 ;
      end
      idx = 1:self.nx ;
      J = self.bc_jacobian( self.nodes(1), self.nodes(end), Z(idx), Z(idx1), Z(idp) ) ;
      imap = [ totx - self.nx + (1:self.nbc) ] ;
      jmap = [ idx, idx1, idp ] ;
      Jac(imap,jmap) = Jac(imap,jmap) + J ;
    end

    % -------
    function Jac = NLP_constraints_jacobian_pattern( self )
      totx = self.N*self.nx ;
      totu = (self.N-1)*self.nu ;
      dimC = (self.N-1)*self.nx+self.nbc ;
      dimZ = totx+totu+self.np ;
      Jac  = sparse( dimC, dimZ ) ;
      J    = ones(self.nx,2*self.nx+self.nu+self.np) ;
      idp  = totx + totu + (1:self.np) ;
      nsg  = 1 ; % segment number
      for k=1:self.N-1
        idx  = (k-1)*self.nx ;
        idu  = (k-1)*self.nu + totx ;
        imap = idx + (1:self.nx) ;
        jmap = [ idx + (1:2*self.nx), idu + (1:self.nu), idp  ] ;
        Jac(imap,jmap) = J ;
      end
      imap = totx - self.nx + (1:self.nbc) ;
      jmap = [ 1:self.nx, totx-self.nx+(1:self.nx), idp ] ;
      Jac(imap,jmap) = ones(self.nbc,2*self.nx+self.np)  ;
    end

    %  _   _ _   _ _
    % | | | | |_(_) |___
    % | |_| |  _| | (_-<
    %  \___/ \__|_|_/__/
    %
    function H = FD_ds_hessian( self, nseg, tL, tR, XL, XR, UC, PARS, L )
      N = 2*self.nx+self.nu+self.np ;

      id1 = 1:self.nx ;
      id2 = self.nx+id1 ;
      id3 = 2*self.nx+(1:self.nu) ;
      id4 = 2*self.nx+self.nu+(1:self.np) ;

      GRAD = @(W) self.ds_jacobian( nseg, tL, tR, XL+W(id1), XR+W(id2), UC+W(id3), PARS+W(id4)).' * L ;

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
      JAC = [ -eye(self.nx,self.nx), ...
               eye(self.nx,self.nx), ...
               zeros(self.nx, self.nu+self.np) ] ;
    end

    %
    function H = jump_standard_hessian( ~, nsegL, t, XL, XR, UC, L )
      dim = 2*self.nx+self.nu+self.np ;
      H   = zeros(dim,dim) ;
    end

    %  _______     __                  _             _
    % |_   _\ \   / /   ___ ___  _ __ | |_ _ __ ___ | |___
    %   | |  \ \ / /   / __/ _ \| '_ \| __| '__/ _ \| / __|
    %   | |   \ V /   | (_| (_) | | | | |_| | | (_) | \__ \
    %   |_|    \_/     \___\___/|_| |_|\__|_|  \___/|_|___/
    % tvU
    function tvU = TVU_standard( self, tL, tC, tR, UCL, UCR )
      tvU = 0 ;
    end

    function tvG = TVU_standard_gradient( self, tL, tC, tR, UCL, UCR )
      tvG = zeros(1,2*self.nu) ;
    end

    function tvH = TVU_standard_hessian( self, tL, tC, tR, UCL, UCR )
      tvH = zeros(2*self.nu,2*self.nu) ;      
    end

    %        _    _           _     _
    %  _ __ (_)__| |_ __  ___(_)_ _| |_
    % | '  \| / _` | '_ \/ _ \ | ' \  _|
    % |_|_|_|_\__,_| .__/\___/_|_||_\__|
    %              |_|
    %     
    function C = midpoint_ds( self, nseg, tL, tR, XL, XR, UC, PARS, RHS )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      C  = (XR-XL)/(tR-tL) - feval( RHS, nseg, tM, XM, UC, PARS ) ;
    end
 
    function CJ = midpoint_ds_jacobian( self, nseg, tL, tR, XL, XR, UC, PARS, JAC )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      JJ = feval( JAC, nseg, tM, XM, UC, PARS ) ;
      B1 = (-0.5)*JJ(1:self.nx,1:self.nx) ;
      B2 = JJ(1:self.nx,self.nx+1:end) ;
      bf = 1/(tR - tL) ;
      CJ = [ B1-bf*eye(self.nx), B1+bf*eye(self.nx), -B2 ] ;
    end

    function CH = midpoint_ds_hessian( self, nseg, tL, tR, XL, XR, UC, PARS, L, HESS )
      tM = (tR+tL)/2 ;
      XM = (XR+XL)./2 ;
      HH = feval( HESS, nseg, tM, XM, UC, PARS, L ) ;
      D1 = (-0.25)*HH(1:self.nx,1:self.nx) ;
      R1 = (-0.5)*HH(1:self.nx,self.nx+1:end) ;
      D2 = -HH(self.nx+1:end,self.nx+1:end) ;
      CH = [ D1,   D1,   R1 ; ...
             D1,   D1,   R1 ; ...
             R1.', R1.', D2 ] ;
    end
  end
end
