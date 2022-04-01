%% DIRECT OCP - STATES & CONTROL BOUNDS - - - - - - - - - - - - - - -
% Author: Mattia Piazza
function [x_lb,x_ub,u_lb,u_ub] = bounds(self, varargin) 
	% bounds()
	% define bounds for all states and controls

	oneN      = ones(1,self.N);
	oneN_1    = ones(1,(self.N-1));
	v__ub      = oneN * double( self.pins_data.Parameters.v__ub );
	v__lb      = oneN * double( self.pins_data.Parameters.v__lb );
	omega__ub  = oneN * double( self.pins_data.Parameters.omega__ub );
	omega__lb  = oneN * double( self.pins_data.Parameters.omega__lb );
	lambda__ub = oneN * double( self.pins_data.Parameters.lambda__ub );
	lambda__lb = oneN * double( self.pins_data.Parameters.lambda__lb );
	p__ub      = oneN * double( self.pins_data.Parameters.p__ub );
	p__lb      = oneN * double( self.pins_data.Parameters.p__lb );
	b__ub      = oneN * double( self.pins_data.Parameters.b__ub );
	b__lb      = oneN * double( self.pins_data.Parameters.b__lb );
	p__o__ub   = oneN_1 * double( self.pins_data.Parameters.p__o__ub );
	p__o__lb   = oneN_1 * double( self.pins_data.Parameters.p__o__lb );
	b__o__ub   = oneN_1 * double( self.pins_data.Parameters.b__o__ub );
	b__o__lb   = oneN_1 * double( self.pins_data.Parameters.b__o__lb );

	x_ub = reshape([ v__ub; omega__ub; lambda__ub; p__ub; b__ub;  ], 1, self.N*self.nx );
	x_lb = reshape([ v__lb; omega__lb; lambda__lb; p__lb; b__lb;  ], 1, self.N*self.nx );
	u_ub = reshape([ p__o__ub; b__o__ub;  ], 1, (self.N-1)*self.nu );
	u_lb = reshape([ p__o__lb; b__o__lb;  ], 1, (self.N-1)*self.nu );
end 
