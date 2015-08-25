function varargout = clip( varargin )
  if nargin == 1
    ClipIntervalWithErf('clip', varargin{:} ) ;
  elseif nargin == 3
    varargout{1} = ClipIntervalWithErf('clip', 'eval', varargin{:} ) ;  
  else
    varargout{1} = ClipIntervalWithErf('clip', varargin{:} ) ;
  end
end
