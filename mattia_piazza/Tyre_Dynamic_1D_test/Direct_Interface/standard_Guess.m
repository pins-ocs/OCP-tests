%% DIRECT OCP - STATES & CONTROL GUESS - - - - - - - - - - - - - - -
% Author: Mattia Piazza
function x0 = standard_Guess(self) 
	% bounds()
	% Define guess for all states and controls

	oneN      = ones(1,self.N);
	oneN_1    = ones(1,(self.N-1));
	v__g       = oneN * double( self.pins_data.Parameters.v__ss );
	omega__g   = oneN * double( self.pins_data.Parameters.omega__ss );
	lambda__g  = oneN * double( self.pins_data.Parameters.lambda__ss );
	p__g       = oneN * double( self.pins_data.Parameters.p__ss );
	b__g       = oneN * double( self.pins_data.Parameters.b__ss );
	p__o__g    = oneN_1 * 0 ;
	b__o__g    = oneN_1 * 0 ;

	x_g = reshape([ v__g; omega__g; lambda__g; p__g; b__g;  ], 1, self.N*self.nx );
	u_g = reshape([ p__o__g; b__o__g;  ], 1, (self.N-1)*self.nu );
	x0 = [ x_g , u_g ] ;
end 
