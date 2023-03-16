classdef PINS_NewtonSolver < handle
  %% MATLAB class wrapper for the underlying C++ class
  properties (SetAccess = private, Hidden = true)
    tolerance;
    iter;
    max_iterations;
    ierr;

    selected_merit;

    x0;
    f0;
    J0;
    d0;
    mu;

    c1;

    L;
    U;
    P;
    Q;
    cosa;
    minimize;

    f_eval;
    j_eval;
    ck_eval;
  end

  methods

    function self = PINS_NewtonSolver( selected_merit )
      self.tolerance      = 1e-8 ;
      self.max_iterations = 100 ;
      self.c1             = 0.001;
      self.selected_merit = selected_merit;
    end

    function delete( ~ )
      %% Destroy the C++ class instance
    end

    function set_max_iter( self, miter )
      self.max_iterations = miter;
    end

    %  ____                      _ _
    % / ___| _ __ ___   ___ _ __(_) |_
    % \___ \| '_ ` _ \ / _ \ '__| | __|
    %  ___) | | | | | |  __/ |  | | |_
    % |____/|_| |_| |_|\___|_|  |_|\__|
    %
    function m = Smerit( self, alpha )
      f = feval( self.f_eval, self.x0 + alpha * self.d0 ) ;
      e = self.tolerance ;
      m = sum( f.^2 ./ sqrt(f.^2+e) ) ;
    end

    function m0 = Smerit0( self )
      f  = self.f0 ;
      e  = self.tolerance ;
      m0 = sum( f.^2 ./ sqrt(f.^2+e) ) ;
    end

    function Dm0 = Smerit0_D( self )
      f   = self.f0 ;
      e   = self.tolerance ;
      tmp = f.^2+e ;
      Dm0 = - sum( (1+e./tmp).*(f.^2./sqrt(tmp)) ) ;
    end
    %       _                     _ _
    %      | |_ __ ___   ___ _ __(_) |_
    %   _  | | '_ ` _ \ / _ \ '__| | __|
    %  | |_| | | | | | |  __/ |  | | |_
    %   \___/|_| |_| |_|\___|_|  |_|\__|
    %
    function m = Jmerit( self, alpha )
      fa = feval( self.f_eval, self.x0 + alpha * self.d0 ) ;
      d  = -self.Jsolve(fa);
      e  = self.tolerance ;
      m  = sum( d.^2 ./ sqrt(d.^2+e) ) ;
    end

    function m0 = Jmerit0( self )
      d  = self.d0 ;
      e  = self.tolerance ;
      m0 = sum( d.^2 ./ sqrt(d.^2+e) ) ;
    end

    function Dm0 = Jmerit0_D( self )
      d   = self.d0 ;
      e   = self.tolerance ;
      tmp = d.^2+e ;
      Dm0 = - sum( (1+e./tmp).*(d.^2./sqrt(tmp)) ) ;
    end

    %  _   _ ____                      _ _
    % | \ | |___ \ _ __ ___   ___ _ __(_) |_
    % |  \| | __) | '_ ` _ \ / _ \ '__| | __|
    % | |\  |/ __/| | | | | |  __/ |  | | |_
    % |_| \_|_____|_| |_| |_|\___|_|  |_|\__|
    %
    function m = N2merit( self, alpha )
      fa = feval( self.f_eval, self.x0 + alpha * self.d0 ) ;
      m  = 0.5*dot( fa, fa ) ;
    end

    function m0 = N2merit0( self )
      m0 = 0.5*dot(self.f0,self.f0) ;
    end

    function Dm0 = N2merit0_D( self )
      Dm0 = -dot(self.f0,self.f0) ;
    end

    %     _    ___                     _ _
    %    / \  |_ _|_ __ ___   ___ _ __(_) |_
    %   / _ \  | || '_ ` _ \ / _ \ '__| | __|
    %  / ___ \ | || | | | | |  __/ |  | | |_
    % /_/   \_\___|_| |_| |_|\___|_|  |_|\__|
    %
    function m = AImerit( self, alpha )
      fa = feval( self.f_eval, self.x0 + alpha * self.d0 ) ;
      d  = -self.Jsolve(fa);
      m  = 0.5*dot( d, d ) ;
    end

    function m0 = AImerit0( self )
      m0 = 0.5*dot(self.d0,self.d0) ;
    end

    function Dm0 = AImerit0_D( self )
      Dm0 = -dot(self.d0,self.d0) ;
    end

    %   ___                      _ _
    %  / _ \ _ __ ___   ___ _ __(_) |_
    % | | | | '_ ` _ \ / _ \ '__| | __|
    % | |_| | | | | | |  __/ |  | | |_
    %  \___/|_| |_| |_|\___|_|  |_|\__|
    %
    function m = Omerit( self, alpha )
      fa = feval( self.f_eval, self.x0 + alpha * self.d0 ) ;
      d  = -self.Jsolve(fa);
      e  = self.tolerance ;
      m  = sum( (self.d0.*d) ./ sqrt(e+self.d0.^2) )^2 ;
    end

    function m0 = Omerit0( self )
      e  = self.tolerance ;
      m0 = sum( self.d0.^2 ./ sqrt(e+self.d0.^2) )^2 ;
    end

    function Dm0 = Omerit0_D( self )
      e   = self.tolerance ;
      bf  = sum( self.d0.^2 ./ sqrt(e+self.d0.^2) ) ;
      Dm0 = -2*bf^2 ;
    end

    %                      _ _
    %  _ __ ___   ___ _ __(_) |_
    % | '_ ` _ \ / _ \ '__| | __|
    % | | | | | |  __/ |  | | |_
    % |_| |_| |_|\___|_|  |_|\__|
    %
    function m = merit( self, alpha )
      switch self.selected_merit
      case 1
        m = self.Smerit( alpha ) ;
      case 2
        m = self.Jmerit( alpha ) ;
      case 3
        m = self.N2merit( alpha ) ;
      case 4
        m = self.AImerit( alpha ) ;
      case 5
        m = self.Omerit( alpha ) ;
      end
    end

    function m0 = merit0( self )
      switch self.selected_merit
      case 1
        m0 = self.Smerit0() ;
      case 2
        m0 = self.Jmerit0() ;
      case 3
        m0 = self.N2merit0() ;
      case 4
        m0 = self.AImerit0() ;
      case 5
        m0 = self.Omerit0() ;
      end
    end

    function Dm0 = merit0_D( self )
      switch self.selected_merit
      case 1
        Dm0 = self.Smerit0_D() ;
      case 2
        Dm0 = self.Jmerit0_D() ;
      case 3
        Dm0 = self.N2merit0_D() ;
      case 4
        Dm0 = self.AImerit0_D() ;
      case 5
        Dm0 = self.Omerit0_D() ;
      end
    end

    function res = Jsolve( self, fa )
      res = self.Q*(self.U\(self.L\(self.P*fa)));
    end

    function setDirection( self )
      [self.L,self.U,self.P,self.Q] = lu(self.J0); % A = P'*L*U*Q'
      self.d0 = -self.Jsolve(self.f0);
    end

    function [xk,ierr] = solve( self, xinit, fun, jac, check )

      self.f_eval  = fun;
      self.j_eval  = jac;
      self.ck_eval = check;
      self.iter    = 0;

      self.x0 = xinit;
      xk      = xinit;
      zold    = xinit;
      for k=1:self.max_iterations
        self.iter = k;

        % evaluate merit function and gradient
        if ~feval( self.ck_eval, self.x0 )
          disp(self.c0);
          fprintf(1, 'NewtonSolver: Bad point!\n' );
          ierr = 2;
          return;
        end

        self.f0 = feval( self.f_eval, self.x0 );
        self.J0 = feval( self.j_eval, self.x0 );

        if ~all(isfinite(self.f0)) %| ~all(isfinite(self.J0))
          disp(self.f0);
          fprintf(1, 'NewtonSolver: Bad f(x)!\n' );
          ierr = 2;
          return;
        end

        % direction search
        self.setDirection();

        normi_f = norm( self.f0, inf );
        normi_d = norm( self.d0, inf );

        % do line search
        if self.selected_merit == 0
          alpha = self.max_step();
        else
          alpha = self.linesearch();
        end
        if ~isfinite(alpha)
          ierr = 3;
          return;
        end

        fprintf('iter %3d |f| = %8g |d| = %8g alpha = %5g\n',...
                k, normi_f, normi_d, alpha );

        % check if finished
        if normi_d < self.tolerance || normi_f < self.tolerance^2
          fprintf('iter %3d |f| = %8g |d| = %8g (CONVERGED)\n', ...
                  k, normi_f, normi_d);
          ierr = 0;
          return;
        end

        self.x0 = self.x0 + alpha * self.d0;
        xk      = self.x0;

        if ~feval( self.ck_eval, self.x0 )
          ierr = 7;
          return;
        end

      end
      ierr = 1;
    end

    function it = iterations( self )
      it = self.iter;
    end

    function lambda = max_step( self )
      lambda = 1;
      mul    = 1.5;
      for k=1:20
        x1 = self.x0 + lambda * self.d0;
        if feval( self.ck_eval, x1 )
          f1 = feval( self.f_eval, x1 );
          if all(isfinite(f1))
            %d1 = -self.Jsolve(f1);
            %if all(isfinite(d1))
            %  if norm(d1) < 1.5*norm(self.d0)
                break;
            %  end
            %end
          end
        end
        lambda = lambda/mul;
        mul    = mul*1.2;
      end
    end

    function lambda = linesearch( self )
      lambda = 1;
      mul    = 1.5;
      m0     = self.merit0();
      Dm0    = self.merit0_D();
      for k=1:20
        x1 = self.x0 + lambda * self.d0;
        if feval( self.ck_eval, x1 )
          m = self.merit( lambda );
          if isfinite(m)
            if m < m0+lambda*self.c1*Dm0 ; return ; end
          end
        end
        lambda = lambda/mul;
        mul    = mul*1.2;
      end
      fprintf('Linesearch failed! lambda = %g\n',lambda);
    end

  end
end
