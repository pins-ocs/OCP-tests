function varargout = clip( varargin )
  if nargin == 1
    ClipIntervalWithSinAtan('clip', varargin{:} ) ;
  elseif nargin == 3
    varargout{1} = ClipIntervalWithSinAtan('clip', 'eval', varargin{:} ) ;  
  else
    varargout{1} = ClipIntervalWithSinAtan('clip', varargin{:} ) ;
  end
end
