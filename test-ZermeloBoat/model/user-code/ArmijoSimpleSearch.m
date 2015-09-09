%
% Perform Armijo Line Search
%
% the input are
%   fun  = the function to minimize with the derivative of the function
%   xk   = starting point
%   d    = search direction
%
%  optional extra arguments
%
%    tau   = 0.5    reduction parameter for Armijo algorithm
%    c1    = 10-3   parameter for Armijo test
%    f0    = f(0)   for non monotone line search
%    lmin  = 1E-8   minimum step length
%    lmax  = 1E+8   maximum step length
%
function lambda = ArmijoSimpleSearch( fun, xk, d, varargin )

  fX0  = feval( fun, 'f', xk ) ;
  opts = { 'c1', 'c2', 'tau', 'lmin', 'lmax', 'f0' } ;
  defs = { 1E-3,  0.5,   0.5,  1E-20,  1E+10, fX0  } ;

  OPTS = parseArgs( opts, defs, varargin{:} ) ;

  lambdaMin = OPTS . lmin ;
  lambdaMax = OPTS . lmax ;
  tau       = OPTS . tau  ;
  c1        = OPTS . c1   ;
  f0        = OPTS . f0   ;

  if any(isnan(xk)) & any(isinf(xk))
    disp(xk) ;
    fprintf( 1, 'ArmijoSimpleSearch: Bad initial point!' ) ;
    lambda = NaN ;
    return ;
  end
  
  lambda  = 1 ;
  fLambda = feval( fun, 'f', xk + lambda * d ) ;
  Df0     = feval( fun, 'Df', xk ) * d ;

  if isnan(Df0) | Df0 == 0
    fprintf( 1, 'ArmijoSimpleSearch: Bad search direction Df0 = %g', Df0 ) ;
    lambda = NaN ;
    return ;
  end

  rev = 1 ;
  if Df0 >= 0
    fprintf( 1, 'ArmijoSimpleSearch: Bad search direction Df0 = %g, reversing\n', Df0 ) ;
    Df0 = -Df0 ;
    d   = -d ;
    rev = -1 ;
  end

  c1Df0 = c1 * Df0 ;
  if fLambda <= f0 + lambda*c1Df0
    % forward search
    fOld    = fLambda ;
    lambda  = lambda/tau ;
    fLambda = feval( fun, 'f', xk + lambda * d ) ;
    while (fLambda <= f0 + lambda*c1Df0) & (fLambda < fOld) & lambda < lambdaMax
      fOld    = fLambda ;
      lambda  = lambda/tau ;
      fLambda = feval( fun, 'f', xk + lambda * d ) ;
    end ;
    lambda = lambda*tau ;
  else
    % backward search
    while fLambda > f0 + lambda*c1Df0
      if lambda < lambdaMin 
        fprintf( 1, 'ArmijoSimpleSearch: lambda=%g too short!', lambda ) ;
        lambda = NaN ;
        return ;
      end ;
      lambda  = lambda * tau ;
      fLambda = feval( fun, 'f', xk + lambda * d ) ;
    end ;
  end ;
  lambda = rev * lambda ;
end
