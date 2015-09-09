function [xk,fk,niter,ierr] = NewtonNonlinear( fun, X0, varargin )
  global NewtonNonlinear_fun ;

  ierr = 0 ;

  NewtonNonlinear_fun = fun ;

  opts = { 'tol', 'linesearch', 'maxiter', 'c1', 'c2', 'tau', 'lmin', 'lmax', 'plotstep' } ;
  defs = {  1E-8,            1,       100, 1E-3,  0.5,   0.5,   1E-8,   1E+8, @plotnone } ;

  OPTS = parseArgs( opts, defs, varargin{:} ) ;

  TOL        = OPTS.tol ;
  tau        = OPTS.tau ;
  c1         = OPTS.c1 ;
  c2         = OPTS.c2 ;
  maxiter    = OPTS.maxiter ;
  linesearch = OPTS.linesearch ;
  plotstep   = OPTS.plotstep ;

  if any(isnan(X0))
    disp(X0) ;
    fprintf(1, 'NewtonNonlinear: Bad initial point!\n' ) ;
    ierr = 1 ;
    return ;
  end

  if linesearch < 0 | linesearch > 3
    fprintf( 1, 'NewtonNonlinear: lineserarch=%d must be in [0,3]\n',linesearch) ;    
    ierr = 2 ;
    return ;
  end

  xk = X0 ;
  for niter=1:maxiter
    % evaluate merit function and gradient
    fk = merit( 'f', xk ) ;
    fprintf(1,'iter %d ||f|| = %g (%g)\n',niter,sqrt(fk),TOL ) ;
    % check if finished
    if sqrt(fk) < TOL
      return ;
    end
    % direction search
    [Fk,Jk] = feval( fun, xk ) ;
    d  = -Jk\Fk ;
    % do line search
    switch linesearch
      case 0 ; alpha = 1 ; % no line search
      case 1 ; alpha = ArmijoSimpleSearch( @merit, xk, d, 'c1', c1, 'tau', tau ) ;
      case 2 ; alpha = ArmijoLineSearch( @merit, xk, d, 'c1', c1 ) ;
      case 3 ; alpha = WolfeLineSearch( @merit, xk, d, 'c1', c1, 'c2', c2 ) ;
    end
    if ~isfinite(alpha)
      break ;
    end
    xk = xk + alpha * d ;
    feval( plotstep, xk, X0 ) ;
  end
  ierr = 1 ;
end

function plotnone( xk, x0 )

end

function RES = merit( what, varargin )
  global NewtonNonlinear_fun ;
  
  switch what
  case 'f'  ; F   = feval( NewtonNonlinear_fun, varargin{:} ) ;
              RES = (1/2)*dot(F,F) ;
  case 'Df' ; [F,JF] = feval( NewtonNonlinear_fun, varargin{:} ) ;
              RES = F' * JF ;
  end
end
