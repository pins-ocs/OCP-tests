classdef PINS_LevenbergMarquardt < handle
  properties (SetAccess = private, Hidden = true)
    tolerance;
    iter;
    max_iterations;
    ierr;

    tau;

    f_eval;
    j_eval;
    ck_eval;
  end

  methods

    function self = PINS_LevenbergMarquardt()
      self.tolerance      = 1e-12;
      self.max_iterations = 400;
      self.tau            = 1;
    end

    function delete( ~ )
      %% Destroy the C++ class instance
    end

    function set_max_iteration( self, miter )
      self.max_iterations = miter;
    end

    function [xk,ierr] = solve( self, xinit, fun, jac, check )

      self.f_eval  = fun;
      self.j_eval  = jac;
      self.ck_eval = check;
      self.iter    = 0;

      dim = length(xinit);
      x0  = xinit;
      f0  = feval( self.f_eval, x0 );
      J0  = feval( self.j_eval, x0 );

      if ~all(isfinite(f0))
        disp(f0);
        fprintf( 'LM: Bad f(x)!\n' );
        ierr = 2;
        return;
      end

      mu = self.tau;%full(max(max(abs(J0))));
      nu = 2;

      % gradient
      g0       = J0.'*f0;
      normi_g0 = norm( g0, inf );
      normi_f0 = norm( f0, inf );
      norm2_f0 = norm( f0, 2   );

      for k=1:self.max_iterations
        self.iter = k;
        xk = x0;

        %D  = sparse(diag(max(abs(J0))));
        D  = sparse(diag(sum(abs(J0)))); % best result
        %D  = sparse(diag(sqrt(sum(J0.^2))));
        %D  = speye(dim);
        dd = [J0;sqrt(mu)*D]\[f0;zeros(dim,1)];
        d0 = -dd(1:dim);

        fprintf( ...
          'iter %3d |g|=%8.3g, |f|=%8.3g, |d|=%8.3g, mu = %8.3g\n', ...
          k, normi_g0, normi_f0, norm( d0, inf ), mu ...
        );

        if norm(d0,inf) < self.tolerance
          fprintf('(STEP TOO SHORT)\n');
          ierr = 3;
          return;
        end

        % check if finished
        if normi_g0 < self.tolerance
          fprintf('(CONVERGED)\n');
          ierr = 0;
          return;
        end

        x1 = x0 + d0;
        ok = feval( self.ck_eval, x1 );
        if ok
          f1       = feval( self.f_eval, x1 );
          norm2_f1 = norm( f1, 2 );
          top      = norm2_f0^2 - norm2_f1^2;
          bot      = dot(mu*d0-g0,d0);
          if top > 0 && bot > 0
            rho      = top/bot;
            J1       = feval( self.j_eval, x1 );
            g1       = J1.'*f1;
            normi_g1 = norm( g1, inf );
            normi_f1 = norm( f1, inf );
            ok       = isfinite(normi_g1) && isfinite(normi_f1);
            if ok
              nu = 2;
              mu = mu*max(1/3,1-(2*rho-1)^3);
              %if rho < 0.5
              %  mu = mu*4;
              %elseif rho > 0.75
              %  mu = max(mu/4,1e-6);
              %end
            end
           else
            ok = false;
          end
        end

        if ok
          x0 = x1;
          f0 = f1;
          g0 = g1;
          J0 = J1;
          norm2_f0 = norm2_f1;
          normi_f0 = normi_f1;
          normi_g0 = normi_g1;

          % check if finished
          if normi_g0 < self.tolerance || normi_f0 < self.tolerance || norm(d0,inf) < self.tolerance
            fprintf( ...
              'iter %3d |g|=%8.3g, |f|=%8.3g, mu=%8.3g (CONVERGED)\n', ...
              k, normi_g0, normi_f0, mu ...
            );
            xk   = x0;
            ierr = 0;
            return;
          end
        else
          fprintf('(REJECT)\n');
          mu = mu*nu;
          nu = 2*nu;
        end

        if mu > 1e100
          mu = 1e100;
        end

      end
      ierr = 1 ;
    end

    function it = iterations( self )
      it = self.iter;
    end

  end
end
